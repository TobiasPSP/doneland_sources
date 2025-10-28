<img src="/assets/images/battery.png" width="100%" height="100%" />


# 4S - Using 4 Batteries in Series

> 4S BMS Protect Four (Groups of) Batteries From Mishap. Combined With Balancing They Are A Perfect Fit For Your Batteries.


4S battery packs are a popular choice because they result in a raw battery voltage of *10.0-14.6V* (for LiFePo4 cells) and *12.0V-16.8V* (for LiIon/LiPo cells), depending on state of charge.

This makes them ideal for supplying power to 12V loads: by adding a buck-boost-converter, the battery pack can deliver stabilized 12V output at minimal losses.

A 4S BMS is required for basic battery pack protection. The BMS is neither a charger nor a discharger and simply cuts off the power in cases of short circuit (fire hazard) or over-discharge (battery cell damage).

## Caveats

When building 4S battery packs, it is crucial to pick battery cells of same type and state-of-charge. Always make sure all four cells are fully charged.

### Using Adequate Battery Cells

If you use batteries of different type or age, or if one of the cells isn't fully charged, yozr entire battery pack will perform as bad as the worst cell you used:

Let's assume you forgot to charge one of the four cells. When you later charge the battery pack through the BMS, it will detect that three of the four cells are eventually fully charged, and stop charging. The forth cell that wasn't initially fully charged will never receive a full charge.

When you then use your battery pack to power a load, the halfway charged cell will first reach the over-discharge voltage, and the BMS cuts power - even though the other three cells are still good to go.

So by not fully charging one of the four cells, you are effectively crippling the overall capacity of your battery pack to the charge that was in that forth cell when you assembled it.

### Balancing

As you have seen, the culprit with multi-string batteries is **balancing**: such packs work well only when all cells are *balanced* and charged to the same level.

A **balancer** can equal out cell imbalances:

* **Simple BMS:**     
  Simple and cost-effective BMS do not balance at all. That's ok as long as you carefully pick battery calls that are **absolutely identical** in state, capacity, age, and make.    
* **Passive Balancing:**    
  Average BMS come with **passive** balancing, and you can also add dedicated passive balanacer modules to simple BMS: if a cell reaches full-charge voltage before other cells, the excess power is wasted and converted to heat until all cells are fully charged. Passive balancing is not very efficient, and balancing currents are very small (in the mA range). While passive balancers can prevent imbalances from happening, they cannot typically heal gross imbalances due to differences in cells or their state-of-charge during assembly.
* **Active Balancing:**      
  These typically are dedicated modules that can be added to a BMS. Active balancers **actively** feed extra charging current into cells that are behind. The balancing current is **much higher** than with passive balancers, often in the *Ampere* region.

## Example

I am frequently using 4S battery packs for projects involving 12V loads:

* [Powering Hänsch Comet Emergency Light from Internal 4S Battery](https://done.land/components/power/powersupplies/battery/chargers/charge/buck-boost/lifc2-n/portableemergencylight/)



> Tags: Battery, BMS, 4S

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/bms/4s?998282020426240854) - created 2024-02-27 - last edited 2025-10-27
