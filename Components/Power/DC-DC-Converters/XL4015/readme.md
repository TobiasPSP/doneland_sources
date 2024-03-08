<img src="/assets/images/power.jpg" width="80%" height="80%" />


# XL4015 Voltage Regulator

> Buck-Regulator from XLSEMI: 5A, 36V, 180kHz

The **XL4015** from *XLSEMI* is a popular step-down (**Buck**) voltage regulator chip that is used in many cheap breakout boards.

<img src="images/xl4015_buck_5a_top_side_t.png" width="50%" height="50%" />

Here are the key specs for this chip:

| Spec | Value |
| --- | --- |
| *Input* Voltage | 8V-36V |
| *Output* Voltage | 1.25V-32V |
| Max *Output* Current | 5A |
| Minimum Voltage Difference | 0.3V |
| Max Continuous Power in Breakout Boards | 40W |

> [!IMPORTANT]
> The actual *XL4015 chip* can handle **5A** across all voltages, however the *overall power* that a breakout board using the *XL4015* can provide **is further limited**. It depends on supporting components such as *MosFET*, *coils*, and *capacitors*. As a *rule of thumb*, typical breakout boards using *XL4015* can *safely and continuously* handle around *40W* (with peaks at *80W*).


| Spec | Value |
| --- | --- |
| Switching Frequency | fixed 180kHz |
| Short Circuit Protection | yes |
| Constant Current Function  | yes |
| Thermal Protection | yes |
| Max Junction Temperature | 125C |
| Design | PWM-Buck |
| Efficiency | up to 96% |


<details><summary>What does "Efficiency" mean?</summary><br/>

Any *voltage regulator* converts a *input* voltage to a different *output* voltage, and this process has losses (causes heat). The *efficiency* states how much of the *input* energy is actually ending up at the *output* terminal, and how much is lost as heat:

An efficiency of *96%* states that 4% of the energy is lost in heat. The amount of heat generated depends on the total amount of energy you feed into the regulator.

### Examples

If you supply **12V** and would like to get **5V** and **3A**, then these calculations apply:

* The total *output* energy is **5V** x **3A** = **15W**.
* At *96%* efficiency, *4%* of *input* energy is lost. You need **15W** x **100%** / **96%** = **15.625W** at the *input* (and **0.625W** dissipate as heat)
* When you drive the *input* with **12V**, you need **15.625W** / **12V** = **1.3A**

The *XL4015* has a **maximum** efficiency of *96%*. Efficiency is very different for different *input* and *output voltage* scenarios.

* When you reduce **24V** to **12V** and draw **4A** at the *output* side (i.e. to run a car cooling box off a truck battery), efficiency is *93%* (according to data sheet).
* When you reduce **12V** to **5V** and draw **5A** at the *output* side (i.e. to operate USB devices from a car lighter jack or power a microcontroller), efficiency is just *87%*.

### Dissipate Heat 

This illustrates another important consideration: *heat sinks*.

In the latter example, **5V** @ **5A** result in **25W** power. The lost energy at *87% efficiency* is ( **25W** / **0.96**) - **25W**: **1.04W**. So in this scenario, the voltage regulator also works like a *1W heater element*. Make sure your housing and device design allows *1W* worth of heat to be dissipated. If it is less, your device will continuously heat up until it breaks.

### Affecting Efficiency

*XL4015* efficiency is generally controlled by these scenarios:

* **<200mA Output Current:** when drawing currents *less than 200mA*, efficiency is worst and can drop to as low as 62%. This regulator is therefore *not ideal* to power small microcontroller circuits.
* **>3A Output Current:** Output currents above *3A* hurt efficiency over-proportionally across all voltages.
* **Voltage Difference:** the *higher* the voltage difference between *input* and *output*, the *lower* the efficiency. Converting **36V** to **5V** drops efficiency to around *80%* whereas converting **12V** to **5V** keeps efficiency above *90%* most of the time.
* **Very Low Output Voltage:** the *lower* the *output* voltage, the less efficient. It is more efficient to reduce **24V** to **12V** (*12V* drop) than to reduce **12V** to **5V** (just a *7V* drop, should be *more* efficient but the *output* voltage is *very low*

The *XL4015* is best if operated in the mid-range. It suffers when you move towards its *edge cases*, either by drawing *too little* or *too much* **current**, or by using *a very high input* or a *very low output* voltage.

That said, even with a relatively lower efficiency, the *XL4015* still performs well even in edge cases. Just don't over-do it. The lesser the efficiency and the higher the current you draw, the better should be your *heat sink*.


</details>

## Common Pitfalls

Here is a list of the common *novice misperceptions* that cause breakout boards to go off in flames and sad faces:

* **Maximum Current:** The *maximum* current (of **5A** for this chip) does not mean that any breakout board using this chip can produce **5A** output *at any output voltage*. It is the absolute *maximum* the chip can sustain, typically only for *short periods of time*, and only when additional *heat sinks* are in place.
* **Maximum Power:** An important rating (for **breakout boards using this chip**) is often missing: the *overall power* the *breakout board* can provide (in *Watts*). **40W** allows a current of **8A** at **5V**, but only a current of **1.6A** at **24V**. So while the breakout board you bought *may indeed safely produce **5A** (at a low output voltage)*, the same **5A** may *kill* the board and cause a *fire* when you draw them from a *higher* output voltage. The total *watts* are what counts.
* **Consider *both*:** To operate a regulator safely, neither exceed the maximum current *nor* the maximum power:
  * should you operate this regulator at an output voltage of **5V**, the maximum power of **40W** would allow a maximum current of **8A** however the maximum allowable current is **5A**. Thus, when operated at **5V** output, the maximum power is just **25W**.
  * operating the regulator at an output voltage of **24V** cannot provide the maximum current of **5A** because this would result in a power of **120W**. At **24V** output, the maximum allowable current is **1.6A**.
* **Short Circuit Protection:** While the *XL4015* comes with *short-circuit protection*, this does not mean that you can do without a *fuse* - or keep the output short-circuited for a long period of time: the *XL4015* can reduce switching frequency from 180kHz to 48kHz when short-circuited but *will not* disconnect the output. It will ultimately run into its *thermal protection* which *wears down and can eventually damage* the chip. *Short-circuit protection* is meant to protect from *very short* instances.
* **Input Voltage > Output Voltage:** this is a **Buck** regulator. It *reduces* the input voltage. Once you set an *output voltage*, this limits the range of allowable *input* voltages:
  * The regulator supports *input* voltages in the range of *8-36V*. If you set the regulator to an *output* voltage of *12V*, the *input* voltage now must be in the range of *12.3-36V* (add *0.3V* to the *output voltage*: this is the *minimum voltage difference* found in the specs above).
   
<details><summary>What does "Switching Frequency" mean?</summary><br/>

The *XL4015* uses a *fixed* switching frequency of 180kHz which is considered to be relatively *low*. 

### Benefits of Low Switching Frequency

Low switching frequencies must store *more* energy per switch so they must increase component size (for *coils* and *inductors* so that they can actually store more energy) which increases board size, weight, and cost. 

At the same time, this can improve *efficiency* though, especially when larger currents are required: each time energy needs to be transferred back and forth, losses occur. With lower frequency, losses happen less frequent.

Another positive effect of *low* switching frequencies is less *EMI* (electromagnetic interference). Using regulators with *low* switching frequencies like the *XL4015* are well-suited for *DIY projects* where *makers* seldom pay attention to proper *EMI protection*, and where miniaturization is not critical.

### Benefits of High Switching Frequency

There are advantages for *high* switching frequencies, too: Regulators with *high* switching frequencies (up in the range of several MHz) are much smaller. 

They need to switch only very small amounts of energy because due to the high frequency, they switch much more often. 

This can result in less *output voltage ripple*. For the same reasons, regulators with *high* switching frequency can *respond faster* to changes in load and output impedance. In general, *high* switching frequencies produce more stable output voltages (*steady-state*). They are ideal for highly integrated devices such as *smartphones*.



</details>

## Pins

Most probably the *XL4015* will be mounted on a supporting breakout board but you can operate the chip by itself, too, and design your own **Buck** converter around it:

| Pin | Name | Description |
| --- | --- | --- |
| 1 | GND | Make sure you connect it outside a supporting Schottky diode to prevent switching current spikes to backfire as noise into the chip |
| 2 | FB | Feedback. Typically a resistor voltage divider senses the actual output voltage and reports it through this pin (feedback threshold voltage is 1.25V) so that the chip knows whether adjustments are needed |
| 3 | SW | Output positive voltage |
| 4 | VC | Connects a 1uF bypass capacitor to VIN |
| 5 | VIN | Input positive voltage. Use large capacitor to GND to control noise |
 
[Data Sheet](materials/XL4015_datasheet.pdf)


## Simple Constant Voltage Buck Converter

Even though the *XL4015* comes with *constant current* functionality built-in, some breakout boards do not utilize this functionality and provide *constant voltage* (**CV**) only. You can easily recognize these boards by the *one* trim potentiometer (instead of *two*):

<img src="images/xl4015_buck_cvonly_top_left_t.png" width="50%" height="50%" />

These *very simple* **Buck** converters feature through-hole connectors for *input* and *output* power on both ends, and a printed arrow on the back side indicates the direction of power flow.

<img src="images/xl4015_buck_cvonly_bottom_t.png" width="50%" height="50%" />

Often, you can get these converters for cheap in packs of 3 or 5 from places like *Amazon*.

A small LED beneath the trim potentiometer lights up when powered.

### Setting Output Voltage

To set the desired fixed output voltage, connect a multimeter to the output, set its range to the **200V** range (or any range that safely covers your input voltage), then connect the *input power*.

The multimeter shows the actual *output* voltage. This voltage *cannot be higher than your input voltage*.

Now turn the trim potentiometer in either direction and watch the voltage change at your multimeter.

### Specs

| Feature | Value |
| --- | --- |
| Input | 4-38V |
| Output | 1.25-36V |
| Maximum Current | 5A |
| Maximum Power | 50W |
| With Heat Sink | 75W |
| Reverse Voltage Protection | yes |
| Reverse Polarity Protection | no |
<sup>*(always double-check the data sheet or manual of *your* board. There are many different variants available that all look and behave similar but not necessarily identical)*</sup>

> [!TIP]
> The *quality* of these boards varies greatly: they can work great, and they can be dead out of the box. You get what you paid for.
> Any of the boards showcased here can be destroyed by overloading them: keep in mind that the maximum power is **50W**, so when your *input* voltage is **24V**, the maximum current is **2A** (not **5A**), and with a good extra *heat sink* you might push this to a maximum of **3A**.
> These boards work best when *not* pushed to their limits, though.

## Tenstar CC CV Buck Converter

The company *Tenstar* supposingly were the first to come up with a very popular **Buck** converter breakout board design that has been *cloned* numerous times since it surfaced.

<img src="images/xl4015_buck_5a_tenstar_top_angle_overview_t.png" width="50%" height="50%" />

> [!TIP]
> The board color is **black** which distinguishes it from most *clones* that use a **red** board.

### Terminals

The board comes with two *screw terminals* to easily connect input and output power.

<img src="images/xl4015_buck_5a_tenstar_top_2_t.png" width="50%" height="50%" />

### Two Potentiometers

One important detail to look out for are the *two potentiometers*: they indicate that this board supports both *constant voltage* (**CV**) and *constant current* (**CC**). Not all *XL4015* breakout boards do.

### Version With Display Shield

There is also a special version of this breakout board available that comes with a mounted *display shield* to display the *voltage* and *current*.

<img src="images/xl4015_buck_5a_tenstar_display_top_poti_t.png" width="50%" height="50%" />

The *display shield* is not just mounted to a regular **Buck** board. The **Buck** board has a modified design and uses different trim potentiometers that can be adjusted from the side (instead from top).

### Shunt-Resistor

A typical characteristic of this board is a prominent **R050** shunt resistor that is mounted on its back.

> The batch of *Tenstar **Buck** boards* I received showed a *very dirty* back side full of residue that you should clean with some iso alcohol before use.

<img src="images/xl4015_buck_5a_tenstar_bottom_dirty_t.png" width="50%" height="50%" />


> Tags: Buck, CC, CV, 36V, 5A

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/dc-dc-converters/xl4015?344080020426240854) - last edited 2024-02-27
