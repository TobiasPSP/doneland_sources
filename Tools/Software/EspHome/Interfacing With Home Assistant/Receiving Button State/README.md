<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Receiving Button State

> Getting Notified When A Certain Home Assistant Device Like A Switch Or Sensor Changes Its State

It is trivial to instruct *Home Assistant* to *forward* the state of a given entity to your device. Before you look into the details, here are the prerequisites:

* **Device Added To Home Assistant:** your *ESPHome device* **must have been** added to *Home Assistant*, and your *configuration* must have requested `api:` access. This is typically automatically configured in your *configuration* when you add a new *ESPHome device*.
* **Sensor Type:** you must know the *sensor type* of the entity you want to read: `binary_sensor:` (like a switch), `sensor:` (numerical data like a temperature sensor), or `text_sensor:` (for text values). If the sensor you are interested in was defined by an *ESPHome device*, simply look up the sensor type in that *configuration*.

## Button State
Most buttons are represented by a `binary_sensor:` and can have an *on* and *off* state. Let's assume the *entity id* of the switch you are interested in is `switch.powerstrip_400w_ssr_1_switch1`. Then this `binary_sensor` named *light1state* would notify you whenever the button state changes:

````
binary_sensor:
  # HOMEASSISTANT SENSORS
  - platform: homeassistant
    name: "Light1"
    id: light1state
    entity_id: switch.powerstrip_400w_ssr_1_switch1
    on_state: 
      then:
        - if:
            condition:
              lambda: 'return id(light1state).state == true;'
            then:
              # Actions when the switch is turned on
              - logger.log: "The switch was turned ON!"
            else:
              # Actions when the switch is turned off
              - logger.log: "The switch was turned OFF!"
````


If your *ESPHome device* has been added to *Home Assistant*, you can interface your *configuration* with *Home Assistant entities* in a number of ways.

> [!IMPORTANT]
> Your device **must have been added to Home Assistant** before you can access *Home Assistant entities*. Even if you are using *ESPHome* inside of *Home Assistant*, you **still** need to explicitly *add* your *ESPHome device* to *Home Assistant*. Typically, when you create a new *ESPHome device*, the first time you upload your firmware to it and run it, *Home Assistant* pops up an automatic notification about "newly discovered devices". Click the notification and follow the instructions to add the device.


## Overview

Here are a few use cases illustrating the potential of interfacing *ESPHome configurations* with *Home Assistant*:

* **Publishing Information:** your microcontroller may be battery-driven, and you'd like to publish the current battery state to *Home Assistant* so in the *Home Assistant dashboard*, you can immediately see when the battery runs low.
* **Publishing Controls:** you may want to use buttons on your device to control *other devices* managed by *Home Assistant*. For example, you may want to create a set of buttons that can switch on and off some lights in your house.
* **Receiving Device State:** you want *Home Assistant* to inform your device when a given entity state changes. For example, you want your device to show icons based on which lamps in your house are currently turned on or off.




> Tags: ESPHome, Home Assistant, Interface, Event


