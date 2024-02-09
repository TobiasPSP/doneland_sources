# Measuring Currents
:stopwatch: Reading time: 10 minutes.

## Quick overview
Unlike *voltage*, *current* cannot be measured directly. Instead, you measure *indirect effects*, for example:

* [**Voltage Drop**](Shunt): Every *load* consumes energy and causes a proportional *voltage drop* that can be measured to determine the *current* indirectly: by inserting an *artificial load* in the form of a **Shunt** *resistor*, the *current* can be measured via the *voltage drop* at the known **Shunt** resistance. The **Shunt** must have (a) a *very precise* resistance, (b) a *very low* resistance, and (c) must be capable of handling the *total load current*.
* **Hall Effect**: Every electrical current produces a magnetic field. In *AC* current, the magnetic field is alternating and can be measured using a coil. In *DC* current, the magnetic field is fixed and can be measured using the so-called *hall effect*. Since the sensor is separate from the *load circuit* , even very high currents can be measured, and there is no risk of overload. Magnetic fields generated in the proximity by other sources can influence the result.

