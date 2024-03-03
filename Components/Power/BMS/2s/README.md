<img src="/assets/images/battery.png" width="100%" height="100%" />


# 2S - Using 2 Batteries in Series

> 2S BMS Protect Two (Groups of) Batteries From Mishap. Combined With Balancing They Are A Perfect Fit For Your Batteries.

A **2S BMS** is needed to protect *two* batteries (or groups of batteries connected *in parallel*) that are connected *in series*. 

Each lithium battery has a voltage between *3.2V*-*4.2V*, depending on state of charge. When you connect two of them *in series*, the **BMS** needs to handle a voltage in the range of *6.4V*-*8.4V*.

## Selecting Maximum Current

A **BMS** limits the maximum current. Selecting the appropriate **BMS** requires that you know the *maximum current* you want it to allow.

> [!TIP]
> One of the risks a **BMS** protects is *over-current*. By adding the appropriate **BMS** to your battery, you essentially also get a *fuse*: should your load require *more power* than anticipated, the **BMS** shuts down the connection.
> Since **BMS** are not designed to routinely handle *over-current* and *short circuits*, still *do use* a fuse. If the **BMS** encounters an *over-current*, it may permanently shut-down the connection until you re-connect it with a charger.

### Maximum Current

The *maximum current* you want to allow *cannot be higher* than the *maximum technically safe current*. 

Let's first quantify the absolute maximum current safely possible for your battery pack:

The *maximum technically safe current* is determined by the batteries you use. As a rule of thumb, *lithium batteries* sustain a maximum discharge rate of *3C* where **C** stands for the *battery capacity*. 

> If your battery has a *capacity* of *3.000mAh*, then this is **1C**. The maximum safe discharge current would then be *9A* (3x3.000mA).
>
> With 10.000mAh batteries, the maximum safe discharge current would be *30A*.

That's just a rule of thumb though. Be careful, and always look up the datasheet of the actual batteries *you use*. There are huge variations.

* Cheap *LiPo* batteries may allow a maximum discharge current of as low as *0.3C*.

* *Big LiFePo4* batteries can deliver *10-30C* and more.


<details><summary>How batteries connected *in parallel* increase current</summary><br/>

What has been discussed so far applies to *one* battery. When you connect batteries *in parallel*, the voltage stays the same but the *maximum possible current* raises as all batteries now *share* the load.

* If you connect *two* batteries *in parallel*, this *doubles* the maximum safe current. 
* Connecting *ten* batteries *in parallel* raises the maximum allowable current *tenfold*.

> [!TIP]
> If your battery does not sustain the maximum current you need, connecting more batteries *in parallel* is your option to *raise the current* to the level you need.

</details>

### Real Maximum Current

The *technically possible* maximum current often is much higher than the *real needs* of the load you want to power.

What is the *maximum current* your load will need under the most demanding conditions? 

Add a reasonable safety margin, and you now know the maximum current your **BMS** should allow.

## 3A

For currents up to **3A**, you can use a very small **BMS**:

<img src="images/bms_2s_3a_top_angle_t.png" width="100%" height="100%" />

The connectors are located on the back:

<img src="images/bms_2s_3a_bottom_t.png" width="100%" height="100%" />

This is a *balanced* board. Connect one battery to **B-** (-) and **BM** (+), and connect the other battery to **BM** (-) and **B+** (+). 

The output voltage is available at **P+** and **p-**.

## 8A

For currents up to **8A**, a board with more powerful *MosFET* like this one is necessary:

<img src="images/bms_2s_8A_top_angle_t.png" width="100%" height="100%" />

The terminals are accessible both from top and bottom.


<img src="images/bms_2s_8a_bottom_t.png" width="100%" height="100%" />

This is a *balanced* board. Connect one battery to **B-** (-) and **BM** (+), and connect the other battery to **BM** (-) and **B+** (+). 

The output voltage is available at **P+** and **p-**.

## 10A

For currents up to **10A**, a very *compact* board is available:

<img src="images/2s_10a_top_angle_t.png" width="100%" height="100%" />

Unfortunately, the compactness of the board did not leave room for markings on the front side. Instead, the markings for the soldering pads were printed on the *back side*:


<img src="images/2s_10a_bottom_t.png" width="100%" height="100%" />

On the other end, the board has a big soldering pad marked as **B-** which is accessible from both sides, and two smaller ones marked **B1** and **B+** on the backside whereas the solder pads are accessible on the front.

This is a *balanced* board. Connect one battery to **B-** (-) and **B1** (+), and connect the other battery to **B1** (-) and **B+** (+).

The output voltage is available at **B+** and **C-**. These two pads are accessible from both sides.


## 20A


For currents up to **20A**, you need a bigger board with more *MosFETs* that share the load, like this one:

<img src="images/bms_2s_20a_top_angle_t.png" width="100%" height="100%" />

All terminals are accessible both from top and bottom.


<img src="images/bms_2s_20a_bottom_t.png" width="100%" height="100%" />

This is a *balanced* board. Connect one battery to **0V** (-) and **4.2V** (+), and connect the other battery to **4.2V** (-) and **8.4V** (+). 

The output voltage is available at **+** and **-** located in the inside of the board.












Here are commonly available **2S BMS**:

> Tags: Battery, BMS, 2S

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/bms/2s?268282020426240854) - last edited 2024-02-27
