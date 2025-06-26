<img src="/assets/images/lightning.png" width="100%" height="100%" />

# USB (Universal Serial Bus) 

> Clever Analog And Digital Power Supply System

Consumers know *USB* from a plethora of devices: it is used to supply *power* from chargers and power banks to devices, and it can also transport *data*.

Once you start examining *USB* closer, you'll discover that it has evolved to become a highly sophisticated power management system that can be used in many DIY projects. It can often replace cumbersome buck and boost converters, and it can even challenge traditional lab bench power supplies.

## Overview
The **Universal Serial Bus (USB)** is an industry standard that defines cables, connectors, and protocols used for 

* connection
* communication
* power supply

between computers and electronic devices. 

### Roots
Introduced in the mid-1990s by a consortium of companies, USB was designed to standardize and simplify the way peripherals such as keyboards, mice, printers, and storage devices connect to computers. The goal was to replace a variety of older, less user-friendly, and incompatible standards:

* **Data:**     
  USB today replaces proprietary interfaces like serial and parallel ports
* **Power:**   
  USB today replaces proprietary chargers and plugs and provides a solution to charge and power a variety of devices with a variety of voltages and currents

### Using as Power Supply
  
Even though USB was initially focusing on data exchange, with the availability of wireless data transmission, today USB is often used primarily as a power supply, i.e. to charge smartphones, flashlights and most other battery-driven devices.

Over the years, *USB* has transitioned from a simple *5V 2.5W* power supply for low-power devices to a digitally-controlled power management system capable of delivering almost arbitrary voltages in a range from *3.3-48V* at powers of up to *240 watts*.

| USB Version / Spec           | Year      | Max Power Output    | Key Power Features                                                                    | Typical USB Connectors           | Delivered Voltages (Range & Steps)                   | Negotiation Protocol                   |
|------------------------------|-----------|---------------------|---------------------------------------------------------------------------------------|----------------------------------|------------------------------------------------------|----------------------------------------|
| USB 1.0 / 1.1                | 1996-1998 | 2.5W (5V, 0.5A)     | Low-power devices                                                                     | USB-A, USB-B, Mini-USB           | 5V (fixed)                                           | none                    |
| USB 2.0                      | 2000      | 2.5W (5V, 0.5A)     | Same power as 1.1; higher data rate                                                   | USB-A, USB-B, Mini-USB, Micro-USB| 5V (fixed)                                           | none                   |
| USB 3.0 / 3.1 Gen 1          | 2008-2013 | 4.5W (5V, 0.9A)     | Slightly higher current for more demanding devices                                    | USB-A, USB-B, Micro-B, USB-C     | 5V (fixed)                                           | none                  |
| USB BC 1.2 (Battery Charging)| 2010      | 7.5W (5V, 1.5A)     | Faster charging for phones, tablets                                                   | USB-A, USB-B, Micro-USB          | 5V (fixed)                                           | Analog (D+/D- shorting & detection)    |
| USB PD 1.0 (Power Delivery)  | 2012      | 60W (20V, 3A)      | Introduces **negotiated voltage steps** to support high-power devices (like laptops)  | typically USB-C | 5V, 9V, 15V, 20V       | Digital (USB PD protocol over CC line) |
| QC 3.0 (Quick Charge)        | 2015      | Up to 36W (20V, 1.8A)| Introduces **adjustable voltage** in *200mV* steps   | USB-A, Micro-USB, USB-C    | 5V, 9V, 12V, 20V; 3.6V–20V (*200mV* steps, often the upper voltage range limited to *12V* by chargers)             | Digital (D+/D- pulse signaling, INOV)  |
| USB PD 3.0                   | 2015      | 100W (20V, 5A)      | Introduces support for **e-marker cables** that can actively advertise their capabilities, raising power to *100W* with safe cables     | USB-C                            | 5V, 9V, 15V, 20V (fixed steps)                       | Digital (USB PD protocol over CC line) |
| USB PD 3.0 PPS (Programmable Power Supply) | 2015 | 100W (20V, 5A) | Introduces **programmable current** in addition to programmable voltage (current programmable in *50mA* steps).                                        | USB-C                            | 5V, 9V, 15V, 20V; PPS: 3.3–21V (*20mV* steps)          | Digital (USB PD protocol over CC line) |
| USB PD 3.1 (Standard Power Range) | 2021 | 100W (20V, 5A)      | Basic family member of the PD 3.1 family that remains backwards compatible with PD 3.0     | USB-C                            | 5V, 9V, 15V, 20V; PPS: 3.3–21V (*20mV* steps)          | Digital (USB PD protocol over CC line) |
| USB PD 3.1 EPR (Extended Power Range) | 2021 | 240W (48V, 5A)     | Introduces support for up to **48V**/**240W** required for powering high-demand devices    | USB-C (EPR-certified cable)      | 5V, 9V, 15V, 20V, 28V, 36V, 48V (fixed steps)        | Digital (USB PD protocol over CC line) |
| USB PD 3.1 AVS (Adjustable Voltage Supply) | 2021 | 240W (48V, 5A)    | Optional feature in *EPR* that introduces **adjustable voltage 15V–48V** in *100mV* steps. The real upper voltage limit is determined by charger capabilities. **Programmable current feature is dropped in this mode (CV only)**     | USB-C (EPR-certified cable)      | 15V–28/36/48V (upper limit depending on charger, *100mV* steps)| Digital (USB PD protocol over CC line) |

> **Note:**  
> Key changes were introduced starting in *2015* when voltages became *negotiable* with USB Power Delivery, enabling higher currents and support for much more power-demanding devices (like laptops).
>
> At the same time, *PD 3.0* marked the inflection point where protocol emulation with generic MCUs became impractical due to the introduction of BMC (*Biphase Mark Coding* signaling), PPS (Programmable Power Supply), and cryptographic requirements. PD 3.1 (2021) and later (e.g., EPR/AVS) further increased complexity with higher voltage/current limits and stricter timing, solidifying the need for dedicated PD controllers (e.g., STM32 UCPD, TI TCPP).
>
> *QC3* remains the only widely used specification supporting freely definable voltages (in *200mV* increments) that can be easily emulated (triggered) by simple MCUs like *Arduino* or *ESP32*. Any specification beyond *QC3* requires specialized *trigger chips* or *I2C-enabled helper ICs* that handle the complex protocol requirements.


### Using for Data Exchange

Data exchange over wires (instead of wireless) is still an issue when performance like speed is an issue. USB has evolved tremendously over the years, raising the data transfer speed from *12 Mbps* in *USB 1.0* to *40 Gbps* in *USB4* (more than *3000x* faster).

| USB Version   | Year     | Max Speed         | Key Features                                      |
|---------------|----------|-------------------|---------------------------------------------------|
| USB 1.0       | 1996     | 1.5 Mbps, 12 Mbps | First standard, plug-and-play, low/full speed      |
| USB 1.1       | 1998     | 12 Mbps           | Improved reliability and compatibility             |
| USB 2.0       | 2000     | 480 Mbps          | High speed, bus power, mass adoption               |
| USB 3.0       | 2008     | 5 Gbps            | SuperSpeed, dual-bus, improved power management    |
| USB 3.1       | 2013     | 10 Gbps           | SuperSpeed+, reversible Type-C connector           |
| USB 3.2       | 2017     | 20 Gbps           | Multi-lane operation, Type-C standardization       |
| USB4          | 2019     | 40 Gbps           | Thunderbolt 3 integration, multi-protocol support  |


### General Principles

Here are a few general USB concepts you should be familiar with.

#### Power Delivery

In power delivery scenarios, devices are categorized as **source** (delivering power, i.e. a power bank or charger), and **sink** (consuming power, i.e. a smartphone, MCU, laptop).

In modern USB versions, *source* and *sink* actively **negotiate** the best voltage and current requirements. *USB cables* with **e-markers** (specialized chips) contribute to the negotiation: only when the cable(s) indicate that they are capable of handling high currents will the *source* actually deliver them. Unmarked cabled trigger low-power modes (and can i.e. slow down charging).

A special challenge are devices that can act both as *source* and *sink*, i.e. a powerbank (and sometimes even a laptop): they can *supply* power, but they can also *be charged* (*consuming* power).

When such devices are connected, part of the negotiation is to figure out which device takes on the role *source*, and which is acting as *sink*. If this negotiation fails, malfunction or even damages can occur.

#### Data Transmission

For data transmission, USB is a host-centric, asymmetric architecture. The host (typically a computer) manages communication, while peripheral devices (such as flash drives or cameras) connect through USB ports. 

Devices can be connected in a star topology, often using hubs to expand the number of available ports. The interface supports "hot swapping," meaning devices can be plugged or unplugged while the system is powered on, and "plug and play," so most devices work automatically without manual configuration.

> Tags: Voltage, Current, USB, PD, Power Delivery, QC


