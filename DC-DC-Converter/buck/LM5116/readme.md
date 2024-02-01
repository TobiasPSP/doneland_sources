# LM5116
:stopwatch: Reading time: 4 minutes.

Input 6-100V, Output 1.215-80V (often limited to 32V to protect *condensators* used in breakout board, Current 20A, CV, CC

## Quick Overview

The **LM5116** from *Texas Instruments* is a popular step-down converter capable of outputting significant currents of up to *20A*. 

<img src="images/LM5116_all_w.png" width="90%" height="90%" />

> The board above costs around €4 including heat sinks and is a *heavy-duty* workhorse for hobbyist projects. It supports both *constant voltage* and *constant current*, settable via two clearly marked potentiometers. Turn them *rightwards* to *increase* their setting, and *leftwards* to *decrease*. 
>
> :warning: The board comes with a tiny switch at the *input* terminal. Make sure this switch is in *ON* position or else there will be no output voltage.
>
> To adjust the voltage, connect a voltmeter to the output terminal, then turn the potentiometer marked **CV** (turn *right* to *raise* and *left* to *lower*).
>
> To adjust the *constant current* requires a load to be connected to the output terminal (preferrably a dedicated electronic load device where you can vary the load, but any load will do).
>
> You can now measure the current that flows at the output terminal with a **DC** clamp ampere meter (do *not* use simple multimeters for the currents at play here. They typically support high currents only for a few seconds).
>
> A red *LED* close to the *input terminal* tells you if your output is *above* the *constant current*: if the LED is *dim* or *off*, then the **Buck** converter actively lowers the current (by lowering the voltage). You would have to turn the **CC* potentiometer rightwards to *increase* the *constant voltage* until the red *LED* is *fully on* again if you wanted to allow such current.
>
> If you find that the breakout board provides much less current than **20A** before it starts to drop the voltage, regardless of what you do, make sure your *input power supply* is capable of providing *enough energy* in the first place. The **Buck** can't generate current out of nothing.
>
> For example, if you supply *24V* and want to draw *10A* at *12V*, your power supply must be capable of supplying at least *24V* at *5A*. If it does not, or if you have accidentally set it to some *constant current* cap, the **LM5116** tries to maintain the *constant current* by gradually *decreasing the voltage*.

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


