# ESP-NOW milestone — BatCharger 1.3.0

This release implements the agreed unencrypted LabLink protocol and supplies a separate LabEspNowTester 1.0.0 project for an identical JC3248W535 tablet. Neither build nor packaging flashes physical devices.

## First use

1. Upload BatCharger 1.3.0 to the charger tablet. Enable **ESPNow** in Gear > Settings or web Settings. The option is always persisted independently of Persist charger config.
2. Upload LabEspNowTester 1.0.0 to the second tablet. It does not initialize GPIO17/18/6 or communicate with IP2366.
3. In Devices select the charger. Inspect identity, capability pages, configuration and telemetry. Selection subscribes but never starts a charge.
4. To test control, review the entire Profile and confirm Configure and Start. A device-issued no-battery confirmation is a separate, explicit step. Abort is available on Inspect.

ESP-NOW-only operation keeps the radio active in STA mode on channel 6 while WiFi networking is off. With WiFi Join/AP enabled, ESP-NOW follows that radio channel. The charger never hops channels for a client. The tester searches the SDK-permitted country channels and follows a selected instrument; it is not a scanner for unrelated third-party ESP-NOW protocols.

## Ownership and reliability

Each ESP-NOW Start submits the complete profile atomically. Hardware validation, the 100 W battery-side cap, IP2366 setup/readback, fault handling and persistence are the same existing controller path. The adapter does not add register meanings. Starts are rejected while active; there is no takeover or live profile modification. A stopped/disable-confirmed charger can be started without remotely navigating its local screens.

A successfully ESP-NOW-started session belongs to the initiating device ID **and boot ID**. The owner sends a heartbeat every second. Only a fresh matching owner/device/boot/subscription/session heartbeat renews the lease, using its actual receive timestamp, not queue-drain time. Duplicate heartbeats, discovery, resubscription and other subscribers cannot renew it. At 10,000 ms since the last valid owner heartbeat the main task stops the charge with **ESP-NOW owner heartbeat lost** and shows Summary. Hardware disable confirmation remains authoritative and is reported separately. There is no automatic restart after recovery.

Manual and web starts have no ESP-NOW owner and continue when observers disappear. Any currently subscribed device may Abort the current session. Disabling ESP-NOW during an owned charge does not cancel its deadline. A new session invalidates old ownership. Client/server restart IDs prevent stale commands applying to another boot; exact session checks prevent an old Abort stopping a newer charge.

Client commands retry the same sequence/content every 500 ms for up to five seconds. Servers cache four recent Start/Abort responses per peer and retain the command high-water mark: an evicted old command is rejected, never executed again. An uncertain command timeout requires reading current state rather than automatically issuing a fresh Start. A no-battery confirmation token is bound to the exact profile, requesting device/boot, current session and UI revision, and expires after 30 seconds.

The initial server accepts eight distinct client device IDs per charger boot, with telemetry intervals 500–5000 ms (default 1000 ms). Inactive subscriptions expire after 30 seconds; replay tombstones remain. Sixteen retired client boot IDs per device are retained to reject delayed boot rollback; a seventeenth additional boot is refused until the charger restarts. These bounds prevent unbounded memory use and are reported explicitly; they are implementation limits, not ESP-NOW's hardware peer capacity.

## Instance capabilities and units

Discovery advertises equipment type **0x0001 Battery Charger**, stable STA-MAC-derived device identity, a fresh nonzero boot ID, device name, firmware version, radio channel and feature bits. Type IDs 0x0000–0x0006 are permanently assigned as agreed in `lib/LabLink/PROTOCOL.md`; future instruments receive new assignments.

Capabilities contain stable property IDs, read/profile-write/command access, wire value type, physical unit, signed 64-bit range/step, enum mask and qualifiers. `charger_limits.h` is shared by the capability descriptor and profile validation; the existing exact IP2366Control source and `REGISTER_CONTRACT.md` verify hardware ranges/steps. Battery current is the IP2366's **unsigned magnitude**, carried as nonnegative int32 mA; no sign/direction is invented. ADC encoding ranges are not accuracy or safe-operating-range claims. Temperature is calculated from the established 10k/B3850 model, monitoring-only. SOC is explicitly estimated using the existing charging curves.

Configuration uses integer mV/cell, mA and percent. Telemetry uses pack mV, mA magnitude, centidegrees C, percent, milliseconds, microAh and microWh. The application-to-wire boundary converts temperature x100 and mAh/mWh x1000 once. Totals saturate at INT64_MAX micro-units, elapsed time at UINT32_MAX ms; descriptor limits match this behavior. Identifiers/commands have no numeric operating range. Validity and sample age accompany readings; missing measurement intervals invalidate the totals flag rather than silently advertising complete totals. Effective current and target voltage expose the result of full-profile validation and limiting. Profiles also obey chemistry/voltage consistency and termination-vs-charge-current dependencies.

## Task boundaries and external contracts

- Main task: LVGL, charger controller, LabChargerServer/adapter and owner deadline.
- Core-0 web/network task: WiFi/AP/mDNS lifecycle and HTTP; no charger calls.
- Separate core-0 radio pump: bounded RX/TX every three milliseconds. A lifecycle mutex serializes radio begin/end/pumping; it is never held during HTTP handling. Network changes first mark the radio inactive and pause it.
- WiFi receive callback: fixed-size copy of MAC, bytes and hardware timestamp into a bounded queue. No UI, controller, blocking, dynamic allocation or packet dispatch.

`LabQueue` bridges main and radio tasks with fixed copied messages. SDK errors and queue drops are visible in Settings/Diagnostics along with channel, ID, subscribers and owner heartbeat age. Radio receive memory is retained across restarts so an in-flight callback cannot use a freed queue.

Exact Arduino-ESP32 2.0.17 sources and ESP32-S3 SDK `esp_now.h`, `esp_wifi.h`, `esp_mac.h`, `esp_timer.h` and FreeRTOS declarations were checked. The transport uses the pinned legacy callback signature, 250-byte payload maximum, explicit unencrypted peer interfaces/current channel and documented return errors. `esp_timer_get_time()` microseconds are converted once to uint32 milliseconds, matching the exact Arduino `millis()` implementation. `esp_read_mac(ESP_MAC_WIFI_STA)` yields the stable radio identity independently of active STA/AP interface. Task stack arguments are ESP-IDF bytes. The full wire contract and primary source locations are in `lib/LabLink/PROTOCOL.md` and its README.

## Validation and bench follow-up

`tests/Test-Lab.ps1` verifies codec bounds/known bytes, units, capability pages, actual reusable clients against the portable charger server, multiple subscriptions, command retries/replay rejection, no-battery binding/expiry, owner identity and wrap-safe deadline, manual charge independence, channel/subscription recovery and retired-boot replay rejection. `Test-Preview.ps1` additionally tests the real adapter/controller/driver with fake register I/O and real LVGL, unit conversion, capability limits and owner-loss Summary. Existing controller/GPIO/library/NVS regressions and web tests remain required.

The two ESP32 firmware builds and deterministic tests do not establish physical RF reliability. Use the tester's documented bench sequence, including paused owner heartbeat, two observers, WiFi channel changes, tablet reboots and an owned charge while operating the browser. No physical device has been flashed or started remotely during this implementation.
