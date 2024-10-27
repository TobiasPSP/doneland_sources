<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# HC-12

> A Very Powerful 433-473MHz Sender And Receiver With Its Own Microprocessor

The *HC-12* can send *and* receive in the frequency range *433.4-473.0 MHz* with an exceptionally *high maximum transmission of **100mW** (20dB)*. It supports *multiple channels* and different *modes* to optimize for different use cases, i.e. *low power consumption*, *transmission speed*, or *maximum range*. The module is based on the [Silicon Labs SI4463](materials/si44xx_datasheet.pdf) and supports both simple *OSK* and all flavors of *FSK modulation*.



<img src="images/433_Extension_HC-12_angle_t.png" width="40%" height="40%" />



> [!NOTE]
> This module *can* control *garage doors* and remote-control devices via simple *OOK*, however such simple tasks can be delegated to much simpler modules. *HC-12* is **much more capable** and serves as a fully programmable data transceiver with relatively **high RF power** - in fact, its strongest transmission modes **exceed the legal limits** in most countries, and you would have to be a **licensed radio amateur (HAM)** to operate this module at its maximum settings..

## Overview
This board uses its own microprocessor that takes care of all *receiving* and *sending* tasks. Controlling the board is very easy and does not add any overhead to your own microprocessor.

### Frequency Range And Channels
The board can *send and receive* in a frequency range of *433.4-473.0MHz* which is organized in *channels* with a step size of *400kHz*. 

Its maximum transmitting power is +20dBm/100mW, and the receiver sensitivity is excellent with *-116dBm*. In free *line of sight*, and with a decent antenna, transmission distances of over *1km* and much more should be no problem.

> [!CAUTION]
> Both its **wide frequency range** and its **high RF transmission power** are **not covered by license-free bands** and  **illegal to use** in *Europe* unless you are appropriately **licensed** (i.e. radio amateur).   



### Specs

This breakout board by default emits *100mW* which is well above the legal limit of *10mW* in *Europe*. The RF power can be reduced by software.

| Item | Value |
| --- | --- |
| Voltage | 3.2-5.5V |
| Frequency | 433.4-473.0 MHz |
| Antenna  | external Antenna (SMA) or spring antenna via solder connection |
| Output Power | 20dBm max (100mW max) |
| Sending Modes | FU1, FU2, FU3, FU4 |
| Default Mode | FU3: 9600bps, Channel 1 (433.4MHz) |
| Standby Current (per mode) | 3.6mA, 80uA, 16mA, 16mA |
| Sleep Current | 22uA |
| Operating Current | 100mA |
| Default Mode | FU3 at 9600bps, Channel 01 (433.4MHz) |
| Modulation Mode | OOK, FSK, GFSK, MSK, GMSK, 4FSK, 4GFSK |
| Transmission Rate | <10 Kbps |
| Interface | UART 3.3V/5V TTL level |
| Chip | [Silicon Labs SI4463](materials/si44xx_datasheet.pdf) |
| Size | 27.4x13.2x4mm |

> [!NOTE]
> There are *two* versions of this board available: one with the microcontroller *STM8S003F3**U**6*, and one with the *STM8S003F3**P**6*. These microcontrollers are *identical*. They differ solely in *package size*.

## Connectors

### Antenna
On the one side, the board features a through-hole connector and an *IPEX* connector, both to connect the *antenna*. The *antenna* solder pin is flanked by two *GND* pins on either side.



<img src="images/433_Extension_HC-12_top_t.png" width="60%" height="60%">



> [!TIP]
> Always operate this device *with an antenna*. If no designated antenna is at hand, use a plain *17.3cm* wire. Operating this device without antenna can irreversibly damage the RF unit.


### Interface

On the other end, five through-holes provide the connectivity. They are clearly marked on the back side:


<img src="images/433_Extension_HC-12_back_t.png" width="60%" height="60%" />


| Pin | Tag | Description |
| --- | --- | --- |
| 1 | SET | Input, internal 10K pull-up |
| 2 | TXD | Output |
| 3 | RXD | Input, internal 3.3K pull-up |
| 4 | GND | negative voltage |
| 5 | VCC | +3.2-5.5V |


> [!CAUTION]
> If the *sender* needs to transmit data for a lengthy time, and the power supply is *>4.5V*, then **VCC** should be reduced to no more than *4.5V*, i.e. by connecting a *1N4007* diode in series to prevent over-heating. The limiting factor seems to be the *LDO voltage regulator* on the board which heats up considerably when the input voltage is (much) higher than the required internal voltage **and** current consumption is high (i.e. using high RF transmission power).

## Working Modes
The board supports the following transmission modes:

| Mode | Description | Idle Current | Serial Baud | Air Baud Rate |
| --- | --- | --- | --- | --- |
| FU1 | Power Savings Mode | 3.6mA | 1200-115200 | 250kBps |
| FU2 | Super Power Savings | 80uA | 1200-4800 | 250kBps |
| FU3 | Normal | 16mA | 1200-115200 | 236kBps |
| FU4 | Ultra Long Distance | 16mA | 1200 | 500bps |

### Transmission Speed
The *serial baud rate* controls the *over the air* baud rate. 

| Serial baud (bps) | 1200-2400 | 4800-9600 | 19.2k-38.4k | 57.6-115.2k |
| --- | --- | --- | --- | --- | 
| Wireless baud (Kbps) | 5 | 15 | 58 | 236 |  

### Receiver Sensitivity
The faster the data transfer rate is, the lower is the *receiver* sensitivity:

| Serial Baud (bps) | 500 | 5k  | 15k | 58k | 236-250k |
| ---  | ---  | ---  | ---  | ---  | ---  |
| Receiver Sensitivity  | -124dBm |-116dBm |-111dBm |-106dBm |-100dBm |

> [!TIP]
> Communication distance reduces by half for every *6dBm* decrese in receiver sensitivity.

## Materials

[Silicon Lab Si4463 Datasheet](materials/si44xx_datasheet.pdf)

> Tags: HC-12, Sender, Receiver, Transceiver, RF, 433MHz, 3.3V, 5V, IPEX, OOK, ASK, FSK, GFSK

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/transceiver/hc-12?649483042001242432) - created 2024-04-01 - last edited 2024-10-26
