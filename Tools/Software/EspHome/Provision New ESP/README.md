<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Provision New ESP Microcontroller

> Prepare A New Microcontroller And Turn It Into A Managed ESPHome Device

When you want to launch a new microcontroller-based electronics project, the first thing is to grab a supported microcontroller board and *provision* it. 

> [!NOTE]
> *ESPHome* supports *ESP8266*, the *ESP32* family, the *Raspberry RP2040*, plus the *Beken BK72xx* and *Realtec RTL87xx* microcontrollers typically found in commercial "smart" devices.



## Quick Overview
*Provisioning* a new microcontroller involves these two simple steps:

* Add a *New Device* to *ESPHome*
* Upload *ESPHome Firmware* to the microcontroller

After this, your *microcontroller* turns into a fully manageable *ESPHome device*. From then on, you can edit and change its *configuration*, adapt it to your needs and your project circuitry, and conveniently upload the automatically generated *firmware* via *OTA* (*over-the-air*, *wireless*) to your microcontroller.


### What's needed
Here are the prerequisites to create a *ESPHome-provisioned microcontroller*:

* **ESPHome:** you have already installed *ESPHome*. You can install it *stand-alone*, but it is strongly suggested you install *ESPHome* inside *Home Assistant* to fully leverage all of its capabilities and synergies.
* **Microcontroller:** you need a [supported](https://esphome.io/) microcontroller board
* **USB Cable:** during initial provisioning, the *ESPHome firmware* needs to be uploaded via *USB cable* (once provisioned, all future firmware uploads work wirelessly).


> [!NOTE]
> Here is an edge-case: if you'd like to flash a microcontroller inside a commercial "smart" device (to free it from the cloud and turn it into a locally controlled *ESPHome* device), the steps are the same except for the last one: since these microcontrollers are not designed to receive firmware updates via USB, you need to upload the firmware using a *UART-to-USB* controller, and manually solder the appropriate wires to the microcontroller pins *in situ*.    



## Adding New ESPHome Device

This first step does not require any hardware. You are creating a *ESPHome default configuration*.


### Visiting ESPHome Dashboard

When using *ESPHome* inside *Home Assistant*, click *ESPHome* in the *Home Assistant* side bar. This opens your *ESPHome dashboard*:

<img src="images/gui_esphome_addon.png" width="100%" height="100%" />

<details><summary>Using ESPHome Stand-Alone</summary><br/>

If you have installed *ESPHome* stand-alone, you need to first start the local *ESPHome webserver* via this command: `esphome dashboard d:\esphome_projects`. Make sure you adjust the path at the end of the command with the path to your local *ESPHome* project folder that you created during installation.

> [!TIP]
> You can enter above command in any *CLI console* (i.e. *cmd.exe* or *powershell.exe*), or you can press `WIN`+`R` to open the *Run* dialog, and enter the command here.





The command opens a console window that runs the local webserver. Now open a browser, and enter this url: `http://localhost:6052`. This opens the local stand-alone *ESPHome dashboard*:


<img src="images/dashboard_local.png" width="100%" height="100%" />


</details>


### Add New Configuration

Inside the *ESPHome Dashboard*, add a new device:

1. Click *NEW DEVICE*. A dialog opens and explains a lot of things that you can safely ignore for now. Just click *CONTINUE*.

<img src="images/1_esphome_config_start.png" width="100%" height="100%" />

2. You are asked to assign a *name* to your new device. Spaces will be converted to hyphens. In this example, the chosen name is *CO2 Sensor #1* (because ultimately, I want this new *ESPHome device* to become a precision CO2 sensor). Click *Next*.

<img src="images/2_esphome_config_name.png" width="100%" height="100%" />

4. Now select the type of microcontroller you are using. 

<img src="images/3_esphome_config_type.png" width="100%" height="100%" />

5. Access to your device is going to be protected by an *API key*. The next dialog page shows the assigned key so you can copy it. This is not necessary though as *ESPHome* manages the key for you, and you can always show it in the *ESPHome dashboard* later. Click *SKIP* to skip uploading the automatically generated firmware to your microcontroller for now.

<img src="images/4_esphome_config_secret.png" width="100%" height="100%" />

In your *ESPHome dashboard*, you now see your new *ESPHome device*. It is marked as *OFFLINE* in the tiles' right upper corner which isn't surprising: the device does not yet physically exist. Up to this point, we just created the *default configuration*.


### Default Configuration
During provisioning, *ESPHome* has created a *default configuration* for your device. You can see this configuration when you click *EDIT*:

<img src="images/editconfig.png" width="100%" height="100%" />

The *default configuration* takes care of the fundamentals like naming, board specs, connecting details for your *WiFi*, etc., and looks similar to this:


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

You don't necessarily need to touch these entries. 

> [!TIP]
> Hover over items in the *configuration* to view *tooltips* that explain in detail what these items do.    

<img src="images/7_tooltip.png" width="100%" height="100%" />



#### IMPORTANT: Breaking Change
Previously, *OTA* was defined in this way:

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

If you are using older configurations, it is sufficient to add `- platform: esphome` to make sure your configuration compiles with the current versions of *ESPHome*.



<details><summary>Here is what the default configuration items do:</summary><br/>



* **esphome:**
  * *name:* *mDNS* network name that is assigned to the device. It is derived from your project name. Spaces and special characters are replaced.
  * *friendly name:* clear-text name that appears in the *ESPHome dashboard*. 

* **esp32:** (this can be a different item when you have selected a different microcontroller)
  * *board:* the type of microcontroller board. *esp32dev* is the default configuration for generic *ESP32* boards.
  * *framework:* the type of programming framework to use. By default, *ESPHome* uses *Arduino*, but you could also use *ESP-IDF* (the ESP vendors' own programming environment)

* **logger:** by default, all messages with a severity of *DEBUG* or higher are logged through the serial port. You can [adjust](https://esphome.io/components/logger.html#logger-component) these settings, i.e. for more verbose logging.

* **api:** specifies an *encryption key* that is required whenever you want to communicate wirelessly with the microcontroller via the *ESPHome API*. This key is automatically generated and stored for you. It must match the key inside the *firmware* that was uploaded to your microcontroller.   

* **ota:** defines the secret password for *over-the-air* firmware updates. This password must match the password defined in the uploaded firmware. *ESPHome* can then upload future *firmware updates* conveniently via *WiFi*.   



* **wifi:** defines the access parameters for your home *WiFi*. The actual *SSID* and *password* are stored globaly in the secret store.

  * *ap:** if your microcontroller is unable to connect to your *home Wifi* for whatever reason, the *ESPHome firmware* automatically opens its own *WiFi access point* (*hotspot*). 

* **captive_portal:** when this component is part of your *configuration*, it instructs your microcontroller to provide a web portal that you can use to change the *WiFi settings* or manually upload *new firmware*. The *captive portal* is activated when the regular *WiFi* cannot be reached, and can be accessed via the *hotspot* that is defined in *ap:*. There are no configuration settings for this item.


</details>



## Uploading Firmware
Next, connect your *microcontroller board* via USB cable **to the computer that is running ESPHome**. 

This physical connection is required only for initial provisioning. Once provisioned, all future firmware updates can be performed wirelessly via *OTA* (*over-the-air updates*). 



> [!TIP]
> If you have installed *ESPHome* as part of *Home Assistant* and run this on a *Raspberry Pi*, connect your microcontroller board to one of the *USB ports* of the *Raspberry Pi*.




1. Visit the *ESPHome Dashboard*. and look for the tile that represents your *ESPHome device*. Click the *three-dot* icon, and choose *Install*.




<img src="images/install.png" width="60%" height="60%" />










2. Choose *Plug into the computer running ESPHome Dashboard*. 



<img src="images/rasp_selectport.png" width="100%" height="100%" />

3. The port connected to the microcontroller in the screen shot below is shown as *dev/tty/USB0*, indicating that this port is provided by a *Linux* system (a *Raspberry Pi* running *Home Assistant*). On a *Windows* machine, the port would show as *COMxxx*.




<img src="images/rasp_port.png" width="100%" height="100%" />

4. *ESPHome* now compiles the firmware file and then uploads it to the microcontroller. This can take several minutes. A terminal window logs each step taken.

<img src="images/rasp_install.png" width="100%" height="100%" />

9. Wait for the installation process to be finished. There is no distinct *finish* message: the dialog simply shows the output of the serial monitor until you click *STOP*. When you feel the installation is done (or when you are no longer interested in viewing the log entries), click *STOP* to close the window.


Once the firmware has been uploaded to your microcontroller board, it reboots and becomes available: in *ESPHome dashboard*, its tile is now marked *ONLINE* in its upper right corner:

<img src="images/rasp_sensor_online.png" width="100%" height="100%" />


> [!IMPORTANT]
> The indicator of success at this point is that your new *ESPHome device* reports as being **online** in *ESPHome dashboard*. If it remains **offline**, you need to troubleshoot connectivity issues before proceeding with anything else (see below).







### Troubleshooting Offline Devices
Should your *ESPHome device* not show *ONLINE* in *ESPHome dashboard*, review the following troubleshooting steps:

* **Reset:** Press the *RESET* button on the microcontroller just to make sure the microcontroller is not locked in the *firmware upload mode*.   
* **Power:** Make sure you connect the microcontroller to a *solid and reliable* power source. Most cheap *USB splitters* do not provide enough power. Keep in mind that sensors and components may cause spikes of high power consumption. When the power supply is insufficient, the *ESPHome* firmware senses a *brown-out* and keeps resetting the microcontroller.   
* **Network:** Is the computer that is running *Home Assistant* connected *to the same network* as the microcontroller? This is crucial. If your *Home Assistant* is running on a *Raspberry Pi* that is using a *wired* network cable, and your microcontroller is connecting to *WiFi*, then *mDNS* may not work. 


<details><summary>Using Static IP Addresses (Not Recommended)</summary><br/>

While you *can* configure the *ESPHome* device to use *static IP addresses*, and while you also *can* use *ping* instead of *mDNS* to check for availability, these options are all just *workarounds* for a more fundamental underlying networking problem. 

If you apply these workarounds, chances are you eventually run into other issues until you *fix the underlying network problems* which almost always boil down to this: *Home Assistant* and your devices are connected to different subnets (i.e. *Raspberry Pi* running *Home Assistant* is connected to a *wired* network while all of your devices connect *wirelessly*, and your *WiFi* is running in *Router* mode, effectively separating these networks from each other in a way that *mDNS* name resolution does not work across the networks).    

If you cannot fix the network, you may work around it by using *static IP addresses* and/or *ping* instead of *mDNS*. 

To assign a static *IP address*, add these lines to the section *wifi:*:
````
  manual_ip:
    static_ip: 192.168.2.231
    gateway: 192.168.2.1
    subnet: 255.255.255.0
````

If the problem persists, you may want to disable the *WiFi power saving features* by adding this setting:

````
  power_save_mode: none
````

If you'd like to use *ping* instead of *mDNS* to check availability, in *Home Assistant* go to *Settings*, then *Add-ons*, then click on *ESPHome*. At the top of the page, click on *Configuration*, and turn on *Show unused optional configuration options*. Identify the option *Use ping for status* and turn it on. Then click on *SAVE*. 

**IMPORTANT:** click on the *SAVE* right next to the group of settings you changed. You are prompted to restart *ESPHome*.


</details>





### Automatic Device Discovery

*Home Assistant* should pick up your new *ESPHome* device automatically within seconds. Just make sure the device reports *ONLINE* in the *ESPHome Dashboard*.


> [!TIP]
> If your *ESPHome* device won't be automatically recognized by *Home Assistant*, check this: go to *Settings*, then *Add-ons*, then click on *ESPHome*. At the top of the page, click on *Configuration*, and turn on *Show unused optional configuration options*. Identify the option *Home Assistant Dashboard Integration* and turn it on if it was off. Then click on *SAVE*.  





### Notification
In its *side bar*, the item *Notification* is marked with an orange bullet, and when you click it, a newly discovered device is reported:


 

Click *Check it out* to see the newly discovered devices. In my example, the newly created *CO2 Sensor* shows up.

<img src="images/rasp_co2sensor.png" width="100%" height="100%" />

Click *CONFIGURE* to add it to *Home Assistant*. You can then assign it a room or location:

<img src="images/rasp_adddevice.png" width="100%" height="100%" />

> [!IMPORTANT]
> Up until now, you have just *provisioned* your microcontroller and turned it into a generic *ESPHome device*. This device isn't really doing anything useful yet. The indicator of success at this point is that your device shows up in *Home Assistant*, and that it is labeled *ONLINE* in the *ESPHome Dashboard*.


> Tags: EspHome, Home Assistant, Provision, Initialize, Configuration

[Visit Page on Website](https://done.land/tools/software/esphome/provisionnewesp?134804061917245543) - created 2024-06-02 - last edited 2024-07-02
