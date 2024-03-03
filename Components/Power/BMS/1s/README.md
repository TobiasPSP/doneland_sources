<img src="/assets/images/battery.png" width="100%" height="100%" />


# 1S - Protecting Single Batteries 

> 1S BMS Protect One (Groups of) Batteries From Mishap.

Single batteries often come with a *basic* **BMS** built-in. If you want more control over the protection features, you can select and add your own **1S BMS** according to your needs.

If you connect multiple batteries *in parallel* to build a battery pack with more power, you should always add your own **1S BMS**.


> [!IMPORTANT]
> **BMS** often ship in *locked state*: *no output voltage* is available at the output pins. 
> *Locked state* is entered whenever *over-current protection* was triggered. 
> To *unlock* the **BMS**, connect it to a charger. If you did not add a dedicated *charger board*, apply *4.2-4.5V* to its output terminal.



All **BMS** listed below are designed for *LiIon* and *LiPo* batteries. They are not compatible with *LiFePo4* batteries because *LiFePo4* uses different cell voltages.

## 5A

For currents up to **5A**, you can use a very simple **BMS**:

<img src="images/1s_5a_top_angle_t.png" width="100%" height="100%" />

Its long metal sleeves are designed to be fitted to *18650 LiIon Cells* using spot welding but you can shorten the connector terminals and solder them to *LiPo* as well.

<img src="images/1s_5a_wiring.png" width="100%" height="100%" />


On the backside, there are two terminals marked **B+** and **B-** that are identical to the metal sleeves and go to the battery.

The output voltage is available at the terminals **P+** and **P-** in the middle of the backside.

### Specs


| Protection | Threshold | Release | Delay |
| --- | --- | --- | --- | 
| Over-Charge | >4.3V | <4.1V | 70ms |
| Over-Discharge | <2.4V | >3.0V | 35ms |
| Over-Current | 5-6A | | |


> Tags: Battery, BMS, 1S

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/bms/1s?268282020426240854) - last edited 2024-02-27
