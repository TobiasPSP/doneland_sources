<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />

# HC-12

> A Very Powerful 433–473 MHz Transmitter and Receiver with Built-in Microprocessor

The *HC-12* module is a half-duplex *100mW* multi-channel *FM* transceiver for digital data transmission with a built-in microcontroller that allows it to run autonomously without external microcontrollers.

Its primary use case is wirelessly transmitting serial data at various baud rates. 

Note that *HC-12* is capable of outputting RF signals ten times above the legal limit of license-free ISM bands (*100 mW* instead of *10 mW*). If you are not a licensed radio amateur, you must program the board to emit *10 mW* at maximum.


## Overview
Sometimes there is a need to have a data connection between devices over some distance. *HC-12* works as a wireless UART extender, forwarding the transmitted information wirelessly to another *HC-12* module.

To enable this, *HC-12* has a built-in microcontroller. Its firmware autonomously takes care of all required tasks and controls the *SI4438/SI4463* radio chip via an internal *SPI* interface. 

The user simply connects the UART output of one device to `RX` and `TX`, and picks up the signals at the other *HC-12* module at its `RX` and `TX` pins.

### Ease of Use

It is important to understand that *HC-12* is a **specialized** application that does not expose the *SI44xx* radio chip or its capabilities to the outside. Instead, its built-in microcontroller interfaces with the radio chip.

This makes using this module so simple: to the outside, a user simply connects the data lines. *HC-12* immediately starts transferring the data wirelessly.

The user can configure the module by setting certain high-level preferences, such as focussing on low power, high speed, or long distance. *HC-12* internally then picks the most appropriate *FM modulations* and radio settings.

The module covers the frequency range *425-525 MHz* and divides it into 100 channels at a *400 kHz* spacing, and the user picks a channel.

### Limitations

The downside to this abstraction is that you have no access to low level radio settings, and you can transfer data only as UART data streams.

If you want to directly access the *SI44xx** API, you would have to [re-program the onboard microcontroller](https://github.com/rumpeltux/hc12) as it is the only one with direct *SPI* access to the radio module. This is complex, so if you need low-level access to radio functions, *HC-12* is not for you. Instead, choose a simpler board without microcontroller and with an exposed *SPI* interface so you can use your own microcontroller to talk to the radio module.

### Built-In Microcontroller
*HC-12* uses the 16 MHz 8-bit *STM8S003F3* microcontroller made by *STMicroelectronics* with proprietary firmware that translates a set of UART commands into commands for the internal *ST44xx* radio chip. 

The package type of the microcontroller may vary: both small square-shaped *U6* (LQFP-20) or larger *P6* (TSSOP-20) package types are commonly found.



### Clones: SI4438 vs. SI4463
*HC-12* is available in many versions and cloned designs. They all use a *SI44xx* radio chip from *Silicon Labs*. Unbranded and very affordable boards often use the cheaper and less feature-rich *SI4438*.

> [!IMPORTANT]
> Both versions are marketed under the same name: *HC-12*. Vendors often use *SI4438* and *SI4463* interchangeably in their ads, still shipping *SI4438* only. Check the chip markings on the boards you receive.

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


From a practical perspective, these are the relevant consequences:

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


## Configuring HC-12

With *HC-12*, only the built-in microcontroller has direct access to the radio module. The user *cannot* directly control them and uses simple *AT commands* instead to tell the built-in microcontroller what to do:

* **Priorities:**     
  a choice of four different transmission modes (`FU1` - `FU4`) allow the user to prioritize *power consumption*, *speed*, or *communication distance*. Internally, the microcontroller translates these modes into the most appropriate FM modulations and radio settings.
* **Channel:**     
  the user cannot set a specific frequency. Instead, there is a choice of *100 channels*. Internally, the microcontroller translates these channels into frequencies within the *425-525 MHz* frequency range. **Only channels 1-4** represent license-free frequencies in Europe.
* **Power:**     
  the user can set the RF output power in eight steps from *0.8 mW* to *100 mW*, roughly doubling the power with each step. **Only the first four RF power choices** (*0.8 mW*, *1.6 mW*, *3.2 mW*, *6.3 mW*) are legal to use in license-free bands.   
* **Serial Interface:**    
  the user can configure speed and settings of the serial interface so it matches the devices that need to communicate. *HC-12* supports baud rates in the range of *1200-115200*. However, the maximum baud rate depends on the transmission mode you chose and is limited to *4800* in `FU2` and to *1200* in `FU4`. `FU1` and `FU3` do not restrict the available baud rates. In addition, number of bits, parity, and stop bits can be defined. 

By default, *HC-12* uses `FU3` at 9600,8,N,1 on *channel 1* (433.4MHz).
  
### Sending Commands
By default, *HC-12* works in data mode and treats all input at `RX` as data that is sent off.

To instruct the microcontroller to treat input as *commands*,  pin `SET` must be connected to `GND`. While this connection exists, all input is treated as *AT commands*.

> [!TIP]
> To reset the communication settings to the default `9600 baud, 8, N, 1`, connect `SET` to `GND`, then **power on HC-12**.

## Choosing Transmission Mode
The transmission mode prioritizes low power consumption, speed, or communication distance. 

The mode is set via `AT+FU1` through `AT+FU4`.

| Mode | `FU1` | `FU2` | **`FU3`** | `FU4` |
| --- | --- | --- | --- | --- |
| Use Case | power efficient | extreme low power | **normal** | long distance |
| Power (receive) | 3.6 mA | 80 uA | **16 mA** | 16 mA |
| Latency | 15-25 ms | 500 ms | **4-80 ms** | 1000 ms |
| Maximum baud rate | 115.200 | 4.800 | **115.200** | 1.200 |
| Communication Distance (*100 mW*) | 100 m | 100 m | **1.000 m (2.400 baud)<br/>600 m (9.600 baud)** | 1.800 m |
| Air Baud Rate (kbps) | 250  | 250 | 236 | 0.5 |

* In `FU2`, receiving power consumption is extremely low (80 uA). The price you pay speed capped at *4.800 baud*, plus long latency (*500 ms*): the radio chip is sent to sleep in regular intervals. 
* The sleep current is 22uA (in sleep, the board is not operational and cannot receive). 
* When transmitting with full power, power consumption can raise to *100 mA*, regardless of mode.

### Choosing Baud Rate
The baud rate at which the data is delivered by the external device can be set via `AT+B*x*` (where *x* is the baud rate, i.e. `AT+B9600`).

| Serial Baud Rate | 1.200 | 2.400 | 4.800 | 9.600 | 19.200 | 38.400 | 57.600 | 115.200 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | 
| Air Baud Rate | 5.000 | 5.000 | 15.000 | 15.000 | 58.000 | 58.000 | 236.000 | 236.000 |
| `FU1` | yes | yes | yes | yes | yes | yes | yes | yes |
| `FU2` | yes | yes | yes | - | - | - | - | - |
| `FU3` | yes | yes | yes | yes | yes | yes | yes | yes |
| `FU4` | yes | - | - | - | - | - | - | - |
| RX Sensitivity (dBm) | -117  |  -117  |  -112  | -112 | -107 | -107 |  -100 |  -100 | 

* The trade-off is *speed* versus *communication distance* because with faster data transfer rates, the receiver sensitivity decreases. That's why the long range mode `FU4` supports only slow *1.200 baud*.
* Due to error correction and related overhead, the data transmission rate (serial baud rate) is always considerably lower than the air baud rate.

## RF Power
The radio chip on *HC-12* boards supports RF power of up to *20dBm/100mW* and can be controlled in eight steps via `AT+P1` through `AT+P8`. 

The default is maximum RF power at *100 mW*.

| Power Level | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| --- | --- |  --- | --- |  --- | --- | --- | --- | --- |
| mW | 0.8 | 1.6 | 3.2 | 6.3 | 12 | 25 | 50 | 100 |
| dBm | -1 | 2 | 5 | 8 | 11 | 14 | 17 | 20 |

In most regions of the world, the limit for the license-free 433 MHz band is *10 mW* (power levels *1-4*). For RF power exceeding *10 mW*, a license is required (i.e. HAM Radio Amateur).


## Channel

With `AT+C1` through `AT+C100` the user can select a channel. *HC-12* translates channels to frequencies, starting at *433.4 MHz*, with a spacing of *400 kHz*. So channel #1 represents *433.4 MHz*, channel #2 *433.8 MHz*, channel #3 *434.2 MHz*, and so forth.

Channel #1 is set by default.

In Europe, the license-free frequency range is *433.05-434.79 MHz*, so only channels #1-#4 are legal to use (without a license).

### Incompatibilities

Internally, the firmware translates the selected operation mode into  appropriate digital FM modulations. 

This explains reports that *HC-12* modules from different vendors cannot communicate. If you experience issues like this, start by checking the firmware versions using `AT+V`.

If firmware versions do not match, they may use different *FM modulations* for the more specialized modes `FU1`, `FU2`, and `FU4`. Try `FU3` to see whether the modules can connect now.

One of the reasons why different firmware versions exist that use incompatible radio settings lays in the fact that *HC-12* boards use different radio chips.

Boards with the more sophisticated *SI4463* take advantage of more sophisticated modulations like *(G)MSK*, which increases data rates and/or long distance communication. Since these modulations aren't supported with boards using the *SI4438*, the result are incompatibilities.


> [!TIP]
> Communication distance reduces by half for every *6dBm* decrease in receiver sensitivity.


## Materials

[HC-12 Manual](materials/hc-12_manual.pdf)    
[Silicon Lab Si4438 Datasheet](materials/si4438.pdf)     
[Silicon Lab Si4463 Datasheet](materials/si4463.pdf)     
[STM8S103 Microcontroller Datasheet](materials/stm8s103f2.pdf)     

> Tags: HC-12, Sender, Receiver, Transceiver, RF, 433MHz, 3.3V, 5V, IPEX, OOK, ASK, FSK, GFSK

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/fm/gfsk/transceiver/hc-12?649483042001242432) - created 2024-04-01 - last edited 2025-03-22
