<img src="/assets/images/processor.png" width="80%" height="80%" />

 
# S3

> Modern Successor of ESP32S

The ESP32-S3 is the modern successor to the [ESP32S](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/).

Compared to the original ESP32, the S3 removes some rarely used features (like the Hall Sensor and DAC) to provide more GPIO pins, a dedicated camera interface, and BLE 5.0 support as well as AI acceleration, more ADC channels, more touch inputs, and USB OTG.

Some resources like SRAM and ROM are slightly reduced, but overall, the S3 is a more capable and versatile chip designed for advanced applications.

## Overview

The *ESP* family of microcontrollers has grown quite large and has become somewhat confusing. Here is a quick overview:

For general tasks, the *ESP32-S3* speed is similar to *ESP32S*. The *ESP32-S3* excels though with computation-heavy tasks due to its better math coprocessor.


### ESP32-S3 vs ESP32S


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

> [!TIP]
> Keep some *ESP8266* and *ESP32S* to stay compatible with the older projects and sample codes that were developed for these two MCUs, but 

## Limitations
Some useful features found in *ESP32S* have been removed in *ESP32-S3*:

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
| Digital Video Port | ✅ | 
| Touch | 14 instead of 10 |
| Temperature Sensor | ✅ (but just for the MCU temperature, not environmental) |
| GPIO | 45 instead of 34 |
| SD Host | 2 instead of 1 (no SD Slave support anymore) |
| USB OTG | ✅ |
| Math Coprocessor | significantly extended |


### Camera Support
Traditionally, *ESP32S* has often been used with camera modules, implementing surveillance systems and face recognition.

The *ESP32-S3*—while running at comparable clock rates—improves these use cases significantly. Its *AI Acceleration Support* improves a wide range of computational tasks, allowing for more efficient image manipulation, edge detections, face recognition, and related AI-based tasks.

In addition, the **ESP32-S3** features dedicated hardware support for parallel camera interfaces, specifically the *DVP* (*Digital Video Port*) interface. This allows the S3 to connect directly to camera modules (like the *OV2640* or *OV7670*) using an 8-bit parallel data bus, along with dedicated pins for pixel clock (PCLK), horizontal sync (HREF), and vertical sync (VSYNC).

The *ESP32S* can connect to cameras using its *I2S* peripheral in parallel mode, but this is a workaround and not a dedicated camera interface. It is less efficient, can be more complex to implement, and is limited by the number of available GPIOs and the lack of hardware acceleration for camera data. As a result, the ESP32S typically supports lower frame rates and resolutions for camera applications, and the CPU is more heavily loaded during image capture.

## Math Coprocessor
Both have a dedicated math coprocessor and built-in math acceleration, however the capabilities of *ESP32-S3* are much extended. This can lead to *significant* improvements for computational intense applications (speed, higher resolutions, better frame rates), i.e. *AI* or *cameras/image processing*:

| Feature                  | ESP32S (Xtensa LX6)                  | ESP32-S3 (Xtensa LX7)                      |
|--------------------------|--------------------------------------|--------------------------------------------|
| Math Coprocessor (FPU)   | ✅ (single-precision floating point)| ✅ (single-precision floating point)      |
| Vector Instructions      | ❌                                   | ✅ (for AI acceleration and SIMD math)    | |
| AI Acceleration          | ❌                                   | ✅ (dedicated vector extensions)          |
| Integer Performance      | ++                                 | ++++ (architectural enhancements)      |
| Floating Point Performance| ++                                | +++                          |
| Use Cases                | General math, DSP                    | General math, DSP, AI, Image Processing    |


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
| **Digital Video Port** | ❌ | ✅|
| **Touch Inputs**   | 10                                       | 14                                       |
| **AI Acceleration**| ❌                                       | ✅ (vector instructions)                |
| **USB OTG**        | ❌                                       | ✅                                      |
| **Temperature Sensor** | ❌                                   | ✅                                      |
| **DAC**            | ✅ (2 channels)                         | ❌                                       |
| **Hall Sensor**    | ✅                                      | ❌                                       |

## Recommendation

* **ESP32-S3:** more GPIO, improved BLE (v5.0), camera support, image processing, USB OTG, slightly lower power consumption, and better AI/vector processing.

* **ESP32S:** *Bluetooth Classic*, built-in *DAC*, Hall sensor. Maximum compatibility with older projects and libraries. Still a solid choice for many existing designs.



> Tags: Microcontroller, ESP32, S3, ESP32-S3, ESP32S, ESP32-C3, ESP32-S2, ESP32-H2, BLE, Bluetooth, USB, AI, Camera, Thread, Zigbee,
 
[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s3?530017031823244200) - created 2024-03-23 - last edited 2025-08-02
