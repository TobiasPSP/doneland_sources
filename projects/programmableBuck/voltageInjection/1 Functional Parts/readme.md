# Implementation Steps
:stopwatch: Reading time: 5 minutes.

## Step 1: Interfacing With Buck Converter

The digital control we are building here is an *external component* and does not require any changes in the stock **Buck** converter. All we need is a way to interface with it.

According to the schematics, six connection points are needed:

|  Pin |  Description |
| --- | --- |
| GND IN | Measure current |
| GND OUT | Measure current |
| V+ OUT | Measure voltage |
| POT1 | Voltage control |
| POT2.1 | Current control |
| POT2.2 | 0V reference |

* **Measuring Current**: The **Buck** controller connects **GND IN** with **GND OUT** across a *R050* shunt resistor used internally to meassure the current. Since we also need to know the current, we too measure the voltage drop. For this, all we need is access to the terminals **GND IN** and **GND OUT**.
* **Measuring Voltage**: To measure the output voltage, we also need access to the terminal **V+ OUT**. Voltage can then directly measured either against **GND IN** or **GND OUT** (the voltage drop at the shunt resistor is neglectible and can also be adjusted by software later)
* **Controlling Constant Voltage**: To digitally control constant voltage, we need a connection to the voltage sensor pin of the **XL4015** which can conveniently be accessed at one of the *CV* *portentiometer* pins.
* **Controlling Constant Current**: Same goes for current settings: our injected voltage goes into the *middle* leg of the **CC** *potentiometer* pin.
* **0V Reference**: We also need a **0V** reference (more later) which is accessible at the **CC** *potentiometer*.

We need a total of *six* wires to connect to the **Buck** controller.

> [!TIP]
> Of course, our digital control needs its own power supply as well. Since I don't want to power it externally, we will be using a separate mini buck converter that takes a high *DC* voltage and outputs the stable *3.3V* needed for an *ESP8266*.
>
> Even though it seems tempting to choose the *output* voltage as it is lower than the *input* voltage and thus would be closer to what we need, resulting in higher efficiency, the solution is more robust when powering the digital control via the *input* power.
>
> Else, if we ever choose to **turn off** the **Buck** controller programmatically, i.e. to enter some energy savings mode, we'd cut off ourselves from power. If we wanted to power our digital control via the interface we are designing here, thus we would need a seventh wire to expose **V+ IN**.

## Step 2: Reading Voltage And Current

The microcontroller needs to know the actual *voltage* and *current* before it can tell the **Buck** breakout board what to do. 

Let*s look at this part first. Viewed isolated, it is much easier to understand, and you can re-use this logic for many other purposes, i.e. to monitor batteries or build your own *Coloumbmeters*.

<img src="../images/voltage_and_current_measurement_t_w.png" width="90%" height="90%" />

### ADS1115 - Reads Voltages

The *voltage* and *current* measuring is done by a **ADS1115**: a cheap and precise 12-bit *ADC* (Analog-To-Digital-Converter). 

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

### Meassuring Current

*Current* cannot be measured directly. An *ADC* can measure *voltage* only. One way of measuring *current* is by measuring the *voltage drop* at a low-resistance *shunt* resistor.

The **Buck** converter used here has a shunt resistor mounted on its back and uses it internally to measure the output current. The shunt resistor is connected in series between **GND** input and **GND** output: the other two *ADC* inputs (*AIN2* and *AIN3*) are therefore connected to the **output GND** and the **input GND**.

Since the voltage drop typically is a very low voltage, no additional *voltage divider* is required here. 

> [!TIP]
> To create the digitally controllable **Buck** converter, all we need is a way for the microprocessor to know the *voltage* and *current*.
>
> Using an **ADS1115** and taking advantage of the *shunt resistor* built into the **Buck** converter (as illustrated here) is one clever way of doing so. There are many alternatives, though. You could use a *hall sensor* to measure *current* (i.e. if you wanted to adapt this concept to different **Buck** converters that have no easily accessible *shunt resistor*), or use your own *shunt resistor*.
>
> In fact, there are cheap boards available based on *INA226* or *INA3221* that do *current* and *voltage* measuring via *I2C* as a one-stop solution. They are also super cheap. However, most of them use *R100* shunt resistors and can only handle a maximum of **3A**. 

### Building And Testing

The actual *building* and testing, including *programming* the microprocessor and adjusting the raw input readings from *ADS1115* to display the measured *voltage* and *current* on a *OLED* display can be found here (TBD, coming soon).

## Step 3: Regulating the **Buck** Controller

Once the microcontroller knows the exact *voltage* and *current*, it can start controlling the **Buck** converter, asking to increase or decrease *voltage* and/or *current*. How this is done is the clever trick and special beauty of this solution:

* **Potentiometers**: By design and stand-alone, the **Buck** converter controls *constant voltage* and *constant current* via two manually operated potentiometers. Both potentiometers are marked **W103** so they are **10K**.
* **Constant Voltage**: To keep the voltage constant, the voltage regulator *XL4016* inside the **Buck** converter uses a *voltage divider*, consisting of a 270R fixed resistor and the potentiometer. 

<img src="../images/voltageControl_w.png" width="90%" height="90%" />
