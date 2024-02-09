# Battery Management System (BMS)
:stopwatch: Reading time: 10 minutes.

## Overview

Modern *lithium ion*, *lithium polymer*, and *LiFePo4* rechargable batteries store huge amounts of energy. Even small batteries can wreck havoc when the battery is short ciruited, and while these batteries are a solid source of portable power, they can be damaged and destroyed by wrong *charging* and *discharging*.

*Battery Management Systems* are electronic circuits designed to provide the necessary protection. Most high-quality batteries come with a *BMS* built-in. They are then labelled *protected*.

When you use such batteries to power your projects and devices, in many cases you should add your own *BMS*. For example, if you build your own *power banks*, *power packs*, or generally connect more than one battery *in series*, you need your own *BMS* to *balance* the individual batteries during charging.

> [!CAUTION]
> Below, I am discussing handling the commonly used *lithium ion* and *lithium polymer* batteries.
>
> If you use a *LiFePo4* battery, and even more so if you are using older technology like *lead* or *NiCad*, different thresholds apply based on the different battery chemistry.

### Important Protection Features

The following protection features are important and should be provided by the *BMS* you choose:

| Feature | Typical Threshold | Description |
| --- | --- | --- |
| Over voltage | >4.3V | Protects the battery from *over-charging*. When 

Whenever you connect more than one battery in *series*
[Small loads (up to 3A)](small)
[Medium loads (up to 8A)](medium)
