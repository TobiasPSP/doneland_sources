<img src="/assets/images/opampsmall.png" width="80%" height="80%" />
 
# Operational Amplifier

> Comparing Voltages And Amplifying Signals

An *operational amplifier* (*OpAmp*) is a very versatile component: it amplifies the difference between two input voltages. 

This simple functionality enables a surprisingly wide area of functionalities: *OpAmps* are found in the tone controls of audio amplifiers, in the feedback circuits of analog-to-digital converters, and in the active filters of signal processing systems.

In DIY projects, *OpAmps* compare voltages, cut off power when a battery is fully charged, or build signal generators.

> [!IMPORTANT]
> *OpAmps* are among the most commonly **faked components**, especially with modern and high quality *OpAmps* like the *MCP6002*. Never purchase them from untrusted sources such as *AliExpress*. If you have done  already, or are unsure whether your *OpAmp* is genuine, [test them](https://done.land/components/signalprocessing/operationalamplifier/fakeopamps). Using fake *OpAmps* in your projects and circuits is **complete frustration**:  circuits don't work, you waste hours in troubleshooting, and other components may even get damaged.

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

> Tags: OpAmp, Operational Amplifier, MCP6002, Slew, DIP, Package, PDIP, SOT, SOIC, MSOP, Input Offset Voltage, rail-to-rail

[Visit Page on Website](https://done.land/components/signalprocessing/operationalamplifier?516644081822241138) - created 2024-08-21 - last edited 2024-08-28
