<img src="/assets/images/processor.png" width="80%" height="80%" />

 
# S3

> Modern Successor of ESP32S

The ESP32-S3 is the modern successor to the [ESP32S](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/), offering more power and features. 

Compared to the original ESP32, the S3 removes some rarely used features (like the Hall Sensor and DAC) to provide more GPIO pins, a temperature sensor, and BLE 5.0 support. It also introduces new features such as AI acceleration, more ADC channels, more touch inputs, and USB OTG. 

Some resources like SRAM and ROM are slightly reduced, but overall, the S3 is a more capable and versatile chip designed for advanced applications.


## Overview

The *ESP* family of microcontrollers has grown quite large and has become somewhat confusing. So here is a quick overview to help you relate the *ESP32-S3* to other ESP family members:

| Microcontroller | Remark | Successor |
| --- | --- | --- |
| [ESP8266](https://done.land/components/microcontroller/families/esp/esp8266/) | Single-Core Simple MCU, many users transitioned to this MCU from *Arduino* | [ESP32-C3](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/), [ESP32-S2](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/) |
| [ESP32S](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/) | Powerful Two-Core MCU, has become DIY default for many projects | **ESP32-S3** |

For general tasks, the *ESP32-S3* speed is similar to *ESP32S*.

## Upgrade Path

It is always wise to keep some *ESP8266* and *ESP32S* to stay compatible with the older projects and sample codes that were developed for these two MCUs.

However, for new projects - regardless of whether you used *ESP8266* or *ESP32S* before - it makes sense to look at transitioning to the more modern variants:

* [ESP32-C3](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/), [ESP32-S2](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/): most simple projects, very cost-efficient and small
* **ESP32-S3:** projects that would previously have used a [ESP32S](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/), i.e. use cases that require higher computational power such as camera projects.

To help decide whether the classic *ESP32S* or the newer *ESP32-S3* is right for you, here is a table with the key differences:

| You need... | ESP32S | ESP32-S3 | 
| --- | --- | --- |
| more GPIOs |  | ✅ (from 34 to 45 with 2 additional analog inputs, actually usable GPIOs depends on development board design) |
| more speed |  | ✅ (when computational demanding) |
| camera support | | ✅ |
| lower energy |  | ✅ (slight advantage) |
| support for Bluetooth Classic | ✅ | |
| support for BLE 5.0 | | ✅ |
| built-in DAC | ✅ | |
| support for USB devices | | ✅ |
| compatibility to older projects/example code | ✅ | |

Neither one comes with modern *Thread* wireless radio (802.15.4). Currently the only ESP microcontroller that natively supports 802.15.4 (required for *Thread* and *Zigbee*) is the *ESP32-H2*.

## Limitations
Some useful features found in *ESP32S* have been removed in *ESP32-S3*. Here are the key differences: 

| Feature | Removal |
| --- | --- |
| Size  | 7x7 instead of 5x5 |
| SRAM  | reduced from 520 to 512 |
| ROM | reduced from 448 to 384 |
| Bluetooth | no longer supports *Bluetooth Classic*, just *BLE* |
| LED PWM | reduced from 16 to 8 |
| DAC | ❌ |
| SD Slave | ❌ |
| Hall Sensor | ❌ |
| Ethernet | ❌ |

## New Features

*ESP32-S3* introduces these key improvements (compared to *ESP32S*):

| Feature | Addition |
| --- | --- |
| Bluetooth | BLE 5.0 instead of BLE 4.2 (**but no support for Bluetooth Classic anymore**) |
| ADC | 18 instead of 20 |
| Touch | 14 instead of 10 |
| Temperature Sensor | ✅ (but just for the MCU temperature, not environmental) |
| GPIO | 45 instead of 34 |
| SD Host | 2 instead of 1 (no SD Slave support anymore) |
| USB OTG | ✅ |

### Camera Support
Traditionally, *ESP32S* has often been used with camera modules, implementing surveillance systems and face recognition.

The *ESP32-S3* - while running at comparable clock rates - improves these use cases significantly. Its *AI Acceleration Support* improves a wide range of computational tasks, allowing for more efficient image manipulation, edge detections, face recognition, and related AI-based tasks. 

In addition, The **ESP32-S3** features dedicated hardware support for parallel camera interfaces, specifically the *DVP* (*Digital Video Port*) interface. This allows the S3 to connect directly to camera modules (like the *OV2640* or *OV7670*) using an 8-bit parallel data bus, along with dedicated pins for pixel clock (PCLK), horizontal sync (HREF), and vertical sync (VSYNC).

The *ESP32S* can connect to cameras using its *I2S* peripheral in parallel mode, but this is a workaround and not a dedicated camera interface. It is less efficient, can be more complex to implement, and is limited by the number of available GPIOs and the lack of hardware acceleration for camera data. As a result, the ESP32S typically supports lower frame rates and resolutions for camera applications, and the CPU is more heavily loaded during image capture.


## Detailed Comparison

| Feature            | ESP32S                                   | ESP32-S3                                 |
|--------------------|------------------------------------------|------------------------------------------|
| **CPU**            | Dual-core Xtensa LX6 @ 240 MHz           | Dual-core Xtensa LX7 @ 240 MHz           |
| **SRAM**           | 520 KB                                   | 512 KB                                   |
| **ROM**            | 448 KB                                   | 384 KB                                   |
| **Power Consumption** | ~20 µA (deep sleep), ~80-260 mA (active Wi-Fi) | ~20 µA (deep sleep), ~80-240 mA (active Wi-Fi, more efficient sleep modes) |
| **Wi-Fi**          | 802.11 b/g/n                             | 802.11 b/g/n                             |
| **Bluetooth**      | v4.2 (Classic + BLE)                     | v5.0 (BLE only, no Classic)              |
| **GPIO**           | 34                                       | 45                                       |
| **ADC Channels**   | 18                                       | 20                                       |
| **Touch Inputs**   | 10                                       | 14                                       |
| **AI Acceleration**| No                                       | Yes (vector instructions)                |
| **USB OTG**        | No                                       | Yes                                      |
| **Temperature Sensor** | No                                   | Yes                                      |
| **DAC**            | Yes (2 channels)                         | No                                       |
| **Hall Sensor**    | Yes                                      | No                                       |

## Recommendation

* **ESP32-S3:** more GPIO, improved BLE (v5.0), USB OTG, slightly lower power consumption, and better AI/vector processing. 

* **ESP32S:** support for *Bluetooth Classic*, built-in *DAC*, Hall sensor. Ideal for maximum compatibility with older projects and libraries. It’s still a solid choice for many existing designs.

> [!TIP]
> For most **new** projects, *ESP32-S3* is recommended. *ESP32S* is the better choice if you'd like to use projects or firmware originally developed for *ESP32S* although many source code can be adjusted to *ESP32-S3* with little effort.

> Tags: Microcontroller, ESP32, S3, ESP32-S3

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s3?530017031823244200) - created 2024-03-23 - last edited 2025-08-02
