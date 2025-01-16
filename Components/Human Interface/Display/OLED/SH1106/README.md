<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# SH1106-Based OLED Display

> 128x64 Monochrome OLED Displays For Little Money

The *SH1106* is a modern, cost-optimized *OLED display driver*, often considered a successor to the highly popular *SSD1306*.


## Overview
The *SSD1306* (released *2007*) has been the dominant OLED driver for many years, but the *SH1106* (released *2013*) has become more popular in recent years due to its affordability. 

The trade-off is the lack of hardware acceleration for scrolling and animations in the cheaper *SH1106*. However, such features are often unnecessary for typical OLED use cases where only static text is displayed.


*SH1106* supports monochrome OLED displays with a maximum resolution of *132x64* pixels, and breakout boards typically use the *I2C* interface.

<img src="images/oled_sh1106_white_alpha_t.png" width="30%" height="30%" />




### Breakout Boards 

Typically, you purchase ready-to-use breakout boards that come with the driver and an OLED display (*0.96"* and *1.3"* are most common).

<img src="images/oled_sh1106_white_text_t.png" width="30%" height="30%" />

Occasionally, such displays are integrated in *keyboard-display-combos* like the one below:

<img src="images/oled_sh1106_keyboard_t.png" width="60%" height="60%" />

### Display Colors
*SH1106*-based OLED displays are **always monochrome**, however the display color may vary.

Typically, they are offered in *white* and *blue*. There are also displays with a combination of *yellow* and *blue*: a small stripe of the display is *yellow*, and the rest is *blue*.

Recently, *fully yellow* displays emerged at slightly higher cost.

> [!NOTE]
> All OLED displays are susceptible to wear: after extended use of *10.000 hours* or more, their brightness may fade. *Blue* displays are more susceptible than other colors.     


### I2C Interface
Almost all breakout boards utilize the simpler *I2C* interface, although occasionally you see breakout boards with *SPI* interface, too.

The I2C address is typically fixed and cannot be changed. It is either *0x3c* or *0x3d*. As a rule of thumb, *128x64* displays use *0x3c*, and *128x32* displays use *0x3d*, however exceptions exist.

> [!TIP]
> If you need to operate multiple OLED displays, use a *I2C Multiplexer* such as the *PCF8575*, or use a *SPI* version: with *SPI*, you can select the active device via the *CS* pin.    

## Programming

The by far easiest way of using *SH1106* OLED displays is via [ESPHome](https://done.land/tools/software/esphome/introduction/), however this platform is targeting primarily *ESP32* microcontrollers.

Alternately, you can use *C++ libraries* to program the firmware manually.

## ESPHome

Using *ESPHome* is the simplest approach, as *ESPHome* includes a native [SSD1306 OLED Display](https://esphome.io/components/display/ssd1306.html) component that supports most monochrome OLED drivers, including the *SH1106*. Here are the supported OLED drivers:

* **SSD1306:** 128x32, 128x64, 96x16, 72x40, 64x48
* **SSD1305:** 128x32, 128x64
* **SH1107:** 128x64, 128x128
* **SH1106:** 128x32, 128x64, 96x16, 64x48

Here is an example configuration:

````
# define the I2C pins that you use 
# to connect the display to your microcontroller
i2c:
  sda: GPIO21
  scl: GPIO22

display:
  - platform: ssd1306_i2c
    model: "SH1106 128x64"  # 0.96/1.3" 128x64 OLED display
    address: 0x3C           # default address, use 0x3D if default fails
    rotation: 180           # rotate content if needed
    update_interval: 3000ms # 1s is default (1000ms)
    lambda: |-
      it.print(0, 0, id(lato400), "Hello World!");

# you need at least one font to output text
font:
  - file:
      type: gfonts
      family: Lato
      weight: 400
    id: lato400
    size: 20
````


To compile and upload the sample configuration, simply [follow these simple steps](https://done.land/tools/software/esphome/compileconfiguration/).


<img src="images/sh1106_esphome_example_t.png" width="50%" height="50%" />

> [!NOTE]
> OLED displays are crisp and clear. If texts appear unsharp like in the picture, you may have used a font that was scaled up or down. You get the best results with pixel fonts specifically designed for a given size.   

You can now use all the graphics commands supported by the [ESPHome Display Component](https://esphome.io/components/display/index.html) to draw images, shapes, lines, arcs, etc.

## C++

For direct programming (using the *Arduino Framework*), two popular libraries support the *SH1106*:

- [U8G2 Library](https://github.com/olikraus/u8g2)
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) + [Adafruit_SH110x](https://github.com/adafruit/Adafruit_SH110x)

#### Why Adafruit Library?
The US company *Adafruit* produces and sells electronic components and provides extensive support for it, including state-of-the-art *C++ libraries*. 

Their libraries are popular because of good quality, documentation, and especially modular design: they consist of a *hardware specific* library for the particular display driver you need, and a *hardware neutral* core graphics library that provides the drawing commands:

* [Specific Driver Library:](https://github.com/adafruit/Adafruit_SH110x) targets a specific family of display drivers, i.e. *SH110x* drivers
* [Adafruit GFX:](https://github.com/adafruit/Adafruit-GFX-Library) core grafics library which is hardware independent and provides the drawing commands.

This way, source code remains compatible to most displays. All you need to do is change the hardware neutral library to target your display.

#### Why u8g2 Library
The [u8g2](https://github.com/olikraus/u8g2) library is another de-facto standard: it targets *all **monochrome** displays*, including OLED display drivers like *SH1106*.

With this library, your source code remains compatible to a variety of *monochrome displays*: all you need to do is use the appropriate display class in your code to initialize your display.

> [!TIP]
> *Oli Kraus* has created a universal library for **color displays**, too: [ucglib](https://github.com/olikraus/ucglib).



<details><summary>Caveats: Using ArduinoIDE Code In platformio</summary><br/>

You simply do not know most of the time *which IDE* was used to program a given library or example code that you want to use. A lot of the code you find in the Internet is many years old. Often, it was created using *ArduinoIDE*.

*ArduinoIDE* is a beginners-friendly (but rather limited) *C++ editor*. In order to simplify its user experience, it lets the user get away with many bad programming habits that a more professional IDE (like *platformio*) would flag down.

If examples do not compile right in *platformio*, you have two options:

* **Try with ArduinoIDE:** the code may compile just fine in *ArduinoIDE*. If so, it was probably created in *ArduinoIDE* in the first place, and requires some of the *ArduinoIDE* leniency.
* **Fix it:** check the code for signs of *ArduinoIDE specifics*, and turn the code into clean and solid *C++* source code that works fine in other IDEs such as *platformio*.

These are the most common issues with code that was created in *ArduinoIDE* and fails to compile in *platformio*:

* **`.ino` is `.cpp`:** *ArduinoIDE* uses the file extension `.ino` (as in *Ardu**ino***) for *C++ source code* files. The official extension is `.cpp` (as in *C++*). You can simply rename the file extension.
* **Add `#include <Arduino.h>`:** while not always necessary, it enables *ArduinoIDE-specific* features
* **Use `setup()` and `loop()`:** define both `setup()` and `loop()`. If you don't need `loop()`, define it anyway, and leave it empty.
* **Method Order:** make sure you define every method in your code **before you call the method**. Code written in *ArduinoIDE* typically moves method definitions to the *bottom* of the source code. This is only allowed in *ArduinoIDE*. For use in *platformio* and other professional IDEs, move the method definitions *up* so that they are defined when code wants to call them.

</details>


### Using u8g2 Library

The [U8G2 library](https://github.com/olikraus/u8g2) is a versatile and robust option that supports a wide range of **monochrome** display drivers.

#### Selecting the OLED Driver


In the *U8G2* C++ example, the display interface and resolution are selected through the *class*. For a *128x64 SH1106 OLED display* connected via *I2C*, you can use one of the following classes:

- **`U8X8_SH1106_128X64_NONAME_HW_I2C`**: For hardware *I2C*.
- **`U8X8_SH1106_128X64_NONAME_SW_I2C`**: For software *I2C* (allows custom *I2C GPIOs*).

Once you’ve configured the appropriate class, the rest of the code is straightforward. I successfully tested this approach on *ESP32*, *ESP32-S2*, and *ESP32-C3*. 

> [!TIP:] 
> Ensure the *I2C GPIOs* in your code match your hardware setup; otherwise, the display will remain dark.



<details><summary>C++ Example Code using u8g2</summary><br/>


````c++
#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// use hardware I2C (if you know the hardware i2c GPIOs for your board):
//U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);

// use software I2C (and define GPIOs yourself)
// pins below are for ESP32S, adjust as needed for other mc models:
#define SDA 21
#define SCL 22

U8X8_SH1106_128X64_NONAME_SW_I2C u8x8(SCL, SDA);

void setup(void)
{
  u8x8.begin();
  u8x8.setFlipMode(1);
}

void pre(void)
{
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);    
  u8x8.clear();

  u8x8.inverse();
  u8x8.print(" U8x8 Library ");
  u8x8.setFont(u8x8_font_chroma48medium8_r);  
  u8x8.noInverse();
  u8x8.setCursor(0,1);
}

void draw_bar(uint8_t c, uint8_t is_inverse)
{	
  uint8_t r;
  u8x8.setInverseFont(is_inverse);
  for( r = 0; r < u8x8.getRows(); r++ )
  {
    u8x8.setCursor(c, r);
    u8x8.print(" ");
  }
}

void draw_ascii_row(uint8_t r, int start)
{
  int a;
  uint8_t c;
  for( c = 0; c < u8x8.getCols(); c++ )
  {
    u8x8.setCursor(c,r);
    a = start + c;
    if ( a <= 255 )
      u8x8.write(a);
  }
}

void loop(void)
{
  int i;
  uint8_t c, r, d;
  pre();
  u8x8.print("github.com/");
  u8x8.setCursor(0,2);
  u8x8.print("olikraus/u8g2");
  delay(2000);
  u8x8.setCursor(0,3);
  u8x8.print("Tile size:");
  u8x8.print((int)u8x8.getCols());
  u8x8.print("x");
  u8x8.print((int)u8x8.getRows());
  
  delay(2000);
   
  pre();
  for( i = 19; i > 0; i-- )
  {
    u8x8.setCursor(3,2);
    u8x8.print(i);
    u8x8.print("  ");
    delay(150);
  }
  
  draw_bar(0, 1);
  for( c = 1; c < u8x8.getCols(); c++ )
  {
    draw_bar(c, 1);
    draw_bar(c-1, 0);
    delay(50);
  }
  draw_bar(u8x8.getCols()-1, 0);

  pre();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f); 
  for( d = 0; d < 8; d ++ )
  {
    for( r = 1; r < u8x8.getRows(); r++ )
    {
      draw_ascii_row(r, (r-1+d)*u8x8.getCols() + 32);
    }
    delay(400);
  }

  draw_bar(u8x8.getCols()-1, 1);
  for( c = u8x8.getCols()-1; c > 0; c--)
  {
    draw_bar(c-1, 1);
    draw_bar(c, 0);
    delay(50);
  }
  draw_bar(0, 0);

  pre();
  u8x8.drawString(0, 2, "Small");
  u8x8.draw2x2String(0, 5, "Scale Up");
  delay(3000);

  pre();
  u8x8.drawString(0, 2, "Small");
  u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);
  u8x8.drawString(0, 5, "2x2 Font");
  delay(3000);

  pre();
  u8x8.drawString(0, 1, "3x6 Font");
  u8x8.setFont(u8x8_font_inb33_3x6_n);
  for(i = 0; i < 100; i++ )
  {
    u8x8.setCursor(0, 2);
    u8x8.print(i);			// Arduino Print function
    delay(10);
  }
  for(i = 0; i < 100; i++ )
  {
    u8x8.drawString(0, 2, u8x8_u16toa(i, 5));	// U8g2 Build-In functions
    delay(10);		
  }

  pre();
  u8x8.drawString(0, 2, "Weather");
  u8x8.setFont(u8x8_font_open_iconic_weather_4x4);
  for(c = 0; c < 6; c++ )
  {
    u8x8.drawGlyph(0, 4, '@'+c);
    delay(300);
  }
  

  pre();
  u8x8.print("print \\n\n");
  delay(500);
  u8x8.println("println");
  delay(500);
  u8x8.println("done");
  delay(1500);

  pre();
  u8x8.fillDisplay();
  for( r = 0; r < u8x8.getRows(); r++ )
  {
    u8x8.clearLine(r);
    delay(100);
  }
  delay(1000);
}
````


</details>

### Adafruit SH110x
Adafruit display libraries are quite popular because of their modular design. They consist of two separate libraries:

* [Specific Driver Library:](https://github.com/adafruit/Adafruit_SH110x) targets a specific family of display drivers, i.e. *SH110x* drivers
* [Adafruit GFX:](https://github.com/adafruit/Adafruit-GFX-Library) core grafics library which is hardware independent and provides the drawing commands.

This way, source code can be compatible with a variety of displays. You just adjust the specific driver library.


<details><summary>Better not use "hacked" libraries!</summary><br/>

The *SSD1306* was the dominant driver for monochrome OLED displays for a long time. When *SH1106* surfaced a few years later, it initially lacked driver support. 

This is why users *adjusted* the original [Adafruit SSD1306 library](https://github.com/adafruit/Adafruit_SSD1306) to work with *SH1106* as well. Here is one such [edited Adafruit library that is compatible with SH1106](https://github.com/wonho-maker/Adafruit_SH1106), and many others exist.

Unfortunately, these adaptations were not always done according to standards. They may have worked for the original author, and they may also work for you, but there can be header file errors and linker issues when your environment doesn't match the library authors' environment, i.e. because you might be using *platformio* instead of *ArduinoIDE*.

In addition, these adapted libraries aren't updated anymore by the original author and may have become seriously outdated.

By now, Adafruit has released an official library targeting all *SH111x* monochrome OLED displays: [Adafruit_SH110x](https://github.com/adafruit/Adafruit_SH110x). That's the library you should pick if you want to use [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library). 


</details>

<img src="images/oled_sh1106_white_numbers2_t.png" width="30%" height="30%" />


## Conclusions

Getting started with *ESPHome* was incredibly fast—it took me about five minutes to put together and run an example code. In contrast, it took over an hour (including a fair bit of cursing) to figure out the specifics for the *U8G2* library. *ESPHome* is far more efficient, at least for developers.

However, the firmware generated by *ESPHome* is significantly larger than manually compiled C++ code. This is expected because *ESPHome* firmware includes standard features like *OTA updates* and encrypted wireless communication. 

As a result, *C++ programming* is generally best suited for highly proficient developers or cases where memory space is at a premium. For most users—especially those working with microcontrollers like the *ESP32* with 4+ MB of flash memory—*ESPHome* provides a much more streamlined and user-friendly approach to firmware development.


## Data Sheets

[SH1106](materials/sh1106_datasheet.pdf)   





> Tags: HID, Display, OLED, I2C, Driver, SH1106, Monochrome, 132x64, 128x64, 128x32

[Visit Page on Website](https://done.land/components/humaninterface/display/oled/sh1106?448322050807243142) - created 2024-04-28 - last edited 2025-01-10
