<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# ESPHome

> Free Open-Source Framework To Control And Manage ESP Microcontrollers (And Others, Too)

[ESPHome](https://esphome.io/) is a free *open-source* software that seamlessly integrates into *Home Assistant*, but can also be installed *stand-alone* on various operating systems. It automatically creates *firmware* for *ESP* microcontrollers based on *configurations* so you don't need to write *c++* code yourself or need programming skills at all. 

Via a *configuration* file, you instead *describe* the hardware that your microcontroller project is using, i.e. which *microcontroller type* you are using, and which *GPIOs* are connected to which kind of *sensors* or *displays*. 

*ESPHome* then programs the required firmware for you and uploads it to your microcontroller.


## Why Using ESPHome?

*ESPHome* is a completely different approach for creating microcontroller-based DIY projects. It shields you as much as possible from repetitive technical and programming tasks, and lets you focus entirely on the genuine functionality you are trying to build:

* **No Programming:** create microcontroller-based projects without complex programming: just *describe your hardware setup* in simple terms.
* **Simple:** new firmware is *wirelessly* transferred to your microcontroller (*OTA*): no need for *USB cables*, awkward button presses to get in *firmware upload mode*, or external tools to do the firmware upload.
* **Fast:** all *repetitive tasks* are taken care of, so you can focus fully on your genuine project idea. 
* **Extensible:** *ESPHome devices* automatically support *Home Assistant* and can be added to a central dashboard to become fully manageable and part of larger automation tasks.

<details><summary>How ESPHome takes care of time-consuming repetitive tasks</summary><br/>

With traditional microcontroller projects, you are faced with numerous *repetitive tasks* that take the bulk of your time:

* **Libraries:** find, download and integrate libraries that support the devices and components you want to use.
* **Displays:** writing extra code to drive a display, or manage some other kind of *user interface* or web interfaces.
* **Connectivity:** For *remote management capabilities*, you need to set up a wireless network and implement ways to provide access parameters such as your wifi *SSID* and password. If you want your devices to interact with frameworks like *Home Assistant*, you'd have to add the appropriate API calls.   
* **OTA Updates:** provision the microcontroller to enable *over-the-air* updates so you can maintain your firmware *wirelessly* (often microcontrollers are mounted in inaccessible locations).
* **Security:** carefully implement security measures and manage secret keys.
* **Build Environment:** operate a tool chain to *compile* your code and *upload* the binary firmware file to the microcontroller.

These tasks take up valuable time that you'd probably much rather like to focus on the *creative and fun* part of your projects: designing special functionality of your device.

*ESPHome* handles all *repetitive tasks* automatically for you:

* **Libraries:** *ESPHome* supports almost all standard components (i.e. sensors, displays, etc) and *knows* the libraries required to drive them. It takes care of all provisioning.
* **Displays:** it knows almost all commonly used displays and automatically integrates support for them. *ESPHome firmware* automatically implements a basic web interface and web services. The device can be managed with the *ESPHome Web Tools*, and they are automatically discovered by *Home Assistant*. 
* **Connectivity:** automatically connects the microcontroller to a *WiFi* network and integrates your devices automatically with *Home Assistant*.   
* **OTA Updates:** automatic support for *OTA*: once a microcontroller runs *ESPHome firmware*, it can be updated *wirelessly*.
* **Security:** secrets management (i.e. safely storing *WiFi* passwords) is taken care of by *ESPHome* (and seamlessly integrates with *Home Assistant*). Access to the microcontroller is protected by secret API keys that are transparently managed.
* **Build Environment:** no extra tools or editors are required. You update firmware simply by changing the *configuration file* that describes your hardware. *ESPHome* automatically derives the firmware from it and uploads it to your microcontroller.


</details>


### Home Assistant Integration

[Home Assistant](https://done.land/tools/software/homeassistant) is another free open-source software designed to centrally manage all of your devices. *ESPHome devices* automagically support *Home Assistant* and are auto-discovered by it.

While using *Home Assistant* is not required, both *ESPHome* and *Home Assistant* compliment each other in an almost perfect way. Since you get *Home Assistant* compatibility for free once you start building *ESPHome devices*, you can add *Home Assistant* at any time to your environment.

You might want to decide **how** to install *ESPHome* right at the beginning of your journey, though: changing it later might add a lot of extra work. These are your installation options:

* **ESPHome Add-On:** *Home Assistant* includes an *ESPHome addon*, and it takes merely a single click to set up *ESPHome* inside *Home Assistant*. It is by far the easiest way of setting up *ESPHome* but it requires that you set up *Home Assistant* first.
* **ESPHome Stand-Alone:** Without *Home Assistant*, you install *ESPHome* stand-alone. This is no rocket science either but does require quite a few steps.

The important part is that any *ESPHome device* is bound to the *ESPHome instance* that created it. So if you start with a *stand-alone ESPHome* installation and only later switch to the *ESPHome Add-On inside Home Assistant*, you have to migrate all of your existing *ESPHome devices* to the new *ESPHome instance*.


> [!NOTE]
> You can *always* add *ESPHome devices* to any *Home Assistant* instance at any time, regardless of which *ESPHome instance* created it. *ESPHome devices* can only be *edited and changed* by the *ESPHome* instance that created it.


So it is best to install *ESPHome* the way that you are most likely going to use it *long-term*. If you do not yet run *Home Assistant* and are unsure whether that could be an option for you, [setting up](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/setup) your own *Home Assistant server* on *Raspberry Pi 5* is a matter of just 10 minutes. A *Raspberry Pi 5 server* is a highly useful addition to your lab, so maybe now is the best time to set one up.

<details><summary>Understanding Relationship Between ESPHome And Home Assistant</summary><br/>

*ESPHome* and *Home Assistant* are both free open-source software. They are completely separate and made by separate parties. However, their strengths and features complement each other perfectly.

* **ESPHome:** creates firmware for microcontroller-based projects and uploads it *wirelessly* at any time
* **Home Assistant:** manages devices centrally, including (but not limited to) *ESPHome devices*

To understand how both of them integrate, consider this:

* **ESPHome Integration:** *Integrations* are part of *Home Assistant* and make specidfic families of devices discoverable and accessible to *Home Assistant*. The *ESPHome integration* lets *Home Assistant* discover any *ESPHome device*, regardless of which *ESPHome* instance has created the device. There are many other *integrations* available, i.e. for *Blink* surveillance cameras, or for *Tuya smart home devices*.
* **ESPHome Add-On:** *Add-Ons* are third-party software packages in a format that can be installed by *Home Assistant*. The *ESPHome Add-On* is authored by *ESPHome* and made available via the *Home Assistant Add-On Store*

To understand how *ESPHome devices* are *bound* to a specific *ESPHome instance*, consider this:

* **Security:** *ESPHome firmware* contains industry-strength security mechanisms including *encryption* and *secret keys* to make sure that sensitive secrets (like your *WiFi password*) are safely stored on a device, and that no unauthorized source can read or change the firmware.
* **Configuration:** The *ESPHome instance* that creates a particular *ESPHome* device maintains a *configuration file* for it that you use to describe the device hardware and store sensitive API keys and secrets. 

So in order for *ESPHome* to access and update a particular *ESPHome device*, it needs to have access to its *configuration file* with the secret access keys. That's why you cannot change or edit an *ESPHome device* from a *ESPHome instance* other than the one that initially created it.

If you do need to change your *ESPHome instance*, you would need to migrate the *configuration files* and all secrets saved in the *ESPHome secret store* to the new *ESPHome instance*.

Such a migration is no rocket science but does involve time and effort which is why you should carefully consider in the first place how to set up your *ESPHome installation* - so you don't need to change it in the foreseeable future.

</details>

<details><summary>Why should I take the effort and set up Home Assistant first?</summary><br/>

The reason why you can't simply *postpone* the decision whether or not you want to use *Home Assistant* has been clarified above: it affects your *ESPHome installation options*. Only when you have set up *Home Assistant* can you use the *ESPHome Add-On* inside of it.

If you are happy with setting up *ESPHome stand-alone* and feel this is not a *temporary solution*, and you are ok with setting up all of your *ESPHome device* in this stand-alone environment, then you *can* postpone the decision to add *Home Assistant*. 

Again: the only reason why you might want to **first** install *Home Assistant* **before** you move on to using *ESPHome* is that you prefer a one-stop solution with a perfectly integrated *ESPHome Dashboard*.

In any respect, here are the synergies you gain when **combining** *ESPHome* with *Home Assistant*, regardless of which *ESPHome instance* you are ending up using to *author ESPHome devices*:

*ESPHome* can automatically...

* **...create firmware:** based on your *configurations* (hardware descriptions), all programming is taken care of.
* **...maintain firmware:** at any time you can change or expand your *configurations* and push the new firmware to your microcontroller via *OTA* (*over-the-air*) updates.
* **...integrate with Home Assistant:** your *ESPHome devices* are automatically detectable by *Home Assistant* and expose their capabilities and features in a way that *Home Assistant* can understand and manage.

*Home Assistant* can automatically...

* **...monitor:** It monitors your devices and queries data and sensor readings in defined intervals. Monitoring can include battery and online status. All data is kept in a database for easy reference.
* **...display information:** ...provide appealing graphical *dashboards* with switches, gauges, graphs, and more, to *visualize* the data retrieved from your devices. These dashboards are available in any browser, and there are even free apps for smartphones. When configured, dashboards can be available from the public internet so you can easily monitor and control all of your devices from anywhere in the world.
* **...perform tasks:** It can trigger *automation scripts* based on defined *conditions*. For example, when a *temperature sensor* registers a high temperature, an automation script could automatically turn on the *air conditioning*. Likewise, when a *camera* detects movement, you could get a notification or start a recording.   


In a nutshell, with *Home Assistant*, devices no longer act isolated and no longer must implement a *complete feature set* for *stand-alone operation*. 

Devices can now focus on *very specific features* (i.e. measuring air quality, detecting a button press) that by itself might not even make much sense. With *Home Assistant*, you can access such features and create dashboards and automation scripts. 

For example, a device that controls *air quality* (but has no display or other user interface) could display its readings on a *Home Assistant* dashboard, along with other readings from other devices. Likewise, the readings from that sensor could be used to trigger an *automation script* that turns on *air conditioning* when a temperature threshold is exceeded.


</details>

<details><summary>How Devices Are Abstracted in Home Assistant</summary><br/>

*Home Assistant* can manage all kinds of devices from all kinds of sources and does this through its *integrations*:

*Integrations* abstract the specific device features and requirements and present the devices in a *uniform way*. each device *capability* - regardless of how it is technically implemented and accessed - surfaces as a *entity*. [Entities](https://done.land/tools/software/esphome/reviewdeviceentities) are really *device capabilities*.

The *Home Assistant* user accesses **entities** in two ways: *manually* or *automatically*. Any complexity or technical requirement that the particular device requires is taken care of transparently in the background:

* **Manually:** You can add as many [Dashboards](https://done.land/tools/software/esphome/usingdashboards) to *Home Assistant* as you need. *Dashboards* enable you to *manually* interact with devices. Each *dashboard* is composed of graphical *user controls* that are tied to one or more *entities*. For example, the entity representing a *temperature sensor* can be tied to a *gauge* or a *graph*. Likewise, an entity representing a *button* or *switch* can be tied to a *GPIO* that may control a relais.
* **Automatically:** Entities can also be accessed from within [automation scripts](https://done.land/tools/software/esphome/addingautomation). *Home Assistant* runs these scripts when the defined *conditions* are met. For example, when you tie the entity representing a *temperature sensor* to an automation script, you could define a condition to be a "temperature reading greater than 25 degree celsius", and when the condition is met, the script automatically targets another entity in a completely different device, i.e. an entity representing an *electric plug* that turns on the *air conditioning*.



</details>





## Installing ESPHome

If you have a running instance of *Home Assistant*, installing *ESPHome* is a matter of *one click*:

[<img src="images/add_ha.svg" width="40%" height="40%">](https://my.home-assistant.io/redirect/supervisor_addon/?addon=5c53de3b_esphome&repository_url=https%3A%2F%2Fgithub.com%2Fesphome%2Fhome-assistant-addon)




This connects you to your local *Home Assistant* instance and opens an assistant that walks you through the installation once you click *INSTALL*.

Once you installed the *Add-On*, you can choose whether you want *Home Assistant* to start the *add-on* automatically on boot, whether you want to restart it per watchdog in case it crashes, and whether the *add-on* should be accessible via the *Home Assistant* sidebar (its main menu on the left side of the screen).

> [!TIP]
> The *ESPHome Add-on* is required only when you author *ESPHome* devices, not for device discovery or automation. That's why it does not necessarily need to be automatically launched on boot. To be able to easily access and launch it on demand, opt-in to add it to the *Home Assistant Sidebar*.


<img src="images/config_esphome_addon.png" width="100%" height="100%" />


### Installing Stand-Alone ESPHome Instance

Installing a *stand-alone* version of *ESPHome* has its own set of pros and cons compared to the *ESPHome Add-On* in *Home Assistant*.

> [!IMPORTANT]
> Make sure you understand: regardless of *how* you install *ESPHome*: any *ESPHome device* you cvreate can be discovered by *Home Assistant* thanks to its built-in *ESPHome Integration*. You can *edit and change the firmware* of a *ESPHome device* **only in the *ESPHome* instance** that created it, though.

* **Pro:** when you set up *ESPHome* locally on your *PC*, you can easily provision new microcontrollers directly via *USB cable*. When you run it inside *Home Assistant* on another server, you would have to connect the microcontroller to the local USB port of that server. Also, it might count as *pro* for some users that no *Home Assistant* is required.
* **Con:** you need to install a *Python environment* on your computer and awkwardky launch *ESPHome* each time you want to use it. If you would like to use the same convenient graphical user interface that the *ESPHome Add-On* comes with by default, you need to launch a temporary *web server*. All of this works beautifully but is neither beginner-friendly nor convenient.


Installation is a three-step process: 

* **Prerequisites:** ensure that your operating system supports *Python*, and install *Python* if it is missing.   
* **ESPHome Command Line Interface:** download and install the actual *ESPHome* Python software.   
* **ESPHome Dashboard (GUI):** add the *ESPHome dashboard* on top of the command line interface. This step is optional.   




<details><summary>Installing ESPHome On Windows</summary><br/>

Here are the installation steps on a *Windows* computer:

1. [Install Python](https://www.python.org/downloads/windows/). Scroll down to the *download links*, and download the appropriate installation file, then run it. Install *Python* with the default options.
2. Press `WIN`+`R` to open the *Run* dialog. Enter `cmd` and press `ENTER` to open a classic console window.
3. In the console window, enter `pip install esphome` and press `ENTER`. 


<img src="images/console01.png" width="100%" height="100%" />

4. Next, in the console window create a new folder for your *ESPHome* projects and set the current path to this folder (adjust the paths in the next three commands accordingly): enter `mkdir d:\esphome_projects`, then enter `d:`, then enter `cd d:\esphome_prpjects`.

Up to this point, you have installed the core *ESPHome engine* which is accessible only through a console, and controlled exclusively with cryptic console commands.

To get the same easy-to-use graphical *ESPHome Dashboard* that the *ESPHome Add-On* in *Home Assistant* provides, you need to install a separate component. This is only required when installing *ESPHome stand-alone*. The *ESPHome Add-On* in *Home Assistant* includes the *ESPHome Dashboard* by default.

1. In the console, enter this command: `pip install tornado esphome`. This installs the necessary files (if required).
2. Launch the dashboard with this command (make sure you replace the path to your projects folder with the path that you used when you installed *ESPHome*): `esphome dashboard d:\esphome_projects`.
3. A *Windows Security Alert* dialog opens and asks for firewall permissions. This occurs automatically when a process opens a *web socket*. Since *ESPHome* is only using the local network, the dialog should be dismissed by clicking *Cancel*. **Do not change your firewall permissions.**
4. *ESPHome* is now running its own webserver for as long as the console window remains open. Visit the *ESPHome dashboard* by opening a browser and entering the url `http://localhost:6052`.


<img src="images/consolegui.png" width="100%" height="100%" />

</details>



> Tags: EspHome, Dashboard, Home Assistant, Entity

[Visit Page on Website](https://done.land/tools/software/esphome?105913061917245543) - created 2024-06-16 - last edited 2024-07-11
