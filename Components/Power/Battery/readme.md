<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Batteries

> Batteries Provide Portable Power. Rechargeable Batteries Store Immense Energy And Can Be Refilled Thousands Of Times 

A battery cell contains *chemistry* able to *store electrons*. Regular batteries use *chemistries* that cannot be *recharged*. *Rechargeable batteries* can be re-charged thousands of times.

A number of different chemistries are in use today that vary considerably in *price*, *energy density*, and other specs. Let's first take a look at use cases, then closer investigate the specific advantages and disadvantages of each chemistry.

## Use Cases
In *DIY scenarios*, these chemistries are worth mentioning:

* **Lead-Acid:** due to its low cost per *Wh*, commonly used in *model making* when weight does not matter (i.e. ship modelling)
* **NiCad:** Not widely used anymore due to its toxic *Cadmium* ingredient.
* **NiMH:* Used for *rugged environments*, i.e. in solar lamps (that must sustain high operating temperatures)
* **LiIon:** commonly used to power all kinds of small devices, due to their high energy density
* **LiPo:** highly popular due to their flexible sizes that can be easily fit into even small devices. 
* **LiFePo4/LFP:** used whenever large amounts of energy are required (and size and weight is secondary). Also used to directly power *3.3V microcontrollers* (without the need for a voltage regulator) in low-power devices.

## Chemistry Types

Batteries behave differently based on their *chemistry*:


| Battery Type  | Cost per Wh  | Life Span         | C-Rate | Energy Density  (Wh/kg) | Depth of Discharge | Self-Discharge/month | Nominal cell voltage | Operating Temperature (Celsius) |
|---|---|---|---|---|---|---|---|---|
| Lead-Acid | €0.09  | 3-12 years | 2-3 | 30-50 | 50% | 10-15% | 2.2V | -40 to +55 |
| NiCd | €1.05-€1.31 | 1500 cycles | 15 | 40-60 | 80% | 20% | 1.2V | -40 to +70
| NiMH | €1.30-€1.80 | 180-1000 cycles | 1 | 70-100 | 80% | 100% (4%/day), less with modern NiMH| 1.2V | -30 to +100 | 
| Li-Ion        | €0.28-€0.50     | 500-1000 cycles | 1 | 150-200 |80-90% | 1-5% | 3.6V | -20 to +60 |
| LiPo          | €0.59-€0.80     | 300-500 cycles | 1 | 150-250 | 80-90% | 1-5% | 3.7V | -20 to +60 |
| LiFePo4       | €0.08-€0.45     | 2000+ cycles | 1 | 90-120 | 80-90% | 1-5% | 3.2V | -20 to +45|

A few notes:

* **Price:** Cost is just an estimate and is affected by the typical *battery sizes*. *NiCd* and *NiMH* are typically small batteries with a higher relative cost. *LiFePo4* are typically very large capacity batteries with a relatively low cost per *Wh*.
* **Life Span:** for *lead-acid*, life span is a *time span* due to the internal chemistry (which degrades over time). *Lithium*-based chemistries are relatively unaffected by time and degrade only during *charge/discharge*-cycles. All battery types degrade prematurely when discharged above the *Depth of Discharge* level due to irreversible chemical and structural changes that occur at these low voltage levels. High *charge currents* further reduce battery life.
* **Operating Temperature:** *Lithium*-based batteries **must not** be charged below *0 Celsius* (but can be discharged down to *-20 Celsius*). *Nickel*-based batteries are among the most rugged chemistries and work well both in extremely *cold* conditions as well as in *full sunshine*.


## Self-Discharge
All batteries are affected by self-discharge, regardless of technology. The *rate* of self-discharge varies greatly, though.

*Primary cells* (non-rechargeable batteries) such as lithium-metal and alkaline retain the stored energy best, and can be kept in storage for many years. 

*Rechargeable batteries* constantly lose charge. The rate is affected by their *state of charge* (highest losses when fully charged, then tapering off) and environment (discharge *doubles* for every 10C temperature rise). High cycle count and aging also increase self-discharge of all systems. 

> [!TIP]
> A fully charged *LiIon* battery may loose *6%* per month at *0 Celsius*, yet *35%* at *60 Celsius* environmental temperature. At just *50%* charge, the discharge is *2%* at *0 Celsius* and *15%* at *60 Celsius*.

*Nickel-based batteries* lose as much as *10–15%* of their capacity in the **first 24 hours after charge**, then *10–15%* per month. These batteries need recharging before use when placed on a shelf for a few weeks. 

## Risks And Permanent Damage

Modern rechargeable batteries are robust and can be used for many thousand cycles. There are just *two mechanisms* that can permanently damage the battery:

### Over-Charge
When a battery is charged with *too high currents*, or *too high voltages*, it *over-charges*: the supplied energy cannot be absorbed and instead turns into *heat*. In addition, chemical processes can produce gases (like oxygen) that build up *pressure* and can lead to *bulking*, *fire*, and even *explosion*. That's why you should only use *trustworthy chargers* that were *designed for the battery chemistry* you use:

* Do not use *LiIon* chargers for *LiFePo4* batteries, or *car (lead acid) chargers* for *LiIon*.    
* Do not use generic *constant current* power supplies (let alone regular DC power sources without regulation)
* Do not charge batteries with currents higher than necessary. Do not use *quick chargers* if you have the time for a *regular charge*. Never charge a battery above *1C* (its capacity in *Ampere*, i.e. never charge a *100Ah* battery with more than *100A*). 

### Over-Discharge
Most battery types can be permanently damaged when *over-discharged*. Below a certain voltage, inside the battery *irreversible chemical reactions* take place. For *lead-acid batteries*, discharging below *50%* can already start *sulfation*. *Lithium*-based batteries experience similarly destructive reactions when they are discharged below *10% capacity*.

## Storage
If you do not use batteries for an extended period of time, *self-discharge* can lead to *over-discharge* and permanent damage. To safely store batteries for extended periods of time, you therefore need to make sure that natural *self-discharge* cannot excessively discharge the battery:

* **Cool Environment:** since *self-discharge* is affected by temperature, store batteries in a cool place (*0-15 Celsius*)
* **Fully Charge:** while you shouldn't *routinely* charge your batteries to *100%*, a battery should be *fully charged* when you put it in storage. This way, natural *self-discharge* will take much longer until critical *over-discharge voltages* are reached.

> Tags: Battery, Charge, BMS, Lead, NiCd, NiCad, LiIon, LiPo, LiFePo4, LFP, CR2025, CR2035, CR123A, Charging Cycle

[Visit Page on Website](https://done.land/components/power/battery?676524101918241704) - created 2024-10-17 - last edited 2024-10-17
