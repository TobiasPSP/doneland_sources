<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# ST7789

> Drives TFT Displays Up To 240x320 Pixels At 262K Colors (18bit)

The *ST7789* is a versatile *TFT display driver IC* commonly used for small to medium-sized displays with resolutions of up to *240x320* pixels at full *18bit color* (262 thousand different colors). Many *TFT display boards* and *ESP32 development boards with integrated display* use this device driver.

The driver supports [SPI](https://done.land/fundamentals/interface/spi) and the *Parallel* interface, plus some lesser used ones. 


## Versions
Although *ST7789* exists in a number of variants, there seem to be *no substantial differences* between the *2012 version* [ST7789S](materials/st7789v_datasheet.pdf) and the *2021 version* [ST7789P3](materials/st7789p3_datasheet.pdf). Apparently, the different versions are mere *maintenance releases* with minor hardware adjustments to chip size, pad locations, and supported voltage ranges.

The key display features remain identical:

* **Maximum Resolution:** *240(H)x320(V)* pixels
* **Maximum Color Depth:** *18bit* (262K)
* **Source and Gate Lines:** 720/320
* **Interface:** [SPI](https://done.land/fundamentals/interface/spi) and *Parallel*

The power consumption also remains identical.

| Version | Spotted Changes |  Chip Size | Year |
|---|---|---|---|
| [ST7789S](materials/st7789v_datasheet.pdf)   |  |300um  | 2012  | 
| [ST7789V](materials/st7789v_datasheet.pdf)   | gate-driver supply voltage range extended  | 300um | 2013   | 
| [ST7789H2](materials/st7789h2_datasheet.pdf)      | | 300um   | 2014   |
| [ST7789VI](materials/st7789vi_datasheet.pdf)      | power consumption in *normal mode* changed from *7.5mA* to *8mA*   | 300um   | 2016   | 
| [ST7789V2](materials/st7789v2_datasheet.pdf)      | power consumption back to normal (possibly documentation bug) | 300um   | 2016   | 
| [ST7789VW](materials/st7789vw_datasheet.pdf)      | | 300um   | 2017   |
| [ST7789V3](materials/st7789v3_datasheet.pdf)      |  | 200um   | 2020   |
| [ST7789P3](materials/st7789p3_datasheet.pdf)     | | 200um   | 2021   | 

That said, the data sheets are *300 pages+*, filled with technical glibber and timing protocols. If **you** spot significant differences or know of compatibility issues, please leave a comment below.


> [!NOTE]
> Regardless of which *ST7789* variant your display uses, they are all supported by the same libraries. If your display does not work, it is most likely due to incorrect *GPIO* assignments on your side, or due to incompatibilities between the display breakout board and your microcontroller (i.e. incompatible operating voltage, incompatible interface (*Parallel* instead of *SPI*), no exposed *CS pin*, etc.). It may help to test with different libraries (*Adafruit*, *TFT_eSPI*) as they use different default behaviors.



## ESPHome Support
[ESPHome](https://done.land/tools/software/esphome/introduction) started to support *ST7789* with a dedicated component called [ST7789V TFT LCD](https://esphome.io/components/display/st7789v.html). This component has been made redundant since the *ST7789* is now supported by the more generic [ILI9XXX](https://esphome.io/components/display/ili9xxx#ili9xxx) component.

## platformio/Arduino Support
[Adafruit](https://www.adafruit.com/) provides a free [Adafruit library for ST77* drivers](https://github.com/adafruit/Adafruit-ST7735-Library) (including the *ST7789*). It is also supported by [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI).

> Tags: Display Driver, Resolution, ST7789V, ST7789S, ST7789P, ST7789H

[Visit Page on Website](https://done.land/components/humaninterface/display/tft/st7789?705830101817240754) - created 2024-10-16 - last edited 2024-10-16
