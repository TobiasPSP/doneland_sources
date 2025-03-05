<img src="/assets/images/battery.png" width="100%" height="100%" />


# 2S 4A Battery Management Systems (BMS)

> BMS For Two Battery Strings And 4A Max Current



> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. *Locked state* is also entered whenever *over-current protection* was triggered. To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.



> [!CAUTION]
> When connecting batteries to your **BMS**, make sure to use *wires* with sufficient diameter for the anticipated *high currents*.


> [!CAUTION]
> When designing *battery packs*, use batteries of *same type* and *same state of charge* only. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 



## 4A

[LiIon](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}
 [LiPo](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}
For currents up to **4A**, you can use a small **BMS**:

<img src="images/bms_2s_4a_angle_t.png" width="100%" height="100%" />

The board shape suggests that this *BMS* was designed to be used with two *18650* batteries but can of course be used with any *LiIon* or *LiPo* batteries.

There are no connectors located on the back:

<img src="images/bms_2s_4a_back_t.png" width="100%" height="100%" />


Connect the batteries like this:

* First battery string to **B-** (-) and **BM** (+)
* Second battery string to **BM** (-) and **B+** (+)


The output voltage is available at **P+** and **P-**.

<img src="images/bms_2s_4a_top_t.png" width="100%" height="100%" />


### Specs

| Protection | Threshold | 
| --- | --- | 
| Over-Charge | >4.3V (delay time *1s*), recovery voltage 4.05V |
| Over-Discharge | <3V (detection time *128ms*), recovery voltage 3.2V |
| Over-Current | 9.8A (delay time *12ms*), auto-recovery | 
| Short Circuit | yes (delay time <50us), auto-recovery | 
| Continuous Current | 4A |
| Size | 35x17mm |




> Tags: Battery, BMS, 2S, 4A

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/bms/2s/4a?133747031821241432) - created 2024-03-21 - last edited 2024-03-21
