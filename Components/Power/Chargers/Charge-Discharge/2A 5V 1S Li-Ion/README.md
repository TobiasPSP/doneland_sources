<img src="/assets/images/charging.png" width="100%" height="100%" />

# 2A 5V From 1S Li-Ion Battery

> 2A 5V Power Supply Driven By A Single Li-Ion Cell

This is a compact module designed for single (1S) Li-Ion or Li-Po cells (or multiple cells connected in parallel). The module is built around the [IP5306](materials/ip5306_datasheet.pdf) power management chip (or one of its Chinese clones, like the [FM5324GA](materials/fm5324ga_datasheet.pdf)).

## Overview

This *20x25mm* module integrates all necessary components for building power banks, portable chargers, or adding battery support to USB/5V devices. Some versions are labeled *X-150*.

### Separate Input and Output Connectors

The module features **separate connectors** for input and output:

- **USB-C Input:** A pre-soldered *USB-C* connector functions exclusively as the **input**. It cannot supply power to USB devices.
- **USB-A Output:** An optional *USB-A* connector serves exclusively as the **output**, supplying power to USB devices. Alternatively, dedicated *5V solder pads* allow direct power output to a board or microcontroller.

Both connectors operate independently, allowing simultaneous power supply and charging. This is particularly useful for adding battery support to a microcontroller or portable device, as the module can charge the battery while the device remains powered.

> [!IMPORTANT]
> Plugging in or unplugging the *USB-C* cable may cause a brief power interruption, potentially rebooting connected microcontroller boards. Adding a sufficiently large capacitor to the power input can mitigate this issue.

### Supported Batteries

The module is designed for *1S* battery configurations (single cell or parallel cells). It supports both Li-Ion and Li-Po batteries, with a default charging cut-off voltage of *4.2V*. This can be adjusted to *4.35V* by bridging specific PCB contacts.

> [!IMPORTANT]
> The battery is charged at up to *2.4A*. Small batteries may not handle this current. Batteries should have a capacity of at least *2500mAh*. The charging current is fixed and cannot be adjusted.
### Optional Push Button

An optional push button can be connected to the *K* and *GND* solder pads, with a *10kΩ* resistor in series. The button allows manual control of the power supply:

- **Short press (>30ms but <2s):** Turns on indicator LEDs and enables power output.
- **Double short press or long press (>2s):** Turns off indicator LEDs and disables power output.

#### Torch LED and Caveat

A *torch LED* can be connected in parallel to the push button,  using a *100Ω* series resistor. The push button can then turn the LED on and off with a double-short press. The torch LED is designed to use *25mA*.

> [!IMPORTANT]
> The *torch LED* feature explains why it is important to use a *10kΩ* resistor in series with the push button: if you just short circuit the *K* solder pad with *GND*, then the maximum torch LED current (north of *25mA*) would pass through the push button. While this won't hurt the board, it may damage simple logic-level push buttons that can handle only a few *mA*, and might produce some smoke and smells.


### Limitations

The module does not support temperature sensors that could be used to monitor the battery and detect malfunctions. 

It also does not support any *quick charge protocols*: the *USB-C* connector accepts *5V input* only and requires *2A*.

> [!TIP]
> Not supporting *quick charge protocols* is not really a significant limitation considering that this charger stay within the *5V 2A* limits of regular USB.

## Supplying Power

The module provides *5V* at up to *2A* via the *USB-A connector* or *5V solder pads*. The *USB-C connector* is for charging only.

Four SMD LEDs display charging status and battery state of charge in 25% increments.

### Over-Discharge Protection

If the battery charge drops below *3%*, one LED blinks at *1.5Hz*. When the voltage falls below *2.95V*, the module disables the power output to prevent over-discharge.

The module includes additional protections:
- If the output voltage drops below *4.4V* for more than *30ms*, the chip shuts off, assuming over-current.
- If the output current exceeds *4A*, the chip cuts power within *200µs*, protecting against short circuits.

### Automatic Power Output

By default, the module remains in *Off* mode, consuming *<50µA*. 

| Item                  | Description                    |
|-----------------------|--------------------------------|
| Output Voltage        | *5-5.15V* (USB-A, 5V pads)    |
| Output Voltage Ripple | *50mV*                        |
| Output Current        | max. *2.1A*                   |
| Indicator LED Current | *4mA* each                    |
| Off Current           | *<50µA*                       |
| Standby Current       | *<100µA*                      |
| Load Removal Detection| *<45mA* for *32s*             |
| Boost Switching Freq. | *500kHz*                      |
| Boost Efficiency      | *92.5%*                       |
| Short Circuit Prot.   | Yes                           |
| Other Protections     | Over-Current, Over-Voltage    |

In *Off* mode, neither the boost converter nor the LEDs are active. The module monitors the output and enters *Standby* mode when it detects a load exceeding *50mA*. If the load drops below *45mA* for *32 seconds*, it reverts to *Off* mode.

### Manual Mode

Manual mode allows direct control of power supply via the optional push button:

- **Short press:** Manually enters *Standby* mode.
- **Double short press or long press:** Exits *Standby* mode and stops power output.

## Charging Mode

The charger activates automatically when a power supply is connected to the *USB-C* port, charging the battery at up to *2.4A*.

| Item                         | Description                    |
|------------------------------|--------------------------------|
| Input Voltage                | *5-5.5V* (USB-C)              |
| Charging Current (Input)     | *2.4A*                        |
| Charge Switching Freq.       | *750kHz*                      |
| Charging Cut-Off Voltage     | *4.2V* or *4.35V* (config.)   |
| Charging Efficiency          | *91%*                         |
| Battery Reverse Polarity Prot.| No                           |
| Charging While Discharging   | Yes                           |

### Additional Protections

- **Low Voltage Protection:** Pre-charges the battery at *180mA* if voltage falls below *2.8V*.
- **Charge Complete:** Stops charging when current drops to *100mA* at floating voltage.
- **Automatic Recharge:** Restarts charging if battery voltage drops below *4.1V*.
- **Safety Timer:** Stops charging if the process exceeds *24 hours*.

> [!TIP]
> If charging stops prematurely, the charging current may be too high for the battery, causing a temporary voltage increase that triggers an early cut-off.



## Materials

[IP5306 Power Management SoC Datasheet](materials/ip5306_datasheet.pdf)     
[FM5324GA Power Management SoC (Chinese Clone) Datasheet](materials/fm5324ga_datasheet.pdf) (*in Chinese*)  

> Tags: Charger, Li-Ion, LiIon, Li-Po, LiPo, Boost Converter, 2A, USB, 1S, X-150, IP5306, FM5324GA

[Visit Page on Website](https://done.land/components/power/chargers/charge-discharge/2a5v1sli-ion?160929011912250937) - created 2025-01-11 - last edited 2025-01-11
