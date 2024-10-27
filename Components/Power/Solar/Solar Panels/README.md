<img src="/assets/images/sun.png" width="100%" height="100%" />

# Solar Panels

> Turning Sunlight Into Electicity

*Solar panels* (aka *photovoltaic modules*) consist of thin layers of *polycristalline* or *monocrystalline* silicon.


<img src="images/solar_poly_small_overview_t.png" width="50%" height="50%" />

## Overview
Solar panels can come in almost any size and shape, and each solar panel has a specific *voltage* that it can deliver in full sunshine. On the market, a rich variety of *solar panels* exist with  *different maximum voltages*, catering your needs. For *DIY projects*, *solar panels* with *3V*, *6V*, *9V*, *12V*, and *24V* are common. Larger systems designed to power an entire household often use *18V panels*.

In reality, solar panels can deliver *any voltage* as long as it is a multipiler of *0.5*. That's because *any solar panel* regardless of size, shape, or voltage, uses the *same basic solar cells*. These units always have a voltage of around *0.5V*, and in direct sunlight, these units can deliver only a tiny current. When you look closely at a solar panel, you may be able to identify these units as a uniform "pattern*.

### Material and Efficiency
Solar cells are made from silicon, a semiconductor. There are two common ways of producing it:

* **Polycrystalline:** cheaper to produce, less efficient
* **Monocrystalline:** more expensive to produce, better efficiency

Here is a comparison:

| Temperature (°C) | Polycrystalline Efficiency | Monocrystalline Efficiency |
|------------------|---------------------------|----------------------------|
| -10              | ~17.5% - 20.5%            | ~20% - 23%                 |
| 0                | ~16.5% - 19.5%            | ~19% - 22%                 |
| 10               | ~15.5% - 18.5%            | ~18% - 21%                 |
| 20               | ~14.5% - 17.5%            | ~17% - 20%                 |
| 30               | ~13.5% - 16.5%            | ~16% - 19%                 |
| 40               | ~12.5% - 15.5%            | ~15% - 18%                 |

>  [!TIP]
> When planning a solar system, *available space* is an important parameter: if space is not an issue, then *cheaper but less efficient polycrystalline panels* may be the better choice, because although they are less efficient than more expensive monocrystalline panels, you may compensate this easily by adding one or more panels at the same cost.

### Identifying Fake Offers
Solar panels have become very affordable, yet it is often very hard to compare offers and find the best deal: the technical specifications claimed by sellers are often outright phantasy, and without knowing the true specs, it is impossible to compare products. Frequently, you'll come across **300W** solar panels at suspiciously low prices (or small sizes). Rogue vendors cannot bend *physics* though. Before purchasing, do the *physics plausibility check*:

* **Same Material:** although there may be subtle differences, overall all solar panels use roughly the same silicon material. This material has a defined yield of *0.015-0.023W/cm2* (harvested energy per area)
* **Same Sunlight:** sunlight delivers roughly 1kW of energy per square meter (*1000W/m2*) on a clear day at solar noon in the summer. That's *0.1W/cm2*. 
* **Efficiency:** even though sellers would like you to believe their panels were substantially more efficient than panels from other sources, these sellers are not known for having won the *Nobel Prize* lately. Chances are the conversion efficiency of their panels is anywhere between *15-23%*. So these panels produce *0.015W-0.023W/cm2*.

So when you know the *size of the active solar panel area* (*height x width* less aluminum frames), you can estimate the wattage with this formula: *Area* x *Solar Input* x *Efficiency* = *Watts*.

Let's assume the vendor sells a *monocrystalline panel* with a size of *90x50cm*. According to the table above, you can assume a conversion efficiency of around *20%* at *20C*. The area is *90x50cm=4500cm2": 

***4500**cm2* x *0.1W/cm2* x ***20**%* = ***90**W*

Should the vendor claim his panels deliver *300W*, then you now know that's out of the question.

<details>
  <summary>Example Check</summary>

The same goes for small DIY panels. Let's take a look at these *polycrystalline* mini solar panels. They have a size of *53x30mm*:


<img src="images/solar_poly_small_front_t.png" width="50%" height="50%" />

### Test 1: Polycrystalline Panels

The vendor claims these cells produce a current of *30mA* at *5V* (*0.03A x 5V = 0.15W*). Their surface is *5.3cm x 3cm = 16cm2*. Being *polycrystalline*, their *efficiency* is at the low end and can be estimated at *15%*.

Here is the plausibility check: physically, these panels should be able to produce this:

*Area* x *Solar Input* x *Efficiency* = *Watts*
*16cm2* x *0.1W/cm2* x *15%* = *0.24W*

The irritating result: that is *too much*, actually *much more* than the vendor claimed. 


#### Identify The Active Area

The unexpected result illustrates how important it is to look at the *relevant* dimensions: while the total physical size of the panel is indeed *5.3cm x 3cm*, the *effective* light-converting area is much smaller: *4.5cm x 2.3cm* = *10cm2*.


<img src="images/solar_poly_small_measure_t.png" width="50%" height="50%" />

Let's repeat the math with the corrected surface area:

*10cm2* x *0.1W/cm2* x *15%* = *0.15W*

A *0.15W* yield is exactly what the vendor claimed.

### Test 2: Monocrystalline Panels

*Monocrystalline* panels have a *higher efficiency* (up to *23%* compared to *15%*). They cost more, too. Let's test plausibility for this larger *monocrystalline* panel:


<img src="images/solar_panel_mono_6v_3w_top_t.png" width="50%" height="50%" />

The vendor claims this panel delivers *3W* at *5V*. The panel size is *12.1cm x 12.5cm*, and on closer inspection, there is a *6.4mm inactive rim* on both sides:



<img src="images/solar_panel_mono_6v_3w_inactiverim_t.png" width="50%" height="50%" />

The *12.5cm* physical width of the panel is thus reduced by *2 x 0.64cm* to *11.2cm*, providing an active area of *12.1cm x 11.2cm*: *135.5cm2*.

#### Performing Plausibility Check

Let's do the math again. This time, a *23%* efficiency is used as it is claimed to be a *monocrystalline panel* (plus the vendor explictly claimed a *23%* efficiency):

*135.5cm2* x *0.1W/cm2* x *23%* = *3.11W*

This panel (and this vendor) passed the plausibility check.

> [!NOTE]
> Whether or not the panel in fact yields the full energy calculated is a separate question. The plausibility check uncovers vendor specs that are physically impossible, i.e. a "200W panel" for less than EUR 10.00 and sized 20x20cm. Only practical testing can verify the claimed panel *efficiency*.



</details>



### Solar Panel Construction
Large solar panels consist of any number of these basic solar cells. The bigger the solar panel is, the more fundamental solar cells are combined. The way how these cells are internally connected determines the voltage of the panel:

* **Parallel:** voltage does not change, current doubles
* **Series:** current does not change, voltage doubles

That explains why Solar Panel voltages are typically multiples of *0.5V*:

* **DIY Solar Cells:** in small DIY projects, very small solar panels with a voltage of *6V* are used. Internally, such cells must consist of at least *12 solar cells*, connected in series. If it is a larger solar panel with more power output, multiple *strings* of 12 cells each are connected in parallel to each other, increasing the current.
* **Household Systems:** on larger scale, solar panels often have a voltage of *18V*, so these panels use strings of 36 solar cells to achieve this voltage.

## How Sunshine Turns Into Electricity
*Solar cells* are typically made of *silicon* which is a semiconductor. When photons hit its surface, this dislodges electrons which in turn create a flow in electric charge. 

Normally, these dislodged electrons would move in random directions and not produce a usable current. By special treatment, *solar panels* make sure the dislodged electrons move in the *same* direction, producing an electrical *current*.


<img src="images/solar_panel_mono_6v_3w_back_t.png" width="50%" height="50%" />

## Serial and Parallel Connections
You do not necessarily

## Choosing A Good Panel

There is a huge variety of *solar panels* to choose from. With the following quick guide you can effectively *compare* different panels and identify the one that works best for you at the lowest price.

It's a two-step process:

* **What Is Needed?** First, make up your mind *what you actually need*: what should be the *solar panel voltage*, and what are your *power requirements* and *space constraints*.
* **Choose Model:** Once you know the *solar panel voltage* and the *maximum area* you have available, compare different models in an educated manner to find the best and most cost effective solution.


<img src="images/solar_poly_small_back_t.png" width="50%" height="50%" />


### Panel Voltage

*Solar panels* can come with a variety of maximum output voltages. This solely depends on how the vendor has connected the internal basic solar cells.

The first decision for you should always be: what is the *solar panel voltage* that you need. As a rule of thumb, the voltage should be as close as possible to the voltage you actually require. *DC-DC voltage conversion* is most efficient when the raw input voltage and the fixed output voltage are close to each other.

So if you plan to power a *microcontroller*, a *5-6V* panel is best. If you'd rather like to charge your car battery or a power bank, then a *24V* panel might be best (as it can easily power the high performance *20V USB charging standard*).

> [!CAUTION]
> In any case, *never* use the *solar panel output voltage* **directly** to power devices. Solar panels deliver an inconsistent, raw and strongly *fluctuating* voltage that can be dangerous and destroy electronics if applied directly. Always use a *charger module* to convert the raw solar voltage to the desired fixed output voltage!


### Solar Panel Size
There is an easy rule of thumb for solar panels: *size (area) rules*. 

As you have seen, the active area of a panel is the most important factor determining the power you can get.

> [!TIP]
> You can *connect multiple smaller panels* to *one large active area* yourself, too: just connect the panels *in parallel* to not change their total voltage. By connecting multiple smaller panels **in parallel** (using panels with **identical nominal voltage** each!), you may be more flexible in where to place the panels, and at which angle. What matters is the *total active panel size*, regardless of whether it's one piece or a bunch of smaller ones.





#### Oversizing: Cost Effective

*Oversizing* a panel can compensate many other flaws, such as *less efficient panel technology*, *less efficient charger technology*, *less that ideal location for the panel* in respect to sun intensity.

> [!TIP]
> Rather than spending extra money on high efficiency components such as *super-efficient panels* or *super-efficient MPPT solar chargers*, this money is often spent more effectively in purchasing a larger solar panel.



#### Space Constraints
If *space constraints* or *design issues* impose a hard limit on the maximum solar panel size you can use, then tweaking *panel efficiency* and/or *charger efficiency* can compensate this.

> [!TIP]
> Compensating space constraints has its price: more efficient panels and more efficient DC-DC converters in total are more expensive than a larger cheap panel.





#### Compensating Via Panel Efficiency

*10cm2* space can be reduced to *6.5cm2* by switching a *polycrystalline panel* with a *monocrystalline panel*:

*10cm2* * *0.015W/cm2* / *0.023W/cm2* = *6.5cm2*

A *polycrystalline panel* has a *15%* efficiency (yielding *0.015W/cm2*) whereas a *monocrystalline panel* has a *23%* efficiency, yielding *0.023W/cm2*. 


#### Compensating Via Charger Efficiency
Post-processing the raw *solar panel voltage* consumes energy. The *efficiency* of *DC-DC converters* vary greatly and can *eat up all your other efforts* or - when done correctly - provide great optimization potential.


The raw *solar panel voltage* needs to go through a *DC-DC converter* to turn it into a stable fixed output voltage. This is often combined with *charger technology* and a *buffer battery*.

All of this can be performed with efficiencies in the range of *50-90%*, depending on technology used:

* **Solar panel voltage:** Choosing a solar panel with a maximum output voltage close to the intended fixed voltage improves the efficiency of *DC-DC converters*. Converting a *24V solar panel* to *5V USB power* is far less efficient than using a *12V* or *9V* panel.
* **MPPT:** Specialized *MPPT converters* (*Maximum Power Point Tracking*) take into account that solar panels have a *sweet spot* (a *current*) at which they deliver the most energy. *MPPT* converters control the *current* they draw from the panel to optimize and improve *solar panel efficiency*.
* **Linear vs. Switched Regulators:** *Linear* converters (regulators) are much less efficient: they dissipate extra energy as heat. *Linear converters* exist just because they are cheaper, and in many scenarios *efficiency* is not important. Slightly more expensive *switched* converters utilize *significantly more* of the input energy and are much more efficient.

### Cost Optimization

Once you know the *solar panel voltage* and roughly the *size* of the *solar panels*, you can now search for deals and compare models.

To identify the best buy, rate the panels by *cost per watt*.


#### Cost per Watt


Let's calculate *cost per watt* fro the two quite different panels from above. 


<img src="images/solar_panel_mono_6v_3w_front_t.png" width="50%" height="50%" />


* **Small, cheap, less efficient:** these panels were purchased in a *10 pack* for a total of *EUR 2.38*. Each panel cost *EUR 0.24* and yielded *0.15W*. That is *EUR 0.24* / *0.15W* = *EUR 1.60/W*.
* **Larger, more expensive, more efficient:** these panels were purchased as *5 pack* for a total of *EUR 14.99*. Each panel cost *EUR 3.00* and yielded *3W*. That is *EUR 3.00* / *3W* = *EUR 1.00/W*.



<img src="images/solar_poly_small_wrapped_t.png" width="50%" height="50%" />



If you had to choose between the two panel models above, the *cost per watt* calculation would clearly favor the more expensive and larger *monocrystalline* board which yields the same energy for *37.5% less cost*:

*100%* - (*EUR 1.00* x 100 / *EUR 1.60*) = *37.5%*


## Final Thoughts

A few practical facts:

### No Covers Please

Often, small *DIY solar panels* are protected by a thin plastic cover. Make sure you remove this before use, and make sure you do not place anything else inbetween the solar panel surface and the sunlight (i.e. a plexiglas cover, etc).


<img src="images/solar_poly_small_wrapped2_t.png" width="50%" height="50%" />

*Solar energy* can be *very powerful* when it can reach the *solar panel*. Most materials - even when they appear *transparent* to the human eye - *filter out* a great portion of the energetic light spectrum, severely impacting the solar panel efficiency.

### Solar Panels Inside The House

It makes no sense whatsoever to use *solar panels* inside the house. Only *natural sunshine* provides the raw energy needed to produce significant currents.

Even on a cloudy day, *solar panels* work surprisingly well outside. Inside, and with artificial light, they are useless.

> [!NOTE]
> That's actually a good thing: it illustrates *how efficient*  artificial light sources have become: light is emitted only in the *visible* spectrum. *Infrared* and *ultraviolet* ranges not visible by the human eye are filtered out. Coincidentally, these are the ranges that transport the most energy to *solar panels* which is why - for them - it is always pitch dark inside.   




> Tags: Solar Panel, Silicon, Monocrystalline, Polycrystalline, MPPT,

[Visit Page on Website](https://done.land/components/power/solar/solarpanels?150501051702244054) - created 2024-05-01 - last edited 2024-05-01
