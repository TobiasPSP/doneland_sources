<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP32

> The Classic ESP32 Microcontroller Sets New Standards and Comes in WROOM and WROVER Variants

The *classic ESP32* is known as the *ESP32S*. Since its debut in 2016, many additional *ESP32 variants* have been introduced, such as the *ESP32-S3* and *ESP32-C6*. However, the *ESP32S* remains highly popular among *DIY makers* because it is particularly straightforward to use:

* **Well-Known:** Most *ESP32 examples* available online or on platforms like YouTube are for either the *ESP8266* or the *ESP32S*. There is an abundance of documentation.
* **Well-Supported:** Regardless of your project, chances are the *ESP32S* is fully supported. After nearly a decade, almost all editors, development environments, home automation systems, and other tools incorporate support for this microcontroller.
* **Well-Balanced:** The *ESP32S* features an exceptionally balanced set of capabilities, including motor control, a *DAC* (*digital-to-analog converter*), *touch input support*, and more—perfect for *DIY makers*.

That said, if you’re looking for a *miniature footprint*, cutting-edge *low power consumption*, or compatibility with the latest *wireless standards* like *Matter* or *Thread*, you may want to explore the successors to the *ESP32S*.

<img src="images/esp_wroom_top_front2_t.png" width="60%" height="60%" />

## ESP32 Types

The most popular and widely available *ESP32S* variant is the *WROOM-32D*. However, there are several variations to consider. When purchasing **ESP32** development boards, pay attention to the fine print in the type:

* **WROOM-32:** The original version of the **ESP32**.
* **WROOM-32D:** A revised version featuring a PCB antenna.
* **WROOM-32E:** Similar to the *WROOM-32D* but with an IPX antenna jack for external antennas.
* **WROVER:** Similar to the *WROOM-32* but includes additional 4/8 MB *pSRAM*.
* **WROVER-B:** A version of the *WROOM-32D* with 8 MB *pSRAM*.
* **WROVER-IB:** Same as the *WROVER-B* but includes an IPX antenna jack instead of a built-in PCB antenna.

Additionally, check the memory size when choosing a module. The price difference between *4 MB* and *8 MB* versions is typically minimal, and the extra memory could prove invaluable for future projects.

When planning to use an *ESP32S* in your project, one of the first things to determine is which *GPIO pins* are safe to use. This is covered in the next section below.

## GPIOs

The GPIO information in this section applies specifically to the *classic ESP32* (ESP32S) and all development boards that use it.


| GPIO | Modes             | Remark                                |
|------|-------------------|---------------------------------------|
| 0    | Ain, Din, Dout    | Pulled up; must be low for flash mode; outputs PWM at boot |
| 1    | Dout              | TX for serial communication; debug output at boot |
| 2    | Ain, Din, Dout    | Connected to onboard LED; floating/low for flash mode |
| 3    | Din               | RX for serial communication; high at boot |
| 5    | Din, Dout         | Outputs PWM at boot; strapping pin, VSPI |
| 12   | Ain, Din, Dout    | Boot fails if pulled high; strapping pin, HSPI |
| 13   | Ain, Din, Dout    | Free if HSPI is not used           |
| 14   | Ain, Din, Dout    | Free if HSPI is not used           |
| 15   | Ain, Din, Dout    | Free if HSPI is not used           |
| 18   | Din, Dout         | Free if VSPI is not used           |
| 19   | Din, Dout         | Free if VSPI is not used           |
| 21   | Din, Dout         | Free if I2C is not used            |
| 22   | Din, Dout         | Free if I2C is not used            |
| 23   | Din, Dout         | Free if VSPI is not used           |
| 4    | Ain, Din, Dout    | General-purpose input/output         |
| 16   | Din, Dout         | RX2; general-purpose input/output    |
| 17   | Din, Dout         | TX2; general-purpose input/output    |
| 25   | Ain, Aout, Din, Dout | Exposes DAC1 (if used)             |
| 26   | Ain, Aout, Din, Dout | Exposes DAC2 (if used)             |
| 27   | Ain, Din, Dout    | General-purpose input/output         |
| 32   | Ain, Din, Dout    | General-purpose input/output         |
| 33   | Ain, Din, Dout    | General-purpose input/output         |
| 34   | Ain, Din          | Input only, no pull-up/pull-down     |
| 35   | Ain, Din          | Input only, no pull-up/pull-down     |
| 36   | Ain, Din          | Input only, no pull-up/pull-down     |
| 37   | Ain, Din          | Input only, no pull-up/pull-down     |
| 38   | Ain, Din          | Input only, no pull-up/pull-down     |
| 39   | Ain, Din          | Input only, no pull-up/pull-down     |


| 20   | May be available in newer revisions |
| 24   | Not functional           |
| 28-30| Not functional           |

GPIOs 6 to 11 on the ESP32 are typically used for the internal flash interface and are not intended for general-purpose I/O. These pins are part of the SPI interface used to connect the ESP32 to its onboard flash memory. Since these GPIOs are dedicated to this purpose, using them for general I/O can interfere with the functioning of the flash memory and is not recommended. On many development boards, these pins are not exposed to external connections, and even if they are exposed, they should be used with caution as their behavior is tied to the boot process and internal memory access. If you do need additional GPIOs for your project, it is better to use other pins that do not conflict with the flash interface.


### Exposed Pins

The GPIOs available to you depend on the specific development board you purchase. Boards come in various configurations, such as *38 pins*, *30 pins*, or even smaller form factors with fewer exposed pins. The fewer pins a board exposes, the more *ESP32S* functionality becomes unavailable. This trade-off can be acceptable if your project prioritizes compactness over functionality.

> [!IMPORTANT]
> The information below applies only to *ESP32S*. It does not apply to other *ESP32 microcontrollers* (e.g., ESP32-S2 or ESP32-C3), as their GPIO layouts, while similar, are not identical.


### Always-Safe ESP32 GPIOs

The following GPIOs are always safe to use for general purposes. They have no boot-time restrictions or specific roles that might interfere with typical use:




| GPIO | Usable            | Analog In | Modes               | Remarks                                                                     |
|------|--------------------|-----------|---------------------|----------------------------------------------------------------------------|
| 0    | After boot completed: strapping pin      | No        | Ain, Din, Dout      | *low* enters bootloader, *high* runs user code (sketch).  |
| 1    | Not when using serial communication        | No        | Din, Dout                | TX for serial communication; debug output at boot                           |
| 2    | After boot completed: strapping pin      | Yes        | Ain, Din, Dout      | often connected to onboard LED (when present); floating/low to enter boot loader.               |
| 3    | No if serial communication is required      | No        | Din, Dout                 | RX for serial communication; high at boot                                  |
| 4    | Yes        | Yes       | Ain, Din, Dout      | General-purpose input/output                                                |
| 5    | After boot completed: strapping pin      | No        | Din, Dout           | Outputs PWM at boot. Controls timing for SDIO slave in some configurations, irrelevant when using SPI flash. (V)SPI CS |
| 6    | No, always required for internal flash memory communication | No        | Ain, Din, Dout    | SPI Flash MISO (Master In Slave Out) - Used for reading data from external SPI flash |
| 7    | No | No, always required for internal flash memory communication       | Ain, Din, Dout    | SPI Flash MOSI (Master Out Slave In) - Used for sending data to external SPI flash |
| 8    | No | No, always required for internal flash memory communication       | Ain, Din, Dout    | SPI Flash SCLK (Serial Clock) - Provides clock signal for SPI communication with the flash |
| 9    |  No | No, always required for internal flash memory communication        | Ain, Din, Dout    | SPI Flash CS (Chip Select) - Used to select the SPI flash for communication |
| 10   | No | No, always required for internal flash memory communication       | Ain, Din, Dout    | SPI Flash WP (Write Protect) - Used to prevent writing to the flash when high |
| 11   | No | No, always required for internal flash memory communication        | Ain, Din, Dout    | SPI Flash HD (Hold) - Used to hold the SPI flash communication (pauses SPI operations) |
| 12   | After boot completed, strapping pin       | Yes       | Ain, Din, Dout      | strapping pin: sets flash voltage (3.3V by default). If set to high on accident during boot, 3.3V flash receives 1.8V and browns out; (H)SPI MISO |
| 13   | Yes, when not using secondary SPI        | Yes       | Ain, Din, Dout      | (H)SPI MOSI                                                                 |
| 14   | Yes, when not using secondary SPI        | Yes       | Ain, Din, Dout      | (H)SPI CLK                                                                 |
| 15   | Yes, when not using secondary SPI        | No        | Ain, Din, Dout      | low silences boot messages; (H)SPI CS                                       |
| 16   | Yes, when UART2 is not in use or when not using WROVER.        | No        | Din, Dout           | UART2 RX, never available when using WROVER                           |
| 17   | Yes, when UART2 is not in use or when not using WROVER.        | No        | Din, Dout           | UART2 TX, never available when using WROVER                           |
| 18   | Yes, when not using primary SPI        | No        | Din, Dout           | (V)SPI CLK                                                                 |
| 19   | Yes, when not using primary SPI         | No        | Din, Dout           | (V)SPI MISO                                                                 |
| 20   | No, ghost              | No        | - | Not exposed on ESP32S models |
| 21   | Yes, when not using I2C        | No        | SDA                 | I2C                                                                          |
| 22   | Yes, when not using I2C        | No        | SCL                 | I2C                                                                          |
| 23   | Yes, when not using primary SPI        | No        | Din, Dout           | (V)SPI MOSI                                                                 |
| 24   | No, ghost              | No        | - | Not exposed on ESP32S models   |
| 25   | Yes, when not using DAC1        | Yes       | Ain, Aout, Din, Dout| Used for DAC1 output when not configured for other purposes. |
| 26   | Yes, when not using DAC2        | Yes       | Ain, Aout, Din, Dout| Used for DAC2 output when not configured for other purposes.  |
| 27   | Yes        | Yes       | Ain, Din, Dout      | General-purpose input/output                                                |
| 28   | No, ghost              | No        | - | Not exposed on ESP32S models  |
| 29   | No, ghost              | No        | - | Not exposed on ESP32S models |
| 30   | No, ghost              | No        | - | Not exposed on ESP32S models  |
| 32   | Yes        | Yes       | Ain, Din, Dout      | General-purpose input/output                                                |
| 33   | Yes        | Yes       | Ain, Din, Dout      | General-purpose input/output                                                |
| 34   | Yes, input only    | Yes       | Ain, Din            | Input only, no pull-up/pull-down, typically used for analog inputs |
| 35   | Yes, input only    | Yes       | Ain, Din            | Input only, no pull-up/pull-down, typically used for analog inputs |
| 36   | Yes, input only    | Yes       | Ain, Din            | Input only, no pull-up/pull-down, typically used for analog inputs |
| 37   | Yes, input only    | Yes       | Ain, Din            | Input only, no pull-up/pull-down                                            |
| 38   | Yes, input only    | Yes       | Ain, Din            | Input only, no pull-up/pull-down                                            |
| 39   | Yes, input only    | Yes       | Ain, Din            | Input only, no pull-up/pull-down                                            |


### Second-Choice GPIOs

If you need additional GPIOs, you can consider these. However, they serve dual purposes, so ensure there are no conflicts with your project requirements:

| GPIO | Modes             | Caveat                              |
|------|-------------------|-------------------------------------|
| 0    | Ain, Din, Dout    | Pulled up; must be low for flash mode; outputs PWM at boot |
| 1    | Dout              | TX for serial communication; debug output at boot |
| 2    | Ain, Din, Dout    | Connected to onboard LED; floating/low for flash mode |
| 3    | Din               | RX for serial communication; high at boot |
| 5    | Din, Dout         | Outputs PWM at boot; strapping pin, VSPI |
| 12   | Ain, Din, Dout    | Boot fails if pulled high; strapping pin, HSPI |
| 13   | Ain, Din, Dout    | Free if HSPI is not used           |
| 14   | Ain, Din, Dout    | Free if HSPI is not used           |
| 15   | Ain, Din, Dout    | Free if HSPI is not used           |
| 18   | Din, Dout         | Free if VSPI is not used           |
| 19   | Din, Dout         | Free if VSPI is not used           |
| 21   | Din, Dout         | Free if I2C is not used            |
| 22   | Din, Dout         | Free if I2C is not used            |
| 23   | Din, Dout         | Free if VSPI is not used           |


### Interface Pins (I2C and SPI)

Most sensors and peripherals use either the *I2C* (slow speed) or *SPI* (high speed) interface. While these can be emulated in software, dedicated hardware GPIOs are faster and more efficient.

#### I2C

| GPIO | Function |
|------|----------|
| 21   | SDA      |
| 22   | SCL      |

#### SPI

| Function | VSPI | HSPI |
|----------|------|------|
| MOSI     | 23   | 13   |
| MISO     | 19   | 12   |
| CLK      | 18   | 14   |
| CS       | 5    | 15   |



### Strapping Pins

Strapping pins determine the chip's behavior at boot time. While most restrictions only apply during boot, care must be taken not to hard-wire these pins incorrectly.

| GPIO | Label | Remark                                    |
|------|-------|------------------------------------------|
| 0    | 0     | Low to enter ROM serial bootloader       |
| 2    | D2    | Must not be hard-wired to high           |
| 5    | D5    | Irrelevant on most boards unless SPI flash is used |
| 12   | D12   | Sets flash voltage; must not be hard-wired high |
| 15   | D15   | Low silences boot messages               |

In most cases, these pins are safe to use once the device has booted.



### Serial Communication GPIOs

These GPIOs are used for uploading firmware and debugging. They can be repurposed during normal operation, but care must be taken to avoid interference with boot or firmware uploads.

| GPIO | Label | Remark                                |
|------|-------|---------------------------------------|
| 1    | TX0   | Transmit for serial communication    |
| 3    | RX0   | Receive for serial communication     |

Avoid connecting components that alter their state during boot.


### Ghost GPIOs

Some GPIOs are not functional or not exposed:

| GPIO | Remark                   |
|------|--------------------------|
| 20   | May be available in newer revisions |
| 24   | Not functional           |
| 28-30| Not functional           |


> Tags: Microcontroller, ESP32, WROOM, WROVER, 32D, 32E, WROOM-32D, WROOM-32E, WROVER-B, WROVER-IB, PSRAM, GPIO

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/classicesp32?486134031823244200) - created 2024-03-23 - last edited 2024-09-29
