# XL4015
:stopwatch: Reading time: 4 minutes.

## Quick Overview

The **XL4015** from *XLSEMI* is a very popular step-down converter capable of outputting significant currents of up to *5A*. The chip often is sold as a complete breakout board ready-to-go for around € 1.00:

<img src="images/xl4015_boards.png" width="100%" height="100%" />

> [!WARNING]  
> The way how such boards implement the **XL4015** can differ. Not all boards leverage all features provided by the **XL4015**.
> Some boards come with just *one* potentiometer to setup the *constant voltage* output voltage (i.e. left board in above image).
> At almost the same cost, other boards sport *two* potentiometers and let you *additionally* specify the maximum current (*constant current*). This can be an important feature, i.e. when you plan to use it for battery charging. 

| Property | Value |
| --- | --- |
| Input Voltage | 8-36V |
| Output Voltage | 1.2-32V |
| Max Constant Current Output | 5A |
| Efficiency | up to 96% |
| Switching Frequency | 180kHz fixed |

It comes with the following extra features:

| Feature | Supported |
| --- | --- |
| Constant Current | yes |
| Output Shortcut Protection | yes |
| Thermal Protection | yes |

[Data Sheet](materials/XL4015_datasheet.pdf)


