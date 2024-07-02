<img src="/assets/images/projects2.png" width="80%" height="80%" />
 
# Using Existing Firmware

> Flashing An ESP32 With Off-The-Shelf Firmware

In this first step my goal is a *proof of concept*: getting a fully functional *CO2 meter* with *minimum effort*.

## Selecting Firmware & Hardware
*CO2 Gadget* offers [five firmware versions](https://emariete.com/en/co2-meter-gadget/) targeting different microcontroller boards.


### Selecting Firmware Version

I opted for the generic *esp32dev_OLED* firmware which runs on a standard *ESP32* development board and comes with support for a standard *128x64 pixel OLED* display:

* **Generic Board:** I explicitly avoided the *TTGO* firmware versions that target a specific microcontroller board with built-in display. The goal was to work as much as possible with cheap standard components.
* **Using Display:** Even though I don't plan to use a tiny *OLED display* in the final device, for testing it is crucial to have a built-in display. It makes it much easier to see whether or not *everything works as designed*.

### Checking GPIO Pins

Here are the pins that the selected *firmware* is using:

| GPIO | Feature |
| --- | --- |
| 21/22 | I2C |
|  15/0 | Up/Down Button |
| 32 | Orange LED |
| 33 | Red LED |
| 2 | Buzzer |
| 26 | NeoPixel LED |

I then compared these pins with the *ESP32 DevKitC V4* microcontroller breakout board that I intended to use. 

Since *I2C* can be assigned to basically any pin on *ESP32*, it was important to check whether the pins used by the firmware were actually *exposed at all* on the breakout board. Which was the case.

> [!NOTE]
> Interesting boards like the *ESP32-S2 Mini* or the *ESP32-C3 SuperMini* do not expose all of the pins needed, so when a pre-compiled *firmware* is to be used, this significantly reduces the hardware choices.

### Figuring Out Circuitry
[CO2 Gadget](https://emariete.com/en/co2-meter-gadget/) is amazing but also somewhat *disorganized*: a wealth of information is presented, but not necessarily in the order in which an external person would approach such a project. 

The *firmware pin list* already suggests the circuitry. More detailed information is available as part of a [separate project](https://emariete.com/en/co2-meter-co2-display-tft-colour-ttgo-t-display-sensirion-scd30/) that focuses more on the *hardware* part. It points to a (Spanish) [YouTube video](https://youtu.be/pK5tKRq2gDo?si=PSeGYzxYTB4PquAu). Thanks to *auto translate*, it is simple to follow.

[Visit Page on Website](https://done.land/projects/sensors/co2sensor/firmware?467823061105240706) - created 2024-06-04 - last edited 2024-06-04
