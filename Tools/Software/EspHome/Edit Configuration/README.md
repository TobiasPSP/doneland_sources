<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Edit Configuration

> Programming A ESPHome Device By Describing Its Hardware 


When you created a new device in *ESPHome*, you are now ready to *program* its microcontroller - without actually writing a single line of code. Instead, you *describe* your hardware to *ESPHome*.

Here is the typical workflow:

* **Adjusting Configuration:** edit the *configuration* of a *ESPHome device*, and describe its hardware design
* **Install Updated Firmware:** let *ESPHome* create a new firmware based on your updated *configuration*, and upload it *wirelessly* to your microcontroller



## Prerequisites

This article deals with *updating* a *configuration*. It assumes that you already did this:

* **ESPHome installed:** *ESPHome* should be up and running already, either as part of *Home Assistant*, or *stand-alone*
* **New Device created:** You created a *new device* inside the *ESPHome Dashboard* and ensured that your new device is marked as *ONLINE*.  

<details><summary>Recap: How To Successfully Provision A New EspHome Device</summary><br/>   

Let's recap the process of *initializing* a new microcontroller in *ESPHome*:

1. **Create New Device:** inside the *ESPHome Dashboard*, create a new device during which you will be asked to *name* your project, and to select the type of *microcontroller* you are using. At the end of the creation process, the dialog offers to *Install* the created firmware to your microcontroller. Choose *Skip*.

2. Microcontrollers that you have previously provisioned and that are powered on will be marked with *ONLINE* in the tiles' upper right corner. Your newly added *configuration* hasn't yet been uploaded to any microcontroller, so it is obviously still marked as *OFFLINE*:    

<img src="images/1_newdevice.png" width="100%" height="100%" />

3. Now your actual microcontroller is provisioned: the automatically created *firmware* needs to be uploaded for the first time. This initial provisioning requires that you connect the microcontroller via *USB cable* to the computer running *ESPHome*. Then click the *three dot* menu, and choose *Install*:

<img src="images/2_install.png" width="100%" height="100%" />

3. This invokes the *firmware upload tool*. Choose *Plug into the computer running ESPHome Dashboard*, and select the *USB port* the microcontroller is connected to:


<img src="images/3_select_port.png" width="100%" height="100%" />

4. Now the *firmware* is compiled and will be uploaded to your microcontroller. You see a terminal window that logs every step, similar to what you would see in a manual *IDE* like *platformio*.

<img src="images/4_upload.png" width="100%" height="100%" />


5. In the dialog showing the terminal window, click *STOP* to no longer listen to the status messages. In your *ESPHome Dashboard*, your microcontroller will now be marked *ONLINE*: it is now running the *ESPHome firmware* that you just uploaded.


<img src="images/5_online.png" width="100%" height="100%" />


</details>

## Editing The Configuration

To open and view the *configuration* of an *ESPHome device*, click *EDIT*. This opens its current *configuration* in the editor. 


<img src="images/6_edit.png" width="100%" height="100%" />

Do not touch the default configuration (unless you know what you are doing and would i.e. like to rename your project, or change the *WiFi* connection).

Move to the *end* of the configuration, and *begin adding* new lines that describe the additional components that your project is using. 

All the details involved here are best learned by example, so I prepared a number of sample configurations in separate articles where you learn the details about "translating" your hardware into a valid *configuration*:

* **CO2 Sensor:** Use a *SCD30* CO2 sensor component to precisely measure the *CO2 concentration* in the air.
* **Push Button:** Use a simple push button that can then be tied to any other device. In essence, the *push button* serves as an example on how to build physical dashboards that can control any other device


## Validating Edited Configuration
You can (and should) always *validate* an edited configuration by clicking the *three-dot* menu in the *ESPHome device tile*. 


<img src="images/validate.png" width="100%" height="100%" />

The validation result should always be *Configuration is valid!*. If it is not, here are the top two reasons for validation errors:

### Caveat: Indentation
A *configuration* really is a *tree-like* hierarchical structure: items are *grouped* by *indentation*. That's why *correct order* and *indentation* is *crucial*. 

Here is a typical error message that may bite you:

````
mapping values are not allowed here
  in "/config/esphome/push-button.yaml", line 35, column 18
````

This essentially translates to: *ESPHome* came across key words that did not make any sense at that position.

And here is the root cause (don't focus on the details, just look at the general structure):

````
binary_sensor:
  - platform: gpio
    pin: GPIO4
         inverted: true
    name: Pushbutton1
    filters: - delayed_on: 10ms
             - delayed_off: 10ms
    mode:
        input: true
        pullup: true
````

This is how the *configuration* needs to be correctly indented and grouped:

````
binary_sensor:
  - platform: gpio
    name: Pushbutton1
    pin: 
        number: GPIO4
        inverted: true
        mode:
          input: true
          pullup: true
    filters: 
      - delayed_on: 10ms
      - delayed_off: 10ms
````

As you see, the *order*, the *indentation*, and thus the *grouping* is essential for *ESPHome* to correctly understand your input.

### Breaking Changes
From time to time, *ESPHome* evolves and introduces *breaking changes*. So when you *update ESPHome*, your configuration may no longer work.

Instead, you may receive a validation error like this one:

````
Failed config

ota.unknown: [source /config/esphome/push-button.yaml:19]
  
  'ota' requires a 'platform' key but it was not specified.
````

Fortunately, breaking changes do not occur frequently, but they do occur. Previously, *OTA* was defined in this way:

````
ota:
  password: "..."
````

Starting with *ESPHome 2024.6.0*, this entry now must look like this:

````
ota:
  - platform: esphome
    password: "..."
````

<img src="images/validate2.png" width="100%" height="100%" />




## Uploading Configuration
When your updated *configuration* is validated, you can upload it to your microcontroller:

1. In the *ESPHome Dashboard*, make sure your microcontroller is marked *ONLINE*. Click the *three-dot* menu, and choose *Install*.

2. Since your microcontroller has already been provisioned, you can now choose *Wirelessly*, and upload the new firmware conveniently via *OTA* (*over-the-air*).

3. *ESPHome* now compiles the new *firmware* and then uses *OTA* to wirelessly transfer the new *firmware* to your microcontroller:

<img src="images/9_ota.png" width="100%" height="100%" />

4. Once the transfer has completed, click *STOP* to close the terminal window. Verify that your microcontroller is still labeled *ONLINE* in *ESPHome Dashboard*. You just successfully re-programmed your microcontroller - without writing any code.


> Tags: EspHome, Home Assistant, Configuration, Programming, YAML, Validation

[Visit Page on Website](https://done.land/tools/software/esphome/editconfiguration?070255061229240725) - created 2024-06-04 - last edited 2024-07-02
