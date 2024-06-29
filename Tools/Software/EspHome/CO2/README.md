<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Provision New ESP Microcontroller

> Prepare A New ESP32 Or ESP8266 Microcontroller And Turn It Into A Managed ESPHome Device

When you want to launch a new microcontroller-based electronics project, the first thing is to grab a generic *ESP32* or *ESP8266* microcontroller board and *provision* it. 


## Updating Configuration
The *configuration* describes the *hardware setup* of your microcontroller project. Up until now, *ESPHome* just knows the *microcontroller type* because it asked for it.

In this example, I wanted to implement a high-precision *CO2 Sensor* using a *SCD30* sensor component. Without diving into technical details, let's see how a generic microcontroller is turned into such a device - without one line of programming.

### Default Configuration

Visit the *ESPHome Dashboard*, identify your device, and click on *EDIT*. This opens its current *configuration* in an editor.

By default, the configuration may look similar to this:


````yaml
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
  password: "..."

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Co2-Sensor-1 Fallback Hotspot"
    password: "..."

captive_portal:
    
````

The format of this file is called *YAML*, and it organizes information **by indentation**. This is very important when you start editing it: Always **use two spaces** for indenting one level.

The default configuration defines the network name, the microcontroller type, and the *WiFi* access.

It also contains a number of *security items* like an *API* key, or the *WiFi* password.

*Global* secrets (like the *WiFi* password) are stored centrally, and a placeholder is used. Specific secrets are stored directly in the *configuration*, i.e. the password for uploading a new firmware image (which I have replaced by *...*).


### Adding Hardware Description

You don't really need to mess with the default part of the configuration. You just *add* the description of *what **you** added* to the microcontroller.

Here is my *full* configuration for a beautifully working *CO2 Sensor*:

````yaml
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
  password: "..."

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Co2-Sensor-1 Fallback Hotspot"
    password: "..."

captive_portal:

i2c:
  sda: GPIO21
  scl: GPIO22
  scan: False
  id: bus_a

sensor:
  - platform: scd30
    co2:
      name: "Workshop CO2"
      accuracy_decimals: 1
    temperature:
      name: "Workshop Temperature"
      accuracy_decimals: 2
    humidity:
      name: "Workshop Humidity"
      accuracy_decimals: 1
    temperature_offset: 1.5 °C
    address: 0x61
    update_interval: 60s
    
````

Basically, I added the information for the *I2C* interface that the sensor uses to communicate with the microcontroller (defining the *GPIOs* used). 

And I added the sensor itself, including its *I2C* address and the desired update interval.

### Update Microcontroller

Whenever you make changes to a *configuration* and save it, these changes must be uploaded to your *microcontroller* to take effect.

So after you saved the changes and closed the editor, click the *three dot* menu. Click *Install*.

Now you see the same dialogs that you saw initially: choose an installation method, and upload the new firmware to your microcontroller.

> [!TIP]
> Once a microcontroller has received its *ESPHome firmware*, from now on its security is set up, and you can use convenient *OTA* (*over-the-air*, *wireless*) updates. No need anymore to physically connect the microcontroller to your computer.







### Notification
In its *side bar*, the item *Notification* is marked with an orange bullet, and when you click it, a newly discovered device is reported:

<img src="images/rasp_notification.png" width="100%" height="100%" />
 

Click *Check it out* to see the newly discovered devices. In my example, the newly created *CO2 Sensor* shows up.

<img src="images/rasp_co2sensor.png" width="100%" height="100%" />

Click *CONFIGURE* to add it to *Home Assistant*. You can then assign it a room or location:

<img src="images/rasp_adddevice.png" width="100%" height="100%" />

### Dashboards And User Interfaces

The new device is now part of *Home Assistant* and can be added to *dashboards* or used in *automation rules*.

<img src="images/rasp_newdash.png" width="100%" height="100%" />

When you add its *entities* (i.e. sensor values) to a dashboard, you immediately see the *synergies*: you can now view the sensor readings in real time and combine this sensor with other information.

<img src="images/dashboard_co2.png" width="100%" height="100%" />

### Monitoring And Logs

You don't just get a momentary display but also a *continuous monitoring* and *logging*: when you click the sensor gauge, *Home Assistant* pulls the sensor log and shows a graph.

Without diving too much into detail, all of this is highly customizable: you control the type and style of dashboard item, can define the timespan to show, and your *ESPHome* device *configuration* sets the *update interval* in which *Home Assistant* polls new sensor values.



<img src="images/sensordetail.png" width="100%" height="100%" />

> Tags: EspHome, Home Assistant, ESP8266, ESP32
