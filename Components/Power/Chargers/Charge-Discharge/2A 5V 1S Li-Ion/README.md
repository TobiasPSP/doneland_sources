<img src="/assets/images/charging.png" width="100%" height="100%" />
# 2A 5V From 1S Li-Ion Battery

> 2A 5V Power Supply Driven By A Single Li-Ion Cell

This is a compact module designed to work with a single (1S) Li-Ion cell. 

It features a *USB-C* connector that functions as both a power input and output, with the option to install an additional *USB-A* connector.

The module charges the battery at a maximum rate of *2.4A* and can supply *5V* at up to *2A* (10W) to USB devices or any other 5V-powered loads, such as microcontroller development boards.

With minimal effort, you can use this module to create a simple power bank or add battery support to portable microcontroller projects.

> [!IMPORTANT]
> Keep in mind the relatively high charging current (*2.4A*). This typically requires batteries with a minimum capacity of *2500mAh*. Using smaller batteries may lead to overcharging and potential damage.

## Overview
This module includes everything needed to charge a *1S Li-Ion Cell* via *USB-C*, and to supply up to *2A* of battery power to devices connected to the *USB-C* port or the *5V* solder pads. It also supports discharging while the battery is charging.

A *USB-C* connector is pre-soldered to the PCB, and there is an option to install a *USB-A* connector on the opposite side.

Four SMD LEDs indicate the charging status and state of charge.

| Item | Description |
| --- | --- |
| Input Voltage | *5-5.5V* (USB) |
| Output Voltage | *5-5.15V* |
| Output Voltage Ripple | *100mV* |
| Charging Current (Input) | *2.4A* |
| Supply Current (Output) | *2A* |
| Charging Cut-Off Voltage | *4.2-4.35V* |
| Conversion Efficiency | *92.5%* |
| Standby Current (Battery) | <30uA |

The PCB also supports an external push button, which can be used to turn the device on or off.

## Output Mode
In output mode, the module provides *5V* at up to *2A*. Power is automatically cut off when the battery voltage drops below *2.95V* (over-discharge protection). 

There are two ways to trigger output mode: *automatic* and *manual*.

### Automatic Mode
In automatic mode, power is supplied when a load is connected to the *USB-C* connector or the *5V* solder pads. If the load current drops below *50mA*, the module will automatically enter standby mode.

### Manual Mode
In manual mode, a push button connected to the solder pad labeled *K* (and the other end to *GND*) controls power:

* **Short Press:** Turns on power supply continuously.
* **Two Short Presses:** Turns off power supply.

## Charging Mode
The charger automatically activates when a power supply is connected to the *USB-C* port. It charges the battery with a maximum current of *2.4A*.

* **Low Voltage Protection:** When the battery voltage is below *2.8V*, the battery is pre-charged at *180mA* until it reaches a safe voltage.
* **Charge Completed:** Charging stops once the current drops to *100mA* at floating voltage.
* **Automatic Recharge:** A new charging cycle starts when the battery voltage drops below *4.1V*.


> Tags: Charger, Li-Ion, LiIon, Li-Po, LiPo, Boost Converter, 2A, USB, 1S

