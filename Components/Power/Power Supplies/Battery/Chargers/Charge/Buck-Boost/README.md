<img src="/assets/images/charging.png" width="100%" height="100%" />

# Buck-Boost Battery Chargers

> Chargers With Charging Voltage Independent Of Suppy Voltage

Buck-Boost chargers are extremely flexible: they can produce the required charging voltage from **lower or higher** input voltages.

This is especially useful if the charger supports USB PD input. When you connect a modern USB power supply to such chargers, they negotiate the most efficient input voltage for charging, minimizing heat and losses.

## Overview

Buck-Boost battery chargers use an input voltage that is completely independent of the required output voltage. Here is what this means:

### USB Input

You can use all kinds of USB power supplies - simple 5V "wall warts" as well as sophisticated USB PD supplies - and also classic power supplies. 

Here is an example: let's say you want to charge a 3S LiIon battery pack. This requires a 12.6V charging voltage.

* **Simple 5V USB Power Supply:**      
  If you just got a simple 5V USB power supply, the charger **boosts** the 5V up to the required 12.6V. While this may not be highly efficient, and while the charger may therefore get fairly hot, charging works reliably.

* **Modern USB PD Power Supply:**   
  If your USB power supply supports USB PD, then the charger negotiates the most efficient input voltage. It could, for example, negotiate 12V. Now the **boost** converter would have to boost up the voltage only marginally, resulting in a much higher efficiency and much less heat generation.

  Or it could request 15V and use its **buck** converter to lower the voltage down to the required 12.6V.

* **Classic Power Supply:**   
  Since buck-boost chargers can work with a wide input voltage range - lower or higher than the required voltage - you can power the charger with *any* power supply within the supported voltage range. You could, for example, repurpose an old laptop brick or use any other DC power supply at hand.

> [!NOTE]
> Make sure you check the charger specs. The input voltage range is wide, however it differs between models. Also, not all charger modells support USB PD negotiation. Some simpler models expect *you* to supply the best voltage directly.   




> Tags: Battery chargers, Charger, LiIon, LiPo, LiFePO4, Strings Buck, Boost

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge/buck-boost?169719101913255914) - created 2025-10-12 - last edited 2025-10-12
