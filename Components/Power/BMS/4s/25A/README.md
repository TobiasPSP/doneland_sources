<img src="/assets/images/battery.png" width="100%" height="100%" />


# 4S 25A Battery Management Systems (BMS)

> BMS For Four Battery Strings And 25A Max Current


> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. 
> *Locked state* is entered whenever *over-current protection* was triggered. 
> To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.



> [!CAUTION]
> When connecting batteries to your **BMS**, make sure you use *wires* with sufficient diameter for the anticipated *high currents*.
> Also make sure you only use batteries of *same type* and *same state of charge*. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 



## 25A

[LiIon/LiPo](#){:.button.button--success.button--rounded.button--sm}


For currents up to **25A**, this rounded multi-purpose board is available:

<img src="images/bms_4s_25A_top_angle_t.png" width="100%" height="100%" />


Connect the batteries like this:

* First battery string to **B-** (-) and **B** (+)
* Second battery string to **B** (-) and **B1** (+)
* Third battery string to **B1** (-) and **B2** (+)
* Forth battery string to **B2** (-) and **B+** (+)


<img src="images/bms_4s_25A_top_t.png" width="100%" height="100%" />


The output voltage is available at **P+** and **P-**. These two pads are accessible from both sides.

<img src="images/bms_4s_25a_wiring.png" width="100%" height="100%" />

> [!TIP]
> The terminal **A** is not used. It is reserved for the **5S** version of this board.



### Specs

| Protection | Threshold | 
| --- | --- | 
| Over-Charge | >4.25V |
| Over-Discharge | 2.8V |
| Over-Current | 60A | 
| Short Circuit | yes,resettable | 
| Continuous Current | 25A |
| Size | 50x22x4mm |


### Charging

When *charging* batteries through this **BMS**, the charging voltage needs to be *16.8-17.0V*. The **BMS** limits the charging current to *25A*.

### Changing **BMS** Type

This is a *multipurpose* board and can be used for **3S**, **4S**, and **5S**. The number of supported strings can be configured on the board at four locations:

<img src="images/bms_4s_25a_configloc-t.png" width="100%" height="100%" />

| Location | **3S** | **4S** | **5S** | 
| --- | --- | --- | --- |
| 1 | unconnected | 0R | unconnected |
| 2 | 0R | unconnected |unconnected |
| 3 | 0R | 0R |unconnected |
| 4 | 0R | unconnected |unconnected |

> [!TIP]
> *0R* refers to a 0-Ohm resistor (a solder bridge). If you'd like to change the configuration of your **BMS**, you can remove **0R** resistors (to switch to *unconnected*), or *bridge* the pads with solder (to switch to *0R*). No need to try and move around and re-solder the tiny *0R* resistors.

For **3S BMS**, connect the batteries like this:

* First battery string to **B-** (-) and **B1** (+)
* Third battery string to **B1** (-) and **B2** (+)
* Forth battery string to **B2** (-) and **B+** (+)

For **5S BMS** connect the batteries like this:

Connect the batteries like this:

* First battery string to **B-** (-) and **A** (+)
* Second battery string to **A** (-) and **B** (+)
* Third battery string to **B** (-) and **B1** (+)
* Forth battery string to **B1** (-) and **B2** (+)
* Fifth battery string to **B2** (-) and **B+** (+)

> Tags: Battery, BMS, 4S, 25A

:eye:&nbsp;[Visit Page on Website](https://done.land/components/power/bms/4s/25a?704910031516242508) - last edited 2024-03-16
