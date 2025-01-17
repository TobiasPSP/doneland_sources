<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Batteries  

> Batteries Use Chemical Processes To Create Electricity 

Disposable and rechargeable batteries both store energy and provide electrical power. However, they differ primarily in their chemistry and usage.

Disposable batteries, such as alkaline or zinc-carbon types, are designed for one-time use, relying on chemical reactions that cannot be reversed. In contrast, rechargeable batteries, like lithium-ion or nickel-metal hydride, use reversible reactions, allowing them to be charged and discharged multiple times.

## Overview

Disposable batteries are typically cheaper upfront but become more expensive over time due to the need for repeated purchases. As a result, they are best suited for low-energy applications, such as remotes or sensors that can run on a battery for an extended period. In these cases, the ease of use, affordability, simplicity, and small form factor outweigh the disadvantages of having to replace the batteries regularly.

Rechargeable batteries, on the other hand, have a higher initial cost but offer much better long-term value. To make this investment worthwhile, they are used in applications with higher energy consumption, requiring many charge cycles, which makes the use of disposable batteries economically impractical.

### Energy Density

Disposable batteries often last longer before depletion compared to rechargeable batteries, as the latter tend to have lower energy density and capacity. 

When device size is a concern, tiny disposable button cells are commonly used. 

For high-energy applications, such as cameras, **non-rechargeable** lithium-based high-performance batteries are preferred due to their exceptionally high energy density.

Advances in technology have miniaturized charger and battery management system (BMS) components to the point where *rechargeable* lithium batteries are now available with similar energy density to high-quality alkaline batteries. These rechargeable lithium batteries can directly replace conventional AA and AAA alkaline cells and can be easily recharged via a USB plug, without the need for a dedicated charger.


| Battery Type            | Energy Density (Wh/kg) | Notes                                                                 |
|-------------------------|-------------------------|-----------------------------------------------------------------------|
| **Alkaline (Disposable)** | 80–120                 | Commonly used in low-drain devices like remotes and clocks.           |
| **Zinc-Carbon (Disposable)** | 30–50               | Lower energy density; typically used in inexpensive applications.     |
| **Lithium-Ion (Rechargeable)** | 150–250          | High energy density; widely used in smartphones, laptops, and EVs.    |
| **Lithium Polymer (LiPo)** | 100–250             | Flexible form factor; often used in drones and compact electronics.   |
| **Lithium (Non-Rechargeable)** | 250–300         | Extremely high energy density; used in medical devices and sensors.   |
| **Nickel-Metal Hydride (NiMH)** | 60–120         | Common in rechargeable AA/AAA batteries; moderate energy density.     |
| **Nickel-Cadmium (NiCd)** | 40–60                | Older technology, now less common due to toxicity and low density.    |
| **Lead-Acid**            | 30–50                 | Heavy and bulky; used in vehicles and backup power systems.           |
| **Lithium Iron Phosphate (LiFePO₄)** | 90–140    | Safer and more stable than Li-ion; used in solar systems and EVs.     |
| **Zinc-Air (Disposable)** | 300–400              | High energy density; typically used in hearing aids and medical devices. |
| **Silver Oxide (Disposable)** | 100–130          | Used in button cells for watches and small electronics.               |

## Self-Discharge and Storage

Self-discharge rates vary, with disposable batteries retaining charge for years in storage. Rechargeable batteries can lose charge over time even when unused. 

| Battery Type               | Self-Discharge Rate (% per month) | Shelf Life               | Notes                                                                 |
|----------------------------|-----------------------------------|--------------------------|----------------------------------------------------------------------|
| **Alkaline (Disposable)**  | ~0.3–2%                          | 5–10 years               | Long shelf life; suitable for infrequently used devices.             |
| **Zinc-Carbon (Disposable)** | ~2–5%                          | 2–3 years                | Shorter shelf life; commonly used in low-cost applications.          |
| **Lithium (Non-Rechargeable)** | <1%                          | 10–20 years              | Extremely low self-discharge; ideal for long-term use in critical devices. |
| **Lithium-Ion (Rechargeable)** | ~2–8%                        | 2–5 years (in storage)   | Higher self-discharge than non-rechargeable lithium; depends on storage conditions. |
| **Lithium Polymer (LiPo)** | ~2–10%                          | 2–3 years (in storage)   | Similar to lithium-ion but with more sensitivity to storage conditions. |
| **Nickel-Metal Hydride (NiMH)** | ~15–30%                    | 3–5 years                | High self-discharge, though low-self-discharge NiMH variants (LSD NiMH) reduce this to ~1–5%. |
| **Nickel-Cadmium (NiCd)**  | ~10–20%                         | 3–5 years                | Moderate self-discharge; better for high-drain applications.         |
| **Lead-Acid**              | ~3–5%                           | 3–6 years (sealed types) | Self-discharge increases at higher temperatures; good for standby power. |
| **Lithium Iron Phosphate (LiFePO₄)** | ~2–3%                 | 10+ years                | Low self-discharge; excellent for long-term storage and cyclic use.  |
| **Zinc-Air (Disposable)**  | Activation required (dry storage) | ~3 years (unactivated)   | Once exposed to air, short shelf life; used in hearing aids.         |
| **Silver Oxide (Disposable)** | ~1–2%                        | ~5 years                 | Long-lasting for button cells in low-drain applications.             |
| **Silver Oxide (Button Cell)** | ~1–2%                      | ~5–10 years              | Used in watches and medical devices; stable voltage output.          |
| **Lithium (Button Cell)**  | <1%                              | 10–20 years              | Extremely long-lasting; used in devices like calculators and backup memory. |
| **Alkaline (Button Cell)** | ~2–5%                            | ~3–5 years               | Common in small devices; lower energy density compared to lithium.   |
| **Zinc-Air (Button Cell)** | ~0.5–1%                          | ~3 years (unactivated)   | Used in hearing aids; requires air activation to work.               |
| **Mercury Oxide (Button Cell)** | ~1–2%                      | ~5–10 years              | Phased out due to environmental concerns, used for stable output.    |

### Storage Recommendations

Rechargeable batteries have a relatively high self-discharge rate, which is why they should not be stored unattended for extended periods. If left unchecked, their voltage may drop to near *0V*.

> [!IMPORTANT]
> Some battery chemistries, such as *lithium-based rechargeable batteries*, **must be kept at a certain minimum voltage**. Allowing the voltage to drop below a critical threshold—either due to excessive over-discharge or self-discharge—can permanently damage or even destroy the battery.

Not all battery chemistries are susceptible to permanent damage from low voltage. While all lithium-based batteries can be harmed, other chemistries, such as *NiCd*, can sustain even extended *0V* charge levels without issues.

For this reason, it's important to follow a few guidelines when storing rechargeable batteries for long periods (months to years):

* **Storage Charge:** Charge the batteries to around *50% SOC* (state of charge) before storing them. Higher SOCs lead to faster self-discharge, while lower SOCs reduce the time before the battery voltage drops to critical levels. Only *LiFePO₄* batteries should be fully charged to 100% when stored.
* **Temperature:** Store batteries at temperatures below 20°C. Higher temperatures significantly increase the self-discharge rate.
* **Monitor and Recharge:** Regularly check the battery voltage and recharge it when the voltage drops below 20–30% SOC. Always fully recharge the battery before use if it has been in extended storage.

 

> Tags: Battery, Rechargeable, Disposable

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/batterytypes?261774121809244816) - created 2024-12-08 - last edited 2024-12-08
