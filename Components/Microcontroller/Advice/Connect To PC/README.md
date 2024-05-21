<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Connect Development Board To Computer

> Everything You Need To Know To Successfully Connect A Development Board With Your Computer


You got a new *development board*, and now you want to hook it up to your computer (so you can program it and upload new firmware, or receive output via the *Terminal* window).

Sounds easy: just connect a *USB cable* to the development board and plug its other end into your computer. And often it *is* this easy.

However, when your computer stubbornly won't *recognize* the board, things quickly become *frustating* as there are no *error messages* or other indicators that would tell you what is amiss. That's why it's a good thing to *understand* how the development board is recognized by a computer, and what the steps are to *diagnose and correct* connection issues.

## Overview
In order to *communicate* with a development board, typically a *USB port* is used *for convenience*. In *reality* though, most microcontrollers use a simple *serial* interface for communications. Only the latest *ESPxxxx* modules support direct communication via *USB*.

In any respect, *connecting issues* are *not related to a particular IDE you may be using*. *Connecting issues* are *always* an issue between the development board and your computer. This makes *diagnosis* easy because you can *ignore* the *ISE*.

### Test Connection
This is how *connecting* a development board to a computer *should* look like:

1. You plug in a *USB cable* into the development board.
2. Once you plug in the other end of the *USB cable* into any *USB port* on your computer, the computer immediately plays the sound *New USB Device Discovered*.
3. In Device Manager (on *Windows*), a new *COM Port* appears.


<img src="images/devmgr.png" width="100%" height="100%" />

#### Using PowerShell To Check Port Details
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

* The *first* record represents a connected *ESP8266* at *COM4* using a *custom port driver* located at *C:\WINDOWS\SYSTEM32\DRIVERS\CH341S64.SYS*.
* The *second* record represents a connected *ESP32 S2* at *COM77* using the default *Microsoft USB Serial Driver*.

<details><summary>Testing COM Port Connection</summary><br/>


Once the *development board* is recognized by the computer and got a *COM Port* assigned, you are good to go. 

*IDEs* like *Arduino IDE* and *platformio* use generic tools to communicate to the development board over the assigned COM port.

*ESPxxxx*-based development boards i.e. are managed by the tool *esptool* from its vendor *Espressif*. 

You can freely download and install this tool stand-alone if you like. Once there is a *COM Port* that you can use to communicate with a development board, tools like *esptool* can gather important detail information about a particular board.

On my *COM4*, I connected a *D1 Mini ESP8266* development board. With the command below, *esptool* examines the *Flash memory* of this board and reports back its total physical size, among other details:

````
PS> esptool --port COM4 flash_id
esptool.py v4.7.0
Serial port COM4
Connecting....
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting....
Detecting chip type... ESP8266
Chip is ESP8266EX
Features: WiFi
Crystal is 26MHz
MAC: 08:3a:8d:cc:dd:a9
Uploading stub...
Running stub...
Stub running...
Manufacturer: 5e
Device: 4016
Detected flash size: 4MB
Hard resetting via RTS pin...
````

Likewise, on my *COM port 77* I connected a *ESP32 S2 Mini* board. The same command can query this microcontroller as well:

````
PS> esptool --port COM76 flash_id
esptool.py v4.7.0
Serial port COM76
Connecting....
Detecting chip type... Unsupported detection protocol, switching and trying again...
Detecting chip type... ESP32-S2
Chip is ESP32-S2FNR2 (revision v1.0)
Features: WiFi, Embedded Flash 4MB, Embedded PSRAM 2MB, ADC and temperature sensor calibration in BLK2 of efuse V2
Crystal is 40MHz
MAC: 80:65:99:fc:f4:d0
Uploading stub...
Running stub...
Stub running...
Manufacturer: 20
Device: 4016
Detected flash size: 4MB
Flash type set in eFuse: quad (4 data lines)
Hard resetting via RTS pin...
````

Without delving too much into this topic, *esptool* and other console commands are *low level tools* that may require a bit of background information. For the *ESP S2* for example, due to the way how it connects to *USB*, it is necessary to query *COM77* (triggering a port exception), and then query *COM76*.

</details>

### No Device Detected

What if the computer *ignores* a connected development board and *does not assign a COM Port* to it? That's a *show stopper*. Without a *COM Port*, you *cannot communicate* with the board.

> [!IMPORTANT]
> You **must** solve this issue first - before looking into other configurations and settings. There **must** be a **COM port** (on *Windows*) showing up in *Device Manager*.

The two most common issues for this behavior:

* **Bad USB Cable:** this is meant dead serious. Some *USB* cables are made just to supply *power* and do not connect the *data lines*, but the *majority* of cables connects *all pins*. Still, a great many *USB cables* cause *connection issues*, most likely due to low quality, high cable resistance, loose jacks, etc. The best option would be to use a *known good* USB cable that you previously successfully used to connect to a breakout board. Make sure you try and test as many different cables as you can get a hold of, and if the cable was indeed the issue, attach a label to the cable that finally worked.
* **Missing Driver:** On *Windows*, missing drivers are not a very common issue. *Windows* ships with the most common drivers. However, if the breakout board is not recognized even though you tried multiple *USB cables*, you should find out what kind of driver the development board requires, and install it.







> Tags: USB, UART, TTL, Connect, Port, COM

[Visit Page on Website](https://done.land/components/microcontroller/advice/connecttopc?359846051021241839) - created 2024-05-20 - last edited 2024-05-20
