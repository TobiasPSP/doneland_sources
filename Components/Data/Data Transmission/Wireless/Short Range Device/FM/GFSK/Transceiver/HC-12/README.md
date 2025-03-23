<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />

# HC-12

> A Very Powerful 433–473 MHz Transmitter and Receiver with Built-in Microprocessor

The *HC-12* module is a half-duplex *100mW* multi-channel *FM* transceiver for digital data transmission with a built-in microcontroller that allows it to run autonomously without external microcontrollers.

Its primary use case is wirelessly transmitting serial data at various baud rates. 

Note that *HC-12* is capable of outputting RF signals ten times above the legal limit of license-free ISM bands (*100 mW* instead of *10 mW*). If you are not a licensed radio amateur, you must program the board to emit *10 mW* at maximum.


## Overview

This *433 MHz* digital FM radio board uses its own on-board microcontroller that takes care of most radio and modulation complexities and lets you focus on simple UART/serial commands. 


### Built-In Microcontroller
*HC-12* is designed to be operated stand-alone without the need for an external microcontroller and firmware.

It uses the 16 MHz 8-bit *STM8S003F3* microcontroller made by *STMicroelectronics* with proprietary firmware that translates a set of UART commands into commands for the internal *ST44xx* radio chip. Boards use the small square-shaped *U6* (LQFP-20) or the larger *P6* (TSSOP-20) package type.

The microcontroller firmware takes care of all fundamental sending and receiving, and the module can be used to autonomously wirelessly transmit *serial data* with various baud rates: simply connect a serial line to `RX` and `TX`, and use a second module to receive the signals again at `RX` and `TX`. 

Provided both modules use the same configuration, then this solution works out of the box with minimal effort.

#### Configuring Microcontroller
To configure the microcontroller and i.e. set channel, output power, or data speed, connect pin `SET` to `GND`: now serial input is treated as commands at `9600 baud, 8, N, 1` until you disconnect `SET` from `GND` again.

The microcontroller supports four different transmission modes (`FU1` - `FU4`) and *100* channels spaced *400 kHz* apart.

| Item | Value |
| --- | --- |
| Sending Modes | FU1, FU2, FU3, FU4 |
| Default Mode | FU3: 9600bps, Channel 1 (433.4MHz) |
| Standby Current (per mode) | 3.6mA, 80uA, 16mA, 16mA |
| Sleep Current | 22uA |
| Operating Current | 100mA |
| Transmission Rate | <10 Kbps |
| Channels | 100 |
| Channel Spacing | 400 kHz |
| Interface | UART 3.3V/5V TTL level |
| Size | 27.4x13.2x4mm |

> [!TIP]
> You can program your own firmware and [upload it to the onboard microcontroller](https://github.com/rumpeltux/hc12). This way you get direct *SPI access* to the *SI4438*/*SI4463* registers.

### High RF Power

RF Power is programmable, and the board can be configured to stay within legal limits (*10 mW*). Operating the board at full RF power (*100 mW*) requires a license (i.e. *HAM Radio Amateurs*).

### Clones: SI4438 vs. SI4463
*HC-12* is available in many versions and cloned designs. They all use a *SI44xx* radio chip from *Silicon Labs*. Especially unbranded and very affordable boards use the cheaper and less feature-rich *SI4438*.

Both versions are marketed under the same name: *HC-12*. Vendors often use *SI4438* and *SI4463* interchangeably in their ads, still shipping *SI4438* only. Check the chip markings on the boards you receive.

*SI4438* and *SI4463* differ considerably:

| Feature                   | SI4463                                | SI4438                                |
|---------------------------|---------------------------------------|---------------------------------------|
| **Power Supply**           | 1.8 V to 3.6 V                        | 1.8 V to 3.6 V                        |
| **Frequency Range**        | 119-1050 MHz                          | 425-525 MHz                           |
| **Modulation**             | (G)FSK, 4(G)FSK, (G)MSK, OOK         | (G)FSK, OOK                           |
| **Data Rate**              | 0.123 kbps - 1 Mbps                   | 100 - 500 kbps                        |
| **Output Power**           | up to +20 dBm                         | up to +20 dBm                         |
| **Receiver Sensitivity**   | -126 dBm                              | -124 dBm                              |
| **Current Consumption (TX)**| 20 mA at +20 dBm                      | 22 mA at +20 dBm                      |
| **Current Consumption (RX)**| 10/13 mA                              | 14 mA                                 |
| **Standby Consumption**    | 50 nA                                  | 50 nA                                 |
| **Integrated Features**    | AES encryption                        | Low-power sleep mode                 |

However, practical consequences are limited because the radio chip is used within the *HC-12 board design* which works on 433 MHz only. The radio chip features (i.e., modulation or encryption) are not directly accessible.

*HC-12* own microcontroller with custom firmware lets the user select predefined "working modes" only. It is up to the firmware to internally translate these "working modes" into particular *FM modulations* used by the radio chip.

From a practical perspective, these are important consequences:

* **Compatiblity:** make sure not to mix boards with *SI4438* and *SI4463*. To leverage features of the *SI4463*, the firmware needs to use modulations that are not available in *SI4438*, making both **incompatible**. 
* **Recommendation:** if you have the choice, opt for boards with *SI4463* as it is the far superior chip with a much better sensitivity (boosting communication distance by *25%*) and up to *30%* better battery life in receive mode.



<img src="images/433_Extension_HC-12_angle_t.png" width="40%" height="40%" />

> [!TIP]
> The UART command `AT+VER` returns the board versions. "Original" boards should return `www.hc01.com` (and have this URL printed on their back side). That said, clone boards from other sources may work reliably, too.

## Connectors

### Antenna
One side of the board features a through-hole connector and an *IPEX* connector, both for attaching the *antenna*. The *antenna* solder pin is flanked by two *GND* pins on either side.

<img src="images/433_Extension_HC-12_top_t.png" width="60%" height="60%">

> [!TIP]
> Always operate this device *with an antenna*. If you don’t have a designated antenna, a simple *17.3 cm* wire will do. Operating without an antenna can irreversibly damage the RF unit.

### Interface

On the opposite end, five through-holes provide connectivity, clearly marked on the backside:

<img src="images/433_Extension_HC-12_back_t.png" width="60%" height="60%" />

| Pin | Tag | Description |
| --- | --- | --- |
| 1 | SET | pulled up, connect to `GND` to issue *AT* commands via serial |
| 2 | TXD | Serial interface |
| 3 | RXD | Serial interface |
| 4 | GND | Ground |
| 5 | VCC | 3.2 - 5.5V |

> [!CAUTION]
> The *LDO voltage regulator* on this board is problematic. When operating at maximum power over extended periods, the LDO needs to convert considerable energy to heat in an effort to lower the input voltage to the required level. To workaround, **lower** the input voltage yourself to *4.5 V*. This can also be achieved by placing a *1N4007* diode in series with a *5 V* power supply.

## Configuration

The module stores its configuration until you re-configure it. To re-configure, connect pin `SET` to `GND` (to enter command mode), then send the appropriate AT commands to `RX`.

The default communication settings for command mode are:

`9660 baud, 8 data bits, no parity, one stop bit`

To reset communication settings to factory defaults, connect `SET` to `GND` when **powering on**.

### Working Modes

The built-in microcontroller takes care of all complex radio operations, including managing *FM modulations*, and translates these into four available operating modes:

| Mode | Description | Idle Current | Serial Baud | Air Baud Rate |
| --- | --- | --- | --- | --- |
| FU1 | Power Saving | 3.6mA | 1200-115200 | 250kBps |
| FU2 | Super Power Saving | 80uA | 1200-4800 | 250kBps |
| FU3 | Normal | 16mA | 1200-115200 | 236kBps |
| FU4 | Long Distance | 16mA | 1200 | 500bps |

Internally, the firmware translates these modes into the appropriate digital FM modulations. You have no direct control over these settings.

This explains why you may experience communication problems when using different *HC-12* modules from different sources. If you experience issues, always start by checking the firmware versions using `AT+VER`.

When modules use different firmwares, these firmwares may use different *FM modulations*, making communication incompatible. Try using one of the other modes, i.e. `FU3` or `FU1`, to check whether the modules can connect this way.

The reason why different modules use different firmwares which in turn use incompatible modulations is the radio chip: 

Boards with the more sophisticated *SI4463* can take advantage of more sophisticated modulations like *(G)MSK* for higher data rates, or better long distance performance. These modes are not available on boards using the *SI4438*. 


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
> Communication distance reduces by half for every *6dBm* decrease in receiver sensitivity.


## Materials

[HC-12 Manual](materials/hc-12_manual.pdf)    
[Silicon Lab Si4438 Datasheet](materials/si4438.pdf)     
[Silicon Lab Si4463 Datasheet](materials/si4463.pdf)     
[STM8S103 Microcontroller Datasheet](materials/stm8s103f2.pdf)     

> Tags: HC-12, Sender, Receiver, Transceiver, RF, 433MHz, 3.3V, 5V, IPEX, OOK, ASK, FSK, GFSK

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/fm/gfsk/transceiver/hc-12?649483042001242432) - created 2024-04-01 - last edited 2025-03-22
