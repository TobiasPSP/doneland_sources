<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Short Range Device

> Devices With Low Radio Output Power, Working On 315MHz, 433MHz, 868MHz, And 915MHz

*Short Range Devices* (*SRD*, formerly known as *Low Powered Devices*, *LPD*) transmit radio frequencies with very low output power. 

Examples for *SRD* are wireless sensors, microphones, garage door opener, home automation, etc.

## Designated Frequencies

*SRD* operate on distinct frequencies:

| Frequency | Region | max. Output Power |
| --- | --- | --- |
| 315MHz | US | 1W |
| 433MHz | Europe/Asia | 10mW |
| 868MHz | Europe/Asia | 25mW/1% duty cycle |
| 915MHz | US | 1W/400ms *dwell time* |

## Modulations

The modulation and the data format control how information is sent and received over the air.

### ASK - Amplitude-Shift-Keying

Simple *SDRs* use *ASK* (*Amplitude-Shift-Keying*) modulation. 

#### EV1527

One coding format used on *ASK* is *EV1527*, a 20bit code with roughly a million different codes. *EV1527* is often used with simple remote controls, especially those with *learning codes*.

### LoRa - Chirp Spread Spectrum

In recent times, *LoRa* has also become a popular modulation and encoding scheme. It is using the proprietary, patented *LoRa* (*LongRange*) wireless protocol based on the *Chirp-Spread-Spectrum* modulation technique.

*LoRa* is able to bridge distances of many kilometers (2km within cities and up to 40km in rural areas) despite the low radio emission allowed for *SDR* devices.


## Senders

[Senders](Senders) actively transmit a *RF* signal on a given frequency. 

Senders are available as ready-to-use *remote controls*  (typically using *EV1527* and emitting one or more fixed codes), or as freely programmable *breakout boards*:


<img src="images/433_tx_overview_t.png" width="40%" height="40%" />

Breakout boards are available as *generic senders* that can send anything using *ASK* modulation (including but not limited to *EV1527* codes), and as designated *EV1527* senders (that can *only* send *EV1527* codes and nothing else).

Most senders come with a *fixed frequency range* and cannot be changed to a different frequency band later.

> [!CAUTION]
> Make sure you purchase the remote control or breakout board for the frequency that is legal to use in your region. *315MHz* senders are *illegal to use* in *Europe*, for example. Likewise, *433MHz* senders are *illegal to use* in the *US*.




## Receivers

As with the *senders*, on the *receiver* side you can choose to pick *ready-to-use receivers* (i.e. built-in *relais* to control external loads) or programmable *receiver breakout board*:

<img src="images/433_rx_overview_t.png" width="40%" height="40%" />


As with the senders, there are receivers that are designed to work with *EV1527* codes and cannot receive anything else, and generic receivers that just receive the raw digital *ASK* information. 

The latter can receive anything at the expense of requiring additional programming to deal with *EV1527* codes.

## Transceivers

Some devices and breakout boards are *transceivers*: they can send *and* receive.

*Clone remote controls* for example can *receive* the *EV1527* code sent out by another remote control, store it, and play it back by *sending* it out later.

Transceiver *breakout boards* can be used to establish a two-way-communication, i.e. to set up a wireless data communication that can confirm and provide feedback to the sender of a wireless command.


> Tags: Frequency, RF,  315MHz, 433MHz, 868MHz, 915MHz, ASK, LoRa, Sender, Receiver, Transceiver, EV1527, Wireless, Remote Control

[Visit Page on Website](https://done.land/components/datatransmission/wireless/radio/433mhz?512393041001243228) - created 2024-04-01 - last edited 2024-04-01
