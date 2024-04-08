<img src="/assets/images/treasureChest.png" width="100%" height="100%" />

# Mini W5500 Ethernet Controller

> Fast 80MHz SPI-Ethernet Controller For Up To 8 Sockets 

This is the *miniature version* of the standard *W5500* breakout board. It is much smaller but lacks the voltage regulator. It must be supplied with **3.3V**. Only the *SPI* data pins are **5V** tolerant.

Other than that, the breakout board is fully compatible with the normal-sized breakout board as both are based on the same fast and performant *W5500* controller chip. The chip supports up to eight sockets, comes with hardware-implemented *TCP/IP*-stack and Wake-On-LAN. Like most *Ethernet* breakout boards, it supports *IPv4* only.

This board is one of the smallest available. It is also known as **W5500 Lite**.

<img src="images/ethernet_w5500_front_hightop_t.png" width="50%" height="50%" />

## Interface

The boards use the **SPI** interface.

## Operating Voltage

The operating voltage is **3.3V**.

> [!TIP]
> To operate this breakout board with a **5V** microcontroller like *Arduino*, use dedicated **3.3V** pin for power supply. The *SPI* interface is *5V* tolerant. A level shifter is not mandatory.

<img src="images/ethernet_w5500_top_t.png" width="50%" height="50%" />


## Specs

| Item | Value |
| --- | --- |
| Voltage | 3.3V (5V tolerant) |
| Frequency | 80MHz |
| Cache Buffer | 32KB               |
| Speed | 10/100MBps |
| Current | 200mA |
| Chip Set | W5500 |
| Size | 23x29x24mm |

## Pins

The board comes with six pins on each size, 12 pins in total.

Viewed from back:

| Pin  | Left | Right |
| ---- | ---- | ----- |
| 1    | GND  | GND   |
| 2    | GND  | 3V3   |
| 3    | MOSI | 3V3   |
| 4    | SCLK | NC    |
| 5    | CS   | RST   |
| 6    | INT  | MISO  |

The *SPI* interface is implemented via *MOSI*, *MISO*, *SCLK*, and *CS* (4-wire). 

*RST* is the reset pin (low active). and *INT* is the *W5500* interrupt output pin.

## LED

The board comes with two *LED*:

* Activity (yellow): bright (carrier signal with physical connection), dim (just carrier signal)
* Link (green): lit when connected

## Data Sheets

* [W5500](materials/w5500_datasheet.pdf)


> Tags: Data, Network, Ethernet, W5500. Mini W5500, W5500 Lite
