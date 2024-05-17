<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP32 DevKitC V4

> Original DevKit From Espressif That Exposes Most ESP32 Pins

*ESP32-DevKitC V4* is a small-sized ESP32-based development board produced by the original *ESP32* manufacturer *Espressif*. This board is ideal for experimenting with all *ESP32 features* as most of the I/O pins are broken out to the pin headers on both sides for easy interfacing.

The breakout board is available with a wide variety of original *ESP32 modules*, including the popular *WROOM 32D* (with PCB antenna) and *WROOM 32U* (with IPX-connector to connect an external antenna).


<img src="images/esp32_devkitc_v4_compare_t.png" width="80%" height="80%" />

The board comes with a *Micro USB* connector to connect to a PC.

<img src="images/esp32_devkitc_v4_usb_t.png" width="50%" height="50%" />

## Hardware Overview
The dominant part of the breakout board is the *ESP32 module* (depending on type either with attached PCB antenna, or with an IPX antenna jack). On the inner side, there is unused space unless your breakout board uses the larger *WROVER* module with additional *PSRAM*.

<img src="images/esp32_devkitc_v4_module_t.png" width="100%" height="100%" />

### USB Connector
On the opposite side, a *Micro USB* connector lets you connect the board to a computer.


Behind the *USB connector*, a *Silicon Labs CP2102* chip provides the *USB to UART* bridge at speeds of up to 3Mbps.


<img src="images/esp32_devkitc_v4_regulator_t.png" width="100%" height="100%" />


### Power Supply
The board provides three *mutually exclusive* ways to power it:

* **USB:** *5V USB* is used and converted internally to *3.3V*
* **5V/GND Pins:** You can power the board through an external power supply by connecting it to the pins *5V* and *GND*. The input power goes through the voltage regulator (like *USB* option).
* **3.3V/GND Pins:** You can provide *3.3V* directly by connecting a suitable power supply to the pins *3.3V* and *GND*. These pins power the microcontroller *directly* and do not go through a voltage regulator. This option provides the best energy efficiency but is also the most dangerous one: if your external power supply does not *always* deliver regulated voltage in the range of *3.0-3.6V*, the board and/or microcontroller *will be damaged*.

> [!CAUTION]
> Always use **only one** of the three power methods listed above. When you power the board through an external power supply, **never** also supply power through *USB*. The most common error is to keep the board supplied by an external power supply while connecting it via *USB cable* to a computer in order to upload new firmware. Always make sure you either *disconnect the external power supply*, or you use a *USB connector* where the *power lines* can be turned off.




<img src="images/usb_power_turnoff_t.png" width="100%" height="100%" />

### Voltage Regulator
Behind the *CP2102*, there is a dedicated *IRU1117-33* 3.3V *voltage regulator* capable of supplying *800mA*. This regulator is used when you supply voltage either via *USB* or directly via the *5V* pin. The voltage regulator accepts an absolute *maximum input voltage* of *7V*.

On the right side, there are two *JY3/S8050* epitaxal planar transistors with a high collector current of *500mA* each and high total power dissipation.


### Power LED
On the opposite side, a *SMD power LED* is located. It turns on whenever input power passes the *voltage regulator*. It **does not turn on** when you supply *3.3V* directly to the *3.3V pin.*


> [!CAUTION]
> Do not be confused when you power the board directly via the *3.3V Pin*. The board runs perfectly ok even though the *power LED* will not turn on. This is by design and a good thing: typically, when powering the board directly via *3.3V*, this is done to maximize energy efficiency in use cases where energy is limited (i.e. battery-operated devices). In such scenarios, it is a smart decision to *not turn on* a *power indicator* that would otherwise just waste energy.








### Firmware Download Mode
To download new firmware into the *ESP32* via the *USB port*, you need to enable the *Firmware download mode*: holding down *Boot* and then pressing *EN* initiates this *Firmware Download mode*.

Once the new firmware is successfully transferred to the board, press *EN* (reset) to leave the *Firmware download mode* and run your sketch.


> [!TIP]
> You may not have to press the buttons to upload new firmware. Depending on the firmware currently running, the *Firmware download mode* can be activated automatically. This however is not guaranteed. Also, when your current sketch keeps the microcontroller constantly busy, the automatic method may fail. Pressing the buttons as illustrated is always a safe and reliable way of stopping the current sketch and switching the board in *Firmware download mode*.






## Materials
[CP2102 USB-UART-Bridge](materials/cp2102_datasheet.pdf)    
[IRU1117 3.3V Voltage Regulator](materials/iru1117_datasheet.pdf)     
[S3050/J3Y Transistor](materials/iru1117_datasheet.pdf)     




  


> Tags: Microcontroller, ESP32, CP2102

