<img src="/assets/images/battery.png" width="100%" height="100%" />


# Battery Management Systems (BMS)

> They Protect Lithium Batteries From Dangerous Risks And Keep Your Batteries Healthy.

*Lithium*-based rechargable batteries store *enormous amounts of energy*. They need electronic protection for safe operation:

* **Fire Hazard**: the stored energy can *erupt in flames* or *explode* when the battery is physically damaged or short circuited - or when it is *charged* below or above safe voltage thresholds where the battery cannot store the excess energy anymore.
* **Permanent Battery Damage**: permanent damage (loss of battery capacity or complete destruction) may occur when the battery is *fully* discharged. Discharge *must stop* at a certain minimum voltage. Else, the battery chemistry can suffer irreversible structural damage. 

> [!TIP]
> A **BMS** is important both for *charging* and *discharging* a battery. 

## Typical Risks Ruining Your Day

A **BMS** (*Battery Management System*) is an electronic circuit that protect from many risks. Without a **BMS**, you may easily run into serious problems while using *lithium* batteries:

* You charge the battery and leave the charger connected. Without a **BMS** (or a clever charger), your *lithium* battery will eventually catch fire.
* You connect a device to your battery and leave it *on*, then walk away. Once the battery is completely drained, it also is permanently damaged.
* You accidentally connect both poles of the battery and produce a short circuit. Enormous currents will flow and can hurt you, or the battery explodes.

That's why most quality *lithium* batteries come with a basic **BMS** already integrated into them.

## Important Protection Features

A sufficient *BMS* must provide these key protection features:

* Over-Current Protection
* Over-Charge Protection
* Over-Discharge Protection
* Load Balancing

<details><summary>What is *over-current protection*?</summary><br/>

*Over-current protection* cuts off the battery once the *current* exceeds a certain threshold. Typically, *over-current protection* kicks in when the current roughly exceeds *double* of the continuous (normal) maximum current.

When this happens, i.e. due to a short circuit, the **BMS** enters *lockdown mode*. To *reset* it, connect it to a charger.

*Over-current protection* protects **fire hazards**: every battery can provide a maximum discharge current. If more current is drawn, the battery releases so much energy in such a short time that resulting heat can set the battery on fire. 

In addition, this also protects your *load*. Should it encounter a failure or cause a short circuit, power will be quickly removed.

Most **BMS** have a latency of 100-200ms before *over-current protection* cuts off power.
</details>

<details><summary>What is *over-charge protection*?</summary><br/>

This kind of protection becomes important when you *charge* your battery through the **BMS**.

During *charging*, the *voltage* raises steadily until the battery is fully charged. The **BMS** monitors the *voltage*. If the voltage exceeds a threshold that indicates that the battery is *fully charged* and cannot accept any more energy, the **BMS** cuts off the battery.

*Over-charge protection* prevents **fire hazards** from *over-charging*. If you keep charging an already fully charged battery, the additional energy coming from your charger can no longer be stored by the battery and is now converted to heat. Without *over-charge protection*, your battery would gradually heat up until it eventually causes a fire or explodes.

</details>

<details><summary>What is *over-discharge protection*?</summary><br/>

When you draw energy from your battery, its voltage slowly falls. When the battery is almost empty, and you continue to draw energy, its internal cell chemistry will suffer irreversible damage, and your battery will permamently lose capacity or stop working at all.

The **BMS** monitors the battery voltage. When it falls below a threshold, indicating that the battery is almost empty, the **BMS** cuts off the load from the battery.

If the battery voltage has already fallen below this threshold, and you start *charging* the battery, *over-discharge protection* unfolds a second protection mechanism: it limits the *current* that the charger can deliver to the *over-discharged* battery until it reaches safe voltage levels.

This prevents yet another **fire hazard**: a lithium battery that is *completely* empty cannot store energy in the same way a *healthy* battery can. If you would charge it at normal current, most of the charging energy could not be stored and would start to heat up the battery. Eventually, the battery could catch fire or explode.

By limiting the current until the battery reaches a safe voltage level (and thus normal storage behavior), even completely drained batteries can be safely charged.
</details>

<details><summary>What is *balancing*?</summary><br/>

When you connect more than one battery *in series*, the overall voltage is higher than the voltage of the individual batteries.

If you charged all batteries together, you would no longer be able to monitor *individual* battery voltages. Since batteries are not 100% identical, chances are one battery would be fully charged while another battery would still need energy.

*Balancing* protects from unevenly charging batteries by monitoring the voltages of all connected batteries individually, and adding extra charge to individual batteries if they lag behind other cells. 

When a **BMS** includes *balancing*, each battery is connected *individually* to the **BMS**. Typically, at the begin and at the end of your battery string, there is a *large* solder pad. This is where the bulk of charging current is fed.

Then there are *smaller* solder pads for connecting *each junction* of two batteries. These connections feed the (much lower) *balancing current* to *individually* boost the charge of a particular cell that lags behind.

Balancing is a protection for *charging* and not used during *discharging*.

</details>

> [!TIP]
> When you review specs for **BMS** and their voltage threshold for *over-discharge protection*, you may be surprised to see the threshold voltage often about *0.5V below* the typically recommended thresholds. Keep in mind that *over-discharge protection* monitors the battery *under load*. When you draw energy from a lithium battery, its voltage drops by as much as *0.5V*. In order to not accidentally cut off power prematurely, *over-discharge protection* voltage thresholds take this into account.

### Battery Voltage Thresholds

The threshold voltages a *BMS* needs to monitor *vary based on cell chemistry* and manufacturer. That's why you need a **BMS** made specifically *for your battery type*.

| Chemistry | Min V (Empty) | Max V (Full) | Nominal (During Operation) | 
| --- | --- | --- | --- | 
| LiIon | 2.7V | 4.2V | 3.7V | 
| LiPo | 3V | 4.2V | 3.7V | 
| LiFePo4 | 2.5V | 3.65V | 3.2 | 

<sup>*(typical values, consult your battery data sheet)*</sup>

As you see, *LiIon* and *LiPo* batteries display roughly the same behavior and voltages. You can use the same **BMS** for both battery types.

*LiFePo4* batteries display significantly different voltages and thus need different **BMS** that honor their voltage thresholds.

## Using a *Balanced* BMS

When you connect multiple batteries *in series* (to get a higher output voltage) and plan to *charge* your batteries through the **BMS**, you should *always* select a **BMS** with *balancer* capabilities. 

> [!NOTE]
> A *balancer* is used exclusively for *charging* and is *not used* for discharging.

With balanced **BMS**, each battery string is connected separately to the **BMS**. 

The balancer makes sure each cell voltage is monitored individually. Without balancing, one battery could already be fully charged when another is not, resulting either in only *partially* loaded batteries, or risk of *over-charging* a battery.

## BMS Is Not a Charger

One of the most common misperceptions is that **BMS** can also be used to *charge* your battery. 

This is only partially true and in fact can damage your batteries. A **BMS** can *assist* a dedicated charger through its *balancing* capabilities but you should avoid charging batteries directly through your **BMS**.

While you can connect a power supply to the *output terminals* of a **BMS** and feed energy back into the battery, the **BMS** only limits the *input current*. 

Typically, this *current limit* is much higher than it should be for charging your batteries. Chances are you will be *over-charging* your batteries with currents that are much too high.

**BMS** also typically do not employ sophisticated **CC*-*CV*-charging cycles that should be used with lithium batteries to ensure a *full load*.

To *charge* a battery with a **BMS** alone, you would need to supply the proper *charging voltage* for your batteries:

| Strings (batteries connected *in series* ) | LiIon/LiPo | LiFePo4 |
| --- | --- | --- |
| 1S (one battery) | 4.2V | 3.65V |
| 2S (two batteries) | 8.4V | 7.3V |
| 3S (three batteries) | 12.6V | 10.95V |
| 4S (four batteries) | 16.8V | 14.6V |

> [!TIP]
> When building *battery packs*, always add a proper **BMS** *and* a separate *charger* board that takes the desired charging input voltage (i.e. USB 5V) and supplies it to the **BMS** output terminals for even distribution to the batteries.

## BMS Needed Or Already Built-In?

Quality batteries come with a simple **BMS** built-in for *basic protection*. You can't typically see the **BMS**. It is located inside the battery.

> [!CAUTION]
> Since you can't *see* the **BMS**, make sure your battery has one. Cheap batteries from untrusted sources *may come without **BMS*** and can easily explode when there is a short circuit or when you charge them for too long. 

### Adding a BMS 

Adding your own **BMS** for DIY projects is *always* a good idea since you probably do not know the specs of the built-in **BMS** and whether it covers *all* important risks.

Once you start building your own battery constructs, i.e. by combining multiple batteries, you *should always* add your own **BMS**. 


## Choosing a Ready-To-Use BMS

You could be intrigued to build your own **BMS** circuit. Don't do it.

There are plenty of ready-to-go **BMS** breakout boards available that are much cheaper than even the total component cost if built your own.

There are *4 questions* to be answered to select the appropriate **BMS**:

1. **Battery Chemistry:** you either need a **BMS** designed for *LiIon/LiPo*, or for *LiFePo4*. 
2. **Strings:** How many batteries do you want to connect *in series*? In other words: what is the intended *total output voltage* of your battery pack?
3. **Current:** What is the maximum current you want to draw? In other words: at which current should the **BMS** disconnect the batteries to protect them (and also *protect your load* should it cause a short circuit or suffer another failure)?
4. **Balancer:** Do you need *balancing capabilities*? In other words: do you use more than one battery and want to charge it through the **BMS**? 

> [!CAUTION]
> Never use a **BMS** designed for *LiPo/LiIon* and connect *LiFePo4* batteries to it (or vice versa). The safe voltage range for *LiIon/LiPo* is *2.8-4.2V* whereas the safe voltage range for *LiFePo4* is *2.5-3.65V*. Your **BMS** must enforce the safe voltage levels appropriate for the battery type you use.

### Understanding *Strings*: 1S, 2S, 3S, 4S...

To select the appropriate **BMS**, you need to know *how many battery strings* you have. 

**BMS** types use **S** as short for *strings*: a **2S BMS** can be used with *two* batteries *connected in series*. So for the *string count*, only the number of batteries *connected in series* count.

> [!IMPORTANT]
> If you connect batteries *in parallel*, they count as *one string*.

The reason *why* a **BMS** cares only about batteries connected *in series* is because this *increases the voltage*, so it directly affects the *voltage thresholds* the **BMS** is supposed to monitor. Batteries connected *in parallel* do not change the resulting *voltage*.

Here are some "string counting" examples: 

* If you connect *two batteries in parallel*, this would be a **1S** system. If you connect the same two batteries *in series*, you would have a **2S** system.
* Should you use a total of *six* batteries, *two* of each connected *in parallel*, and then the three pairs *connected in series*, you would have a **3S** system.

### Maximum Current (Power)

A **BMS** limits the maximum current. That is one of its fundamental protection features (*over-current protection*).

Selecting the appropriate **BMS** requires that you know the *maximum current* you want to draw from your batteries.

> [!TIP]
> One of the risks a **BMS** protects is *over-current*. By adding the appropriate **BMS** to your battery, you essentially also get a *fuse*: should your load require *more power* than anticipated, the **BMS** cuts off power.
> Since **BMS** are not designed to routinely handle *over-current* and *short circuits*, still *do use* a fuse. If the **BMS** encounters an *over-current*, it may permanently shut-down the connection until you re-connect it with a charger.

#### Absolute Maximum Current

The *maximum current* you want to draw *cannot be higher* than the *absolute maximum technically safe current*. 

The *absolute maximum technically safe current* is determined by the batteries you use. As a rule of thumb, *lithium batteries* sustain a maximum discharge rate of *3C* where **C** stands for the *battery capacity*. 

> If your battery has a *capacity* of *3.000mAh*, then this is **1C**. The maximum safe discharge current would then be *9A* (3x3.000mA).
>
> With 10.000mAh batteries, the maximum safe discharge current would be *30A*.

That's just a rule of thumb. Be careful, and always look up the datasheet of the actual batteries *you use*. There are huge variations.

* Cheap *LiPo* batteries may allow a maximum discharge current of as low as *0.3C*.

* *Big LiFePo4* batteries can deliver *10-30C* and more.


<details><summary>How batteries connected *in parallel* increase current</summary><br/>

What has been discussed so far applies to *one* battery. When you connect batteries *in parallel*, the voltage stays the same but the *maximum possible current* raises as all batteries now *share* the load.

* If you connect *two* batteries *in parallel*, this *doubles* the maximum safe current. 
* Connecting *ten* batteries *in parallel* raises the maximum allowable current *tenfold*.

> [!TIP]
> If your battery does not sustain the maximum current you need, connecting more batteries *in parallel* is your option to *raise the current* to the level you need.

</details>

#### True Maximum Current

The *technically possible* maximum current often is much higher than the *real needs* of the load you want to power.

Just make up your mind: what is the *maximum current* your load will possibly draw under the most demanding conditions? 

Add a reasonable safety margin, and you now know the maximum current your **BMS** should allow.


### Balancing Capabilities

*Balancing* (explained earlier) is *not required* with just *one* battery, or when you do not plan to ever *charge* the batteries through your **BMS**.

In all other cases, the **BMS** should have *balancing capabilities*. The extra cost is marginal.

> To find the appropriate **BMS** breakout board for your project, first select the number of *strings*, then visit the appropriate section below to select the **BMS** supporting the *maximum current* you need.

## 1S BMS

Most quality batteries come with a **BMS** built-in, but if you want to make sure you can add a **1S BMS**. 

This is a *must* if you decide to connect multiple batteries *in parallel* because now the total current raises considerably, introducing new risks that your **1S BMS** should mitigate.

[Here](1s) is a list of popular ready-to-use **1S BMS*.

## 2S BMS



[Here](2s) is a list of popular ready-to-use **2S BMS*.

## 3S BMS



[Here](3s) is a list of popular ready-to-use **3S BMS*.

## 4S BMS



[Here](4s) is a list of popular ready-to-use **4S BMS*.


> Tags: BMS, Battery, Balancer, Charging, Protection, 1S, 2S, 3S, 4S, Strings

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/bms?260305020426240854) - last edited 2024-02-27
