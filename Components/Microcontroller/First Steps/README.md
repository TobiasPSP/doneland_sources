<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# First Steps With Microcontrollers

> **How to Successfully Get Started With Microcontrollers**

Starting with microcontrollers is easy when you follow these simple steps:

1. **Choose a Microcontroller:**  
   Review the available [microcontroller models](https://done.land/components/microcontroller/families/) and choose the one that best fits your needs.

2. **Pick a Development Board:**  
   Select a user-friendly development board that includes your chosen microcontroller. Development boards are *ready-to-use PCBs* with the microcontroller and essential peripherals (e.g., USB connectors, UART, crystal, and voltage regulators). You might also consider a matching [expansion board](https://done.land/components/microcontroller/expansionboards/), which acts like a [breadboard](https://done.land/tools/breadboard/) but is tailored to specific development boards. Expansion boards simplify prototyping by managing power supply, wiring, sensors, and peripherals.

3. **Buy the Necessary Hardware:**  
   Once you’ve chosen your microcontroller and development board, acquire the necessary hardware. Start with a simple project, like building a [WLED LED Controller](https://done.land/components/microcontroller/firmware/fromsomeoneelse/wled/#what-you-need). These projects list all required components and guide you through initial steps.

4. **Program Your Microcontroller:**  
   Write instructions for your microcontroller using *firmware*. Begin with *pre-made firmware*, such as the [WLED LED Controller](https://done.land/components/microcontroller/firmware/fromsomeoneelse/wled/#what-you-need). This lets you focus on connecting your development board to your PC. Once comfortable with uploading firmware, you can explore creating your own programs.



Once you've mastered your first microcontroller projects, consider these next steps:

1. **Explore ESPHome:**  
   Learn about [ESPHome](https://done.land/tools/software/esphome/introduction/), a modern way of programming microcontroller firmware without needing coding skills. It’s growing in popularity as an alternative to traditional *C++* programming. Before committing to learning *C++*, review what ESPHome offers.

2. **Understand IDEs:**  
   Discover [integrated development environments (IDEs)](https://done.land/components/microcontroller/firmware/writingownfirmware/). IDEs are free tools for writing custom firmware, offering flexibility and control. However, programming in *C++* can be challenging, especially for beginners, due to the limited resources of microcontrollers.

3. **Explore Development Boards:**  
   Dive into the world of [development boards](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/). Whether you need compact designs, battery-powered options, built-in displays, or even e-ink screens, there’s a board that fits your requirements.



Embark on your journey by selecting a great microcontroller paired with an easy-to-use development board.

## 1. Choose a Microcontroller

I’ve created a [microcontroller comparison](https://done.land/components/microcontroller/families/) to help you make an informed decision. Let’s focus on what matters most for beginners. Consider these factors:

- **Popularity:**  
  Choose a microcontroller that is *widely used*. This ensures access to plenty of example code, community advice, and detailed documentation. The two most popular options are [Arduinos](https://done.land/components/microcontroller/families/arduino/) and the [ESP32 family](https://done.land/components/microcontroller/families/esp/esp32/).  

- **Future-Proofing:**  
  Pick a board with enough processing power and memory for advanced projects. While most boards can handle simple *blink* sketches, you'll quickly outgrow their capabilities. Additionally, ensure the voltage regulator can manage connected sensors and peripherals. Comparing [ESP32 and Arduinos](https://done.land/components/microcontroller/families/comparison/arduinovsesp32/) shows that *ESP32* boards are far more powerful and future-proof than typical *Arduino* boards.  

- **Affordability:**  
  Instead of spending €10-20 on a single branded *Arduino* board, you can buy 10-20 *ESP32* boards for the same cost on *AliExpress*. This is particularly useful as boards can get damaged during experiments or be dedicated to specific projects. Having spares is always a good idea.

### My Recommendation  

Avoid getting an *Arduino*. Instead, start with an *ESP32* board. Here's why:

- **Ease of Use:**  
  *Arduinos* were once known for their simplicity, but the brand now includes various boards with different microcontrollers and pin layouts. Running an *Arduino* example code often requires additional drivers, pin configuration changes, and troubleshooting. In contrast, the *ESP32* family offers a more streamlined experience.

- **Cost-Effectiveness:**  
  Branded *Arduino* boards are often overpriced (€20-30), while *ESP32* boards provide better performance, more memory, and built-in wireless capabilities at a fraction of the cost.  

- **Unified Toolchain:**  
  Both *Arduinos* and *ESP32* use the same toolchains. If you prefer the *Arduino IDE* for writing firmware, it works seamlessly with either board.

- **Modern Features:**  
  The *ESP32* ecosystem is well-supported with tools like [ESPHome](https://esphome.io/) for firmware and [Home Assistant](https://www.home-assistant.io/) for smart home integration. Projects like [WLED](https://kno.wled.ge/) allow advanced control of LED strips. These features are often missing in the *Arduino* ecosystem.

> **Note:**  
> The *ESP32* has roots in the *smart device industry*, which explains its superior design. Originally created for professional hardware producers, it’s affordable and frequently updated. By contrast, Arduino, a private company, has struggled to stay modern after its initial success.

> **Tip:**  
> Avoid the [ESP8266](https://done.land/components/microcontroller/families/esp/esp8266/), the predecessor of the *ESP32*. While it was once popular, the *ESP32* offers better performance, more memory, and improved peripherals for the same price. The *ESP8266* also suffered from unstable voltage regulators, causing issues when peripherals were connected.

## 2. Choose a Development Board

If you’ve followed my advice, you’re now looking for a development board with an [ESP32S](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/) microcontroller.

### Boards to Avoid  

While you can use almost any *ESP32S development board*—they are pin-compatible and fundamentally similar—it’s better to avoid certain boards initially. Specifically, steer clear of the 38-pin [ESP32 DevKitC V4](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/esp32devkitcv4/) (and its smaller 30-pin variant):  

<img src="images/esp32devkitcv4_usbc_t.png" width="40%" height="40%" />  

This board is challenging for beginners. It exposes more pins than needed, some of which can destabilize or damage the system if used incorrectly. This is because it’s a true *engineering development board*, designed for professionals testing every aspect of the microcontroller.
### Recommended Boards

For beginners, it’s essential to have boards that are easy to use, affordable, and flexible. Here are two highly recommended options that I’ve used for years:

#### LilyGO T-Display

<img src="images/lilygo_t-display_defaultfirmware_clock_t.png" width="90%" height="80%" />

The [T-Display LilyGO](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/t-display/) is an excellent choice for beginners. The *16MB* version is often available for just €4.00–6.00 on AliExpress.

This board is widely supported in the community and includes a TFT color display, two programmable buttons, and a *LiIon battery* connector, making it ideal for portable, battery-powered projects. Its *deep sleep* power consumption is also outstanding and can be [reduced to below 300µA](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/t-display/programming/usingesphome/addingdeepsleep/), making it perfect for general use.

> **Important:**  
> Shop wisely: this board is sometimes sold for over €20. I recently purchased ten for just €4.55 each on AliExpress.

#### ESP32-C3 SuperMini

<img src="images/c3_top_overview_t.png" width="30%" height="30%" />

The [ESP32-C3 SuperMini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/c3supermini/) is another great option for beginners. It features the single-core [ESP32-C3](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/), a successor to the dual-core *ESP32S*. While it lacks a second core, it remains extremely powerful, easily surpassing the original [ESP8266](https://done.land/components/microcontroller/families/esp/esp8266/) and most *Arduino* boards.

This board stands out due to its compact size, which fits well on a regular breadboard, making it ideal for DIY projects. It’s straightforward to connect to your PC, with no complicated button sequences required to upload firmware. As a beginner-friendly option, it’s available on AliExpress for as little as €1.00, making it easy to stock up on several.

**Drawbacks:**  
- The board lacks some features of the classic *ESP32S*, such as the [DAC](https://done.land/components/microcontroller/families/esp/espfeatures/dac/), which may cause compatibility issues with certain sketches or examples. However, I’ve personally never encountered such issues with mainstream projects.
- The onboard *WiFi antenna* is not very powerful. While sufficient for connecting to home WiFi, the range is limited (3–5 meters) when used as a WiFi access point.


## 3. Where to Buy

When purchasing microcontroller boards, *AliExpress* is a great option due to its affordability. By buying almost directly from manufacturers, you avoid the higher costs associated with middlemen.

If you shop on *Amazon*, *eBay*, or with local dealers, you may end up paying **substantially higher prices** for essentially the same boards.

> **Tip:**  
> *AliExpress* prices are low due to minimal middlemen and less stringent quality control. Based on my experience, about 1 in 300 boards may have defects or poor soldering. To mitigate this, order in bulk (packs of 5 or 10). Even with the occasional defective board, you’ll still save money compared to purchasing individual boards locally.



## 4. Program Your Microcontroller

Once you have your microcontroller, you’ll need to program it to define its functionality. This process involves creating or installing *firmware*, which serves as the board’s software. You can choose between:

- **Pre-Made Firmware:** Ideal for getting started quickly with common use cases.
- **Custom Firmware:** Allows you to tailor functionality to your specific needs.

### Connect the Board to Your PC

To start using your microcontroller, the first step is to [connect it to your PC](https://done.land/components/microcontroller/firststeps/connecttopc/#connecting-to-computer) via USB. Verify that your PC recognizes the board.

Once connected, you can upload *firmware* to define your board's functionality.

#### Pre-Made Firmware via Browser Upload

For beginners, it’s easier to start with *pre-made firmware* so you can focus on connecting your board correctly without worrying about coding right away.

Here are two popular options for *ESP32* boards that can be installed directly from your browser:

- **[WLED](https://install.wled.me/):** Visit [install.wled.me](https://install.wled.me/) to install WLED firmware. It allows you to control programmable *LED strips* or matrix displays.
- **[ESPHome](https://web.esphome.io/):** Visit [web.esphome.io](https://web.esphome.io/) to install [ESPHome](https://done.land/tools/software/esphome/introduction/) firmware. ESPHome lets you create custom firmware with simple text configurations and upload it wirelessly to your *ESP32*.

For additional options, check out [more pre-made firmware](https://done.land/components/microcontroller/firmware/fromsomeoneelse/).

> **Important:**  
> Pre-made firmware **must match your microcontroller type**. The examples above work for *ESP32* boards but cannot be used on *Arduino*.

#### Programming Your Own Firmware 

If you’re comfortable with programming or have sample code to work with, you can use a [development environment](https://done.land/components/microcontroller/firmware/writingownfirmware/) to write and compile source code into firmware. Once compiled, it can be uploaded to your microcontroller.


> Tags: Microcontroller, First Steps, Beginner, Board, Recommendation

[Visit Page on Website](https://done.land/components/microcontroller/firststeps?343890051021241839) - created 2024-05-01 - last edited 2025-01-04
