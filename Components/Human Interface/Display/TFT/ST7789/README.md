<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# ST7789

> Drives TFT Displays Up To 240x320 Pixels At 262K Colors (18bit)

The *ST7789* is a versatile *TFT display driver IC* commonly used for small to medium-sized displays with resolutions of up to *240x320* pixels at full *18bit color* (262 thousand different colors). Many *TFT display boards* and *ESP32 development boards with integrated display* use this device driver.

The driver supports [SPI](https://done.land/fundamentals/interface/spi) and the *Parallel* interface, plus some lesser used ones. 


## Versions
Although *ST7789* exists in a number of variants, there seem to be *no substantial differences* between the *2012 version* [ST7789S](materials/st7789v_datasheet.pdf) and the *2021 version* [ST7789P3](materials/st7789p3_datasheet.pdf). Apparently, the different versions are mere *maintenance releases* with minor hardware adjustments to chip size, pad locations, and supported voltage ranges.

The key display features remain identical:

* **Maximum Resolution:** *240(H)x320(V)* pixels
* **Maximum Color Depth:** *18bit* (262K)
* **Source and Gate Lines:** 720/320
* **Interface:** [SPI](https://done.land/fundamentals/interface/spi) and *Parallel*

The power consumption also remains identical.

| Version | Spotted Changes |  Chip Size | Year |
|---|---|---|---|
| [ST7789S](materials/st7789v_datasheet.pdf)   |  |300um  | 2012  | 
| [ST7789V](materials/st7789v_datasheet.pdf)   | gate-driver supply voltage range extended  | 300um | 2013   | 
| [ST7789H2](materials/st7789h2_datasheet.pdf)      | | 300um   | 2014   |
| [ST7789VI](materials/st7789vi_datasheet.pdf)      | power consumption in *normal mode* changed from *7.5mA* to *8mA*   | 300um   | 2016   | 
| [ST7789V2](materials/st7789v2_datasheet.pdf)      | power consumption back to normal (possibly documentation bug) | 300um   | 2016   | 
| [ST7789VW](materials/st7789vw_datasheet.pdf)      | | 300um   | 2017   |
| [ST7789V3](materials/st7789v3_datasheet.pdf)      |  | 200um   | 2020   |
| [ST7789P3](materials/st7789p3_datasheet.pdf)     | | 200um   | 2021   | 

That said, the data sheets are *300 pages+*, filled with technical glibber and timing protocols. If **you** spot significant differences or know of compatibility issues, please leave a comment below.


> [!NOTE]
> Regardless of which *ST7789* variant your display uses, they are all supported by the same libraries. If your display does not work, it is most likely due to incorrect *GPIO* assignments on your side, or due to incompatibilities between the display breakout board and your microcontroller (i.e. incompatible operating voltage, incompatible interface (*Parallel* instead of *SPI*), no exposed *CS pin*, etc.). It may help to test with different libraries (*Adafruit*, *TFT_eSPI*) as they use different default behaviors.


## Programming

### ESPHome Support
[ESPHome](https://done.land/tools/software/esphome/introduction) started to support *ST7789* with a dedicated component called [ST7789V TFT LCD](https://esphome.io/components/display/st7789v.html). This component has been made redundant since the *ST7789* is now supported by the more generic [ILI9XXX](https://esphome.io/components/display/ili9xxx#ili9xxx) component.

### platformio/Arduino Support
[Adafruit](https://www.adafruit.com/) provides a free [Adafruit library for ST77* drivers](https://github.com/adafruit/Adafruit-ST7735-Library) (including the *ST7789*). It is also supported by [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI).


## Low Energy Modes
The *ST7789* supports a *low power sleep mode* (**SLEEP IN**) in which *power consumption* drops from *6mA* to just a few *uA*. It is important to note that the **display keeps working** (although you cannot change its content in *sleep mode*).

| Command | Value |
| --- | --- |
| **SLEEP IN** | *0x10* |
| **SLEEP_OUT** | *0x11* |

This opens up exciting opportunities for low-power devices.

### Deep Sleep
It is critical to send the *ST7789* to its own **SLEEP IN** mode *before* you are sending your microcontroller to *deep sleep*. Else, the *ST7789* would stay awake and continue to consume *4-6mA* even though the microcontroller has switched to *deep sleep*.

#### Arduino & platformio
Here is the core of the code to *effectively* send an *ESP32* **and** its display to sleep:

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
Likewise, to send an *ESP32* **and** its display to power-efficient *deep sleep* in *ESPHome*, just a few lines of *ESPHome code* are needed. 

Here is the example behavior to add to your *ESPHome device:**

* **Deep Sleep Button:** when you press the *deep sleep button* (in this example, *GPIO0* is used to utilize the existing *boot* button) for *more than 3 seconds*, the system enters the most power-efficient *deep sleep mode* (and sends the display to sleep as well).
* **Wake-Up Button:** when you press the *wake-up button* (assigned to *GPIO35 low active* in this example), both microcontroller and display wake up.

And this is the *ESPHome code* to add to your *configuration* to add the behavior to your *ESPHome device:*

````
# enable deep sleep capabilities and set wakeup-pin (GPIO35) in energy-efficient ext1 mode
deep_sleep:
  id: deep_sleep_control
  esp32_ext1_wakeup:       # uses much less deep sleep power than wakeup_pin:
    pins:
      - number: 35
        allow_other_uses: true
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

While you could choose a *less efficient deep sleep* mode for your *ESP32* and keep the backlight GPIO active, this is not the most power efficient approach. Instead, you should power the backlight pin independently from the microcontroller, either by directly connecting it to a positive voltage (depending on the display breakout board you are using), or via a current limiting resistor (or potentiometer to manually adjust brightness).

This way, when you send your device to full deep sleep, the display would still display its last content. The total power consumption would just be the backlight current (which can be as low as *0.5mA*), and the *deep sleep current* (with a highly efficient *FireBeetle ESP32 breakout board*, this would be *12uA*, whereas a *Lolin32 Lite* would require *350uA*).

### ESP32 With Running Display At 1mA

In any respect, your *deep sleeping* device would have a running display with static content at just about *1mA* power consumption.

> Tags: Display Driver, Resolution, ST7789V, ST7789S, ST7789P, ST7789H

[Visit Page on Website](https://done.land/components/humaninterface/display/tft/st7789?705830101817240754) - created 2024-10-16 - last edited 2024-10-20
