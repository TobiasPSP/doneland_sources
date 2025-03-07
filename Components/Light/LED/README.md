<img src="/assets/images/light.png" width="80%" height="80%" />
 
# LED (Light Emitting Diodes)

> LEDs can be flexibly shaped, produce light in any color efficiently, last a long time, and cost little.

**LEDs** (*light-emitting diodes*) are *semiconductor devices* that function as *diodes* but with the primary feature of emitting *light* when an electric current passes through them.

## Overview
The first practical LED was [invented in 1962 by Nick Holonyak Jr.](https://en.wikipedia.org/wiki/History_of_the_LED?utm_source=chatgpt.com) while working at General Electric.


LEDs produce light when electrons recombine with holes in the semiconductor material, releasing energy as photons—a process called electroluminescence. The color of the emitted light depends on the semiconductor material's bandgap. 


Their conversion of electrical energy into *light* is highly efficient, meaning that **LEDs** typically generate minimal *heat* (though high-power **LEDs** can still produce significant heat). This characteristic is why **LEDs** are often described as producing *cold light*.


### Laser Diodes

Laser diodes are closely related to LEDs as both are semiconductor devices that emit light when current passes through them. However, laser diodes differ from LEDs in that they produce coherent, highly collimated light through stimulated emission, whereas LEDs produce incoherent, diffused light through spontaneous emission.

Laser diodes work on a similar fundamental principle as LEDs—electroluminescence in a semiconductor—but with a key difference: stimulated emission. While LEDs emit incoherent light in all directions, laser diodes have a built-in optical cavity that amplifies light through stimulated emission, producing coherent, monochromatic, and highly directional light. Like LEDs, laser diodes have a p-n junction and emit photons when electrons recombine with holes, but their design enables optical feedback and gain, allowing the light to build up in intensity before escaping as a laser beam. The emitted wavelength depends on the semiconductor material, just like in LEDs.

### Normal Diodes

*LEDs* and *Laser Diodes* belong to the family of *diodes*, meaning they conduct current only in one direction. However, since *LEDs* are optimized for light emission rather than blocking reverse voltage, their *reverse voltage rating* is typically very low, often around *5-7V*. Unlike standard diodes, which are designed to withstand reverse voltage safely, *LEDs* are much more vulnerable and can degrade or fail quickly if exposed to excessive reverse voltage.

This means an *LED* can only block reverse voltage up to *5-7V* before it starts conducting in reverse, potentially overheating and becoming damaged. In AC applications, where voltage polarity constantly alternates, this repeated stress can quickly destroy the LED.

For this reason, *LEDs* should never be connected directly to *110V/220V AC* through a simple resistor. This would not only expose them to excessive *reverse voltage* but also result in severe inefficiencies. Using a *33kΩ resistor* to power an LED from *110/220V AC* works but would cause noticeable flickering, waste significant energy as heat, and likely cause the resistor to overheat. Instead, for AC-powered LEDs, proper circuit designs include *anti-parallel protection diodes*, *bridge rectifiers*, or *capacitive droppers* to ensure stable and efficient operation.



<details><summary>More About Forward Voltage, Reverse Voltage, and Breakdown Voltage</summary><br/>

Every material has a *breakdown voltage*, the point at which it becomes *conductive*.  

Semiconductors, including **LEDs**, have **two** breakdown voltages:  
- The **forward voltage** is the breakdown voltage for *normal* operation, allowing current to flow from **+** to **-** (the intended direction).  
- The **reverse voltage** is the breakdown voltage when current attempts to flow in the opposite direction.  

When an **LED** is connected correctly, it begins to emit light once the applied voltage exceeds its *forward voltage*. Typical *forward voltages* range from **1.6V to 4.0V**, depending on the *color* and semiconductor materials used.  

If an **LED** is connected *backward* (reverse polarity), it acts as a diode and initially does not conduct electricity. However, unlike purpose-built diodes, **LEDs** have a very low *reverse voltage threshold*—typically around **5V**.  

If the *reverse voltage* exceeds this limit, the **LED** begins to conduct, but instead of emitting light, it dissipates power as *heat*, ultimately destroying the LED.  

Using a current-limiting *series resistor* or another *current-limiting* method can help protect against accidental reverse voltage. Even if the voltage exceeds the *reverse threshold*, only a small current will flow—insufficient to cause significant damage.  
</details>


### LED Technologies

*LED* technology has advanced significantly over the years. Today, *LEDs* are affordable and available in various shapes and forms, ranging from simple indicator LEDs to advanced applications such as **COBs (Chip-on-Board LEDs), LEPs (Laser-Excited Phosphor), programmable LED strips, and OLED displays**.


| Technology             | Year of invention | Description                                                                                                                                                                                                                                   |
|------------------------|-----------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| LED                    | 1962      | The invention of semiconductors that emit light. Initially limited to a few colors, later advancements enabled LEDs to emit nearly any visible color. |
| Laser Diodes          | 1962      | Semiconductor devices that produce coherent, highly collimated light through stimulated emission. Used in optical communication, barcode scanners, and laser pointers. |
| Seven-Segment Displays | 1969      | LEDs integrated into display modules and driven by a multiplexer to show simple numbers and characters. |
| Dot-Matrix Displays    | 1970s     | Arrays of LEDs arranged in an 8×8 (or similar) grid, driven by a multiplexer, capable of displaying simple graphics and symbols. |
| COB (Chip-on-Board)    | 1980s     | High-density LED packaging where multiple LED chips are mounted directly onto a substrate, creating a seamless light-emitting surface. |
| Programmable LEDs      | 2000s     | LEDs with built-in driver circuits, often in RGB, RGBW, or RGBWW configurations (e.g., WS2812), using single- or two-wire protocols. These allow large numbers of LEDs to be controlled via a single GPIO, commonly found in LED strips and matrices. |
| OLED Displays          | 1987      | High-resolution displays composed of self-illuminating organic LEDs, eliminating the need for a backlight. |
| LEP (Laser-Excited Phosphor) | 2000s     | High-intensity, highly focusable light sources using a blue laser diode to excite a phosphor substrate, producing white or colored light. |


* The [HP Model 5082-7000 Numeric Indicator](https://en.wikipedia.org/wiki/History_of_the_LED?utm_source=chatgpt.com), introduced in 1969, was among the first LED devices to use integrated circuit technology, paving the way for seven-segment displays.

* Organic Light-Emitting Diode (OLED) technology was [first demonstrated in 1987 by Ching W. Tang and Steven Van Slyke](https://en.wikipedia.org/wiki/Flat-panel_display?utm_source=chatgpt.com) at Eastman Kodak. It took until the 2000s until OLED technology was affordable and robust enough for widespread adoption.

> [!NOTE]
> Other display types, such as *LCD* and *TFT* screens, rely on liquid crystal technology, which differs from LED-based displays. These displays do not emit light themselves but instead use a backlight, with liquid crystals controlling which areas allow light to pass through.

## Rugged Yet Easy to Destroy

**LEDs** are *rugged*, long-lasting, and more *resilient* to *mechanical* stress than most other light sources. However, despite their durability, they can be *easily destroyed* if not used correctly.  

### Low Internal Resistance

One key characteristic makes LEDs *delicate and sensitive*: they have *very low internal resistance*.  

If an **LED** is connected directly to a power source, it will *almost instantly burn out*. Due to its *low resistance*, an **LED** behaves similarly to a wire or a *fuse*—when exposed to excessive current, it heats up rapidly and is permanently damaged.  


### Always Control Current

To operate an **LED** safely, you must always *limit the current* flowing through it. There are [various methods](Current) to achieve this, but in hobbyist projects, a simple *series resistor* is the most common solution.  
## Identifying Anode and Cathode

Since **LEDs** are semiconductors that conduct current in only one direction, it is crucial to connect them with the correct *polarity*. The two *legs* of an **LED** are called the *anode* (**+**) and the *cathode* (**-**).  



## Standard Indicator LEDs

[Indicator LED](Classic%20Indicator%20LED) are *cheap* and *simple to use*. Many hobbyist projects use these.

<img src="images/led_generic_group1_t.png" width="50%" height="50%" />


## Straw-Hat LED

[Straw Hat](Straw%20Hat) **LED** have a shape resembling a *straw hat*, partially because they feature a built-in *lens* for a wide *viewing angle*.

<img src="images/led_strawhat_top_t.png" width="50%" height="50%" />




## Piranha / SuperFlux LED

[Piranha](Piranha%20SuperFlux) **LED** are small and compact *square* **LED** with a relatively large *light output* with *four* pins (instead of *two*). They are also known as *SuperFlux*.


<img src="images/led_piranha_pile_top_t.png" width="50%" height="50%" />

## Dual Color LED

[Dual color](Dual%20Color) **LED** are really just *two-in-one* **LED** that internally consist of two regular **LED** in different colors. They are perfect for *indicating* two different states, i.e. *funtional* (green) and *error* (red).


<img src="images/led_dual_overview_t.png" width="50%" height="50%" />

## RGB Color LED

[RGB](RGB) **LED** can produce *any color*: three internal **LED** in *red*, *green* and *blue* mix any other color.

## Programmable LED

Once **LED** consist of more than one *color*, they become difficult to operate: each internal color **LED** has its own specific *forward voltage* and needs its own specific *voltage*.

Worse, **LED** *strip* multiply this effort: *each* of the *three* color **LED** in *each* of the connected **RGB LED** need to be carefully wired.

[Programmable](Programmable) **RGB LED** come to the rescue by adding a tiny chip to *each programmable **RGB LED***. Both *color mixing* and *current control* is managed by this chip. It is controlled by just one *data pin* that can be *daisy chained* to string up any number of *programmable **RGB LED***.

Most commonly, the **LED** controllers are *embedded* in **SMD LED** like the type *5050* in the picture above.

> [!NOTE]
> *Programmable* **LED** are comprised of a **LED** and a *controller chip*. From the outside, you can only see the **LED**. This is why *regular* **SMD LED** are *indistinguishable* on first sight from *programmable* **SMD LED**. 

The **LED** *controller* chip can essentially be embedded in *any* **LED** and are not restricted to **LED strips**. They are i.e. also available as *single discrete* **LED***. 

<img src="images/led_ws8212_single_back_t.png" width="50%" height="50%" />

## SMD LED

[SMD](SMD) (*surface mounted device*) **LED** are a special form factor and suitable for *direct mounting* (soldering) to *PCB*. This *SMD* form factor is available for any of the discussed **LED** types:

<img src="images/led_ws2812_5050_top_t.png" width="50%" height="50%" />

You get *SMD* versions of *single color*, *RGB*, and *programmable* **LED**.

## 3W High Performance LED (Generic)

**LED** can be used for **illumination**, too. These [high performance **LED**](High%20Performance) turn *much higher currents* into *light* than the typical *10-20mA* used by simple *indicator* **LED**.

## COB LED

With *dual color* and *RGB* **LED**, you have seen *multiple individual **LED*** blended together. [COB (*Chip On Board*)](COB) takes this a step further and mounts a large number of **LED** directly onto a substrate or circuit board. 

<img src="images/led_panel_collection_angle_t.png" width="50%" height="50%" />

The result are large surfaces of any shape or area, a *cheap* production method and very much homogenous *light output*.


<img src="images/led_panel_narrow_top_t.png" width="50%" height="50%" />

> [!NOTE]
> The many different **LED** on a *COB* are partially connected in series and partially connected in parallel to design a particular desired *total forward voltage*.
They often can be connected directly to voltages like **12-13V** without the need of *series resistors* or *constant voltage*/*constant current* power supplies.


## 7-Segment Displays

Multiple **LED** are combined in *7-Segment* displays. They are commonly used to display numeric information.

<img src="images/led_7seg_overview_t.png" width="50%" height="50%" />

Dedicated *controller IC* make it simple to drive these displays via *I2C* or similar interfaces.


> Tags: LED, Light, Anode, Cathode, RGB, Neopixel, WS2812, COB, Piranha, Superflux, Straw Hat, Matrix, 7-Segment, Forward Voltage, Reverse Voltage, Breakdown Voltage

[Visit Page on Website](https://done.land/components/light/led?198499031411241041) - created 2024-03-17 - last edited 2025-03-05
