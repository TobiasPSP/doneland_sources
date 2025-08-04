<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP32 Microprocessor Family

> High-Powered Single- And Dual-Core Microcontrollers With WiFi, Bluetooth, And Now Also Zigbee And Thread Support

ESP microcontrollers are renown for their affordability, performance, and well-balanced feature set including support for wireless communications. 

This makes ESP microcontrollers very popular for DIY projects.

On the downside, ESP microcontrollers are power-hungry and may not the best choice for battery-powered portable devices. Their power consumption during normal operation is well above *100mA*, whereas the most power-efficient microcontrollers (i.e. the *Nordic nRF52* series (such as the *nRF52840*) consume just *4-8mA*.

## Overview

The ESP family of microcontrollers has grown quite large over time. For general purpose DIY projects, however, only a few models are relevant:


| Microcontroller | Remark | Successor |
| --- | --- | --- |
| [ESP8266](https://done.land/components/microcontroller/families/esp/esp8266/) | Single-Core Simple MCU, many users transitioned to this MCU from *Arduino* | [ESP32-C3](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/), [ESP32-S2](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/) |
| [ESP32S](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/) | Powerful Two-Core MCU, has become DIY default for many projects | **ESP32-S3** |

The first ESP microcontroller with overwhelming traction was the [ESP8266](https://done.land/components/microcontroller/families/esp/esp8266/). In 2016, the much more powerful dual-core [ESP32S](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/) started to replace the *ESP8266* and established itself as an affordable general-purpose DIY standard.

While this is still the case, meanwhile a number of successor microcontrollers surfaced. In a nutshell: 

* for simple projects that used *ESP8266* previously, today *ESP32-S2* or *ESP32-C3* are used.
* for more advanced projects that used *ESP32S* before, today *ESP32-S3* often is a better choice.

The [Expressif Product Comparison](https://products.espressif.com/#/product-comparison) provides a complete list of models and specs. 


### Specialized ESP32 Models
Some ESP family members focus primarily on new radio standards such as *Thread*, *Matter*, and *WiFi 5GHz*. 

Unless this is important for you, you can safely ignore these MCUs:

| Microcontroller | Remark  | Key Radio Standards |
| --- | --- |  --- |
| **ESP32-C6** | Adds Wi-Fi 6, Thread, Zigbee |  Wi-Fi 6 (2.4 GHz), BLE 5.0, IEEE 802.15.4 (Thread, Zigbee) |
| **ESP32-H2** | Focus on Thread/Zigbee, no Wi-Fi |  IEEE 802.15.4 (Thread, Zigbee), BLE 5.2 |
| **ESP32-P4** | Newest member, supports Wi-Fi 5 GHz |  Wi-Fi 2.4 GHz & 5 GHz, BLE 5.x |


### History
To better understand how the ESP family of MCU evolves, here is a comparison:

| Feature | [ESP32](ESP32) | [S2](S2) | [S3](S3) | [C3](C3) | [C6](C6)  | H2 |[ESP8266](https://done.land/components/microcontroller/families/esp/esp8266/) |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Launch | 2016 |  2019 | 2020 | 2020 | 2021 | 2021 | 2014 |
| Core Type | LX6 | LX7 | LX7 | RISC-V | RISC-V | RISC-V | L106
| Cores | 2 | 1 | 2 | 1 | 1 | 1 | 1| 
| Frequency | 240 | 240 | 240 | 160 | 160 | 96 | 160 |
| Voltage | 2.3-3.6 | 3.0-3.6| 3.0-3.6 | 3.0-3.6 | 3.0-3.6 | 3.3-3.6 | 2.5-3.6 |
| GPIOs | 34 | 43 | 45 | 22 | 30 | 19 |17 |
| SRAM KB | 520 | 320 | 512 | 400 | 320 | 256 |160 |
| RTC/LP SRAM KB | 16 | 16 | 16 | 8 | 16 | 4 | 1 |
| int Flash MB | 0/2/4 | 0/2/4 | 0/8 | 0/4 | 0/4 | 2/4 | 4 |
| Cache KB | 64 | 8/16 | 16 | 16 | 16 | 16 | 32 |
| ROM KB | 448 | 128 | 384 | 384 | 320 | 128 | 0 |
| ADC | 2x12bit 18ch | 2x13bit 20ch | 2x12bit 20ch | 1x12bit 6ch | 1x12bit 7ch | 1x12bit 5ch | 1x10bit 1ch |
| DAC | 2x8bit | 2x8bit | ❌  | ❌ | ❌  | ❌  | ❌ |
| Timers | 4x64bit | 4x64bit | 4x64bit | 2x54bit | ? | 2x54bit | 2x23bit |
| Watchdog | 3 | 3 | 3 | 3 | 3 | 3 | 1 |
| I2C | 2 | 2 | 2 | 1 | 2 | 2 | 1 |
| I2S | 2 | 1 | 2  | 1 | 1 | 1 | 1 |
| SPI | 4 | 4 | 4 | 3 | 2 | 3 |2 |
| Digital Video Interface | ❌ | ✅ | ✅ | ❌| ❌| ❌| ❌| ❌|
| Ethernet | ✅ | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| LCD Interface | ✅ | ✅ | ✅ | ❌ | ❌ | ❌ | ❌ |
| MCU Temperature | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ❌ |
| Touch | 10 | 14 | 14 | ❌ | ❌ | ❌ | ❌ |
| UART | 3  | 2 | 3 | 2 | 3 | 2 | 2|
| Ethernet | 1 | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| IR/RMT | 8  | 4 | 8 | 4 | 4 | 4 | 1 |
| Hall Sensor | 1 | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |
| LED PWM | 16  | 8 | 8 | 6 | 6 | 6 | 5 |
| Motor PWM | 6 | ❌ | 2| ❌ | ❌ | 1 | ❌ |
| Wifi | 4 | 4 | 4 | 4 | 4/6 | no | 4 | 
| Wifi Mbps | 150 | 150 | 150 | 150 | 150 | ❌ | 72.2 |
| Bluetooth Classic | ✅ | ❌| ❌| ❌| ❌| ❌| ❌|
| Bluetooth BLE | BLE4.2  | ❌ | BLE5.0 | BLE5.0 | BLE5.3 | BLE5.3 | ❌ |
| Thread 1.3 | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ | ❌ |
| Zigbee 3.0 | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ | ❌ |
| Matter | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ | ❌ |
| HomeKit, MQTT, etc | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ | ❌ |
| USB OTG | ❌ | ✅ | ✅ | ❌ |❌ | ❌ |❌ |
| Camera Interface | ✅  | ✅ | ✅ | ❌ | ❌ | ❌ |❌ |
| TWAI (CAN 2.0) | ✅ | ✅ | ✅ | ✅ | ✅ (2) | ✅ | ❌ |
| SD Host | ✅ | ❌ | ✅ (2) | ❌ | ❌ | ❌ | ❌ |
| SD Slave | ✅ | ❌ | ❌ | ❌ | ✅ |❌ |  ✅ |
| JTAG | ✅ | ✅ | ✅ | ✅ | ✅ | ❌ | ❌ |
| TOF | ❌ | ✅ | ❌ | ❌ |❌ | ❌  | ❌ |
| AI Acceleration Support | ❌ | ❌ | ✅ | ❌ | ❌ | ❌ | ❌ |
| Deep Sleep | 10µA | 20µA | 7µA | 5µA | 7µA | 8µA | 20µA |  
| Size mm | 5x5/6x6 | 7x7 | 7x7 | 5x5 | 5x5 | 4x4 | 5x5 |

> [!NOTE]
> What was previously referred to as *RTC memory* has been renamed to *LP memory* (*low power memory*). You might see both terms used interchangeably.


## Quick Selection Guide
In a nutshell:

* if you *want it all* then get an *ESP32 S3*. They come in *large boards* (with all pins exposed) and *super-tiny*.
* if your focus is *GPIO* then get an *ESP32 S2*. They are super cheap with large memory.
* if you want *matter* support, get an *ESP32 C3*. They are super cheap as well.

*Classic ESP32 WROOM* are perfect generalists as well - as long as you don't want to *minimize energy consumption in battery projects* or use the fancy new wireless techniques like *matter*.

Depending on your feature requirements, here is a more feature-based guidance:

| Category | You want to... | Recommendation |
| --- | --- | --- |
| I/O | control as many external devices as possible | *S2* or *S3* (>40 GPIOs) | 
| DAC |output analog voltages using a built-in DAC | *ESP32* or *S2* |
| Touch | use touch sensors | *ESP32*, *S2*, or *S3* |
| USB Support | use USB devices such as keyboards and mice, or turn your microcontroller into a USB memory stick | *S2* or *S3* (USB-OTG required) |
| Camera Support | use a camera | *ESP32*, *S2*, or *S3* |
| Low Voltage | work with the lowest-possible voltage (i.e. solar projects) | *ESP32*, all other versions require a minimum of *3.0-3.3V* |
| Low Energy | run on battery for a long time | *S3* or *C3* |
| Bluetooth | use advanced Bluetooth LE features | *C6* or *H2* |
| Temperature | monitor the CPU temperature | *any* except *ESP32* |
| Motor Control | control motors | *ESP32* or *S3* |
| Matter, Threads, etc. | build *matter*-compatible devices | *C6* or *H2* |


## Overview
*Espressif*, the company producing *ESPxxx* microcontrollers, has never targeted the hpbbyist market: their processors were always targeting commercial *IoT device applications*.

The *ESP32* process family therefore is driven by the needs of this industry, and *DIY hobbyists* happily benefit from the top notch innovations that become available for very little money (as the *commercial market* consumes high numbers of these microcontrollers and dictates low prices).

As *commercial IoT devices* are increasingly interconnected, smartphone controlled, using cloud backends and requiring to run days and weeks on small batteries while providing complex and even AI-based services, the three major fields of innovation are *lower energy consumption*, *support for all broadly used wireless technologies*, and *support for AI vector analysis math coprocessors*.

### Wireless Strategy
All *ESPxxx*-based microcontrollers come with classic *WiFi support* - with one exception: the new *H2* is the first *ESP32* **not supporting** *WiFI*. That's for a reason because the *H2* has a very special role.

* **Matter over WiFi:** *Matter* is a new wireless standard that makes it simple to *add* and to control *matter-compliant* devices to *smartphones*. Any *WiFI*-enabled *ESPxxx* can be used to build *Matter WiFi* devices.
* **Matter Thread:** *Matter* can use *Thread* as a transport as well. Only the *C6* and *H2* come with the *802.15.4-compliant* (*5GHz*) technology for *Thread*.
* **Thread Border Routers:** A *H2* can be used to build a *Thread Border Router* to bridge between *Thread* and the regular *WiFi* world (including all other *ESPxxx* that have no native *Thread* support).
* **Matter Zigbee Routers:** A *H2* can also be used to build a *Matter Zigbee Router* to bridge between *Zigbee* and the regular *WiFi* world (including all other *ESPxxx* that have no native *Zigbee* support).





The original *ESP32* (and its successors like the *C3* or *S3*) are a great choice for almost any microcontroller-based *DIY project*: they are cheap and come with a wealth of useful features, including wireless support for many wireless standards and also sophisticated interfaces (such as *I2S* which enables high-frequency analog sampling and direct memory access).

In addition, *ESP32* development boards come with decent voltage regulators (compared to *ESP8266*), a massive number of *GPIOs*, and generous memory sizes.

In a nutshell, there is no good reason today anymore to purchase *ESP8266* as you get *ESP32* development boards for the same price.

The same is true for *Arduinos*: they were indeed ground breaking 15 years ago. Today, almost all *Arduino* boards are *massively underpowered* and at the same time *massively overpriced* when you compare them to any of the *ESP32* microcontrollers. Since you can continue to use your favorite *IDE* (Arduino IDE, platformio, etc), run the same sketches, enjoy *ESP32*-support for almost any library, and can continue to use *5V components*, considering one of the *ESP32* types for your next project might be a good idea.





> [!NOTE]
> If you can get your hands on *really really cheap ESP8266 boards* (below EUR 1.00), or if you still have a pile of them on stock, you can of course continue to use them, and they will continue to perform great for most typical *DIY projects*. Before you *buy new boards*, though, please compare offers: most likely you'll quickly find *ESP32 sales* matching the price tag of *ESP8266*. At the time of writing, *ESP32*, *C3*, and *S2* are all available for under EUR 2.00/piece.




### Comparing to ESP8266

Compared to the **ESP8266**, in a nutshell **ESP32** **doubles** everything :

Double the *CPU cores*, double the *WiFi Speed*, (roughly) double the *internal memory*, double the *GPIO pins*, double the *I2C* and *SPI* interfaces, double the *ADCs*, double the *Infrared support*

Plus, it *adds* many interfaces and capabilities: built-in support for *Bluetooth*, *CAN*, *LCDs*, *SD Cards*, *Ethernet*, *Camera*, *Touch*, you name it.

> [!TIP]
> The *ESP32* *doubles everything*, except the *price*. *ESP32* breakout boards start under EUR 3.00. Even if you don't need the power or extra features (like bluetooth) offered by *ESP32*, choosing *ESP32* breakout boards over *ESP8266* today is almost always the best choice. Unlike many *ESP8266* breakout board, *ESP32 boards* come with *decent power regulators*. 


| Feature | ESP32 | ESP8266 |
| --- | --- | --- |
| Core | 2 | 1 |
| Frequency MHz | 240 | 160 |
| SRAM KB | 520 | 160 |
| GPIO | 36 | 17 |
| Touch | 10 | - |
| ADC | 16, 12bit | 1, 10bit |
| DAC | 1, 8bit | - |
| Bluetooth | BLE 1.3 | - |
| CAN | 1 | - |
| I2C | 2 | 1 |
| PWM | 16 | 8 |
| Hall | 1 | - |
| typ. Power Consumption | 260mA | 80mA |


> [!TIP]
> The *only good reason* for picking *ESP8266* might appear to be its much lower *normal* energy consumption. This lower consumption though is a direct effect of its lower performance: a higher frequency and two cores cost energy. At the same time, they can solve tasks much faster. In real-world device design, when power consumption is an issue, the trick is to use the various *sleep modes* during *idle times*. In well-designed solutions, *ESP32* almost always uses *less energy over-all*: it solves issues faster and can stay most of the time in power-saving *sleep modes*.





### Same Form Factor

Despite its many additional features, **ESP32** are not necessarily bigger in size. The raw chip size did not change from **ESP8266*.

The **ESP32 C3**-based board from **Seeed** for example is tiny:

<img src="images/esp32_c3_seed_top_front_t.png" width="40%" height="40%" />

<sup>**ESP32** boards can be extremely small yet very powerful</sup>

If you do not need a *USB Connector*, you can further cut board size. The picture below shows an **ESP8266** on such a board. The same form factor is available for **ESP32**, effectively reducing the board size to the size of the actual microcontroller and a few supporting elements like a *ceramic WiFI antenna*:

<img src="images/esp8266_wo_USB_t.png" width="40%" height="40%" />

<sup>Boards without USB connector and UART are even smaller but require an external programmer to transfer the firmware.</sup>


> Tags: Microcontroller, ESP8266, ESP32

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32?405392031823244200) - created 2024-03-23 - last edited 2024-03-23
