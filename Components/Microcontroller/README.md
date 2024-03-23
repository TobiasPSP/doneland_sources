<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Microcontrollers

> They Manage Sensors, LEDs And Other Components Much Cheaper Than Implementations With Discrete Elements Only.

What started in *PCs* and carried over to devices like *Smartphones* is now common-place even for *DIY projects*: instead of trying to implement features exclusively with *discrete elements* like transistors and some *ICs*, it is much easier and more *cost-effective* to add a **microcontroller**.

In this section you learn more about the typical microcontrollers used in *DIY projects*, how they differ, and what they can do for you.

> [!TIP]
> Programming a microcontroller today is fundamentally the same, regardless of vendor and microcontroller type you choose, thanks to the *Arduino Framework*: all microcontrollers listed below understand the same code.


> [!CAUTION]
> There are hardware differences of course, and while *code examples* will run on all microcontrollers, there may be minor hardware adjustments needed, i.e. you might need to review and adjust the GPIO pins used.
> Be aware that *Arduinos* are **5V** devices whereas *ESPs* use **3.3V**.


## Microcontroller Families

There are *three* families of microcontrollers that are commonly used in *DIY* projects:

* [ATMega/Arduino](Arduino): *Arduino breakout boards* started to make *microcontrollers* popular among hobbyist and makers. Until recently, *Arduinos* exclusively used the *ATMega* microcontrollers. Meanwhile, some *Arduino breakout boards also use *ESP* and other microcontrollers. 
* [ESP/Expressif](ESP): When the Chinese company *Expressif* released its **ESP8266**, it became an instant success: it was comparably powerful and *WiFi*-enabled. Today, the single- and dual-core **ESP32** microcontrollers probably are among the most powerful, most competetively priced and most popular processors.
* [ATTiny](ATTiny): for less computing intensive use cases, *ATTiny* microcontrollers are are great alternative due to their very small size and very low cost.

> [!NOTE]
> There are *many more* microcontrollers available. For now, I am focusing on the *most popular* among low-level *DIY* makers. I am neither focusing on the many other *industrial* microcontrollers (that require expensive development tools to program) nor on the almost *PC*-like *Raspberry Pi* and similar.


## Development Environments

All three processor families can be programmed using the same *Arduino Framework*. There are *two* commonly used *development environments*:

* **Arduino IDE:** this proprietary free development environment is very simple to use and because of this *simplicity* was the key to success for making *Arduinos* immensely popular. Today, the other microcontroller families can also be programmed using this *IDE*. This is not quite as simple as it initially requires to load certain extensions and changing of some configurations. Once code becomes a bit more complex, the *Arduino IDE* cannot hide its age and simplistic editing functionality. It is best used for beginners and for playing with *very simple* code examples.
* **VSCode/platformio:** Microsofts free *VSCode* text editor comes with numerous extensions for almost any programming language and is highly extensible. This is why this editor today is the choice for many *professionals*. The free extension **platformio** is an excellent *development environment* for programming any of the three microcontroller families listed above.

There are *many more* development environments available. The two examples listed above are the most commonly used choices among hobbyists and *DIY* makers.

> [!NOTE]
> Most microcontrollers mentioned here support the *Arduino Framework*. Very new *microcontrollers* may not yet support this framework. Currently, the *ESP32 C6* is an example. Microcontrollers that do not support the *Arduino Framework* can only be programmed using the vendors own *development environment*, for the *C6* the [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html) (*ExpressIf IoT Development Framework).

## Originals and Clones

At the heart of any microcontroller board is always a *CPU* which is the only truly *unique* part.

The supporting boards can come from a variety of sources. Aside from the *original company* that came up with a particular design, there are numerous *clones* available that *copied* the (open-source) design. These *clones* are *much cheaper* and typically work very well, too.

<img src="images/clones2_t.png" width="80%" height="80%" />

<sup>**Nano Every**, a clone (*left*) and the original (*right*)</sup>


### CH9102, CP210x, CH340

*Older microcontrollers* such as the *ATMega* and *ESP8266* do not come with a *USB-to-Serial* controller built-in. This controller is necessary to connect the board to your *PC* when you want to program it.

Most breakout boards with the mentioned microcontrollers therefore add discrete *USB-to-Serial* chips. 

There are different types available. The type of *USB-to-Serial* controller determines whether you can connect the board to your PC *without having to install additional drivers*, and it determines the *speed* in which you can upload new firmware.

Here are the differences:

| OS | CH9102 | CP210x | CH340 |
| --- | --- | --- | --- |
| Windows | yes | yes | yes |
| MacOS | yes | yes | driver needed |
| Speed Mbps | 4 | 12 | 2 |

On *Windows* you can use all chips. For maximum transfer speed, try and choose boards with *CP210x*.

On *Apple*, try to avoid *CH340* unless you are ok with potentially having to search for and install an appropriate driver for it.

> Tags: Microcontroller, Arduino, ESP8266, ESP32

:eye:&nbsp;[Visit Page on Website](https://done.land/components/microcontroller?237357031823244200) - last edited 2024-03-23
