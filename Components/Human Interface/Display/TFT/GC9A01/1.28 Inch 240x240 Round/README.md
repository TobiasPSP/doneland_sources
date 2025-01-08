<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# 1.28 Inch Round TFT Display

> Round 240x240 Full-Color TFT Display

This uniquely-shaped TFT display features a relatively high *240x240* resolution with a high pixel density, offering crisp visuals on a *full-perspective IPS* screen that can be viewed from nearly any angle.

It is available in a variety of breakout board shapes:

<img src="images/tft_round_1.26_overview_t.png" width="70%" height="70%" />

## Overview
The display utilizes the *GC9A01* driver, which is now supported by both [ESPHome](https://esphome.io/components/display/ili9xxx.html) and widely used *Arduino* libraries, which are also compatible with *ESP32*: [Adafruit GFX library](https://www.adafruit.com/) and [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI).

Thanks to its *watch*-like form factor and high pixel density, this display is ideal for various projects, including [building a "smart watch"](https://www.instructables.com/ESP32-and-Round-OLED-Smart-Watch-Concept/):

<img src="images/wearable_round_tft.png" width="40%" height="40%" />

Most commonly available breakout boards support a *3-5V* supply voltage, making them compatible with both [Arduino](https://done.land/components/microcontroller/families/arduino/) and modern microcontrollers like the [ESP32](https://done.land/components/microcontroller/families/esp/esp32/).

The *GC9A01* display driver is typically controlled via [SPI](https://done.land/fundamentals/interface/spi/).

## Programming

For programming, you have two primary options:

### 1. C++ Libraries
You can use *C++* with one of the following libraries for full control over your display:

- [Adafruit library for GC9A01 drivers](https://github.com/adafruit/Adafruit_GC9A01A)
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)

This gives you full flexibility but requires programming expertise, as you'll need to implement everything yourself.

### 2. ESPHome
Alternatively, you can use [ESPHome](https://done.land/tools/software/esphome/introduction/), which simplifies the setup and eliminates the need for extensive coding. The [ILI9xxx component](https://esphome.io/components/display/ili9xxx.html) supports this display and is also compatible with a variety of other TFT displays, meaning any *ESPHome* sample configuration using the *ILI9xxx* component can be used with this display.

> [!IMPORTANT]
> The *ILI9xxx* component began supporting this display in March 2024. Ensure your *ESPHome* installation is up-to-date.


> Tags: GC9A01, Adafruit, TFT_eSPI, ESPHome, ILI9xxx, Round Display 
