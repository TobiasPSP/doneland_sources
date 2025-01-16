<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Advanced Battery Testers

> Testing Batteries For Quality And Health

You can't see from the outside whether a battery is in good shape, a fake, or what the true battery capacity is. *Battery testers* are small devices that help you examine batteries and determining their health and true capacity.

There are many different types of battery testers, and strategies to test batteries:

* **All-in-One Testers:** Low cost devices that perform all the essential tests to determine battery capacity and health. While they may not be scientifically precise, they are highly effective and often suffiencient to evaluate your batteries. They typically bring their own load, producing a discharge current of around *1A*, and can recharge your batteries as well. They are typically designed to measure individual battery cells and can handle voltages of no more than **5V**.
* **State of Charge (SOC) Meters:** such low cost devices derive the current battery *state of charge* from its voltage. They can tell you whether a battery is fully charged or empty, but they are generally rather unprecise due to the flat voltage curve in modern lithium batteries. In its simplest form, they are simple *LED bars*. Advanced SOC meters can analyze individual battery cells in multi-cell battery packs and might even be able to *balance* these cells in case their voltages differ. They do not evaluate the total battery capacity, though.
* **Current Meters:** Low cost breakout boards or portable devices that measure **and sum up** the current that flows through them. Most devices can also calculate the total energy in watts. They do not provide a load by themselves, so you place them *in series* to (any) load you operate. Such devices are especially useful if you need to measure wider voltage ranges or higher currents. Some devices can handle currents of up to *200A*. 
* **Specialized Internal Resistance Meters:** these devices are costly and measure only one parameter: the batteries' *internal resistance* which can be a good indicator for battery health. While they do not measure the total battery capacity, they employ advanced *AC internal resistance measurements* that are much more precise than the measurements performed by *affordable All-in-One testers*. Specialized internal resistance meters can be very helpful for professionals, or when you use costly batteries in solar energy farms. They are not so helpful for DIY makers that would just want to know if their batteries are genuine and in good health.


## Entry-Level All-In-One Testers
At the entry level, affordable testers costing just a few dollars can perform all the essential tests needed to provide a reliable assessment of your battery.


<img src="images/battery_test_charge_on2_t.png" width="50%" height="50%" />

While often designed for specific battery types, such as *18650* cells, these *all-in-one* testers also feature solder pads that allow you to add connectors or battery holders for other types, as long as their voltage is below **5V**.

Here are the tests you can perform:

* **Total Capacity:** Determine the total battery capacity by conducting a full charge/discharge cycle, with the results displayed in *mAh*.
* **Internal Resistance:** Measure the internal resistance in *mOhm*. Although this method relies on the less accurate and simpler *voltage measurement method* (*DC resistance measurement*), it still provides a useful general assessment of battery health. The margin of error can be between *10%* and *30%*.


## Current and Energy Meters
While *All-in-One testers* come with a load that can discharge the battery, there are also simpler *current or energy logger*: they simply log the current (or energy in watts) that passes through them. This gives you the flexibility to use whatever load you want. Through the load you use, you can also vary the discharge current. Typically, current and energy meters have a much wider voltage range (allowing you to measure large battery packs or solar panels) and can handle much higher currents.

Here is a breakout board that can handle voltages of up to *15V* and currents of up to *3A*:
<img src="images/dedicated_capacity_tester_hw586_overview_t.png" width="50%" height="50%" />

Boards like this are low-cost and available for under *€3.00*.

## Specialized Internal Resistance Testers
If you are willing to spend at least €40.00, specialized *internal resistance testers* are available, such as the *FNIRSI HRM-10* or the *RC3563*. For a significantly higher price, you can find similar devices from renowned brands, although they might be overkill for *DIY purposes*.

<img src="images/rc3562_internal_resistance_packshot_t.png" width="20%" height="20%" />

All of these devices utilize the more accurate *AC Resistance Test* to measure the batteries' *internal resistance*, with a margin of error of less than *0.5%*. Often, they include *data export features* to computers.



<img src="images/fnirsi_hrm_10_internal_resistance_packshot_t.png" width="20%" height="20%" />


The downside is that these devices *exclusively* measure *internal resistance*. To assess the battery *capacity*, you will need additional testers that can log the charge or discharge energy over time.




> Tags: Battery, Test, Capacity, Internal Resistance, FNIRSI HRM-10, RC3562, HW-586

[Visit Page on Website](https://done.land/components/power/battery/batterytesters?089440101519243644) - created 2024-10-18 - last edited 2024-10-18
