<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Connect Development Board To Computer

> Successfully Connect A Development Board To Your Computer

You’ve just received a new *development board* and want to connect it to your computer for programming, uploading new firmware, or receiving output through the *Terminal* window.

The process may seem straightforward: simply connect a *USB cable* to the development board and plug the other end into your computer. In many cases, it really is that simple. If it works seamlessly for you, **you can skip the rest of this article and move on to the next steps**.

However, if your computer fails to *recognize* the board, or if you're curious about what happens behind the scenes when you connect your *development board* to a *computer*, read on. You’re likely to resolve any connection issues quickly and gain a deeper understanding of how the system works.

> [!NOTE]
> If things don’t go as expected, avoid blaming the board or complaining about the *“poor quality”* of some sellers. Initial *connection issues* are common and often stem from *easily fixable user errors*. True hardware defects are rare.

## USB-to-UART Chip

Most microcontrollers don’t have built-in *USB* support. Instead, they rely on a chip that acts as a *translator* between the *USB port* on your computer and the *serial interface* on the microcontroller.

### External Programmers

These translator chips are available *separately* in various form factors and can be used to connect *directly* to microcontrollers for occasional *firmware updates*.

<img src="images/usb_ttl_overview_t.png" width="100%" height="100%" />

The chip typically includes a *USB connector* that connects to a *USB-to-UART* (also known as *USB-to-Serial* or *USB-to-TTL*) chip:

<img src="images/usb_ttl_detail_t.png" width="50%" height="50%" />

On the other side, you’ll find connectors that can be wired to the *RX* and *TX* pins of the microcontroller.

> [!TIP]
> When using external programmers, always connect *RX* to *TX*, and vice versa. However, in most cases, you will use a *built-in* programmer (explained below).

### Built-In Programmers

*Development boards* are designed for users who need to *frequently* update firmware due to testing or experimenting with microcontrollers. Wiring up an *external programmer* would be cumbersome in this case.

That’s why most *development boards* come with *USB-to-UART* chips that feature built-in *USB connectors*:

<img src="images/usb_ttl_builtin_t.png" width="80%" height="80%" />

## Connecting To Computer

When you connect a *development board* (or an *external programmer*) to your computer's USB port, the *USB-to-Serial* chip should be *automatically recognized* as a new *Plug & Play USB device*. You’ll typically hear a sound indicating that a new USB device has been detected.

1. Plug the *USB cable* into the development board.
2. When you connect the other end of the *USB cable* to a *USB port* on your computer, you should hear the *New USB Device Discovered* sound.
3. In *Device Manager* (on *Windows*), you’ll see a new *COM Port* listed.

<img src="images/devmgr.png" width="80%" height="80%" />

The *USB-to-Serial* chip provides a new *serial port* that can be used by your computer software just like any built-in serial port.

> [!CAUTION]
> If your computer doesn’t recognize the *USB-to-Serial* chip when connecting the *development board* to a USB port, and no new *COM Port* appears in *Device Manager*, don’t panic—your computer may be missing the necessary driver. Refer to the next section for guidance on how to resolve this.

<details><summary>Using PowerShell To Check Port Details</summary><br/>

On *Windows*, you can use the *cmdlet* `Get-ComPortInfo` from the *PowerShell module* [DoneLandTools](https://www.powershellgallery.com/packages/DoneLandTools/):


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

* The *first* set of data represents a connected *ESP8266* at *COM4*, using a *custom port driver* located at *C:\WINDOWS\SYSTEM32\DRIVERS\CH341S64.SYS*.
* The *second* set of data represents a connected *ESP32 S2* at *COM77*, using the default *Microsoft USB Serial Driver*.

</details>

### Drivers Required?

What if the computer simply *ignores* a connected development board (or *external programmer*) and *does not assign a COM Port* to it? This is an issue between your computer and the *USB-to-Serial* chip, with no involvement from your *IDE* configuration or settings.

#### Ruling Out Physical Problems

Before delving into driver issues, ensure there are no *physical problems*. These are by far the most common causes and are usually easy to fix:

* **Loose Connections:** Ensure the *USB cable* is *firmly* plugged in. It should *snap into place* securely.
* **Bad USB Cable:** Yes, this is a real concern. Some *USB cables* are designed only to supply *power* and don't connect the *data lines*. Most cables should connect *all pins*, but many poor-quality cables, with high resistance or loose connectors, can cause *connection issues*. The best solution is to use a *known good* USB cable that you’ve successfully used with a breakout board. If you don't have such a cable, try several different cables. If one works, label it to identify the best cable for future use.

## Installing Drivers

If you've reached this point and still face connection issues, it's time to check for missing drivers.

In order to use the *USB-to-Serial* controller on a board, your *computer* needs the appropriate *driver*. If the board isn't recognized, and you've ruled out all other causes, the issue is likely a missing driver.

Most *development boards* and *external programmers* use one of these *USB-to-Serial* chips, which work similarly:

|  [CH9102](https://www.wch-ic.com/downloads/category/30.html) | [CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) | [CH34x](https://www.wch-ic.com/products/categories/46.html?pid=1) |
| ---  | --- | --- |
| 4Mbps | 12Mbps | 2Mbps |

The primary difference between these chips is the *transfer speed*, which impacts how quickly you can upload new firmware to the microcontroller.

Here are the steps to resolve missing drivers:

1. First, *identify* the *USB-to-Serial* chip on your development board. It’s usually the second-largest chip on the PCB. However, some boards may have unmarked chips or unreadable markings.
2. If you *know* the chip type, click the appropriate link in the table above or use the table below to visit the manufacturer's driver download page. Download the driver compatible with your operating system. If you're unsure about the chip type, try installing one driver at a time. You might end up installing all three drivers (which is generally fine).
3. On *Windows*, right-click the downloaded driver archive, select *Properties*, and click *Unblock* on the file.
4. Extract the archive and run the installer.
5. After installation, try reconnecting the *development board*. Most likely, the *USB-to-Serial* chip will now be recognized, and a new *serial port* will appear.

| Chip | Driver Download |
| --- | --- |
| CH9102 | [https://www.wch-ic.com/downloads/category/30.html](https://www.wch-ic.com/downloads/category/30.html) | 
| CP210x | [https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) |
| CH34x | [https://www.wch-ic.com/products/categories/46.html?pid=1](https://www.wch-ic.com/products/categories/46.html?pid=1) |

### Hardware Issues

In rare cases, even with *correct drivers*, *restarting the computer*, trying different *USB cables*, and ensuring all connections are secure, the development board may still fail to respond properly.

If you've exhausted all these steps, it may be time to consider the possibility of a *board defect*.

#### Verify Board Defect

To verify if there is a board defect, try connecting a different development board (ideally, of the same type requiring the same *drivers*). If the new board connects successfully, you've ruled out the most common causes for connection issues (USB cable problem, missing driver), and it’s most likely a *board issue*.

> [!NOTE]
> Even the *cheapest development boards* typically work well **provided** they were *assembled correctly*. The low cost often stems from poor *quality control*, meaning that defective boards can slip through unnoticed. Typically, out of a hundred boards, one or two might have a hardware issue. However, you often get ten *no-name* boards for the price of one from a renowned brand. Even if one of them has a defect, it can still be a great deal for hobbyists who are comfortable testing and troubleshooting boards themselves.

<img src="images/solder_defect1_t.png" width="50%" height="50%" />

Here are the two most common *hardware defects*:

* **Bad USB Connectors:** Occasionally, the *USB connector* is not properly soldered onto the *PCB*, or it may be slightly off-spec, leading to loose or unreliable connections.
* **Bad Soldering:** Solder drops can cause *short circuits* on some pins. If the board *heats up* quickly after powering it on, immediately disconnect it and inspect all solder joints closely.


<img src="images/solder_defect_detail.png" width="80%" height="80%" />



> Tags: USB, UART, TTL, Connect, Port, COM

[Visit Page on Website](https://done.land/components/microcontroller/firststeps/connecttopc?505691051225241424) - created 2024-05-03 - last edited 2025-01-05
