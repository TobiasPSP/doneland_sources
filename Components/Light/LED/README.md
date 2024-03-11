<img src="/assets/images/light.png" width="80%" height="80%" />
 
# LED (Light Emitting Diodes)

> LEDs Can Be Flexibly Shaped. They Produce Light In Any Color Efficiently, Last Forever and Cost Little

**LED**s (*light emitting diodes*) are *semiconductors* and indeed work like a *diode*. What's important about them though is their ability to turn electric power into light. This conversion is so efficient that *LEDs* typically do not produce heat (although high powered LEDs can), and they are said to emit "cold light".

On this page you get a comprehensive *overview* about **LED** fundamentals and common **LED** options. Whenever there are more details to know, a *link* takes you to a separate article.

## Delicate And Simple to Destroy

Although **LEDs** themselves are rugged and can last much longer than most other light sources, there is one peculiarity about **LEDs** that can get them easily destroyed:

They have a very low internal *resistance* so when you power them directly, a *large current* flows. Whenever the current is larger than the energy the **LED** can turn into *light*, the remaining energy is converted to *heat*. This heat can build up momentarily and destroy the **LED** in a blink of a moment.



That's why it is mandatory that you control the *current* that passes a **LED**. Here are the options:

* **Resistor:** most commonly in hobbyist projects, an appropriate *resistor* is connected *in series* to the **LED**. The resistor and the **LED** form a *voltage divider*, so the **LED** gets exactly the voltage necessary to drive the appropriate *current*.
* **Constant Voltage:** if you connect the **LED** to *exactly the right voltage* (its so-called *forward voltage*), this, too, drives the appropriate *current*, and no resistor is needed. 
* **Constant Current:** the best way to drive a **LED** is by providing a *constant current* in the first place and not use *voltage* to *guess it*. Many voltage regulators support this setting, and there are specialized **LED** drivers for set constant currents.


> [!NOTE]
> All that matters to a **LED** is the *current* you provide. The *voltage* is just *driving* this current. Using a resistor or a *constant voltage* works in most cases but is not providing a *constant* current: when the **LED** gets warmer during operation, its internal *resistance* changes, and when the *voltage* stays constant, the *current* changes. With a *constant current* power supply, the power supply would immediately notice that due to the temperature and resistance change, the *current* rises, and automatically correct this by *lowering the voltage*.

### Using Constant Voltage

*Constant voltage* at first seems like an edge case because the forward voltage of **LEDs** typically is in the range of *1.8V-4V* which is not the typical voltage of off-the-shelf power supplies.

*Constant voltage* starts to make more sense when you connect multiple **LED** *in series*: now the required voltage is the *sum of all forward voltages of all connected **LED**. When you connect four **LED** in series, the *constant voltage* supply is more in the range of *12V*.

I am not digging deeper into *constant voltage* as it merely is the process of calculating the **LED** forward voltage(s) and then connecting a power supply with this voltage.

### Using the Correct Resistor Value

In simple hobbyist projects, adding a *resistor* *in series* to the **LED** is the most common approach because it is simple, cheap, and reasonably safe.

> [!TIP]
> Keep in mind that *resistors* used to drop the voltage are very inefficient. The portion of the energy that you want to get rid off is converted to *heat* by the *resistor*. For small *indicator **LED***, the wasted energy is small though.

The basic principle is a common *voltage divider*: when you connect multiple resistors in series, the total voltage is *divided* across the individual resistors proportionally to their resistances.

In a *traditional* voltage divider, you need to know the total *voltage* and then the *required voltage* and the *load resistance*. That's a problem in most cases because the **LED** resistance typically not known.

#### Using Known LED Specs...

Alternatively, you need to know the total *voltage* and then the *required voltage* and the *required current*. That's better: if you know your **LED** type you can look up these values in the data sheet.

#### ...or Using Educated Guesses...

If you don't know the specific **LED** type or don't have the data sheet at hand, there are well-known rules of thumb based on the **LED** color and the materials used to create these:

| Color | Forward Voltage | Material |
| --- | --- | --- |
|  blue | 3.0-3.6 | InGaN, SiC |
| green | 2.0-3.5 | GaP, AlGaInP, AlGaP |
| yellow | 1.8-2.2 | GaAsP, AlGaInP, GaP |
| orange | 2.0-2.1 | GaAsP, AlGaUInP, GaP |
| red | 1.6-2.0 |  AlGaAs, GaAsP, AlGaInP, GaP |

> {!TIP]
> *White* **LED** are typically made from *blue* **LED** and share their specs.    
> *Amber* **LED** can either be made from *orange* **LED** (and share their specs), or can be also made from *blue* **LED** (in which case their specs are similar to those)

Low-power indicator **LED** typically use a *current* of *5-20mA*. Other **LED** may need drastically different *currents*. High power *Cree* **LED** used in flashlights and emergency vehicles typically use *1-2A*.

Let's assume you want to power a normal *red* indicator **LED** off a *car battery*, then this is the data to calculate with:

* Total Voltage: *13.8V*
* Required Voltage: *1.8V* (guessed, you may start with *1.6V* to be safe)
* Required Current: *10mA* (guessed, you could probably go up to *20mA*)

The required *voltage drop* of the resistor is then *13.8V - 1.8V* = *12.0V*

According to *ohms law*, you can now calculate the resistance: *12V / 0.01A (10mA) = 1.200 Ohm. Round this value up to the next available resistor value you have. In this case, a 1.2KOhm resistor would work.

#### ...or Testing the LED

Yet another approach is the technically most interesting as it exposes much of how **LEDs** truly work. What you need for this is a *power supply* with *variable voltage* in the range of *1.5-4V*, and an Ampere-Meter.

> [!TIP]
> If you have a *power supply* with a *variable voltage* but the voltage range does not fit, you can connect multiple **LED** in series to *raise* the required voltage. Connect *two* **LED** for a voltage range of *3-8V*, or *three* **LED** for a range of *4.5-12V*. In the following text I am assuming *one* **LED**. Adjust the mentioned voltages below accordingly.

If the power supply does not show the *current*, add an Ampere-Meter to your setup, either by connecting an appropriate multimeter in series, or by using a clamp meter.

Set the power supply to a definitely safe *voltage* like *1.5V*, then connect the **LED** to the power supply and turn it on. Most likely, the **LED** will not emit any light at this *voltage*. 

Now *slowly* raise the voltage and monitor both the *current* and the physical **LED**. You are about to witness the *physics of **LED***:

* **Phase 1: Current Increases Slowly** At first, when raising the *voltage*, the *current* will also raise, but *very slowly*. At some voltage, the **LED** starts to emit light. When you further increase the voltage, this will further increase the current. And the **LED** light emission will raise, too.
* **Phase 2: Current Increases Rapidly** At one point you will notice that suddenly the *current* will start to raise much more rapidly when you raise the *voltage*. Now, every tiny increase in *voltage* will result in an ever higher *current*. You are now entering the *danger zone* and have soon passed the safe area of **LED** forward voltage: the **LED** now cannot shine much brighter and starts to increasingly convert *input current* into *heat*: the **LED** gets *hotter* without emitting much more *light*.
* **Phase 3: Stop** You must now decide at which level the **LED** produces *enough* light for your purpose. To find the *sweet spot*, monitor the **LED** *temperature*: the **LED** can get *warm* but should *not get hot*. If it does, reduce the voltage. 

Now you can read the values from your power supply and Ampere-Meter: 

* **Required Voltage:** the **LED** forward voltage as shown by the power supply. Let's assume *3.1V*
* **Required Current:** the **LED** current as shown by the power supply or your Ampere-Meter. Let's assume *12mA*

All you need to add is the intended *voltage* you later want to use to operate the **LED**. Let's assume you want to operate it from a **5V** GPIO in your *Arduino* project:

The required *voltage drop* of the resistor is then *5.0V - 3.1V* = *1.9V*

According to *ohms law*, you can now calculate the resistance: *1.9V / 0.012A (12mA) = 158.3 Ohm*. Round this value up to the next available resistor value you have, for example *180Ohm*.


> [!TIP]
> **LEDs** perform better when operated at *50-70%* of their maximum possible current. At this *sweet spot*, they often *do not get hot*, do not need extensive *heat sinks*, and when you compare their *light yield*, they are close to their maximum light output anyway. Raising the current above just raises the problems. If you indeed need *more light*, get a *higher rated LED*. After all, you wouldn't drive your car constantly at full speeds either.



## Standard Hobbyist LEDs

Anyone in electronics has come across the classic standard LEDs that typically come in two diameters: 3mm and 5mm:

<img src="images/led_normal_back_t.png" width="50%" height="50%" />

The picture shows already wired **LED**, and you can identify the *resistor* that was added to one leg of the **LED**. These **LEDs** were already tailored to work with a specific voltage.

*Indicator* **LED** exist in many different shapes and forms and can also be *square*, *clear* or *fogged*. They all work the same.

### Anode and Cathode

It is important to connect **+** and **-** to the correct "legs" of the **LED**. With most **LED**, one "leg" is *shorter* than the other.

* **Anode (+):** the **longer** leg is connected to the *anode* and needs a *positive* voltage
* **Cathode (-):** the **shorter** leg is connected to the *cathode* and needs a connection to *ground*

<img src="images/led_square_many_top_t.png" width="50%" height="50%" />


> [!TIP]
> You can identify the *anode* even when **LEDs** are already *wired* or the "legs" have been shortened, and you cannot see the original difference in length anymore.    
> Look inside the **LED** head: you'll identify a *wider* metal part, and a relatively *short* one. The *short* one belongs to the *anode* (**+**)




> Tags: LED, Light, Anode, Cathode

:eye:&nbsp;[Visit Page on Website](https://done.land/components/light/led?198478031411241041) - last edited 2024-03-11
