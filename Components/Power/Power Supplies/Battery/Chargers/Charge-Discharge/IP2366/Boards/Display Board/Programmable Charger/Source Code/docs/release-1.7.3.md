# BatCharger 1.7.3

Charging status is prefixed IP2366: and continues to report the chip state. Graph markers now estimate CC/CV from measured pack mV and charging mA, independently of register 0x31 stage. Hardware control, completion flags and safety handling are unchanged.

The 1 Hz estimator uses a three-sample median, least-squares trends over 5-10 seconds, then requires five seconds of continuous qualifying evidence. CV requires a current decline of at least max(20 mA, 1% of mean current) across the window, voltage within 60 mV/cell below the target or above it, and voltage not falling more than 10 mV/cell across the window. CC requires voltage at least 10 mV/cell below target, rising by at least 2 mV/cell across the window, with current not declining beyond the margin. These are presentation heuristics, not proof of which regulation loop is active. The generous target margin accommodates the observed ADC offset. Single spikes are median-filtered; invalid/inactive samples and gaps over two seconds reset pending evidence. Ambiguous behavior retains the last confirmed marker mode.

After confirmation a transition is timestamped at the start of its qualifying evidence; the first confirmed mode labels the beginning of the graph. Median/trend warm-up adds detection latency beyond five seconds. Both tablet and web/export use the same timestamped event log and full-session scaling.

## Calibration
Settings includes signed Voltage Calibration (mV, pack voltage) and Current Calibration (mA), default zero, range -5000..5000. These offsets are added exactly once at the measurement boundary. Corrected unsigned telemetry clamps to 0..65535 to prevent underflow/overflow. Tablet, web, graph/SOC/trend markers and ESPNow consume corrected values; mAh and mWh integrate corrected current and power. Raw ADC values remain in Diagnostics, alongside corrected readings, and raw measured power still drives the 100 W protection. Hardware setpoints, startup pack checks and completion flags are unaffected.

Offsets always persist independently of Persist charger config. Version-1 preferences migrate to zero offsets. Calibration changes do not rewrite historical points/totals; the integration interval spanning a change is omitted and trend evidence resets. Settings/HTTP signed values use strict decimal validation. Example raw 12525 mV plus -105 mV displays 12420 mV.
