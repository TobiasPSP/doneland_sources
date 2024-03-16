<img src="/assets/images/battery.png" width="100%" height="100%" />


# 2S 10A Battery Management Systems (BMS)

> BMS For Two Battery Strings And 10A Max Current




> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. 
> *Locked state* is entered whenever *over-current protection* was triggered. 
> To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.



> [!CAUTION]
> When connecting batteries to your **BMS**, make sure you use *wires* with sufficient diameter for the anticipated *high currents*.
> Also make sure you only use batteries of *same type* and *same state of charge*. It is recommended you *fully charge* all batteries before connecting. All batteries must have *the same voltage* (voltage difference less than *0.05V*). Do not mix batteries from different vendors, types, capacity, or age. 



## 10A

[LiIon/LiPo](#){:.button.button--success.button--rounded.button--sm}


For currents up to **10A**, a very *compact* board is available:

<img src="images/2s_10a_top_angle_t.png" width="100%" height="100%" />

Unfortunately, the compactness of the board did not leave room for markings on the front side. Instead, the markings for the soldering pads were printed on the *back side*:


<img src="images/2s_10a_wiring.png" width="100%" height="100%" />

On the other end, the board has a big soldering pad marked as **B-** which is accessible from both sides, and two smaller ones marked **B1** and **B+** on the backside whereas the solder pads are accessible on the front.


Connect the batteries like this:

* First battery string to **B-** (-) and **B1** (+)
* Second battery string to **B1** (-) and **B+** (+)

The output voltage is available at **B+** and **C-**. These two pads are accessible from both sides.


### Specs

| Protection | Threshold | 
| --- | --- | 
| Over-Charge | >4.3V | 
| Over-Discharge | <2.3-2.5V | 
| Over-Current | 16A | 
| Short Circuit | yes,resettable, 200mS delay | 
| Continuous Current | 10A |
| Size | 24x11x2mm |


### Charging

When *charging* batteries through this **BMS**, the charging voltage needs to be *8.4V*. The **BMS** limits the charging current to *10A*.

> [!CAUTION]
> This board is available as **1S BMS** also and looks almost the same. The **1S BMS** is lacking the **B1** terminal.

> Tags: Battery, BMS, 2S, 10A

:eye:&nbsp;[Visit Page on Website](https://done.land/components/power/bms/2s/10a?828179031416241946) - last edited 2024-03-16
