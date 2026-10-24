# Firmware 1.4.0 module boundaries

1.1.1 replaces the application SOC references with digitized manufacturer charging curves: LFP/Li-ion 1C, LiHV 0.5C. The active session profile selects the curve; the same table drives percentage targets. A display helper caps the estimate at 99% before whole-percent formatting until the controller accepts chip completion. The web UI receives the same state and source curves as JSON. IP2366Control 1.2.1 adds masked SYS_CTL9 EN_Standby=0 to initialization/configuration and slow settings enforcement. Source plots, rates, normalization and hashes are retained in docs/sources/charging-curves.json.

Current web modules: `remote_command.h` defines typed command/results; `web_model.h` serializes coherent cached snapshots; `web_service.h` owns networking and queues; `web/index.html` renders responsive controls and charts. `tools/embed_web.py` generates `web_page.h`. The former `web_frame.h`, `web_transport.h` and synthetic LVGL pointer are removed. Main-task `Ui::executeRemote` shares controller validation with native actions. Full-screen roots use radius zero. The release history below retains earlier implementations for context and is superseded where it describes pixel mirroring.

```
main.cpp
  app_ui.h -> charger.h (composition only)
    settings.h -> soc.h -> app_types.h
    thermistor.h
    session_controller.h -> IP2366Control
    diagnostics.h -> session_controller.h + version.h
  IP2366Arduino.h -> portable IP2366Control transport interface
```

- `lib/IP2366Control/src/IP2366.h/.cpp`: standalone driver with validated settings, register encoding/decoding, readback checks, status/fault decoding, on/off/configuration/enforcement and explicit-unit measurement reads.
- `lib/IP2366Control/src/IP2366Arduino.h`: optional configurable ESP32 Arduino software-I2C/wake adapter. No tablet display or UI dependency.
- `include/app_types.h`: chemistry/configuration types, measurement presentation data, totals and graph history.
- `include/soc.h`: sourced chemistry curves and forward/inverse interpolation.
- `include/settings.h`: application input policy, SOC targets, 100 W current cap and conversion into library settings.
- `include/thermistor.h`: user-selected 10 kohm/B3850 model, separate from device telemetry.
- `include/session_controller.h`: startup wait, charging/completion/abort/fault lifecycle, polling schedule and integration.
- `include/diagnostics.h`: UI diagnostic text; hardware failure records are provided by the library.
- `include/version.h`: application version; shown in diagnostics only.
- `include/charger.h`: small application composition header; no register operations.
- `include/app_ui.h`: LVGL widgets and input behavior.

All hardware actions in the session controller call named library methods. Raw addresses/masks are private to the driver, apart from diagnostic labels and independent test expectations. Unit conversion from IP2366 register encodings occurs once inside the library. Application SOC, power and thermistor calculations operate on the returned physical units.

Behavior retained from hardware-confirmed 1.0.3: startup input-loss waiting/reconfiguration, established-session fault latching, 10 kohm NTC model, explicit undetected-battery override, 500 ms/2 s enforcement, current telemetry without guessed calibration, completion/abort total freezing, dark UI and version in diagnostics only.

The separate library can be copied into another project; no application code needs to be copied. See its README for public API, transport responsibilities and the existing UFP/charging policy.

In 1.0.5, IP2366Control 1.1.0 owns per-message retries, immediate address probing after every failed transfer, and latched disconnected/unstable classifications. The controller owns the one-second initial detection retry and the transition to Fault/Summary after communication failure. The UI owns warning icons and automatically switches from detection to Configure. New faults trigger a UI refresh in the same main-loop iteration.

In 1.0.6, the UI draws the charge-end reference with LVGL 9.2.2's DRAW_MAIN_END event and a single horizontal line primitive (2-pixel dots, 4-pixel gaps). Mapping follows the pinned chart source's content-height transformation and the primary voltage range. Both the plotted reference and its label use the active session's effective per-cell target multiplied by cell count, in mV internally and V for presentation. The voltage autoscale includes the target and measurement extrema with padding. The reference remains visible before samples and with the full history buffer; dot spacing does not depend on sample count.

1.0.7 replaces autoscaling with fixed session bounds: primary voltage 0 to target pack mV + 1000 mV, secondary current 0 to limitedCurrent_mA(active config) + 300 mA. It adds a cyan dotted termination reference using the active termination_mA and the secondary range. The End label is reduced to 12 px; Term is 12 px in the current column; the elapsed timer is 12 px in the header. Both line mappings use their own axis units and a 64-bit intermediate for pixel conversion. No hardware-control or IP2366Control API changes.


1.0.8 adds readChargingSnapshot() to IP2366Control 1.2.0. Before begin() performs any register write, it reads SYS00 charge enable, current ADC (unsigned mA), target/cell-count/charge/termination fields and rechecks enable/current. Invalid or incomplete reads never provide defaults. The controller always proceeds to the existing disable/idle initialization, then loads saved metadata and compares all four screen-controlled hardware settings against deviceSettings(saved). The original request can exceed the 100 W effective cap, so matching uses the encoded effective current rather than the requested number. No automatic charger enable occurs during recovery.

profile_store.h defines the portable ProfileStore boundary and an 18-byte record: bytes 0..3 are 'B','C',1,0; byte 4 is chemistry (1..3), byte 5 cells, byte 6 percentage, byte 7 reserved zero; unsigned little-endian mV/mA pairs at 8..9,10..11,12..13 hold original cell voltage, requested current and termination current; bytes 14..17 hold little-endian FNV-1a over bytes 0..13. Decode validates version, reserved fields, checksum, enum and application/device ranges before publishing a Config. profile_store_arduino.h uses Arduino-ESP32 2.0.17 Preferences namespace batcharger, key profile-v1. The exact installed Preferences source confirms that putBytes returns the committed byte count and getBytes requires exact length; begin(false return) provides no usable handle. Reads close their handle; saving compares bytes before writing and checks the committed count. Configuration is saved while charging is confirmed off, before chargerOn(). Native tests inject ProfileStore without Arduino dependencies.

Voltage plotting now starts at low_mV(active chemistry) times cell count, bounded down to the target for unusual below-threshold custom targets. Its upper bound remains target+1000 mV. The current range is unchanged. Hardware-control thresholds are unchanged by this display refinement.


1.1.0 adds app_options.h (portable options and 191-byte validated settings record), settings_store_arduino.h (Preferences adapter), web_frame.h (bounded RGB565 RLE/telemetry format), web_page.h (self-contained browser asset) and web_service.h (core-0 WiFi/mDNS/HTTP task, bounded command queue and copied frames). The UI owns the gear/tabs, WiFi dialog and native input focus. Main owns full-settings save/restore and executes remote gestures through a second LVGL pointer device. IP2366Control remains 1.2.0 and all remote charger actions use the existing application checks. Full settings use NVS batcharger/settings-v1; the earlier profile-v1 record remains independent. The settings record has a BS/version1 header, flags/mode/reserved fields, the validated 18-byte profile record, fixed 33/64/64-byte zero-terminated SSID/password/hostname fields, and a little-endian FNV-1a checksum over its first 187 bytes. No C++ structure padding is serialized.


1.1.2 separates `OptionsRecord`/`options-v1` from the charger settings record. Main saves preferences independently of sessions; the NVS adapter migrates old valid combined records. `wifi_signal.h` is a portable, unit-bearing copied network status model; Ui draws signal states and numeric dBm without accessing the radio. `web_transport.h` owns byte-exact partial-write handling in bounded RAM blocks. BCW2 length/checksum and bounded JS decoding reject malformed transfers before rendering; HTTP ETags and display revisions avoid unchanged work. All radio/socket operations remain on core 0, and only the main task touches LVGL or the charger.


## Confirmed Arduino encoder fix (firmware 1.1.3)

A direct read of the running tablet's `/api/frame` returned HTTP 200, `Content-Length: 5`, and exactly `42 43 57 32 05` (`BCW2` plus byte5). The transfer was complete according to its HTTP length; the serialized frame itself was incomplete.

The exact pinned Arduino-ESP32 2.0.17 `cores/esp32/Arduino.h` declares `makeWord` and defines `#define word(...) makeWord(__VA_ARGS__)` at line211. The previous encoder's `auto word = ...` declaration did not invoke that function-like macro, but every `word(...)` call did. Those calls converted a value instead of writing bytes. Consequently all 16/32-bit fields and RLE runs disappeared; only the four magic bytes and flags advanced the output position to5. Writing the total-length field then replaced the fifth byte with5. BCW1 had the same collision, explaining the earlier DataView error.

Rename the serialization helpers to `writeByte`, `writeU16` and `writeU32`. The frame format remains BCW2. No transport or WiFi setting change is needed for this correction. Browser errors now include received/declared sizes or read offset/required bytes when a future malformed frame is encountered.

The prior host tests did not include Arduino.h and therefore missed the collision. The actual native screen encoder is now compiled under a fixture reproducing the exact Arduino macro, with an interception counter. Every encoded frame must be at least51 bytes and the macro-call counter must remain zero. All33 native frames are decoded and compared against the independently emitted pixels. JavaScript also tests the exact five-byte body observed on hardware. The device's malformed response was read directly; this task does not flash the device or claim that the new build has already run there.


## 1.3.0 LabLink ESP-NOW milestone

The agreed lab protocol and independent identical-tablet test project are implemented. `espnow.md` records equipment type assignments, instance capability descriptors/limits/units, unencrypted multi-subscriber operation, atomic Start, per-session ownership, ten-second owner heartbeat timeout, replay protection, channel recovery, task boundaries and bench tests. The reusable wire/client/transport library is vendored in `lib/LabLink`. This supersedes the former reserved-only ESPNow flag; connectivity persistence and manual/web charge independence remain intact. The test tablet project is `LabEspNowTester`, with no IP2366 access. No automatic charge restart or silent ownership transfer is permitted.


## 1.4.0 implemented graph/display refinements

The authorized testing revisions are implemented; `release-1.4.0.md` defines
the current behavior and supersedes earlier rolling-history descriptions.
`session_history.h` owns twelve-hour raw PSRAM points and a separate mode log;
`PlotHistory` is the bounded projection copied to network/UI consumers.
Status stage decoding is verified from supplied IP2366 V1.13 page 8 and belongs
to IP2366Control 1.2.2. Both Charger and Graph show status, with graph text
above the plot. Native scatter coordinates are normalized with uint64 math
to avoid the pinned LVGL int32 mapping overflow. History schema 2 carries
timed points, independent mode events, source counts, revision and compression
flags; each changed projection replaces the prior plot. SOC bar, W/mWh tile,
temperature formatting, successful session origin and stop-warning gating
follow the new release contract. ESP-NOW wire semantics and owner lease do
not change. Simulated ten-hour storage/geometry tests supplement actual LVGL,
web, controller, persistence and LabLink regressions; no physical charge or
flash was performed during development.

## 1.5.0 application time limit

`terminationTime_min` is persisted in profile record v2 with v1 migration and
included in web config commands. The controller compares 64-bit elapsed ms with
64-bit minutes × 60000 on every active tick, then uses its existing verified
stop path. Native and web Start controls review a snapshot before submitting it.
See `release-1.5.0.md` for the exact record offsets and lifecycle behavior.

## 1.6.0 graph mode filtering and browser export

`release-1.6.0.md` supersedes earlier immediate mode-marker behavior. Subsequent
TR/CC/CV graph events require five seconds of continuous observations, retaining
the first-observed timestamp; raw status/protection remain immediate. The web
Graph tab exports a self-contained 1600x1060 PNG or A4 landscape raster PDF with
graph scales, readings, settings and totals. Browser generation requires no new
MCU requests or external libraries.

## 1.7.0 partial-charge policy (supersedes reduced hardware CV)

All sessions configure the entered 100% cell voltage on the IP2366. For a target
below 100%, firmware independently stops at the charging-curve threshold on a
valid one-second ADC sample. Software cutoff uses integer mV, not hardware 10 mV
quantization. Register enforcement, reboot matching and current/power limits use
the full CV setting. Hardware full status is distinct from requested-goal
completion. SOC progress is relative to the active target, labeled below the
bar. See `release-1.7.0.md` for examples and validation.


## 1.7.1: restored hardware CV termination
Supersedes the 1.7.0 partial-target software cutoff. All percentages program the IP2366 with the selected curve-derived cell voltage (100% uses the entered cell voltage unchanged). Partial targets round down to the hardware 10 mV step. The controller waits for IP2366 charge completion; reaching the voltage alone does not end the session. Existing time limit, fault handling, SOC display and target-relative progress remain. Example: 4S LiFePO4 at 70% programs 3.460 V/cell, 13.840 V total. Current limiting uses this programmed voltage.


# BatCharger 1.7.3

Charging status is prefixed IP2366: and continues to report the chip state. Graph markers now estimate CC/CV from measured pack mV and charging mA, independently of register 0x31 stage. Hardware control, completion flags and safety handling are unchanged.

The 1 Hz estimator uses a three-sample median, least-squares trends over 5-10 seconds, then requires five seconds of continuous qualifying evidence. CV requires a current decline of at least max(20 mA, 1% of mean current) across the window, voltage within 60 mV/cell below the target or above it, and voltage not falling more than 10 mV/cell across the window. CC requires voltage at least 10 mV/cell below target, rising by at least 2 mV/cell across the window, with current not declining beyond the margin. These are presentation heuristics, not proof of which regulation loop is active. The generous target margin accommodates the observed ADC offset. Single spikes are median-filtered; invalid/inactive samples and gaps over two seconds reset pending evidence. Ambiguous behavior retains the last confirmed marker mode.

After confirmation a transition is timestamped at the start of its qualifying evidence; the first confirmed mode labels the beginning of the graph. Median/trend warm-up adds detection latency beyond five seconds. Both tablet and web/export use the same timestamped event log and full-session scaling.
