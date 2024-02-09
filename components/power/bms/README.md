# Battery Management System (BMS)
:stopwatch: Reading time: 10 minutes.

## Overview

*Lithium ion*, *lithium polymer*, and *LiFePo4* rechargable batteries store huge amounts of energy. Protection is needed for safe operation:

* **Fire Hazard**: The stored energy can erupt in seconds when the battery is physically damaged or short circuited and cause fire or explosions. Likewise, the battery can erupt in flames when it is *charged* below or above safe voltage thresholds.
* **Battery Damage**: Discharging below safe voltages can permanently damage the battery due to irreversible structural damages.

*Battery Management Systems* (BMS) are electronic circuits that help prevent damages. Often, simple *BMS* are already built into batteries. 

> [!IMPORTANT]  
> Once you add individual batteries in *series* to get a higher output voltage, you should always add your own *BMS*.


### Important Protection Features

The following protection features should be provided by a *BMS*:

| Feature | Typical Threshold | Description |
| --- | --- | --- |
| Over voltage | >4.3V | Protects fire hazard from *over-charging*. When batteries are charged, voltage slowly rises. At a threshold voltage, it is fully charged and cannot store additional energy. If you charge beyond this point, the energy is converted to heat and may cause a fire or explosion |
| Over discharge | <2.3-3V | Protects battery from permanent damage. When you draw energy from a battery below a threshold voltage, its internal chemistry starts to change irreversibly, and the battery permanently loses capacity or does not work anymore at all. |
| Short circuit | varies | Protects fire hazard from *over-current*. Every battery can provide a maximum discharge current. If more current is drawn, or in the worst case if the battery output is short circuited, the battery releases so much energy in such a short time that resulting heat can set the battery on fire. A *BMS* sets a maximum current and - similar to a fuse - cuts off the load when the current is exceeded. Often resettable by initiating a charge. |
| Balancing | n/a | Protects from unevenly charging batteries (when the *BMS* controls more than one battery) by monitoring the voltages of all connected batteries individually, and adding extra charge to individual batteries if they lag behind other cells. Balancing improves overall battery lifetime and protects from over- or under-charging scenarios. Balancing is a protection for *charging*. During *discharge*, balancing is typically not required or useful.

### Battery Voltage Thresholds

The threshold voltages a *BMS* needs to monitor can vary based on cell chemistry and manufacturer. Always consult the data sheet of the battery you are actually using.

There are rules of thumb:

| Chemistry | Min V | Max V | Nominal | 
| --- | --- | --- | --- | 
| LiIon | 2.7V | 4.2V | 3.7V | 
| LiPo | 3V | 4.2V | 3.7V | 
| LiFePo4 | 2.5V | 3.65V | 3.2 | 

* **Minimum Voltage**: If you continue to *discharge* the battery below *minimum voltage*, it can get permanently damaged. If you *charge* a battery that has a below-minimum voltage, much of the energy may be converted to heat, potentially leading to fire and explosion.
* **Maximum Voltage**: When *charging* a battery, the voltage increases up to the *maximum voltage* when it is fully loaded. When you continue to charge a battery beyond its *maximum voltage*, the energy can no longer be stored and is converted to heat, potentially leading to fire and explosion.
* **Nominal Voltage**: When in operation, the battery *on average* delivers the *nominal voltage*. Lithium batteries generally have a very flat voltage discharge curve, so between *minimum* and *maximum* voltage, the battery will deliver the *nominal voltage* for a very long period of time.
