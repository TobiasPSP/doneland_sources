<img src="/assets/images/battery.png" width="100%" height="100%" />


# 2S 20A Battery Management Systems (BMS)

> BMS For Two Battery Strings And 20A Max Current




> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. 
> *Locked state* is entered whenever *over-current protection* was triggered. 
> To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.



> [!CAUTION]
> When connecting batteries to your **BMS**, make sure you use *wires* with sufficient diameter for the anticipated *high currents*.
> Also make sure you only use batteries of *same type* and *same state of charge*. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 



## 20A

[LiIon/LiPo](#){:.button.button--success.button--rounded.button--sm}


For currents up to **20A**, you need a bigger board with more *MosFETs* that share the load, like this one:

<img src="images/bms_2s_20a_top_angle_t.png" width="100%" height="100%" />

All terminals are accessible both from top and bottom.


<img src="images/bms_2s_20a_wiring.png" width="100%" height="100%" />


Connect the batteries like this:

* First battery string to **0V** (-) and **4.2V** (+)
* Second battery string to **4.2V** (-) and **8.4V** (+)


The output voltage is available at **+** and **-** located in the inside of the board.



### Specs

| Protection | Threshold | 
| --- | --- | 
| Over-Charge | >4.3V | 
| Over-Discharge | <2.3-2.5V | 
| Over-Current | 25A | 
| Short Circuit | yes,resettable, 200mS delay | 
| Continuous Current | 20A (may need heat sink) |
| Size | 48x20x3.4mm |


### Charging

When *charging* batteries through this **BMS**, the charging voltage needs to be *8.4-9.0V*. The **BMS** limits the charging current to *10A*.


> Tags: Battery, BMS, 2S, 20A

:eye:&nbsp;[Visit Page on Website](https://done.land/components/power/bms/2s/20a?862063031416241946) - last edited 2024-03-16