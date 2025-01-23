<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# Connect SPI Displays

> Using The 3/4-Wire SPI Interface To Connect Color Displays

Color displays use the fast [SPI](https://done.land/fundamentals/interface/spi/) interface, supporting speeds of *1-80 Mbps* with a bus frequency of *10-20 MHz*.



## Overview
The [SPI](https://done.land/fundamentals/interface/spi/) interface requires significantly more *GPIOs* than the simpler and slower [I2C](https://done.land/fundamentals/interface/i2c/) interface:

* **Distinct data lines:** *SPI* comes with *two* data lines compared to *one* in *I2C*:
    * **MOSI:** One line is used to transfer data from the controller to the peripheral. 
    * **MISO:** The other one is used for the opposite direction. In displays where communication is typically one-way, *MISO* is often not used (saving one wire, so-called *3-wire SPI*)
* **CS Pin:** *SPI* does not use unique device addresses. Instead, the device is selected via the *CS* pin. Each SPI device therefore needs an exclusive wire and GPIO so the controller can select it.

A few additional GPIOs are required in addition to the *SPI* pins:

* **D/C Pin:** displays require a *D/C* pin. It tells the device whether the incoming data is screen content, or a command for the device control.
* **Reset:** Many color displays expose a *Reset* pin. This pin needs to be pulled up for the display to be active.
* **Backlight:** *SPI* is typically used with color TFTs. Such displays require an active backlight, so yet another pin is needed to power the backlight LED(s).

When you add the two wires for the power supply, a total of 6 GPIOs and 8 wires may be required to connect a *SPI* display.


## Pins On Display
*SPI* displays can have *these* pins:


| Pin | Description |
| --- | --- |
| SDI/SDA/MOSI | connects to MOSI on the microcontroller. This is where the display *receives* data  |
| SCL/SCK/SCLK | Serial Clock (synchronizes the data speed)  |
| CS | Chip Select. Active *low*: when *low*, the display is operational |
| DC | Data/Command. Distinguishes between content data and device commands |
| LED/BL/BLK | Backlight LED. Supply appropriate voltage or *PWM* |
| RES/RESET | Reset pin. Must be pulled *high* for normal operations |
| VDD | positive voltage, make sure the voltage matches the display requirements |
| GND | Ground |


Sometimes, pins are missing in an effort to save GPIOs. In this case, the missing pins receive standard values directly from the display board:

| Pin | Description | Limitation |
| --- | --- | --- |
| CS | permanently pulled *low* | *SPI* can no longer control multiple devices as this device will always receive and process data, even if they were meant for a different device |
| LED/BL/BLK | connected to VDD | Backlight LED always runs at full brightness and cannot be dimmed or turned off to save energy |
| RES/RESET | permanently pulled *high* | Display controller cannot be resetted manually |

> [!TIP]
> With displays that expose these pins, *you* can save *GPIOs*, too, by connecting the pins as indicated in above table.


## Pins On Microcontroller

The pins you use for *SPI* on the microcontroller development board depend on the microcontroller type you use, and sometimes on the board design:

* **Mandatory Pins:** Older microcontrollers like the one on *Arduino Mega* have designated *SPI* pins that you *must* use.
* **Assignable Pins:** Microcontrollers like *ESP32* have default *SPI* GPIOs that you *should* use (because they are more performant), but you can also use any other suitable *GPIO* instead (which then emulates *SPI* in software).
* **Routable Pins:**  Modern microcontrollers like *ESP32-C3* and *ESP32-S3* have routable *SPI controllers*, so you can assign any suitable *GPIO* with their hardware-optimized *SPI controller(s)*.

Here is a table with some suggestions:

> [!IMPORTANT]
> The development board **you** are using [may use different GPIOs](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/c3supermini/#i2c). Modern *ESP32 family members* such as *ESP32-C3* or *ESP32-S3* can route *any* GPIO to its hardware *I2C controllers*, and development board designers may have designated arbitrary *GPIOs*.

| Microcontroller       | MOSI       | MISO       | SCK | CS | Remarks |
|-----------------------|----------------|----------------|----------|-----|----|
| **Arduino Uno/Leonardo/Nano**        | 11   | 12   | 13     | 10 | |
| **Arduino Micro**        | 16   | 14   | 15                       | any | |
| **Arduino MKR**        | 8   | 10   | 9                       | any | |
| **Arduino Giga R1**        | 90   | 89   | 91                       |any  | |
| **Arduino Due**        | 75   | 74   | 76                       | any  | |
| **Arduino Mega 2560**  | 51  | 50                      | 52              | any  | |
| **ESP8266 Wemos D1 Mini**   | 13/D7    | 12/D6    | 14/D5  |  15/D8 | |
| **ESP32**              | 23 [13]  | 19 [12]  | 18 [14] | 5 [15] | VSPI used by default, secondary HSPI in brackets |
| **ESP32-S2**           | 36   | 35   | 34       | 33 | four SPI interfaces, accessible via GPIO9-GPIO14, and GPIO33-GPIO37. The actual pins you assign from these ranges are free to choose. |
| **ESP32-S3**           | 11   | 13  | 12      | 10 | default pins run through IOMUX instead of GPIO matrix, IOMUX supports max. 80 MHz |
| **ESP32-C3**           | 10  | 9   | 8  | any | remappable, may vary greatly between dev boards |
| **Teensy**         | [varies](https://www.pjrc.com/teensy/td_libs_SPI.html)  | [varies](https://www.pjrc.com/teensy/td_libs_SPI.html)  | Y[varies](https://www.pjrc.com/teensy/td_libs_SPI.html) | [varies](https://www.pjrc.com/teensy/td_libs_SPI.html) |                     |
| **STM32 (Blue Pill)**  | PB5   | PB4  | PB3   | PA15 |
| **Digispark (ATTiny85)**| PB0/pin 5  | PB1/pin 6   | PB2/pin 7 | any other if required | no hardware *SPI*, emulated *using universal serial interface* (*USI*) |



## Power Supply

It is crucial to connect the *VDD* pin on your display with a power source of appropriate voltage. Typically, you must decide whether you connect *VDD* to the *5V* or *3.3V* pin on your microcontroller board:

* **Multiple Voltages:** some displays use internal voltage regulators so you can supply both *5V* and *3.3V*
* **Configurable Voltages:** some displays have *solder bridges* that you can leave open or bridge with some solder. This activates or bypasses internal voltage regulators. Depending on the state of the solder bridge, such displays require **either** *5V* **or** *3.3V*
* **Fixed Voltage:** some displays support just one fixed voltage, either *3.3V* or *5V*.

If in doubt, try with the *3.3V* pin first. If the display does not work with this lower voltage, you may want to use *5V*.

### Logical Level Voltage

Most displays internally use *3.3V logic levels* for the data pins. When your microcontroller uses *5V* (i.e. older *Arduinos*), you might need a fast *level-shifter*, or at least some protective restistors for the data pins.

Modern microcontrollers like the *ESP32* family run on *3.3V* and do not require level shifter.


> Tags: Display, SPI, Pins, GPIO

[Visit Page on Website](https://done.land/components/humaninterface/display/usage/connecting/spi?518786012023251935) - created 2025-01-22 - last edited 2025-01-22
