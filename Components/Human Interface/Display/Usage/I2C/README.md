<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# Connect I2C Displays

> Using The 2-Wire I2C Interface To Connect Monochrome Displays

Small monochrome displays often use the slower but much simpler [I2C](https://done.land/fundamentals/interface/i2c/) interface to connect to a microcontroller. Almost all monochrome [OLED](https://done.land/components/humaninterface/display/oled/) displays, for example, use *I2C*, and because of their simplicity, they are a great way to start with displays.

## Overview
The [I2C](https://done.land/fundamentals/interface/i2c/) interface is a two-wire *bus system* where multiple peripherals share the same bus and are distinguished by fixed device addresses. This has two real-world consequences:

* **Efficient:** Since all peripherals share the same bus, you just need *two GPIOs*, regardless of how many peripherals (i.e. displays, sensors, etc) you want to connect.
* **Limited:** Since each *I2C* peripheral needs to be targeted by its specific *address*, and since most peripheral classes use *hard coded addresses*, you can only use *one display*, or you would have to find multiple *I2C displays* with *different* built-in addresses. In addition, the data transfer speed of *I2C* is limited. While you can display text and static information, *I2C* is less ideal for high data rates such as streaming video or sophisticated animations.

## Pins On Display
*I2C* displays typically have *four* pins, two of which are for their power supply. The other two pins resemble the *I2C interface*:


| Pin | Description |
| --- | --- |
| SDA | Serial Data  (data packages with payload and overhead information, i.e. the target address) |
| SCL | Serial Clock (synchronizes the data speed)  |
| VDD | positive voltage, make sure the voltage matches the display requirements |
| GND | ground |

## Pins On Microcontroller

The pins you use for *I2C* on the microcontroller development board depends on the microcontroller type you use, and sometimes on the board design:

* **Mandatory Pins:** Older microcontrollers like the one on *Arduino Mega* have designated *I2C* pins that you *must* use.
* **Assignable Pins:** Microcontrollers like *ESP32* have default *I2C* GPIOs that you *should* use (because they are more performant), but you can also use any other suitable *GPIO* instead (which then emulates *I2C* in software).
* **Routable Pins:**  Modern microcontrollers like *ESP32-C3* and *ESP32-S3* have routable *I2C controllers*, so you can assign any suitable *GPIO* with their hardware-optimized *I2C controller(s)*.

Here is a table with some suggestions:

> [!IMPORTANT]
> The development board **you** are using [may use different GPIOs](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/c3supermini/#i2c). Modern *ESP32 family members* such as *ESP32-C3* or *ESP32-S3* can route *any* GPIO to its hardware *I2C controllers*, and development board designers may have designated arbitrary *GPIOs*.

| Microcontroller       | SDA Pin        | SCL Pin        | Pin Reassignment Allowed? |
|-----------------------|----------------|----------------|--------------------------|
| **Arduino Uno R3**        | A4   | A5   | No                       |
| **Arduino Uno Mini LE**        | A4   | A5   | No                       |
| **Arduino Uno R4**        | A4   | A5   | No                       |
| **Arduino Uno WiFi**        | 20   | 21   | No                       |
| **Arduino Leonardo**        | D2   | D3   | No                       |
| **Arduino Nano**        | A4   | A5   | No                       |
| **Arduino MKR**        | D11   | D12   | No                       |
| **Arduino Giga R1**        | 20   | 21   | No                       |
| **Arduino Due**        | 20   | 21   | No                       |
| **Arduino Mega 2560**  | 20  | 21                      | No                       |
| **ESP8266**            | 4/D2    | 5/D1    | Yes                      |
| **ESP8266-01**            | 0/D5   | GPIO2/D3   | Yes                      |
| **ESP32**              | 21  | 22  | Yes                      |
| **ESP32-S2**           | 8   | 9   | Yes                      |
| **ESP32-S3**           | 8   | 9  | Yes                      |
| **ESP32-C3**           | 5   | 4   | Yes                      |
| **Teensy**         | [varies](https://www.pjrc.com/teensy/td_libs_Wire.html)  | [varies](https://www.pjrc.com/teensy/td_libs_Wire.html)  | Yes                      |
| **STM32 (Blue Pill)**  | PB9   | PB8  | Yes                      |
| **Digispark (ATTiny85)**| PB0/pin 5  | PB2/pin 7   | No                       |


When you are using a microcontroller that supports *I2C pin reassignments*, make sure you use a freely available *GPIO* that can *read* and *write* and has a built-in pull-up resistor.

## Power Supply

It is crucial to connect the *VDD* pin on your display with a power source of appropriate voltage. Typically, you must decide whether you connect *VDD* to the *5V* or *3.3V* pin on your microcontroller board:

* **Multiple Voltages:** some displays use internal voltage regulators so you can supply both *5V* and *3.3V*
* **Configurable Voltages:** some displays have *solder bridges* that you can leave open or bridge with some solder. This activates or bypasses internal voltage regulators. Depending on the state of the solder bridge, such displays require **either** *5V* **or** *3.3V*
* **Fixed Voltage:** some displays support just one fixed voltage, either *3.3V* or *5V*.

If in doubt, try with the *3.3V* pin first. If the display does not work with this lower voltage, you may want to use *5V*.

### Logical Level Voltage

Most displays internally use *3.3V logic levels* for *SDA* and *SCL*. When your microcontroller uses *5V* (i.e. older *Arduinos*), you need to use a *I2C-compatible* (fast) *level-shifter*, or at least some protective restistors for *SDA* and *SCL*.

Modern microcontrollers like the *ESP32* family run on *3.3V* and do not require level shifter.


> Tags: Display, I2C

[Visit Page on Website](https://done.land/components/humaninterface/display/usage/i2c?124774011323251131) - created 2025-01-22 - last edited 2025-01-22
