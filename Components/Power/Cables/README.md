<img src="/assets/images/lightning.png" width="100%" height="100%" />
# Cables

> Picking Appropriate Wires And Cables

Cables serve as critical connectors for power, data, and signal transmission.

* **Power cables** (e.g., thicker gauge wires) handle high currents and minimize voltage drop
* **Data cables** (e.g., twisted pairs or shielded wires) ensure reliable communication with minimal interference.

The choice of cable depends on factors like current capacity, signal type, flexibility, and environmental conditions.


## Overview

A *cable* is a collection of two or more insulated *wires* bundled together, often covered by an outer protective sheath. A *wire* is a single conductor, solid or stranded, usually made of copper or aluminum. It can be insulated or bare (uninsulated).

In the remainder of this article, I am using the terms *cable* and *wire* interchangeably. When talking about physical properties, I refer to *wires*, regardless of how many conductors a *cable* may have.


## Selecting Appropriate Cables/Wires

When picking a cable or wire for your project, ask yourself these three simple questions:

* **Power or Signal?** Is this for transporting raw electric *power* (i.e., *AC power cables*, *solar panels*), or *signals*/*data* (i.e., *sensor information*, *I2C bus*, *input buttons*)?
* **Maximum Current?** What is the *maximum current* that needs to be transported?
* **Distance?** Is this for short distances (i.e., inside a device (also known as *chassis wiring*)), or larger distances (*>15cm*)?

*Voltage* is typically not a primary concern in *DIY* applications, as only low voltages are used. However, once voltages exceed *1000V*, you must also consider the *insulation type*.


### Key Properties

Once you know the answers to the above questions, look at these fundamental cable properties:

* **Gauge:** The *gauge* (cross-sectional area) of a cable defines how much current it can transport without heating up. This also depends on the *material*: a material with lower resistance (i.e., *copper*) requires smaller gauges than a material with higher resistance (i.e., *aluminum*).
* **Conductor Material:** *Copper* wires have the best conductivity but are more costly. *Copper-clad aluminum wires* (*CCA* or *CCAW*) are dual-metal electrical conductors, with an inner aluminum core and outer copper cladding. They are more cost-effective but have higher resistance compared to pure copper wires.
* **Solid/Stranded:** Solid wire with a single, solid conductor are rigid and best for stationary installations like building wiring. Stranded wire, made of multiple thin strands twisted together, is flexible and more often used in DIY projects. However, the more strands a wire has, the higher is its resistance.
* **Cable Shielding:** When transmitting high-frequency or weak data signals, the cable type and its *shielding* are important. A common cable type for such signals is *coaxial cable*, where the conductor for data is in the center, and a common ground shield protects it from noise. For less sensitive data, you may only need a *twisted pair* cable, where the wires are twisted together to reduce noise effects.


## Gauge

The wire gauge is the most important property of any cable: the larger the cross-sectional diameter, the lower the *resistance*, and the more current can be conducted without *heating* or ultimately *melting* the cable.

However, the maximum current is also affected by a few other factors:

* **Material:** Significantly affects resistance.
* **Stranded:** Stranded wires have higher resistance, which is proportional to the number of strands.
* **Chassis Wiring:** The term *chassis wiring* refers to the use of individual wires inside a device. Compared to cables where multiple wires are bundled together in close proximity, *chassis wiring* allows for better heat dissipation. Combined with shorter wires (less overall heat buildup), *chassis wiring* can typically handle slightly higher currents.

Here are the most commonly used wire gauges in DIY, based on *stranded copper wires*:

| AWG  | mm²   | Diameter (mm) | Maximum Current  | Use Case                              |
|------|-------|----------------|----------------------------------|---------------------------------------|
| 28   | 0.08  | 0.32           | 1.2 A                  | Data, chassis wiring                  |
| 24   | 0.20  | 0.511          | 3.0 A                 | Data and power, chassis wiring        |
| 22   | 0.32  | 0.644          | 5.5 A                 | Data, power, battery in chassis wiring|
| 18   | 0.82  | 1.024          | 7 A                   | Power, long distance                  |
| 14   | 2.08  | 1.628          | 15 A                 | Power, long distance                  |
| 8    | 8.37  | 3.264          | 28 A                 | Power, solar panels, long distance    |

Note that these values are rough estimates, considering typical use cases. For more detailed information, use the *wire gauge comparison table* below.


<details><summary>Wire Gauges Comparison Table</summary><br/>


| AWG  | mm²   | Diameter (mm) | Chassis Wiring (Copper)         | Normal Wiring (Copper)          | Chassis Wiring (CCA)             | Normal Wiring (CCA)             |
|------|-------|----------------|---------------------------------|---------------------------------|----------------------------------|---------------------------------|
| 30   | 0.05  | 0.255          | 0.86 A (solid)/0.75 A (stranded) | 0.5 A (solid)/0.46 A (stranded) | 0.60 A (solid)/0.42 A (stranded) | 0.35 A (solid)/0.26 A (stranded) |
| 28   | 0.08  | 0.32           | 1.4 A (solid)/1.2 A (stranded)  | 0.8 A (solid)/0.74 A (stranded) | 1.0 A (solid)/0.70 A (stranded)  | 0.56 A (solid)/0.39 A (stranded) |
| 26   | 0.13  | 0.405          | 2.2 A (solid)/1.8 A (stranded)  | 1.4 A (solid)/1.1 A (stranded)  | 1.5 A (solid)/1.05 A (stranded)  | 1.0 A (solid)/0.65 A (stranded)  |
| 24   | 0.20  | 0.511          | 3.5 A (solid)/3.0 A (stranded)  | 2.1 A (solid)/1.85 A (stranded) | 2.5 A (solid)/1.75 A (stranded)  | 1.47 A (solid)/1.0 A (stranded)  |
| 22   | 0.32  | 0.644          | 7.0 A (solid)/5.5 A (stranded)  | 3.0 A (solid)/3.0 A (stranded)  | 4.9 A (solid)/3.4 A (stranded)   | 2.1 A (solid)/1.75 A (stranded)  |
| 20   | 0.52  | 0.812          | 11 A (solid)/9.0 A (stranded)   | 5.5 A (solid)/5.0 A (stranded)  | 7.7 A (solid)/5.6 A (stranded)   | 3.85 A (solid)/2.6 A (stranded)  |
| 18   | 0.82  | 1.024          | 16 A (solid)/13 A (stranded)    | 10 A (solid)/7.0 A (stranded)   | 11.2 A (solid)/7.8 A (stranded)  | 7.0 A (solid)/4.5 A (stranded)   |
| 16   | 1.31  | 1.291          | 22 A (solid)/19 A (stranded)    | 13 A (solid)/9.1 A (stranded)   | 15.4 A (solid)/10.8 A (stranded) | 9.1 A (solid)/6.3 A (stranded)   |
| 14   | 2.08  | 1.628          | 32 A (solid)/28 A (stranded)    | 18 A (solid)/12.6 A (stranded)  | 22.4 A (solid)/15.7 A (stranded) | 12.6 A (solid)/8.8 A (stranded)  |
| 12   | 3.31  | 2.053          | 41 A (solid)/35 A (stranded)    | 23 A (solid)/16.1 A (stranded)  | 28.7 A (solid)/20.0 A (stranded) | 16.1 A (solid)/11.3 A (stranded) |
| 10   | 5.26  | 2.588          | 55 A (solid)/48 A (stranded)    | 30 A (solid)/21.0 A (stranded)  | 38.5 A (solid)/27.0 A (stranded) | 21.0 A (solid)/14.7 A (stranded) |
| 8    | 8.37  | 3.264          | 80 A (solid)/72 A (stranded)    | 40 A (solid)/28.0 A (stranded) | 56 A (solid)/45.0 A (stranded)  | 28.0 A (solid)/21.0 A (stranded) |
| 6    | 13.3  | 4.115          | 105 A (solid)/90 A (stranded)   | 65 A (solid)/45.5 A (stranded) | 73.5 A (solid)/56.0 A (stranded) | 45.5 A (solid)/32.0 A (stranded) |

* *Chassis wiring* refers to short, open-air wiring, which can handle higher currents due to better cooling.
* *Normal wiring* is for longer runs or enclosed wiring, where heat dissipation is limited.
* *Copper-clad aluminium wires (CCA)*: CCA derating is applied as approximately 70% of copper capacity.

> [!TIP]
> Add *10-25%* to the intended maximum current to allow for a safety margin. All numbers are *approximations* and just a *rough guideline*. Always consult the specifications of *your particular cable*.  

</details>

## Material

When comparing prices and cables, always take the *material* into account. Cheap cables often use inferior materials (such as *copper-clad aluminum*), which have much higher resistance. While these cables may be substantially cheaper, you’ll need a higher gauge (larger cables) to carry the same amount of current. 

The following are common materials used in DIY projects:

* **Copper:** The preferred material for electrical wiring due to its excellent conductivity, malleability, and resistance to corrosion, but it is also one of the *most expensive materials*.
* **Tinned Copper:** Coated with a thin layer of tin to improve corrosion resistance (ideal for marine or outdoor applications). It has slightly lower conductivity due to the tin layer and is slightly more expensive than bare copper.
* **Silver-Plated Copper:** Copper core coated with silver, used in high-frequency and specialized applications. It has the best conductivity and is excellent for RF applications, but it is very expensive and overkill for most DIY applications.
* **Nickel-Plated Copper:** Copper coated with nickel, providing higher resistance to high-temperature or high-wear environments. It’s more expensive and has lower conductivity than bare copper.
* **Copper-Clad Aluminum (CCA):** A budget alternative where the aluminum core is coated with a thin layer of copper. It is cost-effective for larger diameter power cables but should be avoided for small gauges due to its higher resistance.
* **Aluminum:** Commonly used for power transmission with large-diameter wires where the price difference in materials is significant. Not typically used in DIY projects due to its poor conductivity and high weight.

| Material            | Conductivity (Relative to Copper) | Corrosion Resistance | Cost               | Quality  | 
|---------------------|-----------------------------------|----------------------|--------------------|----------|
| Copper              | 100%                              | Moderate             | Moderate           | ++    |
| Silver-Plated Copper| 105%                              | High                 | High               | ++++    |
| Tinned Copper       | ~97%                              | High                 | Moderate           | ++    | 
| Nickel-Plated Copper| ~90%                              | Very High            | High               | +++    | 
| Copper-Clad Aluminum| ~61%                              | Low                  | Low                | -    | 
| Aluminum            | ~61%                              | Low                  | Low                | -- Light| 

## Stranded Cores versus Solid Conductor

Since wires in most *DIY projects* need to be *flexible*, they are *stranded*, consisting of many small cores. The more cores a wire has, the more flexible it is. At the same time, its resistance rises, so the number of cores is a trade-off.

| Feature              | Solid Wire                      | Stranded Wire                   |
|----------------------|----------------------------------|----------------------------------|
| Structure            | Single solid conductor          | Multiple thin strands twisted together |
| Flexibility          | Less flexible                   | Highly flexible                 |
| Durability           | More resistant to nicks or cuts | Less resistant to nicks or cuts |
| Applications         | Permanent installations (e.g., building wiring) | Moving parts, portable devices, or tight spaces |
| Cost                 | Cheaper due to simpler design   | Slightly more expensive         |
| Conductivity         | Lower surface area, slightly lower resistance | Higher surface area, slightly higher resistance |
| Corrosion Resistance | Better (less exposed surface area) | Prone to corrosion (more exposed surface area) |
| Ease of Termination  | Easier to terminate             | Requires crimping or soldering  |

## Recommendations

Here are a few practical recommendations:

* **Roll Included?:** Only buy cables that ship well-spooled on a roll. Some cheap offers send you cables wound up by hand. It can be nearly impossible and *very* frustrating to unwind such cables, especially when they are longer than 1-2 meters. You may end up cutting these cables into shorter parts to untangle them.
* **Material:** Tempting offers with low prices often turn out to use inferior materials (such as *CCA* instead of *copper*). Do not compare apples with oranges when shopping.
* **Double-Check:** It is common for some sellers, especially on untrusted marketplaces like *eBay* or *AliExpress*, to ship cables that don’t match the *AWG* gauge you ordered. When you receive cables and wires, always double-check their dimensions with a caliper, and measure the cable resistance. You can return them in time if needed.
* **Preconfigured:** In *DIY projects*, short *AWG22/24* wires are frequently needed for data and signals. Sources like *AliExpress* offer low-cost packages with *100+* short *AWG22/24* pre-tinned wires.

> [!TIP]
> While electronic components, plugs, and connectors are often made in *China*, *Asian Direct Sellers* like *AliExpress* usually offer the best prices. Cables are produced in many places around the world and are heavy (shipping). That’s why I found the best price/performance for cables on *Amazon*.




> Tags: Cable, Wire, AWG, Gauge, Resistance, AWG, CCA, CCAW, Copper, Aluminum, Stranded Wire, Shielding

[Visit Page on Website](https://done.land/components/power/cables?651121011321252314) - created 2025-01-20 - last edited 2025-01-20
