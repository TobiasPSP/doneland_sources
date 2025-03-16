<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Introduction to Wireless Data Transmission

> How Wireless Data Trasmission Works, And Identifying The Best Devices For A Use Case

When starting with wireless transmissions, there is an overwhelming number of moving parts: frequencies, RF power, transmitter, receiver, modulations and so much more.

In this section, I am explaining the basics of wireless data transmissions in a fun and practical step-by-step series, including sample projects that you can build or expand on.

## Overview
*Electromagnetic waves* carry energy through space without the need for physical wires. They oscillate at certain frequencies and can travel long distances at the speed of light. The distance they can bridge depends on frequency and power.

### Spark-Gap Transmitters
Initially, it was discovered that **sparks** emit electromagnetic waves, and the first radio transmitters were [spark-gap transmitters](https://en.wikipedia.org/wiki/Spark-gap_transmitter). [Guglielmo Marconi](https://en.wikipedia.org/wiki/Guglielmo_Marconi) created radiotelegraphy communication on the basis of them which played a crucial role 1912 in the maritime rescue of the RMS Titanic disaster.

### Oscillating Circuit
It is not the spark itself though that produces the radio waves. The spark just serves as a fast acting switch to excite oscillating electric currents. 

The oscillating conductors - **any** oscillating conductor - radiate energy as radio waves.

## Modern Radio Wave Generators
Modern radio wave generators (and receivers) have much improved, mainly due to two factors:

* **Transistor:** there are much better *fast-acting switches* than sparks. For a while, vacuum tubes were used, and then largely replaced by semiconductors like transistors.
* **Crystal:** Uses a piezoelectric crystal (i.e. quartz) that oscillates at a highly stable frequency. Unlike classic LC circuits, the frequency is determined by the physical properties of the crystal, and does not depend on the values of the inductor and capacitor, which in turn are affected by temperature, humidity, and aging.

*Crystal Oscillators* are much more precise but also more complex to build: crystal resonant frequency range is typically in the range of a few hundred kHz to 30-40MHz. Higher frequencies (and most modern wireless technologies use *much* higher frequencies in the range of *400MHz-20GHz*) require additional techniques that *multiply* the crystal frequency.

That's why for simple use cases - i.e. remote controls - today occasionally still simple LC circuits without a crystal are in use.

## Modern RF Receivers
Radio energy can be re-converted back to electrical energy in a number of ways:

* **Superregenerative:** uses positive feedback to amplify weak RF signals. This is simple and cheap, but it also doesn't work reliably. Superregenerative receivers can be found in toys, and occasionally they are also bundled with decent RF sender boards (i.e. [MX-RM-5V](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/mx-rm-5v/)). Try and avoid superregenerative receivers as they often don't work, and they are just a few cents cheaper than decent superheterodyne receivers anyway.
* **Superheterodyne:** Converts RF signals to an intermediate frequency (IF) for better filtering and amplification. This is how most professional transceivers and walky-talkys work, too, and there are plenty of superheterodyne receiver modules available (i.e. [AK-RXB59R](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/ak-rxb59r/), [RX470-4](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/rx470-4/), [SYN480R](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/syn480r/), [RXB*xxx*](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/rxb8/)).
* **SDR:** *Software Defined Radio* uses digital signal processing (DSP) to handle RF signals, replacing many analog components. SDR does not target data transmission in IoT devices but *complements* it for *analyzing* RF signals. SDR can monitor an entire frequency range, visualize signals in waterfall diagrams, and examine modulations and bandwidths.


### Super-Regenerative vs. Superheterodyne Receivers

| Feature                | Super-Regenerative                          | Superheterodyne                         |
|------------------------|--------------------------------------------|-----------------------------------------|
| **Principle of Operation** | Uses positive feedback in short bursts to amplify weak signals | Converts RF signals to a lower intermediate frequency (IF) for improved processing |
| **Selectivity**        | Poor, easily affected by interference      | Excellent, sharp filtering at IF stage |
| **Sensitivity**        | High but inconsistent                      | High and stable                        |
| **Frequency Range**    | Low to Medium (kHz - MHz)                  | Wide (kHz - GHz)                        |
| **Stability**         | Poor, prone to drift                        | Very stable due to fixed IF filtering  |
| **Complexity**         | Very simple, few components                | Complex, requires mixers, IF amplifiers, and filters |
| **Cost**              | Very cheap                                  | More expensive due to additional components |
| **Power Consumption**  | Very low                                    | Higher, due to multiple amplification stages |
| **Typical Applications** | Toy radios, low-cost wireless receivers  | AM/FM radio, TV tuners, radar, communication receivers |
| **Modern Relevance**   | Mostly obsolete, used in niche applications | Still widely used in many RF systems |



## Antenna
For an electromagnetic wave to be radiated into space (i.e., to transmit), or picked up again and converted to an electric signal (i.e., to receive), the resonant circuit must be connected to an antenna. 

The antenna converts the electrical oscillations from the circuit into electromagnetic radiation. In its most basic form, an antenna is simply a piece of wire. It must however have exactly the right length so that the oscillating currents can *resonate*.

The antenna size is related to the wavelength of the oscillating signal:

* **Frequency Hz (Hertz):** how many times per second your LC circuit oscillates
* **Wavelength λ (lambda, in meters):** divide the frequency by the speed of light. Since radio waves are travelling at the speed of light, this gives you the distance a radio wave travels at the given frequency during one cycle.

  ````
  λ=frequency / speed of light 
  ````

 For a signal at 433 MHz (for example), the wavelength is approximately 69.1 cm. A *full-λ* antenna would have a length of *69.1 cm*. To keep the antenna practical, it can be wound up as a coil (as long as the wire is insulated), or you can use *fractions* of the wavelength λ: a quarter-wave (around 17 cm) or half-wave (around 34.5 cm) antenna may fit better into your device, at the expense of reduced efficiency.

 > [!IMPORTANT]
 > If you do not use an antenna at all, or if the antenna length does not match your frequency, then your oscillating circuit will be unable to emit the radio energy. Instead, this energy floats back into the circuit and produces *heat*. In professional transmitters with higher RF output, a mismatched antenna can quickly **destroy** the power amplifier through overheat.




## Using Basic Radio Waves (OOK)
With just the theory discussed above, you can already start using radio waves and operate a basic *OOK* sender and receiver. 

*OOK* (*On-Off-Keying*) is the modern version of an early *Marconi Morse Code Setup*, just without the sparks: you can turn the transceiver **on** and **off**. When turned on, it emits a constant radio wave at a designated frequency. This radio wave can then be picked up by a receiver.

*OOK* is the basis of almost all digital wireless transmission modulations. In its most pure form (as described above), it does not need any complex *modulation*: a simple **OOK* transceiver is neither *AM* nor *FM* nor anything else. It is just a radio transmitter.

Later you'll see how you can *add modulation* to your OOK transceiver to do more. For now though, we focus on a simple *morse code transceiver* similar to the one that was used in 1912 to save the *RMS Titanic*.

### Transmitter

As a transmitter, I use the popular and affordable [FS1000A](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/sender/fs1000a/) sender.

<img src="images/433_fs1000a_tx_top_t.png" width="50%" height="50%" />

> [!IMPORTANT]
> Simple senders like the *FS1000A* are **theoretically** no rocket science: they consist of just a few components. If you are inclined to design your own LC circuits and/or integrate them into your PCBs, be aware. Designing a proper PCB for RF is challenging: traces, component orientation, distances on the PCB, you name it, all influence capacitances and overall oscillation. It's smarter to get ready-to-use breakout boards and plug them into your own PCBs. 

#### Pins
The board has three pins: **GND** and **VCC** supply the board with power, and any voltage in the range of *5-12V* will do. The higher the voltage, the more powerful the radio signal. At *5V* input voltage, the RF signal is rather weak.

The pin **ATAD** was printed backwards and is **DATA**: whenever this pin is *high*, the transmitter emits a radio wave at its designated frequency.

#### Frequency
These modules come for different ISM bands that can be used license-free for everybody - provided you do not exceed the regulatory thresholds like the maximum RF power. That's why you might want to operate the board with *5V* instead of *12V*. At *12V*, the output power may be *much* higher than the legal limit of *10mW*.

#### Board Design
The boards consists basically just of a LC circuit with a crystal. The coil on the board **is not the antenna**. You need to add an external antenna yourself and solder it to the through-hole solder pad marked **ANT**.

Often, these modules come with coil antennas (that you may want to wrap in some shrink tube for better optics and insulation). 

<img src="images/433_antenna_overview2_t.png" width="50%" height="50%" />

Or you use a simple wire of appropriate length as discussed above.

#### Receiver
Often, the *FS1000A* comes bundled with a very cheap *superregenerative* receiver module: [MX-RM-5V](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/mx-rm-5v/).


<img src="images/rx_mx-rm-5v_top_t.png" width="50%" height="50%" />

Superregenerative receivers like the *MX-RM-5V* are designed to work (somewhat) with signals in the range of 1-5kHz (burst of signals). They do not work well with signals that last longer, i.e. when creating a morse code generator where a "beep" can last a second or two.

That's why I generally do not use superregenerative receivers and switched to a *superheterodyne* receiver. I picked the [AK-RXB59R](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/ak-rxb59r/) but there are many others to choose from.



<img src="images/rf_rx_rxb59r_top_t.png" width="50%" height="50%" />


> [!IMPORTANT]
> Most **receiver** boards have much stricter requirements for supply voltage. Many require **5V** and do not work with **3.V**. **12V** destroys them. Look up the data sheet for the receiver you are using.   

## Morse Code Transceiver Setup

The receiver board essentially works like the transceiver board, just in the opposite way:

* **Sending Signal:** set **DATA** to *high* on the *sender* board. The sender starts sending out a continuous radio wave
* **Receiving Signal:** the receivers' **DATA** pin turns *high* when it receives the signal from the sender.

### Setting Up Sender

Connect the [FS1000A](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/sender/fs1000a/) like this:

| Pin | Connection |
| --- | --- |
| VCC | 5-12V |
| GND | Ground |
| DATA | Morse button, other end of button to *VCC* |


### Setting Up Receiver

Connect the [AK-RXB59R](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/ak-rxb59r/) (or any other superheterodyne reciever you picked) like this:


| Pin | Connection |
| --- | --- |
| V | 3.6-5V |
| G | Ground |
| DATA | connect LED or buzzer anode |

Depending on the receiver you are using, the **DATA** pin may not be providing enough power to directly drive your device. After al, the **DATA** pin of most receiver boards is designed to provide an input signal for a microcontroller. It is not designed to directly drive loads.

* **Add Microcontroller:** connect **DATA** to a digital **GPIO Input** pin. In your firmware, you can then respond to this GPIO changing from *low* to *high* and vice versa.
* **Add Transistor:**    
  - Connect the base/gate of a *NPN transistor* or *N-channel MosFET* (i.e. *2N222*, *TIP120*) to **DATA**. 
  - With *NPN-transistors*, use a 1-10kΩ current limiting resistor. 
  - Connect emitter/source to ground. 
  - Connect *collector/drain* to the *negative* side of the load.


## Materials


[Receiver Signal Measurements](https://youtu.be/bmLJvkIA__I?si=DmeE1JSHZeUn8-di)

> Tags: RF, Radio, Wave, Crystal, Spark, Wireless, Transmission

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/intro?580633031316254246) - created 2025-03-15 - last edited 2025-03-15
