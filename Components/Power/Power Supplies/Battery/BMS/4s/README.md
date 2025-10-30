<img src="/assets/images/battery.png" width="100%" height="100%" />


# 4S - Using 4 Batteries in Series

> 4S BMS Protect Four (Groups of) Batteries From Mishap. Combined With Balancing They Are A Perfect Fit For Your Batteries.


4S battery packs are a popular choice because they result in a raw battery voltage of *10.0-14.6V* (for LiFePo4 cells) and *12.0V-16.8V* (for LiIon/LiPo cells), depending on state of charge.

This makes them ideal for supplying power to 12V loads: by adding a buck-boost-converter, the battery pack can deliver stabilized 12V output at minimal losses.

A 4S BMS is required for basic battery pack protection. The BMS is neither a charger nor a discharger and simply cuts off the power in cases of short circuit (fire hazard) or over-discharge (battery cell damage).

## Caveats

When building 4S battery packs, it is crucial to pick battery cells of same type and state-of-charge. Always make sure all four cells are fully charged. 

If you have the opportunity, measure the battery *internal resistance* (requires a special meter and cannot be done with a normal multimeter), and make sure these resistances are roughly equal for all cells.

### Using Adequate Battery Cells

If you use batteries of different type or age, or if one of the cells isn't fully charged, yozr entire battery pack will perform as bad as the worst cell you used.

Let's assume you forgot to charge one of the four cells. When you later charge the battery pack through the BMS, it will stop charging **all** cells once **any** cell reaches its top voltage. If cells aren't equal, or if one cell initially wasn't fully charged, it will no longer fully charge anymore because it is always lagging behind.

When you then later use your battery pack to power a load, the BMS cuts power once the **first** cell drops below the over-discharge voltage - which coincidentally is the worst cell or the one that  initially wasn't fully charged. So BMS cuts power even though the other three cells are still good to go.

With multi-string battery packs, you therefore easily cripple the overall capacity of your pack by using bad cells or by using cells that weren't initially fully charged. 



### Balancing

The culprit with multi-string batteries is **balancing**: such packs work well only when all cells are *balanced* and charged to the same level. If only one cell is out-of-balance, this cell dictates the behavior and severely limits overall capacity.

A **balancer** can equal out cell imbalances:

* **Simple BMS:**     
  Simple and cost-effective BMS do not balance at all. That's ok as long as you carefully pick battery calls that are **absolutely identical** in state, capacity, age, and make.    
* **Passive Balancing:**    
  Average BMS come with **passive** balancing, and you can also add dedicated passive balancer modules to simple BMS: if a cell reaches full-charge voltage before other cells, the excess power is wasted and converted to heat until all cells are fully charged. Passive balancing is not very efficient, and balancing currents are very small (in the mA range). While passive balancers can prevent imbalances from happening, they cannot typically heal gross imbalances that existed in the first place, i.e. due to differences in cell quality or their state-of-charge during assembly.
* **Active Balancing:**      
  These typically are dedicated modules that can be added to a BMS. Active balancers **actively** feed extra charging current into cells that are behind. The balancing current is **much higher** than with passive balancers, often in the *Ampere* region.

#### Balancers May Not Always Be Needed
Even renown manufacturers with excellent quality record may not use balancers  (i.e. *Makita* in their *5S tool battery packs*). Instead, they solely trust in first grade battery cells of equal specs and quality. 

This is much more important than balancing: balancing is merely **straightening out problems** that shouldn't occur in the first place when using good battery cells. 

So balancers maximize battery pack capacity when you must use lower grade battery cells (i.e. because you repurpose older batteries from different sources).   


## Example

I am frequently using 4S battery packs for projects involving 12V loads:

* [Powering Hänsch Comet Emergency Light from Internal 4S Battery](https://done.land/components/power/powersupplies/battery/chargers/charge/buck-boost/lifc2-n/portableemergencylight/)



> Tags: Battery, BMS, 4S

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/bms/4s?998282020426240854) - created 2024-02-27 - last edited 2025-10-27
