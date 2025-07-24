<img src="/assets/images/components.png" width="80%" height="80%" />
 
# Level Shifter

> Translating Logic Levels Between Different Voltages

Level shifters are electronic circuits used to interface components that operate at different voltage levels. Level shifters safely translate signal voltages from one logic level to another. For example, a microcontroller running at 3.3V needs to communicate with a device that requires 5V logic signals, or vice versa.

<img src="images/levelshift_overview_t.webp" width="70%" height="70%" />

## Why Level Shifters Matter

Not all parts of a project may operate at the same voltage. For example, a microcontroller may run on *3.3V* but needs to interface with sensors that require higher (e.g., *5V*) or lower voltages (e.g., *1.6V*). Likewise, when controlling car system components, the voltage level of microcontrollers may need to be translated to *12V* or *24V*.

<img src="images/levelshift_bss138_back.webp" width="30%" height="30%" />

Directly connecting components with mismatched voltage standards can lead to malfunction, excessive current draw, or even permanent damage to sensitive devices. **Level shifters safely translate digital signals between different voltages.**

## Level Shifters vs. Resistors

Occasionally, hobbyists connect different voltages directly: 

When operating sensors at *5V*, they connect communication wires—e.g., for *I2C* interfaces—directly to a *GPIO* of a *3.3V microcontroller* (e.g., ESP32). 

Often, this seems to work, and even though not officially confirmed, ESP32 GPIOs are supposedly *5V tolerant*. You may get away with this; however, over-voltage on GPIO pins may not lead to immediate failure, and in the long run can reduce the lifespan of the microcontroller.

More considerate hobbyists frequently use *resistors* to interface different voltage levels, utilizing the resistor as a simple voltage divider. For signals like analog or one-way digital outputs—where the direction is fixed and speed or reliability demands are modest—resistor dividers can suffice if the load and signal integrity requirements are understood and controlled.

However, resistor dividers have key limitations: they are only suitable for unidirectional voltage lowering, can degrade signal integrity due to loading effects, and do not support bidirectional communication well.

**Dedicated active level shifters** (e.g., transistor- or IC-based) offer better signal integrity, support for bidirectional signals (important in protocols like I2C), and protection for sensitive low-voltage devices.

> [!TIP]
> Often, you can eliminate the problem altogether: many sensors run happily in a wide voltage range (i.e., *3.3-5V*), so there may not be the need for voltage differences in the first place. Try and run sensors with the same microcontroller voltage wherever possible.

## Level Shifter Types

There are two main types of logic level shifter boards available:

* **Chip-based:**  
  These use a specialized and highly integrated chip (e.g., *TXS0108E*, *TXB0108*, *74LVC245*, etc.).

<img src="images/txs0108e_levelshift_top_t.webp" width="30%" height="30%" />

* **Discrete MOSFET-based:**  
  These use dedicated *MOSFET* transistors (*BSS138* and similar).

<img src="images/levelshift_bss138_top.webp" width="25%" height="25%" />

### MOSFET-based Level Shifters

Level shifters with discrete MOSFETs work well for **specific use cases** due to their operating principles:

* **Open-Drain/Open-Collector:**  
  Well-suited for open-drain or open-collector outputs such as *1-Wire* and *I2C*.
* **Bidirectional:**  
  Support bidirectional signals by design.
* **Voltage Crossing:**  
  May function even when `LV` (lower voltage side) is higher than `HV` (higher voltage side) due to the *body diode effect*.
* **Low Speed:**  
  Typically work up to *400kHz*, which suffices for *I2C* but is too slow for *WLED*.

## Wiring

Level shifters are designed to translate between two systems with **stable** (but different) voltages: one side connects to the *higher* voltage (often marked `HV`), and the other to the *lower* voltage (marked `LV`).

<img src="images/levelshift_bss138front.webp" width="30%" height="30%" />

Basic wiring steps:

* **LV:** Connected to the lower voltage supply  
* **HV:** Connected to the higher voltage supply  
* **Lx:** Signal line of the lower voltage system (where *x* is a channel number)  
* **Hx:** Signal line of the higher voltage system (where *x* is a channel number)  
* **`GND`:** Both sides must share a common ground

To add a level shifter to your project:

* Connect the positive rail of the lower voltage system to `LV`, and of the higher voltage system to `HV`.
* Connect `GND` to the ground of both sides; ground must be shared between the two systems.
* Connect the data lines to `LVx` and `HVx` according to channel numbers.

> [!IMPORTANT]
> With most level shifter types, the lower voltage must always be lower than the higher voltage for guaranteed correct operation.

## Selecting Appropriate Level Shifter

While all level shifters generally translate digital signals between two voltage domains, there are significant differences in **how** they do this, so level shifters should be carefully selected to match a given use case.

### 1-Wire

*1-Wire* operates with minimal wiring (*one data wire* plus ground), often powered parasitically through the bus. It's common for simple sensor connections (e.g., [Dallas Temperature Sensors](https://done.land/components/data/sensor/temperature/dallas/)).

Characteristics for 1-Wire level shifting:

* **Strong pull-down capability** is required, especially for long cables/capacitive buses; chip-based shifters may not always provide enough current.
* **Fast, clean transitions** are needed for reliable timing; slow edges from some chip-based shifters may cause errors.

Here are recommended level shifters for *1-Wire*:

| Device / Chip | Max Speed | Typ. External Pullups | Significant Remarks |
|---|---|---|---|
| [BSS138 MOSFET (Discrete)](https://done.land/components/signalprocessing/levelshifter/bss138/) | <100kHz (typical) | 4.7kΩ–10kΩ | limited speed, low-cost, ESD-sensitive |
| MAX3394E | ≥400kHz | 4.7kΩ–10kΩ | ESD protected, designed for 1-Wire, handles capacitance well, Maxim Integrated-recommended |
| LSF0102 | Up to 1MHz (typical) | 4.7kΩ–10kΩ | Specifically recommended for 1-Wire, low power, open-drain compatible |
| PCA9306 | Up to 1MHz (I²C typical) | 4.7kΩ–10kΩ | Designed for I²C, used for 1-Wire with external pullups |

### I²C

*I²C* is a *two-wire* interface and bus used for peripherals with *moderate data rates* (e.g., sensors, displays).

Requirements for I²C level shifters:

* Must support **bidirectional open-drain** signals.
* Require **pull-up** resistors.

Resistor value should match speed/load—lower resistance for higher speed/longer cables.

| Device Used On Board | Max Speed | Built-In Pullups | Significant Remarks |
|---|---|---|---|
| [BSS138 MOSFET (Discrete)](https://done.land/components/signalprocessing/levelshifter/bss138/) | ~400kHz (I²C Fast-mode) | 10kΩ | Simple, low-cost, needs correct pullups, ESD sensitive |
| Pololu 4-Ch (BSS138 board) | ~400kHz | 10kΩ | Supports up to *18V* |
| [TXS0108E](https://done.land/components/signalprocessing/levelshifter/txs0108e/) | 1.2Mbps (open-drain) | 4kΩ | Auto direction, good ESD protection, supports open-drain |
| PCA9306 | Up to 400kHz, 1MHz typical | None (external 10kΩ) | Explicitly for I²C/SMBus, common on dev boards |
| LSF0102 | Up to 1MHz | None (external 4.7–10kΩ) | Specialized, robust for I²C, TI/NXP recommended |
| TCA9517A | 1MHz | None (external) | I²C buffer/repeater, tolerates heavy capacitive loads, bus recovery |
| NLSX4373 | Up to 400kHz | None (external) | Logic converter module IC, robust open-drain support |

### WLED/NeoPixel/WS2812/Addressable LED

When a *5V* LED strip is controlled by a *3.3V* microcontroller, a level shifter may be needed: 

Once the cable length to the first LED exceeds a certain threshold (e.g., > *1m*), the strip may start to flicker or show distorted colors.

Addressable LEDs use a special *one-wire* protocol (not to be confused with **1-Wire**). It works **unidirectional** (from microcontroller to LED strip) at speeds of around *800kHz* (no clock line, fixed timing at 1.25μs per bit).

The protocol only requires the controller to actively drive the data line. Each WS2812 chip relays the remaining data downstream passively after latching its own data, but does not actively drive the line high and low in a push-pull manner.

In terms of level shifting, the requirements are:

* **Speed:**  
  Must support speeds of *800kHz*. Level shifters designed for I²C (open-drain) are usually too slow for WLED and can result in unreliable performance.
* **Current:**  
  Sufficient output current capability (strong drive) is needed to overcome capacitance on longer wires — especially for setups where the controller is more than 15–50cm from the first pixel of the LED strip.
* **Clean Edges:**  
  Must support precise, fast edge transitions. It must propagate fast, clean edges to avoid glitches, color misfires, or strip flicker.

While you occasionally see reports claiming that *I2C level shifters* work with *WLED*, such reports are often misconceptions: under **ideal circumstances** (short cable and/or strip length, and/or no `GND` wire close to the `DATA` wire), even sub-optimal level shifters may appear to work.

For best performance, choose a level shifter that is recommended specifically for *WLED signals*:

| Device / Chip   | Max Speed     | Built-In Pullups | Significant Remarks                                   |
|-----------------|---------------|------------------|------------------------------------------------------|
| SN74AHCT125N    | >20MHz        | No               | Excellent for addressable LED signal translation; unidirectional buffer/line driver |
| SN74AHCT245     | >20MHz        | No               | Octal bus transceiver with direction control; good for LED data needing isolation or buffering |
| SN74HCT14       | >10MHz (typical) | No             | Hex Schmitt-trigger inverter; signal conditioner for noisy or slow signals |
| SN74HCT04       | >10MHz (typical) | No             | Hex inverter; used similarly for signal conditioning; may invert LED data, requiring extra logic |

### Simple GPIOs

For basic GPIO translation (e.g., controlling *12V car electronics* with a *3.3V* microcontroller):

* **Resistor May Suffice** for reading a high-voltage GPIO, as a divider; for output driving, use a true level shifter.
* **Push-Pull:** GPIOs are often actively driven (high or low), called push-pull—unlike open-drain in buses.
* **Uncritical Timing:** Nanosecond precision is not critical for casual GPIO translation.

Almost any level shifter can work, but ensure voltage compatibility especially for automotive or industrial contexts.

#### Caveats When Using I²C-Level Shifters for GPIOs

I²C shifters (open-drain) risk power waste or failure if both sides drive the line oppositely. In I²C, devices only pull low, with pullups providing high. Using these for GPIO push-pull communication runs the risk of short circuits, but this can be managed if you control at least one side.

Still, dedicated *push-pull level shifters* provide better protection.

| Device / Chip | Significant Remarks | Safe |
|---|---|---|
| [BSS138 MOSFET (Discrete)](https://done.land/components/signalprocessing/levelshifter/bss138/) | Simple, moderate speeds, DIY/commercial modules | ❌ |
| Pololu 4-channel board | Bi-directional, handles 1.5V–18V, MOSFET + pullups | ❌ |
| BS170 MOSFET (Discrete) | Like BSS138, up to 18V, simple control | ❌ |
| CD40109B | 4-channel CMOS, 3–18V, high-voltage applications | ✅ |
| [EzSBC LS2/LS3](https://done.land/components/signalprocessing/levelshifter/ezsbc/) | Unidirectional, 3.3–18V translation | ✅ |
| TXB0108/TXB0104 | Auto-direction, high-speed push-pull, low drive | ✅ |
| [TXS0108E](https://done.land/components/signalprocessing/levelshifter/txs0108e/)/TXS0102 | Open-drain & push-pull, works for many GPIO applications | ✅ |
| SN74AHCT125 / SN74AHCT245 | Strong driver, robust, fast, not bidirectional, ideal for 3.3V↔5V | ✅ |
| 74HCT14 / 74HCT04 | Signal cleanup, not a translator per se | ✅ |
| Voltage Divider (Resistors) | Ultra-simple, very low speed, basic logic only | ❌ |

### UART

*UART* (*Universal Asynchronous Receiver/Transmitter*) is a traditional serial interface, found on microcontrollers and PCs.

Features:

* Two wires, *1:1* communication.
* Each line is **unidirectional**: TX→RX.
* TX pin is **actively driven** (push-pull output). No pull-ups are required.

Recommended level shifters for UART should be optimized for push-pull, not for I²C/1-Wire.

| Device / Chip | Max Speed | Built-In Pullups | Significant Remarks |
|---|---|---|---|
| 2N7001T | Up to 30MHz+ | None | High speed, good for UART, ESD robustness varies |
| [TXS0108E](https://done.land/components/signalprocessing/levelshifter/txs0108e/) | 110Mbps | 4kΩ (`high`)/40kΩ (`low`) | Common, available, affordable |
| TXB0108 | 60Mbps (1:1), 20Mbps (30pF) | 50kΩ | Chosen in industrial cases, TXS0108E is often more affordable and outperforms |
| SN74LVC2T45 | 420Mbps (1.8V–3.3V), 200Mbps (3.3V–5V) | None | Dual-channel hi-speed, direction pin, robust for fast UART |
| 74LVC1T45 | 420Mbps | None | Uni/bi-directional (direction pin), high speed, good for fast UART |
| TXS0102 | 24Mbps | 10kΩ | Dual-channel, handles UART up to 8Mbps, open-drain support |

### SPI

*SPI* is a high-speed bus for peripherals (e.g., displays, SD cards).

Compared to UART:

* **Much higher speed** (10–50Mbps, sometimes more).
* **Synchronous, clocked signals**—timing is critical.
* Level shifters must be ultra-fast and support push-pull, not open-drain.

| Device / Chip | Max Speed | Built-In Pullups | Significant Remarks |
|---|---|---|---|
| TXB0108 | 60Mbps (1:1), 20Mbps (30pF) | 50kΩ | Bidirectional, auto-sensing, optimized for push-pull |
| SN74LVC2T45 | 420Mbps (1.8V–3.3V), 200Mbps (3.3V–5V) | None | Direction pin, robust at SPI speeds |
| 74LVC1T45 | 420Mbps | None | Direction pin, strong drive |
| SN74LVC8T245 | 420Mbps | None | 8-bit, for wide/multichannel SPI |
| TXB0104 | 100Mbps (typ) | 50kΩ | 4-channel, push-pull only, great for short SPI lines |
| 2N7001T | 100Mbps | None | Unidirectional, reliable at high-speed SPI |

### RS232

Industrial/PC devices commonly use a classic 9-pin **RS232** interface. Compared to *UART*, **SPI**...

* has very strict timing requirements (clocked, synchronous signals)
* has a much higher data rate and reach 10–50Mbps (sometimes more, especially with SD cards)	

This limits the level shifter selection and excludes i.e. chips like [TXS0108E](https://done.land/components/signalprocessing/levelshifter/txs0108e/) and certainly MOSFETs like [BSS138](https://done.land/components/signalprocessing/levelshifter/bss138/) for their insufficient speed.

Level shifters must handle conversion between TTL/CMOS logic and RS232 domain.

| Device / Chip | Max Speed | Built-In Features | Significant Remarks |
|---|---|---|---|
| MAX232 | 120kbps | Integrated charge pump, capacitors required | Classic RS232↔TTL, robust, 5V, 2 drivers/receivers |
| MAX232A | 230kbps | Charge pump, lower capacitance | Improved MAX232, faster/lower power |
| MAX3232 | 250kbps | Charge pump, 3.0–5.5V supply | Supports modern MCUs, industry standard |
| MAX3243 | 250kbps | 8-channel, ±15kV ESD | Supports full DE-9, flow control, 3.3–5V |
| MAX233/233A | 115/230kbps | Internal cap/charge pumps | No external capacitors needed, compact |
| SP3232 | 250kbps | Max3232-compatible | 3.0–5.5V, robust ESD |
| TRS3122E | 1000kbps | Low voltage, VL ref, ±15kV ESD | For 1.8V–3.3V MCUs, very fast |

## Galvanically Isolated Level Shifters

Conventional level shifters require a *common ground* between voltage domains, meaning no true galvanic isolation—both sides are electrically connected.

### Why Galvanic Isolation May Matter

Galvanic isolation is needed when:

* **Voltage crossing:** `LV` may exceed `HV` (battery management). MOSFET body diode is not a robust solution for this.
* **Noise:** Preventing noise/distortion in audio and sensitive signals.
* **Safety:** Isolation from dangerous voltages/leakage.

### Optocouplers Are Slow

Optocouplers can provide isolation, but are generally too slow for modern fast interfaces.

### Specialized Level Shifter ICs

*Galvanically isolated level shifters* (e.g., ISO1540, ISO1640) feature completely separate voltage domains. They're common in power management with rechargeable batteries and in safety-critical designs.

## Common Pitfalls

- **Do not treat all level shifters the same;** always match specs to your use case.
- **Do not assume ESP32 or similar MCUs are always 5V tolerant.** Check datasheets, use a level shifter or protective resistor.
- **Do not rely on resistor dividers for bidirectional protocols** (like I²C) or for fast signals.
- **For discrete MOSFET shifters, assign LV/HV per expected voltage ranges,** and avoid LV > HV where possible.

> Tags: Level Shifter, Logic Level Converter, BSS138, TXS0108E, TXB0108, SN74LVC245, 74LVC245, PCA9306, LSF0102, Pololu Level Shifter, MAX3394E, MAX232, MAX3232, MAX3243, MAX233, SN74AHCT125N, SN74AHCT245, SN74HCT14, SN74HCT04, CD40109B, EzSBC LS2, EzSBC LS3, TCA9517A, NLSX4373, TXS0102, 2N7001T, Voltage Divider, Voltage Crossing, Body Diode Effect, ESD Protection, MOSFET Level Shifter, Chip-based Level Shifter, Discrete Level Shifter, I2C, UART, SPI, RS232, Open-Drain, Push-Pull, Pull-up Resistor, GPIO, WLED, NeoPixel, WS2812, Addressable LED, 1-Wire, IP5306, LiIon, ISO1540, ISO1640, Optocoupler, Galvanic Isolation

[Visit Page on Website](https://done.land/components/signalprocessing/levelshifter?519094071721255105) - created 2025-07-20 - last edited 2025-07-22
