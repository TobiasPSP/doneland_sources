# 2S BMS for Medium Loads
:stopwatch: Reading time: 10 minutes.

## Overview

For projects with medium current needs in the range of *8A* with occasional spikes of up to *15A*, at 4.1cm x 1.6cm x 0.35cm a small and reasonably-priced breakout board delivers the required protection features. 

The total cost including customs and shipping is around EUR 0.80/piece when ordered in quantities of 10.

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
| Over discharge | yes | <2.5-3V |
| Max continuous current | yes | 8A |
| Max peak current | yes | 15A |
| Short circuit | yes | resettable by initiating a charge |

[Visit Page on Website](https://github.com/tobiaspsp/doneland_sources/components/power/bms/2s/medium?275263020426240854)
