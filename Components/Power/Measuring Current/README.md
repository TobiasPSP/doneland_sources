# Measuring Currents
:stopwatch: Reading time: 10 minutes.

## Quick overview
Unlike *voltage*, *current* cannot be measured directly. Instead, you measure *indirect effects*, for example:

* [**Voltage Drop**(Shunt)]: Measure the *voltage drop* at a *very low ohm resistor* (called **Shunt**) connected *in series* with your load. The voltage drop very accurately correlates with the *current*. However, the **Shunt** resistor must be capable of handling the total load current.
* **Hall Effect**: Every electrical current produces a magnetic field. In *AC* current, the magnetic field is alternating and can be measured using a coil. In *DC* current, the magnetic field is fixed and can be measured using the so-called *hall effect*. Since the sensor is separate from the *load circuit* , even very high currents can be measured, and there is no risk of overload. Magnetic fields generated in the proximity by other sources can influence the result.

