<img src="/assets/images/battery.png" width="100%" height="100%" />


# 3S - Using 3 Batteries in Series

> 3S BMS Protect Three (Groups of) Batteries From Mishap. Combined With Balancing They Are A Perfect Fit For Your Batteries.

A **3S BMS** is needed to protect *three* batteries (or groups of batteries connected *in parallel*) that are connected *in series*. 

Each lithium battery has a voltage between *3.2V*-*4.2V*, depending on state of charge. When you connect three of them *in series*, the **BMS** needs to handle a voltage in the range of *9.6V*-*12.6V*.

> [!IMPORTANT]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. 
> *Locked state* is entered whenever *over-current protection* was triggered. 
> To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply *12.6-13.0V* to its output terminal.



> [!CAUTION]
> When connecting batteries to your **BMS**, make sure you use *wires* with sufficient diameter for the anticipated *high currents*.
> Also make sure you only use batteries of *same type* and *same state of charge*. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 


All **BMS** listed below are designed for *LiIon* and *LiPo* batteries. They are not compatible with *LiFePo4* batteries because *LiFePo4* uses different cell voltages.

## 20A

For currents up to **20A**, here is a rugged and balanced **BMS**:

<img src="images/3S_20A_top_angle_t.png" width="100%" height="100%" />


Connect the batteries like this:

* First battery string to **0V** (-) and **4.2V** (+)
* Second battery string to **4.2V** (-) and **8.4V** (+)
* Third battery string to **8.4V** (-) and **12.6V** (+)

<img src="images/3s_20a_wiring.png" width="100%" height="100%" />

The output voltage is available at the terminals marked  **+** and **-**.


All terminals are also available at the bottom:

<img src="images/3S_20A_bottom_t.png" width="100%" height="100%" />


### Specs

| Protection | Threshold | 
| --- | --- | 
| Over-Charge | >4.25V |
| Over-Discharge | <2.5V |
| Over-Current | 60A (100ms delay) | 
| Short Circuit | yes,resettable | 
| Continuous Current | 20A |
| Size | 59x20x3.4mm |


### Charging

When *charging* batteries through this **BMS**, the charging voltage needs to be *12.6-13.0V*. The **BMS** limits the charging current to *10A*.


> Tags: Battery, BMS, 3S

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/bms/3s?268282020426240854) - last edited 2024-02-27
