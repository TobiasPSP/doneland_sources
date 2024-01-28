# Transistors - Practical Summary
:stopwatch: Reading time: 10 minutes.

## Quick overview
Transistors work similar to a dam, and while a *valve wheel* in a dam *controls how much water can flow* through it, the transistor control pin (called *base* or *gate*) controls how much current can flow through the remaining two pins. 

Depending on transistor type, the control pin that is telling the transistor what to do is driven either by *voltage* or by *current*.  

<img src="/Images/damIntro1.jpg" width="110%" height="110%" />

A transistor can act either as **switch** or **potentiometer**:

**Switch**: the transistor is either fully *on* (fully conductive), or completely *off* (non-conductive), acting like a physical **switch**. Rather than you flipping a real switch, the transistor is controlled electronically. In fact, in many scenarios power transistors (*MOSFETs*) are used this way to replace slow and power-hungry mechanical relais, so tiny non-powerful low-voltage buttons or small currents and voltages can control huge currents or dangerous voltages. 

**Amplifier**:  By slowly increasing *voltage* or *current* to the control pin, the transistor works like a variable resistor and slowly increases or decreases its resistance between the other two pins. So a transistor can be used like a potentiometer, and the use case of a *switch* (above) is just an extreme example of this (cranking the potentiometer fully open or closed). Unlike a real potentiometer, the transistor can support significant currents. So a tiny voltage or current change at the control pin can result in a massive current change between the other two pins. This is how a transistor *amplifier* operates.

### Circuit Symbols

In schematics, you identify transistors by these symbols:

<img src="/Images/transistor_symbols_wide.png" width="50%" height="50%" />


<details>
  <summary>Slight Symbol Variants</summary>
  


  <br/>
You may run across slight variations of these symbols, however for most practical purposes, you can focus on the four different transistor types depicted above and can safely ignore the rest of this paragraph if you are in a rush.
 
* **Diode**: Some FET symbols include a symbol for a *diode* (like above). This often indicates *Power MOSFET* transistors that can handle huge amounts of currents.   

* **Straight** line vs. **dashed** line: the FET symbol may show a *straight line* instead of *three separated small lines* (*dashed* line as seen in the image above). A *dashed* line represents an *enhancement mode* FET whereas a *straight line* represents a much less common *depletion mode* FET. *Enhancement mode* FETs are "normally open" so by default, they are *off* (non-conductive). *Depletion mode* FETs are "normally closed" so by default, they are *on* (conductive).
 
* **4 Terminals instead of 3**: *FET* transistors *internally* use *four* connections, one on the left side and three on the right side. They only *expose three* terminals though. So typically, the symbol combines two lines with the **source** pin (as seen above). Occasionally, you may find symbols with a separate *forth* exposed terminal called *substrate*. However, there are practcally no FET transistors available that in fact expose this forth terminal.
</details>

<details>
  <summary>Special Purpose Transistors</summary>
  <br/>
In schematics, you may come across special purpose transistors in preconfigured setups:

<br/>
<br/>
<img src="/Images/special_types.PNG" width="70%" height="70%" />

<br/>
<br/> 

* **Darlington**: a *Darlington* transistor is actually a combination of two transistors coupled together for *amplification* purposes: by combining two transistors, the *gain* is much higher than any single transistor could provide. The first transistor amplifies the input voltage and then uses the amplified current to drive a second transistor. That is why *Darlington* transistors are used when you have very weak input signals and require a high amplification factor.
The symbol either identifies a *Darlington* transistor by a **double line** at the *collector*, or the dual transistors are actually depicted. When the symbol also includes a *diode*, this is representing a *Power Darlington* transistor, capable of handling high currents.
* **Phototransistor**: here, a light-sensitive input replaces the *base* terminal. The minute current created by the light-sensitive material drives the transistor. In essence, the conductivity of the photo transistor is controlled by the intensity of the incoming light.
* **Optocoupler**: in this device, a *photo transistor* is combined with a light source (LED). This way, one circuit (driving the LED) can control a second circuit (driven by the transistor), so *Optocouplers* **physically separate** two circuits, much similar to magnetic *Reed Contacts* or *Relais* - except *Optocouplers* have no movable parts, and they support more than just a simple *on* and *off*. Instead, they can couple any signal strength. *Optocouplers* are often used to connect microcontrollers with other circuitry that runs on a much higher voltage.

</details>

### Transistor Families: BJT and FET

There are two fundamental transistor types available: classic *BJT* transistors and *FET* transistors:

* **BJT**: In hobbyist projects, these are the most commonly used transistors. They are used for logic and for switching small loads such as LED. **BJT** are controlled by *current* and need a protective resistor at their *base*.
* **MOSFET**: They are typically used to switch high current loads such as lamps, Power-LEDs, motors, heaters, etc. **FET** are controlled by *voltage* (electrical field) and do not need a protective resistor at their *gate*.


<img src="/Images/transistor_types_real_.png" width="50%" height="50%" />

<details>
  <summary>How do *BJT* and *FET* differ?</summary>
<br/>
  
* **BJT**: they come in a plastic housing with one side flat and have a *low input impedance*: their resistance between *base* and *emitter* is *very low* so they are driven by *current*. In fact, since their resistance at the control pin is so *low*, you *have to use a resistor* at the *base* pin to limit the current. Otherwise, due to the low resistance, a huge current could flow and quickly destroy the transistor. In hobbyist use cases, *BJT* transistors are typically used for logic and to switch small loads such as LEDs.   
* **MOSFET**: they come in a rectangular plastic housing with metal heat sink, indicating their capability to handle large currents. They have a *high input impedance*: since their resistance between *gate* and *source* is *very high*, there is almost no current flowing inbetween *gate* and *source*. So *FET* transistors are driven by *voltage* (using an *electrical field* to control conductivity), so they require almost no energy to control. Thanks to their hight resistance at the control pin, you *do not necessarily need a protective resistor*. Even if you directly connect positive voltage to the control pin, due to its high resistance, the current is always tiny with no risk to destroy the transistor. In hobbyist projects, *FET*s are used primarily to switch *high current* loads.  
</details>


In the image above, you see the typical shape of different transistor families: *MOSFET*, *BJT*, and a *Power BJT* (left to right).

### Legs and Terminals

Transistors have three connectors (legs):

* **Base**/**Gate** (Control): this is the control input that tells the transistor how much power it should let pass through. 
* **Collector**/**Source** (Input): this is "collecting" the electrical power you want to control, so here is the *source* of the power. It is the **positive lead**.
* **Emitter**/**Drain** (Output): this is where the current "leaves" the transistor (gets *emitted* or *drained*). Both the *base* and the *collector* current leaves the transistor via the *emitter* pin. This is the **negative lead**. 

> The terms *base*, *collector*, and *emitter* are used with *BJT* type transistors whereas the terms *gate*, *source*, and *drain* are used with *FET* type transistors. Regardless, their purpose is similar.

### Types: NPN, PNP, N-Type, P-Type

Transistors come in *N* and in *P* types. *MOSFET* transistors are called *n-type* and *p-type*, whereas **BJT** transistors are called *NPN* and *PNP*. The *P*-type has much more typical use cases than the *N*-type.

The most important practical difference is in how *N*- and *P*-types are controlled: the typical *N*-type transistors are controlled via a *positive* voltage, whereas the less common *P*-type transistors are controlled via a *negative* voltage.

* **NPN**,**N-Type**: A *NPN BJT transistor* needs a **positive** *current* flowing from *base* to *emitter* to conduct. A *N-Type MOSFET* also needs a **positive** *voltage* between *gate* and *source* to conduct. Note how the little arrow at the *emitter*/*source* pin indicates the direction of current flow.  
* **PNP**,**P-Type**: A *PNP BJT transistor* needs a **negative** *current* between *base* to *emitter* to conduct. A *P-Type MOSFET* also needs a **negative** *voltage* between *gate* and *source* to conduct. Again, note how the little arrow at the *emitter*/*source* pin indicates the direction of current flow. For these transistors, the arrow points to the reverse direction.
 

The schematics illustrate the fundamental difference between *NPN* and *PNP* type transistors. Both schematics use a switch and a transistor to control a load:

<img src="/Images/pnp_npn_compare.PNG" width="80%" height="80%" />

**NPN**: the left schematic uses a **NPN** transistor which switches *ON* the load when the transistor *base* is connected to *Vcc* (positive voltage).

**PNP**: the right schematic uses a **PNP** transistor which switches *ON* the load when the transistor *base* is connected to *GND* (0V).

Here are some more observations to note:

* **NPN**/**n-type FET**: Current flows from *collector*/*source* to *emitter*/*drain*. This is the most commonly used type. Both *base*/*gate* and *collector*/*source* are connected to the **positive** voltage: the *load* controlled by the transistor is wired between **positive** voltage and *collector*/*source*. The combined current leaves the transistor through the *emitter*/*drain* which is connected to GND.
* **PNP**/**p-type FET**: Current flows from *emitter*/*drain* to *collector*/*source*. The positive voltage is connected to the *emitter*/*drain*, so the entire current enters the transistor through the *emitter*/*drain*. Both *base*/*gate* and *collector*/*source* are connected to the **negative** voltage. So by controlling how much current is "leaving" the base towards GND, you control how much current goes through the *load* which is wired between **GND**  and collector.

> Commonly used **NPN** transistors are *2N2222*, *2N3904*, *TIP120*   
> Commonly used **PNP** transistors are *2N2907*, *2N3906*

# Identifying Legs and Terminals

Transistors of all types have three legs. Obviously, it is crucial to identify the correct terminals. 

> [!CAUTION]  
> The only *dependable* ways of determining the pins is either review the *data sheet* for the *particular transistor type* you want to use, or to physically *test* the transistor.

> [!TIP]
> Many multimeters have built-in transistor test capabilities when you switch the dial to the *hFE* setting.
>
> You may even want to look into purchasing a dedicated transistor test device. They are available for around €20 and tell you exactly not just the pins but also the N- or P-type and many additional useful parameters.

Only very few transistors actually show distinct pin markings on their housing. There are a few rules of thumb though (use at own risk):

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






