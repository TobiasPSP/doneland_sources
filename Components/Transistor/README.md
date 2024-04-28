<img src="/assets/images/dam.png" width="80%" height="80%" />
 
# Transistors

> Switching Loads And Amplifying Currents

Transistors are versatile *semi-conductors* that can act both as an *electronic switch* or as an *amplifier*.


## Picking A Transistor

There is a vast variety of *transistors* available: they exist in different *technologies* (*BJT*, *MOSFET*, and more) and *configurations* (*P*- and *N*-type). So it is not *trivial*, especially if you are just starting, to *pick the right transistor* for a *given purpose*.

In this section, I break down transistors based on *what you want to **do*** with them. For each *use case*, you'll then learn *which particular transistor specs* you need to care about. You also get a list of *suitable transistor models* that you can pick.

> [NOTE:]
> If you are *fundamentally interested* in *how transistors work* and what their different *technologies* are, please visit the [Fundamentals Section](https://done.land/fundamentals/discrete/transistor).


## Use Cases

*Transistors* are very versatile and can be used for many different *use cases*. Each *use case* focuses on specific features of a *transistor*. To find the *best and most suitable transistor*, it all starts with your *intended use case*.


### Switching Loads

One of the most common *use cases* is using a *transistor* to switch big(ger) *loads*. Here, the *transistor* acts like an electronically controllable *switch*. Like with a *real* switch, there are technical specs to watch out for:

* **Voltage:** what is the *maximum voltage* you can switch? What is the *maximum isolation voltage* (the *reverse* voltage)?
* **Current:** how much electrical *power* do you want to switch? What are the maximum *currents* the switch needs to sustain?
* **On-Resistance:** when in *on* state, is the *transistor* really acting like a *closed switch* with next-to-zero *resistance*, or is there still a small *on-resistance* that may cause a *voltage drop* and produce *heat*?
* **Off-Resistance:** when in *off* state, is the *transistor* really acting like an *opened switch* with *no resistance*, or is there still a small *leaking current* that might cause a battery power supply to slowly drain?
* **Frequency:** in cases where you want to use the switch not just as a *replacement* for a *manual switch* (occassionally turning it *on* and *off*), the *maximum frequency* may become important as well: when you use the switch as part of a *PWM* (pulse width modulation) *dimmer* or inside a *switching DC-DC-regulator*, the switch is turned on and off many thousand times per second. Here, it is important to check that the *transistor* can actually switch this fast.

### Amplification

Another most common *use case* is *amplification*: you need more than just *on* and *off* and what to use the *transistor* like a *potentiometer*? Maybe you want to control the brightness of a lamp, or the speed of a motor.

When you *amplify*, the *transistor* continues to act like a *switch*: all considerations above continue to apply. In *addition* - since now the transistor can also have a *variable resistance* - these considerations become important, too:

* **Heat:** When a *transistor* is not *fully open*, it has a *resistance*, and when *current* flows through a resistance, *heat* is produced: how much *heat* does the *transistor* tolerate, and how much heat can it *dissipate*? In essence: *how much current* can you *amplify* without frying the *transistor* by *excessive heat*?


> Tags: Transistor, Choice, Selection, Heat, Amplifier, Switch