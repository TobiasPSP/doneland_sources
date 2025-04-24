<img src="/assets/images/lightning.png" width="100%" height="100%" />

# HW-586 Battery Discharger Module

> Very Affordable And Flexible Battery Discharger Module

`HW-586` is a breakout board designed to *discharge* batteries down to a defineable stop-voltage. It originally surfaced as `ZB2L3`. 

It can be used with single cells as well as battery packs up to a total voltage of *15V*. 



<img src="images/hw586_battery_discharge_overview_t.png" width="70%" height="70%" />


The board comes with two *5W 7.5Ohms* load resistors which you can use in parallel or in series, or replace by a different load resistor altogether. Just make sure the discharge current stays below *3A* at all times.

<img src="images/resistor_3ohms_50w_2_t.png" width="50%" height="50%" />

## Overview
*HW-586* is a microcontroller-based battery discharge tester that can be used to discharge a battery down to a defineable stop voltage. 

It records the discharged energy (in *mAh*) up to a total battery capacity of *9.999 Ah* (*9.999.000 mAh*).

| Item | Description |
| --- | --- |
| Power Supply | 4.5-6V, <70mA<br/>typically supplied via a *Micro USB* connector |
| Test Battery Voltage | 1.0V - 15.0V |
| Test Discharge Current | max. 3A. 0.001A resolution |
| Test Battery Capacity | max. 9999Ah (9999000mAh) |
| Board size | 50x37mm |


### Versions and Evolutions

Initially, this board surfaced as `ZB2L3` and used a *STM8S003F3P6* microcontroller (hidden underneath the seven-segment display), plus a *TM1650* LED controller.

Starting in 2019, the board is now sold as `HW-586`, and while it still looks identical, it has gone through a number of silent revisions. 

To cut costs, [both the microcontroller and the LED controller were replaced](https://github.com/TG9541/stm8ef/issues/248) with cheaper pin-compatible no-name clones (i.e. *Nuvoton* microcontrollers and *ET6226M* LED controllers).

The most important change is that the cheaper *Nuvoton* microcontroller has less memory, so the original firmware had to be reduced, and the *calibration* features were removed.

In the original models, when pressing all three push buttons, then powering on the module, a special calibration mode was entered that allowed the user to improve voltage and current measuring precision. This no longer exists.

### Practical Consequences

[Deep analysis](https://youtu.be/7SWExcGAnOQ?si=ZEkMyMa3liwBq4_D) of this module revealed that it may or may not work well for you: the reported battery capacity works great for many users, while other users report errors of up to *30%*. 

The reason for these different experiences seem to be the great number of identical-looking clones and variations that circulate in the market. If you get the module from sellers that used fake OpAmps on their boards, then this explains outrageous errors.

While the original module allowed you to compensate errors to some extent via its calibration mode, this is no longer an option. Therefore, if you plan to use this module to measure battery capacities, make sure you test and compare this module to other battery tester results in order to determine whether it works well enough.



### Workaround

Even if your module is unable to reliably measure battery capacity, this module can still be highly useful. 

Simply use it as a *discharger* only: set a stop voltage, and let the module discharge the battery. Test to make sure that the discharge stops at the desired stop voltage.

Once that works, use any regular battery charger that features a battery capacity (*mAh*) display to do the actual battery capacity testing. Use the *HW-586* solely to discharge your batteries to a defined voltage.



## Wiring 

The board comes with four screw terminals that are labelled on the backside of the PCB:

| Screw Terminal | Description |
| --- | --- |
| R, R | connects the external load resistor |
| +IN | **positive** pole of battery under test |
| IN- | **negative** pole of battery under test |

Here is a typical setup with a *18650 battery holder* and an external load resistor:

<img src="images/wiring.png" width="100%" height="100%" />

The board requires a separate power supply via its *Micro USB connector*.

## Choosing Load Resistor
The discharge current is determined by the load resistor(s) **and** the voltage of your battery under test. 

The board comes with two *5W 7.5 Ohms* load resistors. This way, you can adjust the discharge current:

* **Highest:**  
  use both resistors **in parallel** (3.75Ω)
* **Medium:**   
  use **only one** of the two resistors (7.5Ω)
* **Lowest:**   
  use both resistors **in series** (15Ω)
 
### Calculating Discharge Current

The discharge current can be calculated using *Ohms Law*: 

````
I = V / R
````

The total discharge current depends on the **voltage** of the battery under test:

| Resistance | 4.2 V        | 3.7 V        | 3.0 V        | 12 V         |
|------------|--------------|--------------|--------------|--------------|
| 3.75 Ω/10W <br/>(in parallel)     | 1.12 A / 4.70 W | 0.99 A / 3.66 W | 0.80 A / 2.40 W | **3.20 A / 38.40 W** |
| 7.5 Ω/5W<br/>(one resistor)      | 0.56 A / 2.35 W | 0.49 A / 1.81 W | 0.40 A / 1.20 W | 1.60 A / **19.20 W** |
| 15 Ω/10W<br/>(in series)       | 0.28 A / 1.18 W | 0.25 A / 0.91 W | 0.20 A / 0.60 W | 0.80 A / 9.60 W  |


### Replace Load Resistors With Better Ones
As can be seen, testing a *12V battery* produces much higher discharge currents than testing a single LiIon cell. Plus the total wattage is higher as well at higher battery coltages, often exceeding the specs of the board and/or the load resistors.

For example, testing a *12V* battery with both load resistors connected in parallel would produce a *3.2A discharge current* (exceeding the boards' *3A* maximum), and would apply a *38.4W* load to the load resistors (exceeding their *10W* rating almost four-fold).

That's why the included load resistors are ideal for testing single *LiIon* batteries only. When testing batteries with higher voltage, make sure you use load resistors capable of handling the heat. They should be rated for at least **50W**, and the discharge current must not exceed *3.0A* at all times.

To use the maximum discharge current of *3A* with single LiIon cells, use a 1.4 Ω resistor, rated for at least 15 W.

## Errors
The firmware performs a few tests before starting to discharge the battery. If a test fails, the display shows an error number, and the discharge is aborted:

| Error | Description |
| --- | --- |
| Err1 | Battery voltage >15V |
| Err2 | Battery voltage is below stop-voltage |
| Err3 | Voltage drop too high |
| Err4 | Discharge current exceeded *3.1A* |

If you get one of these errors, here is what to do:

| Error | Fix |
| --- | --- |
| Err1 | you cannot test the battery with this board because its voltage exceeds *15V* |
| Err2 | fully charge the battery, or adjust the stop voltage to a value that is lower than the battery voltage |
| Err3 | your battery holder (or its cables) has a resistance that is too high. Use a better battery holder, or reduce the discharge current by using a higher load resistor value |
| Err4 | Use a higher load resistor value, or use (test) batteries with a lower voltage. This error occurs if you use a load resistor for single LiIon cells, and then decide to test a battery with much higher voltage (i.e. 12V). According to Ohms Law, the discharge current is determined by the load resistor value **and** the battery voltage under test. If you significantly change the battery voltage, you also need to raise the load resistor value to keep the discharge current within specs. |

### Dreaded Err3

*Err3* is a particularly irritating error. Originally, this error was designed to protect the battery under test from too much load. Unfortunately this test often produces false alerts, and here is why:

When a load is applied to any battery, its voltage will sag a bit. That's normal and related to the batteries' internal resistance. If however the load is too high for a battery, the voltage drops considerably. This is a warning sign that you should reduce the discharge current.

The firmware therefore monitors the battery voltage for significant sags during the first seconds of discharge. When it determines that the voltage drop is too high, it displays *Err3* and aborts the discharge process.

That sounds like a considerate safety mechanism, however often is **not the battery that causes the excessive voltage drop**, but instead your battery holder or its wiring. Many battery holders simply have a high surface resistance. Which isn't a problem in most cases.

Since you just want to discharge a battery down to a defined level, or record the discharged current over time, the resistance of the battery holder is basically just an additional load resistance. 

### Workarounds

If you are hit by *Err3*, here is what you can do:

* **Better Battery Holder:**    
  Use a better battery holder (or wiring) with less resistance. This reduces the voltage drop so that *Err3* is no longer triggered.
* **Less Discharge Current:**    
  Use a higher load resistor value to reduce the discharge current. The voltage drop is proportional to the discharge current. By reducing the discharge current, you are reducing the voltage drop.
* **Delayed Load Resistance:**    
  Start with a high load resistor, i.e. *7.5 Ohms*. This keeps the discharge current (and voltage drop) initially low. After 10 seconds, when the system has stabilized and the firmware has conducted the voltage drop test, add a second *2 Ohm* resistor in parallel, reducing overall load resistance to *1.58 Ohms*. When testing a single LiIon cell at *4.2V*, you'll start with around *500mA* discharge current, and once the firmware has finished the voltage drop testing, you increase the discharge current to *2.66A*





> Tags: Battery Tester, Discharge, HW-586, ZB2L3

