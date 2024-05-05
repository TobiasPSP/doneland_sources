<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# S2 Mini

> Powerful ESP32 S2 Board That Works With ESP8266 Shields


The *S2 Mini* microcontroller board (aka *LOLIN S2 Mini* or *Wemos S2 Mini*) is a very popular and powerful board that uses the same *form factor* as its equally popular predecessor, the *ESP8266 D1 Mini*.



<img src="images/s2_mini_top_overview_t.png" width="80%" height="80%" />


This enables the *S2 Mini* to continue to use *shields* that were designed for the *D1 Mini*, i.e. *battery shields*.


<img src="images/esp32_s2_shield_esp8266_compare_t.png" width="80%" height="80%" />



## S2 Mini Technical Data

Due to its form factor, the *S2 Mini* does not expose *all available hardware pins*. With *27 GPIOs*, this board is most sufficient for most *DIY projects*.




| Item | Value |
| --- | --- |
| Operating Voltage | 3.3V (2.5-3.6V) |
| Digital IO Pins | 27 |
| Clock Speed | 240MHz |
| Flash | 4MB |
| PSRAM | 2MB |
| Size | 34.4x25.4mm |
| Weight | 2.4g |

### Pins And Compatible Shields

All pins that are not *sofware-assignable* are *compatible with ESP8266 D1 Mini* pins:

<img src="images/s2_pins.png" width="100%" height="100%" />

Specifically, the pins for *GND*, *3.3V*, and *VBus* (*5V*) are hardware-identical:


<img src="images/esp32_s2_shield_pns_top_t.png" width="80%" height="80%" />


This allows users to continue to use *shields* that were designed for *ESP8266*, i.e. *battery shields* that add *charging* and a battery to *portable projects*:


<img src="images/esp32_s2_shield_side_t.png" width="80%" height="80%" />


> [!CAUTION]
> All *software-configurable* pins (such as *GPIOs* and the pin for the built-in *LED*) are **not compatible** with *ESP8266 D1 Mini*. Since these pins can be adjusted freely in software in the *S2*, converting software from *ESP8266 D1 Mini* to *S2 Mini* is a matter of checking and potentially reassigning pin numbers.

### S2 Mini Pinout


The pin numbers printed on the backside of the breakout board represent the exposed *GPIO* numbers. I.e., pin marked *1* represents *GPIO1*.


| Pin |  Remark | Description |
| --- |  --- | --- |
| 1-6 |  | general purpose: analog input (ADC1) and digital in/output |
| 7 | SPI SCK | general purpose: analog input (ADC1) and digital in/output |
| 8 | | general purpose: analog input (ADC1) and digital in/output |
| 9 | SPI MISO | general purpose: analog input (ADC1) and digital in/output |
| 10 | | general purpose: analog input (ADC1) and digital in/output |
| 11 | SPI MOSI | general purpose: analog input (ADC2) and digital in/output |
| 12 | SPI SS | general purpose: analog input (ADC2) and digital in/output |
| 13-14 | | general purpose: analog input (ADC2) and digital in/output |
| 15 | internal LED | general purpose: analog input (ADC2) and digital in/output |
| 16 | | general purpose: analog input (ADC2) and digital in/output |
| 17 | DAC1 | general purpose: analog input (ADC2) and digital in/output |
| 18 | DAC2 | general purpose: analog input (ADC2) and digital in/output |
| 21 | | general purpose digital in/output |
| 33 | I2C SDA | general purpose digital in/output |
| 34 | | general purpose digital in/output |
| 35 | I2C SCL | general purpose digital in/output|
| 36-40 | | general purpose digital in/output |



> [!CAUTION]
> The *ADC2* (and thus *analog inputs* at *GPIO11-GPIO18*) can only be used when *WiFi* is *disabled*.




<img src="images/esp32_s2_shield_pins_angle_t.png" width="80%" height="80%" />

## Prototyping

The *S2 Mini* uses *dual line header pins* (2x8 pins on both sides for a total of 32 pins).


<img src="images/s2_mini_dual_header_t.png" width="80%" height="80%" />


This design was necessary to keep the *hardware compatibility* to the predecessor *ESP8266 D1 Mini* board: the *outer* 8-pin headers match the header pins in a *ESP8266 D1 Mini* (for power and *GND* pins at least).

You cannot of course use *dual line header pins* with a prototyping bread board as this would *short circuiting* both header pin lines.

### Soldering Header Pins

For prototyping, it makes most sense to solder the *outer* header pins normally for a *ESP8266 D1 Mini*-compatible foot print. 


<img src="images/esp32_s2_prototyping_t.png" width="80%" height="80%" />


The *inner* header pins should *not be connected* to the bread board. Instead, solder the header pins *on top*: this way, the additional pins can be connected using *female DuPont cables*.




<img src="images/esp32_s2_prototyping2_t.png" width="80%" height="80%" />


## Fixing Missing Pins

When programming the *S2 Mini* in *platform.io*, the translation between true *hardware pins* and *common pin labels* is performed automatically: the *IDE* looks up the appropriate version of the file *pins_arduino.h* in the folder *%USERPROFILE%\.platformio\packages\framework-arduinoespressif32\variants\lolin_s2_mini*.

### Pin Declarations Missing

At the time of this writing, the appropriate file *pins_arduino.h* does exit but is incomplete. It does not define the *common pin labels* for all *digital pins*. 

Whenever you try and compile source code that refers to a **D*x*** pin, compilation files with an exception.

There does not seem to exist an *officially updated version* of this file. To fix, you have two choices:

* **Quick Fix:** Replace the *common pin labels* in the code with the actual *hardware pin* numbers. Since with *S2 Mini* the numbers are identical, you would i.e. change *D2* by *2*. If you do this, the code will compile but is now *specific* for *S2 Mini* and will no longer work on different microcontroller boards.
* **Permanent Fix:** Open the file *%USERPROFILE%\.platformio\packages\framework-arduinoespressif32\variants\lolin_s2_mini\pins_arduino.h* in a text editor, and add the missing declarations. You find an example below. When you do this, you might lose your changes with the next update of the *espressif32 arduino framework*, though.

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

## Materials

[S2 Mini Datasheet](materials/esp32-s2_datasheet.pdf)   
[S2 Mini Schematics](materials/s2_mini_schematic.pdf)   
[S2 Mini Dimensions](materials/s2mini_dimensions.pdf)   


> Tags: Microcontroller, ESP32, S2, ESP32 S2, Shield, Pin, I2C, SPI

[Visit Page on Website](https://done.land/components/microcontroller/esp/esp32/s2/s2mini?273412051205244129) - created 2024-05-04 - last edited 2024-05-04
