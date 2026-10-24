# Interface verification and numerical provenance

Checked 17 October 2026 before integrating the corresponding interfaces. Hardware configuration/protection, thermistor installation/limits, INT electrical compatibility and BMS arrangements are externally handled by the user and are not firmware-development blockers.

Version 1.0.4 moves the already-verified register contracts into `lib/IP2366Control`. The portable driver owns masks, encoding/decoding, units and readback semantics. The optional `IP2366Arduino.h` adapter retains the existing GPIO protocol; SDA/SCL/wake pins and a 7-bit address are explicit constructor parameters. Address values above 0x7F are rejected without bus activity. Metadata follows the official [PlatformIO library.json specification](https://docs.platformio.org/en/latest/manifests/library-json/index.html) and [Arduino library specification](https://docs.arduino.cc/arduino-cli/library-specification/). No new chip register meanings are introduced by the extraction. See `architecture.md` for application/library ownership.

## IP2366

Primary supplied document: `ip2366_i2c_regs_v1.13_en.pdf`, Injoinic V1.13. Pages 1-2 establish 7-bit address 0x75, 3.3 V bus, timing, single-byte reads, final NACK, wake timing, and read-modify-write. Pages 3-5 establish configuration encodings; pages 8-11 establish status and measurement contracts. Full field table is in specification.md.

Explicit user validations override this document's omissions: 0x04 bits2:0 directly encode 2-6 cells; 0x0C bits7:5=101 is the intended 140 W headroom configuration. Status registers remain read-and-react, and 0x38 fault flags are never auto-cleared.

Exact existing dependency/source inspection:

- Existing tablet v25 `profiles/ip2366.yaml`: independent DUT measurements dated 2026-10-09 establish current as a positive magnitude in both directions: 0x07A3=1955 mA charging; 0x07D1=2001 mA discharging. Therefore software does NOT use a signed int16 interpretation. Integration additionally requires charging states 1-3, CHG_En, input power present, and output state absent.
- `0x50/0x51`: unsigned little-endian pack mV; `0x6E/0x6F`: unsigned little-endian current mA. Each low-byte read precedes its high byte; no burst auto-increment assumption.
- `0x77[7]`: measured excitation selection (20 or 80 uA); `0x78/0x79`: NTC node mV, valid voltage range 0-3300 mV. NTC voltage 0 or saturated 3300+ yields unavailable temperature.
- Temperature display uses the user-corrected 10 kohm / beta 3850 K parameters (nominal resistance at 25 C) with a directly current-biased thermistor to ground: R_ohm=V_mV*1000/I_uA; T_K=1/(1/298.15+ln(R_ohm/10000)/3850). Known-value checks: 200 mV at 20 uA or 800 mV at 80 uA -> 10 kohm -> 25 C. Reported board observation: 863 mV at 80 uA -> 10787.5 ohm -> approximately 23.3 C. Version 1.0.3 replaces the earlier incorrect user-supplied 50 kohm assumption with 10 kohm; the documented excitation mapping remains unchanged. This is a display calculation, not software thermal protection. Board topology/calibration and native protection are externally handled. No inferred 0x17 write or undocumented NTC enable bit is used. NTC enable/excitation is externally configured; firmware reads the actual 20/80 uA selection rather than assuming 80 uA.

## Tablet and dependency versions

Baseline: `jc3248w535-tablet-v25`, user-provided project. Exact platform configuration retained: espressif32 6.12.0; Arduino-ESP32 2.0.17 (`3.20017.241212+sha.dcc1105b` package); GFX Library for Arduino 1.5.9; LVGL 9.2.2. The newer website's LVGL 8 example is not substituted for this known working baseline.

- GFX 1.5.9 `Arduino_ESP32QSPI.h` verifies constructor order CS,SCK,D0,D1,D2,D3. Working baseline supplies GPIO45,47,21,48,40,39 and AXS15231B portrait dimensions 320x480. Full-frame RGB565 buffer is 307200 bytes in PSRAM; LVGL draw-buffer size is bytes.
- Exact Arduino-ESP32 `esp32-hal-gpio.h/.c`: OUTPUT_OPEN_DRAIN=0x13 includes input/output/open-drain; PULLUP=0x04. SDA/SCL HIGH releases the line; software never drives these signals push-pull HIGH. Software I2C clocks no faster than nominal 100 kHz (5 us low, 5 us high plus GPIO overhead), permits 2 ms clock stretch per clock release, and inserts 50 us after each address ACK plus 1 ms between single-byte register transactions.
- Exact `Wire.h/.cpp`: begin returns bool, timeout is milliseconds, endTransmission returns 0 on success and 1-5 error codes, requestFrom returns byte count. Its combined repeated-start implementation queues the pointer write, preventing an explicit address-ACK preparation delay, so charger access uses the tested software master. Wire remains dedicated to touch at GPIO4/8, 400 kHz, 20 ms timeout.
- Touch command and decode copied from exact baseline source: 11-byte command B5 AB A5 5A 00 00 00 08 00 00 00; 8-byte response; contact count raw[1]==1; 12-bit coordinates raw[2:3] and raw[4:5], bounds checked.
- LVGL 9.2.2 widget headers and implementation establish chart arrays/ranges in int32 values, separate primary/secondary Y axes, point count, events, and RGB565 buffer interface. Native preview compiles these exact library sources with the same UI header.
- Board reference: https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s3/guitionjc3248w535/ . Its connector table establishes P2 pin2=GPIO6 and P3/P4 pin3=GPIO17, pin4=GPIO18, pin1=GND. GPIO6 -> 10 kohm -> INT is user-selected. Firmware drives GPIO6 HIGH before its 110 ms startup wait. INT-side level/electrical behavior is externally handled, not inferred from a GPIO6 read.

## SOC charging references (1.1.1)

The previous Zephyr/Linux tables were **OCV/rest** data and overestimated SOC during charging. They are retained only as historical source snapshots. Active curves now use manufacturer **charging-terminal-voltage** plots:

| Chemistry | Primary charging reference | Rate / conditions |
| --- | --- | --- |
| LiFePO4 | [EVE LF105 manufacturer sheet](http://www.adafruit.evebatteryusa.com/linked/lfp105.pdf), blue 1C CC-CV trace in Charge Characteristics | 1C, 25 +/-2 C, 3.65 V |
| Li-ion | [Molicel P42A product data sheet](https://www.molicel.com/wp-content/uploads/INR21700P42A_1.7_Product-Data-Sheet-of-INR-21700-P42A-80092.pdf), solid 4.2 A voltage/capacity traces | 1C for the 4200 mAh reference cell, 23 C, 4.2 V / 50 mA cutoff |
| LiHV | [Grepow GRP2440 manufacturer page](https://www.grepow.com/button-cell-battery/grp2440.html), [4.4 V charging plot](https://www.grepow.com/ueditor/php/upload/image/20240722/1721642875808531.png) | 0.5C, room temperature, 4.4 V / 0.05C cutoff; explicitly approved by user because a verified 1C plot was unavailable |

These are representative cell references, **not universal standard curves**. Capacity/model are unknown. Actual charging current in mA cannot identify actual C-rate without capacity in mAh, so no unsupported current/IR compensation is applied. The 1C assumption does not change or recommend a charging-current setting. Rates are shown in Diagnostics, and SOC retains its approximate marker. Cell construction, ageing, temperature, polarization, pack resistance and imbalance can materially change the estimate, especially on LiFePO4's flat plateau. The display is intended for charging and does not become a rested/discharge fuel gauge when current stops.

Numeric digitization and source SHA256 hashes are in `sources/charging-curves.json`, alongside the original manufacturer files. Values enter the model as **mV per cell** exactly once. LFP values are digitized to about 5 mV, others 10 mV; those steps are digitization resolution, not promised accuracy. EVE's plotted capacity endpoint is approximately 109% of nominal; normalize it to 100% of that reference's full delivered charge. For Molicel, CC capacity follows 100*t_hours at 1C; the solid voltage trace reaches the 4.2 V plateau around 90%. For Grepow, integrate the plotted current at one-minute intervals through the 140-minute endpoint, normalize total charge to 100%, and interpolate voltage at the SOC steps. No 4.2-to-4.4 V stretching is used.

One nondecreasing voltage table per chemistry serves forward/inverse linear interpolation. CV can contain equal voltage entries for different SOC values; voltage alone cannot resolve the CV interval. At or above the reference's final voltage, the raw lookup returns 100%. **Before whole-percent formatting, clamp to 99% unless the controller has accepted the IP2366 CHG_END completion indication (0x31 bit4)**. This also prevents 99.5-99.9% rounding to 100%. Completion permits the curve result; it never forces a partial-target charge to 100%.

For 10-90%, use the same charging table, cap at configured cell voltage and floor to a 10 mV register step. At 100%, bypass the curve and use configured voltage exactly. Examples: Li-ion 80% -> 4120 mV; LFP 80% -> 3475 mV -> 3470 mV; LiHV 80% -> 4260 mV. A 4S LFP pack at 13.700 V gives approximately 28% on this 1C reference, rather than the old OCV curve's 100%; this is not a calibrated measurement of an unknown pack's true SOC. The new percentage-based targets apply on the next manually started charge, including restored profiles. Reboot never starts charging automatically. When custom voltage caps the table-derived target, effective SOC can be below the selected percentage.

## Automatic standby (1.1.1 / library 1.2.1)

Supplied IP2366 V1.13, page 4, SYS_CTL9 (0x09): EN_Standby bit7 is R/W, reset value1; 0 disables standby and 1 enables it. Bit6 is a separate one-shot immediate-standby command; bit5 is the battery-low shutdown option, bits4:0 reserved. The driver clears **only mask0x80**, preserving bits6:0, during initialization/idle configuration and active configuration. The application's existing 2000 ms slow settings audit enforces this field again if it drifts. It does not intentionally assert bit6. Tests check 0xBF -> 0x3F and repair during charging without altering the lower bits. The existing INT/GPIO6 behavior remains as agreed.

## Power, integration, errors

- Battery power_mW=pack_mV*current_mA/1000. Requested current cap_mA=floor(100000000/target_pack_mV/100)*100, limited to 9700 mA. Example: 6S at 4400 mV/cell -> 3700 mA, nominal 97.68 W. Actual measured charging power above 100 W latches a fault. Software sampling does not promise a hardware/transient power clamp.
- Charge_mAh += average_current_mA*dt_ms/3600000. Energy_mWh += average_power_mW*dt_ms/3600000. Uses trapezoids between consecutive valid charging samples, unsigned wrap-safe millisecond deltas, 64-bit elapsed time, double totals. First interval before the first sample is excluded; no interval spanning non-charging status, reconfiguration, or a gap over 2 seconds is invented. Waiting time remains part of session duration. A gap over 2 seconds is reported in totals metadata.
- Communication failures latch a fault, attempt disable immediately, and keep retrying disable/configuration. An unreachable chip cannot have its disabled state confirmed. UI blocks return from summary until disable is confirmed. No automatic restart after reset or link recovery.
- Stop/completion/abort freezes totals immediately. Status is checked before configuration correction. On drift, disable first, correct masked fields, verify readback, then enable last only if the session is still active and status permits it.
- Pack plausibility rejects voltage above selected count times the chemistry preset full voltage. There is no lower cutoff blocking deep packs; <100 mV offers explicit Proceed. Pack-only voltage cannot prove the selected count or chemistry. User hardware/protection responsibilities are external.

## Scope

No physical flashing, live charging or electrical measurements have been performed. Build, portable controller/protocol tests and native LVGL interaction/render tests are software evidence only. External protection and hardware arrangements are intentionally not expanded or redesigned here.


## WiFi, persistence and binary frames (1.1.2)

Rechecked exact pinned Arduino-ESP32 2.0.17 `WiFiClient.cpp`, `WebServer.h/.cpp`, `WiFiSTA.cpp`, `WiFiGeneric.cpp`, `Preferences.cpp`, bundled ESP-IDF `esp_wifi.h`/`esp_wifi_types.h`, and LVGL 9.2.2 checkbox/core-position/drawing headers before modifying these boundaries.

- `Preferences::putBytes` returns byte count only after `nvs_commit` succeeds; getBytesLength/getBytes must match exact record size. Connectivity is a separate 173-byte `BO`/version1 record: eight-byte header, flags and WiFi mode, 33/64/64-byte terminated SSID/password/hostname, little-endian FNV-1a checksum of the first 169 bytes. The existing 191-byte `BS`/version1 charger record remains readable for migration and charger restoration. Options save without any valid charger config; unchanged bytes do not rewrite flash. Disabling charger persistence removes only the charger record.
- `WiFiClient::write(buffer,length)` returns bytes sent, which can be shorter than requested or zero; never assume one call sends a full header/body. Frame transport now writes every header/body byte in bounded blocks, handling partial/zero writes. The binary payload contains NUL bytes and uses explicit lengths. Frame snapshot copies are mutex protected; network sends run without holding the mutex and never call I2C/LVGL. `setNoDelay(true)` enables TCP_NODELAY. Exact WiFiGeneric `setSleep(false)` selects `WIFI_PS_NONE`; applied to station mode to avoid modem-sleep web latency.
- `esp_wifi_sta_get_ap_info` returns `ESP_OK` only for a valid connected station record, otherwise the header shows connecting/unavailable. The RSSI boundary uses signed `wifi_ap_record_t::rssi` in dBm, stored as `rssi_dBm`; strong signals may be slightly positive, so no assumed negative-only range. Units/return semantics checked against bundled SDK and [Espressif WiFi reference](https://docs.espressif.com/projects/esp-idf/en/v4.4.7/esp32/api-reference/network/esp_wifi.html). AP mode has no upstream RSSI and displays AP instead of an invented number.
- LVGL checkboxes have content-sized hit areas by default. They now have explicit 276x44-pixel rows and larger indicators; no overlapping extended click areas. A native pointer test taps the far right of each settings row, beyond the checkbox/text, and checks state/dialog transitions.
- BCW2 adds total length and FNV-1a body checksum before the former BCW1 metadata; decoding checks them and guards every DataView access. This detects truncation/corruption before pixel decode. Last valid pixels remain while retrying. HTTP length and five-second request timeout are checked; ETags suppress unchanged transfers and framebuffer revisions suppress unnecessary encoding. No live tablet network measurements have been performed, so the hardware report's exact failure cause is not claimed to be reproduced by host tests.


## Confirmed Arduino encoder fix (firmware 1.1.3)

A direct read of the running tablet's `/api/frame` returned HTTP 200, `Content-Length: 5`, and exactly `42 43 57 32 05` (`BCW2` plus byte5). The transfer was complete according to its HTTP length; the serialized frame itself was incomplete.

The exact pinned Arduino-ESP32 2.0.17 `cores/esp32/Arduino.h` declares `makeWord` and defines `#define word(...) makeWord(__VA_ARGS__)` at line211. The previous encoder's `auto word = ...` declaration did not invoke that function-like macro, but every `word(...)` call did. Those calls converted a value instead of writing bytes. Consequently all 16/32-bit fields and RLE runs disappeared; only the four magic bytes and flags advanced the output position to5. Writing the total-length field then replaced the fifth byte with5. BCW1 had the same collision, explaining the earlier DataView error.

Rename the serialization helpers to `writeByte`, `writeU16` and `writeU32`. The frame format remains BCW2. No transport or WiFi setting change is needed for this correction. Browser errors now include received/declared sizes or read offset/required bytes when a future malformed frame is encountered.

The prior host tests did not include Arduino.h and therefore missed the collision. The actual native screen encoder is now compiled under a fixture reproducing the exact Arduino macro, with an interception counter. Every encoded frame must be at least51 bytes and the macro-call counter must remain zero. All33 native frames are decoded and compared against the independently emitted pixels. JavaScript also tests the exact five-byte body observed on hardware. The device's malformed response was read directly; this task does not flash the device or claim that the new build has already run there.


## 1.2.0 responsive JSON web refinement

The approved browser design preserves colors, fonts and design philosophy while using browser space. It supersedes the earlier one-to-one framebuffer mirror. Browser JavaScript renders typed JSON state and incremental graph history (maximum 300 points); main-task typed commands retain controller validation, stale-edit checks, no-battery confirmation and applied/rejected acknowledgments. Passwords are excluded from state. The full-screen tablet root and full-screen settings/WiFi panels have square corners to match the physical display; interior tiles stay rounded. Current routes, units, source verification, task boundaries and test procedure are defined in `../web/README.md`. Charging, protection, register encodings and persistence policy are unchanged.


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
