# Transistors - Practical Summary
Here you'll find a general introduction to **transistors**, focused on practical aspects and essentials. 

## Quick overview
Transistors work similar to a dam, and while a valve wheel in a dam controls how much water can flow through the dam, the voltage at the transistor control pin (*base* or *gate*) controls how much current can flow through the remaining two pins. 

That's why a transistor can be viewed like a voltage-driven adjustable resistor (similar to a manually operated potentiometer), and in its two extreme positions a transistor acts like a plain *on*/*off*-switch.

<img src="/Images/damIntro1.jpg" width="110%" height="110%" />

**Acting as a switch**: in its most extreme scenarios, the transistor control pin is either 0V or full voltage. Depending on transistor type, this will either turn the transistor completely *on* (producing a shortcut), or completely *off* (being non-conductive). 

The transistor now acts like a simple **switch**, only instead of you flipping a real switch, the transistor can be controlled electronically. In fact, in many scenarios power transistors (*MOSFETs*) are used this way to replace slow and power-hungry mechanical relais. 

**Acting as an amplifier**: if you submit a voltage inbetween the two extremes, the transistor resistance slowly decreases or increases. So a tiny voltage change at the control pin can result in a massive current change inbetween its other two pins. Here, the transistor is used as an **amplifier**.

### Circuit Symbols

In schematics, you can identify transistors by these symbols:

<img src="/Images/transistor_symbols_wide.png" width="50%" height="50%" />

The upper two symbols represent "classic* **BJT** transistors, the lower two symbols represent **FET** transistors. More on that below. 

#### Slight Variations
You may run across slight variations of these symbols, however for most practical purposes, you can focus on the four different transistor types depicted above and can safely ignore the rest of this paragraph if you are in a rush.
  
Some FET symbols include a symbol for a *diode* (like above). This often indicates *Power MOSFET* transistors that can handle huge amounts of currents.   

At other times, the FET symbol may show a straight line instead of three separated small lines (like above).
A straight line indicates a *depletion mode* FET whereas the three separate short lines indicate an *enhancement mode* FET.   

A *depletion mode* FET is similar to a "normally closed" (NC) switch, so this transistor is *conductive* when there is no voltage between *gate* and *source*. In contrast, an *enhanced mode* FET is the other way around and works like a "normally open" (NO) switch: when there is no voltage between *base* and *source*, these transistors are *off* and do not conduct.   

*FET* transistors (the lower line in above image) generally show *four* instead of *three* terminals, one on the left side and three on the right side. This represents the inner physical structure of these transistor types.

Still, these transistors, just like the classic *BJT* transistors, have just *three* exposed terminals, which is why the symbol combines two lines with the **source** pin. In some symbols you may find a separate *forth* terminal called *substrate*. Practically though, there are no FET transistors around that physically expose this forth terminal.

#### Special Purpose Transistors

In schematics, you may come across special purpose transistors in preconfigured setups. Here are the three most common types:

<img src="/Images/special_types.PNG" width="70%" height="70%" />

* **Darlington**: a *Darlington* transistor is actually a combination of two transistors coupled together for *amplification* purposes: by combining two transistors, the *gain* is much higher than any single transistor could provide. The first transistor amplifies the input voltage and then uses the amplified current to drive a second transistor. That is why *Darlington* transistors are used when you have very weak input signals and require a high amplification factor.
The symbol either identifies a *Darlington* transistor by a **double line** at the *collector*, or the dual transistors are actually depicted. When the symbol also includes a *diode*, this is representing a *Power Darlington* transistor, capable of handling high currents.
* **Phototransistor**: here, a light-sensitive input replaces the *base* terminal. The minute voltage created by the light-sensitive material drives the transistor current. In essence, the conductivity of the photo transistor is controlled by the incoming light intensity.
* **Optocoupler**: in this device, a photo transistor is combined with a light emitting diode (LED). This way, one circuit (driving the LED) can control a second circuit (driven by the transistor). *Optocoupler* can physically separate two circuits, much similar to magnetic *Reed Contacts* or *Relais*, except *Optocoupler* have no movable parts, and they support more than just a simple *on* and *off*. Instead, they can couple any signal strength.
*Optocouplers* are often used to connect microcontrollers with other circuitry that runs on much higher voltages.

### Transistor Families

Transistors use different architectures:

* **MOSFET**: 99.9% of all transistors today are of this type. MOSFETs change conductivity based on the applied voltage, and *Power MOSFETs* can control extremely high currents. MOSFET input impedance (resistance) is *high*. They act as voltage-controlled variable resistors.
* **BJT**: they used to be the most widely used transistors decades ago. BJT input impedance is *low*. They are often used to amplify current. Although *BJT* transistors are still used, their future is uncertain, and they may eventually be completely replaced by *MOS* type of transistors.
* **Other**: there are plenty more transistor types for special purposes that are not discussed here.

> Hobbyists often use **BJT** transistors for logic and **MOSFET** transistors as power switches when devices like LEDs or motors need to be controlled.

<img src="/Images/transistor_types_real_.png" width="50%" height="50%" />

In the image above, you see the typical shape of different transistor families: *MOSFET*, *BJT*, and a *Power BJT* (left to right).

### Wiring

Transistors have three connectors:

* **Base**/**Gate** (Control): this is the control input that tells the transistor how much power it should let pass through. 
* **Collector**/**Source** (Input): this is "collecting" the electrical power you want to control, so here is the *source* of the power. It is the **positive lead**.
* **Emitter**/**Drain** (Output): this is where the current "leaves" the transistor (gets *emitted* or *drained*). Both the *base* and the *collector* current leaves the transistor via the *emitter* pin. This is the **negative lead**. 

> The terms *base*, *collector*, and *emitter* are used with *BJT* type transistors whereas the terms *gate*, *source*, and *drain* are used with *FET* type transistors. Regardless, their purpose is similar.

### Types

Transistors come in *N* and in *P* types. *MOSFET* transistors are called *n-type* and *p-type*, whereas **BJT** transistors are called *NPN* and *PNP*. The *P*-type has much more typical use cases than the *N*-type.

The most important practical difference is in how *N*- and *P*-types are controlled: the typical *N*-type transistors are controlled via a *positive* voltage, whereas the less common *P*-type transistors are controlled via a *negative* voltage.

The schematics illustrate the fundamental difference between *NPN* and *PNP* type transistors. Both schematics use a switch and a transistor to control a load:

<img src="/Images/pnp_npn_compare.PNG" width="80%" height="80%" />

**NPN**: the left schematic uses a **NPN** transistor which switches *ON* the load when the transistor *base* is connected to *Vcc* (positive voltage).

**PNP**: the right schematic uses a **PNP** transistor which switches *ON* the load when the transistor *base* is connected to *GND* (0V).

Here are some more observations to note:

* **NPN**/**n-type FET**: Current flows from *collector*/*source* to *emitter*/*drain*. This is the most commonly used type. Both *base*/*gate* and *collector*/*source* are connected to the **positive** voltage: the *load* controlled by the transistor is wired between **positive** voltage and *collector*/*source*. The combined current leaves the transistor through the *emitter*/*drain* which is connected to GND.
* **PNP**/**p-type FET**: Current flows from *emitter*/*drain* to *collector*/*source*. The positive voltage is connected to the *emitter*/*drain*, so the entire current enters the transistor through the *emitter*/*drain*. Both *base*/*gate* and *collector*/*source* are connected to the **negative** voltage. So by controlling how much current is "leaving" the base towards GND, you control how much current goes through the *load* which is wired between **GND**  and collector.

> Commonly used **NPN** transistors are *2N2222*, *2N3904*, *TIP120*   
> Commonly used **PNP** transistors are *2N2907*, *2N3906*

# Identifying Pins

Transistors of all types expose three terminals. Obviously, it is crucial to identify the correct terminals. 

> :warning: The only *dependable* ways of determining the pins is to either view the *data sheet* for the particular transistor type you want to use, or to actually *test* the transistor.
> Many multimeters have built-in transistor tester when you switch the dial to the *hFE* setting.
>
> You may even want to look into purchasing a dedicated transistor test device. They are available for around €20 and tell you exactly not just the pins but also the N- or P-type and many additional useful parameters.

Only very few transistors actually show distinct pin markings on their housing. However, there are a few rules of thumb (use at own risk):

## Plastic Casing With Flat Side

*BJT* transistory typically come in a black plastic casing with one *flat* side which is the *front* side. To identify the pins, look at the flat side and keep the pins pointing downwards:

* **NPN**: (from left to right) the pins are: *Collector*, *Base*, *Emitter* (remember "CuBE").
* **PNP**: (from left to right) the order is reversed, and the pins are *Emitter*, *Base*, *Collector*

<img src="/Images/bjt_pins.PNG" width="50%" height="50%" />

> :warning: The default pin arrangement is not mandatory, and there are many exceptions to the rule. So always look up the transistor type you are using and verify the pin assignment in its data sheet!

## Metal housed "can" type

Pins are arranged circularly. There is a tab in the rim of the housing. Typically, the pin closest to the tab is *Emitter*, the opposite pin is *Collector*, and inbetween is *Base*.

> :warning: The default pin arrangement is not mandatory, and there are many exceptions to the rule. So always look up the transistor type you are using and verify the pin assignment in its data sheet!

### MOSFETs






