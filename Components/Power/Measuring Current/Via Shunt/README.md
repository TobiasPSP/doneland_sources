<img src="/assets/images/lightning.png" width="100%" height="100%" />


# Measuring Current Via Shunt

> When You Connect a Known Resistor In Series With a Load, the Voltage Drop is Proportional to the Current.

Measurement should not influence the circuit you are examining: that is why the inserted resistor must have a *very low* resistence in the range of only a few *milliohm*. This ensures that the *real load* "won't notice" the presence of the additional *shunt* resistor, and no excessive energy is consumed by the *resistor* and converted to *heat*. Such special resistors are called **shunt**.

When you add a *shunt* to a circuit, all of the current passes the low-resistance *shunt*. The *current* flow is equal to the *voltage drop* across the *shunt* divided by the resistance of the *shunt*. 

The result is typicall a *very low voltage* that can be measured. Since this voltage drop is in the range of a few *milliamperes*, special amplifier circuits are used. A regular *multimeter* would not be able to measure the minimal voltage drop across a *shunt* with the necessary precision.

## Selecting a Shunt

The most important spec for a *shunt* is the maximum *current* it is supposed to measure. *Shunts* are typically designed to drop *50mV*, *75mV*, or *100mV* when operating at their maximum rated current. When the maximum current is known, the necessary *resistance* can be calculated based on the anticipated voltage drop.

Depending on maximum current, a *shunt* can be a tiny **SMD** resistor or a huge external stripe of metal. For large currents, you can even build your own *shunt* from a piece of wire.

Here is an example calculation for a maximum current of **5A** and a desired *voltage drop* of **100mA**:

* **0.02 Ohm:** The required *shunt* resistance is according to *Ohms Law* calculated like this: *U = R * I*, *R = U / I*, thus *0.1V / 5A = 0.02 Ohm*. The maximum *power* passing through the *shunt* would be *5A * 
* **0.5W:** The *shunt* would also need to be rated for *P = U * I*, thus *0.1V * 5A = 0.5W*. This would be the *minimum* rating, and you should double it as a safety margin.


> Tags: Measure, Current, Shunt, Voltage Drop

:eye:&nbsp;[Visit Page on Website](https://done.land/components/power/measuringcurrent/viashunt?379984020426240854) - last edited 2024-02-27
