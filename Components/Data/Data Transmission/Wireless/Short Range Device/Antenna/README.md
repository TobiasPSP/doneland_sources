<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# SRD Antennas

> Precisely Tuned Antennas Improve SRD Efficiency And Reach

A precisely tuned *antenna* is one of the most affordable and most effective tuning mechanisms to improve transmission quality and reach. A piece of wire, cut to the exact length, can often outperform generic commercial antennas.

## Overview
Since *SRDs* operate with very low RF power (often <=10mW), you need to utilize as much of this energy as possible. That's why good antennas are especially important for *SRD*, both for transmitter and receiver.

The antenna quality is determined by a simple factor: the antenna must have a specific length that is **a fraction of the wave length**, and the longer the antenna the better.


## Antenna Length

Here is a table with the common antenna lenghts for ISM bands:

| ISM Band         | Frequency Range     | Wavelength (cm) | Quarter-Wave Antenna (cm) | Half-Wave Antenna (cm) | 5/8-Wave Antenna (cm) | Full-Wave Antenna (cm) |
|------------------|---------------------|-----------------|---------------------------|------------------------|-----------------------|------------------------|
| **315 MHz**      | 314.0 - 316.0 MHz   | 95.5 cm         | 23.9 cm                   | 47.8 cm                | 59.5 cm               | 95.5 cm                |
| **433 MHz**      | 430.0 - 440.0 MHz   | 69.2 cm         | 17.3 cm                   | 34.6 cm                | 43.2 cm               | 69.2 cm                |
| **868 MHz**      | 868.0 - 870.0 MHz   | 34.6 cm         | 8.65 cm                   | 17.3 cm                | 21.6 cm               | 34.6 cm                |
| **915 MHz**      | 902.0 - 928.0 MHz   | 32.8 cm         | 8.2 cm                    | 16.4 cm                | 20.5 cm               | 32.8 cm                |
| **2.4 GHz**      | 2.400 - 2.483 GHz   | 12.5 cm         | 3.1 cm                    | 6.25 cm                | 7.8 cm                | 12.5 cm                |
| **5.8 GHz**      | 5.725 - 5.850 GHz   | 5.17 cm         | 1.29 cm                   | 2.58 cm                | 3.22 cm               | 5.17 cm                |


There are even shorter antennas (i.e. rubber ducks): these are longer wires that have been formed to a coil.

### Precise Antenna Length

The **exact** antenna length is calculated by the formula **299792458 / *frequency (in Hertz)***. The former is the *speed of light*. If you are operating on a very specific frequency, i.e. using a EV1528 remote control, you can improve performance by cutting a cable *to the exact length* that is needed for this frequency. Such a *hand-tailored* antenna often performs much better than a generic commercial antenna.

> [!NOTE]
> This explains why users report better test results when using simple *coil antennas* coming with certain transceivers, when compared to boards with external IPEX antenna jack. Those coil antenna lengths are perfectly adjusted to the required frequencies, whereas external antennas often are generic rubberduck style antennas targeting a much wider frequency range. They may simply be optimized for a *different* frequency than the one you are using.    


### Hand-Tailored Antenna
For a typical *garage door opener* operating on *433.95MHz*, the perfect antenna length would be *299792458 / 433950000*. The result is *0.6908456227676*: the full wave length for this frequency is *69cm*.

Typical antennas use a quarter of the full wavelength (*lambda/4* or *1/4*). A good antenna length for *433.95MHz* devices could therefore be *17.3cm*.

### Get-AntennaLength Command

To calculate antenna lengths, use *PowerShell*. It is preinstalled on any *Windows PC* and can be downloaded for most other operating systems for free.

Next, install the *DoneLandTools* extension:

```powershell
Install-Module -Name DoneLandTools -Scope CurrentUser -Force -AllowClobber
```

> [!TIP]
> You may omit `-Force -AllowClobber` if you prefer to see confirmation dialogs.

Now it's simple to calculate antenna lengths. Simply specify the target frequency in MHz, for example `433.95`. 

```powershell
Get-AntennaLength 433.95
```

The result lists various resonant antenna lengths: pick the length that works best for you.

> [!TIP]
> Antennas work better the longer they are - as long as the picked length is resonant. So pick any length listed, and choose the longest one you can accommodate. If you wind up the antenna wire to a coil, the length is not as much important, and you should go with the 1/4 length.




```
Frequency (MHz) : 433.95
Lambda          : 69.1
Lambda 7/8 (cm) : 60.4
Lambda 5/8 (cm) : 43.2
Lambda/2 (cm)   : 34.5
Lambda/4 (cm)   : 17.3
Lambda/8 (cm)   : 8.6
```



> Tags: Antenna, Antenna Length

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/antenna?197165030916250921) - created 2025-03-12 - last edited 2025-03-15
