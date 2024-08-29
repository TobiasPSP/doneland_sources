<img src="/assets/images/interface.png" width="80%" height="80%" />
 
# I2C 

> Connects Components To Microcontrollers Inside Devices

*I2C* (*Inter-Integrated Circuit*, aka *IIC*, Speak: *Eye-Squared-See*) is a synchronous bus system invented 1982 by *Philips*. Today, it is widely used to connect *components* to *microcontrollers* inside devices.

Since *I2C* is relatively slow, for components requiring higher data rates (such as color displays), [SPI](https://done.land/fundamentals/interface/spi) is used.

## Quick Overview

[I2C](materials/um10204_i2c.pdf) is a bus that is used to inter-connect components *inside a device* and over a short distance. 

Here are its key benefits:

* **GPIOs:** requires just *two GPIOs* to connect up to 127 devices (*SDA* and *SCL*)
* **Device Address:** every device on the bus has a unique predefined *address*

And these are the most important limitations:

* **Speed:** in *standard mode*, speed is *100 kbit/s*. There are faster modes (*400 kbit/s*, *1/3.4/5 MBit/s*) that are not supported by all devices.
* **Noise:** Its high impedance and low noise immunity require a *common ground* and short distances.
* **Address:** Since addresses are often not fully configurable or even fixed, the already small 7-bit address space is further limited,effectively preventing the use of multiple components of the same kind (i.e. multi-display use cases). 

*Buffers* and *multiplexers* can stretch the limits of *I2C*. Most of the time, switchting to a *different bus system* that is suited for the task (i.e. *SPI*) is a better approach.

## I2C Address

*I2C* uses a 7-bit address to uniquely address invididual devices. Theoretically, this provides *127* unique device addresses. 

Realistically, most components have *fixed addresses* or just a small number of selectable addresses. So the number of *I2C devices* on an *I2C* bus is much lower.

### Hex vs. Binary vs. Decimal

*I2C addresses* can be specified in different formats.

* in *binary format*, the *address bits* are specified, i.e. `1000000`. The true address is defined by *two 4-bit values*: `0100 0000`. In this example, these would be the numbers `4` and `0`, resulting in the *I2C address* `40`.
* in *hexadecimal format*, the address is specified as `0x40`
* in *decimal format*, the hexadecimal address is converted to the decimal system: `0x40` can also be expressed as `60`.

The most commonly used format are *hexadecimal addresses*.


## Materials

[I2C User Guide](materials/um10204_i2c.pdf)

> Tags: I2C, Address

[Visit Page on Website](https://done.land/fundamentals/interface/i2c?007365071608243322) - created 2024-07-07 - last edited 2024-07-07
