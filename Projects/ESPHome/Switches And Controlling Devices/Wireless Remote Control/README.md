<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Wireless 433MHz Remote Control

> Use License-Free 433MHz Remote Control To Control Home Assistant Devices

Affordable RF Remote Controls can be used to control devices managed by *Home Assistant*. 

## Overview

[RF Remote Controls](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/) that operate on one of the license-free ISM frequencies are commonly used to open garage doors or start fans. They are not typically associated with *Home Assistant*.

That's because *Home Assistant* is wireless by nature: it uses *WiFi* and *Bluetooth* to communicate with devices. So if you wanted to build or use a wireless remote control, the natural choice would be to use *WiFi* and *Bluetooth* as well.

However, there are a number of good reasons why you may want to look into adding *RF remote controls* to *Home Assistant*:

* **Affordable:** Ready-to-use RF Remote Controls are very cheap and available in many different forms and shapes. They often are much cheaper than even the parts for building your own.
* **Battery-Efficient:** RF Remote Controls can operate for months and years on a single battery because only when you press a button and send a signal will they use energy. That's much different from *WiFi* and *Bluetooth* where you typically need a microcontroller, and you either needs to keep it in sleep mode for fast response, or you'd have considerable latency when the microcontroller first needs to log into *WiFi*. 
* **Range:** Since RF Remote Controls do not require any infrastructure like an existing WiFi network, they work everywhere and have quite a remarkable range. This may not necessarily be of advantage inside your house (where WiFi coverage is good and RF may be impaired by walls). It definitely is of advantage when you have a larger property and/or backyard, and would like to control devices there (or control devices in your house from outside which is coincidentally the typical use-case of garage door openers).

### Requirements

Since *Home Assistant* cannot recognize radio frequencies other than *WiFi* by default, you need one or more "base stations": receivers that can pick up the radio signals sent by remote controls, and forward them to *Home Assistant*.

Once the base station(s) are in place, you can pair any number of remote controls, and assign arbitrary devices to the remote control(s).

## Base Station

A base station works very similar to the [RF Remote Control Sniffing](https://done.land/components/data/datatransmission/wireless/intro/usingradiowaves%28ook%29/sniffingrfremotes/) project: you need a simple [OOK receiver breakout board](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/) like the [RXB59R](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/ak-rxb59r/), plus a microcontroller.

[Visit Page on Website](https://done.land/projects/esphome/switchesandcontrollingdevices/wirelessremotecontrol?335465041919251538) - created 2025-04-18 - last edited 2025-04-18
