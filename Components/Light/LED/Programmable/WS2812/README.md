<img src="/assets/images/light.png" width="80%" height="80%" />
 
# Programmable LED

> A Built-In Chip Controls Colors, Handles Currents, And Can Be Daisy-Chained To More Programmable LED. That Saves Effort And Wires.

*Smart* **LED** have *four* or more legs and use an integrated chip to drive its internal **LED**.


> [!TIP]
> Thanks to the on-board chip, you need to supply *only one voltage* to all internal **LED**.
> *Smart* **LED** can be *daisy chained* which drastically reduces the *wiring*.
> Since they are *digitally controlled*, a *microcontroller* is mandatory to operate them.

Sophisticated **LED Strips** often use *WS2812* **LED** that come with full RGB color, an internal controller chip *per LED*, and *four* legs.

These **LED** are available in many different forms and shapes and are not restricted to **LED strips**. They are also available as *regular individual **LED***.

<img src="images/led_ws8212_single_back_t.png" width="50%" height="50%" />

Some vendors call this **LED** type *NeoPixel*.

### Advantages

Each *programmable* **LED** can display the full *color spectrum* and works similar to *simple RGB* **LED**: internally *three* **LED** in *red*, *green*, and *blue* color can be mixed to produce all other colors.

> [!NOTE]
> There are many different variations and also different on-board controllers. The *WS2812* typically uses **5V** and comes with three **LED** (*RGB*). There are also versions and controllers for other voltages and combinations with *white* **LED** (*RGBW*, *RGBWW*) for added brightness.
> Especially for *long* **LED strips**, choosing a *higher voltage* is wise: with **5V**, the *current* requirements for hundreds or thousands of **LED** can easily exceed *10-20A*, require expensive thick wires and can produce considerable *heat*.

Programmable **LED** are *much simpler* to operate than *simple RGB* **LED**:

* **Uniform Voltage:** *WS8212* **LED** require *5V*. The different *voltages* and *currents* required by each of the three internal color **LED** is automatically adjusted by the internal driver chip. Other controller support different supply *voltages* but fundamentally do the same.   
* **Digital Control:** to display a given *color* and *brightness*, you send a *digital control signal* to the **LED**. There is no need to manually calculate and provide the individual *current* to each of the three **LED** to mix the desired *color* and *brightness*.
* **Daisy Chain:** *WS8212* **LED** can be daisy-chained which makes them especially suitable for **LED strips**. When daisy-chained, *each **LED*** can be controlled *individually*. This makes *WS8212* also very interesting for *individual indicator **LED***: you need just *one* GPIO pin to control an arbirary number of indicator **LED**.

> [!NOTE]
> Programmable **LED** do need a digital control signal. They are perfect for microcontroller projects. They cannot be used without one, though.


### Pins for Single Programmable LED

For individual (non-SMD) *WS8212* (or similar) **LED**, look at the *length* of the legs:

<img src="images/led_ws8212_single_front_t.png" width="50%" height="50%" />


* **Two different lengths:** some **LED** come with legs in *two* different lengths: two legs are shorter than the other two.
* **Four different lengths:** typically, each leg has a different length.

#### Power Connection

The two *inner* legs are connected to the **5V** power supply. The *longer* leg is **GND**, the *shorter* leg is **+5V**.

#### Digital Connection

The two *outer* legs carry the *digital control signal*. The leg next to **V+** (*shorter* pin) is the digital *input* **DIN**. The leg on the other side (*longer* pin) is digital *output* **DOUT**.

Connect **DIN** to your microcontrollers' GPIO output, and connect **DOUT** to **DIN** of the next **LED** in the daisy chain.

## Considerations

Here are a few points to consider when using *programmable **LED***:

* **Microcontroller Required:** You need a *microcontroller* to operate *programmable **LED***. Either program your own, or use one of the readily available and *cheap* **RGB Controllers**
* **Voltage May Differ:** Always make sure you know the *specs* of the type of *programmable **LED*** you use. Their supply voltages may vary. While *WS2812* are operated with **5V**, there are other types that need **12V** or even **24V**.
* **Beware Of High Current:** A higher supply voltage lowers the required *current* which starts to matter when you daisy-chain more than just a couple of **LED**. **LED strips** operated at **5V** can quickly exceed currents of *10-20A*. For *long **LED** strips*, it's more efficient to use an **LED** type that takes **12V** or **24V** supply voltage.


## Examples

Over time, I am adding practical examples on how to operate *programmable **LED*** here.



> Tags: LED, Light, Anode, Cathode, RGB, Neopixel, WS2812, Programmable LED

:eye:&nbsp;[Visit Page on Website](https://done.land/components/light/led/programmable/ws2812?668154031318243445) - last edited 2024-03-18
