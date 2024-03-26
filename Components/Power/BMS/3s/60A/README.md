<img src="/assets/images/battery.png" width="100%" height="100%" />


# 3S 60A Battery Management Systems (BMS)

> BMS For Three Battery Strings And 60A Max Current


> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. *Locked state* is also entered whenever *over-current protection* was triggered. To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.


> [!CAUTION]
> This *BMS* is designed for *high currents*. Use copper 3mm2 copper wires to connect the batteries.  



> [!CAUTION]
> When designing *battery packs*, use batteries of *same type* and *same state of charge* only. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 


## 60A

[LiIon](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}
 [LiPo](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}

For currents up to **60A**, here is a rugged and balanced **BMS**:

<img src="images/bms_3s_60a_angle_t.png" width="50%" height="50%" />

> [!CAUTION]
> There is a similar board available for currents up to **40A**. Make sure you check the markings on the board. These *BMS* are designed for *tool batteries* (i.e. a drill) that draw a *high initial* current. The *continuous current* is typically much lower and should not exceed **30A**. Make sure you connect *batteries* with the appropriate current capabilities. Typically batteries with **20C** or more discharge current are required. 

> [!NOTE]
> A *heat sink* may be required with *continuous* currents exceeding **30A**.

### Connections

Connect the batteries like this:

* First battery string to **0V** (-) and **4.2V** (+)
* Second battery string to **4.2V** (-) and **8.4V** (+)
* Third battery string to **8.4V** (-) and **12.6V** (+)

<img src="images/bms_3s_60a_top_t.png" width="50%" height="50%" />

The output voltage is available at the terminals marked  **+** and **-** at the port labelled *Discharge*.


All terminals are also available at the bottom:

<img src="images/bms_3s_60a_bottom_t.png" width="50%" height="50%" />


### Specs

| Protection | Threshold | 
| --- | --- | 
| Continuous current | 60A |
| Over-Charge | >4.20V |
| Over-Discharge | <3.0V |
| Over-Current | 125A  | 
| Short Circuit | yes,resettable | 
| Continuous Current | 20A |
| Size | 62x41x3.4mm |

> [!NOTE]
> The vendor claims this *BMS* has a *short circuit protection*. At the same time the vendor warns to deliberately *short circuit* the *BMS*. Due to the high currents, it is likely that the *BMS* can be damaged by a prolonged *short circuit* due to excessive *heat*. 

### Charging

This *BMS* has dedicated *charging* terminals marked as *Charge*. Charging voltage needs to be *12.6-13.6V*. The **BMS** limits the charging current to *20A*.


> Tags: Battery, BMS, 3S, 60A

[Visit Page on Website](https://done.land/components/power/bms/3s/60a?354301032326245105) - created 0001-01-01
