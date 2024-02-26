# Measuring Currents
:stopwatch: Reading time: 10 minutes.

## Quick overview
Unlike *voltage*, *current* cannot be measured directly. Instead, you measure *indirect effects*, for example:

* [**Voltage Drop**](Via%20Shunt): Every *load* consumes energy and causes a proportional *voltage drop* that can be measured to determine the *current* indirectly: by inserting an *artificial load* (**Shunt** resistor) in series with the *load*, the *current* can be measured via the *voltage drop* at the known **Shunt** resistance. The **Shunt** must have (a) a *very precisely known* resistance, (b) a *very low* resistance, and (c) must be capable of handling the *total load current*.
* **Hall Effect**: Every electrical current produces a magnetic field. In *AC* current, the magnetic field is alternating and can be measured using a coil. In *DC* current, the magnetic field is fixed and can be measured using the *hall effect*. Since coil and hall sensor are physically separated from the *load circuit*, even very high currents can be measured. There is no risk of thermal overload. Magnetic fields generated in the proximity by other sources can influence the result, though.

[Visit Page on Website](https://github.com/tobiaspsp/doneland_sources/components/power/measuring%20current?376991020426240854)
