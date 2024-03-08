<img src="/assets/images/power.jpg" width="80%" height="80%" />


# XL4015 Voltage Regulator

> Buck-Regulator from XLSEMI: 5A, 36V, 180kHz

The **XL4015** from *XLSEMI* is a popular step-down (**Buck**) voltage regulator chip that is used in many cheap breakout boards.

Here are the key specs for this chip:

| Spec | Value |
| --- | --- |
| *Input* Voltage | 8V-36V |
| *Output* Voltage | 1.25V-32V |
| Max *Output* Current | 5A |
| Max Continuous Power | 40W |
| Minimum Voltage Difference | 0.3V |
| Switching Frequency | fixed 180kHz |
| Efficiency | up to 96% |
| Short Circuit Protection | yes |
| Constant Current Function  | yes |
| Thermal Protection | yes |
| Design | PWM-Buck |

> [!WARNING]
> These are the maximum *chip* values. Neither are they intended for constant use, nor may they apply to a *breakout board* that uses this chip along with other components and designs that may be *less capable*. Always also check the *breakout board* specs.

## Common Pitfalls

Here are the common *novice* misperceptions and pitfalls that frequently cause breakout boards to go off in flames:

* **Maximum Current:** The *maximum* current (of **5A** for this chip) does not mean that any breakout board using this chip can produce **5A** output. It is the absolute *maximum* the chip can sustain, typically only for *short periods of time*, and only when additional *heat sinks* are in place.
* **Maximum Power:** An important rating is often missing in the specs: the *overall power* the regulator can provide (in *Watts*). **40W** allows a current of **8A** at **5V**, but only a current of **1.6A** at **24V**.
* **Consider *both*:** To operate a regulator safely, neither exceed the maximum current *nor* the maximum power:
  * should you operate this regulator at an output voltage of **5V**, the maximum power of **40W** would allow a maximum current of **8A** however the maximum allowable current is **5A**. Thus, when operated at **5V** output, the maximum power is just **25W**.
  * operating the regulator at an output voltage of **24V** cannot provide the maximum current of **5A** because this would result in a power of **120W**. At **24V** output, the maximum allowable current is **1.6A**.
* **Input Voltage > Output Voltage:** this is a **Buck** regulator. It *reduces* the input voltage. Even though the *output voltage* has a wide selectable range of *1.25-32V*, once you choose an *output voltage*, this limits the range of allowable *input* voltages:
  * The regulator supports *input* voltages in the range of *8-36V*. If you set the regulator to an *output* voltage of *12V*, the *input* voltage now must be in the range of *12.3-36V* (add *0.3V* to the *output voltage*: this is the *minimum voltage difference* found in the specs above).
   
<details><summary>What does *Switching Frequency* mean?</summary><br/>


</details>


converter capable of outputting significant currents of up to *5A*. 

The chip is sold separately and also embedded in a complete breakout, board ready-to-go, for as little as EUR 1.00 in total:

<img src="images/xl4015_boards.png" width="100%" height="100%" />

> [!IMPORTANT]  
> Boards can *differ considerably*: not all boards support all **XL4015** features.
> 
> Some boards come with just *one* potentiometer to setup a *constant voltage* only (i.e. left board in above image). This is sufficient if you i.e. plan to use the converter to supply a constant voltage to a microprocessor from a 8-36V input range.
> 
> At practically same cost, different boards provide *two* potentiometers (i.e. right board in above image), so in addition to a *constant voltage*, you can also set a maximum *constant current*. This can be an important requirement, i.e. when you plan to use it for battery charging or to drive LEDs.
>
> If you plan to stock your electronic lab, I recommend you choose boards with *two* potentiometers for maximum flexibility.

| Property | Value |
| --- | --- |
| Input Voltage | 8-36V |
| Output Voltage | 1.2-32V |
| Max Output Current | 5A |
| Efficiency | up to 96% |
| Switching Frequency | 180kHz |

> [!TIP]
> The maximum output current of **5A** requires to add a heat sink to the chip. While the **XL4015** is dependable and rugged, avoid exploting its maximum specs. Boards using **XL4015** run well for long-time output currents of **3-4A**.
>
> Stable output current also depends on the voltage difference between input and output. The lower the difference, the less work needs to be done, and the more stable output current and less heat is produced.

| Feature | Supported |
| --- | --- |
| Constant Current | yes |
| Output Shortcut Protection | yes |
| Over Voltage Protection | no |
| Thermal Protection | yes |

[Data Sheet](materials/XL4015_datasheet.pdf)

> Tags: Buck, CC, CV, 36V, 5A

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/dc-dc-converters/buck/xl4015?344080020426240854) - last edited 2024-02-27
