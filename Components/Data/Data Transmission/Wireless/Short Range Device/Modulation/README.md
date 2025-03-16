<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Radio Modulations

> SRD devices (like any radio) uses different *modulations* to transport information over radio waves.



In its most basic form, radio does not need a modulation: **OOK** (on-off-keying) works like ancient *morse transmitters* and turns a radio emitter either **on** or **off**. 

*OOK* cannot transport much information at high speeds which is why *modulations* where added that can be imposed on a *continuous transmission*. So rather than turning the transmitter completely *on* and *off* all the time, modern radios slightly **vary the output power** (affecting the *amplitude*, AM) or **vary the frequency** (within a predefined *bandwidth*, FM).



> [!NOTE]
> There are many more sophisticated modulations, including *phase-modulation* which is a third way of modulating information onto a radio wave. Digital communications uses *PSK* (*Phase-shift keying*) and combinations with other encodings.

## Overview

Transmitting large amounts of information over radio waves requires using the same *modulation* at both sender and receiver, and also to *encode* and *decode* the information so that it can be imposed onto the modulation.

In the context of this website, I am looking at *digital* data transmissions only. Transmitting *analog* data via AM or FM is much simpler: the audio NF itself is modulating either the amplitude or frequency of the radio wave.

With digital information, consisting of binary *on* and *off* information only, various modulations and encodings are used:

| **Modulation Type** | **Typical Use in ISM Bands** | **Modulation Characteristics**        | **Use Cases**                                  | **When to Use**                                | **Digital DIY Examples**                |
|---------------------|-----------------------------|---------------------------------------|------------------------------------------------|------------------------------------------------|-----------------------------------------|
| **AM (Amplitude Modulation)** | 433 MHz, 315 MHz, 868 MHz (Low power) | The amplitude of the carrier is varied by the signal | AM Radio, OOK (On-Off Keying), Simple Analog Communication | When simplicity and low power are required, or when long-range communication is not critical | **OOK** (e.g., simple on/off signals), **AM Radio** (low-fi communication), **Home automation** (simple, long-range, low-data-rate links) |
| **FM (Frequency Modulation)** | 433 MHz, 868 MHz, 2.4 GHz, 5.8 GHz | The frequency of the carrier is varied by the signal | FM Radio, Wi-Fi, LoRa, Bluetooth | When higher noise immunity, better signal quality, and higher data rates are needed | **Wi-Fi** (using OFDM modulation), **LoRa** (for long-range, low-power, wide-area networks), **Bluetooth** |
| **OOK (On-Off Keying)** | 433 MHz, 315 MHz, 868 MHz | A form of **AM modulation** where the presence or absence of a signal represents data | Simple remote controls, basic sensor networks | When very low power is needed and simple binary data transmission is sufficient | **Simple RF modules** like nRF24L01, **RFID tags**, **keyfob remotes** |
| **ASK (Amplitude Shift Keying)** | 433 MHz, 315 MHz | A form of AM where the amplitude of the carrier is modulated to represent data | Basic digital communication over short distances | When minimal complexity and low data rates are sufficient | **RF modules** (e.g., 433 MHz ASK modules for simple communication) |
| **LoRa (Long Range)** | 433 MHz, 868 MHz, 915 MHz | **FM** with spread-spectrum modulation, using Chirp Spread Spectrum (CSS) | Long-range, low-power IoT communication networks | When long-range, low-data-rate, and low-power communication is needed in areas with potential interference | **LoRaWAN** (for IoT networks, agriculture, and smart cities) |
| **Wi-Fi (OFDM)** | 2.4 GHz, 5 GHz | **AM** (using Orthogonal Frequency Division Multiplexing) with Frequency Modulation | High-speed data transmission in local area networks | When high bandwidth, reliable communication, and moderate range are needed | **Wi-Fi routers**, **IoT devices**, **Smart home systems** |
| **Bluetooth** | 2.4 GHz | **FM** with **FHSS (Frequency-Hopping Spread Spectrum)** | Short-range wireless communication for devices | When low-power, short-range communication is needed with robust interference resistance | **Bluetooth Low Energy (BLE)** devices, **Wireless peripherals** (e.g., keyboards, headphones) |
| **Zigbee** | 2.4 GHz | **FM** (with DSSS) | Low-power, low-data-rate networks for home automation, smart devices | When very low power consumption is critical and short-range, reliable communication is needed | **Smart home** devices, **Home automation networks** |



## AM (Amplitude Modulation)

For *digital transmissions* on *AM*, *ASK* (*Amplitude-Shift keying*) is used: in its simplest form (*OOK*, *On-Off keying*), bit *1* is represented by full amplitude, and bit *0* is represented by absence of signal.

AM is typically used for low-power and long-range communication but has lower noise immunity and limited data rate capabilities.

Here are popular use cases that utilize **AM**:
 
### EV1527 - Remote Controls

One coding format used on *ASK* is *EV1527*, a 24bit code with roughly a million different *ID* codes and four bits of payload. *EV1527* is often used with simple remote controls, especially those with *learning codes*.

### WiFi

*WiFi* also uses *AM* although in reality, it is a mixture that contains both AM and FM components. To encode information and achieve high transmission speeds, much more sophisticated encodings are used (i.e. *QAM*, *Quadrature Amplitude Modulation*).

> [!NOTE]
> *QAD* is a combination of *PSK* (*Phase-shift keying*) and *ASK* (*Amplitude-shift keying*). Using both *phase* and *amplitude* shifts can encode *more information* and is one of the reasons why modern *WiFi* standards were able to increase the maximum data transmission speed.

| Standard | Year | Speed | Encoding |
| --- | --- | --- | --- |
| 802.11 | 1997 | 1MBit | DBPSK (Differential-binary Phase-shift keying) | 
| 802.11 | 1997 | 2MBit | DQPSK (Differential-quadrature Phase-shift keying) | 
| 802.11b | 1999 | 5.5/11MBit | CCK (Complementary-code keying) | 





## FM (Frequency Modulation)
FM is used in applications that require better noise immunity and higher data rates, such as Wi-Fi, LoRa, and Bluetooth. It is basically used in most modern radio applications.

FM works by varying the frequency of the carrier signal, making it resistant to noise and suitable for longer-range communications with better signal quality.

For *digital transmissions* on *FM*, *FSK* (*Frequency-Shift keying*) or one of its successors is often used: *bits* (or *symbols*) are encoded in shifts of frequency. 



## Spread Spectrum

Aside from modulation (like *AM* and *FM*), another technology is used in modern digital data transmissions: *spread spectrum*.


### FHSS
FHSS (Frequency Hopping Spread Spectrum) is a method of transmitting radio signals by rapidly switching the carrier frequency among many different frequency channels, in a pseudo-random sequence. The frequency hops are done in a way that both the transmitter and receiver are synchronized to hop to the same frequencies at the same time.

*FHSS* is part of many modern wireless technologies:

* Bluetooth: Uses FHSS to reduce interference from other devices in the 2.4 GHz ISM band, making it more reliable in crowded environments.
* Zigbee: Also uses FHSS for robust, short-range, low-power wireless communication.
* Military and Secure Communications: Because of its security features, FHSS is often used in military applications to avoid detection or interception.


FHSS improves the reliability of wireless communication, especially in environments with a lot of interference, by constantly changing the frequency the signal uses.

> [!NOTE]
> *WiFi* is not using *FHSS*. It uses OFDM (Orthogonal Frequency Division Multiplexing), which is not based on frequency hopping. **OFDM** divides the available bandwidth into several subcarriers that are orthogonal to each other. These subcarriers are used to transmit data simultaneously, increasing the data rate and efficiency of the communication. 


Rapidly changing frequencies has a number of advantages:

* **Distance:** strong interference and noise signals on one particular frequency cannot distort the signal as only a very small fraction of it is affected.
* **Security:** the spread-out signal is almost impossible to detect and intercept without knowing the parameters in which it was spread out
* **Field Strength:** the field strength for a particular frequency is lower



### LoRa - Chirp Spread Spectrum

*LoRa* (*Long Range*) is a modern modulation that builds on *FHSS* but adds *chirp*. It is a proprietary modulation intended for long range transmissions at very low radio power (10mW *LoRa* radio signals can travel 2km within cities and up to 40km in rural areas). 

To achieve this, it is using the proprietary, patented *LoRa* (*LongRange*) wireless protocol based on the *Chirp-Spread-Spectrum* modulation technique.



> Tags: AM, FM, ASK, FSK, PSK, LoRa, WiFi, EV1527, DSSS, Spread Spectrum, Chirp, PSK, DBPSK, CCK, DQPSK

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/modulation?751038030916250921) - created 2025-03-15 - last edited 2025-03-15
