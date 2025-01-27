<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# Hardware vs. Emulation

> Enjoy High Frame Rates And Flicker-Free Displays

Displays require relatively high data transfer rates. For a flicker-free display with smooth animations and high frame rates, it is important to use the hardware supported interfaces that are built into most microcontrollers. Avoid software-emulated interfaces.

## Overview


````c++
#include <SPI.h>
#include "Ucglib.h"
#include <Arduino.h>


// Pin definitions (remapped GPIOs)
#define SCK_PIN       36   // Clock
#define MOSI_PIN      35  // Master Out Slave In
#define MISO_PIN      -1  // Master In Slave Out (if required)
#define CS_PIN        12  // Chip Select for the display, low for normal operations
#define DC_PIN        5   // Data/Command for the display
#define BACKLIGHT_PIN 3   // Resets display, high for normal operations
#define RESET_PIN     -1  // Resets display, high for normal operations, can be connected to EN if exposed
    
// Software-defined SPI: 
//Ucglib_ILI9341_18x240x320_SWSPI ucg(SCK_PIN, MOSI_PIN, DC_PIN, CS_PIN, RESET_PIN);

// Hardware SPI pins:
Ucglib_ILI9341_18x240x320_HWSPI ucg(DC_PIN, CS_PIN, RESET_PIN);

float_t fps_text;
float_t fps_box;
float_t fps_gradient;
float_t secondsToTest = 10.0;

// pseudo-random generator (LCG)
uint8_t z = 127;	// start value
uint8_t lcg_rnd(void) {
  z = (uint8_t)((uint16_t)65*(uint16_t)z + (uint16_t)17);
  return z;
}



void draw_text(void) {
  ucg.setFont(ucg_font_ncenR14_tr);
  //ucg.setColor(255, 255, 255);
  ucg.setColor(lcg_rnd(),lcg_rnd(),lcg_rnd());
  ucg.setPrintPos(0,20);
  ucg.print("The quick brown");
  ucg.setPrintPos(0,40);
  ucg.print("fox jumps over");
  ucg.setPrintPos(0,60);
  ucg.print("the lazy dog");
}

void draw_box(void) {
  ucg_int_t x, y, w, h;
  ucg.setColor(lcg_rnd(),lcg_rnd(),lcg_rnd());
  x = lcg_rnd() & 31;
  y = lcg_rnd() & 31;
  w = 63;
  w += lcg_rnd() & 31;
  h = 63;
  h += lcg_rnd() & 31;
  ucg.drawBox(x,y,w, h);
}

void draw_gradient_box(void) {
  ucg_int_t x, y, w, h;
  static uint8_t idx = 0;
  switch(idx & 3)
  {
    case 0: ucg.setColor(0, lcg_rnd(),lcg_rnd(),lcg_rnd()); break;
    case 1: ucg.setColor(1, lcg_rnd(),lcg_rnd(),lcg_rnd()); break;
    case 2: ucg.setColor(2, lcg_rnd(),lcg_rnd(),lcg_rnd()); break;
    case 3: ucg.setColor(3, lcg_rnd(),lcg_rnd(),lcg_rnd()); break;
  }
  idx++;
  x = lcg_rnd() & 31;
  y = lcg_rnd() & 31;
  w = 63;
  w += lcg_rnd() & 31;
  h = 63;
  h += lcg_rnd() & 31;
  ucg.drawGradientBox(x,y,w, h);
}


// returns FPS*10
float_t measure(void (*draw_fn)(void)) {
  uint16_t fps = 0;
  uint32_t time;


  time = millis() + secondsToTest*1000;
  do {
    draw_fn();
    fps++;
  } while( millis() < time );
  
  return fps/secondsToTest;  
}



void show_result()  {
  ucg.clearScreen();
  ucg.setFont(ucg_font_helvR18_tr);
  ucg.setColor(255, 255, 255);
  
  ucg.setPrintPos(0,50);
  ucg.print("Text");
  ucg.setPrintPos(130,50);
  ucg.print(fps_text);  

  ucg.setPrintPos(0,100);
  ucg.print("Box");
  ucg.setPrintPos(130,100);
  ucg.print(fps_box);  

  ucg.setPrintPos(0,150);
  ucg.print("Gradient");
  ucg.setPrintPos(130,150);
  ucg.print(fps_gradient);  
}



void setup(void) {
  Serial.begin(115200);
  delay(5000);

  // Print the default hardware SPI pins
  Serial.printf("Default SCK: %d\n", SCK);
  Serial.printf("Default MOSI: %d\n", MOSI);
  Serial.printf("Default MISO: %d\n", MISO);

  
  // Backlight
  pinMode(BACKLIGHT_PIN, OUTPUT);

  // full brightness or off
  // digitalWrite(BACKLIGHT_PIN, HIGH);
  // dimmable (dark-bright: 0-255)
  analogWrite(BACKLIGHT_PIN, 180);

  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setColor(0, 0,0,0);
  ucg.setColor(1, 0,0,0);
  ucg.setColor(2, 0,0,0);
  ucg.setColor(3, 0,0,0);

  fps_text = measure(draw_text);
  fps_box = measure(draw_box);
  fps_gradient = measure(draw_gradient_box);
  
  // perform tests:
  show_result();

  Serial.printf("Text: %d\n", fps_text);
  Serial.printf("Box: %d\n", fps_box);
  Serial.printf("Gradient: %d\n", fps_gradient);
}

void loop(void)
{
  
}
````


> Tags: Display, Interface, Connect, I2C, SPI, TFT, OLED

[Visit Page on Website](https://done.land/components/humaninterface/display/usage/connecting/hardwarevsemulation?950826011326253154) - created 2025-01-25 - last edited 2025-01-25
