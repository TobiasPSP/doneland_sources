<img src="/assets/images/light.png" width="80%" height="80%" />
 
# Limiting Current And Picking Appropriate Series Resistors

> Everything You Need To Know To Limit LED Current And Operate Them Safely

**LED** get destroyed immediately if you run them off normal power sources: their *very low* internal resistance would cause a short-circuit and in a blink of a moment burn the **LED** and destroy it forever.

To safely operate **LED**, you must limit the *current* supplied to the **LED**. There are two popular ways to do this:

* via a **Series Resistor** or a **Constant Voltage** power supply
* by using a **Constant Current** power supply

> [!NOTE]
> It is *only relevant* to supply the correct *current* to the **LED**: using a **constant current** power supply guarantees that.   
> Supplying a specific *voltage* to the **LED** (using a *series resistor* or a *constant voltage* power source) is *not really* providing a *constant* current:
> **LED** are not perfectly identical and can vary in *resistance*. Factors like *temperature* *further change* their *resistance*. All of this *affects the current* they receive when supplied by a *fixed voltage*. 


## Using a LED Series Resistor

For hobbyist projects, a *series resistor* is simple, cheap and typically sufficient. The resistor and the **LED** form a classic *voltage divider*: the **LED** gets the voltage necessary to drive the appropriate *current*.

> [!CAUTION]
> A *voltage divider* can only *lower* the input voltage. The input voltage must be *higher* than the *forward voltage* needed by the **LED**.

> [!NOTE]
> A *voltage divider* is a very *inefficient* way of reducing the *voltage*: excess energy is converted to *heat* and wasted. A *series resistor* should only be considered for *low power* indicator **LED**. 


### Calculating Resistor Value

The basic principle is a *voltage divider*: when you connect multiple resistors in series, the total voltage is *divided* across the individual resistors proportionally to their resistances.

In a *traditional* voltage divider, to calculate the required *resistance* you need to know the total *voltage*, the *required voltage* and the *load resistance*. 

That's a problem for **LED** because their resistance is typically not known (and can vary). So you need to calculate the resistance using alternate parameters. These values are needed:

* Required **LED** voltage
* Required **LED** current
* The *voltage* you want to apply to power the **LED**

Here are three approaches to find out the values needed for *your particular* **LED** to then calculate the approriate *resistance* for the protective *series resistor*:

#### ...When You Know The LED Specs

If you know the specs of your *particular* **LED** (taken from its data sheet or vendor information), you are all set. This is what you need to know: 

* Required **LED** voltage (its *forward voltage*), typically in the range of *1.5V-4.0V*
* Required **LED** current: for simple indicator **LED** typically in the range of *5-20mA*

#### ...When You Don't Know LED Specs

If **LED** type and specs are *unknown*, there are well-known *rules of thumb* based on **LED** color and materials **LED** are made of:

| Color | Forward Voltage | Material |
| --- | --- | --- |
|  blue | 3.0-3.6 | InGaN, SiC |
| green | 2.0-3.5 | GaP, AlGaInP, AlGaP |
| yellow | 1.8-2.2 | GaAsP, AlGaInP, GaP |
| orange | 2.0-2.1 | GaAsP, AlGaUInP, GaP |
| red | 1.6-2.0 |  AlGaAs, GaAsP, AlGaInP, GaP |

> [!TIP]
> *White* **LED** are made from *blue* **LED** and share their specs.    
> *Amber* **LED** can either be made from *orange* **LED** (and then share their specs), or can be also made from *blue* **LED** (in which case their specs are similar to those)   

Regarding *current*, low-power indicator **LED** typically need a *current* of *5-20mA*. Other **LED** may use drastically higher *currents*: High power *Cree* **LED** for use in flashlights and emergency vehicles typically need *1-2A*.

> [!TIP]
> Some **LED** like *green* ones have a large *voltage range*. Always start with the lowest *voltage*, calculate the *resistance* for it (below), and then test-drive. Measure the *current* with a multimeter. If it is much lower than the expected current, you now know that the **LED** uses a higher *forward voltage*, and you can lower the *resistance*.


### Identifying LED Specs by Testing

Probably the most interesting and precise way of identifying the specs of your **LED** is to *test* them. This exposes much of how **LEDs** truly work. For this you need:

* A *power supply* with *variable voltage* in the range of *1.5-4V*
* Optionally an Ampere-Meter (multimeter or clamp) in case your *power supply* does *not* show the *current*

#### 1. Preparation

Set the power supply to a definitely safe *voltage* like *1.5V*. 

Add an Ampere-Meter to one of the power supply outputs if the power supply has no *current* display.

Now connect the **LED** to the power supply. Turn on the power supply. The **LED** will typically not emit any light at this *low initial voltage*: it is *below* the **LED** forward voltage, so no *current* flows. 

#### 2. Raise Voltage Slowly

Now *slowly* raise the voltage and monitor both the *current* and the physical **LED**. You are about to witness the *physics of **LED***:

* **Phase 1: Current Increases Slowly** At first, when raising the *voltage*, the *current* will also raise, but *very slowly*. At some voltage, the **LED** starts to emit light. When you further increase the voltage, this will further increase the current. And the **LED** light emission will raise, too.
* **Phase 2: Current Increases Rapidly** At one point you will notice that suddenly the *current* will start to raise much more rapidly when you raise the *voltage*. Now, every tiny increase in *voltage* will result in an ever higher *current*. You are now entering the *danger zone* and have soon passed the safe area of **LED** forward voltage: the **LED** now cannot shine much brighter and starts to increasingly convert *input current* into *heat*: the **LED** gets *hotter* without emitting much more *light*.
* **Phase 3: Stop** You must now decide at which level the **LED** produces *enough* light for your purpose. To find the *sweet spot*, monitor the **LED** *temperature*: the **LED** can get *warm* but should *not get hot*. If it does, reduce the voltage. 


> [!TIP]
> **LEDs** perform better when operated at *50-70%* of their maximum possible current. At this *sweet spot*, they often *do not get hot*, do not need extensive *heat sinks*, and when you compare their *light yield*, they are close to their maximum light output anyway.    
> Raising the current any further just adds problems without much benefit. Should you indeed need *more light*, get a *higher rated LED*. 

#### 3. Read Results

Now you can read the values required to calculate the *resistance* from your power supply and Ampere-Meter: 

* **Required LED Voltage:** the **LED** forward voltage as shown by the power supply at this point. 
* **Required LED Current:** the **LED** current as shown by the power supply or your Ampere-Meter. 


### Calculating LED Resistor

Let's assume you want to power a normal *red* indicator **LED** off a *car battery*, and you *don't know* the exact values for your **LED*. Then this is the data to calculate with, taken from the *rules of thumb* table above:

* Total voltage: *13.8V* (controlled by you, can be any voltage *above* the **LED** voltage)
* Required **LED** voltage: *1.8V* (guessed, you may start with *1.6V* to be extra safe)
* Required **LED** current: *10mA* (guessed, you could probably go up to *20mA*)

#### How much voltage should the resistor remove?

The required *voltage drop* that the resistor should cause is then *your supply voltage - LED voltage* = *13.8V - 1.8V* = *12.0V*

#### Finding Out The Required Resistance

The required *resistance* is now calculated using *Ohms Law*: *12V / 0.01A (10mA) = 1.200 Ohm*. 

Round this value up to the next available resistor value you have. In this case, a *1.2KOhm* resistor would work.

## Using Constant Voltage

*Constant voltage* is the same as using a *series resistor*: you, too, supply the **LED** forward voltage to the **LED**(s).

Only in this case, you are using a *constant voltage* power supply instead of *dropping excess voltage* using a simple *voltage divider*.

> [!NOTE]
> *Constant voltage* power supplies are *much more efficient* than *voltage dividers* because they do not *waste* excess energy through *heat*. They are therefore suited even for *higher powered* **LED** and **LED strips**.    
> You would in turn never use a relatively costly *constant voltage* power supply to drive a single **LED**.


## Using Constant Current

The most fundamental *spec* of every **LED** is the *current* it needs. Using a *constant current* power supply is therefore the *best* way to drive **LED**.

*Constant current* power supplies are the most *complex* way of supplying power mentioned here which is why it is typically used for *high power* **LED** or **LED strips**, not for simple indicator **LED**.

> [!WARNING]
> *Constant current* power supplies automatically determine the *voltage* necessary to drive the requested *current*. They *adjust* the *voltage* automatically when resistances change, i.e. when **LED** get hot.
> A *constant current* power supply **can not lower the voltage arbitrarily** though: it has a certain *voltage range*.    
> For example, you can get a *700mA constant current* supply that has a *voltage range* of *30-38V*.
> This particular power supply would be *completely unsuitable* to drive a *single **LED** because it outputs *at least 30V*.   
> If you use **LED** with a *forward voltage* of *3.5V* each, though, you can connect *10 **LED** in series*. They now have a *total forward voltage* of *35V* which is well in the *voltage range* of the power supply.   
> The power supply would now drive the *10 **LED** and provide the *constant current* of *700mA* to each of the **LED** in your string.   



> Tags: LED, Resistor, Constant Current, Constant Voltage, Forward Voltage
