<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Classic Button-and-LED Remote Control

> The Most Simple Form Of Remote Control Requires Just A Few Push Buttons And LEDs

The most basic remote control needs push buttons to toggle devices, and an indicator LED to display the device status.

In addition, you need a microcontroller that is compatible with *ESPHome*, i.e. a [ESP32-S2 Mini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/s2mini/).

## Overview
In its most simple form, a remote control requires one push button plus one standard indicator LED per controllable device. For example, with four push buttons and four LEDs, you get a 4-channel remote control. 

### Push Buttons
Each push button will be implemented as `binary_sensor:` and requires one *GPIO*. 

### LEDs
To provide visual feedback and indicate the current device status for the device that the push button controls, add at least one LED per push button. LEDs will be implemented as `output:`.

Here are your options:

* **One LED:**    
  The LED is *on* when the device is *on*, and *off* otherwise.
* **Two LEDs:**
  One LED is *on* when the device is *on* (i.e. *green*), and another LED is *on* (i.e. *red*) when the device is *off*
* **Bi-Polar LED:**
  By using a *bi-polar LED*, a single LED can visualize both states: it lights *green* when the device is *on*, and *red* when it is *off*

Regardless of how you wish to implement your visualization, the *ESPHome configuration* works fundamentally the same.

## Design

Each push button and each LED needs to be connected to **GND** and a dedicated *GPIO*.

### Push Buttons

Each push button needs a dedicated GPIO. You may want to use one of the *input-only GPIOs*. Enable the pullup resistor. If the GPIO has no built-in pullup resistor, add an external one.

In the ESPHome configuration, each push button is configured like this:

```yaml
binary_sensor:
  - platform: gpio
    name: button_channel1
    pin: 
        number: GPIO4       # adjust to the GPIO that you use
        inverted: true      # when button is pressed, GPIO is LOW. Invert this.
        mode:
          input: true
          pullup: true      # makes sure the GPIO is not floating (undefined) when button is not pressed
    filters:                # debouncing
      - delayed_on: 10ms
      - delayed_off: 10ms
```

### LEDs

Each LED requires a dedicated GPIO that can be used in *output* mode. Do not use *input-only GPIOs*.


In the ESPHome configuration, each push button is configured like this:

```yaml
output:
  - platform: gpio
    pin: GPIO2            # adjust to the GPIO that you use
    id: 'led_channel1'
```

### Wiring




> Tags: ESPHome, Remote Control

[Visit Page on Website](https://done.land/projects/esphome/showingstate/remotecontrol/classicbuttonandled?670268041919251438) - created 2025-04-18 - last edited 2025-04-18
