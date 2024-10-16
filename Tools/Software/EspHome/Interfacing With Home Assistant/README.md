<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Interfacing With Home Assistant

> Invoking Actions In Home Assistant, And Reading Sensor Values From Other Devices Managed By Home Assistant

If your *ESPHome device* has been added to *Home Assistant*, you can interface your *configuration* with *Home Assistant entities* in a number of ways.

> [!IMPORTANT]
> Your device **must have been added to Home Assistant** before you can access *Home Assistant entities*. Even if you are using *ESPHome* inside of *Home Assistant*, you **still** need to explicitly *add* your *ESPHome device* to *Home Assistant*. Typically, when you create a new *ESPHome device*, the first time you upload your firmware to it and run it, *Home Assistant* pops up an automatic notification about "newly discovered devices". Click the notification and follow the instructions to add the device.


## Overview

Here are a few use cases illustrating the potential of interfacing *ESPHome configurations* with *Home Assistant*:

* **Publishing Information:** your microcontroller may be battery-driven, and you'd like to publish the current battery state to *Home Assistant* so in the *Home Assistant dashboard*, you can immediately see when the battery runs low.
* **Publishing Controls:** you may want to use buttons on your device to control *other devices* managed by *Home Assistant*. For example, you may want to create a set of buttons that can switch on and off some lights in your house.
* **Receiving Device State:** you want *Home Assistant* to inform your device when a given entity state changes. For example, you want your device to show icons based on which lamps in your house are currently turned on or off.




> Tags: ESPHome, Home Assistant, Interface, Event

[Visit Page on Website](https://done.land/tools/software/esphome/interfacingwithhomeassistant?076110101316244926) - created 2024-10-15 - last edited 2024-10-15
