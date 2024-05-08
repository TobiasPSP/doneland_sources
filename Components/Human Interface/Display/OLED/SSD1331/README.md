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

### Confusing Pin Labels

The *pin labels* on this *OLED display breakout board* are *confusing* because they do not use the commonly used *SPI pin names*. Instead, some pins are labeled *SCL* and *SDA* which would typically indicate support for *I2C* interfaces.


<img src="images/oled_ssh1331_pins_t.png" width="100%" height="100%" />

That is *not the case*. The display supports *SPI*. It does not support *I2C*. Here is what the pins do:



The display has seven pins:

| Pin | Label | Description |
| --- | --- | --- |
| 1 | GND | Ground |
| 2 | VCC | *3.3-5.0V* |
| 3 | SCL | SPI: Clock (SCLK, CLK) |
| 4 | SDA | SPI: MOSI |
| 5 | RES | Reset |
| 6 | DC | Data/Command |
| 7 | CS | SPI: Chip Select |

The *SPI* interface is implemented as a typical *three-wire design* using the pins *SDA* (*MOSI*), *SCL* (*CLK*), and *CS*.


> [!TIP]
> Pin *DC* is not common and used with components that can receive large amounts of data (such as *displays*): when this pin is pulled *low*, it indicates that the data received is a *command*, else *display data*.



### Connecting To ESP32 S2 Mini
In my tests, I am connecting the display to a *ESP32 S2 Mini* like so:

| Pin S2 | Pin Display | Description |
| --- | --- | --- |
| Gnd | Gnd | Ground |
| VCC | 3V3 | 3.3V |
| SCL | 7 | SPI Clock |
| CS | 12 | SPI Chip Select |
| SDA | 11 | SPI MOSI |
| RES | 33 | Reset |
| DC | 35 | Data/Command |





<img src="images/oled_ssh1331_back_t.png" width="60%" height="60%" />




### Example Code
Here is example code taken from the *Adafruit SSD1306 library* that I used to create the pictures on this page. The code is already adjusted and runs fine in *platformio*:

````c++
/***************************************************
  This is a example sketch demonstrating the graphics
  capabilities of the SSD1331 library  for the 0.96"
  16-bit Color OLED with SSD1331 driver chip

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/684

  These displays use SPI to communicate, 4 or 5 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>


// You can use any (4 or) 5 pins
#define sclk 7
#define mosi 11
#define cs   12
#define rst  33
#define dc   35


// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

// Option 1: use any pins but a little slower
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

// Option 2: must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
//Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst);

float p = 3.1415926;


void testlines(uint16_t color) {
   display.fillScreen(BLACK);
   for (int16_t x=0; x < display.width()-1; x+=6) {
     display.drawLine(0, 0, x, display.height()-1, color);
   }
   for (int16_t y=0; y < display.height()-1; y+=6) {
     display.drawLine(0, 0, display.width()-1, y, color);
   }

   display.fillScreen(BLACK);
   for (int16_t x=0; x < display.width()-1; x+=6) {
     display.drawLine(display.width()-1, 0, x, display.height()-1, color);
   }
   for (int16_t y=0; y < display.height()-1; y+=6) {
     display.drawLine(display.width()-1, 0, 0, y, color);
   }

   // To avoid ESP8266 watchdog timer resets when not using the hardware SPI pins
   delay(0);

   display.fillScreen(BLACK);
   for (int16_t x=0; x < display.width()-1; x+=6) {
     display.drawLine(0, display.height()-1, x, 0, color);
   }
   for (int16_t y=0; y < display.height()-1; y+=6) {
     display.drawLine(0, display.height()-1, display.width()-1, y, color);
   }

   display.fillScreen(BLACK);
   for (int16_t x=0; x < display.width()-1; x+=6) {
     display.drawLine(display.width()-1, display.height()-1, x, 0, color);
   }
   for (int16_t y=0; y < display.height()-1; y+=6) {
     display.drawLine(display.width()-1, display.height()-1, 0, y, color);
   }

}

void testdrawtext(char *text, uint16_t color) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
}

void testfastlines(uint16_t color1, uint16_t color2) {
   display.fillScreen(BLACK);
   for (int16_t y=0; y < display.height()-1; y+=5) {
     display.drawFastHLine(0, y, display.width()-1, color1);
   }
   for (int16_t x=0; x < display.width()-1; x+=5) {
     display.drawFastVLine(x, 0, display.height()-1, color2);
   }
}

void testdrawrects(uint16_t color) {
 display.fillScreen(BLACK);
 for (int16_t x=0; x < display.height()-1; x+=6) {
   display.drawRect((display.width()-1)/2 -x/2, (display.height()-1)/2 -x/2 , x, x, color);
 }
}

void testfillrects(uint16_t color1, uint16_t color2) {
 display.fillScreen(BLACK);
 for (int16_t x=display.height()-1; x > 6; x-=6) {
   display.fillRect((display.width()-1)/2 -x/2, (display.height()-1)/2 -x/2 , x, x, color1);
   display.drawRect((display.width()-1)/2 -x/2, (display.height()-1)/2 -x/2 , x, x, color2);
 }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (uint8_t x=radius; x < display.width()-1; x+=radius*2) {
    for (uint8_t y=radius; y < display.height()-1; y+=radius*2) {
      display.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < display.width()-1+radius; x+=radius*2) {
    for (int16_t y=0; y < display.height()-1+radius; y+=radius*2) {
      display.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  display.fillScreen(BLACK);
  int color = 0xF800;
  int t;
  int w = display.width()/2;
  int x = display.height();
  int y = 0;
  int z = display.width();
  for (t = 0 ; t <= 15; t+=1) {
    display.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  display.fillScreen(BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = display.width();
    int h = display.height();
    for(i = 0 ; i <= 8; i+=1) {
      display.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  display.fillScreen(BLACK);
  display.setCursor(0, 5);
  display.setTextColor(RED);
  display.setTextSize(1);
  display.println("Hello World!");
  display.setTextColor(YELLOW, GREEN);
  display.setTextSize(2);
  display.print("Hello Wo");
  display.setTextColor(BLUE);
  display.setTextSize(3);
  display.print(1234.567);
  delay(10000);
  display.setCursor(0, 5);
  display.fillScreen(BLACK);
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.println("Hello World!");
  display.setTextSize(1);
  display.setTextColor(GREEN);
  display.print(p, 5);
  display.println(" Want pi?");
  display.print(8675309, HEX); // print 8,675,309 out in HEX!
  display.print(" Print HEX");
  display.setTextColor(WHITE);
  display.println("Sketch has been");
  display.println("running for: ");
  display.setTextColor(MAGENTA);
  display.print(millis() / 1000);
  display.setTextColor(WHITE);
  display.print(" seconds.");
}

void mediabuttons() {
 // play
  display.fillScreen(BLACK);
  display.fillRoundRect(25, 10, 78, 60, 8, WHITE);
  display.fillTriangle(42, 20, 42, 60, 90, 40, RED);
  delay(500);
  // pause
  display.fillRoundRect(25, 90, 78, 60, 8, WHITE);
  display.fillRoundRect(39, 98, 20, 45, 5, GREEN);
  display.fillRoundRect(69, 98, 20, 45, 5, GREEN);
  delay(500);
  // play color
  display.fillTriangle(42, 20, 42, 60, 90, 40, BLUE);
  delay(50);
  // pause color
  display.fillRoundRect(39, 98, 20, 45, 5, RED);
  display.fillRoundRect(69, 98, 20, 45, 5, RED);
  // play color
  display.fillTriangle(42, 20, 42, 60, 90, 40, GREEN);
}

/**************************************************************************/
/*!
    @brief  Renders a simple test pattern on the LCD
*/
/**************************************************************************/
void lcdTestPattern(void)
{
  uint8_t w,h;
  display.setAddrWindow(0, 0, 96, 64);

  for (h = 0; h < 64; h++) {
    for (w = 0; w < 96; w++) {
      if (w > 83) {
        display.writePixel(w, h, WHITE);
      } else if (w > 71) {
        display.writePixel(w, h, BLUE);
      } else if (w > 59) {
        display.writePixel(w, h, GREEN);
      } else if (w > 47) {
        display.writePixel(w, h, CYAN);
      } else if (w > 35) {
        display.writePixel(w, h, RED);
      } else if (w > 23) {
        display.writePixel(w, h, MAGENTA);
      } else if (w > 11) {
        display.writePixel(w, h, YELLOW);
      } else {
        display.writePixel(w, h, BLACK);
      }
    }
  }
  display.endWrite();
}

void setup(void) {
  Serial.begin(9600);
  Serial.print("hello!");
  display.begin();

  Serial.println("init");
  uint16_t time = millis();
  display.fillScreen(BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(10000);

  lcdTestPattern();
  delay(10000);

  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa");
  delay(10000);

  // tft print function!
  tftPrintTest();
  delay(10000);

  //a single pixel
  display.drawPixel(display.width()/2, display.height()/2, GREEN);
  delay(10000);

  // line draw test
  testlines(YELLOW);
  delay(10000);

  // optimized lines
  testfastlines(RED, BLUE);
  delay(10000);

  testdrawrects(GREEN);
  delay(10000);

  testfillrects(YELLOW, MAGENTA);
  delay(10000);

  display.fillScreen(BLACK);
  testfillcircles(10, BLUE);
  testdrawcircles(10, WHITE);
  delay(10000);

  testroundrects();
  delay(10000);

  testtriangles();
  delay(10000);

  display.fillScreen(BLACK);
  Serial.println("done");
}

void loop() {
}
````

This is the *platformio.ini* I used to compile the sketch in *platform.io* and run it on a *ESP32 S2 Mini*:

````
[env:lolin_s2_mini]
platform = espressif32
board = lolin_s2_mini
framework = arduino
lib_deps = adafruit/Adafruit SSD1331 OLED Driver Library for Arduino@^1.2.0
````


## Data Sheets

[SSD1331](materials/ssd1331_datasheet.pdf)   





> Tags: HID, Display, OLED, Color, 16K, SPI, Driver, SSD1331, 96x64
