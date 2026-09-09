<img src="/assets/images/lightning.png" width="100%" height="100%" />


# Firmware to Emulate Makita Protocol

> Implementing the Proprietary Makita 1-Wire Protocol



In the previous part, you created the required hardware to build a Makita "dongle" that translates the proprietary Makita 1-Wire protocol. To make it work, pick a suitable firmware for it.



## Overview

Makita batteries use default 1-Wire, but with proprietary timings, so you cannot use default 1-Wire libraries. In 2021, *Martin Jansson* started to reverse-engineer the Makita protocol:

* Protocol analysis in 2021:     
  [Battery Hacking](https://martinjansson.netlify.app/posts/makita-battery-post-1) – Initial reverse-engineering work.

* Firmware extraction & command discovery in 2024:      
  [Command Set Analysis](https://martinjansson.netlify.app/posts/makita-battery-post-1) – Extracted original firmware, identified key commands.

He then open-sourced his findings and created the first open-source firmware: [ArduinoOBI](https://github.com/mnh-jansson/open-battery-information/tree/main/ArduinoOBI). It used an Arduino Uno and implemented the Makita 1-Wire protocol. Today, this firmware also runs on ESP32-C3 SuperMini and Arduino Nano.

It was part of a larger project called [OpenBatteryInformation](https://github.com/mnh-jansson/open-battery-information) which contains the software that actually talks to the battery through the *ArduinoOBI* dongle.

Almost all newer developments base on this ground work.

### Challenges and Caveats

Deciphering the Makita 1-Wire protocol is only the first challenge. There is another one:

Once you know *how* to talk to Makita batteries, you still don't know *which commands* the battery supports, and how the results are interpreted that you get back from it.

As it turns out, Makita has revised its LXT batteries numerous times and is using a wide variety of boards and controllers. That's why *Martin Janssen* maintains a [comprehensive wiki](https://github.com/mnh-jansson/open-battery-information/wiki/Makita) with the different battery types that have surfaced so far.

At present, there seem to be at least five fundamentally different LXT battery subtypes. Not all of these are fully reverse-engineered yet, so at present, most LXT batteries are supported, but **not all**.

## Choosing Firmware

In the past years, the community has created a number of firmware options that you can choose from. They all work with numerous cheap microcontrollers:

1. [**ArduinoOBI** (2024):](https://github.com/mnh-jansson/open-battery-information/tree/main/ArduinoOBI)    
This is the original implementation maintained by *Martin Janssen*. It requires a separate python script called [OpenBatteryInformation](https://github.com/mnh-jansson/open-battery-information) which sends the actual battery commands and displays the results in a graphical user interface.

    The [ArduinoOBI](https://github.com/mnh-jansson/open-battery-information/tree/main/ArduinoOBI) firmware acts like a pure dongle and implements the Makita timings only. Separate software must send the actual commands, but you can easily use your own scripts written i.e. in Python or PowerShell in place of the original software.

2. [**ESP32 Makita BMS Reader** (2025):](https://github.com/Belik1982/esp32-makita-bms-reader)   
  Designed for *ESP32* microcontrollers only, this firmware takes advantage of its internal web server, combining both the Makita protocol implementation and the command logic inside the microcontroller. No external PC or other dependencies are required.

    Instead, you use your smartphone as the presentation layer and get sophisticated battery information and graphs.

3. [**Automatic Makita LXT Battery Unlocker** (2026)](https://github.com/synrais/Makita-LXT-Battery-Monitor-Unlocker)     
Major rewrite with some improvements. This firmware combines Makita protocol implementation and command logic and primarily targets *battery unlocking* which is done automatically. It can also *lock* batteries, and software is included that can be used to display battery information if needed.    

This firmware is currently the most sophisticated solution, especially when you want to unlock batteries.
 
## [ArduinoOBI](https://github.com/mnh-jansson/open-battery-information/tree/main/ArduinoOBI)

Use this firmware if you want a pure Makita 1-Wire Protocol dongle. Here, you also find the most comprehensive [community support](https://github.com/mnh-jansson/open-battery-information/issues) as it is the longest-running project.

You can use the provided [OpenBatteryInformation](https://github.com/mnh-jansson/open-battery-information) python script/executable to display battery information or unlock a locked battery, or write your own scripts using i.e. Python or PowerShell to explore the Makita interface on your own terms.

Should battery unlocking fail, then you may want to switch to [Automatic Makita LXT Battery Unlocker](https://github.com/synrais/Makita-LXT-Battery-Monitor-Unlocker). This firmware has been optimized specifically to unlock (and lock) Makita LXT batteries and employes more sophisticated unlock procedures than [OpenBatteryInformation](https://github.com/mnh-jansson/open-battery-information).

## [Automatic Makita LXT Battery Unlocker](https://github.com/synrais/Makita-LXT-Battery-Monitor-Unlocker)

This firmware is a major rewrite and cleanup. It is much more complex than the original *ArduinoOBI* since it implements both the "dongle" part (as in *ArduinoOBI*) and the logic/command part (as in *OpenBatteryInformation*).

This firmware can be used stand-alone to unlock locked batteries, and it provides software that runs on various operating systems to display battery information. 

If you run this firmware on a *RP2040 Zero*, you get support for a WS2812 RGB LED that provides simple but effective feedback, turning it in a simple stand-alone handheld device. On other microcontrollers, the LED is currently not supported.

The author has made several enhancements, i.e. more complete unlock procedures, and automatic battery health calculations. That's why this firmware is also a great starting point for your own developments as it is probably the cleanest, most structured, and most complete implementation as of today.


## [ESP32 Makita BMS Reader](https://github.com/Belik1982/esp32-makita-bms-reader)     
 
If you want a generic Makita handheld tool without any dependencies, this firmware uses an ESP32 microcontroller and its internal web server. The firmware includes both the "dongle" and the command logic implementation and uses your smart phone screen as user interface.

That's a great way of testing and checking Makita batteries without the need to have a PC around.

> Tags: Makita, One-Wire, 1-Wire, OneWire, Digital Interface, LXT, Firmware

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/toolbatteries/makita/makitalxtdigitalinterface/2.firmware?628932051009261136) - created 2026-05-08 - last edited 2026-05-08
