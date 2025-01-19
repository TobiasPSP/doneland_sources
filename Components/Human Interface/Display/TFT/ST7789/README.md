<img src="/assets/images/screenwire.png" width="100%" height="100%" />
# ST7789

> Drives TFT Displays Up To 240x320 Pixels At 262K Colors (18bit)

The *ST7789* is a versatile *TFT display driver IC* commonly used for small to medium-sized displays with resolutions of up to *240x320* pixels at full *18bit color* (262 thousand different colors). It is in some respect a more modern successor of the popular *ILI9341* which shares the same fundamental features but consumes slightly more power at slightly slower refresh rates. 

Many modern *TFT display boards* and *ESP32 development boards with integrated display* use the *ST7789* device driver.

The driver supports [SPI](https://done.land/fundamentals/interface/spi) and the *Parallel* interface, as well as some lesser-used options.

## Versions
Although *ST7789* exists in a number of variants, there seem to be *no substantial differences* between the *2012 version* [ST7789S](materials/st7789v_datasheet.pdf) and the *2021 version* [ST7789P3](materials/st7789p3_datasheet.pdf). These variants appear to be *maintenance releases* with minor hardware adjustments, such as chip size, pad locations, and supported voltage ranges.

The key display features remain consistent across versions:

| Item | Description |
| --- | --- |
| Maximum Resolution | *240(H)x320(V)* pixels |
| Maximum Color Depth | *18bit* (262K) |
| Source and Gate Lines | 720/320 |
| Power Consumption | *4mA* |
| Idle Mode | *0.4mA* |
| Sleep-In Power Consumption | *5uA* |
| Backlight Power Consumption | *20-40mA* |
| Interface | [SPI](https://done.land/fundamentals/interface/spi) and *Parallel* |

The following table summarizes the observed changes between versions:

| Version | Spotted Changes | Chip Size | Year |
| --- | --- | --- | --- |
| [ST7789S](materials/st7789v_datasheet.pdf) | None documented | 300μm | 2012 |
| [ST7789V](materials/st7789v_datasheet.pdf) | Gate-driver supply voltage range extended | 300μm | 2013 |
| [ST7789H2](materials/st7789h2_datasheet.pdf) | None documented | 300μm | 2014 |
| [ST7789VI](materials/st7789vi_datasheet.pdf) | Power consumption in *normal mode* increased from *7.5mA* to *8mA* | 300μm | 2016 |
| [ST7789V2](materials/st7789v2_datasheet.pdf) | Power consumption reverted to *7.5mA* (documentation correction) | 300μm | 2016 |
| [ST7789VW](materials/st7789vw_datasheet.pdf) | None documented | 300μm | 2017 |
| [ST7789V3](materials/st7789v3_datasheet.pdf) | None documented | 200μm | 2020 |
| [ST7789P3](materials/st7789p3_datasheet.pdf) | None documented | 200μm | 2021 |

If **you** identify any significant differences or compatibility issues, please share your findings in the comments below.

> [!NOTE]
> All *ST7789* variants are supported by the same libraries. If your display does not work, check for issues such as incorrect *GPIO* assignments, incompatible interface settings (*Parallel* vs. *SPI*), or mismatched operating voltages. Testing with multiple libraries (*Adafruit*, *TFT_eSPI*) may help identify the problem, as each has different default behaviors.

## Programming

### ESPHome Support
[ESPHome](https://done.land/tools/software/esphome/introduction) has dedicated support for *ST7789* through the [ILI9XXX](https://esphome.io/components/display/ili9xxx#ili9xxx) component, which supersedes the older [ST7789V TFT LCD](https://esphome.io/components/display/st7789v.html) component.

### PlatformIO/Arduino Support
[Adafruit](https://www.adafruit.com/) offers a free [Adafruit library for ST77* drivers](https://github.com/adafruit/Adafruit-ST7735-Library) (including *ST7789*), and it is also supported by the [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library.

## Low Energy Modes
The *ST7789* supports a *low power sleep mode* (**SLEEP IN**) in which *power consumption* drops from *6mA* to *30μA*. Notably, the **display content remains visible** in sleep mode, although no updates can be made.

| Command | Value |
| --- | --- |
| **SLEEP IN** | *0x10* |
| **SLEEP OUT** | *0x11* |

This feature makes the *ST7789* particularly useful for low-power devices.

### Deep Sleep
It is crucial to send the *ST7789* into **SLEEP IN** mode *before* putting your microcontroller into deep sleep. If omitted, the *ST7789* will continue drawing *4-6mA*, even when the microcontroller is in deep sleep.

#### Arduino & PlatformIO
Here is an example of code to effectively send both an *ESP32* **and** its display into deep sleep:

````
// define wakeup pin
esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 0);

// instantiate the display controller using the Adafruit Library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

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
> By cleverly sending the *ST7789* to its own sleep mode when you don't need screen updates, and waking it up via **SLEEP OUT** only temporarily for screen updates, you can minimize the power consumption of your device by roughly *4-6mA*.

### Show Display During Deep Sleep
You can even keep the display on during *deep sleep*. In fact, the display *remained on* in all of the examples above. The reason why you did not see any display content was that the *display backlight* was turned off.

When you power the display backlight via a *GPIO pin*, in the most efficient deep sleep modes, all *GPIOs go low*, so the display backlight is turned off.

While you could choose a *less efficient deep sleep* mode for your *ESP32* and keep the backlight GPIO active, this is not the most power-efficient approach. Instead, you should power the backlight pin independently from the microcontroller, either by directly connecting it to a positive voltage (depending on the display breakout board you are using), or via a current-limiting resistor (or potentiometer to manually adjust brightness).

This way, when you send your device to full deep sleep, the display would still show its last content. The total power consumption would just be the backlight current (which can be as low as *20mA*), and the *deep sleep current* (with a highly efficient *FireBeetle ESP32 breakout board*, this would be *12uA*, whereas a *Lolin32 Lite* would require *350uA*).

### ESP32 With Active Display At 20mA
In any case, your *deep sleeping* device would have a running display with static content at just about *20mA* power consumption (with basically only the backlight LEDs consuming power).

> Tags: Display Driver, Resolution, ST7789V, ST7789S, ST7789P, ST7789H

[Visit Page on Website](https://done.land/components/humaninterface/display/tft/st7789?705830101817240754) - created 2024-10-16 - last edited 2024-10-20
