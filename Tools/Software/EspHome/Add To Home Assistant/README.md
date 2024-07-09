<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Add ESPHome Device To Home Assistant

> Adding Your ESPHome Device To Home Assistant And Turning It Into A Fully Manageable Device

While this is not required, adding an *ESPHome device* to *Home Assistant* opens a whole new world of options.

<details><summary>Benefits of Home Assistant Integration</summary><br/>

*ESPHome* runs stand-alone and does not require *Home Assistant*.

*Home Assistant* makes *ESPHome* just better. Without it, you need to add *user interfaces* and *automation logic* yourself. 


Adding *ESPHome* devices to *Home Assistant* turns your device into a "lego" piece, and it can now be used in conjunction with all the other devices you may have set up. No longer does your *ESPHome device* need to handle everything itself. 

You may for example want to create a really simple *CO2 sensor* that can just collect CO2 environmental data, and delegate the *display of these values* to a *Home Assistant dashboard* where you collect and display the environmental data from all of your sensor devices.

Or you may want to create a really simple *ESPHome push button device* that you can place anywhere. By adding it to *Home Assistant*, the push button device does not need to also implement the effector device. Instead, you can device yourself which other device the push button should control.

</details>




## Auto-Discovery


When everything is configured correctly, your *ESPHome device* is automatically discovered by *Home Assistant* once it goes online. If you are using the *Home Assistant App* on your smartphone, it is as simple as this four-click process:


<img src="images/ha_autodiscovery.png" width="80%" height="80%" />

On a computer and from within *Home Assistant*, the auto-discovery process starts with a *notification* in the *Home Assistant sidebar*:

<img src="images/rasp_notification.png" width="80%" height="80%" />

To accept the new device, follow these steps:

1. Click *Notifications* in the *Home Assistant* side bar, then *check it out* to see the newly discovered device(s):


    <img src="images/10_discover.png" width="80%" height="80%" />
  

2. Click *CONFIGURE* to add the new device to *Home Assistant*. Once you confirm, the device is added, and you can optionally assign it a location:


    <img src="images/11_added.png" width="80%" height="80%" />
  

### Manually Adding Device

If you have a wireless device in range but *Home Assistant* won't automatically recognize it, you can always *manually* add it.

> [!TIP]
> Manually adding a device is not just a bit more *inconvenient*, rather it often indicates an underlying **fundamental problem** with your **network configuration** that most likely will bite you in many unexpected situations - until you fix it.





<details><summary>Manually Adding ESPHome Device</summary><br/>

If *Auto-Discovery* does not work for you, add the *ESPHome device* manually. For this, you need its *IP address*.

If you don't know the *IP address* assigned to the *ESPHome device* you want to add, go to *ESPHome dashboard*, identify the tile for your *ESPHome device*, and click *LOGS*.

This opens a window with the device logs, and in this log you find the currently assigned IP address.


<img src="images/logs.png" width="80%" height="80%" />
  
Once you know the devices' currently assigned *IP address*, follow these steps:


1. In *Home Assistant*, go to *Settings*, then *Devices & services*, then click on the integration *ESPHome*. 
2. On the *ESPHpme* page, click *ADD DEVICE*:

    <img src="images/13_add_ha.png" width="80%" height="80%" />
  

3. A dialog opens. As *Host*, enter the currently assigned *IP address* of your *ESPHome device*. Leave the port at *6503*, and click *SUBMIT*.

    <img src="images/14_add_manually.png" width="80%" height="80%" />




</details>



### Why Auto-Discovery May Fail
If you configured *Home Assistant*, *ESPHome*, and your *network* correctly, you should never need to manually add *ESPHome devices* to *Home Assistant*. Built-in *Auto-Discovery* should always pick up your devices automatically.

If *Auto-Discovery* does not work, you may work around it by manually adding the device. However, that does not fix your fundamental network problem. Until your network issue is identified and fixed for good, your home automation setup is not robust and may experience issues regularly.

#### mDNS Is Critical
*ESPHome* relies on *mDNS* names to identify and access devices. 

When *mDNS* is not working (correctly), *ESPHome* may not find your device, and it is marked *OFFLINE* in the *ESPHome dashboard*.

Since the device in reality *is* available, you can add it successfully manually via its *IP address*. A much better approach would be however to ensure that *mDNS* works for you.

> [!TIP]
> If your network architecture does not allow *mDNS* to work, you can change *ESPHome settings* and use *ping* instead of *mDNS* to check for device availability. Do this as a last resort, and do check your network configuration first.



### Checking Network Configuration
*mDNS* works only within *one* network. Many users operate *more than one* network without knowing.

When your *WiFi* is running in *Router* mode (and not in *Access Point* mode), it spawns a new *separate* network and acts as *DHCP server*. *mDNS* cannot traverse to the wired network (and vice versa).

So if you connected your *Home Assistant server* to your *wired* network, it cannot discover any *wireless* device via *mDNS*.

### Fixing Your Network
The best approach often *would be* to have just *one* network. That's why many users set up their **new** *wireless* network in *Access Point mode*.

#### Do not immediately switch WiFi network mode
While you *can* switch an **existing** wireless network from *Router* mode to *Access Point* mode, you should never do this light-heartedly. It may seriously *break* your existing networks and causing you hours of headaches.

> [!NOTE]
> When you switch an **existing** WiFi network to *Access Point* mode, your ISP router now starts assigning IP addresses to all of your wireless devices. These addresses are in a different range, and when you ever assigned addresses manually, then they do not match the subnet mask anymore. On top, many old ISP routers can only handle a limited number of devices and may not assign IP addresses to all of them, randomly leaving devices inaccessible.


#### Easiest Fix
Often, when operating a *WiFi* in *Router* mode, the easiest fix is to leave your networks untouched.

Instead, make sure the *Home Assistant server* is **on the same network** with your wireless devices:

* **Bridge:** either connect the network cable of your *Home Assistant server* to your *wireless network*. Often, access points provide a few network cable connectors where you can plug in the network cable. You can also buy a cheap *WiFi bridge device*.
* **Wireless:** or, connect the *Home Assistant server* wirelessly to your network. This way it is automatically sharing the same network your *wireless* devices are using. However, configuring the network of your *Home Assistant server* to use the wireless adapter may require advanced technical skills.

> [!TIP]
> With the fix above, your *Home Assistant server* can access all *wireless* devices. Wired devices remain inaccessible as they are on a separate network. If that is of concern to you, then carefully redesigning and cleaning up your network design is a great idea. Just don't rush, and never switch your *WiFi* from *Router* to *Access Point* mode without prior careful evaluation.


> Tags: EspHome, Home Assistant, Discovery, Auto-Discovery, Adding

[Visit Page on Website](https://done.land/tools/software/esphome/addtohomeassistant?002745061229240725) - created 2024-06-06 - last edited 2024-07-09
