<img src="/assets/images/dam.png" width="80%" height="80%" />

# Transistors

> Switching Loads and Amplifying Currents

[Transistors](https://done.land/fundamentals/discrete/transistor) are versatile *semiconductors* that can act as both an *electronic switch* and an *amplifier*. There are two main families of transistors:

* **BJT (*Bipolar Junction Transistor*):**  
  * Analogy: potentiometer  
  * Three pins: *base* (control), *collector*, and *emitter* (the path for the load).  
  * The output is controlled via *current*, and the *base* requires a current-limiting resistor.  
  * Ideal for **amplification**.  
  * Best for switching low loads at low frequencies.  
  * Often (mis)used in DIY projects as "general-purpose transistors".  
  * Commonly found in the **TO-92** package: a small, plastic-encapsulated package with a flat side and three legs.  

* **MOSFET (*Metal-Oxide-Semiconductor Field-Effect Transistor*):**  
  * Analogy: electrical switch  
  * Three pins: *gate* (control), *source*, and *drain* (the paths for the load).  
  * The output is controlled via *voltage* (electrical field). The *gate* may need a resistor to protect the GPIO from *inrush current* when the MOSFET has relatively large capacitance.  
  * Ideal for **switching**, with fast switching speeds and the ability to handle very high frequencies.  
  * Often (mis)used in DIY projects as "general-purpose transistors".  
  * Commonly found in the **TO-220** package: a metal tab for heat dissipation, with three legs.

## Overview

*BJT* and *MOSFET* functionality overlap in many areas; however, both have distinct advantages and disadvantages. 

Beginners often use a random type of transistor for all applications, based on availability. 

Once you gain more experience, selecting the appropriate transistor type based on the use case can significantly improve the performance of your projects.

| Feature                          | BJT                                       | MOSFET                                              |
|-----------------------------------|-------------------------------------------|-----------------------------------------------------|
| **Used as Switch**                | < 500mA                                   | 100 mA - >10 A (much higher depending on type)      |
| **Maximum Switch Frequency**     | < 500 MHz <br/>*(charge storage effects)* | Up to 10 GHz                                        |
| **Used as Linear Amplifier**     | Ideal                                    | Requires careful biasing to operate in saturation region; noisier |
| **Handling**                      | Robust                                   | Can be damaged by ESD <br/>*(Electrostatic Discharge)* |
| **Signal Type**                   | Analog                                   | Digital                                             |
| **Power Consumption**             | Higher <br/>*(base current requirement)*  | Lower <br/>*(gate draws almost no current)*          |
| **Efficiency**                    | Less efficient                           | More efficient <br/>*(especially in power electronics)* |

### Typical DIY Use Cases

For rough orientation, these are typical use cases for both transistor families:

* **BJT Transistor Use Cases:**  
  * Experimentation  
  * Low-power DC switching  
  * Low-frequency circuits  
  * Current amplification (e.g., sensors)  

* **MOSFET Transistor Use Cases:**  
  * DC power switching (high loads, e.g., motors, heaters)  
  * High-frequency applications (e.g., digital interfaces, radio frequencies)  

### Common Mistakes

When using transistors in simple DIY circuits as proof of concept or for basic experimentation, both BJT and MOSFET types often work well.

However, once your projects involve higher currents or frequencies, selecting the *appropriate* transistor type can make the difference between success and failure.

For example, when transistors operate close to their thresholds, they can generate excessive heat and eventually be destroyed by overheating.

At lower currents, things may seem fine, but as the currents increase, problems begin to surface. 

Switching to a MOSFET with a low resistance (*Rds(on)*) at your switching voltage can easily resolve such issues.
## Polarity (P versus N)

Within both families, there are **N** and **P** types, denoting the *polarity* in which they can be controlled. For historical and technical reasons, both types are named differently across the transistor families:

* **BJT:** *NPN* vs *PNP*
* **MOSFET:** *N-Channel* vs *P-Channel*

Or put differently:

* **N** *(controlled by positive voltage):* *NPN*, *N-Channel*
* **P** *(controlled by negative voltage):* *PNP*, *P-Channel*

### Practical Guidance
From a purely practical (and simplified) perspective:

* Use **N** type (**NPN**, **N-Channel**):
  * Transistor should be **OFF** by default.
  * You want to use a **positive voltage** to control its *ON* state.
  * You want to use **ground** or a **negative voltage** to turn it *OFF*.
* Use **P** type (**PNP**, **P-Channel**):
  * Transistor should be **ON** by default.
  * You want to use a **positive voltage** to control its *OFF* state.
  * You want to use **ground** or a **negative voltage** to turn it *ON*.

> [!NOTE]
> This is a highly simplified list. The behavior of a transistor depends on more factors. With MOSFETs, for example, the *gate-source voltage* (**V_GS**) is the true key factor that determines whether it is *ON* or *OFF*.




> Tags: Transistor, BJT, MOSFET, Bipolar Junction Transistor, Metal-Oxide-Semiconductor Field-Effect Transistor, Amplifier, Switch, Electronic switch, TO-92, TO-220, TO-247, Rds(on), NPN, PNP, N-Channel, P-Channel

[Visit Page on Website](https://done.land/components/signalprocessing/transistor?418279041228244933) - created 2024-04-27 - last edited 2025-03-24
