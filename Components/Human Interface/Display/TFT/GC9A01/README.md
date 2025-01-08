<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# GC9A01

> Drives TFT Displays Up To 240x240 Pixels At 262K Colors (18bit)

The *GC9A01* is a versatile *TFT display driver IC* commonly used for **square or round displays** (equal height and width) with resolutions of up to *240x240* pixels at full *18bit color* (262 thousand different colors). 

Its low power consumption and sleep mode make this driver ideal for medium or small size portable products such as digital cellular phones, smart phone, MP3 and PMP where long battery life is a major concern

## Overview
This driver is used by many square and round *TFT display boards* up to a resolution of *240x240*. This includes the popular *watch-like* shaped round displays.


<img src="images/tft_round_1.26_overview_t.png" width="70%" height="70%" />

The driver supports [SPI](https://done.land/fundamentals/interface/spi) and the *Parallel* interface, as well as some lesser-used options. In typical applications, it is controlled via *SPI*.
| Item | Description |
| --- | --- |
| Maximum Resolution | *240(H)x240(V)* pixels |
| Supported Resolutions | *80x160*, *120x120*, *128x128*, *160x160*, *240x240* |
| Maximum Color Depth | *18bit* (262K) |
| Reduced Color Mode | Yes, *3bit* (*8 colors*) |
| Source and Gate Lines | 360/32 |
| Memory | *129,600 bytes GRAM* |
| Voltage | *2.5-3.3V* |
| Power Consumption | *14mA* (with backlight) |
| Sleep-In Power Consumption | In the range of *uA* (no exact value in datasheet) |
| Sleep Command | *0x10* (enter), *0x11* (exit) |
| Interface | [SPI](https://done.land/fundamentals/interface/spi) and *Parallel* |

## Power Saving
In battery-operated devices or other environments where low power consumption is a priority, the *GC9A01* driver supports multiple power-saving modes. These modes reduce power consumption in five stages:

1. **Partial Mode:** A part of the display is used with a maximum of 262,144 colors.
2. **Idle Mode:** The full display is used with reduced colors (8 colors).
3. A combination of **Partial Mode** and **Idle Mode**.
4. **Sleep Mode:** The DC-DC converter, internal oscillator, and panel driver circuit are stopped. The MCU interface and memory continue to operate, and the contents of the memory are preserved.
5. **Power Off:** Both *VCI* and *IOVCC* are cut off, meaning there is no communication with the driver and memory is lost.

### Strategies
For many applications, using the *8-Color Mode* is sufficient (e.g., indicator displays that only need a few colors) to reduce power consumption during normal operation.

If the driver is used with displays that do not use the maximum resolution, *Partial Mode* can turn off areas of the display that are not in use.

Before sending your microcontroller to deep sleep, issue command *0x10* to put the display driver into its own sleep mode. The content currently displayed will remain visible on the screen. Command *0x11* will wake the display (if necessary).

> [!IMPORTANT]
> It is [extremely important to manually send the display driver to its sleep state](https://community.home-assistant.io/t/esp32-c3-with-integrated-gc9a01-cheap-touch-controller/610314/106?page=6) **before** putting the microcontroller into deep sleep. When the display is in sleep mode, typical deep sleep consumption of the system will be in the *uA* range. Without putting the display to sleep, its power consumption will be in the *10-20mA* range.

## Programming

### ESPHome Support

In [March 2024](https://github.com/esphome/esphome/pull/6351), *ESPHome* added long-requested support for the *GC9A01* to the official [ILI9xxx TFT LCD Component](https://esphome.io/components/display/ili9xxx.html). Now, you no longer need external code or libraries for this display driver.

The [ILI9xxx component](https://esphome.io/components/display/ili9xxx.html), originally intended for *ILI9xxx* drivers (as the component name suggests), has expanded over the years to support a wide range of TFT drivers. As a result, this component now provides interchangeable support for various TFT displays, including the *GC9A01*.

This is particularly beneficial, as it makes *ESPHome configurations* compatible with a broad range of TFT displays.

> [!NOTE]
> At the time of writing, *ESPHome* documentation does not yet explicitly list *GC9A01* as being supported by their [ILI9xxx component](https://esphome.io/components/display/ili9xxx.html).

### PlatformIO/Arduino Support

[Adafruit](https://www.adafruit.com/) offers a free [Adafruit library for GC9A01 drivers](https://github.com/adafruit/Adafruit_GC9A01A), and the *GC9A01* driver is also supported by the [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library.


> Tags: Display Driver, Resolution, 

