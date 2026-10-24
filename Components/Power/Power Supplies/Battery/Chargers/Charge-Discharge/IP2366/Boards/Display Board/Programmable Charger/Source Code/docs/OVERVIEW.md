# BatCharger

Current release **1.7.8** adds charging current beneath charging voltage in the tablet/web pre-charge review. See [release details](docs/release-1.7.8.md).

Version **1.6.0** filters CC/CV graph markers using five seconds of stable
status and adds browser-side **Save as PNG** / **Save as PDF** on Graph. Raw
charger status, control and protection remain immediate. See
[release details](docs/release-1.6.0.md) and the sample exports in `docs/previews/`.

ESP32-S3 firmware for the JC3248W535C_I_Y tablet and an IP2366 charger. Three dark LVGL screens configure 2S-6S LiFePO4, Li-ion or LiHV packs, monitor charging, and summarize time, mAh and mWh.

Version **1.4.0** keeps full-session graphs with twelve hours of one-second PSRAM history (at least ten hours required), reduced to at most 300 web / 240 tablet points. It adds verified IP2366 stage text on Charger and above Graph, separate CC/CV mode markers, a green/gray SOC bar, battery power and delivered mWh, and a framed TABLET/WEB/REMOTEHOST session origin. The false active-charge Summary warning is fixed. Reload the browser after uploading: the graph API now sends bounded full-session projections rather than rolling-window deltas. See `docs/release-1.4.0.md` for memory, compression and validation details.

Version **1.3.0** adds LabLink ESP-NOW discovery, multi-client telemetry/capabilities, atomic Configure and Start, acknowledged/replay-protected commands and per-session ownership. An ESP-NOW-owned charge stops after ten seconds without its valid owner heartbeat; manual/web starts continue independently. Enable ESPNow in Settings. See `docs/espnow.md` and the separate **LabEspNowTester 1.0.0** project for the test tablet.

Version **1.2.2** adds live voltage, current, temperature, SOC and elapsed time above the web graph. Browser API calls are serialized through body consumption, polling pauses during commands, and read requests retry once on transport/body errors. The timeout is eight seconds from dispatch; control commands are never automatically repeated. This addresses overlapping requests as a possible source of startup interruptions; physical WiFi stability still needs an uploaded-device check.

Version **1.2.1** adds separate Charger, Graph and Summary browser tabs. The latest session graph remains available after charging ends and while preparing the next charge, until a new charge starts or the tablet restarts.

Version **1.2.0** replaces the framebuffer mirror with a lightweight responsive browser dashboard. The tablet sends compact JSON; browser JavaScript renders controls, readings and a wider graph with up to 300 samples. Colors and Montserrat typography match the tablet. Commands receive an applied/rejected acknowledgment from the main task. Full-screen tablet backgrounds now have square corners, while interior tiles retain rounded edges.

Earlier releases below describe historical changes; their pixel-frame protocol is superseded by 1.2.0. See `web/README.md` for the current interface.

Version **1.1.3** fixes the confirmed black-page cause: Arduino’s `word(...)` macro replaced the frame encoder’s 16-bit write helper calls, producing a five-byte frame. The encoder now uses macro-safe helper names. Native screen/codec tests compile the encoder with the actual Arduino macro semantics present and verify that it never intercepts a frame write.

Version 1.1.2 adds full-row checkbox touch targets, always-persisted connectivity preferences, and WiFi/RSSI headers. “Persist charger config” controls only charger-profile persistence after a charge starts. Web frames use explicit binary transfer lengths, partial-write handling, length/checksum validation, unchanged-frame responses and no WiFi modem sleep. Reload the browser page after installing this firmware because its frame format changed.

Version 1.1.1 replaces the old OCV/rest tables with manufacturer charging references: LiFePO4 and Li-ion at 1C, LiHV at the approved 0.5C. SOC stays at most 99% until IP2366 confirms completion. Percentage-based voltage targets use those same charging tables; 100% keeps the configured voltage. Automatic standby is disabled through 0x09 bit7 and checked every 2 seconds. See `docs/interfaces.md` for sources, digitization and limitations.

Version 1.1.0 replaces DIAG with a gear on every screen. The gear opens Settings (default) and Diagnostics tabs. Settings adds Persist charger config, WiFi setup (Access Point / Join WiFi, SSID/password/mDNS) and the ESPNow flag reserved for a future automation interface.

With WiFi enabled, browse to the IP address shown under Settings or `http://charger1.local/`. The responsive web dashboard uses the same controller and settings, with browser-rendered controls and up to 300 full-session graph points; the tablet plots up to 240 points from the full session. Join WiFi defaults to `internet-cafe` / `meincofi66` and hostname `charger1`. Failed connection/reconnection falls back to a protected AP after 15 seconds and shows a warning on the tablet. Default AP name is `charger1`, password `meincofi66`.

Connectivity preferences (WiFi, ESPNow, mode, SSID, password and mDNS) and the persistence checkbox are saved whenever changed, independently of charging. Persist charger config saves the charger profile after a charge starts, then restores it on reboot without starting charging. With it off, the 1.0.8 active-charger/matching-profile boot recovery remains available. See `web/README.md` for operation, persistence and threading details.

Voltage stays fixed from chemistry discharge-end pack voltage to target pack voltage +1 V; current stays 0 A to effective charging current +300 mA. End voltage and termination-current dotted references remain in place.

Initial detection automatically retries every second and advances when initialization succeeds. On every failed register transaction, firmware probes address **0x75**: a failed probe stops at Summary with **IP2366 was disconnected.** Otherwise it retries the same message, stopping on the sixth consecutive failure with **IP2366 communication instable**. Successful register transfers reset the consecutive-failure count; address probes do not. These checks cover reads and writes on every screen after initial detection, including disable actions. Warning messages carry a warning icon. A communication fault stops the session and never automatically resumes charging after reconnection.

Includes reusable **IP2366Control 1.2.2**. Open **Gear > Diagnostics** to see firmware version 1.7.8; the version remains in diagnostics only. No terminal is needed. The existing startup negotiation and 10 kohm / beta 3850 K NTC conversion remain in place. See `docs/architecture.md` and `lib/IP2366Control/README.md`.

## Connections

| Tablet | IP2366 |
| --- | --- |
| P3/P4 GPIO17 | SDA |
| P3/P4 GPIO18 | SCL |
| P3/P4 GND | GND |
| P2 pin2 GPIO6 through 10 kohm | INT |

GPIO6 is HIGH during operation. Touch retains its own GPIO4/8 bus. Hardware, thermistor protection and BMS setup are externally handled as agreed. Firmware does not configure undocumented NTC protection bits; it reads actual excitation and displays temperature using 10 kohm / beta 3850 parameters for a directly current-biased NTC to ground.

## Build and upload

Open this folder in PlatformIO, or run from this folder:

```powershell
python -m platformio run
python -m platformio run --target upload --upload-port COM7
python -m platformio device monitor --port COM7 --baud 115200
```

Replace COM7 with the tablet's actual port. The upload command builds and writes the application and required boot/partition images through PlatformIO. Do not write the standalone application binary at address 0.

Pinned versions: espressif32 6.12.0, Arduino-ESP32 2.0.17, GFX Library for Arduino 1.5.9, LVGL 9.2.2. The board target is generic but the 16 MB flash and octal PSRAM settings match the existing tablet baseline. No live device has been flashed by this task.

`firmware/` contains the application binary, bootloader, partition table, combined flash image (address 0), ELF for debugging and SHA256 checksums. Prefer PlatformIO upload; the combined image is provided for a compatible ESP32-S3 flashing workflow. Flashing is a user action.

## Behavior

- No chemistry or cell-count default. 1000 mA charge, 100 mA termination, 100% level. Settings survive screen navigation. The latest successfully configured profile is saved for matching recovery only when charging is active at reboot.
- Under 100 mV, Start offers **No battery detected. Proceed anyway?**. I2C errors are not interpreted as zero battery voltage.
- Published SOC tables drive approximate display and 10-90% target voltages. 100% uses the configured voltage. See `docs/interfaces.md` for source snapshots, exact encodings, conversions and limitations.
- Requests are capped to 100 W battery power with the user-validated 140 W chip headroom configuration. Inputs enforce supported steps and ranges. The effective current is shown before Start.
- 500 ms: voltage-setting check and live status/fault monitoring. 2000 ms: remaining configured fields, including UFP and 0x09 EN_Standby=0. Read-modify-write preserves unrelated bits. Status/fault flags are not overwritten or automatically cleared.
- Completion, abort or fault immediately latches stop and freezes totals. A recovered link never automatically resumes. No charging automatically resumes after reboot.
- Separate fixed voltage/current graph axes, no axis labels, matching numeric/trace colors. Up to 240 reduced points span the full session duration. Voltage: discharge-end pack voltage to target + 1 V; current: 0 to effective charging current + 300 mA.
- Temperature is display-only; externally handled protection remains outside this firmware's scope. Saturated/unusable NTC voltage displays unavailable temperature.

## Software verification

Using Windows PowerShell 5.1 and an installed LLVM compiler:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tests/Test-Controller.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File tests/Test-Preview.ps1
```

Controller, standalone IP2366 library and GPIO protocol tests run without hardware. The standalone tests compile the library with no application, Arduino or LVGL headers. Preview compiles the exact LVGL library with the same UI and exercises selection, dialogs, charging, completion, summary, faults, and retained settings. Rendered UI images are in `docs/previews/`.

The firmware has compiled successfully and passed host tests. Physical display/touch, I2C timing and live charging have not been bench-tested by this task.

## Files

- `src/main.cpp`: tablet display/touch initialization and main loop.
- `lib/IP2366Control/`: standalone IP2366 register driver and optional Arduino GPIO I2C transport.
- `include/charger.h`: application composition header; no register operations.
- `include/session_controller.h`: startup/charging/abort/completion/fault lifecycle, scheduling and totals.
- `include/settings.h`, `include/soc.h`, `include/thermistor.h`: application configuration/power policy, sourced SOC curves and NTC model.
- `include/diagnostics.h`, `include/version.h`, `include/app_types.h`: diagnostics, version and application data types.
- `include/app_ui.h`: shared embedded/native LVGL UI.
- `docs/specification.md`: consolidated requirements and latest scope refinement.
- `docs/interfaces.md`: integration contracts and data provenance.
- `tests/`: standalone library, controller, bus protocol, source-data and actual UI tests.

Third-party source snapshots retain their license headers. Zephyr battery helpers are Apache-2.0; the Linux source snapshot is GPL-2.0-only; LVGL is MIT. These files are references for numerical data and build dependencies, not modified vendor code.


## Web/settings verification (1.1.0)

The real LVGL preview covers gear/settings/diagnostics, WiFi setup/keyboard, persisted defaults, AP warning and completion-gated SOC. `tests/test_web_page.cjs` verifies 33 native frame pixel round trips, password metadata masking, a 300-sample history, widened rendering paths and malformed-frame rejection. Run it after native previews, via `tests/Test-Web.ps1` with Node.js installed. Live radio connection/fallback and physical tablet remote control need an uploaded-device check; no hardware was flashed here.


## LabLink 1.1 shared extension

The canonical shared package in lib/LabLink now includes current-meter messages and client/server support. See [lib/LabLink/METER-PROTOCOL.md](lib/LabLink/METER-PROTOCOL.md). Charger firmware behavior is unchanged; no meter hardware code was added to the charger application.

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2366/boards/displayboard/programmablecharger/sourcecode/docs?393130101024264749) - created 2026-10-23 - last edited 2026-10-23
