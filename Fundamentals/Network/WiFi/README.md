<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# WiFi

> Practical Details You Should Know About Your WiFi Network

Of course you know what *WiFi* is. This section focuses specifically on *WiFi details* you **may not yet know** and that can be very important for using *WiFi* with *home automation* and *WiFi-enabled microcontrollers*.

## Overview

A wireless network (*WiFi*) provides the fundamental *infrastructure* to work with *wireless devices*. It makes a significant difference whether you set up *WiFi* for a typical *consumer household*, or whether you need it for *home automation*:

* **Coverage:** with *home automation*, there may be much higher requirements for seamless coverage: *wireless devices* may be located in areas different from *consumer devices*: *garden* (*moisture* and *temperature* sensors or *cameras*), *garage* (*garage door sensors*, *cameras*, *alarm system*), *utility rooms* (*heating system*, *gas and water meter*). *WiFi* needs to cover virtually every area of your home property.
* **Number of devices:** Once you start adding *smart wireless devices* to your home, you quickly and significantly increase the number of devices that are connected to *WiFi*: every *WiFi* device (every sensor, smart plug, remote button, etc.) counts as one. Thus, your *WiFi* needs to be capable of handling this many devices.
* **WiFi Bands:** Modern *WiFi stations* use *2.4GHz*, *5GHz*, and even *6GHz* in parallel to transmit data. Each frequency band increases the *bandwidth* (speed of data transfer) and has individual transmission characteristics that in combination ensures good coverage across walls or levels - but only for *consumer devices* such as *smartphones*. *Home automation* uses *WiFi-enabled microcontrollers* that exclusively work with the *2.4GHz band*. So if *WiFi coverage* in this particular band is poor, impaired by interference, or if this band was disabled altogether, it hits *home automation* severely while at the same time, *WiFi* seems to operate smoothly for *consumer devices*.

> [!TIP]
> You might want to also look into using *Zigbee* devices (and an appropriate *Zigbee gateway*) to shift load off your *WiFi* and reduce the number of devices that need to connect to your *WiFi*: *Zigbee* automatically creates its own network in which any *Zigbee* device can act as *repeater* and extend *network coverage* automatically.


## WiFi Stations
*WiFi networks* are created by one or more *WiFi stations* that *wireless devices* can connect to, and in a consumer household, you are typically just concerned about setting a *WiFi SSID* (*WiFi* name) and a secret password to access the network - and off you go.

With *home automation*, additional thoughts and configurations are required to set up and configure a *reliable WiFi*.

### Typical Consumer Setup
In most *consumer homes*, connection to the Internet is established by a *Router* that was installed (or provided) by the *internet service provider* (*ISP*).

This router is connected to the *phone line* (or whatever cable the *ISP* is using), and on its other end it provides *ethernet plugs* (to connect *wired* devices) and sets up a simple *WiFi Access Point* (to connect *wireless* devices).

### Improving Coverage
Simple *ISP routers* often do not provide sufficient coverage, even for pure *consumer scenarios* with no *home automation ambition* at all.

That's why *WiFi coverage* often is improved by using these strategies:

* **WiFi Extenders:** devices that pick up the *WiFi signal* from one station and amplify and re-send it. The involved *data hopping* from one device to the next *slows down* data transfer and may work only for *one* of the *WiFi bands*.
* **Additional Access Points:** by setting up *additional WiFi access points* in different locations of your home, *wireless devices* can connect to *any* of them, effectively extending coverage. Each *Access Point* needs to be connected to the *wired network*, though.
* **Mesh Networks:** Only the *main WiFi station* needs to be connected to the *wired network*. The *satellite stations* use *wireless* or *wired backhaul connections* to connect with each other.


### Home Automation Aspects
*Mesh WiFi* is the best strategy for setting up a *WiFi network* suitable for serious *home automation*: a *mesh* allows for extending coverage to any rooms, levels or locations simply by adding another *satellite*.

Each new *WiFi station* also increases the total number of devices that can connect to *WiFi*. This number depends on two factors:

* **WiFi Station Capability:** each *WiFi station* has its own maximum number of clients it can serve. Simple devices typically allow for 20-30 clients, low-budget devices support up to 50 devices, main-stream devices can serve 100 devices, and high-end stations support 200 or more devices. This number is *per station*. In a mesh, you can granularly control the number of devices by adding another satellite to areas with many devices, or by switching the satellite type to a model with more capability.
* **Bandwidth:** the data that can be transferred by *WiFi* is another limiting factor that typically is not relevant in *home automation*: *sensors*, *plugs*, and even *cameras* transmit only a *fraction* of the data that your *smartphone* or a *TV set* utilizes.

When setting up a *mesh WiFi*, here are a few considerations:

* **Disable Original AP:** *disable* the built-in *WiFi access point* in your *ISP router* as it is no longer needed and would just *interfere*, especially if your new *WiFi* is using the same *SSID* (network name).
* **Use wired backhaul:** whenever possible, use an ethernet cable to connect *satellites* with the main station. A wired backhaul is much faster and more stable. If no cable connection is possible between given satellites, they use a *wireless* backhaul automatically.
* **WiFi Band:** make sure your *WiFi* uses the *2.4GHz band* which is the one used by *wireless-enabled microcontrollers and devices*.


## WiFi Mode

Each *WiFi network* can operate in one of two modes which can have **significant impact** on whether your *home automation solution* work well or not:

* **Router Mode:** the main *WiFi station* acts like a *Router*: it defines its own *subnet*, runs its own *DHCP server*, and issues its own *IP addresses* to connected devices.
* **Access Point Mode:** each *WiFi station* (regardless whether *main station* or *satellite*) connects wireless devices to the original router. Devices receive their *IP addresses* from the original router, and *no subnet is created*.

### Impact Of Subnets
Most *WiFi stations* use *Router mode* by default, so if you have already set up your *WiFi* and not paid special attention to the *WiFi mode*, chances are you are currently using *Router mode*.

> [!IMPORTANT]
> While you *can* change the *WiFi mode* easily at any time, **do not do it just yet!** Understand the consequences first (see below).

#### mDNS Cannot Traverse Subnets
In *Router mode*, your *WiFi network* is a *separate network*. *mDNS name resolution* does not work across such networks. That has significant consequences when *mDNS device names* are used to resolve the *IP address* of a device.

Here are typical real-world consequences that a *home automation* user may experience:

* **Home Assistant:** *wireless* devices are not discovered and need to be manually added via their *IP address*. 
* **ESPHome:** *wireless* devices are reported to be *offline* when in fact they are *online*.

These issues occur because the user has connected his *Home Assistant server* with a network cable to his *wired* network, whereas the devices connect *wirelessly* to *WiFi*, and his *WiFi* runs in *Router mode*.

Because of the *WiFi Router Mode*, neither the devices can contact the *mDNS name **homeassistant.local*** (because it exists in a different subnet), nor can *Home Assistant* (as well as its *ESPHome* add-on) contact the *mDNS device name* of a *wireless* device to determine its online status (because it exists in a different subnet).


<details><summary>Is My Network Setup Currently Affected By This?</summary><br/>


To check whether your current network setup is problematic, determine the *local IP addresses* of a *wired* and of a *wireless* device, and compare them.

First start by finding out the *local IP address* assigned to a *wireless device* such as your *smartphone*. The process of getting to see the *local IP address* is different for each device type and operating system. Here are the steps for *iPhones*:

1. Tap *Settings*, then tap *WLAN* or *WiFi* (the setting that you use to connect to a *WiFi*).

2. In the top area, you see a checkmark and the name of the *WiFi* you are currently connected to. At the right end of this line, there is a round *info* symbol. Tap it.

3. You now see the *WiFi* details. Scroll down until you see *IP Address*. Make a note of the currently assigned local IP address.

Next, do the same with a *wired* device, i.e. your *PC* (provided it is connected to your network via *network cable*). Again, the procedure varies with the *operating system* you use. Here are the steps for *Windows 10*:

1. Open the *start menu*, then click the *gear* symbol to visit *Settings*.

2. Click the category *Network & Internet*, then in the sidebar to the left, click *Ethernet*. Now you see your active *ethernet connection(s)*.

3. Double-click your *ethernet connection icon* to view its properties. When you scroll down a bit, you see its *IPv4 address* (do not confuse it with any *driver versions* that may look similar). Make a note of the address.

As a rough estimate, when you compare the first three numbers of both *IP addresses*, and they differ, then most likely you are using separate subnets.

</details>



## Fixing Your Network
As you have seen, the *WiFi mode* can cause significant issues with *home automation*:

* **Access Point mode:** does not create *subnets* and thus uses the *primary Router and its DHCP* for **all** devices, *wireless* and *wired*. This is the simplest way to ensure that all devices and computers can contact each other.
* **Router mode:** do not allow *wired* devices to discover *wireless* devices (and vice versa).

> [!IMPORTANT]
> **Hold on - do not change the *WiFi mode*** of an *existing WiFi network* **just yet**! Before you consider to make *any changes*, first read on to fully understand the consequences.

### Caveat: Access Point Mode
Switching a *WiFi network* to *Access Point mode* may solve the issues outlined above, but may cause *new* trouble on other ends:

* **DHCP Limitations:** once you *disable WiFi Router mode*, all devices in your home start requesting new *IP addresses* from your primary router. Since this router often is quite old, it may not at all be *capable* of issuing this many *IP addresses*, leaving random devices without valid *IP address* and *inaccessible*. 
* **IP Address Change:** if you decide to *switch WiFi mode* from *Router mode* to *Access Point mode* for a network that already **ran for a while**, this will cause all devices to receive new *IP addresses* from a completely different range. This can break existing *integrations* in *Home Assistant*, may leave behind devices that you assigned *static IP addresses manually*, breaks pre-existing *Cloudflare tunnels* you may use for remote access, and much more.


So what now?

### Recommended Fixes

Here are some remedies to fix the subnet issues without creating new issues elsewhere.

#### Using WiFi Router Mode 

If your *WiFi* is currently running in *Router mode*, then the easiest and least impactful fix is to ensure that your *computers*  connect to your *WiFi* so they *share* the same subnet with your *devices* - at least the one computer that is running *Home Server*/*EspHome* or is otherwise supposed to manage your devices:

If you are using a *Raspberry Pi* to host *Home Assistant*, connect it *wirelessly* to your network, or plug its *network cable* into one of your *WiFi stations*.

<details><summary>I cannot connect an Ethernet cable to my WiFi station(s)</summary><br/>


If your *WiFi Stations* do not have a spare ethernet plug to connect *wired* clients, use of of these alternatives:

* **WiFi Extender:** purchase a cheap *WiFi Extender*. These devices connect a network cable to a *WiFi* network.
* **Mesh Satellite:** check your *WiFi box* type and vendor. If you are running a *Mesh WiFi*, you may want to purchase a compatible satellite with network cable connector. This option has the benefit of extending your *WiFi coverage*.
* **Raspberry Pi:** If you know the inner workings of *Raspberry Pi*, you can also reconfigure it so it uses its own built-in *WiFi adapter* to directly connect to your *WiFi*. Unplug its network cable in this case.


</details>

### Using WiFi Access Point Mode

The *cleanest* solution is to *completely redesign your **entire** network* and operate your *WiFi* in *Access Point mode* - **beware:** this is **not** done in a few minutes, and *most definitely not done* just by switching *WiFi mode* to *Access Point mode*.

> [!TIP]
> Seriously: the most reliable way to **waste many days** with completely senseless work at a high heart frequency is to switch an existing *WiFi* network from *Router* mode to *Access Point* mode without proper preparation.

Before you switch the *WiFi mode* to *Access Point*, consider these aspects:

* **Primary Router:** is your primary router and its *DHCP service* capable of handling hundreds of devices? Do you possibly have to edit its settings and define a wider *DHCP address range*? Do you possibly have to change the network subnet mask from `255.255.255.0` to `255.255.252.0` to extend the number of available *IP addresses* from *253* to *1022*? Or do you even have to switch to an external *DHCP service*?
* **Static IP Addresses:** have you set up any *static IP addresses* manually? Will they still work with the new DHCP settings?
* **Integrations & Tunnels:** Have you set up any *integrations* or configured any *add-ons* in *Home Assistant* that rely on *IP Ranges*? Will they continue to work with your new *DHCP settings*?


> [!TIP]
> If your computer **must** stay in the *wired* network, you may be able to work around the subnet issue by re-configuring software like *Home Assistant* and *ESPHome* to use *IP addresses* and *ping* instead of *mDNS*. Or, you can add a simple manual network switch that can switch between *wired* and *wireless* networks. Or, you can add another network card to your computer and connect it to *both* subnets. There are many more workarounds. Just make sure you *understand the problem* and configure your network in such a way that all devices can contact each other and share the required information with each other.


> Tags: WiFi Mode, Subnet, Mesh, Backhaul, Access Point, Router, Zigbee

[Visit Page on Website](https://done.land/fundamentals/network/wifi?438829071318241908) - created 2024-07-17 - last edited 2024-07-17
