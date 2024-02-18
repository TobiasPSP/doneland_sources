# Transistors - Practical Summary
:stopwatch: Reading time: 10 minutes.

## Quick overview
Transistors work similar to a dam, and while a *valve wheel* in a dam *controls how much water can flow* through it, the transistor control pin (called *base* or *gate*) controls how much current can flow through the remaining two pins. 

Depending on transistor type, the control pin that is telling the transistor what to do is driven either by *voltage* or by *current*.  

<img src="images/damIntro1.jpg" width="80%" height="80%" />

A transistor typically acts either as **switch** or **potentiometer**:

**Switch**: the transistor is either fully *on* (fully conductive), or completely *off* (non-conductive), acting like a physical **switch**. Rather than you flipping a real switch, the transistor is controlled electronically. In fact, in many scenarios power transistors (*MOSFETs*) are used this way to replace slow and power-hungry mechanical relais, so tiny non-powerful low-voltage buttons or small currents and voltages can control huge currents or dangerous voltages. 

**Amplifier**:  By slowly increasing *voltage* or *current* to the control pin, the transistor works like a variable resistor and slowly increases or decreases its resistance between the other two pins. So a transistor can be used like a potentiometer, and the use case of a *switch* (above) is just an extreme example of this (cranking the potentiometer fully open or closed). Unlike a real potentiometer, the transistor can support significant currents. So a tiny voltage or current change at the control pin can result in a massive current change between the other two pins. This is how a transistor *amplifier* operates.

### Circuit Symbols

In schematics, you identify transistors by these symbols:

<img src="images/transistor_symbols_wide.png" width="70%" height="70%" />


<details>
  <summary>:information_source: Slight Symbol Variants</summary>
  
  <br/>
You may run across slight variations of these symbols, however for most practical purposes, you can focus on the four different transistor types depicted above and can safely ignore the rest of this paragraph if you are in a rush.<br/><br/>

<img src="images/depletion_substrate.png" width="50%" height="50%" />
 
* **Diode**: Some FET symbols include a symbol for a *diode* (like above). This often indicates *Power MOSFET* transistors that can handle huge amounts of currents.

* **Straight** line vs. **dashed** line: the FET symbol may show a *straight line* instead of *three separated small lines* (*dashed* line as seen in the image above). A *dashed* line represents an *enhancement mode* FET whereas a *straight line* represents a much less common *depletion mode* FET. *Enhancement mode* FETs are "normally open" so by default, they are *off* (non-conductive). *Depletion mode* FETs are "normally closed" so by default, they are *on* (conductive).
 
* **4 Terminals instead of 3**: *FET* transistors *internally* use *four* connections, one on the left side and three on the right side. They only *expose three* terminals though. So typically, the symbol combines two lines with the **source** pin (as seen above). Occasionally, you may find symbols with a separate *forth* exposed terminal called *substrate*. However, there are practcally no FET transistors available that in fact expose this forth terminal.
</details>

<details>
  <summary>:information_source: Special Purpose Transistors</summary>
  <br/>
In schematics, you may come across special purpose transistors in preconfigured setups:

<br/>
<br/>
<img src="images/special_types.PNG" width="70%" height="70%" />

<br/>
<br/> 

* **Darlington**: a *Darlington* transistor is actually a combination of two transistors coupled together for *amplification* purposes: by combining two transistors, the *gain* is much higher than any single transistor could provide. The first transistor amplifies the input voltage and then uses the amplified current to drive a second transistor. That is why *Darlington* transistors are used when you have very weak input signals and require a high amplification factor.
The symbol either identifies a *Darlington* transistor by a **double line** at the *collector*, or the dual transistors are actually depicted. When the symbol also includes a *diode*, this is representing a *Power Darlington* transistor, capable of handling high currents.
* **Phototransistor**: here, a light-sensitive input replaces the *base* terminal. The minute current created by the light-sensitive material drives the transistor. In essence, the conductivity of the photo transistor is controlled by the intensity of the incoming light.
* **Optocoupler**: in this device, a *photo transistor* is combined with a light source (LED). This way, one circuit (driving the LED) can control a second circuit (driven by the transistor), so *Optocouplers* **physically separate** two circuits, much similar to magnetic *Reed Contacts* or *Relais* - except *Optocouplers* have no movable parts, and they support more than just a simple *on* and *off*. Instead, they can couple any signal strength. *Optocouplers* are often used to connect microcontrollers with other circuitry that runs on a much higher voltage.

</details>

### Transistor Families: BJT and FET

There are two fundamental transistor types available: classic *BJT* transistors and *FET* transistors:

* **BJT**: most commonly used transistors in hobbyist projects. They are used for logic and for switching *small* loads such as LED. **BJT** are controlled by *current* and need a protective resistor at their *base* because their internal resistance between the control pin and the *collector* is *very low*. So without a protective resistor or another current-limiting component at their *base* (i.e. a conductor), they would shortcut the circuit and go up in flames (very much like LEDs). 
* **MOSFET**: They are typically used to switch high current loads such as lamps, Power-LEDs, motors, heaters, etc. **FET** are controlled by *voltage* (electrical field) and do not need a protective resistor at their *gate* because their internal resistance between the control pin and the *source* pin is *very high* so there is no significant current flow between these two pins under any circumstances anyway.

<img src="images/transistor_types_real_.png" width="30%" height="30%" />

(*from left to right*: *MOSFET*, *BJT*, and a *Power BJT*)

### Legs and Terminals

Transistors have three connectors (legs):

* **Base**/**Gate** (Control): this is the control input that tells the transistor how much power it should pass between the other two pins. 
* **Collector**/**Source** and **Emitter**/**Drain**: these remaining two pins carry the *load current*.

The load current flows between **Collector**/**Source** and **Emitter**/**Drain**. The *direction* of current flow depends on the transistor type.

<details>
  <summary>:information_source: Why Transistor Pins Have So Many Names</summary><br/>

  
  The terms *base*, *collector*, and *emitter* are used with *BJT* transistors whereas the terms *gate*, *source*, and *drain* are used with *FET* transistors. Regardless, their purpose is similar.

  * The *base* and *gate* pins act as the *control pin* that tells the transistor what to do.

  * The *emitter* and *drain* pins *combine* the current from the other two pins, so they *emit* or *drain* the current that entered the transistor through the other two pins (regardless of current flow direction). The *collector* and *source* pins acquire the load current that is to be controlled by the transistor, so they *collect* or are the *source* of the load current (again, regardless of current flow direction).

  You may ask why both *BJT* and *FET* transistors are using different terminology for their pins when the three pins actually behave the same. And the answer is: they are *not* behaving *exactly* the same, and *BJT* and *FET* transistors internally are completely different devices. So their terminology derives from their internal architecture and design, and electrical engineers applaud that. 

  That said, for *practical* aspects and *hobbyist* level, it is perfectly ok to go by the simple "control pin" and two "load current" pins paradigm.
</details>

### Types: NPN, PNP, N-Channel, P-Channel

Transistors come in *N* and in *P* types. **FET** transistors are called *n-Channel* and *p-Channel*, whereas **BJT** transistors are called *NPN* and *PNP*. As with the pin terminology, you can simplify and consider just two fundamental types of transistors: **N-Type** (*NPN* and *N-Channel*) and **P-Type** (*PNP* and *P-Channel*):

* In **N**-type transistors, the **Emitter**/**Drain** (the one with the arrow in the symbol) is **n***egative*, the control pin is *positive*, and the current flows from control pin *and* **Collector**/**Source** to **Emitter**/**Drain**.
* In **P**-type transistors, the **Emitter**/**Drain** (again, the one with the arrow in the symbol) is **P***ositive*, the control pin is *negative*, and the current flows from **Emitter**/**Drain** to control pin *and* **Collector**/**Source**.

> [!TIP]
> **N-Type**, **N-Channel**, and **NPN** all are **n***egative* at their emitter (the pin marked with the arrow), and require a *positive* control signal   
> **P-Type**, **P-Channel**, and **PNP** all are **p***ositive* at their emitter (the pin marked with the arrow), and require a *negative* control signal   

> [!IMPORTANT]  
> The arrow in the transistor symbol *does not* generally indicate the direction of the current. Only for *BJT* transistors, the arrow  points into the direction of current. With *FET* transistors, the arrow points into the *opposite* direction however. The reason for this inconsistency again is historic: in *FET* transistors, the arrow points into the direction of *internal* electron flow.

Choosing between **N-Type** and **P-Type** transistors depends entirely on *where* you want to place the transistor in your schematics, and whether you want to control them with a positive or negative signal. 

#### Examples With BJT Transistors

Both schematics below do the same thing and control a load via a push button. The left schematic uses an **NPN** transistor, and the right schematic uses a **PNP** transistor:

<img src="images/pnp_npn_compare.PNG" width="80%" height="80%" />

* **N-Type** (*left circuit*): the **NPN** *BJT* transistor switches the load *on* when the *base* is connected to *positive* voltage. The current flows from *collector* to *emitter*. The *emitter* (the pin with the arrow) is **N***egative* (as in **N**PN or **N**-Type). A current limiting resistor makes sure the *base* current is not excessive.  
* **P-Type** (*right circuit*): the **PNP** transistor switches the load *on* when the *base* is connected to *GND* (0V). The current flows from *emitter* to *collector*. The *emitter* (the pin with the arrow) is **P***ositive* (as in **P**NP or **P**-Type). A current limiting resistor again makes sure the *base* current is not excessive. 

> [!IMPORTANT]  
> Note how the transistor in the right circuit is *flipped vertically*. In the *left* circuit, the *emitter* (marked with arrow) is on the *bottom* and connected to **GND**. In the *right* circuit, the *emitter* (marked with arrow) is on *top* and connected to the *positive* side.

#### Examples With FET Transistors

The same circuitry can also be designed with *FET* transistors:

<img src="images/mosfet_compare.PNG" width="80%" height="80%" />

> [!IMPORTANT]  
> Note how the transistor in the right curcuit is again *flipped vertically*. In the *left* circuit, the *source* (marked with arrow) is on the *bottom* and connected to **GND**. In the *right* circuit, the *source* (marked with arrow) is on *top* and connected to the *positive* side.

* **N-Type** (*left circuit*): the **N-Channel** *FET* transistor switches the load *on* when the *gate* is connected to *positive* voltage.  The current flows from *drain* to *source*. The *source* (marked with arrow) is **N***egative* (as in **N**PN or **N**-Type). Since *FET* transistors have a *high resistance* between *gate* and *source*, they do not require a current limiting resistor because there is no way a destructive current could flow anyway. Instead, since *FET*s are controlled by tiny *voltages* at their *gate*, the *gate* must now use a *pull down* resistor that connects the *gate* with **GND**. This keeps the *gate* from floating in an undefined state. So the *pull down resistor* safely pulls the *gate* to ground when there is no control signal.   
* **P-Type** (*right circuit*): the **P-Channel** *FET* transistor switches the load *on* when the *gate* is connected to *GND* (or a *lower* voltage than *source*). The current flows from *source* to *drain*. The *source* (marked with arrow) is **P***ositive* (as in **P**NP or **P**-Type). Again, the *gate* does not need a protective current limiting resistor. Instead, a *pull up* resistor is required to safely keep the *base* positive when the *FET* is supposed to be *off*.

<details>
  <summary>:information_source: Controlling FETs With Microcontrollers</summary><br/>

When you plan to control the *gate* of a *FET* transistor by a microprocessor, you *must* add a current limiting resistor between your digital output pin and *gate*. *FET* transistors have a *capacitance*, so they act like a *capacitor*. When you turn on the *MOSFET*, it can momentarily draw a huge current of up to a couple of Amperes that may easily destroy your digital output pin. A current limiting resistor in series protects your microprocessor output (not the *FET*).  
  
Also remember that *FET* transistors are *voltage*-controlled and need a given voltage difference between *gate* and *source*. The voltage difference required for a *FET* to become fully conductive (opened) depends on the *FET* specs. It is specified as **Vgs** or **Vth** in the transistor data sheet. 

If you (or your microcontroller output) cannot provide the required voltage, you need to add a *driver* for the *gate* - which in its simplest form is another transistor that connects *gate* with whatever voltage is required.

*Logic level FET*s are specifically designed to directly work with microcontrollers: their *gate*-*source*-voltage is within the voltage range of typical microcontrollers. If you must use *FET*s with higher voltage requirements, there are specific *driver ICs* available (i.e. **LTC7004**) that can drive *FET*s with *gate*-*source*-voltages of up to 60V.
</details>

> Commonly used **NPN** transistors are *2N2222*, *2N3904*, *TIP120*   
> Commonly used **PNP** transistors are *2N2907*, *2N3906*

# Identifying Legs and Terminals

Transistors of all types have three legs. Obviously, it is crucial to identify the correct terminals. 

> [!CAUTION]  
> The only *dependable* ways of determining the pins is either review the *data sheet* for the *particular transistor type* you want to use, or to physically *test* the transistor. Only very few transistors actually show distinct pin markings on their housing. 


> [!TIP]
> Many multimeters have built-in transistor test capabilities when you switch the dial to the *hFE* setting.
>
> You may even want to look into purchasing a dedicated transistor test device. They are available for around â‚¬20 and tell you exactly not just the pins but also the N- or P-type and many additional useful parameters.

<img src="images/tester.jpg" width="30%" height="30%" />


If you have neither a *component tester* device nor the data sheet, then there are a few rules of thumb though (use at own risk):

## Plastic Casing With Flat Side

*BJT* transistory typically come in a black plastic casing with one *flat* side which is the *front* side. To identify the pins, look at the flat side and keep the pins pointing downwards: from left to right, the pins are: *Collector*, *Base*, *Emitter* (remember "CuBE").

<img src="images/bjt_pins.PNG" width="50%" height="50%" />

> :warning: The default pin arrangement is not mandatory, and there are many exceptions to the rule. So always look up the transistor type you are using and verify the pin assignment in its data sheet!

## Metal housed "can" type

Pins are arranged circularly. There is a tab in the rim of the housing. Typically, the pin closest to the tab is *Emitter*, the opposite pin is *Collector*, and inbetween is *Base*.

> :warning: The default pin arrangement is not mandatory, and there are many exceptions to the rule. So always look up the transistor type you are using and verify the pin assignment in its data sheet!

### MOSFETs

<sup><sub>*(article:059353021812241121)*</sub></sup>
