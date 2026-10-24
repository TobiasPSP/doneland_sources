# LabLink 1.2.0

Version 1.2 adds the **SMBus Adapter** (equipment 0004): cached battery data,
global YAML actions with confirmation, and graph controls/settings/paged history.
See [ADAPTER-PROTOCOL.md](ADAPTER-PROTOCOL.md). The 1.1 meter extension is documented
in [METER-PROTOCOL.md](METER-PROTOCOL.md). Charger and meter wire layouts and IDs
remain unchanged; the shared packet/client handles all three equipment types.

Small, unencrypted ESP-NOW protocol for lab equipment. The portable codec and client do not depend on Arduino. The optional ESP32 transport targets the **exact Arduino ESP32 2.0.17 / ESP-IDF 4.4 interfaces** used by the charger and test tablet. ESP-IDF 5.x callback signatures differ and are not supported by this adapter.

The reusable library contains no charger register operations, battery safety limits or automatic charge-start policy. Equipment adapters provide those through the same validated controller used by their local UI.

## Equipment registry

| ID | Equipment |
|---|---|
| `0x0000` | Unspecified |
| `0x0001` | Battery Charger |
| `0x0002` | Electronic Load |
| `0x0003` | Current Meter |
| `0x0004` | SMBus Adapter |
| `0x0005` | Power Supply |
| `0x0006` | USB PD Trigger |

Assignments are permanent; future types receive new values. Equipment type is distinct from unique device identity. `deviceIdFromMac()` namespaces the six-byte STA MAC into a stable 64-bit identity (`0x4c4c` prefix), independent of whether the radio currently sends through STA or AP. Boot identity must be a fresh nonzero random 32-bit value on every boot.

## Client integration

Include `LabLink.h`. The caller initializes WiFi in STA mode and disables WiFi sleep, then calls `EspNowTransport::begin()`. Call `Client::tick(millis())` regularly from one task. All Client methods and transport lifecycle operations belong to that same task.

```cpp
lablink::EspNowTransport transport;
// After WiFi.mode(WIFI_STA), WiFi.setSleep(false), and reading STA MAC:
// transport.begin(WIFI_IF_STA);
// lablink::Client client(transport, lablink::deviceIdFromMac(mac), nonzeroBootId);
// loop: client.tick(millis());
```

The client collects up to 12 advertisers. `deviceCount()`, `device(index)` and `select(index)` drive discovery UI; selecting automatically subscribes at 1 second. `subscribe(interval_ms)` clamps the requested interval to 500–5000 ms; the equipment can reject or constrain it further. `clearSelection()` enables scanning again, but refuses to discard an owned live session. Selecting an already selected device preserves the session.

`getCapabilities(page)`, `getConfig()`, `start(completeProfile)` and `abort()` are acknowledged operations. One command is outstanding at a time. `pending()`, `result()`, `eventCounter()`, `config()` and `capabilities()` expose their results. `hasTelemetry()` and `telemetry()` expose the latest readings. Check validity and freshness before displaying a number as current.

A `ConfirmationRequired` Start result is not success. Present its message, and only after explicit user consent call `start(theSameProfile, true, result().confirmationToken)`. The equipment binds confirmation to the profile, requesting boot/device, current session and its local UI revision. Token expiry and validation belong to the equipment adapter.

## Reliability and ownership

An ESP-NOW send returning success means the SDK accepted the packet; it is not an application acknowledgment. Client commands retransmit the same ID every 500 ms for up to 5 seconds. A timeout means the outcome is uncertain: inspect state, never automatically issue a fresh Start. Heartbeats and command sequence high-water marks must be tracked separately by servers, and cached command replies must be returned before replay rejection. A client accepts an outstanding cached response even when newer telemetry has arrived.

The client sends a heartbeat every second with subscription ID, current session and ownership claim. Only a successful Start or telemetry explicitly naming this device **and boot** gives it ownership. Both Starting and Charging retain ownership. An equipment adapter must validate a fresh heartbeat against owner device, boot, subscription and session before extending its lease. Discovery, subscription requests and other observers never extend that lease. Charger owners receive approximately 10 seconds from their last valid received heartbeat before abort; manually/web-started charging has no ESP-NOW owner.

The ESP32 receive callback records the hardware uptime timestamp in milliseconds before queueing data. A server must use `Received.receivedAt_ms`, not a later queue-drain time, for the lease. Duplicate or stale heartbeat sequences must not renew it. The portable `elapsed()` helper handles 32-bit uptime wrap; `newerSequence()` uses modulo sequence ordering with a half-range bound. Sequences skip zero.

After 2.5 seconds without a selected peer response the client searches permitted local channels, dwelling 300 ms each and broadcasting discovery. It retains the same boot/session ownership while searching; rediscovery permits a matching heartbeat to recover. A restarted server clears ownership and pending commands and never restarts charging. `setHeartbeatEnabled(false)` is provided for the test tool; telemetry/subscription can remain active so owner-timeout behavior can be observed.

The charger must stay on its current WiFi/AP channel. Only a dedicated unassociated client may call channel-hunting methods. The SDK prohibits `esp_wifi_set_channel` during STA scanning/connection and with associated AP clients. This library does not disconnect or reconfigure WiFi to evade those restrictions. It queries the configured country channel range rather than assuming all 14 channels are available.

If a subscription expires while the client is silent, a rejected heartbeat causes the client to subscribe again without starting a charge. The charger adapter retains eight distinct device slots for its boot and remembers up to 16 retired boots per device; old-boot Subscribe packets cannot roll replay protection backward. After that bounded reboot history is full, restart the charger to admit another boot of that device. Existing admitted boots continue to work.

## Transport boundary

`Transport` is a portable interface: `receive(Received&)`, `send(mac, packet)`, `setChannel(channel)`, `channel()`, `firstChannel()`, `channelCount()`. Fake implementations support deterministic native tests.

`EspNowTransport::begin(wifi_interface_t)` supports an explicitly chosen active STA or AP interface. It does not start/stop/change WiFi mode. Its receive callback only copies up to 250 bytes, MAC and timestamp to a fixed 12-item FreeRTOS queue with zero wait. Decode and application work run when `receive()` is called. Unencrypted peers use channel 0, meaning the current local channel, and are registered on demand. The SDK limits the peer table to 20; this adapter returns failure when that table is full instead of evicting an active peer. The client discovery limit is 12; a server should bound its subscribers below the peer limit.

Counters expose receive queue drops, malformed packets and immediate SDK send errors. They do not claim to measure RF delivery. Application results and heartbeat acknowledgments establish end-to-end communication. Packet buffers are local because the exact SDK contract says they need not remain valid after `esp_now_send` returns.

`begin/end/send/receive` must be serialized with WiFi lifecycle operations. Keep transport instances at static lifetime, as in the supplied firmware projects, and disable application traffic before shutdown. Receive callback memory is fixed and no heap allocation occurs in the callback.

## Primary interface sources checked

Installed framework: `framework-arduinoespressif32`, Arduino ESP32 **2.0.17**, ESP32-S3 SDK:

- `tools/sdk/esp32s3/include/esp_wifi/include/esp_now.h`: 250-byte maximum, legacy receive callback `(const uint8_t*, const uint8_t*, int)`, channel 0 meaning current channel, peer/interface/encryption fields, explicit send errors, payload lifetime after send.
- `tools/sdk/esp32s3/include/esp_wifi/include/esp_wifi.h`: set/get channel and country calls, radio-start prerequisites and channel-change restrictions.
- `tools/sdk/esp32s3/include/esp_wifi/include/esp_wifi_types.h`: country `schan`/`nchan` units.
- `tools/sdk/esp32s3/include/esp_timer/include/esp_timer.h`: `esp_timer_get_time()` is signed 64-bit microseconds since boot; conversion is performed once to a wrap-safe `uint32_t receivedAt_ms`.
- `tools/sdk/esp32s3/include/freertos/include/freertos/queue.h`: fixed-size copy queues, zero-wait `xQueueSend`/`xQueueReceive`, success `pdTRUE`; WiFi callback is task context, not an ISR.

The wire contract, units and numeric registry are documented in [PROTOCOL.md](PROTOCOL.md). The charger adapter remains authoritative for its hardware and firmware limits.

## Native tests

On Windows with the installed LLVM compiler:

```powershell
& 'C:/Program Files/LLVM/bin/clang++.exe' -std=c++17 -D_CRT_SECURE_NO_WARNINGS -Wall -Wextra -Werror -I src tests/test_lablink.cpp -o test_lablink.exe
./test_lablink.exe
```

The library itself uses C++11 constructs; the Windows standard library used by the test harness requires a newer language mode. Tests check exact little-endian values, malformed/truncated packets, signed/64-bit conversions, bounded descriptor pages, retries, late cached acknowledgments, owner heartbeat during Starting, paused heartbeat, channel recovery, wrong target boot and reboot invalidation. Real radio/channel recovery still requires the two tablets.
