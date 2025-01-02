<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# AS07-M1101S

> 10mW FSK Transceiver With Wide Frequency Support, SPI Interface And High Sensitivity Based On CC1101

This is a transceiver module based on the *CC1101* transceiver chip from *Texas Instruments* that can be programmed via *SPI* interface and sends/receives in the 387-464MHz range. It comes with an *SMA* terminal to attach an external antenna. The theoretical distance this device can cap is estimated at *600m-1000m* due to its increased receiver sensitivity.



<img src="images/radio_as07-m1101s_side1_t.png" width="80%" height="80%" />


> [!TIP]
> This breakout board exists in a number of variations. Sometimes it is referred to as *HW-863*.

It uses *FSK* modulation which is based on *frequency modulation* (*FM*). It is incompatible with simple remote controls which use *ASK* (*AM*).

The *AS07-M1101S* is a good choice when you want to design your own high speed two-way data transfer system, i.e. to send sensor data or text messages.




## Frequency Range And Channels
The board can *send and receive* in a frequency range of *387-464MHz*.

Its maximum transmitting power is +10dBm/10mW, and the receiver sensitivity is excellent with *-116dBm*. In free *line of sight*, distances of up to *1km* can be bridged.

<img src="images/radio_as07-m1101s_top2_t.png" width="80%" height="80%" />

## Specs


| Item | Value |
| --- | --- |
| Voltage | 1.8-3.6V |
| Frequency | 387-464MHz |
| Output Power | 10dBm / 10mW |
| Modulation | 2-FSK, GFSK, MSK |
| Standby Current |  |
| Sleep Current |  |
| Operating Current | 30mA, power supply >100mA |
| Transmission Rate | 1.2-500kbps |
| Receiver Sensitivity | -116dBm @ 0.6kps |
| Extras | RSSI signal detection, hardware CRC, carrier sense, 64-byte RX and TX buffer |
| Interface | SPI |
| Size | 20.65x12.1x7mm |

## Connectors

The board comes with eight solder pads. They are clearly marked on the backside:

<img src="images/radio_as07-m1101s_back3_t.png" width="100%" height="100%" />

| Pin | Tag | Description |
| --- | --- | --- |
| 1 | GND | negative voltage |
| 2 | GOD2 | I/O |
| 3 | GDO1 | MISO, SPI |
| 4 | MOSI | SPI |
| 5 | SCK | SPI |
| 6 | CSN | SPI |
| 7 | GOD0 | I/O |
| 8 | VCC | +1.8V to +3.6V |



### Antenna

The board comes with solder pads both for a pre-soldered *bullet pole* coil antenna and an *IPEX* connector.





### Interface

This board uses the *SPI* interface to communicate with a microcontroller.

<img src="images/radio_as07-m1101s_back1_t.png" width="100%" height="100%" />


<img src="images/radio_as07-m1101s_top_t.png" width="100%" height="100%" />




### Data Sheet

[CC1101 from Texas Instruments](materials/cc1101_datasheet.pdf)


> Tags: CC1101, AS07-M1101S, HW-863, Sender, Receiver, Transceiver, RF, 433MHz, 3.3V, IPEX

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/fm/fsk/transceiver/as07-m1101s?593316041116244739) - created 2024-04-15 - last edited 2024-04-15
