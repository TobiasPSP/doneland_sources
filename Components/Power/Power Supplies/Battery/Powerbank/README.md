<img src="/assets/images/powerbank2.png" width="100%" height="100%" />
# Powerbank 


> Turning Batteries Into Powerbanks



Powerbanks are a safe and convenient way to supply portable energy, coming in many shapes and forms. Today, USB powerbanks are the most common type:


<img src="images/powerbank_commercial__overview_t.webp" width="100%" height="100%" />


Batteries for your favorite gardening tool are often powerbanks too—but typically with higher voltages and greater current capabilities.



<img src="images/tools_batterypack_gardening_t.webp" width="80%" height="80%" />


And when you equip your portable microcontroller project with a rechargeable battery, you are essentially building your own custom powerbank:


<img src="images/lilygo_t-display_esphome3_t.webp" width="40%" height="40%" />




## Understanding Powerbanks


To fully understand what a powerbank **is** (and how you can **test**, **judge**, and even build them yourself), let's look closer at its main components.


All components found in a powerbank can also appear individually:


### Battery Cell 
A battery cell is a single battery of a given chemistry. 


The battery voltage is always determined by its cell chemistry, so for example, all *Li-ion* batteries have the same *3.7V* nominal voltage. The chemistry also determines whether the battery is rechargeable.


<img src="images/batterycells_vs_packs_t.webp" width="50%" height="50%" />


You can use raw battery cells in many devices, e.g., flashlights or radios. Primary batteries like this 9V block battery are an example of a *non-rechargeable* battery chemistry:


<img src="images/batteryholder_9V_t.webp" width="30%" height="30%" />


### Battery Pack
A battery pack is a combination of several battery cells. 


The individual cells can be connected **in series** (to increase voltage) and/or **in parallel** (to increase capacity).


A common form is a battery holder for primary batteries:


<img src="images/batteryholder_4.5V_AAA_t.webp" width="30%" height="30%" />


Here, *AA*- or *AAA* batteries are connected **in series**; three *AAA* primary batteries deliver a total of *4.5V*.


The same logic applies to rechargeable battery packs. In RC (Drones, Airsoft, etc.), *LiPo* cells are combined into battery packs that deliver 7.4V (two LiPo cells in series) or 11.1V (three LiPo cells).


<img src="images/lipo_rc_overview_t.webp" width="50%" height="50%" /> 


Legacy devices (such as cameras) used proprietary (and typically overpriced) battery packs that required equally expensive proprietary chargers:


<img src="images/batterypack1_t.webp" width="40%" height="40%" />


Inside powerbanks (commercial and DIY), individual battery cells are often connected using nickel strips and spot welding:



<img src="images/powerbank_diy_overview_t.webp" width="60%" height="60%" />


  
### Protection and Safety
Some batteries and battery packs already come with a BMS (Battery Management System) built in. With LiPo cells, you often see an electronic board under the plastic wrapping:


<img src="images/batterypack_bms_t.webp" width="40%" height="40%" />


This is a BMS, protecting the battery from over-charge and over-discharge. It also protects *you* from fire in case of accidental short circuits or overloads (though, note, it won't protect against fire hazards caused by mechanical damage).


In other battery types, the BMS may be present but is hard to see. For example, 18650 Li-ion cells may or may not have a BMS built in. If they do, it's located below the anode. You can't see it, but you can *measure* it: 18650 batteries with BMS are slightly longer (69-71mm versus 65mm).




#### Dangerous Battery Packs
Battery packs used in drones, RC, and similar applications can be very dangerous: they often lack an integrated BMS and store large amounts of energy, leading to significant fire and explosion risks.


- Always use a specialized, non-flammable bag during charging.
- **Never charge unattended.**
- Handle with care: avoid physical damage, short circuits, or storing near heat sources.




## Definition


Powerbanks are a blend of four essential features:


* **Battery/Battery Pack:**     
  One or more **rechargeable** battery cells, connected in series and/or in parallel, to provide raw internal voltage and energy.
* **Charger:**    
  Electronics for safely charging the battery cells with the correct voltage. The charging circuit internally adapts the input voltage to match the battery chemistry and its current state of charge. 
  
  For example, **empty** lithium cells require constant current; nearly **fully recharged** cells require constant voltage. 
  
  Sometimes, the charging unit also handles cell balancing; in other cases, the BMS provides this function.
* **Discharger:**    
  Electronics that transform the raw battery voltage (which can vary with state of charge) to a **stabilized output voltage**. For instance, USB powerbanks output *5V*, often supporting other voltages via **USB Power Delivery** and similar protocols.
* **Safety/BMS:**    
  Electronics that protect battery cells from abuse. A BMS ensures no cell is overcharged or discharged below a safe cutoff.


  **Note:** Even if each cell in your battery pack has a built-in BMS, the overall pack still needs its own. Cell-level BMSes are not designed to protect multi-cell packs.


 

## Optional Components


Typical *powerbanks* also include these *optional* components:


* **Visuals:** *LED Bars*, *digital displays*, etc., to show *state of charge*.
* **Button:** For manual activation of power output. Most powerbanks automatically detect a connected load; with very small loads, this can fail.
* **USB interfaces and Cables:** Various USB input and output ports for charging versatility; some may include USB-C, micro-USB, or wireless charging features.




> Tags: Powerbank, Battery, BMS, Charger, Battery Pack, Li-ion, LiPo, USB Power Delivery, Protection, Safety, Battery Management System, Portable Energy, Rechargeable Batteries, DIY Powerbanks, USB Output, Visual Indicators, Cell Balancing, Safe Charging


[Visit Page on Website](https://done.land/components/power/powersupplies/battery/powerbank?340059051703244602) - created 2024-05-02 - last edited 25-08-15
