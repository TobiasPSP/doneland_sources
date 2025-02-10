<img src="/assets/images/butler.jpg" width="80%" height="80%" />
 
# PowerShell

> PowerShell Is A Cross-Platform Scripting Language - Perfect For Creating Tools And Custom Commands


**PowerShell** is a modern scripting language [available](https://github.com/PowerShell/PowerShell/releases) cross-platform for *Windows*, *Linux*, *MacOS* and many other operating systems.

## Installing PowerShell

On *Windows*, you do not necessarily need to install **PowerShell**: *Windows PowerShell* is part of the operating system: press `Win`+`R` to open the *Run* dialog.

<img src="images/dialog_run_powershell.png" width="50%" height="50%" />

Enter `powershell` and press `ENTER`. A *blue* console window opens and is labeled *Windows PowerShell*. This is your *built-in* *Windows* **PowerShell**. It runs **PowerShell** *version 5.1*. 

<img src="images/windowspowershell_console.png" width="80%" height="80%" />


### PowerShell 7: Cross Platform

On other operating systems (and also on *Windows* if you want to use the *latest* **PowerShell** version), visit [PowerShell Releases](https://github.com/PowerShell/PowerShell/releases). 

Scroll down until you see the item *Assets*. Click to expand.

<img src="images/powershell_assets.png" width="100%" height="100%" />

This opens a list of ready-to-download installation binaries, available for many operating systems and in many formats (*tar.gz*, *zip*, *msi*, *pkg*).

> [!CAUTION]
> Make sure you select the appropriate operating system. For *Windows*, this would be the suffix *win-x64*.

When you download an *archive* format such as *tar.gz* or *zip*, you can use **PowerShell** as a *portable app*. Here is how:

1. Download the appropriate archive file
2. *Unblock* the downloaded file *before* you unpack it: in *Windows*, right-click the downloaded archive file, choose *Properties*, then check *Unblock*.
3. Open the folder with the unpacked files, and launch `pwsh.exe`

The cross-platform **PowerShell** displays as a *black* console. 



<img src="images/powershell_console.png" width="80%" height="80%" />


> [!NOTE]
> **PowerShell** is actively developed: its *versions* increment rapidly. *Version 7.4.0* as depicted above is probably long outdated and replaced by a higher version number when you read this. 


## Install DoneLandTools

It's extremely *simple* to add new *Done.Land* **PowerShell** commands to your *PowerShell*: the module *DoneLandTools* is available for installation from the Microsoft [PowerShellGallery](https://www.powershellgallery.com/packages/DoneLandTools).

> **PowerShell** comes with a basic set of *general-purpose* commands. You extend them for your *specific needs and use cases* by adding additional *modules* that provide *more specific* commands.

To download and use the *DoneLandTools*, run this line:

```powershell
Install-Module -Name DoneLandTools -Scope CurrentUser -Force
```

> [!TIP]
> The switch `-Force` omits confirmation dialogs. If you'd rather see them, omit `-Force`. Modules are downloaded from the *Microsoft PowerShell Gallery*. Since this is a *public* place, and *Microsoft* is not taking responsibility for any materials you download from there, you need to confirm your choice.

### Module Installation Fails

Should the above command be unable to download the module, check these items:

* **Internet:** obviously you need to have internet access. Try visiting the [PowerShell Gallery](https://www.powershellgallery.com/) directly. 
* **Permissions:** within company networks, access to the gallery may be restricted.
* **Conflicts:** when an *existing* module added commands with the *same name* as commands in *DoneLandTools*, a *name conflict* would occur, and the new module cannot be installed. Either remove the conflicting module that is already present, or add the switch parameter `-AllowClobber` to install the *DoneLandTools* module anyway.
* **Outdated:** *Windows PowerShell* may use outdated libraries. Try updating them using this command: `Install-Module -Name PowerShellGet -Scope CurrentUser -Force`

## DoneLand Commands

To see the new **PowerShell** commands the *DoneLandTools* module provides, run this:

```powershell
Get-Command -Module DoneLandTools
```

```
CommandType Name                      Version Source
----------- ----                      ------- ------
Function    Find-NetworkDevice        1.3.0   DoneLandTools
Function    Get-AntennaLength         1.3.0   DoneLandTools
Function    Get-ComPortInfo           1.3.0   DoneLandTools
Function    Get-IpRange               1.3.0   DoneLandTools
Function    Get-LedResistor           1.3.0   DoneLandTools
Function    Get-LedStripFramerateInfo 1.3.0   DoneLandTools
Function    Get-MyIpAddress           1.3.0   DoneLandTools
Function    Invoke-ForeachParallel    1.3.0   DoneLandTools
Function    Show-Fat32Converter       1.3.0   DoneLandTools
Function    Test-Ping                 1.3.0   DoneLandTools
Function    Test-PingRange            1.3.0   DoneLandTools
Function    Test-Port                 1.3.0   DoneLandTools
Function    Test-PortRange            1.3.0   DoneLandTools
```

> [!NOTE]
> The **PowerShell** module *DoneLandTools* is a work in progress. When you download and use it, it may contain *more* then the functions showed here. To *check for updates* and always use the *latest* version, you may want to occasionally run `Update-Module -Name DoneLandTools`.

### Exploring New Commands

All commands come with *help*. To i.e. find out what `Get-LedStripFramerateInfo` can do for you, run the command like this:

```powershell
 Get-LedStripFramerateInfo -?
```

```
NAME
    Get-LedStripFramerateInfo

SYNOPSIS
    Calculates the maximum frame rate possible for a LED strip or the maximum LED that can be used for a desired frame
    rate


SYNTAX
    Get-LedStripFramerateInfo -Framerate <Int32> [-LedPerMeter <Int32>] [-ResetTimeMicroSec <Int32>]
    [-IncludeWhiteLed] [-DataRateKhz <Int32>] [<CommonParameters>]

    Get-LedStripFramerateInfo -LedPerMeter <Int32> [-ResetTimeMicroSec <Int32>] [-IncludeWhiteLed] [-DataRateKhz
    <Int32>] -StripLengthCm <Double> [<CommonParameters>]

    Get-LedStripFramerateInfo [-ResetTimeMicroSec <Int32>] [-IncludeWhiteLed] [-DataRateKhz <Int32>] -TotalLedCount
    <Int32> [<CommonParameters>]


DESCRIPTION
    In WS2182B and similar strings of LED, the one-wire data line has a maximum data transmission rate.
    This command can calculate two things:
    - given the number of LED (or the length and type of LED string), it calculates the maximum possible frame rate
    - given the framerate, it calculates the maximum possible number of LED that you can string together


RELATED LINKS
    URLs to related sites
    The first link is opened by Get-Help -Online Get-LedStripInfo

REMARKS
    To see the examples, type: "get-help Get-LedStripFramerateInfo -examples".
    For more information, type: "get-help Get-LedStripFramerateInfo -detailed".
    For technical information, type: "get-help Get-LedStripFramerateInfo -full".
    For online help, type: "get-help Get-LedStripFramerateInfo -online"
```

This is the *complete* but sometimes *overwhelming* help information. 

> [!TIP]
> At the *bottom* of the help text in the section *Remarks*, you find additional ways of retrieving specific help information that may be more suitable for you. Run `help Get-LedStripFramerateInfo -Online` to open *this* page in your browser.

### Practical Examples

Much more fun are *examples* that show distinct use cases on how to actually run the command. Run this to get the examples for a command: 

```powershell
Get-Help Get-LedStripFramerateInfo -Examples
```

Now you get a list of fun examples that you can try:

```
NAME
    Get-LedStripFramerateInfo

SYNOPSIS
    Calculates the maximum frame rate possible for a LED strip or the maximum LED that can be used for a desired frame
    rate

    -------------------------- EXAMPLE 1 --------------------------

    PS C:\>Get-LedStripFramerateInfo -TotalLedCount 100

    Calculates the maximum framerate achievable for 100 RGB LEDs in a string:

    LedCount Type Framerate DataTime (us)
    -------- ---- --------- -------------
         100 RGB        305       0.00328


    -------------------------- EXAMPLE 2 --------------------------

    PS C:\>Get-LedStripFramerateInfo -TotalLedCount 100 -IncludeWhiteLed

    Calculates the maximum framerate achievable for 100 RGBW LEDs in a string (including separate white, 32 instead of 24 bit):

    LedCount Type Framerate DataTime (us)
    -------- ---- --------- -------------
         100 RGBW       234       0.00428


    -------------------------- EXAMPLE 3 --------------------------

    PS C:\>60,90,120,144 | Get-LedStripFramerateInfo -StripLengthCm 150

    Calculates the maximum framerates for a strip of 150cm length and different LED/m:

    LedCount Type Framerate DataTime (us)
    -------- ---- --------- -------------
      90     RGB  336       0.00298
     135     RGB  231       0.00433
     180     RGB  176       0.00568
     216     RGB  148       0.00676


    -------------------------- EXAMPLE 4 --------------------------

    PS C:\>Get-LedStripFramerateInfo -Framerate 60

    Determines the maximum number of LED that can be used to achieve a 60Hz frame rate:

    LedCount Type StripType StripLengthCm
    -------- ---- --------- -------------
         546 RGB  n/a       n/a


    -------------------------- EXAMPLE 5 --------------------------

    PS C:\>Get-LedStripFramerateInfo -Framerate 30 -LedPerMeter 144

    Determines the maximum length for a LED strip using 144 LED/m to achieve a 30Hz frame rate:

    LedCount Type StripType StripLengthCm
    -------- ---- --------- -------------
        1102 RGB  144LED/m          765.3


    -------------------------- EXAMPLE 6 --------------------------

    PS C:\>200,100,60,30,15 | Get-LedStripFramerateInfo -LedPerMeter 144

    Calculates the maximum length of a 144LED/m LED strip for various frame rates:

    LedCount Type StripType StripLengthCm
    -------- ---- --------- -------------
         157 RGB  144LED/m            109
         324 RGB  144LED/m            225
         546 RGB  144LED/m          379.2
        1102 RGB  144LED/m          765.3
        2213 RGB  144LED/m         1536.8
```


## Discovering Network Devices
*WiFi*-enabled wireless development boards get an *IP address* assigned. Typically, *DHCP* is used: the assigned *IP address* can *change* over time.

That makes it hard to connect to the device. While there are often *specific* work-arounds such as *enabling mDNS*, or implementing *dash boards* that are hosted on *servers* like *HomeAssistant*, if you want to find out the *IP address* of your develoipment board, you can always use a *brute force* approach: scan your network.

Microcontroller boards typically respond to *ICMP ping requests*. Firmware that exposes a *web interface* (such as *ESPEasy* and others) can also be identified by testing *port 80*.

### Range-Pinging Devices

*DoneLandTools* makes it simple to scan your network (scanning by default with 64 threads simultaneously to speed it up). Issue this command:

````powershell
Find-NetworkDevice
````

The command figures out your active network range of possible *IP Addresses*, then asks you to *turn off* your device. This way, the tool can perform a *baseline scan*, picking up all the *other* devices that respond to *ping*:

````
[1] Make sure the device is currently NOT TURNED ON. TURN IT OFF if necessary.
Press ENTER when you are ready.
````

Once you turned off your device, press `ENTER`. Now the baseline scan is performed which typically takes less than *20sec* in a typical network range of 256 IP addresses, but can also take considerably longer if you use a larger *subnet mask* (mask *255.255.255.0* is recommended for home networks).

Next, the tool asks you to *turn on* your device. Once you have done this, press `ENTER` again. Now the scan is repeated.

````
[2] NOW TURN ON the device.                                                                                       Press ENTER when you are ready. 
````

Once the second scan has completed, the tool returns the *IP addresses* that were *not* present in the initial scan:

````
192.168.68.120
````

> [!TIP]
> If the results are incorrect, then your devices may need a *longer timeout* to respond. You may then want to run the tool with an increased timeout like so:  `Find-NetworkDevice -Timeout 10000`. The scans now take a bit longer, but the results are more reliable. When you also add `-Verbose`, the tool outputs how much time it took to scan your network.

````
[1] Make sure the device is currently NOT TURNED ON. TURN IT OFF if necessary.
Press ENTER when you are ready.

VERBOSE: Initial baseline scan took 12.5 seconds.
[2] NOW TURN ON the device.
Press ENTER when you are ready.

VERBOSE: Total scan time was 26.2 seconds. 1 devices found.
192.168.68.124
````

### Finding Web Interfaces
An even more reliable and convenient way is to ask the tool to look for *web interfaces* the device may implement. This of course works only if the *firmware* of your microcontroller indeed exposes a web interface.

````powershell
Find-NetworkDevice -OpenInBrowser -Verbose
````

The sequence is the same: you are first asked to *turn off* the device to perform a baseline scan, then asked to *turn the device on* to perform the second scan.

The tool then reports all *IP addresses that respond to *port 80*, and also opens the found *web interfaces* in your browser.

````
[1] Make sure the device is currently NOT TURNED ON. TURN IT OFF if necessary.
Press ENTER when you are ready.
VERBOSE: Initial baseline scan took 17.5 seconds.
[2] NOW TURN ON the device.
Press ENTER when you are ready.

VERBOSE: Total scan time was 34.6 seconds. 1 devices found.
192.168.68.124
````
Here is the discovered *web interface* provided by an *ESPEasy* node found in this example:

<img src="images/webinterface.png" width="100%" height="100%" />


### Finding All Web Interfaces
In the previous examples, the tool always performed *two* network scans: one *before* the device was turned on, and one *after* it became online. This way, the tool can filter out all *IP addresses* from other devices that may also be present in your network.

If you cannot turn your device off (maybe you have no physical access), or if you want to see *all* web interfaces from *every* device available in your network, you can also run the command with just *one* scan:

````powershell
Find-NetworkDevice -FindAllWebInterfaces -Verbose
````

The tool now immediately performs a *network scan*. It then outputs *all IP addresses* that responded to *port 80*:

````
VERBOSE: Total scan time was 17.3 seconds. 7 devices found.
192.168.68.112
192.168.68.118
192.168.68.124
192.168.68.128
192.168.68.111
192.168.68.249
192.168.68.250
````

Since you cannot judge by the *IP address* what *kind* of device is using it, the tool also *opens all IP addresses* in your *browser*.

Do not be surprised to see a lot of third-party devices showing up: many devices expose secret web interfaces that you find this way.


<img src="images/webinterface_many_t.png" width="100%" height="100%" />

## Formatting SD Cards
*DoneLandTools PowerShell Commands* can help you properly format *SD Card Media* on *Windows* with the command `Show-Fat32Converter`.


### FAT32 on Large SD Cards
By default, *Windows* cannot format modern *SD Card media* with the `FAT32` file system anymore: any SD Card larger than *4GB* can only be formatted using the `exFAT` or `NTFS` file system.

That's a problem since most *SD Card Reader modules* and *MP3 Players* require the `FAT32` file system. They do not work with SD Cards formatted with `exFAT`. 

Your options are to either try and get a smaller SD Card (<4GB), or to use the PowerShell command `Show-Fat32Converter` that is part of *DoneLandTools*.

> [!IMPORTANT]
> It won't help to convert a *64GB* SD Card to `FAT32` when the device can only handle smaller cards. So always check the requirements of the device where you want to use the SD Card. The popular MP3 player *DFPlayer Mini* for example handles SD Cards of up to *32GB*.

### Converting Any Media To FAT32
Here is how you convert SD Cards of any size to `FAT32`:

1. Make sure the SD Card does not contain any valuable data. Insert it into your PC. *Windows Explorer* shows a new drive representing your SD Card Media.
2. Launch *PowerShell*, for example by pressing `Win`+`R`, then entering `powershell` into the *Run* dialog.
3. In the PowerShell console, enter `Show-Fat32Converter`, and press `ENTER`.
4. A dialog opens, and you can now select the drive that you want to convert to `FAT32`, and define a new volume label (optional).
5. Click `Format`, and follow the instructions. A few seconds later, the media is converted to `FAT32`.


<img src="images/dfplayermini_format2.png" width="100%" height="100%" />


> Tags: PowerShell, Module, Install, Tools, FAT32, Convert, SD-Card

[Visit Page on Website](https://done.land/tools/powershell?911673031121245307) - created 2024-03-21 - last edited 2025-02-09
