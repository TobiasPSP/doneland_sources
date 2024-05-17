<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP32 DevKitC V4

> Original DevKit From Espressif Providing Access To Almost All ESP32 Pins - For Experienced Users Only

*ESP32-DevKitC V4* is a small-sized ESP32-based development board produced by the original *ESP32* manufacturer *Espressif*. This board is suitable for experimenting with all *ESP32 features* as most of the I/O pins are broken out to the pin headers on both sides for easy interfacing however it is not easy to use: you may have to manually *install drivers* on your computer to recognize it, and uploading new sketches is very inconvenient as two buttons need to be pressed *in the right way at the right time*. Its *form factor* makes it hard to use on standard breadboards.

Unfortunately, this board has no built-in *user-controllable LED*, and *blink sketches* will not work.

On the *pro* side, the board comes with a good voltage regulator, and once a sketch is successfully uploaded, it works reliably. Street prices for under EUR 2.00 make it a good value, albeit not necessarily for novice users.

The breakout board is available with a wide variety of original *ESP32 modules*, including the popular *WROOM 32D* (with PCB antenna) and *WROOM 32U* (with IPX-connector to connect an external antenna).


<img src="images/esp32_devkitc_v4_compare_t.png" width="60%" height="60%" />


| Item | Description |
| --- | --- |
| USB Connector | Micro USB |
| Size | 48.2x27.9mm (without PCB antenna), 54.4x27.9mm (with PCB antenna) |
| Microcontroller | ESP32-WROOM-DA/32E/32UE/32D/32U, ESP32-WROVER-E/IE, ESP32-SOLO1 |


## Hardware Overview
The dominant part of the breakout board is the *ESP32 module* (depending on type either with attached PCB antenna, or with an IPX antenna jack). On the inner side, there is unused space unless your breakout board uses the larger *WROVER* module with additional *PSRAM*.

<img src="images/esp32_devkitc_v4_module_t.png" width="40%" height="40%" />

### USB Connector
On the opposite side, a *Micro USB* connector lets you connect the board to a computer.


<img src="images/esp32_devkitc_v4_usb_t.png" width="40%" height="40%" />


Behind the *USB connector*, a *Silicon Labs CP2102* chip provides the *USB to UART* bridge at speeds of up to 3Mbps. This chip may require *manual driver installation* before you can use it.


<img src="images/esp32_devkitc_v4_regulator_t.png" width="70%" height="70%" />


### Power Supply
The board provides three *mutually exclusive* ways to power it:

* **USB:** *5V USB* is used and converted internally to *3.3V*
* **5V/GND Pins:** You can power the board through an external power supply by connecting it to the pins *5V* and *GND*. The input power goes through the voltage regulator (like *USB* option).
* **3.3V/GND Pins:** You can provide *3.3V* directly by connecting a suitable power supply to the pins *3.3V* and *GND*. These pins power the microcontroller *directly* and do not go through a voltage regulator. This option provides the best energy efficiency but is also the most dangerous one: if your external power supply does not *always* deliver regulated voltage in the range of *3.0-3.6V*, the board and/or microcontroller *will be damaged*.

> [!CAUTION]
> Always use **only one** of the three power methods listed above. When you power the board through an external power supply, **never** also supply power through *USB*. The most common error is to keep the board supplied by an external power supply while connecting it via *USB cable* to a computer in order to upload new firmware. Always make sure you either *disconnect the external power supply*, or you use a *USB connector* where the *power lines* can be turned off.




<img src="images/usb_power_turnoff_t.png" width="70%" height="70%" />

### Voltage Regulator
Behind the *CP2102*, there is a dedicated *IRU1117-33* 3.3V *voltage regulator* capable of supplying *800mA*. This regulator is used when you supply voltage either via *USB* or directly via the *5V* pin. The voltage regulator accepts an absolute *maximum input voltage* of *7V*.

On the right side, there are two *JY3/S8050* epitaxal planar transistors with a high collector current of *500mA* each and high total power dissipation.


### Power LED
On the opposite side, a *SMD power LED* is located. It turns on whenever input power passes through the *voltage regulator*. It **does not turn on** when you supply *3.3V* directly to the *3.3V pin.*


> [!CAUTION]
> When you power the board directly via the *3.3V Pin*, the *power LED* stays *off* even though the board runs perfectly fine. This behavior is by design and a good thing: when powering the board directly via *3.3V*, this is done typically to maximize energy efficiency in use cases where energy is limited (i.e. battery-operated devices). In such scenarios, you do not want the *power LED* to waste precious energy.











### Firmware Download Mode
The board comes with two *push buttons* labeled *EN* (reset button) and *Boot*.

To reliably put the board in *Firmware download mode*, hold down *Boot* and then press *EN*. The board is now ready to download new firmware via the *USB connector*.

Important: once the new firmware is successfully transferred to the board, press *EN* (reset) to *leave* the *Firmware download mode* and run your sketch.


> [!TIP]
> Depending on the currently uploaded firmware, you may not have to press buttons to transfer new firmware to the board: the board may enter the *Firmware download mode* automatically once you connect it via USB cable to a computer and upload a new sketch. This however is not guaranteed, and when your current sketch keeps the microcontroller very busy, the automatic method may fail. Pressing the buttons as illustrated is always a safe and reliable way of *stopping the current sketch* and instructing the board to look for new firmware.


## Pinouts
This breakout board exposes most *ESP32* pins:


<img src="images/esp32-devkitC_V4_pinout_t.png" width="100%" height="100%" />

The tables below provide detailed information for each header pin. The *Pin Type* resolves as follows: **P**ower supply, **G**round, **I**nput, **O**utput.

### Header Pin Row 1

| Pin | Label | Pin Type | Description |
|  --- |  --- |  --- |  --- |  
| 1 | 3V3 | P | 3.3V power supply |
| 2 | EN | I | CHIP_PU, Reset |
| 3 | VP | I | GPIO36, ADC1_CH0, S_VP |
| 4 | VN | I | GPIO39, ADC1_CH3, S_VN |
| 5 | IO34 | I | GPIO34, ADC1_CH6, VDET_1 |
| 6 | IO35 | I | GPIO35, ADC1_CH7, VDET_2 |
| 7 | IO32 | IO | GPIO32, ADC1_CH4, TOUCH_CH9, XTAL_32K_P |
| 8 | IO33 | IO | GPIO33, ADC1_CH5, TOUCH_CH8, XTAL_32K_N |
| 9 | IO25 | IO | GPIO25, ADC1_CH8, DAC_1 |
| 10 | IO26 | IO | GPIO26, ADC2_CH9, DAC_2 |
| 11 | IO27 | IO | GPIO27, ADC2_CH7, TOUCH_CH7 |
| 12 | IO14 | IO | GPIO14, ADC2_CH6, TOUCH_CH6, MTMS |
| 13 | IO12 | IO | GPIO12, ADC2_CH5, TOUCH_CH5, MTDI |
| 14 | GND | G | Ground |
| 15 | IO13 | IO | GPIO13, ADC2_CH4, TOUCH_CH4, MTCK |
| 16 | D2 | IO | GPIO9, D2 |
| 17 | D3 | IO | GPIO10, D3 |
| 18 | CMD | IO | GPIO11, CMD |
| 19 | 5V | P | 5V power supply |


<img src="images/esp32_devkitc_v4_back_t.png" width="50%" height="50%" />

### Header Pin Row 2

| Pin | Label | Pin Type | Description |
|  --- |  --- |  --- |  --- | 
| 1 | GND | G | Ground |
| 2 | IO23 | IO | GPIO23 |
| 3 | IO22 | IO | GPIO22 |
| 4 | TX | IO | GPIO1, U0TXD |
| 5 | RX | IO | GPIO3, U0RXD |
| 6 | IO21 | IO | GPIO21 |
| 7 | GND | G | Ground |
| 8 | IO19 | IO | GPIO19 |
| 9 | IO18 | IO | GPIO18 |
| 10 | IO5 | IO | GPIO5 |
| 11 | IO17 | IO | GPIO17 |
| 12 | IO16 | IO | GPIO16 |
| 13 | IO4 | IO | GPIO4, ADC2_CH0, TOUCH_CH0 |
| 14 | IO0 | IO | GPIO0, ADC2_CH1, TOUCH_CH1, Boot |
| 15 | IO2 | IO | GPIO2, ADC2_CH2, TOUCH_CH2 |
| 16 | IO15 | IO | GPIO15, ADC2_CH3, TOUCH_CH3, MTDO |
| 17 | D1 | IO | GPIO8, D1 |
| 18 | D0 | IO | GPIO7, D0 |
| 19 | CLK | IO | GPIO6, CLK |


<img src="images/esp32_devkitc_v4_side2_t.png" width="60%" height="60%" />


### Pins To Avoid
Some pins are used internally for communication between ESP32 and *SPI flash memory*. They are grouped on both sides near the USB connector. Avoid using these pins, as it may disrupt access to the SPI flash memory/SPI RAM:

**D0**-**D3**, **CMD**, and **CLK**

Pins **GPIO16** and **GPIO17** are used internally by *ESP32-WROVER*. If you use the more commonly *ESP32-WROOM*, you are free to use these pins.


<img src="images/esp32_devkitc_v4_side_t.png" width="60%" height="60%" />


## Issue On External Power
When this board is powered externally, it may not run the sketch immediately but requires the button *EN* to be pressed. Only then will the sketch run. The issue does not occur when the board is powered via *USB*.

The reason for this unwanted behavior is a *capacitor* (C15) connected in parallel to the *Boot* button. On newer versions of this breakout board, the *capacitor* meanwhile has been removed.

The picture shows a newer version with the solder pads for *C15* (but with no capacitor present):


<img src="images/esp32_devkitc_v4_c15_fail_t.png" width="80%" height="80%" />

Only relatively old boards have this capacitor in place. If you do find a capacitor at this location and suffer from the issue, remove the capacitor manually. 

> [!CAUTION]
> The SMD capacitor is very small, and there are delicate tracks behind it that can easily be damaged by brute force or an over-sized and over-heated soldering iron. Desoldering this component requires proper tools (i.e. a heat gun). 



## Practical Considerations
This board is a *development board* in its best sense: it exposes almost all *ESP32* pins and invites anyone to fully test-drive the *ESP32*.

Unfortunately, for the same reasons, the board is fairly large. Its *width* is *28mm* which is unfortunately *too wide* to place the breakout board on the typical breadboards:


<img src="images/esp32_devkitc_v4_breadboard_t.png" width="70%" height="70%" />

Only one row of header pins would remain accessible.

### One Breadboard Isn't Enough
Most breadboards are modular and can be combined and rearranged. When you take *two* breadboards and remove *one powerrail* each, you can stick them together in a way that provides the necessary real estate to place the breakout board:


<img src="images/esp32_devkitc_v4_breadboard2_t.png" width="80%" height="80%" />


> [!CAUTION]
> Make sure you *ground yourself* before fiddling too much with the board trying to place it. Almost all microcontroller breakout boards are sensitive towards static electricity and can be accidentally destroyed by a single static spark.


## Challenging: Working With The Board
Working with the *DevKitC V4* isn't as intuitive as with other boards. 

### No Builtin LED
For one, it does not have a built-in user-controllable *LED*, so simple *blink* sketches to verify the setup will not work.

> [!NOTE]
> There *is* a *LED* on the board, however this is the *power LED* that is not user-controllable. 

### No Dedicated Board Definition
Second, neither *Arduino IDE* nor *platformio* provide a dedicated board *DevKitC V4*, so you need to find a similar board youself. That's no rocket science but also not trivial, especially for novice users.

In *platformio*, I opted for *AZ-Delivery-Devkit-V4* (as some of the boards I used were indeed purchased at *AZ-Delivery* before I noticed that the same boards are available at a fraction of the price at *AliExpress*). 


Most likely, the generic board *esp32dev* would have as well worked just fine.

This is *platformio.ini* I successfully used for testing:


````
[env:az-delivery-devkit-v4]
platform = espressif32
board = az-delivery-devkit-v4
framework = arduino
````

> [!CAUTION]
> Make sure you remove any *build flags* or other settings that you do not *positively know are necessary*. If you *copy&paste* extra settings from other boards, you may easily run into compile exceptions like "Serial was not declared in this scope".





In *Arduino IDE*, the generic board *ESP-WROOM-32* seems like a reasonable choice.

### Manual Driver Installation Required

Worst, the board may not even be recognized by your computer when you plug it in via a *USB cable*. 

This is due to the *USB to UART bridge* used by this board: the *CP2102* from *Silicon Labs* is powerful - but not as ubiquous as i.e. the *CH340*. 

Thus, it may require a manual *driver installation*.

#### Is Board Recognized When USB-Connected?
The first step in diagnosing issues is to check whether the board gets recognized by the computer when you plug in its USB cable. If a *new device discovered* sound plays, that's a good indicator. However, do make sure whether there is indeed a new *COM Port* visible in *device manager* (on *Windows*).


<img src="images/devmgr_usb_com_disc.png" width="80%" height="80%" />


#### Install Drivers Manually
If *no COM Port* appears in *device manager* when you connect the board to the computer, then most likely the *CP210x drivers* are missing.

[Visit Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) and download the appropriate driver package. On *Windows*, I installed *CP210x Windows Drivers* and *CP210x VCP Windows*.

> [!TIP]
> Once you downloaded the driver packages, make sure you right-click the downloaded ZIP file, choose *Properties*, and click on the button to *unblock* the file **before you unzip it**.


Once drivers are installed, restart the computer. When you now connect the board, it should be correctly recognized, and a *COM port* should appear in *device manager*.

> [!TIP]
> If things *still* do not work, make sure you use an appropriate *USB cable*. Try using a cable that you previously successfully used to upload firmware. There are plenty of cheap cables with no data wire connection, high cable resistance, or loose plug connections.

### Button Press Required To Upload Sketch
If you managed to successfully connect the board to your computer, then there is a final challenge to master: the board needs to be set to *firmware download mode* at *just the right moment* in time.

When you upload a new sketch, your *IDE* by now should be able to identify a *COM port* at which the board is to be found.

The *IDE* next tries to connect to the board - which *will fail* if you don't manually intervene:

As soon as the *IDE* starts trying to connect to the board, hold the *Boot* button and press *EN* shortly. This procedure enables the firmware download mode. *Only now* will the board respond to the connection requests.

The *connecting...* message will now hold for a second, and then the *IDE* starts to upload the new sketch to the board.


## Conclusion
The DevKitC V4 is a great *development board* to test-drive *ESP32* features simply because it exposes all important CPU pins.

### Solid

It's solidly made with a good voltage regulator, and its *street price* of under EUR 2.00 is ok, too (don't buy it for EUR 12.00 or more - there are still people selling it for prices like this).

### But, but, but...

There are a lot of down-sides, though, which make this board definitely not a recommendation for novices or anyone focusing on convenience:

* **USB to UART component** apparently requiring manual driver install
* Cumbersome procedure to enable *firmware download mode*
* hard-to-read and somewhat confusing pin labels on PCB
* no internal LED (which is just very convenient for simple checks and balances)
* *wide form factor* that makes it impossible to plug the board into a single standard breadboard.






## Materials
[Board Schematics](materials/esp32_devkitc_v4-sch.pdf)    
[ESP32 Datasheet](materials/esp32_datasheet_en.pdf)    
[CP2102 USB-UART-Bridge](materials/cp2102_datasheet.pdf)    
[IRU1117 3.3V Voltage Regulator](materials/iru1117_datasheet.pdf)     
[S3050/J3Y Transistor](materials/iru1117_datasheet.pdf)     




  


> Tags: Microcontroller, ESP32, CP2102

[Visit Page on Website](https://done.land/components/microcontroller/esp/esp32/classicesp32/esp32devkitcv4?604445051417245543) - created 2024-05-16 - last edited 2024-05-16
