<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Uploading New Sketches

> Successfully Uploading New Firmware To A Development Board


Once you manage to connect
You got a new *development board*, and now you want to hook it up to your computer (so you can program it and upload new firmware, or receive output via the *Terminal* window).

Sounds easy: just connect a *USB cable* to the development board and plug its other end into your computer. And often enough it *is* that easy.

However, when your computer stubbornly won't *recognize* the board, things quickly become *frustating* as there are no *error messages* or other indicators that would tell you what is amiss. That's why it's a good thing to *understand* how the development board is recognized by a computer, and what the steps are to *diagnose and correct* connection issues.

## Overview
In order to *communicate* with a development board, typically a *USB port* is used *for convenience*. In *reality* though, most microcontrollers use a simple *serial* interface for communications. Only the latest *ESPxxxx* modules support direct communication via *USB*.

In any respect, *connecting issues* are *not related to a particular IDE you may be using*. *Connecting issues* are *always* an issue between the development board and your computer. This makes *diagnosis* easy because you can *ignore* the *ISE* and focus solely on the raw *USB connection*.

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

* The *first* set of data represents a connected *ESP8266* at *COM4* using a *custom port driver* located at *C:\WINDOWS\SYSTEM32\DRIVERS\CH341S64.SYS*.
* The *second* set of data represents a connected *ESP32 S2* at *COM77* using the default *Microsoft USB Serial Driver*.

<details><summary>Testing COM Port Connection</summary><br/>


Once the *development board* is recognized by the computer and got a *COM Port* assigned, you are good to go. 

*IDEs* like *Arduino IDE* and *platformio* use generic tools to communicate to the development board over the assigned COM port. *ESPxxxx*-based development boards are managed by the tool *esptool* supplied by its vendor *Espressif*. 

Anyone can freely [download and install](https://github.com/espressif/esptool/tree/master/esptool) this tool, and you could install it *stand-alone* as part of your personal tool set if you like. Once there is a *COM Port* that you can use to communicate with a development board, tools like *esptool* can gather important *detail information* about a particular board and its hardware. That's useful to check *USB connectivity* as well as i.e. *verify* that your development board in fact came with the features and memory sizes a vendor promised.

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

What however if the computer simply *ignores* a connected development board and *does not assign a COM Port* to it? That's a *show stopper*. Without a *COM Port*, you *cannot communicate* with the board. Bummer.

> [!IMPORTANT]
> You **must** solve this issue first - before looking into any other configurations and settings. There **must** be a **COM port** (on *Windows*) showing up in *Device Manager*.

These are the most common issues causing connection issues:

* **Loose Connections:** make sure you *firmly* plugged in the *USB cable*. It should *snap into place*.
* **Bad USB Cable:** this is meant dead serious. Some *USB* cables are made just to supply *power* and do not connect the *data lines*, but the *majority* of cables connects *all pins*. Still, a great many *USB cables* cause *connection issues*, most likely due to low quality, high cable resistance, loose jacks, etc. The best option is to use a *known good* USB cable that you previously successfully used to connect to a breakout board. If you don't have such a cable, make sure you try and test as many different cables as you can get a hold of, and if the cable was indeed the issue, attach a label to the cable that finally worked so you know which one to use in the future.
* **Missing Driver:** On *Windows*, missing drivers are not a very common issue. *Windows* ships with the most common drivers. However, if the breakout board is not recognized even though you tried multiple *USB cables*, you should find out what kind of driver the development board requires, and install it.
* **Defects:** If you got your development board from a cheap source like *AliExpress*, that's perfectly fine. Often they ship the very same boards that you can get elsewhere at ten times the price. However, *quality control* is a problem. Expect one out of thirty boards to have a defect. Most defects are related to *bad soldering* and can be repaired: drops of *solder* may have caused a *short circuit* on some pins, or the *USB connector* is not firmly soldered onto the *PCB*. When the board *gets warm* quickly after supplying it with power, immediately disconnect it and closely examine all solder spots. That said, there are (few) cases when a development board just won't work. These cases are *rare* though. Try connecting a different development board (ideally of the same type requiring the same *drivers*) to isolate the cause. If the new board connects fine, then it definitely is a *board issue*.

> [!NOTE]
> When things don't work as expected, many users are *quick to blame the board* or brag about the *"rotten quality"* of Asian sellers. That doesn't match my experience. Over the years, I ran into numerous *connection issues*, and yes they are *frustrating* and get you annoyed. Yet out of 100 cases, maybe just one turned out to be a *genuine board hardware defect*. All other issues were related to cables, drivers, and other things *that I was responsible for*. In the end, they all could be happily resolved. Let's not forget: *development boards* are no *toys*. They do require technical skill and background information to run them appropriately. When things go wrong, take it as a *mental challenge*.



## Entering Boot Loader
The need to press the boot button on an ESP32 board during firmware upload depends on how the board handles the bootloader mode entry. HereÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢s a detailed explanation of the different scenarios you can encounter:

1. Boards That Require a Boot Button Press
Some ESP32 boards require you to manually press and hold the boot button, then press the reset button, then release the boot button during the firmware upload process. This is because these boards donÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢t have the circuitry needed to automatically reset and put the ESP32 into the bootloader mode. When you press the boot button, you are manually putting the ESP32 into the mode where it can receive new firmware.

2. Boards That Automatically Enter Bootloader Mode
Other ESP32 boards have additional circuitry that allows the development environment to automatically reset the ESP32 and put it into bootloader mode. This is typically achieved using a combination of the RTS (Request to Send) and DTR (Data Terminal Ready) signals from the USB-to-Serial converter chip on the board. When you start the upload process, the development environment toggles these signals to reset the ESP32 and initiate the bootloader mode without the need for manual intervention.

3. Boards That Occasionally Need a Boot Button Press
There are instances where boards that generally can enter bootloader mode automatically might still require a manual boot button press. This can happen due to:

* Timing Issues: Occasionally, the timing of the signals might not be perfectly aligned, causing the ESP32 to miss the automatic reset and bootloader initiation.
* Power Supply Fluctuations: Inconsistent power supply or voltage drops can cause the automatic reset mechanism to fail.

### How the Boot Process Works
Understanding the boot process can provide more clarity:

#### Boot Mode Selection
The ESP32 has three primary boot modes:

* **Normal Boot:** Runs the user application code.
* **Download Boot:** Used for flashing new firmware.
* **SD-Card Boot:** Boots from an SD card, if configured.

#### GPIO Pin States

GPIO0 (Boot Button): Holding GPIO0 low during reset puts the ESP32 into download boot mode.
EN (Enable): Reset pin for the ESP32. Pulling it low resets the chip.


#### Automatic Bootloader Entry
For boards with automatic bootloader entry:

RTS and DTR Signals: These signals from the USB-to-Serial chip (such as CP2102, CH340G, or FTDI) control the state of GPIO0 and EN pins.
RTS: Often connected to the EN pin through a capacitor.
DTR: Often connected to GPIO0 through a capacitor.
The development environment (like Arduino IDE, PlatformIO, etc.) toggles these signals to create the necessary pulse sequence:
DTR (GPIO0) goes low first, then RTS (EN) goes low, resetting the chip.
As EN goes high again, if GPIO0 is still low, the ESP32 enters the download boot mode.
Manual Bootloader Entry

#### For boards requiring manual intervention:

You press and hold the boot button (GPIO0 goes low).
Then, you press and release the reset button (EN goes low and then high), while still holding the boot button.
The ESP32 enters the download boot mode, ready to receive firmware.
Occasional Manual Intervention
Even boards designed for automatic bootloader entry might occasionally require manual intervention due to the reasons mentioned above. Ensuring stable power supply, using high-quality USB cables, and verifying driver installations can help mitigate these issues.

### Behavior in Bootloader Mode
Waiting for Firmware: In bootloader mode, the ESP32 is ready to receive new firmware. If no data is sent, it will remain idle.
No Automatic Exit: Unlike some other microcontrollers, the ESP32 does not automatically exit bootloader mode after a timeout or upon receiving incomplete data. It requires an explicit reset to exit this mode.

#### Practical Implications
Firmware Upload: During a firmware upload process, the development environment will send the new firmware data to the ESP32. Once the upload is complete, it typically sends a reset command to start running the newly uploaded firmware.
Manual Reset: If the firmware upload process fails or you need to exit bootloader mode for any other reason, you must manually reset the ESP32 by pressing the reset button or power cycling the board.

## Arduino Bootloader Process
Automatic Bootloader Entry: Most Arduino boards, like the Arduino Uno, handle the bootloader process automatically. When you initiate a firmware upload from the Arduino IDE, the following happens:

### DTR Signal
The USB-to-Serial adapter (such as the ATmega16U2 on the Uno) asserts the DTR (Data Terminal Ready) line.
Auto-Reset Circuit: This signal is connected to the reset pin of the microcontroller through a capacitor, causing the microcontroller to reset.
Bootloader Activation: On reset, the Arduino bootloader runs briefly and checks if there's new firmware being sent via serial. If it detects new firmware data, it stays in bootloader mode to receive and write the new firmware.
Bootloader Mode Duration:

### Brief Window
The Arduino bootloader remains active only for a brief period (a few seconds) after a reset. If it doesn't receive firmware data within this time, it times out and proceeds to run the existing sketch (user application code).


### Automatic Exit
The bootloader automatically exits and the microcontroller runs the user program if no new firmware is detected.
Manual Intervention: Normally, you donÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢t need to press any buttons to upload new firmware to an Arduino. However, if there are issues with the auto-reset mechanism (e.g., using certain third-party USB-to-Serial adapters), you might need to manually press the reset button right when you start the upload process.


## Bootloader in ROM
The ESP32 (and other Espressif chips like the ESP8266) has its bootloader stored in ROM (Read-Only Memory), making it robust against being accidentally overwritten or corrupted. Here's how this works and why it is beneficial:

* Permanent Storage: The bootloader code in the ESP32 is stored in ROM, which is non-volatile and read-only. This means the bootloader is permanently written during the manufacturing process and cannot be modified or deleted through normal operations.

* Protected from Corruption: Since the bootloader resides in ROM, it is immune to software bugs, power failures, or accidental overwrites that might occur during firmware updates or application development. This protection ensures that the core functionality needed to load new firmware is always intact.

* Initial Boot Process: When the ESP32 is powered on or reset, it first runs the code in the ROM bootloader. This bootloader is responsible for:
  * Initializing hardware and peripherals.
  * Checking the GPIO pins (such as GPIO0) to determine the boot mode (normal execution, bootloader mode, etc.).
  * Loading the user application code from flash memory if no special boot mode is triggered.

### Benefits of ROM-Based Bootloader
* Brick Prevention: Devices with a ROM-based bootloader are much harder to brick because the bootloader cannot be accidentally erased or corrupted. This ensures that you always have a reliable method to upload new firmware even if the current application firmware is problematic.

* Consistent Recovery Option: In case of a firmware failure, you can always enter the bootloader mode to flash new firmware. This makes it easier to recover from errors during development or updates.

* Simplified Firmware Updates: With the bootloader in ROM, developers and users don't have to worry about maintaining or protecting the bootloader code when updating firmware. The update process can focus solely on the application code.

## Arduino Bootloader in Flash
The bootloader is stored in a designated section at the beginning of the flash memory of the microcontroller. For instance, on an ATmega328P (used in the Arduino Uno), the bootloader typically occupies the upper 2 KB of the 32 KB flash memory.

### Bootloader Size and Location

Arduino Uno (ATmega328P): The bootloader is stored in the upper 2 KB of the flash memory, leaving 30 KB available for user applications.
Other Arduino Models: Different models might have different sizes for the bootloader and available flash memory for user applications. The exact size and location depend on the specific microcontroller and the bootloader used.
Firmware Upload:

When you upload new firmware via the Arduino IDE, the bootloader facilitates the communication between the IDE and the microcontroller over the serial interface.
The bootloader is responsible for writing the new firmware to the appropriate sections of the flash memory.
Protection and Update Mechanism
Protected Area: The bootloader section of the flash memory is protected during normal operation. This means that user programs cannot overwrite the bootloader code. However, it can be updated using special programming tools or processes.

### Bootloader Update

* In-System Programming (ISP): The bootloader can be updated or replaced using an ISP programmer. This is often done when initially setting up a new microcontroller or if you need to restore or replace a corrupted bootloader.
* Over-The-Air (OTA) Updates: Some advanced Arduino setups, especially those with network capabilities, can perform bootloader updates via OTA mechanisms, but this is less common for typical Arduino projects.

### Boot Process
Power-On or Reset: When the Arduino is powered on or reset, it starts executing the code from the bootloader section of the flash memory.

The bootloader checks if there is an attempt to upload new firmware (usually by monitoring the serial interface for specific signals).
If new firmware is detected, the bootloader enters a mode to receive and write the new firmware.
If no new firmware is detected within a short timeout period (usually a few seconds), the bootloader jumps to the user application code starting at a predefined memory address in the flash.
Comparison to ESP32

### Location
Arduino bootloaders are stored in flash memory, while ESP32 bootloaders are stored in ROM.
* Update Capability: Arduino bootloaders can be updated or replaced, whereas ESP32 bootloaders in ROM cannot be modified.
* Brick Prevention: While Arduino bootloaders are protected during normal operation, they can be overwritten with the proper tools. ESP32 bootloaders are inherently protected because they reside in ROM.

### Conclusion
Arduino boards store their bootloader in a protected section of the microcontrollerÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢s flash memory, allowing for flexible firmware updates and bootloader management. This approach contrasts with the ESP32ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢s ROM-based bootloader, providing different advantages and considerations in terms of update capability and protection.


> Tags: USB, UART, TTL, Connect, Port, COM

[Visit Page on Website](https://done.land/components/microcontroller/programming/uploadsketch?359846051021241839) - created 2024-05-20 - last edited 2024-05-20
