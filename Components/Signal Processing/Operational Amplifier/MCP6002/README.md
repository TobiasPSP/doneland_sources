<img src="/assets/images/opampsmall.png" width="80%" height="80%" />
 
# MCP6002

> Modern Rail-to-Rail OpAmp That Can Sink And Source Up To 20mA

The [MCP6002](materials/mcp6002_datasheet.pdf) is a modern low-power, dual operational amplifier from [Microchip Technology](https://www.microchip.com/en-us/product/MCP6002). It is part of the *MCP600x* series of op-amps, which are known for low power consumption, low offset voltage, and rail-to-rail input/output capability: 


* **MCP6001:** 5-pin, **one** *OpAmp*
* **MCP6002:** 8-pin, **two** *OpAmps*
* **MCP6004:** 14-pin, **four** *OpAmps*


> [!TIP]
> Do not confuse the *MCP6002* with the *MCP602*. The *MCP602* is more expensive and better suited for *high frequency applications* with a *gain bandwidth product* of *10MHz* (versus *1MHz*), and a *slew rate* of *7V/us* (versus *0.6V/us*).






> [!IMPORTANT]
> Do not purchase the *MCP6002* from untrusted sources like *AliExpress*. Else, you will almost inevitably receive faked chips that in reality are very basic and old non-rail-to-rail *OpAmps* (at least I did from four different sellers). If you got them already, [always test them](https://done.land/components/signalprocessing/opamp/fakeopamps) before use. Akquire *MCP6002* from renown distributors like [Mouser](https://www.mouser.com), [DigiKey](https://www.digikey.com/), or similar.







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
* **Two OpAmps:** minimizing the risk of leaving OpAmps unused (see above) as would often be the case with models that contain more than two *OpAmps*. The majority of DIY projects uses no more than two *OpAmps*. If more are required, adding more *MCP6002* is always possible.
* **Temperature Range:** with -40°C to +85°C, this *OpAmp* can be used in almost all environments.
* **Low Cost:** widely available, with a robust supply chain ensuring easy sourcing for manufacturers.
* **Single-Sided Power Supply:** operates in-between a positive voltage and **GND** (i.e. a *battery*, *USB power supply*, *bench power supply*). If you need to work with *positive* **and** *negative* voltages and use *GND* as a midpoint, you must use a different *OpAmp*.
* **Precision:** input offset voltage is around 4 mV. That is sufficient for many precision applications, helping to minimize error in analog signal processing including sensor signal conditioning.
* **Stability:** stable at unity gain, which simplifies circuit design, especially in feedback configurations. With a decent phase margin, it can be used in a variety of filter and feedback circuits without risking instability.
* **Input Bias Current:** typically 1 pA, which is quite low (good). 

> [!IMPORTANT]
> The *MCP600x OpAmps* are *general purpose* components that are very well suited for most DIY projects. They respond swiftly to signal changes, but this may still not be fast enough for projects involving *high frequency* or *rapid signal changes* due to its *GBWP* of *1 MHz*, and its *Slew Rate* of *0.6 V/µs*. 


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
* **Ground or Negative Supply Voltage (VSS):**  the *MCP600x* does not support dual power supplies (with negative voltages), so this is always **GND**.

    <img src="images/single_opamp_illustration.png" width="50%" height="50%" />

#### DIP Package Pins
The *MCP6002* comes in a 8-pin DIP package:

* **VDD:** +*1.8V*-*6.0V*
* **VSS:** *GND*
* **VinA-, VinA+, VoutA:** OpAmp *#1*
* **VinB-, VinB+, VoutB:** OpAmp *#2*



    <img src="images/mcp6002_schematic2.png" width="100%" height="100%" />

> Tags: OpAmp, Operational Amplifier, MCP6002, Slew, DIP, Package, PDIP, SOT, SOIC, MSOP, Input Offset Voltage, rail-to-rail

[Visit Page on Website](https://done.land/components/signalprocessing/operationalamplifier/mcp6002?806419081329240816) - created 2024-08-28 - last edited 2024-08-28
