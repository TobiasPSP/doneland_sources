<img src="/assets/images/charging.png" width="100%" height="100%" />

# IP5306 Power Management IC

> 2.4A 1S Li-Ion Charger Plus 5V 2A Boost Converter In One SoC Solution That Drives Many DIY Boards

The [IP5306](materials/ip5306_datasheet.pdf) is a fully integrated *power bank* system-on-chip with a *2.4A* charger and a *2A* discharger. This chip—or one of its many Chinese clones, like the [FM5324GA](materials/fm5324ga_datasheet_en.pdf)—is commonly used in modern DIY modules.


<img src="images/ip5306_chip_hr.png" width="30%" height="30%" />


For highly integrated chips like this one, it is essential to understand their concepts and functionality before use. Some of its features - like its optional *torch mode* -  may not be immediately apparent and could lead to unintended risks. 

## Overview
The *IP5306* is found on affordable breakout boards like the [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/) and the *MH-CD42*.



<img src="images/ip5306_overview_t.png" width="100%" height="100%" />



Modules utilizing this chip are highly compact (typically *15-20x25mm*) yet surprisingly powerful. With a single *Li-Ion* cell, they can deliver up to *2A* at *5V*. 

This compactness is made possible by a clever architecture that uses a single inductor for both charging and discharging operations.


<details><summary>How simultaneous charge and discharge really work</summary><br/>

### Power Paths
This chip can **either** use its integrated boost converter to increase the battery voltage to *5V* at a maximum of *2A* output (*10W total*), **or** it can step down an external *5V* input to a charging voltage suitable for *Li-Ion* or *Li-Po* batteries. However, the chip can only perform *one* of these conversions at a time.

Despite this limitation, the chip supports simultaneous discharging and charging. This means you can operate a connected device both while the chip is charging and when the device is powered by the battery alone.

Understanding the involved switching between different power paths is critical.

### Battery Operation
When the chip operates solely on battery power, its boost converter supplies *5V* at a maximum of *2A* to the output, providing up to *10W* of power. The battery must be capable of supplying a peak current of *3.5A* to support this load. Be aware that smaller batteries or low-cost, low-current *Li-Po* batteries may not be sufficient to meet this demand.

### Charging
When an external *5V* power supply is connected, the chip dynamically switches internal power paths:
- The input voltage is stepped down to a suitable charging voltage for the battery, with a maximum charging current of *2.4A*.
- The internal boost converter is deactivated.
- The power output is now directly supplied by the *5V* input. 

This allows the device to continue operating while the battery is being charged. However, during this mode:
- If the connected device draws the full *10W* output **while** the battery is simultaneously charged at the maximum rate, the total power demand can reach *21W* when accounting for conversion inefficiencies.
- The external *5V* power supply must provide at least *4.2A* to handle this combined maximum load.
- If no device is connected to the output during charging, a standard *5V 2A* power supply is sufficient for charging the battery alone.

### Temporary Power Cut
When an external power supply is connected or disconnected, the chip actively switches power paths. During this transition, there may be a **brief power interruption** at the output. This can cause connected devices, such as microcontrollers, to reboot. To prevent this, you can add an appropriately sized capacitor to the output line, which will smooth out any voltage dips during these transitions.


</details>

### Use Cases
This chip is ideal for adding battery power to external *5V* devices such as microcontrollers, [WS2812](https://done.land/components/light/led/programmable/ws2812/) LED strips, DIY flashlights, and more. It is also suitable for building simple power banks.


#### Permanently Connected Devices
This chip is especially suited for adding battery support to *5V* devices:

- a *push button* can be used to control power to the connected device, so it can be turned on and off as needed.
- Only the device connected to the *power output* can draw energy from the battery.
- The *power input* is exclusively reserved for charging the battery and does not allow external devices to deplete the battery. 



#### Power Bank
When designing a power bank, the goal is to provide power on demand to various USB devices. To achieve this, you can add one or more USB connectors (of your chosen type) to the chip's power output.

Key considerations for power bank design with this chip:
- The chip provides a fixed *5V* output voltage only. This limitation is a direct consequence of the chip targeting *1S batteries* (single-cell configurations). 
- Boosting the voltage beyond *5V* would require higher battery currents, larger physical components (e.g., coils), and lead to inefficiencies. 

As a result:
- This chip does not support *quick charge protocols*, which rely on multiple output voltages such as *9/12/15/20V*. 
- Devices connected to the power bank will charge at standard speeds, limited to a fixed *5V* output at a maximum current of *2A* (10W).

In a nutshell, this chip is excellent for building *physically very small* power banks.

### No Temperature Sensor
The *IP5306* features several built-in protection mechanisms, including *over-temperature protection*, but there is no support for external temperature sensors.

External temperature sensors can detect catastrophic battery failures during charging. 

Such sensors, though, are more commonly integrated into power management chips designed for higher-capacity battery systems, where the risk of thermal issues is higher due to larger energy storage and discharge rates.

## Battery Requirements
The *IP5306* supports *1S* battery configurations (*Li-Ion* and *Li-Po*). You can use a single cell or connect multiple cells in *parallel* to increase capacity while maintaining the required *1S* voltage.


### Battery Voltage
This chip is designed for *Li-Ion* and *Li-Po* batteries with a maximum voltage of *4.2V*. It also includes optional support for *high-voltage* cells with a maximum voltage of *4.35V*. However, *LiFePO₄* batteries are **incompatible**, and using them can be hazardous.

> [!TIP]
> Some users have reported that the *4.35V* setting is ineffective, with the maximum charging voltage remaining at *4.2V*. Batteries must explicitly support *4.35V* to utilize this setting. Many standard *Li-Ion* batteries with built-in BMS will cut off power above *4.2V*. Additionally, their internal resistance increases sharply beyond this voltage, causing the charging current to taper naturally. To use the *4.35V* setting, ensure your batteries are specifically designed for *4.35V* operation.

### Selecting Appropriate Battery Capacity
Given the high performance of the *IP5306*, selecting a suitable battery is critical. Batteries that are too small can lead to overcharging and/or over-discharging, increasing the risk of fire hazards. 

Generally, you will need a battery with a minimum capacity of around *3,500mAh*.

#### Key Considerations:
- **High Charging Current:**  
  The charging current is fixed at *2.4A*. At a *1C* charge rate, the battery must have a capacity of at least *2,400mAh* to safely handle this current. 

- **High Power Output:**  
  The chip can supply up to *10W* to its power output. When the battery voltage drops to *3V* near depletion, a *10W* output at *90% conversion efficiency* requires approximately *3.5A*. At a *1C* discharge rate, the battery must have a capacity of at least *3,500mAh*. 

- **Minimum Capacity:**    
  Due to the fixed charging current, at *1C* charge rate, your battery **must have** a capacity of **at least** *2.400mAh*. Assuming a *1C* discharge rate as well, at this capacity the battery could deliver a maximum output current of *2.4A*. When the battery is close to depletion at *3V*, this allows for a maximum of *6.5W* power output (*1.3A* at *5V* output).
- **Recommended Minimum Capacity:**    
  To take advantage of the maximum *2A* output (10W) that this chip supports, your battery capacity must be at least *3.500mAh* at an assumed *1C* discharge rate.

> [!TIP]
> If the chip stops charging after only a few minutes and reports the battery as fully charged when it is not, this might indicate that the battery is too small for the *2.4A* charging current. Overcharging a small battery can cause its voltage to temporarily rise too quickly, triggering the chip's early cut-off protection.


<details><summary>Risk: Low-Performance Batteries</summary><br/>
Low-performance *Li-Ion*/*Li-Po* batteries, such as the one shown below, can be a perfect and affordable choice for projects requiring only small currents.  

However, it is **essential** to understand their **limitations** before using them with *high performance* chips like the *IP5306*.

<img src="images/makerfocus_battery_3000_t.png" width="40%" height="40%" />

In the calculations discussed earlier, a default *1C* charge and discharge rate was assumed. This means the current can reach the same value as the battery's total capacity. For example, with a *3000mAh* battery like the one depicted, a *1C* rate would allow for a charge or discharge current of *3A*.  

However, low-performance batteries often fall short of the *1C* standard. For the battery shown:  
- **Maximum charge current:** **0.2C** (*600mA*)  
- **Maximum discharge current:** **0.5C** (*1,500mA*)  

If this battery were connected to the *IP5306*, the chip's fixed charging current of *2,400mA* would exceed the battery's maximum safe charge current by four times, potentially damaging the battery and creating safety hazards.


</details>


## Charging
Charging and discharging are separate features, and you can use the *IP5306* for charging only, possibly as a replacement for a simple *TP4056*, simply to achieve higher charging currents.

| Item                         | Description                    |
|------------------------------|--------------------------------|
| Input Voltage                | *5-5.5V*                      |
| Charging Current             | *2.4A*                        |
| Charge Switching Freq.       | *750kHz*                      |
| Charging Cut-Off Voltage     | *4.2V* or *4.35V* (configurable)   |
| Charging Efficiency          | *91%*                         |
| Short Circuit Protection     | Yes                           |
| Low Voltage Recovery         | Yes                           |
| Battery Reverse Polarity Prot.| No                           |
| Charging While Discharging   | Yes                           |

> [!IMPORTANT]
> The chip lacks *battery reverse polarity protection*. Use an *ideal diode* or other suitable protection if reverse polarity is a risk, i.e. because you are using battery holders where a user could be intreagued to insert a battery in wrong position.

### Initiating Charging
Charging starts automatically when a power supply is connected, and the battery voltage is *>2.8V* and *<4.2V*. The external power supply must provide *5V* at *2A* minimum.

During charging, the indicator LED show charging progress in *25%* increments, and one LED is blinking at *1Hz*.

Charging phases:
1. **Deep Discharge Recovery:** If battery voltage is below *2.8V*, the chip supplies *180mA* until safe voltage levels are reached.
2. **Constant Current:** For voltage between *2.8V* and the cut-off, the chip charges at *2.4A*.
3. **Constant Voltage:** Once the battery reaches *4.2V*, current tapers off until it falls below *100mA* or 24 hours elapse.



Once charging has completed, all four indicator LEDs light solidly.

A new charging cycle is initiated automatically once the battery voltage drops below *4.1V*.


> [!NOTE]
> When a battery has accidentally been *deeply discharged* (i.e. by keeping it in storage for too long so that normal self-discharge could cause a voltage drop below *2.8V*), it can no longer absorb the normal amount of energy. Charging such a battery with a normal charge current would convert the excess energy into heat and might cause a fire or explosion. The *recovery charge mode* is taking this into account. Whether or not it will be successful in recovering such a battery is not certain. However, if the battery isn't fully charged after a maximum of 24 hours, the charging cycle is aborted.



## Supplying Power

The chip includes a robust and efficient boost converter capable of supplying *5V* at up to *2A*. It is equipped with *over-current* and *short circuit* protection mechanisms.

<img src="images/ip5306_overview2_t.png" width="100%" height="100%" />



| Item                  | Description                    |
|-----------------------|--------------------------------|
| Output Voltage        | *5-5.15V* (USB-A, 5V pads)    |
| Output Voltage Ripple | *50mV*                        |
| Output Current        | max. *2.1A*                   |
| Indicator LED Current | *4mA* each                    |
| Off Current           | *<50µA*                       |
| Standby Current       | *<100µA*                      |
| Load Removal Detection| *<45mA* for *32s*             |
| Boost Switching Freq. | *500kHz*                      |
| Boost Efficiency      | *92.5%*                       |
| Short Circuit Prot.   | Yes                           |
| Other Protections     | Over-Current, Over-Voltage    |

When a load is connected to the power output, the boost converter activates and begins supplying power. When the load is removed (or the load drops below *45mA* for more than *32s*), the boost converter automatically shuts down to conserve battery power.


While power is being supplied, four LEDs indicate the battery's *state of charge* in *25%* increments. Each LED is supplied with *4mA*.

When the battery's *state of charge* drops below *3%*, one LED will blink at *2Hz* to alert the user. If the battery voltage falls further, below *2.8-2.9V*, the *over-discharge* protection feature turns off the power output to prevent damage to the battery.

| LED | *On* at battery voltage *(V)* |
| --- | --- |
| 1 | *>3.36* |
| 2 | *>3.57* |
| 3 | *>3.65* |
| 4 | *>3.91* |


### Automatic Load Detection
The *automatic load detection* feature is essential for preserving battery life. 

Operating the boost converter requires approximately *100µA*. If the boost converter remained active continuously—even without an active load—it could deplete the battery unnecessarily.

To address this, both the boost converter and the indicator LEDs are activated only when required. In inactive states, the chip minimizes power consumption, reducing quiescent current to *30-50µA*. 

Two operational modes manage this behavior:

| Mode | Boost Converter | Indicator LED | Power Supply | Quiescent Power |
| --- | --- | --- | --- | --- |
| **Standby Mode** | on | on | available | 100µA |
| **Off Mode** | off | off | not available | 30-50µA |

The chip automatically transitions between these modes:

* **Load Detection:** The chip continuously monitors the power output. When it detects a load, it activates *Standby Mode* to supply power to the connected device.
* **Load Removal Detection:** If the load drops below *45mA* for a continuous period of at least *32 seconds*, the chip shuts off the boost converter and switches to *Off Mode*.

> [!TIP]
> A user once reported that the chip worked properly but stopped after exactly 33 seconds. This behavior was due to the *automatic load removal detection*. The user's load was too small to sustain *Standby Mode*. To prevent this, you can increase the load above *45mA* (e.g., by adding a small LED or resistor). Alternatively, you can enable the power output manually using the push button connector in regular intervals to reset the load removal timer (see below).




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
A *short press* (*>30ms* impulse) enables power output in all chip variants. Use a short press to turn on a device, or to reset the *load removal detection timer* before it can kick in on light loads *<45mA*.

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

### Keeping Power Output Active
One of the top design issues is the *load removal detection* that kicks in once the load drops below *<50mA* for more than *32s*.

Whether you want to work around this *load removal detection*, or whether you want to generally prevent the board from entering *Off* mode, i.e. to work around wake-up problems, here are two suggestions you may want to try (at own risk) to keep the power output active:

* **MH-CD42** breakout board:

    <img src="images/ip5306_mh-cd42_always_on.png" width="100%" height="40%" />      

* **X-150** breakout board:


   <img src="images/ip5306_x-150_keep_on.png" width="40%" height="40%" /> 

By keeping the boards' boost converter active all the time, this will increase quiescent current consumption by approximately *50uA*.     

> [!IMPORTANT]    
> As always on this site, use all information including suggested circuitry entirely at your own risk.    

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

**Auto Power On When Load Connected**, when enabled, automatically detects a connected load. This very same feature is also responsible for automatically **turning off** the output once the load is removed. This includes the **light load detection**: once the load drops below *50mA* for the time configured in **REG_SYS_2** (`0x02`, normally *32 seconds*), the outout is also automatically turned off.

This may be undesirable: when you supply light loads (i.e. microcontrollers in sleep mode), the *IP5306* may unexpectedly turn off the power supply.

In order to **disable light load detection** and ensure that the *IP5306* supplies power all the time, turn off **Auto Power On When Load Connected** by setting its bit to `0`.

As a consequence, *IP5306* no longer automatically turns on its output once power is drawn, and it *never* turns off power automatically anymore, even if no power at all is drawn. You now control the power output entirely manually via the control button.

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
