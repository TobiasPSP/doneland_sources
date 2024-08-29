<img src="/assets/images/relais.png" width="80%" height="80%" />
 
# Relais

> Electro-Mechanical Switch Using A Magnetic Field To Separate Circuits

A *relais* is the ubiquous *low cost* solution to switching *large currents* or *high voltages*, and separating the *control circuit* from the *load circuit*.

## Basic Principle

All *electromechanical relais* work the same:

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

[Visit Page on Website](https://done.land/components/signalprocessing/switch/relais?115988041230242855) - created 2024-04-29 - last edited 2024-04-29
