# LM5116
:stopwatch: Reading time: 4 minutes.

Input 6-100V, Output 1.215-80V (often limited to 32V to protect *condensators* used in breakout board, Current 20A, CV, CC

## Quick Overview

The **LM5116** from *Texas Instruments* is a popular step-down converter capable of outputting significant currents of up to *20A*. 

<img src="images/LM5116_all_w.png" width="90%" height="90%" />

> The board above costs around €4 including heat sinks and is a *heavy-duty* workhorse for hobbyist projects. It supports both *constant voltage* and *constant current*, settable via two clearly marked potentiometers. Turn them *rightwards* to *increase* output voltage and current, respectively.
>
> If you find that the breakout board cuts down at output currents below **20A**, even though you have turned the *constant current* potentiometer all the way to the right, make sure your *input power supply* is capable of providing *enough energy*.
>
> If you for example supply *24V* and want to draw *10A* at *12V*, your power supply must be capable of supplying at least *24V* at *5A*. If it does not, or if you have accidentally set it to some *constant current* cap, the **LM5116** tries to maintain the *constant current* by gradually *decreasing the voltage*.

> [!IMPORTANT]  
> Boards can *differ considerably*: not all boards support all **LM5116** features.
> 
> Some boards come with just *one* potentiometer to setup a *constant voltage* only (i.e. in above image). This is sufficient if you i.e. plan to use the converter to supply a constant voltage to a microprocessor from a 8-36V input range.
> 
> At practically same cost, different boards provide *two* potentiometers, so in addition to a *constant voltage*, you can also set a maximum *constant current*. This can be an important requirement, i.e. when you plan to use it for battery charging or to drive LEDs.
>
> If you plan to stock your electronic lab, I recommend you choose boards with *two* potentiometers for maximum flexibility.

| Property | Value |
| --- | --- |
| Input Voltage | 6-100V |
| Output Voltage | 1.215-80V (may be lower in breakout boards |
| Max Output Current | 20A |
| Efficiency | up to 96% |
| Switching Frequency | 50kHz-1MHz (programmable) |

> [!TIP]
> The maximum output current of **20A** requires to add a heat sink to the chip. While the **LM5116** is dependable and rugged, avoid exploting its maximum specs. Boards using **LM5116** run well for long-time output currents of **10-15A**.
>
> Stable output current also depends on the voltage difference between input and output. The lower the difference, the less work needs to be done, and the more stable output current and less heat is produced.

| Feature | Supported |
| --- | --- |
| Constant Current | yes |
| Output Shortcut Protection | yes |
| Over Voltage Protection | yes |
| Thermal Protection | yes |
| Softstart | yes, programmable |

[Data Sheet](materials/LM5116_datasheet.pdf)


