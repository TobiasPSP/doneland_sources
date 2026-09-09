<img src="/assets/images/lightning.png" width="100%" height="100%" />


# Makita LXT Monitoring and Unlocking Tools

> Building Makita LXT Tools For Monitoring And Unlocking

In this section I'll build a number of tools - very simple proof-of-concepts as well as rugged tools for daily use. They all query Makita LXT battery state and can optionally unlock dead batteries.


## Overview

All tools presented in this section are based on community work:

* **Makita Battery Unlocker:**     
  The most sophisticated firmware. It runs best on a *RP2040 Zero* but also supports *ESP32* and *Arduino Uno/Nano*.   

* **ArduinoOBI:**     
  The classic firmware that surfaced first. This is a dongle only that needs a PC connected to its USB interface. It runs on *Arduino Nano/Uno* and *ESP32-C3 SuperMini*.  

* **ESP32 Makita Reader:**     
  Runs on *ESP32*-family MCUs only and leverages the built-in webserver to present a rich graphical user interface on your smartphone.   

> [!NOTE]
> You can run firmwares on other MCUs as well if you are comfortable with adjusting the firmware source code yourself.

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/toolbatteries/makita/makitalxtdigitalinterface/tools?313596051114263256) - created 2026-05-13 - last edited 2026-05-13
