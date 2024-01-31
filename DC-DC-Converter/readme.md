# DC-DC Converters
:stopwatch: Reading time: 10 minutes.

## Quick Overview

*DC-DC Converter* change an input *DC* voltage to a different output *DC* voltage. They cannot work with *AC*.

For *AC* circuits, *transformers* are used to change one voltage into another using alternating *magnetic fields*. Since *DC* does not use *alternate* current and thus does not produce alternating magnetic fields, transformers do not work for *DC*.

*DC-DC Converters* change the voltage electronically by using components that can temporarily store energy, such as *capacitors* or *coils*. In combination with a high frequency *switch* (transistor), they can add or reduce voltage as needed, producing a *constant voltage* (**CV**).

The typical switching frequency is in the range of 50-500kHz, and depending implementation, this frequency can either be *fixed* or *variable*. 

<details>
<summary>Why Should I Care About Switching Frequency?</summary><br/>

  In hobby projects, you typically do not care about the switching frequency of *DC-DC Converters*, and whether they are fixed or variable. Most cheap hobbyist *DC-DC Converters* are *fixed frequency PWM* converters.

  *DC-DC Converters* with *fixed* frequency typically use the same **PWM** (pulse width modulation) that you may have used in your electronics projects to dim LEDs. If there ever is interference, due to the fixed (and thus known) frequency, it is easier to identify and filter out. Also, since the frequency is fixed and well above audible frequencies, converters will never emit annoying hissing sounds. While efficiency generally is very good for these converters, unfortunately for light loads this is not the case. Due to the *fixed* frequency, the pulse width can only be shortened so much, so with light loads, energy is lost and turned into heat.

  In *DC-DC Converters* with *variable* frequency, typically **PFM** (pulse frequency modulation) is used: the pulse width stays the same but the frequency of pulses changes. They are more efficient with light loads as the frequency can be easily lowered in a wide range. This can lead to a different problem, though: when with light loads the frequency is lowered so much that it enters audible ranges, these converters can produce an audible annoying high pitched hissing sound. This is also known as **Coil Whine** and can be produced by other parts of circuits as well when frequency drops into audible ranges.
</details>

In addition, many *DC-DC Converters* can also limit the maximum current by reducing the voltage when the current exceeds a limit (*constant current*, **CC**).


### **Buck** Or **Boost** (Or Both): Lower Or Raise Voltages

*DC-DC Converters* can lower or raise the voltage:

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

