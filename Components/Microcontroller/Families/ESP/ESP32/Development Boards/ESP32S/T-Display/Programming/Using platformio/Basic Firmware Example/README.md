<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Basic Firmware Example

> Jump-Start Your T-Display Firmware Projects



The T-Display board comes with a built-in TFT display and two built-in push buttons. Here is a simple platformio.project that illustrates how to work with the two push buttons, and how to display text on the TFT display.

## Overview

The simple firmware created here will do this:

* **Button Press:**    
  When you press one of the two buttons, the display the button you pressed. When you press both buttons simultaneously, "Both buttons" is shown on the display.    
* **TFT Display:**    
  The project illustrates how you write text to the display using the *eTFT* library. The methods in this library allow you to draw geometric shapes and more, so once it is up and running, you can easily extend the sample project.

To start, create a new project in *platform.io*.

## platformio.ini

The first customization happens inside the *platformio.ini* file: open it in VSCode, and replace its content with this:

````
[env:lilygo-t-display]
platform = espressif32
board = lilygo-t-display
framework = arduino
lib_deps = 
  bodmer/TFT_eSPI@^2.5.43
````

Save the file. *Platformio* automatically installs the dependencies, i.e. the referenced *eTFT* library.

## main.cpp
Your source code goes into the file *src/main.cpp*. Replace its content with this:

````cpp
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

const int BTN1_PIN = 0;
const int BTN2_PIN = 35;

const int TEXT_X = 10;
const int TEXT_Y = 40;

String lastText = "";

/*
nmake sure you adjusted user_Setup.h in the eTFT library to match 
your display. 

Uncomment the line:
// #include <User_Setups/Setup25_TTGO_T_Display.h>
and comment out any other display type setup 
*/

TFT_eSPI tft = TFT_eSPI();  

bool initial = 1;

void drawStateText(const String &s) {
  // Option 1: clear the whole line area before drawing
  tft.fillRect(0, TEXT_Y, tft.width(), 20, TFT_BLACK);  // simple "clear line" [web:22][web:30]
  tft.setCursor(TEXT_X, TEXT_Y);
  tft.print(s);
}

void setup(void) {
  // initialize built-in buttons
  pinMode(BTN1_PIN, INPUT_PULLUP);  // active‑low
  pinMode(BTN2_PIN, INPUT_PULLUP);
  Serial.begin(115200);

  // initialize built-in display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK); 
  tft.setTextSize(2);

  drawStateText("No button");

}

void loop() {
  bool b1 = (digitalRead(BTN1_PIN) == LOW);
  bool b2 = (digitalRead(BTN2_PIN) == LOW);

  String text;

  if (!b1 && !b2)       text = "No button";
  else if (b1 && !b2)   text = "Button 1";
  else if (!b1 && b2)   text = "Button 2";
  else                  text = "Both buttons";

  // Only re‑draw when the text actually changes
  if (text != lastText) {
    drawStateText(text);
    lastText = text;
  }

  delay(20);  // basic debounce
}
````
## Adjusting TFT_eSPI Library
The *TFT_eSPI* library is a generic TFT library thats supports all kinds of TFT display sizes and controllers. In order for it to work, you need to adjust a setup file in the library.

In the file explorer, navigate to *.pio/libdeps/lilygo-t-display/TFT_eSPI*, and identify the file *User_Setup_Select.h*. Comment-out the default line:

````cpp
//#include <User_Setup.h>  
````

Then comment-in the line that correctly defines the display driver, display type and SPI pins for your board:

````cpp
#include <User_Setups/Setup25_TTGO_T_Display.h>
````


````cpp
#define ILI9341_DRIVER
````

## Next Steps

Your basic example project is done. You can now **build** and **upload** it in *platformio*. 

Once uploaded, the built-in TFT display shows "No button". Once you press one or both of the built-in buttons, the text changes and shows the pressed buttons.


> Tags: Lilygo, T-Display, platformio, TFT_eSPI, C++, platformio, Template

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/t-display/programming/usingplatformio/basicfirmwareexample?849079031001261309) - created 2026-02-02 - last edited 2026-02-02
