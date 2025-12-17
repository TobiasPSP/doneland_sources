<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Arduino Nano

> Arduino Nano is a compact 5V board with 8-bit ATmega328P running at 16 MHz, 32 KB flash, 2 KB SRAM, 1 KB EEPROM, 14 digital I/O pins (6 PWM), and 8 analog inputs


The original *Arduino Nano* was released in 2008. Today, there are also very affordable *Arduino Nano Clones* for less than €2. Even though more modern MCUs like [ESP32](https://done.land/components/microcontroller/families/esp/esp32/) offer vastly superior performance, *Arduino Nano* can still be an excellent choice for its low power consumption since many projects do not require high computational performance.

## Overview

*Arduino Nano* is a good development board for simple automation tasks, especially when low power consumption is important. For example, an Arduino Nano board draws around 20-50mA when in contrast a ESP32 can draw up to 240mA.

There are a few caveats though that you should consider before looking deeper into using an Arduino Nano:

* **No Radio:**      
  Arduino Nano does not come with any radio capabilities (WiFi, Bluetooth).    
* **Small Memory:**    
  There are just 30 KB usable flash memory, compared to 4-16 MB flash memory in ESP32. If your firmware gets more complex, you may run into memory issues.    
* **Voltage:**    
  Arduino Nano runs on 5V whereas ESP32 runs on 3.3V. This may be important in respect to the peripherals you plan to connect to the board.   

## Arduino Nano Clones

Today, Arduino Nano Clones are commonplace and very affordable. Clones typically use the "old" bootloader, so this is the `platformio.ini` for [platformio](https://platformio.org/) that you most likely need to use:

````
[env:nano_old]
platform  = atmelavr
board     = nanoatmega328
framework = arduino
upload_speed = 57600
````

> Tags: Microcontroller, Arduino Nano, Clone, Bootloader

