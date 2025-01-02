<img src="/assets/images/powerbank2.png" width="100%" height="100%" />

# Powerbank Modules

> One-Stop-Solutions To Turn Batteries Into Powerbanks

*Powerbank modules* are ready-to-use modules that come with everything required to turn *batteries* into *powerbanks*.

## Overview

*Powerbank modules* are breakout boards equipped with all components required by a *powerbank*. You just need to connect an appropriate *battery pack* and add a proper housing.

Such modules typically come with these features:

* **Output Connectors:** presoldered connectors for most or all common *USB* socket types. Some boards include *Apple Lightning* connectors.
* **Charger:** circuitry to safely *charge* the attached *battery*. 
* **BMS:** protection circuitry to protect the attached *battery* from *over-charge*, *over-discharge*, and *short-circuits*. When protection was triggered, it is typically resettable by reconnecting the board to a charging current.
* **Visuals:** some sort of indicator to show *state of charge*
* **Button:** a button to wake up the electronics in order to draw power from the *power bank*
* **Temperature Probe:** good boards come with a temperature probe to stop operations on high temperatures. High temperatures can indicate a problem but can also occur environmentally: when the *powerbank* is exposed to direct *sunshine*, it can quickly heat up. Charging *lithium batteries* over 60 degree centigrade is dangerous and can lead to *fire* or *explosion*.
* **Power Delivery:** advanced boards come with *power delivery ICs* and support various *quick charge* standards. Simple boards only support the *classic 5V USB charge*.

## Use Appropriate Batteries

Since *powerbank modules* already come with almost all required components, you often just need to add a suitable battery. Connecting a *wrong* battery can break havok and cause great damage, though.

*Powerbank modules* are designed for a *particular battery type*. Make sure the battery matches the board. This is *extremely important* because the *charger* built into these boards must match the *battery requirements*. 

### Battery Chemistry

Most modules require *LiIon* or *LiPo* batteries. Never connect such a board to a *LiFePo4* battery, or else the battery will be *overcharged* and may be damaged or can catch fire. *LiIon* and *LiPo* batteries require different *charging voltages* and *discharging voltage converters* than *LiFePo4*.

### Battery Voltage

Make sure the *powerbank module* is designed to work with the *battery pack* you want to use. 

*Small* powerbanks and *solar power banks* use single batteries (*1S*). Larger and more powerful powerbanks often connect many batteries *in series* (*2S*, *3S*, *4S*, *5S*, *6S*, etc.). 

The *powerbank module* **must match** the number of batteries you connected *in series*. A *1S powerbank module* can only be used with *single* batteries (or a bunch of single batteries connected *in parallel*). Likewise, a *3S powerbank module* always *requires exactly three* batteries connected *in series*.

The reason for this is similar to *battery chemistry*: when you connect *batteries in series*, this *changes the charging and discharging voltage*. 

### Building Battery Packs

Building *powerbanks* that use a *single* battery is the safest design and perfect as a start. All you need to care about is *match* the battery chemistry to the *powerbank module*.

*Single battery powerbanks* are typically not very powerful, though, which is why many users construct larger and more powerful *battery packs*. By connecting batteries *in series*, you can raise the *voltage*, and by connecting batteries *in parallel*, you can raise the *current*.

Constructing *battery packs* from more than one battery can be dangerous when done wrongly. Here are the most common mistakes:

* **Unbalanced batteries:** always use batteries of same type, same age, same vendor, and *same state of charge*. Their chemistry must behave similarly, and they must be charged to the same level before combining them. Even small imbalances can cause severe issues.
* **Insufficient Electrical Connections:** Powerbanks can draw enormous *currents*. When you *power* a *notebook* from a powerbank (provided the powerbank electronics support the required power delivery protocol and voltage), it may easily draw *65W*. At *20V*, that is a *3.5A* current. At the *battery level*, the same *65W* are drawn from *3.7V* batteries, resulting in a *17.5A current*. If you connected the batteries inside your *battery pack* with *simple DIY wires*, then these will probably soon go up in smoke.







> Tags: Powerbank, Battery, BMS, Charger

[Visit Page on Website](https://done.land/components/power/powerbank/modules?362038051703244602) - created 2024-05-02 - last edited 2024-05-02
