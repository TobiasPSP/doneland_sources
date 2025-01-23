<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# Connecting Displays

> Successfully Connecting Displays To Microcontroller Boards

Getting a new *display* is exciting, but not always purely in a positive sense: each display board may use differently ordered pins, voltages, variations in pin names, different driver chips, and interfaces.

If you did *everything* right, your display works beautifully, however if you do *just one thing* wrong, nothing works. Since connecting a display involves multiple caveats, it is easy to fail without proper documentation and experience.

In this section you learn how to successfully connect your display to a microcontroller board.

## Overview

Most displays use either the two-wire [I2C](https://done.land/fundamentals/interface/i2c/) interface, or the three- or four-wire [SPI](https://done.land/fundamentals/interface/spi/) interface. Other connection types exist, i.e. *parallel interfaces*, but are less common due to their high number of required *GPIOs*.

### Interface

The *interface* is used to control the display content. Typically, a *display board* exposes *one* of these *two* interfaces:

* **I2C:** very simple to use, typically used with small monochrome displays. If you are new to displays, start with affordable and simple monochrome *OLED displays* that use *I2C*.
* **SPI:** used by color displays. Almost all *TFT displays* use *SPI*. *SPI* is faster and can handle the large amounts of data required for large and/or color displays.

### Support Pins

In addition to the basic interface pins, additional pins may be needed, especially with *TFT displays* that almost always use the *SPI* interface:

* **Data/Command:** Often present with displays that use the *SPI* interface. This pin tells the display when the microcontroller is sending control instructions (rather than display content): *data* or *command*.

* **Backlight:** *TFT displays* need an active backlight. It can either be connected directly to an appropriate voltage, or connected to a *GPIO* capable of output. The latter is needed if you want to control the brightness of the backlight. 

* **Reset:** some displays expose a *reset* pin that can be used to *reset* the display controller. This pin needs to be *high* during normal operation.

When adding these pins, it becomes clear that the type of display and interface determines the number of valuable output *GPIOs* that you need to invest.

| Interface | Required GPIOs (output) |
| --- | --- |
| I2C | 2 |
| SPI | 6-7 |

Adding the power cables, a 4-wire SPI display requires 9 wires and 7 *GPIOs*, whereas a simple *I2C* display just requires 4 wires and 2 *GPIOs*.


> Tags: Display, Interface, Connect, I2C, SPI, TFT, OLED

[Visit Page on Website](https://done.land/components/humaninterface/display/usage?091862011323251131) - created 2025-01-22 - last edited 2025-01-22
