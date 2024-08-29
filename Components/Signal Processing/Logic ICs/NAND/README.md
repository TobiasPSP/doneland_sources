<img src="/assets/images/components.png" width="80%" height="80%" />
 
# NAND Gates

> NAND Gates Are Negated AND Gates: Both Inputs Must be Identical For The Output To Switch State

*NAND gates* have two inputs. To better understand what they do, first look at the underlying *AND gate*: when *both* inputs are *high*, then the result is *high*, else *low*. Here is the truth table for an *AND gate*: 


| A | B | A AND B |
|---|---|---------|
| 0 | 0 |    0    |
| 0 | 1 |    0    |
| 1 | 0 |    0    |
| 1 | 1 |    1    |

A *NAND* gate is an *AND gate* with an added *NOT*, inverting the result. So whenever an *AND gate* would be *true*, the *NAND gate* is *false* - and vice versa.

Here is the truth table for a *NAND gate*:

| A | B | A NAND B |
|---|---|----------|
| 0 | 0 |    1     |
| 0 | 1 |    1     |
| 1 | 0 |    1     |
| 1 | 1 |    0     |

When *both* inputs are *high*, then the result is *low*, else *high* - the exact opposite of an *AND gate*.

## Use Cases

A *NAND gate* is *flexible* and can be used for many different operations, depending on how you wire it.

For example, a *NAND gate* can *invert* a signal (flipping the state of a *GPIO* around) simply by connecting the signal to *both inputs* of the gate.

## Key Aspects When Selecting NAND Gates
There are many different *NAND chips* available that differ in just a few aspects:

| Property | Note |
| --- | --- |
| Voltage  | make sure the component supports the voltage you need. Some components require a minimum voltage of *5V* and cannot be used with *3.3V* circuitry |
| Current | If you want to directly drive electronic components off the component, i.e. a *LED*, make sure it can *sink* and/or *source* the required current. Typically, components can sink and source small currents of up to *10mA*. Anything beyond requires additional transistors |
| Number of Gates | Most chips come with a number of *NAND gates*. The popular *CD4011* for example comes with four *NAND gates* |
| Trigger | Simple *NAND gates* require clean logic levels to work properly which is not an issue in digital circuits. When input signals are not clean, may contain noise or may not always have clear and distinct *high* and *low* voltages, then built-in *Schmitt Triggers* (like in the *CD4093*) help: they use hysteresis and make sure than indistinct intermediate voltages may cause oscillations |




> Tags: NAND, Schmitt Trigger

[Visit Page on Website](https://done.land/components/signalprocessing/logicics/nand?415475081329241200) - created 2024-08-28 - last edited 2024-08-28
