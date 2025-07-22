<img src="/assets/images/components.png" width="80%" height="80%" />
 

# Level Shifter

> Translating Logic Levels Between Different Voltages

Level shifters are electronic circuits used to interface components that operate at different voltage levels. Level shifters safely translate signal voltages from one logic level to another. For example, a microcontroller running at 3.3V needs to communicate with a device that requires 5V logic signals, or vice versa.

<img src="images/levelshift_overview_t.webp" width="70%" height="70%" />

## Why Level Shifters Matter

Not all parts of a project may operate at the same voltage. For example, a microcontroller may run on *3.3V* but needs to interface with sensors that require *5V* or *1.6V*. Likewise, when controlling car system components, the voltage level of microcontrollers may need to be translated to *12V* or *24V*.

<img src="images/levelshift_bss138_back.webp" width="30%" height="30%" />

Directly connecting components with mismatched voltage standards can lead to malfunction, excessive current draw, or even permanent damage to sensitive devices. **Level shifters safely translate digital signals between different voltages.**

## Level Shifters vs. Resistors

Occasionally, hobbyists connect different voltages directly: when they operate a sensor at *5V*, they connect communication wires—e.g. for *I2C* interfaces—directly to a *GPIO* of a *3.3V microcontroller* (e.g. ESP32). Often, this seems to work, and even though not officially confirmed, ESP32 GPIOs are supposedly *5V tolerant*. You may get away with this; however, over-voltage on GPIO pins may not lead to immediate failure and can reduce the lifespan of the microcontroller.

More considerate hobbyists frequently use *resistors* to interface different voltage levels, utilizing the resistor as a simple voltage divider. For signals like analog or one-way digital outputs—where the direction is fixed and speed or reliability demands are modest—resistor dividers can suffice if the load and signal integrity requirements are understood and controlled.

However, resistor dividers have key limitations: they are only suitable for unidirectional voltage lowering, can degrade signal integrity due to loading effects, and do not support bidirectional communication well.

**Dedicated active level shifters** (e.g., transistor- or IC-based) offer better signal integrity, support for bidirectional signals (important in protocols like I2C), and protection for sensitive low-voltage devices.

## Level Shifter Types

Typically, there are two main types of logic level shifter boards available:

* **Chip-based:**  
  These use a specialized and highly integrated chip (e.g. *TXS0108E*, *TXB0108*, *74LVC245*, and similar).

  <img src="images/txs0108e_levelshift_top_t.webp" width="30%" height="30%" />

* **Discrete MOSFET-based:**  
  These use dedicated *MOSFET* transistors (*BSS138* and similar).

  <img src="images/levelshift_bss138_top.webp" width="25%" height="25%" />

At first glance, they behave similarly:

* **LV:** Connected to the lower voltage supply  
* **HV:** Connected to the higher voltage supply  
* **`GND`:** Both sides must share a common ground

However, on closer inspection, there are subtle differences that can be key for your intended use case:

| Feature                | Discrete MOSFET (BSS138) Shifter                                                   | IC-Based (Chip) Level Shifter                                                                           |
|------------------------|------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------|
| **Cost**               | Low (≈$0.05–0.20/component); breakout boards ≈$0.30–1.00[1]                        | Moderate (≈$0.50–$2.50 depending on channels & features)[2]                                             |
| **Speed**              | I²C, SPI, UART up to ~400kHz (I²C). Limited by MOSFET Rds(on) and pull-up choice   | Often rated for >24MHz (ideal for fast bus interfaces like SDIO, fast SPI, parallel data)               |
| **Bidirectional**      | Yes (auto-sensing, open-drain buses); ideal for I²C, 1-Wire                        | Yes (auto or direction-controlled, depending on IC); supports push-pull and open-drain protocols        |
| **I2C Voltage Crossing** | Yes (body diode enables partial operation if HV < LV, but not fully reliable)    | No (will not operate or may be damaged if LV > HV)                                                      |
| **Power Consumption**  | Negligible; mostly static current via pull-ups                                     | Low, but ICs may have a small quiescent current                                                         |
| **Robustness/ESD**     | Can be damaged by electrostatic discharge; basic protection                        | Often includes ESD, short-circuit, overvoltage protection, and thermal shutdown features                |
| **Channel Count**      | Typically 1–4                                                                      | Commonly 4, 8, or 16                                                                                    |
| **Board Space**        | Small                                                                              | Efficient for many signals; single chip streamlines board space                                         |
| **Ease of Use**        | Simple, easy for DIY or breadboarding                                              | Simple to use; datasheet reading may be needed for full understanding                                   |
| **Typical Use Cases**  | Hobbyist/DIY, simple MCU interface, I²C, UART, occasional SPI                      | Professional products, high-speed buses, multiplexed data, robust commercial designs                    |

---

## Translating Voltages

Level shifters are designed to translate between two systems with **stable** (but different) voltages: one side of the level shifter connects to the *higher* voltage (often marked `HV`), whereas the other side connects to the *lower* voltage (often marked `LV`).

<img src="images/levelshift_bss138front.webp" width="30%" height="30%" />

* Connect the positive rail of the lower voltage system to `LV`, and the positive rail of the higher voltage system to `HV`.
* Connect `GND` to the ground of both sides: ground needs to be shared across the two systems you want to interface.
* Depending on the number of channels provided by the level shifter, you connect the data lines to `LVx` and `HVx`, respectively, where "x" stands for the channel number.

> **The lower voltage must always be lower than the higher voltage for guaranteed correct operation of all types.**

## Voltage Crossing (Dynamic Rails and Special Cases)

Occasionally, you may face a special challenge if one system runs on a wide voltage range that can overlap the voltage of the other system.

For example, when interfacing with the *LiIon* charger IC *IP5306*, this chip runs on battery voltage in a range of *2.8–4.2V*. When you interface this range with a modern *3.3V* microcontroller, the *IP5306* voltage can be *lower* **or** *higher* than the microcontroller voltage.

To solve this issue, consider these options:

- **Choose a higher-voltage microcontroller:**  
  Use a microcontroller running on *5V* instead of *3.3V*, guaranteeing its supply is always on the higher side.
- **Use a discrete MOSFET level shifter:**  
  Select a level shifter based on a discrete MOSFET (i.e. *BSS138*). **Only discrete MOSFET solutions can permit accidental or partial ("quasi-working") operation when voltage rails cross, thanks to the body diode.** Most IC-based shifters are strict and may malfunction or become damaged when HV < LV.

  Connect the *3.3V* side to `LV` and the *2.8–4.2V* side to `HV` (as this side is higher than *3.3V* most of the time, minimizing reliance on the body diode effect to nearly empty battery scenarios).

> **Note:** Even when using a discrete MOSFET shifter, reliability is only guaranteed when `LV` ≤ `HV`.

## Body Diode Effect

The MOSFET shifter is **guaranteed to function properly only when `LV` ≤ `HV`**. This ensures the correct *Vgs/Vds* biasing for normal switching. When `LV` voltage is higher than `HV` voltage, you are operating the level shifter **outside of its specifications**.

**In chip-based level shifters, the circuit will not function if `LV` > `HV`. They may stop translating, go into error, or risk damage.**

With discrete MOSFET-based shifters, however, **LOW signals can still propagate via the body diode even when `LV` > `HV`**. This lets a logic LOW from the higher-voltage side (now on `LV`) pull down the lower-voltage line (on `HV`) through the diode. This effect often allows a basic communication link to appear to "work" in some directions, especially for I²C lines with pull-up resistors on both sides.

> [!IMPORTANT]
> The *body diode effect* is only a convenient side effect. For critical or high-speed designs, this behavior should **not** be relied on: when voltage rails cross, logic compatibility is lost and error rates may increase. Robust board design and proper voltage assignment are strongly recommended for production.



## Common Pitfalls

- **Do not assume ESP32 or similar MCUs are always 5V tolerant.** Check official datasheets.
- **Do not rely on resistor dividers for protocols requiring bidirectionality (like I²C)** or for fast signal edges.
- **When using discrete MOSFET shifters, always assign LV and HV according to the expected voltage ranges** and minimize scenarios where LV > HV.


> Tags: BSS138, TXS0108E, Voltage Crossing, Body Diode Effect, MOSFET Level Shifter, I2C, Logic Level Converter, Voltage Divider, ESD Protection, Bidirectional, UART, SPI, Open-Drain, Pull-Up Resistor, IP5306, LiIon

[Visit Page on Website](https://done.land/components/signalprocessing/levelshifter?519094071721255105) - created 2025-07-20 - last edited 2025-07-20
