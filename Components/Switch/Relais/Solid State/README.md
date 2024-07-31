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



However, there are also important caveats and risks to consider:

### Semiconductor


* **Control Circuit:** A control circuit is connected to a *coil*. When electrical power is applied to the *coil*, it produces a *magnetic field*.
* **Load Circuit:** A (separate) load circuit is placed in close proximity of the coil and uses an *iron* (or elsehow magnetic) latch. The *magnetic field* produced by the *coil* can *move* the latch physically, thus opening or closing the *load circuit*.

### Advantages

The *relais design* is *cheap*, *well-proven for many decades*, and *versatile*:

Depending on construction and materials, a *relais* can be *small*, or it can switch *huge loads*. It can be *normally open* or *normally closed*, or both.

### Disadvantages

In *electronic projects*, a *mechanical relais* is problematic primarily because of this:

* **High Power Consumption:** The current required for the *coil* to produce a magnetic field strong enough to operate the latch is comparably *high*. In *car electric*, it does not matter whether a *relais* requires *100-200mA* of current just to stay in the *on* state. In electronics, this is a huge current that cannot be handled by microcontroller *GPIO*. In addition, a battery-operated device would soon deplete its batteries just by operating the *relais*.
* **Dangerous Voltage Spikes:** When a relais switches from *on* to *off*, the magnetic field produced by the coil *collapses* and induces a momentary spike of *high voltage*. In simple *car electric*, this spike does not harm. It can easily destroy sensitive electronics, though.

> [!TIP]
> When using *electromechanical relais*, *motors*, or anything else with *coils* that can produce *magnetic fields* in *sensitive electronics projects*, always make sure to use a *freewheeling* or *flyback diode*: this is a *regular diode* that is connected *anti-parallel* to safely take care of the energy of the collapsing magnetic field: the diode enables the energy to *circulate* inside the *coil*, thus prolonging the time it takes for the *magnetic field* to collapse and protecting the rest of the circuit from unwanted *energy spikes*. 

## Controlling Relais

### Discrete Solutions
*Relais* can control powerful loads by using tiny *switches* or *buttons*: 

Since the *control circuit* requires only relatively low voltage and current, and since the *load circuit* is separated from the *control circuit*, it is sufficient for a switch to be capable of handling only *low voltage* and *current* of a few hundred milliamperes.

This is how *relais* are used in *cars*: when you turn on the (powerful) *head lights* with a tiny switch on your dashboard, the switch really only operates a *relais*. The *relais* in turn controls the large currents required by the head lamps.

### Microcontrollers and Electronics
In *microcontroller*-based solutions or when using sensitive *ICs*, even a *relais* often requires *too much current* to be operated directly by a *GPIO*.

This is why *transistors* are used to *amplify* the current. Breakout boards with *relais*, *flyback diode* and *amplifying transistor* are readily available for low money.

### Remote Control

*Relais* are often used to *remotely control* devices over the air. In this scenario, the *relais* is combined with a *receiver*:

* **Radio Frequency (RF):** Most cost-effective classic remote control solutions use *license free* radio bands, i.e. *315MHz** (US) or *433MHz* (Europe). When the *RF signal* is picked up by the *receiver*, it turns the *relais* on or off.
* **WiFi:** With the increasing popularity of home *WiFi* networks, a relais can also be controlled by *WiFi* signals. In this case, the relais is connected to a *WiFi*-enabled microcontroller (such as a cheap *ESP8266*). This microcontroller can connect to the *home WiFi*. Instead of using dedicated *senders* or *remote controls*, the control signal comes from a *smartphone app* (and often involves intransparent *cloud solutions* operated by the vendor).  
* **Light:** Less common is the use of *infrared light* (IR) that can also be used to transmit a control signal. Since *light* needs a free *line of sight* between sender and receiver, this only works for limited use cases.

#### WiFi-Controlled Devices
*WiFi* solutions work very similar to *RF* solutions and in fact both use *radio frequencies*. 

Whereas *RF* solutions typically use *315/433MHz*, *WiFi* uses *2.4GHz* and can benefit from the potentially wide coverage of your home *WiFi* network. 

The fundamental difference is *how* control signals are processed: 

* **RF: You Are In Control:** With *RF*, there are distinct *senders* and *receivers* that *directly communicate* and that *you control*. 

* **WiFi: Vendor Is In Control:** With *WiFi* (at least with prefabricated switches and remote control solutions), the digital control signals are beyond your control and often involve proprietary *cloud processing* and non-public encryption keys, controlled alone by the *vendor architecture*. 

#### Security
*WiFi* solutions are convenient and flexible in *normal times*. 

Once *SHTF*, they can quickly become insecure and fragile: should the vendor architecture go offline or fail, so does your remote control architecture. All of your remote switches can be operated by *anyone in control* of the vendor architecture.

> [!TIP]
> As part of your planning, always consider *what* you want to *remote control*, and *how critical* this is for you and your safety: how would it affect you if *someone else* starts remote controlling? Turning on and off the lights in the living room probably has a low risk assessment, especially if you can still use regular switches, too. Opening your garage door or turning on the oven may have much more security implications. 






> Tags: Relais, Remote Control, Security, RF, WiFi, Infrared, IR

[Visit Page on Website](https://done.land/components/switch/relais?115988041230242855) - created 2024-04-29 - last edited 2024-04-29
