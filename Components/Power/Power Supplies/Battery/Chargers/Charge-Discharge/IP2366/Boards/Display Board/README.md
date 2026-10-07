<img src="/assets/images/charging.png" width="100%" height="100%" />

# IP2366 Display Board

> Versatile IP2366 Board With Optional Display and I2C

This compact board comes in two flavors: 

* As a simple base board with an IP2366, XT30 jack, NTC temperature probe, and 10-switch configuration panel. 
* Or with an enhanced base board (I2C-capable), plus a pluggable Arm Cortex microcontroller daughter board with TFT display, three push buttons and NTC-controlled fan connector.

<img src="images/ip2366_daughter.webp" width="70%" height="70%" />

## Overview

This board is currently sold in two variants and two screen sizes:

* **Without Display:**    

  Contains the base board only. The IP2366 on this board **does not support I2C**, so a daughter board cannot be fitted later, nor can you connect your own microcontroller to it. 

  <img src="images/ip2366_manual.webp" width="50%" height="50%" />

  A 10-switch DIP panel allows for convenient configuration. Four white LEDs are located on the board and indicate battery state-of-charge, charging, and discharging.

* **With Display:**    

  The base board included here uses the exact same PCB but a IP2366 variant with I2C-enabled firmware. The same ten-switch DIP panel can be used to configure the board defaults. 

  <img src="images/ip2366_i2c.webp" width="50%" height="50%" />

  Most of these values can later be overridden via I2C and the display. Instead of the four white LEDs, this board has a six-pin connector.

  <img src="images/ip2366_6pin.webp" width="30%" height="30%" />

  The **daughter board** plugs onto the six-pin connector and comes with an Arm Cortex microcontroller (Puya PY32F030K28), three push buttons marked `S1` - `S3`, and a second NTC temperature probe as part of a 2-wire 5 V fan control.

  <img src="images/ip2366_daughter.webp" width="60%" height="50%" />

  The daughter board is available with two different TFT display sizes:

  * 0.96-inch, 80×160 ST7735 TFT
  * 1.47-inch, 170x320 ST7789 TFT

## Base Board Configuration

Before use, adjust the ten DIP switches to your needs:

<img src="images/dipswitch_ip2366_display.webp" width="100%" height="100%" />

If you use the display board, you should still use the DIP switches to set your default values: carefully pull off the daughter board with the display to gain access to the base board DIP switches.

* **Battery:**    

  Switches 1 - 5 set the string count to 2 - 6, so the minimum string count is 2S.

* **Power:**  

  Set the maximum power using switches 6 - 8. Keep in mind that even with the lowest setting of 65 W, the board can already warm up significantly. To be able to use 140 W, you **must add a fan and heat sink**.    

* **Battery Chemistry:**    

  Take special care with switches 9 and 10: they set the battery chemistry and determine whether the charger charges to 3.7 V (LiFePo4) or 4.2 V (LiIon). **Apparently, there is an error in the original documentation:** all boards I tested used switch 9 for LiIon/LiPo and switch 10 for LiFePo4. The vendors' documentation claims it is the other way around. If in doubt, measure the battery connector's open-circuit voltage.

> [!IMPORTANT]
> Only **one switch per group** may be in the `ON` position, so make sure there are exactly **three switches in `ON` position**.

### Wiring

Here is the fundamental setup:


<img src="images/ip2366_schematic_illu2.webp" width="100%" height="100%" />


#### 1. Connect Charger Only

Initially, connect only a USB charger to the board. Do not yet connect the battery. Then check this:

* **Screen broken?**    
  Does the screen come up at all? Is it broken? The screen is fragile, and the units are often shipped with poor protection, so checking for damages should be done immediately after arrival to not miss return windows.

* **Charging Voltage Correct?**   
  Next, measure the voltage at the battery connector. While it may fluctuate a bit as the chip is trying to identify the battery, make sure the highest voltage **does not exceed the intended charging voltage**. 

  If it does, power off the unit, and revisit the configuration of the DIP switches. Make sure you configured string count and battery chemistry correctly. Make also sure you did not accidentally put more than one switch to `ON` per configuration group.

  Note that the description of switches 9 and 10 (battery chemistry) may be reversed in the original vendor documentation. Always check the output voltage **before you connect a battery**.   

#### 2. Disconnect Charger, and Connect Battery
Next, remove the USB charger, and connect the battery. This is important because in the default settings, charging current may be way too high for your battery.

With only the battery connected, the screen should come to live, and you can now review the settings and make any adjustments necessary (see below). One of the first things you may want to do is change the UI language from Chinese to English.



### Warning: High Battery Current

Depending on how you operate the board, there can be **high currents on the battery side** (which is why the board uses XT30 high-current connectors that can handle up to 30 A).

If, for example, you use a 2S battery and have enabled the full 140 W, then a load on the USB PD side could draw a maximum of 20 V 7 A (140 W). At a nominal 7.4 V on the 2S battery side, this would require roughly 21 A (including converter losses).

So in the settings (see below), make sure you use `In/Out Power` and `Batt Cur` together to control the available power:

* `In/Out Power`:   
  Configurable to 65/100/140 W. At 140 W, a 2S battery would be charged with almost **20 A**. Even at 65 W, charging would still be around **9 A**. This setting can be set via DIP switches on all boards.
*  `Batt Cur`:    
  Sets the maximum current the battery can provide. It is still unclear at this time whether this is a global setting or applies to charging or discharging only. This setting is available only on display boards. 


### Enable Button

The base board does not come with an installed `Enable` push button, so by default, the USB PD power output is **activated automatically** when a sufficiently large load is plugged in.

<img src="images/ip2366_enable_button.jpg" width="40%" height="40%" />

If you want to be able to **manually** enable the output via a push button - like many power banks do - there are already three through-holes on the PCB, next to the USB-C connector, that let you solder on a push button or wires.

The single through-hole towards the side with the USB-C connector is `GND`. You need the other two through-holes that are lined up: when you short these for a few milliseconds, the output is activated.

## Display Board Configuration

If you opted for a board with a TFT-display daughter board, you should first configure the base board exactly as described above. Carefully pull off the daughter board to gain access to the 10-switch DIP panel, and set your defaults.

After this, you continue with the software configuration. Unfortunately, that's not trivial since the firmware uses Chinese characters by default. Once you have completed the initial setup, though, the UI is in English.

### Navigation

Navigation for this board is done through the three push buttons:


<img src="images/ip2366_disp_buttons.jpg" width="20%" height="20%" />

| Button | Description |
| --- | --- |
| `S1` |  move up |
| `S2` | short press: select<br/>long press: confirm and exit
| `S3` | move down |



### Configuration

When you connect the display board to a USB charger, the display turns on. Unfortunately, the firmware initially runs with Chinese language settings.

1. **Unlocking IP2366:**    

    If you see a screen with Chinese characters that does not respond to button presses, then you need to connect a USB charger to the board, at least for a few seconds. By default, IP2366 is in locked mode. Connecting a charger unlocks it.

    <img src="images/ip2366_unseal.jpg" width="30%" height="30%" />

    Generally, this Chinese screen appears whenever the microcontroller cannot access the IP2366 I2C interface.

2. **Pre-Setup:**  

    Next, you see a setup page with only the most important settings, such as string count and battery voltages.

    <img src="images/ip2366_initscreen1.jpg" width="50%" height="50%" />

    This screen, too, is initially in Chinese, and there is no way to change the language at this point. Later, once you have changed the language, this screen will also be translated. I have included the English screens here for better orientation.

    <img src="images/ip2366_initscreen2.jpg" width="50%" height="50%" />

    `Setup Next` controls whether you want to see this setup screen the next time you power on the chip. If you plan to experiment, keep `Yes`. If you permanently attach the board to a particular battery that will not require changes later, choose `No`.

    Accept the values by long-pressing the middle button (`S2`).

3. **Operations Screen:**    

    This brings you to the regular operations screen, where you see a varying number of monitoring and operation-related properties.

    <img src="images/ip2366_screen1.jpg" width="50%" height="50%" />

    Pressing the upper button switches between screen layouts.

    <img src="images/ip2366_screen2.jpg" width="50%" height="50%" />    
    <img src="images/ip2366_screen3.jpg" width="50%" height="50%" />    
    <img src="images/ip2366_screen4.jpg" width="50%" height="50%" />    
    <img src="images/ip2366_screen5.jpg" width="50%" height="50%" />  
    <img src="images/ip2366_screen6.jpg" width="50%" height="50%" />  

4. **Settings:**      

    Long-pressing the middle button (`S2`) opens the settings menu.   

    - **Gauging, Battery, Max Power, and State of Charge:**

      <img src="images/ip2366_set1.jpg" width="50%" height="50%" />  

      Battery state-of-charge can be based on voltage or on coloumb counting, controlled by `Batt Percent`. 
      
      Coloumb counting (set to `Gauge`) is much more accurate but requires that you set the accurate battery capacity in `Capacity`. It also requires a full discharge/charge cycle. So initially, in this setting the battery gauge is not working properly. 

      Use the setting `Voltage` instead of `Gauge` to derive the state of charge from the battery voltage. This works immediately, but it can provide only a rough estimate with a high margin of error.

      `In/Out Power` controls the maximum power available. Make sure this fits your battery (both charging and discharging current at battery voltage), and ensure a fan and heat sinks are in place before you select any rating above **65 W**.

    - **Maximum Battery Current:**   

      <img src="images/ip2366_set2.jpg" width="50%" height="50%" />  

      `Batt Cur` limits the battery current if necessary. This also reduces maximum available power. So in essence, both `In/Out Power` and `Batt Cur` together control the available power.

      

    - **Fan Control and Bidirectional Operation:**      

      <img src="images/ip2366_set3.jpg" width="50%" height="50%" />      


      `Fan Temp` sets the temperature at which the attached fan activates. This is controlled by the NTC Sensor attached to the daughter board. You need to connect a 5 V two-wire fan to the daughter board yourself; a fan is not included.

      Connect it to the through-holes marked `+ -` next to the push buttons:
      
      <img src="images/ip2366_disp_buttons.jpg" width="20%" height="20%" /> 

      The second NTC sensor connected to the base board is controlled via `Batt NTC` and should remain `ON` and placed close to the battery to ensure charging stops on overheating.


      With `C Mode`, you control whether the IP2366 should work bidirectional (charge and discharge), or just one way.    

    - **Auto Sleep and Screen Rotation:**   

      <img src="images/ip2366_set4.jpg" width="50%" height="50%" />  

    
      `Auto Sleep` is important: by default, it is set to `OFF`, meaning the display will stay on forever, eventually draining a battery. You can set it to `Auto` or specify a time in the range of 5-120 seconds. This turns off the display and puts the MCU in sleep until you press any button.

      
      With `Rotation` you can rotate the screen in order to adjust it to the way you mount this board.

    - **UI Language:**   

      <img src="images/ip2366_set5.jpg" width="50%" height="50%" />  

      Finally, at the very end you find the setting `Language`. Press the middle button `S2` to enter the setting, press `S3` to select `English`, and press `S2` again to confirm. Long-press `S2` to save and exit the menu.

## Fan Control

The display version comes with built-in temperature-controlled fan support. You just need to supply a two-wire 5 V fan.


Connect the fan to the two solder pads marked `+ -`, and make sure you use the correct polarity.


<img src="images/ip2366_disp_buttons2.jpg" width="40%" height="40%" />


In the settings (discussed above), you can set the temperature at which the fan should start spinning. The fan is controlled by the NTC temperature probe soldered to the daughter board. The other NTC probe is soldered to the base board and controls the IP2366.

### Attention: Heat!

IP2366 is so powerful that it potentially generates a lot of heat. Even with its lowest setting (65 W max), the board gets quite warm. If you decide to use the maximum 140 W, you *must install* a fan, and you should also add heat sinks to the base board.

Adding heat sinks is not trivial though because the back side of the board is populated as well. Probably the best place for a heat sink is the inductor on the back side, and with the display-less version, also the IP2366 on the front side.

## I2C Connector

Versions with a display feature a 6-pin connector on the base board:

<img src="images/ip2366_6pin_connector.jpg" width="50%" height="50%" />  

Pin assignment from left to right:

| Pin | Description |
| --- | --- |
| 1 | `GND` |
| 2 | *(unknown)* |
| 3 | `INT`|
| 4 | `SDA` |
| 5 | `SCL`|
| 6 | `BAT+` |

The base board that comes without a display has no connector and instead four LEDs. The through-holes for the connector are nonetheless present.

### Testing I2C

If you want to test whether your display-less board may possibly have an I2C-enabled IP2366, you must remove the two tiny LED resistors (or better yet: lift them up just on one side so you can later solder them back in place).

> [!IMPORTANT]
> Do this only with appropriate soldering skills and at your own risk. If you accidentally confuse the `GND` and `VBAT` pins, or pin order in general, you can easily destroy the board or anything you connect to it. I have tested a number of boards for you, and they all **did not support I2C**.

The picture below shows both methods: on the left, the resistor is removed, and on the right, it is lifted up on one side only:

<img src="images/ip2366_led_remove.jpg" width="50%" height="50%" />  

Next, add pull-up resistors to `4` (`SDA`) and `5` (`SCL`), and connect them to an I2C scanner (sketches for I2C scanners are available everywhere and are really simple). Do not forget to connect pin `1` (`GND`) to your scanner's `GND`.

If your IP2366 supports I2C, it responds at address `0x75`.

An even easier test: with the pull-ups in place, check the voltage on both I2C pins. When I2C is enabled, they should sit at around 3.3 V most of the time. With the non-I2C version of IP2366, the voltage is around 1.6 V despite the pull-ups.

## Firmware Updates

The display version is highly interesting since it comes with its own dedicated microcontroller that is fully programmable.

<img src="images/puya_ip2366.png" width="50%" height="50%" />  

The programming interface for this Arm Cortex MCU can be found on the back side of the PCB:

<img src="images/puya_2366_mcu.webp" width="50%" height="50%" />  

The board developers even promise full open source and access to the toolchain and future firmware updates. This would place this board in a premier league because it would come with an I2C-enabled IP2366 that is already hooked up to a microcontroller and screen, potentially opening up an entire universe of useful applications.

When you scan the QR code on the board, it leads you to a Chinese QQ group:

<img src="images/ip2366_qr_qq.webp" width="50%" height="50%" />  

The developers maintain all resources for this board in QQ group 170681020. Unfortunately, to access this group, you must sign up for QQ, and to be able to sign up for QQ, you must be Chinese (and have a Chinese phone number at hand).

> [!NOTE]
> If anyone has a QQ account and was able to download the materials, please leave a comment below, and I will get in touch with you ASAP. I would really love to get the official firmware and play with it here.

> Tags: IP2366, Charger, Firmware, QQ, Display

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2366/boards/displayboard?444791101706263214) - created 2026-10-05 - last edited 2026-10-05
