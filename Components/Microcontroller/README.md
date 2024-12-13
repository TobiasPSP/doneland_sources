<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Microcontrollers

> Controlling Your DIY Electronics With Microcontrollers

Microcontrollers have become so affordable that in many cases, it is easier to design circuits using flexible microcontroller programming than relying solely on discrete components.

For example, while you can design LED effects or emergency lights using *flip-flops*, timer ICs, or other discrete components like resistors, transistors, and capacitors, replacing all of these with a single microcontroller is often much more flexible, easier, and more affordable.

> [!TIP]  
> Powerful microcontroller boards with built-in *WiFi* and *Bluetooth*, along with substantial *4MB flash memory*, are available today for under €2. This makes microcontroller projects much more cost-effective compared to implementing the same functionality with discrete components or specialized ICs. As a result, microcontrollers are ubiquitous in low-cost consumer devices like smart plugs, thermometers, and other gadgets.

## Overview

Microcontrollers function like *mini computers* and can be programmed using simple programming or scripting languages. This creates the software that instructs the microcontroller which is called *firmware*.

Creating *firmware* does not necessarily require programming skills. Tools like [ESPHome](https://esphome.io/) allow you to auto-generate firmware based on high-level *configurations* that describe the microcontroller's behavior in abstract terms.

Often, you do not even need to create new firmware at all. Flexible, pre-made *firmwares* already exist for many use cases. For instance, if you want to control *programmable LED strips* (*WS2812*), [WLED](https://kno.wled.ge/) is a powerful and free firmware that can be [uploaded to your microcontroller directly from a browser](https://install.wled.me/) without requiring any tools or prior knowledge.

### GPIOs

At the heart of each microcontroller are its *GPIOs* (*general-purpose input/output*): versatile pins that can act as either inputs or outputs:

- **Output:** Functions like a switch, toggling between *on* and *off*. This allows you to control devices, lights, or other components. Since *GPIOs* are *signal pins* and typically handle only *10-40mA* (depending on the microcontroller), external components like *MOSFETs* or *relays* are often needed to drive higher loads.  

- **Input:**  
  - **Digital inputs** detect *high* (positive voltage) or *low* (ground) states, enabling connection to switches, sensors, or other components.  
  - **Analog inputs** (available on some GPIOs) measure *voltage levels*, useful for components like potentiometers or voltage sensors.  

### Communication
*Input* and *output GPIOs* can also be used for **communication**. This is how microcontrollers connect to external devices like sensors and displays. Communication protocols like [Serial](https://done.land/components/microcontroller/families/esp/espfeatures/serial/), [I2C](https://done.land/fundamentals/interface/i2c/), and [SPI](https://done.land/fundamentals/interface/spi/) function like high-speed "morse code," transferring data back and forth.  

- For **unidirectional communication** (e.g., microcontroller to display), one side serves as the *sender* (using an *output GPIO*), and the other as the *receiver* (using an *input GPIO*).  
- **Bidirectional communication** generally requires at least two GPIOs per device—one for sending (output) and another for receiving (input).  

> [!TIP]  
> A critical factor when selecting a microcontroller board is the number of available *GPIOs*. Ensure the board you choose has enough GPIOs for your project. If you need additional GPIOs, you can use *port extenders*—external modules that add more GPIOs.  
### Wireless

Another form of communication involves wireless protocols like *WiFi* and *Bluetooth*. Modern microcontrollers, such as those in the *ESP32 family*, come equipped with integrated transmitters and receivers, making it easy to connect devices wirelessly. For example, you can control your device via a web interface on your smartphone or integrate it into home automation platforms like [Home Assistant](https://done.land/tools/software/homeassistant/).

Wireless capabilities also enable the upload of new firmware *wirelessly*. This feature, called *OTA* (*over-the-air updates*), is particularly useful when your microcontroller is built into a device. With OTA, you can update the firmware remotely—fixing bugs or adding new features—without needing physical access to the microcontroller board.







<details><summary>Microcontrollers used in Computers and Smartphones</summary><br/>

Here are some microcontrollers used in popular *computers*, *notebooks*, and *smartphones*:

| Microcontroller | Used In |
| --- | --- |
| Intel i3, i5, i7, i9, Xenon | Computers running *Windows* (Microsoft) |
| AMD Ryzen 3, 5, 7, 9, EPYC | Computers running *Windows* (Microsoft) |
| Apple Silicon M1, M1 Pro, M1 Max, M2 | Computers running *MacOs* (Apple) |
| Apple A14, A15, ... Bionic | *Apple* iPhone Smartphones | 
| Qualcom SnapDragon 4xxx, 6xxx, 7xxx, 8xxx | *Android* Smartphones |
| Mediatec Helio, Dimensity | *Android* Smartphones |
| Samsung Exynos | *Android* Smartphones |
| Huawai Kirin | *Android* Smartphones |

These *microcontrollers* are fundamentally no different from the microcontrollers I am discussing in this section, however they are *more powerful* and *harder to use*: after all, they are designed to run full-fledged general-purpose *operating systems*.

In *DIY* projects and to control hardware, *simpler microcontrollers* are used that are much *cheaper* (cost is often below EUR 1.00/piece) and very much easier to program.

</details>

## DIY Microcontrollers

There are thousands of different microcontroller types available, yet in *DIY projects*, only a few microcontroller families are typically used. Sticking to popular microcontroller families for your own DIY projects is wise because they offer a rich community base of sample code, tips, and support.

### Popular Microcontroller Families

- **[Arduino](families/Arduino)**:  
  "Arduino" is an Italian open-source hardware and software company, not a specific microcontroller family. Arduino board designs use a variety of microprocessors and controllers. When this project began in 2005, it was state-of-the-art and made microcontrollers feasible for hobbyists. Today, however, many users still rely on *Arduino boards*, despite their technical obsolescence, higher cost, and lack of crucial features like wireless communications.

- **[ESP](families/ESP)**:  
  Originally, the Chinese manufacturer *Espressif* produced *cheap but powerful* microcontrollers for industrial use with built-in *WiFi communications*. The community adopted the *ESP-01* module with the *ESP8266* microcontroller in 2014, integrating it into the *Arduino* ecosystem. The release of the dual-core *ESP32* in 2015 established it as the de-facto standard for affordable and powerful microcontrollers, outperforming *Arduino boards* in features and price. Subsequent *Espressif* releases have maintained compatibility while adding functionality. *ESP* microcontrollers can use *Arduino* code and libraries, along with thousands of additional libraries and projects designed exclusively for *ESP*, such as [ESPHome](https://esphome.io/) and [WLED](https://kno.wled.ge/).

- **[ATtiny](families/ATtiny)**:  
  These microcontrollers focus on small size (*DIP packages*) and extremely low energy consumption, making them ideal for battery-operated sensors. While functionally limited (e.g., slower speed, fewer GPIOs), their capabilities often suffice for simple automation tasks. However, when evaluated purely on computational power, *ATtiny* microcontrollers are relatively expensive, costing as much as an entry-level *ESP32 C3* (*€1-2*). Their exceptionally low power consumption still makes them a solid choice for specialized, low-computation projects.



### Raspberry Pi

[Raspberry Pi](families/Raspberry) computers also play an important role in DIY projects, though they are not microcontrollers. Instead, *Raspberry Pi* boards are mini-computers comparable to PCs. The latest *Raspberry Pi 5* is fast enough to run a Linux operating system with a graphical user interface.

Compared to traditional PCs, *Raspberry Pis* are more affordable, compact, and energy-efficient, making them a popular choice for running servers, such as [Home Assistant](https://www.home-assistant.io/).


### Mini-PC and Proxmox

For projects requiring more server power than a *Raspberry Pi* can provide, users often turn to *Intel-based Mini-PCs* paired with the free virtualization software [Proxmox](https://www.proxmox.com/en/). This setup enables the running of multiple server instances in parallel, but it comes with added complexity and significantly higher energy consumption, especially when running *24/7*.

> [!TIP]  
> If you **really need to run multiple server instances** or handle high-computation tasks, a *Mini-PC* with virtualization software like *Proxmox* can be a cost-effective solution. However, for simpler use cases like running [Home Assistant](https://done.land/tools/software/homeassistant/), a *Mini-PC* would mostly idle, wasting energy. Given today’s high energy costs and environmental concerns, a *Raspberry Pi 5* is often the most economical choice for many scenarios.



### Conclusions

- **Microcontroller Selection**: Choosing a microcontroller family with a strong community (e.g., *ESP* or *Arduino*) ensures access to extensive resources, making troubleshooting and development much easier.
- **Cost-Effectiveness**: While *Arduino* remains popular, modern microcontrollers like the *ESP32* often provide better performance and features at a fraction of the cost.
- **Energy Efficiency**: For low-power or battery-powered projects, consider microcontrollers like *ATtiny*. For servers or always-on devices, weigh the energy usage of solutions like *Raspberry Pi* versus Mini-PCs carefully.
- **Scalability**: If you anticipate needing advanced features like virtualization, start with a *Raspberry Pi* but plan for potential migration to a *Mini-PC* or *Proxmox* solution.




## Development Boards
Development boards are *ready-to-use* PCBs that integrate a *microcontroller* with essential components such as a *voltage regulator* and a *Serial-to-USB bridge*. They simplify the process of working with microcontrollers by providing an accessible platform for programming and development.

---

### Originals and Clones

While the *microcontroller* itself is manufactured by specific companies (e.g., Espressif or Atmel), *development boards* are produced by various vendors. These include well-known brands like *Arduino*, *Adafruit*, or *Espressif*, as well as less-known manufacturers who create *clones*. 

#### Key Differences Between Originals and Clones

- **Originals**: Designed and built by reputable companies, offering high-quality components and support.
- **Clones**: Functionally equivalent to originals but manufactured by third parties, often at a much lower price.


<img src="images/clones2_t.png" width="80%" height="80%" />

*Clones* are usually *much cheaper* than originals, especially for *Arduino* boards.




> [!NOTE]  
> *Clones* in this context are not about *piracy* or *deception*. These boards replicate functionality but not *appearance*. You can easily differentiate between an *original* board and a *clone*. Since the hardware designs are *open source*, creating clones is neither *copyright infringement* nor unethical.


### Quality of Clones

The quality of *clones* varies significantly depending on the manufacturer. While some are well-built and even offer added features (e.g., integrated displays), others use cost-saving measures that may affect reliability. Here are some common issues:

| **Issue**               | **Symptom**                                      | **Remarks**                                                                                      |
|--------------------------|--------------------------------------------------|--------------------------------------------------------------------------------------------------|
| Cheap voltage regulator  | Board reboots or stops working with multiple connected components | A known issue with early *ESP8266* boards; most newer boards have improved.                     |
| Soldering issues         | Short circuits due to solder drops              | Rare (1 in 100), related to low-quality control in mass production. Usually evident at first use. |
| PCB quality              | Hard-to-read labels                              | Does not affect functionality but may indicate lower-cost production.                           |

> **Tip**: Consider the cost of *ten units* when comparing prices between originals and clones. For large-scale DIY projects, clones may offer significant savings.

---

### Ethical Considerations

#### Is Buying Clones Morally Reprehensible?

Some wonder if purchasing *clones* undermines intellectual property or takes advantage of others' efforts. However:

- The *microcontroller chip* itself is always original and purchased legitimately.
- Circuit designs for development boards are typically *open source*.
- Tools and firmware are community-supported, making the ecosystem robust.

**Why are clones cheaper?**  
The cost savings often come from:

- **Lean production processes**.
- **Fewer middlemen** and distributors.
- Direct purchasing from platforms like *AliExpress* at wholesale prices.

In many cases, the same boards are sold on *Amazon* or local stores for significantly higher prices, even though they are identical to those found on global e-commerce platforms.



#### Conclusion

When deciding between originals and clones:

- **Originals**: Offer reliability and support, ideal for beginners or critical projects.  
- **Clones**: Provide cost-effective alternatives, especially for bulk purchases or non-critical projects.

Both have their place in the DIY ecosystem, and choosing between them depends on your priorities: cost, quality, or brand trust.







> Tags: Microcontroller, Arduino, ESP32, ESP8266, ATtiny, Raspberry Pi

[Visit Page on Website](https://done.land/components/microcontroller?237357031823244200) - created 2024-02-15 - last edited 2024-12-11
