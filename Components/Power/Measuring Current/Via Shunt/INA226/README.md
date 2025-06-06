<img src="/assets/images/lightning.png" width="100%" height="100%" />


# INA226 Current And Voltage Monitoring

> Modern Chip For Accurately Measuring Current and Voltage Via I2C Interface 

[**INA226**](https://www.ti.com/lit/ds/symlink/ina226.pdf) is a microchip from *Texas Instruments* that can measure *current* and *voltage* and calculate *power* from it. Its separate *VBS* (Bus) pin allows precise voltage measurements using [four-wire techniques](https://en.wikipedia.org/wiki/Four-terminal_sensing) (*Kelvin* probe). 

This chip is the more modern successor of the popular *INA219*. Like *INA219*, it is a digital component that communicates via *I2C* and requires a microcontroller.

> [!TIP]
> *INA226* isn't always superior to the older *INA219*: it has a fixed gain, so the current range that it can measure is fixed and depends on the value of the shunt resistor. *INA219* in contrast, while less accurate due to its inferior *ADC* (12bit instead of 16bit), lets you control the gain. This enables *INA219* to adapt to various current ranges and cover a much larger range: if the current exceeds the active range, simply switch the gain. On the contrary, *INA219* cannot separately measure the bus voltage and thus cannot be used with *four-wire techniques* which may be an issue with high currents when cable resistance leads to significant voltage drop.



**INA226** is available as *ready-to-go* breakout board with an integrated **Shunt** and should cost less than EUR 2/piece. 

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

Typical **INA226** breakout boards come with 8 pins:

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

* **VCC** and **GND** supply the breakout board with the power it needs to operate. Both *3.3V* and *5V* are supported.
* **SDA** and **SCL** are the typical *I2C* pins used to communicate measured values to a microcontroller.

## How to Connect a Load
To measure *voltage* and *current*, you typically need *four* probes: two wires to the positive and negative pole of the power supply to measure the *voltage*, and two wires the cut the circuit to insert the **Shunt** and connect it in series. In reality, you just need *three* probes because depending on whether you measure on the *high* (positive) or *low* (negative) side, two probes will either both be **GND** or **V+**.

To translate this to the **INA226** breakout board, it is important to understand how it measures the *voltage*: in addition the *voltage drop* across the **Shunt**, it measures the *voltage drop* across the *load*. By summing up both, the total *voltage* is calculated.

The *four* probes (pins) involved in *current* and *voltage* measuring for the **INA226** look like this:

<img src="images/principle.png" width="40%" height="40%" />

This helps understanding how the external circuit that you want to measure needs to be connected to the breakout board:

* The *load* needs to be connected to *VBS* and *GND*
* The *Power Source* for the *load* needs to be connected to *VIN+* and *GND*

As outlined above, in reality for combined *current* and *voltage* measurements, only *three* probes (pins) are needed. In this *high side* setup, *VIN+* and *VBS* are connected to the same spot and can be combined.

Here is the complete circuit for a *high side* setup (measuring the current on the *positive* side of the *load*):

<img src="images/ina226_circuit1.png" width="40%" height="40%" />

## Examples

Here are available example sketches:

* [**Basic Setup**:](Example%20Basic%20Setup) Setting up a **INA226** breakout board with an **ESP8266** microcontroller to perform *voltage* and *current* measurements. Includes necessary *library* and complete *platform.io* project.

> Tags: Measure, Current, INA, Shunt, Voltage Drop, Integrated Circuit

[Visit Page on Website](https://done.land/components/power/measuringcurrent/viashunt/ina226?383973020426240854) - created 2024-02-27 - last edited 2024-02-27
