<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# ESPHome Remote Control

> Universal Remote Control With Buttons And Indicator Lamps

It is simple to create a universal remote control device with ESPHome: it consists of a number of buttons and indicator lamps, and you can use it to control devices and see the device state.

For example, you could pair the remote control with a [smart powerstrip](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/4-socketsmartpowerstrip/) and turn the devices on and off that you plug into the power strip. 

Indicator LEDs on the remote control always visualize the state of the plugs.

## Overview

This article consists of a two parts:

* **Hardware:** Create a universal remote control device. It's up to you how many buttons your remote control should get, and what kind of indicator lamps you want to use.
* **Firmware:** To *pair* the remote control with actual devices, there are two options:
  * **Push:** Use a centrally managed *Home Assistant* automation script. In this case, *Home Assistant* manages your remote control.
  * **Pull:** Make your remote control firmware intelligent by granting it access to the *Home Assistant API*. In this case, the remote control manages itself.



> Tags: ESPHome, Remote Control

[Visit Page on Website](https://done.land/projects/esphome/showingstate/remotecontrol?657329041919251438) - created 2025-04-18 - last edited 2025-04-18
