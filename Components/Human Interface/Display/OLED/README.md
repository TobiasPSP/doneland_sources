<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# OLED Displays

> Awesome Contrast, Great Readability And Self-Illuminating Pixels

*OLED Displays* use *organic light-emitting diodes* to display pixels. Since each pixel is its own *light source*, these displays have an excellent contrast, can be clearly read from a wide viewing angle and are readable in dim as well as very bright environments.

## Overview

*OLED displays* are expensive to produce which is why affordable *OLED displays* for *DIY projects* are *very small* and typically *single-colored*.

Surprisingly, these limitations make *OLED displays* very attractive for certain use cases: since the amount of data that needs to be transferred from a microcontroller to the display is small, a simple *two-wire I2C* interface is sufficient to connect these displays to a microcontroller, saving precious *GPIOs*.

While you certainly wouldn't use these small *OLED displays* for watching videos, they are perfect for displaying *sensor information*, provide *device feedback*, indicate *charging status*, and alike. And since *OLED* does not require *backlighting*, they do not require as much energy as other types of display. That's a big advantage in battery-driven use cases.

> [!NOTE]
> Since in *OLED displays*, **each pixel** is an independent **light source**, the power consumption largely depends on how many pixels are *on*. That's why *white content* on *back background* is much more efficient for *OLED displays* than *black text* on *white background*. With mixed content, *OLED displays* typically consume *40-60%* of the energy a comparable *LCD display* would require.

## Caveats

There are two specific *caveats* with *OLED displays*:

* **Limited Life-Span:** their *organic* materials can degrade over time which leads to decreasing brightness. However, this effect may become visible only after more than 10.000 hours of operation. It may be a problem in *TV sets* that are turned on continuously day and night. It is not a typical problem in *DIY projects*.
* **Burn In/Ghosting:** **OLED displays* are susceptible to image retention (burn in aka *ghosting*) if static images are displayed for extended periods. This may be a problem in *DIY projects* as most device display designs do use a rather *static layout*.

Both shortcomings can be overcome though by turning *OLED displays* off when they are not needed, much similar to how many *OLED*-based smartwatches and smartphones work. This strategy also helps conserving power. Here is the typical behavior of such devices:

When there is information to display, the firmware turns the display on. After a certain time period, the display automatically turns off (or dims). Typically, users can press a key on the device to turn the display on anytime when needed.


## OLED Driver Chips
*OLED displays* require a *driver chip* that takes the information to be displayed and draws it to the screen. Knowing the *driver chip* used on a particular *OLED breakout board* is important because the chip type determines which *software library* your code needs in order to work with the display.

These are commonly found *OLED drivers* in breakout boards:

* **Small Monochrome - SSD1306:** Entry-level for small monochrome (1bit) displays up to a resolution of *128x64* pixels. Uses *I2C*.
* **Small Monochrome - SH1106:** Very similar to *SSD1306*, resolution of *132x64* pixels. No hardware scroll functions. Uses *I2C*.
* **Large Monochrome - SH1107:** Supports monochrome (1bit) resolutions of up to *128x128*. Supports *I2C* and *SPI*.
* **Large Grayscale - SSD1327:** Supports 16 levels of gray (4bit) and resolutions of up to *128x128* pixels. Supports *I2C* and *SPI*.
* **Small Color - SSD1331:** Supports 65k color (16bit) and resolutions of up to *96x64* pixels. Supports *I2C* and *SPI*.
* **Large Color - SSD1351:** Supports 262k color (18bit) and resolutions of up to *128x128* pixels. This driver supports *SPI* only.

There are many more *OLED* drivers. The *software library* [u8g2](https://github.com/olikraus/u8g2/wiki/gallery) aims to provide a hardware-independent solution for a multitide of *OLED drivers*. It [lists](https://github.com/olikraus/u8g2/wiki/gallery) many more *OLED drivers* and their specifications.


## Data Sheets

[SSD1306](materials/ssd1306_datasheet.pdf)   
[SSD1327](materials/ssd1327_datasheet.pdf)   
[SSD1331](materials/ssd1331_datasheet.pdf)   
[SSD1351](materials/ssd1351_datasheet.pdf)   
[SH1106](materials/sh1106_datasheet.pdf)   
[SH1107](materials/sh1107_datasheet.pdf)   





> Tags: HID, Display, OLED, I2C, Driver, SSD1306, SSD1327, SSD1331, SSD1351, SH1106, SH1107, Monochrome, Color, Resolution

[Visit Page on Website](https://done.land/components/humaninterface/display/oled?644321051706242045) - created 2024-05-05 - last edited 2024-05-05
