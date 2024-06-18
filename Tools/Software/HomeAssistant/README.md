<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Home Assistant

> Free & Open-Source Automation Software Providing Dashboards That Can Manage All Of Your Device

[Home Assistant](https://www.home-assistant.io/) is an open-source platform designed for *home automation*, allowing users to control and manage various smart devices from a *single user interface*. 

## Key Features

Key features of this software are:

* **Privacy/No Cloud:** *Home Assistant* runs in your own network and does not depend on external *Cloud Services*.
* **Open Source/Free:** It is free *open-source software* with no strings or recurring cost attached to it.
* **Compatibility:** The software offers support for various *IoT platforms* so you can integrate a wide range of commercial devices and sensors as well as your own *DIY microcontroller projects*.

The software is *Python*-based and runs on any operating system that supports *Python*. One very popular option is to set up a cheap *Raspberry Pi computer* and run *Home Assistant* on it. 

### Universal Dashboard
The *extensibility* makes *Home Assistant* highly interesting for *electronics hobbyists*: 

Self-made microcontroller-based projects can easily be integrated, and *Home Assistant* provides the necessary *graphical interfaces* to manage them:

* **Dashboards:** easy-to-design *dashboards* can group devices and provide graphical representations to show data, and user controls to manage the devices.
* **Automation:** powerful automation rules can be based on specific *triggers* and *conditions* and invoke *actions* - across all devices from all vendors (including self-made hardware).
* **Notifications:** Automation rules can send notifications to a variety of devices.

### User Interface
*Home Assistant* runs its own *webserver* that serves web pages to any device with a browser. In addition, *Home Assistant* offers *smartphone apps* that in turn can forward *smartphone data* to the server, i.e. positional data to determine whether someone is at home or not.

In stark contrast to most *commercial* home automation solutions, *Home Assistant* prioritizes privacy and local control, ensuring that all data and operations remain within the user's home network. There *is* a *Home Assistant Cloud* service that can be optionally used if advcanced and secure *remote control* from anywhere of the world is wanted.

## Supported Platforms
*Home Assistant* is written in *Python*, which makes it compatible with many platforms that support *Python*. However, there are a few important nuances to consider:

1. **System Requirements**: it has specific dependencies and system requirements that need to be met. Some platforms may require additional configuration or might not be officially supported.

2. **Official Support**: Home Assistant has official installation methods for specific platforms, which ensure stability and performance. These include installations via *Docker*, *Home Assistant OS*, and *Home Assistant Supervised* on *Linux*-based systems. Running *Home Assistant* on unsupported platforms could lead to stability issues and lack of support from the community.

3. **Performance Considerations**: Even if a platform supports *Python*, the hardware capabilities and performance characteristics of the platform are crucial. *Home Assistant* manages various automation tasks, real-time data processing, and potentially intensive integrations, which require adequate resources.

4. **Ease of Installation**: The ease of installation and maintenance might vary significantly. Officially supported platforms and methods provide detailed installation instructions, regular updates, and community support, which are beneficial for long-term usage and troubleshooting.

5. **Availability:** *Home Assistant* is targeted towards continuously managing all of your devices, responding to requests and automation tasks any time, and constantly logging and saving information like *sensor data* and *health parameters*. As such, it needs to run continously. Some platforms are better suited for this requirement than others, especially when *energy consumption* is considered.

### Raspberry Pi 5
One of the best platforms to *host Home Assistant* is a *Raspberry Pi 5*: it is cheap, very powerful, fully supported, and has an excellent low energy consumption.

You can get the parts for less than EUR 200, and assembly and setup requires just 10-20 minutes time. No special skills are required.

A [fully illustrated guide](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/parts) walks you through all required steps and covers the required parts, the *Raspberry Setup*, and *installing Home Assistant*.

## Important Prerequisites
*Home Assistant* connects to your various devices typically via *WiFi*. To leverage its potential, you need a stable *WiFi* with good coverage.

For *Home Assistant* to reliably work, it is of *utmost importance* that both the computer running *Home Assistant* **and** *all of your devices* that you plan to manage are connected to **the same network**.

### What Are Subnets Anyway?
Subnets (separated networks) occur when you are using more than one *Router* in your network. 

* Typically, you have at least one router that was supplied by your ISP (*Internet Service Provicer*) and connects you to the *Internet*. This router is managing all devices that are connected to your *wired network* and assigns *IP addresses* to them.
* You most probably also have a *WiFi* which can be a single box with antennas, or a sophisticated *Mesh WiFi* with a main station and a number of satellites to improve coverage.

Unfortunately, by default most *WiFi boxes* are running in *Router Mode*: the WiFi becomes a *separate network* with its own *DHCP server* and its own *IP address range*.

> [!TIP]
> You can easily check by comparing the assigned *IP addresses*: when the first three numbers of a *wired* device (i.e. *192.168.2.112*) are different than the first three numbers of a *wireless* device (i.e. *192.168.68.33*), then you are currently operating *different networks*.   



### Subnets Are Evil
There are valid reasons for using separate subnets, i.e. to keep networks organized and/or to limit traffic.

This very advantage can turn into a huge disadvantage when trying to *manage* your devices: certain information is not passed from one subnet to another. Most importantly, *mDNS* names work only within one subnet.

*Home Assistant* relies heavily on *mDNS* names: each device it discovers and manages is accessed by its *mDNS* name.

The problem starts to surface when the server running *Home Assistant* is connected to a subnet different from the one with the devices that you want to manage. Here is a typical scenario:

* **Home Assistant:** runs on a *Raspberry Pi* that is connected to the wired network via network cable.
* **Devices:** all wireless devices are connected to the *WiFi* network. Their *mDNS* names are inaccessible to *Home Assistant*.   

## Correcting Your Network
If you found that you are currently running more than *one* network, here are ways to make sure *Home Assistant* (or any other home automation solution) works correctly.

> [!Important] **Do not rush** any configuration change. Your network(s) are the crucial backbone of a lot of things in your home. A light-hearted change in your network configuration can easily mess up your network in minutes. Read, think, and only then *act*.   




You basically have two choices that both in essence lead to the same result: all relevant devices are connected to *the same* network.

### Move Server

If *all* of your important devices and sensors are connected *wirelessly* anyway, then the *safest* and *most simple* way is to *connect* the computer that is running *Home Assistant* to the *wireless* network instead of the *wired* network.

* When you run *Home Assistant* on a regular PC, unplug its network cable, and connect it via its *wireless* adapter.
* The same is possible (yet possibly a lot harder) if you run *Home Assistant* on a *Raspberry Pi*. Almost any computer (including *Raspberry Pi*) has an own *WiFi adapter* and can be connected to a *wireless* rather than a *wired* network.

If you're not a *Raspberry Pi* expert and would rather *not* touch its network configuration, then continue to use a network cable, **but** plug the cable into your *wireless* network:

* **WiFi Box Connector:** many *WiFi boxes* have one or two connectors for network cables. When you plug i.e. the *Raspberry Pi* network cable into one of these, it connects to the *wireless network*. No need for any *Raspberry Pi* re-configuration: the *Raspberry Pi* now receives its IP address from the *WiFi box DHCP server*.   

If your *WiFi Box* does not have a connector for network cables:

* **WiFi Extender:** purchase a cheap *WiFi Extender*. These devices connect a network cable to a *WiFi* network.
* **Mesh Satellite:** check your *WiFi box* type and vendor. If you are running a *Mesh WiFi*, you may want to purchase a compatible satellite with network cable connector. This option has the benefit of extending your *WiFi coverage*.
* **Raspberry Pi:** If you know the inner workings of *Raspberry Pi*, you can also reconfigure it so it uses its own built-in *WiFi adapter* to directly connect to your *WiFi*. Unplug its network cable in this case.


### Change WiFi Mode
You could as well simply change the *WiFi* operating mode from *Router* to *Access Point*. The *WiFi box* will then stop acting as a *Router* and no longer issues *DHCP IP addresses*. Instead, it simply forwards the wired network, and all devices - wired or wireless - receive their *IP addresses* from your primary router. 

This way, now *all* devices share the same network, *wired* **and** *wireless*. That is a benefit if some of the devices you'd like to manage are *wired*.



> [!TIP]
> If you *plan to setup a **new** WiFi*, then it's always a good idea to start it in *Access Point* mode. If you are already *running* a *WiFi* in *Router* mode, you should plan this change **very carefully** (see below).   


#### Don't Lock Yourself Out
Changing the *WiFi* operating mode can have *serious consequences* and may render your entire network unusable within minutes, or may render important devices (like i.e. your NAS) inaccessible:

* **New IP Addresses:** since now the *primary router* is the only *DHCP server*, all wireless devices request new *IP addresses* from it. The newly assigned *IP addresses* are in a different range. If you have assigned *static IP addresses* to some devices earlier, then these devices become unaccessible until you update their static *IP addresses* to match the new address range. Updating their *IP addresses* may be challenging as they are now inaccessible from your computers and smart devices.
* **DHCP Overload:** the *primary* router may be many years old. Back when it shipped, it was not anticipated that a modern home would have hundreds of network devices (cameras, door bells, hifi receivers, smart devices, watches, you name it). Outdated *DHCP server software* in old routers may be able to only assign a very limited number of *IP addresses*. When there are more devices than available *IP addresses*, some devices will randomly not receive *any* IP address and instead fall back to self-assigned APIPA adresses in the *168.* range. Effectively, these devices become unaccessible. 


So before you change your *WiFi* operating mode, consider this:

* **Static IP Addresses:** Make sure you know *all wireless* devices that you ever assigned *static IP addresses* (*wired* devices don't matter as for them, the *IP range* does not change). 

  Switch them to *DHCP*, or *assign new static IP addresses* in the *new IP address segment* that will become effective when you switch *WiFi* to *Access Point* mode.
* **Check DHCP Server:** Log into your *primary router*, and review its *DHCP* settings: they show the *IP range* used for *DHCP*. Verify that this range is large enough to serve the number of *IP addresses* needed for all of your network devices.   

  If the *DHCP address range* is too small, try and update the router *firmware*. If all else fails, replace the router with a modern device.



> [!CAUTION]
> **Only** turn your *WiFi* to *Access Point* mode if **you are positive** that your *primary router DHCP* is **capable of handling the number of *IP assignments***. When you switch to *Access Point* mode, every single *WiFi*-enabled device in your home is requesting a new unique *IP address*.    





> Tags: Home Assistant, Network, Router, WiFi, Access Point, APIPA

[Visit Page on Website](https://done.land/tools/software/homeassistant?196642061917245543) - created 2024-06-16 - last edited 2024-06-16
