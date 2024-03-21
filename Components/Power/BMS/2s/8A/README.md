<img src="/assets/images/battery.png" width="100%" height="100%" />


# 2S 8A Battery Management Systems (BMS)

> BMS For Two Battery Strings And 8A Max Current




> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. 
> *Locked state* is entered whenever *over-current protection* was triggered. 
> To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.



> [!CAUTION]
> When connecting batteries to your **BMS**, make sure you use *wires* with sufficient diameter for the anticipated *high currents*.
> Also make sure you only use batteries of *same type* and *same state of charge*. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 



## 8A

[LiIon/LiPo](#){:.button.button--success.button--rounded.button--sm}


For currents up to **8A**, a board with more powerful *MosFET* like this one is necessary:

<img src="images/bms_2s_8a_top_angle_t.png" width="100%" height="100%" />

The terminals are accessible both from top and bottom.

<img src="images/bms_2s_8a_wiring.png" width="100%" height="100%" />


Connect the batteries like this:

* First battery string to **B-** (-) and **BM** (+)
* Second battery string to **BM** (-) and **B+** (+)

The output voltage is available at **P+** and **P-**.


### Specs

| Protection | Threshold | 
| --- | --- | 
| Over-Charge | >4.3V | 
| Over-Discharge | <2.5V | 
| Over-Current | 15A | 
| Short Circuit | yes,resettable | 
| Continuous Current | 8A |
| Size | 41x16x3.5mm |


> Tags: Battery, BMS, 2S, 8A

:eye:&nbsp;[Visit Page on Website](https://done.land/components/power/bms/2s/8a?927886031416241946) - last edited 2024-03-16
