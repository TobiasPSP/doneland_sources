<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# ESPHome

> Free Open-Source Software To Control And Manage ESP Microcontrollers

[ESPHome](https://esphome.io/) is a free *open-source* software that seamlessly integrates into *Home Assistant*, but can also be installed *stand-alone* on various operating systems.

It automatically creates the *firmware* for *ESP* microcontrollers without writing any code. Via a *YAML* file, you *describe* the features of your microcontroller project, i.e. which *GPIOs* you use and what kind of *sensors* or *displays* you connected. *ESPHome* then takes care of the heavy lifting and automatically creates the firmware necessary to operate the microcontroller.

When integrated into *Home Assistant*, your *ESPHome-enabled* microcontrollers can be discovered like any other device and seamlessly integrate into your dashboards. 

## Quick Overview

When you create microcontroller projects, you are faced with a lot of repetitive tasks while programming firmware for it:

* **Libraries:** you need to find, download and integrate the necessary libraries that support the devices and components you use.
* **Displays:** when outputting information locally, you need to write code to drive a display
* **Management:** in order to really use your device, you need to add management capabilities, i.e. a web interface, or some sort of web service.
* **Wireless:** In order to receive data from your microcontroller, you need to set up a wireless network and implement ways to provide your wifi **SSID*.
* **OTA Updates:** since devices are often mounted in inaccessible locations, you need to provision the microcontroller to receive *over-the-air* updates
* **Security:** to make sure that only you can re-flash the microcontroller, receive its data, and protect WiFi passwords, you need to carefully implement security features and manage secret keys.
* **Build Environment:** once you finally have written the firmware code, you need a tool chain to *compile* the code and *upload* the binary firmware file to your microcontroller.

Since these tasks are *repetitive* and occur with basically *any* new project, *ESPHome* takes care of this and enables you to focus just on the genuine new features you are trying to implement. All you need to do is *tell ESPHome* (via a *YAML* file) which components your project uses, and what the *GPIOs* are that you used to connect them. Based on this, *ESPHome* automatically includes all necessary libraries, writes the firmware code, compiles it, and uploads it to your microcontroller.

This simplifies the above mentioned *repetitive tasks* tremendously:

* **Libraries:** *ESPHome* supports almost all standard components (i.e. sensors, displays, etc) and *knows* the libraries required to drive them. It takes care of all provisioning.
* **Displays:** For displays, above applies: *ESPHome* knows almost all commonly used displays and automatically integrates them.
* **Management:** the *ESPHome* firmware automatically implements a basic web interface and web services. The device can be managed with the *ESP tools*. *ESPHome-enabled microcontrollers* are automatically discovered by *Home Assistant*, and their data can be conveniently managed via its dashboards.
* **Wireless:** *ESPHome* automatically integrates the microcontroller into your *WiFi* network and lets you select the available *WiFi* networks.
* **OTA Updates:** the *ESPHome* firmware supports *OTA* out of the box: once a microcontroller is *ESPHome-enabled*, it can be updated with just a click via the dashboard.
* **Security:** all secret management (i.e. safely storing *WiFi* passwords) is done by *ESPHome* (and seamlessly integrates with *Home Assistant* if desired). Access to the microcontroller is protected by secret API keys that are, too, transparently managed by *ESPHome*.
* **Build Environment:** since you do not need to write code, no additional tools are required. You change firmware simply by changing the properties of the *YAML* file that describes your microcontroller setup. *ESPHome* automatically derives the firmware from it and provides multiple options to upload new firmware safely to your microcontroller.


> [!TIP]
> *ESPHome* is a great way to convert DIY projects into valuable devices used inside home automation. But even if you are not interested in *home automation*, its *programming-free* concept is appealing to pure electronic hobbyists as well.


## Combining With Home Assistant

While you can operate *ESPHome* stand-alone, combining it with *Home Assistant* leverages huge synergies: your microcontrollers become continuously *monitored*, and they can *interact* with any other device:

* **ESPHome Stand-Alone:** you want to use *ESPHome* to *program your microcontrollers*
* **ESPHome as a Home Assistant Add-On:** in addition, you want your microcontrollers to be constantly *monitored*. Your device becomes fully manageable, and you can use its *entities* to show graphs on a dashboard or control device features via user controls. Your device can now also be part of *automation rules*, i.e. can be turned on or off under certain conditions, or can control other devices (or sending notifications) based on its own state. 

In a nutshell, while running *ESPHome* stand-alone is possible, it is strongly recommended to run it inside *Home Assistant*. Setting up *Home Assistant* is [really easy](https://done.land/components/microcontroller/families/raspberry/raspberrypi).

### Entity Management

Once an *ESPHome* device has been discovered by *Home Assistant*, its sensors, switches, and other components appear as entities in *Home Assistant*, just like with any other commercial or non-commercial device. These entities can be used in automations, scripts, and dashboards just like any other *Home Assistant* entity.

The entities can now also be integrated into *Home Assistant's* automation engine: create complex automations that involve *ESPHome* devices and all the other smart home devices managed by *Home Assistant*.

For example, if you hooked up a *rain sensor* to your microcontroller, *Home Assistant* could then use its output data to control the garden irrigation (and skip an irrigation cycle if it has rained a lot lately). Since *Home Assistant* automatically *collects* device data in configurable intervals, you would also now be able to view the rain fall statistics of the past days, weeks, or months.



## Installation

*ESPHome* can either be installed *stand-alone* (if you just want to use it to create *firmware*), or it can be added as a *plug-in* to *Home Assistant* (if you want to continuously operate and monitor your devices).


### Home Assistant

If you are running [Home Assistant](https://done.land/components/microcontroller/families/raspberry/raspberrypi), the installation of *ESPHome* is easiest: simply [click here](https://my.home-assistant.io/redirect/supervisor_addon/?addon=5c53de3b_esphome&repository_url=https%3A%2F%2Fgithub.com%2Fesphome%2Fhome-assistant-addon).


<img src="images/install_esphome_addon.png" width="100%" height="100%" />

This opens a web-based assistant that connects to your instance of *Home Assistant* and installs the *ESPHome add-on* once you click *INSTALL*:


Once installation completed,  access the *ESPHome GUI* via the *Home Assistant* sidebar: click *ESPHome*. This opens the *GUI* where you can start adding new *ESPHome* devices.


<img src="images/config_esphome_addon.png" width="100%" height="100%" />


### Stand-Alone

*ESPHome* is written in *Python* and runs on any operating system supporting this language. 

These are the installation steps on a *Windows* computer:

1. [Install Python](https://www.python.org/downloads/windows/). Scroll down to the *download links*, and download the appropriate installation file, then run it. Install *Python* with the default options.
2. Press `WIN`+`R` to open the *Run* dialog. Enter `cmd` and press `ENTER` to open a classic console window.
3. In the console window, enter `pip install esphome` and press `ENTER`. 


<img src="images/console01.png" width="100%" height="100%" />

4. Next, in the console window create a new folder for your *ESPHome* projects and set the current path to this folder (adjust the paths in the next three commands accordingly): enter `mkdir d:\esphome_projects`, then enter `d:`, then enter `cd d:\esphome_prpjects`.

This installs the basic (console command driven) version of *ESPHome*. For a more user-friendly *GUI-driven* experience, install the *ESPHome* dashboard:

1. In the console, enter this command: `pip install tornado esphome`. This installs the necessary files (if required).
2. Launch the dashboard with this command (make sure you enter the path to your projects folder that you just created): `esphome dashboard d:\esphome_projects`.
3. A *Windows Security Alert* dialog opens and asks for firewall permissions. This occurs automatically when a process opens a *web socket*. Since *ESPHome* is only using the local network, the dialog should be dismissed ny clicking *Cancel*. Do not change your firewall permissions.
4. *ESPHome* is now running its own webserver for as long as the console window remains open. Open the *ESPHome dashboard* by opening a browser and entering the url `http://localhost:6052`.


<img src="images/consolegui.png" width="100%" height="100%" />



> Tags: EspHome, Home Assistant, ESP8266, ESP32

[Visit Page on Website](https://done.land/tools/software/esphome?105913061917245543) - created 2024-06-16 - last edited 2024-06-16
