<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Connectors

> Using Standard Cable Connectors Instead of Soldering

While soldering wires directly is an option, *standard connectors* are often used for modularity and serviceability. For instance, if you solder a display directly to a microcontroller board, replacing or reusing either part later becomes much more difficult.

Connectors not only save time during assembly but also make devices safer and easier to debug, repair, or upgrade, especially for beginners.

## Overview

In DIY projects, unless you are mass-producing thoroughly designed devices, you need *modularity* and the ability to quickly change or replace components. Connectors are essential for achieving this flexibility.

Connectors allow you to easily *disconnect* or *replace* components (e.g., displays or sensors) during debugging, testing, or when reusing parts for new projects. The type of connector you use depends on the project phase:

- **Prototyping:** For initial experiments and testing, use reconfigurable connectors like *header pins*, *banana plugs*, or *alligator clips*. These are inexpensive, easy to use, and reusable.
- **Evaluation:** As your design matures, choose more reliable connectors. For example, *JST* connectors are compact and secure, while *XT60* connectors are sturdy and ideal for power connections. These connectors are slightly more expensive but improve durability and reliability.
- **Production:** For mass production, you might forgo connectors altogether, opting for soldered wires or designing a PCB that consolidates connections with traces.

## Poor Man's Connectors

For basic *prototyping*, two common single-wire connector types are used:

- **Data:** *Header pins* and *DuPont connectors* are highly cost-effective and flexible, ideal for breadboards and development kits. They are simple and widely compatible, but they are not shielded and cannot handle large currents.
- **Power:** *Banana plugs* offer a large contact area, making them suitable for supplying power to devices requiring more than a few hundred milliamps. They are commonly used with bench power supplies and lab setups.

These connectors are convenient but have significant limitations:

1. **No Lock:** They lack mechanical locks, making them prone to accidental disconnections caused by vibrations or pulling.
2. **No Guidance:** Each wire is connected individually, with no mechanism to ensure correct wiring order or polarity.

As a result, these connectors are best suited for temporary setups during prototyping or experimentation in controlled environments.

## Generic Connectors

Below are some commonly used generic connectors suitable for cost-effective test devices.

### Barrel Connectors

Barrel connectors are a type of *DC power connector* widely used for power input. They have a cylindrical shape with a central pin for the positive connection. 

Common sizes include:

- **5.5 mm outer diameter / 2.1 mm inner diameter**
- **5.5 mm outer diameter / 2.5 mm inner diameter**

By convention, the outer sleeve serves as ground (negative), and the central pin serves as positive. However, mismatched sizes can result in loose or unreliable connections. 

**Tips for ensuring compatibility:**

1. **Buy as a set:** Purchase matching jacks and plugs from the same vendor to avoid mismatches.
2. **Size testing:** Use simple tools to identify jack sizes:
   - Insert a *toothpick* (2.1–2.2 mm). If it fits snugly, it’s a *2.1 mm* jack.
   - Insert a *standard ballpoint pen refill* (2.25–2.35 mm). If it fits, it’s a *2.5 mm* jack.

### Screw Terminal Connectors

Screw terminal blocks are ideal for higher-current, *permanent* connections such as power supplies. They secure wires with a clamping screw, creating a reliable connection.

**Key considerations:**

- Choose a terminal block designed for your wire gauge. If the wire is too thin, it may not clamp securely.
- Avoid using screw terminals in environments with high vibration, as the screws can loosen over time.

**Tips for secure connections:**

- Strip the wire insulation carefully to avoid damaging the strands.
- After stripping, either tin the wire ends with solder or use crimped wire ferrules to ensure a firm, durable connection.

## Environmental Factors

When choosing connectors, consider the operating environment:

- **Moisture:** Opt for sealed or waterproof connectors in damp conditions.
- **Vibration:** Use connectors with locks or latches to prevent accidental disconnections.
- **Temperature:** Ensure the connector materials can handle the operating temperature range without deforming or losing integrity.

Adding the right connectors to your project ensures better reliability, easier debugging, and the ability to reuse components in future designs.


### JST Connectors

The company [JST](https://www.jst.com/) specializes in designing and producing proprietary connectors. Due to the many formats and families, *JST* connectors have become highly popular in DIY. There are many very affordable knock-offs and *clones*, some of which even establishing theor own specifications. 

The *JST-XH* connector, for example, originally targeted a *2.5"* pitch only, rendering it largely unusable for the typical *2.54"* (*1 Inch*) pitch found in many PCBs and breakout boards. Many Chinese suppliers now sell *adjusted JST-XH* versions with a native *2.54"* pitch. Here is an overview of some of the *JST* connector families:

| JST Connector Type | Available Pitches (mm) | Current (A)    |  AWG (Wire Gauge)   | Description                                                                 |
|--------------------|------------------------|----------------|---------------------|-----------------------------------------------------------------------------|
| **EH**             | 2.5                    |  3             |  22-32              | medium-current applications, i.e. balancers |
| **GH**             | 1.25                   |  1             |  26-30              | Small pitch, low-profile for compact, lightweight connections     |
| **PA**             | 2.0                    |  3             |  22-28              | Similar to XA, for higher-current or power connections         |
| **PH**             | 1.25, 2.0              |  2             |  24-32              | general-purpose, low-power connections |
| **RE**             | 2.54                   |  2             |  24                 | Similar to DuPont, connects to header pins |
| **SH**             | 1.0                    |  1             |  28                 | QWIIC and I2C-based connectors |
| **SM**             | 2.0                    |  3             |  22                 | often used for LED strips |
| **VH**             | 3.96                   |  7-10          |  16-18              | higher-current applications |
| **XA**             | 3.96                   |  3             |  20-28              | Large pitch, automotive or high-current connections           |
| **XH**             | 2.50                   |  3             |  22                 | often (ab)used for *2.54"* pitch with 2-pin connectors, clones in real *2.54"* pitch exist |

In DIY, *JST-RE*, *JST-SH*, *JST-PH*, and *JST-XH* are the most popular and widely used families. All connectors come with varying pin numbers and support different wire gauges.

#### QWIIC Connectors

*QWIIC connector* is a brand name for a 4-pin *JST SH 1.0* connector, introduced by the company [SparkFun](https://www.sparkfun.com/qwiic). *QWIIC* connectors - aka *4-pin JST-SH 1.0* - are used to connect microcontroller boards and peripherals such as sensors via *I2C*. 

You can use the *QWIIK* connectors manufactured by *SparkFun*, or regular *JST-SH 1.0* connectors with 4 pins interchangeably.

### XT60 Connectors

For high power demands up to *60A*, *XT60* connectors are popular. For example, high-current battery connections in RC vehicles, drones, and other battery-powered devices often use *XT60*. 

They use large gold-plated solder contacts for *10-12AWG* cables and are rated for up to *60A* (the attached cables being typically the true limiting factor).

### Lemo Connectors

Lemo connectors are highly durable and provide secure, high-performance connections for precision applications. They can handle high voltages and currents and are often used in professional audio, video, and medical devices due to their ruggedness and locking mechanisms. Lemo connectors are very pricey.

### Molex Connectors

Molex is a well-known manufacturer of connectors, and their connectors are often used in both consumer and industrial electronics. Some common types are:

* **Mini-Fit Jr.**: These are popular in power applications (up to 13A per pin), with a pitch of 4.2mm. They are used in power supplies, computers, and other equipment that requires higher current.
* **Micro-Fit 3.0**: Smaller than the Mini-Fit Jr., but still capable of handling up to 5A per pin. The pitch is 3.0mm, and these connectors are often used in compact devices like small appliances and automotive electronics.

### Anderson Powerpole Connectors

Anderson Powerpole connectors are often used in power distribution systems for DIY electronics, especially for high-current applications. They come in modular, stackable designs, which can be easily connected to one another. These connectors are widely used in hobbyist electronics, amateur radio, and power systems.

* **High Power**: Rated for current up to 15A to 45A, depending on the configuration and size of the connector.

### IDC (Insulation Displacement Connectors)

IDC connectors are used for ribbon cables and are very popular in applications where many signals need to be connected simultaneously. They have a simple design, where a metal blade pushes through the insulation of the wire and makes a connection with the conductor inside.

* **Common Use**: Often used for connecting flat, multi-wire cables in devices like hard drives, printers, and other consumer electronics.

### USB Connectors

USB connectors are widely used in both consumer and DIY electronics for data and power connections. Some of the most common types are:

* **USB-A**: The most commonly recognized type of USB connector, typically used for connections to computers or chargers. 
* **USB-B**: Often used in devices like printers, scanners, or external drives.
* **Micro USB**: A smaller version of USB-B, used in older smartphones, power banks, and smaller devices.
* **USB-C**: The newer, reversible connector used for both power and data, supporting higher data transfer rates and power delivery.



> Tags: Connector, USB, JST, Molex, Anderson, IDCQWIIK, Lemo, Plug, Screw Terminal, Barrel Connector, Banana Plug, DuPont, Header, Current, AWG

[Visit Page on Website](https://done.land/components/power/cables/connectors?679035011321252314) - created 2025-01-20 - last edited 2025-01-20
