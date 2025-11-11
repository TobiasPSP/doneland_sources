<img src="/assets/images/power.jpg" width="80%" height="80%" />

# Boost Converters

> Raising DC Voltage (And Optionally Limiting Current, Too)

While AC uses transformers to transfer energy between windings via a time‑varying magnetic field, this is not possible with DC alone because there is no alternating field to induce voltage in a second winding.

Instead, DC boost converters electronically raise the input voltage to a higher output voltage.

They are basically the opposite of a <a href="https://done.land/components/power/powersupplies/dc-dc-converters/buck/">buck converter</a>.

## Overview

Raising a voltage can be very important for many projects:

- <b>Battery Operation:</b>  
  You may want to power a device or microcontroller from <a href="https://done.land/components/power/powersupplies/battery/batterytypes/">batteries</a>. If the battery voltage does not match your requirements — typically it is lower than needed — a boost converter raises the battery voltage to a stable higher voltage.

- <b>USB Discharger/Ports:</b>  
  Many small Li‑ion power banks use 1S configurations (a single Li‑ion cell). The cell voltage varies with state of charge, roughly from about 2.8–4.2 V.  
  To charge USB devices from such a power bank, a boost converter steps the cell voltage up to a regulated 5 V output.  
  Even with multi‑string power banks, boost conversion is important to enable fast‑charge protocols: USB PD supports output voltages such as 5, 9, 12, 15, and 20 V. With Li‑ion batteries, you would need at least an 8S configuration to sit safely above 20 V.  
  Boost converters allow a small battery pack with a much lower voltage to provide all common USB PD voltages.

- <b>Car Electronics:</b>  
  There are many devices running on 12 V that were originally designed for automotive systems. Boost converters enable a regulated 12 V output from a small Li‑ion battery pack.


## Working Principles

A boost converter is an electronic switching circuit using a MOSFET switch and an inductor (magnetic energy storage), much like a <a href="https://done.land/components/power/powersupplies/dc-dc-converters/buck/">buck converter</a>:

- <b>Boost (raising voltage):</b>  
  <i>stores then adds</i> energy: it first stores energy in an inductor at the input voltage, then releases that energy in series with the input to raise the output voltage above the input.

- <b>Buck (lowering voltage):</b>  
  <i>stores then subtracts</i> energy: it first stores part of the input energy in an inductor, then, when the input switch turns off, releases the stored energy to the load through a low‑side path, reducing the average voltage delivered so the output sits below the input.


## Challenges

Raising DC voltage (“boosting”) is harder than lowering it, and boost converters are typically slightly less efficient than <a href="https://done.land/components/power/powersupplies/dc-dc-converters/buck/">buck converters</a>. Lower efficiency means more heat.

Additionally, while buck converters can handle large input‑to‑output voltage differences relatively gracefully, boost converters struggle as the required step‑up ratio grows. In practice, simple single‑stage boosts are often used for modest increases; pushing to much higher voltages quickly demands larger inductors and capacitors, more substantial thermal design, and sometimes multi‑stage or hybrid topologies.

That said, modern highly integrated power‑management ICs can be extremely efficient for reasonable step‑up ratios. Devices such as the TPS61088‑class parts (step‑up controllers/regulators available from major vendors) achieve excellent performance in compact designs.

One fundamental constraint is input current: when stepping up voltage, input current rises roughly in proportion to output power. For example, if you need 12 V at 1.5 A (18 W) from a 3.7 V source (1S Li‑ion nominal), the ideal input current is about 4.9 A; accounting for losses and battery voltage sag across state‑of‑charge, real input current can approach ~7 A.

> Tags: Boost, Voltage, Regulator, Constant Voltage, Constant Current, CV, CC, DC-DC

[Visit Page on Website](https://done.land/components/power/powersupplies/dc-dc-converters/boost?295625111804254647) - created 2025-11-03 - last edited 2025-11-03
