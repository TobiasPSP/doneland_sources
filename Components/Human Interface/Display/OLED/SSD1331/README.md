<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# SSD1331-Based OLED Display

> Small Full-Color OLED Displays 

Most *OLED displays* are *monochrome*. *OLED displays* using the *SSD1331 driver* can display 65K colors.

<img src="images/oled_ssh1331_front_t.png" width="60%" height="60%" />

## Resolution

Since *full color OLED displays* are still quite expensive, most of these displays are *very small* and feature a *limited resolution*. Entry-level displays are *0.95inch* at a resolution of *96x64* pixels and typically work with *3.3V* and *5V*.

## Interface

Due to the higher data volume that is required for color displays, these *OLED displays* use the faster *SPI interface*.


## Libraries

There is a variety of libraries to select from, for example the *Adafruit SSD1331 OLED Driver Library for Arduino*. 


## Wiring
*SSD1331*-based displays use the faster *SPI interface* which requires more *GPIOs* compared to *I2C* and makes wiring a bit more complex.


<img src="images/oled_ssh1331_pins_t.png" width="100%" height="100%" />


The display has seven pins:

| Pin | Label | Description |
| --- | --- | --- |
| 1 | GND | Ground |
| 2 | VCC | *3.3-5.0V* |
| 3 | SCL |  |
| 4 | SDA |  |
| 5 | RES | Reset |
| 6 | DC |  |
| 7 | CS | SPI: Chip Select |

<img src="images/oled_ssh1331_back_t.png" width="60%" height="60%" />


### Example Code
Here is example code taken from the *Adafruit SSD1306 library* that I used to create the pictures on this page. The code is already adjusted and runs fine in *platformio*:

````c++

````

This is the *platformio.ini* I used to compile the sketch in *platform.io* and run it on a *ESP32 S2 Mini*:

````

````


## Data Sheets

[SSD1331](materials/ssd1331_datasheet.pdf)   





> Tags: HID, Display, OLED, Color, 16K, SPI, Driver, SSD1331, 96x64
