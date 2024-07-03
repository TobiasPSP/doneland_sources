<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# ESPHome

> Free Open-Source Framework To Control And Manage ESP Microcontrollers (And Others, Too)

[ESPHome](https://esphome.io/) is a free *open-source* software that seamlessly integrates into *Home Assistant*, but can also be installed *stand-alone* on various operating systems.

It automatically creates the *firmware* for *ESP* microcontrollers without writing any code. Via a *YAML* file, you *describe* the features of your microcontroller project, i.e. which *GPIOs* you use and what kind of *sensors* or *displays* you connected. *ESPHome* then takes care of the heavy lifting and automatically creates the firmware necessary to operate the microcontroller.

> [!NOTE]
> *ESPHome* is no longer limited to *ESP* microcontrollers. Recent versions integrate [LibreTiny](https://esphome.io/components/libretiny.html), an open-source platform that supports *BK72xx* and *RTL87xx* microcontrollers often found in "smart" devices such as *Plugs* and *Sensors*.




*ESPHome* can run *stand-alone* or as part of *Home Assistant*. The latter is strongly recommended because then your *ESPHome devices* that you created can be discovered in *Home Assistant* just like any other (commercial) device, and seamlessly integrate into dashboards (self-defined user interfaces) and automation workflows. 

## Quick Overview

Let's first identify the benefits of *ESPHome*, and why *you* may want to use it.

### Repetitive Tasks

Whenever you create microcontroller projects, you are faced with always the same *repetitive tasks* while programming firmware for it:

* **Libraries:** You need to find, download and integrate libraries that support the devices and components you want to use.
* **Displays:** When outputting information, you need to write extra code to drive a display, or manage some other kind of *user interface* or web interfaces.
* **Connectivity:** For *remote management capabilities*, you need to set up a wireless network and implement ways to provide access parameters such as your wifi *SSID* and password.
* **OTA Updates:** Since devices are often mounted in inaccessible locations, you need to provision the microcontroller in a way that enables *over-the-air* updates so you can maintain your firmware.
* **Security:** To make sure that *only you* can access the microcontroller, you need to carefully implement security measures and manage secret keys.
* **Build Environment:** Once you have written the firmware code, you need a tool chain to *compile* the code and *upload* the binary firmware file to your microcontroller.

These are a lot of tasks that take up valuable time that you'd probably much rather would like to focus on the *creative and fun* part of your projects: designing the special functionality of your device.

### Free Yourself From Boring Tasks
Since above tasks are *repetitive* and required for basically *any* new project, the default *ESPHome firmware* takes care of them and enables you to focus on the genuine new features you are trying to implement. 


All you need to do is *tell ESPHome* what your hardware looks like: what are the components you hooked up to your microcontroller, and which *GPIOs* did you connect them to.

Based on this description, *ESPHome* takes care of all the rest, identifies and integrates the necessary libraries, programs the firmware, compiles it and uploads it to your microcontroller. You don't need to program a single line of code.

> [!TIP]
> *ESPHome* is extremely flexible: simple devices can be set up with almost no prior knowledge. Even complex devices are absolutely doable but require more advanced *ESPHome features*. So working professionally with *ESPHome* does have a learning curve, just like any other programming environment.   






### Benefits For Free

All of the above mentioned *repetitive tasks* are handled *automatically* by the *ESPHome firmware*, so you don't have to worry about them anymore:

* **Libraries:** *ESPHome* supports almost all standard components (i.e. sensors, displays, etc) and *knows* the libraries required to drive them. It takes care of all provisioning.
* **Displays:** For displays, the same applies: *ESPHome* knows almost all commonly used displays and automatically integrates them if you want. *ESPHome firmware* automatically implements a basic web interface and web services. The device can be managed with the *ESP tools*, and they are automatically discovered by *Home Assistant*. 
* **Connectivity:** *ESPHome* automatically connects your microcontroller to your *WiFi* network.
* **OTA Updates:** the *ESPHome* firmware supports *OTA* out of the box: once a microcontroller is *ESPHome-enabled*, it can be updated with just a click over the air.
* **Security:** all secrets management (i.e. safely storing *WiFi* passwords) is taken care of by *ESPHome* (and seamlessly integrates with *Home Assistant* if desired). Access to the microcontroller is protected by secret API keys that are, too, transparently managed by *ESPHome*.
* **Build Environment:** since you do not need to write code, no additional tools are required. You update firmware simply by changing the properties of the *device configuration* file that describes your microcontroller hardware. *ESPHome* automatically derives the firmware from it and provides multiple options to upload firmware safely to your microcontroller.


> [!TIP]
> *ESPHome* is a great way to convert DIY projects into valuable devices used inside home automation. Even if you are not interested in *home automation* at all, its *programming-free* concept might be appealing to pure electronic hobbyists as well and is definitely worth a look.





## Home Assistant

While you can run *ESPHome* stand-alone, typically *ESPHome* is used in conjunction with *Home Assistant*. *Home Assistant* is another free open-source framework designed to manage all kinds of wireless devices in one place. 


* [ESPHome Stand-Alone:](https://esphome.io/guides/installing_esphome) the *Python*-based *ESPHome* software that can be installed and run on any computer that supports *Python*. *Python* can be [installed](https://www.python.org/downloads/) on most operating systems including *Windows*, *Linux*, *macOS*, and many more.
* [ESPHome as a Home Assistant Add-On:](https://esphome.io/guides/getting_started_hassio) Once you installed *Home Assistant*, it takes just a [click](https://my.home-assistant.io/redirect/supervisor_addon/?addon=5c53de3b_esphome&repository_url=https%3A%2F%2Fgithub.com%2Fesphome%2Fhome-assistant-addon) to install the *ESPHome Add-On* inside of *Home Assistant*.

[<img src="images/add_ha.svg" width="30%" height="30%">](https://my.home-assistant.io/redirect/supervisor_addon/?addon=5c53de3b_esphome&repository_url=https%3A%2F%2Fgithub.com%2Fesphome%2Fhome-assistant-addon)

By using the *ESPHome Add-On* inside *Home Assistant*, you are combining *ESPHome features* with *Home Assistant features* and get even more very useful features for free:

*Home Assistant* can automatically...

* **Monitor:** It monitors your devices and queries data and sensor readings in defined intervals. Monitoring can include battery and online status. All data is kept in a database for easy lookup.
* **Show Information:** ...provide graphical *dashboards* with switches, gauges, graphs, and more, to *visualize* the data retrieved from your devices.
* **Perform Tasks:** It can trigger *automation scripts* based on self-defined *conditions*. For example, when a *temperature sensor* registers a high temperature, an automation script could automatically turn on the *air conditioning*.    
Devices no longer have to implement complete *stand-alone* solutions. They can now focus on a specific feature (i.e. measuring something), and *in combination* with other devices, *Home Assistant* implements the final solution.

Because of all of these benefits, it is strongly recommended to run *ESPHome* as part of *Home Assistant*. Setting up *Home Assistant* is [really easy](https://done.land/components/microcontroller/families/raspberry/raspberrypi).

> [!TIP:]
> Running *ESPHome* **stand-alone** makes sense if you want to use its *programming-free concept* to design devices that are running **stand-alone** as well. I can only urge you to *not* go this route and instead start with *Home Assistant*, then add *ESPHome* to it. If you are new to *Home Assistant*, it is [really simple](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/setup) to set up a *Raspberry Pi 5* with pre-installed *Home Assistant* and takes less than 10 minutes.   





### Understanding Entities
When you run *ESPHome* as part of *Home Assistant* and create a new *ESPHome device*, it is automatically discovered by *Home Assistant* once it goes online. 

From the perspective of *Home Assistant*, your *ESPHome devices* are treated just like any other remotely accessible device. In order for *Home Assistant* to work with all kinds of devices, it *abstracts* device capabilities: each device *capability* surfaces as a so-called *entity*.

#### Entities = Device Capabilities

To get a better feeling just how your *ESPHome microcontroller project* can interact with other devices in *Home Assistant*, it's useful to know how *Home Assistant* deals with the huge variety of *wireless devices* from *many different vendors* in a uniform way.

Whatever the capabilities of your *ESPHome device* may be (sensors, switches, lights, etc.), they all surface as *entities* in *Home Assistant*. This is true for *any* device discovered by *Home Assistant*: *Entities* (and their unique *Ids*) are used to address specific features of *any* device.

These entities can then be accessed *manually* or *automatically*:

* **Manually:** You can easily add as many *Dashboards* to *Home Assistant* as you may need. *Dashboards* enable you to *manually* interact with devices. Each *dashboard* is composed of graphical *user controls* that are tied to one or more *entities*. For example, the entity representing a *temperature sensor* can be tied to a *gauge* or a *graph*. Likewise, an entity representing a *button* or *switch* can be tied to a *GPIO* that may control a relais.
* **Automatically:** Entities can also be accessed from within *automation scripts*. *Home Assistant* runs these scripts when the defined *conditions* are met. For example, when you tie the entity representing a *temperature sensor* to an automation script, you could define a condition to be a "temperature reading greater than 25 degree celsius", and when the condition is met, the script automatically targets another entity representing an *electric plug* that turns on the *air conditioning*.







## Installation

*ESPHome* can either be installed *stand-alone* (if you just want to use it to create *firmware* for *stand-alone* devices), or it can be added as a *plug-in* to *Home Assistant* (if you want to continuously operate and monitor your devices and enable them to interact with each other).


### Home Assistant

If you have a running instance of *Home Assistant*, installing *ESPHome* on it is a matter of a simple click:

[<img src="images/add_ha.svg" width="30%" height="30%">](https://my.home-assistant.io/redirect/supervisor_addon/?addon=5c53de3b_esphome&repository_url=https%3A%2F%2Fgithub.com%2Fesphome%2Fhome-assistant-addon)

> [!TIP:]
> If you *do not yet* run *Home Assistant*, consider [setting up](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/setup) your own *Home Assistant server* - it's really simple and well worth the investment.    


<img src="images/install_esphome_addon.png" width="100%" height="100%" />

This opens a web-based assistant that connects to your instance of *Home Assistant* and installs the *ESPHome add-on* once you click *INSTALL*:


Once installation completed,  access the *ESPHome GUI* via the *Home Assistant* sidebar: click *ESPHome*. This opens the *GUI* where you can start adding new *ESPHome* devices.


<img src="images/config_esphome_addon.png" width="100%" height="100%" />


### Stand-Alone

*ESPHome* is written in *Python* and runs on any operating system that is supporting this language. 

These are the installation steps on a *Windows* computer:

1. [Install Python](https://www.python.org/downloads/windows/). Scroll down to the *download links*, and download the appropriate installation file, then run it. Install *Python* with the default options.
2. Press `WIN`+`R` to open the *Run* dialog. Enter `cmd` and press `ENTER` to open a classic console window.
3. In the console window, enter `pip install esphome` and press `ENTER`. 


<img src="images/console01.png" width="100%" height="100%" />

4. Next, in the console window create a new folder for your *ESPHome* projects and set the current path to this folder (adjust the paths in the next three commands accordingly): enter `mkdir d:\esphome_projects`, then enter `d:`, then enter `cd d:\esphome_prpjects`.

This installs the basic (console command driven) version of *ESPHome*. For a more user-friendly *GUI-driven* experience, install the *ESPHome* dashboard.

<details><summary>Installing ESPHome Dashboard</summary><br/>

These steps are necessary only for *stand-alone* installations. When *ESPHome* runs as part of *Home Assistant*, it always has a dashboard.

1. In the console, enter this command: `pip install tornado esphome`. This installs the necessary files (if required).
2. Launch the dashboard with this command (make sure you enter the path to your projects folder that you just created): `esphome dashboard d:\esphome_projects`.
3. A *Windows Security Alert* dialog opens and asks for firewall permissions. This occurs automatically when a process opens a *web socket*. Since *ESPHome* is only using the local network, the dialog should be dismissed ny clicking *Cancel*. Do not change your firewall permissions.
4. *ESPHome* is now running its own webserver for as long as the console window remains open. Open the *ESPHome dashboard* by opening a browser and entering the url `http://localhost:6052`.


<img src="images/consolegui.png" width="100%" height="100%" />

</details>



> Tags: EspHome, Home Assistant, Entity

[Visit Page on Website](https://done.land/tools/software/esphome?105913061917245543) - created 2024-06-16 - last edited 2024-07-02
