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

These huge storage capacities are seldom needed in microcontroller projects. Always make sure the **SD Card Module** you are going to use supports SD cards with the size you want. 


### Physical Formats

The *classic* SD cards are the largest with dimensions of 24x32x2.1mm. The newer *microSD* format is considerably smaller: 11x15x1mm.


## SD Card Modules

**SD Card Modules** cost less than €2 and are connected to microcontrollers using a **SPI** connection (4 GPIO pins).




