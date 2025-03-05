<img src="/assets/images/power.jpg" width="80%" height="80%" />

# XL4005 Buck Converter

> Input 5-32V, Output 0.8-30V, Current 5A, CV, CC

The **XL4005** from *XLSEMI* is a popular step-down converter capable of outputting significant currents of up to *5A*. 

The chip is sold separately and also embedded in a complete breakout, board ready-to-go, for EUR 2-4:

<img src="images/xl4005_example_w.png" width="70%" height="70%" />

> [!CAUTION]
> Although the actual controller **XL4005** is possibly a bit outdated but technically fine, the breakout boards embedding it may be fraudulent.
>
> For example, the depicted breakout board comes with 3 (three) potentiometers (and no documentation). Simple boards have one potentiometer (for *constant voltage*), more advanced boards have two (*constant voltage* and *constant current*), but there is no need for a third potentiometer.
>
> It turns out the third potentiometer controls the threshold for an on-board *LED* that lights *green* for low currents and *red* for high currents - a quite eerie and specific feature.
>
> While such a *LED* might be fun for some and can safely be ignored by others, the board has more serious flaws: the maximum output current is capped at around **1A**, so while the **XL4005** used on the board can handle up to **5A**, the board cannot. If all you require is **1A**, then there are much cheaper and so much smaller converter boards available.
>
> On top, many cheap breakout boards use counterfeit controllers that may still work for you but have significantly different specs. For example, some counterfeit **XL4005** do not run at 300kHz switching frequency but rather 50kHz.
>
> If the core of the inductor on the board is colored *yellow-white* (like the depicted one), then it might be a cheap iron core with a maximum frequency of around 70kHz (real **XL4005** run at 300kHz) that is originally designed to be used in filters, not in *DC-DC converters*.
>
> Takeaway: controller specs and data sheets are for the chip only. The actual board design determines what **you** get out of it. Since typically there are no schematics available for breakout boards, the only way to find out is to test and measure yourself with a dummy load and see if a given board is suiting your needs before you buy in larger quantity.

| Property | Value |
| --- | --- |
| Input Voltage | 5-32V |
| Output Voltage | 0.8-30V |
| Max Output Current | 5A |
| Efficiency | up to 96% |
| Switching Frequency | 300kHz |

> [!TIP]
> The maximum output current of **5A** requires to add a heat sink to the chip. While the **XL4005** is dependable and rugged, avoid exploting its maximum specs. Boards using **XL4005** run well for long-time output currents of **2-3A**.
>
> Stable output current also depends on the voltage difference between input and output. The lower the difference, the less work needs to be done, and the more stable output current and less heat is produced.
>
> As mentioned, some boards cut off current at very low thresholds such as **1A**. In these cases, you definitely need no heat sink but a different board.

| Feature | Supported |
| --- | --- |
| Constant Current | yes |
| Output Shortcut Protection | yes |
| Over Voltage Protection | no |
| Thermal Protection | yes |

[Data Sheet](materials/XL4005_datasheet.pdf)

> Tags: Buck, CC, CV, 32V, 5A

[Visit Page on Website](https://done.land/components/power/powersupplies/dc-dc-converters/buck/xl4005?334106020426240854) - created 2024-02-27 - last edited 2024-02-27
