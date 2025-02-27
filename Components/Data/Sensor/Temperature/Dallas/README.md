<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# Dallas One-Wire Temperature Sensor

> Affordable Industrial Temperature Sensors That Can Be Daisy-Chained To Monitor Sensitive Devices

## Overview
*Dallas* temperature sensors cover a wide temperature range suitable for many DIY projects: from monitoring deep freezers (down to -55°C) to safe-guarding power supplies or chargers (up to +125°C).

They are exceptionally energy-efficient, requiring **~1mA** during active measurement (peaking at **1.5mA**). This makes them ideal for **battery-operated** applications or monitoring critical components like power supplies or chargers.

### Digital Sensor

Since *Dallas* sensors emit a **digital signal**, a microcontroller is needed to receive and evaluate the sensor output. 

Advantages of Digital Output:

- **One-Wire Protocol:**  
  *Dallas* temperature sensors use the **One-Wire** protocol, requiring only a **single data line** for communication. Multiple sensors can be daisy-chained, as each sensor has a unique **64-bit serial number**.
- **Selectable Resolution:**  
  All models (except the *DS18S20*) support **adjustable resolution**. Lower resolutions result in **faster response times**, while higher resolutions improve **accuracy**.

### Latency (Conversion Time)

The conversion time is the time it takes to receive a temperature reading. It varies based on the selected **resolution**:

| Resolution | Conversion Time (Latency) |
|-----------|--------------------------|
| 9-bit     | 94 ms                     |
| 10-bit    | 188 ms                    |
| 11-bit    | 375 ms                    |
| 12-bit    | 750 ms                    |

Depending on use case, you can prioritize accuracy (higher resolution) or fast and speedy response (lower resolution).

## Sensor Models



| Model       | Temp Range     | Special Features                        | Remarks                                      |
|------------|---------------|-----------------------------------------|----------------------------------------------|
| **DS18B20** | -55°C to +125°C | Waterproof version available, long cable support | Most popular model for DIY and industrial use |
| **DS18S20** | -55°C to +125°C | Fixed 9-bit resolution, slow conversion time | Less commonly used due to high latency |
| **DS1822**  | -55°C to +125°C | Minor internal differences from DS18B20 | Can be an alternative to DS18B20 |
| **DS28EA00** | -40°C to +85°C  | Tamper detection, GPIO support | Used in security, asset tracking, and authentication |

### Special Case: DS18S20
The *DS18S20* is a **low-cost** model with **reduced accuracy and speed**. It only supports **9-bit resolution**, but **does not benefit from the faster 9-bit mode** of other models.

- Unlike other Dallas sensors, the *DS18S20* takes **750ms per reading**, even though its output is limited to **9-bit resolution**.
- Internally, it applies **linear interpolation** to estimate **higher precision**, but it does not actually operate at 12-bit resolution.
- This means the *DS18S20* has **both lower accuracy and higher latency** compared to the *DS18B20*.

## Package Types

Dallas temperature sensors are available in multiple **form factors** to suit different applications. These form factors determine mounting options, durability, and environmental resistance.

## Common Packages

| Package   | Description | Advantages | Common Models |
|--------------|------------|------------|--------------|
| **TO-92**    | Small, three-pin plastic package, similar to a transistor | Compact, inexpensive, easy to integrate into PCBs and breadboards | DS18B20, DS18S20, DS1822 |
| **Stainless Steel Probe** | Waterproof enclosure with pre-attached cable | for outdoor, liquid, and industrial applications | DS18B20 |


### TO-92 
Cost-effective, especially for monitoring the temperature of electronic devices. However, the plastic casing has poor thermal conductivity, so proper placement is crucial.

Use thermal paste or epoxy if mounting on a heat sink or metal surface. Use thermal adhesive tape to fix it to a chassis or PCB.
 
- **Looks Like:** Small black transistor (similar to a 2N2222)
- **Size:** ~4.7mm x 4.0mm x 5.0mm (excluding leads)
- **Disadvantages:** 
  - limited heat dissipation
  - requires external protection if used in harsh environments


### Stainless Steel Probe (Waterproof)
Ensures efficient heat transfer and is ideal for harsh environments.

- **Looks Like:** A sealed metal cylinder with a cable
- **Typical Sizes:** 6mm diameter, 30-50mm length
- **Caveats:** 
  - cannot be directly mounted to a PCB
  - may be overkill (i.e. inside a device enclosure)



> Tags: One-Wire, One Wire, DS18B20, DS18S20, DS1822, DS28EA00
