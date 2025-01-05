<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Microcontroller Families

> How To Select The Right Microcontroller For Your Project

If you are completely new to microcontrollers, your first important decision is selecting the type of microcontroller you want to use.

There are many *microcontrollers* and *boards* available for *DIY projects*, each with its own strengths and shortcomings. In this section, we provide guidance on selecting the best *microcontroller type* for a given task.

## Overview

Most hobbyists associate the term *Arduino* with DIY microcontrollers. This is because the company *Arduino* deserves credit for making microcontrollers accessible to the general public. When the first *Arduino* development board hit the market, it revolutionized the way people viewed microcontrollers, offering simple-to-use kits, good documentation, and an intuitive IDE (*integrated development environment*).

That was twenty years ago, though. Since then, much has changed and improved. Today, an ever-growing number of hobbyists are turning to microcontrollers from the [ESP32 family](https://done.land/components/microcontroller/families/esp/esp32/) and using affordable, generic development boards. These are just as easy to use as *Arduinos* were in their early days. However, *ESP32* and its successor models are much more powerful, offering *WiFi* and *Bluetooth* capabilities at a fraction of the cost.

Still, determining the "best hobbyist microcontroller model" is a personal and often highly emotional debate. To help, I have summarized all the popular microcontroller ecosystems in more detail below.

> [!NOTE]
> Most of the microcontrollers listed below can be programmed using the same tools, programming languages, and libraries. This is an important point to note. Today, choosing a microcontroller model is primarily a question of hardware, not software.
## [Arduino](https://done.land/components/microcontroller/families/arduino)

[Arduinos](https://done.land/components/microcontroller/families/arduino) first emerged in 2005, opening up microcontrollers to hobbyists and DIY makers. *Arduinos* are *open-source* board designs that use a variety of microcontrollers. They are simple to program, and the *Arduino IDE* is a free, pragmatic coding editor. Given the long time that *Arduinos* have been around, you'll find a wealth of tutorials and code examples. In the past, *Arduinos* were the #1 choice for beginners. However, that has changed somewhat over time.

### Considerations

If you're thinking about using an *Arduino*, here are some critics pointed out by users:

* **Expensive:** Original *Arduinos* are significantly overpriced. Since their board design is *open-source*, many affordable *clones* are available from *Chinese companies* on *AliExpress*. These clones often cost less than *10%* of the price of an original board.
* **Slow:** Many *Arduino boards* use outdated and slow *ATmel* microcontrollers. While they can handle simple tasks, they are much slower compared to other modern microcontrollers and boards.
* **No WiFi:** Most *Arduinos* do not include wireless technology by default. While they can function as stand-alone solutions, they require expensive add-ons to enable remote control or smartphone connectivity.
* **Compatibility:** Although there are numerous free tutorials and resources for *Arduinos*, their once-reliable *compatibility* has diminished. As *Arduino* introduced new models with different designs, you may encounter compatibility issues. Code written for older *Arduinos* may not work on the newer boards.
* **Memory:** Most *Arduinos* come with limited memory. They work well for small projects, but as your projects grow larger, you'll encounter memory limitations, compilation errors, and possible instability.
* **Power:** Most *Arduinos* are **5V** devices, meaning they can't use *3.3V peripherals* and are not particularly power-efficient. Battery-operated projects may not last long. In contrast, modern microcontrollers like the *ESP32* family are **3.3V** operated, which means they can be powered directly from a *LiFePO₄* battery. They can also be powered by *5V* (boards with integrated voltage regulators), supporting both *3.3V* and *5V* peripherals. Additionally, their *GPIOs* are *5V* tolerant.

In summary, if you're considering starting out with microcontroller-based projects today, look into the *ESP32* family of microcontrollers right away. Consider using [PlatformIO](https://platformio.org/) (or better yet, [ESPHome](https://done.land/tools/software/esphome)) instead of the outdated *Arduino IDE*.

> [!TIP]
> Most example code works equally well on *ESP32* microcontrollers and often only requires adjustments to the *GPIO pin numbers*.

### Recommendations

If you're set on using an *Arduino*, I recommend getting two or three affordable *Arduino Nano Clones* (avoid the overpriced originals). *Arduino Nano Clones* are reasonably priced, offer many *GPIOs* to experiment with, have a *small form factor*, and are *breadboard-friendly*. They're also compatible with most *Arduino examples*, providing a worry-free experience.

The *Arduino Uno* is now outdated, while newer boards like the *Arduino Every*, *Arduino Nano ESP32*, and *Arduino Uno R4* lack compatibility and ease of use. These newer models often require extra configuration and code adjustments to function properly.


## [ESP32](https://done.land/components/microcontroller/families/esp)

*Espressif's* line of *ESP32* microcontrollers is currently the best choice for *general-purpose microcontroller projects*:

They are affordable (not exclusively produced for hobbyists but are a standard in the smart home industry, often found inside commercial smart devices, which drives down the cost due to mass production). They come with *WiFi* support out-of-the-box (most models also include *Bluetooth*), typically include *16MB flash memory*, and are compatible with both *Arduino IDE* and *PlatformIO*.

*ESP32* microcontrollers are incredibly fast, with many models featuring *dual-core* processors. They also come with a built-in *RTOS* (*real-time operating system*), allowing advanced programmers to create true *multi-tasking firmware*. Additionally, they feature efficient *deep sleep* modes and a low-power *real-time clock*, making them ideal for battery- or solar-powered devices.

*ESP32* has been around since *2016*, so the number of examples and tutorials is on par with *Arduino* or even better now. Many highly popular community projects like [WLED](https://done.land/components/microcontroller/firmware/fromsomeoneelse/wled/) (controlling LED strips and matrix panels) or [CO2-Gadget](https://done.land/components/microcontroller/firmware/fromsomeoneelse/co2gadget/) provide ready-to-use firmware exclusively for *ESP32*. If you are still using *Arduinos*, you'd miss out.

> [!TIP]
> Another **huge** advantage of *ESP32* microcontrollers is that they can be used with [ESPHome](https://done.land/tools/software/esphome), which offers a much easier programming concept than writing C++ code, and integrates seamlessly with [Home Assistant](https://done.land/tools/software/homeassistant). This indicates that *ESP32* has been adopted by the professional community much more than *Arduinos*.

### Recommendations

For a worry-free experience, stick to the original *ESP32* microcontrollers (also called *ESP32S*, *WROOM*, or *WROVER*). These have been around the longest, offer the best compatibility, and have the most examples and resources available.

Here are some other *ESP32 models* along with some development boards worth considering:

* **Super Small - ESP32-C3:** If you need a very small footprint, check out the [ESP32-C3 SuperMini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/c3supermini/). It's affordable (less than €2) and just as reliable as other *ESP32* models.
* **Super Many GPIOs - ESP32-S2:** The *ESP32-S2 Mini* is a true bargain, offering a massive 27 *GPIOs* in a *single-core* design. Available for under €2, this board is *pin-compatible* with the popular *Wemos D1 Mini (ESP8266)*, meaning it can use the same *shields* (such as those for supplying rechargeable battery power). However, the *S2 Mini* is not ideal for *beginners* due to a [strange USB port implementation](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/s2mini/#strange-usb-design) that may require workarounds before you can upload new firmware.

The *ESP32 family* is constantly growing. New models such as *ESP32-C6* or *ESP32-H2* target new *wireless technologies* like *Matter* or *Thread*, but they are not yet widely supported by many development environments and code examples. You will typically need to program these models using the *Espressif* framework and cannot use *Arduino code*. Therefore, unless you really need their unique features, it’s better to avoid them for now.

> [!IMPORTANT]
> **Better not** purchase [ESP8266](https://done.land/components/microcontroller/families/esp/esp8266/) anymore. They are outdated, considered potentially *unsafe* (lacking *HTTPS* support), and cost about the same as *ESP32*. If you still have some *ESP8266* at hand, it is ok to continue to use them of course.

## [ATTiny](https://done.land/components/microcontroller/families/attiny)

If you need a microcontroller for controlling hardware and sensors in very *space-constrained* environments with **extremely low** *energy consumption*, then *ATtiny* is a great option.

### Very Small

*ATtiny* microcontrollers often do not come on *development boards*. To program them, you'll need a separate *programmer board* where the microcontroller is temporarily plugged in.

Compared to other microcontroller families, *ATtiny* microcontrollers are *exceptionally expensive* given their capabilities. Their computational power, number of *GPIOs*, and memory are very limited.

### Battery-Efficient

Where *ATtiny* microcontrollers truly excel is in *power consumption*. Running at a clock speed of *1MHz*, the *ATTiny85* consumes less than *2mA* (compared to *130mA* for an *ESP32* with *WiFi*). If used in *watchdog mode* and only waking up occasionally (e.g., to take sensor readings), it consumes just *5uA* in standby—significantly lower than the *200-900uA* in *ESP32 deep sleep* for typical development boards.

## [Raspberry Pi](https://done.land/components/microcontroller/families/raspberry)

*Raspberry Pis* are popular DIY microcontrollers, though they are technically *CPUs* and are designed to run *real operating systems*, much like classic PCs.

> [!NOTE]
> *Raspberry Pis* should not be confused with the *Raspberry RP2040*, which is the first microcontroller produced by *Raspberry Pi*. The *RP2040* is comparable to the *ESP32* and targets small devices.

*Raspberry Pi 5* is the latest *Raspberry Pi* model, and compared to its predecessors, it is significantly more powerful. It can be used as an *always-on server*, running *Linux* or [Home Assistant](https://done.land/tools/software/homeassistant).

### Recommendations

Use the *Raspberry Pi 5* to *complement* your *microcontrollers* and operate an efficient *always-on* server.

Some argue that a *Mini PC* would be much more powerful than a *Raspberry Pi 5* at almost the same cost, but this is not true. The unique selling point of the *Raspberry Pi 5* is its **ultra-low power consumption**.

When you run a *Mini PC* with *virtualization software*, the computing power is much higher, but so is your electricity bill. The difference can quickly add up to a few hundred Euros per year.

* **Simple Server:** If all you need is to operate a simple server or *Home Assistant*, use the *Raspberry Pi 5* with an *SSD hard drive*. It offers the most efficient solution with the lowest *total cost of ownership* (TOC). For this use case, running a *Mini PC* would be overkill, and the *Mini PC* would idle most of the time while consuming unnecessary electricity.
* **Heavy Duty Server:** If your requirements are much higher and you need to run a multitude of services and/or servers, then choose a classic *computer* or *mini-PC* and use virtualization software on it.

## Others

There are many more microcontroller models to choose from, though they are less popular. For example, the *NRF52840* excels in low power consumption and *Bluetooth Low Energy* (BLE) support (ideal for battery-operated DIY devices), while the *RP2040* is the first dedicated microcontroller designed by the *Raspberry Pi ecosystem*.

These microcontrollers definitely have their place, but if you're just getting started, it's best to choose between the *Arduino Nano* and one of the many *ESP32S* boards for the reasons mentioned earlier.


> Tags: Microcontroller, Guidance, Select, Arduino, ESP32, ESP8266, ATtiny, Raspberry Pi

[Visit Page on Website](https://done.land/components/microcontroller/families?358952051123244751) - created 2024-04-22 - last edited 2024-05-22
