# DC-DC Converters
:stopwatch: Reading time: 10 minutes.

## Quick Overview

In *AC* circuits, transformers are used to transform one voltage into another using *magnetic fields*. This does not work for *DC* though.

For *DC*, to change the voltage you use electronic circuits that take a given *DC* voltage and convert it to a different *DC* voltage. 

Typically, *DC-DC Converters* accept a wide range of input voltages and convert it to a precise output voltage. For example, a *DC-DC Converter* can accept a wide range of input voltages from a car battery (12V) to a 9V block battery, and convert the input voltage to exactly *5V* (or *3.3V* or whatever you need) to run i.e. a microcontroller.

<details>
  
<summary>:information_source: How Do DC-DC Converters Work?</summary></summary><BR/>

  While transformers use the magnetic field created by *alternate current* and two coils with a different number of windings, *DC-DC Converters* work differently:
  
  They combine a fast transistor switch and a transient energy storage like a capacitor or a coil. Capacitors get loaded and unloaded in quick succession and "pump up" or lower the voltage. If more energy is needed, more expensive coils are used to temporarily store energy.

  There are excellent resources available at *YouTube* and in the net that explain in great detail how *DC-DC Converters* internally work. For *practical* purposes, they are breakout boards that take an input voltage and deliver a different voltage that can be adjusted with a potentiometer.
  
</details>


### **Buck** Or **Boost**: Lower Or Raise Voltages

There are many types of *DC-DC Converters* but two types are most important:

* **Buck** (lower the voltage): A **buck* converter *decreases* the input voltage. This is the most common converter which is typically used to supply microcontrollers (which require very low voltages) from powerbanks or car batteries.
* **Boost** (raise the voltage): A **boost** converter *increases* the input voltage. This way, you could i.e. run a *5V* microcontroller off a single *3.7V* lithium-ion battery. **Boost** converters can be used in many places, i.e. if you want to run a series of LEDs from a battery, you could "pump up" the input voltage.

There are also combinations of both: **Buck-Boost-Converters** convert a DC voltage to another DC voltage, regardless of whether the input voltage is lower or higher than the output voltage.

> [!TIP]
> *DC-DC Converters* are often used to *stabilize* the voltage. Lithium-Ion batteries, for example, can supply a wide range of voltage between 3.7V and 4.2V, based on their charge state. If you wanted to run a *voltage-sensitive* device like a microcontroller off such a battery, you could either use a **Buck** (to *lower* the voltage to precisely 3.3V for an *ESP8266*) or a **Boost** (to *raise* the voltage to precisely 5V for an *Arduino*).

### Constant Current (CC)

Simple *DC-DC Converters* produce a *constant voltage* (**CV**): regardless of input voltage, the output voltage is *constant*. 

More advanced *DC-DC Converters* can also produce a *constant current* (**CC**): the output voltage is set to a given *maximum* but is automatically lowered to a level where a *constant current* flows. A *constant current* can be useful for a variety of use cases, i.e.:

* **Protection**: **CC** can protect you from accidental shortcuts: if the output is shortened, only a safe maximum current will flow, and the *DC-DC Converter* will automatically lower the voltage to almost 0V in this case, protecting you from burning wires and damaged components.
* **LED**: *LEDs* are *current-driven*. They need a certain current to light up brightly. This is why you typically add a *current-limiting resistor* to *LEDs*. Instead, you could also supply the *LEDs* directly from a **CC** power source. This is even better than using resistors because not every LED is equal, and what really matters in the end is the exact *current* that is supplied. A resistor is always just an approximation.
