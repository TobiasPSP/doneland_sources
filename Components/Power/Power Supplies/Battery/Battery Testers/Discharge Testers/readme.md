<img src="/assets/images/lightning.png" width="100%" height="100%" />
# Discharge-Only Battery Testers

> Simple Battery Capacity Testers That Require Fully Charged Batteries Under Test

The basic principle behind all battery testers is straightforward: draw energy from a fully charged battery until it is depleted, while logging the total amount of energy drawn.

While there are [*fully automatic* battery testers](https://done.land/components/power/powersupplies/battery/batterytesters/all-in-onetesters/) capable of handling the entire testing cycle—including *charging*—simple *discharge-only* testers can be a compelling alternative.

## Overview

*Discharge-only* testers do not have the ability to *charge* batteries. They depend on *you* to fully charge the battery before starting the test. Compared to [all-in-one testers](https://done.land/components/power/powersupplies/battery/batterytesters/all-in-onetesters), they still provide *voltage and current logging* as well as a *test load*, but they lack *charging functionality*.

### A Flexible Tool

What may initially seem like a major limitation can actually be an advantage. Having a dedicated *battery discharger* on hand can be incredibly useful:

* **Mass Testing:** If you're testing many individual round cells and want to monitor battery performance, a simple discharger can be an effective part of a streamlined testing setup (see below).
* **Storage:** *Li-ion* and *LiPo* batteries should be discharged to around *3.7V* for long-term storage. (*LiFePO₄* batteries are an exception, as they tolerate being fully charged for extended periods.) A basic discharger can bring any battery down to a desired storage voltage.
* **Safety:** When shipping lithium-ion batteries—especially by air—there are both legal and safety recommendations for their state of charge (SoC). A 30% SoC is typically advised for air transport, which corresponds to about 3.6V per cell for most chemistries. A discharger allows you to reliably prepare batteries for safe shipping.

## Devices

Here are the common types of battery dischargers:

* **Full-Blown Testers:**  
  Discharge testers like the [XH-M239](https://done.land/components/power/powersupplies/battery/batterytesters/dischargetesters/xh-m239/) are designed for testing individual batteries. They feature a built-in load resistor and display key battery metrics. However, such testers **often aren’t worth it**—for a similar cost, you could invest in a *fully automatic tester* that includes *charging capabilities*.
  
* **Discharge Modules:**  
  Compact and versatile modules like the *HW-586* offer excellent flexibility. They can be used with any external load resistor, support batteries up to 15V, and allow discharge currents up to 3A. Despite including a display and microcontroller-based monitoring, these modules are remarkably affordable—often available for under €2.00.

  
### Recommended Test Scenario

Most commercially available battery chargers do not include battery capacity testing. This is because they typically lack the ability to *discharge* batteries.

However, many chargers—even budget-friendly ones—do track the total energy delivered during charging. When you recharge a cell, the charger often displays the total *mAh* supplied to it.

By combining such a charger with the *HW-586* discharger module, you can build a highly flexible and efficient testing setup. Here’s how it works:

* **Battery Use:**  
  Use your rechargeable cells as you normally would.  
  Once a cell is considered "empty," you would typically recharge it. However, the voltage at which a cell is considered *empty* can vary depending on the application. Some devices shut down when the battery voltage drops below *2.8V*, while others may cut off at *3.4V*—especially under high current draw.

* **Discharge to a Defined Cutoff Voltage:**  
  To standardize your testing, place the cells into the *HW-586* discharger and discharge them further to a consistent cutoff voltage—e.g., *3.0V*.

* **Recharge and Measure:**  
  After discharging to the target voltage, insert the cells into your charger. If your charger reports the total energy in *mAh*, this allows you to evaluate each cell’s actual capacity and track degradation over time—key data for maintaining reliable battery-powered devices.


> Tags: Battery Tester, Discharge-Only, Capacity, Internal Resistance

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/batterytesters/dischargetesters?643318111410241653) - created 2024-11-09 - last edited 2025-04-23
