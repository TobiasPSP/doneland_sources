# BatCharger 1.0.3

This combined update includes:

- Corrected NTC nominal resistance: 10,000 ohm at 25 C, retaining beta 3850 K. The user confirmed the fitted sensor is 10 kohm, resolving the earlier 50 kohm assumption. The same conversion helper now serves the displayed temperature and diagnostic candidate calculations.
- The 1.0.2 startup handshake: before charging is confirmed, input loss disables charging and waits for input to return, reconfiguring/verifying before enabling last. Startup has a 10-second application deadline. Established charging still latches input loss as a fault; hardware/I2C faults remain immediate.
- Visible DIAG button on every screen. **BatCharger 1.0.3** appears at the top of diagnostics only, including before any measurement sample exists. No version label was added to the normal screens. No USB serial or terminal is needed to identify the firmware.
- Existing fault snapshots, failed-register/readback diagnostics and before/after NTC excitation indication.

Known-value checks: 200 mV / 20 uA = 10 kohm and 800 mV / 80 uA = 10 kohm both yield 25.0 C. The user's observed 863 mV / 80 uA = 10.7875 kohm yields about 23.3 C under the retained beta model. Zero/saturated ADC readings and inconsistent excitation indications remain unavailable rather than generating a temperature.

Current measurements, totals and current-limit configuration are not recalibrated. The supplied meter comparisons are retained as observations; no guessed low-current correction is applied.

The project is updated in place. The standalone application image is firmware/firmware.bin at 0x10000; firmware/BatCharger-combined.bin includes the bootloader/partition/application images for flashing at 0x0. Use the same upload workflow that worked for the original firmware. This task has not flashed the tablet.
