<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Push Button

> Controlling Any Device Via Physical Push Buttons

Occasionally it is easier to control devices via *physical buttons* than having to grab your smartphone and using the *Home Assistant* app. 

In this article I am going to show how a simple *physical push button* can be added to *Home Assistant*, and how you can assign *actions* to it to control any device that was added to *Home Assistant*.

> [!TIP]
> Once you get the basic idea, it is simple to expand the example and build more sophisticated physical *dash boards* with many more buttons.     







## Hardware

You need a *push button*, a *resistor*, and an *ESP* microcontroller.



### Selecting ESP Microcontroller
This example requires just *one input pin* so you can use just about *any* ESP microcontroller board (including *ESP8266*).   

If you plan to *expand* this example in the future to host additional buttons (and possibly displays or other components) to build a sophisticated *dashboard*, make sure you pick an *ESP* board that exposes as many *ESP32 pins* as possible.


> [!TIP]
> The *ESP32 DevkitC V4 38 pin* microcontroller board is a good choice as it exposes all available *GPIOs* and does not have a built-in user-configurable *LED*.    






### Selecting GPIO
A *ESP32* can provide a maximum of *15 input pins* that are *safe to use*, and an additional *5 pins* that can be used with only moderate limitations.


#### 6 Safe ESP32 Pins

Below *ESP32 pins* are safe to use for *whatever purpose*. Whether your microcontroller board actually *exposes* a particular pin depends on the board design.


| GPIO | Label | Remark |
| --- | --- | --- |
| 4 | D4 | general purpose input/output GPIO|
| 13 | D13 | general purpose input/output GPIO|
| 14 | D14 | general purpose input/output GPIO|
| 16 | RX2 | general purpose input/output GPIO|
| 17 | TX2 | general purpose input/output GPIO|
| 20 | D20 | general purpose input/output GPIO|


#### 4 Safe ESP32 Input-Only Pins

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


## Circuit

The circuit diagram is straight-forward. I am using *GPIO34* (*input* pin that has no internal pullup/pulldown resistor) to illustrate how to use an external *pull-down resistor*.



<img src="images/schematics_button.png" width="100%" height="100%" />



> Tags: EspHome, Home Assistant, ESP8266, ESP32

[Visit Page on Website](https://done.land/tools/software/esphome/editconfiguration/pushbutton?114898061229240725) - created 2024-06-28 - last edited 2024-06-28
