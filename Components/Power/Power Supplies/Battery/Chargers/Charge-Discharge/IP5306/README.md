<img src="/assets/images/charging.png" width="100%" height="100%" />

# IP5306 Power Management IC

> Charger/Discharger for Single Lithium Batteries (Some Versions Programmable)

The [IP5306](materials/ip5306_datasheet.pdf) is a fully integrated *power bank* system-on-chip (SOC) with a charger and a *2A* discharger that works with single *LiIon* cells:

* **Charger**     
  uses a *buck* converter at *750kHz* switching frequency, and charges with a maximum current of **2.1A**. Can be adjusted to *0.05-3.2A* using *I2C* (when the *IP5306* version supports *I2C*, see below for details).
* **Discharge:**     
  uses a *boost* converter at *500kHz* switching frequency and a *5V* output at a maximum current of *2.4A* (12W)

This chip—or one of its many Chinese clones, like the [FM5324GA](materials/fm5324ga_datasheet_en.pdf)—is commonly used in modern DIY modules.


<img src="images/ip5306_chip_hr.png" width="30%" height="30%" />




## Overview
The *IP5306* is found on affordable breakout boards like the [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/) and the [MH-CD42](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/mh-cd42/). 


<img src="images/ip5306_overview_t.png" width="100%" height="100%" />

These modules use *IP5306*-variants that are non-programmable, so you are limited to the chip defaults which are tailored to powerbank use-cases, not so much to power microcontroller projects:

* **High Charging Current:** uses a maximum current of *2.1A* (which may be too much for small *LiIon/LiPo* batteries).
* **Low Current Cut-Off:** turn automatically off when the load current drops below *50mA* for more than *32s* (which can cause problems, i.e. with microcontroller projects that use deep sleep)

### I2C to the rescue
There are more sophisticated versions of *IP5306* that include a [I2C](https://done.land/fundamentals/interface/i2c/) interface. This interface allows microcontrollers to communicate with the chip, and change its settings.

The [PB01](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/) is an example of a very affordable breakout board (below €1.00) that comes with the I2C-enabled IP5306 and exposes the *I2C* pins.

Adjusting the IP5306 configuration provides immense flexibility:

* **Adjust Charge:**    
The maximum charging current can be adjusted in a wide range of *0.05-3.2A*, i.e. you can lower it to match the requirements of small *LiPo* batteries you may be using.
* **Continuous Power:**   
You can tell the chip to keep its 5V output open continuously and not turn off after a while when the load drops below *50mA*. This way, microcontrollers continue to receive power even when they switch to power-saving deep sleep modes.

There are many more things [I2C can read or change](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/#i2c-configuration), i.e. fine-tune discharge protection or battery specifics, determine whether the battery is fully charged, and even manually controlling the charger. 

> [!NOTE]
> One thing the *IP5306* isn't able to do though is provide energy statistics such as actual battery voltage, or measuring currents.


### Power While Charging

Devices can be powered continuously even during charging, with a small power gap occuring when charging ends and the internal boost converter is re-enabled, and an optional push button can be used to *manually* turn power on and off.

<details><summary>How simultaneous charge and discharge works</summary><br/>

This chip **either** use its integrated boost converter to increase the battery voltage to *5V* at a maximum of *2.4A* output (*12W total*), **or** it can step down an external *5V* input to a charging voltage suitable for *Li-Ion* or *Li-Po* batteries. However, the chip can only perform *one* of these conversions at a time because it only has one external coil that is used *either* for *boost* **or** for *buck* operations.

Despite this limitation, the chip supports simultaneous discharging and charging. This means you can operate a connected device both while the chip is charging and when the device is powered by the battery alone.

Understanding the involved switching between different power paths is critical.

### On Battery
Boost converter supplies *5V* at *2.4A* max (12W). The battery must be capable of supplying a peak current of *4A* to support this load. Be aware that smaller batteries or low-cost, low-current *Li-Po* batteries may not be sufficient to meet this demand.

### When Charging
Input voltage powers **both** the charger (at a maximum current of *2.1A* at up to *4.2V*) **and** the load (at a maximum of *12W*).

The total power demand can reach *22W* when accounting for conversion inefficiencies. The external *5V* power supply must provide *4.2A* to handle a combined maximum load. With charging only, a standard *5V 2A* power supply is sufficient.

### Temporary Power Cut
When an external power supply is connected or disconnected, the chip actively switches power paths. During this transition, there may be a **brief power interruption** at the output. This can cause connected devices, such as microcontrollers, to reboot. To prevent this, you can add an appropriately sized capacitor to the output line, which will smooth out any voltage dips during these transitions.


</details>

## Operational Modes

*IP5306* can be in four different operational modes:

| Mode | When Active | LED(s) | 5V Output | I2C Active | Can Charge  | Description |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | remove power source | ❌ | ❌ | ❌ | ❌ | Chip is off, resets to default configuration |
| 1 | add power source | ❌ | ❌ | ❌ | ✅| All configuration changes made by *I2C* are lost. |
| 2 | short-press button, or connect load | ✅ | ✅ | ✅ | ✅| Disconnecting the load for >32s or double-pressing the push button switches to mode 1 |
| 3 | setting bit `1` of I2C register `00` | ❌ | ✅ | ❌ | ✅| *IP5306* stays active and keeps all settings, power output is permanently on |

Mode 3 is available only in *I2C*-enabled versions of *IP5306*.

## Use Cases
Originally, *IP5306* was designed for power banks, and you can of course use it to [design your very own power bank](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/#creating-a-power-bank).

As a spin-off - and often more interesting for DIY makers - you can power your projects with it: *IP5306* turns any regular microcontroller board into a rechargeable and portable battery solution.

Better yet, if you opt for the *I2C*-enabled variant, your microcontroller gains minute control over the power management chip.

### Powering Portable DIY devices
This chip is almost perfect for adding battery power to external *5V* devices such as microcontrollers, [WS2812](https://done.land/components/light/led/programmable/ws2812/) LED strips, DIY flashlights, and more: it is low cost, small, and sufficiently powerful.

#### Basic IP5306...
The generic *IP5306* (without *I2C* interface) that is found on [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/) and [MH-CD42](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/mh-cd42/) breakout boards is perfect for **power-hungry projects** that do not continuously drop below *50mA* and use a **large battery** that can sustain the up to *2.1A charging rate* (i.e. *18650 LiIon*).

> [!IMPORTANT]
> Keep in mind that the popular small *LiPo*-cells often used in microcontroller projects typically have a maximum recommended charging rate of **0.3C**, so a *1000mAh* cell shouldn't be charged with more than *350mA*.

#### ...versus I2C-Enabled IP5306
If you want to power microcontroller projects that use *deep sleep*, or any other project that may consume less than *50mA*, and/or if you are using *LiPo* batteries smaller than *3000mAh*, you should use utilize a **IP5306** with [enabled I2C interface](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/#i2c-configuration).


> [!NOTE]
> Even *3000mAh LiPo* batteries work best when not charged with more than *1000mA*. The *IP5306* uses up to *2.1A*. For *3000mAh* and more *LiPo* batteries, this is considered "quick charging" (which may be desireable but stresses the battery), but it typically is still safe. Smaller *LiPo* batteries may overcharge at *2.1A* and then pose a fire hazard.


The [PB0A](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/) breakout board has such a *IP5306-variant* and exposes the *I2C* interface, so your microcontroller can adjust IP5306 settings to match your needs.



### Creating a Power Bank
**IP5306** was originally created to drive power banks (and can be found in many commercial entry-level power banks).

#### ESP32-Controlled Power Bank
There are even some commercial [ESP32-programmable power banks](https://docs.m5stack.com/en/core/basic). The links provide technical documentation and schematics that may help interface your own *ESP32* microcontrollers via *I2C* to *IP5306*:

* **I2C Programming:**  [C++ code](https://github.com/m5stack/M5Stack/blob/master/src/utility/Power.cpp) illustrating how the power bank's *ESP32* microcontroller communicates with the *IP5306* registers via *I2C*.
* **Schematics:** [Circuitry](https://community.m5stack.com/assets/uploads/files/1515402963959-97994060-2969-49dc-ad9c-7b3887d95a17-image.png) showing the wiring and implementation, including the use of *BSS138* MOSFETs used as a level shifter to translate between the battery voltage and the *3.3V* used by the *ESP32* microcontroller.

You, too, can use breakout boards like the [PB0A](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/) to build your own sophisticated and microcontroller-operated power bank. Just keep in mind the limitation: *IP5306* works with *1S LiIon Cells* only, and it outputs *5V* only - no higher voltages or *USB Power Delivery* features..

#### Separate Input and Output Connectors
Also note the design of the *IP5306* power paths: the chip uses separate connectors for *input* (charging) and *output* (5V output).

This is great for scenarios where you want to charge while keeping a device running, but it also means that your power bank will have separate connectors for charging and discharging.

## BMS and Protection

The *IP5306* has the most important security features built in:

### Output protection

* **Over-Current detection:**    
  Output voltage **<4.4V** for over *30ms*
* **Short-Circuit Protection:**   
  Output current **>4A** for over *200us*

### Battery protection

* **Over-Discharge:**     
  turns off battery when voltage **<3.25V** (may vary with internal configuration)
* **Over-Charge:**   
  Charge termination at *4.2V*, safety timer cuts off at **<24h**
* **Under-Voltage:**    
  Trickle charge (*100mA*) when battery voltage *<2.9V*
* **Over-Voltage:**    
  Turns off charging when battery voltage **>4.2V**
* **Over-Current:**    
  Limits charging to **2.1A** max., and limits further if charger voltage drops too much
* **Auto-Recharge:**     
  Starts when battery voltage *<4.1V*

### General protection

* Thermal shutdown (at *125C*)


### Missing Protections
For a safe and robust power bank, *IP5306* lacks these two protections:

* **Temperature Sensor:**   
  No support for external temperature sensors. External temperature sensors typically detect catastrophic battery failures during charging.   
* **Revers Battery Polarity:**     
  Connecting the battery in reverse polarity destroys the chip. Since rechargeable batteries are typically not serviceable in portable devices and powerbanks, such a protection is normally not needed (with proper assembly). 
  
To cover this:

* Use an affordable [Dallas](https://done.land/components/data/sensor/temperature/dallas/) temperature sensor (or similar). They can be connected directly to your microcontroller, and in case of excessive temperatures, your microcontroller can disable the charger via *I2C*.
* Add an *ideal diode* if you do not hard-wire the battery (in which case there would be the risk of users not replacing the battery in correct polarity).



## Charging
Charging is a separate feature and can be utilized independently from other features if you wish.

You could, for instance, use the *IP5306* solely for charging *LiIon/LiPo* cells, possibly as a replacement for a simple *TP4056* if you want higher charging rates:

| Item                         | Description                    |
|------------------------------|--------------------------------|
| Input Voltage                | *5-5.5V*                      |
| Charging Current             | *2.1A*                        |
| Charge Switching Freq.       | *750kHz*                      |
| Charging Cut-Off Voltage     | *4.2V* or *4.35V* (configurable)   |
| Charging Efficiency          | *91%*                         |
| Short Circuit Protection     | Yes                           |
| Low Voltage Recovery         | Yes                           |
| Battery Reverse Polarity Prot.| No                           |
| Charging While Discharging   | Yes                           |

> [!IMPORTANT]
> If you are using the *IP5306* as a simple charger, the lacking *battery reverse polarity protection* becomes an issue. Either make sure the battery connectors or bays are fool-proof, or add an *ideal diode* to the battery wiring.

### Initiating Charging
Charging starts automatically when a power supply is connected, and the battery voltage is *>2.8V* and *<4.2V*. The external power supply must provide *5V* at *2A* minimum.

During charging, the indicator LED show charging progress in *25%* increments, and one LED is blinking at *1Hz*.

Charging phases:
1. **Deep Discharge Recovery:** If battery voltage is below *2.8V*, the chip supplies *180mA* until safe voltage levels are reached.
2. **Constant Current:** For voltage between *2.8V* and the cut-off, the chip charges at *2.4A*.
3. **Constant Voltage:** Once the battery reaches *4.2V*, current tapers off until it falls below *100mA* or 24 hours elapse.



Once charging has completed, all four indicator LEDs light solidly.

> [!NOTE]
> I2C-enabled breakout boards, like the [PB01](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/), use the status LED connectors as *I2C* interface. These boards use additional helper ICs to drive a WS2812 RGB LED which typically pulsates in changing color, indicating the charging state.

A new charging cycle is initiated automatically once the battery voltage drops below *4.1V*.

### "Dead" Batteries
When a battery has accidentally been *deeply discharged* (i.e. by keeping it in storage for too long so that normal self-discharge could cause a voltage drop below *2.8V*), it can no longer absorb the normal amount of energy. 

That's why many chargers refuse to charge such batteries at all. Charging such a battery with normal charging rates would convert the excess energy into heat and can subsequently easily cause a fire or explosion. 

*IP5306* can deal with over-discharged batteries. When the battery voltage is too low for normal charging, its *recovery charge mode* reduces the charging rate and charges in intervals. 

This is not guaranteed to work of course, it is just a best effort. If the battery was damaged beyond recovery, *IP5306* aborts the *recovery charge mode* after 24 hours.



## Supplying Power

*IP5306* has a robust and efficient boost converter. It boosts the battery voltage to *5V* at up to *2A*. The boost converter is equipped with *over-current* and *short circuit* protection.

<img src="images/ip5306_overview2_t.png" width="100%" height="100%" />



| Item                  | Description                    |
|-----------------------|--------------------------------|
| Output Voltage        | *5-5.15V* (USB-A, 5V pads)    |
| Output Voltage Ripple | *50mV*                        |
| Output Current        | max. *2.4A*                   |
| Indicator LED Current | *4mA* each                    |
| Off Current           | *<50µA*                       |
| Standby Current       | *<100µA*                      |
| Load Removal Detection| *<45mA* for *32s*             |
| Boost Switching Freq. | *500kHz*                      |
| Boost Efficiency      | *92.5%*                       |
| Short Circuit Prot.   | Yes                           |
| Other Protections     | Over-Current, Over-Voltage    |


### Automatic Load Detection
When a load is connected to the power output, the boost converter activates and begins supplying power. This requires the load to consume significant currents. Light loads may require to *manually* turn on the power output by pressing a push button (connected to pins `K` and `GND` on most breakout boards). This behavior is inline with typical powerbanks.

When the load is removed (or the load drops below *45mA* for more than *32s*), the boost converter automatically shuts down to conserve battery power.

> [!NOTE]
> The *I2C*-enabled versions of *IP5306* can adjust all this. Specifically, *IP5306* can be switched to an *always-on* mode that works also with light loads (*I2C* register `00`, bit `1` set to `1`). When *always-on* is enabled, the on-board LED still turns off after the designated time (*32s* by default, can be shortened via *I2C* to *8s*), but the *5V* output remains active, and the *IP5306* preserves all other changes that have been made via *I2C*.

While power is being supplied, four LEDs indicate the battery's *state of charge* in *25%* increments. Each LED is supplied with *4mA*. *I2

When the battery's *state of charge* drops below *3%*, one LED will blink at *2Hz* to alert the user. If the battery voltage falls further, below *2.8-2.9V*, the *over-discharge* protection feature turns off the power output to prevent damage to the battery.

| LED | *On* at battery voltage *(V)* |
| --- | --- |
| 1 | *>3.36* |
| 2 | *>3.57* |
| 3 | *>3.65* |
| 4 | *>3.91* |

> [!IMPORTANT]
> *I2C*-enabled breakout boards often use a single pulsating WS2812-RGB LED.

### Power Consumption

Operating the boost converter requires approximately *100µA*. 

To save even more energy, the chip can minimize power consumption to just *30-50µA* when disabling the power output (quiescent current).

That's why by default, *IP5306* has an active *low load detection*: once the load drops below 50mA for more than 32 seconds, the chip switches off the boost converter and cuts power output.

Like mentioned before, if this power-savings feature causes problems because your load requires low current (i.e. deep sleep), you have two options:
* **Manual:**    
  pull pin `K` low every 30 seconds, either by external discrete logic, or by waking up your MCU every 30 seconds.
* **Reconfigure:**   
  if you use an *I2C*-enabled *IP5306*, set bit `1` of register `00` to keep the boost converter turned on all the time. Be aware that the power LED(s) on the board will turn off, yet the power output stays enabled.

Two operational modes manage this behavior:

| Mode | Boost Converter | Indicator LED | Power Supply | Quiescent Power |
| --- | --- | --- | --- | --- |
| **Standby Mode** | on | on | available | 100µA |
| **Off Mode** | off | off | not available | 30-50µA |

The chip automatically transitions between these modes:

* **Load Detection:** The chip continuously monitors the power output. When it detects a load, it activates *Standby Mode* to supply power to the connected device.
* **Load Removal Detection:** If the load drops below *45mA* for a continuous period of at least *32 seconds*, the chip shuts off the boost converter and switches to *Off Mode*.



### Automatic Power-off

The chip automatically cuts off power in the following scenarios (**when operating on battery power**):

* **Low Load:** If the load drops below *45mA* for at least *32 seconds*, the chip assumes the load is disconnected and turns off the boost converter.
* **High Load:** If the load exceeds *4A*, the chip performs an emergency shutdown within *200µs* to prevent damage.
* **Battery Empty:** If the battery voltage falls below *2.8-2.9V*, the chip disables the boost converter to protect the battery from *over-discharge*.
* **Manual:** Using a push button signal (see below), the chip turns off the boost converter, even with the load still connected. This is useful for turning off permanently connected devices.

While charging, the output **is always active**.


## Push Button Support
An optional push button can be connected to the *K* and *GND* solder pads on most boards. While not mandatory, it allows manual control over power output and can access a special "torch mode".


<img src="images/ip5306_x-150_button.png" width="40%" height="40%" />

**Always use a resistor** in series with the push button to limit potential current flow:  

- In some chip configurations, an optional *flashlight function* may be present. In this setup, an LED is connected in parallel with the push button. Pressing the button in such configurations effectively short-circuits the LED, which can result in high currents. These currents may damage the button, the LED, or the board itself.  

- To prevent such issues, use a resistor with a value of *2kΩ* or *10kΩ* in series with the button. Some chips can *actively differentiate* between these two resistor values. Depending on the resistance used, the chip may either *activate* or *deactivate* the flashlight function.



> [!NOTE]
> A user reported that pressing the push button produced a cloud of smoke. It turned out this user had taken *two breakout boards* and connected both push button wires to *one push button* to control both boards at the same time. While this is perfectly ok to do, the user did not add *10kΩ* resistors. So when the push button was pressed, a temporary *short circuit* occured in *both boards*, resulting in high currents flowing across the push button. Since DIY push buttons typically are for logic levels only, they can easily burn up when exposed to such high currents. You now know that with this board, it is crucial to limit current flow with at least a *2kΩ* resistor.


### Types of Button Presses
All chip variants distinguish three fundamental key press patterns:

* **Short press:** *>30ms but <=2s*
* **2x Short press**
* **Long press:** *>2s*



### Manually Control Output Power
A *short press* (*>30ms* but *<200ms* impulse) enables power output in all chip variants. Use a short press to turn on a device, or to reset the *load removal detection timer* before it can kick in on light loads *<45mA*.

> [!TIP]
> With low loads (*<50mA*), your logic could send an impulse (*<30ms <2s*, simulated short press) in *<30s* intervals to prevent unintentional power off.

Manually *turning off* the boost converter varies between chip variants. With the original *IP5306*, this requires a *long press*, whereas clones like the *FM5324GA* may require two short presses instead.

> [!NOTE]
> Button presses only control the internal boost converter. The power output remains *always active* when the chip is connected to an external power supply (i.e., during charging).

### Torch Mode
A less commonly noticed feature of this chip is its ability to support an external *flashlight LED*. When present, the LED is connected *in parallel* with the push button.



<img src="images/ip5306_x-150_button-torch_led.png" width="40%" height="40%" />

This *torch mode* is the reason why the push button must always be used with a *2kΩ* or *10kΩ* resistor in series. Without this resistor, activating the *torch mode*—either intentionally or accidentally—can result in large currents, as pressing the push button would effectively short-circuit the flashlight LED.

On certain chip models, the *torch mode* may either be permanently disabled or configurable by using a *2kΩ* resistor instead of a *10kΩ* in series with the push button.

| Variant | Short Press | 2x Short Press | Long Press | Remark |
| --- | --- | --- | --- | --- |
| 1 | turns on power output and indicator LEDs | toggles flashlight | turns off power | *IP5306* |
| 2 | turns on power output and indicator LEDs | turns off power output | toggles flashlight | *FM5324GA*: use *10kΩ* in series with push button |
| 3 | turns on power output and indicator LEDs | turns off power output | no function | *FM5324GA*: use *2kΩ* in series with push button |

> [!NOTE]  
> Keep in mind that chips are often manufactured to meet specific customer requirements. If your chip has a different marking, it may function similarly to the *IP5306* but exhibit slight variations, such as different push button actions or modified indicator LED behavior.  

## Issues

Here are the top issues with this chip and the boards that are using it:

* **User Errors:** 
  * **Battery:** when you add a battery that is too small and cannot handle the high charge and discharge currents, charging the battery may not work, and there is a fire hazard.
  * **Push Button:** when you add a push button and omit a *10kΩ* series resistor, when you press the button, high currents can flow and damage the button.

* **Design Issues:**
  * **Load Removal Discovery:** with small loads *<50mA*, the unit cuts power after *32s*. This is by design. To work around this, you can have your microcontroller ground the push button key (via a *10kΩ* resistor, or you might ruin your microcontroller) in intervals of *<30s*. This resets the load removal discovery timer. Make sure you ground the pin for at least *50ms* in order to be considered a *short press*. Alternatively, you can keep the pin permanently to *ground* as described below.
  * **Various Chip Variants:** the fact that boards are produced with a variety of generic and cloned chips instead of the original *IP5306* can cause issues due to slight variations in behavior. 
  * **Wake-Up Issues:** there are reports with boards using the *FM5324GA*, that after prolonged operation for *24-48hrs*, the board may not automatically wake up from standby anymore when a new load is connected.     
  
     The reason is not yet clear. A remidy is to manually *short press* the push button or cause a reset of power paths by supplying a charging power. You might be able to work around this by keeping the chip active all the time (preventing *Off* mode) at the expense of a slightly higher quiescent power consumption via the following circuit (which may also help with continuously operating low loads *<50mA*):

## I2C Configuration
**Specific** versions of the *IP5306* may behave differently and can have additional features, most notably an *I2C* interface for advanced configuration. Please note that most "normal" breakout boards use the default *IP5306* which has **no I2C interface**.

The following applies only to *IP5306* chips with enabled *I2C* interface:

### I2C Settings

| Item | Description |
| --- | --- |
| Address | `0x75` |
| Speed | 400Kbps |
| Address Width | 8 bit |
| Data Width | 8 bit |
| Bit order | MSB first |
| SCK/SCL | pin `L1`, driven by master (connected MCU), pull up to VCC via 2.2K resistor |
| SDA | pin `L2`, pull up to VCC via 2.2K resistor |
| IRQ | pin `L3`, *high* when in working status/*low* when in sleep state |


### Registers

Here is a list of registers accessible via *I2C* on *IP5306* chips with enabled *I2C* interface:

#### REG_SYS_0: `0x00` Input/Output Enable

| Bit | Description | Default |
| --- | --- | --- |
| 7, 6 | reserved |   |
| 5 | **Boost Enable:** 1: enable |  1 |
| 4 | **Charger Enable:** 1: enable |  1 |
| 3 | reserved |  1 |
| 2 | **Auto Power On When Load Connected:** 1: enable | 1 |
| 1 | **Boost Output Normally Open:** 1: enable |  1 |
| 0 | **Button Shutdown Enable:** 1: enable |  0 |

**Boost Output Normally Open**, when enabled, keeps the boost converter active permanently. When this mode is active, light loads no longer cause the power output to be turned off after *32s*.

#### REG_SYS_1: `0x01` Buttons

| Bit | Description |  Default |
| --- | --- | --- |
| 7 | **Boost Closure:** 1: press/ 0: short press twice |  0 |
| 6 | **WLED Flashlight:** 1: short press twice/ 0: press | 0  |
| 5 | **Short Press Switch Boost:** 1: enable | 0 |
| 4,3 | reserved |  |
| 2 | **Turn On Boost After Unplugging:** 1: enabled |  1 |
| 1 | reserved |  |
| 0 | **3.0V Low Voltage Shutdown:** 1: enabled |  1 |


#### REG_SYS_2: `0x02` Light Load Shutdown

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6,5 | reserved |   |
| 4 | **Long Press Time:** 0: 2sec/ 1: 3sec | 0 |
| 3,2 | **Light Load Shutdown:** 11: 64sec/ 10: 16sec/ 01: 32sec/ 00: 8sec | 0 |
| 1,0 | reserved |  |


#### REG_CHG_0: `0x020` Stop Charging

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6,5,4,3,2 | reserved |   |
| 1,0 | **Charge Stop Voltage:** 11:4.2/4.305/4.35/4.395 / 10:4.185/4.29/4.335/4.38 / 01:4.17/4.275/4.32/4.365 / 00:4.14/4.26/4.305/4.35 V  | 10 |

#### REG_CHG_1:  `0x021` Stop Charging

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6 | **End Stop Charging:** 11: 600mA/ 10: 500mA/ 01: 400mA/ 00: 200mA |  01 |
| 5 | reserved | 0 |
| 4,3,2 | **Charging Under Voltage:** 111: 4.8V/ 110: 4.75V/ 101: 4.7V/ 100: 4.65/ 011: 4.6V/ 010: 4.55V/ 001: 4.5V/ 000: 4.45V  | 101  |
| 1,0 | reserved  |   |


#### REG_CHG_2: `0x22` Battery Adjustment

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6,5,4 | reserved |   |
| 3,2 | **Battery Voltage:** 11: 4.4V / 10: 4.35V / 01: 4.3V / 00: 4.2V | 00 |
| 1,0 | **CV Charging:** 11: 42mV/ 10: 28mV / 01: 14mV / 00: none  | 00  |


#### REG_CHG_3: `0x23` Constant Current Charging

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6 | reserved |   |
| 5 | **CC End Detection:** 0: BAT / 1: VIN | 1 |
| 4,3,2,1,0 | reserved |  |

#### REG_CHG_4: `0x24` Charging Current

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6,5 | reserved |   |
| 4,3,2,1,0 | **Charger Current:** I=0.05 + `0`*0.1 + `1`*0.2 + `2`*0.4 + `3`*0.8 + `4`*1.6A |  |



#### REG_READ_0: `0x70` Charging Status

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6,5,4 | reserved |   |
| 3 | **Charging Status:** 1: charging (**read only**)|  |
| 2,1,0 |reserved  |   |

#### REG_READ_1: `0x71` Charging Status

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6,5,4 | reserved |   |
| 3 | **Full Charge:** 1: fully charged (**read only**)|  |
| 2,1,0 |reserved  |   |

#### REG_READ_2: `0x72` Charging Status

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6,5,4,3 | reserved |   |
| 2 | **Light Load Detection:** 1: light load (**read only**)|  |
| 1,0 |reserved  |   |

#### REG_READ_3: `0x77` Key Press Detection

| Bit | Description |  Default |
| --- | --- | --- |
| 7,6,5,4,3 | reserved |   |
| 2 | **Double Click:** 1: has occured (write `1` to clear) |  |
| 1 | **Long Press:** 1: has occured (write `1` to clear) |  |
| 0 | **Short Press:** 1: has occured (write `1` to clear) |  |

#### REG_READ_4: `0x78` LED Indicator

| Bit | Description |  Default |
| --- | --- | --- |
| 7 | **LED4:** 0: on (**read-only**) |   |
| 6 | **LED3:** 0: on (**read-only**) |   |
| 5 | **LED2:** 0: on (**read-only**) |   |
| 4 | **LED1:** 0: on (**read-only**) |   |
| 3,2,1,0 | reserved |  |

## I2C Libraries

If you want to read and write configuration data via *I2C*, you need to know:

* **I2C Register:** what is the number of the register that holds the required information?
* **Bit(s):** which bit(s) store the desired information? There can be other bits in the same register that control other things.
* **Meaning:** how are the bit values actually *interpreted*? So what does a `0` or `1` in a bit actually stand for, or do?

Libraries can help you very much as they do much of this work for you, and provide simple-to-use functions.

> [!IMPORTANT]
> Keep in mind that in order to successfully use any of these libraries, you need to physically correctly **wire up** the *IP5306* breakout board to your microcontroller, **and** your breakout board must be using a **I2C-enabled IP5306**. Many cheap boards use *IP5306* variants **without I2C interface** (as it is not needed). In this case, you cannot use *I2C*, and below libraries won't help you.     



### Basic IP5306 I2C Control Library (Example #2)
[IP5306-arduino](https://github.com/Al1c3-1337/IP5306-arduino) is a very simple yet very efficient library that works for a large range of microcontrollers. It provides a range of functions covering all controllable *I2C* features: 


````
uint8_t IP5306_GetKeyOffEnabled() 
uint8_t IP5306_SetKeyOffEnabled(uint8_t value)                //0:dis,*1:en
uint8_t IP5306_GetBoostOutputEnabled()         
uint8_t IP5306_SetBoostOutputEnabled(uint8_t value)           //*0:dis,1:en
uint8_t IP5306_GetPowerOnLoadEnabled()          
uint8_t IP5306_SetPowerOnLoadEnabled(uint8_t value)           //0:dis,*1:en
uint8_t IP5306_GetChargerEnabled()      
uint8_t IP5306_SetChargerEnabled(uint8_t value)               //0:dis,*1:en
uint8_t IP5306_GetBoostEnabled()          
uint8_t IP5306_SetBoostEnabled(uint8_t value)                 //0:dis,*1:en
uint8_t IP5306_GetLowBatShutdownEnable()        
uint8_t IP5306_SetLowBatShutdownEnable(uint8_t value)         //0:dis,*1:en
uint8_t IP5306_GetBoostAfterVin()             
uint8_t IP5306_SetBoostAfterVin(uint8_t value)                //0:Closed, *1:Open
uint8_t IP5306_GetShortPressBoostSwitchEnable() 
uint8_t IP5306_SetShortPressBoostSwitchEnable(uint8_t value)  //*0:disabled, 1:enabled
uint8_t IP5306_GetFlashlightClicks()          
uint8_t IP5306_SetFlashlightClicks(uint8_t value)             //*0:short press twice, 1:long press
uint8_t IP5306_GetBoostOffClicks()              
uint8_t IP5306_SetBoostOffClicks(uint8_t value)               //*0:long press, 1:short press twice
uint8_t IP5306_GetLightLoadShutdownTime()    
uint8_t IP5306_SetLightLoadShutdownTime(uint8_t value)        //0:8s, *1:32s, 2:16s, 3:64s
uint8_t IP5306_GetLongPressTime()              
uint8_t IP5306_SetLongPressTime(uint8_t value)                //*0:2s, 1:3s
uint8_t IP5306_GetChargingFullStopVoltage()     
uint8_t IP5306_SetChargingFullStopVoltage(uint8_t value)      //0:4.14V, *1:4.17V, 2:4.185V, 3:4.2V (values are for charge voltage 4.2V, 0 or 1 is recommended)
uint8_t IP5306_GetChargeUnderVoltageLoop()                    //Automatically adjust the charging current when the voltage is greater than the set value
uint8_t IP5306_SetChargeUnderVoltageLoop(uint8_t value)       //Vout=4.45V + (v * 0.05V) (default 4.55V) //When charging maximum current, the charge is less than the set value. Slowly reducing the charging current to maintain this voltage
uint8_t IP5306_GetEndChargeCurrentDetection() 
uint8_t IP5306_SetEndChargeCurrentDetection(uint8_t value)    //0:200mA, 1:400mA, *2:500mA, 3:600mA
uint8_t IP5306_GetVoltagePressure()            
uint8_t IP5306_SetVoltagePressure(uint8_t value)              //0:none, 1:14mV, *2:28mV, 3:42mV (28mV recommended for 4.2V)
uint8_t IP5306_GetChargeCutoffVoltage()        
uint8_t IP5306_SetChargeCutoffVoltage(uint8_t value)          //*0:4.2V, 1:4.3V, 2:4.35V, 3:4.4V
uint8_t IP5306_GetChargeCCLoop()               
uint8_t IP5306_SetChargeCCLoop(uint8_t value)                 //0:BAT, *1:VIN
uint8_t IP5306_GetVinCurrent()                              
uint8_t IP5306_SetVinCurrent(uint8_t value)                   //ImA=(v*100)+50 (default 2250mA)
uint8_t IP5306_GetShortPressDetected()                      
uint8_t IP5306_ClearShortPressDetected()                    
uint8_t IP5306_GetLongPressDetected()                     
uint8_t IP5306_ClearLongPressDetected()                   
uint8_t IP5306_GetDoubleClickDetected()                     
uint8_t IP5306_ClearDoubleClickDetected()                   
uint8_t IP5306_GetPowerSource()                               //0:BAT, 1:VIN
uint8_t IP5306_GetBatteryFull()                               //0:CHG/DIS, 1:FULL
uint8_t IP5306_GetLevelLeds()                                 //LED[0-4] State (inverted)
uint8_t IP5306_GetOutputLoad()                                //0:heavy, 1:light
````

This library is so small that you could in fact incorporate the code into your own source code. Here is what the library does:

#### Helpers

The library comes with four helpers:

* **I2C Registers:** it defines the available *I2C* registers for you:    
  ````
  #define IP5306_REG_SYS_0    0x00
  #define IP5306_REG_SYS_1    0x01
  #define IP5306_REG_SYS_2    0x02
  #define IP5306_REG_CHG_0    0x20
  #define IP5306_REG_CHG_1    0x21
  #define IP5306_REG_CHG_2    0x22
  #define IP5306_REG_CHG_3    0x23
  #define IP5306_REG_CHG_4    0x24
  #define IP5306_REG_READ_0   0x70
  #define IP5306_REG_READ_1   0x71
  #define IP5306_REG_READ_2   0x72
  #define IP5306_REG_READ_3   0x77
  #define IP5306_REG_READ_4   0x78
  ````
* **Bit Banging:** it defines two mathematical helper functions that help you extract bits from a byte, and changing bits in an existing byte:    
  ````c++
  uint8_t ip5306_get_bits(uint8_t reg, uint8_t index, uint8_t bits) {
      int value = ip5306_get_reg(reg);
      if(value < 0) {
        return 0;
      }
      return (value >> index) & ((1 << bits)-1);
  }

  void ip5306_set_bits(uint8_t reg, uint8_t index, uint8_t bits, uint8_t value) {
      uint8_t mask = (1 << bits) - 1;
      int v = ip5306_get_reg(reg);
      if(v < 0) {
          //Serial.printf("ip5306_get_reg fail: 0x%02x\n", reg);
          return;
      }
      v &= ~(mask << index);
      v |= ((value & mask) << index);
        if(ip5306_set_reg(reg, v)) {
      }
  }
  ````    

* **I2C Read/Write:** it defines two generic functions to read or write a byte to an *I2C* register:     
  ````c++
  int ip5306_get_reg(uint8_t reg){
      Wire.beginTransmission(0x75);
      Wire.write(reg);
      if(Wire.endTransmission(false) == 0 && Wire.requestFrom(0x75, 1)){
          return Wire.read();
      }
      return -1;
  }

  int ip5306_set_reg(uint8_t reg, uint8_t value){
      Wire.beginTransmission(0x75);
      Wire.write(reg);
      Wire.write(value);
      if(Wire.endTransmission(true) == 0){
          return 0;
      }
      return -1;
  }
  ````

#### Specific I2C Functions
With the three helpers from above, it then defines all specific functions that you can use to control the *IP5306* in the [header file](https://github.com/Al1c3-1337/IP5306-arduino/blob/master/IP5306.h), like this one:

````c++
#define IP5306_GetKeyOffEnabled()               ip5306_get_bits(IP5306_REG_SYS_0, 0, 1)
````

Here is how this works:

* The function **IP5306_GetKeyOffEnabled()** is actually calling the generic **ip5306_get_bits()**
* It is asking to return **one bit** (`1`) from index position 0 (`0`) of register *0x00* (`IP5306_REG_SYS_0`).
* According to the [IP5306 register map](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/#reg_sys_0-0x00-inputoutput-enable), bit `0` controls **Button Shutdown Enable**:

| Button Shutdown Enable | Value |
| --- | --- |
| 0 | disabled |
| 1 | enabled |

> What exactly **Button Shutdown Enable** *does* is often not well documented, even if you dig through the official [I2C Register Map](materials/ip5306_i2c_registers.pdf), and requires some guessing and experimenting. In this particular case, **Button Shutdown Enable** controls whether the button that can be connected to the *IP5306* can serve to *manually turn off* the power output, typically by *double pressing* it. **IP5306_GetBoostOffClicks()** and **IP5306_SetBoostOffClicks()** coincidentally control whether shutting off the power is controlled by a double-click or a long press.    

As you see, the way this library is organized is working well but requires intimate knowledge of the bit definitions and their meaning. Prepare to keep the [I2C Register Map](materials/ip5306_i2c_registers.pdf) open in parallel, especially when you deal with configuration items that use more than one bit.

For example, **IP5306_SetLightLoadShutdownTime()** can set the timeout after which the IP5306 shuts off when a load *<50mA* is connected:

````c++
#define IP5306_SetLightLoadShutdownTime(v)      ip5306_set_bits(IP5306_REG_SYS_2, 2, 2, v)//0:8s, *1:32s, 2:16s, 3:64s
````

This setting is controlled by *two* bits, and the comment explains the bits:

| Light Load Shutdown Time (seconds) | Value |
| --- | --- |
| 8 | 0 |
|16 | 2 |
| 32 | 1 |
| 64 | 3 |

You just need to know what the expected values are. The function calls **ip5306_set_bits()** with the appropriate arguments. In this particular case, **two** bits (`2`) need to be written to I2C register *0x02* (`IP5306_REG_SYS_2`) starting at index position 2 ( `2`). Again, you can [look up](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/#reg_sys_2-0x02-light-load-shutdown) the details for this *I2C register* and its bits and definitons.


### Sophisticated IP5306 I2C Library 
[IP5306_I2C](https://github.com/AvinasheeTech/IP5306_I2C) does basically what the previous library did, however this author has also *typed* many of the arguments and return values. 

So instead of having to guess what a specific bit actually means, you find *structs* (self-defined structured records).

Here is the list of functions this library provides:

````
void boost_mode(uint8_t boost_en);
void charger_mode(uint8_t charger_en);
void power_on_load(uint8_t power_on_en);
void boost_output(uint8_t output_val);
void button_shutdown(uint8_t shutdown_val);

void boost_ctrl_signal(uint8_t press_val);
void flashlight_ctrl_signal(uint8_t press_val);
void short_press_boost(uint8_t boost_en);
void boost_after_vin(uint8_t val);
void low_battery_shutdown(uint8_t shutdown_en);

void set_long_press_time(uint8_t press_time_val);
void set_light_load_shutdown_time(uint8_t shutdown_time);

void set_charging_stop_voltage(uint8_t voltage_val);
void end_charge_current(uint8_t current_val);
void charger_under_voltage(uint8_t voltage_val);

void set_battery_voltage(uint8_t voltage_val);
void set_voltage_pressure(uint8_t voltage_val);
void set_cc_loop(uint8_t current_val);

uint8_t check_charging_status(void);
uint8_t check_battery_status(void);
uint8_t check_load_level(void);
uint8_t short_press_detect(void);
uint8_t long_press_detect(void);
uint8_t double_press_detect(void);
````

When you look at the function signatures and compare them with the previous library, you'll see that function arguments are *typed*. The previous library used `uint8_t` for all arguments, and you had to know the appropriate byte values (and bit-bang the appropriate bits).

Let's take a closer look what is different in this library:

#### Easier Handling
Instead of using just *bytes* for everything, this library defines *structs* (structured data records) per *I2C* register. Here is an example for `0x00`:

````c++
/*SYS_CTL0*/
union{
    struct{
     uint8_t BUTTON_SHUTDOWN             : 1;
     uint8_t SET_BOOST_OUTPUT_ENABLE     : 1;
     uint8_t POWER_ON_LOAD               : 1;
     uint8_t RSVD                        : 1;
     uint8_t CHARGER_ENABLE              : 1;
     uint8_t BOOST_ENABLE                : 1;
     uint8_t RSVD2                       : 2;
       
    }bits;

    uint8_t reg_byte;

}reg_SYS_CTL0_t;
````

Now all the bits inside this byte are *named*, and directly accessible.

Likewise, when entities are configured using more than one bit, like the *LightLoadShutdownTime* from before in register `0x02`, a *struct* simplifies the handling enormously:

````c++
/*SYS_CTL2*/
union{
    struct{
       uint8_t RSVD                              : 2;
       uint8_t LIGHT_LOAD_SHUTDOWN_TIME          : 2;
       uint8_t LONG_PRESS_TIME                   : 1;
       uint8_t RSVD2                             : 3;  
    }bits;

    uint8_t reg_byte;
}reg_SYS_CTL2_t;
````

You can now read the relevant two bits via `LIGHT_LOAD_SHUTDOWN_TIME`. Unfortunately, the author is still returning `uint8_t`, so while it is now much easier to *read* the required bits, you still need to interpret the resulting byte yourself.

*Setting* (writing) these bits is easier since the author has defined constants:

````c++
/*SHUTDOWN_TIME_VALUE*/
#define SHUTDOWN_8s                                 0
#define SHUTDOWN_32s                                1
#define SHUTDOWN_16s                                2
#define SHUTDOWN_64s                                3
````

#### Room for Improvement
It would take only a small step to improve this library even further, so you would no longer need to look up values in *I2C register maps*. 

This is how the library currently works:

````c++
union {
    struct {
        uint8_t RSVD                      : 2;
        uint8_t LIGHT_LOAD_SHUTDOWN_TIME  : 2;
        uint8_t LONG_PRESS_TIME           : 1;
        uint8_t RSVD2                     : 3;
    } bits;
    uint8_t reg_byte;
} reg_SYS_CTL2_t;

/* SHUTDOWN_TIME_VALUE */
#define SHUTDOWN_8s   0
#define SHUTDOWN_32s  1
#define SHUTDOWN_16s  2
#define SHUTDOWN_64s  3
````

And this is how a more modern and object-oriented approach would look like:

````c++
// define possible values as a enum:
enum class ShutdownTime : uint8_t {
    S8  = 0,  // 8 seconds
    S32 = 1,  // 32 seconds
    S16 = 2,  // 16 seconds
    S64 = 3   // 64 seconds
};

// define the structure of the byte that the particular I2C register uses:
struct SYS_CTL2_Bits {
    uint8_t RSVD                      : 2;
    uint8_t LIGHT_LOAD_SHUTDOWN_TIME  : 2;
    uint8_t LONG_PRESS_TIME           : 1;
    uint8_t RSVD2                     : 3;
};

// create a union (map the raw byte to the struct): 
union reg_SYS_CTL2_t {
    SYS_CTL2_Bits bits;
    uint8_t reg_byte;
};

// create type-safe setter and getter functions:
inline void set_shutdown_time(reg_SYS_CTL2_t& reg, ShutdownTime time) {
    reg.bits.LIGHT_LOAD_SHUTDOWN_TIME = static_cast<uint8_t>(time);
}

inline ShutdownTime get_shutdown_time(const reg_SYS_CTL2_t& reg) {
    return static_cast<ShutdownTime>(reg.bits.LIGHT_LOAD_SHUTDOWN_TIME);
}
````

From a users perspective, the code would now be simplified and type-safe, with no room for misunderstandings and unclear values:

````c++
// define variable to hold the I2C register 0x02:
reg_SYS_CTL2_t reg{};

// Set shutdown time to 16 seconds
set_shutdown_time(reg, ShutdownTime::S16);

// Read shutdown time
ShutdownTime t = get_shutdown_time(reg);
if (t == ShutdownTime::S16) {
    // Do something
}
````




## Materials

[IP5306 Datasheet](materials/ip5306_datasheet.pdf)     
[IP5306 I2C Register Map](materials/ip5306_i2c_registers.pdf)
[FM5324GA (IP5306 Clone) Translated English](materials/fm5324ga_datasheet_en.pdf) *(translated)*       
[FM5324GA (IP5306 Clone) Chinese Original](materials/fm5324ga_datasheet.pdf) *(Chinese original)*  

> Tags: Charger, Li-Ion, Li-Po, Boost Converter, 2A, USB, 1S, IP5306, FM5324GA, Torch Mode, Push Button

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306?313487011513254524) - created 2025-01-12 - last edited 2025-06-13
