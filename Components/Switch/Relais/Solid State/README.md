<img src="/assets/images/relais.png" width="80%" height="80%" />
 
# Solid State

> Semiconductor Relais Without Moving Parts

A *solid state relay* (*SSR*) is an electronic switch that uses semiconductor components to switch on or off when an external voltage is applied. Unlike traditional electromechanical relays, SSRs have no moving parts, resulting in faster switching times, greater reliability, and longer operational life. They are commonly used in applications where silent operation, low power consumption, and high durability are required.

## Basic Principle

*SSR* de-couple the control circuit with an *optocoupler*: the trigger signal activates an internal LED. Its light in turn activates a photodiode in the load circuit which then uses a semiconductor to switch the load.

So while classic electromagnetic relais use a magnetic field to de-couple trigger and load circuits, the same is achieved in *SSR* by using light.

### DA, DD, AD, AA
Depending on how a *SSR* is designed, it can switch *AC* or *DC*, and the trigger signal can also be either *AC* or *DC*. *SSRs* are marked with two letters to indicate their design:

| Marking | Description |
| --- | --- |
| DA | a digital control signal (i.e. *GPIO*) controls an *AC* load |
| DD | a digital control signal (i.e. *GPIO*) controls a *DC* load (i.e. a motor or high-power LED) |
| AA | an *AC* signal controls an *AC* load |
| AD | an *AC* signal controls a *DC* load |

### Semiconductors
*SSR* use *solid-state components* to perform the actual switching. Since there are no moving parts involved, *SSRs* do not wear out easily, and they are completely silent.

The type of semiconductor depends on whether the *SSR* is designed to switch *AC* or *DC*:

* **MOSFET:** like anywhere else in electronics, *SSR* use traditional *MOSFET* to switch *DC* loads
* *Triac, Thyristor:** *Triacs* are most commonly used in *SSR* for switching *AC loads* as they can conduct in both direction which makes them ideal for *AC*. *Thyristors* are sometimes also used (in pairs back-to-back, since they only conduct in one direction).

## Advantages...
There are solid advantages of *SSR* over classic mechanical relais:

* **Low Power Consumption:** while a mechanical relais must maintain a magnetic field for the entire time it is switched on (which can take considerable *current*), *SSRs* are controlled electronically and typically only require a few *mA* that can be directly taken from a *GPIO*.
* **Silent:** *SSRs* operate completely noise-free. There is no *clack* sound from a switching mechanical relais.
* **No Sparks:** since there are no moving contacts, there are also no *sparks* (that can happen with mechanical relais when they switch high loads). In addition, *SSR* relais often use *Zero-Crossing Detection* to switch *AC loads* when the AC waveform crosses 0V. This minimizes *EMR* and physical stress since the load is zero at the time where the switch takes place.
* **Less EMR:** *Zero-Crossing Detection* immediately leads to an important problem with mechanical relais: *EMR* and *radio interference* (which is directly related to *sparks*). *SSRs* do not produce this kind of interference.
* **No Flyback Diode:** since classic relais rely on *magnetic fields*, a *flyback diode* is needed to protect sensitive electronics from being hit by high momentary voltages that can occur when the magnetic field of a classic relais breaks down. *SSRs* do not use magnetic fields and thus do not need a *flyback diode* or otherwise can produce harmful voltage spikes to the trigger circuit.
* **Wear-Out:** like any *physical device* with moving parts, mechanical relais wear out over time. The *sparks* can corrode the switching contacts, and the relais may eventually fail to reliably switch.

## ...and Caveats
Despite the many advantages, *SSRs* have their own lost of important caveats and risks that need to be carefully considered:

* **Fire Hazard:** When the solid state component that performs the switching gets overloaded, it may burst into flames and start a house fire. This risk is completely manageable by sticking to the *SSR specs*: never switch loads that are higher than 50% of the maximum *SSR rating*.

> [!CAUTION]
> *SSRs* from renown manufacturers are considerably more expensive than mechanical relais. However, cheap generic *SSRs* (or fake *clones*) are available for a fraction of that price. Typically, suspiciously cheap *SSR* internally use semiconductors that are much less capable than the claimed ratings. A *40A SSR* from cheap sources i.e. uses semiconductors that can handle just *12A*. *Cheap SSR* are widely used and do a good job, provided you add your own safety margin and do not exceed *30%* of their specs.

* **Heat Sink:** The resistance in mechanical switches is almost zero, however the solid state components inside a *SSR* can introduce a slightly higher resistance and/or produce a slight voltage drop, all of which is turned into heat. This is why *SSR* typically require a *heat sink* and can produce considerable heat when used with high loads. Switching typical small applicance in the range of 400W or less causes much less often a heat dissipation problem, however when you switch a water heater or powerful motors, lack of a proper *heat sink* can destroy the *SSR* or even cause a fire.


> Tags: Relais, SSR, Solid State Relais, MosFET, Thyristor, Triac, Fire Hazard, Heat Sink
