<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP32

> The Classic ESP32 Microcontroller Sets New Standards And Comes As WROOM and WROVER



The *original (classic) **ESP32*** was launched in 2016 and called *WROOM*. A variant with extra *PSRAM* was called *WROVER*. There are dev boards with a built-in *PCB antenna*, and boards with an *IPX connector* to connect a *real external antenna* for more reach.

<img src="images/esp_wroom_top_front2_t.png" width="60%" height="60%" />

## ESP32 Types

When you purchase **ESP32** dev boards, look for the fine print in the type:

* **WROOM-32:** First version of **ESP32**
* **WROOM-32D:** Revised version of **ESP32** with PCB antenna
* **WROOM-32E:** Same as *WROOM-32D* but with an IPX antenna jack for connecting an external antenna
* **WROVER:** Same as *WROOM-32* but with additional 4/8 MB *pSRAM*
* **WROVER-B:** Same as *WROOM-32D* but with additional 8MB *pSRAM*
* **WROVER-IB:** Same as *WROVER-B* but with an IPX antenna jack instead of a built-in PCB antenna

## ESP32 Pins

When using an *ESP32* in projects, one of the most important question is which *GPIO* pins to use. All *ESP32 Types* use the same pins, so below list of available general purpose pins applies to all of them.

> [!IMPORTANT]
> Not all microcontroller boards expose all pins. 


### Selecting GPIO
Any *ESP32* provides six *general purpose GPIO* pins that are always *safe to use*, work as *input* or *output*, and support pullup/pulldown resistors.

Then there are an additional four *input-only* pins that do not support pullup/pulldown.

Five pins are designated for commonly used hardware interfaces (*I2C* and *SPI*). They can be used for other purposes if these interfaces are not needed.

A *ESP32* can provide a maximum of *15 input pins* that are *safe to use*, and an additional *5 pins* that can be used with only moderate limitations.

Finally, there are five more *GPIOs* that are used by the *ESP32* during *boot* and for *serial communications*. With care, these pins can also be used.

#### 6 Always-Safe General Purpose GPIOs

Below *ESP32 pins* are safe to use for *whatever purpose*. Whether your microcontroller board actually *exposes* a particular pin depends on the board design.


| GPIO | Label | Remark |
| --- | --- | --- |
| 4 | D4 | general purpose input/output GPIO|
| 13 | D13 | general purpose input/output GPIO|
| 14 | D14 | general purpose input/output GPIO|
| 16 | RX2 | general purpose input/output GPIO|
| 17 | TX2 | general purpose input/output GPIO|
| 20 | D20 | general purpose input/output GPIO|


#### 4 Safe Input-Only Pins

The pins below are *safe* to use for *inputs only*. These pins do not feature a built-in pullup/pulldown resistor. If you use these, add an external resistor.

| GPIO | Label | Remark |
| --- | --- | --- |
| 34-35 | D34-D35 | input only, no pullup/pulldown resistor |
| 36 | VP | input only, no pullup/pulldown resistor |
| 39 | VN | input only, no pullup/pulldown resistor |


> [!CAUTION]
> *GPIOs 34-36* and *39* do not provide an internal pullup/pulldown-resistor. If you want to use one of these, make sure you add an external resistor to prevent the input from *floating* when the button is not pressed.     

#### 5 Interface Pins
The pins below are used for *I2C* and *SPI* communications. 

They are not needed in *this* example, so you are free to use them. If you plan to add components to your project later that require *I2C* or *SPI*, then better keep them reserved.

| GPIO | Label | Remark |
| --- | --- | --- |
| 18-19 | D18-D19 | SPI: 18=SCLK, 19=MISO |
| 21-22 | D21-D22 | I2C: 21=SDA, 22=SCL |
| 23 | D23 | SPI: MOSI |


#### 5 Dual-Use Pins
If you *need even more* inputs, you can safely use the additional *five pins* listed below - provided **you do not push** attached buttons while the microcontroller is using these pins for other purposes (see column *do not use while...*):


| GPIO | Label | Do not use while... |
| --- | --- | --- |
| 2 | D2 | booting. Pin is attached to internal LED (if present) |
| 3 | RX | serial communication (i.e. uploading via serial) |
| 5 | D5 | booting |
| 12 | D12 | booting |
| 15 | D15 | booting |



> Tags: Microcontroller, ESP32, WROOM, WROVER, 32D, 32E, WROOM-32D, WROOM-32E, WROVER-B, WROVER-IB, PSRAM, GPIO

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/classicesp32?486134031823244200) - created 2024-03-23 - last edited 2024-07-02
