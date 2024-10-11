<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Microcontroller Families

> How To Select The Right Microcontroller For Your Project

There are many *microcontrollers* and *boards* available for *DIY projects*, all with their individual strengths and shortcomings. In this section here is some guidance for selecting the best *microcontroller type* for a given task.

## [Arduino](https://done.land/components/microcontroller/families/arduino)
[Arduinos](https://done.land/components/microcontroller/families/arduino) surfaced in 2005 and started to open up microcontrollers to hobbyists and DIY makers. *Arduinos* are *open-source* board designs using a variety of microcontrollers. They are simple to program, and *ArduinoIDE* is a free and pragmatic coding editor. Also, given the long time that *Arduinos* are around, you find plenty of tutorials and code examples. In the past, *Arduinos* have therefore been the #1 choice for beginners. This has changed a bit, though.

### Considerations

If you'd think about using an *Arduino*, here are some thoughts:

* **Expensive:** Original *Arduinos* are hugely overpriced. Since their board design is *open-source*, there are plenty of cheap *clones* available from *Chinese companies* at *AliExpress*. Often, they cost less than *10%* of what you'd invest for an original board.
* **Slow:** Many *Arduino boards* use outdated and slow *ATmel* microcontrollers. They work for simple tasks but are very slow when compared to other microcontrollers and boards.
* **No WiFi:** Most *Arduinos* come with no wireless technology built-in. They can serve as stand-alone solutions but need expensive add-ons if you'd like to control them remotely or via your smartphone.
* **Compatibility:** While there are many free tutorials and resources for *Arduinos*, their once famous *compatibility* has faded away once *Arduino* started to add new models with different designs. Today, when you purchase one of the latest *Arduino boards*, you may run into frustrating compatibility issues, and code designed for the early *Arduinos* may not work on the newer ones.
* **Memory:** Most *Arduinos* come with very little memory. They work fine at first, but once your projects (and ideas) grow larger, you run into memory issues, your sketches won't compile, and/or the board becomes unstable.
* **Power:** most *Ardunios* are **5V** devices, cannot use *3.3V peripherals*, and are not especially power-efficient. Battery-operated projects may not last too long. Most modern microcontrollers (like the *ESP32* family) are **3.3V** operated so you can power them directly off a *LiFePo4* battery. They can be powered from *5V* as well (boards come with integrated voltage regulators) and then support both *3.3V* and *5V* peripherals: their *GPIOs* are *5V* tolerant.

In a nutshell, if you *today* think about onboarding the microcontroller hobby, look right away into the *ESP32* family of microcontrollers, and use [platformio](https://platformio.org/) (or even better yet, [ESPHome](https://done.land/tools/software/esphome)) rather than the stale *ArduinoIDE*.


> [!TIP]
> Most example code runs equally well on *ESP32* microcontrollers and often just requires some adjustments to the *GPIO pin numbers*. 

### Recommendations

If you are determined to use an *Arduino*, get two or three cheap *Arduino Nano Clones* (avoid the heavily overpriced originals): *Arduino Nano Clones* are reasonably priced, provide a lot of *GPIOs* to play with, have a *small form factor*, and are *breadboard-friendly*. They are also *compatible* to most of the *Arduino examples* out there for a worry-free experience.

*Arduino Uno* is completely outdated, whereas newer boards such as *Arduino Every*, *Arduino Nano ESP32*, *Arduino Uno R4*, and others lack compatibility and ease-of-use: they often no longer "just work" and  require extra configuration and code adjustments. 

## [ESP32](https://done.land/components/microcontroller/families/esp)
*Espressifs* line of *ESP32* microcontrollers today is the best choice for *general purpose microcontroller projects*: 

They are cheap (they are not exclusively produced for hobbyists but are a smart home industry standard, often found inside commercial smart devices - mass production drops cost). They support *WiFi* out-of-the-box (most models also *Bluetooth*), today typically come with *16MB flash memory*, and can be used with *ArduinoIDE* and *platformio*.

*ESP32* are insanely fast, many models using *dual core* concepts. They also come with *RTOS* (*real time operating system*) built-in, so advanced programmers can easily create true *multi-tasking firmware*. They also feature efficient *deep sleep* modes and a low-power *real time clock*, making this microcontroller suited for battery- or solar-operated devices.

*ESP32* have been around since *2016*: the number of examples and tutorials is comparable to *Arduino*.

> [!TIP]
> One great advantage of *ESP32* microcontrollers is that they can be used with [ESPHome](https://done.land/tools/software/esphome) (a much easier-to-use programming concept than writing C++ code), and integrate with [Home Assistant](https://done.land/tools/software/homeassistant). 

### Recommendations

For a most worry-free experience, stick to the original *ESP32* microcontrollers (also called *ESP32S*, *WROOM*, or *WROVER*): they have been around for the longest time and provide the best compatibility and most examples.

Here are some other *ESP32 models* worth looking at:

* **Super Small - ESP32-C3:** If you are looking for an especially small footprint, look into [ESP32-C3 SuperMini](https://done.land/components/microcontroller/families/esp/esp32/c3/c3supermini). These are just as worry-free and very cheap (less that €2).
* **Super Many GPIOs - ESP32-S2:** a true bargain with a massive 27 *GPIOs* is the *single-core* [ESP32-S2 Mini](https://done.land/components/microcontroller/families/esp/esp32/s2/s2mini), also often available for under €2. This board is *pin-compatible* with the popular *Wemos D1 Mini (ESP8266)* and can use the same *shields*, i.e. for supplying rechargeable battery power. The *S2 Mini* is not perfectly suited for *beginners* though: it has a [strange USB port implementation](https://done.land/components/microcontroller/families/esp/esp32/s2/s2mini#strange-usb-design) that can require workarounds before you can upload new firmware.

The *ESP32 family* is constantly growing. Latest models such as *ESP32-C6* or *ESP32-H2* target new *wireless technologies* such as *Matter* or *Thread*, but are not yet fully supported by many development environments and code examples. You typically have to program them using the *Espressif* framework, and cannot use *Arduino code*. That's why you should avoid these unless you really need their unique selling points.

> [!IMPORTANT]
> **Do not** purchase *ESP8266* anymore. They are outdated, considered *unsafe* (no *https* support), and cost just about as much as *ESP32*.



## [ATTiny](https://done.land/components/microcontroller/families/attiny)

If you need a microcontroller to just *control hardware* and *sensors* in very *space-constrained* environments and with **extremely low** *energy consumption*, then *ATtiny* is a good way to go.

### Very Small

These microcontrollers often do not come on *development boards*. To program them, you need a separate *programmer board* where the microcontroller is temporarily plugged in.

*ATTiny* microcontrollers are *exceptionally expensive* when comparing their capabilities to other microcontroller families, and their computational power, number of *GPIOs*, and memory is very limited.

### Very Battery-Efficient

They shine when it comes to *power consumption*: running at a clock speed of *1MHz*, the *ATTiny85* consumes less than *2mA* (compared to *130mA* for an *ESP32* with *WiFi*). If you use the microcontroller in *watchdog mode* and wake it up only occasionally, i.e. to take some sensor readings, it consumes just *5uA* in standby (compared to 200-900uA in *ESP32 deep sleep* for typical development boards). 

## [Raspberry Pi](https://done.land/components/microcontroller/families/raspberry)

*Raspberry Pis* are also popular DIY microcontrollers, although these really are *CPUs*, and they are used for running *real operating systems*, much similar to classic PCs.

> [!NOTE]
> *Raspberry Pis* are not to be confused with *Raspberry RP2040* (which is the first microcontroller produced by *Raspberry*). The *RP2040* is comparable to *ESP32* and targets small devices.


*Raspberry Pi 5* is the latest *Raspberry Pi* and compared to its predecessors, it is much more powerful. It can be used as an *always on server*, running *Linux* or [Home Assistant](https://done.land/tools/software/homeassistant).

### Recommendations
Use *Raspberry Pi 5* to *complement* your *microcontrollers*, and operate an efficient *always-on* server.

Some argue that a *Mini PC* would be much more powerful than a *Raspberry Pi 5* at almost the same cost, but that is not true: the unique selling point for a *Raspberry Pi 5* is its **ultra low power consumption**. 

When you run a *Mini PC* plus *virtualization software*, computing power is much higher, but so is your electricity bill. The difference can quickly be a few hundred Euros per year. 

* **Simple Server:** if all you need is operating a simple server or *Home Assistant*, then use *Raspberry Pi 5* with *SSD hard drive*. It's the most efficient solution with the lowest *TOC* (total cost of ownership). For this use case, running a *Mini PC* would be overkill, and the *Mini PC* would idle most of the time while burning electricity.
* **Heavy Duty Server:** if your requirements are much higher, and you'd like to run a multitude of services and/or servers, then pick a classic *computer* or *mini-PC*, and use virtualization software on it.

> Tags: Microcontroller, Guidance, Select, Arduino, ESP32, ESP8266, ATtiny, Raspberry Pi

[Visit Page on Website](https://done.land/components/microcontroller/families?358952051123244751) - created 2024-05-22 - last edited 2024-05-22
