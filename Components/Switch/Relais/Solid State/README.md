<img src="/assets/images/relais.png" width="80%" height="80%" />
 
# Solid State Relais

> Semiconductor Relais Without Moving Parts

A *solid state relay* (*SSR*) is an electronic switch that uses semiconductor components to switch on or off when an external voltage is applied. Unlike traditional electromechanical relays, SSRs have no moving parts, resulting in faster switching times, greater reliability, and longer operational life. They are commonly used in applications where silent operation, low power consumption, and high durability are required.

## Basic Principle

A classic *electromagnetic* relais use a *magnetic field* to electrically separate the trigger circuit from the load circuit. The same electrical isolation is achieved in *SSR* by using light:

In a *SSR*, the trigger circuit operates an *optocoupler*: it turns on an internal LED. The light that is emitted by this LED is picked up by a photodiode, providing the *electrical isolation* of both circuits.

The *photodiode* in turn uses a semiconductor to switch the load.


### DA, DD, AD, AA
Depending on how a *SSR* is designed, it can switch *AC* or *DC*, and the trigger signal can be either *AC* or *DC*. *SSRs* are marked with two letters to indicate their design:

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
* **Triac, Thyristor:** *Triacs* are most commonly used in *SSR* for switching *AC loads* as they can conduct *in both directions* which makes them ideal for *AC*. *Thyristors* are sometimes also used (in pairs back-to-back, since they only conduct in *one direction*).

## Advantages...
There are important advantages of *SSR* over classic *mechanical* relais:

* **Low Power Consumption:** a mechanical relais must maintain a magnetic field for the entire period of time it is switched *on* (which can require considerable power: mechanical relais typically can not be directly driven by a *GPIO*). *SSRs* are controlled *electronically* and only require a few *mA* that can be directly supplied by a *GPIO*.
* **Silent:** *SSRs* operate completely noise-free. There is no *clack* sound that is typically emitted by a switching mechanical relais.
* **No Sparks:** since there are no moving contacts, there are also no *sparks* (that can happen with mechanical relais when they switch high loads). In addition, *SSR* relais often use *Zero-Crossing Detection* to switch *AC loads* when the AC waveform crosses 0V. This further minimizes *EMR* and physical stress since the load is zero at the time where the switch takes place.
* **Less EMR:** *Zero-Crossing Detection* mechanical relais can create significant electrical *interference*: *EMR* and *radio noise*. Such *electro-magnetic* interference is caused by *sparks* and also the coils used in mechanical relais. *SSRs* do not produce this kind of interference.
* **No Flyback Diode:** since classic relais rely on *magnetic fields*, a *flyback diode* is needed to protect sensitive electronic parts from being hit by high momentary voltage spikes that can occur when the magnetic field of a classic relais collapses and releases its stored energy. *SSRs* do not use magnetic fields and thus do not need a *flyback diode* or can otherwise produce harmful voltage spikes that harm the trigger circuit.
* **Wear-Out:** like any *physical device* that uses moving parts, mechanical relais wear out over time. The *sparks* can corrode the switching contacts, and the relais may eventually fail to reliably switch.

## ...and Caveats
Despite the many advantages, *SSRs* have their own important caveats and risks that need to be carefully considered:



* **Heat Sink:** The resistance in mechanical switches is almost zero. *Solid state components* inside a *SSR* can introduce a *slightly higher resistance* and/or produce a slight *voltage drop*, all of which is turned into heat that must be *dissipated* or else *accumulates*. Switching small applicances in the range of *<400W* typically do not produce relevant heat that requires *heat sinks* or *active cooling*. When you switch more powerful appliances, i.e. a water heater or powerful motors, the *heat dissipation* of *SSRs* must always be taken into consideration: use a proper heat sink, and make sure the housing allows the dissipated heat to vent off. Lack of proper heat dissipation may lead to the destruction of the *SSR* and can eventually cause fires.

* **Fire Hazard:** Generally, *SSRs* do have an inherent risk of causing *house fires* when used improperly. Lacking *heat dissipation* (see above) is just one cause. Another avoidable fire hazard is *overloading SSRs*. Always keep in mind that *SSRs* use *solid state switches* that can explode or catch fire when loads are switched that exceed their specifications. As a rule of thumb, with *quality SSRs* from *known sources*, never switch loads that are higher than **80%** of the maximum *SSR rating*. With *cheap SSRs* from *unknown sources*, never switch loads that are higher than **30%** of the maximum *SSR rating* 

> [!CAUTION]
> *SSRs* from renown manufacturers are considerably more expensive than mechanical relais. Cheap generic *SSRs* (or fake *clones*) are available for a fraction of that price. These cheap **SSRs** regularly use inferior semiconductors, and the ratings printed on these *SSRs* are **not trustworthy**. Often, a *SSR* rated for *40A* contains semiconductors rated for *12A*. Likewise, a *SSR* rated for *10A* can only switch loads up to *3A*. Many people around the world successfully use cheap *SSRs*, however they add generous safety margins. Either do not exceed **30%** of *SSR ratings* with these cheap clones, or *disassemble one of them* and *check out the semiconductor used inside*. Never ever trust the printed ratings. 



> Tags: Relais, SSR, Solid State Relais, MosFET, Thyristor, Triac, Fire Hazard, Heat Sink

[Visit Page on Website](https://done.land/components/switch/relais/solidstate?888119072031245401) - created 2024-07-30 - last edited 2024-07-30
