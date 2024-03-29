<img src="/assets/images/butler.jpg" width="80%" height="80%" />
 
# Devices

> Useful Devices For Your Electronics Lab


In this section you'll find the devices I find indispensible for an electronics lab.


## Electronic Load

An *electronic load* is a test instrument to simulate electric loads. Loads can be *resistive*, *inductive*, or *capacitive*, and real loads often are a mixture of these and can behave differently under different conditions.

Typically, *electronic loads* therefore support *four different* test modes to test specific aspects of a device.

### Constant Current (CC)
This is a *power consumption* test and is the most frequently used mode in electronic loads. Use it to test the stability of power supplies under load. 

It can also be used to *discharge a battery* in a controlled way, either to safely dispose it, or to measure its capacity. In *CC* mode, the battery is discharged at a constant current regardless of the voltage which is typically dropping over time.

Technically, the electronic load uses *power transistors* that act as *variable resistors* to ensure that regardless of voltage, a *constant current* flows.

### Constant Voltage (CV)
The load adjusts its resistance to keep the voltage *constant*: when you *lower* the *constant voltage setting*, a *higher current is drawn*. Use it to test *current limiting capabilities* of power supplies, or to test *battery chargers* to find out the battery's terminal voltage.


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


> Tags: Electronic Load, Constant Current, Constant Voltage, Constant Power, Constant Resistance, CC, CV, CP, CW, CR
