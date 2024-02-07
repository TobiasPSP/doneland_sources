# Connecting Directly
:stopwatch: Reading time: 10 minutes.

<img src="images/RotaryRight.png" width="10%" height="10%" />

## Rotary Encoder Pins
Let's hook up a mechanical **Rotary Encoder** to a microcontroller and see how things go. Here is the pin-out for most encoder types:

<img src="images/rotaryEncoder_RawPins_w.png" width="50%" height="50%" />


For this test, you need this:

* **Microprocessor**: I am using an *ESP8266*.
* **Rotary Encoder**: I am using a vanilla encoder with built-in switch (5-pn model)
* **OLED Display**: I am using a vanilla *I2C* 0.96 inch *SSD1306* display

> [!NOTE]  
> If you have never worked with *OLED* displays before, then you should now. Of course you could output information to the *IDE*s serial monitor and skip the *OLED* stuff. But after all, we are all creating gadgets and fun electronics for the real world, so serial monitor output is really no fun.
>
> *OLED* displays are so inexpensive, so readily available, and so easy to use that you shouldn't hesitate to routinely add them to your microcontroller projects for outputting information in a fun and intuitive way.

### Different Types

When you purchase a *really really raw* **Rotary Encoder**, you just get an encoder switch which looks similar to a potentiometer. It has four or five "legs", two on one side and two or three on the other:



A bit easier to work with are breakout boards: they provide easily accessible pins and come with three pullup resistors. 

<img src="images/rotaryEncoder_simple_board.png" width="50%" height="50%" />

> [!IMPORTANT]  
> Do not confuse these breakout boards with *smart* **Rotary Encoders* mentioned above. 

Here is the schematic of such a breakout board:





### Schematics




