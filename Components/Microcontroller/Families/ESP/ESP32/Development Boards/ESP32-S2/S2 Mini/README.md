<img src="/assets/images/processor.png" width="80%" height="80%" />


# S2 Mini

> Powerful ESP32-S2 Board That Works With ESP8266 Shields

The pink [S2 Mini microcontroller board](https://www.wemos.cc/en/latest/s2/s2_mini.html) (also known as *LOLIN S2 Mini* or *Wemos S2 Mini*) is an affordable and powerful option when you need *many GPIOs* and have space constraints. 


## Overview

The *ESP32-S2 Mini* is powered by the **single-core** *ESP32-S2 microcontroller*. Unlike most other *ESP32* variants, this microcontroller lacks **Bluetooth support**.

Despite these limitations, the *ESP32-S2* is an exceptional microcontroller for several reasons: 

* **DACs:**    
   It retains some features from the original *ESP32*, such as the two built-in *DACs* (*Digital-to-Analog Converters*)—a useful capability removed in all other *ESP32* successors.
* **Full USB-Stack Support:**    
   Additionally, it is the first *ESP32* variant to offer full USB stack support, enabling it to emulate a wide range of USB device types, not just *human input devices*.

    For example, the *ESP32-S2* is the first *ESP32* family member that can natively [emulate mass storage devices](https://github.com/hathach/tinyusb/discussions/583), such as USB sticks. Older microcontrollers could only emulate *human input devices* like keyboards and mice. To dive deeper into these capabilities, check out the [TinyUSB library](https://github.com/adafruit/Adafruit_TinyUSB_Arduino).

While the *ESP32-S2 Mini* comes with a modest *4MB flash memory*, it includes an additional *2MB high speed PSRAM*. This extra memory can be particularly useful for applications that involve connecting displays to the board.


### The New ESP8266?

In some respect, the *ESP32-S2 Mini* can be seen as the successor to the widely popular *ESP8266*:

- very affordable (comparable to *ESP8266* boards)
- many GPIOs
- same small, flat form factor of the *Wemos D1 Mini*
- supports shields designed for the *D1 Mini* (e.g., battery shields)

It blends these features with some of the best features of the *ESP32* world: 

* high speed memory
* fast CPU core
* much more efficient deep sleep
* two built-in DACs
* hardware support for cryptography
* full native USB stack support and no need for UARTs anymore.

| Use Case                                | Suitability |
|-----------------------------------------|-------------|
| Controlling devices via many GPIOs      | +++         |
| Migrating from *ESP8266*                | +++         |
| Integrating into small devices          | +++         |
| Beginner-friendly / ease-of-use         | o           |
| Bluetooth                               | -           |
| Demanding calculations                  | -           |
| Multi-tasking                           | -           |


The *ESP32-S2 Mini* preserves pin compatibility with the *ESP8266 D1 Mini*. Additional features are exposed via two extra pin header rows. This compatibility makes it an excellent replacement for *ESP8266*-based projects while allowing continued use of shields originally designed for the *D1 Mini*, such as battery shields.

<img src="images/esp32_s2_shield_esp8266_compare_t.png" width="80%" height="80%" />

### Alternatives

Here is a decision matrix for *budget ESP microcontrollers*:

| What I need | What I use |
| --- | --- |
| massive number of GPIOs | *ESP32-S2 Mini* |
| extremely small form factor | [ESP32-C3 Super Mini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/c3supermini/) |
| battery support | [Lolin32 Lite](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/lolin32lite/) |
| small display and battery support | [Lilygo T-Display](https://done.land/components/microcontroller/families/esp/vendorsandseries/lilygot-display/) |
| 100% ESP32 Compatibility | [ESP32S DevKitC V4](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32s/esp32devkitcv4/) |
| anything beyond that | [ESP32-S3](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s3/)



## Arduino Framework


For the *S2 Mini*, use the board definition `LOLIN S2 Mini`.


### ArduinoIDE
Verify that you have selected the board `LOLIN S2 Mini`:


<img src="images/esp32s2mini_arduinoide2_t.png" width="80%" height="80%" />

Verify that the optional tool settings have been set correctly. In menu `Tools`, check these options:

* **USB CDC On Boot:** must be set to *Enabled*  
* **Upload Mode:** must be set to *UART0*

<img src="images/esp32s2mini_arduinoide1_t.png" width="100%" height="100%" />

### platformio
Use this `platformio.ini`:

````
[env:lolin_s2_mini]
platform = espressif32
board = lolin_s2_mini
framework = arduino
build_flags = 
    -DARDUINO_USB_SERIAL
````




<details><summary>Example Code</summary><br/>

Use this code to test-drive the settings with your *S2 Mini*: the built-in LED should start blinking with *1 Hz* frequency, and the serial interface prints the *GPIO constants* and their values to the *ArduinoIDE Serial Monitor*: 


````c++
#include <Arduino.h>

void showPins() {
  // prints currently valid pin assignments to terminal:
  Serial.println("Pin Definitions for the Board:");

  // SPI Pins
  Serial.println("\nSPI Pins:");
  Serial.printf("MISO: %d\n", MISO);
  Serial.printf("MOSI: %d\n", MOSI);
  Serial.printf("SCK: %d\n", SCK);
  Serial.printf("SS (CS): %d\n", SS);

  // I2C Pins
  Serial.println("\nI2C Pins:");
  Serial.printf("SDA: %d\n", SDA);
  Serial.printf("SCL: %d\n", SCL);

  // LED Pin
  Serial.println("\nLED Pin:");
#ifdef LED_BUILTIN
  Serial.printf("LED_BUILTIN: %d\n", LED_BUILTIN);
#else
  Serial.println("No LED_BUILTIN defined for this board.");
#endif

  // DAC Pins
  Serial.println("\nDAC Pins (if available):");
#if defined(DAC1) && defined(DAC2)
  Serial.printf("DAC1: %d\n", DAC1); // Often GPIO25
  Serial.printf("DAC2: %d\n", DAC2); // Often GPIO26
#else
  Serial.println("DAC not available on this board.");
#endif

  // UART/Serial Pins
  Serial.println("\nSerial Pins:");
#if defined(TX) && defined(RX)
  Serial.printf("TX: %d\n", TX);
  Serial.printf("RX: %d\n", RX);
#else
  Serial.println("Default UART TX and RX not defined for this board.");
#endif
}


void setup() {
  // start serial output (baud rate does not matter with USB CDC)
  Serial.begin();
  // set built-in LED on GPIO8 for output
  pinMode(LED_BUILTIN, OUTPUT);
  // wait for the serial output to be ready
  delay(5000);
  // output pin assignments
  showPins();
}

void loop() {
  // blinks built-in LED at 1Hz to check that firmware is running:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
````
</details>




### ESPHome
In *ESPHome*, use the board `lolin_s2_mini`:

````
esp32:
  board: lolin_s2_mini
  framework:
    type: arduino
````

> [!IMPORTANT]
> If you upload via USB cable, you may have to *enable firmware upload mode* manually: hold button `0`, then press `RST`. Once upload completes, press `RST` to return to normal mode.



<details><summary>Examle configuration</summary><br/>

Here is an example configuration showing how yo interface a `ili9341` *TFT display* using *hardware SPI*:

````
esp32:
  board: lolin_s2_mini
  framework:
    type: arduino

output:
  - platform: ledc
    pin: 3
    id: gpio_3_backlight_pwm
    
light:
  - platform: monochromatic
    output: gpio_3_backlight_pwm
    name: "Touchdisplay Licht"
    id: back_light
    restore_mode: ALWAYS_ON

spi:
  clk_pin: GPIO07
  mosi_pin: GPIO11
  miso_pin: GPIO09

display:
  - platform: ili9xxx
    model: ili9341
    dc_pin: GPIO05
    cs_pin: GPIO12
    invert_colors: false
    show_test_card: true
    reset_pin: GPIO01
````

</details>

### GPIO Pin Assignments
The board definition `LOLIN S2 Mini` defines these *GPIO* pin constants:

| GPIO | Constant | Description |
| :---: | :---: | --- |
| 15 | `LED_BUILTIN` | built-in blue LED, *high active* (*on* when *high) |
|11 | `MOSI` | *SPI:* MOSI |
| 9 | `MISO`| *SPI:* MISO |
| 7 | `SCK` | *SPI:* SCK |
| 12 | `SS` | *SPI:* SS/CS |
| 33 | `SDA` | *I2C:* SDA |
| 35 | `SCL`| *I2C:* SCL | 

Since these constants are used for most libraries, make sure you use these *GPIOs* for fast hardware *SPI* and *I2C*.

If you'd like to use `DACL1` and `DACL2` or other constants, define them manually in your source code:

````c++
#define DAC1 17
#define DAC2 18
````





## Expansion Board

The *ESP32-S2 Mini* cannot be used directly on standard breadboards due to its dual header rows. The easiest workaround is to get two double-row 8-pin female *header sockets* (2.54mm pitch), and solder them onto the front side of the PCB.

<img src="images/esp32-s2_mini_devboard-removebg-preview.png" width="100%" height="100%" />

This way, you can use regular *DuPont* wires for prototyping, essentially turning your *ESP32-S2 Mini* into a miniature breakout board. 

> [!IMPORTANT]
> Make sure to use decent solder temperatures: there are a lot of pins to solder, so the PCB can heat up easily. When the PCB gets too hot, sensitive components may be damaged. ALso, make sure no solder is dripping through the through-holes, potentially causing short circuits underneath the *header socket*.   




## 27 Safely Usable GPIOs

The *ESP32-S2* microcontroller provides **43 GPIOs**, of which a maximum of [30 GPIOs are safely usable as input and output](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/#30-recommended-general-purpose-gpios). Since the *ESP32-S2 Mini* uses the ESP32-S2FN4R2 chip with integrated flash memory, it doesn't require external flash memory, freeing up more GPIOs.

The *S2 Mini* exposes **27 GPIOs**, which is sufficient for most projects.

| GPIO  | Remark                                |
|-------|---------------------------------------|
| 1–18  | *Input and output, pullup and pulldown resistors* |
| 21    | *Input and output, pullup and pulldown resistors* |
| 33–40 | *Input and output, pullup and pulldown resistors* |

All GPIOs support internal pullup and pulldown resistors.

<img src="images/s2_mini_top_overview_t.png" width="40%" height="40%" />

### Built-In LED

| GPIO | Purpose | Remark |
| --- | --- | --- |
| 15 | built-in blue LED | **high-active:**  *high*=on, *low*=off |



## S2 Mini Technical Data

| Item | Value |
| --- | --- |
| CPU | ESP32-S2FN4R2 WiFi SoC, Xtensa single-core 32-bit LX7 microprocessor |
| Speed | 240MHz |
| Coprocessor | RISC-V ULP Coprocessor |

> [!TIP]
> The relatively new *ESP32-S2FN4R2* chip integrates flash and PSRAM directly into the *ESP32-S2 silicon*, saving space and reducing design complexity.

Due to its compact form factor, the *S2 Mini* does not expose all available hardware pins. However, the *27 GPIOs* provided are sufficient for most DIY projects.

| Item | Value |
| --- | --- |
| Digital IO Pins | 27 |
| Clock Speed | 240MHz |
| Flash | 4MB |
| PSRAM | 2MB |
| SRAM | 320KB |
| SRAM in RTC | 16KB (8KB accessible by ULP coprocessor) |
| Temperature Sensor | -20°C to +110°C |
| eFuse | 1792-bit for user data |
| SAR ADC | 2×13-bit, up to 20 channels, optimized for voltages <2.45V |
| DAC | 2×8-bit (Note: Second DAC has [fixable issues](https://vuknikolic.rs/en/posts/esp32/dac_fix/)) |
| Touch | 12× touch sensing IOs |
| SPI | 4×, SPI2 and SPI3 usable: HSPI and VSPI |
| I2S | 1× |
| I2C | 2× |
| UART | 2× |
| DVP 8/16 Camera Interface | 1× |
| LCD Interface | 1× 8-bit serial, 1× 8/16/24-bit parallel |
| TWAI (CAN-Bus) | 1×, ISO11898-1 (CAN Specification 2.0) |
| PWM Controller | 8× |
| USB OTG 1.1/PHY | Host and device support |
| Cryptographic | Hardware accelerators for AES (ECB/CBC/OFB/CFB/CTR, GCM), SHA, RSA, ECC (Digital Signature) |
| Size | 34.4×25.4mm |
| Weight | 2.4g |

The *ESP32-S2* offers improved power consumption in its sleep modes compared to the classic *ESP32*:

| Operation | Current |
| --- | --- |
| Normal (WiFi) | 310mA peak |
| Modem-Sleep | 12-19mA |
| Light-Sleep | 450µA |
| Deep-Sleep | 20-190µA |

Power regulation is managed by the *ME6211C33* voltage regulator:

| Item | Value |
| --- | --- |
| Input Voltage | 4.7-6.5V |
| Operating Voltage | 2-6V |
| Max Current | 500mA @ 4.3V input / 3.3V output |


## Hardware I2C Interface
Any pin can *emulate* an *I2C* interface (or define additional ones). However, only the *hardware I2C interface* uses optimized hardware that reduces load on the microcontroller and operates at higher speeds.

| Pin | Label | Description |
| --- | --- | --- |
| 33 | SDA | Data line |
| 35 | SCL | Clock line |

## Hardware SPI Interface
Any pin can *emulate* an *SPI* interface (or define additional ones). However, only the *hardware SPI interface* uses optimized hardware that reduces load on the microcontroller. For components requiring high data rates (such as *displays*), using *hardware SPI* is recommended for much better performance and higher frame rates.

| Pin | Label | Alternate Labels | Description |
| --- | --- | --- | --- |
| 11 | MOSI | SDO, SDA | Master Out Slave In – Data sent from the master to the slave. |
| 9 | MISO | SDI | Master In Slave Out – Data sent from the slave to the master. |
| 7 | CLK | SCL, SCLK | Clock – Synchronizes communication between the master and the slave. |
| 12 | SS | Chip Select | Used by the master to select the active slave. |

> [!TIP]
> Since the *S2 Mini* is pin-compatible with the *D1 Mini*, you can refer to *D1 Mini* documentation when specific details for the *ESP32-S2* are unavailable. Documentation for the *D1 Mini* is more widely available.

### Pins and Compatible Shields

The *S2 Mini* board has 32 pins organized in two rows of 16 pins each. The *outer* row of pins is compatible with the *ESP8266 D1 Mini*. This allows the *S2 Mini* to use existing *D1 Mini-compatible shields* seamlessly.

<img src="images/s2_pins.png" width="100%" height="100%" />

To ensure maximum backwards compatibility, the *S2 Mini* designers rearranged certain pin pairs. Pins *2-11* are organized in *pairs* (e.g., *2/3*, *4/5*, *6/7*, *8/9*, *10/11*). However, some pairs are reversed; for example, *12* and *13* are placed as *13/12* instead of *12/13*. This adjustment ensures that both *11* and *12* (which are used for the *hardware SPI interface*) remain accessible when using *D1 Mini-compatible shields*.

Without this reversal, pin *12* would have been located on the *inner* rows and become inaccessible for *D1 Mini* shields.

<img src="images/esp32_s2_shield_pns_top_t.png" width="80%" height="80%" />

This compatibility enables the use of *battery shields* for adding charging functionality and battery power supply, making it easier to create portable projects.

<img src="images/esp32_s2_shield_side_t.png" width="40%" height="40%" />

> [!CAUTION]
> Some *software-configurable* pins (like the GPIO pins and the built-in LED pin) are **not compatible** with the *ESP8266 D1 Mini*. When converting software from the *ESP8266 D1 Mini* to the *S2 Mini*, ensure that pin numbers are reviewed and reassigned as necessary.

### S2 Mini Pinout

The pin numbers printed on the backside of the *S2 Mini* breakout board correspond to the exposed *GPIO* numbers. For instance, the pin marked *1* represents *GPIO1*.

| Pin | Remark | Description |
| --- | --- | --- |
| EN | | Reset button |
| 3V3 | | Direct power supply to the CPU |
| VBUS | | Connected to the ME6211C33 voltage regulator |
| 0 | Not exposed | Boot button pulls this pin low |
| 1-6 | | General-purpose: Analog input (ADC1) and digital input/output |
| 7 | SPI SCK | General-purpose: Analog input (ADC1) and digital input/output |
| 8 | | General-purpose: Analog input (ADC1) and digital input/output |
| 9 | SPI MISO | General-purpose: Analog input (ADC1) and digital input/output |
| 10 | | General-purpose: Analog input (ADC1) and digital input/output |
| 11 | SPI MOSI | General-purpose: Analog input (ADC2) and digital input/output |
| 12 | SPI SS | General-purpose: Analog input (ADC2) and digital input/output |
| 13-14 | | General-purpose: Analog input (ADC2) and digital input/output |
| 15 | Internal LED | General-purpose: Analog input (ADC2) and digital input/output |
| 16 | | General-purpose: Analog input (ADC2) and digital input/output |
| 17 | DAC1 | General-purpose: Analog input (ADC2) and digital input/output |
| 18 | DAC2 | General-purpose: Analog input (ADC2) and digital input/output |
| 19, 20 | Not exposed | *USB D1/D2*, connected to the *USB-C* connector | 
| 21 | | General-purpose digital input/output |
| 33 | I2C SDA | General-purpose digital input/output |
| 34 | | General-purpose digital input/output |
| 35 | I2C SCL | General-purpose digital input/output |
| 36-40 | | General-purpose digital input/output |

> [!CAUTION]
> The *ADC2* (used for analog inputs on *GPIO11-GPIO18*) is only available when *WiFi* is disabled. This limitation is due to shared hardware resources.

<img src="images/esp32_s2_shield_pins_angle_t.png" width="80%" height="80%" />



## Fixing Missing Pins

When programming the *S2 Mini* in *PlatformIO*, the translation between the true *hardware pins* and the *common pin labels* is handled automatically. The *IDE* refers to the appropriate version of the file `pins_arduino.h` in the folder: `%USERPROFILE%\\.platformio\packages\framework-arduinoespressif32\variants\lolin_s2_mini`.

### Pin Declarations Missing

At the time of this writing, the `pins_arduino.h` file exists but is incomplete. It does not define the *common pin labels* for all *digital pins*.

If your source code refers to a **D*x*** pin (e.g., `D2`) and you try to compile it, the compilation will fail with an exception because these labels are undefined.

Currently, no *officially updated version* of this file is available. To resolve this issue, you have two options:

1. **Quick Fix:**  
   Replace the *common pin labels* in your source code with the actual *hardware pin* numbers. For example, change `D2` to `2`. Since the *S2 Mini* uses hardware pin numbers directly, this approach works. However, it makes your code specific to the *S2 Mini*, meaning it will no longer work on other microcontroller boards.

2. **Permanent Fix:**  
   Open the file `pins_arduino.h` in a text editor and manually add the missing declarations. Below is an example of the declarations you can add. Be aware that your changes may be overwritten during future updates to the *Espressif32 Arduino framework*.


````c++
#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

// Default USB Settings
#define USB_VID 			0x303a
#define USB_PID 			0x80C2
#define USB_MANUFACTURER 	"WEMOS.CC"
#define USB_PRODUCT 		"LOLIN-S2-MINI"
#define USB_SERIAL 			"0"


// Default USB FirmwareMSC Settings
#define USB_FW_MSC_VENDOR_ID 		"ESP32-S2" 		//max 8 chars
#define USB_FW_MSC_PRODUCT_ID 		"Firmware MSC"	//max 16 chars
#define USB_FW_MSC_PRODUCT_REVISION	"1.23" 			//max 4 chars
#define USB_FW_MSC_VOLUME_NAME 		"S2-Firmware" 	//max 11 chars
#define USB_FW_MSC_SERIAL_NUMBER 	0x00000000

#define EXTERNAL_NUM_INTERRUPTS 46
#define NUM_DIGITAL_PINS        48
#define NUM_ANALOG_INPUTS       20

#define analogInputToDigitalPin(p)  (((p)<20)?(analogChannelToDigitalPin(p)):-1)
#define digitalPinToInterrupt(p)    (((p)<48)?(p):-1)
#define digitalPinHasPWM(p)         (p < 46)

static const uint8_t LED_BUILTIN = 15;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility

static const uint8_t TX = 39;
static const uint8_t RX = 37;

static const uint8_t SDA = 33;
static const uint8_t SCL = 35;

static const uint8_t SS    = 12;
static const uint8_t MOSI  = 11;
static const uint8_t MISO  = 9;
static const uint8_t SCK   = 7;

static const uint8_t A0 = 1;
static const uint8_t A1 = 2;
static const uint8_t A2 = 3;
static const uint8_t A3 = 4;
static const uint8_t A4 = 5;
static const uint8_t A5 = 6;
static const uint8_t A6 = 7;
static const uint8_t A7 = 8;
static const uint8_t A8 = 9;
static const uint8_t A9 = 10;
static const uint8_t A10 = 11;
static const uint8_t A11 = 12;
static const uint8_t A12 = 13;
static const uint8_t A13 = 14;
static const uint8_t A14 = 15;
static const uint8_t A15 = 16;
static const uint8_t A16 = 17;
static const uint8_t A17 = 18;
static const uint8_t A18 = 19;
static const uint8_t A19 = 20;

static const uint8_t D1 = 1;
static const uint8_t D2 = 2;
static const uint8_t D3 = 3;
static const uint8_t D4 = 4;
static const uint8_t D5 = 5;
static const uint8_t D6 = 6;
static const uint8_t D7 = 7;
static const uint8_t D8 = 8;
static const uint8_t D9 = 9;
static const uint8_t D10 = 10;
static const uint8_t D11 = 11;
static const uint8_t D12 = 12;
static const uint8_t D13 = 13;
static const uint8_t D14 = 14;
static const uint8_t D15 = 15;
static const uint8_t D16 = 16;
static const uint8_t D17 = 17;
static const uint8_t D18 = 18;
static const uint8_t D33 = 33;
static const uint8_t D34 = 34;
static const uint8_t D35 = 35;
static const uint8_t D36 = 36;
static const uint8_t D37 = 37;
static const uint8_t D38 = 38;
static const uint8_t D39 = 39;
static const uint8_t D40 = 40;

static const uint8_t T1 = 1;
static const uint8_t T2 = 2;
static const uint8_t T3 = 3;
static const uint8_t T4 = 4;
static const uint8_t T5 = 5;
static const uint8_t T6 = 6;
static const uint8_t T7 = 7;
static const uint8_t T8 = 8;
static const uint8_t T9 = 9;
static const uint8_t T10 = 10;
static const uint8_t T11 = 11;
static const uint8_t T12 = 12;
static const uint8_t T13 = 13;
static const uint8_t T14 = 14;

static const uint8_t DAC1 = 17;
static const uint8_t DAC2 = 18;

#endif /* Pins_Arduino_h */
````
## Uploading Firmware

Follow these steps to upload new firmware to the *S2 Mini* using *PlatformIO*:

1. **Connect the Board**:  
   Use a USB-C cable to connect the *S2 Mini* to your computer. Ensure the cable is a *data cable* and not a *power-only cable*.

2. **Enter Flash Mode**:  
   - Hold down the *0* button.
   - While holding *0*, short-press the *RST* button.
   - Release the *RST* button. Your computer should play the sound indicating *new USB device discovery*.

3. **Upload the Firmware**:  
   - In *PlatformIO*, click the *Upload* button.  
   - *PlatformIO* will automatically:
     - Search for a port.
     - Reset the *S2 Mini*.
     - Find the port again and upload the firmware.

4. **Execute the Sketch**:  
   Once the upload completes, short-press the *RST* button again. The uploaded sketch should now execute.



### Troubleshooting USB Recognition Issues

If the *S2 Mini* is not recognized by your computer (e.g., no "new USB device" sound plays after following the above steps), try the following:

- Ensure the *USB cable* is fully plugged in at both ends.
- Reverse the plugs (try flipping the cable's orientation if possible).
- Use a different USB-C cable. Some cables may not make proper contact due to low-quality connectors.

> [!TIP]
> If changing the USB cable does not resolve the issue, try rebooting your computer. USB communication can sometimes fail over time, or other running software may interfere with USB device discovery. A reboot often resolves these unrelated USB issues, which can occur with any microcontroller board.

If the problem persists, check if the board is unusually warm. Poor build quality in some *S2 Mini* units may cause issues such as solder residue short-circuiting the CPU contacts. Inspect the board closely, paying attention to solder joints and potential defects.


### ESPHome

To flash the *S2 Mini* with [ESPHome](https://esphome.io/), note the following:

- The [ESPHome Web Tool](https://web.esphome.io/) is **incompatible** with this board (as of this writing).
- Use the [manual provisioning workaround](https://esphome.io/guides/manual-provisioning.html) to upload the ESPHome firmware or to provision the board with the generic ESPHome firmware.

Once the ESPHome firmware has been successfully uploaded via USB at least **once**, you can use *Over-The-Air (OTA)* updates for future firmware uploads. This approach bypasses the *S2 Mini USB incompatibilities* entirely for subsequent updates.


## Manually Enabling Firmware Update Mode
If your *development environment* does not automatically switch to *firmware upload mode*, enable *firmware upload mode manually* before trying to upload new firmware:

1. Keep the button `0` pressed
2. Push the button `RST`
3. Release the button `0`

Once the firmware has been uploaded, manually press `RST` once (without pressing `0`) to exit *firmware upload mode* and run the newly uploaded firmware.

> [!TIP]
> Whether or not your development board handles this switch auto-magically may depend on a variety of factors, including the correct board definition you selected.

## Materials

[S2 Mini Datasheet](materials/esp32-s2_datasheet.pdf)   
[S2 Mini Schematics](materials/s2_mini_schematic.pdf)   
[S2 Mini Dimensions](materials/s2mini_dimensions.pdf)   
[ME6211 voltage regulator](materials/me6211_datasheet.pdf)   



> Tags: Microcontroller, ESP32, S2, ESP32 S2, Shield, Pin, I2C, SPI

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-s2/s2mini?273412051205244129) - created 2024-05-04 - last edited 2024-07-16
