<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Voltage

> Voltage Is Electric Pressure Or Tension. It Is The Power That Drives Current Through Resistance. 

*Voltage* defines the *power* to surpass a *resistance*. The *higher* the *voltage*, the *more resistance* can be overcome. 

That's why *voltages above **30V*** are considered *dangerous*: higher voltages can surpass the *resistance* of the human skin and drive a harmful *current* through your body. Voltages *below **30V*** cannot do this and are considered *safe*. That's why *DIY projects* typically use *voltages* well below **30V**.

> **30V** is a *conservative* threshold. Healthy and *dry* skin will not conduct electricity below **50V**. However, when skin gets *wet* or has lacerations, even voltage below **40V** can be *lethal*. By keeping voltages below **30V**, you make sure electricity cannot penetrate your skin even under the most adverse conditions.

## Voltage and Current

The *total electric power* (in *Watts*) is defined as *voltage x current*. This total power is the energy that can do work for you.

Voltage influences the total power in two ways:

* The higher the voltage, the more *power* can be driven through a *resistance*
* If the voltage is too low to penetrate a given *resistance*, no *current* can flow, and the total power is null.

> [!NOTE]
> To clarify: if you touch wires connected to a **5V** voltage, *no current at all* will flow through your body because the *voltage* is too low to drive electrons through the resistance of your skin.
> To operate devices, you also need a certain *minimum voltage*. For example, **LED** have an internal resistance, similar to your skin. **LED** define a *forward voltage* (minimum voltage) that must be present for *current* to flow. Voltages below their *forward voltage* will keep **LED** dark.

## AC and DC

In **AC**, the polarity changes contiuously many times per second, and *current* flows *back and forth*. The *voltage* is not constant but rather an *average voltage*. Typically, electrical household power is **AC** (due to the way how it is generated and transported to you).

In **DC**, the polarity does not change, and *current* always flows in the *same* direction. Typically, *battery power* and electrical power provided by *power adapters* is **DC**.

> [!NOTE]
> In most *hobbyist projects*, you use **DC** and therefore need a *battery*, or a *power adapter* to convert **AC** to **DC**.
> The reason **AC** exists at all is that it can be easily *generated* using magnetic fields in *dynamos* and *turbines*, and that **AC** can be easily transmitted over long distances because **AC** voltage can be easily raised or lowered using transformers.
> To transport energy, the *higher* the voltage, the *lower* the *current* can be. This reduces losses through *heat* and is the reason why electrical transmission lines use super high voltages like 380.000V and more.

## Voltage Sources

Voltage is produced whenever there is a difference in electric charge between two points. This difference can be produced in a number of ways:

* **Battery:** a *battery* uses *chemistry* to store more electrons on one side than on the other. It is a **DC** source. Since a *battery* stores electrons to produce the *voltage*, it deplets over time, and while you use it, the *voltage* slowly decreases.
* **Power Supply:** electrical energy is produced elsewhere as **AC** and delivered to your home. A *power supply* converts the energy to **DC** and lowers the voltage to safe levels that you then can use. *Power supplies* deliver *endless* energy with a constant voltage (as long as you pay your bills).
* **Dynamo:** similar to a power plant, you, too, can *generate* electrical energy by converting *physical movement*. A *dynamo* moves *magnets* embedded in a *coil* to produce alternating magnetic fields that *induce* electrical current. Like a power plant, this produces **AC**.
* **Photovoltaic:** *Solar cells* use substrates that convert the energy of natural *light* into *electrical power* and produce **DC**. The *voltage* depends largely on the *amount of light* which is why you cannot use *solar cells* directly. You need a *voltage regulator* to convert the wide range of incoming voltage to a fixed *output voltage* that you can use.

 
