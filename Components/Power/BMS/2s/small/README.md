# 2S BMS for Small Loads
:stopwatch: Reading time: 10 minutes.

## Overview

For projects with small current needs in the range of *3A* with occasional spikes of up to *5A*, a tiny breakout board can provide all the protection features needed. 

The board dinmensions are a mere 3.6cm x 0.7cm at 2mm overall height. The total cost including customs and shipping is around EUR 0.50/piece when ordered in quantities of 10.

> [!TIP]
> There are BMS boards with much higher specs at similar cost. It still makes a lot of sense to look into this module because of its size. 
>
> If your project does not require huge currents, then why waste precious space when you can get all the required battery protection in such a small form factor?

## Setup

The board comes with balancing capabilities: One battery is connected to **B+** and **BM**. The other battery is connected to **B-** and **BM**.

Both batteries are connected in series. The combined output is available at **P+** and **P-** and delivers *7.4V* to *8.4V*.

With just 3uA, the *BMS* has a neglectible standby current consumption. It can stay connected with the battery without risk of draining it.

> [!IMPORTANT]  
> The *BMS* can also charge the batteries when you connect a *constant current* power source to **P+** and **P-**. The recommended way of charging is however to add a separate *2S* charger board and connect it to **P+** and **P-**..


## Protection Features

Here is the list of protection features:

| Feature | Support | Trigger Threshold |
| --- | --- | --- |
| Over voltage | yes | >4.25-4.35V |
| Over discharge | yes | <2.3-3V |
| Max continuous current | yes | 3A |
| Max peak current | yes | 5A |
| Short circuit | yes | resettable by initiating a charge |

[Visit Page on Website](https://github.com/tobiaspsp/doneland_sources/components/power/bms/2s/small?300197020426240854)
