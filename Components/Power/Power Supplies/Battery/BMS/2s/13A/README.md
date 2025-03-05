<img src="/assets/images/battery.png" width="100%" height="100%" />


# 2S 13A Battery Management Systems (BMS)

> BMS For Two Battery Strings And 13A Max Current





> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. *Locked state* is also entered whenever *over-current protection* was triggered. To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.



> [!CAUTION]
> When connecting batteries to your **BMS**, make sure to use *wires* with sufficient diameter for the anticipated *high currents*.


> [!CAUTION]
> When designing *battery packs*, use batteries of *same type* and *same state of charge* only. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 



## 13A

[LiIon](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}
 [LiPo](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}


For currents up to **13A**, this *balancing BMS* can be used:

<img src="images/bms_2s_13a_angle_t.png" width="50%" height="50%" />

All connections are available from both sides and are clearly marked:

<img src="images/bms_2s_13a_back_t.png" width="50%" height="50%" />


### Connection

Connect the batteries like this:

* First battery string to **B-** (-) and **BM** (+)
* Second battery string to **BM** (-) and **B+** (+)

The output voltage is available at **P+** and **P-**. 

> [!TIP]
> This board often has the model specification *HX-2S-D20* printed on the back side.

#### Specs

| Protection | Threshold | 
| --- | --- | 
| Over-Charge | >4.3V | 
| Over-Discharge | <2.5-3.0V | 
| Over-Current | 20A | 
| Short Circuit | yes, resettable | 
| Continuous Current | 13A |
| Size | 46.0x20.0x3.6mm |



#### Charging

When *charging* batteries through this **BMS**, the charging voltage needs to be *8.4V-9.0V*. The **BMS** limits the charging current to *10A*.

> [!CAUTION]
> A *heat sink* may be required with currents exceeding **8A**.




> Tags: Battery, BMS, 2S, 13A, HX-2S-D20

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/bms/2s/13a?039112031222243921) - created 2024-03-28 - last edited 2024-03-28
