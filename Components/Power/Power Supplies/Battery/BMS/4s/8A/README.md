<img src="/assets/images/battery.png" width="100%" height="100%" />


# 4S 8A Battery Management Systems (BMS)

> BMS For Four Battery Strings And 8A Max Current



> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. *Locked state* is also entered whenever *over-current protection* was triggered. To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.



> [!CAUTION]
> When connecting batteries to your **BMS**, make sure to use *wires* with sufficient diameter for the anticipated *high currents*.


> [!CAUTION]
> When designing *battery packs*, use batteries of *same type* and *same state of charge* only. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 



## 8A

[LiIon](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}
 [LiPo](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}
For currents up to **8A**, you can use a **BMS** with a square form factor. This makes it ideal for battery packs with four *18650 LiIon* cells but can also be used for other lithium batteries including *LiPo*:

<img src="images/4s_8a_top_angle_t.png" width="50%" height="50%" />

There are quite a few connectors on this board that are accessible only from the top. Make sure you connect your batteries correctly.

<img src="images/4s_8a_wiring.png" width="50%" height="50%" />

Connect the batteries like this:

* First battery string to **B-** (-) and **B1** (+)
* Second battery string to **B1** (-) and **B2** (+)
* Third battery string to **B2** (-) and **B3** (+)
* Forth battery string to **B3** (-) and **B+** (+) 

The output voltage is available at the (relatively small) **P+** and **P-** terminals.

The terminals **B1** and **B3** are also available on the back side of the board:

<img src="images/4s_8a_bottom_t.png" width="50%" height="50%" />


### Specs

| Protection | Threshold | 
| --- | --- | 
| Over-Charge | >4.25V |
| Over-Discharge | 2.3-3.0V |
| Over-Current | 20A | 
| Short Circuit | yes,resettable | 
| Continuous Current | 8A |
| Size | 34x34x3.2mm |


### Charging

When *charging* batteries through this **BMS**, the charging voltage needs to be *16.8-17.0V*. The **BMS** limits the charging current to *6A*.


> Tags: Battery, BMS, 4S, 8A

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/bms/4s/8a?268282020426240854) - created 2024-02-27 - last edited 2024-02-27
