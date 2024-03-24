<img src="/assets/images/battery.png" width="100%" height="100%" />


# 1S 2A Battery Management Systems (BMS) 

> BMS For A Single Battery String And 2A Max Current


> [!NOTE]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. *Locked state* is also entered whenever *over-current protection* was triggered. To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply the appropriate charging voltage to its output terminal.


## 2A


[LiIon](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}
 [LiPo](https://done.land/fundamentals/battery){:.button.button--success.button--rounded.button--sm}


For currents up to **2A**, you can use a tiny **BMS**:

<img src="images/bms_1s_2_5a_angle_t.png" width="50%" height="50%" />

> [!TIP]
> This board often goes by the model number *HX-1S-3038*.

The solder pads for the battery are available on both sides and marked **B+** and **B-**:

<img src="images/bms_1s_2_5a_top_t.png" width="50%" height="50%" />

Due to the *small size*, all markings are printed on the *back side only*:

<img src="images/bms_1s_2_5a_back_t.png" width="50%" height="50%" />


The output voltage is available at the terminals **P+** and **P-** in the middle of the backside.

### Specs


| Protection | Threshold |
| --- | --- | 
| Operating Current | 2A |
| Upper Peak Current | 2.5A |
| Over-Charge | >4.25V |
| Over-Discharge | <2.5V |
| Short-Circuit Protection | yes, delayed self-recovery |
| Size | 30x3.7x2.2mm |


> Tags: Battery, BMS, 1S, 2A, HX-1S-3038


