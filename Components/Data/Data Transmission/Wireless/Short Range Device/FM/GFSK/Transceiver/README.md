<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# GFSK-Transceivers

> High-Speed Digital Data Transmission 

*Transceivers* can both *send* and *receive*. 

*GFSK-Transceivers* are *FM* (*Frequency Modulation*) transceivers for *digital communication*: they use *GFSK* (*Gaussian Frequency-Shift keying*) to encode bits or symbols.

> [!NOTE]
> *GFSK* is a *FSK* enhancement so any *GFSK* transceiver can also use *FSK*. While *FSK* transceivers are not fully compatible with *ASK* (as they cannot change the *amplitude*), they are still compatible with the simple *OOK* modulation since this only requires sending at *full amplitude* and *not sending*. *GFSK* transceivers are therefore compatible with most usage scenarios including communicating with simple *OOK remote controls*.






## Overview

*GFSK* is an evolved *FSK* modulation designed to efficiently transmit data at high data rates and without causing much interference.

*GFSK* is used commericially for example in *Bluetooth* and *DECT* wireless phones.

## Use Cases

*GFSK transceiver breakout boards* can use the same fundamental technology for high-speed custom-protocol data transmission.

Essentially, they provide the core transmission protocol without any other and more specific data protocols (such as *Bluetooth* or *DECT*).

This way, you can use your own libraries and/or create light-weight custom protocols to transfer large amounts of data reliably. 

*GFSK* (and the powerful breakout boards supporting it) are perfectly suited to transmit data-intensive payloads (such as video) over distances of 300-1000m without the need of any supporting infrastructure.

## When Not To Use

If you need to transmit only small amounts of data (i.e. temperature sensor data or remote control commands), you should rather fall back to simple and inexpensive *FSK* or *ASK* transceivers.


> Tags: FM, GFSK, Transceiver, Radio

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/fm/gfsk/transceiver?421331041718243057) - created 2024-04-17 - last edited 2024-04-17
