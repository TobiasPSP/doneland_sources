# DC-DC Converters

In *AC* circuits, transformers are used to transform one voltage into another using *magnetic fields*. This does not work for *DC* though.

For *DC*, to change the voltage you use electronic circuits that take a given *DC* voltage and convert it to a different *DC* voltage. 

Typically, *DC-DC Converters* accept a wide range of input voltages and convert it to a precise output voltage. For example, a *DC-DC Converter* can accept a wide range of input voltages from a car battery (12V) to a 9V block battery, and convert the input voltage to exactly *5V* (or *3.3V* or whatever you need) to run i.e. a microcontroller.

<details>
  
<summary>:information_source: How Do DC-DC Converters Work?</summary></summary><BR/>

  While transformers use the magnetic field created by *alternate current* and two coils with a different number of windings, *DC-DC Converters* work differently:
  
  They combine a fast transistor switch and a transient energy storage like a capacitor or a coil. Capacitors get loaded and unloaded in quick succession and "pump up" or lower the voltage. If more energy is needed, more expensive coils are used to temporarily store energy.

## **Buck** And **Boost**: Lower Or Raise Voltages

  There are excellent resources available at *YouTube* and in the net that explain in great detail how *DC-DC Converters* internally work. For *practical* purposes, they are breakout boards that take an input voltage and deliver a different voltage that can be adjusted with a potentiometer.
  
</details>

There are many types of *DC-DC Converters* but two types are most important:

* **Buck** (lower the voltage): A **buck* converter *decreases* the input voltage. This is the most common converter which is typically used to supply microcontrollers (which require very low voltages) from powerbanks or car batteries.
* **Boost** (raise the voltage): A **boost** converter *increases* the input voltage. This way, you could i.e. run a *5V* microcontroller off a single *3.7V* lithium-ion battery. **Boost** converters can be used in many places, i.e. if you want to run a series of LEDs from a battery, you could "pump up" the input voltage.

There are also combinations of both: **Buck-Boost-Converters** convert a DC voltage to another DC voltage, regardless of whether the input voltage is lower or higher than the output voltage.

> [!TIP]
> *DC-DC Converters* can also *stabilize* the voltage. Lithium-Ion batteries, for example, can supply a wide range of voltage between 3.7V and 4.2V, based on charge state. If you wanted to run a *voltage-sensitive* device like a microcontroller off such a battery, you could either use a **Buck** (to *lower* the voltage to precisely 3.3V for an *ESP8266*) or a **Boost** (to *raise* the voltage to precisely 5V for an *Arduino*).
