<img src="/assets/images/processor.png" width="80%" height="80%" />
# ESP32

> ESP32S Microcontrollers - Capable And Affordable For General-Purpose Applications

The *classic ESP32* is known as the *ESP32S*. Since its debut in 2016, many additional *ESP32 variants* have been introduced, such as the [ESP32-C3](https://done.land/components/microcontroller/families/esp/esp32/c3/), [ESP32-S2](https://done.land/components/microcontroller/families/esp/esp32/s2/s2mini/), [ESP32-S3](https://done.land/components/microcontroller/families/esp/esp32/s3/) and [ESP32-C6](https://done.land/components/microcontroller/families/esp/esp32/c6/). However, the *ESP32S* remains highly popular among *DIY makers* because it is particularly straightforward to use:

* **Well-Known:** Most *ESP32 examples* available online or on platforms like YouTube are for either the *ESP8266* or the *ESP32S*. There is an abundance of documentation.
* **Well-Supported:** Regardless of your project, chances are the *ESP32S* is fully supported. After nearly a decade, almost all editors, development environments, home automation systems, and other tools incorporate support for this microcontroller.
* **Well-Balanced:** The *ESP32S* features an exceptionally balanced set of capabilities, including motor control, a *DAC* (*digital-to-analog converter*), *touch input support*, and more—perfect for *DIY makers*.

    It also has a wide support for DIY-friendly technologies: i.e., only the original ESP32S supports both *Bluetooth Classic* and *BLE* (Bluetooth Low Energy), the former still being needed for high-throughput audio (e.g., Bluetooth audio streaming) and device emulation capabilities. All of its successors no longer support classic Bluetooth modes anymore.


<img src="images/esp_wroom_top_front2_t.png" width="60%" height="60%" />


That said, if you’re looking for a *miniature footprint*, cutting-edge *low power consumption*, or compatibility with the latest *wireless standards* like *Matter* or *Thread*, you may want to explore the successors to the *ESP32S* like the [ESP32-C3 SuperMini](https://done.land/components/microcontroller/families/esp/esp32/c3/c3supermini/)

## ESP32 Types

The most popular and widely available *ESP32S* variant is the *WROOM-32D*. However, there are several variations to consider. When purchasing **ESP32** development boards, pay attention to the fine print in the type:

* **WROOM-32:** The original version of the **ESP32**.
* **WROOM-32D:** A revised version featuring a PCB antenna.
* **WROOM-32E:** Similar to the *WROOM-32D* but with an IPX antenna jack for external antennas.
* **WROVER:** Similar to the *WROOM-32* but includes additional 4/8 MB *pSRAM*.
* **WROVER-B:** A version of the *WROOM-32D* with 8 MB *pSRAM*.
* **WROVER-IB:** Same as the *WROVER-B* but includes an IPX antenna jack instead of a built-in PCB antenna.

Additionally, check the memory size when choosing a module. The price difference between *4 MB* and *16 MB* versions is typically minimal, and the extra memory could prove invaluable for future projects.

> [!TIP]
> Be aware of fishy vendors that specify the on-board memory in the unit *MBit*: *32MBit* turn out to be just the minimum *4MB* (*32MBit / 8bit = 4MB*).

When planning to use an *ESP32S* in your project, one of the first things to determine is which *GPIO pins* are safe to use. This is covered in the next section below.

## GPIOs

The GPIO information in this section applies specifically to the *classic ESP32* (ESP32S) and all development boards that use it. In column "Usability" you can quickly identify which *GPIOs* are free to be used. GPIOs **typically** safe-to-use are marked with a bold **Yes**. Also consult the column *When Usable?* to understand under which conditions a given GPIO is safe to use. GPIOs marked with *Always* can always be used and do not interfere with any of the other *ESP32* features.

> [!TIP]
> Verify that the GPIO plan to use is actually capable of what you intend to do. Not all GPIOs can be used as output, and only some accept *analog* input.

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 0    | Yes       | after boot   | **critical during boot:** *low*: enters bootloader; *high*: runs user code (sketch) | Yes | Yes | - | - | strapping pin |
| 1    | Yes       | serial communication is not required (UART1) | debug output at boot | Yes | Yes | - | - | TX for serial communication |
| 2    | Yes       | after boot   | **critical during boot:** floating/low to enter bootloader | Yes | Yes | Yes | - | Controls onboard LED (if present); strapping pin |
| 3    | Yes       | serial communication is not required (UART1) | high at boot | Yes | Yes | - | - | RX for serial communication |
| 4    | **Yes**   | Always       | - | Yes | Yes | Yes | - | General-purpose input/output |
| 5    | Yes       | after boot, primary SPI is not used | Outputs PWM at boot. Controls timing for SDIO slave in some configurations, irrelevant when using SPI flash. | Yes | Yes | - | - | (V)SPI CS |
| 6    | No        | never        | - | Yes | Yes | Yes | - | internal SPI Flash MISO (Master In Slave Out) - Used for reading data from external SPI flash |
| 7    | No        | never        | - | Yes | Yes | Yes | - | internal SPI Flash MOSI (Master Out Slave In) - Used for sending data to external SPI flash |
| 8    | No        | never        | - | Yes | Yes | Yes | - | internal SPI Flash SCLK (Serial Clock) - Provides clock signal for SPI communication with the flash |
| 9    | No        | never        | - | Yes | Yes | Yes | - | internal SPI Flash CS (Chip Select) - Used to select the SPI flash for communication |
| 10   | No        | never        | - | Yes | Yes | Yes | - | internal SPI Flash WP (Write Protect) - Used to prevent writing to the flash when high |
| 11   | No        | never        | - | Yes | Yes | Yes | - | internal SPI Flash HD (Hold) - Used to hold the SPI flash communication (pauses SPI operations) |
| 12   | Yes       | after boot, if secondary SPI is not used | **critical during boot:** sets flash voltage (3.3V by default). If set to high during boot, 3.3V flash receives 1.8V and browns out | Yes | Yes | Yes | - | (H)SPI MISO |
| 13   | **Yes**   | not using secondary SPI | - | Yes | Yes | Yes | - | (H)SPI MOSI |
| 14   | **Yes**   | not using secondary SPI | - | Yes | Yes | Yes | - | (H)SPI CLK |
| 15   | **Yes**   | not using secondary SPI | Low disables boot messages | Yes | Yes | Yes | - | (H)SPI CS |
| 16   | **Yes**   | UART2 is not used; not using WROVER | - | Yes | Yes | - | - | UART2 RX, used by WROVER for PSRAM |
| 17   | **Yes**   | UART2 is not used; not using WROVER | - | Yes | Yes | - | - | UART2 TX, used by WROVER for PSRAM |
| 18   | Yes       | not using primary SPI | - | Yes | Yes | - | - | (V)SPI CLK |
| 19   | Yes       | not using primary SPI | - | Yes | Yes | - | - | (V)SPI MISO |
| 20   | No        | never        | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 21   | Yes       | not using I2C | - | Yes | Yes | - | - | I2C SDA |
| 22   | Yes       | not using I2C | - | Yes | Yes | - | - | I2C SCL |
| 23   | Yes       | not using primary SPI | - | Yes | Yes | - | - | (V)SPI MOSI |
| 24   | No        | never        | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 25   | **Yes**   | not using DAC1 | - | Yes | Yes | Yes | Yes | Used for DAC1 output when not configured for other purposes. |
| 26   | **Yes**   | not using DAC2 | - | Yes | Yes | Yes | Yes | Used for DAC2 output when not configured for other purposes. |
| 27   | **Yes**   | Always       | - | Yes | Yes | Yes | - | General-purpose input/output |
| 28   | No        | never        | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 29   | No        | never        | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 30   | No        | never        | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 32   | **Yes**   | Always       | - | Yes | Yes | Yes | - | General-purpose input/output |
| 33   | **Yes**   | Always       | - | Yes | Yes | Yes | - | General-purpose input/output |
| 34   | **Yes**   | Always       | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 35   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 36   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 37   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |
| 38   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |
| 39   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |

The information above applies to *ESP32S* microcontrollers only. It is not applicable to any of the newer *ESP32 microcontrollers* (e.g., *ESP32-S2*, *ESP32-S3*, or *ESP32-C3*), as their GPIO layouts, while similar, are not identical.

> [!NOTE]
> The table lists all ESP32 pins, but a development board will likely only expose a subset of these. The number of exposed pins doesn't necessarily indicate better quality; rather, it's a balance between ESP32S functionality and compactness/ease-of-use. Many of the pins listed above are not helpful or outright unsafe to use, so even though a [38-pin ESP32 development board](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/esp32devkitcv4/) may expose all pins, this isn’t the most efficient or sophisticated approach. A well-designed board makes a smart trade-off, exposing only the safe-to-use pins while optimizing the footprint by omitting those that have no impact on the user experience.

## Safe GPIOs 

Ten GPIOs are *always safe to use*: in the column *When Usable?*, they are marked *Always*: GPIO4, GPIO27, GPIO32-39.

These are your **primary GPIOs**, and many projects do not need more than that. Note however that only four of them can be used for *output*:

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 4    | **Yes**   | Always       | -             | Yes        | Yes         | Yes       | -          | General-purpose input/output |
| 27   | **Yes**   | Always       | -             | Yes        | Yes         | Yes       | -          | General-purpose input/output |
| 32   | **Yes**   | Always       | -             | Yes        | Yes         | Yes       | -          | General-purpose input/output |
| 33   | **Yes**   | Always       | -             | Yes        | Yes         | Yes       | -          | General-purpose input/output |
| 34   | **Yes**   | Always       | -             | Yes        | -           | Yes       | -          | Input only, no pull-up/pull-down, typically used for analog inputs |
| 35   | **Yes**   | Always       | -             | Yes        | -           | Yes       | -          | Input only, no pull-up/pull-down, typically used for analog inputs |
| 36   | **Yes**   | Always       | -             | Yes        | -           | Yes       | -          | Input only, no pull-up/pull-down, typically used for analog inputs |
| 37   | **Yes**   | Always       | -             | Yes        | -           | Yes       | -          | Input only, no pull-up/pull-down |
| 38   | **Yes**   | Always       | -             | Yes        | -           | Yes       | -          | Input only, no pull-up/pull-down |
| 39   | **Yes**   | Always       | -             | Yes        | -           | Yes       | -          | Input only, no pull-up/pull-down |



### Second-Choice GPIOs
If you require more GPIOs, then there are fortunately many more that can also be perfectly safe to use. Since these GPIOs serve other roles, too, you cannot use them blindly. In order to safely use them, you must check the column *When usable?*, and make your project does not need the functionality that a GPIO is assigned to.

For example, in most projects you do not need a secondary *SPI* interface, secondary serial port, and *DAC* access. In this case, you can safely use seven more GPIOs: 13-17 and 25-26.

Here are the second-choice GPIOs that are most commonly used:

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 5    | Yes       | after boot, primary SPI is not used | Outputs PWM at boot. Controls timing for SDIO slave in some configurations, irrelevant when using SPI flash. | Yes | Yes | - | - | (V)SPI CS |
| 13   | **Yes**   | not using secondary SPI | - | Yes | Yes | Yes | - | (H)SPI MOSI |
| 14   | **Yes**   | not using secondary SPI | - | Yes | Yes | Yes | - | (H)SPI CLK |
| 15   | **Yes**   | not using secondary SPI | Low disables boot messages | Yes | Yes | Yes | - | (H)SPI CS |
| 16   | **Yes**   | UART2 is not used; not using WROVER | - | Yes | Yes | - | - | UART2 RX, used by WROVER for PSRAM |
| 17   | **Yes**   | UART2 is not used; not using WROVER | - | Yes | Yes | - | - | UART2 TX, used by WROVER for PSRAM |
| 25   | **Yes**   | not using DAC1 | - | Yes | Yes | Yes | Yes | Used for DAC1 output when not configured for other purposes. |
| 26   | **Yes**   | not using DAC2 | - | Yes | Yes | Yes | Yes | Used for DAC2 output when not configured for other purposes. |

### Interface Pins (UART, I2C and SPI)
Peripherals like sensors or displays need a way to communicate with the *ESP32*, and typically this is done using one of three interfaces: *UART* (primitive serial interface), *I2C* (bus interface), or *SPI* (point-to-point high-speed bus interface).

> [!IMPORTANT]
> Be aware that *UART* is also used to connect the microcontroller to your PC and upload new firmware or output information to the terminal. Better avoid messing with the UART1 GPIOs unless you understand all consequences.

Only rarely do projects require *all* these interfaces. Frequently, none of these interfaces is used, and so you can potentially repurpose a maximum of additional seven GPIOs:

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 1    | Yes       | serial communication is not required (UART1) | debug output at boot | Yes | Yes | - | - | TX for serial communication |
| 3    | Yes       | serial communication is not required (UART1) | high at boot | Yes | Yes | - | - | RX for serial communication |
| 18   | Yes       | not using primary SPI | - | Yes | Yes | - | - | (V)SPI CLK |
| 19   | Yes       | not using primary SPI | - | Yes | Yes | - | - | (V)SPI MISO |
| 21   | Yes       | not using I2C | - | Yes | Yes | - | - | I2C SDA |
| 22   | Yes       | not using I2C | - | Yes | Yes | - | - | I2C SCL |
| 23   | Yes       | not using primary SPI | - | Yes | Yes | - | - | (V)SPI MOSI |


### Unsafe Pins

Some GPIOs are unsafe to use because they are tied to critical internal functions. Many development boards do not expose these pins, but some do, as certain GPIOs may still be usable if you fully understand their limitations.

#### Strapping Pins

*Strapping pins* play a vital role during the *boot process*. They determine whether the microcontroller runs the bootloader code from its ROM or the user code you’ve uploaded. Strapping pins also control critical configurations, such as the flash memory voltage.

You can safely use strapping pins only **after the boot process has completed** and your user code starts executing. However, certain limitations apply because these pins may be pulled high or low during boot:

- **Boot Failures:** If a sensor or button connected to a strapping pin alters its state during boot (e.g., a button is pressed), it can prevent the microcontroller from booting properly.
- **Erratic Behavior:** Strapping pins may behave unpredictably during boot, potentially causing unintended activation of attached components (e.g., LEDs or relays).

Strapping pins should only be used as a last resort, and only if their roles and restrictions are fully understood:

| GPIO | Usability | When Usable?       | Boot Behavior                                                                                   | Digital In | Digital Out | Analog In | Analog Out | Remarks                                                                                          |
|------|-----------|--------------------|-------------------------------------------------------------------------------------------------|------------|-------------|-----------|------------|--------------------------------------------------------------------------------------------------|
| 0    | Yes       | After boot         | **Critical during boot:** Low enters bootloader; High runs user code                            | Yes        | Yes         | -         | -          | Strapping pin                                                                                   |
| 2    | Yes       | After boot         | **Critical during boot:** Floating or low enters bootloader                                     | Yes        | Yes         | Yes       | -          | Controls onboard LED (if present); strapping pin                                                |
| 12   | Yes       | After boot, if secondary SPI is not used | **Critical during boot:** Sets flash voltage (3.3V by default). High during boot causes 1.8V flash brownout | Yes        | Yes         | Yes       | -          | (H)SPI MISO                                                                                     |

#### Flash Memory SPI Pins

GPIOs 6 through 11 are reserved for internal flash memory communication and must not be used for other purposes. Interfering with these pins will likely crash the microcontroller or cause severe malfunctions. Most boards do not expose these pins.

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks                                                                                   |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|-------------------------------------------------------------------------------------------|
| 6    | No        | Never        | -             | Yes        | Yes         | Yes       | -          | Internal SPI Flash MISO (Master In Slave Out) - Reads data from external SPI flash        |
| 7    | No        | Never        | -             | Yes        | Yes         | Yes       | -          | Internal SPI Flash MOSI (Master Out Slave In) - Sends data to external SPI flash          |
| 8    | No        | Never        | -             | Yes        | Yes         | Yes       | -          | Internal SPI Flash SCLK (Serial Clock) - Provides clock signal for SPI communication      |
| 9    | No        | Never        | -             | Yes        | Yes         | Yes       | -          | Internal SPI Flash CS (Chip Select) - Selects the SPI flash for communication             |
| 10   | No        | Never        | -             | Yes        | Yes         | Yes       | -          | Internal SPI Flash WP (Write Protect) - Prevents writing to the flash when high           |
| 11   | No        | Never        | -             | Yes        | Yes         | Yes       | -          | Internal SPI Flash HD (Hold) - Pauses SPI operations                                      |

#### Ghost Pins

Some pin numbers *appear* valid but are not implemented in the *ESP32S* microcontroller. These *ghost pins* cannot be used under any circumstances.

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks                           |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|-----------------------------------|
| 20   | No        | Never        | -             | -          | -           | -         | -          | Ghost pin, not implemented       |
| 24   | No        | Never        | -             | -          | -           | -         | -          | Ghost pin, not implemented       |
| 28   | No        | Never        | -             | -          | -           | -         | -          | Ghost pin, not implemented       |
| 29   | No        | Never        | -             | -          | -           | -         | -          | Ghost pin, not implemented       |
| 30   | No        | Never        | -             | -          | -           | -         | -          | Ghost pin, not implemented       |


> Tags: ESP32, WROOM, WROVER, 32D, 32E, WROOM-32D, WROOM-32E, WROVER-B, WROVER-IB, PSRAM, GPIO, Pins, Bluetooth Classic, BLE

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/classicesp32?486134031823244200) - created 2024-03-23 - last edited 2024-12-26
