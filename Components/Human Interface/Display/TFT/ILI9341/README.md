<img src="/assets/images/screenwire.png" width="100%" height="100%" />
# ILI9341

> Drives TFT Displays Up To 240x320 Pixels At 262K Colors (18bit)

The *ILI9341* is a versatile *TFT display driver IC* commonly used for small to medium-sized displays with resolutions of up to *240x320* pixels at full *18bit color* (262 thousand different colors). It is still a very popular TFT driver, however more modern drivers like the [ST7789](https://done.land/components/humaninterface/display/tft/st7789/) are starting to replace it.

The *ILI9341* is marginally less power efficient than its successors like the *ST7789*. It is slightly more affordable, though, so you find it in cheaper display designs. 

Both drivers support the same major interfaces (like [SPI](https://done.land/fundamentals/interface/spi)), the same maximum resolution (*240x320*), the same *18-bit* maximum colors, and can be controlled with the same software libraries (i.e. *ESPHome* [ILI9xxx component](https://esphome.io/components/display/ili9xxx#ili9xxx)). 

Given the typical DIY use cases, both drivers can be used interchangeably for most projects.


## Overview


| Item | Description |
| --- | --- |
| Maximum Resolution | *240(H)x320(V)* pixels |
| Maximum Color Depth | *18bit* (262K) |
| Reduced Color Mode (*Idle* mode) | *2-bit* (8 colors) |
| Source and Gate Lines | 720/320 |
| Power Consumption (w/o backlight current) | *6mA* |
| Idle Mode | *1mA* |
| Sleep-In Power Consumption | *100uA* |
| Backlight Power Consumption | *20-40mA* |
| Interface | [SPI](https://done.land/fundamentals/interface/spi) and *Parallel* |

## Programming

### ESPHome Support
[ESPHome](https://done.land/tools/software/esphome/introduction) has dedicated support for *ILI9341* through the [ILI9XXX](https://esphome.io/components/display/ili9xxx#ili9xxx) component.

### PlatformIO/Arduino Support

* [Adafruit ILI9341:](https://github.com/adafruit/Adafruit_ILI9341) specific library for this driver, well documented, enables the use of the hardware-neutral [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) library on top of it
* [TFT_eSPI:](https://github.com/Bodmer/TFT_eSPI) generic library for a wide range of TFT displays. Requires slightly confusing selection of the driver type you intend to use
* [ucglib:](https://github.com/olikraus/ucglib) universal library for *color TFT displays*, [well documented](https://code.google.com/archive/p/ucglib/wikis/connectili9341.wiki), the *ILI9341* driver is selected through the classes `Ucglib_ILI9341_18x240x320_SWSPI` and `Ucglib_ILI9341_18x240x320_HWSPI`. 

## Low Energy Modes
The *ILI9341* supports a *low power sleep mode* (**SLEEP IN**) in which *power consumption* drops from *6mA* to *100μA*. Notably, the **display content remains visible** in sleep mode, although no updates can be made.

| Command | Value |
| --- | --- |
| **SLEEP IN** | *0x10* |
| **SLEEP OUT** | *0x11* |

This feature makes the *ILI9341* particularly useful for low-power devices, however the [ST7789](https://done.land/components/humaninterface/display/tft/st7789/) is slightly more power efficient.

### Deep Sleep
It is crucial to send the *ILI9341* into **SLEEP IN** mode *before* putting your microcontroller into deep sleep. If omitted, the *ILI9341* will continue drawing *4-6mA*, even when the microcontroller is in deep sleep.

#### Arduino & PlatformIO
Here is an example of code to effectively send both an *ESP32* **and** its display into deep sleep:

````
// define wakeup pin
esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 0);

// instantiate the display controller using the Adafruit Library
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

...

// send display to sleep:
tft.sendCommand(0x10);  // Send the SLEEP IN command
delay(120);             // Wait for the display to enter sleep mode
// Enter deep sleep
esp_deep_sleep_start();
````
#### ESPHome
To send an *ESP32* **and** its display into power-efficient *deep sleep* in *ESPHome*, only a few lines of *ESPHome code* are required.

Here is an example of the behavior to add to your *ESPHome device*:

- **Deep Sleep Button:** When you press the *deep sleep button* (in this example, *GPIO0* is used to leverage the existing *boot* button) for *more than 3 seconds*, the system enters the most power-efficient *deep sleep mode* (and sends the display to sleep as well).
- **Wake-Up Button:** When you press the *wake-up button* (assigned to *GPIO35 low active* in this example), both the microcontroller and display will wake up.

Here is the *ESPHome code* to add to your *configuration* for this functionality:

````
# enable deep sleep capabilities and set wakeup-pin (GPIO35) in energy-efficient ext1 mode
deep_sleep:
  id: deep_sleep_control
  esp32_ext1_wakeup:       # uses much less deep sleep power than wakeup_pin:
    pins:
      - number: 35
    mode: ALL_LOW 

# perform all necessary actions to send peripherals to deep sleep
script:
  - id: prepare_for_sleep
    then:
      # switch display controller in sleep mode:
      - lambda: |-
          // Send display to sleep before deep sleep
          uint8_t command = 0x10;  // Your command
          id(display1).command(command);
      - delay: 120ms    
      # send esp32 to deep sleep:
      - deep_sleep.enter: deep_sleep_control

# button to invoke deep sleep (in this case, the *boot* button is used)
binary_sensor:
  - platform: gpio
    name: "Deep Sleep Button"
    id: deep_sleep_button

    pin:
        number: GPIO0
        # low active:
        inverted: True
        mode:
        input: True
        pullup: True

    # debounce:
    filters: 
        - delayed_on: 10ms
        - delayed_off: 10ms  

    # super long press (>3s) without need to release
    on_multi_click:
        - timing:
            - ON for at least 3.1s
            then:
            # invoke deep sleep
            - script.execute: prepare_for_sleep
````
### Low Power Display Operations
When your device needs to display *static content*, you can send the *ST7789* to its **SLEEP IN** mode. The display continues to show its content.

> [!TIP]
> By cleverly sending the *ILI9341* to its own sleep mode when you don't need screen updates, and waking it up via **SLEEP OUT** only temporarily for screen updates, you can minimize the power consumption of your device by roughly *4-6mA*.

### Show Display During Deep Sleep
You can even keep the display on during *deep sleep*. In fact, the display *remained on* in all of the examples above. The reason why you did not see any display content was that the *display backlight* was turned off.

When you power the display backlight via a *GPIO pin*, in the most efficient deep sleep modes, all *GPIOs go low*, so the display backlight is turned off.

While you could choose a *less efficient deep sleep* mode for your *ESP32* and keep the backlight GPIO active, this is not the most power-efficient approach. Instead, you should power the backlight pin independently from the microcontroller, either by directly connecting it to a positive voltage (depending on the display breakout board you are using), or via a current-limiting resistor (or potentiometer to manually adjust brightness).

This way, when you send your device to full deep sleep, the display would still show its last content. The total power consumption would just be the backlight current (which can be as low as *20mA*), and the *deep sleep current* (with a highly efficient *FireBeetle ESP32 breakout board*, this would be *12uA*, whereas a *Lolin32 Lite* would require *350uA*).

### ESP32 With Active Display At 20mA
In any case, your *deep sleeping* device would have a running display with static content at just about *20mA* power consumption (with basically only the backlight LEDs consuming power).

> Tags: Display Driver, Resolution, ST7789
