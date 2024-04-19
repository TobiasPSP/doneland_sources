<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# RFM69

> 20/100mW GFSK Transceiver With Scrambler, AES-Encryption And SPI Interface Based On Semtech SX1231

This transceiver module is based on the *RF69* transceiver chip that can be programmed via *SPI* interface. This chip in turn is based on *Semtech SX1231* (20mW standard version) and *Semtech SX1231H* (100mW *H* version).

> [!TIP]
> On the *RF69* transceiver chip, look at the 4-digit number below *RF69* to find out the production date. The first two numbers are the year, the second two numbers represent the week of year.



The board is available in four frequency versions: *315MHz*, *433MHz*, *868MHz*, and *915MHz*.



<img src="images/fsk_rxtx_rfm69_angle_t.png" width="60%" height="60%" />

## Board Variations

This board is available in four variants:

| Model  | TX Power  | Pins | Size | Remarks |
| --- | --- | --- | --- | --- |
| RFM69(W) | 13dBm/20mW | 16 | 19.7x16mm | end of life |
| RFM69C(W) | 13dBm/20mW | 14 | 16x16mm | active, pin-compatible to older model *RFM12B* |
| RFM69H(W) | 20dBm/100mW | 16 | 19.7x16mm | end of life |
| RFM69HC(W) |20dBm/100mW | 14 |  pin-compatible to older model *RFM12B* |

The actual version is printed on the back side:


<img src="images/fsk_rxtx_rfm69_back_t.png" width="80%" height="80%" />



## Technical Data

| Item | Value |
| --- | --- |
| Voltage | 1.8-3.6V |
| Frequency | 387-464MHz |
| Output Power | 10dBm / 10mW |
| Modulation | FSK, GFSK, MSK, GMSK and OOK |
| Standby Current | 0.1uA |
| TX Operating Current | 45mA at 13dBa/20mW |
| RX Operating Current | 16mA
| Transmission Rate | up to 300kbps (FSK) |
| Receiver Sensitivity | -115dBm  |
| Extras | RSSI signal detection, hardware CRC, carrier sense, 64-byte RX and TX buffer |
| Interface | SPI |




## Special Features

The transceiver chip comes with a number of useful functionalities built into its hardware:

* *Manchester Encoder/Decoder* 
* Packetengine for *synchronous word*, *CRC*, *Scrambling*, *AES-128 encryption*
* 66bit FIFO buffer
* built-in temperature sensor

## Pins

All pins are labeled on the back side:

<img src="images/fsk_rxtx_rfm69_top_t.png" width="80%" height="80%" />

<img src="images/fsk_rxtx_rfm69_back_t.png" width="80%" height="80%" />

| Pin | Description |
| --- | --- |
| GND | negative voltage |
| ANA | Antenna |
| GND | negative voltage |
| SCK | SPI-Interface, Clock |
| MISO | SPI-Interface, Data Out |
| MOSI | SPI-Interface, Data In |
| NSS | SPI-Interface, Chip Select|
| NC | not connected |
| 3.3V | 1.8-3.6V |
| DIO5 | ModeReady ClkOut, Data |
| DIO4 | |
| DIO3 | Fifo Full, PLL Lock, RSSI, SyncAddress, TXReady |
| DIO2 | FifoNotEmpty, Automode, Data|
| DIO1 | FifoLevel, FifoFull, FifoNotEmpty, PLL Lock, Timeout|
| DIO0 | PLL Lock, CrcOk, Payload Ready, SyncAddress, RSSI, PacketSent, TxReady|
| RESET | Reset |




### Interface

This board uses the *SPI* interface to communicate with a microcontroller.

## Software Libraries

[RFM69](https://github.com/LowPowerLab/RFM69)   
[jeelib](https://github.com/LowPowerLab/RFM69)

### Data Sheet

[RF69 Transceiver Chip](materials/rf69_datasheet.pdf)   
[Semtech SX1231](materials/sx1231_datasheet.pdf)


> Tags: Sender, Receiver, Transceiver, RF, AM, FM, FSK, OOB, AES, Encryption, Scrambling, Manchester Encoding

[Visit Page on Website](https://done.land/components/datatransmission/wireless/shortrangedevice/fm/gfsk/transceiver/rfm69?329536041219242052) - created 2024-04-18 - last edited 2024-04-18
