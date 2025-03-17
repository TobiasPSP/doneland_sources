<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# SRD Frequencies

> SRD Devices can work on various license-free frequencies, inclusing 315MHz, 433MHz, 868MHz, And 915MHz


*SRDs* operate in four distinct *sub-GHz* frequency ranges: *315MHz*, *433MHz*, *868MHz*, and *915MHz*, and it depends primarily on your geographic location which frequency you may legally use:

| Region        | ISM Band  | Frequency Range       | Bandwidth  | Channels | Max Power          | Regulatory Remarks                                          | Typical ASK/EV1527 Frequency |
|--------------|----------|----------------------|------------|----------|--------------------|-------------------------------------------------------------|------------------------------|
| **US**       | 315 MHz  | 314.92 – 315.08 MHz  | 160 kHz    | 1        | ≤ 25 mW ERP        | FCC Part 15.231 (remote control, non-continuous only)       | 315.00 MHz                   |
| **Europe, Asia** | 433 MHz  | 433.05 – 434.79 MHz | 1.74 MHz   | ~20      | ≤ 10 mW (EU)       | EU: License-free ISM band, ETSI EN 300 220                  | 433.92 MHz                   |
| **US**       | 433 MHz  | 433.05 – 434.79 MHz | 1.74 MHz   | ~20      | ≤ 10 mW ERP        | FCC Part 15.231 (only for alarms, remote controls, etc.)    | 433.92 MHz (limited use)     |
| **Europe**   | 868 MHz  | 868.0 – 868.6 MHz   | 600 kHz    | ~6        | ≤ 25 mW (low duty) | EU SRD band, ETSI EN 300 220, limited duty cycle            | 868.35 MHz                   |
| **US, Australia** | 915 MHz  | 902 – 928 MHz       | 26 MHz     | ~50      | ≤ 1 W (US)         | FCC Part 15 ISM band, widely used for general data          | 915.00 MHz                   |
| **Worldwide** | 2.4 GHz  | 2.400 – 2.4835 GHz  | 83.5 MHz   | 79        | ≤ 100 mW (EU)      | Global ISM band, used for Wi-Fi, Bluetooth, Zigbee          | Not typically used for ASK   |
| **Worldwide** | 5.8 GHz  | 5.725 – 5.875 GHz   | 150 MHz    | ~25       | ≤ 1 W (US)         | Global ISM band, used for Wi-Fi, radar, industrial use      | Not typically used for ASK   |

*Sub-GHz ISM bands* (license-free bands) are strictly regulated with significant differences between geographic location. More modern ISM bands above *1 GHz* are globally regulated and free to use (within the thresholds) almost anywhere on the world.

### Crystals

Breakout boards for receiving or transmitting in the sub-GHz region are typically made **for one specific ISM band only** and cannot be changed later.

Even though the transmitter chip used on a board may support multiple ISM bands or wider frequency ranges, and even though a vendor may claim *315/433/868/915MHz supported*, this is **not true**. 

There are distinct external components such as crystal, capacitors and coils (that form *filters*), which determine the frequency the board is optimized for. The *antenna length*, too, must match the desired frequency. You cannot use the same antenna for multiple ISM bands (without significantly hitting transmission performance).

So when you purchase a SRD receiver or transmitter, you must make sure it is desiged to use the frequency you want to use (and that is **legal** to use for you in your region).

The *crystal* can be a good indicator to reveal the frequency range your devices is designed to work on. The operating frequency is typically a multiple of the crystal frequency. There can be different *factors* used by your device, so there are a number of commonly used crystal frequencies per ISM band.

The table below can help you identify the frequency range your device was made for: compare the crystal frequency on your device with this table:

| ASK/EV1527 Frequency | Region        | Crystal Frequencies & Factors |
|------------------------------|--------------|--------------------------------------|
| 315.00 MHz                   | **US**       | **13.560 MHz** × 23.25, **21.000 MHz** × 15  |
| 330.00 MHz                   | **Some regions** | **13.200 MHz** × 25                    |
| 390.00 MHz                   | **US**       | **13.000 MHz** × 30                     |
| 418.00 MHz                   | **UK (legacy use)** | **13.933 MHz** × 30                     |
| 433.92 MHz                   | **Europe, Asia** | **13.52127 MHz** x 33, **13.560 MHz** × 32, **6.7458 MHz** × 64, **21.600 MHz** × 20, **6.000 MHz × 72**, **7.000 MHz** × 62, **8.000 MHz** × 54.4, **12.000 MHz** × 36 |
| 868.35 MHz                   | **Europe**   | **13.560 MHz** × 64, **21.708 MHz** × 40    |
| 915.00 MHz                   | **US, Australia** | **13.107 MHz** × 69.8, **26.214 MHz** × 35 |

> [!IMPORTANT]
> It's not uncommon for the bandwidth to span over a small range of frequencies around the nominal frequency, i.e. *433.92 MHz* (typically within *±100 kHz*), especially with basic OOK modulation and lower-cost receivers.On 433MHz, the signal may be anywhere in the range of *433.8-434.0MHz*.

> Tags: Frequency, Bands, ISM, license-free

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/frequency?727103030916250921) - created 2025-03-10 - last edited 2025-03-15
