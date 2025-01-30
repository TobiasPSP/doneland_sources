<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# Writing C++ Code for Displays

> Using a Classic IDE Like Arduino IDE or PlatformIO to Write Firmware That Controls Displays

Using a classic *IDE* and writing your own firmware to control a display is simple and straightforward, thanks to excellent libraries that provide easy access to display hardware.

## Overview

The key to programming a display with *C++* is finding and understanding a good *library* that is compatible with your specific display.

### Display Driver

Your software does not interact directly with the display hardware but rather with the display *driver* it uses. To find the right library, you need to determine the name of the driver your display is based on.

If you don't know the driver:

1. Identify the display *type* first (e.g., *TFT*, *OLED*, *e-Ink*, *LCD*).  
2. Visit the appropriate sections: [TFT](https://done.land/components/humaninterface/display/tft/), [OLED](https://done.land/components/humaninterface/display/oled/). Each section lists commonly used drivers, such as the [ILI9341](https://done.land/components/humaninterface/display/tft/ili9341/), the more modern [ST7789](https://done.land/components/humaninterface/display/tft/st7789/), or widely used monochrome OLED drivers like [SH1106](https://done.land/components/humaninterface/display/oled/sh1106/) and the older but more capable [SSD1306](https://done.land/components/humaninterface/display/oled/ssd1306/).
3. Each driver section includes a list of *display boards* that use that driver. Browse through them until you find a match for your display board.

## Choosing the Right Display Library

Finding the best library for your display may seem overwhelming at first due to the sheer number of options available.

### Avoid Cloned Libraries

One reason for this abundance of libraries is that users frequently *clone* well-established libraries to make minor adjustments or add specific features for their projects. These modified versions (*forks*) often become outdated and are not actively maintained.

For long-term reliability and access to updates, always prioritize the *original* library from its primary author. The original developers are typically committed to maintaining and improving their libraries over time, whereas cloned versions often remain as static snapshots with minor modifications.

### Choose a Library Based on Your Project Needs

Not all libraries follow the same approach. Different libraries offer unique design philosophies, optimizations, and trade-offs. Understanding these differences will help you select the most suitable library for your specific application.

Evaluate the strengths and weaknesses of each approach, consider how they align with your project goals, and make an informed decision.
### Universal Libraries

There are several *universal libraries* that support a wide range of displays:

- **Monochrome Displays:** [u8g2](https://github.com/olikraus/u8g2) supports a vast number of *monochrome* displays, including both *TFT* and *OLED*.
- **Color Displays:** [ucglib](https://github.com/olikraus/ucglib) provides support for numerous *color* displays, covering both *TFT* and *OLED* technologies.
- **TFT Displays:** [TFT-eSPI](https://github.com/Bodmer/TFT_eSPI) is optimized for *SPI*-based *TFT* displays, supporting both monochrome and color variants.

Using these libraries is straightforward: a single library can handle many different displays. If you decide to change your display hardware later, you typically only need to adjust the constructor or modify configuration settings, without rewriting large parts of your code.

### Specific Libraries

In contrast, *specific libraries* are designed to support a single display driver. These libraries are often easier to use because they are tailored specifically for your display, eliminating the need for extensive configuration.

However, the main drawback of *specific* libraries is that they lock your code into a particular display model. If you later switch to a different display, you may need to rewrite significant portions of your code.

To address this issue, *Adafruit* introduced a smart approach: it provides *hardware-specific libraries* for all popular display drivers.


| Display Type         | Library Name & Link                                    | Supported Displays                                |
|----------------------|-------------------------------------------------------|-------------------------------------------------|
| OLED Displays        | [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) | 128x64 and 128x32 monochrome OLEDs             |
|                      | [Adafruit SH1106](https://github.com/adafruit/Adafruit_SH1106)   | SH1106-based OLEDs (e.g., 128x64 resolution)   |
| TFT and LCD Displays | [Adafruit ILI9341](https://github.com/adafruit/Adafruit_ILI9341) | ILI9341-based 320x240 TFT displays             |
|                      | [Adafruit ST7735 and ST7789](https://github.com/adafruit/Adafruit-ST7735-Library) | ST7735 and ST7789-based TFT displays           |
|                      | [Adafruit ILI9486](https://github.com/adafruit/Adafruit_ILI9486) | ILI9486-based TFTs, often 480x320 resolution   |
|                      | [Adafruit HX8357](https://github.com/adafruit/Adafruit_HX8357) | HX8357-based TFT displays                      |
| E-Paper Displays     | [Adafruit EPD](https://github.com/adafruit/Adafruit_EPD)       | Supports various ePaper (E Ink) displays       |
| Monochrome LCDs      | [Adafruit PCD8544](https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library) | Nokia 5110 LCDs (84x48)                        |
|                      | [Adafruit ST7565](https://github.com/adafruit/ST7565-LCD)      | ST7565-based graphic LCDs                      |
These libraries focus solely on display hardware and do not include high-level graphics functions for rendering text or drawing shapes.

All drawing functionality is handled by a separate *hardware-neutral* library: [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library).

Thanks to this modular approach, you can use *highly specific display driver libraries* that require minimal configuration while keeping your source code display-independent. If you later switch to a different display, you only need to replace the *hardware-specific* display library—your source code remains unchanged.

## Using `platformio`

[PlatformIO](https://platformio.org/) is a modern and highly capable development environment available as a free extension for [VSCode](https://code.visualstudio.com/), Microsoft's free code editor. It supports *Windows*, *Linux*, and *macOS*.

Compared to *Arduino IDE*, *PlatformIO* has a steeper learning curve but offers significantly more power and flexibility.

### Source Code Compatibility

*PlatformIO* generates standard *C++* source code, whereas *Arduino IDE* introduces custom leniencies and private rules that are not part of the *C++* standard. This can cause compatibility issues when using *Arduino IDE* code in *PlatformIO*, as is often the case with examples found online.

Fortunately, adapting *Arduino IDE* code for *PlatformIO* is straightforward. Once the necessary adjustments are made, *Arduino IDE* code runs seamlessly in *PlatformIO*.

#### Key Adjustments for Compatibility

- **Rename `.ino` to `.cpp`:**  
  *Arduino IDE* uses the `.ino` file extension (derived from *Ardu**ino***) for *C++ source files*, while the standard extension is `.cpp` (from *C++*). Simply rename your file to match this standard.

- **Explicitly include `Arduino.h`:**  
  *Arduino IDE* automatically includes `Arduino.h`, but in *PlatformIO*, you must add `#include <Arduino.h>` at the top of your code.

- **Ensure `setup()` and `loop()` exist:**  
  Both `setup()` and `loop()` must be defined. If `loop()` is unnecessary, define an empty function to prevent errors.

- **Correct function order:**  
  *Arduino IDE* allows calling functions before they are defined, but *PlatformIO* follows standard *C++* rules. Place `setup()` at the **bottom** of your code and ensure all functions are defined before they are called to avoid "undefined function" errors.


> Tags: Display, C++, Library, Programming, u8g2, ucglib, TFT_eSPI, Adafruit GFX

[Visit Page on Website](https://done.land/components/humaninterface/display/usage/programming/writingc++code?560674012023251935) - created 2025-01-22 - last edited 2025-01-22
