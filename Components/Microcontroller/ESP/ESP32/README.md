<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP32 Microprocessor Family

> High-Powered Single- And Dual-Core Microcontrollers With WiFi, Bluetooth, And Now Also Zigbee And Thread Support



**ESP32** is the **ESP8266** *successor* that surfaced in 2016. The *ESP32 microcontroller* has since then evolved, and many subtypes surfaced:

The [Expressif Product Comparison](https://products.espressif.com/#/product-comparison) provides even more details and models.


| Feature | [ESP32](ESP32) | [S2](S2) | [S3](S3) | [C3](C3) | [C6](C6)  | ESP8266 |
| --- | --- | --- | --- | --- | --- | --- |
| Launch | 2016 |  2019 | 2020 | 2020 | 2021 | 2014 |
| Core Type | LX6 | LX7 | LX7 | RISC-V | RISC-V | L106
| Cores | 2 | 1 | 2 | 1 | 1 | 1 | 
| Frequency | 240 | 240 | 240 | 160 | 160 | 160 |
| GPIOs | 34 | 43 | 45 | 22 | 30 | 17 |
| SRAM KB | 520 | 320 | 512 | 400 | 512 | 160 |
| RTC/LP SRAM KB | 16 | 16 | 16 | 8 | 16 | 1 |
| ext RAM MB | 8 | 1024 | ? | ? | 0 | 0 |
| int Flash MB | 0/2/4 | 0/2/4 | ? | 0/4 | ? | 0 |
| ext Flash MB | 16 | 1024 | ? | 16 | ? | ? |
| Cache KB | 64 | 8/16 | 16 | 16 | 16 | 32 |
| ROM KB | 448 | 128 | 384 | 384 | 320 | 0 |
| ADC | 2x12bit 18ch | 2x13bit 20ch | ? | 2x12bit 6ch | ? | 1x10bit 1ch |
| DAC | 2x8bit | 2x8bit | ?  | 0 | 0  | 0  |
| Timers | 4x64bit | 4x64bit | ? | 2x54bit/1x52bit | ? | 2x23bit |
| Watchdog | 3 | 3 | ? | 3 | ? | ? |
| I2C | 2 | 2 | 2 | 1 | 2 | 1 |
| I2S | 2 | 1 | 2  | 1 | 1 | 1 |
| SPI | 4 | 4 | 4 | 3 | 1 | 2 |
| LCD Interface | 1 | 1 | 1 | 0 | 0 | 0 |
| Temperature | 0 | 1 | 1 | 1 | 1 | 0 |
| Touch | 10 | 14 | 14 | 0 | 0 | 0 |
| UART | 3  | 2 | 3 | 2 | 3 | 2 |
| Ethernet | 1 | 0 | 0 | 0 | 0 | 0 |
| IR/RMT | 8  | 4 | 8 | 4 | 4 | 1 |
| Hall Sensor | 1 | 0 | ? | 0 | ? | 0 |
| LED PWM | 16  | 8 | 8 | 6 | 6 | 5 |
| Motor PWM | 6 | 0 | 2| 0 | 0 | 0 |
| Wifi | 4 | 4 | 4 | 4 | 6 | 4 | 
| Wifi Mbps | 150 | 150 | 150 | 150 | 150 | 75 |
| Bluetooth | 4.2  | BLE5.0 | BLE5.0 | BLE5.0 | BLE5.3 | 0 |
| USB OTG | 0 | 1 | 1 | 0 | 0 | 0 |
| Camera Interface | 1  | 1 | 1 | 0 | 0 | 0 |
| TWAI (CAN 2.0) | 1 | 1 | 1 | 1 | 2 | 0 |
| SD Host | 1 | 0 | 2 | 0 | 0 | 0 |
| SD Slave | 1 | 0 | 0 | 0 | 1 | 1 |
| Size mm | 5x5/6x6 | 7x7 | 7x7 | 5x5 | 5x5 | 5x5 |


### Comparing to ESP8266

Compared to the **ESP8266**, in a nutshell it **doubles** everything :

Double the *CPU cores*, double the *WiFi Speed*, (roughly) double the *internal memory*, double the *GPIO pins*, double the *I2C* and *SPI* interfaces, double the *ADCs*, double the *Infrared support*

In addition, it *adds* many interfaces and capabilities: built-in support for *Bluetooth*, *CAN*, *LCDs*, *SD Cards*, *Ethernet*, *Camera*, *Touch*, you name it.

> [!TIP]
> The *ESP32* *doubles everything*, except the *price*. *ESP32* breakout boards start under EUR 3.00. Even if you don't need the power or extra features (like bluetooth) offered by *ESP32*, choosing *ESP32* breakout boards over *ESP8266* today is almost always the best choice. Unlike many *ESP8266* breakout board, *ESP32 boards* come with *decent power regulators*. 



### Same Form Factor

Despite its many additional features, **ESP32** are not necessarily bigger in size. The raw chip size did not change from **ESP8266*.

The **ESP32 C3**-based board from **Seeed** for example is tiny:

<img src="images/esp32_c3_seed_top_front_t.png" width="40%" height="40%" />

<sup>**ESP32** boards can be extremely small yet very powerful</sup>

If you do not need a *USB Connector*, you can further cut board size. The picture below shows an **ESP8266** on such a board. The same form factor is available for **ESP32**, effectively reducing the board size to the size of the actual microcontroller and a few supporting elements like a *ceramic WiFI antenna*:

<img src="images/esp8266_wo_USB_t.png" width="40%" height="40%" />

<sup>Boards without USB connector and UART are even smaller but require an external programmer to transfer the firmware.</sup>


> Tags: Microcontroller, ESP8266, ESP32
