# INA226 Current And Voltage Monitoring
:stopwatch: Reading time: 10 minutes.

## Quick overview
**INA226** is a microchip from *Texas Instruments* that can measure *current* and *voltage* and calculate *power* from it. It is often used to *monitor* power consumption or the yield from *solar generators*.

**INA226** is available as *ready-to-go* breakout board with an integrated **Shunt** and should cost less than €2/piece. 

<img src="images/ina226_soldered.png" width="40%" height="40%" />

**INA226** internally uses a 16-bit *ADC* (Analog-To-Digital converter) to measure *voltage*. It uses the **Shunt** principle to measure *current* via measuring the *voltage drop* at a **Shunt** resistor.

The maximum measured *voltage* is *36V*. The maximum measured *current* depends on the value of the **Shunt**.

Because of its high-resolution 16-bit *ADC* and automatic internal *averaging* of multiple samples, it produces very accurate and reliable readings. All of its measured and calculated values can be read by a microcontroller via *I2C*.

### Shunt Value and Maximum Current

**INA226** does not measure *current* directly. Instead, it measures the *voltage drop* at a **Shunt** resistor. The resistance of the **Shunt** determines the maximum *current* that you can measure.

#### Integrated Shunts

When using breakout boards, the most common presoldered **Shunt** is *R100* (0.1 Ohm). In theory, this enables the breakout board to measure a maximum *current* of *0.8A*. 

Less often you find boards with a *R010* **Shunt** (0.01 Ohm) which increases the maximum *current* to *8A* at the expense of precision. Boards with a *R002* **Shunt** can measure up to *20A*.

The *real* maximum current that you can measure with this type of breakout board depends on two factors:

* **Overall resistance**: In addition to the resistance of the soldered **Shunt**, there can be more resistances adding up. Cheap breakout boards use PCBs that add additional resistance in their paths. Likely, the overall resistance is *higher* than expected.
* **Conductance**: A small PCB cannot conduct high currents. Since the **Shunt** is connected *in series* with the load, the *full total currency* is flowing through it. The practical maximum current - regardless of **Shunt** - is most likely limited to *5-8A*, depending on PCB quality.

Always test and measure breakout boards with integrated **Shunts** yourself and individually board-by-board to find out their true maximum *current*.

> [!TIP]
> Should the breakout board max out even on low currents (indicating that the **Shunt** resistance is too high), you can try and *short circuit* the integrated **Shunt** resistor. Often, the low-quality internal resistance of the *PCB* all by itself is acting well enough as a **Shunt**.
>
> If you need to measure larger *currents*, consider removing the presoldered **Shunt** and connecting an external **Shunt** rated for higher currents.

## Pin Layout

Typical **INA226* breakout boards come with 8 pins:

| Pin Label | Description |
| --- | --- |
| IN+ | Positive Voltage for Load Circuit |
| IN- | Negative Voltage for Load Circuit |
| VBS | Bus Voltage |
| ALE | Alert |
| SDA | I2C SDA |
| SCL | I2C SCL |
| GND | Common GND |
| VCC | 3.3V/5V supply for INA226 |

The pin purpose is best understood when pins are broken down by functionality: 

### Power Supply for INA226

**VCC** and **GND** supply the breakout board with the power it needs to operate. Both *3.3V* and *5V* are supported.

### Communication

**SDA** and **SCL** are the typical *I2C* pins used to communicate measured values to a microcontroller.

### Load

**INA226** measures *two voltage drops*, one across the **Shunt**, and one across the *Load* (which is basically just another resistance). This explains why the breakout board has *four* pins for measurements:

<img src="images/principle_clean.png" width="40%" height="40%" />

The *current* is determined by measuring the *voltage drop* across the **Shunt**. The *voltage* is measured by *adding* the measured *voltage drops* across the **Shunt** (already known via the current measurement) and across the *load*. 

When you look at the circuit above, this explains how the *load* needs to be connected to the breakout board:

* The *load* needs to be connected to *VBS* and *GND*
* The *Power Source* for the *load* needs to be connected to *VIN+* and *GND*
* *VIN-* and *VBS* need to be connected

Here is the complete circuit for a *high side* setup (measuring the current on the *positive* side of the *load*):

<img src="images/ina226_circuit1.png" width="40%" height="40%" />




