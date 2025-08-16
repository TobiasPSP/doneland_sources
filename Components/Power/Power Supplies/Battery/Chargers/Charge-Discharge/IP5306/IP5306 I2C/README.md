<img src="/assets/images/charging.png" width="100%" height="100%" />

# IP5306 I2C Interface

> Understanding the IP5306 I2C Interface (Selected IP5306 Versions)

The regular version of [IP5306](materials/ip5306_datasheet.pdf) **does not implement I2C**. Only special variants of IP5306 contain a I2C interface:

* This article **applies** to I2C-enabled versions of IP5306 (i.e. [PB01](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/)).    
* This article **does not apply** to regular versions of IP5306 (i.e. [X-150](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/x-150/) or [MH-CD42](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/mh-cd42/)).

For a basic understanding what IP5306 does, [review the introduction](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/).





## Overview
I2C-enabled IP5306 utilize the pins `L1`, `L2`, and `L3` for I2C. Here is a sample schematic:


<img src="images/îp5306_wiring_i2c.webp" width="100%" height="100%" />

That's why I2C-enabled breakout boards like the [PB01](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/) do not use classic status LEDs. Instead, they typically add an additional chip to drive a WS2812 RGB LED.

Note the use of BSS138 MOSFETs that act as a level shifter. Selecting an appropriate level shifting concept depends on your microcontroller voltage and is discussed below.

### Warning
It is important to understand that IP5306 is an industrial chip, not a typical DIY module. 

Its I2C interface is timing- and noise-sensitive and requires strong pullup resistors (*2.2K*) for `SDA` and `SCL`. You may run into difficulties when prototyping with DuPont wires and breadboards.

* Try soldering cables for robust connections.
* Use short wires.

#### Simple Test Setup Without Level Shifting
Since voltage domains are different for IP5306 and the external microcontroller, a **suitable** level shifter is required which adds complexity and margin of error.

To test-drive your IP5306 and minimize complexity at first, [power IP5306 from your microcontroller](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/i2ctestsetup/). This way, no level shifter is required. 

Only once this works reliably for you, proceed to production design, include a level shifter, and power IP5306 from a battery and your microcontroller from the IP5306 5V output.

#### Noisy I2C Lines
When your I2C lines are noisy, you either won't be able to contact IP5306 via I2C at all, or you may experience malfunctions. They occur when your I2C data gets corrupted, so you accidentally write to the wrong registers or bits. In such cases, the RGB LED on IP5306 boards may start to blink, switch colors, or turn white.


## Selecting Level Shifter
Selection of an appropriate level shifting method depends on the voltage of your microcontroller.

### 5V Microcontrollers
5V microcontrollers (i.e. *Arduino Nano*) always use a higher voltage than IP5306, so you can use any level shifter that supports I2C.

Connect your microcontroller voltage to **HV**, and the battery voltage to **LV**.

### 3.3V Microcontrollers
3.3V microcontrollers (i.e. *ESP32*) are more challenging because their voltage lies within the range of the battery voltage (*2.8-4.2V*). That means the microcontroller voltage can be *lower* or *higher* than the battery voltage, depending on state of charge. There is no distinct **HV** and **LV** side.

Most level shifters, however, strictly require **LV** to be **always lower** than **HV**. 

Here are your choices:

* **Crossing Fingers and Hoping for the Best:**    
  Connect your microcontroller voltage to **LV**.    
    
    Use a discrete level shifter based on **BSS138**, and hope that the *body diode effect* of this MOSFET keeps working even when your battery voltage drops below your microcontroller voltage (in which case **LV** exceeds **HV**).

    Chances are this works, but it is running the *BSS138* or related level shifters outside their specs.

* **Isolated Lavel Shifter:**     
  Use an **isolated** level shifter, i.e. based on *ISO1540* or *ISO1640*.  

  The voltages of both sides can be independent with this type of level shifter, so there is no distinct **HV** and **LV**, just **Side 1** and **Side 2**.   

  * For *ISO1540*, both sides support a voltage range of *2.25-5.5V*, so it does not matter which side you connect to the battery.
  * For the successor *ISO1640*, **side 1** supports a voltage range of *3.0-5.5V* and should be connected to your microcontroller. **Side 2** supports *2.25-5.5V* and should be connected to the battery.





## I2C Configuration

IP5306 uses the I2C address `75`. You can use the *Wire* library to communicate with it. 

While IP5306 supports I2C speeds of up to 400kHz, it is recommended to use the default "normal" speed at 100kHz to increase robustness. Since there is not much payload, a higher speed does not yield any advantages.



| Item | Description |
| --- | --- |
| Address | `0x75` |
| Speed | up tp 400kHz, 100kHz recommended |
| Address Width | 8 bit |
| Data Width | 8 bit |
| Bit order | MSB first |
| SCK/SCL | pin `L1`, driven by master (connected MCU), pull up to VCC via 2.2K resistor |
| SDA | pin `L2`, pull up to VCC via 2.2K resistor |
| IRQ | pin `L3`, *high* when in working status/*low* when in sleep state |

Here is the complete [IP5306 I2C Register Map](materials/ip5306_i2c_registers.pdf).

## Keeping IP5306 Always Active

IP5306 has no built-in memory. Any configuration change you apply via I2C can (and will) be resetted once you remove power from the chip. 

By default IP5306 manages its power output automatically: when you connect a suffiently large load, it opens the 5V output, and once the load drops below *50mA* for more than *32 seconds*, it turns off the power output. 

Both can be undesired, so it is important to know about the two different IP5306 operating modes, and how you can switch between them.

### Power Down Mode
The "Power Down Mode" is active by default, and it is the only available mode for IP5306 variants without I2C interface.


In "Power Down Mode", whenever IP5306 turns off its 5V output, it almost fully turns itself off, dropping power consumption to just 50 µA. 

The downside is that its memory, too, is turned off, so whenever the 5V output is turned off, all previously made I2C configuration changes are lost.

That's why in this mode, your microcontroller is typically supplied by the IP5306 5V output: 

* whenever the output turns on, your microcontroller boots.
* during boot, it (re-)configures the IP5306 via I2C to whatever settings you require.
* there may naturally be a short lag between powering on IP5306 and applying the configuration changes with this approach.

### Standby Mode

IP5306 also supports a "Standby Mode" that can be enabled via I2C.

In "Standby Mode", the 5V output is no longer automatically controlled. Instead, it is always available and never turns off (unless you request via I2C). Only the onboard LED (if any) will still turn off after a set time (32 seconds by default). 

Since IP5306 is now powered constantly, it retains all I2C setting changes.

The extra energy consumption for this mode is moderate: the boost converter consumes approximately 100µA at idle in this mode.

So "Standby Mode" introduces two important changes:

* **Settings are retained:**     
  Since IP5306 stays powered all the time, it retains all settings changes that you may have applied via I2C. It is not necessary for your microcontroller to refresh the settings, and there is no risk of using wrong configuration settings, i.e. default battery charging rates instead of reduced customized rates.
* **Continuous Output:**    
  IP5306 will no longer cut its output power automatically once the load drops below *50mA* for more than *32 seconds*. This is critical for many projects where i.e. a microcontroller may enter deep sleep. 
  
    The onboad LED (if any) no longer indicates an active power output. It turns off after a few seconds to conserve energy.

In "Standby Mode", the I2C interface is **not always active**. It gets turned off at the same time when the LED is turned off. 

If you need to re-enable I2C, your microcontroller must pull `K`/`KEY` low for *200-2000ms*.

### Enabling Standby Mode

"Standby Mode" is controlled by register `00` and bit `1`:

| Register | Bit | Description |
| --- | --- | --- |
| `00` | `1` | 0: Power Down Mode<br/>1: Standby Mode |

## Controlling 5V Output (Boost Converter)

The boost converter can be manually turned on and off, and automatically turned on and off based on connected load.

When "Automatic Load Detection" is enabled (default), connecting a load with sufficiently low resistance enables the boost converter automatically.

* Small loads may not automatically trigger the boost converter
* When "Automatic Load Detection" is enabled, IP5306 sends a small test current each second. If connected devices (i.e. microcontrollers) use a power LED, the test current may cause the LED to dimmly blink.

When "Power Down Mode" is enabled (default), IP5306 automatically turns off the boost converter once the load drops below *50mA* for more than 32 seconds.

* The time can be set to *8*,*16*,*32*, and *64* seconds
* To disable automatic power down completely, switch to "Standby Mode"
* In "Standby Mode", the onboad LED is turned off after the specified time, but the 5V power output remains active.

In "Standby Mode", the 5V output is kept open continuously. The push button can no longer be used to power down IP5306, regardless of how it is configured.

### Power Output after Charging
When IP5306 is connected to a charger, the charger also supplies power directly to the 5V power output (even though the boost converter is not running). 

So during charging, the 5V power output is always active.

You can control whether IP5306 should automatically turn on the boost converter once the charger is removed to ensure uninterrupted power supply to your device. However, even when enabled, there may be a small period of power loss as it takes a few microseconds for the boost converter to fully turn on.

If you require an uninterruptable power supply, you may want to add a capacitor to the 5V output.


### Over-Discharge Protection
IP5306 has built-in over-discharge protection: once the battery voltage drops below 3.0V, the 5V output is turned off to protect the battery.

However, depending on the voltage drop induced by your battery holder and wiring, IP5306 may not see the full battery voltage. As a consequence, it may shut down when the real battery voltage is still well above 3.0V.

* Try to minimize the voltage drop by soldering the battery to IP5306 rather than using spring-type battery holders, and use short wiring with sufficient diameter.
* Turning off the built-in over-discharge protection and instead measure battery voltage yourself (similar to Kelvin 4-Wire) is possible but risky: your microcontroller now needs to turn off the 5V output via I2C, and if this fails, your battery may get damaged.


### Registers and Bits

| Register (hex) | Bit | Action | Read/Write |
| --- | --- | --- | --- |
| `00`| `5` | 0: turn off 5V Output<br/>1: turn on 5V Output | RW |
| `00`| `5` | 0: Power Down Mode<br/>1: Standby Mode | RW |
| `00` | `2` | 0: No Automatic Load Detection<br/>1: Automatic Load Detection | RW |
| `02` | `2`+`3` | Light Load Shutdown Time:<br/> `11` : 64s<br/>`01` : 32s<br/>`10` : 16s<br/>`00` : 8s | RW |
| `72` | `2` | 0: heavy load (high current)<br/>1: light load | R |
| `00` | `0` | 0: Push button cannot power down<br/>1: Push button can power down | RW |
| `01`| `5` | Button press to turn on 5V output:<br/>0: disabled<br/>1: Short press | RW |
| `01`| `7` | Button press to turn off 5V output:<br/>0: Long press<br/>1: two short presses | RW |
| `01`| `2` | Continue to supply 5V output power when charger is removed:<br/>0: no<br/>1: yes | RW |
| `01` | `0` | 3.0V over-discharge protection:<br/>0: disabled<br/>1: enabled | RW |



### Recommendations
In microcontroller-based projects:

* Turn on "Standby Mode"
* Turn off "Automatic Load Detection"
* Set "Light Load Shutdown Time" to **8s** to turn off the LED as quickly as possible

## Controlling Charger

When an external charger is connected to `VIN`, by default IP5306 starts charging the battery.

Via I2C, you can manually turn the charger on or off, adjust the maximum charging current, and query whether the battery is fully charged.

IP5306 does not include features to query the current charging rate or the current state of charge (other than "fully charged").


### Registers and Bits

| Register (hex) | Bit | Action | Read/Write |
| --- | --- | --- | --- |
| `00`| `4` | 0: turn off Charger<br/>1: turn on 5V Charger | RW |
| `23` | `5` | CC-to-CV transition:<br/>`0`: BAT<br/>`1`: VIN<br/>`01`: 14mV<br/>`00`: 0mV | RW |
| `70` | `3` | 0: charging disabled<br/>1: charging enabled | **R** |
| `71` | `3` | 0: currently charging<br/>1: battery fully charged | **R** |
| `01` | `0`,`1`, `2`, `3`, `4` | Maximum charging current:<br/>*I=0.05+b0*0.1+b1*0.2+b2*0.4+b3*0.8+b4*1.6A*<br/>*(see separate table)* | RW |

Bits `0:4` in register `0x01` control the maximum charging current. While the standard IP5306 uses a fixed *2.1A* charging rate, I2C allows granular adjustments. 

| Bits   | Current | Supported |
|--------|---------|-----------|
| `00000` | 0.05 A | ✅ |
| `00001` | 0.15 A | ✅ |
| `00010` | 0.25 A | ✅ |
| `00011` | 0.35 A | ✅ |
| `00100` | 0.45 A | ✅ |
| `00101` | 0.55 A | ✅ |
| `00110` | 0.65 A | ✅ |
| `00111` | 0.75 A | ✅ |
| `01000` | 0.85 A | ✅ |
| `01001` | 0.95 A | ✅ |
| `01010` | 1.05 A | ✅ |
| `01011` | 1.15 A | ✅ |
| `01100` | 1.25 A | ✅ |
| `01101` | 1.35 A | ✅ |
| `01110` | 1.45 A | ✅ |
| `01111` | 1.55 A | ✅ |
| `10000` | 1.65 A | ✅ |
| `10001` | 1.75 A | ✅ |
| `10010` | 1.85 A | ✅ |
| `10011` | 1.95 A | ✅ |
| `10100` | 2.05 A | ✅ |
| `10101` | 2.15 A | ❌ |
| `10110` | 2.25 A | ❌ |
| `10111` | 2.35 A | ❌ |
| `11000` | 2.45 A | ❌ |
| `11001` | 2.55 A | ❌ |
| `11010` | 2.65 A | ❌ |
| `11011` | 2.75 A | ❌ |
| `11100` | 2.85 A | ❌ |
| `11101` | 2.95 A | ❌ |
| `11110` | 3.05 A | ❌ |
| `11111` | 3.15 A | ❌ |

Theoretically, the charging rate can be set to as much as *3.15A* but whether this is feasible or causes heat sink problems I haven't tested yet.

### Determining Full Battery Charge

When the battery is fully charged, the charger stops. The "battery full" status is determined as a combination:

* when in CV mode, the charging current drops below a threshold...
* ...then the battery is considered fully loaded once the battery voltage exceeds a threshold.

Both thresholds can be adjusted:

| Register (hex) | Bit | Action | Read/Write |
| --- | --- | --- | --- |
| `21` | `6`,`7` | `11`: 600mA<br/>`10`: 500mA<br/>`01`: 400mA<br/>`00`: 200mA | RW |
| `20` | `0`,`1` | Battery Full Charge Voltage<br/>*(see separate table below)* | RW |



| Bits | 4.2 V   | 4.3 V   | 4.35 V  | 4.4 V   |
|------|---------|---------|---------|---------|
| `11`   | 4.2 V     | 4.305 V   | 4.35 V    | 4.395 V   |
| `10`   | 4.185 V   | 4.29 V    | 4.335 V   | 4.38 V    |
| `01`   | 4.17 V    | 4.275 V   | 4.32 V    | 4.365 V   |
| `00`   | 4.14 V    | 4.26 V    | 4.305 V   | 4.35 V    |



## Battery Configuration

IP5306 is designed to work with 1S LiIon/LiPo batteries. Via I2C, you can granularly fine-tune IP5306 to the battery type and capacity you use.

### Battery Type

Set the voltage that corresponds to your battery chemistry and type. For almost all *LiIon*/*LiPo* batteries, this is *4.2V* (IP5306 default). 

* Change battery voltage only if you are positive that your particular battery uses a higher charging end voltage (fire hazard).
* To account for voltage drops in your wiring, you can "pressurize" (slightly increase) the charging voltage in 14mV increments.
* For regular 4.2V batteries, the vendor recommends *28mV*. The default setting is *14mV*.



### Adjusting Charging Curve
Like most other chargers, IP5306 starts charging with constant current (CC), and when the current drops below a threshold, switches to constant voltage (CV).

* set the maximum charging current to match the battery requirements.     
  * LiIon: typically 1-3C
  * LiPo: typically 0.3C
* determine whether the **charger** current or the **battery** current should be used for transitioning from CC to CV:
  * VIN: charger current is used (good for weak chargers)
  * BAT: battery current is used (more precise control, may require stronger chargers)

### Registers and Bits

| Register (hex) | Bit | Action | Read/Write |
| --- | --- | --- | --- |
| `22` | `2`,`3` | Battery voltage:<br/>`11`: 4.4V<br/>`10`: 4.35V<br/>`01`: 4.3V<br/>`00`: 4.2V | RW |
| `22` | `0`,`1` | Wire Voltage Drop Compensation for CV charging:<br/>`11`: 42mV<br/>`10`: 28mV<br/>`01`: 14mV<br/>`00`: 0mV | RW |


## Push Button

An optional push button can be connected to `K`/`KEY` and `GND`. The push button can either control IP5306 features (like opening or closing the 5V output), or can be used for custom features.

By default, IP5306 recognizes short and long presses:

* **Short Press:**    
  *>20 - <2000ms*
* **Long Press:**    
  *>2 seconds*


### Registers and Bits

| Register (hex) | Bit | Action | Read/Write |
| --- | --- | --- | --- |
| `02` | `4` | Minimum long press duration:<br/>0: 2s<br/>1: 3s | RW |
| `02` | `4` | Minimum long press duration:<br/>0: 2s<br/>1: 3s | RW |
| `01` | `6` | Turn on WLED flashlight feature:<br/>0: two short presses<br/>long press | RW |
| `77` | `0` | Short press detected | RW |
| `77` | `1` | Long press detected | RW |
| `77` | `2` | Double-click detected | RW |

## LED Indicators


### Registers and Bits

| Register (hex) | Bit | Action | Read/Write |
| --- | --- | --- | --- |
| `78` | `7` | 1: LED 4 is on | **R** |
| `78` | `6` | 1: LED 3 is on | **R** |
| `78` | `5` | 1: LED 2 is on | **R** |
| `78` | `4` | 1: LED 1 is on | **R** |



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
[ESP32-controlled Powerbank Schematics](https://done.land/assets/img/m5stack_basic_ip5306_interface.png) (image)

> Tags: Charger, Li-Ion, Li-Po, Boost Converter, 2A, USB, 1S, IP5306, FM5324GA, Torch Mode, Push Button

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/ip5306i2c?313487011513254524) - created 2025-01-12 - last edited 2025-06-13
