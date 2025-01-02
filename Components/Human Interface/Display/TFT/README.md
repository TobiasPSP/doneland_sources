<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# TFT Displays

> Colorful Content And Available In Almost Any Size, TFT Displays Are The Most Economic Solution To Add A Screen To Your Device

A **TFT** (*Thin Film Transistor*) display is a type of **LCD** (*Liquid Crystal Display*) that utilizes thin film transistor technology to control individual pixels (*actively* controlled). This provides higher image quality and faster refresh rates compared to traditional passive-matrix displays. Most modern computer displays today use **IPS TFT** technology.


| Display Technology | Remark |
| --- | --- |
| LCD | Text only, cheap, for outdoors |
| TFT | High resolution color graphics, cheap, readily available in almost any size, for indoors |
| IPS TFT | *In-Plane Switching:* advanced TFT technology for *superior viewing angles* and *better color reproduction* |
| OLED | Very expensive, only *very small* and *monochrome* *OLEDs* are affordable |

## Overview
A usable **TFT display** consists of two main components:

- **Display:** The actual display unit, which can vary in form, pixel density, TFT technology, and shape.
- **Controller:** A chip that drives the display and acts as an interface between the display and a microcontroller.

While you can purchase these separately, it's more common to buy a ready-to-use **breakout board** that integrates both on a single **PCB**.

### Display Controller
There are far more **displays** than **display controllers**. For example, the popular [ST7789](https://done.land/components/humaninterface/display/tft/st7789) is a widely used TFT display controller capable of driving most **TFT displays** with a maximum resolution of **240x320** at **262K colors** (18-bit).

The display controller provides the **interfaces** that microcontrollers use to communicate with the display. When purchasing a **breakout board**, most designs expose only the pins for the **SPI interface**.

#### SPI Interface
Most **TFT display controllers** support the fast [SPI interface](https://done.land/fundamentals/interface/spi), which is a **serial** interface where data is transmitted **bit by bit**, requiring only a few (typically three) wires. Modern microcontrollers, such as the **ESP32**, are fast enough to support even **high frame rates** over this interface.

#### Parallel Interface
Some controllers also support a **Parallel interface**, where multiple bits are transmitted simultaneously. **Parallel interfaces** come in **8-bit** and **16-bit** variants, and the more bits transferred at once, the faster the data transfer rate.

**Parallel interfaces** are significantly faster than **SPI**, enabling smoother and faster display refresh rates, especially on larger or high-resolution displays. These are well-suited for complex graphics or real-time applications like video playback.

However, the downside is the **high number of GPIOs** required and more complex wiring. Many microcontrollers lack the necessary **GPIO pins** for this interface.

For most **DIY** projects, implementing a **Parallel interface** is usually overkill. The **SPI** interface is sufficient for nearly all DIY use cases, as real-time high-resolution video at high frame rates is not typically what you’re aiming for with small **TFT display boards**.



## LCD, TFT, IPS 
**TFT** is an evolution of simple **LCD displays**, which is why you might come across the term **TFT LCD**.

### TFT LCD

While **TFT LCDs** offer **faster response times** and **better color contrasts** compared to older **matrix LCDs**, they are still a type of **LCD display** that uses **liquid crystals**, now controlled **actively** rather than **passively**.

Basic **TFT displays** are very affordable today, but they do have a few limitations:

- **Viewing Angle:** A narrow **viewing angle** results in image degradation when viewed from the side.
- **Low Color Accuracy:** Color and contrast are limited, with colors potentially appearing faded.

### IPS

**IPS** (In-Plane Switching) is an advanced type of **TFT LCD** that, while slightly more expensive, improves on many of the limitations of standard TFTs by offering better **liquid crystal alignment**. IPS displays are also more *durable* but tend to have slower *response rates* compared to other technologies.

- **Wide Viewing Angle:** **IPS screens** maintain color accuracy and contrast even when viewed from extreme angles. This feature is sometimes referred to as **Full Angle**.
- **Better Color:** **IPS displays** offer more vivid colors and stronger contrasts compared to standard TFTs.

### Power Consumption

The improvements in display quality come with an increase in power consumption:

- **TFT** displays generally consume more power compared to older LCDs due to their active control mechanism. 
- **IPS** displays consume more power than standard **TFTs** due to the enhanced crystal alignment and the additional backlight needed for better color accuracy and viewing angles.

## Use Cases

Depending on your *use case*, *TFT displays* are often the most cost-effective choice, but they are not always the best option:

- **Battery-Operated Devices:** If *power consumption* is a concern, consider *LCD*, *OLED*, or *ePaper* displays. You could also opt for simpler, low-power *LEDs* with just a few *µA* current consumption, or skip the display altogether.
- **Display Quality:** If superior display quality is your priority, you might want to explore the (more expensive) *OLED* displays.
- **Outdoor Use:** For devices used *outdoors* in *bright sunlight*, *TFT* is typically not suitable. *ePaper* is the best choice for visibility, though *LCD* and *OLED* can also work due to their high contrast ratios.
- **Fast Refresh Rates:** If high *refresh rates* are crucial (e.g., for *real-time displays* or *gaming*), classic *TFT* (over *IPS*) is the better option. For the best combination of display quality *and* fast refresh rates, choose *OLED*.

| Feature          | LCD  | TFT  | IPS  | OLED | ePaper |
|------------------|------|------|------|------|--------|
| Energy Efficient  | +++  | ++   | +    | ++   | ++++   |
| Display Quality   | -    | +    | ++   | +++  | +      |
| Sunshine-Proof    | ++   | -    | -    | +    | ++++   |
| Fast Refresh      | +    | +++  | ++   | ++++ | -      |


> Tags: TFT, IPS, Display, Full Angle, Viewing Angle

[Visit Page on Website](https://done.land/components/humaninterface/display/tft?647185101517241243) - created 2024-10-16 - last edited 2024-10-16
