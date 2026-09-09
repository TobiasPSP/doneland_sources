<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# I2C Scanner

> Simple Tool For Testing I2C Devices


Test whether I2C devices are functional, and identify their I2C address(es).


## Overview

Tools do not need to be complex to be useful, so here I am implementing a simple I2C address scanner which is a perfect example for a T-Display development board.

I want the tool to be ready to use when-ever and where-ever I need it. Specifically, I want it to run on battery and not require a PC or serial monitor to display results. T-Display has all that is required:

* **Battery:**     
  Comes with full 1S LiIon cell support, including charger.
* **Display:**   
  Comes with a relatively large color TFT display which is perfect for displaying the results.
* **Push Buttons:**   
  Comes with two programmable push buttons that can be used to trigger I2C address scans.


## platformio.ini

The first step is to define the hardware in *platformio.ini*. This takes care of almost everything:

* downloads the required TFT display driver
* configures the TFT driver for the specific display used by T-Display
* enables full 16MB flash memory (although not needed by this tiny sketch)


````
[env:lilygo-t-display]
platform = espressif32
board = lilygo-t-display
framework = arduino
lib_deps = 
  bodmer/TFT_eSPI
build_flags =
    -D USER_SETUP_LOADED=1
    -include $PROJECT_LIBDEPS_DIR/$PIOENV/TFT_eSPI/User_Setups/Setup25_TTGO_T_Display.h

# unlock full flash size:
board_build.flash_size = 16MB  
# maximize flash size for firmware if no OTA req:
board_build.partitions = no_ota.csv
# set default serial speed:
monitor_speed = 115200
# enable serial output (prevent reboot loop):
monitor_rts = 0
monitor_dtr = 0
````

Once you save the file inside *Platformio*, it automatically starts downloading and installing the dependencies, i.e. the referenced *TFT_eSPI* library.

## main.cpp
Your source code goes into the file *src/main.cpp*. Replace its content with this:

````cpp
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h>

const int BTN2_PIN = 35;
bool isScanning = false;

TFT_eSPI tft = TFT_eSPI();  

void setup() {
  // initialize I2C
  Wire.begin();

  // initialize built-in buttons
  pinMode(BTN2_PIN, INPUT_PULLUP);
  
  // enable weak pullups on I2C pins to avoid floating state when no device is connected
  pinMode(SDA, INPUT_PULLUP);
  pinMode(SCL, INPUT_PULLUP);
  
  // initialize serial for debug output
  Serial.begin(115200);
  while(!Serial);

  // initialize built-in display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK); 
  tft.setTextSize(2);
  
  // display I2C pins:
  tft.println("I2C Scanner");
  tft.print("SDA=");
  tft.println(SDA);
  tft.print("SCL=");
  tft.println(SCL);
  tft.println();
  tft.println("Press button");
  tft.println("to start.");
}

void scanI2C() {
  if (!isScanning) return;

  byte error, address;

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0,0);
  tft.println("Scanning:");
  Serial.println("Scanning I2C bus...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {

      if (address < 16) {
          tft.print("0");
          Serial.print("0");
      }
      tft.println(address, HEX);
      Serial.println(address, HEX);      
    }
    else if (error == 4) {
      tft.print("E:");
      Serial.print("Error at address 0x");
      if (address < 16) {
        tft.print("0");
        Serial.print("0");
      }
      tft.println(address, HEX);
      Serial.println(address, HEX);
    }
  }
}

void handleButtons() {
  // read button state (active LOW)
  bool button = (digitalRead(BTN2_PIN) == LOW);

  // toggle scan:
  if (button) {
    if (isScanning) {
      tft.println("Scan stopped.");
      tft.println("Press button");
      tft.println("to start.");
    }
    isScanning = !isScanning;
  }

  delay(100); // debounce delay
}

void loop() {
  handleButtons();  
  scanI2C();
  delay(500);
}
````

> Tags: I2C, I2C Scanner, T-Display

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/t-display/programming/usingplatformio/i2cscanner?908964031516262914) - created 2026-03-15 - last edited 2026-03-15
