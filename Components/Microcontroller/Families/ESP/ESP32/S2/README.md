<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# S2

> Full Native USB Support And Low Energy Consumption


In 2020, *Expressif* released both the *S-Series* and the first member of the *C-Series*.



<img src="images/esp32_s2_chip.jpg" width="80%" height="80%" />

## When To Use

Here are the top reasons for choosing a **S2**:

| Feature | Use Cases |
| --- | --- |
| Low Energy | perfect for battery-driven devices |
| MSC Support | can act as USB flash drive and also r/w from real USB flash drives, i.e. to easily transfer (sensor) data to a computer |
| HID Support | can simulate *USB input devices* such as *keyboards* and also use attached real input devices, i.e. an external keyboard. Perfect for devices that require extensive or convenient human data input |
| 43 GPIO | massive number of available *GPIOs* can control even very complex hardware scenarios |
| Temperature Sensor | **S2** can monitor its temperature. Perfect for use cases that can get (too) hot and then require an action |
| Time Of Flight | **S2** can use *radio waves* to locate items and calculate distances (with low resolution of roughly *1m*)

These are *potential* reasons to choose a different microcontroller type:

| Use Case | Recommendation |
| --- | --- |
| Complex and calculation-intensive | **S2** is fast but *single core*. For better multitasking, *dual core*, i.e. **ESP32**, **C3**, **S3** |
| Small Form Factor | **S2** does not support *USB-Serial-JTAG* to directly program it via *USB*. Additional components are required. Choose **S3**. |
| Bluetooth | **S2** does not support *Bluetooth*. Choose i.e. **S3**. 

## Evolution
Differences between **S2** and the original (initial) **ESP32**:

| Feature | Removal |
| --- | --- |
| Cores | one core instead of two |
| Size  | 7x7 instead of 5x5 |
| Memory | SRAM reduced from 520 to 320, ROM reduced from 448 to 128 |
| LED PWM | reduced from 16 to 8 |
| ADC | 2x12bit 18ch instead of 2x13bit 20ch |
| UART  | reduced from 3 to 2 |
| I2C | reduced from 2 to 1 |
| IR/RMT | reduced from 8 to 4 |
| Bluetooth | removed |
| SD Card support | removed |
| Motor PWM | removed |
| Hall Sensor | removed |
| Ethernet  | removed |


Aside from the much lower *energy consumption*, the **S2** got some enhancements:

| Feature | Addition |
| --- | --- |
| Touch | extended from 10 to 14 |
| GPIO  | extended from 34 to 43 |
| USB HID | HID Client and Host added |
| USB MSC | MSC Device and Host added
| TOF  | added |
| Temperature Sensor | added |


## GPIOs

The **S2** comes with *43 physical GPIO pins*. Not all pins are fully usable, and not all boards expose all pins.

> [!CAUTION]
> Pins may be labelled differently by a board. *Hardware* pin **10** and the *generic pin label* **D10** for example do not necessarily designate the same pin.


The 46 physical *GPIO* are labeled *GPIO0-GPIO21* and *GPIO26-GPIO46*.

Each pin can be used as a general *input* or *output* pin, or connected to an internal peripheral signal. Internal peripheral signals can be routed to *any* pin.

### Analog Input

*GPIO1-GPIO10* can be connected to *ADC1* for analog input, and *GPIO11-GPIO20* can be connected to *ADC2*.



> [!CAUTION]
> *ADC2* (and therefore *analog inputs* at *GPIO11-GPIO20*) can only be used when *WiFi* is *disabled*. During *WiFi* operations, *ADC2* produces random values.






### RTC Pins (Deep Sleep)

The *RTC*  component (*Real Time Clock*, usable during *Deep Sleep*) uses *GPIO0-GPIO21* as *RTC_GPIO0-RTC_GPIO21*.

### Special Purpose Pins

Some pins serve internal functions and should be used only for their intended purpose. 

#### Strapping Pins
*GPIO0* (as well as *GPIO45* and *GPIO46*) are *strapping pins* that play a role when switching the microcontroller to *firmware upload mode*.

| Pin | Strapping Use |
| --- | --- |
| GPIO0 | pull down during reset to enable firmware upload mode |
| GPIO45 | sets SPI voltage: low for 3.3V, high for 1.8V |
| GPIO46 | pull down to enable ROM messages during boot |


#### SPI
*GPIO26-GPIO32* are reserved for *SPI0/1*.


#### USB JTAG
*GPIO39-GPIO42* are used for *USB JTAG* (*Joined Test Action Group*) and can be used for *OpenOCD* debugging.


#### SPI
The **S2** has four *SPI* interfaces, accessible via *GPIO9-GPIO14*, and *GPIO33-GPIO37*.

#### I2C
Any *GPIO* pin can be configured for *I2C*.

#### PWM
All *GPIO* pins support *PWM*.

#### Pullup And Pulldown
All *GPIO* pins support internal *pull-up* and *pull-down* resistors.


## Programming

The *S2* supports the *Arduino Framework*.

It can be programmed using [platformio](https://platformio.org/), the vendors' [esp-idf](https://github.com/espressif/esp-idf), or the classic [Arduino IDE](https://www.arduino.cc/en/software).

<details><summary>Adding ESP Support To Arduino IDE</summary><br/>

*Arduino IDE* by default only supports *Arduino*-compatible microcontrollers. To use it with *ESP* microcontrollers like the **S2**, the appropriate additional *board manager* needs to be installed. After that, *ESP* microcontrollers can be programmed just like any *Arduino* board.

To add an *ESP-compatible board manager*, in *Arduino IDE* choose the menu item *File/Preferences*, fill the url *https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json* into the field *Additional Boards Manager URLs*, and click *OK*.


Next, go to *Tools/Board/Boards Manager*, and search for *esp32*. Install the board manager created by *Espressif Systems*.   
</details>

### Connecting Microcontroller To Computer
Most microcontroller boards come with a *USB connector* and a *USB-to-Serial* component. They can be directly connected to the *USB* interface of your computer.

> [!TIP]
> When you plug in the *USB cable* into your computer, you should hear the typical *sound* that plays when a new *USB device* is discovered. If you do not hear this sound (even though sound is enabled), make sure you are using a suitable *USB **data** cable*. Simple *USB charger cables* have no data pins and do not work. Also make sure you plugged in the USB cable *firmly* on both ends.


Once the microcontroller board is successfully connected to the computer, most boards indicate *power on* status via a *red LED*. A new *port* should also become available.

#### Manually Entering Bootloader
Most *S2 boards* initially require you to enter the boot loader *manually*:

1. On the board, press and hold the push button marked as *BOOT* or *0*.
2. Press and release the *Reset* (*RST*) button while you continue to hold the *boot* button.
3. Release the *boot* button.

At this point you should hear the typical sound on your computer that indicates discovery of a new *USB device*.

> [!TIP]
> The *boot* button pulls down *GPIO0* (which is why this button sometimes is labelled *0*). If your board has no *boot* button (or if it is not working), you can manually connect *GPIO0* to *GND*. If *GPIO0* is pulled down during *reset*, this forces the *S2* into bootloader mode.



You can now upload new firmware to the board (i.e. by using one of the *IDEs* listed below).

#### Manually Exiting Bootloader
Once the new firmware is uploaded, you may receive an *error message* from the *IDE* that is no reason to worry: when you enter the *boot loader* manually, you need to also *exit* it *manually. So when the upload is completed, press the *reset* (*RST*) button.

> [!NOTE]
> Typically, once you uploaded your own firmware to the *S2*, from now on it enters the bootloader automatically and no longer requires you to fiddle with the push buttons. However, should the board not connect automatically to your *IDE*, you can always use the manual steps described above to force bootloader mode.

#### Connection Issues
If the microcontroller board won't connect to your computer, and/or no *port* is shown in *Arduino IDE*, then check this troubleshooting list:

* **Manual Bootloader:** test whether you need to enter the bootloader manually (as described above)
* **Close Programs:** close all other open programs, and try again. Occasionally, programs can block a port. When that happens, your *IDE* cannot access it.
* **Restart Computer:** Restart the computer, and try again. *Ports* can be blocked by software that is running invisibly in the background. *IDEs* like *Arduino IDE* and *platform.io* use *tools* and *scripts* that run silently in the background. When such a program stalls, restarting the computer frees all ports.
* **Check Cable:** Make sure the *USB cable* you use has worked before, and is indeed a *data cable*. If the cable type is ok, make sure the cable is *firmly plugged in* on both ends, then try again. Loosely connected plugs are an important connection error source.
* **Reverse Plug:** when you use *USB C* on the microcontroller side, unplug the *USB plug* and plug it in upside down. Occasionally, contacts and/or solder bridges may be fragile. By turning the plug upside down, you are using other connectors that may work better.

If things still do not work, you may want to try the microcontroller board on a different computer. Users quickly blame a microcontroller board, but more often than not the issues are related to software, cables and computer.





### Select Board Type
Once the microcontroller board is successfully connected to the computer, the final step before you can start programming and playing with it is to choose the correct *board type*.

To work with (any) microcontroller in (any) *IDE*, you need to first tell the *IDE* what the *hardware design* of the board is, i.e. which hardware pins expose which functionality. This is done by choosing a *board type*. Behind the scenes, this attaches a configuration file to your project with all the specific board hardware specs. 

Most importantly, the config file sets the available *on-board memory* and assigns the *common pin labels* (like **LED_BUILTIN** or **SDA**) to the actual hardware *pin numbers* of a particular board.

*Common pin labels* make code independent of specific hardware so that it can be freely exchanged and used with different microcontroller boards.

[Here is an example](https://github.com/espressif/arduino-esp32/blob/master/variants/lolin_s2_mini/pins_arduino.h) showing the config file for a *S2 Mini* board.

Here are a few conclusions to chew on:

* **Wrong board type:** When you choose a wrong board type, the *pin labels* no longer point to the correct hardware pins, and your code cannot work.
* **Compatible board type:** It is not necessary to choose the exact board type you are using, and there is only a limited number of board types available in most *IDEs*. Instead, choose a board type with *matching hardware*: hardware pins and available memory must match your board.
* **Hardware Pins Instead of Pin Labels:** Occasionally, you may come across code that does not use *common pin labels* like *D1*, *SDA*, or *LED_BUILTIN*. Instead, the code uses *raw hardware pin numbers like *4*, *15*, or *33*. Such code only runs on microcontroller boards it was originally designed for. *Replace* the *specific hardware pin numbers* with the appropriate *common pin labels* if you know the original board the code was created for, or when the pin purpose is obvious.
* **Mixing Hardware Pin Numbers With Common Pin Labels:** When reading documentation or articles, never confuse *specific hardware pin numbers* with *common pin labels*: i.e. when an author for example refers to pin *D1*, **do not** use *hardware pin 1*. *D1* is a *common pin label* for GPIO1 in *digital mode*. It depends on your particular board type which *hardware pin* represents *GPIO1* and can be completely different for different boards.


#### Using platform.io
In *platform.io*, when you start a new project you are asked for the *board type*. The selected *board type* is saved in the file *platformio.ini* where it can later be changed or adjusted. 

Here is an example for a project using the *S2 Mini* board:

````
[env:lolin_s2_mini]
platform = espressif32
board = lolin_s2_mini
framework = arduino
upload_speed = 115200
monitor_speed = 115200
upload_flags = --after=no_reset
````

#### Using Arduino IDE
In *Arduino IDE*, the *board type* is selected in the menu *Tools/Board*:

Once you connected the microcontroller to your computer using a *USB cable*, select *Tools/Board/ESP32 Arduino*, then select the appropriate board in the list. To work with the *S2 Mini* for example, choose *LOLIN S2*.

Finally, select *Tools/Port*, and select the port you connected the board to.

> [!TIP]
> If no port is shown, press the *RESET* button on the board. Then open the *Port* menu again. If still no port is shown, close all other programs or restart the computer. Make sure you are using a *USB data cable* (not a simple *charger* cable), and that the cable is firmly plugged in.








## Materials

[S2 Datasheet](materials/esp32-s2_datasheet.pdf)   
  


> Tags: Microcontroller, ESP32, S2, ESP32 S2, Energy

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/s2?502092031823244200) - created 2024-03-23 - last edited 2024-05-04
