# Permanent Storage on SD Cards
:stopwatch: Reading time: 10 minutes.

## Overview

SD Cards (memory cards) can store large amounts of data permanently, and since SD cards can be removed, they are an excellent way of transferring data (i.e. sensor data) to a PC to do evaluations. 

### Life Span

There is no definite life span of SD Cards and last at least 10 to 30 years. 

SD cards primarily use a special type of Flash memory called *NAND*. Flash memory in general has a finite number of write cycles. Saving, deleting, and re-writing data contributes to the wear of SD cards.

Modern SD cards employ advanced wear-leveling technology for even distribution of data across all memory cells. When you store relatively small amounts of data, the overall life-span is further extended.

> [!TIP]
> Flash memory (including SD cards) is not ideal for storing sensor data in high frequency. This increases the wear and tear of the card.
>
> That said, if you use SD cards to store sensor data in a measuring device, while it is in operation it may indeed stress SD cards. Typically though such devices are used only occasionally and for limited time. Using SD cards can be a cheap and reliable way of storing the data even for devices that log data in high frequency.
>
> If you need a more *resilient* way of permanent data store (and the data is relatively small), you may want to also look into the new *FRAM* storage which does not wear out.


### Speed

Data transfer speed relies on (a) the type of SD card and (b) the capabilities of the SD card reader board. For typical data logging applications, read and write access times are no issue.

### Size

SD cards can store enourmous amounts of data. The initial SD cards stored already up to *2GB*. Modern SD cards have lifted this limit to beyond *128GB*.

These huge storage capacities are seldom needed in microcontroller projects. Always make sure the **SD Card Module** *and* the libraries you intend to use supports SD cards with the size you want. Some limit the maximum size to *4GB* or even *2GB*. Most work with all sizes.

> [!NOTE]  
> *4GB* is the maximum amount of memory addresses that can directly be addressed by *32 bit*.


### Physical Dimensions

The *classic* SD cards are the largest with dimensions of 24x32x2.1mm. The newer *microSD* format is considerably smaller: 11x15x1mm.

## SD Card Modules

**SD Card Modules** are small breakout boards with a **SD Card** slot. They can read and write data and communicate with microcontrollers using a **SPI** connection (4 GPIO pins).

Things to watch out for before buying a **SD Card Module**:

* **Voltage:** Does the module support the voltage you use? Internally, **SD Card Modules** use 3.3V technology. Breakout boards often add voltage regulators. Modules can have both *3.3V* and *5V* pins. Occasionally, modules have *just a 5V* pin and are unsuitable for *ESP8266* and other *3.3V* environments. To operate them with 3.3V, you would have to manually cut printed wires on the board to disable the internal voltage regulator. A better choice is to pick a module with the correct voltage requirements in the first place.
* **SD Card Format:** Most modules have slots for small *microSD* cards and do not support the original *SD Card* format.
* **SD Card Size:** Some modules impose restrictions on the maximum size of **SD Cards**. They can handle a maximum size of *8GB* or even *2GB* only.

### Pin Layout

Most **SD Card Modules** come with six pins:

| Pin Label | ESP8266 (adjust pins for other microcontrollers accordingly) |
| --- | --- |
| VCC | 3.3V (may be 5V tolerant, check datasheet) |
| CS |   |
| MOSI |  |
| CLK |   |
| MISO |   |
| GND | Ground pin **G** |

Some modules feature an additional *5V* pin and use a voltage regulator when this pin is used.

> [!NOTE]  
> Essentially, the pins resemble the *power supply* (**VCC** and **GND**) and *communications* via *SPI*.
>
> Different microcontrollers have different *SPI* pins. Most *SPI* pins are typically fixed and assigned to specific microcontroller pins. **CS** can be freely assigned to any suitable *GPIO* pin.
>
> If you plan to use a microcontroller other than *ESP8266*, look up the designated *SPI* pins for your model.

## Preparing SD Cards

Before use, it is recommended to *format* **SD Cards**. Formatting completely erases the **SD Card** and adds a *file system structure*. On Windows, **SD Cards** can be formatted like any other drive using *Windows Explorer*. 

The *file system* should be either **FAT** or **exFAT**. **FAT** is limited to a maximum size of *4GB*. It is the most compatible file system format. **exFAT** may not be supported by the **SD Card Reader**.







