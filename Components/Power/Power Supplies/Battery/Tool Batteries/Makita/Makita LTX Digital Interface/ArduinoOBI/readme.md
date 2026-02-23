<img src="/assets/images/lightning.png" width="100%" height="100%" />

# ArduinoOBI 

> Diagnostic Tool for Makita LTX Batteries to Test, Query, and Unlock

This is the original implementation of a Makita diagnostic dongle (called **[ArduinoOBI](https://github.com/mnh-jansson/open-battery-information/tree/main/ArduinoOBI)**) that connects a Makita LTX battery to a PC.  It uses the original [Open Battery Information](https://github.com/mnh-jansson/open-battery-information/tree/main) resources and runs on Arduino UNO/Arduino Nano.

<img src="images/makita_obi_inuse_t.webp" width="50%" height="50%" />

This [YouTube video](https://www.youtube.com/watch?v=kUg9jWvf5FM) explains how to build the adapter and provides free [3D printing files](https://shorturl.at/W719g) for a matching enclosure.

## Overview

The original **[ArduinoOBI](https://github.com/mnh-jansson/open-battery-information/tree/main/ArduinoOBI)** was the first adapter capable of querying Makita LTX batteries and also **unlocking** batteries that the BMS has locked.  

It is based on the extensive reverse‑engineering work by Martin Jansson and uses an *Arduino Nano* to bridge the Makita LTX 1‑Wire interface to a PC over USB.

If you want to build and use this adapter to manage your Makita batteries, here are the steps:

1. **Hardware:**      
  Build the actual adapter that connects to the Makita battery on one end, and to your PC via USB on the other end.    

    <img src="images/makita_obi_inuse_t.webp" width="50%" height="50%" />
2. **Arduino Software (aka Firmware):**  
  Upload the *ArduinoOBI* firmware to your Arduino board. Use your development environment of choice.   
3. **PC Software:**    
  Use either the open-source software [OpenBatteryInformation.exe](https://github.com/mnh-jansson/open-battery-information/releases/latest), or the underlying [Python script](https://github.com/mnh-jansson/open-battery-information/tree/main/OpenBatteryInformation) directly.    

  
    <img src="images/obi_application_bl1860B.webp" width="100%" height="100%" />


## Step 1: Building Adapter

To build the adapter that connects to your PC to a Makita battery, only a handful of low‑cost parts are required:

* **Arduino Nano clone:**  
  A low‑cost Arduino Nano‑compatible board (around €1.50) works fine, yet you can also use an original Arduino UNO or Nano of course.    


  <img src="images/arduino_nano_clone_top_t.webp" width="30%" height="30%" />

* **Connector cable:**  
  Use a [Makita charger replacement connector cable](https://www.google.com/search?q=aliexpress+makita+charger+connector) to interface cleanly with the battery.

  <img src="images/makita_obi_cable_t.webp" width="30%" height="30%" />

  


* **Other items:**     
  You need two 4.7 kΩ resistors and a spade connector, keeping the total hardware cost to under €5.

### Step‑By‑Step Instructions

Rather than repeating the complete build process here, follow the [original instructions](https://github.com/mnh-jansson/open-battery-information/tree/main/ArduinoOBI) and/or watch this [YouTube video](https://www.youtube.com/watch?v=kUg9jWvf5FM).

### Wiring Makita Connector

While the source instructions are mostly great, they do not clearly illustrate the orientation and wiring of the yellow connector. To clarify, here is the pin assignment:

<img src="images/makita_ltx_plug_connector.webp" width="50%" height="50%" />

The two active pins connect to Arduino Nano GPIOs `D6` and `D8`:

| GPIO | Connect to |
| --- | --- |
| `D6` | `1-Wire` |
| `D8` | `Enable` |

<img src="images/makita_obi_wiring_arduino_turned.webp" width="30%" height="30%" />

<img src="images/arduino_obi_connection.webp" width="100%" height="100%" />

<img src="images/makita_obi_wiring2_t.webp" width="40%" height="40%" />

### Pull‑Up Resistors

Both `D6` and `D8` must be pulled up to `5V` using 4.7 kΩ resistors to meet the 1‑Wire electrical requirements. When soldering, ensure the resistor leads cannot short to nearby components or tracks on the Arduino board.

### Ground Connection

The Arduino `GND` pin needs to be connected to the Makita battery `-` terminal to share a common reference for the 1‑Wire interface. A crimped spade connector, as demonstrated in the YouTube build video, is a practical way to attach to the battery terminal.

## Part 2: Uploading Firmware to your Adapter

The original author and also the [YouTube video](https://www.youtube.com/watch?v=kUg9jWvf5FM) uses the *Arduino IDE* to compile and upload the firmware to the Arduino Nano or UNO.  

I prefer *platform.io*, so here is what I did:

1. [download the ready‑to‑build PlatformIO ArduinoOBI project](materials/arduinoobi.zip)
2. Open the folder with the extracted content in *VSCode*.
3. In the *VSCode platformio extension*, click *Build*.

Here are the steps in more detail:

> [!NOTE]  
> The steps below assume you are already familiar with *PlatformIO* and *VS Code*.

### Manually Creating PlatformIO Project

In *PlatformIO*, create a new project and select your target microcontroller. Once the project is created, adjust it in the file explorer:

1. Open `platform.ini` and review the auto‑generated settings. For an *Arduino Nano Clone*, use:

    ```
    [env:nano_old]
    platform  = atmelavr
    board     = nanoatmega328
    framework = arduino
    upload_speed = 57600
    ````

2. In your browser, open [Arduino OBI/main.cpp](https://github.com/mnh-jansson/open-battery-information/blob/v0.2.2/ArduinoOBI/src/main.cpp) and copy the complete source code.  
3. In VS Code, open `src\main.cpp` and replace its contents with the copied source.  
4. In the VS Code Explorer, right‑click `lib` → **New Folder** and name it `OneWire2`.  
5. In your browser, navigate to `ArduinoOBI/lib/OneWire` where you find `OneWire2.cpp` and `OneWire2.h`.  
6. Open `OneWire2.cpp`, copy the source, then in VS Code create `OneWire2.cpp` inside the `OneWire2` folder (exact file name and casing) and paste the code. Save the file.  
7. Repeat the previous step for `OneWire2.h`.  
8. In the Explorer, right‑click the `OneWire2` folder → **New Folder** and name it `util`.  
9. In your browser, navigate to `ArduinoOBI/lib/OneWire/util`, which contains `OneWire_direct_gpio.h` and `OneWire_direct_regtype.h`.  
10. Copy `OneWire_direct_gpio.h`, then in VS Code create a file with the same name under `OneWire2/util`, paste the contents, and save.  
11. Repeat for `OneWire_direct_regtype.h`.

Now everything is in place; in PlatformIO, choose *Upload* to build and flash the firmware onto your microcontroller.



## Part 3: Running PC Software

Since the Arduino used inside the hardware adapter isn't very powerful, all the processing and GUI parts are offloaded to software running on your PC.

<img src="images/obi_application_bl1860B.webp" width="100%" height="100%" />



A python script creates a rich GUI and connects the PC to your hardware adapter. It can then communicate with the Makita battery through the hardware adapter, and query information, or unlock a locked battery.

> [!IMPORTANT]
> It is **very** important to carefully read the next part, or else you may run into issues.     

### Binary or Python Script?

There are two ways of running the software:

* **Single Executable:**   
  The easiest way of running the python script is through a binary program: [OpenBatteryInformation.exe](https://github.com/mnh-jansson/open-battery-information/releases/latest) works like any other application, and when you launch it, the GUI opens. However, Windows, Chrome, and many other entities classify this program as **malware** (although it probably isn't).

  Because of this, in order to run the software, you must temporarily turn off operating system protection features - which is not recommended. 

* **Python Script:**
  Running the actual python script **yourself** is the most robust way, and this won't trigger alarm bells in your operating system or browser.

  However, it comes with a new set of challenges: the python interpreter may not be present on your system yet, and/or your python installation may be missing dependencies required by the script.

So in a nutshell, neither of these ways is intuitive. Below, you find simple walk-throughs for both approaches.

Note that both sections below just deal with **launching** the software, not **using** it. Once the GUI successfully opens and is functional, you can move on to the final section which explains how to **use** the software.

## Running Binary Application

To run the binary application, you need to download it from [github](https://github.com/mnh-jansson/open-battery-information/releases/latest) - which will probably fail. Most browsers flag the download of executables and won't give you the file.

### Downloading Executable

So here is a PowerShell script that you can use to download, unblock and unzip the file automatically:

````powershell
# store binary in TEMP folder:
$rootFolder = $env:temp

# define paths for our project:

# top folder where everything is stored:
$projectRoot = Join-Path -Path $rootFolder -ChildPath OpenBatteryInformation
# path to zip that gets downloaded:
$pathZip = "$projectRoot\obi.zip"

# create folder
$exists = Test-Path $projectRoot
if (!$exists) { $null = New-Item -Path $projectRoot -ItemType Directory -Force }

# download zip from github
$url = 'https://github.com/mnh-jansson/open-battery-information/releases/download/v0.2.2/OBI.exe.zip'
Invoke-WebRequest -Uri $url -UseBasicParsing -OutFile $pathZip

# remove virus alarm:
Unblock-File -Path $pathZip

# unzip file:
Expand-Archive -Path $pathZip -DestinationPath $projectRoot

# open folder
explorer $projectRoot
````

### Disabling Anti-Virus (Not Recommended - But Required)
Once you ran this script, Windows Explorer opens the folder with *openbatteryinformation.exe* (if you are running this on a non-Windows operating system, you need to open the folder yourself).

If you launch *openbatteryinformation.exe*, though, your operating system will most likely pop up a virus alert and then delete the file. This is standard procedure for any binary that contains a python script, regardless of whether it is malicious or not.

So in order to run the file, you need to go to your operating system/anti-virus software-settings, and disable the "real-time virus protection". I am not walking you through these steps.

If your anti-virus features have already deleted the executable, simply run the PowerShell script again once you disabled the real-time virus protection.

> [!IMPORTANT]
> **Do not** forget to re-enable the anti-virus protection once you are done. Or better yet: look at the aöternative option below, and avoid the binary file altogether.    


## Running Python Script Directly

A much easier way is to run the underlying python script directly. Since this is not a single file, you should first download the entire [script folder](https://github.com/mnh-jansson/open-battery-information/tree/main/OpenBatteryInformation).

### Downloading Python Script + Dependencies

Here is a PowerShell script that downloads the python source code so you can run it:

````powershell
# store binary in TEMP folder:
$rootFolder = $env:temp

# define paths for our project:

# top folder where everything is stored:
$projectRoot = Join-Path -Path $rootFolder -ChildPath OpenBatteryInformation
# path to zip that gets downloaded:
$pathZip = "$projectRoot\obiSource.zip"
# path to extracted files:
$pathExtracted = "$projectRoot\obiSourceFolder"


# create folder
$exists = Test-Path $projectRoot
if (!$exists) { $null = New-Item -Path $projectRoot -ItemType Directory -Force }

# download zip from github
$url = 'https://github.com/mnh-jansson/open-battery-information/archive/refs/heads/main.zip'
Invoke-WebRequest -Uri $url -UseBasicParsing -OutFile $pathZip

# remove virus alarm:
Unblock-File -Path $pathZip

# unzip file:
Expand-Archive -Path $pathZip -DestinationPath $pathExtracted

# find python sources:
$file = Get-ChildItem -Path $projectRoot -File -Filter main.py -Recurse
$folder = $file.DirectoryName

# move them to the root of our project:
$newFolderPath = Join-Path -Path $projectRoot -ChildPath $file.Directory.Name
Move-Item -Path $folder -Destination $projectRoot

# delete the rest:
Remove-Item -Path $pathExtracted -Recurse

# open the folder with the python script and its dependencies:
explorer $newFolderPath
````

### Running Python Script

To run the python script, you need python. Run this line to check whether it is already there:

````powershell
python --version
````

#### Prerequisite #1: Installing Python
If the command **python** isn't found, run this to set up python on Windows (use a newer python version if by the time you read this 3.13 is no longer up-to-date):

````powershell
winget install -e --id Python.Python.3.13
````

Once you successfully installed python, make sure **you close and open the PowerShell console**. That's because the installation changes the environment paths, and you get the new python path only when you re-launch the console. In the **newly launched** console, you should now be able to successfully run `python --version`.

#### Prerequisite #2: Installing Dependencies
The script requires access to the serial port, so in order to run it, you need to first install the *pyserial* library like so:

````powershell
python -m pip install pyserial
````

#### Running Script
Now that you have successfully set up your python environment, you can launch the script. For this, it is crucial that you first set the current directory to the directory with your script, like so:

````powershell
# this is the path where you downloaded the python script (see above)
Set-Location -Path 'C:\Users\...\Temp\OpenBatteryInformation\OpenBatteryInformation'
.\main.py
````

Never run the script with an absolute path name.

#### Quick Checklist
Here are common quirks, and why they happen:

* **I try and launch the python script, but can't find "python":**       
  Make sure you have installed and set-up python first.   
* **Lots of error messages when I launch the script:**   
  Make sure you set your own current directory to the directory where the python script is located.    
* **The GUI opens, but I cannot select an interface. The combo box is empty:**    
  Make sure you installed the library **pyserial** before you launch the script.


## Using PC Software
Regardless of how you managed to get the software running, once the GUI opens, you can now start and manage your Makita battery.

### Physically Connect Battery to PC

Your Arduino hardware that you built earlier - **ArduinoOBI** for short - acts as interface between your Makita battery and your PC:
* Connect **ArduinoOBI** via its USB connector to your PC.
* Slide **ArduinoOBI** onto your Makita LTX battery.

<img src="images/makita_obi_inuse_t.webp" width="50%" height="50%" />


### Launch Software
Depending on which route you chose, either launch **OpenBatteryInformation.exe**, or launch **main.py**. This opens the main GUI:


<img src="images/obi_application_bl1860B.webp" width="100%" height="100%" />

### Connect Software to Battery

In the application window:

1. In **Makita Selection**, select **Makita LXT**. It is the only option available.
2. In **Interface**, select **Arduino OBI**. It is the only option available.     
**NOTE:** If there is *no option at all* in this drop box, then you need to install *pyserial* as a prerequisite for the script.     
3. In the **Select Port** list, choose the COM port assigned to your Arduino.  
4. Click **Connect**.  
5. In the top‑center section, click **Read battery model** and **Read battery data** to populate all details in the list below.

### Unlocking Battery

Occasionally, the internal BMS will **lock** a battery, making it unusable. While lockouts often indicate legitimate issues such as cell defects, overload events, or other safety‑critical faults, there are also many reports of otherwise healthy batteries being locked purely by software. 

In such cases, you can click *Clear Errors* in the software to attempt to unlock the battery.   **Proceed entirely at your own risk:** overriding a safety lock on a damaged battery can lead to overheating or fire.


## Materials

* [ArduinoOBI (platformio):](materials/arduinoobi.zip)       
Complete sample project, ready to be built in *platformio*: download and unpack this zip, then in VSCode choose `File / Open Folder`. 


> Tags: LTX, Makita, ArduinoOBI, Open Battery Information, 1-Wire protocol, battery diagnostic, BMS unlock, Arduino Nano, Arduino UNO, PlatformIO, battery lockout, lockout, Martin Jansson



[Visit Page on Website](https://done.land/components/power/powersupplies/battery/toolbatteries/makita/makitaltxdigitalinterface/arduinoobi?170009121517253207) - created 2025-12-16 - last edited 2026-02-22
