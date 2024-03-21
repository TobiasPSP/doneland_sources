<img src="/assets/images/power.jpg" width="80%" height="80%" />

# LM5116 Buck Converter

> Input 6-100V, Output 1.215-80V, Often Limited to 32V to Protect Condensators, Current 20A, CV, CC


The **LM5116** from *Texas Instruments* is a popular step-down converter capable of outputting significant currents of up to *20A*. 

<img src="images/LM5116_all_w.png" width="90%" height="90%" />

> The board above costs around EUR 4 including heat sinks and is a *heavy-duty* workhorse for hobbyist projects. It supports both *constant voltage* and *constant current*, settable via two clearly marked potentiometers. Turn them *rightwards* to *increase* their setting, and *leftwards* to *decrease*. 
>
> :warning: The board comes with a tiny switch at the *input* terminal. Make sure this switch is in *ON* position or else there will be no output voltage.
>
> To adjust the voltage, connect a voltmeter to the output terminal, then turn the potentiometer marked **CV** (turn *right* to *raise* and *left* to *lower*).
>
> To adjust the *constant current* requires a load to be connected to the output terminal (preferrably a dedicated electronic load device where you can vary the load, but any load will do).
>
> You can now measure the current that flows at the output terminal with a **DC** clamp ampere meter (do *not* use a simple multimeter. It typically support high currents only for a few seconds before it starts to smoke).
>
> A red *LED* close to the *input terminal* tells you if your output is *above* the *constant current*: if the LED is *dim* or *off*, then the **Buck** converter has actively lowered or shutdown the current (by lowering the voltage, and if that still did not suffice, by turning the output *off*).
>
> You can then turn the **CC* potentiometer rightwards to *increase* the *constant voltage* until the red *LED* starts to *fully* glow again (if you wanted to allow higher currents at the output).
>
> If you find that the breakout board provides much less current than **20A** before it starts to drop the voltage and shutdown, regardless of what you do, make sure your *input power supply* is capable of providing *enough energy* in the first place. The **Buck** can't generate current out of nothing.
>
> For example, if you supply *24V* and want to draw *10A* at *12V*, your power supply must be capable of supplying at least *24V* at *5A*. If it does not, or if you have accidentally set it to some *constant current* cap, the **LM5116** tries to maintain the set *constant current* by gradually *decreasing the voltage*.

| Property | Value |
| --- | --- |
| Input Voltage | 6-100V |
| Output Voltage | 1.215-80V (may be lower in breakout boards |
| Max Output Current | 20A |
| Efficiency | up to 96% |
| Switching Frequency | 50kHz-1MHz (programmable) |

> [!TIP]
> The maximum output current of **20A** requires heat sinks. Fortunately, many breakout boards come with them premounted. That said, you should test and experiment for yourself to see at which parameters the **LM5116** gets too hot.
>
> This depends on how much "work" it needs to do, so it is related to the actual *input* and *output* voltages you have set, and the voltage difference between them. So you might get away with a fairly cool **LM5116** at high currents for hours, while other setups may experience excess heat even after a few minutes.
>
> One cause of excessive heat is when you *do not supply enough input power*: if the power source cannot provide enough current to drive the output terminal, the **LM5116** works very hard to try and provide the set *constant current* nevertheless (i.e. by lowering the voltage). This is inefficient and makes no sense. You should always use the *constant current* setting to limit the output current to a safe level that does not cause excessive *input currents* that your *input power supply* cannot handle.

| Feature | Supported |
| --- | --- |
| Constant Current | yes |
| Output Shortcut Protection | yes |
| Over Voltage Protection | yes |
| Thermal Protection | yes |
| Softstart | yes, programmable |

[Data Sheet](materials/LM5116_datasheet.pdf)

> Tags: Buck, CC, CV, 20A, 36V

:eye:&nbsp;[Visit Page on Website](https://done.land/components/power/dc-dc-converters/buck/lm5116?325130020426240854) - last edited 2024-02-27
