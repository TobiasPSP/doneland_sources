<img src="/assets/images/transistorswitch.png" width="80%" height="80%" />
 
# Switching DC Loads With Transistors

> Selecting A Transistor For Switching DC Loads

In this section I am looking at transistors suitable for switching big loads: the *transistor* acts like a *physical switch* and is operated either in *fully open* or *fully closed* mode.

> [!CAUTION]
> *Transistors* can only switch *DC* loads. They **cannot switch AC**. If you want to switch *AC*, use a *relais*, a solid-state *DA* relais, or a *thyristor*.






## Selecting Suitable Transistor

To select a suitable transistor for *switching* purposes, these are the *key aspects* to check:

### Positive vs. Negative Voltage

*N*-type *transistors* are more common because they are more readily available, and also *cheaper* to produce. They need to be ***n**egative* at their emitter (which is typically connected to *GND*), so they are controlled by a *positive* voltage.

If you *must* control the *transistor* by a *negative* voltage, choose a *P*-type transistor.

> [!NOTE]
> Whether you require a *N*- or *P*-type transistor depends entirely on your *circuit design*.



### Available Voltage

What is the *maximum voltage* your circuit can apply to the *transistor* control pin? 

*MOSFET* transistors are controlled by *voltage*: if you cannot supply enough *voltage* to the *MOSFET control pin*, then it may never *close the switch*, or more likely: *not **fully** close*: you are now accidentally operating the *transistor* like an *amplifier*. It now has a very high *on-resistance*, producing *excessive heat* and wasting energy.


> [!CAUTION]
> In *low voltage circuits* (i.e. *ESP32* with *3.3V*), you need to be extra careful when selecting a *transistor*: make sure it can fully turn on with the voltage you can provide. 




### Load

What kind of *load* do you want the *transistor* to switch?

* **Current:** what is the *maximum current* you want to switch (just like physical switches)? If you have a choice of suitable *transistor types*, choose the one with the highest allowable current.
* **Voltage:** in *DIY* projects, *voltage* is typically secondary as most circuits use the *same single low supply voltage*. If however you design a *circuit* with multiple *supply voltages*, i.e. using a microcontroller at *3.3V* and switching an *LED strip* at *48V*, then make sure the *transistor* is rated for the voltage you want to switch, i.e. *48V* or more.



### Efficiency

If *efficiency* is a priority, i.e. because the device is battery-operated, take a look at the *on-resistance* (what is the *loss* you have when the load is turned *on*?), and the *off-resistance* (how much electrical power is still flowing even though the *transistor* is in *off* state)?


#### Ideal Physical Switch
A physical switch uses *air* as *insulator*: when it is turned *on*, two contacts *touch* and provide a connection with *very low resistance*. When the switch is turned *off*, the two contacts are moved away from each other, and the *air* inbetween insulates them so that they have a *very high resistance*: no current flows.


#### Not-So-Ideal Transistor Switch
A *transistor* is a *semiconductor*: *electrons* are controlled by the *control pin*, and these electrons in turn control the conductance of the *transistor*. 

* **Transistor Gets Hot:** Depending on *transistor type*, the *on-resistance* can be significant. When switching small loads, this loss can typically be ignored. However, with higher currents this loss can quickly turn into an unwanted *heat source*. The most common *practical* reason for *transistors* that get *too hot* is a *MOSFET transistor* that is controlled by *insufficient voltage*: the chosen *MOSFET* requires a control voltage (much) higher than the voltage that was actually supplied.

* **Battery Dies Prematurely:** *Transistors* are never *completely off*: some electrons still conduct energy, even in *off* state. The *leakage current* is typically *very small* but can add up over time. Battery-operated devices that may need to run for weeks or years can easily be depleted prematurely when selecting the *wrong transistor* type with a relatively *high off-resistance*.

> [!TIP]
> When powering a device through a power adapter, worrying about tiny leakage currents makes neither sense nor a difference.





> Tags: Transistor, Choice, Selection, Heat, Amplifier, Switch

[Visit Page on Website](https://done.land/components/transistor/switch?453841041228244933) - created 2024-04-27 - last edited 2024-04-27
