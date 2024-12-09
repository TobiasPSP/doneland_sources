<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Battery Packs  

> Creating Batteries Out of Individual Battery Cells  

There is an important distinction between a rechargeable *battery cell* and a rechargeable *battery*: the latter is typically a *battery pack* composed of multiple battery cells.  

Battery cells have fixed voltage ranges that depend solely on their chemistry. For instance:  
- A *Li-ion* battery cell operates between *3.0V* (empty) and *4.2V* (full).  
- A *LiFePO₄* (lithium iron phosphate) battery cell ranges from *2.5V* (empty) to *3.65V* (full).  

In contrast, batteries (or *battery packs*) come in a wide variety of voltages and capacities. This is achieved by combining individual battery cells through configurations that connect them *in series* or *in parallel*.  



## Overview  

Batteries are categorized by their *voltages* and *capacities*:  
- **Voltage:** Increased by connecting battery cells *in series* (a configuration called a "string").  
- **Capacity:** Increased by connecting multiple strings *in parallel*.  

For example, consider a traditional lead-acid car battery with a nominal voltage of *12V*. Many modern batteries replace lead-acid with lithium-based chemistries due to their superior energy density and other benefits. To create a lithium-based *12V* battery pack, you would typically connect four lithium cells in series (denoted as *4S*).  

### Chemistry and Voltage  

Depending on the chemistry used, the voltage of a *4S* lithium battery pack approximates *12V*:  

| Chemistry  | Empty   | Full    | Nominal   |  
|------------|---------|---------|-----------|  
| Li-ion     | 12.0V   | 16.8V   | 14.8V     |  
| LiPo       | 12.8V   | 16.8V   | 14.8V     |  
| LiFePO₄    | 10.0V   | 14.6V   | 12.8V     |  

> [!TIP]  
> Lithium-based batteries maintain a relatively stable voltage plateau for most of their state of charge. This makes their *nominal voltage*—the average voltage during normal operation—similar to that of lead-acid batteries. However, when fully charged, lithium batteries can exhibit significantly higher voltages.



### Battery Management System (BMS)  

Most battery packs include a built-in BMS to safeguard against common hazards:  
- **Overcharging:** Prevents exceeding the safe voltage range of the cells.  
- **Over-discharging:** Protects against excessive voltage drops that can damage the battery.  
- **Short circuits:** Limits current to prevent overheating or fires.  

However, certain specialized battery packs, such as those used in RC models and drones, may lack a built-in BMS. Instead, they include a secondary *balancer plug* that provides access to each individual cell. This enables external chargers and balancers to monitor and manage the cells independently, offering greater control for advanced users.



## Key Points on Battery Pack Construction  

- **Series Connections:** Combine cells to increase voltage. For example, a *4S* configuration adds the voltage of four cells together.  
- **Parallel Connections:** Combine strings of cells to increase capacity, sharing the load across multiple cells.  
- **Mixed Configurations:** For higher capacity and voltage, cells are often arranged in both series and parallel, such as *4S2P* (four cells in series, with two parallel strings).  

## Practical Considerations  

When building or selecting a battery pack:  
1. **Ensure Compatibility:** Confirm the voltage range aligns with the device's requirements.  
2. **Use Appropriate Charging Equipment:** If the pack lacks a BMS, use a charger designed for the battery's chemistry with balancing capabilities.  
3. **Prioritize Safety:** Overvoltage and undervoltage conditions can damage cells or pose safety risks, particularly in unprotected battery packs.  

By understanding the principles of battery pack design, you can select or construct packs that meet your specific needs while ensuring safety and performance.

> Tags: Battery Pack

[Visit Page on Website](https://done.land/components/power/battery/batterytypes/rechargeable/batterypacks?326572121809244816) - created 2024-12-08 - last edited 2024-12-08
