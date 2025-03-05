<img src="/assets/images/screenwire.png" width="100%" height="100%" />
# Programming Displays

> Controlling Displays With a Microcontroller

Once you have [connected](https://done.land/components/humaninterface/display/usage/connecting/) a display to your microcontroller, the next step is to *program* it: your firmware needs to instruct the display on what to show.

## Overview

There are two primary approaches to programming firmware for displays:

### 1. **C++ Code**

This method involves writing the source code yourself, which requires basic programming skills. Using traditional development environments like *Arduino IDE* or *PlatformIO*, you:

1. Compose the source code.
2. Compile it into a binary file.
3. Upload the binary to your microcontroller.

These platforms offer libraries and prebuilt modules for most display types, making it accessible even if you’re not an expert programmer.

### 2. **ESPHome**

[ESPHome](https://done.land/tools/software/esphome/) is a modern development environment that does not require programming skills. Instead of writing code, you:

1. Describe the desired behavior and configuration of your components using a simple YAML file.
2. ESPHome generates the source code, compiles it, and uploads it to your microcontroller automatically.


> [!NOTE]
> Both methods come with prebuilt *libraries* and *components* that support a wide variety of displays. This ensures you can get started quickly, whether you prefer a hands-on coding approach or a simplified configuration-based workflow. Even if you choose the programming route, advanced programming knowledge is not required.

## I2C Address

If your display comes with a *I2C* interface, you will need to know the *I2C address* that is assigned to the display.




> Tags: Display, ArduinoIDE, platformio, ESPHome

[Visit Page on Website](https://done.land/components/humaninterface/display/usage/programming?341520011623251850) - created 2025-01-22 - last edited 2025-01-22
