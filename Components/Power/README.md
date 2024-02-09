# Power
:stopwatch: Reading time: 10 minutes.

## Power-Related Components

In this section I discuss components used for **Power Management**:

### Providing Power
* **[Adjusting Voltage And/Or Current](DC-DC-Converters):** I am looking at *Buck* and *Boost* converters, and combinations, and explain differences between readily available breakout boards.

### Batteries
* **[Protecting Lithium Batteries](BMS):** Rechargeable batteries can provide power, too. For safe operations, both *charging* and *discharging* needs careful attention and protection. That's what a **BMS** (*Battery Management System*) does. Here, I am discussing what a **BMS** does, which types there are, and when you need one. I am also looking at readily available low-cost **BMS** breakout boards that you can easily add to your projects.

### Measuring And Monitoring
* **[Measuring Current](Measuring Current):** There are many very good reasons why measuring *current* can be useful, and I am sharing some ideas here. Primarily though, I look at different ways to safely measure *currents*, both small currents and huge currents. 

**Rotary Encoders** are *input devices*. While they look similar to *potentiometers*, they are completely different: a **Rotary Encoder** knob can be endlessly turned right or left, and when you press the encoder, it often additionally works like a switch (i.e. to confirm a setting).

To register when the knob turns, the **Rotary Encoder** internally has a disk with holes and two switches. When you turn the encoder knob, the disk turns. Whenever a hole in the disk passes the two switches, they get contact to **GND**, one after the other.

When you turn the knob in *one* direction, then switch A gets contact before switch B, and when you turn the knob in the *other* direction, it is the other way around. The *frequency* of impulses sent by both switches indicates the speed in which the knob is turned.

Some **Rotary Encoder** have a third (and independent) switch that is activated when the knob is pressed.

The picture below shows a *raw* **Rotary Encoder** at the left side. Often, they are mounted to a simple breakout board like the one on the right side:

<img src="images/rawRotaryEncoders.png" width="50%" height="50%" />

## *Smart* **Rotary Encoders** 
Internally, a **Rotary Encoder** is a very simple construct consisting of a disk and two or three switches. When you connect a **Rotary Encoder** *directly* to your microcontroller, then *you* have to do all the heavy-lifting yourself:

* **Debouncing**: mechanical switches *bounce* (when pressed, they can vibrate and send more than just one impulse). You would have to electrically or in software *debounce* the encoder input.
* **Signal Analysis/Post-Processing**: as the encoder is just sending two phase-shifted *High/Low* signals from its two internal switches, your software needs to figure out the direction of phase shift to determine the rotational direction, and analyze the signal frequency to determine the rotational speed.

Fortunately, there are a lot of libraries available that take care of these things. Two things remain, though, that the libraries can't leverage when you work directly with **Rotary Encoders**:

* **Many GPIO Pins**: You need one wire per switch plus **GND**, so depending on whether the encoder has an additional *press* switch, between *3* and *4* wires and between *2* and *3* GPIO pins.
* **CPU Load**: Whenever the **Rotary Encoder** moves, your CPU has work to do, on top of the monitoring load.

That's why there are also *smart* **Rotary Encoders**: all of the hassle described above is shiftet over to a dedicated microprocessor. Here is a picture of such a *smart* **Rotary Encoders**:

<img src="images/RotaryEncoder_Smart.png" width="30%" height="30%" />

You can clearly see the dedicated microprocessor that makes this **Rotary Encoder** *smart*.

Such boards typically communicate via *IC2*: just two wires are needed (not four), and just two GPIO pins. These GPIO pins are shared among all other *I2C* devices, too. If you increase the number of **Rotary Encoders** in your project or use other *I2C* devices like *OLED* screens, the number of required GPIO stays the same.

