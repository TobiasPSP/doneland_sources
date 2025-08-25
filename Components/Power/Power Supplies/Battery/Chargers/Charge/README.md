<img src="/assets/images/charging.png" width="100%" height="100%" />

# Battery Chargers

> Modules For Charging Batteries

There is a huge variety of modules available to charge batteries. Picking the correct one can be challenging as they need to fit the battery you are intending to charge.

## Overview

Charger modules **must fit the battery type** you are intending to charge: the output voltage must match, and the charging current must never exceed the thresholds of your battery.

Here is what to look out for:

* **Battery Type (Chemistry):**  
  Make sure the charger fits your battery chemistry. Most chargers target *LiIon/LiPo* while others target *LiFePo4*.  

  Since voltages differ, using a *LiFePo4* charger on a *LiIon* battery will not fully charge it, while a *LiIon* charger applied to a *LiFePo4* battery will over-charge and likely destroy the battery.  

* **Strings:**  
  Batteries often internally connect multiple battery cells in series to increase the voltage. The number of battery cells that are connected **in series** is called a **string**.  

  Simple chargers target **1S** batteries (single cells). If you want to charge battery packs with multiple battery cells inside (that are connected in series; parallel does not count), make sure the string (number of cells in series) matches the charger voltage.

  |String Count|LiIon/LiPo|LiFePo4|
  |---|---|---|
  |1S|3.7|3.2|
  |2S|7.4|6.4|
  |3S|11.1|9.6|
  |4S|14.8|12.8|
  |5S|18.5|16.0|
  |6S|22.2|19.2|
  |7S|25.9|22.4|
  |8S|29.6|25.6|

* **Current:**  
  More is not always better: the maximum charging current that a charger can deliver must not exceed the charging current the battery can safely accept. Otherwise, excess charging energy turns into heat and can set the battery on fire.

  The maximum charging current a battery can accept is specified in "C", where "C" represents the battery capacity: so a battery charging rate of **1C** for a 1000mAh battery would equal a maximum charging rate of 1000mA. The same **1C** for a 400mAh battery would result in a maximum current of just 400mA.

  Unless you positively know that your battery can sustain higher rates, the below table provides some rough estimates:

  | Battery Chemistry | Typical Charging Rate |
  | --- | --- |
  | LiIon | 0.5-1C |
  | LiPo | 0.3-0.5C |
  | LiFePo4 | 1-2C |

## Charger Design

The most fundamental aspect of charger modules is how they convert input voltage to the required battery charging voltage:

* **Buck:**  
  Most affordable and simple charger boards are buck converters. Buck converters can only reduce voltage, so the input voltage must always be higher than the required charging (output) voltage due to their inherent topology.  

* **Boost:**  
  Some sophisticated charging boards boost a low input voltage to the required (higher) charging voltage. This is especially useful if you want to charge a 2-5S battery pack from 5V USB.  

* **Buck/Boost:**  
  The most advanced charger boards accept any voltage in a wide range and convert it to the required charging voltage. The input voltage can be lower or higher than the output voltage. This can be useful when input voltage fluctuates, i.e., with solar panels.  

### Components

There are three categories of charger designs, each with different efficiency and size characteristics:

* **Simple and bulky:**  
  Simple and very affordable modules use discrete components like power MOSFETs and large inductors to implement the charger logic.  

  They are typically bulky and less efficient, which is why they can generate a lot of heat and may require additional heat sinks.  

* **IC-based:**  
  There is a wealth of very affordable and very small charger boards based on specialized ICs (such as the TP4056). These ICs target highly specific use cases, i.e., charging a single LiIon cell.

  If that's exactly what you want, then charger boards based on such ICs are a perfect choice. These designs are usually quite efficient for their intended purpose.

* **Sophisticated Power Management ICs:**  
  In recent years, an armada of highly sophisticated power management ICs evolved. First developed for commercial powerbanks, they are now also readily available as DIY breakout boards.

  They are highly efficient, configurable, and can often be tailored to exactly the battery pack configuration you need. Some chips can even be configured digitally via *I2C*, while others still require external resistors for configuration.



> Tags: Battery chargers, LiIon, LiPo, LiFePO4, Strings, C-Rate, Buck, Boost, Battery Management

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge?891113081818254701) - created 2025-08-17 - last edited 2025-08-17
