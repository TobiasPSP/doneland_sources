<img src="/assets/images/screenwire.png" width="100%" height="100%" />
# Connecting Displays

> Successfully Connecting Displays to Microcontroller Boards

Getting a new *display* is exciting, but it can also feel daunting. Display boards often have variations in pin order, voltage requirements, pin naming, driver chips, and communication interfaces. 

If you connect everything correctly, the display works beautifully. However, a single misstep can result in nothing working. Given the multiple caveats involved, successful connection requires proper documentation and some experience.

This section will guide you through the process of connecting a display to a microcontroller board.

## Overview

Most displays use one of two common communication interfaces:

- **[I2C](https://done.land/fundamentals/interface/i2c/):** A two-wire interface.
- **[SPI](https://done.land/fundamentals/interface/spi/):** A three- or four-wire interface.

Less common options include parallel interfaces, which require a large number of GPIO pins, making them less practical for many applications.

### Interface Types

The *interface* controls how the microcontroller communicates with the display. Typically, display boards use one of these two interfaces:

- **I2C:** 
  - Simple to use and ideal for beginners.
  - Often used with small monochrome displays.
  - If you’re new to displays, starting with an affordable monochrome *OLED display* that uses *I2C* is a good choice.
  
- **SPI:**
  - Faster and capable of handling larger amounts of data.
  - Used by most *TFT displays*, which are often color displays.
  - Essential for projects involving large or color-intensive displays.

### Support Pins

In addition to interface pins, many displays require additional support pins, especially *TFT displays* that commonly use the *SPI* interface:

- **Data/Command (D/C):**  
  - Found on most *SPI* displays.  
  - Used to distinguish between control instructions (commands) and display content (data).  

- **Backlight:**  
  - *TFT displays* require an active backlight.  
  - This pin can be connected directly to a voltage source or a GPIO pin if brightness control is desired.

- **Reset:**  
  - Some displays include a reset pin for reinitializing the display controller.  
  - This pin must remain *high* during normal operation.

The type of display and interface determines how many GPIO pins you need to allocate.

| Interface | Required GPIOs (Output) |
|-----------|--------------------------|
| I2C       | 2                        |
| SPI       | 6-7                      |

### Wiring Summary

Including power connections:

- A 4-wire SPI display requires **9 wires** and **7 GPIO pins**.
- A simple *I2C* display requires just **4 wires** and **2 GPIO pins**.

Choosing the right display and understanding its requirements is key to a successful connection.

> Tags: Display, Interface, Connect, I2C, SPI, TFT, OLED

[Visit Page on Website](https://done.land/components/humaninterface/display/usage/connecting?091862011323251131) - created 2025-01-22 - last edited 2025-01-22
