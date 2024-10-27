<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# HC-12
> A Very Powerful 433–473 MHz Transmitter and Receiver with Built-in Microprocessor

The *HC-12* module is capable of both transmitting and receiving within the *433.4–473.0 MHz* range, offering an exceptionally high maximum RF transmission power of **100 mW** (20 dBm). It supports multiple channels and various modes tailored for different applications, including *low power consumption*, *transmission speed*, and *maximum range*. The module is built on the [Silicon Labs SI4463](materials/si44xx_datasheet.pdf) and supports both simple *OSK* and various forms of *FSK modulation*.


The SI4463 remains in production as of this writing and is readily available from various sources. However, Silicon Labs has labeled the [SI4463 Data Sheet](materials/si44xx_datasheet.pdf) with a "Not Recommended For New Designs" (NRND) designation. What does this imply?

The SI4463 is an outstanding and affordable transceiver chip. Boards like the HC-12, which utilize this chip, may gradually be phased out over the coming years, likely replaced by successor chips that further optimize power consumption or offer tighter integration with microcontrollers. In practical terms, this note suggests that if you're content with the HC-12’s features and price, it might be wise to stock up on a few extra boards while they're still readily available.


<img src="images/433_Extension_HC-12_angle_t.png" width="40%" height="40%" />



> [!NOTE]
> This module *can* control *garage doors* and remote-controlled devices via simple *OOK* modulation. However, such straightforward tasks are better suited to simpler modules. The *HC-12* is **far more capable**, functioning as a fully programmable data transceiver with relatively **high RF output power**. In fact, its strongest transmission modes **exceed legal limits** in most countries, requiring a **licensed radio amateur (HAM)** to operate at maximum settings.

## Overview
This board has an onboard microprocessor that manages all *receiving* and *sending* tasks, making control straightforward and adding no processing overhead to your own microcontroller.

### Frequency Range and Channels
The board operates in a frequency range of *433.4–473.0 MHz*, organized into *channels* with a step size of *400 kHz*. 

It has a maximum transmission power of +20 dBm/100 mW, and excellent receiver sensitivity at *-116 dBm*. In clear *line of sight* and with a suitable antenna, transmission distances of *over 1 km* or more are easily achievable.

> [!CAUTION]
> Due to its **broad frequency range** and **high RF transmission power**, this board operates outside license-free bands and is therefore **illegal to use** in *Europe* without an appropriate **license** (such as a *HAM radio amateur license*).

### Specs

| Item | Value |
| --- | --- |
| Voltage | 3.2-5.5V |
| Frequency | 433.4-473.0 MHz |
| Antenna  | external Antenna (SMA) or spring antenna via solder connection |
| Output Power | 20dBm max (100mW max, can be set to lower RD power) |
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
One side of the board features a through-hole connector and an *IPEX* connector, both for attaching the *antenna*. The *antenna* solder pin is flanked by two *GND* pins on either side.

<img src="images/433_Extension_HC-12_top_t.png" width="60%" height="60%">

> [!TIP]
> Always operate this device *with an antenna*. If you don’t have a designated antenna, a simple *17.3 cm* wire will work. Operating without an antenna can irreversibly damage the RF unit.

### Interface

On the opposite end, five through-holes provide connectivity, clearly marked on the backside:


<img src="images/433_Extension_HC-12_back_t.png" width="60%" height="60%" />


| Pin | Tag | Description |
| --- | --- | --- |
| 1 | SET | Input, internal 10K pull-up |
| 2 | TXD | Output |
| 3 | RXD | Input, internal 3.3K pull-up |
| 4 | GND | negative voltage |
| 5 | VCC | +3.2-5.5V |

> [!CAUTION]
> If the *transmitter* needs to send data for an extended period and the power supply exceeds *4.5V*, it is recommended to reduce **VCC** to *4.5V* or lower. This can be achieved by placing a *1N4007* diode in series to prevent overheating. The limiting factor is the *LDO voltage regulator* on the board, which can heat up significantly when the input voltage is much higher than the required internal voltage and current consumption is high (such as when using high RF transmission power).

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
