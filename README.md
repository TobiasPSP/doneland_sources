# Transistors - Practical Summary
Here you'll find a general introduction to **transistors**, focused on practical aspects and essentials. 

## Quick overview
Transistors are electronic switches. They can turn a connection *on* and *off*, but they can also *amplify* electrical signals. That's why transistors have a *third* connector which is used to control the behavior (turn on, turn off, amplify). This third "control" connector is called *base* or *gate*.

In circuit diagrams, transistors are represented by these symbols:

<img src="/Images/transistor_symbols.svg" width="50%" height="50%" />

The upper two symbols represent "classic* **BJT** transistors, the lower two symbols represent **FET** transistors. More on that below. 

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

Transistors come in *P* and in *N* types. This refers to the internal architecture. **MOSFET* transistors are called *p-type* and *n-type*, whereas **BJT** transistors are called *PNP* and *NPN*.

The most important practical difference is in how *N*- and *P*-types are controlled: the typical *N*-type transistors are controlled via a *positive* voltage, whereas the less common *P*-type transistors are controlled via a *negative* voltage.

The schematics illustrate the fundamental difference between *NPN* and *PNP* type transistors. Both schematics use a switch and a transistor to control a load:

<img src="/Images/pnp_npn_compare.PNG" width="50%" height="50%" />

**NPN**: the left schematic uses a **NPN** transistor which switches *ON* the load when the transistor *base* is connected to *Vcc* (positive voltage).

**PNP**: the right schematic uses a **PNP** transistor which switches *ON* the load when the transistor *base* is connected to *GND* (0V).

Here are some more observations to note:

* **NPN**/**n-type FET**: Current flows from *collector*/*source* to *emitter*/*drain*. This is the most commonly used type. Both *base*/*gate* and *collector*/*source* are connected to the **positive** voltage: the *load* controlled by the transistor is wired between **positive** voltage and *collector*/*source*. The combined current leaves the transistor through the *emitter*/*drain* which is connected to GND.
* **PNP**/**p-type FET**: Current flows from *emitter*/*drain* to *collector*/*source*. The positive voltage is connected to the *emitter*/*drain*, so the entire current enters the transistor through the *emitter*/*drain*. Both *base*/*gate* and *collector*/*source* are connected to the **negative** voltage. So by controlling how much current is "leaving" the base towards GND, you control how much current goes through the *load* which is wired between **GND**  and collector.



> Commonly used **NPN* transistors are *2N2222*, *2N3904*, *TIP120*
> Commonly used *PNP* transistors are *2N2907*, *2N3906*

