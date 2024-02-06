# Raw Rotary Encoders
:stopwatch: Reading time: 10 minutes.

## *Raw* and *Advanced* Rotary Encoders
Let's quickly define the terms:

* A *raw* rotary encoder is just the physical device, without any additional parts or electronic components that post-process its signals.
* An *advanced* rotary encoder is a *raw* rotary encoder embedded in supporting hardware.

In this section, I am looking into using *simple* **Rotary Encoders**.

### Pro and Con
There are actually just two good reasons for using *raw* **Rotary Encoders in your projects:

* **Cheap and Available**: **Rotary Encoders** are readily available in many forms and shapes, and they are very inexpensive.
* **Simple and Small**: since you are dealing with all of the challenges and shortcomings of *raw* **Rotary Encoders** yourself, in your software, you can save physical space as you don't need any other supporting components.

On the *Con* side:

* **Many I/O Pins Required**: a *raw* **Rotary Encoder** requires at least **4** GPIO pins. If the encoder also acts as a switch when you press it, you need a total of **5** GPIO pins. Plus as many wires. Most microprocessors have a very limited number of GPIOs. This is a scarce and valuable resource. 
* **Complex Programming**: the **Rotary Encoder** sends raw impulses to your microprocessor. You (your firmware) needs to interpret these and figure out i.e. in which direction (and how fast) the encoder is moving. The software needs to deal with noisy (bouncing) keys, too. Your microprocessor will have to spend a significant part of its capabilities just on interpreting the encoder signals. Your software gets more complex, too. 

## Testing A *Raw* Rotary Encoder

For this test, you need this:

* **Microprocessor**: I am using an *ESP8266*.
* **Rotary Encoder**: I am using a vanilla type with built-in switch (5-pn model)
* **OLED Display**: I am using a vanilla *I2C* 0.96 inch *SSD1306* display

> [!NOTE]  
> Instead of outputting feedback to the *OLED* display, you could as well write to the serial monitor.
>
> *OLED* displays are inexpensive, readily available, and easy to use. That's why I prefer them over serial debug messaging.

