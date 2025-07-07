<img src="/assets/images/charging.png" width="100%" height="100%" />

# CKCS PB0A

> I2C-Enabled Programmable 1S LiIon Charger and Discharger

The *PB0A* module is one of the most affordable **programmable** charger/discharger for single-cell (1S) LiIon batteries. It supports *I2C*.

<img src="images/pb0a_data_t.png" width="50%" height="50%" />

The module comes with a *DATA* through-hole pin and a separate solder pad on the front side that provide access to its internal *I2C* programming interface.

## Overview
The *PB0A* breakout board is the sophisticated version of the basic [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/). Both boards are based on the power management chip [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/). This chip comes in two different versions: 

* **No I2C (non-programmable):**    
  Basic versions (like the chip used on [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/)) are **pre-programmed** and have no built-in *I2C* interface. 
* **I2C (programmable):**    
  *PB0A* (which is discussed here) comes with a sophisticated version of [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) which includes a [I2C Interface](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/#i2c-configuration).




| Feature | [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/) | **PB0A** |
| --- | --- | --- |
| I2C Interface | no | yes |
| LEDs | 4 (monochrome) | 1 (RGB) |
| Charging Current | 2.4A | 2.4A (default),<br/>0.05-3.2A (configurable) |
| Auto-Shutoff | *<50mA* for *>32s* | *<50mA* for *>32s* (default)<br/>8s/16s/32s/no Auto-Shutoff (configurable) |





> [!IMPORTANT]
> You may want to make yourself familiar with [this comprehensive IP5306 guide](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) before reading on. The article you are currently reading focuses exclusively on the specific details and nuances* of the PB0A breakout board. 


### Why Using I2C?
If you are happy with the default specs of [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/), and/or if your project is not using a microcontroller, then you are well off using one of the simpler breakout boards like [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/) or [MH-CD42](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/mh-cd42/). These are much easier to use and a bit cheaper. In fact, the **PB0A** behaves **exactly like those** by default. 

Once you start working with [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/)-based charger/dischargers, though, you may run into some common issues:

* **Too much charging current:**    
  By default, the [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) typically delivers a maximum charging current of **2.4A**. If your project is using *small* batteries, especially affordable *LiPo* pouches with capacities of *400-3000mA*, then this charging current is **way too high** and may damage the battery or cause a fire hazard. The typical safe charging current for those batteries is **0.3C** (*100-900mA*).
* **Auto-Shutdown:**     
  [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) was created for use in power banks. By default, it has a built-in auto-shutdown that kicks in when the output current drops below *50mA* for more than *32s*. If your project is low-power, or if you want to power microcontrollers that occasionally go into *deep sleep*, then the default [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) may unexpectedly cut power.

Rather than having to work around those issues, or taking the risk, with **programmable [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/#i2c-configuration)**, you can *re-configure* the chip to match your needs: 

* raise or lower the maximum charging current
* turn on or off the automatic shutdown feature

For this, you need a microcontroller that can talk to the *I2C* interface.



### Caveats

Before you dive into working with *PB0A* and its *I2C* interface, here are a few things you should know:


#### Unmarked Chips
Often, **PB0A** breakout boards use unmarked chips. It is not clear whether these chips are original [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) or clones, and whether the chips indeed have an enabled *I2C* interface:

<img src="images/pb0a_data_chip_unmarked2_t.png" width="50%" height="50%" />

All boards I aquired from different sources at *AliExpress* worked flawlessly.

#### Confusing Labels
The battery output pins are marked with a battery symbol, lacking distinct `BAT+` and `BAT-` labels. The small "pin" on the battery symbol marks the positive (`BAT+`) pin.

Likewise, a number of additional pins and solder pads are unmarked, and one pin is labeled `DATA`. These pins resemble the access to the *I2C* interface (see [below](#missing-i2c-documentation) for clear pin labels).


#### I2C vs Default Configuration

Some sellers claim that the **PB0A** board delivers **3.2A** charging current (in contrast to just **2.4A** for "normal" boards). This is not entirely true, though: while the board **can** deliver up to **3.2A** charging current, in its base configuration its configuration is **identical** to [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/) and [MH-CD42](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/mh-cd42/):

* **Charging:** *2.4A* max.
* **Discharging:** *10W* (max *2.1A* at *5V*)

To unlock any special **PB0A** features (like increased or decreased charging currents), you need to use its *I2C* interface, and you need to do this *every time the **PB0A** board wakes up* (it has no memory and therefore cannot remember any configuration changes). 

These are some valuable conclusions:

* If your project does not use a microcontroller that can talk to *I2C*, choose the more affordable [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/) or [MH-CD42](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/mh-cd42/). Without *I2C* configuration, they behave **exactly** like the **PB0A**.
* If your project does use a microcontroller that can talk to *I2C*, then **PB0A** is an **excellent choice** for portable power solutions, and you can adjust the maximum charging current exactly to the needs of your battery, plus you can make sure the power isn't cut off just because your microcontroller may have entered *deep sleep*. 


## Understanding Power Output Paths
All [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/)-based boards - including **PB0A** - use **different connectors** for input and output. The *USB-C* connector does not work bi-directional and can **only be used for charging**. It does not supply power.

This is not really a problem as long as you are aware of this: **PB0A** supplies *5V* at *10W*/*2.1A* output at its `5V+` and `5V-` solder pads and to the (optional) *USB-A* connector (solder pads on the backside of the module).

### Power While Charging

With this module, you can supply *5V* power to an external device while operating from a *single cell LiIon battery*, and also while *charging* the battery through its built-in *USB-C* connector. 

However, when you **unplug** the charging cable, there may be a short power interruption that can cause microcontrollers to reboot (unless you use large-enough capacitors to smooth this short interruption). Here is why:

* **Battery Operation:**    
  uses its boost converter to *boost* the battery voltage to *5V*
* **Charging:**   
  turns off its boost converter, and supplies *5V USB-C input* **both** to the charger **and** to the connected external device.

When you stop charging (unplugging the USB-C cable), the module needs to turn on its boost converter before it can continue to supply *5V*. This takes a few milliseconds which is the power gap you are experiencing.

<img src="images/pb0a_back_angle_t.png" width="40%" height="40%" />

Note also that this power path design can draw up to **5A** during charging:

* **Charging:**     
  supplying up to *3.2A at 4.2V* (14W) to charge the battery
* **Device:**     
  supplying up to *2.1A at 5V* (10.5W) to the power output
* **Total:**    
  combined output power is *25W*.     
  The *USB-C power supply* must be capable of delivering up to *25W*/*5A* at *5V* for maximum performance.


### Push Button

An optional push button can be connected to the `K` and `GND` solder pads with a *10kΩ* resistor in series. The push button is used to power an external device *on* or *off*. 


<img src="images/pb0a_top_t.png" width="60%" height="60%" />

This is the default behavior:

- **Short press (>30ms but <2s):** Turns on indicator LEDs and enables power output.
- **Double short press:** Turns off indicator LEDs and disables power output.

The button behavior can be adjusted via *I2C*. For example, you can control whether the push button should power the device *on*, *off*, or *on* and *off*, and what kind of button presses should be used.


## Charging Mode

The built-in charger activates automatically once a power supply is connected to the built-in *USB-C* port, charging the battery at up to *2.4A* (by default) or *0.05-3.2A* (when configured via *I2C*). 


## Supplying Power

The module provides *5V output* automatically **on demand**, similar to a power bank:

* **Auto Power On:**    
  When you connect a load to either the *USB-A* connector (may not be soldered, see solder pads on backside), or the `5V+` and `5V-` pins, the module automatically enables its internal boost converter and supplies up to *10W* at *5V*.
* **Auto Power Off:**    
  Once the load draws less than *50mA* over a *32s* period, the module automatically cuts power, turns off its boost converter, and goes into standby mode.


### Disabling Auto Power Off
This behavior can be re-configured using *I2C*. For microcontroller projects that are permanently connected to this module, a distinct power *on* and *off* often makes more sense:

* **Manual Power On and Off:**    
The feature **Auto Power On When Load Connected** can be disabled by *I2C* (Register `0x00`, set bit `2` to `0`). Now, power must be enabled manually via a push button connected to pin `K`. 

  The module now no longer automatically cuts power, even if the current drops below *50mA*.

  Instead, to power off the module, the push button connected to `K` needs to be manually double-pressed.

* **Continuous Operation For Microcontrollers:**    
  Powering a microcontroller project works similarly:

  1. **Initial default behavior:**     
  By default, the board powers on automatically once a load is detected, so it powers on once your microcontroller is connected.
  2. **Turn off "Auto Power On When Load Connected":**    
    The microcontroller can then turn off "Auto Power On When Load Connected" via *I2C*, making sure the power supply continues to supply power even if power consumption drops below *50mA*.

      Now the microcontroller can safely enter *deep sleep* without risking to lose power.
    3. **Permanently Turning Off:**    
      If the microcontroller wants to *permanently* turn off battery power (permanently turn off the device), it could re-enable "Auto Power On When Load Connected" via *I2C* and then enter *deep sleep*. Now, the board detects the *<50mA* current and turns off battery power altogether. Your microcontroller is now permanently turned off, and no battery power is drawn anymore, until a user manually turns on the device again by pressing the push button on pin `K`.

<img src="images/pb0a_back_t.png" width="40%" height="40%" />


## Missing I2C documentation

Should you be eager to try *I2C* and use it to program **PB0A** now, there is one issue: lack of documentation. 

Even though sellers frequently mention a mysterious **PB0A Configuration Tool Instructions.doc** document to provide details on *I2C support*, such a "Configuration Tool" does not exist, nor can the mentioned document be found anywhere.

<img src="images/configtool_pb0a.png" width="100%" height="100%" />

You don't need either one. These are the facts:

* **No Configuration Tool:**     
  There *is no* specific "configuration tool" because such a tool would not make any sense anyway: [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/#i2c-configuration) *has no built-in memory*, and thus **it cannot be permanently re-programmed** by any external configuration tool. 
  
  Instead, it needs to be configured at each power-on by a microcontroller that is part of your project.
* **Standard I2C Interface:**    
  The board exposes a standard *I2C* interface on pins `DATA` (`SDA`) and `SCL`. The I2C device address is `0x75`.

  Whenever the [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) starts to supply power, it also powers on your microcontroller. All you need to do is make sure your microcontroller's firmware sends the required configuration data via *I2C* to the board whenever your microcontroller is powered on.



<img src="images/pb0a_pins.png" width="100%" height="100%" />

* **Level Shifter Required:**    
  *I2C* logic levels are tied to the *IP5306* internal voltages which may vary depending on battery state of charge (*2.8-4.2V*). In order for *I2C* to work, your microcontroller must either be powered by the battery (**not** the *5V* output), or you need to use a *level shifter*.

  Powering the microcontroller directly off the battery will be infeasible as most microcontrollers are incompatible with the *2.8-4.2V* voltage range. You cannot use a voltage regulator either, as this would change the logic levels, too.

  So using a level shifter is a crucial part of your setup. Make sure you select a level shifter that supports independent voltages on both of its sides since the battery voltage can be lower **or** higher than the MCU voltage. Most chip-based level shifters like *TXS0108* and others are unsuitable. Select one that is using discreet MOSFETs (like the *BSS138*). 
  
  If you don't have a suitable level shifter at hand, **for testing purposes only** you can power the *PB0A* board **and** your microcontroller together from a lab bench power supply set to *3.3V*. Use pins `BAT+` and `GND` to connect **PB0A** to the power supply (which would be simulating a connected battery at a voltage level suitable for your MCU). 

* **Strong Pull-Ups Required:**   
  Both `SDA` and `SCK`/`SCL` must be pulled up to `VDD` (`BAT+`) using *2.2K* resistors. Due to the relatively high *400kHz I2C* speed and the design, a strong pull-up is required. *10K* and higher resistors may not work.

    

> Tags: Charger, Li-Ion, LiIon, Li-Po, LiPo, Boost Converter, 2A, 3.2A, USB, 1S, X-150, IP5306, I2C, CKCS, PB0A Configuration Tool Instructions.doc, TXS0108, BSS138, Level Shifter

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a?992043071607250919) - created 2025-07-06 - last edited 2025-07-06
