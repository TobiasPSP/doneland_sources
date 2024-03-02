<img src="/assets/images/battery.png" width="100%" height="100%" />


# 2S - Using 2 Batteries in Series

> 2S BMS Protect Two (Groups of) Batteries And Should Have Balancing Capabilities To Fully Charge Both Batteries.

A **2S BMS** is right when you want to protect *two* batteries (or groups of batteries connected *in parallel*) that are connected *in series*. 

Each lithium battery typically has a voltage between *3.2V* and *4.2V*, depending on state of charge. When you connect two of them *in series*, the **BMS** needs to handle a voltage in the range of *6.4V* and *8.4V*.

## Selecting a Safe Current

Once you know you need a **2S BMS**, the second decision to select the appropriate **BMS** is the *maximum current* you want it to allow.

> [!TIP]
> One of the risks a **BMS** protects is *over-current*. By adding the appropriate **BMS** to your battery, you essentially also get a *fuse*: should your load require *more power* than anticipated, the **BMS** shuts down the connection.
> Since **BMS** are not designed to routinely handle *over-current* and *short circuits*, still *do use* a fuse. If the **BMS** encounters an *over-current*, it may permanently shut-down the connection until you re-connect it with a charger.

### Maximum Technically Safe Current

The *maximum current* you want to allow *cannot be higher* than the *maximum technically safe current*. So let's first quantify the absolute maximum current safely possible for your battery pack:

The *maximum technically safe current* is determined by the batteries you use. As a raw rule of thumb, *lithium batteries* have a maximum discharge rate of *3C* where **C** stands for the *battery capacity*. 

> If your battery has a *capacity* of *3.000mAh*, then this is **1C**. The maximum safe discharge current would then be *9A* (3x3.000mA).
>
> With 10.000mAh batteries, the maximum safe discharge current would be *30A*.

That's just a rule of thumb though. So be careful, and always look up the datasheet of the actual batteries *you use*.

* Many cheap *LiPo* batteries allow a maximum discharge current of just *0.3C*.

* *Big LiFePo4* batteries can deliver *10-30C*. 

### Connecting Batteries in Parallel

What we discussed applies to *one* battery. If you connect batteries *in parallel*, while this does not raise  *voltage*, it *increases the maximum possible current*.

* If you connect *two* batteries *in parallel*, this *doubles* the maximum safe current. 
* Connecting *ten* batteries *in parallel* raises the maximum allowable current *tenfold*.

> [!TIP]
> If your battery does not sustain the maximum current you need, connecting more batteries *in parallel* is your option to *raise the current* to the level you need.

### Maximum Current That Makes Sense

Once you know the *technically safe maximum current*, you can start thinking about the **real** *maximum current*: what is the *maximum current* your load will need under the most demanding conditions? 

Add a reasonable safety margin, and now you know the maximum current your **BMS** should allow.

## Selection of 2S BMS

Here are commonly available **2S BMS**:

> Tags: Battery, BMS, 2S

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/bms/2s?268282020426240854) - last edited 2024-02-27
