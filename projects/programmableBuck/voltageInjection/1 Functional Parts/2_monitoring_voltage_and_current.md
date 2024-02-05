# Step 2: Monitoring Voltage And Current
:stopwatch: Reading time: 5 minutes.

## Concept

The microcontroller needs to know the actual *voltage* and *current* before it can tell the **Buck** breakout board what to do. Here is the part of the schematics that does this:

<img src="../images/voltage_and_current_measurement_t_w.png" width="90%" height="90%" />

> [!TIP]
> To create the digitally controllable **Buck** converter, all we need is a way for the microprocessor to know the *voltage* and *current*.
>
> Using an **ADS1115** and taking advantage of the *shunt resistor* built into the **Buck** converter is one clever way of doing this. There are other ways to monitor *voltage* and *current*, though, that may be more appealing to you.
>
> You could use a *hall sensor* to measure *current* (i.e. if you wanted to adapt this concept to different **Buck** converters that have no easily accessible *shunt resistor* necessarily), or use your own *shunt resistor*.
>
> In fact, there are cheap boards available based on *INA226* or *INA3221* that do *current* and *voltage* measuring via *I2C* as a one-stop solution. They are also super cheap. However, most of them use *R100* shunt resistors and can only handle a maximum of **3A**.
>
> Takeaway: if you already *have* a digitally controllable way of monitoring *voltage* and *current* that you are comfortable with, you could skip this entire part, use your own monitoring solution, and directly move on to the [next part](3_injecting_voltage.md).

<details>
<summary>How Voltage And Current Are Measured</summary></details<br/>
  

### Analog-To-Digital Converter (ADC) Reads Voltages

The *voltage* and *current* measuring is done by a **ADS1115**: a cheap and precise 16-bit *ADC* (Analog-To-Digital-Converter). 

It comes with four inputs marked as *AIN0* to *AIN3*. The chip communicates via **I2C** so it is connected to the microcontroller with just two wires: *SCL* and *SDA*.

> [!NOTE]  
> Most microcontrollers like *Arduino* and *ESP8266* come with their own *ADC* built-in. You could skip the *ADS1115* and use the built-in *ADC* instead to save a bit.
>
> However, the built-in *ADC*s are much less precise and much more susceptible to external influences. In an application that is designed to control output *voltage* and *current* of a power supply you need precise and robust readings. After all, you cannot have an unexpected voltage surge just because there is noise on the line.
>
> It's well invested money to use external *ADC*s in your projects. After all, a *ADS1115* cost less than €2 and is well worth it.

### Measuring Voltage

The *voltage* is measured by *AIN0* and *AIN1*: *AIN0* is connected to the positive *output* voltage, and *AIN1* is connected to **GND**. The measured *difference* is the *output voltage*.

> [!IMPORTANT]  
> Most *ADC*s can measure only a limited voltage range and are very sensitive to over-voltage. That's why the *ADS11215* cannot measure the output voltage directly. It is too high.
>
> Instead, a *voltage divider* is used (*R11* and *R12*). The resistor values *1K* and *10K* drop the measured voltage by factor 10 so it is now in the safe range for the *ADS1115* input.

> Even though the *ADS1115* comes with *four* independent inputs and can measure *four* different input voltages against **GND**, it alternatively supports a *differential mode* where it can measure *voltage differences* between two inputs, respectively. This *can* be more precise, and it *can* be used to also measure negative voltages.
>
> However, nothing is won if the second input is connected to **GND** (which is what the one-pin input does by default).
>
> I may be overlooking the obvious, and will investigate further, but on first sight it appears as if *AIN1* could safely be used for other purposes: *AIN0' would yield the same result when used in default *single pin* mode.

### Measuring Current (Indirectly Via Voltage)

*Current* cannot be measured directly. An *ADC* can measure *voltage* only. So we are measuring the *voltage drop* at a low-resistance *shunt* resistor instead.

Coincidentally, the **Buck** converter used has a shunt resistor built-in on its back and uses it internally to measure the output current. The shunt resistor is connected in series between **GND** input and **GND** output: the other two *ADC* inputs (*AIN2* and *AIN3*) are therefore connected to the **output GND** and the **input GND**.

Since the voltage drop is typically a very low voltage, no additional *voltage divider* is required here. 


> [!NOTE]  
> Should you *not* find a big black *R050* *shunt resistor* on the back of your **Buck** converter then you might be using a different model.
>
> Natively, the *XL4015* chip used in these converters supports just *constant voltage* but does *not* support *constant current*. It is the discrete logic on the breakout board that *adds* *constant current* capabilities, and there are breakout boards out there that look much alike but are missing the additional **CC** logic (in which case you can still use the board in this project, but you will only be able to control voltage, not current).
>
> The external **CC** logic consists primarily of a *shunt resistor* (to measure current, like we do), a *potentiometer* to adjust *constant current* (so these boards have *two* potentiometers and not just one), and an *OpAmp* (that produces the actual control signal to tell the *XL4015* to lower its voltage when there is an over-current).

</details>

## Solder Points

To measure voltage and current, add wires to the **Buck** converter at the marked pins:

<img src="../images/step1 interface with buck_w.png" width="90%" height="90%" />


The actual *building* and testing, including *programming* the microprocessor and adjusting the raw input readings from *ADS1115* to display the measured *voltage* and *current* on a *OLED* display can be found here (TBD, coming soon).


## Next Step

Now that our microcontroller can monitor *voltage* and *current*, it is time to *control* them. This is done by *injecting* voltages into the **Buck** controller to mimick a change in the manual potentiometers. [The next part has the details](3_injecting_voltage.md).

