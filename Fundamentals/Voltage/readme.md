<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Voltage

> Voltage Is Electric Pressure, Tension Or Generally Difference In Electrons. It Is The Power That Drives Current Through Resistance. 

*Voltage* defines the *power* to surpass a *resistance*. The *higher* the *voltage*, the *more resistance* can be overcome. 

That's why *voltages above **30V*** are considered *dangerous*: higher voltages can surpass the *resistance* of the human skin and drive a harmful *current* through your body. Voltages *below **30V*** cannot do this and are considered *safe*. That's why *DIY projects* typically use *voltages* well below **30V**.

> **30V** is a *conservative* threshold. Healthy and *dry* skin will not conduct electricity up until **50V**. However, when skin gets *wet* or has lacerations, even voltage below **40V** can be *lethal*. By keeping voltages below **30V**, you make sure electricity cannot penetrate your skin even under the most adverse conditions.

## Voltage and Current

The *total electric power* (in *Watts*) is defined as *voltage x current*. This total power is the energy that can do work for you.

Voltage influences the total power in two ways:

* The higher the voltage, the more *power* can be driven through a *resistance*
* If the voltage is too low to penetrate a given *resistance*, no *current* will flow at all, and the total power is null.

> [!NOTE]
> To clarify: if you touch wires connected to a **5V** voltage, *no current at all* will flow through your body because the *voltage* is too low to drive electrons through the resistance of your skin.   
> To operate devices, you also need a certain *minimum voltage*. For example, **LED** have an internal resistance, similar to your skin. **LED** define a *forward voltage* (minimum voltage) that must be present for *current* to flow. Voltages below their *forward voltage* will keep **LED** dark.

## AC and DC

In **AC**, the polarity changes continuously many times per second, and *current* flows *back and forth*. The *voltage* is not constant but rather an *average voltage*, and the electrons in a wire rather *vibrate* than *flow*. Typically, electrical household power is **AC** (due to the way how it is generated and transported to you).

In **DC**, the polarity does not change, and *current* always flows in the *same* direction. Typically, *battery power* and electrical power provided by *power adapters* is **DC**.

> [!NOTE]
> If you rub something, it gets *hot*: you applied a *force*. It does not really matter though whether you *rub* back and forth (**AC**), or *drag* something behind you in one direcion (**DC**).
> In either way, *friction* (*resistance*) was overcome, and this applied *force* produces *heat*.
> In the same way, both **AC** and **DC** can perform work. It does not matter whether *electrons* travel from **A** to **B**, or whether they just *vibrate*, as long as they *move*.

In most *hobbyist projects*, you use **DC** and therefore need a *battery*, or a *power adapter* to convert **AC** to **DC**.   

The reason **AC** exists at all is that it can be easily *produced* using magnetic fields in *generators* and *turbines*, and that **AC** can be efficiently transmitted over long distances because **AC** voltage can be easily raised or lowered using transformers.

To transport energy, the *higher* the voltage, the *lower* the *current* can be (because the total energy is *voltage x current*). This reduces losses through *heat* and is the reason why electrical transmission lines use super high voltages like 1.200kV and more.

## Voltage Sources

Voltage exists whenever there is a difference in electric charge between two points: this creates an *electric field* between these two points that can in turn move (*apply force* or *induce energy into*) electrically charged particles (*electrons*). 

This *potential difference* can exist in a number of ways:

* **Battery:** a *battery* uses *chemistry* to store more electrons on one side than on the other. It is a **DC** source. Since a *battery* stores electrons to produce the *voltage*, its supply is *limited* and deplets over time, and while you use it, the *voltage* slowly decreases because the *difference* in electrons on both poles of the battery decreases.
* **Power Supply:** electrical energy is produced elsewhere (**AC**) and delivered to your home. A *power supply* converts the energy from **AC** to **DC** and lowers the voltage to safe levels that you then can use. *Power supplies* deliver *endless* energy with a constant voltage (as long as you pay your bills).
* **Generator:** similar to a power plant, you, too, can *generate* electrical energy by converting *physical movement*. A *dynamo* or *generator* moves *magnets* embedded in a *coil* to produce alternating magnetic fields that *induce* electrical current. Like a power plant, this is **AC**.
* **Photovoltaic:** *Solar cells* use substrates that convert the *photon energy* of natural *light* into *electrical power* and produce **DC**. The *voltage* depends largely on the *amount of light* which is why you cannot use *solar cells* directly. You need a *voltage regulator* to convert the wide range of incoming voltage to a fixed *output voltage* that you can use.
* **Static electricity and Lightning:** when air is dry (and less conductive), huge amounts of electrons can gather on surfaces. When enough electrons cumulate, the resulting *voltage* can be so incredibly high that even very high resistances such as *air* start to conduct at this voltage. The results are *little sparks* (with *electrostatic discharges*) and *huge thunderbolts* (with *lightning*). Even though *electrostatic discharge* is not dangerous **to you** due to the low *current*, it may well be dangerous enough to sensitive semiconductor components that you play with, and can destroy them. That's why you shouldn't touch their pins or use *ground straps* to prevent electrons from building up.

## Hydraulic Analogy

A good way of picturing *voltage* is a hydraulic analogy. When a *pump* (power source) is driving water through a closed circuit of pipework, then *voltage* is the *speed* of the water (depending on the speed of the pump), and *current* is the *amount* of water (depending on the pipe diameter and the volume of the pump). 

Both the *speed* (voltage) and the *amount* (current) of water *together* determine the total amount of water (energy) delivered.

This also explains the *minimum voltage* required to pass a *resistance*: if there is a *bottleneck* (resistor, load, paddle wheel) in the pipework, *more pressure* (voltage) is needed to drive water through it or overcome the initial resistance of the load/paddle wheel. If the *bottleneck* is severe (heavy paddle wheel, high resistance) and the pressure is *low* (low voltage), no water flows at all (the paddle wheel won't move even a bit). A *minimum pressure* (minimum voltage) is required for any given resistance.

## Breakdown and Forward Voltage

Both *breakdown voltage* and *forward voltage* describe the same phenomenon: it is the minimum voltage that causes a material to experience *electrical breakdown* and become *electrically conductive*. Put simple: it is the *voltage* at which a material changes from being an *insulator* to becoming a *conductor*.

For non-semiconducting materials like *metal* or *plastics*, *breakdown voltage* is all that matters, and there is no separate *forward voltage* because the direction of current makes no difference to them.

***Semi**conductors* (like *diodes* or *transistors*) are different: as their name implies, they act *differently* depending on the *direction* of *electric field* (polarity). 

That's why *semiconductors* need *two breakdown voltages*, one for each direction of electric current. To better differentiate, the second *breakdown* voltage is called *forward voltage*:


* **Forward Voltage:** this is the voltage at which *electric breakdown* occurs for *current* in the *forward direction*. A *diode* for example is designed to conduct *current* only in *one direction*, however it does so only when the *voltage* exceeds its *forward voltage*. For *silicon diodes*, this is roughly *0.6-1.0V*, and below this voltage, a *diode* would not conduct current *in either direction*.
* **Breakdown Voltage:** this is the same, just for the *other direction*: a *diode* for example blocks current in reverse direction, yet when *voltage exceeds* its *breakdown voltage*, it becomes conductive nonetheless.

> [!NOTE]
> Materials are classified as *insulators* and *conductors* but this differentiation depends really only on the *voltage applied*: an *insulator* is a material that *conducts* at a *high voltage only* whereas a *conductor* has a much lower *resistance* and conducts always, even at very low *voltages*.

This electrical phenomenon has *practical importance* in many cases, including these:

* **Insulator:** An insulator insulates only up to a certain voltage. Once a voltage exceeds the *breakdown voltage* of the insulator, it is no longer an *insulator* and becomes a *conductor* instead. You need to carefully select the *insulation material* for higher voltages to make sure it really insulates. This also explains why *switches* are rated for certain maximum voltages: once voltages exceed the limit, the *air* insulating the small distance between the two contacts inside the switch becomes *conductive*, and *sparks* can form.
* **Diodes:** Diodes are components that conduct only in one direction. If a large enough negative voltage is applied to the diode, though, a diode will give in and allow current to flow in the reverse direction. This large negative voltage is called the *breakdown voltage*. Some diodes are actually designed to operate in the breakdown region, but for most normal diodes it's not good for them to be subjected to large negative voltages. For normal diodes this breakdown voltage is around -50V to -100V, or even more negative.
* **LED:** A **LED** is an insulator at voltages below its *forward voltage*. Once voltage reaches or exceeds the *forward voltage*, the **LED** becomes a *conductor* and starts to emit light. At the same time, **LED** have a *very low breakdown voltage* of just **5V**: applying power in wrong polarity can easily destroy them.

<details><summary>How does electrical breakdown actually work?</summary><br/>

*Metals* are considered "good" *conductors* (they conduct even at very *low voltages*), whereas *plastics* insulate. Why do these materials behave so differently?

In metals one or more of the negatively charged electrons in each atom (*conduction electrons*) are free to move about the crystal lattice. In materials like *plastics* and *ceramics* ("bad" *conductors*), all electrons are tightly bound to atoms.

When *voltage* is applied, it creates an *electric field* that applies force to *electrically charged particles* such as *electrons*. 

* **Metal:** At a *low voltage*, the *electric field* is weak. Its force, albeit weak, is still strong enough to move the freely movable electrons in *metals*: a *current* flows, the metal *conducts* despite the *low voltage*. 
* **Plastics:** The *electrons* in *plastics* or *ceramics* are tightly bound to their atoms. This force is much stronger than the weak force of the *electric field* at *low voltage*.

When the *voltage* exceeds a certain threshold (the *breakdown voltage*), the *electric field* becomes so strong that it exceeds the force of the atoms, and their *electrons* suddenly start to move. This moment is called *electrical breakdown*.

In essence, *electrical breakdown* in a material occurs when the electric field becomes strong enough to pull electrons from the molecules of the material, ionizing them. 

Once *electric breakdown* occurs, the released electrons are suddenly accelerated by the field and strike other atoms, creating more free electrons and ions in a chain reaction, flooding the material with charged particles. This is why (almost) no *current* flows below a certain *voltage*, and why any material suddenly becomes *conductive* once *voltage* exceeds a certain threshold.

At *which voltage* this occurs is just a matter of the given material, its inner structure and how strongly its atoms bind the *electrons*. This is measured in *volts per centimeter*: it characterizes the *dielectric strength* (or *conductivity*) of a material.

</details>


> Tags: Voltage, Tension, Resistance, Power, Watt, Current, AC, DC, Forward Voltage, Breakdown Voltage, Isulator, Dielectrical Strength, Conductivity

:eye:&nbsp;[Visit Page on Website](https://done.land/fundamentals/voltage?928463030815241653) - last edited 2024-03-15
