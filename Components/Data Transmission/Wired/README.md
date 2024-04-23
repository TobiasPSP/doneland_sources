<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Wired Data Transmission

> Transmitting Data Over Wires



*Wired* communication is used all over the place without you probably even noticing: *components* like *displays* or *sensors* typically use wired protocols to communicate with *microcontrollers*.

For communication *between* devices, *wireless* technologies have become increasingly popular, however anyone requiring *reliable*, *fast*, and *secure* communications still counts on *wired* data transmission whereever possible.

Here are some examples of *wired protocols* used for *data transmission*:

### Intra-Board Communication

Devices often consist of many different and independent components, such as *displays*, *sensors*, or *microcontrollers*. These components need to communicate with each other. The four most widely used *wired* protocols are these:

* **Serial (UART, Universal Aynchronous Receiver/Transmitter):** simple serial *two-wire* protocol similar to *morse code*. It can be used to transfer small amounts of data over relatively long distances with a minimum of hardware effort.
* **USB (Universal Serial Bus):**  *USB* is a truly *universal* bus system that not only manages *power* but can also *communicate* and *transmit data* at very high speed. Via *UART* bridges (i.e. *CH340*), *USB* devices (such as a *PC*) can communicate with *UART* devices (such as an *ESP8266*). Modern microcontrollers (i.e. *ESP32 C3, C6, S2, S3*) come with *native USB support* and communicate directly over the *USB* interface.
* **I2C (Inter-Integrated-Circuit):** Two-wire short-range protocol designed to interconnect components within one device. This slow protocol is used for components that do not need to exchange large amounts of data at high speed, for example *sensors* or small mono-color *displays*.
* **SPI (Serial Peripheral Interface):** Four-wire full-duplex high speed data protocol designed to *synchronously* transmit data between a dedicated *master* and one or more *slave* devices, typically all inside one device. Due to its overhead (*master/slave* architecture, *four* data wires), it is used when data transmission *speed* becomes important, i.e. to connect to large and colorful *displays* or a high-speed *Ethernet* device.

#### Short Distance Communication

*Wired* communication protocols don't actually care *what* they are used for, so all of the previously mentioned protocols could also be used to *communicate between devices* over long distances. However, these protocols are *designed for short distances*, and they all become susceptible to *interferences* and *noise signals* the longer the cables get. *Reliable* communication is possible only for (very) short distances:

| Bus System | max recommended distance | Transmission Speed (typical) | Wires |
| --- | --- | --- | --- |
| UART | 15m | 9.6-115.2kbps | 2 |
| USB  | 3m | 60Mbps | 8 |
| I2C | 1m | 100/400kbps | 2 |
| SPI | 20cm | 80MHz | 4 |

> [!NOTE]
> The table above provides a rule of thumb. It is a *simplification*, and many sub-standards have evolved, affecting maximum speed and number of wires used for these bus systems.




> [!NOTE]
> There are known *tricks* and *workarounds* for using these protocols over much larger distances (i.e.  *active* cables or *amplifiers*) however these protocols are just not designed for bridging long distances, and there are better protocols for it. 


### External Communication

One *well-established* and *reliable* protocol for *high speed* data transfer over relatively *large distances* is *Ethernet* which can bridge distances of up to *100m* without *sweat* and *tricks*.

> [!NOTE]
> By adding an *Ethernet* adapter to your project, you are basically just adding a specialized *long distance* protocol. The *Ethernet* adapter in turn is connected to your microcontroller using a *short-distance SPI* connection.

Aside from pure *data transfer*, adding *Ethernet* connectivity to a device enables it to be connected to a *LAN* (*local area network*) in the most *reliable* and *safe* way.



## Wired - Advantages

While *wireless* communication is convenient, *wired* communication has its own set of advantages:

* **Speed:** Wired transmissions can reach very high data transfer rates (i.e. 100MBps with *Ethernet*)
* **Reliability:** Once a data transmission cable is in place, it performs very reliable. There are no *interferences*, *external noise signals*, *weak field strengths*, etc.
* **Security:** While wireless communications can be picked up by anyone, *wired* transmissions are *physically protected*. An attacker would have to physically tap into the communications wire.
* **Low Interference:** Wired protocols do not influence other wired protocols as information is bound to the physical wires. 


> Tags: Wired, I2C, SPI, UART, USB, Ethernet, Data Transfer, Communication

[Visit Page on Website](https://done.land/components/datatransmission/wired?008443041222244629) - created 2024-04-21 - last edited 2024-04-21
