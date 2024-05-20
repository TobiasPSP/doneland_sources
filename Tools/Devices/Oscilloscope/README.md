<img src="/assets/images/oscilloscope.png" width="80%" height="80%" />
 
# Oscilloscope

> Visualizing High-Frequency Voltage Changes 

An oscilloscope visualizes voltage changes, providing a graphical representation of voltage over time.

While a classic *multimeter* measures voltage as a *static value*, *oscilloscopes* are needed when *voltages change rapidly*.

For example, many *control signals* (like UART, I2C, SPI, etc.) consist of a series of impulses with frequencies in the range of kilohertz or megahertz. A simple *multimeter* would be unable to diagnose such signals primarily because of two limitations:

* **Speed:** A *multimeter* is way too slow to pick up voltage changes that occur in milli- or microseconds.
* **Display:** When diagnosing rapidly changing voltages, a *numeric display* is inappropriate as it would be impossible to read thousands of values per second.

Oscilloscopes can visualize rapidly changing voltages because they can *sample the voltage* many million times per second. They also do not show individual voltages but rather draw graphs, visualizing voltage changes over time by showing their *wave forms*.

## Key Features
When comparing *oscilloscopes*, the following key features are important:


* **Resolution:** number of bits used in the analog-to-digital converter (ADC) to represent the measured *voltage*. Higher resolution lets the oscilloscope detect smaller voltage changes, providing more detailed *vertical* measurements (amplitude). An 8-bit resolution can discern 256 discrete voltage levels, whereas a 12-bit resolution can show 4096 levels. 
* **Sampling Rate:** number of samples the oscilloscope takes per second. The sampling rate determines the *number of measurements* that can be taken per time, determining the detail in the *horizonzal* axis. detail and precision of the waveform capture. The sample rate is typically specified as *Msps* (million samples per second) or *Gsps* (billion samples per second) and determines the granularity of the *horizontal* axis of the graph. The sampling rate must be at least twice as much as the highest frequency you want to diagnose (Nyquist theorem). In practical scenarios, accurate results often require a sample rate of 5 to 10 times the highest frequency of interest. 
* **Bandwidth:** defines the range of frequencies the oscilloscope can accurately measure. A higher bandwidth allows the oscilloscope to capture faster, higher-frequency signals. Bandwidth is crucial for ensuring the device can follow rapid changes in the signal without distortion. Generally, to accurately capture signals, the bandwidth of the oscilloscope should be a significant portion of the sample rate (often around 1/5th of the sample rate).
* **Channels:** Number of separate signals that can be measured *simultaneously*. For diagnosis, it is often important to visualize multiple signals side-by-side. For example, to diagnose a control signal, it may be necessary to visualize the *data signal* and the underlying *clock signal*.
* **Memory:** Determines how much data can be stored for analysis, directly impacting the length of a waveform that can be captured at high resolution.
* **Triggers:** additional capabilities to respond to the captured signals and pick a waveform i.e. based on rising or falling signals.

### Interrelated Features
*Sample Rate*, *Resolution*, and *Bandwidth* are closely interrelated but distinct aspects of an oscilloscope. They together define how sensitive an *oscilloscope* is:

* **Quality of Voltage Measurement:** *Resolution* determines how accurately the *oscilloscope* can measure *voltage*. The higher the *resolution*, the *smaller* are the voltage increments the *oscilloscope* can discern.
* **Number of Voltage Measurements:** the *Sample Rate* determines how often the *voltage* can be measured in a given time. The higher the *sample rate*, the *faster* can signals be that you want to diagnose. *Bandwidth* is somewhat the same however focusing on the *signal processing components* and their maximum frequency limit.

As a *rule of thumb*, the sample rate should be at least 2.5 to 5 times the oscilloscope's bandwidth. For instance, if an oscilloscope has a bandwidth of 100 MHz, a typical sample rate might be 250 Msps to 500 Msps.

An oscilloscope with a 100 Msps sample rate might have a bandwidth of around 20 MHz to 40 MHz. This is because to accurately reconstruct the waveform and capture its details, especially at higher frequencies, the sample rate must be significantly higher than the oscilloscope's bandwidth.


> Tags: Voltage, Frequency, Sample Rate, Bandwidth, Resolution, Diagnosis, Waveform

[Visit Page on Website](https://done.land/tools/devices/oscilloscope?464692052018240527) - created 2024-05-17 - last edited 2024-05-17
