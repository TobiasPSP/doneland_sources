<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP32 Microprocessor Family

> High-Powered Single- And Dual-Core Microcontrollers With WiFi, Bluetooth, And Now Also Zigbee And Thread Support


## GPIOs
Since understanding which *GPIO pins* are safe to use in projects is among the most frequently needed information, this information is placed at the beginning of this article.


### Always-Safe ESP32 GPIOs

Below *ESP32 GPIOs* are **safe to use** for *whatever purpose*. Whether your microcontroller board actually *exposes* a particular pin depends on the board design.


| GPIO | Modes | Remark | Remark |
| --- | --- | --- | --- |
| 4 | Ain Din Dout | D4 | general purpose input/output GPIO|
| 16 | Din Dout | RX2 | general purpose input/output GPIO|
| 17 | Din Dout | TX2 | general purpose input/output GPIO|
| 25 | Ain Aout Din Dout | DAC1 | exposes DAC1 (if used) |
| 26 | Ain Aout Din Dout | DAC2 | exposes DAC2 (if used) |
| 27 | Ain Din Dout |  | general purpose input/output GPIO|
| 32 | Ain Din Dout |  | general purpose input/output GPIO|
| 33 | Ain Din Dout |  | general purpose input/output GPIO|
| 34 | Ain Din |  | input only, no pullup/pulldown |
| 35 | Ain Din |  | input only, no pullup/pulldown |
| 36 | Ain Din |  | input only, no pullup/pulldown |
| 37 | Ain Din |  | input only, no pullup/pulldown |
| 38 | Ain Din |  | input only, no pullup/pulldown |
| 39 | Ain Din |  | input only, no pullup/pulldown |





### Safe ESP32 Input-Only GPIOs

GPIOs *34-39* are *safe* to use as *digital or analog inputs only*. These GPIOs also do not have built-in *pullup/pulldown resistors*, so if you use them as *input pin*, you need to add an external resistor in order to keep the GPIO from *floating* and producing random input values. 




### Reserve GPIOs
If you need even more GPIOs for your project, you can look into using the GPIOs below. They serve other purposes, too, however if you do not need their functionality (i.e. your code does not use the *I2C* interface), you get valuable additional *GPIOs*:

| GPIO | Modes | Caveat |
| --- | --- | --- | 
| 0| Ain Din Dout | input is pulled up, outputs PWM signal at boot, must be *low* to enter flashing mode |
| 1| Dout | **TX** pin for serial communications, debug output at boot |
| 2| Ain Din Dout | connected to on-board *LED*, *floating* or *low* to enter flashing mode |
| 3| Din | **RX** pin for serial communications, *high* at boot |
| 5| Din Dout | outputs PWM signal at boot, strapping pin, VSPI |
| 12 | Ain Din Dout | boot fails if pulled *high*, strapping pin, HSPI |
| 13 | Ain Din Dout | free to use if HSPI is not used|
| 14 | Ain Din Dout | free to use if HSPI is not used |
| 15 | Ain Din Dout | free to use if HSPI is not used |
| 18 | Din Dout | free to use if VSPI is not used |
| 19 | Din Dout | free to use if VSPI is not used |
| 21 | Din Dout | free to use if I2C is not used |
| 22 | Din Dout | free to use if I2C is not used |
| 23 | Din Dout | free to use if VSPI is not used |



### Interface Pins (I2C and SPI)
The GPIOs below are used for *I2C* and *SPI* communications. If you do not require these interfaces, you are free to use these GPIOs for other things.

#### I2C
| GPIO | Label | Remark |
| --- | --- | --- |
| 21 | D21 | SDA |
| 22 | D2 | SCL |

#### SPI


| Function | VSPI | HSPI | 
| --- | --- | --- | 
| MOSI | 23 | 13 | 
| MISO | 19 | 12 |
| CLK | 18 | 14 |
| CS | 5 | 15 |


### Strapping Pins
If you *need even more* GPIOs, you can use the additional *four GPIOs* listed below - provided **you do not inappropriately use** these pins *during boot time*.

| GPIO | Label | Remark |
| --- | --- | --- |
| 0  |  0 | *low* to run ROM serial boot loader. Else, run custom code |
| 2 | D2 | if GPIO is *high*, then GPIO2 is ignored.  Else, must be *low/floating* to enter boot loader. |
| 5 | D5 | controls timing of *SDIO slave*, default is *high* during boot (rising-edge output). Irrelevant when chip uses normal SPI flash. Used for CS in VSPI. |
| 12 | D12 | sets flash voltage (3.3V by default). If set to *high* on accident during boot, 3.3V flash receives 1.8V and browns out |
| 15 | D15 | *low* silences boot messages |

In reality, the restrictions may not be so severe after all:

* **GPIO0:** **do not use**
* **GPIO2:** must never be hard-wired to *high*. In your code, you can freely use *GPIO2* because your code will not run when boot mode was enabled via the *boot button*, and *GPIO2* only matters in boot mode.
* **GPIO5:** its strapping functionality does not apply to normal development boards, so it can be freely used unless *hardware SPI* is needed (i.e. for color displays or other high speed peripherals)
* **GPIO12:** must never be hard-wired to *high*. In your code, you can freely use *GPIO2* because your code will only run *after* the flash voltage has been set.
* **GPIO15:** Freely usable. Whether nor not boot messages are emitted is not interfering with boot.

Try to avoid using these pins as *inputs* (in which case you cannot control whether a user or input sensor delivers a *high* signal in the wrong moment), and never hard-code these pins to *high* levels otherwise.

From your code, you can use these *GPIOs* without much restrictions.


### Serial Com GPIOs

The *serial communications interface* is used to upload new *firmware*, and often also to *communicate* with it: `Serial.print()` commands in your firmware code can output information, i.e. sensor data, that show in the *terminal window* of an *IDE*.

During normal operation, and if you don't need serial communications yourself, its two pins can be used for other purposes as well:


| GPIO | Label | Remark |
| --- | --- | --- |
| 1 | TX0 | serial comm (transmit)
| 3 | RX0 | serial comm (receive) |


However, using these GPIOs may require prerequisites to not interfere with required *serial comm* during *boot* or *firmware upload*.

Since *your firmware code* **can not** run at these sensitive instances, your code is always fine. What you do need to consider is your *hardware design* and *schematics*: **do not** physically pull-up or pull-down these pins or connect components to these pins that can alter their state during *boot*.

### Ghost GPIOs
For unknown reasons, six GPIOs are generally not exposed in the *ESP32S GPIO MUX*, so they are *never exposed* on *any board*:


| GPIO | Label | 
| --- | --- |
| 20 | newer versions may expose this GPIO after all |
| 24 | not working |
| 28-30 | not working |


## ESP32 Microcontroller Types
The **ESP32** processor family is the **ESP8266** *successor* and surfaced in 2016 with the *ESP32 WROOM* and *ESP32 WROVER*. 

The *ESP32* family has since evolved with many more variants. The [Expressif Product Comparison](https://products.espressif.com/#/product-comparison) provides a complete list of models and specs. 

Here is a quick reference covering the most commonly used *ESP32* types, and their most important specs:


| Feature | [ESP32](ESP32) | [S2](S2) | [S3](S3) | [C3](C3) | [C6](C6)  | H2 |ESP8266 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Launch | 2016 |  2019 | 2020 | 2020 | 2021 | 2021 | 2014 |
| Core Type | LX6 | LX7 | LX7 | RISC-V | RISC-V | RISC-V | L106
| Cores | 2 | 1 | 2 | 1 | 1 | 1 | 1| 
| Frequency | 240 | 240 | 240 | 160 | 160 | 96 | 160 |
| Voltage | 2.3-3.6 | 3.0-3.6| 3.0-3.6 | 3.0-3.6 | 3.0-3.6 | 3.3-3.6 | 2.5-3.6 |
| GPIOs | 34 | 43 | 45 | 22 | 30 | 19 |17 |
| SRAM KB | 520 | 320 | 512 | 400 | 512 | 256 |160 |
| RTC/LP SRAM KB | 16 | 16 | 16 | 8 | 16 | 4 | 1 |
| int Flash MB | 0/2/4 | 0/2/4 | 0/8 | 0/4 | 0/4 | 2/4 | 4 |
| Cache KB | 64 | 8/16 | 16 | 16 | 16 | 16 | 32 |
| ROM KB | 448 | 128 | 384 | 384 | 320 | 128 | 0 |
| ADC | 2x12bit 18ch | 2x13bit 20ch | 2x12bit 20ch | 2x12bit 6ch | 1x12bit 7ch | 1x12bit 5ch | 1x10bit 1ch |
| DAC | 2x8bit | 2x8bit | -  | - | -  | -  |- |
| Timers | 4x64bit | 4x64bit | ? | 2x54bit/1x52bit | ? | 2x54bit | 2x23bit |
| Watchdog | 3 | 3 | 3 | 3 | 3 | 3 | 1 |
| I2C | 2 | 2 | 2 | 1 | 2 | 2 | 1 |
| I2S | 2 | 1 | 2  | 1 | 1 | 1 | 1 |
| SPI | 4 | 4 | 4 | 3 | 2 | 3 |2 |
| Ethernet | yes | - | - | - |- | - |- |
| LCD Interface | 1 | 1 | 1 | - | - | - | - |
| Temperature | - | yes | yes | yes | yes | yes | - |
| Touch | 10 | 14 | 14 | - | - | - | - |
| UART | 3  | 2 | 3 | 2 | 3 | 2 | 2|
| Ethernet | 1 | - | - | - | - | - | - |
| IR/RMT | 8  | 4 | 8 | 4 | 4 | 4 | 1 |
| Hall Sensor | 1 | - | - | - | - | - | - |
| LED PWM | 16  | 8 | 8 | 6 | 6 | 6 | 5 |
| Motor PWM | 6 | - | 2| - | - | 1 | - |
| Wifi | 4 | 4 | 4 | 4 | 4/6 | no | 4 | 
| Wifi Mbps | 150 | 150 | 150 | 150 | 150 | - | 75 |
| Bluetooth | 4.2  | - | BLE5.0 | BLE5.0 | BLE5.3 | BLE5.3 | 0 |
| Thread 1.3 | - | - | - | - | yes | yes | - |
| Zigbee 3.0 | - | - | - | - | yes | yes | - |
| Matter | - | - | - | - | yes | yes | - |
| HomeKit, MQTT, etc | - | - | - | - | yes | yes | - |
| USB OTG | - | yes | yes | - |- | - |- |
| Camera Interface | 1  | 1 | 1 | - | - | - |- |
| TWAI (CAN 2.0) | 1 | 1 | 1 | 1 | 2 | 1 | - |
| SD Host | 1 | - | 2 | - | - | - | - |
| SD Slave | 1 | - | - | - | 1 |- |  1 |
| JTAG | yes | yes | yes | yes | yes | - |
| TOF | - | yes | - | - |- | -  | - |
| AI Acceleration Support | - | - | yes | - | - | - | - |
| Deep Sleep | 100uA | 22uA | 7uA | 5uA | 7uA | 8uA | 20uA |  
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
