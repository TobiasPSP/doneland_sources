<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# C3

> The First ESP Microcontroller Based on RISC-V Architecture And A Very Fast One-Core CPU


In 2020, *Expressif* released both the *S-Series* and the first member of the *C-Series*.

## C3 - RISC-V Architecture

The **ESP32-C3** marks a fundamental change in processor architecture as it now uses *RISC-V*. The **C3** is a *very fast* one-core microcontroller.

<img src="images/esp32_c3_seed_top_front_t.png" width="40%" height="40%" />

The **C3** is a very cost-effective microcontroller that comes in development boards with a *tiny form factor*. The [Wemos/Lolin C3 Mini](https://www.wemos.cc/en/latest/c3/c3_mini.html) shares the form factor with the old and highly popular *ESP8266 D1 Mini*, so you can continue to use *shields* (i.e. power supply and battery shields) designed for the *D1 Mini*.

The *ESP32-C3 Super Mini* board is even smaller: with *22.5x18mm*, it can fit into even the smallest projects and DIY devices. Unfortunately, there does not seem to be an official source of documentation for this popular and widely available board. Here is an [unofficial summary](material/esp32_c3_supermini_datasheet_artronshop.co.th.pdf) for the *ESP32-C3 Super Mini* found in the Internet.


## Changes Compared To ESP32 WROOM/WROVER

Here is the list of removed or reduced features compared to **ESP32**:

| Feature | Removal |
| --- | --- |
| Cores  | 1 instead of 2 |
| Frequency  | reduced from 240 to 160 |
| SRAM  | reduced from 520 to 400 |
| ROM | reduced from 448 to 384 |
| RTC RAM | reduced from 16 to 8 |
| GPIOs | reduced from 34 to 22 |
| LED PWM | reduced from 16 to 6 |
| UART  | reduced from 3 to 2 |
| SPI | reduced from 4 to 3 |
| ADC | reduced channels from 18 to 6 |
| Motor PWM | removed |
| Touch | removed |
| DAC | removed |
| SD support | removed |
| Hall Sensor | removed |
| Ethernet | removed |
| Camera support | removed | 

## New Features

This is what's new:

| Feature | Addition |
| --- | --- |
| Bluetooth | BLE v5.0 instead of BLE v4.2 |
| WiFi | WiFi-Alliance/WPA 3 certified |
| Temperature Sensor | added |
| SD Host | extended from 1 to 2 |
| USB OTG | added |

> Tags: Microcontroller, ESP32, ESP32 C3, C3, RISC-V

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3?432279031823244200) - created 2024-03-23 - last edited 2024-03-23
