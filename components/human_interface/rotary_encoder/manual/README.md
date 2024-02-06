# "Dumb" Rotary Encoders
:stopwatch: Reading time: 10 minutes.

## "Dumb" And "Smart"
A *dumb* **Rotary Encoder** is just the physical device itself. You can directly connect it to your microcontroller and work with it. 

The picture below shows a *dumb* **Rotary Encoder** (left). Often, they are mounted to a simple breakout board (right):

<img src="images/rawRotaryEncoders.png" width="50%" height="50%" />

Working with *dumb* **Rotary Encoders** directly can be painful, though: since they are *dumb* devices, they send raw data that needs to be post-processed and interpreted in order to properly figure out what the **Rotary Encoder** is actually doing. 

The smart *post-processing* is done by your software (firmware) and your microcontroller. Luckily, there are ready-to-use libraries that handle most of the tricky parts.

What libraries cannot work around is the fact that *dumb* **Rotary Encoders** require **4** GPIO pins. If the encoder acts as a switch when you press on it, you even need a total of **5** GPIO switches.

That's why there are also *smart* **Rotary Encoders**: the encoder comes bundled with its own specialized mini-processor who does all the heavy lifting (so you and your microprocessor don't have to worry about it anymore): signal interpretation, noise, post-processing, communication. This is what *smart* **Rotary Encoders** can look like:

<img src="images/RotaryEncoder_Smart.png" width="30%" height="30%" />

In the picture, you can clearly identify the dedicated microprocessor that makes this **Rotary Encoder** smart.

Such boards typically communicate via *IC2*: just two GPIO pins are needed (not five), and they are shared among all other *I2C* devices. If you increase the number of **Rotary Encoders** in your project, the number of required GPIO stays the same.

In this section, we are looking at the *dumb* **Rotary Encoders** and how you work with them directly.

## Testing A *Dumb* Rotary Encoder

Here is a test setup to examine how a directly connected **Rotary Encoder** can be used.

For this test, you need this:

* **Microprocessor**: I am using an *ESP8266*.
* **Rotary Encoder**: I am using a vanilla encoder with built-in switch (5-pn model)
* **OLED Display**: I am using a vanilla *I2C* 0.96 inch *SSD1306* display

> [!NOTE]  
> If you have never worked with *OLED* displays before, then you should now. Of course you could output information to the *IDE*s serial monitor and skip the *OLED* stuff. But after all, we are all creating gadgets and fun electronics for the real world, so serial monitor output is really no fun.
>
> *OLED* displays are so inexpensive, so readily available, and so easy to use that you shouldn't hesitate to routinely add them to your microcontroller projects for outputting information in a fun and intuitive way.

### Different Types

When you purchase a **Rotary Encoder**, you just get an encoder switch. It has four or five "legs", two on one side and two or three on the other:

<img src="images/rotaryEncoder_RawPins_w.png" width="50%" height="50%" />

Easier to work with are breakout boards: the encoder is soldered to a simple board: 

<img src="images/rotaryEncoder_simple_board.png" width="50%" height="50%" />

> [!IMPORTANT]  
> Do not confuse these breakout boards with *smart* **Rotary Encoders** mentioned above. These simple breakout boards just embed the **Rotary Encoder** and three pullup resistors. No smart post-processing.

Here is the schematic of such a breakout board:





### Schematics


