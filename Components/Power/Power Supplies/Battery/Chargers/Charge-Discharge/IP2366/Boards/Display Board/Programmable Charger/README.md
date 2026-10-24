<img src="/assets/images/charging.png" width="100%" height="100%" />

# Programmable Charger

> Universal 2-6S Programmable Charger via I²C For Various Lithium Chemistries

The [IP2366 Display Board](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2366/boards/displayboard/) is a capable and very affordable board with a working I²C interface. Out-of-the box, it is a capable powerbank controller.

<img src="images/ip2366_screen6.jpg" width="80%" height="80%" />  

Thanks to its I²C interface, it can be repurposed for a variety of things, for example as a universal 2-6S Lithium battery charger.

## Overview

First of all, you do need the [IP2366 board with a display](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2366/boards/displayboard/). There is also a cheaper display-less board that uses LEDs instead. However, the IP2366 on the display-less board has **no I²C functionality**, even if you remove the LED resistors.

> Of course, you can use *any* board with I²C-compatible IP2366, but the board I am using here is very affordable, is guaranteed to support I²C, and exposes all necessary pins.   

### I²C
I²C allows anyone to send instructions to the IP2366. This is how the display daughter board controls the chip, and this is also how you can modify the IP2366 behavior. 

To change the functionality and turn the powerbank controller i.e. into a universal charger, there are two routes:

* **Change Firmware for Existing MCU:**     
  The Puya microcontroller on the daughter board is fully programmable and exposes the SWD pins to upload new firmware. And in fact, the designer of this board claims the existing firmware is open-source.   
  
  So the most elegant approach would be to keep the daughter board and reprogram its firmware to create a universal charger.

  The board designers keeps all source code and tools in a Chinese **QQ Group** with the **ID 170681020**. QQ groups serve as a Chinese *github* but are open only for Chinese nationals. 

  So unless someone with access to QQ groups can help out, this route is closed.    
* **Create Your Own Controller:**    
  By removing the daughter board altogether, you get access to the raw I²C pins of the IP1266 controller. Adding your own controller opens up a variety of options, as now you can program the IP2366 in any way you want, and you can use any microcontroller of your choice.

  Using this route has a number of advantages: select your favorite microcontroller, possibly with much more RAM and radio support, and stay in your comfort zone. You are now also free to use any display size you want, and optionally add touch screens.


### Hardware Overview

In this project, I am using the affordable and readily available [Guition JC3248W535 3,5" ESP32-S3 Touch Display Board](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s3/guitionjc3248w535/) as a host controller:

* Plenty of RAM
* Large Display
* Enclosure
* Touch Screen
* Radio for Remote Control

This tablet is then connected via I²C to the base board of the [IP2366 Display Board](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2366/boards/displayboard/). 

The daughter board with the display and the original Puya microcontroller is not used.


### Design Objective

Using the IP2366 board as a universal charger that leverages the IP2366 capabiliies:

* **Strings:**   
  Support 2-6S batteries    
* **Chemistry:**   
  Support all lithum chemistries, including LiFePo4, LiIon, LiPo, LiHV
* **Charging Current:**   
  Support charging currents in the range of 100 mA to 9.5 A.    
* **Storage:**   
  Support charging batteries to a configurable percentage, i.e. 50% for storage.    
* **Monitoring:**    
  Monitor battery charging with a V-I-Graph and temperature, and lower charging current and/or abort charging when temperature exceeds a threshold.  
* **Dead Batteries:**    
  Include support for trying to charge 0 V-batteries with a much reduced "reviving" current.

#### Control
The device should be controllable in a variety of ways:

* **Manual:**  
  via touch screen, i.e. to intuitively and easily configure and run the charger stand-alone     
* **Remote:**   
  via web interface, i.e. to check the charger status from elsewhere   
* **Automated:**   
  via *ESPNow* radio, i.e. for automated testing or lab scenarios

The choice for wireless *ESPNow* remote control was based on simplicity. It has a very low latency and works reliably in close range.

Using a wired solution like I²C would have defeated the purpose, because then you could as well directly access the IP2366 board over its own I²C interface. In fact, this project keeps the interaction with the IP2366 separated in a library, so if you want I²C, simply skip the tablet host controller, and instead use the library to interface your lab gear directly with the IP2366.

One challenge with *ESPNow* is that it has dependencies with WiFi (must use the same radio channel), and when the unit is connected to home WiFi (vs. its own hotspot), the WiFi channel can change any time. This needed to be addressed by implementing a fallback where the tablet actively searches for a new radio channel if ESPNow heartbeat breaks.

## Wiring

Wiring is extremely simple.

### I²C

#### Tablet
On the tablet side, [connector `P3`/`P4`](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s3/guitionjc3248w535/#p3-and-p4-ic) is used. You either need a QWIIC 1.0 or a JST 1.25 4-pin connector.

<img src="images/jc3248w535_conn_p3_4.webp" width="80%" height="80%" />  

Pin assignment follows the [QWIIC Standard](https://www.cable-tester.com/i2c-pin-out-qwiic-from-sparkfun-electronics/).

| Connector Pin (left to right)  | Assignment |
| --- | --- |
| `GND` | Ground |
| `VCC` | 3.3V |
| `IO17` | `SDA`|
| `IO18`| `SCL` |

#### IP2366 Board

The IP2366 base board has a 1.25 mm pitch 6-pin header that is normally used to connect the daughter board.

<img src="images/ip2366_6pin_connector.webp" width="80%" height="80%" />  

Pins are (from left to right, from inside to outside):


| Pin | Description | Remark |
| --- | --- | --- |
| 1 | `GND` | |
| 2 | `ENABLE` | not used by the original display board |
| 3 | `INT`| keep `HIGH` to prevent IP2366 from sleeping |
| 4 | `SDA` | I²C |
| 5 | `SCL`| I²C |
| 6 | `BAT+` | **WARNING:** battery pack voltage, can be very high and powerful. Short circuits are dangerous and can destroy the board. Use with suitable buck converter to power the host. 

One of the simplest ways to connect these pins is using a 6-pin JST 1.25 connector: the pitch matches, and the connector slides firmly on the pins. You can of course also solder wires to the pins.

<img src="images/ip2366_6pin_connect.webp" width="80%" height="80%" />

#### Pull-Up Resistors

The IP2366 board does not use I²C pull-up resistors, so you need to provide them. The datasheet recommends 2.3K resistors. I used 10K resistors with no issues.

### Keep-Awake: `INT`

You need a way to keep the IP2366 awake even when it does not charge so it stays responsive, i.e. to initiate another charging cycle. Else, you would have to manually "wake up" the chip by unplugging and re-plugging the USB-C power cable.

There are two routes you can take:

* On the IP2366 board, pull `INT` to `HIGH`. This prevents the charger from going into standby mode.
* Turn off *Automatic Standby* via I²C register `0x09`, bit 7	(`En_Standby`):	0 = disable standby; 1 = allow standby.

I opted for both. To pull `INT` to `HIGH` with the tablet, you need another GPIO. Connector `P2` exposes 8 additional GPIOs and requires a 8-pin JST 1.25 connector:

<img src="images/jc3248w535_conn_p2.webp" width="80%" height="80%" />  

For the `INT` signal, I selected `IO6`. 

**IMPORTANT:** `IO5` is already used internally by the tablet to determine the battery voltage through a voltage divider.

> [!NOTE]
> If you have no 8-pin connector at hand, you may want to try and skip this connection altogether. The firmware already disables sleep via I²C, and that should be good enough. Only when the IP2366 does become unresponsive after charging completed, add this connection.   





> Tags: IP2366, Charger, Firmware, QQ, Display, Puya, PY32F030K28, JTYJ-2366-C, I²C, QQ Firmware

