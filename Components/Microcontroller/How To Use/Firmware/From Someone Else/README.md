<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Firmware From Someone Else

> Uploading Pre-Made Firmware To Your Microcontroller

You don't necessarily need to be a *programmer* to play with *microcontrollers*. Simply grab some *pre-made* firmware from someone else, and use it on your microcontroller - done!

For example, grab an affordable *ESP32 microcontroller board* and a cheap *8x8 WS2812 LED matrix panel*, and upload the awesome *WLED firmware* to your microcontroller - right from within your browser.

With just three wires and very limited soldering expertise, you can create this color cube with a rich list of selectable light effects:

<img src="images/wled_battery_cube_overview_t.png" width="60%" height="60%" />

All required parts cost less than €10 in total, and the project takes just a few minutes:

[Here is everything you need to build your own color cube](https://done.land/components/microcontroller/howtouse/firmware/fromsomeoneelse/wled).

## Overview

Using *firmware* that was made by someone else obviously puts *someone else* in full *control*: the *firmware* you choose does whatever its author *programmed it to do*.

That's not as limiting as it might initially seem:

- **Special Purpose Firmware:** Firmware like *WLED* is *highly specific* and controls *LED strips*. The author added a wireless interface accessible from your smartphone, plus so many options and features that you can tailor the firmware completely to your needs. Whether you want ambient lighting, a flashing emergency light, or intricate LED strip control, pre-defined firmware allows your microcontroller to handle these tasks without requiring you to write any code.

- **Adjustable Firmware:** Firmware like *ESPEasy* and [EspHome](https://done.land/tools/software/esphome/introduction/) takes care of all the complex aspects, such as implementing a *web interface* or enabling *over-the-air updates* (*OTA*). This type of firmware isn't tailored to a single purpose. Instead, it offers customizable options through graphical interfaces or configuration files (e.g., YAML). This flexibility enables you to create *specific solutions* without directly writing *C++* code.

- **Interpreters:** If you're interested in programming but find *C++* too complex, consider using an *Interpreter firmware*. These firmwares allow you to program your microcontroller using higher-level scripting languages such as *LUA*, *Basic*, *Python*, or *JavaScript*. The interpreter handles the translation of your script into the *assembly language* that the microcontroller understands, simplifying the process.

### Uploading New Firmware

Uploading existing firmware to your microcontroller often only requires a *Chromium*-based browser (as shown in the [WLED project](https://done.land/components/microcontroller/howtouse/firmware/fromsomeoneelse/wled)).

If you already have the binary firmware file, you can also use specialized *flashing tools*. These tools are designed for specific microcontroller types and can be run locally or via websites. For example, the [Adafruit ESPTool](https://adafruit.github.io/Adafruit_WebSerial_ESPTool/) works well for flashing firmware onto *ESP32* microcontrollers.


## Special Purpose Firmware
*Special Purpose Firmware* targets a *highly specific use case*. Within this use case, the firmware let you *customize and tailor* the solution *to your needs* using a variety of *web interfaces* and/or *smartphone apps*. The already mentioned 
[WLED](https://kno.wled.ge/) firmware is an example, and there are many more.


### CO2 Sensor

[CO2 Gadget](https://emariete.com/en/co2-meter-gadget/) turns a *CO2 sensor* into a *smartphone app*. It runs on any *ESP32* microcontroller, and it comes with a web browser-based *firmware flashing tool*.

The hardest part often is finding the correct links: the [authors' web page](https://emariete.com/en/co2-meter-gadget/) is huge and not structured too well. Links to the browser-based firmware uploads can be found somewhere in the middle of it.





<img src="images/co2meter.png" width="100%" height="100%" />

There are different *firmware versions*, targeting *ESP32* microcontrollers with different *displays* attached to them.

> [!CAUTION]
> *Source code* is *hardware neutral*. Once it gets *compiled into a binary* by an *IDE*, it is converted into a *hardware-specific* firmware. This *firmware* can now only be used on the particular hardware (microcontroller board) that was specified during compile time. When you take the shortcut and directly upload *pre-fabricated firmware*, you must be certain that it was indeed made for *your particular microcontroller and board*. Else, the firmware will not run (correctly).

## Special Purpose Firmware

*Special Purpose Firmware* targets a *highly specific use case*. Within this use case, the firmware allows you to *customize and tailor* the solution *to your needs* using various *web interfaces* and/or *smartphone apps*. The already mentioned [WLED](https://kno.wled.ge/) firmware is an example, and there are many more.

### CO2 Sensor

[CO2 Gadget](https://emariete.com/en/co2-meter-gadget/) turns a *CO2 sensor* into a *smartphone app*. It runs on any *ESP32* microcontroller and comes with a web browser-based *firmware flashing tool*.

The most challenging part is often locating the correct links: the [authors' web page](https://emariete.com/en/co2-meter-gadget/) is vast and not very well-structured. Links to the browser-based firmware uploads are somewhere in the middle of it.

<img src="images/co2meter.png" width="100%" height="100%" />

There are different *firmware versions* targeting *ESP32* microcontrollers with different *displays* attached to them.

> [!CAUTION]
> *Source code* is *hardware neutral*. Once it gets *compiled into a binary* by an *IDE*, it is converted into a *hardware-specific* firmware. This *firmware* can only be used on the particular hardware (microcontroller board) that was specified during compile time. If you directly upload *pre-fabricated firmware*, ensure it was made for *your particular microcontroller and board*. Otherwise, the firmware may not run correctly or at all.



## Programmable Firmware

The classic type of *programmable* firmware is *interpreters*. Interpreters can understand *script languages*, allowing users to avoid low-level programming and instead focus on the actions the microcontroller should perform.

An interpreter translates the script instructions submitted by the user into actual machine code executed by the microcontroller.

While interpreters simplify programming, scripts are generally limited, and interpreters introduce overhead that can increase energy consumption and execution time.

To address these limitations, frameworks like [ESPHome](https://done.land/tools/software/esphome/introduction/) have emerged. These frameworks use *configurations* to describe desired states or behaviors. These configurations are then compiled into a binary firmware file.

Unlike interpreters, *ESPHome* produces firmware that runs as efficiently and quickly as if it had been manually programmed in *C++*.



### Interpreters

Most script languages designed for microcontrollers are primarily used in educational environments or to play with microcontrollers. 

Script languages powerful enough to be of interest to the industry typically require full-blown computers (e.g., *Python*, which needs a *PC* or *Raspberry Pi*).

Efforts have been made to create optimized script languages like *MicroPython* that run on small microcontrollers. However, the trend today is toward frameworks like [ESPHome](https://done.land/tools/software/esphome/introduction/), which is just as simple to use as a script language, but much more powerful, producing clean binary firmware files.

For completeness, here's an overview of interpreters commonly used with microcontrollers.

#### LUA

* [Lua (eLUA)](https://eluaproject.net/overview/status/) – *Embedded Lua* is a lightweight implementation of the *Lua* programming language for embedded systems.
* [NodeMCU](https://github.com/nodemcu/nodemcu-firmware) – *NodeMCU* is a project that develops *ESP8266* and *ESP32* microcontroller boards bundled with an adaptation of *eLUA* that is guaranteed to match the hardware. The preinstalled firmware can easily be replaced with any other firmware, including custom firmware you write yourself if you are interested in the *hardware board* but not in *Lua*.

#### Python

* [MicroPython](https://github.com/micropython/micropython/) – The *MicroPython* firmware executes scripts written in *Python 3* and also supports *interactive console operation* (REPL, *read-eval-print loop*). It includes a small subset of the Python standard library and is optimized to run on microcontrollers with limited resources (RAM and storage).
* [CircuitPython](https://learn.adafruit.com/circuitpython-with-esp32-quick-start/installing-circuitpython) – A derivative of *MicroPython*, designed by *Adafruit* to make learning and using Python on microcontrollers simpler. It focuses on ease of use and education.

#### JavaScript

* [Espruino](https://www.espruino.com/Download) – A *JavaScript* interpreter for microcontrollers, allowing you to develop embedded applications using JavaScript with an interactive JavaScript environment.
* [JerryScript](https://github.com/nkolban/jerryscript-esp32) – A lightweight JavaScript engine intended for microcontrollers with constrained resources. It features low memory usage and can run on microcontrollers with less than 64KB of RAM. It supports a subset of the ES5.1 standard.

#### BASIC

* [ESPBasic](https://www.esp8266basic.com/) – A *BASIC* interpreter for ESP8266 microcontrollers. It allows easy and wireless programming.
* [TinyBASIC](https://github.com/slviajero/tinybasic) – A minimalistic version of the *BASIC* programming language, designed for resource-constrained systems.

#### Others

* [Squirrel](https://github.com/EternityForest/Acorns) – A high-level scripting language, somewhat inspired by Lua, designed to be lightweight and embeddable, with an object-oriented approach.
* [TinyGo](https://tinygo.org/) – A *Go* compiler that translates *Go* code into machine code, enabling it to run on microcontrollers.
* [WASM3](https://github.com/wasm3/wasm3) – A *WebAssembly* interpreter designed for small devices and microcontrollers that can run WebAssembly bytecode on microcontrollers.




> Tags: Firmware, Interpreter, NodeMCU, WLED, CO2 Gadget, ESPHome, ZeroCode, LUA, eLUA, Squirrel, TinyGo, WASM3, ESPBasic, TinyBasic, Espruino, JerryScript

[Visit Page on Website](https://done.land/components/microcontroller/howtouse/firmware/fromsomeoneelse?351360051527240132) - created 2024-05-11 - last edited 2024-12-17
