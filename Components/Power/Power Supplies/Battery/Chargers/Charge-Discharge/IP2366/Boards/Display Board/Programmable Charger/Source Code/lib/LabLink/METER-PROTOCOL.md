# LabLink 1.1 current-meter extension

The shared package is now outputs/LabLink 1.2.0. Analyzer, charger and tester
copies are synchronized for the SMBus Adapter integration. Meter wire fields,
message IDs and behavior defined here remain unchanged.

## Compatibility and capabilities

Major 1, minor 1; the 40-byte header, 250-byte packet limit, explicit little-endian
integers, device/boot identity and all charger kinds 1..14 remain unchanged.
Older clients ignore the new message kinds. No charger telemetry is reinterpreted.
Equipment category is 0x0003. Meter capabilities:
- 0x0001 CanSubscribe: shared membership and heartbeat, no unsolicited readings.
- 0x0020 HasCapabilities: shared paged descriptors.
- 0x0100 MeterPoll: GetMeterReadings.
- 0x0200 MeterRecord: GetMeterConfig, atomic configure/start, stop.
- 0x0400 MeterClearConfirmed: device-issued confirmation token for clear.
- 0x0800 MeterTemperatures: protocol supports both NTC positions. Actual presence
  and validity are reported separately in each reading.
The production meter advertises 0x0f21. Charger Start/Abort/ReadConfig and
OwnerHeartbeat flags are not advertised. All lab traffic remains unencrypted;
operation permissions do not authenticate a person or protect against spoofing.

## Messages (decimal kind IDs)

| Kind | Payload in wire order |
|---|---|
| 32 GetMeterReadings | empty |
| 33 MeterReadings | state u8, stopReason u8, validity u16, quality u16, temperaturePresent u8, electricalAge_ms u32, temperatureAge_ms u32, voltage_mV u32, current_mA i32, power_mW i32, internal_cC i32, external_cC i32, charge_uAh i64, energy_uWh i64, duration_ms u64 |
| 34 GetMeterConfig | empty |
| 35 MeterConfig | interval_s u32, length_s i32, autoStop u8 |
| 36 MeterStart | complete MeterConfig |
| 37 MeterStop | empty |
| 38 MeterClear | confirmed u8, token u32 |
| 39 MeterResult | code u8, reason u16 (reserved 0), token u32, length-prefixed UTF-8 message (max 95 bytes) |

Booleans accept only 0/1. Result codes retain Applied=0, Rejected=1,
ConfirmationRequired=2, Timeout=3. Typed payloads accept trailing extension bytes.
Unknown state/stop enum values, malformed boolean values and truncated payloads
are rejected without modifying the caller's decoded value.

States: Ready=0, Recording=1, Completed=2.
Stop reasons: None=0, Manual=1, AutoStop=2, FixedLength=3, Remote=4.
Validity: V=1, I=2, P=4, internal T=8, external T=16, totals=32.
Quality: incomplete integration/measurement gaps=1.
Temperature presence: internal=1, external=2. Absent and invalid differ from zero.
Ages saturate at UINT32_MAX; clients add time since receipt and request/retry
latency. The tester polls once per second independently of the active tab.
No push alarms, alarm acknowledgement, threshold changes or override commands
are provided. Local temperature protection remains independent.

Wire units: mV/1000 -> V; mA/1000 -> A; mW/1000 -> W; cC/100 -> degrees C;
uAh/1000 -> mAh; uWh/1000 -> mWh; milliseconds/1000 -> seconds.
Current follows the existing shunt polarity; positive is not labeled battery
charging. Power=V*I. Charge/energy are signed net trapezoidal integrals for the
recording, not absolute-throughput counters. Overflow/nonfinite totals invalidate
the totals bit instead of wrapping. Quantization is not an accuracy guarantee.
Duration uses 64 bits; descriptor maximum is INT64_MAX because descriptor bounds
are signed. The implementation never approaches this representational bound.

## Properties

Allocated IDs (not the tester fixture's synthetic 0x3001):
0x0300 V, 0301 I, 0302 P, 0303 internal NTC, 0304 external NTC,
0305 net charge, 0306 net energy, 0307 duration, 0308 state, 0309 stop reason;
0310 interval, 0311 length, 0312 AutoStop;
0380 configure/start, 0381 stop, 0382 confirmed clear.

Units add mW=12 and Seconds=13; all existing unit numbers are unchanged.
Readings are read-only. Interval/length/AutoStop have ProfileWrite access and
CompleteProfile flag: writable only as a complete valid MeterStart payload.
There is no generic property write. The three actions have Command access.
Four capability pages contain at most five descriptors each.

Interval: whole seconds 1..86400. Length: -1 unlimited or 1..31536000 seconds;
zero is invalid even though it lies within the descriptor's numeric bounds.
AutoStop is true/false; this adapter stops after |I| <=30 mA for >20 seconds.
Meter adapter acquisition bounds: V 0..85000 mV; rounded I +/-204790 mA;
P +/-17407150 mW; both NTCs -4000..12500 cC.
These are validated firmware ranges, not continuous hardware ratings.
Internal temperature means the internal external-to-chip NTC, not INA die temperature.

## Membership, commands and recording lifetime

Subscribe precedes reads/actions. A valid Subscribe replies with shared
HeartbeatAck, owner=false. Heartbeat every 1 second maintains membership.
A membership older than 10 seconds cannot issue commands until a heartbeat or
resubscription refreshes it. The subscription interval field does not schedule
push telemetry for meters: use polling. Any subscribed observer may stop or clear.

Recording does NOT have a remote-owner lease: loss of a tester never stops it.
Local button/web controls remain usable. Mutations carry the last observed
header sessionId. The application checks that identity under its recorder mutex.
Session identity changes on local/remote clear and start, not on each sample.
A completed recording must be cleared before starting another.
Start atomically validates a full profile and healthy fresh sensors, then starts.
Remote profiles are RAM-only and become the current running profile; NVS defaults,
WiFi credentials and temperature settings are not written by LabLink.

Clear is permitted while recording. Tester shows confirmation first, then sends
confirmed=false/token=0. Device returns ConfirmationRequired with a nonzero token.
Tester sends confirmed=true with that token only for the same session shown in
the dialog. The device binds it to peer device ID, boot ID, MAC and session;
it expires after 30 seconds and is consumed on attempted use.
Clear stops/erases the recording, returns Ready and resets the local thermal
override just like a long button press; it does not acknowledge sensor faults.

Commands use one in-flight request, retry the SAME sequence every 500 ms up to
5 seconds. A duplicate replays the cached result, without a second action.
An SDK send success is not an application acknowledgement. On timeout inspect
the device: the operation might have completed. Heartbeats have an independent
sequence high-water mark. Changed payload with the same sequence is ignored.
The server retains eight device identities and up to sixteen retired boots per
identity until meter reboot; exhausted tables reject further identities/boots
instead of reopening old replay windows. These limits are bounded lab resources.

## Threading and verification

ESP-NOW callbacks only enqueue bounded packets. A separate meter task processes
commands; the application mutex protects recorder state. A radio mutex serializes
WiFi lifecycle/scan API calls with transport methods, not HTTP transfers or I2C.
The meter stays on its WiFi/AP channel; the tester performs discovery/recovery.
Arduino ESP32 2.0.17 / IDF 4.4 headers were checked for callback signature, 250-byte
payload maximum, channel=0 peer semantics and send-buffer lifetime.

Portable tests cover signed limits, malformed/truncated codecs, descriptor pages,
lost replies, duplicate mutations, active clear, stale sessions, retired boots,
wrong target boot and recording continuing after client loss. Existing charger
client/codec tests must pass. Tester previews cover actual meter screen selection,
valid/invalid/stale values, confirmations/cancellation and overlay cleanup.
Physical WiFi/channel coexistence and dual-device radio tests remain bench checks.
