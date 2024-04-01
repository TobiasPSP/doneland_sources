<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# HC-12

> A Full-Fledged 433-473MHz Sender And Receiver With Its Own Microprocessor

The *HC-12* goes far beyond the typical *garage-door opener* *RF sender* and *receiver* boards: it is acting more like a professional transceiver, can send *and* receive (allowing two-way communications), and supports a wide frequency range with channels.



<img src="images/433_Extension_HC-12_angle_t.png" width="40%" height="40%" />



> [!NOTE]
> This module can control *garage doors* and remote-control devices just like the other *RF modules* described here. It is much more capable, though, and can serve as a programmable data transceiver.

## Microprocessor-Controlled
This board uses its own microprocessor that takes care of all *receiving* and *sending* tasks. Controlling the board is very easy and does not add any overhead to your own microprocessor.

## Frequency Range And Channels
The board can *send and receive* in a frequency range of *433.4-473.0MHz* which is organized in *channels* with a step size of *400kHz*. 

Its maximum transmitting power is +20dBm/100mW, and the receiver sensitivity is excellent with *-116dBm*. In free *line of sight*, distances of over *1km* can be bridged.

> [!CAUTION]
> Both the wide frequency range and the high RF output power are *incompatible with legal reguirements* for free use in *Europe*. It is *illegal* to use this device without an appropriate license (i.e. radio amateur).   



## Specs

This breakout board by default emits *100mW* which is well above the legal limit of *10mW* in *Europe*. The RF power can be reduced by software.

| Item | Value |
| --- | --- |
| Voltage | 3.2-5.5V |
| Frequency | 433MHz *or* 315MHz |
| Output Power | 11dBm / 12.5mW |
| Sending Modes | FU1, FU2, FU3, FU4 |
| Standby Current | 3.6mA, 80uA, 16mA, 16mA |
| Sleep Current | 22uA |
| Operating Current | 100mA |
| Default Mode | FU3 at 9600bps, Channel 01 (433.4MHz) |
| Modulation Mode | AM (OOK) |
| Transmission Rate | <10 Kbps |
| Interface | UART 3.3V/5V TTL level |
| Size | 27.4x13.2x4mm |

> [!NOTE]
> There are *two* versions of this board available: one with the microcontroller *STM8S003F3**U**6*, and one with the *STM8S003F3**P**6*. These microcontrollers are *identical*. They differ solely in *package size*.

## Connectors

### Antenna
On the one side, the board features a through-hole connector and an *IPEX* connector, both to connect the *antenna*. The *antenna* solder pin is flanked by two *GND* pins on either side.



<img src="images/433_Extension_HC-12_top_t.png" width="90%" height="90%">



> [!TIP]
> Always operate this device *with an antenna*. If no designated antenna is at hand, use a plain *17.3cm* wire. Operating this device without antenna can irreversibly damage the RF unit.


### Interface

On the other end, five through-holes provide the connectivity. They are clearly marked on the back side:


<img src="images/433_Extension_HC-12_back_t.png" width="90%" height="90%" />


| Pin | Tag | Description |
| --- | --- | --- |
| 1 | SET | Input, internal 10K pull-up |
| 2 | TXD | Output |
| 3 | RXD | Input, internal 3.3K pull-up |
| 4 | GND | negative voltage |
| 5 | VCC | +3.2-5.5V |


> [!CAUTION]
> If the *sender* needs to transmit data for a lengthy time, and the power supply is *>4.5V*, then **VCC** should be reduced to no more than *4.5V*, i.e. by connecting a *1N4007* diode in series to prevent over-heating.

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

## Default Working Mode
By default, the module uses transmission mode *FU3*: the module works at full speed, and the *over the air* transmission rate is adjusted to the speed of the *serial port baud rate*.



> Tags: HC-12, Sender, Receiver, Transceiver, RF, 433MHz, 3.3V, 5V, IPEX

