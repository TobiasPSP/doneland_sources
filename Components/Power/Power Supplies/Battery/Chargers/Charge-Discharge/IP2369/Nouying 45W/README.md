<img src="/assets/images/charging.png" width="100%" height="100%" />


# Nouying 45W

> 45W 2-6S Charger/Discharger Board With Protections and Support for LiIon and LiFePo4

The Nouying breakout board lacks any model specification, and it is likely that this board surfaces under various names. It is based on the [IP2369](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2369/) power management chip.

<img src="images/ip2369_chip_t.webp" width="50%" height="50%" />

It is a 45W Charger/Discharger for 2-6S Lithium battery packs, supporting both LiIon/LiPo and LiFePo4. 

Thanks to the enormous flexibility of IP2369, you can add this breakout board to any battery pack ranging from 2-6S to create a powerful USB PD powerbank that can output up to 20V.


> [!NOTE]
> For technical details and use cases, please refer to the article about [IP2369](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2369/). This article focuses on the specifics of the Nouying breakout board.

## Overview

This board can be powered from a 2-6S lithium battery pack, or a static external power supply in the range of 4.5-25V.

This breakout board is special for a number of reasons:

* **LiFePo4-Support:**    
  This board works with LiIon, LiPo, and also LiFePo4 batteries.  
* **Universal Charger:**  
  This board can act as a universal charger for any 2-6S battery of any lithium chemistry. You can use this board to charge a 5S LiIon 18V Makita tool battery or a 4S 12V LiFePo4 battery. 
   
  Just make sure the battery can accept the relatively high charging currents, or limit the maximum charging current. Always select the correct 2–6S setting and chemistry before connecting a pack, and ensure the pack’s BMS and cells can accept the configured charge current.

* **Wide Input Voltage:**    
  IP2369 accepts any input voltage in the range of 4.5-25V.   
  
  Typically, you use the bidirectional USB-C connector to supply power, and when you do, IP2369 can automatically negotiate higher voltages if your USB power supply supports USB PD.

  You can however also supply a fixed voltage (4.5-25V) from a classic power supply.
* **Full USB PD Output (including 20V and PPS):**     
  IP2369 includes a powerful boost converter that can boost even the lowest input voltage up to 20V in order to support all USB PD output voltages. 

  There are not many affordable and small boards that provide 20V out of 4.5V. At a 6V input voltage, IP2369 produces 20V at 1.5A (30W) at a 92% conversion efficiency.
* **Affordability:**     
  Occasionally, the board is offered for as low as €3.00. The typical price range is 3-6€.    
* **Practical build tips:**  
  For sustained 30–45W operation, use short, thick battery leads, keep high‑current loops compact, and provide airflow or a small heatsink to maintain efficiency and avoid thermal throttling; this is especially important when converting from low input to high output voltages.

### LED Indicator
The board implements a 4-LED indicator located next to the USB-C connector.


<img src="images/ip2369_top_t.webp" width="60%" height="60%" />

#### Charging

| Battery Capacity | LED1 | LED2 | LED3 | LED4 |
| --- | --- |--- | --- | --- |
| full | 💡 | 💡 | 💡 | 💡 |
| 75% | 💡 | 💡 | ⚡ (0.5Hz) |  |
| 50% | 💡 | ⚡ (0.5Hz) |  |  |
| 25% | ⚡ (0.5Hz) |  |  |  |

💡 = on, ⚡ (0.5Hz) = slow blink, empty cell = off.

#### Discharging

| Battery Capacity | LED1 | LED2 | LED3 | LED4 |
| --- | --- |--- | --- | --- |
| full | 💡 | 💡 | 💡 | 💡 |
| 75% | 💡 | 💡 | 💡 |  |
| 50% | 💡 | 💡 |  |  |
| 25% | 💡 |  |  |  |
| 0% |  |  |  |  |

💡 = on, ⚡ (0.5Hz) = slow blink, empty cell = off.

> When the over-discharge protection kicks in (battery empty), all four LEDs flash 4 times, then turn off.

<img src="images/ip2369_chip_t.webp" width="60%" height="60%" />

## Push Button
The board automatically enables power output when a load is plugged in, and disables it again when the load is removed.

When the load is very light, it may be undetected, and the power output needs to be manually turned on via a push button that is located next to the USB-C connector.

<img src="images/ip2369_config3_t.webp" width="60%" height="60%" />

### Short Push
Any push longer than 100ms and shorter than 2s is considered a "short push":

* **1x Short Push:**    
  Enables the power output and turns on the LED state-of-charge display.
* **2x Short Push:**  
  Disables power output and enters low-power mode.

### Light Load Detection

The board **automatically turns off the power output** if a "light load" is detected. A light load is defined as a power consumption of <350mW (70mA at 5V). 

Automatic shutdown occurs when the light load is active for more than the time specified:

* **Normal (Non-USB PD) Load:**     
  32 seconds.  
* **PD Protocol:**    
  16 minutes.

Light Load is meant to conserve battery power, but it can also become highly frustrating in solutions where you **want** to run a light load, i.e. a microcontroller in deep sleep.

Light Load detection can be disabled using I2C, however currently, there is no I2C register information available for the IP2369. If you have one, please share in the comments below. (See the IP2369 article for ongoing notes on I2C/disable options.)

<img src="images/ip2369_config1_t.webp" width="60%" height="60%" />

## Battery
The battery pack is connected to `B+` and `B-`. 

* **Protections/BMS:**    
  The board comes with all necessary [protections](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2369/#protections), so the battery pack does not necessarily need its own protections (although recommended).
* **Balancing:**    
  The board has no balancing capabilities. Use a separate BMS for your battery pack that supports balancing.    
* **Wires:**    
  IP2369 limits **input** currents to **3A**/**45W**. Depending on your battery configuration, there can be much higher currents at the battery terminal. For example, in **2S** configuration, the maximum battery current can reach **7.5A**.

<img src="images/ip2369_bottom_t.webp" width="60%" height="60%" />

### Configuring Battery Type

Both string configuration and battery chemistry can conveniently be configured using solder bridges. By default, the board is configured for **4S** and **LiIon/LiPo** chemistry:

<img src="images/ip2369_config2_t.webp" width="60%" height="60%" />

#### LiFePo4

If you want to use LiFePo4 batteries, close the solder bridge marked **Li-fe**.

#### 2-6S Configuration

Bridge the appropriate solder bridge for your battery packs' string configuration. 

> [!IMPORTANT]
> Always make sure **that only ONE solder bridge is bridged**. The solder bridges [enable an internal resistor](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2369/#batteries). If you accidentally bridge more than one solder bridge, the total resistor value decreases (resistor parallel connection), and the effective string configuration may be lower than required.    

#### Solder Bridges
For some reason, on my board the preinstalled **4S** solder bridge was using a 50 Ohm SMB resistor, and the fixed resistor next to it was 9.6K (when it [should have been 9.1K](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2369/#batteries)). Resistor values for all other string configurations matched the values mentioned in the [IP2329 datasheet](materials/ip2369_datasheet_en.pdf).

> Tags: Charger, Li-Ion, Li-Po, LiFePo4, Boost, Buck, Buck-Boost, 20V, IP2369, 45W, Charger, Discharger, Light Load, Powerbank, I2C

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2369/nouying45w?125674091701252408) - created 2025-08-31 - last edited 2025-08-31
