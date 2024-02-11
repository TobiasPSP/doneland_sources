# Welcome to **Done Land** 

Welcome to this repository: here you find information about electronic components, microcontrollers, plus many examples illustrating actual usage.

All content focuses on *practical use* and quick success. It may not always be scientifically correct down to the last detail as long as it is simple to understand and of immediate and safe practical use.

> [!TIP]
> If you find *practically* incorrect statements or would like to add your own tricks and insights, please go to the menu on top of this page and file an [issue](https://github.com/TobiasPSP/doneland/issues), or visit the [discussion](https://github.com/TobiasPSP/doneland/discussions) forum.
> 
> We focus on *practically relevant* information. Please do not file an issue if you feel that there is an *academic* issue with terminology used or explanations given.
> 
> Should you find information that is simply *wrong* or would even lead to *damage* or *malfunction*, or if you'd like to share own *practically relevant* experience, you are most welcome.

This repository is a work in progress. When you visit next week, chances are that you'll see the topic list below grow. So feel free to check back often.

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
