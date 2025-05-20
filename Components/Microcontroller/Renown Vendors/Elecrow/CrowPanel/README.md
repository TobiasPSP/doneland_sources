<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# CrowPanel

> Awesome All-In-One Boards For Learning Or Use In Sophisticated Projects


*CrowPanel* development boards are highly integrated *ESP32*-based development boards with a display. 

The **basic** line uses *ESP32S* with *4MB* flash memory and *resistive* touch, whereas the **advanced** line utilizes the more powerful *ESP32-S3* with *16MB* flash memory and *capacitive* touch.

This is a picture of the backside of a [CrowPanel Advance](https://www.elecrow.com/crowpanel-advance-7-0-hmi-esp32-ai-display-800x480-artificial-intelligent-ips-touch-screen-support-meshtastic-and-arduino-lvgl-micropython.html?idd=5):

<img src="images/backside_pf_esp32_advance_hmi_7inch_screen_t.png" width="100%" height="100%" />

The *CrowPanel* combo can be a great one-stop solution for many audiences:

* **Beginners:** the [CrowPanel Advanced](https://www.elecrow.com/catalogsearch/result/?q=crowpanel+advanced&idd=5) comes with built-in microphone, amplifier, and speaker, plus a touch display. This enables beginners to experiment and explore a rich set of examples, avoiding a steep learning curve. 
* **Advanced Users:** Experienced users find many important peripherals already built into the board, especially with the **advanced** series, enabling them to build small and reliable devices without having to manually design PCBs and add peripherals.
* **Industry:** *CrowPanels* can be cost-effective all-in-one solutions that are simpler to integrate into products than own developments.




## Overview

What sets *CrowPanels* apart from other development boards:

- **Integrated Touch Display:** ranging from *2.4"* to *7"*, *CrowPanel* always comes with a built-in touch display.
- **Rich Peripherals:** With *CrowPanel Advance*, integration of numerous peripherals like microphone, speaker, RTC, etc., enabling compact project designs and providing an excellent platform for learning and experimentation out-of-the-box.
- **Comprehensive Documentation:** Free, detailed video [tutorials on YouTube](https://www.youtube.com/playlist?list=PLwh4PlcPx2GcKJ17Z_xcAxQoh-Tmms_X1) support self-learning and exploration. This may be one of the most important advantages for hobbyists: no time-consuming and often frustrating research just to find out how the board works.

| Product | Free Video Learning Tutorial |
| --- | --- |
| CrowPanel Basic | [YouTube](https://www.youtube.com/playlist?list=PLwh4PlcPx2GcKJ17Z_xcAxQoh-Tmms_X1) |
| CrowPanel Advanced | [YouTube](https://www.youtube.com/playlist?list=PLwh4PlcPx2Gfrtm7TmlARyF4ccTmIy-gK) |

### Battery Support
All *CrowPanel* support rechargeable *LiIon* batteries that can be directly connected to the panel. The panel includes a charger, so when it is connected to stationary USB-C, it automatically charges an attached *LiIon* battery.

## Basic Series

*CrowPanels* originally started as **basic** [Elecrow CrowPanel Display HMI](https://www.elecrow.com/esp32-display-series-hmi-touch-screen.html?idd=5), using the classic *ESP32S* microcontroller with *4MB* flash memory and *resistive* displays in various sizes. 

<img src="images/5.0_hmi_esp32_display_t.png" width="100%" height="100%" />


| Size                | 2.4  | 2.8  | 3.5  | 4.3  | 5.0  | 7.0  | ESP32 Terminal-3.5 RGB Display | ESP32 Terminal-3.5 SPI Display |
|---------------------|------|------|------|------|------|------|-------------------------------|-------------------------------|
| Camera              | -    | -    | -    | -    | -    | -    | -                             | yes                           |
| Resolution          | 320×240 | 320×240 | 480×320 | 480×272 | 800×480 | 800×480 | 480×320 | 480×320 |
| Touch Type          | Resistive | Resistive | Resistive | Resistive | Capacitive | Capacitive | Capacitive | Capacitive |
| Main Processor      | ESP32-WROOM-32-N4 | ESP32-WROOM-32-N4 | ESP32-WROVER-B | ESP32-S3-WROOM-1-N4R2 | ESP32-S3-WROOM-1-N4R8 | ESP32-S3-WROOM-1-N4R8 | ESP32-S3-WROOM-2 | ESP32-S3-WROOM-2 |
| Frequency           | 240MHz | 240MHz | 240MHz | 240MHz | 240MHz | 240MHz | 240MHz | 240MHz |
| Flash               | 4MB   | 4MB   | 4MB   | 4MB   | 4MB   | 4MB   | 16MB  | 16MB  |
| SRAM                | 520KB | 520KB | 520KB | 512KB | 512KB | 512KB | 512KB | 512KB |
| ROM                 | 448KB | 448KB | 448KB | 384KB | 384KB | 384KB | 384KB | 384KB |
| PSRAM               | /     | /     | 8MB   | 2MB   | 8MB   | 8MB   | 8MB   | 8MB   |
| Display Driver      | ILI9341V | ILI9341V | ILI9488 | NV3047 | IL16122 + IL15960 | EK9716BD3 + EK73002ACGB | ILI9488 | ILI9488 |
| Screen              | TFT   | TFT   | TFT   | TFT   | TFT   | TFT   | TFT   | TFT   |
| Type Interface      | 1*UART0, 1*UART1, 1*I2C, 1*GPIO, 1*Battery | 1*UART0, 1*UART1, 1*I2C, 1*GPIO, 1*Battery | 2*UART0, 1*I2C, 1*GPIO, 1*Battery | 1*UART0, 2*UART1, 2*GPIO, 1*Battery | 2*UART0, 2*GPIO, 2*I2C, 1*Battery | 2*UART0, 2*GPIO, 2*I2C, 1*Battery | 1*UART, 1*Analog, 1*IIC, 1*Digital, 1*Battery | 1*UART, 2*Analog, 1*IIC, 2*Digital, 1*Battery |
| Speaker Jack        | YES   | YES   | YES   | YES   | YES   | YES   | NO    | NO    |
| TF Card Slot        | YES   | YES   | YES   | YES   | YES   | YES   | YES   | YES   |
| Active Area         | 36.72×48.96mm (W×H) | 43.2×57.6mm (W×H) | 48.96×73.44mm (W×H) | 95.04×53.8mm (W×H) | 108×64.8mm (W×H) | 153.84×85.63mm (W×H) | 49.79×73.63mm (W×H) | 49.79×73.63mm (W×H) |

This series was quickly adopted both by DIY/makers, smart home enthusiasts, and industry products that used the *CrowPanel* as highly integrated module.



## Advanced Series
Since its debut, newer and more powerful processors have emerged, so *Elecrow* added **advanced** [Elecrow CrowPanel Advance](https://www.elecrow.com/display/esp-hmi-display/esp32-hmi-display-advance-series.html?idd=5) panels that now use the much more powerful *ESP32-S3*. Its flash memory was quadrupled (from *4MB* to *16MB*), and many other features were [significantly enhanced](https://www.elecrow.com/blog/crowpanel-advance-what-sets-it-apart-from-the-basic-series.html?idd=5), too.


<img src="images/hardware_overview_of_esp32_advance_7inchhmi_display.jpg" width="100%" height="100%" />


| Feature         | Remark |
|-----------------|--------|
| Microcontroller | *ESP32-S3* replaces the *ESP32S* |
| Memory          | 16MB of flash memory (up from 4MB) |
| Display         | Brightness up from 175 cd/m² to 400 cd/m²  |
| Touch           | *Capacitive* panels (true finger touch) instead of *resistive* (stylus required) |
| Voice/Audio     | Built-in microphone, amplifier, and speaker for AI, speech recognition, hands-free use, and audio playback |
| Wireless        | Supports plug-in wireless modules, enabling *LoRa*/*Meshtastic*, *Thread*, *Zigbee*, *Matter*, or enhanced *WiFi*/*Bluetooth* capabilities in challenging environments |
| Real-Time Clock (RTC) | Included on models 3.5" and larger, allowing the device to retain date and time during deep sleep |


<img src="images/backside_pf_esp32_advance_hmi_7inch_screen_t.png" width="100%" height="100%" />

### Caveat: Display Size
Note that there are actually **two** groups of panels with distinct functional differences:

| Display Size (Inch) | Resolution | Secondary USB-C Port |
| --- | --- | --- |
| 2.4, 2.8, 3.5 | 480x320 | **yes** |
| 4.3, 5.0, 7.0 | 800x480 | **no** |

* **Bigger Resolution:** starting with *4.3"* display sizes, you get a *much better* resolution
* **Secondary USB-C Port:** surprisingly, the secondary USB-C port is present only on the **smaller** displays (3.5" and lower). 
  
  This secondary USB-C connector can be very useful for connecting external USB peripherals (like keyboards or mice), in which case the built-in *ESP32-S3* can act as a USB host or device mode.
    
    It is surprising this useful additional connector is missing on the physically *larger* boards (which have **more** physical space than the smaller display boards).  
    
    If you plan to hook up external USB devices or want the board to act as a USB device itself, make sure you get *3.5"* displays or smaller.

### Wireless Plug-In Modules
The ability to optionally plug in wireless modules is highly useful: depending on use case, you can now enhance the *CrowPanel* to cover radio projects:

<img src="images/esp32_advance_hmi_7.0inch_display_t.png" width="100%" height="100%" />

* [Meshtastic:](https://meshtastic.org/) turn it into a long-range digital mesh text transceiver (you may have to adjust the firmware as there currently is no prebuilt firmware available for *CrowPanels*, but the opportunities are huge: due to the large capacitive display, you could i.e. create a meshtastic device with on-screen keyboard).
* **Smart Home:** many simple devices such as garage doors or garden lights are controlled via license-free sub-GHz radio bands. By adding an appropriate radio module, you can easily turn *CrowPanels* into sophisticated smart home control tablets.
* **Thread/Zigbee/Matter/Wifi6:** while the *ESP32-S3* main microcontroller does not natively support all brand-new radio technologies and protocols, you can plug in the appropriate module as co-processor.

Here are the currently available add-on wireless modules:

| Driver      | Wireless           | Use Case                                  |
|-------------|--------------------|-------------------------------------------|
| *SX1262*    | LoRa               | *Meshtastic*, long-range data transmission |
| *nRF24L01+* | 2.4GHz             | ISM band data transmission                |
| *ESP32-H2*  | Thread/Zigbee/Matter | Connectivity                            |
| *ESP32-C6*  | WiFi 6             | Connectivity                              |

**Important:**

- Radio modules are currently not sold separately and must be selected when ordering a CrowPanel.
- All radio modules are strictly optional and not required.
- Only one radio module can be plugged in and used at a time.


> Tags: ESP32, S3, ESP32-S3, Elecrow, CrowPanel, Panel, Development Board

