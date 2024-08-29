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

## Antenna Lengths

Antennas are very important for safe and efficient usage. 

> [!CAUTION]
> **Never** operate a *sender* without a proper antenna or else you might damage it. Operating a *receiver* without antenna is technically benign but severely impacts receiver sensitivity.

If you don't have an antenna at hand, you can easily build one yourself: a simple copper wire is sufficient.

What matters is its length that must match the frequency you want to use.

### Calculating Antenna Length

The proper antenna length is calculated by the formula **299792458 / *frequency (in Hertz)***. The former is the *speed of light*.

For a typical *garage door opener* operating on *433.95MHz*, the formula would be *299792458 / 433950000*. The result is *0.6908456227676*: the full wave length for this frequency is *69cm*.

Typical antennas use a quarter of the full wavelength (*lambda/4* or *1/4*). The proper antenna length for *433.95MHz* devices would therefore be *17.3cm*.

### Get-AntennaLength Command

To calculate antenna lengths more easily, you can use *PowerShell*. It is preinstalled on any *Windows PC* and can be downloaded for most other operating systems for free.

First, install the *DoneLandTools* extension:

```powershell
Install-Module -Name DoneLandTools -Scope CurrentUser -Force -AllowClobber
```

> [!TIP]
> You may omit `-Force -AllowClobber` if you prefer to see confirmation dialogs.

Next, it's simple to calculate antenna lengths:

```powershell
Get-AntennaLength 433.95
```

The result lists various resonant antenna lengths, and you can pick the length that works best for you.

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


## Modulations

The modulation and the data format control how information is sent and received over the air. There are two fundamental signal transmission concepts:

* **AM (Amplitude Modulation):** the information is added to the radio wave amplitude. The frequency stays fixed.
* **FM (Frequency Modulation):** the information is modulated onto the carrier frequency. The amplitude stays fixed. The frequency varies (within the defined *bandwidth*).

> [!NOTE]
> There is also *phase-modulation* which is a third way of modulating information onto a radio wave. Digital communications uses *PSK* (*Phase-shift keying*) and combinations with other encodings.



To actually transmit data using one of these ways, additional *information encoding* is required. 

*Encoding schemes* start with simple *On-Off schemes* similar to *morse code*, and can become extremely sophisticated with *chirp symbols* and *signal spreading*. More sophisticated encoding schemes generally are able to transmit *more information* with *higher speed* and/or *extend the distance* that radio waves can travel.

## AM (Amplitude Modulation)

For *digital transmissions* on *AM*, *ASK* (*Amplitude-Shift keying*) is used: in its simplest form (*OOK*, *On-Off keying*), bit *1* is represented by full amplitude, and bit *0* is represented by absence of signal.
 
### EV1527 - Remote Controls

One coding format used on *ASK* is *EV1527*, a 24bit code with roughly a million different *ID* codes and four bits of payload. *EV1527* is often used with simple remote controls, especially those with *learning codes*.

### WiFi

*WiFi* also uses *AM*. To encode the information and achieve high transmission speeds, much more sophisticated encodings are used (i.e. *QAM*, *Quadrature Amplitude Modulation*).

> [!NOTE]
> *QAD* is a combination of *PSK* (*Phase-shift keying*) and *ASK* (*Amplitude-shift keying*). Using both *phase* and *amplitude* shifts can encode *more information* and is one of the reasons why modern *WiFi* standards were able to increase the maximum data transmission speed.

| Standard | Year | Speed | Encoding |
| --- | --- | --- | --- |
| 802.11 | 1997 | 1MBit | DBPSK (Differential-binary Phase-shift keying) | 
| 802.11 | 1997 | 2MBit | DQPSK (Differential-quadrature Phase-shift keying) | 
| 802.11b | 1999 | 5.5/11MBit | CCK (Complementary-code keying) | 





## FM (Frequency Modulation)

For *digital transmissions* on *FM*, *FSK* (*Frequency-Shift keying*) is used: *bits* (or *symbols*) are encoded in shifts of frequency.

There are plenty of *FSK* transceiver breakout boards available. 

### LoRa - Chirp Spread Spectrum

*LoRa* (*Long Range*) is also using *FM*. It specializes in transmitting signals over great distances with very low-powered radio signals (10mW *LoRa* radio signals can travel 2km within cities and up to 40km in rural areas). To achieve this, it is using the proprietary, patented *LoRa* (*LongRange*) wireless protocol based on the *Chirp-Spread-Spectrum* modulation technique.

## Spread Spectrum

Aside from modulation (like *AM* and *FM*), another technology is used in modern digital data transmissions: *spread spectrum*.

With *spread spectrum*, the original *focused* radio signal with its small *bandwidth* is deliberately *spread out* over a much larger frequency spectrum.

Spreading out radio signals yields a number of benefits:

* **Distance:** strong interference and noise signals on one particular frequency cannot distort the signal as only a very small fraction of it is affected.
* **Security:** the spread-out signal is almost impossible to detect and intercept without knowing the parameters in which it was spread out
* **Field Strength:** the field strength for a particular frequency is lower

A number of modern transmission techniques use one form of *spread spectrum* or another, including *LoRa* and *WiFi* (*DSSS*, *Direct Sequence Spread Spectrum*).



> Tags: AM, FM, ASK, FSK, PSK, LoRa, WiFi, EV1527, DSSS, Spread Spectrum, Chirp, PSK, DBPSK, CCK, DQPSK

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice?512393041001243228) - created 2024-04-01 - last edited 2024-04-01
