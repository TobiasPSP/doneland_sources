# DC-DC Converters
:stopwatch: Reading time: 10 minutes.

## Quick Overview

*DC-DC Converter* change an input *DC* voltage to a different output *DC* voltage. They cannot work with *AC*.

For *AC* circuits, *transformers* are used to change one voltage into another using alternating *magnetic fields*. Since *DC* does not use *alternate* current and thus does not produce alternating magnetic fields, transformers do not work for *DC*.

*DC-DC Converters* change the voltage electronically by using components that can temporarily store energy, such as *capacitors* or *coils*. In combination with a high frequency *switch* (transistor), they can add or reduce voltage as needed, producing a *constant voltage* (**CV**).

The typical switching frequency is in the range of 50-500kHz, and depending implementation, this frequency can either be *fixed* or *variable*. 

<details>
<summary>Why Should I Care About Switching Frequency?</summary><br/>

  In hobby projects, you typically do not need to care much about the switching frequency of *DC-DC Converters*, and whether they are fixed or variable. Most cheap hobbyist *DC-DC Converters* are *fixed frequency PWM* converters.

  *DC-DC Converters* with *fixed* frequency typically use the same **PWM** (pulse width modulation) that you may have used in your electronics projects to dim LEDs. Since the frequency is fixed and well above audible frequencies, converters will never emit annoying hissing sounds (*coil whine*). Their weak spot are *light loads*: due to the *fixed* frequency and **PWM**, the pulse width can only be shortened so much. With light loads, energy is lost and turned into heat, and efficiency decreases.

  In *DC-DC Converters* with *variable* frequency, typically **PFM** (pulse frequency modulation) is used: the pulse width stays the same but the frequency of pulses changes. They are more efficient with light loads as the frequency can be easily lowered in a wide range. This can lead to a different problem: when the frequency is lowered so much that it enters audible ranges, these converters can produce an audible annoying high pitched hissing sound. This is also known as **Coil Whine** and can be produced by other parts of circuits as well when frequency drops into audible ranges.

  High switching frequency also helps reducing component size (and cost) because due to the high switching frequency, only relatively small amounts of energy need to be stored in capacitors or coils. 

  Lower switching frequencies require larger components but may create a better conversion efficiency and less *EMI* (radio interference).

  For example, an *LM2853* (designed to lower voltage from 5V to 3.3V at a maximum current of 3A), running at a switching frequency of 550kHz, requires a total component area of 206mm2 with larger components and an inductor height of 4.6mm. The same conversion can also be done by a *LM2833Z* at a switching frequency of 3MHz. Now, the total component area is reduced to just 57mm2, and the inductor height reduced to 2mm.

  While all of this may be crucial in microelectronics and consumer devices such as tablets and phones, for hobbyist projects it does not matter much. That's why most *DC-DC Converter* breakout boards are relatively bulky and use switching frequencies in the lower range.
</details>

> [!NOTE]  
> With pure **Buck** or **Boost**, the output voltage must be higher (**Buck**) or lower (**Boost**) than the input voltage. 
>
> For example, even if a **Buck** converter supports an input voltage range of 8-32V and an output voltage range from 1.25-28V, once you actually supply a voltage, the output voltage *must always be lower* than the input voltage. If you supplied 10V, you now can only produce an output voltage of 1.25-10V (practically rather 1.25-9.5V as there needs to be a certain voltage difference between input and output).
> 
> This limitation does not exist for combined **Buck-Boost** converters. They can always accept *any* allowable input voltage and produce *any* desired output voltage within the supported range: such converters are smart enough to decide whether the input voltage needs to raise, stay the same, or fall to produce the desired output voltage.


### **Buck** Or **Boost**: Lower Or Raise Voltages

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

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/dc-dc-converters?305183020426240854)
