# BatCharger specification

Consolidated discussion specification, updated 18 October 2026. This replaces the original specs.txt as the working requirements document. Confirmed requirements and unresolved integration details are distinguished below.

Version 1.0.4 modularization: IP2366 control is a standalone reusable IP2366Control library with named chargerOff(), chargerOn(), configureCharger(), validateSettings(), readVoltage(), readCurrent(), readStatus(), readNtc() and enforcement APIs. Register masks/encodings/units, readback/fault handling and optional Arduino GPIO transport belong to the library. UI, chemistry/SOC, 100 W application policy, 10 kohm thermistor model, session state, polling schedule, graph and totals remain application modules. Preserve the working 1.0.3 behavior, including the startup fix and version in diagnostics only. Provide both the firmware project and a separate library package, with API documentation and independent tests.

Version 1.0.3 correction: the user confirmed the fitted NTC is **10 kohm at 25 C**, not 50 kohm. Retain beta 3850 K; use 10,000 ohm in all temperature calculations and diagnostics. This supersedes every earlier 50 kohm assumption below. Retain the startup fix from 1.0.2. Show the firmware version at the top of diagnostics only; do not add it to normal screens. Diagnostics are accessible on the tablet without USB serial or a terminal.

Version 1.0.2 refinement: add a Starting state between successful configuration/enable and confirmed active charging. A missing-input indication before confirmation disables the charger and waits for input; recovery reapplies/verifies settings while disabled and enables last, then requires a subsequent active-charge observation. A 10-second application startup deadline latches a fault if starting cannot complete. All hardware/I2C faults remain immediate, and input loss after confirmed charging still latches a fault with no automatic resume. Abort is available during Starting. DIAG is accessible on every screen and preserves the first fault reason/status and failing register/readback details. No current or temperature calibration has yet been applied.

Latest scope refinement: the user states charger-board/hardware references, NTC installation/protection, and BMS arrangements are taken care of externally and are not to be covered further here. Treat those hardware questions as externally resolved rather than implementation blockers. Firmware retains GPIO6 -> 10 kohm -> INT and the agreed control/display behavior; it does not invent or write undocumented NTC protection controls. The implementation reads actual NTC excitation and uses the supplied 50 kohm / beta 3850 K values for display-only conversion of a directly current-biased NTC to ground. Protection remains external.

Implementation refinements: published Zephyr Li-ion/LiFePO4 tables and the upstream Linux Asus Z00T 25 C 4.4 V battery table are adopted, with forward/inverse interpolation and the agreed 100% override. Exact source snapshots and conversions are documented in the BatCharger project's docs/interfaces.md. Current magnitude is verified by the baseline's 2026-10-09 DUT measurements; charging status determines charge accumulation. Graph uses separate automatic voltage/current scales and a rolling 240-second history. No settings persistence across reboot; no automatic charging resume. These decisions supersede earlier pending items below.

Version 1.1.1 supersedes the earlier OCV curve choices: use manufacturer charging curves, LFP/Li-ion at the agreed 1C reference and LiHV at the explicitly approved 0.5C reference. Use the same curve for SOC inference and 10-90% targets; 100% keeps the configured end voltage exactly. Before integer display, cap SOC at 99% until IP2366 charge completion has been accepted. Clear 0x09 bit7 EN_Standby during initialization/configuration and enforce it in the 2000 ms audit; preserve all lower bits. Rates/source provenance are documented in interfaces.md and Diagnostics.

Version 1.1.2: all connectivity/UI preferences persist immediately and independently of charge starts. Rename the checkbox to Persist charger config; it controls only charger-profile saving/restoration after Start. Retain the earlier live-charge recovery. Make settings/radio hit targets full-width 44-pixel rows. Add a WiFi header icon with off/connecting/AP/signal-level states and numeric signed RSSI dBm for connected stations on each screen. SSID/AP name appears in Settings. Make the web binary transport handle partial writes and validate length/checksum before decoding, retain valid frames on retry, and reduce latency with unchanged-frame responses and modem-sleep disabled. Original control/protection behavior remains as agreed.

## 1. Hardware and reference implementation

- Tablet: JC3248W535C_I_Y ESP32-S3 touch tablet, using the display/touch/build baseline and dark LVGL tile style in `C:\Users\tobia\Documents\Codex\2026-07-05\can-you-create-a-baseline-platformio\jc3248w535-tablet-v25`.
- Charger: IP2366 I2C model. P3/P4 connection: SDA GPIO17, SCL GPIO18; pull-ups enabled. Verify the actual board pull-up network and electrical compatibility before implementation.
- I2C address: 7-bit 0x75; 0xEA/0xEB are the address bytes including write/read direction.
- Reference register document: `C:\Users\tobia\OneDrive\Dokumente\done.land\work\BatCharger\ip2366_i2c_regs_v1.13_en.pdf`.
- Original requirements: `C:\Users\tobia\OneDrive\Dokumente\done.land\work\BatCharger\specs.txt`.
- Thermistor: nominal 50 kohm at 25 degrees C, beta 3850 K. Wiring, beta reference temperatures, excitation/enable configuration, and protection thresholds still need verification.
- Accepted batteries: 2S through 6S, LiFePO4, Li-ion, or LiHV, within verified IP2366/board capabilities. Do not invent stricter product restrictions. Pack voltage alone does not identify chemistry, series count, or individual-cell health.

## 2. Verified contracts and user-validated exceptions

Before implementing an external interface, verify its exact contract from primary documentation or exact dependency source, including units, masks, range, signedness, errors, and timing. Stop dependent implementation where a safety-relevant interpretation remains unresolved. Record conversions once at the boundary with unit-bearing names.

User-validated exceptions to omissions/labels in V1.13:

- Cell count is register 0x04, mask 0x07, shift 0. cell_count = code * 1 + 0; codes 2,3,4,5,6 represent 2S,3S,4S,5S,6S. Preserve bits 7:3.
- Register 0x0C is validated by the user for the intended 140 W headroom configuration. V1.13 labels it output maximum power; do not infer a battery charging power limit from that label. Preserve this acknowledged difference in implementation documentation.
- User instructs that read-only labels must not by themselves block the intended configuration operations. This does not authorize writing live status registers as if they were configuration; monitoring and fault acknowledgement are separate operations.

Known register units/fields:

| Register | Contract |
| --- | --- |
| 0x00 | bit7 LOADOTP, bit6 RESETMCU, bit5 INT_low, bits4/3/2 sink DPDM/PD/SCP enable, bit0 charger enable; preserve reserved bit1 |
| 0x02 | Per-cell target: target_cell_mV = code * 10 + 2500; documented maximum 4400 mV |
| 0x03 | Charge-current limit: charge_current_mA = code * 100; maximum 9700 mA; cannot be below termination current |
| 0x04 | User-validated cell count, mask 0x07, shift 0, direct encoding |
| 0x06 | Precharge/trickle current: code * 50 mA; requested 100 mA is code 2 |
| 0x08 | bits7:4 termination current, code * 50 mA; bits3:2 recharge policy; bits1:0 reserved |
| 0x09 | bit7 EN_Standby=0, disable automatic standby; mask0x80, preserve bits6:0 |
| 0x0A | bits7:5 battery-low selection: 000=2500, 001=2600, 010=2700, 011=2800, 100=2900, 101=3000, 110=3100, 111=3200 mV/cell; preserve lower bits |
| 0x0B | bit7 DC/DC discharge enable; bits6/5/4 source DPDM/PD/SCP enable; preserve lower bits |
| 0x0C | 140 W selection is code 101 in bits7:5; preserve lower bits; intended use user-validated as above |
| 0x22 | bits7:6 Type-C mode, 00=UFP; preserve lower bits |
| 0x31 | bit4 CHG_END; bits2:0 charging state, including 110 charging timeout; live status |
| 0x33 | Input power/overvoltage/voltage status; live status |
| 0x34 | Type-C connection/negotiation status; live status |
| 0x38 | Fault flags; documented bits5/4 are write-one-to-clear. Never auto-correct status values or clear before capturing/handling the fault |
| 0x50 then 0x51 | Pack voltage low then high byte, combined value directly in mV |
| 0x6E then 0x6F | Battery current low then high byte, combined value in mA; signedness/direction remain to be verified |
| 0x77 | bit7 indicates 20 uA (0) or 80 uA (1) NTC excitation; desired 80 uA configuration needs the actual control contract verified despite the read-only label override |
| 0x78 then 0x79 | NTC node voltage low then high byte, in mV, documented 0-3.3 V; not a temperature value |

At 2500 mV/cell battery-low, V1.13 states low-voltage protection is software only (also true for 2700 mV/cell and below). The setting changes the precharge-to-constant-current transition. It is not an individual-cell BMS substitute.

## 3. Wake and I2C behavior

- Intended behavior: keep the IP2366 awake continuously while the tablet operates.
- User-selected connection: tablet connector P2 pin 2 (IO6/GPIO6) -> 10 kohm series resistor -> IP2366 INT, with common ground. Drive GPIO6 HIGH during operation to provide the resistive pull-up. This replaces the earlier idea of a direct tie to the 3.3 V rail.
- Board reference supplied by the user: https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s3/guitionjc3248w535/ (checked 17 October 2026). Its P2 table identifies pin 2 as GPIO6, a digital I/O. Its P3/P4 table identifies pin 1 GND, pin 2 3.3 V, pin 3 GPIO17, pin 4 GPIO18. Follow connector numbering/orientation in the board drawing, not cable colors. This resolves the documented connector mapping, not the charger's INT electrical contract.
- Initialize the GPIO6 output HIGH before starting the wake wait; allow INT to settle and satisfy the documented 100 ms high interval before I2C access. GPIO6 reads on the tablet side of the resistor do not establish the voltage on the INT side if the chip pulls INT low.
- V1.13 says high INT prevents sleep and describes wake on INT high, with at least 100 ms continuously high before I2C access. If INT goes low, stop I2C access within 16 ms.
- The 10 kohm connection is the selected design, not an electrical validation result. The chip can drive INT, including fault-related low pulses when enabled. Verify pin drive topology, voltage limits, existing board pulls, valid INT-side HIGH level, and power sequencing/back-power behavior before wiring. Nominal resistor current with GPIO at 3.3 V and INT held at 0 V is 0.33 mA; this calculation alone does not establish pin compatibility. Keep INT_low=0 as specified.
- Use 100 kHz initially; document maximum is 250 kHz and recommended range 100-200 kHz.
- Follow documented ACK/preparation timing, including the stated 50 us preparation delay and recommended single-byte reads with 1 ms between bytes. Verify how the exact ESP32 I2C driver implements this.
- Final read byte must be NACKed. Read low byte before high byte for a coherent measurement pair.
- Use read-modify-write on controlled fields, preserving unrelated/reserved bits. Do not write undocumented bits or assume reset values.
- On initial no response, attempt standard I2C bus recovery where electrically applicable. If still unavailable, show a warning icon with "No 2366 Detected" and automatically repeat initialization every 1000 ms. Remove "Test again". Once initialization succeeds, advance to Configure with charging disabled. Bus recovery does not replace wake handling.

## 4. States and configuration enforcement

States: INITIALIZING, CONFIGURE, CHARGING, COMPLETE, ABORTED, FAULT, SUMMARY. Desired settings depend on state; one stale configuration must never re-enable charging after completion, abort, or a fault.

Idle/initialization/abort/completion/fault settings:

- 0x00: LOADOTP=0, RESETMCU=0, INT_low=0, sink DPDM=1, sink PD=1, sink SCP=1, charger=0.
- 0x22: UFP.
- 0x0B: DC/DC discharge output=0; source DPDM=1, PD=1, SCP=1.
- During active charging only, charger enable=1 after configuration and checks succeed.
- Disable automatic recharge: 0x08 bits3:2=00.

Periodic enforcement:

| Interval | Registers | Action |
| --- | --- | --- |
| 500 ms | 0x02 | Compare controlled target-voltage field against the current desired setting; correct mismatch using read-modify-write |
| 500 ms | 0x31, 0x33, 0x34, 0x38 | Read live status and react to completion, power/connection changes, timeout, or faults; do not overwrite to force an expected status |
| 2000 ms | 0x00, 0x03, 0x04, 0x06, 0x08, 0x0A, 0x0B, 0x0C, 0x22 | Compare controlled configuration fields against the state-specific desired settings; correct mismatches, preserving unrelated bits |

- Do not compare against uninitialized battery-specific settings before the user has selected them. Monitor status meanwhile.
- Capture faults before any deliberate acknowledgement. Never perform generic read-modify-write on write-one-to-clear status fields.
- Application start/stop and fault transitions perform necessary configuration immediately, without waiting for the periodic checks.
- LOADOTP=0 is intentional. V1.13 discourages it and calls for software management of defaults/configuration around boot, wake, and VINOk/VBUOk events. Periodic enforcement is the agreed mechanism, but restart/wake/input-transition handling must also re-establish desired state. Polling is not a hardware safety guarantee.
- On fault/timeout: latch the non-charging state, disable charging when communication permits, capture/report the cause, and prevent automatic re-enable. An unreachable chip cannot have its disabled state confirmed.
- Firmware 1.0.5: after every failed IP2366 register transaction, immediately probe the 7-bit address 0x75. If this probe also fails, immediately enter SUMMARY with a warning icon and "IP2366 was disconnected.". If the probe responds, retry the same message; more than five consecutive failed attempts (six total) enter SUMMARY with a warning icon and "IP2366 communication instable". A successful register transaction resets the streak; a successful address probe does not. Apply monitoring on all post-detection screens, including configuration and Summary, and during disable/configuration actions. Reconnection never resumes charging. Communication warnings supersede an older Summary reason; disconnection takes priority over instability. Add warning icons to all warning messages, keeping diagnostic/informational dialogs distinct.

## 5. Screen 1: CONFIGURE

Dark LVGL tile layout consistent with the baseline. Defaults: no chemistry, no series-count selection; charge current 1000 mA; termination current 100 mA; charge level 100%. Preserve user settings when returning from SUMMARY; persistence across power cycles is not specified.

Controls:

1. Chemistry buttons, mutually exclusive:
   - LiFePO4: target 3650 mV/cell, battery-low 2500 mV/cell.
   - Li-ion: target 4200 mV/cell, battery-low 3000 mV/cell.
   - LiHV: target 4400 mV/cell, battery-low 3000 mV/cell.
2. Series-count buttons: 2S, 3S, 4S, 5S, 6S, mutually exclusive, initially none.
3. Editable Cell Voltage mV, populated when chemistry is selected. An edit changes selected chemistry: <=3800 mV LiFePO4; >3800 and <=4200 mV Li-ion; >4200 mV LiHV. Updating the inferred chemistry must not overwrite the user's edited voltage. Battery-low and SOC curve follow selected chemistry. Enforce documented 2500-4400 mV limits in 10 mV increments.
4. Charging Current, mA. Enforce 100 mA increments, documented 9700 mA maximum, no lower than termination current, and maximum requested battery charging power 100 W.
5. Termination Current, mA. Enforce 50 mA increments and the 4-bit field capacity (0-750 mA representable). Whether zero disables termination is NOT documented; do not assume it is a valid user option without verification.
6. Charge Level: 0-100%, steps of 10%.
7. Measured pack voltage in V, from 0x50/0x51 with explicit mV-to-V conversion.
8. Start Charging button, enabled only once required selections and input validation are complete. Absence of measurable battery voltage must NOT disable it, because the user explicitly may proceed with a deeply discharged/undetected pack.

Start action:

- Read pack voltage.
- If valid reading is below 100 mV, show "No battery detected. Proceed anyway?" with Proceed and Cancel. Proceed bypasses the voltage-presence check, not valid configuration or hardware fault checks. Do not confuse communication failure with a zero-voltage battery.
- For a detected pack incompatible with the selected chemistry/series count, show "Battery does not fit String Count and/or Chemistry" and do not proceed. Exact compatibility bounds must follow verified device/board capabilities; the user permits all supported 2S-6S packs and deeply discharged packs. No arbitrary lower cutoff may defeat the explicit proceed path.
- Keep charger disabled while applying and verifying settings, then enable charging and enter CHARGING.

## 6. SOC and target-voltage calculation

- Use published manufacturer charging curves: EVE LF105 at 1C for LFP, Molicel P42A at 1C for Li-ion, and the user-approved Grepow 4.4 V curve at 0.5C for LiHV. See interfaces.md and sources/charging-curves.json for original plots, conditions, digitization and hashes. Historical OCV tables are superseded.
- Use one nondecreasing per-cell voltage table per chemistry for forward SOC inference and inverse target lookup, interpolating between points. Equal voltages across the CV plateau are allowed; voltage does not identify a unique SOC there.
- At 100%, use the configured Cell Voltage mV unchanged.
- At 10-90%, invert the selected chemistry's charging curve, cap at configured Cell Voltage mV, floor to the 10 mV register step, and validate against the chip range. Reject unsupported targets rather than wrap or silently raise them.
- Encode per-cell voltage in 0x02, not 0x03.
- For displayed SOC, divide measured pack_mV by the active session's cell count, then use its chemistry's charging curve. Keep the approximate marker. Before whole-percent formatting cap to 99% unless IP2366 completion was accepted by the controller; even 99.6% must not round to 100% while charging. Completion permits the curve estimate, never forces an 80% session to 100%.
- Capacity and cell model are unknown, so actual C-rate cannot be inferred from current alone. The fixed reference rates are approximations, not charging-current recommendations or precise SOC termination. Do not invent current compensation or scale a 4.2 V curve to LiHV. Chemistry, temperature, ageing, pack resistance and imbalance limit accuracy.

## 7. Start configuration

Apply controlled fields while charger is disabled:

1. 0x02: calculated per-cell target voltage.
2. 0x04: selected series count, direct encoding under mask 0x07.
3. 0x03: selected charging current, constrained to 100 W battery charging power.
4. 0x06: 100 mA precharge.
5. 0x0A: chemistry-specific battery-low threshold.
6. 0x0C: user-validated 140 W configuration/headroom; this does not replace the 100 W application limit.
7. NTC: intended 80 uA excitation, temperature sensing/protection enabled; actual control fields/wiring still require verification.
8. 0x08: termination current and automatic recharge disabled.
9. Verify relevant configuration, then 0x00 charger enable=1.

100 W means battery charging power, not input power. Derive the requested current cap from selected pack target voltage so requested current times maximum target pack voltage does not exceed 100 W; round current down to 100 mA steps and validate against termination current. Monitor actual voltage/current during charging. Exact treatment of transient overshoot and measurement errors requires verification; do not advertise a hardware 100 W protection guarantee.

## 8. Screen 2: CHARGING

Upper third, refresh every second:

- Pack voltage and approximate SOC.
- Battery current.
- Elapsed charging time and NTC temperature.
- Use matching colors for numeric voltage/current and corresponding graph traces, e.g. orange voltage.

Middle:

- Voltage and current line graph, updated every second.
- No labels; light-gray grid; history always spans available graph width.
- Separate voltage/current scaling was proposed but not explicitly accepted; choose/document graph scaling and history retention during UI design. Do not imply volts and amperes share physical units.

Bottom:

- Red Abort Charge button.
- On CHG_END (0x31 bit4), immediately disable charging, freeze elapsed time and totals, and turn button green with text Done.
- Timeout or fault stops charging and reports the cause; do not present it as successful completion.

Abort/Done:

- Abort immediately disables charging and freezes totals.
- Apply idle settings from section 4, then show SUMMARY. Done uses the already-frozen completion totals and enters SUMMARY.

## 9. Screen 3: SUMMARY

- Total charging time.
- Total mAh charged.
- Total mWh charged.
- Green OK button returns to CONFIGURE with user settings retained.
- Calculate totals from measured battery current/voltage using actual elapsed sample intervals, not an assumed exact one-second tick. Convert units explicitly once. Current sign, handling invalid/missing samples, and net-versus-positive-charge convention must be documented before integration; do not infer signedness from register names.
- Freeze totals at completion, abort, or fault; waiting for Done must not add time or energy.

## 10. Remaining integration details, not silently decided

1. Validate the selected P2 pin 2/GPIO6 -> 10 kohm -> INT electrical interface, INT-side HIGH level, and wake/power sequencing; connector mapping is documented in the supplied board reference. Direct 3.3 V tie is not the selected design.
2. Thermistor circuit/placement, beta reference temperatures, actual NTC enable/excitation controls, permitted charging temperatures, and missing/shorted sensor handling. 50 kohm / 3850 K alone does not specify these.
3. Published numeric SOC tables for LiFePO4, 4.2 V Li-ion, and 4.4 V LiHV, including source/conditions and limitations of charging-voltage inference.
4. Verified pack-compatibility bounds consistent with all supported 2S-6S packs and the undetected-battery override.
5. Battery-current signedness/direction and integration convention; error and lost-communication behavior.
6. Board power/cable/thermal capabilities and any hardware protection/BMS arrangements; generic pack acceptance does not establish these properties.
7. Graph scales/history and settings persistence across reboot.

Do not stop discussion or routine document work because these remain; stop only implementation whose correctness or safety depends on an unresolved contract. No source code, firmware, or hardware has been changed by this specification update.

Firmware 1.0.6 graph refinement: add a horizontal red dotted reference at the active session's effective full-pack charge-end voltage, using the SOC-derived target for levels below 100% and the configured target at 100%. Include it in voltage autoscaling and show it before the first sample. Move elapsed time to the right column below current and NTC; display the charge-end voltage in its former bottom-left position. Version remains in diagnostics only.

Firmware 1.0.7 supersedes the previous graph scaling and timer placement: voltage scale is fixed at 0 V to (effective target pack voltage + 1 V); current scale is fixed at 0 A to (effective configured charging current + 300 mA), including the 100 W current cap. Add a dotted termination-current reference on the secondary current axis, colored cyan. Keep the voltage reference red. Reduce End text size and display Term in the right-hand current/NTC column where the elapsed time was shown. Move elapsed time to a smaller font in the header between CHARGING and DIAG. Both reference values come from the active session settings and remain visible from startup through the complete history buffer. No changes to charging-control thresholds or version visibility.


Firmware 1.0.8: Before boot initialization writes, check Charge Enable and measured battery current >0 mA. If both indicate the requested active condition, capture cell count, target cell voltage, charge current and termination current. Always perform the existing stop/idle initialization afterward. Save original chemistry, SOC percentage, cell-voltage selection and requested current in tablet flash before enabling a new charge. Restore the complete profile as Configure defaults only when its effective hardware settings exactly match the live boot snapshot. Without a match, restore raw readable values, leave chemistry unset and warn the user to verify chemistry/voltage/charge level. No active charging, no valid snapshot or corrupt saved metadata must never cause an old profile to be blindly restored. Resume requires explicit Start, with all normal checks and fresh totals/history. Version remains in DIAG only.

Voltage graph lower bound is the active chemistry's discharge-end voltage multiplied by cell count, replacing 0 V. The upper bound stays target pack voltage +1 V; current stays 0 A to effective charging current +300 mA. If a custom target is below the discharge-end threshold, clamp the lower bound down to the target so the reference remains visible and the axis interval stays positive.


Firmware 1.1.0: replace DIAG on all screens with a gear. Gear opens a screen with Settings and Diagnostics tabs, Settings selected by default; Diagnostics contains the previous diagnostic data and version. Settings includes Persist Settings, WiFi and ESPNow checkboxes. WiFi opens a dialog with mutually exclusive Access Point / Join WiFi radio controls and SSID, password and mDNS fields, defaulting to blank SSID/password and mDNS name charger1. AP name follows mDNS (first 32 bytes); AP passphrase follows the configured password when at least eight bytes, otherwise the public setup passphrase charger-setup (change it before use). Joining/reconnecting times out after 15 seconds, falls back to AP and displays a warning. ESPNow is a stored flag for a later automation interface.

When Persist is enabled, save all charger and connectivity settings once a charge starts and update option changes during that charge. Restore the saved defaults on reboot even if no charging was active; never automatically start charging. Unchecking Persist removes the full-settings record. Preserve the previous matching-live-profile behavior independently when Persist is off.

The web server mirrors the active tablet screen and provides the same configuration/start/stop/navigation controls, confirmations and safety checks. Browser graph can widen independently, maximum 300 points; tablet stays 240 visible points. UI operations are queued to the main thread; networking runs separately so slow clients do not block charging supervision. See web/README.md for the exact frame/API contract and tested limitations.


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

## 1.5.0 Configure and timed-stop refinements

The current Configure UI, explicit review/cancel behavior, termination time in
minutes (default 360), migration contract and saturated-green SOC bar are defined
in `release-1.5.0.md`, which supersedes earlier conflicting Configure details.
The summary distinguishes cell voltage × string count from the effective
SOC-limited target. A software time limit stops through verified disable and
does not claim a full battery. All active target/display paths share the same
charging-reference SOC tables.

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
