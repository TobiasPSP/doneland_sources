<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# OLED Displays

> Awesome Contrast, Great Readability And Self-Illuminating Pixels

*OLED Displays* use *organic light-emitting diodes* to display pixels. Since each pixel acts as its own *light source*, such displays have an excellent contrast, can be clearly read from a wide viewing angle and are readable in dim as well as bright daylight.


<img src="images/oled_sh1107_128x128_compare_t.png" width="80%" height="80%" />

Common display sizes are *0.48*, *0.91*, *0.96*, *1.3*, and *1.5* inch. Resolutions start at *64x48* pixels, and (in affordable price ranges) end at *128x128* pixels. 

## Overview

For monochrome displays, *OLED* is a great and affordable technology. Such displays typically use *I2C* and do not need separate backlights which makes them very easy to connect with a minimum of *GPIOs*, and they can work very power-efficiently when displaying data on a black background.

For simple DIY projects, monochrome OLED displays with a resolution of 128x64 pixels and a screen size of *0.96"* or *1.3"* have become readily available at prices as low as €1.00 per display.    

Once you require color displays, however, *TFT* is still the way to go. While there are *Color OLED* displays available, they are much more expensive than *TFT. The same is true for *larger* displays above *1.3"*.



> [!NOTE]
> Since in *OLED displays*, **each pixel** is an independent **light source**, the power consumption relies on how many pixels are *on*. That's why content on *black background* is more efficient than *inverted displays* where the background is actively lit. With mixed content, *OLED displays* typically consume *40-60%* of the energy a comparable *TFT display* would require.

### Caveats

There are two *caveats* with *OLED displays*:

* **Limited Life-Span:** their *organic* materials can degrade over time which leads to decreasing brightness, especially with *blue* OLED displays. This effect may become visible after more than 10.000 hours of operation. It is not a typical problem in *DIY projects* unless you design devices that are always on, and do not implement screen saver logic.
* **Burn In/Ghosting:** **OLED displays* are susceptible to image retention (burn in aka *ghosting*) if static images are displayed for extended periods. This may be a realistic problem in *DIY projects* as most displays do show a rather *static layout*.

#### Workarounds
Both shortcomings can be overcome by turning *OLED displays* off when they are not needed, much similar to how many *OLED*-based smartwatches and smartphones work. This strategy also helps conserving power. 

Here is the typical behavior of such devices:

* When there is information to display, the firmware turns the display on. 
* After a certain period of inactivity, the display automatically turns off (or dims). 
* Typically, users can press a key on the device to turn the display back on at any time.


### Comparison
Let's compare key facts of OLED and TFT displays:

| Feature               | OLED (Organic Light-Emitting Diode)                     | TFT (Thin Film Transistor LCD)                 |
|-----------------------|---------------------------------------------------------|------------------------------------------------|
| **Display Quality**   | Excellent contrast with true blacks (no backlight).     | Good, but blacks are less true due to backlight. |
| **Brightness**        | High brightness in dark environments but may fade in direct sunlight. | Can be brighter and more sunlight-readable with reflective layers. |
| **Power Efficiency**  | More power-efficient for mostly black screens (each pixel lights individually). | Backlight always on, consuming constant power regardless of image. |
| **Lifespan**          | Organic materials degrade over time, reducing lifespan, especially for blue pixels. | Generally longer lifespan without image burn-in issues. |
| **Viewing Angles**    | Wide viewing angles with consistent colors.             | Often good but may suffer from color shifts depending on panel type (e.g., TN, IPS). |
| **Refresh Rate**      | Very high, suitable for animations and fast updates.    | High, but can be slightly slower for complex graphics. |
| **Cost**              | Generally more expensive per unit size.                | More affordable and available in larger sizes. |
| **Ease of Use**       | Simple to wire and program; fewer connections for small sizes. | Requires more connections (backlight, control pins). |
| **Availability**      | Limited to smaller sizes (<3 inches typical).          | Wide range of sizes (from small to large).     |
| **Durability**        | Fragile; can be damaged by static or environmental factors (moisture). | More robust but may need additional care for backlight longevity. |
| **Color Accuracy**    | Vivid and vibrant colors.                               | Accurate but less vibrant compared to OLED.   |
| **Use Cases**         | Ideal for low-power, compact projects with sharp visuals. | Best for larger displays or applications requiring high brightness. |
| **Drawbacks**         | Risk of burn-in for static images, shorter lifespan for some colors. | Bulkier due to backlight, slightly less contrast. |

### Recommendation
Typical *0.96"* and *1.3"* monochrome OLED displays are an excellent and affordable choice for many DIY projects: they are easy to integrate, there is good support, and the display quality is sharp and crisp.

Once you require multi-color, larger sizes, or need to operate the display continuously for days or months, *TFT* displays may be a better and more economic choice.


## OLED Driver Chips
*OLED displays* require a *driver chip* that takes the information to be displayed and draws it to the screen. Knowing the *driver chip* used on a particular *OLED breakout board* is important because the chip type determines which *software library* your code needs in order to work with the display.

Drivers support both *I2C* and *SPI* interfaces. With monochrome displays, due to the limited need for data transfer, typically the two-wire *I2C* is used. Grayscale and color displays often use the faster *SPI*. Ultimately, the breakout board determines which interface can be used.


> [!NOTE]
> The driver lists below are just a selection of the most commonly used drivers; there are many more. If in doubt, look up their data sheets.    


### Monochrome Displays
Small monochrome OLED displays have become very affordable lately, partially because of new cost-effective drivers like the *SH1106* or *SH1107*. These drivers are great for the primary use case: displaying text and static images.

However, drivers like *SH1106* lack built-in hardware support for scrolling and animations. While these are not the typical use case for OLEDs, if you require it, you may be better off using the older but more powerful **SSD1306* or *SSD1307*.

The *SSD1315* is a revised version of the *SSD1306* with improved brightness and contrast.

|Driver|Resolution Support|Color Support|Interface Types|Unique Features/Benefits|Limitations Compared to Others|Common Applications|
|---|---|---|---|---|---|---|
|SH1106|Up to 132x64 (128x64 typical)|Monochrome|I2C,SPI|Affordable, wide availability, compatible with many small displays.|Lacks hardware scrolling; less efficient addressing.|Small DIY OLEDs (e.g., 0.96").|
|SH1107|Up to 128x128|Monochrome|I2C,SPI|Higher resolution for square displays, compact driver for wearables.|slower refresh|Compact devices, wearables.|
|SSD1306|Up to 128x64|Monochrome|I2C,SPI|Hardware scrolling, smooth animations, very efficient data addressing.|slightly older compared to newer drivers|General-purpose small displays.|
|SSD1307|Up to 128x64|Monochrome|I2C,SPI|Improved version of SSD1306, supports more flexible addressing modes.|No significant added benefits over SSD1306 for most users.|Small monochrome displays.|
|SSD1680|Up to 200x200|Monochrome|SPI|E-paper-like OLED with extremely low power for static content.|Limited refresh rate; not suitable for dynamic or video content.|E-readers, low-power dashboards.|
|SSD1315|Up to 128x64|Monochrome|I2C,SPI|Improved contrast and brightness compared to SSD1306, with backward compatibility.|No significant additional features over SSD1306 apart from brightness.|Budget-friendly small displays.|
|SSD1603|Up to 128x64|Monochrome|I2C|Highly power-efficient for basic applications.|Lacks advanced features like grayscale or color.|Simple text or icon-based displays.|

### Grayscale Displays
These drivers support 16 levels of grayscale for more detailed images and modern UIs. This comes at a cost, though, when compared to monochrome OLED displays:

* **Price:** considerably more expensive 
* **Efficiency:** require more power 
* **Refresh Rate:** slower (of no concern when displaying static text)




|Driver|Resolution Support|Color Support|Interface Types|Unique Features/Benefits|Limitations Compared to Others|Common Applications|
|---|---|---|---|---|---|---|
|SSD1327|Up to 128x128|Grayscale (16 levels)|I2C,SPI| ||Graphical interfaces, detailed UIs.|
|SSD1322|Up to 256x64|Grayscale (16 levels)|SPI|Wide horizontal resolution, suited for panoramic or dashboard displays.||Audio players, control panels.|
|SSD1325|Up to 128x64|Grayscale (16 levels)|SPI|Mid-range grayscale resolution for detailed yet simple graphics.|Lower grayscale resolution than SSD1327; slower refresh rates.|Basic grayscale graphical displays.|


### Color Displays
OLED color displays are generally much more expensive: while a simple monochrome display can cost as low as *1.00€*, a full color display of the same size runs at *5-10x* the cost. 

*SSD1331* is the entry-level driver providing vibrant and excellent display quality, however limited to rather small display resolutions. The *SSD1351* supports reasonable resolutions of up to *128x128* pixel.

The *SEPS525* is unique for its high resolution but rather unusual for DIY displays, which applies to the *RA8875* even more so that can drive displays up to VGA resolution.

|Driver|Resolution Support|Color Support|Interface Types|Unique Features/Benefits|Limitations Compared to Others|Common Applications|
|---|---|---|---|---|---|---|
|SSD1331|Up to 96x64|RGB (65k colors)|SPI|high-speed refresh for animations|Limited resolution compared to SSD1351.|Small, colorful graphical displays.|
|SSD1351|Up to 128x128|RGB (65k colors)|SPI|supports typical DIY display resolutions|Higher power consumption, more expensive.|Wearables, premium graphical UIs.|
|SEPS525|Up to 160x128|RGB (262k colors)|SPI|18-bit colors|less common, lacking support |Portable devices, gaming consoles.|
|RA8875|Large resolutions (e.g., 800x480)|RGB (65k colors)|SPI,Parallel|includes built-in touch controller and advanced graphical functions.|Expensive; less common for small DIY projects.|Advanced graphical interfaces.|

## Programming
Most *monochrome OLED drivers* work similar enough for *universal support*: the [u8g2 C++ library](https://github.com/olikraus/u8g2/wiki/gallery) or the *ESPHome* [SSD1306 platform](https://esphome.io/components/display/ssd1306.html) support *all* monochrome OLED drivers universally.

For *grayscale* and *color* displays, there is also good support, however libraries and *ESPHome platforms* target *specific drivers*:




* **C++/Arduino Framework:** 
    * **Monochrome:** *universal* support: [u8g2](https://github.com/olikraus/u8g2/wiki/gallery). Here is a [full list](https://github.com/olikraus/u8g2/wiki/gallery) of supported drivers. And [here is a full example](https://done.land/components/humaninterface/display/oled/sh1106/#example-code) using a monochrome *SH1106*-based OLED display. There are many other libraries, some of which target *specific* drivers only.
    * **Grayscale:** support for *specific* drivers only, i.e. [Adafruit-SSD1327](https://github.com/adafruit/Adafruit_SSD1327/blob/master/Adafruit_SSD1327.cpp)
    * **Color:** ssupport for *specific* drivers only, i.e.  [Adafruit-SSD1331-OLED](https://github.com/adafruit/Adafruit-SSD1331-OLED-Driver-Library-for-Arduino) 
* **ESPHome:**
    * **Monochrome:** *universal* support: [SSD1306](https://esphome.io/components/display/ssd1306.html) supports all common monochrome OLED drivers including *SH1106*/*SH1107*. Here is a [full example](https://done.land/components/humaninterface/display/oled/sh1106/#esphome). 
    * **Grayscale:** support for *specific* drivers only, i.e.  [SSD1322](https://esphome.io/components/display/ssd1322.html),[SSD1325](https://esphome.io/components/display/ssd1325.html),  [SSD1327](https://esphome.io/components/display/ssd1351.html)
    * **Color:** support for *specific* drivers only, i.e.  [SSD1331](https://esphome.io/components/display/ssd1331.html), [SSD1351](https://esphome.io/components/display/ssd1351.html) 

## Data Sheets

[SSD1306](materials/ssd1306_datasheet.pdf)   
[SSD1327](materials/ssd1327_datasheet.pdf)   
[SSD1331](materials/ssd1331_datasheet.pdf)   
[SSD1351](materials/ssd1351_datasheet.pdf)   
[SH1106](materials/sh1106_datasheet.pdf)   
[SH1107](materials/sh1107_datasheet.pdf)   





> Tags: HID, Display, OLED, I2C, SPI, Driver, SSD1306, SSD1307, SSD1315, SSD1322, SSD1325, SSD1327, SSD1331, SSD1351, SSD1608,  SSD1680, SH1106, SH1107, SEPS525, RA8875, Monochrome, Grayscale, Color, Resolution

[Visit Page on Website](https://done.land/components/humaninterface/display/oled?644321051706242045) - created 2024-05-05 - last edited 2025-01-11
