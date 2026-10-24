# BatCharger 1.6.4

The SOC tile now shows **Target: xx%** below the progress bar. Its saturated-green
fill measures progress toward the selected target: `min(100, SOC / target * 100)`.
For example, 60% SOC with a 70% target fills 85.7% of the bar. The SOC text still
shows the estimated absolute SOC, and reaching a full bar does not declare the
battery full or change charging/termination behavior.

Tablet bars use a 0–1000 LVGL range for tenth-percent presentation precision;
web bars use CSS percentage widths rounded to one decimal. The target always
comes from the active session, not an editable draft. The same representation
is used in the web Charger/Graph tiles and PNG/PDF captures. Invalid readings
show an empty bar. For the supported 0% target, any valid SOC has met the goal
and the bar is full; division by zero is avoided.

Verified against the exact LVGL 9.2.2 bar range/value API. Known-value tests cover
60/70, values beyond target, zero target and missing SOC; the native fixture uses
a 4S LiFePO4 pack at 13.820 V to display 60% SOC and an 85.7% bar toward 70%.
Native/web checks and ESP32-S3 build validated. No hardware flashed.
