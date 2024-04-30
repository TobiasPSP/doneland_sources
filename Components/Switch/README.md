<img src="/assets/images/switch2.png" width="80%" height="80%" />
 
# Switch

> All About Mechanical And Electric Switches To Turn On And Off Power 


*Switches* are needed to turn electrical power *on* and *off*. In essence, a switch is a component that can control *electrical conductivity* and produce a *very high* resistance (when in *off* state) as well as a *very low* resistance (when in *on* state).

The simple *mechanical switch* is just *one* example for this, and there are many different technologies and strategies.

## Mechanical Switches And Buttons

In a *mechanical switch*, two pieces of wire are either *connected* or *moved away from each other*, using *air* as insulation: the electrical circuit is *closed* or *opened*.

### Switches...

Mechanical switches can either be *normally open* (*NO*) or *normally closed* (*NC*), and when the switch is operated, it permanently switches from one state to the other and stays there.

### ...and Buttons

*Buttons* (more correctly *push buttons*, or *momentary* push buttons) have a much simpler mechanical construction: the connection is closed only while you *push* the button, and once you release it, the electrical connection is opened again. 

> [!NOTE]
> *Latched* buttons look like *momentary* buttons but have clever mechanical constructions that keep them in either state after being pushed. Electrically, they behave like a *switch*.


## Electrical Switches

Often, switches need to be *electrically controlled* from the distance. There are a number of good reasons for this:

* **Power:** *mechanical switches* quickly become bulky when they are designed to switch large loads. Such switches do not fit nicely into an operating panel. It is also not very practical having to use expensive and heavy wires to connect the load to a switch that may be far away from the actual load.
* **Safety:** electric power can be dangerous both with high *voltage* and high *currents*. It is not a good idea to deliver dangerously high energy in close vicinity to an operator.

### Relais

The classic approach is to use an *electro-magnetic relais*: when a small current is applied to a *coil*, a *magnetic field* is produced and *physically moves* a piece of metal so that a separate heavy-duty switch is operated. 

*Relais* use *two electrically separated* circuits: the *control circuit* that operates the *coil* can use safe low voltages and needs just a few milliamperes of current. The *load* is switched via a *separate* circuit that uses an iron *latch* that can be moved by the magnetic field.

> [!NOTE]
> A *reed relais* is a special *miniaturized* type of *relais* with *no coil* (external magnet required). In *home alarm systems* it is i.e. used to detect the opening of a *window*: a permanent magnet is mounted on the moving side of a *window frame*, and the *reed relais* is fixed to the other side.

### Transistor

A *transistor* is a semiconductor switch with no moving parts. It can turn *DC* circuits *on* and *off*. It *does not separate* control and load circuits from each other, though.

### Thyristor

A *thyristor* is a semiconductor switch with no moving parts, much similar to a *transistor*. It is designed for *AC* though and can be used to turn *AC* power *on* and *off*.

### Optocoupler

An *optocoupler* is a semiconductor designed to *electronically* separate the *control* from the *load* circuit, much similar to a *mechanical relais*.

An *optocoupler* uses a built-in *LED* instead of a *magnetic field*: when the *operator* applies power to the *optocoupler*, the internal *LED* starts to light up. Adjacent to it, a *photo-sensitive transistor* picks up the light. This current lowers the *transistor resistance* and *closes* the *second* and *completely electrically separated* circuit.

### Solid State Relais (SSR)
*Mechanical relais* are robust but have certain disadvantages: due to their moving parts they can fail over time. Their *coil* produces a magnetic field that can interfere with other electronic parts and produce unwanted large spikes of high voltage in reverse direction when turned off (due to the collapse of the magnetic field). The *coils* in a *magnetic relais* require relatively much electrical power to produce a magnetic field strong enough to operate the switch, and this power consumption is required all the time during which the *relais* is *closed*. Finally, since a *relais* internally uses a classic switch, you can *hear* the *relais* when it is operated, and this noise can be loud and irritating.

#### Solid State 
With the advent of readily available and powerful semiconductors, the functionality of a *mechanical relais* can be achieved with solid-state technology (without moving parts and without magnetic fields) in a much more efficient way.

*Solid State Relais* typically use *optocouplers* to safely *separate the control signal* from the *load circuitry*. The switching of the load is then taken care of by powerful *transistors* or *thyristors*, depending on the use case.

#### Types of SSR

Here are the common types of *SSR*:

* **DA: DC controls AC** Most common: a low *DC* current controls an *AC* load. Internally, this type uses *thyristors* to switch the *AC* load.
* **DD: DC controls DC** Same as *DA*, except this *SSR* controls a *DC load* and uses *transistors* for switching.
* **AA: AC controls AC** In *DIY* rather uncommon: an *AC* control signal controls an *AC* load.


> Tags: Switch, Button, Latched, Momentary, Push Button, Relais, Transistor, Thyristor, SSR, Solid State Relais, Optocoupler