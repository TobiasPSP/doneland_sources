<img src="/assets/images/processor.png" width="80%" height="80%" />
# ESP32-C3 Super Mini

> Extremely Compact And Very Affordable Microcontroller Board With Great Functionality

The **ESP32-C3 Super Mini** is my go-to microcontroller board whenever space is at a premium. Its tiny size allows it to fit into the smallest devices while still offering ten fully usable GPIOs. 

<img src="images/c3_anglefront_overview_t.png" width="30%" height="30%" />

It is fully compatible with all **ESP32** development environments, including [ESPHome](https://done.land/tools/software/esphome/introduction/). Additionally, you can directly upload open-source firmware made for the **ESP32**, such as [WLED](https://kno.wled.ge/). 

[Here’s an example project](https://done.land/components/microcontroller/firmware/fromsomeoneelse/wled/) using the **ESP32-C3 Super Mini** and an **8x8 WS2812 LED Panel** to create an awesome colorful light cube—no programming required and just three short wires:

<img src="images/wled_proj_simple_gray6_t.png" width="50%" height="50%" />

## Overview

The **ESP32-C3 Super Mini** is energy-efficient, widely available, and highly affordable. Its computational power and 4MB flash storage are more than adequate for most DIY projects. 


I’ve replaced **Arduinos** and **ESP8266** boards with this board in most of my new projects. When I need more than 10 GPIOs or require a dual-core processor for computationally intensive tasks, I generally choose the [ESP32-S2 Mini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/s2mini/). For full backward compatibility with older firmware, I stick with the classic **ESP32S**.
### Arduino Framework

The *Arduino Framework* - as of the time writing - does not yet support this board. Users work around by using similar boards like `esp32c3`. This board definition defines these constants:

| Pin Constant             | Value   | Remark |
| ------------------------ | :-----: | --- |
| **LED_BUILTIN**        | n/a     | **wrong:** should be *8* |
| **SDA** *(I2C)*        | 8       | 
| **SCL** *(I2C)*        | 9       | 
| **MOSI**/COPI *(SPI)*  | 6       | 
| **MISO**/CIPO *(SPI)*  | 5       | 
| **SCK**/SCL/SCLK *(SPI)* | 4       | 
| **SS**/CS *(SPI)*      | 7       | 
| **RX** *(Serial)*      | 20      | 
| **TX** *(Serial)*      | 21      | 
| **A0** *(analog input)* | 0       | 
| **A1** *(analog input)* | 1       | 
| **A2** *(analog input)* | 2       | 
| **A3** *(analog input)* | 3       | 
| **A4** *(analog input)* | 4       | 
| **A5** *(analog input)* | 5       | 

Other than the missing/wrong constant `LED_BUILTIN`, this definition works fine. 

In the latest [arduino-esp32](https://github.com/espressif/arduino-esp32) release from *Espressif*, the board has meanwhile dedicated supported under the name `nologo_esp32c3_super_mini`:



| Pin Constant             | Value   |
| ------------------------ | :-----: |
| **LED_BUILTIN**        | 8       | 
| **SDA** *(I2C)*        | 8       | 
| **SCL** *(I2C)*        | 9       | 
| **MOSI**/COPI *(SPI)*  | 6       | 
| **MISO**/CIPO *(SPI)*  | 5       | 
| **SCK**/SCL/SCLK *(SPI)* | 4       | 
| **SS**/CS *(SPI)*      | 7       | 
| **RX** *(Serial)*      | 20      | 
| **TX** *(Serial)*      | 21      | 
| **A0** *(analog input)* | 0       | 
| **A1** *(analog input)* | 1       | 
| **A2** *(analog input)* | 2       | 
| **A3** *(analog input)* | 3       | 
| **A4** *(analog input)* | 4       | 
| **A5** *(analog input)* | 5       | 

Apparently, only the constant `LED_BUILTIN` was updated.

So here are your options:

* define the constant `LED_BUILTIN` manually in your source code
* use the pin number `8` directly in your code when you want to access the built-in LED
* permanently add the board [definition file](https://github.com/espressif/arduino-esp32/blob/master/variants/nologo_esp32c3_super_mini/pins_arduino.h)  to your *Arduino Core* `variants` subfolder, and use the new board definition `nologo_esp32c3_super_mini`.


### Key Benefits of the ESP32-C3 Super Mini

- **Compact:** Extremely small size (*22.5x18mm*).
- **User-Friendly:** Works seamlessly with environments like *platform.io* and *ESPHome*. No need to manually enter firmware upload mode or press "boot" buttons.
- **Low Power:** Energy-efficient with support for *Bluetooth BLE*, ideal for battery-powered devices.
- **Expandable:** Optional battery shields add charging functionality and portable power supply.
- **Affordable:** Often priced under €1.50.

### GPIOs

The board features a **USB-C** connector and 10 fully usable **GPIOs**. Additionally, four GPIOs support **analog input**:

<img src="images/esp32-c3-supermini-pins.png" width="100%" height="100%" />

> [!IMPORTANT]
> In the pin schematic, **D** denotes a **digital-only** GPIO. Always refer to the actual GPIO number shown in the schematic to avoid confusion with legacy labeling.

### Programmable Blue LED

A programmable **blue LED** is connected to **GPIO 8** (inverted: *low* active). There is also a **red power LED** that lights up when the board is connected to **5V** via its internal voltage regulator. This red LED automatically turns off if the board is powered through the **3.3V** pin (e.g., from a battery), which helps conserve energy in low-power scenarios.

### Performance Comparison

While the **ESP32-C3** is more than twice as fast as an **ESP8266**, it is a single-core processor running at **160MHz**. In contrast, classic **ESP32S** boards are dual-core and run at **240MHz**, offering roughly three times the performance. However, most DIY projects don’t require such speeds, and the higher performance comes at the cost of increased power consumption. 

If your project involves computationally intensive tasks or requires real-time responsiveness to multiple tasks, you might consider the classic **ESP32S** or the newer **ESP32-S3**.

The compact form factor of the **ESP32-C3 Super Mini** limits the number of exposed GPIOs. If you need more than 10 GPIOs, consider larger boards that expose up to 22 GPIOs.

<img src="images/c3_angle_overview_t.png" width="50%" height="50%" />

## Interfaces

Depending on the peripherals you wish to connect, you can use the *two-wire serial interface* (*UART*), [I2C](https://done.land/fundamentals/interface/i2c/), and [SPI](https://done.land/fundamentals/interface/spi/).

With the *ESP32-C3*, you can map *any GPIO* to *any interface*. This flexibility explains why you might come across different pin schematics for this chip.

However, it’s recommended to use the *default pins* for a given interface for several reasons:

* **Compatibility:** Example code often assumes the default GPIOs. If you use different GPIOs, you will need to adjust the source code.
* **Default Initialization:** Many libraries provide default initializers, and using them ensures the default GPIOs are automatically chosen.

> [!IMPORTANT]
> Using non-default GPIOs for an interface is technically fine, but you **must ensure** that your code and libraries are instructed to use those GPIOs for the specific interface.

### Serial Interface

| Serial Pin | ESP32-C3 SuperMini Pin |
| --- | --- |
| RX | 20 |
| TX | 21 |

### SPI

| SPI Pin | ESP32-C3 SuperMini Pin |
| --- | --- |
| MOSI | 6 |
| MISO | 5 |
| SCK | 4 |
| CS | 7 |

### I2C

The *I2C* interface poses a challenge with this board. The board definition uses *GPIO8* (SDA) and *GPIO9* (SCL). *GPIO8* is hard-wired to the programmable *LED*, too, though.

If you want to avoid conflicts with the built-in *LED*, use software *I2C* with pins of your choice, for example:

| I2C Pin | ESP32-C3 SuperMini Pin |
| --- | --- |
| SDA | 1 |
| SCL | 3 |

If however you do not need to control the built-in LED and don't care about it, sticking to the hardware *I2C* pins ensures a higher performance.

## Caveat: Defective Board Designs

While the **ESP32-C3 SuperMini** is readily available from many sellers, subtle differences in board layouts have surfaced. In 2024, some board designs began to appear that may cause issues with *WiFi connectivity*:

<img src="images/esp32-c3-supermini-defective_design.png" width="100%" height="100%" />

The image shows the "normal" board design on the left and the "revised" layout on the right. In the new layout, the crystal has been moved closer to the ceramic *WiFi antenna*.

### WiFi Sending Impaired

Users with the new board design report that while they can *receive* WiFi networks, **connecting** to WiFi networks is either impossible or very slow. Some users also reported that connecting to WiFi was only possible after physically touching the antenna. Others experienced connectivity issues when female pin headers were added, especially when *pin 21* was wired.

All observations point to interference during *WiFi transmission*, most likely caused by the crystal's relocation closer to the antenna. Once transmission power was reduced (e.g., by touching the antenna), the problem seemed to resolve. Similarly, the issue worsened when pin headers were installed, especially when wires were connected to pin 21, which is near the antenna.


### Remedy
You can still use the defective boards for many tasks that don’t involve *WiFi*, but if you need the board to transmit WiFi correctly, you can reduce the transmission power through code:

````c++ 
WiFi.setTxPower(WIFI_POWER_8_5dBm);
````
Reducing the transmission power prevents the interference from reaching critical levels.

By reducing the WiFi transmission power, you also reduce the overall power consumption. Since lower transmission power is still sufficient for most home environments with decent WiFi coverage, this may not be a bad thing.

However, this workaround may be impractical when your *C3 SuperMini* needs to operate in weak WiFi environments or far away from access points (e.g., in a garden). In such cases, you should consider returning defective boards.

> [!NOTE]
> The vast majority of **C3 SuperMini** boards use a flawless design. Only selected batches have been affected by a "redesign." If you're unsure, you can measure the distance between the crystal and the ceramic antenna (see image above). A gap of at least *1mm* is normal, while affected boards show a gap of just *0.3mm*. For more details, check out this article: [ESP32-C3 SuperMini Flaw](https://roryhay.es/blog/esp32-c3-super-mini-flaw).

## Performance

The **ESP32-C3 SuperMini** is a great replacement for the **ESP8266**, offering more than double its processing speed. It also features a robust voltage regulator (unlike the under-rated ones often found in ESP8266 boards, which can brown out when connecting power-hungry sensors).

Here’s a quick performance comparison:

| Microcontroller | Performance | SRAM | PSRAM |
| --- | --- | --- | --- |
| ESP32-C3 | 160-200MIPS | 400KB | n/a |
| ESP8266 | 80MIPS | 160KB + 64KB Instruction RAM + 96KB Data RAM | n/a |
| ESP32S | 600MIPS | 520KB | optional, up to 4MB |

## GPIO

The **ESP32-C3** has 22 GPIOs, but the **C3 SuperMini** exposes only 13 due to its compact size. Of these 13 GPIOs, 10 are freely usable, while the remaining 3 are strapping pins and cannot be used during boot.

<img src="images/c3_bottom_overview_t.png" width="50%" height="50%" />

| Pin | Description | Remark |
| --- | --- | --- |
| 5V | External or USB power | Activates the internal voltage regulator and turns on the red power LED |
| G | *GND* | |
| 3.3 | 3.3V directly (3.0-3.6V) | **Bypasses the voltage regulator** and does not turn on the red power LED. Use this pin for low-energy scenarios, such as battery operation, but take **extreme caution** not to exceed the voltage limits. This pin **directly powers** the microcontroller. Exceeding *3.6V* will irreversibly damage the microcontroller. **Do not use LiIon batteries directly**.<br/><br/>When supplying power to the *5V* pin, this pin exposes the *3.3V* produced by the internal voltage regulator. |
| 0-10 | *GPIO0* - *GPIO10* | Pins 2 and 9 are strapping pins reserved during boot. Pin 8 controls the blue LED on the board (inverted). |
| 20-21 | *GPIO20* - *GPIO21* | free to use, no analog input |

All GPIOs are multifunctional and can be configured for various purposes, such as digital I/O, ADC (Analog-to-Digital Converter), UART, SPI, I2C, PWM, and more.

### Ten Freely Usable GPIOs

These 10 GPIO pins can be freely used:

| Pin | Remark |
| --- | --- |
| 0 | Digital and analog (ADC1) |
| 2 | Digital and analog (ADC1) |
| 3 | Digital and analog (ADC1) |
| 4 | Digital and analog (ADC1) |
| 5 | Digital and analog (ADC1) |
| 6 | Digital only |
| 7 | Digital only |
| 10 | Digital only |
| 20 | Digital only |
| 21 | Digital only |

### Three Reserve GPIOs

If you require more *GPIOs*, these three can be used with some restrictions. Ensure your circuitry doesn't pull any of these up or down by hardware.

These strapping pins are only used during boot (when the firmware isn't yet active), so you can use them freely in your software (firmware), just make sure your wiring doesn’t tamper with their state, or your board may not boot properly.

| Pin | Remark | Default |
| --- | --- | --- |
| 8 | Connected to blue LED (*low* turns LED on). Controls ROM message printing (not critical). | Floating |
| 2 | Strapping pin, do not use during boot (selects boot mode). | Floating |
| 9 | Strapping pin, do not use during boot (boot button). | Pulled up |

> [!NOTE]  
> *JTAG* is available on *GPIO4*-*GPIO7*.

### Boot Modes

The strapping pins control the boot behavior during the boot process:

| Mode | GPIO2 | GPIO8 | GPIO9 |
| --- | --- | --- | --- |
| SPI Boot (normal) | *High* | *Any* | *High* |
| UART/JTAG (firmware upload) | *High* | *High* | *High* |

### Board Schematics

<img src="images/esp32-c3-supermini-schematic_t.png" width="100%" height="100%" />

### Programmable LED

The board has a *blue LED* connected to *GPIO8*. This *LED* is *inverted* because it is sinked, not sourced: *low* turns the LED **on**, and *high* turns it **off**.

## Programming

The **ESP32-C3 Super Mini** is widely adopted and simple to use.

### PlatformIO
In **PlatformIO**, use the board [`ESP32-C3-DevKitM-1`](https://docs.platformio.org/en/latest/boards/espressif32/esp32-c3-devkitm-1.html).


````
[env:esp32-c3-devkitm-1]
platform = espressif32
board = esp32-c3-devkitm-1
````

More specialited IDs like [lolin_c3_mini](https://docs.platformio.org/en/latest/boards/espressif32/lolin_c3_mini.html) may work even better:

````
[env:lolin_c3_mini]
platform = espressif32
board = seeed_xiao_esp32c3
````

### ESPHome
In *ESPHome configurations*, use the board id `esp32-c3-devkitm-1`:

````
esp32:
  board: esp32-c3-devkitm-1
````

You can adjust and override specs if needed:

````
esphome:
  name: c3-supermini-test
  friendly_name: C3 SuperMini Test
  platformio_options:
    board_build.f_flash: 40000000L
    board_build.flash_mode: dio
    board_build.flash_size: 4MB

esp32:
  board: esp32-c3-devkitm-1
  variant: esp32c3
  framework:
    type: arduino

light:
  - platform: status_led
    name: "Status LED"
    id: esp_status_led
    icon: "mdi:alarm-light"
    pin:
      number: GPIO8
      inverted: true
    restore_mode: ALWAYS_OFF
````

> Tags: ESP32-C3, C3

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/c3supermini?845657081329241300) - created 2024-08-28 - last edited 2025-01-07
