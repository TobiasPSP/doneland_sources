<img src="/assets/images/components.png" width="80%" height="80%" />
 
# Logic ICs

> Logically Combining Digital Input Signals

*Logic ICs* take two or more digital input signals and *combine these input signals* in a logical manner, producing a new *digital output signal*.

*Logic ICs* can perform fundamental low-level logic operations such as *AND*, *OR*, *XOR*, *NOT*, may process *sequence of signals* (as in *FlipFlops* or *Counters*), or even apply soophisticated signal processing (as in *Encoders*).

All of these logic operations can also be performed in software, so in microcontroller-based projects, *logic level ICs* are much less often used. However, even with microcontrollers, *logic level ICs* may be used for two primary reasons:

* **Speed:** as hardware devices, signal processing is much faster compared to software solutions
* **Simplicity:** can shift complexity away from firmware: it may just be simpler to add a hardware logic IC in your circuitry to solve a challenge rather than having to deal with signal processing in firmware.

## Groups Of Logic ICs

Here are a few of the more popular *logic ICs*:

* **Logic Gates:** perform fundamental logic operations (see next section for details)
* **Buffers:** strengthen or isolate signals to prevent signal degradation and ensure proper transmission across circuits. They are used to interface between different parts of a circuit, protecting against signal loss or interference.
* **FlipFlop:** bistable devices that store a single bit of data, with two stable states (0 and 1). They are used for creating memory elements, counters, and registers in digital systems, as they can "flip" between states based on input signals.
* **Counters:** sequential logic circuits that count pulses, typically in binary or decimal form. They are widely used in time-keeping, event counting, frequency division, and digital clocks.
* **Shift Registers:** shift data bits in or out of a register, serially or in parallel. They are essential in data storage, transfer, and conversion between serial and parallel formats, often used in communication systems.
* **Adders:** arithmetic circuits that perform binary addition, often forming the basis for arithmetic logic units (ALUs) in processors. They add binary numbers and are essential for all computational tasks in digital electronics.
* **Timers:** generate precise time delays, oscillations, and pulse-width modulated signals. They are used in timing applications, like setting delays, generating clocks, and creating waveform signals in various digital circuits.
* **Multiplexers:** select one of many input signals and forward it to a single output, while demultiplexers take a single input and route it to one of many outputs. 
* **Encoders/Decoders:** convert multiple input lines into a smaller number of outputs, typically binary code, while decoders perform the reverse, converting binary inputs into a larger number of outputs. They are key in data encoding, communication, and address decoding in memory systems.


## Logic Gates

* **AND:** *high* when both inputs are *high*, else *low*
* **NAND:** inverted *AND*. *low* when both inputs are *high*, else *high*
* **OR:** *high* when at least one input is *high*, else *low*
* **NOR:** inverted *OR*. *low* when at least one input is *high*, else *high*
* **XOR:** *high* when exactly one input is *high*, regardless which, else *low*
* **XNOR:** inverted *XOR*. *low* when exactly one input is *high*, regardless which, else *high*
* **NOT:** reverses logic level, has just one input



### AND Gate

| A | B | A AND B |
|---|---|---------|
| 0 | 0 |    0    |
| 0 | 1 |    0    |
| 1 | 0 |    0    |
| 1 | 1 |    1    |


### NAND Gate

| A | B | A NAND B |
|---|---|----------|
| 0 | 0 |    1     |
| 0 | 1 |    1     |
| 1 | 0 |    1     |
| 1 | 1 |    0     |

### OR Gate

| A | B | A OR B |
|---|---|--------|
| 0 | 0 |   0    |
| 0 | 1 |   1    |
| 1 | 0 |   1    |
| 1 | 1 |   1    |


### NOR Gate

| A | B | A NOR B |
|---|---|---------|
| 0 | 0 |    1    |
| 0 | 1 |    0    |
| 1 | 0 |    0    |
| 1 | 1 |    0    |




### XOR Gate

| A | B | A XOR B |
|---|---|---------|
| 0 | 0 |    0    |
| 0 | 1 |    1    |
| 1 | 0 |    1    |
| 1 | 1 |    0    |

### XNOR Gate

| A | B | A XNOR B |
|---|---|----------|
| 0 | 0 |    1     |
| 0 | 1 |    0     |
| 1 | 0 |    0     |
| 1 | 1 |    1     |


### NOT Gate

| A | NOT A |
|---|-------|
| 0 |   1   |
| 1 |   0   |

> Tags: AND, NAND, OR, NOR, XOR, XNOR, NOT, Logic Level

[Visit Page on Website](https://done.land/components/signalprocessing/logicics?257651081329241200) - created 2024-08-28 - last edited 2024-08-28
