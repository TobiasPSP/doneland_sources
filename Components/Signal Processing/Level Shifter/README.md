<img src="/assets/images/components.png" width="80%" height="80%" />
 
# Level Shifter

> Translating Logic Levels Between Different Voltages

Level shifters are electronic circuits to interface components that operate at different voltage levels. Level shifters safely translate signal voltages from one logic level to another. For example, a microcontroller running at 3.3V needs to communicate with a device that requires 5V logic signals, or vice versa.

<img src="images/levelshift_bss138front.webp" width="50%" height="50%" />

## Overview
Not all parts of a project may operate at the same voltage. For example, a microcontroller may run on *3.3V* but needs to interface sensors that require *5V* or *1.6V*. Likewise, when controlling car system components, the voltage level of microcontrollers may need to be translated to *12V* or *24V*.

<img src="images/levelshift_bss138_back.webp" width="50%" height="50%" />

Directly connecting components with mismatched voltage standards can lead to malfunction, excessive current draw, or even permanent damage to sensitive devices. Level shifters safely translate digital signals between different voltages.

### Level Shifters vs. Resistors
Occasionally, hobbyists connect different voltages directly: when they operate a sensor at *5V*, they connect communication wires, i.e. for *I2C* interfaces, directly to a *GPIO* of a *3.3V microcontroller*, i.e. a *ESP32*. Often, this seems to work, and even though not officially confirmed, *ESP32* GPIOs are supposingly *5V tolerant*. You may get away with this, however over-voltage on GPIO pins may not lead to immediate failure and can backfire later when the lifespan of the microcontroller is significantly shortened.

More considerate hobbyists frequently use *resistors* to interface different voltage levels, utilizing the resistor as a simple voltage divider. For signals like analog or one-way digital outputs where the direction is fixed and speed/reliability demands are modest, resistor dividers can suffice if the load and signal integrity requirements are understood and controlled. 

However, resistor dividers have key limitations: they are only suitable for unidirectional voltage lowering, they can degrade signal integrity due to loading effects, and they do not support bidirectional communication well.

Dedicated active level shifters (e.g., transistor- or IC-based) offer better signal integrity, support for bidirectional signals (important in protocols like I2C), and protection for sensitive low-voltage devices.

## Level Shifter Types
Typically, there are two different types of logic level shifter boards available:

* **Chip-based:**      
  These use a specialized and highly integrated chip (i.e. *TXS0108E*, *TXB0108*, *74LVC245*, and similar)
* **MOSFET-based:**    
  These use dedicated *MOSFET* transistors (*BSS138* and similar)

On first sight, they behave similarly:

* **LV:** connected to the lower voltage supply
* **HV:** connected to the higher voltage supply
* **`GND`:** both sides must share a common ground

However, on closer inspection, there are subtle differences that can be key for your intended use case:

| Feature          | Discrete MOSFET (BSS138) Shifter        | IC-Based (Chip) Level Shifter            |
|----------------------------|-----------------------------------------|------------------------------------------|
| **Cost**                   | Low (≈$0.05–0.20/component); breakout boards ≈$0.30–1.00[1] | Moderate (≈$0.50–$2.50 depending on channels & features)[2]   |
| **Speed**      | I²C, SPI, UART up to ~400kHz (I²C) | often rated for >24MHz (ideal for fast bus interfaces like SDIO, fast SPI, parallel data) |
| **Bidirectional**       | Yes (auto-sensing, open-drain buses); ideal for I²C, 1-Wire          | Yes (auto or direction-controlled, depending on IC); supports many protocols, suitable for push-pull and open-drain buses |
| **I2C Voltage Crossing**    | Yes (Body Diode Effect) | No (LV must always be lower than HV) |
| **Power Consumption**      | Negligible    | Low, but ICs may have quiescent current |
| **Robustness/ESD**         | Can be damaged by electrostatic voltage    | often includes ESD, short-circuit, overvoltage protection, and thermal shutdown features |
| **Channel Count**          | typically 1–4    | Commonly 4, 8, or 16   |
| **Board Space**            | Small    | Larger |
| **Ease of Use**            | Simple     | Simple |
| **Typical Use Cases**      | Hobbyist/DIY, simple MCU interface, I²C, UART, occasional SPI         | Professional products, high-speed buses, multiplexed data, robust commercial designs |

## Translating Voltages

Level shifters are designed to translate between two systems with **stable** (but different) voltage: one side of the level shifter connects to the *higher* voltage (often marked `HV`), whereas the other side connects to the *lower* voltage (often marked `LV`).

<img src="images/levelshift_bss138_top.webp" width="50%" height="50%" />

* Connect the positive rail of the lower voltage system to `LV`, and the positive rail of the higher voltage system to `HV`.
* Connect `GND` to the ground of both sides: ground needs to be shared across the two systems you want to interface. 
* Depending on the number of channels provided by the level shifter, you connect the data lines to `LVx` and `HVx`, respectively, where "x" stands for the channel number.

The *lower* voltage **must always be lower** than the *higher* voltage. 

### Voltage Crossing

Occasionally, you may come across a special challenge when one system runs dynamically on a wide voltage range that may overlap the voltage of the other system.

For example, when interfacing with the *LiIon* charger IC *IP5306*, this chip runs on battery voltage in a range of *2.8-4.2V*. When you interface this range with a modern *3.3V* microcontroller, the *IP5306* voltage can be *lower* **or** *higher* than the microcontroller voltage.

To solve this issue, there are two options:

* **Resolve Problem:**    
  Pick a microcontroller that runs on *5V* instead of *3.3V*, placing its voltage on the *high* side.
* **Use discreet logic level shifter:**    
  Choose a discreet logic level shifter (i.e. based on *BSS138*) rather than a chip-based one. Only the discrete MOSFET solution allows accidental or "quasi-working" operation when the voltage rails cross, thanks to the body diode. IC-level shifters are more strict and do not tolerate this.     

    Connect the *3.3V* side to `LV` and the *2.8-4.2V* side to `HV` (as this side is higher than *3.3V* most of the time, minimizing the body diode effect to nearly empty battery scenarios)

### Body Diode Effect
 The MOSFET shifter is guaranteed to function properly only when `LV` ≤ `HV`. This ensures the correct Vgs/Vds biasing for normal switching. When `LV` voltage is higher than `HV` voltage, you are operating the level shifter outside its specifications.

Chip-based level shifters would stop working reliably when `LV` > `HV`. *MOSFET*-based level shifters however tolerate `LV`> `HV`: 

The internal body diode of a MOSFET permits current to flow in one direction, meaning a logic `LOW` from the higher-voltage side (in this special case on `LV`) can pull down the lower-voltage line (in this special case the `HV` side) via the diode. 

This lets `LOW` signals propagate, often enough for a basic communication link to appear to "work" in some directions, especially for I²C lines with pull-up resistors on both sides.

However, the *Body Diode Effect* is working merely "accidental", and in critical designs, other and more reliable techniques should be favored.

> Tags: BSS138, TXS0108E, Voltage Crossing, Body Diode Effect

