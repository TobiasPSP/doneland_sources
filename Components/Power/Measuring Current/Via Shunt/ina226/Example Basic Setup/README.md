<img src="/assets/images/lightning.png" width="100%" height="100%" />


# Example: INA226 Basic Setup

> It is Not Obvious at First How a INA226 Chip Needs to be Hooked Up to Measure Current and Voltage. Here is an Example.

<img src="images/ina226_basic.png" width="40%" height="40%" />

## Quick overview
In this example, a typical breakout board with **INA226** is connected to an **ESP8266**, and basic *voltage* and *current* measurements are performed. 

This is a good example to test-drive your **INA226** and get to know its functionality.

## Parts List
For this project you need the following parts:

* **1x ESP8266 microprocessor**: I am using a *Wemos D1 Mini* in this example.
* **1x INA226 breakout board**: I am using a cheap board with mounted *R100* **Shunt**

## Preparing the INA226 Breakout Board
Choose which side of the breakout board should face up, then add header pins, and solder two wires to the large solder pads for **IN+** and **IN-**. 

<img src="images/ina226_soldered.png" width="40%" height="40%" />

> [!TIP]
> Pins **IN+** and **IN-** are *connected in series* with the load. Relatively high currents pass these pins.
>
> That's why most breakout boards expose these pins *twice*: as part of the header pins, and on the opposide side via two larger solder pads. It is recommended that you solder larger diameter wires to these solder pads.

Here is the circuit for this *high side* setup (measuring the current on the *positive* side of the *load*):

<img src="images/ina226_circuit1.png" width="40%" height="40%" />

First place the components onto your bread board and wire them according to the schematics. Things to watch out for:

* Do not forget to onnect pins **IN-** and **VBS**
* Add a black wire to **GND** and leave the other end unconnected for now. You will need it for the terminal later.

Here is a close-up:

<img src="images/ina226_basic_breadboard1.png" width="100%" height="100%" />

### Adding a Terminal

Next, create a *terminal* to connect the *load*. Here is the schematic for the *terminal* part:

<img src="images/ina226_terminalSchema.png" width="50%" height="50%" />

You can use a *4-pin terminal* or just 4 individual clamps (like I did). You also need a short black wire. Here is how my terminal looks like:

<img src="images/ina226_basic_terminal1.png" width="50%" height="50%" />

And this is how to connect the wires:

* Take the red wire coming from **IN+** and one end of a *new short black wire*. Add a clamp on each of these two cables, and combine them with some scotch tape. Lebel them **Power**.
* Take the black wire coming from **IN+** and place a clamp on it. Then take the free end of the black wire that you just added, and combine it with the black wire coming from **GND**, then place one clamp on them both. Combine both clamps and label them **Load**.

## Code

Next, *build* and *upload* the firmware to run the hardware:

* **PlatformIO:** use the project in the subfolder [platformio](platformio) and load it in *VSCode*.
* **Arduino IDE:** use the sketch in the subfolder [arduino](arduino) and load it into the *Arduino IDE*

> Tags: Measure, Current, Voltage, Shunt, INA, INA226, Example

[Visit Page on Website](https://done.land/components/power/measuringcurrent/viashunt/ina226/examplebasicsetup?413892020426240854) - created 2024-02-27
