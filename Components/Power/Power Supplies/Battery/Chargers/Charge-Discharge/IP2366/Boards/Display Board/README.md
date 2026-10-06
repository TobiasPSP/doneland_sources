<img src="/assets/images/charging.png" width="100%" height="100%" />

# IP2366 Display Board

> Versatile IP2366 Board With Optional Display and I2C

This compact board is a modular system: the base board comes with an IP2366, XT30 Jack, NTC Temperature Probe, and 10-Switch configuration panel. Optionally, a daughter board with TFT display and microcontroller can be added.

## Overview

This board is currently sold in three variants:

* **Without Display:**     
  Contains only the base board with the IP2366. The IP2366 used on this board **does not support I2C**, so a daughter board cannot be fitted later, nor can you connect your own microcontroller to it. A 10-switch dip panel allows for convenient configuration. Four white LEDs are located on the board and show battery state-of-charge, charging, and discharging.

  
  <img src="images/ip2366_manual.webp" width="50%" height="50%" />

* **With Display:**     
  The base board uses the exact same PCB, however it uses a different IP2366 variant: the chip on this board supports I2C. It has the same ten-switch dip panel as the display-less version, and you should configure it correctly to set your default values. 
  
  
  <img src="images/ip2366_i2c.webp" width="50%" height="50%" />
  
  Most of these values can later be overridden by the configuration menu accessible via the display. Instead of the four white LEDs, this board has a six-pin connector. 
  
  
  <img src="images/ip2366_6pin.webp" width="30%" height="30%" />
  
  A **daughter board** plugs onto the six-pin connector that comes with an Arm Cortex microcontroller (Puya PY32F030K28), three push buttons marked `S1` - `S3`, and a second NTC temperature probe as part of a 2-wire 5 V fan control. 
  
  
  <img src="images/ip2366_daughter.webp" width="60%" height="50%" />
  
  It is is available with two different TFT display sizes:
  
  * 0.96-inch, 80×160 ST7735 TFT
  * 1.47-inch, 170x320 ST7789 TFT


## Base Board Configuration

Before use, adjust the ten dip switches to your needs:

<img src="images/dipswitch_ip2366_display.webp" width="100%" height="100%" />

If you use the display board, you should still use the dip switches to set your default values: carefully pull off the daughter board with the display to get access to the base board dip switch.



* **Battery:**    
  Switch 1 - 5 sets string count to 2 - 6, so the minimum string count is 2S.

* **Power:**   
  Set the maximum power using the switches 6 - 8. Keep in mind that with the lowest setting 65 W, the board already can warm up significantly. To be able to use 140 W, you **must add a fan and heat sink**.    

* **Battery Chemistry:**    
  Take special care with switches 9 and 10: they set the battery chemistry and determine whether the charger charges to 3.7 V (LiFePo4) or 4.2 V (LiIon). **Apparently, in the original documentation, there is an error:**  all boards I tested used switch 9 for LiIon/LiPo, and switch 10 for LiFePo4. The vendors' documentation claims it is the other way around. If in doubt, measure the battery connectors open circuit voltage.

> [!IMPORTANT]
> Only **one switch per group** may be in `ON` position, so make sure there are exactly **three switches in `ON` position**.

### Wiring

Add a **male XT30** connector to your battery, and connect it to the board. To unseal the IP2366, connect a USB charger to the USB-C port for a few seconds until the white LEDs (on the display-less board) or the TFT screen turn on.


<img src="images/ip2366_schematic_illu2.webp" width="100%" height="100%" />

While you *can* run the board without a connected battery, this triggers constant chip resets and other unusual behavior. 

Running the board just with a charger can still be useful for a number of reasons:

* **Diagnostics:**      
  Does the board work at all? Is the screen possibly broken? 
* **Verifying Charger Settings:**   
  Measure the voltage on the battery side. It should align with the maximum charge voltage for your battery. If it is off, check these:
  - did you configure string count?
  - did you set the battery chemistry correctly? Remember that the vendor has accidentally switched over the settings for LiIon/LiPo and LiFePo4.
  - are you positive you did not accidentally set TWO dip switches in either settings group? Only **one** switch may be set to `ON`.
  

### Warning: High Battery Current

Depending on how you operate the board, there can be **high currents on the battery side** (which is why the board uses XT30 high current connectors that can handle up to 30 A).

If, for example, you use a 2S battery and have enabled full 140 W, then a load on the USB PD side could draw a maximum of 20 V 7 A (140 W). At a nominal 7.4 V on the 2S battery side, this would require roughly 21 A (including converter losses).

### Enable Button

The base board does not come with an installed `Enable` push button, so by default, the USB PD power output is **activated automatically** when a large-enough load is plugged in.



<img src="images/ip2366_enable_button.jpg" width="40%" height="40%" />

If you want to be able to **manually** enable the output via a push button - like many powerbanks do - then there are already three through-holes on the PCB, next to the USB-C connector, that let you solder on a push button, or wires.

The single through-hole towards the side with the USB C connector is `GND`. You need the other two through-holes that are lined up: when you short these for a few milliseconds, the output is activated.



## Display Board Configuration

If you opted for a board with a TFT-display daughter board, you should first configure the base board exactly as described above. Carefully pull off the daughter board to get access to the 10-switch dip, and set your defaults.

After this, you continue with the software configuration. Unfortunately, that's not trivial since the firmware uses Chinese characters by default. Once you have configured the initial setup, though, the UI is in English.

### Navigation
Navigation for this board is done through the three push buttons:

| Button | Description |
| --- | --- |
| `S1` |  move up |
| `S2` | short press: select<br/>long press: confirm and exit
| `S3` | move down |


### Configuration
When you connect the display board to a USB charger, the display turns on. Unfortunately, initially the firmware runs in Chinese language settings. 

1. **Unlocking IP2366:**    

    If you see a screen with Chinese characters that does not respond to button presses, then you need to connect a USB charger to the board, at least for a few seconds. By default, IP2366 is in locked mode. Connecting a charger unlocks it.

    <img src="images/ip2366_unseal.jpg" width="30%" height="30%" />


    Generally, this Chinese screen appears whenever the microcontroller cannot access the IP2366 I2C interface.

2. **Pre-Setup:**   

    Next, you see a setup page with only the most important settings, like string count and battery voltages. 
    
    <img src="images/ip2366_initscreen1.jpg" width="50%" height="50%" />
    
    This screen, too, initially is in Chinese, and there is no way at this point to change the language. Later, when you changed the language, this screen will also be translated. I put here the English screens for better orientation.

    <img src="images/ip2366_initscreen2.jpg" width="50%" height="50%" />

    `Setup Next` controls whether you want to see this setup screen the next time you power on the chip. If you plan to experiment, keep `Yes`. If you permanently attach the board to a particular battery that will not need changes later, choose `No`.

    Accept the values by long-pressing the middle button (`S2`).

3. **Operations Screen:**     
  This brings you to the regular operations screen where you see a varying number of monitoring and operation-related properties. 
  
    <img src="images/ip2366_screen1.jpg" width="50%" height="50%" />
  
    Pressing the upper button switches screen layouts.

    <img src="images/ip2366_screen2.jpg" width="50%" height="50%" />    
    <img src="images/ip2366_screen3.jpg" width="50%" height="50%" />    
    <img src="images/ip2366_screen4.jpg" width="50%" height="50%" />    
    <img src="images/ip2366_screen5.jpg" width="50%" height="50%" />   
    <img src="images/ip2366_screen6.jpg" width="50%" height="50%" />   

4. **Settings:**       
  Long pressing the middle button (`S2`) opens the settings menu.    

   <img src="images/ip2366_set1.jpg" width="50%" height="50%" />   

   If you want to use coloumb counting (gauging), make sure you set the correct battery capacity on the first page.

    <img src="images/ip2366_set2.jpg" width="50%" height="50%" />   

    On the second page, make sure you limit the battery current if necessary. This of course reduces the available power.    

    <img src="images/ip2366_set3.jpg" width="50%" height="50%" />   

    On the third page, set the temperature when the attached fan should activate. You have to connect a 5 V two-wire fan to the daughter board yourself, though, a fan is not included.

    <img src="images/ip2366_set4.jpg" width="50%" height="50%" />   

    On the forth page you can rotate the screen design and adjust it to the way you mount this board.

    <img src="images/ip2366_set5.jpg" width="50%" height="50%" />   

    On the last page, you finally find the setting `Language`. Press the middle button `S2` to enter the setting, press `S3` to select `English`, and press `S2` again to confirm. Long-press `S2` to save and exit the menu.


## Fan Control
The display version comes with built-in temperature-controlled fan support. You just need to supply a two-wire 5 V fan.

<img src="images/ip2366_qr1.jpg" width="50%" height="50%" />   

Connect the fan to the two solder pads marked `+ -`, and make sure you use the correct polarity. 

In the settings (discussed above) you can set the temperature at which the fan should start spinning. The fan is controlled by the NTC temperature probe soldered to the daughter board. The other NTC probe is soldered to the base board and controls the IP2366.

### Attention: Heat!

IP2366 is so powerful that it can potentially cause a lot of heat. Even with its lowest setting (65 W max), the board gets quite warm. When you decide to use the maximum 140 W, you *must install* a fan, and you should also add heat sinks to the base board. 

However, that's not trivial because the back side of the board is populated as well. Probably the best place for a heat sink is the conductor on the one side, and the IP2366 on the other side.

## I2C Connector

Versions with display feature a 6-pin connector on the base board:


<img src="images/ip2366_6pin_connector.jpg" width="50%" height="50%" />   

Pin assignment from left to right:

| Pin | Description |
| --- | --- |
| 1 |  `GND` |
| 2 | *(unknown)* |
| 3 | `INT`|
| 4 | `SDA` |
| 5 | `SCL`|
| 6 | `BAT+` |

The base board without the display has no connector, but the through-holes are present. 

### Testing I2C
If you want to test whether your display-less board may possibly have an I2C-enabled IP2366, you must remove the two tiny LED resistors (or better yet: lift them up just on one side so you can later solder them back in place).

> [!IMPORTANT]
> Do this only with appropriate solder skills and on your own risk. If you accidentally confuse `GND` and `VBAT` pins, you can easily destroy the board or anything you connect to it. I have tested a number of boards for you, and those all **did not support I2C**.

The picture below shows both ways: on the left, the resistor is removed, and on the right, it is lifted up on one side only:

<img src="images/ip2366_led_remove.jpg" width="50%" height="50%" />  

Next, add pullup resistors to `4` (`SDA`) and `5` (`SCL`), and connect them to an I2C scanner (sketches for I2C scanners are available everywhere and really simple). Do not forget to connect pin `1` (`GND`) to your scanners' `GND`.

If your IP2366 supports I2C, it responds with address `0x75`.

An even easier test: with pullups in place, check the voltage on both I2C pins. When I2C is enabled, it should sit at around 3.3 V most of the time. With the non-I2C version of IP2366, the voltage is at around 1.6 V despite the pullups.

## Firmware Updates

The display version is highly interesting since it comes with its own dedicated microcontroller that is fully programmable.

<img src="images/puya_ip2366.png" width="50%" height="50%" />  

The programming interface for this Arm Cortex MCU can be found on the backside of the PCB:

<img src="images/puya_2366_mcu.webp" width="50%" height="50%" />  

The board developers even promise full open source and access to tool chain and future firmware updates. This would place this board into a premier league because it would come with an I2C-enabled IP2366 that is already hooked up to a microcontroller and screen, potentially opening up an entire universe of useful applications.

When you scan the QR code on the board, it leads you to a Chinese QQ group:

<img src="images/ip2366_qr_qq.webp" width="50%" height="50%" />  

The developers maintain all resources for this board in QQ group 170681020. Unfortunately, to access this group, you must sign up for QQ, and to be able to sign up for QQ, you must be Chinese (and have a Chinese phone number at hand).

> [!NOTE]
> If anyone has a QQ account and was able to download the materials, please leave a comment below, and I get in touch with you asap. I really would love to get the official firmware and play with it here.   

> Tags: IP2366, Charger
