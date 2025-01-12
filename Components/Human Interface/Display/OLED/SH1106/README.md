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

<img src="images/oled_sh1106_white_text_t.png" width="60%" height="60%" />

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

### ESPHome

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


You can now use all the graphics commands supported by the [ESPHome Display Component](https://esphome.io/components/display/index.html) to draw images, shapes, lines, arcs, etc.
### C++

For direct programming (using the *Arduino Framework*), two popular libraries support the *SH1106*:

- **U8G2 Library**
- **Adafruit GFX Library**

### U8G2 Library

The *U8G2 library* is a versatile and robust option that supports a wide range of **monochrome** display drivers.

#### Selecting the OLED Driver

Since *U8G2* supports many different drivers, you need to specify your driver at the beginning of the code. 

The example code typically includes a large block of commented lines describing supported drivers and hardware. To select the *SH1106*, uncomment the line corresponding to your required resolution (e.g., *128x64*).

#### Example Code

Compared to *ESPHome* (see above), running *C++ code* can be more challenging. Even though external libraries like *U8G2* handle much of the complexity, there is no universal standard for configuring settings. Determining where to set options such as *I2C GPIOs*, *I2C device address*, and *display resolution* often requires trial and error.

This is where *ESPHome* excels: all settings are centralized in a well-documented configuration file, making the process more streamlined.

In the *U8G2* C++ example, the display interface and resolution are selected through the *class*. For a *128x64 SH1106 OLED display* connected via *I2C*, you can use one of the following classes:

- **`U8X8_SH1106_128X64_NONAME_HW_I2C`**: For hardware *I2C*.
- **`U8X8_SH1106_128X64_NONAME_SW_I2C`**: For software *I2C* (allows custom *I2C GPIOs*).

Once you’ve configured the appropriate class, the rest of the code is straightforward. I successfully tested this approach on *ESP32*, *ESP32-S2*, and *ESP32-C3*. 

> **Tip:** Ensure the *I2C GPIOs* in your code match your hardware setup; otherwise, the display will remain dark.


<details><summary>C++ Source Code</summary><br/>


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

### Adafruit Library

The *SH1106* initially lacked the same level of driver support as the *SSD1306*, leading users to adapt existing *SSD1306* libraries for compatibility with the *SH1106*. 

Unfortunately, these adaptations were not always done according to standards. For instance, an *Adafruit* library ported from their original *SSD1306* library contains crude tweaks, which can cause header file errors and linker issues when used in *PlatformIO*. These problems might have been resolved by the time you read this, so it’s still worth giving the library a try.

<img src="images/oled_sh1106_white_numbers2_t.png" width="30%" height="30%" />

> [!NOTE]  
> Libraries for specific drivers may behave inconsistently depending on the *IDE*. If a library fails in *PlatformIO*, try running it in *ArduinoIDE* to verify its compatibility. A well-designed library should not display such peculiar behavior.

### Thoughts

Getting started with *ESPHome* was incredibly fast—it took me about five minutes to put together and run an example code. In contrast, it took over an hour (including a fair bit of cursing) to figure out the specifics for the *U8G2* library. *ESPHome* is far more efficient, at least for developers.

However, the firmware generated by *ESPHome* is significantly larger than manually compiled C++ code. This is expected because *ESPHome* firmware includes standard features like *OTA updates* and encrypted wireless communication. 

As a result, *C++ programming* is generally best suited for highly proficient developers or cases where memory space is at a premium. For most users—especially those working with microcontrollers like the *ESP32* with 4+ MB of flash memory—*ESPHome* provides a much more streamlined and user-friendly approach to firmware development.


## Data Sheets

[SH1106](materials/sh1106_datasheet.pdf)   





> Tags: HID, Display, OLED, I2C, Driver, SH1106, Monochrome, 132x64, 128x64, 128x32

[Visit Page on Website](https://done.land/components/humaninterface/display/oled/sh1106?448322050807243142) - created 2024-04-28 - last edited 2025-01-10
