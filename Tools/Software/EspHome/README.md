<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# ESPHome

> Free Open-Source Framework To Control And Manage ESP Microcontrollers (And Others, Too)

[ESPHome](https://esphome.io/) is a free *open-source* software that seamlessly integrates into *Home Assistant*, but can also be installed *stand-alone* on various operating systems.

It automatically creates *firmware* for *ESP* microcontrollers based on *configurations* rather than writing *c++* code yourself. 

Via a *configuration* file, you *describe* the hardware of your microcontroller project, i.e. which *GPIOs* you use and what kind of *sensors* or *displays* you connected to them. *ESPHome* then takes care of the programming and automatically creates the firmware for your microcontroller.

> [!NOTE]
> *ESPHome* is no longer limited to *ESP* microcontrollers. You can also use *Raspberry RP2040* and via the integrated [LibreTiny](https://esphome.io/components/libretiny.html)*Beken BK72xx* and *Realtec RTL87xx* often found in commercial "smart" devices such as *Plugs* and *Sensors*.




## Why ESPHome?

*ESPHome* is a completely new way of *programming microcontrollers*: it lets you focus on your hardware design and takes care of the *programming tasks*.

### Repetitive Tasks

With traditional microcontroller projects, you are faced with numerous *repetitive tasks* that take the bulk of your time:

* **Libraries:** find, download and integrate libraries that support the devices and components you want to use.
* **Displays:** writing extra code to drive a display, or manage some other kind of *user interface* or web interfaces.
* **Connectivity:** For *remote management capabilities*, you need to set up a wireless network and implement ways to provide access parameters such as your wifi *SSID* and password. If you want your devices to interact with frameworks like *Home Assistant*, you'd have to add the appropriate API calls.   
* **OTA Updates:** provision the microcontroller to enable *over-the-air* updates so you can maintain your firmware *wirelessly* (often microcontrollers are mounted in inaccessible locations).
* **Security:** carefully implement security measures and manage secret keys.
* **Build Environment:** operate a tool chain to *compile* your code and *upload* the binary firmware file to the microcontroller.

These tasks take up valuable time that you'd probably much rather like to focus on the *creative and fun* part of your projects: designing special functionality of your device.


### Benefits For Free

*ESPHome* handles all *repetitive tasks* automatically for you:

* **Libraries:** *ESPHome* supports almost all standard components (i.e. sensors, displays, etc) and *knows* the libraries required to drive them. It takes care of all provisioning.
* **Displays:** it knows almost all commonly used displays and automatically integrates support for them. *ESPHome firmware* automatically implements a basic web interface and web services. The device can be managed with the *ESPHome Web Tools*, and they are automatically discovered by *Home Assistant*. 
* **Connectivity:** automatically connects the microcontroller to a *WiFi* network and integrates your devices automatically with *Home Assistant*.   
* **OTA Updates:** automatic support for *OTA*: once a microcontroller runs *ESPHome firmware*, it can be updated *wirelessly*.
* **Security:** secrets management (i.e. safely storing *WiFi* passwords) is taken care of by *ESPHome* (and seamlessly integrates with *Home Assistant*). Access to the microcontroller is protected by secret API keys that are transparently managed.
* **Build Environment:** no extra tools or editors are required. You update firmware simply by changing the *configuration file* that describes your hardware. *ESPHome* automatically derives the firmware from it and uploads it to your microcontroller.




## Home Assistant

While you *can* run *ESPHome* stand-alone, it is best used in combination with *Home Assistant*. Their features complement each other seamlessly.

*Home Assistant* is another free open-source framework designed to manage any type of wireless device in one central place.


> [!TIP]
> If you *do not yet* run *Home Assistant*, consider [setting up](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/setup) your own *Home Assistant server* now - it's really simple and well worth the investment.    

### Why Home Assistant?

By using the *ESPHome Add-On* inside *Home Assistant* (rather than installing *ESPHome* stand-alone), you are combining the strengths of both:

*ESPHome* can automatically...

* **...create firmware:** based on your *configurations* (hardware descriptions), all programming is taken care of.
* **...maintain firmware:** at any time you can change or expand your *configurations* and push the new firmware to your microcontroller via *OTA* (*over-the-air*) updates.
* **...integrate with Home Assistant:** your *ESPHome devices* are automatically detectable by *Home Assistant* and expose their capabilities and features in a way that *Home Assistant* can understand and manage.

*Home Assistant* can automatically...

* **...monitor:** It monitors your devices and queries data and sensor readings in defined intervals. Monitoring can include battery and online status. All data is kept in a database for easy reference.
* **...display information:** ...provide appealing graphical *dashboards* with switches, gauges, graphs, and more, to *visualize* the data retrieved from your devices. These dashboards are available in any browser, and there are even free apps for smartphones. When configured, dashboards can be available from the public internet so you can easily monitor and control all of your devices from anywhere in the world.
* **...perform tasks:** It can trigger *automation scripts* based on defined *conditions*. For example, when a *temperature sensor* registers a high temperature, an automation script could automatically turn on the *air conditioning*. Likewise, when a *camera* detects movement, you could get a notification or start a recording.   


In a nutshell, with *Home Assistant*, devices no longer act isolated and no longer need to implement complete *stand-alone* solutions. 

Devices can now focus on *very specific features* (i.e. measuring air quality, detecting a button press) that by itself would make no sense.

With *Home Assistant*, you can access the features of all of your devices and create dashboards and automation scripts. 

For example, a device that controls *air quality* (but has no display or other user interface) could display its readings on a *Home Assistant* dashboard, along with other readings from other devices. Likewise, the readings from that sensor could be used to trigger an *automation script* that turns on *air conditioning* when a temperature threshold is exceeded.

> [!TIP]
> If you got interested, take a look [how easy it is to set up *Home Assistant* running on a low-energy Raspberry Pi 5](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/setup).


<details><summary>Device Features = Entities</summary><br/>
In order for *Home Assistant* to work with all kinds of different devices (including but not limited to *ESPHome devices*), it *abstracts* device capabilities: each device *capability* surfaces as a so-called *entity*.

#### Entities = Device Capabilities


These entities can then be accessed *manually* or *automatically*:

* **Manually:** You can add as many *Dashboards* to *Home Assistant* as you need. *Dashboards* enable you to *manually* interact with devices. Each *dashboard* is composed of graphical *user controls* that are tied to one or more *entities*. For example, the entity representing a *temperature sensor* can be tied to a *gauge* or a *graph*. Likewise, an entity representing a *button* or *switch* can be tied to a *GPIO* that may control a relais.
* **Automatically:** Entities can also be accessed from within *automation scripts*. *Home Assistant* runs these scripts when the defined *conditions* are met. For example, when you tie the entity representing a *temperature sensor* to an automation script, you could define a condition to be a "temperature reading greater than 25 degree celsius", and when the condition is met, the script automatically targets another entity in a completely different device, i.e. an entity representing an *electric plug* that turns on the *air conditioning*.



</details>





## Installing ESPHome

The recommended installation method is to use the *ESPHome Add-On* inside *Home Assistant*. If you have a running instance of *Home Assistant*, installing *ESPHome* is a matter of *one click*:

[<img src="images/add_ha.svg" width="40%" height="40%">](https://my.home-assistant.io/redirect/supervisor_addon/?addon=5c53de3b_esphome&repository_url=https%3A%2F%2Fgithub.com%2Fesphome%2Fhome-assistant-addon)




This connects you to your local *Home Assistant* instance and opens an assistant that walks you through the installation once you click *INSTALL*.


### Understanding Add-On And Integration

*ESPHome* has two parts:

* **Add-On:** *ESP Dashboard* and tools to *author ESPHome devices*
* **Integration:** Allows *Home Assistant* to auto-discover and integrate *ESPHome devices*. The integration is part of *Home Assistant*.

Once you installed the *Add-On*, you can choose whether you want *Home Assistant* to start the *add-on* automatically on boot, whether you want to restart it per watchdog in case it crashes, and whether the *add-on* should be accessible via the *Home Assistant* sidebar (its main menu on the left side of the screen).

> [!TIP]
> Since you need the *add-on* only when you author *ESPHome* devices, it's not required to automatically launch it on boot. To be able to easily access and launch it on demand, you should opt-in to add the *add-on* to the *sidebar*.


<img src="images/config_esphome_addon.png" width="100%" height="100%" />


### Install Stand-Alone

You decide *where* you want to *author ESPHome devices*. The recommended way is to use the *ESPHome Add-On* inside *Home Assistant*, but you can also install *ESPHome* stand-alone on a different computer.

> [!TIP]
> Using the *ESPHome Add-On* inside *Home Assistant* is much easier to set up, especially for beginners. It basically takes just one click. Setting up *ESPHome* separately and stand-alone requires a lot more steps.


Installation is a three-step process: 

* **Prerequisites:** ensure that your operating system supports *Python*, and install *Python* if it is missing.   
* **ESPHome Command Line Interface:** download and install the actual *ESPHome* Python software.   
* **ESPHome Dashboard (GUI):** add the *ESPHome dashboard* on top of the command line interface. This step is optional.   


#### Installing ESPHome On Windows
Here are the installation steps on a *Windows* computer:

1. [Install Python](https://www.python.org/downloads/windows/). Scroll down to the *download links*, and download the appropriate installation file, then run it. Install *Python* with the default options.
2. Press `WIN`+`R` to open the *Run* dialog. Enter `cmd` and press `ENTER` to open a classic console window.
3. In the console window, enter `pip install esphome` and press `ENTER`. 


<img src="images/console01.png" width="100%" height="100%" />

4. Next, in the console window create a new folder for your *ESPHome* projects and set the current path to this folder (adjust the paths in the next three commands accordingly): enter `mkdir d:\esphome_projects`, then enter `d:`, then enter `cd d:\esphome_prpjects`.

Up to this point, you have installed the core *ESPHome engine* which is accessible only through a console, and controlled exclusively with cryptic console commands.

To get the same easy-to-use graphical *ESPHome Dashboard* that the *ESPHome Add-On* in *Home Assistant* provides, you need to install a separate component.




<details><summary>Installing ESPHome Dashboard</summary><br/>

This is only required when installing *ESPHome stand-alone*. The *ESPHome Add-On* in *Home Assistant* includes the *ESPHome Dashboard* by default.

1. In the console, enter this command: `pip install tornado esphome`. This installs the necessary files (if required).
2. Launch the dashboard with this command (make sure you replace the path to your projects folder with the path that you used when you installed *ESPHome*): `esphome dashboard d:\esphome_projects`.
3. A *Windows Security Alert* dialog opens and asks for firewall permissions. This occurs automatically when a process opens a *web socket*. Since *ESPHome* is only using the local network, the dialog should be dismissed by clicking *Cancel*. **Do not change your firewall permissions.**
4. *ESPHome* is now running its own webserver for as long as the console window remains open. Visit the *ESPHome dashboard* by opening a browser and entering the url `http://localhost:6052`.


<img src="images/consolegui.png" width="100%" height="100%" />

</details>



> Tags: EspHome, Dashboard, Home Assistant, Entity

[Visit Page on Website](https://done.land/tools/software/esphome?105913061917245543) - created 2024-06-16 - last edited 2024-07-02
