<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# 1.9 Inch 170x320 IPS TFT Display

> Full-Angle (IPS) Rectangular TFT Display With SPI And 262K Colors (18bit)

This breakout board features a 1.9" *full-angle color TFT display with *SPI interface* that works for *3.3V* and *5V* microcontrollers. Since the display is using *IPS* (*In-Plane Switching*), it has excellent *viewing angles* and rich colors.

The display is available from generic Chinese sources (like [Estardyn](https://www.google.com/search?q=estardyn+tft+1.9) and others) for around €2.00:

<img src="images/tft_st7789_1.9inch_top_side_t.png" width="40%" height="40%" />

It is used by renown brands as well. The [1.9" Adafruit Display](https://www.adafruit.com/product/5394) has a snappier *PCB design* and comes with good documentation. You decide whether this is worth *10x the cost* (around €20.00):

<img src="images/adafruit_tft_1.9inch_st7789_t.png" width="40%" height="40%" />

In-between this price range, there are many other vendors offering their own *PCB designs*, including this cleverly designed *PCB* from [WaveShare](https://www.google.com/search?q=waveshare+tft+1.9) with the smallest-possible form factor and an [excellent documentation](https://www.waveshare.com/wiki/1.9inch_LCD_Module) that equally applies to the breakout boards from other vendors:

<img src="images/tft_st7789_1.9inch_waveshare_t.png" width="42%" height="42%" />

| Item | Description |
| --- | --- |
| Supply Voltage | *3.2-5.0V* |
| Resolution | *170x320* |
| Pixel Size | *0.1335x0.1335mm* |
| Colors | *262K (18bit)* |
| Controller | [ST7789](https://done.land/components/humaninterface/display/tft/st7789) |
| Module Size | *29x62x5.1mm* |
| Screen Size | *23.7x43.7mm* |
| Visible Size | *22.7x42.7mm* (*0.5mm margin*) |
| Weight | *9.8g* |


<img src="images/tft_st7789_1.9inch_sizes.png" width="70%" height="70%" />

## SPI Interface
Both the [Chinese Board](https://www.google.com/search?q=estardyn+tft+1.9) and the [Adafruit Display](https://www.adafruit.com/product/5394) expose the *SPI interface*:


<img src="images/tft_st7789_1.9inch_pin_top_t.png" width="40%" height="40%" />

| Pin (Display Board) | Description | Pin ([Lolin32 Lite](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/lolin32lite)) |
| --- | --- | --- | 
| GND | Ground | G |
| VCC | positive supply voltage | 3V |
| SCL | SPI Clock (SCK) | 18 |
| SDA | SPI MOSI | 23 |
| RES | Reset | EN or programmable GPIO, (*low active*) |
| DC | Data/Command (Data=*high*, Command=*low*) | any output GPIO |
| CS | Chip Select (*low active*) | 5 |
| BLK | Backlight | any PWM pin or 3V (100% bright, no dimming) |



<img src="images/tft_st7789_1.9inch_pin_back2_t.png" width="50%" height="50%" />


### Backlight
The display backlight is controlled via pin **BLK**: 

* **Controllable:** if you want your microcontroller to control the backlight (i.e. to dynamically *dim it*), connect **BLK** to any *PWM pin*.
* **Fixed:** when you connect **BLK** to *3.3V/5V* directly, the backlight works independently from the microcontroller. You could use a small *potentiometer* to manually adjust its brightness. 

> [!TIP]
> With the latter setup, the display remains on (and fully readable) when the board enters *deep sleep*. This can be highly power efficient if you want your device to display *static content*.


## Programming
The display boards use the [ST7789](https://done.land/components/humaninterface/display/tft/st7789) controller that can be programmed with these librarys and components:

* **ArduinoIDE/platformio:** [Adafruit-ST7735-Library](https://github.com/adafruit/Adafruit-ST7735-Library), [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
* **ESPHome:** [ILI9XXX](https://esphome.io/components/display/ili9xxx#ili9xxx) component, [ST7789V TFT LCD](https://esphome.io/components/display/st7789v.html) component (*obsolete*)

Here is a [good walkthrough](https://github.com/mboehmerm/IPS-Display-ST7789-170x320) using this display plus these:

* [Lolin32 Lite](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/lolin32lite) development board
* [ArduinoIDE](https://www.arduino.cc/en/software) 
* [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library


## Materials
* [How To Connect Breakout-Board:](https://www.waveshare.com/wiki/1.9inch_LCD_Module) excellent and detailed documentation (by *WaveShare*) covering the *WaveShare* breakout board. Applies to breakout boards from other vendors as well. Covers using the display with various microcontrollers (including *Raspberry Pi*, *STM32*, and *Arduino*).

> Tags: Display Driver, ST7789, TFT Display, Full Color, 18bit, 262K, SPI, 1.9 Inch, Adafruit, WaveShare, Estardyn, Lolin32 Lite, Raspberry