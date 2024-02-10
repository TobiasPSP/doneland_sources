# INA226 Current And Voltage Monitoring
:stopwatch: Reading time: 10 minutes.

## Quick overview
**INA226** is a microchip from *Texas Instruments* that can measure *current* and *voltage* and calculate *power* from it. It is often used to *monitor* power consumption or the yield from *solar generators*.

**INA226** internally uses a *ADC* (Analog-To-Digital converter) to measure *voltage*. It uses the **Shunt** principle to measure *current* via measuring the *voltage drop* at a **Shunt** resistor.

The measured values can be read by a microcontroller via *I2C*.

**INA226** is available as breakout board with an integrated **Shunt**:

<img src="images/ina226_soldered.png" width="80%" height="80%" />

