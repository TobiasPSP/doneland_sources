<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# CO2 Gadget

> Controlling LED Strips and Matrices Using WLED and an ESP32

[CO2 Gadget](https://emariete.com/en/co2-meter-gadget/) is a free, [open-source firmware](https://github.com/melkati/CO2-Gadget) that you can upload to an *ESP32* microcontroller in under two minutes. This transforms your microcontroller into a sophisticated CO2 sensor capable of monitoring air quality.

The firmware supports a variety of popular CO2 sensor boards and can interface with additional sensors for *temperature*, *humidity*, *atmospheric pressure*, and more.

With minimal effort, this firmware enables you to build your own high-quality, affordable air monitor.

> [!NOTE]
> Quite a number of commercially available *air quality monitors*  rely on [cheap, relatively inaccurate MOS sensors](https://done.land/components/data/sensor/airquality/#cheap-mos-sensors). By using the *CO2 Gadget* firmware, you can invest in a high-quality [dedicated CO2 NDIR sensor](https://done.land/components/data/sensor/airquality/#expensive-ndir-sensors). With parts costing only €20-30, you can create a highly accurate air quality monitoring device that rivals professional-grade equipment.

## Overview

[CO2 Gadget](https://emariete.com/en/co2-meter-gadget/) is a long-standing community project with a mature, feature-rich firmware for *ESP32* microcontrollers. It supports a wide range of sensors and offers great versatility.

The [project website](https://emariete.com/en/co2-meter-gadget/) provides essential resources, though its organization can be challenging to navigate.

### What You Need

Here’s the list of parts required to build your own CO2 monitor:

1. **ESP32 Development Board:** Choose a board **with a built-in display**, such as the [LilyGO T-Display](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display/). If you opt for a board without a display, you’ll need to add an external one or rely on alternative outputs like LEDs or buzzers. While the firmware supports these options, having a display significantly enhances usability.

    <img src="images/co2_gadget_project3_t.png" width="40%" height="40%" />

2. **Sensor:** Invest in a reliable [NDIR CO2 sensor](https://done.land/components/data/sensor/airquality/#expensive-ndir-sensors) such as the [Sensirion SCD30](https://done.land/components/data/sensor/airquality/scd30/). Prices vary widely, but you should be able to find an *SCD30* for under €20. Shop carefully for the best deal.

    <img src="images/co2_gadget_project4_t.png" width="40%" height="40%" />

3. **Optional Add-ons:** The firmware supports [programmable WS2812 RGB LEDs](https://done.land/components/light/led/programmable/ws2812/) and buzzers. These can complement or even replace a display, providing alternative ways to convey air quality information.



> [!IMPORTANT]
> The firmware expects components (like sensors or displays) to be connected to well-known GPIOs. All *ESP32S* (classic ESP32) use the same GPIOs. Newer members of the *ESP32* family (such as *ESP32-C3* or *S3*) use *different* pins. You may have to adjust the source code and compile the firmware yourself for these microcontrollers.     


### Power Supply Considerations

High-quality [CO2 NDIR sensors](https://done.land/components/data/sensor/airquality/#expensive-ndir-sensors) can be relatively power-hungry. For example, the popular [Sensirion SCD30](https://done.land/components/data/sensor/airquality/scd30/) consumes *75mA* during measurements and averages *19mA*.

Since *air quality monitoring devices* are designed to operate continuously, running them on battery power for extended periods is impractical. While the firmware supports battery operation, the most realistic power source is stationary *USB power* through the USB connector on your microcontroller board.


### Next Steps

Here are the steps to build your own CO2 Gadget:

1. **Upload Firmware:** Get an *ESP32 development board* and upload the *CO2 Gadget* firmware. No special tools are required—just a *Chromium-based browser* (e.g., Chrome, Edge, Opera, or Brave).
2. **Configure Firmware:** Once your microcontroller runs the firmware, connect to it wirelessly (e.g., via your smartphone) and use its web interface to configure your options.
3. **Add Sensor(s):** Connect your chosen CO2 sensor to the microcontroller. Optionally, add additional sensors for *temperature*, *humidity*, or other air quality measurements. Many sophisticated CO2 sensors include these additional features.

The first two steps require only an *ESP32 board*, so you can start immediately. This guide will walk you through each step, helping you configure the firmware and connect the sensors. Once your microcontroller successfully runs the *CO2 Gadget firmware* and you can access its web interface, you’ll move on to connecting sensors and fitting the components into a housing.



## 1. Uploading Firmware

You can upload [pre-made firmware](https://emariete.com/en/co2-meter-gadget/#Instalacion_de_CO2_Gadget_Advanced) through your *Chrome* browser - without the need for any special tools or programming.

Alternatively, the source code is freely [available on github.com](https://github.com/melkati/CO2-Gadget) in case you want to review it, make adjustments, and/or compile and upload your own firmware version.

### Connect Microcontroller To PC

Either way, the first step is to ensure your microcontroller connects properly to your PC. When connected via USB, the microcontroller board should power up, and your PC should emit a chime indicating a new USB device has been recognized.

> [!IMPORTANT]
> If the device is not detected, check for issues such as a faulty USB cable or missing drivers. Resolve these problems first by following [this guide](https://done.land/components/microcontroller/howtouse/connecttopc/).


### Browser-Based Firmware Upload

Once your microcontroller is recognized by your PC, follow these steps to upload the *CO2 Gadget firmware*:

1. Open a **Chromium-based browser** and navigate to the [CO2 Gadget homepage](https://emariete.com/en/co2-meter-gadget/#Instalacion_de_CO2_Gadget_Advanced). Look for the **Installation of CO2 Gadget Advanced** section. Scroll down to find a table listing various *ESP32 development boards*. 

2. Identify the board you are using in the table:


    | Variant | Display | Controller | SDA | SCL | Remark |
    | --- | ---  | --- | --- | --- | --- |
    | **TTGO_TDISPLAY** | TFT 1.14" 240x135 | built-in | 21 | 22 | [TTGO Display](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display/) |
    | **TTGO_TDISPLAY_SANDWICH** | TFT 1.14" 240x135 | built-in | 22 | 21 | same, however GPIO21 and GPIO22 (I2C) are **reversed** to that the sensor PCB can be easily piggy-backed onto the microcontroller board for compactness |
    | **TDISPLAY_S3** | TFT 1.9" 320x170 | built-in | 42 | 43 | uses *ESP32-S3* |
    | **esp32dev_OLED** | OLED 0.96/1.3" 128x64 | SH1106 | 21 | 22 | generic 0.96" and 1.3" I2C OLED displays and [classic ESP32S](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/esp32devkitcv4/) |
    | **esp32dev** | none | none | 21 | 22 | [classic ESP32S](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/esp32devkitcv4/) |
    | **esp32dev_ST7789_240×320** | TFT 240x320 | [ST7789](https://done.land/components/humaninterface/display/tft/st7789/) | 21 | 22 | supports [320x240 TFT display](https://done.land/components/humaninterface/display/tft/st7789/1.9inch320x240/) and [classic ESP32S](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/esp32devkitcv4/) |
    | **ttgo-t5-EINKBOARDGDEM0213B74** | e-Ink 2.13" 104x212 | GDEM0213B74 | 21| 22| *Lilygo TTGO T5* board |
    | **ttgo-t5-EINKBOARDDEPG0213BN** | e-Ink 2.13" 104x212 | DEPG0213BN | 21 | 22 | *Lilygo TTGO T5* board |
    | **ttgo-t5-EINKBOARDGDEW0213M21** | e-Ink 2.13" 104x212 | GDEW0213M21 | 21 | 22 | *Lilygo TTGO T5* board |
    | **ttgo-t7-EINKBOARDGDEM029T94** | e-Ink  2.9" 128x296 | GDEM029T94 | 21 | 22 | *Lilygo TTGO T7* board |
    | **ttgo-t7-WEACT_GDEH0154D67** | e-Ink  1.54"  200x200| GDEH0154D67 | 21 | 22 | [classic ESP32S](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/esp32devkitcv4/) and external *WeAct Studio e-Ink display GDEH0154D67*  |
    | **ttgo-t7-WEACT_DEPG0213BN** | external 2.13" e-Ink 104x212 | DEPG0213BN | 21 | 22 | [classic ESP32S](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/esp32devkitcv4/) and external *WeAct Studio e-Ink display DEPG0213BN*  |
    | **ttgo-t7-WEACT_GxEPD2_290_BS** | e-Ink 2.9" 128x296 | GDEM029T94 | 21 |22 | [classic ESP32S](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/esp32devkitcv4/) and external *WeAct Studio e-Ink display GDEM029T94BS*  |
    
    

3. Click the **INSTALL** button for your chosen board. A dialog will appear to select your connected microcontroller. Click *Install CO2-Gadget*. 

    <img src="images/co2_sensor_install_1.png" width="100%" height="70%" />

> [!NOTE]
> If no devices are listed, ensure your microcontroller is connected via USB. Close and reopen your browser, or reboot your PC if necessary. Verify [your microcontroller’s connection](https://done.land/components/microcontroller/howtouse/connecttopc/) and check that drivers are installed.

4. Check the option to erase the flash memory, then click *Next*. 

    <img src="images/co2_sensor_install_2.png" width="60%" height="60%" />

5. Confirm your selection by clicking *Install*. 

    <img src="images/co2_sensor_install_3.png" width="60%" height="60%" />

6. The installation process begins: first, the flash memory is erased, and then the new firmware is uploaded.

    <img src="images/co2_sensor_install_4.png" width="60%" height="60%" />

7. After 1–2 minutes, the installation completes. Click *Next*. 

    <img src="images/co2_sensor_install_6.png" width="60%" height="60%" />

8. Configure your device for WiFi. Select your WiFi SSID, enter the password, and click *Connect*. 

    <img src="images/co2_sensor_install_7.png" width="60%" height="60%" />

9. Once connected, click *Visit Device* to access its web interface. 

    <img src="images/co2_sensor_install_8.png" width="60%" height="60%" />

At this stage, the gauges in the web interface will display zero values since no sensors are connected yet. You’re now ready to move on to configuring your device.

<img src="images/co2_sensor_install_9.png" width="100%" height="60%" />

> [!TIP]
> When you remove power from your microcontroller, the screen may remain blank when you re-power the board later. If this happens to you, press the *Reset* button on the board. This looks like a flaw with the energy savings feature.         


## 2. Connecting To Microcontroller
In order to configure *CO2 Gadget*, you need access to its web interface. If you followed the steps above, this web interface has just opened in your browser. If so, proceed with the configuration immediately (see below).

If you closed the browser, or revisited the device after some time, accessing its web interface may be challenging: you need to know the  current *device IP address*: *http://[IP Address]*.

*CO2 Gadget* does support *mDNS*, and the default device name is *CO2-Gadget*. So you *should* be able to use this name in your browser: [CO2-Gadget](http://co2-gadget/). Unfortunately, *mDNS* often does not work reliably, and if your browser cannot resolve this name, you are in good company.   



> [!TIP]
> If you cannot seem to connect to the IP address, then try temporarily disabling any *VPN* (like *Nord VPN*) you may be using.




### Random IP Address Assignment
By default, the device receives a random IP address from *DHCP* which can change over time. This is why you might want to assign a permanent *static IP address* to your device while you still have a chance and know its IP address. 

Assigning a static IP address is ideally part of the initial device configuration.

<details><summary>What can I do if I don't know the IP address and cannot access the device anymore?</summary><br/>


### Recovering IP Address
Here are the steps to recover the current device IP address:

1. Connect the microcontroller to your PC via USB cable, and navigate to [ESPHome](https://web.esphome.io/) (*CO2 Gadget* is no *ESPHome* software, but you can use the *ESPHome tool chain* to access the device logs).

    <img src="images/esphome_co2gadget_log1.png" width="100%" height="100%" />

2. Click *CONNECT*. The browser opens a dialog with the connected USB devices. Select your microcontroller, and click *Connect*.

    <img src="images/esphome_co2gadget_log2.png" width="100%" height="100%" />

    > If you cannot see your board in the list, close all browser windows, then try again. If that does not help, reboot your PC, then try again. This will free any *Web Serial ports* that may have been locked from earlier sessions.

3. In the next dialog, click *LOGS* to open the device log. **ATTENTION:** do **not** click *Prepare for first use*, or else *ESPHome* will overwrite your firmware with its own. Keep in mind: we are just using the *ESPHome* tools to access the device logs, but you do not want to reprogram your microcontroller.

    <img src="images/esphome_co2gadget_log3.png" width="50%" height="50%" />

4. A console opens and shows the current microcontroller messages. As expected, you can see it complain about missing sensors. Click *RESET DEVICE*.

    <img src="images/esphome_co2gadget_log4.png" width="100%" height="100%" />

5. The device now conducts a reset, and now the log shows the device initialization in minute detail. As part of this, you see the *IP address* that is assigned to the device:

    <img src="images/esphome_co2gadget_log5.png" width="100%" height="100%" />

Once you know the IP address (*192.168.68.23* in the example above), open a browser, and navigate to this IP address. Prepend *http://*. Do not use *http**s**://*!

This shows the devices' web interface:

<img src="images/esphome_co2gadget_log6.png" width="100%" height="100%" />


</details>     


## 3. Configuring CO2 Gadget


With the devices' web interface open (see above), click the menu *Preferences* to see its settings:

<img src="images/esphome_co2gadget_log7.png" width="100%" height="100%" />

Here are the settings that you should review:

* **Connectivity:** Check the technologies you want the device to use for wireless connections. If you do not need *Bluetooth*, for example, uncheck *BLE*.
    > Better not deactivate *BLE* though, or else you miss out on the built-in *app support*: free apps exist both for [Android](https://play.google.com/store/apps/details?id=com.sensirion.myam&hl=es) and [iPhone](https://apps.apple.com/us/app/sensirion-myambience/id1529131572). With these apps, you can conveniently view the sensor information via *Bluetooth* and your smartphone, and even configure the firmware.
* **Networking:** In the text box *Host Name*, set the *mDNS host name* that the device should use. By default, the *mDNS* host name is **CO2-Gadget**. If *mDNS* does not work for you, then you can check *Use Static IP*, and assign a static IP address to your device.
    > In order to use a static IP address, you need to know your valid IP address range and the range of IP addresses assigned by *DHCP* automatically. You must ensure that the IP address you pick is *reachable* (within your subnet mask), and that no other device can ever receive this IP address.     
* **Sensors:** You can define offset values for your sensors (if they are always off by a fixed value), and when you are using a WS2812 LED, you can define the CO2 levels for *orange* and *red* levels. The predefined values typically do not need to be changed.
* **Outputs:** if you use optional components such as a *WS2812 LED* or a buzzer, then you can customize their behavior, i.e. control *LED brightness* and *buzzer tones*.
* **Battery:** even though CO2 sensors are not running well on battery power due to their relatively high current consumption, you can add a battery to your setup and define the battery capacity.
* **Display Preferences:** control which sensor readings should appear on the display. You can also turn off the display after a grace period, and limit such power saving features for when the device is battery powered only.

Once you have adjusted your settings, click *Save*.
## Connecting Peripherals

With your microcontroller configured, you can now move forward. Power off your board and connect a suitable CO2 sensor, such as the [Sensirion SCD30](https://done.land/components/data/sensor/airquality/scd30/). When you power the board back on, you should see actual sensor readings on your display.

Below is an overview of the GPIOs used to connect peripherals like sensors, displays, LEDs, buttons, and buzzers.

### I2C Interface

Currently, *CO2 Gadget* offers precompiled firmware for *ESP32S* and *ESP32-S3* microcontrollers. The required GPIOs for connecting external *I2C* components (e.g., sensors and displays) depend on your microcontroller:

| Microcontroller | SDA | SCL |
| --- | --- | --- |
| **ESP32S** | 21 | 22 |
| **ESP32-S3** | 43 | 44 |

> [!NOTE]  
> The firmware **TTGO_TDISPLAY_SANDWICH** reverses the GPIOs for *SDA* and *SCL*. It is tailored specifically for mounting the *Sensirion SCD30 PCB* piggyback-style onto the *ESP32S PCB*.

### Buttons

GPIOs for buttons vary depending on the board, as some come with built-in buttons on specific GPIOs:

| **Firmware**               | **UP/DWN** |
|----------------------------|------------|
| **TTGO_TDISPLAY**          | 35 / 0     |
| **TTGO_TDISPLAY_SANDWICH** | 35 / 0     |
| **TDISPLAY_S3**            | 14 / 0     |
| **esp32dev_OLED SSH1106**  | 15 / 0     |
| **esp32dev**               | 15 / 0     |
| **esp32dev-ST7789_240x320** | 19 / 0     |

### LEDs & Buzzer

The firmware supports both *regular* LEDs and *programmable* LEDs (WS2812, aka *"NeoPixel"*). The optional buzzer is always wired to *GPIO2*. The LED GPIOs vary by microcontroller:

| **Microcontroller Type**   | **GPIO Orange** | **GPIO Red** | **GPIO WS2812 LED** | 
|----------------------------|------------------|--------------|----------------------|
| **ESP32S**                 | 32              | 33           | 26                   |
| **ESP32-S3**               | 03              | 01           | 16                   |

### Battery

To monitor the state of charge (voltage) of an external battery, use the following GPIOs based on your microcontroller:

| **Microcontroller Type**   | **Battery Voltage GPIO** |
|----------------------------|--------------------------|
| **ESP32S**                 | 34                       |
| **ESP32-S3**               | 04                       |

If the GPIO assignments in the precompiled firmware do not meet your requirements, or if you want to use a different *ESP32 type* (e.g., *ESP32-C3* or *ESP32-S2*), you can [download and adjust the source code](https://github.com/melkati/CO2-Gadget), then compile and upload your custom firmware.

> [!TIP]  
> Sensor support is based on the [CanAirIO](https://github.com/kike-canaries/canairio_sensorlib) library, which supports *ESP32S*, *ESP32-C3*, *ESP32-S3*, *ESP8266*, and *Atmel*. Note that *ESP32-S2* is not explicitly supported.



## Supported Sensors

Sensors are supported through the [CanAirIO](https://canair.io/) library. Check their [GitHub repository](https://github.com/kike-canaries/canairio_sensorlib) for the latest list of supported sensors.

### PM Sensors

| Sensor Model          | UART | I2C | Detection Mode | Status       |
|-----------------------|:----:|:---:|:--------------:|:------------:|
| Honeywell HPMA115S0   | Yes  | --- | Auto           | DEPRECATED   |
| Panasonic SN-GCJA5L   | Yes  | Yes | Auto           | STABLE       |
| Plantower Models      | Yes  | --- | Auto           | STABLE       |
| Nova SDS011           | Yes  | --- | Auto           | STABLE       |
| IKEA Vindriktning     | Yes  | --- | Select         | STABLE       |
| Sensirion SPS30       | Yes  | Yes | Select / Auto  | STABLE       |

> [!NOTE] 
> Panasonic via UART on ESP8266 may require manual selection in detection.    

### CO2 Sensors

| Sensor Model          | UART | I2C | Detection Mode | Status       |
|-----------------------|:----:|:---:|:--------------:|:------------:|
| Sensirion SCD30       | ---  | Yes | Auto           | STABLE       |
| Sensirion SCD4x       | ---  | Yes | Auto           | TESTING      |
| MHZ19                 | Yes  | --- | Select         | STABLE       |
| CM1106                | Yes  | --- | Select         | STABLE       |
| SenseAir S8           | Yes  | --- | Select         | STABLE       |

### Environmental Sensors

| Sensor Model          | Protocol  | Detection Mode | Status       |
|-----------------------|:---------:|:--------------:|:------------:|
| AM2320               | I2C       | Auto           | STABLE       |
| SHT31                | I2C       | Auto           | STABLE       |
| AHT10                | I2C       | Auto           | STABLE       |
| BME280               | I2C       | Auto           | STABLE       |
| BMP280               | I2C       | Auto           | STABLE       |
| BME680               | I2C       | Auto           | STABLE       |
| DfRobot SEN0469 NH3  | I2C       | Auto           | TESTING      |
| DfRobot SEN0466 CO   | I2C       | Auto           | TESTING      |
| Geiger CAJOE         | GPIO      | Select         | TESTING      |
| DHTxx                | TwoWire   | Select         | DISABLED     |



> [!NOTE] 
> *DHT22* is supported but is not recommended.     


> Tags: CO2 Gadget, Sensirion SCD30, Air Quality, Firmware, CanAirIO, Sensor

[Visit Page on Website](https://done.land/components/microcontroller/howtouse/firmware/fromsomeoneelse/co2gadget?641318011502254120) - created 2025-01-01 - last edited 2025-01-01
