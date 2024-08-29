<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Assembling Raspberry Pi 5 And Installing Home Assistant 

> Step By Step Guide To Assemble A Raspberry Pi 5 And Install Home Assistant OS Or Any Other OS

Assembling a *Raspberry Pi 5* is a matter of just 10 minutes. 

> [!TIP]
> Before you start assembling the *Raspberry Hardware*, go to your *PC* or *Apple Computer* and [prepare an *SD-Card* or *SSD Drive*](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/selectingos) with the *operating system* that you want to use on the Raspberry Pi. Once the drive is prepared

Once you have prepared the disk drive that you want to use in your *Raspberry Pi*, here are the steps to put together the *Raspberry Hardware* and run it:

<img src="images/raspberry_pi_5_logo_6_t.png" width="50%" height="50%" />

 

## Mounting Active Cooler
For this you need the *Raspberry Pi 5 board* and the *Raspberry Pi 5 Active Cooler* kit:

<img src="images/12_raspberry_pi_5_fan_t.png" width="50%" height="50%" />

> [!TIP]
> The *Raspberry Pi 5 Active Cooler* kit can be part of the Raspberry housing. In this case, the *active cooler kit* is located *inside the housing*, and you need to unscrew the housing and open it to get to the cooler.

### Two Mounting Holes

First, identify the two mounting holes on the *Raspberry Pi 5* board. The *active cooler* fan has two *snap-connectors* that fit tightly into these holes.

Also indentify the major components on the board that emit heat and need cooling: the *processor*, the *I/O controller*, the *memory*, and the *power management chip*.



<img src="images/14_raspberry_pi_5_mounts_marked2_t.png" width="80%" height="80%" />

### Thermal Adhesive

On the back side of the *active cooler*, *thermal adhesive* can be seen. Peel off the cover, then place the fan onto the board so that the spring-loaded pins fit into the two mounting holes.


<img src="images/13_raspberry_pi_5_fan2_t.png" width="50%" height="50%" />


> [!TIP]
> Do not confuse the *two* mounting holes with the *four* holes that are used to mount a *hat* (extension board). You may want to *practice* first and get a good understanding how the *fan* needs to be positioned before you peel off the adhesive cover and *firmly* press the pins into the mounting holes until they snap into place.    


<img src="images/16_raspberry_pi_5_fan_mounted2_t.png" width="80%" height="80%" />

<img src="images/15_raspberry_pi_5_fan_mounted_t.png" width="80%" height="80%" />


Next, connect the plug from the *active cooler* to the connector on the board - done.


## Adding Disk Drive To Raspberry

*Raspberry Pi 5* really shines when you add a fast *SSD Drive* to it. In this section you learn how you add such a drive to your *Raspberry Pi*.

A *SSD drive* isn't required, though. You can also use a *SD Card*. 

> [!IMPORTANT]
> A *SD Card* is not recommended for your primary operating system because it is so much slower than an *SSD drive* and can also *wear out* over time. Using an *SD Card* can still be a good option for *special scenarios* where you want your *Raspberry* to run a different environment temporarily.

In either case, make sure you [pre-loaded your operating system of choice](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/selectingos) to either the *SSD drive* or a *SD Card* before you proceed.

### SD Card
If you chose to use a *SD Card*, simply slide it into the Raspberry Pi *SD Card reader*.

### SSD Drive
To add a *SSD drive* to the *Raspberry Pi, you need the *M.2 Shield for Raspberry Pi* which looks fairly similar to the *USB adapter* you  used to pre-load the drive on your *PC*. 

The board is slightly bigger and has *three* mounting holes.


<img src="images/17_raspberry_pi_5_ssd_shield_t.png" width="80%" height="80%" />

> [!CAUTION]
> When you unpack the *shield*, make sure you identify a *small flat ribbon cable* that comes with it and is easily lost or confused with a stick of tape. 

<img src="images/18_raspberry_pi_5_ssd_cable_t.png" width="80%" height="80%" />

### Mounting Ribbon Cable
In a first step, connect the *ribbon cable* to the *shield*. The connector on the shield has a plastic lock that can be turned up (*unlock*) and down (*lock*).

Turn it *up*, then place one side of the *ribbon cable* into the connector, and secure the cable by turning the plastic lock *down*.

Next, place the *SSD drive* with its *contacts* into the matching connector, and push it in. This procedure is *identical* to previously mounting the *SSD drive* to the *USB adapter*.

<img src="images/25_raspberry_pi_5_shield_mount_t.png" width="80%" height="80%" />

In fact, the *SSD drive* will again tilt upwards until you push it gently down and secure its end with a screw.

### Mounting Spacer Bolts

In order to mount the *M.2 Shield* to the *Raspberry Pi 5*, you need to first add *three spacer bolts* to the board. The bolts come with the *metal housing*. One of the mounting holes remains untouched for now:

<img src="images/26_raspberry_pi_5_ssd_premount_t.png" width="80%" height="80%" />


> [!TIP]
> Do not use the black screws to secure the bolts to the board. Use the smaller bolts that came with the *metal housing*. They serve as *feet* and are required to later mount the board to the metal housing.




<img src="images/raspberry_pi5_housing_mount2_t.png" width="80%" height="80%" />

### Mounting M.2 Shield
Now you can place the *M.2 Shield* on top of the *spacer bolts* and screw it to the *Raspberry Pi 5*.

<img src="images/29_raspberry_pi_5_done_side_t.png" width="80%" height="80%" />

The final step is connecting the *ribbon cable* to the connector on the *Raspberry Pi 5* board. This is a bit fiddly but the connector works similar to the other one and has a plastic lock. *Pull it up* to *unlock* the connector, and *press it back into place* to secure the cable.



<img src="images/27_raspberry_pi_5_cable_connect_t.png" width="80%" height="80%" />

## Adding RTC Battery
If you got yourself an external *battery case* to power the *RTC* (*real time clock*), make sure you push the small switch to the *on* position.

<img src="images/raspberry_pi5_rtc3_t.png" width="30%" height="30%" />

Open the case, and insert a *CR2032* button cell. Next, plug it into the designated connector on the *Raspberry Pi 5 board*.


<img src="images/raspberry_pi5_rtc2_t.png" width="60%" height="60%" />

## Housing
Finally, get the *metal housing parts* ready.

<img src="images/11_raspberry_pi_5_parts_t.png" width="60%" height="60%" />

Insert the assembled *Raspberry Pi 5* into the main housing component with the network connectors facing to its open side.

Screw it to the metal housing using the *larger* four screws.

If you added an *external battery case*, use double-sided tape to fix it to the ethernet jack. Make sure the battery case is not blocking the ventilation.

<img src="images/raspberry_pi_housing4_t.png" width="60%" height="60%" />

Slide in the top cover, and use the *smaller* four screws to screw it to the larger part of the housing - done.

<img src="images/raspberry_pi_housing3_t.png" width="60%" height="60%" />

## Connecting 
To test-drive the *Raspberry Pi*, you need a *network cable* and a *USB C* power supply capable of at least *30W*.

Connect the network cable to the network jack, and connect the power supply to the *USB C* connector.

Once you power on the *Raspberry Pi*, you see *LED lights* blinking as the *SSD drive* is accessed by the *Raspberry Pi 5*.

> [!TIP]
> If you don't like being blind-folded, connect the *Micro HDMI cable* to the display connector right next to the *USB C* connector, and connect the cable to a *computer display*. This was you can see what the *Raspberry Pi 5* is doing.

<img src="images/raspberry_boot1.png" width="80%" height="80%" />


Let the device work for a few minutes: it is automatically booting from your *SSD drive* and installing the software that you *preloaded* before. This part can take up to 10 minutes to complete.

In the end, *Home Assistant* should be up and running. If you have connected a *computer display*, it tells you the assigned IP address:

<img src="images/raspberry_boot2.png" width="80%" height="80%" />


### Web Interface
You do not need to know the *Raspberry* IP address to access *Home Assistant* through a web browser. Open a browser, and enter `homeassistant.local:8123`.

> [!IMPORTANT]
> If this *mDNS name* does not resolve, then this indicates a network issue that you should resolve (see below). *mDNS* is used by *Home Assistant* and *ESPHome* to identify devices, and when it does not work correctly, you are most likely running into many other issues down the road.




#### Network Address Does Not Resolve
The network address `homeassistant.local:8123` uses the *name* and *port* of your instance. The default port is *8123*. If you change the *name* or *port* of your *Home Assistant*, the address needs to be adjusted accordingly. 

The address is based on *mDNS* and works only *locally* (within a network). Many users run *two different networks* without knowing. When you have set up your *WiFi* in *Router Mode* (and not in *Access Point Mode*), the *WiFi nework* is separated from your *wired* network.

If in this case you have connected the *Raspberry Pi 5* using a *network cable*, then you can only use the *mDNS address* from other network devices that are *wired*. It *will not resolve* for computers and devices that are connected to your network using WiFi. 

If *mDNS* resolution fails, you can always use the actual *IP address*, i.e. `192.168.2.127:8123/`. However, this is only a temporary workaround, and you should [fix your network](https://done.land/tools/software/esphome/introduction/addtohomeassistant#checking-network-configuration). *mDNS* is required by many other services (such as *ESPHome*).



#### Obtaining IP Address
By default, and depending on your general network setup, the *Raspberry Pi 5* typically receives its *IP address* dynamically from your *DHCP server*. This means that its *IP address* can change over time. It does not make much sense then to note the *IP address*, or add bookmarks to it.

If you *rely* on using the raw *IP address* to connect, there are two ways to determine it:

* **Computer Display:** hook up a computer display as described above to see the local *Raspberry Pi 5* screen. On the screen, the currently assigned *IP address* is listed.
* **Port Scan:** by default, *Home Assistant* uses port *8123*. By scanning your network for this port, you can retrieve the currently assigned *IP address* within a few seconds. Below is a *PowerShell* script that can do this for you:

````powershell
# install DoneLandTools module from the Microsoft PowerShellGallery.com if you haven't done so lately:
Install-Module -Name DoneLandTools -Scope CurrentUser -Force

# scan your network for port 8123:
Find-NetworkDevice -FindAllWebInterfaces -Port 8123
````

After a few seconds, `Find-NetworkDevice` returns all *IP addresses* that responded to the specified port, and opens these interfaces in your web browser.





> Tags: Raspberry Pi, Assembly, Active Cooler, Fan, mDNS, IP address, Home Assistant

[Visit Page on Website](https://done.land/components/microcontroller/families/raspberry/raspberrypi/assembly/setup?341188060004241323) - created 2024-06-01 - last edited 2024-07-07
