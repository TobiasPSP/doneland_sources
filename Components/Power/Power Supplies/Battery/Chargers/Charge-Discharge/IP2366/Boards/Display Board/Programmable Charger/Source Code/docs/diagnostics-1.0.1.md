# Current and NTC investigation — 1.0.1

Reported on hardware after the initial firmware worked: a 200 mA setting displays about 320 mA, a 1000 mA setting about 1130 mA, and NTC temperature is about 65 C at approximately 26 C ambient.

The approximately 120-130 mA difference is an observation, not yet an established ADC calibration error. An independent battery-side ammeter comparison is pending. No guessed subtraction, gain adjustment, changed charge-current encoding or altered power/totals calculation has been applied.

## Get the values

During charging, tap the upper measurement tile (voltage/current/temperature). A read-only diagnostic snapshot shows:

- Battery ADC voltage and current, using the existing mV/mA decoding.
- Actual readback of current-limit register 0x03, including its code and decoded mA.
- Charge/input status bytes 0x31 and 0x33.
- Raw 0x77 before AND after the NTC ADC pair, reported 20/80 uA excitation, and whether that indication changed during acquisition.
- NTC voltage in mV, inferred resistance, and candidate temperature calculations at both 20 uA and 80 uA using the supplied 50 kohm / B3850 model.

The snapshot is not a single atomic cross-register capture. Close it and tap again to refresh. Opening it does not pause charge monitoring.

Alternatively send `d` over USB serial at 115200 baud for the same values. This reads the latest cached sample and does not initiate configuration writes.

If the excitation indication changes during the NTC sample, temperature is marked unavailable for that sample rather than pairing voltage with an inconsistent excitation. Identical indications before/after cannot prove the current never changed in between, nor validate the electrical interpretation. The temperature caption now identifies it as an approximate NTC-derived value.

At 26 C the supplied beta model predicts approximately 47.9 kohm. The fourfold difference between the two documented excitation currents makes a selection/physical-current mismatch a useful hypothesis to test, not an established cause. A simple 50 kohm nominal sensor at 80 uA would nominally require 4 V at 25 C, above the documented 3.3 V ADC range; actual bias/compliance must not be inferred from that ideal calculation.

Use the raw values plus independent current/temperature observations to establish the correct calibration or circuit interpretation before changing displayed physical values. Hardware/protection design remains externally handled.
