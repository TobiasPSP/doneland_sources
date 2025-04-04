<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Primary Batteries  

> Primary Batteries Provide Portable Power. They Cannot Be Recharged. Once Depleted, They Must Be Discarded.  

**Primary batteries** are widely used for their low cost, high energy density, and convenience. Unlike rechargeable batteries, they cannot be recharged, making them disposable after use.  

For low-power applications, such as sensors or microcontroller projects that spend most of their time in low-power states, primary batteries are often a better choice. These devices can run for months or even years on a single battery. In such cases, the cost, complexity, and energy overhead of incorporating rechargeable batteries and chargers may not be justified.  



## Form Factors  

Primary batteries are available in various standardized shapes and sizes to suit a wide range of devices.  

The battery form factor is often classified as **LRXX**, where *XX* denotes a numeric value:

* **L:** stands for *alkaline chemistry*
* **R:** stands for *round (cylindrical) shape*

Here is a list of common battery form factors and use cases:

| **Form Factor** | **Description**                          | **Typical Uses**                        |  
|------------------|------------------------------------------|-----------------------------------------|  
| **N (LR1)**   | Smaller cylindrical, 30.2mm x 12mm      | Small electronics, medical devices |  
| **AAA (LR03)**   | Smaller cylindrical, 44mm x 10.5mm      | Compact devices like remotes, toys, clocks, LED lights |  
| **AA (LR6)**    | Cylindrical, 50mm x 14mm                | Flashlights, cameras, toys          |  
| **C (LR14)**     | Cylindrical, 50mm x 26mm                | Flashlights, radios, larger toys               |  
| **D (LR20)**     | Cylindrical, 61mm x 34mm                | High-power devices like lanterns and flashlights      | 
| **Button Cell (LR44)**     | Cylindrical, 11.6mm x 5.4mm                | Humidity sensors, electronic calipers      |  
| **9V (PP3)**     | Rectangular, six 1.5V cells in series   | Smoke detectors, walkie-talkies        |  
| **Coin Cells**   | Flat, small round batteries (e.g., CR2032) | Watches, key fobs, calculators         |  

The larger a battery is, the more capacity it typically has, and the more energy it can supply. That's why the larger *AA* batteries are typically reserved for power-hungry applications whereas the smaller *AAA* batteries are used in less power consuming devices.

Even within a given form factor, there can be tremendous differences in battery capacity, depending on the chemistry the battery uses, and individual quality factors. 

Generally, when comparing battery quality, *weight* is a simple indicator of quality: the heavier a battery is, the more energy it can typically supply. Precise results can only be acquired with a [capacity tester](https://done.land/components/power/powersupplies/battery/batterytesters/) which would drain the battery and render it useless, so capacity testing non-rechargeable batteries makes only sense for testing (and wasting) one specimen to evaluate a battery type from a particular vendor.

> [!IMPORTANT]
> [Capacity Testers](https://done.land/components/power/powersupplies/battery/batterytesters/all-in-onetesters/single-batterytester/) are typically designed for testing *rechargeable* batteries, and often they come with a build-in charger. Make sure you understand the particular tester and disable its charging features before you test primary batteries.

## Chemistries  

Primary batteries differ in their chemical composition, which affects their voltage, energy density, shelf life, and environmental impact.  

| **Chemistry**      | **Voltage** | **Energy Density** | **Shelf Life**   | **Environmental Impact**            | **Typical Uses**               |  
|---------------------|-------------|--------------------|------------------|--------------------------------------|--------------------------------|  
| **Alkaline**       | 1.5V        | Moderate           | 5-10 years      | Low, but not reusable               | Everyday electronics (e.g., remotes, clocks) |  
| **Zinc-Carbon**    | 1.5V        | Low                | 2-3 years       | Low, inexpensive                    | Low-drain devices (e.g., radios) |  
| **Lithium (LiMnO₂)** | 3V         | High               | 10+ years       | Low toxicity, recyclable            | Cameras, medical devices       |  
| **Silver Oxide**   | 1.55V       | High               | 5-10 years      | Low, but limited availability       | Watches, hearing aids          |  
| **Mercury Oxide**  | 1.35V       | Moderate           | Long            | High toxicity, discontinued in most regions | Specialty devices (now obsolete) |  


### Key Comparisons  

| **Feature**        | **Alkaline**         | **Zinc-Carbon**    | **Lithium** (non-rechargeable)            | **Silver Oxide**      | **Mercury Oxide**      |  
|--------------------|----------------------|--------------------|------------------------|-----------------------|------------------------|  
| **Voltage**        | 1.5V                 | 1.5V               | 3V                     | 1.55V                 | 1.35V                 |  
| **Energy Density** | Moderate             | Low                | High                   | High                  | Moderate              |  
| **Cost**           | Moderate             | Low                | High                   | High                  | High                  |  
| **Shelf Life**     | 5-10 years           | 2-3 years          | 10+ years              | 5-10 years            | Long (but obsolete)    |  
| **Best For**       | Everyday devices     | Low-drain devices  | High-drain or long-life devices | Precision instruments | Specialty (now rare)   |  

**Cost Comparison:**
- **Alkaline:** Moderate cost, widely available.
- **Zinc-Carbon:** Very low cost, but lower performance and shorter lifespan.
- **Lithium:** High cost but offers the longest shelf life and high energy density, ideal for high-drain and long-life applications.

> [!TIP]
> As a practical comparison, an average AAA Alkaline battery has a capacity around *700mAh* whereas an AAA Lithium battery (**non**-rechargeable) is around *1200mAh* - at around **5x** the cost. Lithium-based primary batteries can still be worth the money. The raw *mAh value* is just one aspect. A test with a wireless temperature sensor showed that alkaline AAA batteries had to be replaced once a month whereas lithium-based batteries lastet almost three months. 

### Final Notes  

Primary batteries are an excellent option for applications requiring simplicity, long storage life, or infrequent use. 

Choosing the right chemistry and form factor ensures optimal performance and cost-effectiveness. While their non-rechargeable nature limits reusability, many primary batteries are recyclable, helping to reduce environmental impact.


> Tags: Battery, Primary, Non-Rechargeable

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/batterytypes/primary?280698121809244816) - created 2024-12-08 - last edited 2025-01-15
