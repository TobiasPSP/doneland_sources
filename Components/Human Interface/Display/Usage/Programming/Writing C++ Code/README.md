<img src="/assets/images/screenwire.png" width="100%" height="100%" />
# Writing C++ Code For Displays

> Using A Classic IDE Like ArduinoIDE Or platformio To Write Firmware That Controls Displays

Using a classic *IDE* and writing your own firmware that accesses a display is simple and straight-forward thanks to great libraries that you can use to access the display.

## Overview

The secret in programming a display with *C++* really is to find and understand a good *library* that is compatible with your display.

### Display Driver
Your software does not access the actual display but rather the display *driver* it uses. So in order to find the appropriate library, you need to know the driver name that your display uses.

If you don't know the driver:

1. Identify the display *type* first (i.e. *TFT*, *OLED*, *e-Ink*, *LCD*).  
2. Visit the appropriate sections: [TFT](https://done.land/components/humaninterface/display/tft/), [OLED](https://done.land/components/humaninterface/display/oled/). Each section lists commonly used drivers, i.e. the [ILI9341](https://done.land/components/humaninterface/display/tft/ili9341/), the more modern [ST7789](https://done.land/components/humaninterface/display/tft/st7789/), or the ubiquous monochrome OLED drivers like [SH1106](https://done.land/components/humaninterface/display/oled/sh1106/) or the older but more capable [SSD1306](https://done.land/components/humaninterface/display/oled/ssd1306/).
3. Beneath each driver, you find a list of *display boards* that use this driver. Browse through them until you discover your display board.

## Choosing Appropriate Display Libraries
Finding the best library for your display may seem overwhelming at first because there are so many. 

### Ignore Cloned Libraries
One reason for this flood of libraries is that users regularly *clone* a good existing library to adjust minor details or add features they need for their specific use cases. Ignore such knock-offs (*forks*), and focus on the *original* library authors. This also ensures that you always get the latest versions: the original authors are committed to their libraries, so they evolve over time. Cloned libraries often resemble a snapshot in time, spiced with some minor changes, that then typically are no longer maintained.

### Focus On Your Favorite Concept
A much more rewarding reason for library variations are different concepts and approaches. Understand the strengths and weaknesses of these concepts, identify how your project could benefit or be hurt by them, and then make an educated choice.


### Universal Libraries
There are a number of *universal libraries* that support a range of displays:

* **Monochrome Displays:** [u8g2](https://github.com/olikraus/u8g2) supports a vast number of *monochrome* displays, both *TFT* and *OLED*
* **Color Displays:** [ucglib](https://github.com/olikraus/ucglib) supports a vast number of *color* displays, both *TFT* and *OLED*
* **TFT Displays:** [TFT-eSPI](https://github.com/Bodmer/TFT_eSPI) supports a vast number of *TFT* displays that use *SPI*, both monochrome and color

Using such libraries is simple: one library serves many different displays, and when you decide to change a display, you do not need to change anything in your code except for using different constructors, or making configuration changes.




### Specific Libraries
Then there are *specific* libraries that target a single display driver only. Obviously, such libraries are more straight-forward to use since they already foocus on your specific display and its features. No need to find out how the library can be configured and tailored to your needs. 

On the down side, when you use *specific* libraries, your code becomes dependent on a specific display. If you later decide to use a different one, you need to rewrite large parts of your code.

That's why the company *Adafruit* came up with a great idea: it has released *hardware specific libraries* for all popular display drivers:


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

These libraries focus on the display hardware only and do not contain any high level graphics primitives that you would use to display text or draw shapes.

All the drawing functionality is located in another *hardware-neutral* library: [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library). 

Thanks to this modularity, you can use *highly specific display driver libraries* that are easy to use and do not require much configuration, **plus** your source code remains display-independent. If you later decide to use a different display, you simply exchange the *hardware-specific* display library. Your source code remains untouched.



> Tags: Display, C++, Library, Programming, u8g2, ucglib, TFT_eSPI, Adafruit GFX

[Visit Page on Website](https://done.land/components/humaninterface/display/usage/programming/writingc++code?560674012023251935) - created 2025-01-22 - last edited 2025-01-22
