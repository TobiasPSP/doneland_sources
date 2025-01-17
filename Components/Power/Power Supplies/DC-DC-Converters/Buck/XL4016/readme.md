<img src="/assets/images/power.jpg" width="80%" height="80%" />

# XL4016 Buck Converter

> Input 5-40V, Output 1.2-36V, Current 8A, CV, CC


The **XL4016** from *XLSEMI* is a popular step-down converter capable of outputting significant currents of up to *8A*. 

The chip is sold separately and also embedded in a complete breakout, board ready-to-go, for EUR 6-10:

<img src="images/XL4016_cv_w.png" width="70%" height="70%" />

> [!IMPORTANT]  
> Boards can *differ considerably*: not all boards support all **XL4016** features.
> 
> Some boards come with just *one* potentiometer to setup a *constant voltage* only (i.e. in above image). This is sufficient if you i.e. plan to use the converter to supply a constant voltage to a microprocessor from a 8-36V input range.
> 
> At practically same cost, different boards provide *two* potentiometers, so in addition to a *constant voltage*, you can also set a maximum *constant current*. This can be an important requirement, i.e. when you plan to use it for battery charging or to drive LEDs.
>
> If you plan to stock your electronic lab, I recommend you choose boards with *two* potentiometers for maximum flexibility.

| Property | Value |
| --- | --- |
| Input Voltage | 5-40V |
| Output Voltage | 1.2-36V |
| Max Output Current | 8A |
| Efficiency | up to 96% |
| Switching Frequency | 180kHz |

> [!TIP]
> The maximum output current of **8A** requires to add a heat sink to the chip. While the **XL4016** is dependable and rugged, avoid exploting its maximum specs. Boards using **XL4016** run well for long-time output currents of **5A**.
>
> Stable output current also depends on the voltage difference between input and output. The lower the difference, the less work needs to be done, and the more stable output current and less heat is produced.

| Feature | Supported |
| --- | --- |
| Constant Current | yes |
| Output Shortcut Protection | yes |
| Over Voltage Protection | yes |
| Thermal Protection | yes |

[Data Sheet](materials/XL4016_datasheet.pdf)

> Tags: Buck, CC, CV, 8A, 40V

[Visit Page on Website](https://done.land/components/power/powersupplies/dc-dc-converters/buck/xl4016?368014020426240854) - created 2024-02-27 - last edited 2024-02-27
