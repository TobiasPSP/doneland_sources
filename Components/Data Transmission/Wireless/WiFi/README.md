<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Data Transfer Via WiFi

> Using WiFi Networks To Securely Transfer Data

*WiFi* is commonly used everywhere to create wireless networks and transfer data with high speed safely in an encrypted way. When you can rely on an existing *WiFi* network with good coverage, it is an excellent way of transferring data from DIY devices.

Many modern microcontrollers (like the *ESP8266* and the *ESP32* family of microcontrollers) already come with full *WiFi* support.

## Operating WiFi

To set up and operate a *WiFi network*, it is important to understand a few devices and their operating modes so you don't run into issues when later connecting DIY devices to your *WiFi network*.

First off, here is a quick recap of important terms:

* **LAN (local area network):** private network in your home or office, can be wired or wireless.
* **WAN (wide area network):** public network like the *Internet*
* **NAT (network address translation):** exchanges a private *IP address* with a public *IP address*, and vice versa
* **Port:** each *IP address* can receive information on up to 65.535 ports. Some port numbers are statically assigned, i.e. a *webserver* always expects *http* requests at port *80*. Most ports however are *dynamically assigned* during communication between two devices, i.e. when you browse to a web page, your browser addresses port *80* but provides a *dynamic return port* for the webserver to return the requested information to.
* **Firewall:** acts like a data packet filter. A *firewall* scans incoming data packages and then determines whether these packages can pass and connect to the private *LAN*. A *firewall* makes sure that hackers cannot *probe* your internal network and *scan for available ports*. It basically acts like a *concierge* that only allows invited guests to enter the party.
* **DNS (Domain Name System):** Service that translates human-readable domain names into *IP addresses*. Without *DNS*, you would always need to use *IP addresses* to contact network devices and services. Thanks to *DNS*, you can instead *resolve* a friendly name and find out its current *IP address*.
* **DHCP (Dynamic Host Configuration Protocol):** crucial functionality built into most *Routers*. It automatically assigns *IP addresses* to devices on a local network.
* **Router:** creates a new local area network (*LAN*) with its own *IP range* and *firewall*, and connects it to other networks (i.e. the *Internet*)
* **Modem:** converts the digital information from your network to some format that can be carried over the cables that connect you to the *Internet*. Depending on your type of *Internet connection*, there are *DSL modems*, *cable modems*, *fiber-optics modems*, and *GSM/cellular modems*.
* **Access Point:** device that can send and receive wireless information and connect it to a *wired network*

### Setting Up WiFi Network

Devices that you use to set up a *WiFi network* are typically called *Wireless Router* or *WiFi Router*. This term is misleading since such devices do not necessarily act as *Router* and can in fact work in three completely different modes:

* **Router:** the device creates a completely new and isolated LAN (local area network) with its own *IP addresses* and *firewall*, shielding it from other networks such as your *wired LAN* and the *Internet*. It also acts like a *wireless Access Point* that wireless devices can use to connect to.
* **Access Point:** in this mode, the device **does not act as a Router**. It only serves as an *access point* for wireless devices to connect to. The wireless devices are directly connected to the *wired ethernet network*, and the *Router* that manages your *wired network* now also manages the wireless devices. Together, wired and wireless devices form one big LAN, using IP addresses from the same segment.
* **Extender:** This mode plays a special role as it is *not* used to create a new *WiFi*: it connects to an *existing WiFi* and can be used to (a) extend the *WiFi coverage* by amplifying and forwarding signals, and (b) connect *wired devices* to the *WiFi* (provided the device has one or more ethernet jacks).


### Router

A *Router* is the most important device in any *data package-based* network: it connects *two or more* networks and makes sure the data packages know where to go, much like a traffic manager or a navigation system. 

Even with the most simple *WiFi network*, you typically want to connect it to the *Internet*. This is possible only when you operate a *Router* that knows how to transfer data between these two networks.


> [!IMPORTANT]
> For *WiFI*, you **do** need a *Router* - but you **do not** necessarily need a ***dedicated** Router*. You can also use the *existing Router* that was installed by your *Internet Service Provider* and that already manages your *wired network*. Operating your *WiFi* in *Router Mode* (with its own dedicated Router turned on) versus *Access Point Mode* (with its own Router turned off, sharing the existing Router of your wired network) can make substantial differences and should be an educated and carefully considered decision when setting up a new *WiFi*.

*Routers* create an entirely new *LAN* that uses its own *IP address range* and can communicate with other *LANs* and the *WAN* (*Internet*):

* **DHCP:** assigns *IP addresses* to all connected devices from its own *IP address pool* in its own *IP Address Range*.
* **Firewall:** isolates the network against other networks, and i.e. prevents broadcast and *mDNS* messages to be passed on to other networks

> [!IMPORTANT]
> When you set up a *WiFi* via a dedicated *Router* (aka: use *WiFi in Router Mode*), you are shielding your *WiFi* and all of its devices from your *wired network*. If you do this, make sure *all of your devices* are connected to *WiFi* (including your stationary PC, notebooks, Raspberry Pi servers, etc.).


#### Traffic Manager

*Routers* use internal *routing tables*: a list of paths to various network destinations. Just like a navigation system in a car, the *Router* reads a data packet header to determine its intended destination, then looks up the destination in its *routing table* to figure out the most efficient path to this destination.

*Routers* also take care of *network address translation (NAT): your private *Internet connection* gets assigned just *one* public *IP address*. Inside your private *LAN*, there can be numerous devices and software (like browsers), though, that all have unique *private IP addresses*. When such a device sends a data packet to an *Internet-based device or service* (i.e. a web server), *NAT* replaces the private IP address with the *one* public IP address you have, and adds a dynamically assigned *port* so it can later keep track of the incoming data and assign it to the correct device, essentially providing the *Internet-based service* a way to return information back to exactly the one private device that initiated the communication. When this return information arrives, *NAT* identifies the internal device that is supposed to receive this data by looking at the port at which the information was received, and then changes the *public IP address* back to the internal *IP address* matching the device that initiated the communication.

#### Security

Many *Routers* come with additional security features such as a *Firewall*, shielding your *private LAN* from the public Internet and making sure that no unsolicited data packages can penetrate your *LAN*. Today, with the high number of automated attacks against random IP addresses, a firewall must always be in place when connecting any LAN to the Internet.

#### DNS (Domain Name System)

*DNS* is a public service that translates friendly names such as *google.com* to the current IP address of that device or service. Only when you know the *IP address* will you be able to connect a device.

*Routers* typically support *DNS* via *DNS Forwarding*: when local devices want to resolve a domain name, their request is *forwarded* to a public *DNS service*. These services can be made available by your *Internet Service Provider*, but also exist as free services:

| DNS Service Provider | IP Addresses |
| --- | --- |
| Google | `8.8.8.8`, `8.8.4.4`|
| Cloudflare | `1.1.1.1`, `1.0.0.1`|
| Cisco | `208.67.222.222`, `208.67.220.220` |
| QUad9 | `9.9.9.9`, `149.112.112.112`|
| Comodo | `8.26.56.56`, `8.20.247,20`|
| Verisign | `64.6.64.6`, `64.6.65.6`|
| CenturyLink | `4.2.2.1`, `4.2.2.2`|
| Yandex  | `77.88.8.8`, `77.88.8.1`|

*Routers* also often support *local DNS caching*, reducing the number of requests made to public DNS services. Locally cached information is much faster than requesting the information via a public service.

#### DHCP (Automatic IP Address Assignment)

Any device on your network needs a unique *IP address* so other devices can contact it. Without *DHCP*, you would need to manually assign a unique IP address to each and every of your devices, and keep track that no *IP address* is accidentally used with more than one devices. Most *routers* have a built-in *DHCP server*.

*DHCP* takes automatically care of *IP address assignment*: when a devices has no *statically (manually) assigned IP address*, it requests one from *DHCP*. *DHCP* then assigns a random *IP address* from its *IP address pool* that has a *lease period* after which the device mus request a new *IP address*. This way, *IP addresses* are always assigned only for a certain period of time and can then be recycled for other devices. Since typically in a network, not all devices are turned on and used all the time, *DHCP* efficiently manages a scarce resource: the number of available *IP addresses* is limited.

> [!TIP]
> *DHCP* is great for consumer gear that you do not want to connect to manually. For DIY projcts, you often **do want to connect directly** (i.e. access a microcontroller and its web interface). So here, *DHCP* is not ideal because the *IP address* of a device may change at any time. And since you are typically not running your own *DNS server*, you cannot use a static friendly name for your device either. That's why some *DIY Makers* manually assign *static IP addresses* to their devices: now the *IP address* won't randomly change anymore and can be used whenever you want to contact this device. A more sophisticated and user-friendly way uses *mDNS* (*Multicast DNS*) which is a decentralized *DNS* without the need for a dedicated *DNS server*. Instead, the devices themselves listen for *mDNS* multicast requests and provide their current IP address when asked to. Occasionally, *mDNS* does not seem to work right, and some users give up in frustration and return to manually assigned static *IP addresses*. Which is unfortunate because typically, *mDNS* works well when done right: you must understand that *mDNS* only works within a *LAN*. A system in *one* network (i.e. a Raspberry Pi connected to a **wired** ethernet network) cannot resolve *mDNS names* for devices connected to *another* network (i.e. wireless devices connected to a **wireless** network running in *WiFi Router Mode*). 


### Access Point


When you run a *WiFi* in *Access Point Mode*, you simply provide a way for your wireless devices to connect to your wired network. Once connected, your wireless devices are handled by the same *Router* that is already handling all of your wired devices.

Running a *WiFi network* in *Access Point Mode* prevents the *WiFi* from operating its own *Router*. This way, you keep **one** network, and *wired* and *wireless* devices all receive *IP addresses* from the same pool, and can freely communicate with each other without blocking *firewalls*.

### WiFi Bridge
The term *WiFi bridge* is often used when a *wired device* needs to be connected to a *WiFi*, or when a *wireless device* needs to be connected to a wired *ethernet network*. This functionality can typically be implemented with one of the *WiFi modes* discussed earlier.

#### Wired Device To WiFi Network
There is a quite common need to connect a *wired device* to a *WiFi network*. Here are two practical scenarios:

* **Solar Inverter:** you may have a *solar inverter* in your garage or attic that may have an *ethernet port* to monitor its operations and transfer data to the *Internet*. However, at that location you don't happen to have a wired ethernet connection available.
* **Home Assistant Server:** you may have found that your *Home Assistant server* does not discover wireless devices, and found that the reason is that your *WiFi* is running in *Router mode*, and that your *Raspberry Pi server* is connected to your *wired* network. You don't want to switch your *WiFi* to *Access Point mode*, and you also don't want to fiddle with your *Home Assistant installation* and *Raspberry Pi configuration* to directly connect it to *WiFi*. 

In both cases, you can simply plug the ethernet cable into a cheap dedicated *WiFi router* (available for less than €4.00), and run it in one of these modes:

* **Range Extender (with one or more Ethernet ports):** switch it to *Extender* mode, connect it to your existing *WiFi*, and plug in the ethernet cable to one of its ethernet ports. 
* **Access Point (with Client or Bridge mode):** switch it to *Access Point mode*, then look for an option to switch it to *Client* or *Bridge* mode. When these modes are activated, you can connect the device to your existing *WiFi* network, and connect the ethernet cable to one of its ports. **Important:** a *normal Access Point mode* would ask you to set a new *SSID* and *password*, then create a *new WiFi access point*. This is not what you want for this use case. Make sure the device supports a *Client* or *Bridge* mode, and then asks you to connect to *an existing WiFi*.


#### WiFi Device to Wired Network
The opposite use case may be important as well: you want to connect a *wireless* device to a *wired network*. Here is a practical use case:

* **Document Scanner:** you may have purchased a great new *document scanner*, but unfortunately it only comes with *wireless connectivity*. You however would like to scan documents directly to your *NAS* or any other wired computer.

When you connect the device to your *WiFi*, this may already be all you need - provided you run your *WiFi* in *Access Point Mode*. If you run it in *Router mode*, the scanner can connect to your *WiFi*, but since the *WiFi* is a separate network, it cannot connect to your *wired devices* like your *NAS*.

Here are the options you have:

* **Change WiFi Mode:** you *could* simply change your existing *WiFi* and switch it from *Router Mode* to *Access Point Mode*. Now *wired* and *wireless* networks would be combined. However, **never simply switch WiFi mode for existing WiFi networks**, or *very* bad things may happen.

> [!CAUTION]
> Always make sure you understand all consequences, including reassignment of completely new *IP addresses* from a *different segment* for all of your wireless devices, potentially invalidation of statically assigned *ip addresses* that now no longer are in the appropriate ip segment, and overload of old *routers* that are suddenly responsible for managing numerous additional wireless devices.

* **Add dedicated Access Point:** a simple *WiFi Access Point* device can be purchased for less than €4.00, so you may simply want to add a dedicated *Access Point* for this use case. Assign it a distinct *SSID*, then connect your document scanner to this access point.


## Security Considerations

When setting up a wireless network, *security considerations* are especially important: *wireless radio waves* are not confined to your property and can be picked up by anyone. With special antennas, attackers can penetrate your *WiFi* from many miles away.

All security settings are done in the *WiFi Router* (regardless of whether it runs as a *Router* or as a simple *Access Point*). Typically, you connect to it via a browser. Check the manual of your device for specific instructions.

### Encryption
Encryption is part of *WiFi access control*: only when a legit user gains access to the *WiFi* network will that user be able to encrypt and decrypt the data exchanged.

When you do not enable *access control* (by not setting an access password), you are essentially turning off even the most basic security features: anyone can connect, and anyone can monitor any traffic. Obviously, this is no option - even if you use it just for sensor data.

Once you add a *password* to your *SSID*, you also select the *encryption mode*:

| Mode | Introduced | Encryption | Remarks |
| --- | --- | --- | --- |
| WEP | 1997 | RC4 stream cipher | obsolete and insecure. Do not use. |
| WPA | 2003 | TKIP 128bit | low security but ok for use in pure low-importance sensor networks: effort to break WPA is higher than value of data. **Do not use** for *regular WiFi networks* connecting to smartphones, computers, or sensitive home automation devices |
| WPA2 | 2004 | AES 128/192/256bit | standard security protocol in most *WiFi* networks today. It can be hacked, however effort and procedures are impractical for typical scenarios |
| WPA3 | 2018 | AES and MFP/PMF | best security, still less available |

### Deauth Attacks And Spoofing

Unfortunately, *WiFi* does not encrypt the entire traffic. *Management Frames* are partially unencrypted. This opens ways for attacker to find out sensitive network data, manipulate and spoof data, and invoke *deauthentication attacks*: these take advantage of the fact that even without being authenticated, anonymous parties can send unencrypted *deauthentication frames* to your wireless devices. This forces all wireless devices to *reconnect*. *Deauth* attacks are primarily used to (a) deny service and interrupt operations, i.e. when breaking into a house that is protected by *WiFi-based* cameras, and (b) intercept and manipulate forced reconnection attempts, or lure devices into reconnecting at a spoofed rogue access point instead.

**MFP (Management Frame Protection)** aka (**PMF: Protected Management Frames**) aims to close this security issue by protecting management frames from unauthorized access and manipulation. This is outlined in *IEEE 802.11w-2009*.

### (Highly) Secure WiFi
Operating a secure *WiFi* requires *all* devices to support *MFP/PMF* (*802.11w*). Most computers and quality devices today support *802.11w*. For example, *Windows* uses this standard since *Windows 8*. However, wireless devices need to support *WPA3* which is not the case for the majority of consumer gear.

Access Points that support *802.11w* offer three different login methods:

* **No PMF:** no protection for management frames
* **Always PMF:** management frames are always protected however now any device that does not yet support *802.11w* will not be able to connect
* **Client decides:** that's the compatibility mode that allows older clients to connect while enabling *802.11w* for any device that supports it. Put differently, this mode reduces the attack surface but does still provide room for attackers to penetrate.

> [!NOTE]
> *802.11w* aims at professional corporate wireless networks. Private users simply don't provide enough prey that would make attacks worthwhile, and *802.11w*-compliant consumer hardware is still expensive and less available. Still, being **aware** of *802.11w*/*WPA3*, and what it does, makes sense for home users as well: selecting devices that support *802.11w* (when cost and availability allows) enables you to eventually become ready for stepping up your security, too.  





> Tags: WiFi, Data Transfer, WPA, WPA2, WPA3, MFP, PMF, 802.11w, Router, Access Point, Firewall, DNS, DHCP, Range Extender, Bridge, WiFi Bridge, NAT, Port, WAN, LAN

[Visit Page on Website](https://done.land/components/datatransmission/wireless/wifi?570566081114241442) - created 2024-08-13 - last edited 2024-08-13
