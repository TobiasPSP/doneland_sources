# Battery Management System (BMS)
:stopwatch: Reading time: 10 minutes.

## Overview

All types of *lithium*-based rechargable batteries store enormous amounts of energy. They need electronic protection for safe operation:

* **Fire Hazard**: the stored energy can erupt in flames or explode when the battery is physically damaged or short circuited, or when it is *charged* below or above safe voltage thresholds where the battery cannot store the excess energy anymore.
* **Permanent Battery Damage**: permanent damage (loss of battery capacity or complete destruction) may occur when the battery is fully discharged. Discharge must stop at a certain minimum voltage. Else, the battery chemistry will experience irreversible structural damage. 

A **BMS** is an electronic circuit that protect from these risks. Without a **BMS**, it is very easy to run into serious problems while using *lithium* batteries:

* You charge the battery and leave the charger connected. Without a **BMS** (or a clever charger), your *lithium* battery will eventually catch fire.
* You connect a device to your battery and leave it *on*, then walk away. Once the battery is completely drained, it also is permanently damaged.
* You accidentally connect both poles of the battery and produce a short circuit. Enormous currents will flow and can hurt you, or the battery explodes.

That's why most quality *lithium* batteries come with a basic **BMS** already integrated into them.

### Important Protection Features

*BMS* should have at minimum these key protection features:

| Feature | Typical Threshold | Description |
| --- | --- | --- |
| Over voltage | >4.3V | Prevents **fire hazard** from *over-charging*. When batteries are charged, voltage slowly rises. At a threshold voltage, it is fully charged and cannot store additional energy. If you charge beyond this point, the energy is converted to heat and may cause a fire or explosion |
| Over discharge | <2.3-3V | Prevents **permanent battery damage**. When you draw energy from a battery below a threshold voltage, its internal chemistry starts to change irreversibly, and the battery permanently loses capacity or does not work anymore at all. This feature also prevents **fire hazard**: *Charging* a battery below this threshold requires extra care as the battery cannot store much energy. When charged with normal currents, most of the energy is converted to heat and can cause fire or explosion. When the battery is below this threshold, the *BMS* must disable charging or charge with a *reduced* current until the minimum voltage threshold is reached. |
| Short circuit | varies | Protects **fire hazard** from *over-current*. Every battery can provide a maximum discharge current. If more current is drawn, or in the worst case if the battery output is short circuited, the battery releases so much energy in such a short time that resulting heat can set the battery on fire. A *BMS* sets a maximum current and - similar to a fuse - cuts off the load when the current is exceeded. Often resettable by initiating a charge. |
| Balancing | n/a | Protects from unevenly charging batteries (when the *BMS* controls more than one battery) by monitoring the voltages of all connected batteries individually, and adding extra charge to individual batteries if they lag behind other cells. Balancing improves overall battery lifetime and protects from **over- or under-charging** scenarios. Balancing is a protection for *charging*. During *discharge*, balancing is typically not required or useful.

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

## Do I Need A BMS?

Most quality batteries come with their **BMS** built-in without you noticing it. They are to some degree protected.

Adding your own **BMS** is always a good idea since you probably do not know the specs of the built-in **BMS** and whether it covers all important risks.

Once you start building your own battery constructs, i.e. by combining multiple batteries, you *should always* add your own **BMS**. 

> [!TIP]
> When you connect multiple batteries *in series* to get a higher output voltage, your **BMS** should have a *balancer* feature that kicks in during *charging* (it's not in use during *discharge*):
>
> the balancer makes sure each cell voltage is monitored individually. Without balancing, one battery could already be fully charged when another is not, resulting either in partially loaded batteries or risk of *over-charging* a battery.

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/bms?260305020426240854) - last edited 2024-02-27
