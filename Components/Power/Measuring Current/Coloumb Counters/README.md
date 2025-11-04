<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Coloumb Counters

> Measuring Charge-Flow and Investigating Power Yield, Battery Quality, or State-of-Charge

Coulomb counters measure charge flow (ampere‑hours), not energy. They are excellent for tracking battery state of charge, but by themselves they do not account for voltage and therefore cannot directly report power or energy unless combined with voltage measurement and computation of watt‑hours and watts.





## Overview
A coloumb represents the charge flow produced by 1 Ampere for 1 second. Since there are 3600 seconds in an hour, 1Ah equals 3600 coulombs, and likewise 1 coloumb equals *1000mAh / 3600s = 0.27778mAh*.

### Measuring Charge (Ampere-Hours)

A coulomb counter integrates current over time. This makes them ideal to accurately **determine a batteries' state of charge**: once you know the charge that went into a battery, you can track the charge that is drawn from it and find out the remaining capacity.

### Measuring Energy (Watts)
Since coloumb meters represent a charge over time (a certain amount of *mAh*), by also measuring the voltage, you can create an **energy** meter. For this to work, you need to multiply the amount of charge recorded by the coloumb meter with the voltage **at that time**.

That said, there are circumstances in which you can get away with solely measuring charge and still determine the energy: if the voltage is **constant**, you don't need to take voltage into accoount each time you measure charge. Instead, you can simply multiply the recorded total charge with the constant voltage to get the total energy:

* **Device Power Consumption:**     
  If you want to record the energy a device consumes, it is sufficient to count the coloumbs since devices typically require a fixed supply voltage anyway.   
* **Battery Testing:**
  If you test a USB power bank that has a **stabilized output voltage**, i.e. 5V, you again get away solely with coloumb counting and could test the true powerbank capacity.

  If however you need to test raw battery cells, their voltage drops over time as state-of-charge decreases. You could however still determine the total battery capacity in *mAh* (as many do since most battery vendors specify capacity in mAh anyway).    
  
  To truly test the **energy** stored in the battery (in *mWh*), you would have to take the voltage into account each time you measure a certain quantity of charge.

### Options

There are a variety of devices and strategies you can use for coloumb and energy counting, yet they differ in a number of ways:

* **Cost:**    
  How much money are you willing to invest? This determines i.e. whether the chips sum up the recorded count for you, or just emit pulses and leave it to you to count these pulses. Money also determines whether the chip solely records charge (in mAh) or also considers voltage (and can report energy in mWh). Often, simple USB tester devices provide the best bang for the buck.      
* **Accuracy:**    
  Do you need a rough guess, or do you need scientifically accurate charge counts?    
* **Energy Consumption:**    
  Can you afford to spend a few mA to operate the coloumb or energy counter? Or do you need to minimize quiescent current because available energy is limited? In the latter case, dedicated coloumb counter chips are your best bet. 
* **Use Case:**    
  Do you want to monitor charge going in and out of a battery only (in which case simple coloumb counters suffice), or do you want to record the *energy* going in and out of devices, or the yield a solar panel delivers? In the latter case your device may also need to monitor and incorporate voltage if the voltage can fluctuate.

## DIY Solutions

There are many very affordable breakout boards that can measure voltage and current, i.e. [INA219](https://done.land/components/power/measuringcurrent/viashunt/ina219/), [INA226](https://done.land/components/power/measuringcurrent/viashunt/ina226/), and [INA3221](https://done.land/components/power/measuringcurrent/viashunt/ina3221/). 


<img src="images/ina219_breakout_red_grove_1_t.webp" width="40%" height="40%" />

Likewise, you can use hall sensors, too, to determine current.

Since you get both current and voltage, you can use a microcontroller to calculate power in mWh and store the values over time. This provides you both with a coloumb counter and an energy meter.

However, you need an external microcontroller that queries the raw values from these boards in regular intervals and does the math and storage. This defeats the original purpose of coloumb counters as accurate SOC meters for batteries because this setup is complex and energy-hungry. It is though a great solution if you rather want an *energy meter* and not so much a *charge meter*.

* **Power Consumption:**    
  Your microcontroller must be active most of the time, and this can consume considerable power (unless you are using a very low energy MCU). While you *can* send the microcontroller to deep sleep to conserve power, and query the voltage and current in intervals only, this further reduces accuracy.
* **Lower Accuracy:**    
  Since the microcontroller takes only *snapshots* when it queries voltage and current, it may not be very accurate, especially when current and/or voltage fluctuate. If you stretch the query intervals to i.e. 10 seconds to use deep sleep and minimize MCU energy consumption, your device is essentially "blind" in the time periods inbetween.    
  
  If the measured power consumption is relatively consistent, this is perfectly ok, and your firmware can average the power consumption. If however there was a sudden current spike within the 10 second interval, it would go unnoticed and wouldn't be counted.   

### Using Smarter Chips

If you invest more money, you can get a more sophisticated chip like the **INA228**: it has built-in memory, calculates the power in very short intervals, and records it. No need to run a power-hungry external MCU. 

An external MCU can query the **total accumulated power** at any time using an I2C interface, so overall power consumption is minimal.

## USB Testers

USB tester devices are extemely affordable and often come with sophisticated firmware and even color TFT displays. 

While they are targeted towards testing USB devices, many of them are actually coloumb **and energy** counters like this *Hidance HDC-085C* that comes with a metal casing and costs around €3.00: 

<img src="images/hdc-085c_back_t.webp" width="30%" height="30%" />

It supports DC voltages in the range of *4.5-50V* and currents of up to *12A*. Its large color TFT display shows momentary voltage and current as well as accumulated charge (in mAh) **and power (in mWh)**.

<img src="images/hdc-085c_front_t.webp" width="50%" height="50%" />

By simply adding a few USB adapters and some sort of load, you can create very functional battery testers:

<img src="images/hdc-085c_measure1_t.webp" width="100%" height="100%" />

For device and battery testing, using USB testers often is the best and most effective approach with the best bang for the buck. If you require data logging, there are USB testers with bluetooth and other interfaces.

Most USB testers have an error margin between 1-10%, so while this is fully sufficient for basic testing, it may not be accurate enough for more demanding scenarios.


## Dedicated Coloumb Counters

Specialized coloumb counting chips (and breakout boards) are available that provide high accuracy charge counting. All of these boards are **not suitable** though if you need to count **energy** (mWh):

* **LTC4150:**     
  Very affordable coloumb counter that outputs a negative pulse each time a certain quantity of charge (coloumbs) has been recorded. The actual quantity depends on the shunt resistor used.

  <img src="images/lt4150_top_t.webp" width="50%" height="50%" />

  While this chip records the charge with high accuracy, it does not *accumulate* the power and is restricted to voltages in the range of *2.7-8.5V*, targeting *1S* and *2S* lithium batteries. With this chip you would still need an external MCU that picks up and counts the pulses emitted.   

  For low power consumption scenarios, you can store the pulses in cascading CMOS counters like *CD4040* (unidirectional) or *CD40123* (bi-directional), and an external MCU can query these counters later via GPIOs or a I2C port extender at its discretion.

* **LTC2941:**    
  More expensive coloumb counter (around €10.00) with increased accuracy and built-in memory that is accessible via *I2C*, so this IC already integrates counters and an I2C interface, lowering complexity and energy consumption. 

  With a quiescent current of less than 100µA, this chip is ideal for autonomously measuring charge yield or consumption for small devices. Due to its restricted voltage range of just *2.7-5.5V*, it is mostly targeting 1S lithium cells and 3.3/5V operated devices.

  Note that as a pure coloumb counter, this chip records mAh only, not mWh (it does not integrate voltage).

  This chip is marked *end-of-lifetime* though by its manufacturer, and while you still can get breakout boards from some vendors, supply will eventually cease. There is no similar successor chip available.

* **LTC2944:**    
  More flexible chip for voltages up to 60V. This coloumb counter accumulates charge like *LTC2941* but in addition provides **instantaneous** measurements for voltage and current as well. It does not provide accumulated **energy** (in mWh).

## "Fuel Gauges"

You may come across small breakout boards based on chips like the *MAX17043*, marketed as "fuel gauges" for lithium batteries. 


<img src="images/max17043_fuel_gauge_t.webp" width="30%" height="30%" />


Such boards can be attached to lithium batteries to determine their current state of charge.   


### No Coloumb Counters

Internally, the chips may or may not use coloumb counting. The MAX17043 does not and instead relies entirely on proprietary algorithms to determine the state of charge from voltage and current and related effects (such as voltage drop with loads attached). This is called *model-estimation-only*.

Even though higher priced "fuel gauge" chips (like *MAX11040* or *BQ27421*) do use coloumb counting, this is typically done entirely internal and the values are not exposed. 

So no, with "fuel gauges" you cannot measure power consumption or test batteries, solar panels, or other sources or loads.

### Why Do "Fuel Gauges" Exist?
The reason why "fuel gauges" exist is that modern lithium batteries have a very flat voltage discharge curve, so simply measuring battery voltage to estimate state of charge is highly unreliable. That's why "fuel gauge" ICs add mathematical wizardry to improve the accuracy.

This said, most modern powerbank modules and chargers/dischargers already come with sufficiently accurate state-of-charge indicators, and typically a rough estimate in four or five steps is sufficient. If you must know the exact state-of-charge of a lithium battery, though, such "fuel gauge" modules may be handy. However, they are quite expensive and not in the scope of what we discuss here.

## Summary

Depending on your use case, here are some recommendations:

* **Simple Battery Testing:**    
  Use affordable USB testers for basic battery, device, and small solar panel testing. This is fully sufficient to determine whether you have a fake battery with false capacity claims.

* **Power Metering:**     
  Use *INA228* for **energy** accumulation with a high dynamic sense registering. This chip can handle up to 85V, has a 20bit delta-sigma ADC, automatically accumulates charge **and** energy, and can be easily integrated via *I2C*. 

  Be aware though that many untrusted sellers offer *INA228* boards that in fact use *INA226* or fake chips. If opting for INA228, make sure you order from trustworthy sources and/or test the boards immediately.

* **Battery SOC Meter:**    
  Use dedicated coloumb counter ICs for super-accurate charge counting at extremely low power consumption, for example to add a super-accurate SOC meter for your power bank or device.

  Parts like LTC2944 use an analog integrator for coulomb counting, which avoids missing narrow current spikes between ADC samples and is inherently continuous; this can yield better Ah accuracy in highly pulsed loads compared to periodically sampled digital integration approaches.

  Generally, with dedicated coloumb counters the focus lays on low quiescent current (so the meter isn't draining your battery) and highly accurate charge counting.



> Tags: Hidance, HDC-085C, Battery Tester, LTC4150, LTC2941, MAX17043, Fuel Gauge, CD4040, CD40193

[Visit Page on Website](https://done.land/components/power/measuringcurrent/coloumbcounters?825765101030255221) - created 2025-10-29 - last edited 2025-10-29
