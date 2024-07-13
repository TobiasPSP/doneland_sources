<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Introduction

> All You Need To Know To Get Started With ESPHome


*ESPHome* consists of a number of moving parts. To better understand how they interact and work, and where to start, here is a quick overview:


<img src="images/overview_esphome_parts.svg" width="100%" height="100%" />

## Step 1: Use Supported Microcontrollers
Start with a microcontroller board that is [supported](https://done.land/tools/software/esphome/introduction/provisionnewmicrocontroller#supported-microcontrollers) by *ESPHome*. 

<img src="images/esp32_devkitc_v4_side_t.png" width="50%" height="50%" />

## Step 2: Provision Microcontroller
Open a browser like *Chrome*, and [provision](https://done.land/tools/software/esphome/introduction/provisionnewmicrocontroller) your microcontroller so it can be discovered and used by *ESPHome*. Provisioning *uploads ESPHome firmware* to it.


<img src="images/firstuse_provisioning_example.png" width="50%" height="50%" />

Don't forget to [configure WiFi access](https://done.land/tools/software/esphome/introduction/configuringwifi) so it can connect to your *WiFi* and be discovered by *ESPHome*.

<img src="images/esphome_provisioned_dialog.png" width="50%" height="50%" />

## Step 3: Adopt Microcontroller in ESPHome
Once a *provisioned microcontroller* goes online, it is automatically discovered by *ESPHome* and surfaces in *ESPHome Desktop* where you can [adopt](https://done.land/tools/software/esphome/introduction/adoption) it. It is now ready to use.

<img src="images/adoption_tile_detail.png" width="50%" height="50%" />

## Step 4: Design Your Hardware Project
Design your *hardware setup* as you normally would do: compose *schematics*, and wire everything up.

<img src="images/example_hardware_prototype.png" width="100%" height="100%" />

## Step 5: Translate Hardware Into ESPHome Configuration
With *ESPHome*, no programming is required. Instead, you [translate* your hardware setup into a *configuration*](https://done.land/tools/software/esphome/introduction/editconfiguration).


<img src="images/edit_config_esphome_example.png" width="100%" height="100%" />

## Step 6: Upload Auto-Generated Firmware
When you completed the *configuration* and would like to test it, ask ESPHome to [auto-generate the firmware for it and upload it to your microcontroller](https://done.land/tools/software/esphome/introduction/provisioningdirectly#uploading-firmware).



<img src="images/esphome_compile_config_example.png" width="100%" height="100%" />


## Step 7: Add Device To Home Assistant
Once your device is set up and online, *Home Assistant* automatically detects it. [Add your device to Home Assistant](https://done.land/tools/software/esphome/introduction/addtohomeassistant) to be able to tap into plenty of additional functionality.



<img src="images/homeassistant_autodiscovery_example.png" width="100%" height="100%" />

*Integration with Home Assistant* is optional. If you do not run a *Home Assistant* yet, you may want to [look into setting one up](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/setup). It's really simple and adds so much more opportunities for you.



<img src="images/raspberry_homeassistant_overview_example.png" width="100%" height="100%" />

## Step 8: Home Assistant Dashboards
For example, [add new *dashboards*](https://done.land/tools/software/esphome/introduction/usingdashboards) in *Home Assistant*, and display sensor readings or virtual buttons to control your devices *manually*.


<img src="images/sensordetail_co2_sensor_1.png" width="100%" height="100%" />

## Step 9: Set up Automations
You can now also [set up automation scripts](https://done.land/tools/software/esphome/introduction/addingautomation) hosted by *Home Assistant* that are automatically *triggered* when a device state changes. 


<img src="images/example_automation_homeassistant.png" width="100%" height="100%" />

Whether you want to respond to a *button click*, or turn on *air conditioning* based on a *sensor reading*, is now all possible and requires only a few clicks.

> Tags: EspHome, Overview, Concept

[Visit Page on Website](https://done.land/tools/software/esphome/introduction?178673071213245544) - created 2024-07-12 - last edited 2024-07-12
