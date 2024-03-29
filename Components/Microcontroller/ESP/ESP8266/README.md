<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP8266

> A Workhorse With WiFi Support That Can Do The Job Even For Sophisticated Projects


The *ESP8266* from *Expressif* is probably the most widely used *microcontroller* in non-Arduino projects. It became an instant success and convinced many users to move from *Arduino* to *ESP* because of a number of substantial advantages:

<img src="images/esp8266_usbc_top_front_t.png" width="50%" height="50%" />

> [!TIP]
> Today, breakout boards with the successor **ESP32** are only marginally more expensive than the **ESP8266**. **ESP32** boards feature a better power regulator and is about *twice* as performant in any aspect. While the **ESP8266** is perfectly capable of handling most *DIY* projects, for new purchases you should look into buying **ESP32** instead: for example the original **ESP32 DevKit C** with the **ESP32 WROOM**, or better yet the successor **ESP32 C3** which comes with native *USB* support and is available in miniature form factors more closely resembling the **ESP8266** form factor.


## Specs

Here are the most important **ESP8266** specs at a glance:

| Item | Value | Comment |
| --- | --- | --- |
| GPIO | 17 | actually available pins depend on breakout board |
| SPI | 1 | for fast peripherals |
| I2C | 1 | software implentation, for slow peripherals |
| UART | 1 | serial communications, external serial-to-USB chip required for USB |


## USB-to-Serial Controller: CH9102, CP210x, CH340

Initially, microcontrollers were designed to use simple *serial interfaces* which is why they all include at least one *UART*. This does not enable them to connect to *USB*.

Since microcontroller boards need to be programmed, and programming takes place on a desktop computer, the microcontroller boards require a way to connect to *USB* (unless you want to connect them to an old-fashioned *serial port*).

> [!NOTE]
> Starting with **ESP32 S2** and **ESP32 C3**, modern microcontrollers today come with serial communications capabilities built-in. This eliminates the need for external components, and you can connect these microcontrollers directly to the USB port of a PC.

**ESP8266** breakout boards can use different *USB-to-serial* chips. On *Windows*, the type of chip just determines the speed and time it takes to upload new firmware. On other operating systems (like *iOS*), not all *USB-to-serial* chips are natively supported, and you may need to manually install additional drivers on your computer.


| Item | CH210x | CP9102 | CH340 | Remarks |
| --- | --- | --- | --- | --- |
| OS | all | all | Windows | other OS may need manual driver installation |
| Price | medium  | medium   |  low | |
| Speed Mbps | 12 | 4 | 2 | |

> [!NOTE]
> The *CP9102* is a relatively unknown variant that is pin-compatible to the *CH210x*. It is slower but still twice as fast as the *CH340*. 

There are other chip types such as *FT232RL*, *PL2303*, *MCP2221*, and *MAX3421* less commonly found.


## Comparisons

Here are a few comparisons to help you judge whether **ESP8266** is the right choice compared to popular alternatives.

### Arduino

The **ESP8266** solves two common *Arduino* problems:

* **Memory:** the initial (and still popular) *Arduinos* come with very limited programming memory. When sketches become a bit more complex, compiling frequently fails due to *out of memory* errors. This is not the case with **ESP8266*.
* **WiFi:** when your project requires wireless connectivity, the **ESP8266** comes with built-in support for all WiFi modes: it can act as an own *WiFi Access Point*, can work in *Station Mode*, and both. It can easily become a *webserver* and act as *web service*. *Arduinos* do not come with *any* wireless support.

In addition, **ESP8266** breakout boards are *much* cheaper than *Arduinos*. While the old *Arduino Uno* still sells for more than EUR 20,00, complete **ESP8266** breakout boards with 4MB RAM are available for under EUR 2.00.

So overall, **ESP8266** often is the "better *Arduino*". But wait: *the best is the enemy of the good*. The **ESP32**, the *successor* of the **ESP8266**, may be an even better choice. 

### ESP32

The **ESP32** (initially released 2016) succeeded the **ESP8266** (releaased 2014) and has since seen many new subtypes such as the **S2**, **S3**, **C3**, and **C6**.

The initial **ESP32 WROOM** microcontroller (released 2016) can today be purchased for under EUR 3.00. Given its advantages, it may well be the better choice when thinking about purchasing new **ESP8266**:

* **Faster:** The **ESP32 WROOM** microcontroller is a dual-core microcontroller running at 260MHz. It is roughly twice as fast as the **ESP8266**.
* **Bluetooth:** In addition to *WiFi*, the **ESP32 WROOM** also supports *Bluetooth* so you can control your projects from mobile devices such as smartphones.
* **Better Components:** the **ESP8266** breakout boards are known for using inferior *voltage regulators* that can hardly provide the current required to power the microcontroller. Once additional sensors are connected, it is not uncommon for the **ESP8266** microcontroller boards to run into random resets or other erratic behavior due to power problems. **ESP32** breakout boards all come with sufficiently dimensioned *voltage regulators*.
* **Direct USB Support:** The **ESP32** can natively act as *USB Host* and emulate USB devices such as *keyboards* and *mice*. Starting with **ESP S2** and **ESP32 C3** (*not* **ESP WROOM**), the microcontroller also allows direct firmware upload via *USB*, eliminating the need for external components and drivers such as *CH340* 

> [!TIP]
> My personal recommendation is the **ESP32 C3** breakout board (available for under EUR 3.00). It uses one of the most modern **ESP** microcontrollers, specificly one with native *USB* support, and comes in miniature form factors that fits even the smallest DIY devices and specializes in *energy savings modes*.

## ESP8266 from Expressif

The **ESP8266** surfaced in 2014. This microcontroller is much more powerful than the *ATMegas* used by *Arduino* at that time. 

<img src="images/esp32_family1_t.png" width="100%" height="100%" />

<sup>from *left to right ordered by size*: **ESP32 C3** from *Seeed*, **ESP8266** *D1 Mini clone*, **ESP32 WROOM 32D** *dev board*.</sup>

Todays' *entry level* **ESP8266** typically come with *4MB* memory on board (check before you buy though, there are also 512KB variants).


### ESP8266EX

The **D1 Mini** (including clones) probably is the most popular board design: it is *cheap*, *compact*, comes with *WiFi* capabilities, has sufficient *memory* (tyically 4MB), provides enough *GPIO* pins for most projects (9 of which 5 are freely usable), has one *ADC* and supports *SPI* and *I2C* interfaces.

<img src="images/esp8266_angleback_t.png" width="60%" height="60%" />

<sup>The *ESP8266 D1 Mini* is one of the most popular **ESP8266** boards in use.</sup>

It is based on the *Expressif ESP8266EX* chip, basically the only *ESP8266* chip widely used.

### ESP8266 Pro

The **Pro** version of **ESP8266** appears to be merely a marketing gag and refers to a different board layout. Its most visible "advantages* are a *ceramic antenna* instead of the simple *PCB antenna* and more memory: most **ESP8266 Pro** come with *16MB* instead of *4MB* memory (but watch out, some feature just 8MB or just 4MB).


<img src="images/esp8266_mini_pro_front_unsharp_t.png" width="60%" height="60%" />

<sup>The **ESP8266 Pro** is almost as expensive as a full-fledged **ESP32** and not a good choice.</sup>

On the negative side is an *unshielded* version of **ESP8266** (not covered by a shiny silver metal box) that has no *FCC ID*, and the same lame *voltage regulator* you find on the cheapest **ESP8266 clones*.

> [!TIP]
> *ESP8266 Pro* is a product from the past when the price difference between *ESP8266* and *ESP32* was still huge. Anyone in need of more memory could try and use the *ESP8266 Pro*.
> Today with price differences diminishing, either the basic *ESP8266* features are sufficient for your project (in which case you should get an *ESP8266*), or you need more (memory or better specs or a better voltage regulator). In which case you should get an *ESP32*.
> For the price of a *ESP8266 Pro* you can get a *ESP32* as well when you look around a bit.


> Tags: Microcontroller, ESP8266, Clone, Power Regulator, Expressif

[Visit Page on Website](https://done.land/components/microcontroller/esp/esp8266?549965031823244200) - created 2024-03-23 - last edited 2024-03-23
