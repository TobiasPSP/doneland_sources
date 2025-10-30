<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Measuring Voltage and Current

> Measuring Voltage, Current, and Power Consumption 

Often, raw power supply properties are needed: voltage can estimate the current state of charge of a battery, for example, and current indicates the power draw.

By measuring current and voltage, you can also calculate the total power. *Coloumb meters* do this **over time** and work like a "power meter", indicating the total power drawn or produced over a given period of time, for example the yield of a solar panel.



## Measuring Voltage
Both *voltage* and *current* are measured as *voltages*: an *Ampere-Meter* internally is a *Volt-Meter*, too. So let's first look at how voltages can be measured.

To measure a voltage, connect an analog input pin of a microcontroller to the power source, but make sure the expected voltage is within the range that this analog pin can handle.

If you need to measure higher voltages, use a simple *voltage divider* consisting of two high-ohm resistors. This way, your microcontroller can measure only a given "percentage" or "fraction" of the total voltage, staying within its limits, and you can later extrapolate the real voltage in your firmware.

Voltmeters (as well as analog input pins and voltage dividers) have a *high resistance*. This is necessary because with a Voltmeter you are *short-circuiting* your circuit. 

Due to the high resistance, nothing bad happens, and only a very small current flows. By using an analog input pin, you can directly measure this voltage (if it is within the acceptable voltage range), and with a voltage divider, you can measure the *voltage drop* at one of the two resistors.


### Analog Voltmeters

Classic analog voltmeters use a coil or iron part that responds to the *magnetic field* produced by the electrical current. The amount of deflection of the pointer is proportional to the current flowing through the coil, which, in turn, is proportional to the voltage being measured. Since the *internal resistance* of the voltmeter is known, the amount of *current* flowing through it is directly proportional to the *voltage*:

* **5V:** When the voltmeter is connected to **5V** and has a known internal resistance of *500 Ohm*, according to *Ohms law* the *current* then is *U / R = I*, thus *5V/500Ohm = 10mA*. The current of *10mA* produces a magnetic field of 4x10-8 Tesla which moves the indicator of the analog voltmeter.
* **10V:** When the voltmeter is connected to **10V** and continues to have a known internal resistance of *500 Ohm*, according to *Ohms law* the *current* now is *U / R = I*, thus *10V/500Ohm = 20mA*. The current of *20mA* produces a magnetic field of *double the strength*: 8x10-8 Tesla which moves the indicator of the analog voltmeter *twice* as much.


### Digital Voltmeters

*Digital* voltmeters add an **ADC** (Analog-Digital-Converter) to convert analog voltage to a digital signal that is then displayed. When you are using a microcontroller and one of its analog-input pins, you are essentially building a *digital* voltmeter.

## Measuring Current

Current cannot be measured directly. Instead, there are two physical effects that can be used to measure current **indirectly** through a voltage, using the principles outlined above:


* [**Voltage Drop**](https://done.land/components/power/measuringcurrent/viashunt/):     
  Every *load* causes a *voltage drop*. By inserting an *artificial load* (called **Shunt** resistor) with a *very precise known resistance* in series with the real *load*, the *current* can be measured via the *voltage drop*.     
  
  In essence, you are building a *voltage divider* where one resistor is the **Shunt** and the other resistor is the load that you want to measure.    

  The **Shunt** resistance must be *very low* in order to minimize energy losses through *heat*.    
  
  A *shunt* can measure *current* very precisely and is immune to noise and magnetic fields in the vicinity. However, it requires the insertion of a *shunt* resistance into the circuit and is **not isolated** from the circuit that you want to measure.

  For this reason, shunts are typically used with low currents and voltages. 

* **Magnetic Field:**     
  Every electrical current produces a magnetic field. In *AC* current, the magnetic field is alternating and can be measured using a simple coil. With *DC*, the magnetic field is constant. It can be measured using more expensive *hall effect* sensors.    

  Since magnetic fields can be measured "wirelessly" in the vicinity of currents, the measuring setup is **isolated** from the circuit you measure. Typically, such sensors require the wire with the current to be fed through a coil or hall sensor, and *clamps* simplify this even further.

  This is why this approach is safer, especially with high currents and voltages. However, it is also less accurate, especially with low currents, and subject to noise produced by other magnetic fields in the vicinity.

## Coloumb Meters
In some instances, you may not be interested in the *momentary* voltage and current. Instead, you'd like to know **over some time**, how much total power a power source produces (i.e. a solar panel or a battery under test), or how much energy a load consumes.

This is what *coloumb meters* do: they, too, measure voltage and current, but in addition they accurately calculate the total power and often can also accumulate it over time.
  

> Tags: Measure, Current, Voltage Drop, Hall Effect, Shunt, Coloumb Meter

[Visit Page on Website](https://done.land/components/power/measuringcurrent?376991020426240854) - created 2024-03-10 - last edited 2025-10-29
