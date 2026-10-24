# BatCharger 1.7.0 — target-relative SOC and partial-charge cutoff

Includes the previously unshipped 1.6.4 SOC presentation changes and the subsequent
request to change partial-charge control. Start Charging on Configure now uses
the same soft green as the confirmation buttons; the web Start control matches.

## SOC tile

Below the saturated-green bar, **Target: xx%** shows the active session's selected
percentage. SOC text remains the estimated absolute SOC. Fill is
`min(100, SOC / target * 100)`: 60% SOC toward 70% gives 85.7%. Native LVGL uses
0–1000 range units for tenth-percent precision; web CSS uses one decimal. The
same goal-relative bar and label appear in web Charger/Graph and export captures.
Unavailable SOC gives zero fill. A valid SOC with a 0% goal gives full fill,
without division by zero. A full bar alone never declares charging complete.

## Partial-charge control

For **100%**, behavior is unchanged: the IP2366 is configured with the entered
cell voltage and terminates normally using its existing current/completion logic.

For **less than 100%**:

1. Configure the IP2366's CV voltage to the entered **100% cell voltage**, times
   the selected cell count. Do not reduce its hardware CV setting to the SOC goal.
2. Derive a separate per-cell **software stop threshold** from the selected
   chemistry's existing charging curve, capped by the entered cell voltage.
3. Round that per-cell threshold upward to integer mV, then multiply by cell
   count. The ADC is documented in mV; the threshold is no longer constrained
   by the hardware CV register's 10 mV steps. Example: 4S LiFePO4 at 70% uses
   3465 mV/cell, stopping at **13.860 V** while hardware CV stays **14.600 V**.
4. At the normal one-second measurement cadence, the first successful valid
   sample at or above the threshold stops through the existing off/readback
   path. Current/temperature read failures still fault and disable safely; the
   measured 100 W fault takes priority over successful target completion.

Completion reason is **Charge target reached**. This completes the requested
session without waiting for a reduced-voltage CV taper. It does not mean the
IP2366 declared the battery full. Hardware full/completion is latched separately,
so the existing SOC cap at 99% remains unless the IP2366 actually reports full.
For targets at the chemistry's full-voltage plateau, brief CV operation can still
occur; voltage-only SOC estimates remain approximate.

A pack already at/above a partial target is rejected before charge enable, with
**Battery is already at or above selected target**. There is no short charging
pulse or automatic restart. Below-threshold undetected/deep packs retain the
existing explicit no-battery confirmation.

The configured current ceiling is now calculated using the **full hardware CV
voltage**, preserving the conservative 100 W limit. Hardware register auditing
and reboot-profile matching also use that full setting. Graph **End**, the red
dotted line, web target voltage and LabLink TargetPackVoltage continue to describe
the selected stopping goal. Review dialogs distinguish **Charging Voltage** from
**Stop at**. LabLink effective cell voltage reports the actual hardware setting.
No wire-format change is introduced.

Profiles saved under the earlier reduced-CV policy still load as UI preferences.
Live boot recovery only trusts a saved profile when it matches the actual full-CV
register snapshot; otherwise the existing unmatched-profile review is required.

## Verified contracts and validation

Exact IP2366Control register contract: 0x02 is 2500 + 10*code mV/cell; voltage
0x50/0x51 is unsigned pack mV with low-byte latching; 0x31 bit4 reports full.
Existing begin/configure/off/readback APIs and pinned LVGL bar range/value
semantics were inspected. Internal values remain integer mV/mA and milliseconds;
no estimated percentage is written to a hardware voltage register.

Known-value tests cover all three chemistries, full CV register values, 1 mV
below/exact cutoff, verified disable, no restart, already-reached/no-enable,
normal 100% hardware completion, and the 99% cap on a software-completed plateau.
The native fixture demonstrates 60% SOC / 70% target / 85.7% bar, then 70% goal
completion. Controller/driver/settings, native LVGL, web JavaScript and shared
LabLink regressions and the ESP32-S3 release build are checked. No hardware
flashed or real charge started during validation. Reload the browser on upload.
