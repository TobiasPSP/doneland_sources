<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# RXB14

> Super-Tiny ASK (Digital AM) Superheterodyne Receiver With Good Sensitivity 

The *RXB14* is an exceptionally small *ASK* receiver with still good sensitivity. 

<img src="images/rx_rxb14_side_t.png" width="60%" height="60%" />




## Pins

The breakout board exposes three pins which are labeled on the front side:

<img src="images/rx_rxb14_top_t.png" width="60%" height="60%" />


| Pin | Label | Description |
| --- | --- | --- |
| 1 | GND | Ground |
| 2 | D0 | Data Out |
| 3 | +5V | 4.5-5.75V |


> [!CAUTION]
> Make sure the power supply is properly filtered and carries no exceptional noise which could interfere and distort reception.


## Antenna

There is no antenna mounted. Make sure to add an antenna or else the board will have poor reception.

For example, solder a wire to the *ANT* pin (17cm for 433MHz).

## Technical Data

The receiver chip is covered under a metal shield plate.

| Item | Description |
| --- | --- |
| Voltage | 4.5V-5.75V |
| Current fully operational | 6mA @ 433MHz, 4.8mA @ 315MHz |
| Frequency | 315MHz or 433.92MHz |
| RX Sensitivity | -110dBm |
| Modulation | ASK (AM) |
| Data rate | 2.4kbps |
| Size  | 30x8.5x4mm |


<img src="images/rx_rxb14_back_t.png" width="60%" height="60%" />

> [!CAUTION]
> Note the difference in supported input voltage: the *315MHz* version acvcepts *3.3-5.75V*. The *433MHz* version requires at least *4.5V* and *will not work* with *3.3V*.

## Data Sheet

[RXB14 ASK Receiver](materials/rxb14_datasheet.pdf)

> Tags: Receiver,ASK,OOK,AM

[Visit Page on Website](https://done.land/components/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/rxb14?498959041722244512) - created 2024-04-21 - last edited 2024-04-21
