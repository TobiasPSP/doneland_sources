<img src="/assets/images/charging.png" width="100%" height="100%" />


# Charging Batteries

> Chargers Control Voltage and Current To Safely Charge Batteries

*Rechargeable batteries* play an ever more important aspect in our lifes, whether they power portable devices or sensors, harvest solar energy, or provide the energy for electric cars.

In this section, you learn about how chargers (and charging) work, and we'll be looking at a number of chargers that you can use in DIY projects.

## Overview

### Dedicated Chargers
*Dedicated chargers* are limited to charging batteries and act similar to a *one-way-street*: on one side, you supply power, and on the other side, you connect a battery that receives a safe charging current.

Internally, such chargers are *constant voltage constant current* DC-DC converters with some enhanced logic for automatic shutoff, under-voltage-protection, and temperature control.

### Combined Chargers and Dischargers
This type of charger acts like a *two-way-street*, and energy can flow in both directions:

* **Charging:** works like a regular charger. For example, you supply USB power, and the charger converts it to the voltage and current required by the battery for safe charging.
* **Discharging:** converts the battery voltage to a consumable output voltage. For example, you use a *1S LiIon battery cell* and would like to operate USB devices. The *combined* charger contains a *boost converter* that takes the variable battery voltage (*LiIon* voltage range *3.0-4.2V*), and converts it to a constant voltage of *5V* that can be consumed by *USB devices*.

One use case of such combined chargers are *power banks* that can be charged via *USB* and also drive *USB devices*.

> [!NOTE]
> Combined chargers really are just two separate DC-DC converters, one for charging, and another one for discharging. There are modules with both DC-DC-converters conveniently on one PCB, and you can also combine two regular DC-DC converters yourself for such a functionality.

### Solar Chargers
Charging batteries from solar panels is fundamentally no different from charging via another power source, so you can use the same battery chargers for solar panels as well.

However, there are a few specifics to watch out for when using solar cells:

* **Voltage Range:** Solar panels can emit a huge voltage range, and your charger must be capable of accepting this range. For best efficiency, such a charger should be a boost-buck-converter to utilize both voltages *under* and *above* the desired output voltage.
* **MPPT (maximum power point tracker):** the efficiency of power transfer from the solar cell depends on various factors such as sunlight, shading, solar panel temperature and the load's electrical characteristics. MPPT DC-DC converters can adjust the duty cycle to match the best (most efficient) impedance. While you do not have to use dedicated MPPT chargers, they might be able to increase your solar harvest.  



> Tags: Charger, CC, CV, Battery

[Visit Page on Website](https://done.land/components/power/chargers?247473031903243238) - created 2024-03-03 - last edited 2025-01-11
