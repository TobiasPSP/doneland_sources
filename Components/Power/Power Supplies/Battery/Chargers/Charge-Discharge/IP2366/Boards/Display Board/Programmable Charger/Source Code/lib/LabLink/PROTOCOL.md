# LabLink wire protocol 1.2

The charger schemas below are unchanged. Minor 1 adds meter kinds 32..39
([meter extension](METER-PROTOCOL.md)); minor 2 adds SMBus Adapter kinds 48..49
([adapter extension](ADAPTER-PROTOCOL.md)). The adapter assigns capability bits
0x1000/2000/4000/8000 and unit 14 (mAh); all existing assignments remain stable.

All integers are explicitly serialized little-endian. Signed values use two's complement. No native struct layout, floats or pointer values appear on the wire. The maximum datagram is 250 bytes, with a 40-byte header and at most 210 payload bytes. Unencrypted traffic intentionally provides no sender authentication.

## Header

| Offset | Bytes | Meaning |
|---|---:|---|
| 0 | 4 | Magic `4c 41 4c 31` (`LAL1`) |
| 4 | 1 | Major version, currently 1 |
| 5 | 1 | Minor version, currently 0 |
| 6 | 1 | Message kind |
| 7 | 1 | Header length, currently 40 |
| 8 | 2 | Flags, currently zero; unknown flags rejected |
| 10 | 2 | Payload length |
| 12 | 4 | Sender sequence; nonzero |
| 16 | 4 | Sequence being answered, or zero |
| 20 | 8 | Sender device ID; nonzero |
| 28 | 4 | Sender boot ID; nonzero |
| 32 | 4 | Target boot ID; zero only for discovery/advertisements |
| 36 | 4 | Session ID, or zero when idle/unknown |

Total length must match header length + payload length exactly. Header extensions are skipped using header length; unknown major versions are rejected. Typed payloads accept trailing minor-version additions. Capability records have their own lengths so optional fields can be skipped. Unknown message kinds are ignored/rejected rather than dispatched as another command. Advertisements include equipment type; device identity, type and boot identity are independent.

The client requires unicast replies from the selected MAC, device ID and boot, targeted at its own boot. Servers must enforce target boot, subscriber boot and session requirements; a packet addressed to an older server boot must never execute a command. Sequence numbers are global per sender boot, but command replay and owner-heartbeat replay use separate high-water marks. A command retry retains its original sequence and content.

## Message kinds

| ID | Kind | Payload |
|---|---|---|
| 1 | Discover | Empty; broadcast |
| 2 | Advertise | Advertisement |
| 3 | Subscribe | Subscription |
| 4 | Unsubscribe | Subscription |
| 5 | Heartbeat | Heartbeat |
| 6 | HeartbeatAck | HeartbeatAck |
| 7 | GetCapabilities | CapabilityRequest |
| 8 | Capabilities | CapabilityPage |
| 9 | GetConfig | Empty |
| 10 | Config | ChargerConfig |
| 11 | Telemetry | Telemetry |
| 12 | Start | StartRequest |
| 13 | Abort | Empty; session in header |
| 14 | Result | Result |

All unicast command replies set `replyTo` to the requesting sequence. Success means applied by the equipment adapter, not merely received. Result code 0 is Applied, 1 Rejected, 2 ConfirmationRequired; code 3 Timeout is a locally generated client result. `reason` is a machine-readable equipment-specific detail, `message` supplies readable context. Duplicate commands return their original reply. A server should reject a reused ID with changed payload.

## Payload schemas

`u8/u16/u32/u64/i32/i64` indicate byte width and signedness. Strings are a `u8` byte length followed by those bytes, with no trailing NUL. Local decoded arrays always receive a terminating NUL. Oversized strings and truncated fields fail decoding.

- **Advertisement:** `type:u16, capabilities:u32, channel:u8, name:string[31], firmware:string[19]`. Capability bits: 0 Subscribe, 1 ReadConfig, 2 Start, 3 Abort, 4 OwnerHeartbeat, 5 FullCapabilities.
- **ChargerConfig:** `chemistry:u8, cells:u8, targetPercent:u8, cell_mV:u16, current_mA:u16, termination_mA:u16`. Chemistry IDs: 0 LiFePO4, 1 Li-ion, 2 LiHV; 255 denotes unavailable/not configured. This is an encoding range; only the controller's documented profile limits are accepted. Voltage is per cell; current settings are nonnegative magnitudes.
- **StartRequest:** complete ChargerConfig followed by `proceed:u8, confirmationToken:u32`. Booleans must be exactly 0 or 1. A first request cannot bypass an undetected-battery confirmation by setting proceed; the adapter must validate a previously issued token and exact profile.
- **Subscription:** `subscriptionId:u32, interval_ms:u16`. ID is a client-generated nonzero counter per boot. Subscribe acknowledges acceptance; the client then sends heartbeats. Ordinary observer timeout must never stop an unowned/manual session.
- **Heartbeat:** `subscriptionId:u32, owner:u8`. Target session is in header. Only a fresh received owner heartbeat with all identity/session/subscription checks may renew an owned charge. `owner=false` never renews a charge lease.
- **HeartbeatAck:** `subscriptionId:u32, channel:u8, owner:u8`. Header reports current session. Owner indicates whether that client is the current owner.
- **Result:** `code:u8, reason:u16, confirmationToken:u32, effective:ChargerConfig, message:string[95]`. Effective profile applies only where meaningful; fields must not be interpreted as accepted settings after rejection.
- **CapabilityRequest:** `page:u8`.
- **CapabilityPage:** `page:u8, pageCount:u8, count:u8, revision:u32`, then up to 5 records. Each record is `recordLength:u8` (currently 35), followed by `propertyId:u16, access:u8, unit:u8, valueType:u8, flags:u16, minimum:i64, maximum:i64, step:i64, enumMask:u32`. Unknown property IDs/optional record bytes can be skipped. Maximum/minimum describe supported values, not accuracy. Enum mask uses bit N for enum N when N <32; other enum values require a future extension.

### Telemetry

Fields appear in this order:

| Field | Encoding | Interpretation |
|---|---|---|
| state | u8 | 0 Missing, 1 Idle, 2 Starting, 3 Charging, 4 Complete, 5 Aborted, 6 Fault |
| stopReason | u16 | 0 None, 1 Complete, 2 Abort, 3 OwnerLost, 4 HardwareFault, 5 Startup, 6 Communication |
| validity | u16 | Bits 0 voltage, 1 current, 2 temperature, 3 SOC, 4 totals |
| sampleAge_ms | u32 | Milliseconds since the equipment's latest measurement |
| voltage_mV | u32 | Pack voltage in millivolts |
| current_mA | i32 | This charger reports nonnegative charging-current magnitude; no discharge measurement is claimed |
| temperature_cC | i32 | Centidegrees Celsius; divide by 100 exactly once at display boundary |
| soc_percent | u8 | Estimated SOC, 0–100; validity bit required |
| elapsed_ms | u32 | Session milliseconds, saturated at UINT32_MAX if necessary |
| charge_uAh | u64 | Delivered charge in microampere-hours; divide by 1000 for mAh |
| energy_uWh | u64 | Delivered energy in microwatt-hours; divide by 1000 for mWh |
| ownerDeviceId | u64 | Zero for manual/web/unowned sessions |
| ownerBootId | u32 | Owner's boot identity, or zero |
| disableConfirmed | u8 | Whether hardware charger disable has been verified |
| target_mV | u32 | Effective target pack voltage |
| effectiveCurrent_mA | u32 | Actual configured current limit after policy limiting |
| termination_mA | u16 | Termination threshold |
| ownerRemaining_ms | u32 | Remaining lease time, or zero for unowned/expired sessions |

Unavailable is not zero. Consumers must use validity and freshness. NTC is monitoring-only; SOC is a chemistry-curve estimate. Actual hardware measurement range/accuracy belongs to the equipment's verified integration documentation, not to this packet's integer encoding range.

### Property registry

IDs `0x0100` chemistry, `0101` series cells, `0102` cell-end mV, `0103` target %, `0104` requested current mA, `0105` termination mA, `0106` effective current mA, `0107` target pack mV; `0110` battery mV, `0111` current mA, `0112` NTC centi°C, `0113` estimated SOC %, `0114` elapsed ms, `0115` charge µAh, `0116` energy µWh; `0120` operating state, `0121` stop reason, `0122` session owner; commands `0180` ConfigureAndStart, `0181` Abort, `0182` Subscribe, `0183` Unsubscribe.

Access: 1 Read, 3 ProfileWrite (read plus write only through a complete validated Start profile), 4 Command. Unit: 0 None, 1 Enumeration, 2 Count, 3 mV, 4 mA, 5 Percent, 6 CentiCelsius, 7 Milliseconds, 8 MicroAh, 9 MicroWh, 10 DeviceId, 11 Boolean. Value type: 0 generic unsigned, 1 generic signed, 2 Enumeration, 3 Boolean, 4 Identifier, 5 Command, 6 UInt8, 7 UInt16, 8 UInt32, 9 UInt64, 10 Int32, 11 Int64. The registry above fixes actual wire widths even when a descriptor uses a generic type.

Flags: bit 0 Measured, 1 Estimated, 2 Calculated, 3 MonitoringOnly, 4 CompleteProfile, 5 DynamicLimit, 6 SignedChargePositive (reserved for equipment that truly supports signed charge-positive measurement; not set for this charger), 7 Conditional. Range fields are signed 64-bit to cover practical counter and setting ranges; a property without a useful numeric range should be typed Identifier/Command rather than implying measured accuracy. Limits dependent on chemistry, cell count or power need the DynamicLimit/Conditional flags and remain subject to full-profile controller validation.

## Extending the protocol

Add equipment type and property assignments without changing existing IDs. Add optional trailing payload fields only when old receivers can safely ignore them. Incompatible mandatory semantics require a new major version. Capability discovery and read-only status do not grant control ownership. Future equipment-specific commands must use newly assigned kind values and must not reinterpret existing charger commands.


## Current-meter extension (1.1)

See [METER-PROTOCOL.md](METER-PROTOCOL.md) for kinds 32..39, meter capabilities, units and command semantics. Charger payloads remain unchanged.
