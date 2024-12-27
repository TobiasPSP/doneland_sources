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

In column "Usability" you can quickly see which *GPIOs* can be used. GPIOs **typically** safe-to-use are marked with a bold **Yes**. Always review the column *When Usable?* to understand under which conditions a given GPIO is safe to use.

Also make sure the GPIO you pick is capable of what you intend to do. Not all GPIOs can be used as output, and only some GPIOs accept *analog* input.

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 0    | Yes | after boot | **critical during boot:** *low*: enters bootloader; *high*: runs user code (sketch) | Yes | Yes | - | - | strapping pin |
| 1    | Yes | serial communication is not required (UART1) | debug output at boot | Yes | Yes | - | - | TX for serial communication |
| 2    | Yes | after boot | **critical during boot:** floating/low to enter bootloader | Yes | Yes | Yes | - | Controls onboard LED (if present); strapping pin |
| 3    | Yes | serial communication is not required (UART1) | high at boot | Yes | Yes | - | - | RX for serial communication |
| 4    | **Yes** | Always | - | Yes | Yes | Yes | - | General-purpose input/output |
| 5    | Yes | after boot, primary SPI is not used | Outputs PWM at boot. Controls timing for SDIO slave in some configurations, irrelevant when using SPI flash. | Yes | Yes | - | - | (V)SPI CS |
| 6    | No | never | - | Yes | Yes | Yes | - | internal SPI Flash MISO (Master In Slave Out) - Used for reading data from external SPI flash |
| 7    | No | never | - | Yes | Yes | Yes | - | internal SPI Flash MOSI (Master Out Slave In) - Used for sending data to external SPI flash |
| 8    | No | never | - | Yes | Yes | Yes | - | internal SPI Flash SCLK (Serial Clock) - Provides clock signal for SPI communication with the flash |
| 9    | No | never | - | Yes | Yes | Yes | - | internal SPI Flash CS (Chip Select) - Used to select the SPI flash for communication |
| 10   | No | never | - | Yes | Yes | Yes | - | internal SPI Flash WP (Write Protect) - Used to prevent writing to the flash when high |
| 11   | No | never | - | Yes | Yes | Yes | - | internal SPI Flash HD (Hold) - Used to hold the SPI flash communication (pauses SPI operations) |
| 12   | Yes | after boot, if secondary SPI is not used | **critical during boot:** sets flash voltage (3.3V by default). If set to high during boot, 3.3V flash receives 1.8V and browns out | Yes | Yes | Yes | - | (H)SPI MISO |
| 13   | **Yes** | not using secondary SPI | - | Yes | Yes | Yes | - | (H)SPI MOSI |
| 14   | **Yes** | not using secondary SPI | - | Yes | Yes | Yes | - | (H)SPI CLK |
| 15   | **Yes** | not using secondary SPI | Low disables boot messages | Yes | Yes | Yes | - | (H)SPI CS |
| 16   | **Yes** | UART2 is not used; not using WROVER | - | Yes | Yes | - | - | UART2 RX, used by WROVER for PSRAM |
| 17   | **Yes** | UART2 is not used; not using WROVER | - | Yes | Yes | - | - | UART2 TX, used by WROVER for PSRAM |
| 18   | Yes | not using primary SPI | - | Yes | Yes | - | - | (V)SPI CLK |
| 19   | Yes | not using primary SPI | - | Yes | Yes | - | - | (V)SPI MISO |
| 20   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 21   | Yes | not using I2C | - | Yes | Yes | - | - | I2C SDA |
| 22   | Yes | not using I2C | - | Yes | Yes | - | - | I2C SCL |
| 23   | Yes | not using primary SPI | - | Yes | Yes | - | - | (V)SPI MOSI |
| 24   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 25   | **Yes** | not using DAC1 | - | Yes | Yes | Yes | Yes | Used for DAC1 output when not configured for other purposes. |
| 26   | **Yes** | not using DAC2 | - | Yes | Yes | Yes | Yes | Used for DAC2 output when not configured for other purposes. |
| 27   | **Yes** | Always | - | Yes | Yes | Yes | - | General-purpose input/output |
| 28   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 29   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 30   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 32   | **Yes** | Always | - | Yes | Yes | Yes | - | General-purpose input/output |
| 33   | **Yes** | Always | - | Yes | Yes | Yes | - | General-purpose input/output |
| 34   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 35   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 36   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 37   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |
| 38   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |
| 39   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |


The information above applies to *ESP32S* microcontrollers only. It is not applicable to any of the newer *ESP32 microcontrollers* (e.g., *ESP32-S2*, *ESP32-S3*, or *ESP32-C3*), as their GPIO layouts, while similar, are not identical.

> [!NOTE]
> The table above lists all *ESP32* pins, but your development board most likely does not expose them all. The fewer pins a board exposes, the more *ESP32S* functionality becomes unavailable. This trade-off can be acceptable if your project prioritizes compactness over functionality, and quite a significant number of the pins listed above are not useable anyway.    

## Safe GPIOs 

Ten GPIOs are *always safe to use*: in the column *When Usable?*, they are marked *Always*: GPIO4, GPIO27, GPIO32-39.

These are your **primary GPIOs**, and many projects do not need more than that. Note however that only four of them can be used for *output*:

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 4    | **Yes** | Always | - | Yes | Yes | Yes | - | General-purpose input/output |
| 27   | **Yes** | Always | - | Yes | Yes | Yes | - | General-purpose input/output |
| 32   | **Yes** | Always | - | Yes | Yes | Yes | - | General-purpose input/output |
| 33   | **Yes** | Always | - | Yes | Yes | Yes | - | General-purpose input/output |
| 34   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 35   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 36   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down, typically used for analog inputs |
| 37   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |
| 38   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |
| 39   | **Yes** | Always | - | Yes | - | Yes | - | Input only, no pull-up/pull-down |


### Second-Choice GPIOs
If you require more GPIOs, then there are fortunately many more that can also be perfectly safe to use. Since these GPIOs serve other roles, too, you cannot use them blindly. In order to safely use them, you must check the column *When usable?*, and make your project does not need the functionality that a GPIO is assigned to.

For example, in most projects you do not need a secondary *SPI* interface, secondary serial port, and *DAC* access. In this case, you can  safely use seven more GPIOs: 13-17 and 25-26. 

Here are the second-choice GPIOs that are most commonly used:


| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 5    | Yes | after boot, primary SPI is not used | Outputs PWM at boot. Controls timing for SDIO slave in some configurations, irrelevant when using SPI flash. | Yes | Yes | - | - | (V)SPI CS |
| 13   | **Yes** | not using secondary SPI | - | Yes | Yes | Yes | - | (H)SPI MOSI |
| 14   | **Yes** | not using secondary SPI | - | Yes | Yes | Yes | - | (H)SPI CLK |
| 15   | **Yes** | not using secondary SPI | Low disables boot messages | Yes | Yes | Yes | - | (H)SPI CS |
| 16   | **Yes** | UART2 is not used; not using WROVER | - | Yes | Yes | - | - | UART2 RX, used by WROVER for PSRAM |
| 17   | **Yes** | UART2 is not used; not using WROVER | - | Yes | Yes | - | - | UART2 TX, used by WROVER for PSRAM |
| 25   | **Yes** | not using DAC1 | - | Yes | Yes | Yes | Yes | Used for DAC1 output when not configured for other purposes. |
| 26   | **Yes** | not using DAC2 | - | Yes | Yes | Yes | Yes | Used for DAC2 output when not configured for other purposes. |



### Interface Pins (UART, I2C and SPI)
Peripherals like sensors or displays need a way to communicate with the *ESP32*, and typically this is done using one of three interfaces: *UART* (primitive serial interface), *I2C* (bus interface), or *SPI* (point-to-point high-speed bus interface).


> [!IMPORTANT]
> Be aware that *UART* is also used to connect the microcontroller to your PC and upload new firmware or output information to the terminal. Better avoid messing with the UART1 GPIOs unless you understand all consequences.


Only rarely do projects require *all* these interfaces. Frequently, none of these interfaces is used, and so you can potentially repurpose a maxiumum of additional seven GPIOs:

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 1    | Yes | serial communication is not required (UART1) | debug output at boot | Yes | Yes | - | - | TX for serial communication |
| 3    | Yes | serial communication is not required (UART1) | high at boot | Yes | Yes | - | - | RX for serial communication |
| 18   | Yes | not using primary SPI | - | Yes | Yes | - | - | (V)SPI CLK |
| 19   | Yes | not using primary SPI | - | Yes | Yes | - | - | (V)SPI MISO |
| 21   | Yes | not using I2C | - | Yes | Yes | - | - | I2C SDA |
| 22   | Yes | not using I2C | - | Yes | Yes | - | - | I2C SCL |
| 23   | Yes | not using primary SPI | - | Yes | Yes | - | - | (V)SPI MOSI |




### Unsafe Pins
Some GPIOs can be unsafe to use because they are tied to essential internal functionalities. That's why many development boards do not expose them in the first place. Other boards do expose them because you *may be able to safely use many of them* provided you know their limitations.

#### Strapping Pins
*Strapping pins* are GPIOs that play a crucial role during the *boot process*: they determine whether the microcontroller runs the bootloader code from its ROM, or the user code that you uploaded. Strapping pins also control important configuration parameters such as the voltage for the flash memory. 

You can safely use strapping pins only **after the boot process has completed** and your user code starts executing, and other restrictions may apply (strapping pins may be pulled up or low).

Since your own user code starts executing *after the microcontroller has booted* anyway, shouldn't you be able to safely use all strapping pins at this time? Unfortunately, it is not that simple: while you can indeed safely use these pins in your code, you are *not free to connect these pins to sensors or buttons*. And here is why:

* **Boot Fails:** when you connect buttons or sensors to strapping pins, they can alter their state *at any time*, including the vulnerable boot phase: if a user happens to press such a button when your device resets, or if a sensor is pulling a strapping pin low while you turn on the device, it may no longer boot.

* **Erratic Behavior:** viewed from the opposite angle, strapping pins can change their state outside your control during boot. If you connect i.e. a relais or LED to one of them, you may experience unexpected and potentially dangerous behavior during boot.

That's why strapping pins should be only your last resort, and only be used when you fully understand their role and requirements:


| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 0    | Yes | after boot | **critical during boot:** *low*: enters bootloader; *high*: runs user code (sketch) | Yes | Yes | - | - | strapping pin |
| 2    | Yes | after boot | **critical during boot:** floating/low to enter bootloader | Yes | Yes | Yes | - | Controls onboard LED (if present); strapping pin |
| 12   | Yes | after boot, if secondary SPI is not used | **critical during boot:** sets flash voltage (3.3V by default). If set to high during boot, 3.3V flash receives 1.8V and browns out | Yes | Yes | Yes | - | (H)SPI MISO |


#### Flash Memory SPI

GPIOs 6 to 11 are used for the internal flash interface and are off limits at all times. If you mess with these, you will almost certainly crash the microcontroller or cause severe malfunctions. 

That's why most boards do not expose these GPIOs in the first place. 

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 6    | No | never | - | Yes | Yes | Yes | - | internal SPI Flash MISO (Master In Slave Out) - Used for reading data from external SPI flash |
| 7    | No | never | - | Yes | Yes | Yes | - | internal SPI Flash MOSI (Master Out Slave In) - Used for sending data to external SPI flash |
| 8    | No | never | - | Yes | Yes | Yes | - | internal SPI Flash SCLK (Serial Clock) - Provides clock signal for SPI communication with the flash |
| 9    | No | never | - | Yes | Yes | Yes | - | internal SPI Flash CS (Chip Select) - Used to select the SPI flash for communication |
| 10   | No | never | - | Yes | Yes | Yes | - | internal SPI Flash WP (Write Protect) - Used to prevent writing to the flash when high |
| 11   | No | never | - | Yes | Yes | Yes | - | internal SPI Flash HD (Hold) - Used to hold the SPI flash communication (pauses SPI operations) |


### Ghost Pins

Some pins *should* theoretically exist but the *ESP32S* does not implement them. Such pin numbers are marked as *Ghost pin*.

| GPIO | Usability | When Usable? | Boot Behavior | Digital In | Digital Out | Analog In | Analog Out | Remarks |
|------|-----------|--------------|---------------|------------|-------------|-----------|------------|---------|
| 20   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 24   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 28   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 29   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |
| 30   | No | never | - | - | - | - | - | Ghost pin, not exposed on ESP32S models |



> Tags: ESP32, WROOM, WROVER, 32D, 32E, WROOM-32D, WROOM-32E, WROVER-B, WROVER-IB, PSRAM, GPIO, Pins

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/classicesp32?486134031823244200) - created 2024-03-23 - last edited 2024-12-26
