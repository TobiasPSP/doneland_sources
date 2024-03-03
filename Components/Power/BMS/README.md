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

*BMS* must provide *at minimum* these key protection features:

| Feature | Typical Threshold | Description |
| --- | --- | --- |
| Over voltage | >4.3V | Prevents **fire hazard** from *over-charging*. When batteries are charged, voltage slowly rises. At a threshold voltage, it is fully charged and cannot store additional energy. If you keep charging *beyond* this point, any additional energy is converted to heat and may eventually cause a fire or explosion |
| Over discharge | <2.3-3V | Prevents **permanent battery damage**. When you draw energy from a battery below a threshold voltage, its internal chemistry starts to change irreversibly, and the battery permanently loses capacity or does not work anymore at all. This feature also prevents **fire hazard**: *Charging* a battery below this threshold requires extra care as the battery cannot store much energy. When charged with normal currents, most of the energy is converted to heat and can cause fire or explosion. When the battery is below this threshold, the *BMS* must disable charging or charge with a *reduced* current until the minimum voltage threshold is reached. |
| Short circuit | varies | Protects **fire hazard** from *over-current*. Every battery can provide a maximum discharge current. If more current is drawn, or in the worst case if the battery output is short circuited, the battery releases so much energy in such a short time that resulting heat can set the battery on fire. A *BMS* sets a maximum current and - similar to a fuse - cuts off the load when the current is exceeded. Often resettable by initiating a charge. |
| Balancing | n/a | Protects from unevenly charging batteries (when the *BMS* controls more than one battery) by monitoring the voltages of all connected batteries individually, and adding extra charge to individual batteries if they lag behind other cells. Balancing improves overall battery lifetime and protects from **over- or under-charging** scenarios. Balancing is a protection for *charging*. During *discharge*, balancing is typically not required or useful.

### Battery Voltage Thresholds

The threshold voltages a *BMS* needs to monitor *vary based on cell chemistry* and manufacturer. Always consult the data sheet of the battery you are actually using.

There are rules of thumb:

| Chemistry | Min V | Max V | Nominal | 
| --- | --- | --- | --- | 
| LiIon | 2.7V | 4.2V | 3.7V | 
| LiPo | 3V | 4.2V | 3.7V | 
| LiFePo4 | 2.5V | 3.65V | 3.2 | 

These are the important thresholds to monitor:

* **Minimum Voltage**: If you continue to *discharge* the battery below *minimum voltage*, it can get permanently damaged. If you *charge* a battery that has a below-minimum voltage, much of the energy may be converted to heat, potentially leading to fire and explosion.
* **Maximum Voltage**: When *charging* a battery, the voltage increases up to the *maximum voltage* when it is fully loaded. When you continue to charge a battery beyond its *maximum voltage*, the energy can no longer be stored and is converted to heat, potentially leading to fire and explosion.
* **Nominal Voltage**: When in operation, the battery *on average* delivers the *nominal voltage*. Lithium batteries generally have a very flat voltage discharge curve, so between *minimum* and *maximum* voltage, the battery will deliver the *nominal voltage* for a very long period of time.

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

| Strings (batteries connected *in series* ) | Charging Voltage |
| --- | --- |
| 1S (one battery) | 4.2V |
| 2S (two batteries) | 8.4V |
| 3S (three batteries) | 12.6V |
| 4S (four batteries) | 16.8V |

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

Let's examine the basic parameters you need in order to select the appropriate **BMS**:

* **Strings:** How many batteries do you want to connect *in series*? In other words: what is the intended *total output voltage* of your battery pack?
* **Current:** What is the maximum current you want to draw? In other words: at which current should the **BMS** disconnect the batteries to protect them?
* **Balancer:** Do you need *balancing capabilities*? In other words: do you use more than one battery and want to charge it through the **BMS**? 

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
> One of the risks a **BMS** protects is *over-current*. By adding the appropriate **BMS** to your battery, you essentially also get a *fuse*: should your load require *more power* than anticipated, the **BMS** shuts down the connection.
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

Connecting two batteries in series raises the voltage in the range of *6.4-8.2V* (depending on state of battery charge) which is good for powering many microcontroller boards. You should add a **Buck** regulator that takes the battery voltage and reduces it to *exactly the voltage you need*.

[Here](2s) is a list of popular ready-to-use **2S BMS*.

## 3S BMS

Three batteries *in series* result in a voltage in the range of *9.6-12.6V*.

[Here](3s) is a list of popular ready-to-use **3S BMS*.

## 4S BMS

Four batteries *in series* gets you a voltage in the range of *12.8-16.8V*. This configuration is used when you need *12V output*. Just add a **Buck** regulator to reduce the voltage range to the specific output voltage you need, i.e. *12V*.

[Here](4s) is a list of popular ready-to-use **4S BMS*.


> Tags: BMS, Battery, Balancer, Charging, Protection, 1S, 2S, 3S, 4S, Strings

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/bms?260305020426240854) - last edited 2024-02-27
