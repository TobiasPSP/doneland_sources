<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Using FM Transceivers

> Reliable Data Transfer at High Speeds Using FM Modulation

Whenever you need to *reliably* transfer larger amounts of data at high rates of speed, simple *OOK* transmission quickly reaches its limits.

<img src="images/e07-m1101d_top_top_antenna_t.png" alt="FM Transceiver">

**FM** (*Frequency Modulation*) requires more complex receiver circuits than *OOK* as *FM* needs to demodulate frequency shifts while *OOK* is simply detecting on/off signals. That's why *OOK* remains popular for low-cost and low-power applications like simple remote controls. 

Thanks to technological progress, though, *FM breakout boards* today aren't more expensive than *OOK* senders and receivers. They exist in many shapes and forms and work on different frequency bands.

<img src="images/fsk_rxtx_rfm69_back_t.png" alt="FSK Transceiver">

> [!NOTE]
> Even *remote controls* today start using **FM modulation**, especially with security-sensitive use cases (i.e. car key fobs, garage door openers). 

## Overview

Simple *OOK* is the technically most basic way of sending radio waves: the sender is turned on and off in intervals to transmit signals.

With encodings like *EV1527*, this is sufficient to transmit simple chunks of data, i.e., *24-bit IDs* for remote controls. However, this is neither reliable, efficient, nor fast.

*OOK* is still widely used because of its technical simplicity, and low-cost applications like remote controls continue to use it.

Once you need to transfer more data over longer distances at higher speeds or with less power consumption, then more advanced modulation techniques are necessary to make better use of radio waves.

### Transceiver

Most *FM*-based breakout boards are *transceivers*: they can both *send* and *receive*, meaning you don't need distinct *sender boards* and *receiver boards* like in *OOK* and *EV1527*.

<img src="images/radio_as07-m1101s_side1_t.png" alt="Transceiver">

Being able to *send* **and** *receive* enables *two-way communication*, which is important for *robust* data transfer:

A *sender* can **send** data and then switch to **receiver** mode to listen for an acknowledgment from the receiver, ensuring that the transmission was received correctly. Likewise, the **receiver** switches to **sender mode** once it receives data and reports back whether the data was received correctly or if a re-transmission is needed.

Most modern communication protocols use this constant switch in *sending* and *receiving* to ensure data integrity.

### Microcontroller Required

Even though *FM breakout boards* do all the heavy lifting for you, they typically require a microcontroller to program them.

Depending on the type of board, commands can be issued using common interfaces like *UART (serial)*, [I2C](https://done.land/fundamentals/interface/i2c/), or [SPI](https://done.land/fundamentals/interface/spi/).

<img src="images/fsk_rxtx_rfm69_top_t.png" alt="FM Transceiver">

#### Specialized Modules

Most *FM* breakout boards are *generic* and leave it up to you how you'd like to use them: you can choose modulation, speed, RF power, and submit any data in any encoding you wish. 

*Specialized FM modules* exist that are already tailored for a specific use case and require no external microcontroller or programming. 

I am not focusing on these types of *specialized modules* here, but would like to quickly illustrate what they are: one particularly popular type handles *wireless serial*, often bi-directional:

1. Connect **RX** and **TX** to such a module.
2. Connect **RX** and **TX** of another (paired) module somewhere else.

Both modules now transfer any serial data wirelessly at a defined baud rate. No need for expensive cables.

<details><summary>How FM is used in technologies like WiFi, Bluetooth, Zigbee, and Matter</summary><br/>
We all use digital transmission technologies all the time and almost everywhere:

| Technology  | Primary Use Case | Range | Power Consumption |
|-------------|----------------|-------|------------------|
| **Wi-Fi** | High-speed data, internet | Medium (~50m indoors) | High |
| **Bluetooth Classic** | Audio, peripherals | Short (~10m) | Moderate |
| **Bluetooth Low Energy (BLE)** | IoT, sensors, wearables | Short (~50m) | Low |
| **Zigbee (and Thread)** | Smart home, industrial IoT | Medium (~100m) | Very low |


These are all wireless and based on the same simple [OOK principles](https://done.land/components/data/datatransmission/wireless/intro/usingradiowaves%28ook%29/) that *any* digital transmission uses. All of them resemble just clever *wireless communication protocols* that are implemented on top of the physical *OOK* layer (the physical and raw transmission of radio waves).

- **Bluetooth and BLE use GFSK**, a direct descendant of FM that optimizes frequency-based modulation for digital communication.
- **Zigbee (Thread uses the same PHY layer) uses O-QPSK**, which, while not directly FM-based, still benefits from frequency domain processing for noise immunity.
- **Wi-Fi uses OFDM**, which is a multicarrier modulation method that is significantly more complex than FM but still leverages frequency shifts in subcarriers for data transmission.

| Technology  | Modulation Scheme | Notes |
|-------------|------------------|-------|
| **Wi-Fi (802.11)** | **OFDM (Orthogonal Frequency-Division Multiplexing)** | Uses multiple frequency subcarriers to improve spectral efficiency and reduce interference. |
| **Bluetooth (Classic)** | **GFSK (Gaussian Frequency Shift Keying)** | Reduces spectral splatter and improves power efficiency. |
| **Bluetooth Low Energy (BLE)** | **GFSK** | Optimized for low-power applications with a narrower bandwidth than Classic Bluetooth. |
| **Zigbee (IEEE 802.15.4)** | **O-QPSK (Offset Quadrature Phase Shift Keying) with DSSS (Direct Sequence Spread Spectrum)** | Improves noise resistance and reduces interference in the 2.4 GHz band. |


</details>

> [!TIP]
> While digital FM modulations can no longer transfer analog signals directly, you can still build a walkie-talkie: use an *ADC* (analog-to-digital converter) to digitize the microphone's amplitudes. On the receiver side, run the bits through a *DAC* (digital-to-analog converter) to drive a speaker. Alternatively, you can use a *digital microphone* and *digital amplifiers* directly (e.g., using *I2S*).


## Conclusion

FM-based modulation offers a more reliable and efficient way of transmitting data compared to simple OOK, especially when higher data rates, longer distances, or two-way communication are required.

### Two-Way Communication
FM-based transceivers enable both sending and receiving data, allowing mechanisms like acknowledgments and retransmissions to ensure reliable data transfer.

### Digital Data Transmission
Digital modulation schemes such as GFSK, O-QPSK, and OFDM improve data transfer speed, range, and efficiency.

| Modulation Scheme | Description                                 | Primary Use Case                |
|-------------------|---------------------------------------------|---------------------------------|
| **FSK (Frequency Shift Keying)** | The most basic form of FM used for binary data transmission. | Simple communication systems, basic data transfer. |
| **GFSK (Gaussian Frequency Shift Keying)** | A type of FSK where the frequency shifts are smoothed using a Gaussian filter to reduce sideband interference. | Used in Bluetooth Classic and BLE for efficient data transfer with lower power consumption. |
| **O-QPSK (Offset Quadrature Phase Shift Keying)** | A variant of QPSK that offsets the phase shifts to minimize interference. | Used in Zigbee and Thread for smart home and industrial IoT applications. |
| **OFDM (Orthogonal Frequency-Division Multiplexing)** | A complex modulation that splits data across many sub-carriers to improve spectral efficiency. | Used in Wi-Fi (802.11), provides high-speed data transmission over medium-range distances. |

### Foundation Of Modern Wireless Technology
FM modulation is the basis of modern wireless technologies like Bluetooth, Zigbee, and Wi-Fi. These technologies leverage FM principles to handle interference and provide better noise immunity.

| Technology       | Modulation Scheme | Use Case                          | Power Consumption | Range     |
|------------------|-------------------|-----------------------------------|-------------------|-----------|
| **Wi-Fi**        | OFDM              | High-speed data, internet        | High              | Medium (~50m indoors) |
| **Bluetooth**    | GFSK              | Audio, peripherals                | Moderate          | Short (~10m)  |
| **Bluetooth LE** | GFSK              | IoT, wearables                    | Low               | Short (~50m)  |
| **Zigbee**       | O-QPSK            | Smart home, industrial IoT        | Very Low          | Medium (~100m)  |
| **FM (Generic)** | FSK/GFSK          | Wireless serial communication     | Varies            | Short to Medium |

### Affordable And License-Free Option For Your Projects
Affordable breakout boards allow you to leverage these digital modulation schemes in your own DIY projects, taking advantage of license-free ISM frequency bands. 



> Tags: FM, FSK, GFSK, O-QPSK, OFDM, Frequency Modulation, Wireless Communication, Digital Modulation, Data Transmission, Two-Way Communication, Wi-Fi, Bluetooth, Zigbee, ISM Bands

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/intro/usingradiowaves(ook)/fmtransceiver?835237031322255935) - created 2025-03-21 - last edited 2025-03-21
