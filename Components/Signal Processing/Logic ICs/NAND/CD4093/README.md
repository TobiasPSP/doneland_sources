<img src="/assets/images/components.png" width="80%" height="80%" />
 
# CD4093

> CMOS Quad 2-Input NAND Schmitt Triggers

This 14-pin DIP chip contains four separate *NAND gates* that operate according to this truth table:

| Input A | Input B | Output |
|---|---|----------|
| 0 | 0 |    1     |
| 0 | 1 |    1     |
| 1 | 0 |    1     |
| 1 | 1 |    0     |

In a nutshell, when *both* inputs are *high*, then the result is *low*, else *high* - the exact opposite of an *AND gate*. *NAND gates* can be used for a variety of use cases, including *inverting logic signals*, or *debouncing mechanical push buttons*.

In contrast to simpler *NAND gates* like the *CD4011*, the *CD4093* contains *Schmitt Triggers* for handling noisy input signals: if the input signal is not clearly a *high* or *low* voltage but rather inbetween, the hysteresis of the *Schmitt Trigger* prevents unwanted oscillations and keeps the signal stable.

While the added *Schmitt Triggers* are typically no benefit in digital circuits, they don't hurt either.


## Materials

[Data Sheet](materials/cd4093b_datasheet.pdf)

> Tags: Schmitt-Trigger

[Visit Page on Website](https://done.land/components/signalprocessing/logicics/nand/cd4093?568718081329241200) - created 2024-08-28 - last edited 2024-08-28
