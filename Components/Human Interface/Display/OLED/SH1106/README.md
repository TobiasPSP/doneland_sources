<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# SH1106-Based OLED Display

> 1.3 Inch Monochrome OLED Displays For Little Money

*SH1106* is a *OLED display driver* very similar to the popular *SSD1306*. It supports monochrome displays with a maximum resolution of *132x64* pixels and typically uses *I2C*.


<img src="images/oled_sh1106_white_text_t.png" width="30%" height="30%" />


This driver is frequently used in *1.3inch 128x64* display breakout boards. The *SH1106* is rather used in the *0.9inch 128x64* display breakout boards.

> [!CAUTION]
> *SH1106* boards use the pins *GND* and *VDD* in  opposite order compared to *SSD1306* (may be coincidental).



<img src="images/oled_sh1106_white_alpha_t.png" width="30%" height="30%" />

The same applies to breakout boards with *integrated OLED displays* like the *keyboard-display-combo* below:

<img src="images/oled_sh1106_keyboard_t.png" width="60%" height="60%" />

These boards are available with *0.96inch* and *1.3inch* displays. Like with the standalone boards, *SH1106* is typically used in the *1.3inch* version.



> [!TIP]
> The *SH1106* is a great and economical *OLED driver* to display *text* and *static images*. Once you require *animations* like *scrolling*, the *SSD1306* is much better suited (and even more so the many other any more advanced/expensive driver models): *SH1106* does not come with any hardware animation or scrolling support.








## Colors
The *display* comes in different colors: *white*, *blue*, *yellow*.


## Libraries
The *SH1106* does not have the same level of driver support that the *SSD1306* enjoys. 

That's why users have started to tweak and adapt *SSD1306* libraries to use them with *SH1106*. Unfortunately, adaptions were not always done according to standard.


<img src="images/oled_sh1106_white_numbers2_t.png" width="30%" height="30%" />


There is one *Adafruit* library for example that was ported from their original *SSD1306* but apparently tweaking was done rather rude so that errors in the header file produce linker errors now when using the code in *platform.io*.

### U8G2 Library To The Rescue
If you cannot find a dedicated library for a particular *monochrome* display driver, then the library *u8g2* is your best shot. 

This library aims to be compatible to *as many different drivers and different boards as possible*. It runs fine in *platformio*, and I used it with a *ESO32 S2 Mini*.

### Selecting OLED Driver
Since the library *u8g2* is not targeting a *specific driver*, you can select the *driver* at the beginning of the code:

All examples start with a huge section of commented lines. Each line describes a particular driver and OLED hardware. 

To select a particular driver (like the *SH1106*),  uncomment the line for this driver in the resolution you require.

### Example Code
The example code below is taken directly from the *u8g2* examples. 

I just removed the entire comment block at the beginning, and just kept the lines for the *SH1106 I2C driver*. Since I tested with a *132x64* pixel display, I uncommented the line for the *128x64* display.

There was nothing else to configure. The code compiled flawlessly in *platform.io* and ran perfectly on a *ESP32 S2 Mini*.



````c++
/*

  GraphicsTest.ino
  
  Some graphics/text output for U8x8 API

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/
#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
//U8X8_SH1106_128X32_VISIONOX_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 

void setup(void)
{
  u8x8.begin();
  //u8x8.setFlipMode(1);
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

This is the *platformio.ini* I used to compile the sketch in *platform.io* and run it on a *ESP32 S2 Mini*:

````
[env:lolin_s2_mini]
platform = espressif32
board = lolin_s2_mini
framework = arduino
lib_deps = 
	olikraus/U8g2@^2.35.19
````


## Data Sheets

[SH1106](materials/sh1106_datasheet.pdf)   





> Tags: HID, Display, OLED, I2C, Driver, SH1106, Monochrome, 132x64, 128x64, 128x32

[Visit Page on Website](https://done.land/components/humaninterface/display/oled/sh1106?448322050807243142) - created 2024-05-06 - last edited 2024-05-06
