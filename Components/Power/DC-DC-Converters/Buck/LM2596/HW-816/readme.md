<img src="/assets/images/power.jpg" width="80%" height="80%" />

# HW-816 Programmable Buck Converter

> Digitally Programmable 3A 7-37V To 0.5-35V Buck Converter With Display

The **HW-816** is a buck converter based on the *LM2596* regulator from Texas Instruments. It comes with a three-digit 7-segment voltmeter and four buttons. 

This buck converter is exceptional in the way its output voltage is set. Rather than using a conventional multi-turn potentiometer, the output voltage can be lowered or raised in small increments of *0.02V/0.1V* by two push buttons. 

The board is occasionally available for under EUR 3.00 in which case it serves very well as a cheap and small versatile mini bench power supply.

> [!TIP]
>
> By soldering wires to the push buttons, the output voltage decrement and increment functionality can easily be controlled by microcontroller *GPIOs*, additionally enhancing the versatility of this board. In combination with a voltage sensing shunt, the board can be an excellent choice for digitally controllable *constant voltage* power sources of up to *3A*.

<img src="images/XL4016_cv_w.png" width="70%" height="70%" />



> [!CAUTION]
>
> This is a *Constant Voltage (CV)*-only Buck converter. It cannot supply a *constant current* (*CC*) and is therefore unsuitable for charging batteries.






| Property | Value |
| --- | --- |
| Input Voltage | 7-36V                                                        |
| Output Voltage | 0.5-35V |
| Max Output Current | 3A (>2A add heat sink) |
| Size | 56x41x13mm |
| LED                | 2 (*IN* and *OUT*, indicating the voltage the voltmeter is showing) |
| Voltmeter | 3-digit, input or output voltage, can be turned off |

> [!CAUTION]
>
> For output currents >2A, an additional *heat sink* and/or *fan* is required.




## Measuring Input/Output Voltage

The board comes with *four push buttons*, two on each side of the display. The two lower buttons on each side are marked *IN/OUT* and *ON/OFF*:

* **IN/OUT:** Toggles the voltmeter to display either the input voltage or the output voltage. The currently selected mode is shown by the LEDs *IN* and *OUT*.
* **ON/OFF:** When short-pressed, turns the voltmeter on and off. When long-pressed, turns the output voltage terminal on and off. When turning the output voltage off by a long-press without a load connected, it may take a few seconds for the output voltage to drop to 0V.

## Adjusting Output Voltage

This is a *buck* converter: the *output* voltage is always *lower* than the *input* voltage. The maximum output voltage is about *1-2V* below the input voltage.

The output voltage is set with the two buttons at the rim of the board, marked *+* and *-*.

For output voltages below *10V*, the increment and decrement is *0.02V* per key press. For higher voltages, it is *0.1v*.



> Tags: Buck, HW-816, Programmable, Display

[Visit Page on Website](https://done.land/components/power/dc-dc-converters/buck/lm2596/hw-816?499126041911245144) - created 2024-04-11 - last edited 2024-04-11
