# Welcome to **Done Land** 

Welcome to this place where I *document* and *explain* things that I encounter during my projects. It can be fundamentals, data sheets, hints and practical tips about electronics, microcontrollers, tools, and scripts. All content focuses on quick *facts* and *no nonsense* information rather than scientific accuracy. 

I am trying to *structure* the information in a most meaningful tree-like hierarchy for easy discovery.

> [!TIP]
> If you find typos or would like to add *practically relevant* comments or corrections, please file an [issue](https://github.com/TobiasPSP/doneland/issues). If you have questions or would like to get in touch, visit the [discussion](https://github.com/TobiasPSP/doneland/discussions) forum.

This repository is a work in progress. When you visit next week, chances are that you'll see many more topics. Feel free to check back often.

> This repository is mirrored as a website at [powershell.one/doneland](https://powershell.one/doneland/). The original sources are visible and accessible at [github.com/TobiasPSP/doneland](https://github.com/TobiasPSP/doneland).
>
> Both places are great to read and dive into the content, and I urge you to try them both. The website may feel more focused. Once you get used to the *github repository structure* though, visiting the repo directly is much more powerful: in the top pane, you always have easy access to all file-based resources, and on the left you can easily navigate the sites' tree structure.
>
> Website mirroring is done automatically by *github*. The generated website may still have minor formatting deficiencies. Unfortunately, *github pages* does not yet fully support all *github markdown* that I used in my content.

Content is structured in major categories:

## Basic Components

Single parts of electrical circuits with one dominant function:

* [Transistors](Components/Basic/Transistor)

## Power

### [Measuring Current and Voltage](Components/Power/Measuring%20Current)

Knowing the actual *voltage* and *current* is a prerequisite for data logging, electronic fuses, power supplies, chargers and so much more. I am looking into different ways to measure *voltage* and *current*.




### [BMS (Battery Management Systems)](Components/Power/BMS)

Modern rechargeable *lithium*-based batteries can be damaged or catch fire when used wrongly. **BMS** are electronic components designed to *protect* batteries from a number of mishaps.


### [DC-DC Converters](Components/Power/DC-DC-Converters)

They can *lower* or *raise* an input voltage. Important part of a *power supply* to ensure your devices and projects receive the appropriate *voltage* and/or *current*.

For example, *current* can be measured [via *shunts*](Components/Power/Measuring%20Current/Via%20Shunt), and there are excellent and cheap controllers that may do out-of-the box exactly what you need:

* [INA226](Components/Power/Measuring%20Current/Via%20Shunt/ina226)

Controllers are typically sold in a ready-to-go breakout board.

### Buck-Converter (lowering the voltage)

* [LM5116](Components/Power/DC-DC-Converters/buck/LM5116)
* [XL4005](Components/Power/DC-DC-Converters/buck/XL4005)
* [XL4015](Components/Power/DC-DC-Converters/buck/XL4015)
* [XL4016](Components/Power/DC-DC-Converters/buck/XL4016)

## Human Interface

Most electronic projects require human input and interaction. There are a number of *human interface devices* worth looking into:

* [Rotary Encoders](Components/Human%20Interface/Rotary%20Encoder)
