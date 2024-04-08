<img src="/assets/images/treasureChest.png" width="100%" height="100%" />

# W5500 Ethernet Controller

> Fast 80MHz SPI-Ethernet Controller For Up To 8 Sockets 

There are a number of *Ethernet* controllers available that are based on the fast and performant *W5500* controller chip. The chip supports up to eight sockets, comes with hardware-implemented *TCP/IP*-stack and Wake-On-LAN. Like most *Ethernet* breakout boards, it supports *IPv4* only.

This board is the default-sized version. Functionality-wise, it is fully compatible with the **Mini W5500**. Power-wise, this board comes with a dedicated voltage regulator so it can be used with either **3.3V** or **5V**. The **Mini W5500** is lacking this voltage regulator and *requires* a **3.3V** power supply.

> [!CAUTION]
>
> The **W5500** boards require a power supply capable of at least *200mA*. 

<img src="images/ethernet_w5500_front_hightop_t.png" width="50%" height="50%" />

## Interface

The boards use the **SPI** interface.

## Operating Voltage

The board comes with a dedicated **3.3V** and **5V** pin and an internal voltage regulator.

> [!TIP]
> This board can be supplied with either **3.3V** or **5V** (use the appropriate pin). Internally, the board uses **3.3V**. The *SPI* data pins are *5V* tolerant.

<img src="images/ethernet_w5500_top_t.png" width="50%" height="50%" />


## Specs

| Item | Value |
| --- | --- |
| Voltage | 3.3V or 5V |
| Frequency | 80MHz |
| Cache Buffer | 32KB               |
| Speed | 10/100MBps |
| Current | 200mA |
| Chip Set | W5500 |
| Size | 55x29x24mm |

## Pins

The board comes with 5x2 connectors that are labeled on the back side:

| Pin  | Left           | Right |
| ---- | --------------------- | --- |
| 1,2 | SCLK | GND |
| 3,4 | CS | INT |
| 5,6 | MOSI | RST |
| 7,8 | MISO | GND |
| 9,10 | 3.3V | 5V |

*RST* is the reset pin (low active).

## Data Sheets

* [W5500](materials/w5500_datasheet.pdf)


> Tags: Data, Network, Ethernet, W5500, 3.3V, 5V, SPI
