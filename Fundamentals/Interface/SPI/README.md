<img src="/assets/images/interface.png" width="80%" height="80%" />
 
# SPI (Serial Peripheral Interface)

> High-Speed Interface For Connecting Data-Hungry Peripherals To Microcontrollers

*SPI* (*Serial Peripheral Interface*) is a **synchronous** serial communication protocol used for **short-distance** communication between microcontrollers and peripheral devices, such as sensors and displays. 

It typically requires four *GPIOs* (bidirectional communication), but this can sometimes be reduced to three *GPIOs* (in one-directional communication, i.e. *microcontroller* to *display*).

*Displays* (and similar peripherals) may on the other hand need *more than four GPIOs* to be connected: they often require an additional *Reset Line (RST)* (to reset the display to a known state), and a *Data/Command (DC) Line*, to distinguish between *screen content* (pixel information) and commands (control instructions) for the screen. 

Both *RST* and *DC* are not really part of *SPI* though. More accurately, connecting displays often requires *SPI* **plus** display-specific lines such as *RST* and *DC*.

> [!TIP]
> **SPI** is always used when *large amounts of data* need to be transferred *fast*. The much simpler [I2C](https://done.land/fundamentals/interface/i2c) interface is often used when *much smaller amounts of data need to be transferred, i.e. a temperature reading, because [I2C](https://done.land/fundamentals/interface/i2c) is much slower than **SPI**.

## Overview

*SPI* uses *three* or *four* wires to transfer data with a maximum speed of up to *80MBit/s*. 

### Master And Slave(s)

*SPI* uses a *Master/Slave* paradigm: one *master* (i.e. the microcontroller) communicates with a number of *slaves* (i.e. *sensors*, *displays*, and other peripherals conntected to the microcontroller).

The *master* is always generating the *clock signal*.

#### Dedicated Chip Select Lines
A dedicated *chip select* line from *master* to *each client* is used to *select* the *slave* that the master wants to contact. In **SPI**, *slaves* are selected via *hardware* (*CS* is pulled physically *low* to enable communication with a particular *slave*). In [I2C](https://done.land/fundamentals/interface/i2c), on the contrary, each device has its own unique *address*.

#### High GPIO Cost
*SPI* does not scale well with the number of *slaves*: each additional *slave* requires its own *CS* line, and each additional *CS* line requires an additional *GPIO* at the *master*.

The true *hardware cost* on the *master side* is *three GPIO* to support *SPI* plus *one additional GPIO **per slave***.

> [!TIP]
> This cost can be alleviated by using more efficient solutions such as a *multiplexer* (like the one below) that requires just one *GPIO* and can *select **one** out of a large number* of output pins.



<img src="images/hp4067_multiplexer_top_t.png" width="60%" height="60%" />



#### Daisy-Chain Method
*Daisy chaining* the *Chip Select (CS)* lines is a *proprietary method* in certain use cases with a high number of *slaves*: it can share the *CS* line while still being individually addressable. 

In essence, this approach implements *device addresses* (that normally do not exist in *SPI*) and makes *SPI* behave similar to *device address-enabled interfaces* such as [I2C](https://done.land/fundamentals/interface/i2c). Since *SPI* does not natively support this, it must be implemented by all devices as part of *proprietary solutions*.

In a nutshell, typical *SPI* devices require *individual CS lines* and do not have built-in *addresses* nor do they support *address selection*.



### Flexible Speed

*SPI* is *clock-based*, so the actual data transfer speed can be adjusted and depends on the *clock speed*. *ESP32* is capable of using clock speeds of up to *80MHz*. 

Slower microcontrollers or peripherals can negotiate and reduce the clock speed to any frequency that is needed or supported. This limits the data transfer rate while at the same time increasing the robustness of data transfer which can also be helpful in rough and noisy environments.

### Short Distance

SPI connections are designed for **short-distance communication** within a circuit board or between closely located components, typically *within* one device. Connections are typically just a few centimeters long.

> [!TIP]
> While *SPI* was not designed to be used over longer distances (and there are much better suited other interfaces and protocols like *Ethernet*), longer *SPI connections* can be used by *lowering the data rate*, *using better wires*, and *adding shielding*.



## Pins
*SPI* requires a minimum of *three* or *four* wires.

> [!TIP]
> Due to increased *sensitivity* in society, terms like *master* and *slave* have become controversial, even in microelectronics. That's why *pin labels* that were introduced in the *1980s* may be *renamed* in new devices: *Master Out Slave In (MOSI)* for example is now also known as *Serial Data In (SDI)*. You'll find all commonly used pin labels listed below.






### Four-Wire
The *four-wire* connection is the *default SPI setup* and enables true *full duplex communication*:



| Pin | Common Labels | Description |
| --- | --- | --- |
| Clock | CLK, SCL, SCLK | signal sent by *master* to synchronize data and set the data trasfer speed |
| Chip Select | CS, SS | signal used by *master* to select a *slave* |
| Master Out Slave In | MOSI, SDO, SDA | Data sent by master |
| Master In Slave Out | MISO, SDI | Data received by master |

> [!TIP]
> If you come across a pin **DC**, then this is not part of **SPI**. A *Data/Command (DC)* pin is used by *displays* (*low* for command, *high* for data) to distinguish between *screen content* and *device commands*.





### Three-Wire
*Three-wire* (aka *Single-Wire SPI* or *Reduced Pin SPI*) is used in scenarios where the number of *wires* and *GPIOs* are limited, or where data primarily travels in **one direction only** (like with *displays*).

In essence, the *three wire* setup combines the dedicated *MOSI* (*Master Out Slave In*) and *MISO* (*Master In Slave Out*) lines in one single *data* line (often called *SDIO*). In *three-wire* setups, you are loosing *full duplex* capabilities: *data* can no longer be transmitted in both directions *at the same time*.



## Data Communication
Data communication over *SPI* follows these steps:

1. **Clock Signal:** Master starts sending a *clock signal*, setting the data speed.
2. **Slave Select:** Master *selects* the *slave device* it wants to communicate with by pulling this line *low*. The *slave device* with the *low CS line* starts listening.
3. **Sending Data:** *Master* can now send data via *MOSI* to the *slave*. The *slave* can send back data *at the same time* via *MISO*.
4. **Closing Connection:** Once the *master* sets back the *CS* signal to *high*, the *slave* stops listening, and the communication ends.  




> Tags: Interface, SPI, CLK, SCL, SCLK, SS, DC, MOSI, MISO, SDO, SDI, SDA

[Visit Page on Website](https://done.land/fundamentals/interface/spi?090695051108241158) - created 2024-05-07 - last edited 2024-10-16
