<img src="/assets/images/projects2.png" width="80%" height="80%" />
 
# CO2 Air Quality Sensor

> Quick Project To Showcase Building Powerful Devices From 3rd Party Firmware

There are plenty of *CO2 and air quality devices* available that are *ready to use*, neat looking, and cheap. Most of these use sensors though that aren't really suited to accurately measure *CO2*. Measuring *CO2* in a precise way is technically complex. Devices that measure right are very expensive. 

## CO2 Gadget Firmware
[CO2 Gadget](https://emariete.com/en/co2-meter-gadget/) is the name of a project that created a sophisticated *firmware* for *ESP32*-based *microcontrollers*. The *firmware* is highly configurable and works with a variety of precision sensors.

In this project I wanted to see how easy it actually is to turn a couple of components into a top notch *CO2 meter*. At the center of this project is a *Sensirion SCD30* CO2 sensor.


## Steps
This project serves to test and showcase a couple of common concepts which is why it is splitted in a few parts:

* **Flashing Existing Firmware via Browser:** it becomes increasingly popular (and convenient) to *flash* a microcontroller directly from a web browser. *CO2 Gadget* provides this feature as well. When you use a *pre-compiled firmware file*, it is highly specific and runs only on the hardware that it was compiled for. I.e., the GPIO pins need to match your actual board. This is what I am trying first by using one of the supported microcontroller breakout boards.
* **Adjusting Source Code:** I don't want to use a bulky *ESP32 development boards* in my *CO2 Meter Device* and rather take a much smaller *ESP32-C3 SuperMini*, or a *ESP32 WeMos LOLIN* with battery support. Since there is no *pre-compiled firmware* for these boards available, here I am trying to adapt the [Source Code](https://github.com/melkati/CO2-Gadget/tree/master) to other hardware, then compile and upload it to my *ESP32-C3*.
* **Adjusting Display:** the original source code comes with support for small *OLED* screens and *TTGO microcontroller boards with built-in display*. I'd like to find out how hard it is to adapt the *source code* to larger *TFT displays*.
* **Battery-Power:** I'd like the device to run primarily on *USB C* power, but with the option to use an internal *LiPo* battery. Here I am going to test overall power consumption, the changes in hardware design to add a *charger*, and a battery meter.

[Visit Page on Website](https://done.land/projects/sensors/co2sensor?445884061105240706) - created 2024-06-04 - last edited 2024-06-04
