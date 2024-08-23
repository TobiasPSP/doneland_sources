<img src="/assets/images/opampsmall.png" width="80%" height="80%" />
 
# Operational Amplifier

> Comparing Voltages And Amplifying Signals

An *operational amplifier* (*OpAmp*) is a very versatile component: it amplifies the difference between two input voltages. This simple functionality enables a surprisingly wide area of functionalities: *OpAmps* are found in the tone controls of audio amplifiers, in the feedback circuits of analog-to-digital converters, and in the active filters of signal processing systems.

In DIY projects, *OpAmps* compare voltages, cut off power when a battery is fully charged, or build signal generators.

## Common Use Cases

*OpAmps* are used in a number of different use cases and configurations:

- **Voltage Follower (Buffer)**: Provides impedance matching and signal isolation by delivering the same voltage as the input but with a high input impedance and low output impedance.
- **Inverting Amplifier**: Amplifies the input signal with a phase inversion (180 degrees) and a gain determined by external resistors.
- **Non-Inverting Amplifier**: Amplifies the input signal without inverting it, with a gain determined by external resistors.
- **Differential Amplifier**: Amplifies the difference between two input signals, useful for measuring small voltage differences in noisy environments.
- **Integrator**: Produces an output voltage that is proportional to the integral of the input voltage, often used in analog computing and signal processing.
- **Differentiator**: Produces an output voltage that is proportional to the rate of change (derivative) of the input voltage, used in signal processing and for edge detection.
- **Comparator**: Compares two input voltages and outputs a high or low signal depending on which input is higher, used in zero-crossing detectors, level shifters, and pulse-width modulation.
- **Active Filter**: Used in low-pass, high-pass, band-pass, and band-stop filters to filter out unwanted frequencies from signals.
- **Summing Amplifier**: Adds multiple input signals together, commonly used in audio mixing and signal processing.
- **Oscillator**: Generates periodic waveforms (sine, square, triangle) by using op-amps in circuits like Wien bridge or phase-shift oscillators.

## Key Specs
When comparing *OpAmps*, these are specifications to look out for:

- **Package Type**: Choose a package that fits your prototyping or final assembly needs. Common packages like DIP are easier to handle for breadboard prototyping, while surface-mount packages might be preferred for compact designs.   
- **Power Supply Voltage Range**: Ensure the op-amp can operate within the voltage range available in your project. This is particularly important if you're using a specific power supply or battery.
- **Output Voltage Swing**: Ensure the op-amp can output the full range of voltages required by your circuit, particularly if you're working near the power supply rails.
- **Slew Rate**:  indicates how quickly the op-amp can respond to changes in its input signal. Specifically, it measures the maximum rate at which the output voltage can change over time. The slew rate is important primarily for high frequency AC signal processing, not so much for low frequency use cases.
- **Gain-Bandwidth Product (GBP)**: A higher GBP is needed for applications requiring amplification of high-frequency signals, such as in audio or RF projects.
- **Input Impedance**: Most modern *OpAmps* have a sufficiently high input impedance to avoid significant loading effects. Only when high precision is required or tiny signals must be processed, would an *OpAmp* with a exceptionally high input impedance in the gigaohm range preferrable.
- **Input Offset Voltage**: this inherent imprecision in the operational amplifier (op-amp) between the inverting and non-inverting input voltages is also important only for projects with high precision needs.



<details><summary>Extended List Of OpAmp Specs</summary><br/>

- **Gain-Bandwidth Product (GBP)**: Indicates the frequency at which the gain of the op-amp is 1. Higher GBP values allow for higher frequency operation with adequate gain.
- **Input Offset Voltage**: The differential input voltage required to make the output zero. Lower values are preferable for accurate signal processing.
- **Input Bias Current**: The average of the currents entering the inverting and non-inverting inputs. Lower input bias currents are important for high-impedance applications.
- **Input Impedance**: The resistance seen by the input signal. Higher input impedance is desirable to minimize the loading effect on the preceding stage.
- **Output Impedance**: The resistance of the op-amp's output. Lower output impedance ensures better drive capability and signal integrity.
- **Slew Rate**: The maximum rate of change of the output voltage. Higher slew rates are needed for applications involving rapid signal changes.
- **Common-Mode Rejection Ratio (CMRR)**: Measures the op-amp's ability to reject common-mode signals (signals present on both inputs). Higher CMRR indicates better performance in noisy environments.
- **Power Supply Rejection Ratio (PSRR)**: Indicates how well the op-amp can reject variations in its supply voltage. Higher PSRR means less influence of supply noise on the output.
- **Total Harmonic Distortion (THD)**: The level of unwanted harmonics introduced by the op-amp. Lower THD is important for high-fidelity signal applications.
- **Output Voltage Swing**: The range of output voltages the op-amp can provide. Ensure it meets the requirements of your application, especially if operating close to the power supply rails.
- **Noise**: The amount of electrical noise generated by the op-amp. Lower noise is critical for precision and low-signal applications.
- **Package Type**: The physical package (e.g., DIP, SOIC, QFN) affects how the op-amp can be mounted and integrated into a circuit.
- **Power Supply Voltage Range**: The range of supply voltages the op-amp can operate within. Ensure it is compatible with your power supply.
- **Offset Voltage Drift**: The change in input offset voltage with temperature. Lower drift is important for maintaining accuracy across varying temperatures.


</details>

### Multiple OpAmps In One Package
*OpAmp ICs* can contain more than one *OpAmp* circuit:

- **Single Op-Amp**: A chip with one operational amplifier. Common examples include the LM741 and LM358.
- **Dual Op-Amp**: A chip with two operational amplifiers. Popular examples are the LM358 and the TL072.
- **Quad Op-Amp**: A chip with four operational amplifiers. Common examples include the LM324 and the TL074.
- **Octal Op-Amp**: A chip with eight operational amplifiers. An example is the LM324.
- **Multiple Op-Amps (More than Eight)**: Some specialized chips can contain more than eight op-amps, though these are less common and often used in complex or custom applications.



<details><summary>Caveat: bigger is NOT always better...</summary><br/>    

Picking an *OpAmp IC* with as many internal *OpAmps* as possible - *just in case* - seems to make sense from an economic perspective: after all, *ICs* with four or more *OpAmps* are often not much more expensive than those with just one or two.

There are *obvious disadvantages* when you are using only part of the *OpAmps* in a chip, though: each individual *OpAmp* inside the *IC* requires a quiescent current of 100 µA or so (whether you use it or not), takes up space, and adds pins. Then again, you may not have space constraints, and you may not care about a couple hundred µA wasted power. Are you good then? Unfortunately not.

The *real* power loss may be a hundred times higher than the quiescent current, and you risk that your signal processing is not working as expected, or the chip gets destroyed entirely. Here is why (excerpt from [an engineering discussion at Analog Devices](https://www.analog.com/en/resources/analog-dialogue/raqs/raq-issue-46.html#:~:text=If%20the%20terminals%20are%20all,cause%20saturation%20and%20power%20waste.)):

#### Power Waste Or Damage

If the terminals of unused *OpAmps* are left unconnected, stray electromagnetic fields can cause an input to go outside the supply rails. This may cause latch-up and destroy the chip. If latch-up does not happen, a *dc* field may cause saturation, and a power waste much higher than the quiescent current results. The amplifier may also pick up and amplify an *ac* field and, if overdriven, heavily modulates its own supply current, causing crosstalk to other amplifier(s) on the chip. In short, an unconnected *OpAmp* can do unexpected things based on electromagnetic fields.

That's why users sometimes try and connect unused terminals to known potentials in an effort to prevent stray electromagnetic influences. Here are some commonly seen approaches **that you definitely should NOT do:**

* **Connect one input to the positive supply and the other input to the negative supply:** saturates the output, wastes power and may exceed the differential input voltage rating and damage the device. Even if damage does not occur, some input stages draw several tens of milliamps under these conditions, wasting even more power.
* **Grounding both inputs, or shorting them together:** causes the output stage to saturate, since the offset voltage of an op-amp is never exactly zero; shorting them together and not biasing them has the same latch-up risks as mentioned before.

#### Recommendations

If you have unused *OpAmps*, then *use* them: employ them in a defined and safe way that draws the least energy:

* **Follower:** connect the output to the inverting input, and connect the non-inverting input to a potential somewhere between the supply rails. Connecting to the positive or negative supply of a single supply system will cause saturation (power waste) if the offset voltage has the wrong polarity. 
* **Buffer:** use it in a simple *buffer amplifier* configuration for some other part of your circuitry (that does not need one but might even perform slightly better if it had one, at least isn't hurt by an additional buffer).


By far the easiest solution is to pick an *IC* with just the number of *OpAmps* you need in the first place. For simple DIY projects and devices that are not critical when failing, try and at least pick an *IC* that is *close* to the number of *OpAmps* you need, minimizing the mentioned side effects: rather not use a *Quad Op-Amp* when you really just need one.



</details>


## Example: MCP6002

The [MCP6002](materials/mcp6002_datasheet.pdf) is a popular *OpAmp* found in many DIY projects. Let's take a closer look at this example.

The *MCP6002* is a low-power, dual operational amplifier from [Microchip Technology](https://www.microchip.com/en-us/product/MCP6002). It is part of the *MCP600x* series of op-amps, which are known for low power consumption, low offset voltage, and rail-to-rail input/output capability: 


* **MCP6001:** 5-pin, **one** *OpAmp*
* **MCP6002:** 8-pin, **two** *OpAmps*
* **MCP6004:** 14-pin, **four** *OpAmps*

### Key Specifications

- **Supply Voltage Range:** 1.8V to 6.0V
- **Quiescent Current:** 100 µA (typical at 5V per amplifier)
- **Gain Bandwidth Product:** 1 MHz
- **Slew Rate:** 0.6 V/µs
- **Input Offset Voltage:** 4 mV (typical)
- **Input Bias Current:** 1 pA (typical)
- **Operating Temperature Range:** 
  - **Industrial:** -40°C to +85°C 
  - **Extended:** up to +125°C
- **Rail-to-Rail Input and Output:** Yes


### Advantages
These are some of the key advantages that make *MCP6002* a popular choice in DIY projects:


* **Wide Operating Voltage Range:** it operates over a wide supply voltage range from 1.8V to 6.0V and thus supports both *3.3V* and *5V* microcontrollers.
* **Rail-to-Rail:** input can swing from the negative rail (ground) to the positive rail (Vdd), and the output can go almost all the way to both supply rails. That is a very important benefit.
* **Low Power Consumption:** unlike *MCP602*, the *MCP6002* is very energy efficient with a typical quiescent current of just 100 µA per amplifier at 5V. This makes it ideal for portable and battery-operated devices.
* **Two OpAmps:** has *two* *OpAmps* which is what DIY projects typically need, minimizing the risk of leaving OpAmps unused (see above) as would often be the case with *MCP6004* or generally models that contain more than two *OpAmps*.
* **Temperature Range:** with -40°C to +85°C, this *OpAmp* can be used in almost all environments.
* **Low Cost:** widely available, with a robust supply chain ensuring easy sourcing for manufacturers.
* **Single-Sided Power Supply:** operates in-between a positive voltage and **GND** (i.e. a *battery*, *USB power supply*, *bench power supply*). If you need to work with *positive* **and** *negative* voltages and use *GND* as a midpoint, you must use a different *OpAmp*.
* **Precision:** input offset voltage is around 4 mV. That is sufficient for many precision applications, helping to minimize error in analog signal processing including sensor signal conditioning.
* **Stability:** stable at unity gain, which simplifies circuit design, especially in feedback configurations. With a decent phase margin, it can be used in a variety of filter and feedback circuits without risking instability.
* **Input Bias Current:** typically 1 pA, which is quite low (good). 

> [!IMPORTANT]
> The *MCP600x OpAmps* are *general purpose* components that are very well suited for most DIY projects. They respond swiftly to signal changes, but this may not be fast enough for projects involving *high frequency* or *rapid signal changes* due to its *GBWP* of *1 MHz*, and its *Slew Rate* of *0.6 V/µs*. 


### Package Type
*Package type* describes the form factor in which the *OpAmps* reside. The *MCP6002* is available in different package types: *PDIP* (*plastic dual inline package*), *SOT-23-8* (*small outline transistor 8 leads*), *SOIC* (*small outline integrated circuit*), and *MSOP* (*mini small outline package*). 

*SOT*, *SOIC* and *MSOP* are tiny and require special soldering techniques (reflow soldering). They are hard to use in DIY projects and aim to miniaturize professionally produced PCBs.

<img src="images/opamp-mcp6002_illustration_t.png" width="50%" height="50%" />



*PDIP* (*DIP*) is the *classic IC package* that still has individual *legs* which can be easily plugged into prototyping bread boards. For simple DIY projects, this package type is most popular.

### Pin Out
The *MCP6002* has eight pins and contains two *OpAmps*. Each *OpAmp* requires three pins plus a power supply:

#### Operational Amplifier Pins

* **Non-Inverting Input (+)):** Input signal in phase with the signal
* **Inverting Input (-)):** Input signal 180 degrees out of phase with the input. Often, this pin is used for feedback signals.
* **Output (Vout):** amplified output signal based on the difference between the two input voltages
* **Positive Supply Voltage (VDD):** *1.8V*-*6.0V*
* **Ground or Negative Supply Voltage (VSS):  the *MCP600x* does not support dual power supplies (with negative voltages), so this is always **GND**.

    <img src="images/single_opamp_illustration.png" width="50%" height="50%" />

#### DIP Package Pins
The *MCP6002* comes in a 8-pin DIP package:

* **VDD:** +*1.8V*-*6.0V*
* **VSS:** *GND*
* **VinA-, VinA+, VoutA:** OpAmp *#1*
* **VinB-, VinB+, VoutB:** OpAmp *#2*



    <img src="images/mcp6002_schematic2.png" width="100%" height="100%" />

> Tags: OpAmp, Operational Amplifier, MCP6002, Slew, DIP, Package, PDIP, SOT, SOIC, MSOP, Input Offset Voltage, rail-to-rail

[Visit Page on Website](https://done.land/components/opamp?516644081822241138) - created 2024-08-21 - last edited 2024-08-21
