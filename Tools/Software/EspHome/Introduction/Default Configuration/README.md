<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Default Configuration

> Default Configuration Defines The ESPHome Device Fundamentals And How You Can Wirelessly Access It

Whenever you [create](https://done.land/tools/software/esphome/provisioningdirectly) or [adopt](https://done.land/tools/software/esphome/adoption) a new device in *ESPHome*, a *default configuration file* is automatically assigned to it and surfaces in *ESPHome Desktop*.

This *configuration* defines every detail of your device. The initial *default content* focuses on the bare device fundamentals, and you can [add more details](https://done.land/tools/software/esphome/editconfiguration), for example to describe your hardware setup and add special functionality.

## Overview
Each device is represented by its own *configuration file* and surfaces as a *tile* in *ESPHome Dashboard*. 

The name of the *configuration file* is the name of your device, and the file type is *yaml*. Click *EDIT* to view its content.


<img src="images/editconfig.png" width="100%" height="100%" />

The *default configuration* takes care of the fundamentals that are necessary to work with the device, like setting a device name, assigning a *mDNS host name*, defining the microcontroller type, supplying connection details like *WiFi SSID* and *password*, and so on. 

Here is a sample *configuration* from a newly created *ESPHome device*:


````
esphome:
  name: co2-sensor-1
  friendly_name: CO2 Sensor #1

esp32:
  board: esp32dev
  framework:
    type: arduino

# Enable logging
logger:

# Enable Home Assistant API
api:
  encryption:
    key: "..."

ota:
  - platform: esphome
    password: "..."

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Push-Button Fallback Hotspot"
    password: "..."

captive_portal:
````

You typically don't need to touch these entries unless you *really* want to change these fundamentals.

> [!IMPORTANT]
> Changing default entries can render your device inaccessible when you don't know what you are doing. For example, changing *name:* to assign a new hostname to your device fails miserably: ESPHome would use the *new name* to try and contact your device wirelessly to apply the new configuration. Since the device hasn't been renamed yet, it still uses its *old name* and becomes inaccessible. If you really want to rename the device host name, in its tile, click the *three dot* menu and choose *Rename hostname*.

All items in the *configuration* describe their purpose when you *hover* over them with the mouse pointer: *tooltips* summarize the purpose, and links guide you to the *documentation pages*.

<img src="images/7_tooltip.png" width="100%" height="100%" />



### Default Configuration Entries
Here is a quick overview of the *default entries* in your *default configuration*:

* **esphome:**
  * *name:* *mDNS* network name that is assigned to the device. It is derived from your project name. Spaces and special characters are replaced.
  * *friendly name:* clear-text name that appears in the *ESPHome dashboard*. 

* **esp32:** (this can be a different item when you have selected a different microcontroller)
  * *board:* the type of microcontroller board. *esp32dev* is the default configuration for generic *ESP32* boards.
  * *framework:* the type of programming framework to use. By default, *ESPHome* uses *Arduino*, but you could also use *ESP-IDF* (the ESP vendors' own programming environment)

* **logger:** by default, all messages with a severity of *DEBUG* or higher are logged through the serial port. You can [adjust](https://esphome.io/components/logger.html#logger-component) these settings, i.e. for more verbose logging.

* **api:** specifies an *encryption key* that is required whenever you want to communicate wirelessly with the microcontroller via the *ESPHome API*. This key is automatically generated and stored for you. It must match the key inside the *firmware* that was uploaded to your microcontroller.   

* **ota:** defines the secret password for *over-the-air* firmware updates. This password must match the password defined in the uploaded firmware. *ESPHome* can then upload future *firmware updates* conveniently via *WiFi*. The format for this entry has changed recently.   



* **wifi:** defines the access parameters for your home *WiFi*. The actual *SSID* and *password* are stored globaly in the secret store.

  * *ap:** if your microcontroller is unable to connect to your *home Wifi* for whatever reason, the *ESPHome firmware* automatically opens its own *WiFi access point* (*hotspot*). 

* **captive_portal:** when this component is part of your *configuration*, it instructs your microcontroller to provide a web portal that you can use to change the *WiFi settings* or manually upload *new firmware*. The *captive portal* is activated when the regular *WiFi* cannot be reached, and can be accessed via the *hotspot* that is defined in *ap:*. There are no configuration settings for this item.

## Verifying Configuration
You can always formally verify a *configuration* by clicking the *three dot* menu in the device tile, then choosing *Validate*.

Validation makes sure your *configuration* is formally valid. This is an important check once you start [editing and appending](https://done.land/tools/software/esphome/editconfiguration) the configuration, but it can reveal issues even without you touching anything.

### Fixing Breaking Changes
Every now and then, *ESPHome updates* introduce *breaking changes* that may include changes in the formatting rules. One such *breaking change* was introduced just recently (June, 2024). Let's look at this change, and how to identify (and fix) it.

Previously, *OTA* was defined this way:

````
ota:
  password: "..."
````

Starting with *ESPHome 2024.6.0*, this entry now must look like so:

````
ota:
  - platform: esphome
    password: "..."
````

*Validating* an old *configuration* would reveal a *formal problem*. You would then need to *edit* the *configuration*, identify the formal problem, and fix it.

In the case of this breaking change, adding the line  `- platform: esphome` to the *OTA entry* fixes the problem and makes sure that you can compile and upload your *configuration* again with *ESPHome versions 2024.6.0 and above*.


> Tags: EspHome, Configuration, OTA, Breaking Change

[Visit Page on Website](https://done.land/tools/software/esphome/defaultconfiguration?509558071812240227) - created 2024-06-08 - last edited 2024-07-11
