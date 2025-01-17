<img src="/assets/images/charging.png" width="100%" height="100%" />

# Charging Fundamentals

> How Battery Chargers Work

Safely charging a rechargeable battery requires a *charger*, but what exactly does a charger do, and how does it differ from a regular power supply like a bench power supply?

## Overview
To recharge a battery, you need to reverse the flow of electric energy and feed fresh current into the battery. To do this right, you need to consider these two key factors of any battery:

* **Total Battery Capacity:** You cannot supply more energy to a battery than it can hold. Once the battery is full, any excess energy would be turned into heat and could cause the battery to catch fire or explode. The indicator for a battery's *state of charge* is its *voltage*: empty batteries have a lower voltage than full batteries.
* **Speed of Charge:** You cannot charge a battery *faster* than it can absorb the energy. If you supply more *current* to a battery than it can absorb, the excess energy again would be turned into heat and could cause the battery to catch fire or explode. The indicator for the *speed of charge* is the *current*. As a rule of thumb, batteries should not be charged with more than *1C*, where *C* is the total battery capacity. For example, a *2000mAh* battery can be charged with a **maximum** of *2000mA*. 

> [!IMPORTANT]
> *1C* is a **rule of thumb** and can vary for your particular battery. There are high-power batteries that accept *10C*, but also simpler batteries that can only accept *0.5C*. Keep in mind that this is *the maximum* current a battery can accept. If you are not in a rush, you can (and should) use lower currents for charging, such as *0.1C*. Charging takes longer this way but is safer and reduces battery stress, prolonging its lifespan.

The job of a charger is to control the supply of energy and keep it within the thresholds the battery can safely absorb.

## Voltage Limiting
The first job of a charger is to *limit the voltage* to the maximum battery voltage. This prevents excess energy from going into a fully charged battery. Here is how this works:

During charging, the battery voltage rises to keep the current constant. When the battery is fully charged, the battery voltage reaches a specific voltage that depends on the battery chemistry:

| Battery Chemistry | Empty Voltage | Nominal Voltage | Fully Charged Voltage |
|-------------------|---------------|-----------------|-----------------------|
| **Li-ion**        | ~3.0V         | 3.6V–3.7V       | 4.2V                 |
| **LiPo**          | ~3.0V         | 3.7V            | 4.2V                 |
| **LiFePO₄**       | ~2.5V         | 3.2V–3.3V       | 3.6V–3.65V           |

If the charger limits its voltage to this maximum value, once the battery voltage reaches this level, no more energy flows from the charger to the battery because there is no driving voltage difference.

<details><summary>What if I use a Constant Voltage Power Supply For Charging?</summary><br/>

Let's assume you use a simple *4.2V power supply* to charge a *Li-ion* battery. Since the voltage does not exceed the maximum battery voltage, there would be no flow of current once the battery is fully charged. That's good.

Until then, though, the power supply would always supply its maximum current. Put differently, the *speed of charging* would depend solely on the current the power supply can deliver.

This current might exceed the energy the battery can absorb, posing a serious fire hazard. So never use a simple (*constant voltage*) power supply for charging.

That said, and while keeping in mind that using such a power supply for charging can be very dangerous: if the power supply has a maximum current below the maximum charging current of your battery, you *might* get away with it.

For example, if you wanted to charge a *2000mAh 18650 Li-ion cell*, and you connected a simple *1A 4.2V* power supply to it, the battery would probably charge safely. The maximum current the power supply can deliver would act as the required *constant current* control.

However, since a battery has very low *internal resistance*, this might in turn damage your power supply or trigger a fuse: for the power supply, charging an empty battery would resemble short-circuiting its outputs.

</details>

### Current Limiting
Aside from *limiting the voltage*, a charger must also *limit the current* to the maximum current the battery can safely absorb at any time. At its core, a battery charger is therefore a *CV CC power supply*.

### Charging Curves
You might have seen sophisticated *charging curves* with *constant current* and *constant voltage* phases, suggesting that a charger must have advanced control technology and sensors to produce these curves. That is not entirely true. These curves are the natural result of applying a *CC CV power supply* to a battery.

Before we look at why that is, let's first clarify some terms: with battery chargers, the terms *constant current* (CC) and *constant voltage* (CV) are misleading. More accurate terms would be *maximum current* and *maximum voltage*.

Here is what happens during charging:

* **Constant Current, Increasing Voltage:** When charging an empty battery, its voltage is lower than the charger’s maximum voltage, so current flows from the charger to the battery. Since the battery has very low internal resistance, very high currents would normally flow. However, the charger limits the current to a safe maximum by *lowering its voltage*. In this initial charging phase, the current is constant (limited) while the voltage gradually increases as the battery charges.
* **Constant Voltage, Decreasing Current:** Once the battery reaches its maximum voltage, the charger maintains this *constant voltage*. As the battery continues to absorb energy, the current decreases over time as the voltage no longer rises to keep the current constant.  

When the current eventually falls below a certain threshold, the charger assumes the battery is fully charged and stops charging.

<details><summary>What if I use a CV CC Power Supply For Charging?</summary><br/>

Let's assume you use one of the many available *constant-voltage constant-current* DC-DC converters. Let's further assume you wanted to charge a *2000mAh 18650 Li-ion cell* with it.

*Li-ion cells* are considered fully charged at *4.2V*, and the typical maximum charging current is *1C*. If you set the *constant voltage* to *4.2V* and the *constant current* to *2000mA*, then you could indeed use this power supply to charge the battery.

However, it would still not be a safe charger. Here are the missing features:

* **Automatic Turn-Off:** When the charging current drops below a certain threshold (indicating the battery is full), the charger turns off completely whereas a regular CC CV power supply would not.
* **Temperature Control:** The charger might monitor the battery temperature, as unexpected temperature rises indicate failure (i.e. damaged battery), and charging must stop immediately. Some chemistries, like *LiFePO₄*, are damaged if charged below *0°C*. Good chargers account for this and stop charging when temperatures are too low.
* **Low Voltage Control:** Batteries in long-term storage may self-discharge below safe voltage levels. When a charger detects such conditions, it either refuses to charge or uses very low currents to "revive" the battery until safe voltage levels are reached. 
* **Automatic Recharge:** Some chargers restart the charging process if the battery voltage drops below a certain threshold due to self-discharge. This ensures the battery remains charged.

</details>


> Tags: Charger, CC, CV, Battery

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/fundamentals?742219011712254827) - created 2025-01-11 - last edited 2025-01-11
