<img src="/assets/images/powerbank2.png" width="100%" height="100%" />

# Powerbank 

> Turning Batteries Into Powerbanks


Powerbanks are a safe and convenient way for supplying portable energy, and they come in many shapes and forms. USB powerbanks today are the most common type:

<img src="images/powerbank_commercial__overview_t.webp" width="100%" height="100%" />

Batteries for your favorite gardening tool are often powerbanks, too, just with higher voltages and better current capabilities.


<img src="images/tools_batterypack_gardening_t.webp" width="80%" height="80%" />

And when you equip your portable microcontroller project with a rechargeable battery, you are essentially building your own custom powerbank:

<img src="images/lilygo_t-display_esphome3_t.webp" width="40%" height="40%" />



## Understanding Powerbanks

To fully understand what a powerbank **is** (and how you can **test**, **judge** and even build them yourself), let's have a closer look at its components.

All components found in a powerbank can also surface individually:

### Battery Cell 
A battery cell is a single battery of a given chemistry. 

The battery voltage is always determined by its cell chemistry, so i.e. all *LiIon* batteries have the same *3.7V* nominal voltage. The chemistry also determines whether the battery is rechargeable or not.

<img src="images/batterycells_vs_packs_t.webp" width="50%" height="50%" />

You can use raw battery cells in many devices, i.e. flashlights or radios. Primary batteries like this 9V block battery are exactly the same use case, just an example for a *non-rechargeable* battery chemistry:

<img src="images/batteryholder_9V_t.webp" width="30%" height="30%" />

### Battery Pack
A battery pack is a combination of many battery cells. 

The battery cells can be connected **in series** (to increase voltage) and/or **in parallel** to increase capacity.

The most common form are battery holders for primary batteries:

<img src="images/batteryholder_4.5V_AAA_t.webp" width="30%" height="30%" />

Here, *AA*- or *AAA* batteries are connected **in series**, and three *AAA* primary batteries deliver a total of *4.5V*.

The same occurs in rechargeable battery packs. In RC (Drones, Airsoft, etc.), *LiPo* cells are combined to battery packs that deliver 7.4V (two LiPo cells) or 11.1V (3 LiPo cells).

<img src="images/lipo_rc_overview_t.webp" width="50%" height="50%" /> 

Legacy devices (i.e. cameras) started this concept with their proprietary (and typically grossly overpriced) battery packs that required equally expensive proprietary chargers:

<img src="images/batterypack1_t.webp" width="40%" height="40%" />

Inside powerbanks (commercial as well as DIY), individual battery cells are often connected using nickel strips and spot welding:


<img src="images/powerbank_diy_overview_t.webp" width="60%" height="60%" />

  
### Protection and Safety
Some batteries and battery packs already come with a BMS (battery management system) built-in. With LiPo cells, you often see an electronic board under the plastic wrapping:

<img src="images/batterypack_bms_t.webp" width="40%" height="40%" />

This is a BMS and protects the battery from over-charge and over-discharge. It also protects *you* from fire in case of accidental short circuits over overloads (but won't protect you from fire hazards due to mechanical damage).

In other battery types, the BMS may be present but is hard to see. For example, 18650 LiIon cells may or may not have a BMS built-in. If they do, it is located below the anode. You can't see it, but you can *measure* it: 18650 batteries with BMS are slightly longer (69-71mm versus 65mm).



#### Dangerous Battery Packs
Battery packs designed for drones, RC, etc. can be very dangerous: they typically do not have a built-in BMS. Since they store huge amounts of energy, they can be a significant fire and explosion risk.

That's why it is recommended to place such batteries in a specialized non-flammable bag during charging, and **never charge unattended**.



## Definition

Powerbanks are a combination of four features:

* **Battery/Battery Pack:**     
  One or more **rechargeable** battery cells, connected in series and/or in parallel, to deliver raw internal voltage and energy.
* **Charger:**    
  Electronics to safely charge the battery cells with a given charging voltage. This charging unit changes the input voltage internally to whatever voltage is required for the given battery chemistry and its state of charge. 
  
  For example, **empty** lithium cells require a constant current. Almost **fully recharged** cells require a constant voltage. 
  
  The charging unit sometimes also takes care of cell balancing, making sure each battery cell is at equal voltage. In other cases, the BMS is taking care of balancing.
* **Discharger:**    
  Electronics to transform the raw battery voltage (which can significantly fluctuate due to state of charge) to a **stabilized output voltage**. USB-Powerbanks for example output *5V*, and often support additional voltages through **USB Power Delivery** and similar protocols.
* **Safety/BMS:**    
  Electronics to protect the battery cells from mishandling. BMS makes sure cells won't over-charge or be discharged beyond a safe level.

  **Note:** Even if the cells you are using in a battery pack have their own built-in BMS, any battery pack needs its own. Cell-level BMSes are not designed to protect entire battery packs made of many cells. 




## Optional Components

Typically, *powerbanks* also include the following *optional* components:


* **Visuals:** *LED Bars*, *digital displays*, etc. to indicate the  *state of charge*.
* **Button:** manually turns on the power output. Most powerbanks automatically detect when you connect a load, however with small loads this may fail. 





> Tags: Powerbank, Battery, BMS, Charger

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/powerbank?340059051703244602) - created 2024-05-02 - last edited 25-08-15
