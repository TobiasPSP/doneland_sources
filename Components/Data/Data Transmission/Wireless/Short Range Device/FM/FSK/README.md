<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />


 
# Frequency Shift Keying (FSK)

> Simple FM Modulation For Digital Transmissions

In order to transport *digital information* over the air, there needs to be a physical representation for the states *1* and *0* that can be imposed on a radio frequency.

*Frequency Shift Keying* (*FSK*) is a digital modulation technique that uses a carrier frequency and represents *symbols* (i.e. bits *0* and *1*) as *frequency shift*.

For *digital transmissions*, *FSK* (*Frequency-shift keying*) is typically used: a set of frequency deviations are used to define *symbols*. In its most basic form, just two frequency deviations exist, representing the bits *1* and *0*.

> [!NOTE]
> While *FSK* transceivers are not fully compatible with *ASK* (as they cannot change the *amplitude*), they are still compatible with the simple *OOK* modulation since this only requires sending at *full amplitude* and *not sending*. *GFSK* transceivers are therefore compatible with most usage scenarios including communicating with simple *OOK remote controls*.





## Related Modulations

Other more sophisticated encoding schemes exist. 

*LoRa*, for example, is a digital *long range* transmission protocol based on *FM* that can travel long distances while using very low radio emissions. It is based on  *Chirp-Spread-Spectrum* (*CSS*):

* **Chirp:** A *chirp* is a radio signal with a dynamically increasing or decreasing frequency, adding additional information content. 
* **Spread Spectrum:** The narrow bandwith of the carrier signal is spread out to a much wider frequency spectrum. This makes it more resilient towards noise signals and almost impossible to tap and listening in by unwanted third party. This modulation method is also used in *WiFi*, *Bluetooth*, and *ZigBee*.



> Tags: FM, FSK, CSS, Chirp, Frequency-Shift Keying

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/fm/fsk?341492041116242752) - created 2024-04-15 - last edited 2024-04-15
