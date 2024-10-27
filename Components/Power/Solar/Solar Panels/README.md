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

You do not necessarily need to buy solar panels that deliver exactly the voltage you need: by combining multiple solar panels, you can design your own systems and tailor voltage and current to your needs. You are essentially *continuing* to do what the solar panel did internally anyway. Remember? Each solar panel internally consists of many fundamental solar cells that are, too, connected in series and in parallel to produce the desired panel voltage.

By connecting solar panels in series and/or in parallel, you can continue this design process, and optimize the system for your needs.

> [!IMPORTANT]
> Solar panels consist of multiple fundamental solar cells that are **all the same**: same voltage, same current. These can be easily connected in series and/or in parallel, and the same applies to your larger panels: as long as they are all the same size and type (same voltage, same current), you can freely combine them in series and/or in parallel. Once you start combining *different* panels, you must pay much closer attention to physics, or else you may damage your panels.



* **Serial Connection:** do this with solar panels that have **the same wattage**. You can connect a *12V 100W* and a *18V 100W* panel. The voltages add up, so your overall system would deliver *30V 100W*. If the panels do not have the same **wattage**, the current is limited to the current *of the weakest panel*, and the excess wattage is wasted and may even damage the more powerful panel where it leads to heat and hot spots. Serial strings of solar panels are affected by *shading*: if one of the panels is in the shade, the entire string behaves as if you had connected a panel with lower wattage in series, and *all panels* in this string are reduced to the low current of the shaded panel.
* **Parallel Connection:** do this with solar panels that have **the same voltage**. You can connect a 18V 100W* and a *18V 300W* panel. The currents add up, so your overall system would deliver *18V 400W*. If the panels do not have the same **voltage**, the voltage is limited to the voltage *of the weakest panel*, and current may flow in reverse through other panels, severely reducing efficiency and even damaging your panels over time. Parallel strings of solar panels are not affected by shading: if one panel is in the shade, this does not influence the other panels.

### Ideal Solar Panel Voltage
Ideally, a solar panel voltage should be only marginally higher than the voltage that you actually need (or use for charging a battery). So when you design a *12V system* with *12V batteries*, *18V* solar panels sound like a good idea.

This assumes though that the solar panels are always exposed to bright sunshine - which they obviously are not. On cloudy days, the actual voltage of a *18V solar panel* may just be *7V* - too low to operate your battery charger.

To be more flexible and harvest sunlight on cloudy days as well as in bright sunshine, you can use solar panels with higher voltages - or more commonly, connect standard solar panels in series. When you connect three *18V panels*, you get *54V in bright sunshine*, and still *21V on very cloudy days*, both voltages being sufficiently higher than the required charging voltage.

### Solar Controller

As you will see in the detailed part about the *solar controller*, using solar panels in series with a higher voltage makes a lot of sense **as long as you use an appropriate solar charge controller**:

* **Cheap PWM Charge Controller:** these work similar to *LDO voltage regulators* in that they convert excess voltage to *heat*. Such controllers can work well as long as the incoming voltage from your solar panels is close to the voltage you need to charge your battery. So in cheap *12V systems* with *PWM controllers*, **do not connect panels in series**.
* **Professional MPPT Charge Controller:** such controllers are **much more expensive** and work similar to *efficient buck converters*: when the incoming voltage is much too high, they can convert it to lower voltages without wasting the excess energy. In addition, *MPPT* can adjust the duty cycle of the converter so that the solar panel voltage is always kept at the most efficient sweet spot of the panel, maximizing efficiency. When you use an *MPPT controller*, you should connect multiple panels in series and feed in higher voltages of i.e. *36V* (2S) or *54V* (3S). This way, even on cloudy days the solar panels deliver sufficiently high voltages for charging the battery.

## Budget Recommendation
Your available *space* determines what the best bang for the buck is.

* **Space is King:** What matters most is the *overall surface area* you can use to harvest sunlight. Investing your budget into solar panels (when you have the space) is always the best option.
* **Expensive Tech is Auxiliary:** Increasing the efficiency of your panels (by purchasing more efficient but *way more expensive* modules) and your charge controller (by purchasing more efficient but *way more expensive* MPPT controllers) is a consideration only when space is restrained, and you cannot set up enough solar panels.



<img src="images/solar_poly_small_back_t.png" width="50%" height="50%" />

Here are a few calculations illustrating the importance of space, and the cost attached to *reducing space requirements*:

*10cm2* space can be reduced to *6.5cm2* by switching a *polycrystalline panel* with a *monocrystalline panel*: *10cm2* * *0.015W/cm2* / *0.023W/cm2* = *6.5cm2* (a *polycrystalline panel* has a *15%* efficiency (yielding *0.015W/cm2*) whereas a *monocrystalline panel* has a *23%* efficiency, yielding *0.023W/cm2*). 

Let's calculate *cost per watt* fro the two quite different panels from above. 


<img src="images/solar_panel_mono_6v_3w_front_t.png" width="50%" height="50%" />


* **Small, cheap, less efficient:** these panels were purchased in a *10 pack* for a total of *EUR 2.38*. Each panel cost *EUR 0.24* and yielded *0.15W*. That is *EUR 0.24* / *0.15W* = *EUR 1.60/W*.
* **Larger, more expensive, more efficient:** these panels were purchased as *5 pack* for a total of *EUR 14.99*. Each panel cost *EUR 3.00* and yielded *3W*. That is *EUR 3.00* / *3W* = *EUR 1.00/W*.



<img src="images/solar_poly_small_wrapped_t.png" width="50%" height="50%" />



If you had to choose between the two panel models above, the *cost per watt* calculation would clearly favor the more expensive and larger *monocrystalline* board which yields the same energy for *37.5% less cost*:

*100%* - (*EUR 1.00* x 100 / *EUR 1.60*) = *37.5%*


### Final Thoughts

A few practical facts:

#### No Covers Please

Often, small *DIY solar panels* are protected by a thin plastic cover. Make sure you remove this before use, and make sure you do not place anything else inbetween the solar panel surface and the sunlight (i.e. a plexiglas cover, etc).


<img src="images/solar_poly_small_wrapped2_t.png" width="50%" height="50%" />

*Solar energy* can be *very powerful* when it can reach the *solar panel*. Most materials - even when they appear *transparent* to the human eye - *filter out* a great portion of the energetic light spectrum, severely impacting the solar panel efficiency.

#### Solar Panels Inside The House

It makes no sense whatsoever to use *solar panels* inside the house. Only *natural sunshine* provides the raw energy needed to produce significant currents.

Even on a cloudy day, *solar panels* work surprisingly well outside. Inside, and with artificial light, they are useless.

> [!NOTE]
> That's actually a good thing: it illustrates *how efficient*  artificial light sources have become: light is emitted only in the *visible* spectrum. *Infrared* and *ultraviolet* ranges not visible by the human eye are filtered out. Coincidentally, these are the ranges that transport the most energy to *solar panels* which is why - for them - it is always pitch dark inside.   




> Tags: Solar Panel, Silicon, Monocrystalline, Polycrystalline, MPPT,

[Visit Page on Website](https://done.land/components/power/solar/solarpanels?150501051702244054) - created 2024-05-01 - last edited 2024-10-26
