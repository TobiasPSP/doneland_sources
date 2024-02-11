# Welcome to **Done Land** 

Welcome to this place where I *document* and *explain* things as I encounter them during my projects. These can be fundamentals, data sheets, hints or just practical tips about electronics, microcontrollers, tools, and scripts. My content focuses on quick and useful *facts* and *no nonsense* information rather than scientific accuracy. 

All information is structured in a tree-like hierarchy for easy discovery.

> [!TIP]
> If you find typos or would like to add *practically relevant* comments or corrections, please file an [issue](https://github.com/TobiasPSP/doneland/issues). If you have questions or would like to get in touch, visit the [discussion](https://github.com/TobiasPSP/doneland/discussions) forum.

This repository is a work in progress. When you visit next week, chances are that you'll see many more topics. Feel free to check back often.

> This repository is mirrored as a website at [powershell.one/doneland](https://powershell.one/doneland/). The original sources are visible and accessible at [github.com/TobiasPSP/doneland](https://github.com/TobiasPSP/doneland).
>
> Both places are great to read and dive into the content, and I urge you to try them both.
>
> The website may feel more focused. Once you get used to the *github repository* user interface though, visiting the repo directly is much more powerful: in the top pane, you always have easy access to all file-based resources, and on the left you can easily navigate the sites' tree structure.
>
> Website mirroring is done automatically by *github*. The generated website may still have minor formatting deficiencies. Unfortunately, *github pages* does not yet fully support all *github markdown* that I used in my content.

Content is structured in major categories:

## Basic Components

Single parts of electrical circuits with one dominant function:

* [Transistors](Components/Basic/Transistor)

## Power

### [Measuring Current and Voltage](Components/Power/Measuring%20Current)

Knowing the actual *voltage* and *current* is a prerequisite for data logging, electronic fuses, power supplies, chargers and so much more. I am looking into different ways to measure *voltage* and *current*.

One way to measure *current* is [via *shunts*](Components/Power/Measuring%20Current/Via%20Shunt), and there are excellent and cheap controllers that may do out-of-the box exactly what you need:

* [INA226](Components/Power/Measuring%20Current/Via%20Shunt/ina226)

### [BMS (Battery Management Systems)](Components/Power/BMS)

Modern rechargeable *lithium*-based batteries can be damaged or catch fire when used wrongly. **BMS** are electronic components designed to *protect* batteries from a number of mishaps.

### [DC-DC Converters](Components/Power/DC-DC-Converters)

They can *lower* or *raise* an input voltage. Important part of a *power supply* to ensure your devices and projects receive the appropriate *voltage* and/or *current*.

Controllers are typically sold in a ready-to-go breakout board.

#### Buck-Converter (lowering the voltage)

* [LM5116](Components/Power/DC-DC-Converters/buck/LM5116)
* [XL4005](Components/Power/DC-DC-Converters/buck/XL4005)
* [XL4015](Components/Power/DC-DC-Converters/buck/XL4015)
* [XL4016](Components/Power/DC-DC-Converters/buck/XL4016)


## Human Interface

Most electronic projects require human input and interaction. There are a number of *human interface devices* worth looking into:

* [Rotary Encoders](Components/Human%20Interface/Rotary%20Encoder)

## Projects

Here is a list of my current projects I am chewing on:

* **[Digitally controllable Buck Converter](Projects/Programmable%20Buck%20Converter/Via%20Voltage%20Injection)**: You can get powerful **Buck** converters (breakout boards that can lower the *voltage* and provide *constant voltage* (CV) and *constant current* (CC)) for just a few Euro. In this project I want to add a simple way of controlling *CV* and *CC* digitally, i.e. via a microcontroller. Once that works, a digitally controllable **Buck** converter is the basis for intelligent chargers and many follow-up projects.

## Tools

I am using a set of tools that I share with you:

* **[Cropping and Adding Solid Backgrounds for *svg* Images](Tools/Software/PowerShell/Image%20Processing/Cropping%20and%20Transparency/.svg%20Files):** I have written a **PowerShell Module** that provides a new *cmdlet*: `Format-Svg`. With this *cmdlet*, I am prettifying *svg* schematics drawings produced by *KiCAD*. The *cmdlet* can crop and automatically remove excess whitespace, and it can automatically add solid backgrounds.
*  **[Exporting *svg* to *png* Files](Tools/Software/PowerShell/Image%20Processing/File%20Format%20Conversion/.svg%20to%20.png):** There are many ways to export *svg* vector graphics to *png* pixel image files but most of them aren't very flexible and i.e. cannot remove transparency or export in extra high resolution. I am using the free *Inkscape* software and control it via *console commands*. That works excellent for me. 

