<img src="/assets/images/lightning.png" width="100%" height="100%" />


# INA219 Current and Voltage Monitoring

> The INA family of microchips from Texas Instruments is ideal for measuring current and voltage.

[**INA219**](https://www.ti.com/lit/ds/symlink/ina219.pdf) is a microchip from *Texas Instruments* that can measure *current* and *voltage* bidirectionally and calculate *power* (Watts).

<img src="images/ina219_breakout_overview1_t.png" width="80%" height="80%" />

## Overview

A variety of breakout boards are available, featuring either solder pins or pluggable [Grove](https://wiki.seeedstudio.com/Grove_System) connectors ([JST SH 1.0](https://done.land/components/power/cables/connectors/#jst-connectors), *QWIIC*).

<img src="images/ina219_breakout_red_grove_1_t.png" width="40%" height="40%" />

Most boards use an *R100* (0.1 Ohm) shunt resistor, allowing a current range of up to *±3.2 A* (bidirectional), and typically cost well under €2.00 per unit.

> **Tip:**  
> The relatively large current range is due to the built-in *PGA* (programmable gain amplifier), which can amplify the shunt voltage drop by 2x, 4x, or 8x—at the expense of accuracy. Newer chips such as the *INA226* and *INA3221* no longer include a *PGA*, and therefore support lower maximum currents with the same *R100* shunt resistor.

| Spec            | Description                                         |
|-----------------|-----------------------------------------------------|
| Supply Voltage  | 3.3–5V                                              |
| Load Voltage    | 0–26V                                               |
| Interface       | I2C, 16 assignable addresses, default `0x40`/`64`   |
| Max Current     | 3.2A @ R100 (0.1 Ohm) shunt resistor                |

### Shunt Value and Maximum Current

The **INA219** does not measure *current* directly; it measures the *voltage drop* across a **shunt** resistor. The shunt's resistance determines the maximum measurable current.

However, the *INA219* features a *PGA* (programmable gain amplifier) that can increase the current range by factors of 2, 4, or 8, allowing the chip to adapt to different current ranges with optimal precision.

> **Tip:**  
> Newer chips like the *INA226* and *INA3221* do not include a *PGA*, so their current range depends entirely on the shunt resistor. For example, an *INA226* with a typical *R100* (0.1 Ohm) resistor can measure up to 820 mA, and the *INA3221* up to 1.64 A. Thanks to its *PGA*, the *INA219* can measure up to 3.2 A with the same resistor—assuming the PCB traces can handle the current.

#### Integrated Shunts

Most breakout boards come with a presoldered *R100* (0.1 Ohm) shunt resistor, enabling measurement of up to *3.2 A* (with the *PGA* set to 8x). In practice, the maximum usable current also depends on the PCB and trace thickness.  
Always test each breakout board individually to determine its true maximum current capability.

## Breakout Boards

Generic **INA219** breakout boards typically have 6 pins and cost between €0.50 and €1.00:

<img src="images/ina219_breakout__blue_top_t.png" width="50%" height="50%" />

| Pin Label | Description                        |
|-----------|------------------------------------|
| Vin+      | Positive voltage for load circuit  |
| Vin-      | Negative voltage for load circuit  |
| SDA       | I2C data (SDA)                     |
| SCL       | I2C clock (SCL)                    |
| GND       | Common ground                      |
| VCC       | 3.3V/5V supply for INA219          |

- **VCC** and **GND** supply power to the board (supports 3.3V and 5V).
- **VIN+** and **VIN-** carry the load current. These may be duplicated and use thicker traces to support higher currents.
- **SDA** and **SCL** are the I2C communication lines for interfacing with a microcontroller.

### GY-219 Boards

If you plan to measure high currents (2.0–3.4A), look for boards labeled `GY-219`.

The *purple* no-name boards, often marked *GY-219*, use larger PCB traces and a bigger shunt resistor compared to other generic boards.

<img src="images/ina219_purple-gy-219_t.png" width="90%" height="90%" />

These boards are less common and more expensive (€2.00–€5.00).

### Grove Connectors

Some boards feature presoldered *Grove/QWIIC/JST SH1.0* connectors, making it easy to chain multiple I2C sensors.

On these boards, *VCC*, *GND*, *SDA*, and *SCL* are exposed three times: as solder pads and via two Grove connectors, allowing straightforward daisy-chaining of I2C devices.

<img src="images/ina219_breakout_red_top_t.png" width="60%" height="60%" />

> **Tip:**  
> You can connect the board to your microcontroller using the solder pads, turning it into an I2C hub with two additional connectors for more I2C device chains.

The load connects *high-side* via two solder pads to the shunt resistor. The traces are usually thick, but the solder pads may not be labeled, making it unclear which is *Vin+* and which is *Vin-*:

<img src="images/ina219_breakout_red_bottom_t.png" width="60%" height="60%" />

If readings are negative, simply swap the pads.

### Quality Boards

Affordable no-name boards are often *clones* of designs from reputable vendors (such as [Adafruit](https://www.adafruit.com/product/904)). On quality boards, load pins are clearly labeled:

<img src="images/adafruit_ina219_t.png" width="60%" height="60%" />

The Adafruit board, for example, uses a larger shunt resistor, which is beneficial for measuring higher currents due to improved heat dissipation.

Quality comes at a price: Adafruit boards cost around €10.00, while generic versions can be found for €0.50 on AliExpress.

## I2C Address

The *INA219* communicates digitally via [I2C](https://done.land/fundamentals/interface/i2c/), so a microcontroller is required.

I2C is address-based: each device needs a unique address. The *INA219* supports up to 16 different I2C addresses, but most breakout board documentation states that only four are easily configurable.

The default I2C address is `0x40`. To use multiple INA219s, you can change the address via two solder bridges, typically labeled *A0* and *A1*:

<img src="images/ina219_breakout__blue_top_t.png" width="60%" height="60%" />

| A0     | A1     | Address (hex) | Address (decimal) |
|--------|--------|---------------|-------------------|
| -      | -      | `0x40`        | 64                |
| closed | -      | `0x41`        | 65                |
| -      | closed | `0x44`        | 68                |
| closed | closed | `0x45`        | 69                |

### Using 16 I2C Addresses

If you need more than four INA219 boards, you can configure up to 16 different I2C addresses.

This is possible because the `A0` and `A1` pins on the INA219 chip can be connected to `GND`, `VCC`, `SDA`, or `SCL`, resulting in 16 possible configurations.

The solder bridges provide a simple way to connect these pins to `VCC`, allowing easy selection of 4 out of the 16 addresses.

**How it works:**

- Leaving a solder bridge open connects the pin to `GND` (pulled low).
- Closing the solder bridge connects the pin to `VCC`.

#### Identifying True `A0` and `A1`

To configure the remaining 12 addresses, you need to connect `A0` and/or `A1` to different pins. First, identify which side of the solder bridge is the actual chip pin.

Usually, the *inner* pad of the solder bridge is the true chip pin, while the *outer* pad is always connected to *VCC*. You can verify this with a multimeter:

- Measure resistance between the outer pads of both solder bridges—they should be close to 0 Ohms (connected).
- Measure resistance between the outer pad and the *VCC* pin—they should also be close to 0 Ohms.

If not, check the other pads. The pads *not* connected to *VCC* are the true I2C configuration pins (`A0` and `A1`).

#### Using All 16 I2C Addresses

To access all 16 addresses, connect the *true* side of the `A0` and/or `A1` solder bridge to one of the following:

| A0      | A1      | I2C Address | Accessible via Solder Bridge |
|---------|---------|-------------|------------------------------|
| -       | -       | `0x40`      | yes                          |
| -       | VCC     | `0x41`      | yes                          |
| -       | SDA     | `0x42`      | no                           |
| -       | SCL     | `0x43`      | no                           |
| VCC     | -       | `0x44`      | yes                          |
| VCC     | VCC     | `0x45`      | yes                          |
| VCC     | SDA     | `0x46`      | no                           |
| VCC     | SCL     | `0x47`      | no                           |
| SDA     | -       | `0x48`      | no                           |
| SDA     | VCC     | `0x49`      | no                           |
| SDA     | SDA     | `0x4A`      | no                           |
| SDA     | SCL     | `0x4B`      | no                           |
| SCL     | -       | `0x4C`      | no                           |
| SCL     | VCC     | `0x4D`      | no                           |
| SCL     | SDA     | `0x4E`      | no                           |
| SCL     | SCL     | `0x4F`      | no                           |

**IMPORTANT:** Never wire the *wrong* side of the solder bridge. Always ensure you have correctly identified the *true pin side*. The opposite side is always connected to `VCC`.

If you connect the wrong pad (the one connected to `VCC`) to:

- `GND`: you will short-circuit the power supply.
- `SCL` or `SDA`: you risk damaging the INA219 and/or your microcontroller, as this will short the I2C line during communication (normally, a current-limiting pull-up resistor keeps I2C lines high, but now the line is directly connected to `VCC`).

## How to Connect a Load

The *INA219* requires **two** power supplies: one for itself, and another for the load under test.

| Pin    | Purpose                        | Connected to    |
|--------|--------------------------------|-----------------|
| VCC    | Powering INA219                | +3.3–5V         |
| GND    | Common ground for INA219/load  | Ground          |
| Vin+   | Powering load                  | +0–26V          |

**IMPORTANT:** Both power supplies must share the same ground. Otherwise, readings will be unstable and inaccurate.

### High-Side Load Connection

The load under test must always be connected on the *high side* (INA219 in series with the load's positive pole):

| Pin   | Connected to                |
|-------|-----------------------------|
| Vin-  | Positive pole of load       |
| GND   | Negative pole of load       |

**Important:**  
Connect *Vin-*, not *Vin+*, to the positive pole of the load. *Vin+* connects to the positive pole of the load's power supply. If you swap *Vin+* and *Vin-*, current and voltage readings will be negative.

## Programming

The *INA219* communicates digitally via I2C, so a microcontroller is required. Most microcontrollers support I2C.

### Arduino IDE / PlatformIO

There are many [excellent tutorials](https://wolles-elektronikkiste.de/en/ina219-current-and-power-sensor), [videos](https://www.youtube.com/watch?v=JWUKFLCX5Os&ab_channel=GemsungElectronics), and ready-to-use [libraries](https://learn.adafruit.com/adafruit-ina219-current-sensor-breakout/arduino-code) available.

### ESPHome

[ESPHome] natively supports the *INA219* via its `ina219` [sensor platform](https://esphome.io/components/sensor/ina219.html), with many [sample configurations](https://gist.github.com/fabaff/762008f61e745b220b9f4693954427e2) available.


## Materials

[INA219 Datasheet](materials/ina219_datasheet.pdf)



> Tags: GY-219, Current, Voltage, Measure, PGA, Texas Instruments, Adafruit, Grove, Qwiic

[Visit Page on Website](https://done.land/components/power/measuringcurrent/viashunt/ina219?220733051221251119) - created 2025-05-20 - last edited 2025-05-20
