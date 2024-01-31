# XL4005
:stopwatch: Reading time: 4 minutes.

Input 5-32V, Output 0.8-30V, Current 5A, CV, CC

## Quick Overview

The **XL4005** from *XLSEMI* is a popular step-down converter capable of outputting significant currents of up to *5A*. 

The chip is sold separately and also embedded in a complete breakout, board ready-to-go, for € 2-4:

<img src="images/xl4005_example_w.png" width="70%" height="70%" />

> [!CAUTION]
> Although the actual controller **XL4005** is possibly a bit outdated but technically fine, the breakout boards embedding it may be garbage.
>
> For example, the depicted breakout board comes with 3 (three) potentiometers (and no documentation). Simple boards have one potentiometer (for *constant voltage*), more advanced boards have two (*constant voltage* and *constant current*), but there is no need for a third potentiometer.
>
> It turns out the third potentiometer controls an on-board *LED* that lights *green* for low currents and *red* for high currents. The third potentiometer controls the threshold current and tells the LED when to change color.
>
> While such a *LED* might be fun for some and can safely be ignored by others, the board has more serious flaws: the maximum output current is capped at around **1A**, so while the **XL4005** used on the board can handle up to **5A**, the board cannot. If all you require is **1A**, then there are much cheaper and so much smaller converter boards available.
>
> Takeaway: controller specs and data sheets are for the chip only. The actual board design determines what you get out of it. Since typically there are no schematics available for breakout boards, he only way to find out is to test and measure them yourself with dummy loads before you buy in larger quantity.

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

| Feature | Supported |
| --- | --- |
| Constant Current | yes |
| Output Shortcut Protection | yes |
| Over Voltage Protection | no |
| Thermal Protection | yes |

[Data Sheet](materials/XL4005_datasheet.pdf)


