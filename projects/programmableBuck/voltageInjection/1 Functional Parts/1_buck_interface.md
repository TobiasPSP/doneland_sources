# Step 1: Interfacing With Buck Converter
:stopwatch: Reading time: 5 minutes.

## Soldering Wires To Buck Converter

The digital control we are building is a completely separate *external component* and does not require any structural changes in the stock **Buck** converter. All we need is a way to interface with it:

<img src="../images/buck_interface_w.png" width="60%" height="60%" />

The image shows the backside of the **Buck** converter. The big **R050** *shunt resistor* is easily identifyable. 

### Identifying Required Connection Points

According to the schematics, we need a total of *six* wires to connect to the **Buck** controller:

|  Pin |  Description | Color Wire |
| --- | --- | --- |
| GND IN | Measure current | 	:white_square_button: Black |
| GND OUT | Measure current | :black_square_button: White |
| V+ OUT | Measure voltage | :red_square: Red |
| POT1 | Voltage control | :yellow_square: Yellow |
| POT2.1 | Current control | :orange_square: Orange |
| POT2.2 | 0V reference | :green_square: Green |

* **Measuring Current**: The **Buck** controller connects **GND IN** with **GND OUT** across a *R050* shunt resistor used internally to meassure the current. Since we also need to know the current, we too measure the voltage drop. For this, all we need is access to the terminals **GND IN** and **GND OUT**.
* **Measuring Voltage**: To measure the output voltage, we also need access to the terminal **V+ OUT**. Voltage can then directly measured either against **GND IN** or **GND OUT** (the voltage drop at the shunt resistor is neglectible and can also be adjusted by software later)
* **Controlling Constant Voltage**: To digitally control constant voltage, we need a connection to the voltage sensor pin of the **XL4015** which can conveniently be accessed at one of the *CV* *portentiometer* pins.
* **Controlling Constant Current**: Same goes for current settings: our injected voltage goes into the *middle* leg of the **CC** *potentiometer* pin.
* **0V Reference**: We also need a **0V** reference (more later) which is accessible at the **CC** *potentiometer*.

### Attaching Interface

Here is a close-up of the solder points:

<img src="../images/buck_interface_solderpoints_w.png" width="60%" height="60%" />

I opzted for adding a pluggable connector to the backside with all required contacts so later the **Buck** converter can easily be separated from the *digital control unit*.

> [!TIP]
> Of course, our digital control needs its own power supply as well. Since I don't want to power it externally, we will be using a separate mini buck converter that takes a high *DC* voltage and outputs the stable *3.3V* needed for an *ESP8266*.
>
> Even though it seems tempting to choose the *output* voltage as it is lower than the *input* voltage and thus would be closer to what we need, resulting in higher efficiency, the solution is more robust when powering the digital control via the *input* power.
>
> Else, if we ever choose to **turn off** the **Buck** controller programmatically, i.e. to enter some energy savings mode, we'd cut off ourselves from power. If we wanted to power our digital control via the interface we are designing here, thus we would need a seventh wire to expose **V+ IN**.

### Next Step

Now that the interface to the **Buck** controller is in place, we need a way for the microcontroller to attach to it and perform its first task: monitoring *voltage* and *current*. [The next part explains this](2_monitoring_voltage_and_current.md).
