# LabLink 1.2: SMBus Adapter

Equipment type **0x0004**. Header, 250-byte maximum, charger kinds 1..14,
meter kinds 32..39, and existing field/unit assignments are unchanged.
The adapter adds kind **48 AdapterRequest**, **49 AdapterResponse**. All integers
are explicitly little-endian; signed integers use two's complement. Unknown
optional trailing payload bytes are allowed. Charger/meter telemetry is never
reinterpreted as adapter data.

Advertisement flags: Subscribe 0x0001, Capabilities 0x0020, AdapterPoll 0x1000,
AdapterActions 0x2000, AdapterHistory 0x4000, AdapterControl 0x8000. Default name
is `SMBus Adapter`. Identity is the existing STA-MAC-derived ID plus random boot
ID. Unencrypted membership is an operational permission, not authentication.

## Requests

Every request contains, in order:

`op:u8, index:u16, targetRevision:u32, recordingId:u32, generation:u32,
offset:u32, autoStop:u8, deadband_mA:u16, confirmed:u8, token:u32`.

Booleans accept exactly 0 or 1; unknown operations fail decoding.

| Op | Meaning | Parameters / access |
|---|---|---|
| 0 | Readings | Read cached battery dataset; no SMBus transactions |
| 1 | ActionInfo | Read action at zero-based `index` |
| 2 | Execute | Invoke stable action ID in `index`; selected DUT address |
| 3 | DiscoverDut | Scan, identify and populate dataset |
| 4 | Refresh | Read selected gauge's dataset, without identification |
| 5 | GraphInfo | Read graph metadata |
| 6 | GraphPage | Read up to four raw samples at `offset`, with recording ID/generation |
| 7 | GraphStart | Start or resume; preserve existing history |
| 8 | GraphPause | Pause; retain history |
| 9 | GraphClear | Confirmed pause and erase; new recording ID/generation |
| 10 | GraphConfig | Set `autoStop` and `deadband_mA` atomically |

Subscribe before requests. Any subscribed peer can read and mutate. All mutations
except DiscoverDut require the current `targetRevision` from Readings. Graph
mutations also require current recording ID/generation. Selection changes pause
an active recording; resuming history against a different selected target is
rejected until Clear. Start/Resume does not take a remote-owner lease. Losing
a client never stops a recording. Multiple observers share the same model.

All action definitions come from the analyzer's `definitions/actions.yaml`.
They are available with any selected gauge, including before gauge identification
if a DUT address has been selected. The firmware uses the same transaction
executor locally and remotely. There is no arbitrary remote raw-write endpoint.

For `confirm:true`, first send Execute with confirmed=false/token=0. The response
is ConfirmationRequired with a nonzero token and the YAML confirmation message.
Display that message, then resend the same operation/action/target/recording with
confirmed=true and token only after user acceptance. Clear uses the same flow.
Tokens bind MAC/device/boot, action/operation, target revision and recording, expire
after 30 seconds, and are consumed on attempted use. `confirm:false` executes
directly. Physical exchange/identity of a DUT cannot be inferred from its address.

Command retries retain exactly the original packet and sequence. Four replies per
peer are cached; older sequences outside the cache are rejected rather than
executed again. Separate heartbeat and command high-water marks are retained.
Eight peer identities and sixteen retired boots per peer are bounded resources.
Subscriptions expire after 10 seconds without fresh heartbeats; expiry does not
stop recording. Old target boots cannot execute requests. Standard retry interval
is 500 ms. Discovery, dataset refresh and first graph Start allow up to 120 seconds
for battery I/O; other requests time out after 5 seconds. A timeout leaves the
outcome uncertain; inspect state before issuing a new mutation.

## Responses

Common prefix: `op:u8, result:u8, token:u32`. Results retain Applied=0,
Rejected=1, ConfirmationRequired=2. Timeout=3 is generated locally by clients.
Rejected/confirmation responses contain a length-prefixed string of at most
139 bytes. Applied responses contain the operation-specific payload below.
Success means execution completed, not merely queued or radio delivery accepted.

### Cached readings (op 0)

Wire order:

```
targetRevision:u32, age_ms:u32, validity:u32,
address:u8, stringCount:u8,
family:string[31], flavor:string[31], security:string[23], manufactured:string[15],
voltage_mV:u32, designVoltage_mV:u32, chargeVoltage_mV:u32,
design_mAh:u32, full_mAh:u32, remaining_mAh:u32,
current_mA:i32, temperature_cC:i32,
soc_percent:u16, health_percent:u16, cycles:u16, chargingCurrent_mA:u16,
cells_mV:8*u16, cellValidity:u16, batteryStatus:u16, flags:u8
```

Validity bits 0..12: pack voltage, current, SOC, temperature, design capacity,
FCC, remaining capacity, health, cycles, design voltage, charging voltage,
charging current, battery status. Cell validity uses bits 0..7 for Cells 1..8.
Flags: bit0 Full/Empty information available, bit1 Full, bit2 Empty. Unsupported,
invalid, or stale-dataset values must not be presented as valid zeros. An empty
dataset reports validity zero and age UINT32_MAX. A poll never refreshes I2C.

Units: mV, calibrated signed mA from the selected gauge's existing data model,
centidegrees Celsius, mAh, percent, milliseconds. Presentation converts mV/mA
to V/A by dividing by 1000 and cC to C by dividing by 100. The existing gauge
boundary converts 0.1 K with `(raw-2732)*10` cC; raw zero is invalid. Capacity
mode conversions stay in the gauge collector, not the LabLink layer. Current
is the application's charge-positive convention, not a charger magnitude.
Gauge-dependent calibration/interpretation comes from the selected profile;
protocol encoding ranges are not physical measurement-accuracy claims.

### Action catalog (op 1)

`id:u16, total:u16, name:string[39], confirm:u8, confirmation:string[139]`.
Index positions are zero-based and can change; the stable YAML numeric ID is
used for Execute. Catalog content is independent of selected chip. A changed
firmware catalog requires a reboot/new boot ID. The current tester displays up
to 32 entries and reports overflow explicitly.

### Graph metadata and mutation results (ops 5, 7..10)

```
recordingId:u32, generation:u32, revision:u32, count:u32, duration_ms:u64,
recording:u8, autoStop:u8, deadband_mA:u16, stop:u8
```

Stop reasons: None=0, Manual=1, Full=2, Empty=3, NoCurrent=4, StorageFull=5,
DutChanged=6. Revision changes on samples/state/settings changes. ID/generation
change on Clear. Current implementation preserves every raw sample, so append
does not change the generation or invalidate existing offsets. `duration_ms`
is the latest sample's timestamp. Pauses retain elapsed-time gaps on resumption.

Auto-stop defaults ON. Deadband defaults to 0 mA (range 0..32767), using
`abs(calibratedCurrent_mA) <= deadband_mA` continuously for **more than** 10 seconds.
Invalid readings or a gap over 2500 ms restart the continuity timer. Valid
SOC >=100 or a supported BMS Full flag stops with Full only with valid positive
current; both full criteria are ignored during negative-current discharge.
Valid SOC 0 stops with negative current only, with reason
Empty. A final dataset/sample is attempted before pausing. Settings persist in
NVS and apply to both local and remote starts. Recording defaults to 30 s and is
locally configurable from 1..3600 s
in Graph settings. Existing GraphConfig packets retain this local setting; the
packet schema is unchanged. Capability 0431 reports that supported interval range.
Actual elapsed timestamps, not an assumed fixed interval, determine history X.
The one-second current/SOC/status/voltage monitor remains independent of the
stored-sample interval.

### History page (op 6)

`recordingId:u32, generation:u32, offset:u32, count:u8, samples:count*GraphPoint`.
Count is at most four. Each GraphPoint contains:

```
at_ms:u64, validity:u16, voltage_mV:u32, current_mA:i32,
soc_percent:u16, cells_mV:8*u16, flags:u8
```

Validity: bit0 pack, bit1 current, bit2 SOC, bits3..10 Cells 1..8.
Flags: bit0 Full/Empty available, bit1 Full, bit2 Empty. Timestamps determine X
coordinates. Invalid values leave gaps. Read metadata, capture count N, then
request offsets 0,4,8..N; append-only updates can subsequently be fetched from N.
A changed ID/generation requires restarting retrieval. The server does not read
SMBus to serve history. Raw history grows in PSRAM; exhaustion pauses with an
explicit StorageFull reason, never a rolling window or silent decimation.

The tester uses up to 300 evenly spaced raw positions spanning the captured
history, showing its resolution. Other clients can retrieve every point.
Tablet and web render bounded full-span views. All use the same timestamp units.

## Capability/property registry

New unit 14=mAh; existing unit IDs are unchanged. Adapter property names and
descriptors live in `adapterCapabilities()` / `adapterPropertyName()`:
0400 aggregate data, 0401 voltage, 0402 current, 0403 SOC, 0404 temperature,
0405 design capacity, 0406 FCC, 0407 remaining capacity, 0408 string count;
0410..0417 Cell1..8 voltages; 0420 health, 0421 security, 0422 cycles;
0430 history, 0431 interval, 0432 auto-stop, 0433 deadband;
0440 design voltage, 0441 charge voltage, 0442 charge current, 0443 date;
0480 discovery, 0481 refresh, 0482 execute action, 0483 start/resume,
0484 pause, 0485 clear, 0486 graph configuration, 0487 action catalog.

Numeric properties are read-only; 0432/0433 are ProfileWrite only through the
complete GraphConfig operation. Actions and graph/discovery mutations have
Command access. Conditional flags denote gauge-dependent validity. Numeric
descriptor limits describe representation/accepted settings, not accuracy.

## Integration/verification boundary

The analyzer serializes LabLink, LVGL, SMBus and WiFi lifecycle calls on the
application task. The ESP-NOW callback only copies packets into the existing
fixed queue. It never calls I2C or LVGL. HTTP serves published cached fragments
on its existing task. The adapter stays on its WiFi channel; the tester hunts
permitted channels, preserving existing charger/meter behavior.

Verified against installed Arduino ESP32 2.0.17 / ESP-IDF 4.4 sources: callback
signature/250-byte limit/send buffer lifetime in esp_now.h; channel-change
restrictions in esp_wifi.h; Wire.cpp STOP/repeated-START, return codes and exact
requestFrom byte-count semantics. Wire endTransmission(false) defers the actual
write/read exchange until requestFrom; read success requires exactly two bytes.
Physical radio coexistence and real battery command behavior require bench tests.
