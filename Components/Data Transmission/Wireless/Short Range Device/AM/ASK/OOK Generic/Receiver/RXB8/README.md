<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# RXB8

> Superheterodyne ASK (Digital AM) Receiver With Design Issues But Good Reception 

The *RXB8* breakout board is based on the *SYN4126*/*HB4126* single-chip solution. 

<img src="images/rx_ask_rxb8_side2_t.png" width="60%" height="60%" />

## Design Weaknesses

*SYN4126* seems to be out of production for a long time: no data sheets or other information about seems to be available. What seems evident though is that this chip was originally designed to transmit in *FM* modulation. 

In this board, the *RSSI* output is used instead to decode *ASK* (*AM*) signals. One could speculate that the vendor got its hands on a large batch of these *FM* receiver chips and came up with a creative solution to use them in *AM ASK* receivers. This approach has one important backdraw: it limits the minimum detectable impulse widths (and thus the data rate that can be received): impulses of 350us duration and less become accidentally widened by the way how RSSI signals are processed, and communication fails at these speeds.


For simple *remote control* scenarios where only small amounts of data need to be transmitted and low speeds are used, this receiver is very well suited: its very good sensitivity can pick up a signal even through walls or at greater distances where other and more simplistic receivers would not be able to. 

In use cases where large amounts of data need to be received quickly, this receiver chip fails, and you should switch to a receiver using a dedicated *ASK* receiver chip.


<img src="images/rx_ask_rxb8_side_t.png" width="60%" height="60%" />



## Pins

The board exposes five pins, two on the left side and three on the right side. Pins are labeled on the front side of the board:

<img src="images/rx_ask_rxb8_top_t.png" width="60%" height="60%" />


| Pin | Label | Description |
| --- | --- | --- |
| 1 | ANT | Antenna |
| 2 | GND | Ground |
| 3 | GND | Ground |
| 4 | DATA | Data Out |
| 5 | +5V |  4.5-5.5V |


> [!CAUTION]
> Make sure the power supply is properly filtered and carries no exceptional noise which could interfere and distort reception.




> [!NOTE]
> The pins on this module do not fit the common 2.54mm pin grid. This makes it difficult to plug the board into bread boards for testing.



## Antenna


There is no antenna mounted. Make sure to add an antenna or else the board will have poor reception.

For example, solder a wire to the *ANT* pin (17cm for 433MHz).

## Technical Data



| Item | Description |
| --- | --- |
| Voltage | 4.5V-5.5V |
| Current fully operational | 12mA |
| Frequency | 300-440MHz, breakout boards are set to one specific frequency via a crystal |
| RX Sensitivity | -111dBm |
| Modulation | ASK (AM) |
| Chip | SYN4126 |
| Data rate | 10kbps |
| Size  | 31.5x14x7mm |


<img src="images/rx_ask_rxb8_back_t.png" width="60%" height="60%" />


> Tags: Receiver,ASK,OOK,AM, SYN4126

[Visit Page on Website](https://done.land/components/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/rxb8?266135041520244851) - created 2024-04-19 - last edited 2024-04-19
