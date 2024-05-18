<img src="/assets/images/electronicload2.png" width="80%" height="80%" />
 
# Electronic Load

> Simulating Electric Loads Help You Understand How Power Supplies And Batteries Behave Under Load 



An *electronic load* is a test instrument to simulate electric loads. Loads can be *resistive*, *inductive*, or *capacitive*, and real loads often are a mixture of these and can behave differently under different conditions.

Put simple, with an *electronic load* you can simulate the power consumption of electric and electronic devices. This enables you to test power sources, i.e. batteries and power supplies. 

Common test scenarios include measuring the true battery capacity, and testing *power supplies* and their stability under varying loads.

*Electronic loads* support *four different* test modes to test specific aspects of a device.


### Constant Current (CC)
This is a *power consumption* test and is the most frequently used mode in electronic loads. Use it to test the stability of power supplies under load. 

It can also be used to *discharge a battery* in a controlled way, either to safely dispose it, or to measure its capacity. In *CC* mode, the battery is discharged at a constant current regardless of the voltage which is typically dropping over time.

Technically, the electronic load uses *power transistors* that act as *variable resistors* to ensure that regardless of voltage, a *constant current* flows.

> [!NOTE]
> *Constant Current* and *Constant Resistance* both measure fundamentally the same properties: they simulate a *power consuming* load. *Constant Resistance* (see below) is simulating true device behavior (the *current* falls when the *voltage* falls), whereas *Constant Current* focuses more on dynamic loads (like adaptive power regulators) or to easily calculate battery capacity by keeping the *current* **constant**: when the *voltage* falls (i.e. battery is discharging), in *CC* mode the *electronic load* decreases its resistance to keep the *current* constant.


### Constant Resistance (CR)
This is a *resistor simulation* test (the electronic load acts like a typical electrical consumer). This is useful for testing *power supplies* under load and to find out their operating range and how they behave when they reach their load limits. You can also use this mode to test battery capacity.

Provided you are testing *resistive components* (and not *inductive* components), *Ohms Law* applies. When the electronic load is i.e. set to *5 Ohms*, in a circuitry powered by *3.3V*, this causes a current of *0.66A* to flow (*I = U/R*, thus *3.3V/5Ohm* = *0.66A*). Powered with *5V*, the same test setup causes a current of *5V/5Ohm = 1A*.

> [!NOTE]
> In *Constant Resistance* mode, the absorbed *power* is directly related to the *voltage*. When the *voltage* changes, so does the absorbed power. To measure *power* independently from *voltage*, see *Constant Power* below.

*Constant Resistance* can for example be used to discharge a battery and create a specific *battery profile*.

### Constant Power (CP/CW)
In this mode, the electronic load absorbs a defined constant power, *regardless of voltage*. It senses the voltage, calculates the appropriate *current*, and then draws this *current* to consume the set *power*.

This mode can be used to *discharge a battery* with constant power, i.e. to simulate the behavior of a DC-DC-converter. It can also be used to test *DC-DC converters* and *power supplies* to ensure they are able to supply a given power at a set voltage.

Note the fundamental difference compared to *constant resistance*: when a *constant resistance* is applied to a battery, it will draw a certain *current* that depends on the *voltage*. Over time, when the battery gets discharged, its voltage will fall. In *constant resistance* mode, according to *Ohms Law*, the *current* will also fall.

Not so in *constant power* mode: when the *voltage* of the power source falls, the electronic load will automatically increase the *current* to keep the *power* constant. With falling *voltage*, the *current* will rise.


### Constant Voltage (CV)

In this mode, the *electronic load* tries to eliminate enough energy from the load in order to let the voltage drop to a given voltage. Since an *electronic load* can extract only a certain amount of energy (i.e. *400W*), this mode has limitations.

* When the supplied voltage is *lower* than the *CV* set at the *electronic load*, nothing happens.
* When the supplied voltage is *higher* than the *CV* that you set at the *electronic load*, it will try and *eliminate* enough energy to *drop the voltage* to the desired level: it will start to sink *current*. If the voltage source can *provide more energy* than the *electronic load can absorb*, then the voltage *will not drop fully* to the set *constant voltage*: the voltage will be higher than the set *CV* because the *electronic load* could not eliminate enough energy.

#### Analyzing Battery Capacity

To better understand *CV* and its limitations, here is an example: the capacity of a rechargeable battery needs to be examined.

To achieve this, you could set *CV* to the safe discharge voltage of the battery (i.e. *12V* for a *13.8V LiFePo4* battery). The electronic load would now try and eliminate energy from the battery until its voltage drops below *12V*, preventing over-discharge.

#### CV Battery Testing Can Be Dangerous

*CV* does not provide any control over the discharge *currents*. These currents solely depend on the maximum sink capacity of the *electronic load*. Small batteries can be destroyed and can explode under test. Here is why:

With a typical *400W electronic load*, when connecting a battery in *CV* mode and setting *CV* to the desired "fully-discharged" voltage, the electronic load would try to eliminate as much energy from the battery as needed to *immediately drop the voltage* to the set *CV*.

The maximum energy the *electronic load* can extract is limited, though, so with large capacity batteries, the *electronic load* would extract its maximum energy instead (i.e. *400W*), and the voltage would only gradually fall to the desired *CV* as the battery discharges.

For smaller batteries, the maximum discharge power of *400W* can easily exceed its specifications by multitudes. If you i.e. test a *3.3V 1000mA LiPo* cell via *CV* with a *400W electronic load*, the discharge current would be *121.2A*: *400W / 3.3V = 121.2A*: the resulting discharge rate of **121C** (*121.2A / 1Ah = 121.2C*) would most likely lead to fire and explosion.

That's why *CV* can *only be used for battery testing* when the battery is using a relatively high voltage (i.e. 12, 24, or 48V), and/or when its total capacity is *high*. 

A *48V 400Ah solar panel battery pack* can easily be analyzed using *CV*: *400W / 48V = 8.3A*, discharge rate = *8.3A/400Ah = 0.02C*.

> [!TIP]
> A safe way of battery testing is using *CC* (*Constant Current*) mode: now you *can individually set* a safe current tailored to a specific particular battery under test. Just make sure the *electronic load* turns off once the *CC* can no longer be delivered in order to not over-discharge batteries. 


### Battery Test

Many *electronic loads* offer specific *battery test modes* to test battery capacity. 

These modes base on the *Constant Current* (*CC*) mode and add these features:

* **Two Or More Discharge Currents:** once the set *constant current* can no longer be delivered by the battery under test, the *electronic load* can optionally continue discharging the battery until a lower second current threshold is reached.
* **Calculating Capacity:** in battery test mode, the *electronic load* automatically calculates the total battery capacity by summing up the energy extracted by the load.

> Tags: Electronic Load, Constant Current, Constant Voltage, Constant Power, Constant Resistance, CC, CV, CP, CW, CR

[Visit Page on Website](https://done.land/tools/devices/electronicload?899938030130242601) - created 2024-03-30 - last edited 2024-03-30
