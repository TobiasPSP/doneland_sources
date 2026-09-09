<img src="/assets/images/lightning.png" width="100%" height="100%" />


# Automatic Makita Battery Unlocker

> Sophisticated Tool for Monitoring and Unlocking Makita LXT Batteries


The [Automatic Makita Battery Unlocker](https://github.com/synrais/Makita-LXT-Battery-Monitor-Unlocker) is the most sophisticated firmware iteration of date. It is based on the original [OpenBatteryInformation](https://github.com/mnh-jansson/open-battery-information) project but is significantly improved with a focus on reliable unlocking dead batteries. It runs best on *RP2040* but also supports *Arduino Uno/Nano* and *ESP32-C3 SuperMini*.  


## Overview

This tool can work in two ways:

* **Rugged Unlocker Tool:**     
Connect it to a battery, and it automatically detects lock state and unlocks the battery if it was locked. When you run the firmware on a *RP2040 Zero* (or clone), its built-in RGB LED indicates what the tool is doing, whether the unlock was successful, and whether the battery is healthy.

  ***RP2040 Zero* is preferrable** for another reason: you do not need any specific tools to program this MCU. Simply [download the RP2040 firmware file](https://github.com/synrais/Makita-LXT-Battery-Monitor-Unlocker/raw/refs/heads/main/Firmwares/waveshare_rp2040_zero/firmware.uf2), then hold the *Boot* button on the RP2040 when connecting it to a PC. It opens as a USB mass storage device, and to program it, simply drag&drop the downloaded firmware file into this drive.

  If you run the firmware on the other supported MCUs,      
  
  - RGB LED support is missing, so you do not get visual feedback
  - you will need *platformio* or *ArduinoIDE* to compile and upload the firmware yourself. 

* **Monitoring and Reporting:**    
  When you connect the MCU via USB to a PC, the tool dumps detailed battery information to the serial port at 115200 baud. 

  The author also [provides PC software](https://github.com/synrais/Makita-LXT-Battery-Monitor-Unlocker/tree/main/MakitaBatteryMonitor) for Windows and Android, as well as a [Python script](https://raw.githubusercontent.com/synrais/Makita-LXT-Battery-Monitor-Unlocker/refs/heads/main/MakitaBatteryMonitor/PC/build_files/makita_battery_monitor.py) that can be easily adapted to other scripting languages if needed.

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/toolbatteries/makita/makitalxtdigitalinterface/tools/makitabatteryunlocker?342309051114263256) - created 2026-05-13 - last edited 2026-05-13
