# Transistors - Practical Summary
Here you'll find a general introduction to **transistors**, focused on practical aspects and essentials. 

## Quick overview
Transistors are electronic switches. They can turn a connection *on* and *off*, but they can also *amplify* electrical signals.

In circuit diagrams, transistors are represented by a set of similar symbols:

<img src="/Images/transistor_symbols.svg" width="50%" height="50%" />

> Here are a couple of common use-cases:
> - Classic switch: pressing a button tells the transistor to switch on or off an electrical connection. The transistor needs only a very small current to tell it what to do, so the physical switch in this scenario could be a cheap push button that only is capable of switching a few mA. Depending on the transistor type, it can then switch loads of many Ampere.
> - Fast switching: in contrast to physical switches, transistors can switch very fast, many thousand times per second and more. If you use a microprocessor such as *Arduino* or *ESP*, you can turn a transistor on and off many times per second, effectively adjusting the power that it lets through. This principle is known as *PWM* (*pulse width modulation*). It is used i.e. to dim a LED or control motor speed.
> - Amplification: A transistor is not a strict *on*/*off*-switch. Rather, the "strength* of the signal you are sending determines how much power it lets through. For a classic *on*/*off*-switch, you'd send zero or full power. However, you can also use any level inbetween and gradually change the amount of power it lets through. This way, a tiny modulated input signal gets *amplified* to a much stronger output signal with the same amplitude.

### Transistor Families

Transistors internally use different architectures:

* **MOSFET**: 99.9% of all transistors today are of this type. MOSFETs change conductivity based on the applied voltage, and *Power MOSFETs* can control extremely high currents. MOSFET input impedance (resistance) is *high*. They act as voltage-controlled variable resistors.
* **BJT**: they used to be the most widely used transistors decades ago. BJT input impedance is *low*. They are often used to amplify current. Although *BJT* transistors are still used, their future is uncertain, and they may eventually be completely replaced by *MOS* type of transistors.
* **Other**: there are plenty more transistor types for special purposes that are not discussed here.


### Wiring

Transistors typically have three connectors:

* **Base**/**Gate** (Control): this is the control input that tells the transistor how much power it should let pass through. 
* **Collector**/**Source** (Input): this is "collecting" the electrical power you want to control, so here is the *source* of the power. It is the **positive lead**.
* **Emitter**/**Drain** (Output): this is where the current "leaves" the transistor (gets *emitted* or *drained*). Both the *base* and the *collector* current leaves the transistor via the *emitter* pin. This is the **negative lead**. 

> The terms *base*, *collector*, and *emitter* are used with *BJT* type transistors whereas the terms *gate*, *source*, and *drain* are used with *FET* type transistors. Regardless, their purpose is similar.

### Types

Transistors come in *P* and in *N* types. This refers to the internal architecture. **MOSFET* transistors are called *p-type* and *n-type*, whereas **BJT** transistors are called *PNP* and *NPN*.

* **NPN**/**n-type FET**: Current flows from *collector*/*source* to *emitter*/*drain*. This is the most commonly used type. Both *base*/*gate* and *collector*/*source* are connected to the **positive** voltage: the *load* controlled by the transistor is wired between **positive** voltage and *collector*/*source*. The combined current leaves the transistor through the *emitter*/*drain* which is connected to GND.
* **PNP**/**p-type FET**: Current flows from *emitter*/*drain* to *collector*/*source*. The positive voltage is connected to the *emitter*/*drain*, so the entire current enters the transistor through the *emitter*/*drain*. Both *base*/*gate* and *collector*/*source* are connected to the **negative** voltage. So by controlling how much current is "leaving" the base towards GND, you control how much current goes through the *load* which is wired between **GND**  and collector.

> Commonly used **NPN* transistors are *2N2222*, *2N3904*, *TIP120*
> Commonly used *PNP* transistors are *2N2907*, *2N3906*

