<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Wired Data Transmission

> Options To Transmit Data Via Wire

Nowadays, data transmissions are often performed *over the air* using *radio frequencies* and technologies such as i.e. *SRD*, *WiFi*, *Bluetooth*, or *Zigbee*. It's just so much simpler to use the *air* and *radio waves* instead of having to place a communications wire. Mobile applications can't use wires in the first place.

## Advantages

While *wireless* communication is convenient, *wired* communication has its own set of advantages:

* **Speed:** Wired transmissions can reach very high data transfer rates (i.e. 100MBps with *Ethernet*)
* **Reliability:** Once a data transmission cable is in place, it performs very reliable. There are no *interferences*, *external noise signals*, *weak field strengths*, etc.
* **Security:** While wireless communications can be picked up by anyone, *wired* transmissions are *physically protected*. An attacker would have to physically tap into the communications wire.

## Use Cases

*Wired* communications is used in many completely different scenarios. Here are some:

### Intra-Board Communication

Devices often consist of many different and independent components, such as *displays*, *sensors*, or *microcontrollers*. 

These components need to communicate with each other. The four most widely used *wired* protocols are these:

* **Serial (UART, Universal Aynchronous Receiver/Transmitter):** simple serial *two-wire* protocol similar to *morse code*
* **USB (Universal Serial Bus):**  *USB* is a truly *universal* bus system that can manage and provide *power* but also *communicate*. Via *UART* bridges (i.e. *CH340*), *USB* devices (such as a *PC*) can communicate with *UART* devices (such as an *ESP8266*). More modern microcontrollers (i.e. *ESP32 C3, C6, S2, S3*) come with *native USB support* and can communicate directly with a *PC* using the *USB Port*.
* **I2C (Inter-Integrated-Circuit):** Two-wire short-range protocol designed to interconnect components within a device. This interface is relatively slow and used for components that do not need to exchange large amounts of data quickly, for example *sensors* or small mono-color *displays*.
* **SPI (Serial Peripheral Interface):** Four-wire full-duplex high speed data protocol designed to *synchronously* transmit data between a dedicated *master* and one or more *slave* devices, typically all inside one device. Due to its overhead (*master/slave* architecture, *four* data wires), it is used when data transmission *speed* becomes important, i.e. to connect to large and colorful *displays* or a high-speed *Ethernet* device.

## External Communication

*Wired* communication buses don't care *what* they are used for, so all of the previously mentioned protocols can also be used to *communicate between devices* and for longer distances. These protocols are just not designed to communicate over *long distances*, and they all become more susceptible to *interferences* and *noise signals*. With these protocols, *reliable* communication is possible only for (very) short distances:

| Bus System | max recommended distance | Transmission Speed |
| --- | --- | --- |
| UART | 15m | + |
| USB  | 3m | ++ |
| I2C | 1m | ++
| SPI | 20cm | +++ |

> [!NOTE]
> There are known *tricks* and *workarounds* for using these protocols over much larger distances (i.e. using *active* cables or *amplifiers*) however they are just not made for it. 

### Ethernet

One *well-established* and *reliable* protocol for *high speed* data transfer over relatively *large distances* is *Ethernet* which can bridge distances of up to *100m* without the need for additional measures.

Aside from pure *data transfer*, adding *Ethernet* connectivity to a device enables it to be connected to a *LAN* (*local area network*) in the most reliable and safe way.



> Tags: Wired, I2C, SPI, UART, USB, Ethernet, Data Transfer, Communication

