<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Arduino vs. ESP32

> All You Need To Know To Choose The Right Processor Family Or Move From Arduino To ESP

In the early 2000s, *Arduino* revoluzionized the hobbyist market for microprocessors: due to their *simple-to-use* programming environment *Arduino IDE* and their relatively cheap development boards, millions of *Makers* and DIY enthusiasts started to add *microprocessors* to their DIY projects.

> [!NOTE]
**Arduino** is the name of a *company* that originally developed the *breakout boards* that carried the microprocessor and were *simple to use*. *Arduinos* are the (many different) models of breakout boards that the company released. One of the early boards was called *Arduino Uno*.

<img src="images/arduino_mega_top_front_t.png" width="50%" height="50%" />

## Why Arduino Got Challenged By ESP32

The amazing *Arduino* success story did not last forever. Today, many users have switched to **ESP32** or are thinking about it. Before we look at the differences, here is why *Arduino* jeopardized its initially predominant market position:

* **Missing Uniqueness:** *Arduino* never produced its own microprocessors. They are a company developing and producing *breakout boards* that simplified using microcontrollers. That's why they soon faced huge competition from other board manufacturers, especially since their designs were *open source*. They could do the same, just cheaper. In a first step, the market was flooded with cheap *Arduino Clones*: much cheaper copies that performed equally well.
* **Missing Vision:** Initial success made the company focus on their original concept: while *Arduino models* became smaller and more capable, they long focused on the initial *ATMega* family of microcontrollers. When *Espressif* released its new microcontroller **ESP8266**, many board manufacturers acted fast and adapted the *Arduino programming framework* to this much faster and more capable microcontroller that also came with WiFi connectivity built-in. *Arduino* only recently left the *ATMega* path and started to produce its own *ESP32*-based boards ([Nano ESP32](https://docs.arduino.cc/hardware/nano-esp32/)). In essence, the concept of *competition* worked well and led to much more powerful microcontrollers in much smaller form factors that were much cheaper.
* **Internal Conflicts:** As if all of this wasn't enough, with raising success and ever more money involved,  the company *Arduino* got preoccupied with internal legal battles over contracts and ownerships.

### Where To Get

Here is where you can get *microcontroller* breakout boards:

* **Arduinos:** The original *Arduinos* are produced by the italian company **Arduino**. There are numerous nameless board manufacturers who produce *clones* based on the same or slightly modified *open-source* designs.
* **ESP32:** Since **ESP32** is the name of a *microcontroller family* and not a specific breakout board, *all* microcontroller boards with an **ESP32** are "originals": they all use the same genuine microcontroller. The microcontroller producer *Espressif* sells its own *Dev Kit* boards through resellers, and there are countless 
board manufacturers who also produce breakout boards with this microcontroller: *Espressif* has *open sourced* its schematics and PCBs. If you are interested in highest production quality and willing to spend more, look for renown board manufacturers such as *Adafruit*, *Sparkfun*, *Seeed*, *NodeMCU*, or get the *Dev Kit* directly from the microcontroller manufacturer *Espressif* through one of its resellers.



> [!CAUTION]
> In this article, for simplicity I am referring to **ESP32** when in reality I mean the specific **ESP32 WROOM** microcontroller. *Espressif* has an entire *family of **ESP32*** microcontrollers, including the **S2**, **S3**, **C3**, and **C6**. I'll look at the differences in a separate article.

### Shopping Sources

You can get breakout boards - both from original manufacturers like **Arduino** and clones - at a variety of sources. Price differences for the *very same board* often are huge:

* **Reseller:** Official resellers such as *Digikey* or *Mouser* are a trusted source to get a board from an original manufacturer. They are pricey though, especially shipping cost is high.
* **Amazon:** *Amazon* offers both original boards and clones (produced by nameless board manufacturers). Shopping here is convenient but often still pricey.
* **AliExpress:** Market places like *AliExpress* let you buy directly from Chinese sources, bypassing other players. Delivery takes 1-2 weeks. Prices are extremely competitive as you practically buy from the manufacturer. Many of the *AliExpress* offers are essentially the same products you find at *Amazon*, too.


> [!TIP]
> Often, boards are offered as discounted bulk packs of 3 or 5. It makes sense to buy more than one board, just in case you damage one or find it so useful that you'd like to use it in additional projects, too.



## The Rise Of ESP Microcontrollers

When the Chinese company *Espressif* in 2015 released their *ESP8266* microprocessor, it became an instant success. 

Many third parties started to release cheap and *very small* breakout boards that could technically do what *Arduinos* can do, just better and faster and cheaper. These new family of *ESP* microprocessors were code-compatible to *Arduinos* and could be programmed using the same tools.

Meanwhile, *Espressif* has released numerous improved microprocessors in rapid succession, and the *ESP32* family of microprocessors today is the *de-facto standard* for *very fast* one- and dual core microcontrollers. They all come with wireless (WiFi) support, and the latest microcontrollers also support *Bluetooth*, *Zigbee*, and *Threads*.

> [!NOTE]
> The company **Arduino** produces breakout boards only and uses third-party microcontroller. The **ESP32** is *no company* but one specific microcontroller model produced by the company **Espressif**. While *Arduinos* were soon cloned and produced by third party for much cheaper prices, *ESP32* breakout boards are *always* produced by third party, and the *ESP32* producer *Espressif* focuses on its microcontrollers.

The picture below shows the original **ESP32** development board on the right that was *considerably bigger* than the original **ESP8266** in the middle. Meanwhile, **ESP32** dev boards are available in any size, including miniature sizes like the board on the left (produced by the manufacturer *Seeed*):

<img src="images/esp32_family1_t.png" width="50%" height="50%" />


## Moving From Arduino To ESP32

Whether you are already using *Arduinos* and are thinking about a move to **ESP32**, or whether you are completely new and try to find the right microcontroller board to start with, here is a drill down on differences:

### Comparing Arduino UNO And ESP32

The *Arduino Uno* is not the fastest and most capable *Arduino* but among the most common and popular ones. 

The **ESP32 DevC** board (available from many sources in many flavors) using the *ESP32 WROOM* microcontroller is not the fastest and most capable **ESP32** microcontroller-based board either, but just like the *Arduino Uno* it is the most common and cheap one you can get. 

This is why these two are compared here. 

Both can be programmed in the same way using the same tools (i.e. *Arduino IDE*, or *VSCode* and *platformio*).

| Item | Arduino Uno | ESP32 Devkit C | Comment |
| --- | --- | --- | --- |
| Price | EUR 25-30 | EUR 3-7 | depending on source |
| Microcontroller | 16 MHz ATmega328P | 240 MHz ESP32 WROOM | |
| Board Supply Voltage | USB or 5V | USB or 5V or 3.3V | directly supplying 3.3V bypasses the voltage regulator |
| internal Voltage | 5V  | 3.3V | |
| GPIO Pins | 14 | 26 (22 PWM 16bit) | | 
| Analog In Pins | 6 (10bit, 0-1024) | 16 (12bit, 0-4096) | | 
| Digital-to-Analog (DAC) |  1 | 2 | |
| UART | 1 | 3 | Serial Interface, i.e. USB |
| SPI | 1 | multiple (software defined) | to connect fast peripherals |
| I2C | 1 | multiple (software defined) | to connect slow peripherals |
| Calc Primes in 30sec | 3.000 | 125.000 | performance test |
| Pins | 30   | 38 | physical pins |
| WiFi | no | yes | access point, station, and both |
| Bluetooth | no | yes | BLE and Classic | 
| ESP-NOW | no | yes | WiFi-protocol to directly connect two microcontrollers |
| Arduino IDE | yes | yes | ESP32: install ESP32 Board Package (esp32 dev) |
| VSCode/platformio | yes | yes | comes with support for virtually any mcu |
| Code Compatible | yes | yes  | include <Arduino.h> when using Arduino functions |


## Voltage Differences

The most important difference between *Arduinos* and *ESP32* is their *operating voltage*: *Arduinos* use **5V** whereas *ESP32* uses **3.3V**.

> [!NOTE]
> You can still power *all* boards by either connecting it to **USB**, or by supplying **5V** or **3.3V** to the appropriate pin. All boards come with *voltage regulators*. This is why *ESP32* should best be powered by supplying **5V**. *Do not* supply **3.3V** directly as this bypasses the internal power regulator, and when your power supply isn't supplying *exactly* **3.3V**, you may be destroying the microcontroller.


This difference is important when *communicating* with peripheral devices such as sensors etc.:

### Translating Voltage

Some peripherals accept a wide input voltage from **3.3V-5V** so you can run them equally well with *Arduinos* and *ESP32*. Simply supply the same voltage the microcontroller uses. 

Occasionally, the peripheral voltage *does not match* the microcontroller voltage. This can happen both ways:

*Arduinos* (**5V**) can run **3.3V peripherals** by supplying the **3.3V** to the peripheral from its **3.3V** pin.
*ESP32* (**3.3V**) can run **5V peripherals** by supplying the **5V** to the peripheral from its **5V** pin.

> [!CAUTION]
> The latter requires that you supply **5V** to the *ESP32*. It will then use its internal *voltage regulator* to create the required **3.3V** for the microcontroller, and still supply the **5V** to peripherals when they need them. If you power the **ESP32** directly with **3.3V** through its *3.3V pin*, then the board *will not* supply **5V** at the *5V pin*, and you cannot run **5V** peripherals off the board: the **ESP32** comes with a voltage regulator that can turn **5V** to **3.3V**, but not **3.3V** to **5V**.

### Level Shifter

Whenever you use a *different* voltage for peripherals, you need to *translate* their *output* voltage back to the voltage the microcontroller needs.

For example, when you run a **3.3V SD Card Reader** on a **5V Arduino**, the *SD Card Reader* sends data back to the microcontroller GPIO pin using **3.3V**. This voltage needs to be shifted to **5V**.

Likewise, when you run a **5V Sensor** on a **3.3V ESP32**, the sensor sends back **5V** data to the *ESP32 GPIO pin*, and you need to shift the voltage level *down* to **3.3V**.

Fortunately, this is neither complex nor expensive: *level shifter* boards can be hooked between peripheral and microcontroller board to do the level shifting for you.

> [!TIP]
> Often, you can get away without a level shifter when *receiving* signals from peripherals: *Espressif* officials once mentioned in a press release that *ESP32* GPIO pins are *5V tolerant* even though this assurance is not found in the data sheet. When you *send* information to a peripheral, check its data sheet to see whether it is tolerant enough, and whether it interprets the *actual voltage* you send as a *high* signal. If in doubt, use a level shifter anyway.


> Tags: Microcontroller, Comparison, Arduino, ESP32, Level Shifter, Voltage

[Visit Page on Website](https://done.land/components/microcontroller/arduinovsesp32?350852031029241923) - created 2024-03-29 - last edited 2024-03-29
