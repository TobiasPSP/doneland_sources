<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Connect Development Board To Computer

> Everything You Need To Know To Successfully Connect A Development Board To Your Computer


You got a new *development board*, and now you want to hook it up to your computer (so you can program it and upload new firmware, or receive output via the *Terminal* window).

Sounds easy: just connect a *USB cable* to the development board and plug its other end into your computer. And often enough it *is* that easy. If it works like this for you, then **you can skip the remainder of this article and move on to the next**.

If however your computer simply won't *recognize* the board, or if you'd like to better understand what goes on exactly when you connect your *development board* to a *computer*, please read on. Most likely, you'll be able to fix your connection issues in no time and learn a lot of new things.



> [!NOTE]
> When things don't work as expected, some users are *quick to blame the board* or brag about the *"rotten quality"* of Asian sellers. That's not so clever. Initial *connection issues* are actually very *common* and most likely caused by *easily fixable user errors*. True hardware defects are extremely rare.










## USB-to-UART Chip
Most microcontrollers do not support *USB* directly. They need a chip that *translates* between the *USB port* of your computer and the *serial interface* of the *microcontroller*.

### External Programmers

These chips are available *separately* in many different form factors and can be used to connect *directly* to microcontrollers, i.e. to occasionally *update the firmware* on devices.

<img src="images/usb_ttl_overview_t.png" width="100%" height="100%" />

They come with a *USB Connector* that is wired to a *USB-to-UART* (aka *USB-to-Serial* or *USB-to-TTL*) chip:

<img src="images/usb_ttl_detail_t.png" width="100%" height="100%" />

On the opposite site, there are connectors for wires that can be connected to the *RX* and *TX* pins of the microcontroller.

> [!TIP]
> If you use external programmers, always make sure to connect *RX* to *TX*, and vice versa. Typically though, you will be using a *built-in* programmer (see below).







### Built-In Programmers

*Development boards* are targeted towards users that need to *frequently* update the firmware because they are *testing* and *playing with microcontrollers*. Wiring up an *external programmer* would be inconvenient.

That's why most *development boards* come with *USB-to-UART* chips that have *USB connectors* built-in:

<img src="images/usb_ttl_builtin_t.png" width="100%" height="100%" />


## Connecting To Computer
When you connect a *development board* (or an *external programmer*) to the USB port of your computer, the *USB-to-Serial* chip should be *immediately recognized* as a newly discovered *Plug&PLay USB device*. The typical sound for a newly discovered USB device should play on your computer when you plug it in.

1. Plug in a *USB cable* into the development board.
2. Once you plug in the other end of the *USB cable* into any *USB port* on your computer, the computer immediately plays the sound *New USB Device Discovered*.
3. In Device Manager (on *Windows*), a new *COM Port* appears.


<img src="images/devmgr.png" width="100%" height="100%" />

The *USB-to-Serial* chip provides a new *serial port* that can be used by your computer software like any other built-in serial port.



> [!CAUTION]
> If your computer does not recognize the *USB-to-Serial* chip when you connect a *development board* to its USB port, and you don't see a new *COM Port* in *device manager*, don't panic: your computer may just be missing a driver. See next section for fixing this issue.




<details><summary>Using PowerShell To Check Port Details</summary><br/>

On *Windows*, you can use the *cmdlet* `Get-ComPortInfo` provided by the *PowerShell module* [DoneLandTools](https://www.powershellgallery.com/packages/DoneLandTools/):

````powershell
# install module from Microsoft PowerShell Gallery (https://www.powershellgallery.com/packages/DoneLandTools/)
Install-Module -Name DoneLandTools -Scope CurrentUser -Force

# run com port diagnosis command
Get-ComPortInfo
````

Here is a sample result emitted by `Get-ComPortInfo`:

````
PS> Get-ComPortInfo


Name          : USB-SERIAL CH340
ComPort       : COM4
Manufacturer  : wch.cn
DriverPath    : C:\WINDOWS\SYSTEM32\DRIVERS\CH341S64.SYS
DriverVersion : 3.50.2014.8
DriverName    : CH341SER_A64

Name          : USB Serial Device
ComPort       : COM77
Manufacturer  : Microsoft
DriverPath    : C:\WINDOWS\SYSTEM32\DRIVERS\USBSER.SYS
DriverVersion : 10.0.19041.3636
DriverName    : usbser (Microsoft USB Serial Driver)
````

On that system, I had connected *two* development boards:

* The *first* set of data represents a connected *ESP8266* at *COM4* using a *custom port driver* located at *C:\WINDOWS\SYSTEM32\DRIVERS\CH341S64.SYS*.
* The *second* set of data represents a connected *ESP32 S2* at *COM77* using the default *Microsoft USB Serial Driver*.

</details>


### Drivers Required?
What if the computer simply *ignores* a connected development board (or *external programmer*) and *does not assign a COM Port* to it? This is solely an issue between your computer and the *USB-to-Serial* chip. There is nothing else involved, especially no configurations or settings in your *IDE*. 

#### Ruling Out Physical Problems

Before looking at driver issues, make sure there are no *physical problems*. *Physical problems are by far the most common causes and simple to fix:


* **Loose Connections:** make sure you *firmly* plugged in the *USB cable*. It should *snap into place*.
* **Bad USB Cable:** this is meant dead serious. Some *USB* cables are made just to supply *power* and do not connect the *data lines*, but the *majority* of cables connects *all pins*. Still, a great many *USB cables* cause *connection issues*, most likely due to low quality, high cable resistance, loose jacks, etc. The best option is to use a *known good* USB cable that you previously successfully used to connect to a breakout board. If you don't have such a cable, make sure you try and test as many different cables as you can get a hold of, and if the cable was indeed the issue, attach a label to the cable that finally worked so you know which one to use in the future.

## Installing Drivers
If you came this far and still have connection issues, now is the time to check for missing drivers.


In order to use the *USB-to-Serial* controller on a board, the *computer* needs a *driver* for it. If a board is not recognized by your computer, and you checked all other causes mentioned above, then most likely it is missing the appropriate driver.

Most *development boards* and *external programmers* use one of these *USB-to-Serial* chips that all work similar:

|  [CH9102](https://www.wch-ic.com/downloads/category/30.html) | [CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) | [CH34x](https://www.wch-ic.com/products/categories/46.html?pid=1) |
| ---  | --- | --- |
| 4Mbps | 12Mbps | 2Mbps |

Their primary difference is the *transfer speed* that determines how long in takes to upload new firmware to the microcontroller.

Here are the steps to fix missing drivers:

1. First try and *identify* the *USB-to-Serial* chip you are trying to connect to. On most development boards, it is the second-largest chip on the PCB. Occasionally, though, this chip can be *unmarked*, or its markings are unreadable.
2. If you *do know* the type of chip, click on the appropriate header in the table above, or use the table below, to visit the chips' manufacturer driver downloads section. Download the driver for your computer operating system. If you *don't know* the chip type, you go by *trial and error* and install one driver at a time. You may end up installing all three drivers (which isn't a bad thing).
3. On *Windows*, right-click the downloaded driver archive, choose *Properties*, then *Unblock* the file. 
4. Extract the archive and run the installer.
5. Once the driver has been installed, try again connecting the *development board*. Most likely, its *USB-to-Serial* chip will now be recognized, and you get a new *serial port*.

| Chip | Driver Download |
| --- | --- |
| CH9102 | [https://www.wch-ic.com/downloads/category/30.html](https://www.wch-ic.com/downloads/category/30.html) | 
| CP210x | [https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) |
| CH34x | [https://www.wch-ic.com/products/categories/46.html?pid=1](https://www.wch-ic.com/products/categories/46.html?pid=1) |

### Hardware Issues
Rarely, the *USB-to-Serial*-Chip and the *USB connection* are fine, and *still* the development board won't respond correctly.

If you have installed *all* drivers, restarted the computer, tried different *USB cables* and made sure all connections were plugged in tightly, then (and *only* then) it is time to consider a *board defect*.

#### Verify Board Defect

To verify, try connecting a different development board (ideally of the same type requiring the same *drivers*). If the new board connects fine, you ruled out the most common causes for connection issues (USB cable problem, missing driver), and it most definitely is a *board issue*.

> [!NOTE]
> Even the *cheapest development boards* typically work great **provided** these boards were *assembled right*. One reason for cheap prices is poor *quality control*: faulty assembly goes unnoticed, and roughly out of a hundred boards may have a hardware issue. Then again, you often get ten *no-name* boards for the price of one from a renown brand. Even if one out of these has a defect, it's still a good choice for hobbyists that are willing to test boards themselves.



<img src="images/solder_defect1_t.png" width="100%" height="100%" />



Here are the typical two *hardware defects*:

* **Bad USB Connectors:** occasionally, the *USB connector* is not firmly soldered onto the *PCB*, or the connector itself is slightly off specifications, causing loose contacts. 
* **Bad Soldering:** drops of *solder* may have caused a *short circuit* on some pins. **When the board *gets warm* quickly after supplying it with power, immediately disconnect it and closely examine all solder spots.**

<img src="images/solder_defect_detail.png" width="100%" height="100%" />












> Tags: USB, UART, TTL, Connect, Port, COM

[Visit Page on Website](https://done.land/components/microcontroller/firststeps/connecttopc?505691051225241424) - created 2024-05-03 - last edited 2024-05-24
