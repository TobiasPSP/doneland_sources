<img src="/assets/images/light.png" width="80%" height="80%" />
 
# LED Controller

> Safely Driving LEDs With Constant Current Or Constant Voltage

*LEDs* have a very low internal resistance, so when you apply electric power to them, three things can happen:

* **No Light:** if the *voltage* is below the forward voltage of an *LED*, no current will flow, and there is no light emission.
* **LED works:** if the *voltage* is above the forward voltage, and the *current* is not exceeding the amount of power that the *LED* can convert to light, all is good.
* **LED burns (destruction):** if the *voltage* is above the forward voltage, and the *current* is exceeding a certain threshold, then the *LED* can no longer convert all of the supplied energy into light. The excess energy is converted to *heat*, and depending on the amount of excess energy, the *LED* will burn up and be destroyed immediately or over a course of a longer period of time (minutes to hours)

*LED controllers* are circuits designed to keep the supplied energy within the specifications of an *LED*.

> [!NOTE]
> A *current limiting resistor* is a very basic form of *LED controller*: the resistor takes the excess energy and converts it to *heat*. This works well for *signal LEDs* that only take a few mA of current. Resistors do not work well for more powerful *LED*, though: they would need to be capable of dissipating many watts of power, waste a lot of energy and get very hot.

*LEDs* can be controlled by *constant current* (*CC*) or by *constant voltage* (*CV*) power supplies.

## Constant Current Controllers

*Constant current* is the best driver for *LEDs*. Here is why:

* **Light = Current:** the light emission of a *LED* is directly proportional to the *current*. By supplying a fixed current, you ensure that the *LED* is always emitting light of the same intensity. This can become especially important with *RGB LEDs* that *mix* colors out of *red*, *green*, and *blue*: if the light intensity of one of the colors changes, you will see a noticeable change in color.
* **Resistance Varies:** *Voltage* and *internal resistance* determine the *current*. A *constant current* supply continuously monitors the current, and if it changes, the supply changes the *voltage* to bring back the *current* to its target value. For *LEDs*, this automatic adjustment is important because the internal resistance of *LEDs* can vary based on production differences, and more importantly, the resistance is affected by *heat*. When *LEDs* are operated for a longer period of time, they heat up and change resistance. A *constant current* supply notices the decreasing resistance by sensing a *higher current*, and automatically *reduce* the voltage.

In a nutshell, what matters to *LED* is *current*, and a *constant current* supply controls exactly this parameter.

## Constant Voltage Controllers

*Constant voltage* can also be used to drive *LED*: a fixed *voltage* is set that is causing the desired *current* to flow. Remember: *voltage* is the force that drives a *current* through *resistance*.

This would work well if the *resistance* was constant. However with *LEDs*, resistance is **not** constant: it can change i.e. when the *LED* heats up. That's why *constant voltage* can only *approximately* set the *current*, and the real *current* will vary and change based on other factors like the *LED temperature* and its specific internal resistance.


### Saving Money
*Constant voltage* supplies are technically simpler and cheaper than *constant current*. The variations in *current* that you get with *constant voltage* supplies may not be terribly high, so you might want to tolerate them in exchange for lower component cost.

WHenever *exact brightness* does not matter (i.e. decorative or ambient lighting), *constant voltage* supplys may be the most economical solution.

> [!TIP]
> If exact brightness is important (as in *RGB LED* where slight changes in brightness can affect the emitted mixed color), or if you aim to drive a *LED* at its absolute maximum specifications, always use a *constant current* supply.

### Powering Drivers, Not LED
Sometimes, *LED* and *LED strips* come with built-in electronics and use their own *internal drivers* (i.e. programmable LED like the *WS2812*). Cheaper *LED strips* may also use *built-in current-limiting resistors*. In all of these cases, **you are not driving the LEDs**. The *LEDs* are driven by the internal electronic parts. You are simply supplying power to these.

In such cases, you **must** use a *constant voltage* supply and supply exactly the voltage that the internal electronic components require. For example, programmable *WS2812 LED* typically require *5V* and use an internal *constant current* driver to drive the actual *LEDs*.


> Tags: LED Driver, WS2812, COnstant Current, Constant Voltage
