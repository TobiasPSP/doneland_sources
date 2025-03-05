<img src="/assets/images/charging.png" width="100%" height="100%" />

# Modules for Charging & Discharging

> Modules That Can Charge Batteries And Supply A Regulated Output Voltage

Combined *charger* and *discharger* logic in one module provides a simple way of building *powerbank-like* power supplies.

## Overview

*Charging & discharging boards* contain both the battery-charging logic to safely charge a battery, plus a *DC-DC converter* to convert the battery voltage to a stable output voltage. This is all that's needed to turn a rechargeable battery into a power bank.

Even more so, such modules can be used in portable microcontroller devices, turning any *regular* development board into a battery-enabled development board.

### Charger Component
The *charger* part in these boards usually does not differ fundamentally from the common chargers, i.e. *TP4056*. Pay attention to these three parameters:

* **Charging Current:** typically *1A*, but can be different. Make sure the charger does not *exceed* the maximum charging current of the battery you are planning to use. For microcontroller projects, often affordable *Li-Po* pouch batteries are used which have relatively low charging rates of *0.5C*. When using a *1000mAh* battery, the maximum charging rate should not exceed *500mA*.
* **Chemistry:** most chargers target *Li-Ion/Li-Po* batteries. You cannot use these to charge *LiFePo4* batteries.
* **Strings:** the vast majority of small modules is designed for a single battery cell. If you want to charge batteries consisting of multiple cells, make sure the charger voltage matches. 

> [!IMPORTANT]
> You **cannot use** multiple 1S chargers to charge batteries consisting of more than one cell because this would cause short circuits since most chargers are not isolated and must share the same *ground*. Always use chargers dedicated to the number of strings your battery uses.

### Discharger Component
The *discharger* component transforms the battery voltage to a  constant output voltage, typically (but not limited to) *5V*.

Depending on your battery voltage and the desired output voltage, the component uses a *buck*, *boost*, or *buck-boost* component.

For example, if a module is designed for a *1S Li-Ion* battery and outputs *5V* to power USB devices, then the module uses a *boost* converter to raise the input voltage from *3-4.6V* to *5V*. The same would be true for modules designed to supply *3.3V* from a *NiMH* cell (*1.2V*).

Modules outputting *3.3V* from a *1S Li-Ion* battery use a *buck-boost circuit* since the battery voltage can be lower or higher than the output voltage.




> Tags: Charger, Boost, Buck, Microcontroller, Power Supply, Battery

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge?136993011912250937) - created 2025-01-11 - last edited 2025-01-11
