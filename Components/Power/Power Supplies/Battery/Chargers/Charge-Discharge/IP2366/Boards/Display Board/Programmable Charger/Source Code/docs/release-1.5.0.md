# BatCharger 1.5.0 — Configure and timed termination

Configure now has an explicit red CANCEL/close control above its numeric
keyboard. Cancel restores the field's value from when editing began; the
keyboard checkmark accepts it. Focusing a nested input scrolls its ancestors so
the selected value stays visible above the keyboard and Cancel control.

Charge level is in the left column without a visible label. The right column
shows **cell voltage × string count** in volts, in the same 18 px font as the
numeric inputs. Charge level now offers 0–100% in 10% steps.

Start Charging opens a summary containing Charging Voltage (the product above),
String Count, Cell Voltage, Charge Level, Termination Current and Termination
Time. Red CANCEL closes it without enabling the charger; green OK submits the
reviewed settings. The effective SOC-limited target is shown separately, since
it can differ from cell voltage × string count. The existing no-battery override
remains a separate confirmation. Changed settings invalidate that confirmation,
including a changed termination time. The web interface has the same review.

## Termination time

`Config::terminationTime_min` is an integer number of minutes, default **360
(six hours)**, configurable from 1 to 65,535. Conversion to the internal elapsed
millisecond clock occurs at the control boundary using `uint64_t(minutes) *
60000`. Starting and Charging both count toward session elapsed time. Every
controller tick checks whether elapsed time **exceeds** the limit, independently
of measurement/status polling. Reaching the exact limit does not stop until it
has been exceeded.

The existing stop/off/readback path disables charging and preserves the reason
**Termination time reached**. This is a timed stop (`Aborted` lifecycle), not
proof that the battery is full; it opens Summary and does not grant 100% SOC.
Communication failures during disable still become faults and retain the
unconfirmed-disable warning. Stopped sessions do not automatically restart.
Existing hardware faults, startup timeout and ESP-NOW owner timeout remain
independent protections and can stop a session earlier.

The field is included in web config/state/start commands and persisted charger
profiles. Profile record v2 retains the existing 18-byte length and checksum
algorithm: byte 2 is version 2; formerly reserved bytes 3 and 7 now hold the low
and high byte of minutes. Version 1 requires those bytes to remain zero and
restores the six-hour default. Embedded settings record size/offsets and NVS
keys stay stable, so existing WiFi and charger selections survive upgrading.
The Persist charger config policy remains unchanged.

LabLink's existing charger wire profile has no time field. ESP-NOW starts use
the tablet's currently configured termination time (six hours by default).
This release does not allocate a new LabLink property or alter shared codecs;
the existing time limit is enforced for all session origins. The bundled
LabLink 1.1.0 integration from the current-meter work is preserved.

## Charging curves and SOC

Verified against the exact integration source and stored manufacturer source
hashes: target percentage calls `lookup(chemistry, percent, true)`;
displayed/tablet/web/ESP-NOW SOC calls the inverse direction of the **same**
`curve(chemistry)` tables. The tables are charging terminal-voltage references:
EVE LF105 LiFePO4 at 1C, Molicel P42A Li-ion at 1C, and the approved Grepow LiHV
4.4 V reference at 0.5C. Historical rest/OCV files are provenance only and are
not active. At 100%, target voltage still uses the entered cell voltage as
requested. Below 100%, the interpolated charging-curve voltage is capped by the
entered cell voltage and rounded down to the IP2366's 10 mV step. Voltage-only
SOC remains approximate, particularly on a CV plateau; uncompleted sessions
remain capped at 99%.

The SOC progress fill is now saturated green `#00ff35`, fully opaque on the
tablet, with the existing gray remaining segment. The web uses the same green.

## Verified contracts and checks

- Exact LVGL 9.2.2 keyboard implementation: numeric keyboard events, CANCEL,
  READY and explicit input handling. Exact scroll implementation confirms that
  nested fields need `lv_obj_scroll_to_view_recursive`; the immediate-parent
  variant cannot scroll the non-scrollable input row's parent form.
- Exact Arduino ESP32 2.0.17 Preferences implementation: committed byte count,
  read length and byte-record semantics checked before persistence changes.
- Controller/driver/settings regressions, exact native LVGL UI fixtures, shared
  LabLink regressions, web JavaScript tests and source-curve/hash checks.
- Known-value timed stops: one minute, six-hour default, exact-boundary behavior,
  timer wraparound, and failed disable. v1-to-v2 profile/settings migration,
  non-default time persistence, review cancellation and confirmation binding.

Build and tests use simulated hardware. No physical device is flashed or real
charge started as part of validation. Reload the browser after uploading.
