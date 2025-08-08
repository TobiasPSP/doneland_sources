<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP8266

> Outdated (But Still Useful) General-Purpose WiFi-Enabled Microcontroller For Simple Projects And Education

The *ESP8266* from *Espressif* was probably the most widely used *microcontroller* in non-Arduino projects at one time. 

It became an instant success when it surfaced in 2014 and initiated the decline of the Arduino dominance at that time.

The *ESP8266* was remarkably affordable and outperformed *Arduino* boards in almost every aspect at a fraction of the cost.

<img src="images/esp8266_usbc_top_front_t.png" width="50%" height="50%" />

* **Memory:** with *4MB* flash memory (typical), the *ESP8266* ended the notoriously scarce memory that Arduino users fought with back then
* **WiFi:** built-in *WiFi* support opened the doors for home automation and web interfaces while *Arduino* users were stuck with boring and wired terminal communication.
* **Size:** the *ESP8266* had a significantly smaller footprint, enabling users to build slick portable devices.
* **Cost:** *ESP8266* was available at a fraction of the price compared to *Arduino boards*, and even cheaper *Clones* were available thanks to the open-source board designs.

Today, more than a decade after its release, *ESP8266* is **retired** for good, though, and there is no reason anymore to buy new *ESP8266* boards.

While you can certainly use up your stocked *ESP8266* for small projects, consider the [ESP32-S2 Mini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/s2mini/) (if you want to use the same form factor and maintain compatibility with shield boards), or [ESP32-C3 SuperMini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/c3supermini/) (for an extremely affordable board with a super small form factor).

## Overview

The *ESP8266* was the first *Espressif* microcontroller with broad success in the DIY community, primarily because of its affordability and built-in WiFi. 

Many users moved from *Arduino* to *ESP8266*, and in the end, generic *ESP8266* boards were available for under €1.00.

<img src="images/esp32_family1_t.png" width="100%" height="100%" />

Today, do not buy *ESP8266* anymore:

* **Design Flaws:** Most *ESP8266* development boards—at least affordable generic ones—come with *underrated voltage regulators*: unexpected brown-outs and reboots occur when external components like sensors or displays exceed the voltage regulator's maximum current.
* **Unsafe:** *ESP8266* is single-core, and compared to its successors, relatively slow. It cannot use secure *https* connections when connecting to *WiFi* and the Internet. Instead, it uses the unencrypted old *http* standard.
* **Expensive:** Today, the much more capable successors cost just as much as *ESP8266* (sometimes even less), which makes *ESP8266* appear expensive in comparison. You get much less bang for the buck.
* **Features:** *ESP8266* has **less of everything** when compared to its successors: fewer GPIOs, less speed, less memory, less safety, less reliability, etc.

### Key Specs

| Item         | Value         | Comment                                             |
|--------------|--------------|-----------------------------------------------------|
| GPIO         | 17           | Actually available pins depend on breakout board    |
| SPI          | 1            | For fast peripherals                                |
| I2C          | 1            | Software implementation, for slow peripherals       |
| UART         | 1            | Serial communications, external serial-to-USB chip required for USB |
| Flash Memory | 4MB (typical)| Boards range from 512K to 16MB                      |

### UART: CH9102, CP210x, CH340

**ESP8266** do not natively support USB, so they need a dedicated UART chip, plus *you* may need the appropriate driver installed on your PC.

Here is an overview of popular chips and whether they are natively supported on your PC operating system:

| Item        | CH210x | CP9102 | CH340   | Remarks                                 |
|-------------|--------|--------|---------|-----------------------------------------|
| OS          | all    | all    | Windows | Other OS may need manual driver install |
| Price       | medium | medium | low     |                                         |
| Speed Mbps  | 12     | 4      | 2       |                                         |

> [!NOTE]
> The *CP9102* is a relatively unknown variant that is pin-compatible with the *CH210x*. It is slower but still twice as fast as the *CH340*.

There are other chip types such as *FT232RL*, *PL2303*, *MCP2221*, and *MAX3421* that are even less commonly found.

## D1 Mini

The **D1 Mini** was probably the most popular ESP8266 development board: 

It was *affordable*, *compact* and *flat*, came with *WiFi* capabilities, had sufficient *memory* (typically 4MB), provided sufficient *GPIO* pins for most projects (9 of which 5 were freely usable), had one *ADC*, and supported *SPI* and *I2C* interfaces.

<img src="images/esp8266_angleback_t.png" width="60%" height="60%" />

It used the *Espressif ESP8266EX* chip, basically the only *ESP8266* variant widely found.

The *D1 Mini* board was so popular that a whole ecosystem of pin- and size-compatible "shield boards" became available (i.e. power supplies, battery boards, sensor extensions, etc.).

Today, the [ESP32-S2 Mini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/s2mini/) has **preserved the D1 Mini form factor** and is **pin-compatible**, so you can continue to use the shield boards that were originally designed for the *ESP8266 D1 Mini*.

### ESP8266 Pro

The **Pro** version of **ESP8266** never gained traction. Its most visible "advantage" was a *ceramic antenna* instead of the simple *PCB antenna* and more memory: most **ESP8266 Pro** came with *16MB* instead of *4MB* memory (some just 8MB or even 4MB).

<img src="images/esp8266_mini_pro_front_unsharp_t.png" width="60%" height="60%" />

This board used an *unshielded* version of **ESP8266** that has no *FCC ID* (may violate EMR standards and FCC regulations). It typically used the same insufficient *voltage regulator* that was found on other cheap **ESP8266 clones**.

> Tags: Microcontroller, ESP8266, Clone, Power Regulator, Espressif, D1 Mini, USB-to-Serial, WiFi, Arduino, CP210x, CH340, CH9102, FT232RL, PL2303, MCP2221, MAX3421

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp8266?549965031823244200) - created 2024-03-23 - last edited 2025-08-03
