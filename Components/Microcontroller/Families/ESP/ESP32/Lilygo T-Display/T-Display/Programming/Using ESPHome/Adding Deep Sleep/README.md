<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Adding Deep Sleep To T-Display

> Turning Off Battery-Driven T-Displays By Using Deep Sleep And Wakeup


[T-Display](https://www.lilygo.cc/products/lilygo%C2%AE-ttgo-t-display-1-14-inch-lcd-esp32-control-board) is optimized for portable battery operations: at an average power consumption of *130mA*, it can  run short of 8 hours at full power from a *1.000 mAh* battery. 


<img src="images/lilygo_t-display_deepsleep_esphome_display_overview2_t.png" width="40%" height="40%" />

Typically, though, a portable device does not need to continuously run at full power. At minimum, you will want to add a *power switch* so you can manually turn it on and off.

Or, use the *deep sleep* mode: this way, when you don't need the device, it can idle in a very low power mode until you wake it up again. This is also a great solution for sensors or other use cases where you want the microcontroller to perform work in intervals or on input signals.

One challenge with *deep sleep* is though that the actual power consumption drops from *130mA* to *9mA* which is still a very significant power consumption. That's why in this article you learn *why* the board consumes so much power in *deep sleep*, and how you can disable a few components *solely by code* to bring down *deep sleep* power consumption to less than *300uA* (*uA*, not *mA*). 

At *300uA*, with a *1000mAh* battery, the device can stay in *deep sleep* mode for more than 4 months.

> [!TIP]
> Implementing *deep sleep* has a number of additional benefits. For example, you can now add a *low voltage protection*, making sure the device automatically enters deep sleep once the battery is close to depletion, protecting battery health. The [ESPHome configuration](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display/programming/usingesphome/addingdeepsleep/#configuration) below includes *low voltage battery protection*.


## Overview

This article focuses on how to add *deep sleep* support to the *T-Display* board, and how to **do it right**. If you do it carelessly, *deep sleep* may consume a lot more power than anticipated, and drain your batteries much sooner than you expected. The configuration presented here is based on the [*sample configuration* created earlier](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display/programming/usingesphome). 

<img src="images/lilygo_tdisplay_deepsleep_overview_ui.png" width="70%" height="70%" />

The *configuration* also exposes all crucial device information to *Home Assistant*, including a battery icon with the current battery charging state, and a button to remotely send the device to *deep sleep*:


<img src="images/lilygo_t_display_deep_ha1.png" width="100%" height="100%" />


I'll cover the required optimizations first, then present the entire configuration.

### General Optimizations

In the header part of your *configuration*, make sure you *enable 16MB flash memory* if your board has *16MB*. Else, *ESPHome* will only use *4MB flash memory* which is often not sufficient when working with displays.

````
esp32:
  board: esp32dev
  flash_size: 16MB  # important: if your board has 16MB, unlock it!
  framework:
    type: arduino
````

If your device is being used in a stable *WiFi*, and not switching back and forth between different *SSIDs*, do this:

* **Save RAM:** Remove `captive_portal:` as well as the `ap:` access point. Removing the internal web server saves a significant amount of RAM.
* **Save Battery Power:** Add `fast_connect: true` to `wifi:`. This skips scanning available *WiFi networks* (which doesn't make sense when you always connect to the same *SSID* anyway). This speeds up *WiFi connect*, and saves valuable battery power, especially if you later use *deep sleep* and wake up your board only occasionally, i.e. to take sensor readings.

> [!TIP]
> You may want to remove `logger:` along with all log messages once you have debugged your device. This again saves battery power and minimizes *WiFi transmissions*.   

This is what your header part should look like:

````
esphome:
  name: t-display-1
  friendly_name: T-Display #1
  
esp32:
  board: esp32dev
  flash_size: 16MB  # important: if your board has 16MB, unlock it!
  framework:
    type: arduino


# Enable logging (optional)
logger:

# Enable Home Assistant API
api:
  encryption:
    key: "..."

ota:
  - platform: esphome
    password: "..."

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  fast_connect: true
````


## Efficient Deep Sleep

When you send an *ESP32* to *deep sleep* via *ESPHome configuration*, you often see code like this:

````
deep_sleep:
  id: deep_sleep_control
  wakeup_pin: 35
````

If you do it like this, the board would indeed switch to *deep sleep* once you invoke `- deep_sleep.enter: deep_sleep_control` (i.e. via button press). It would now consume horrendous *9mA* though instead of the *370uA* that it *should* take on this board, and here is why:

* **Display Driver:** once you add a *display* component to your configuration, the display controller gets initialized. Even when you send the *ESP32* to *deep sleep* will this driver consume around *6.5mA*.
* **RTC IO Mode:** when you use `wakeup_pin:`, you are automatically keeping the *RTC IO* subsystem active. This mode is called `ext0`, and it costs you another *2mA*. The better approach is to use `esp32_ext1_wakeup:`: this mode can use *multiple wakeup pins*, however it only supports waking up the processor when *all specified pins turn **low** together*, or any *one* of them turns **high**. If that works for you, it saves another *2mA*.  
* **LDO:** the *low dropout voltage regulator* is consuming around *80uA* power even though this component is not needed when powered by a battery.

When using a more efficient deep sleep mode and disabling both display driver and LDO, the power consumption in deep sleep mode can be reduced from *9mA* (*9.000uA*) to just *290uA* - reducing power consumption by factor *31*.

Here is how you do it:


### Using Most Efficient Deep Sleep Mode
Invoke *deep sleep* using `esp32_ext1_wakeup:` is used to enable the power efficient `ext1` deep sleep mode:

````
# enable deep sleep capabilities and set wakeup-pin in energy-efficient ext1 mode
deep_sleep:
  id: deep_sleep_control
  esp32_ext1_wakeup:       # uses much less deep sleep power than wakeup_pin:
    pins:
      - number: 35
        allow_other_uses: true
    mode: ALL_LOW 
````

*GPIO35* (one of the built-in push buttons) is used to wake up the system. Since this push button is also used as a *regular* button elsewhere in the configuration, it is marked `allow_other_uses: true`. Else, since *ESPHome 2023* you would get errors, keeping you from assigning the same *GPIO* to two different components.

The pin mode is `ALL_LOW` since the *T-Display buttons* are *low active*. Note that `esp32_ext1_wakeup:` does not honor `inverted: true` or any other sophisticated pin declarations (which is the primary difference to the more power-hungry `wakeup_pin:`).

### Disabling Display Driver And LDO
Right before sending the board to *deep sleep*, you need to send the display driver to its own sleep mode, and disable the built-in LDO. Else, both components will continue to draw significant current.

That's why a *script* is used to invoke the deep sleep mode. The script can first take care of sending the components to sleep, then send the *ESP32* to sleep:

````
# perform all necessary actions to send peripherals to deep sleep
script:
  - id: prepare_for_sleep
    then:
      # switch display controller in sleep mode:
      - lambda: |-
          // Send display to sleep before deep sleep
          uint8_t command = 0x10;  // Your command
          id(display1).command(command);
          // Turn off LDO for another 80uA savings 
          id(vbat_ldo_pwren).turn_off();
      - delay: 120ms    
      # send esp32 to deep sleep:
      - deep_sleep.enter: deep_sleep_control
````

#### Sending Display To Sleep
It is crucial to send the command *SLEEPIN* (`0x10`) to the display to disable it before entering deep sleep mode. If you omit this, deep sleep will consume an extra *6.5mA*.

> [!NOTE]
> I [raised this issue](https://github.com/esphome/issues/issues/6307) with *ESPHome*, and hopefully we will see the display disabling itself automatically on deep sleep in the future.  

#### Sending LDO To Sleep
The LDO used on this board has an [enable pin](https://github.com/Xinyuan-LilyGO/TTGO-T-Display/issues/6) that is tied to *GPIO14* (as can be seen in the [schematics](https://github.com/Xinyuan-LilyGO/TTGO-T-Display/files/4416932/ESP32-TFT.6-26.pdf)). To control this GPIO from above script, another `switch:` is used:

````
switch:
  # GPOI14 set as output to control the PWR_EN of the LDO chip
  # GPIO14 = 0 : LDO Off
  # GPIO14 = 1 : LDO On (used to measure the current battery voltage)
  - platform: gpio
    pin: GPIO14
    name: "VBAT LDO Power Enable"
    id: vbat_ldo_pwren
    inverted: true
````

> [!TIP]
> When the LDO is disabled, this also disables battery voltage monitoring. For deep sleep, this doesn't matter: the voltage is not monitored anyway, and when the device wakes up, the original GPIO state is restored. However, should you want to also optimize battery consumption during normal operations, you could measure the battery voltage, and when it is below *4.3V* (indicating battery operations), you could disable the LDO. Just make sure you temporarily enable it whenever you want to measure the battery voltage again.



#### Triggering Deep Sleep
The script *prepare_for_sleep* from above can now be tied to any action you like: `- script.execute: prepare_for_sleep`. You can for example use *one* button to send the board to *deep sleep*, and another one to *wake it up again*:

* **Deep Sleep Button:** invoke the script `prepare_for_sleep` when the button is pressed.
* **Wake Up Button:** define the button pin in `esp32_ext1_wakeup:`.

> [!IMPORTANT]
> **Never** use the same button for *invoking deep sleep* and *wake up*, or else the board will immediately wake up again as the button is *still pressed* when *deep sleep* takes over. Also, never use *GPIO0* to send the board to *deep sleep* on a simple button press. *GPIO0* is the *boot* button, and you don't want the board to start *deep sleeping* when you really just wanted to boot into *ROM bootloader* mode. If you do use *GPIO0* (like in this example), make sure *deep sleep* is invoked only on a *long press*.

When *deep sleep* is configured this way, it optimizes power efficiency. In my first attempts, I just disabled the display driver and did not care about the LDO. This lowered consumption from *9mA* to *373uA*:

<img src="images/lilygo_t_display_deep_sleep_consumption_cycle_platformio.png" width="100%" height="100%" />

Then [Laurent](https://github.com/lhac5vet) pointed me to the LDO issue, and this saved another *80uA*, bringing down the deep sleep consumption to *295uA*:

<img src="images/liligo_tdisplay_optimized.png" width="100%" height="100%" />

*295uA* admittedly still isn't awesome: *DFRobots* [FireBeetles](https://www.dfrobot.com/product-1590.html) just take *20uA*, for example. However, given the affordable price and the overall package, *<300uA* deep sleep power consumption is working very well for most battery-operated projects, and just a few lines of code extended deep sleep battery capacity from a month to almost three years.


## Invoking Deep Sleep
Deep sleep can now be invoked manually, automatically, and even remotely. The *reason* why the board entered *deep sleep* is published via a `text_sensor:`:

````
# log system state: running or deep sleep (and reason)
  - platform: template
    name: "DeepSleep State"
    id: sleep_state
    icon: "mdi:power-sleep"
    entity_category: "diagnostic"
    device_class: ""
````

This is important because *Home Assistant* shows the last known parameters, and if the board was sent to *deep sleep*, none of its user controls respond anymore. That's expected since a system in *deep sleep* is essentially *turned off*, but *Home Assistant* should report the fact that the system is currently *sleeping* - which is what this sensor does. It also reports *why* the system is *sleeping*.


<img src="images/lilygo_t_display_deep_ha2-t.png" width="30%" height="30%" />


Here are the three ways how the board can enter *deep sleep*:

### Automatic Low Voltage Protection
*LiIon* and *LiPo* batteries shouldn't be discharged below *3.2V* to ensure longevity. Discharging lower than *3.2V* wouldn't make much sense anyway since the display starts to flicker below this voltage.

To send the device automatically to *deep sleep* when the battery voltage drops below *3.2V*, add this:

````
  - platform: adc
    pin: GPIO34
    id: battery_voltage
    name: "Voltage"
    update_interval: 1s
    #internal: true
    accuracy_decimals: 2
    attenuation: 12dB
    samples: 10
    entity_category: "diagnostic"
    device_class: "voltage"
    filters:
      # transform the raw value (voltage divider) to actual voltage:
      - multiply: 2.04
      # remove outliers (voltage spikes only):
      - quantile:
          window_size: 7
          send_every: 4
          send_first_at: 3
          quantile: .25
    # on new voltage readings, update battery statistics:
    on_value:
      then:
        - component.update: battery_percent
        - component.update: battery_status
    # automatically enter deep-sleep below 3.2V:
    on_value_range:
      below: 3.2
      then:
        - text_sensor.template.publish:
            id: sleep_state
            state: "Deep Sleep (low voltage)"
        - script.execute: prepare_for_sleep
````

Note how the *sleep_state* `text_sensor:` is updated *before* the system enters *deep sleep*.



#### Reading Battery Voltage
Knowing the current *battery voltage* is crucial for battery-operated devices, and the previously discussed *automatic deep sleep* on *low voltage* is just one example. Displaying *battery icons* and status texts are other use cases.

To actually get a *solid battery voltage reading* requires some processing which is also taken care of by this sensor. Here is what the remaining code does:

* **Automatic Deep Sleep:** `on_value_range:` defines the threshold and executes the script to invoke *deep sleep*.
* **Automatic Update:** `on_value:` makes sure dependent sensors are updated whenever the battery voltage changes, one of which shows the battery state of charge in *percent*, and the other one reports the power mode: *USB* or *Battery*.
* **Filters:** the *battery sensor* is really a simple *ADC GPIO* that measures the battery voltage across a *voltage divider*. `filters:` processes the raw readings to create a stable battery voltage. It first uses `multiply:` to account for the voltage divider. The factor is *2.0*. For accurate readings, you should double-check your battery voltage, and make slight adjustments. In my case, the required factor was *2.04*. There are always slight variations in resistor values. Since the sensor frequently produces *voltage spikes*, a `quantile:` filter is used to cut off any value that is not in the bottom *25%* of values, effectively removing sudden positive spikes. Make sure you switch the *ADC* to `attenuation: 12dB`, or else your readings will be clipped, and you always measure a voltage around *1V*.

    Here is a graph taken from *Home Assistant*, showing *battery voltage* over time. On the left, I used a *median* filter, and voltage spikes are still present. On the right is the *25% quantile* filter with a nice and smooth linear discharge curve:


    <img src="images/lilygo_t_display_deep_ha3.png" width="60%" height="60%" />    

    The *flat line* at the bottom represents the *automatic low-voltage protection* when the board switched to *deep sleep* once the voltage fell below *3.2V*.

    Make sure you switch the *ADC* to `attenuation: 12dB`, or else your readings will be clipped, and you always measure a voltage around *1V*.

The *battery voltage sensor* is crucial for updating icons and status text, so `update_interval:` is set to *1s*. *ESPHome* sends updates over the network to *Home Assistant* only when the battery voltage really changes. Increasing the *update interval* is not recommended as it would increase the *lag time* when you connect or disconnect the device to *USB power*.

If you want to minimize network traffic, you can switch the sensor to `internal: true`. You then miss out on the advanced voltage logging and analysis capabilities of *Home Assistant*, though.

#### Battery Status and Percentage
The *raw battery voltage* is picked up by two sensors:

*battery_status* is a `text_sensor:` that translates a voltage reading into a status text:

````
text_sensor:
  # log power mode: USB or battery
  - platform: template
    name: "Battery Status"
    id: battery_status
    entity_category: "diagnostic"
    device_class: ""
    icon: mdi:power-plug-battery
    lambda: |-
      if (id(battery_voltage).state > 4.74) {
        id(display1).filled_rectangle(111, -3, 24, 24, BLACK);
        id(display1).image(111, -3, id(powerPlug), YELLOW, BLACK);
        // clear text background:
        id(display1).filled_rectangle(40, -2, 55, 20, BLACK);
        // output text center-aligned horizontally
        int display_centerwidth = id(display1).get_width()/2;
        id(display1).print(display_centerwidth, -2, id(lato), GRAY, TextAlign::CENTER_HORIZONTAL, "USB");
        return {"USB"};
      } else if (id(battery_voltage).state > 4.18) {
        id(display1).filled_rectangle(111, -3, 24, 24, BLACK);
        id(display1).image(111, -3, id(batcharge), YELLOW, BLACK);

        // clear text background:
        id(display1).filled_rectangle(40, -2, 55, 20, BLACK);
        // output text center-aligned horizontally
        int display_centerwidth = id(display1).get_width()/2;

        if (id(battery_voltage).state > 4.5) {
           id(display1).print(display_centerwidth, -2, id(lato), GREEN, TextAlign::CENTER_HORIZONTAL, "CV");
           return {"Constant Voltage"};
        } else {
           id(display1).print(display_centerwidth, -2, id(lato), YELLOW, TextAlign::CENTER_HORIZONTAL, "CC");
           return {"Constant Current"};
        }
      } else {
        return {"Battery"};
      }
````

Here is how *Home Assistant* converts this text sensor to a graph over time, providing detailed information about battery charging and discharging:

<img src="images/lilygo_t_display_deep_ha5.png" width="100%" height="100%" />    


It also updates icons and status text:

* **Power Mode:** based on the current voltage readings, you get different icons and status texts for these modes:
  * **USB:** board is powered by *USB*/*5V*, and not charging.
  * **Charging:** board is charging a battery. The status differentiates between *constant current* (first charging phase up to *80%*), and *constant voltage* (second charging phase from *80-100%*). The display shows a yellow *CC* or a green *CV*. This allows you to disconnect the board from *USB* if you don't want to fully charge the battery to conserve its life.
  * **Battery Power:** when powered by the battery, the display shows the remaining charge in percent.

The latter - the battery *state of charge*, is determined by *battery_percent*, another templated sensor that is based on the current battery voltage:

````
- platform: template
    name: "Battery %"
    id: battery_percent
    lambda: return id(battery_voltage).state;
    accuracy_decimals: 0
    unit_of_measurement: "%"
    icon: mdi:battery-medium    
    entity_category: "diagnostic"
    device_class: "battery"
    filters:
      # map battery voltages to associated SOC percentages:
      - calibrate_linear:
         method: exact
         datapoints:
          - 0.00 -> 0.0
          - 3.30 -> 1.0
          - 3.39 -> 10.0
          - 3.75 -> 50.0
          - 4.08 -> 97.0
          - 4.11 -> 99.0
          - 4.20 -> 100.0
      # cap at 100%
      - clamp:
          min_value: 0
          max_value: 100
          ignore_out_of_range: true
      # remove outliers (both directions):
      - median:
          window_size: 7
          send_every: 4
          send_first_at: 3
````

This *Home Assistant* graph shows a smooth and almost linear *battery percent* curve when discharging the battery:

<img src="images/lilygo_t_display_deep_ha4.png" width="60%" height="60%" />    

`calibrate_linear:` calibrates the state of charge via some reference points. *LiIon* battery voltage often drops considerably right after disconnecting them from the charger (which is called *relaxation*). The reference points take this into account and produce a curve that linearly depicts the true *state of charge* based on current battery voltage.

`clamp:` limits the range to *0-100*, eliminating invalid readings. And `median:` filters out outliers. Since outliers can be both *positive* and *negative*, this sensor uses the *median* filter rather than the *quantile* filter (which eliminated *positive* spikes).

`on_value:` updates the battery icon whenever a new *state of charge* is emitted. It also prints the current battery charge (in percent) to the screen.

#### Battery Icon and State of Charge
It then also serves to update the battery icon in the display which occurs every time a new battery percentage is reported:

````
    # on new battery percentage, update text and icon on display:
    on_value: 
      then:
        # update battery percent on display:
        - lambda: |-
            // output battery percentage horizontally aligned:

            
            if (id(battery_voltage).state < 4.18) {
              // clear text background:
              id(display1).filled_rectangle(40, -2, 55, 20, BLACK);
              // output text center-aligned horizontally
              int display_centerwidth = id(display1).get_width()/2;
              // update battery percent:
              id(display1).printf(display_centerwidth, -2, id(lato), LIGHTGRAY, TextAlign::CENTER_HORIZONTAL, "%.0f%%", id(battery_percent).state);
            }

            // show battery icon in right corner of display:

            // clear icon background:
            id(display1).filled_rectangle(111, -3, 24, 24, BLACK);

            // read current percentage as integer: 
            int batPercent = (int)id(battery_percent).state;

            // draw appropriate icon:
            if (batPercent<5) {
              id(display1).image(111, -3, id(bat1), RED, BLACK);
            } else if(batPercent < 20) {
              id(display1).image(111, -3, id(bat2), ORANGE, BLACK);
            } else if(batPercent < 40) {
              id(display1).image(111, -3, id(bat3), ORANGE, BLACK);
            } else if(batPercent < 60) {
              id(display1).image(111, -3, id(bat3), GREEN, BLACK);
            } else if(batPercent < 80) {
              id(display1).image(111, -3, id(bat4), GREEN, BLACK);
            } else if(batPercent < 100) {
              id(display1).image(111, -3, id(bat5), GREEN, BLACK);
            } else {
              id(display1).image(111, -3, id(powerPlug), YELLOW, BLACK);
            }
````

Note how the battery state and icon is added to the device in *Home Assistant* so you can immediately see which of your *ESPHome devices* has a battery, and what the current battery status is:

<img src="images/lilygo_t_display_deep_ha6.png" width="60%" height="60%" />    


### Manual Deep Sleep
When the *GPIO0 push button* is pressed for at least *3.1s*, deep sleep is manually invoked:

````

# GPIOs (PHYSICAL BUTTONS)
binary_sensor:
  # left button (boot button):
  - platform: gpio
    name: "Push Button Left"
    id: button_left
    icon: "mdi:toggle-switch-outline"

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

    # super long press (<3s) without need to release
    on_multi_click:
        - timing:
            - ON for at least 3.1s
          then:
            # invoke deep sleep
            - text_sensor.template.publish:
                id: sleep_state
                state: "Deep Sleep (manual invoke)"
            - script.execute: prepare_for_sleep
````

Note how the button publishes the *appropriate deep sleep event* to the `text_sensor:` named *sleep_state* before it actually invokes *deep sleep*.

`on_multi_click:` is the only way you have to respond to a pushed-down button after a given time **without the need for the user to first release it**. So whenever a user pushes down the button for at least *3.1s*, the action invokes the *deep sleep* script.

#### Freely Programmable Buttons
All the other potential functionalities you may want to associate with this push button are handled via `on_click:`: 

* **Internal very short push:** when the user pushes the button only shortly, it controls the display backlight brightness.
* **Short Press:** when pushed for no longer than *0.5s*, it is invoking the *short press* action which is also published to *Home Assistant* - so you can trigger automations based on this push.
* **Long Press:** any pushing for longer than *0.5s* but no more than *3s* is treated as a *long push*, and also published to *Home Assistant*.

````  
    on_click:
    # very short push increases display backlight brightness:
    - min_length: 50ms
      max_length: 250ms
      then:
        - logger.log: "physically dimming up"
        - light.dim_relative:
              id: back_light
              relative_brightness: 5%
              transition_length: 0.1s
    # short press:
    - min_length: 251ms
      max_length: 500ms
      then:
        - logger.log: "physical Short Press 1"
        - button.press: short_press1
    # long press:
    - min_length: 501ms
      max_length: 3000ms
      then:
        - logger.log: "physical Long Press 1"
        - button.press: long_press1
````


<img src="images/lilygo_t_display_deep_ha7-t.png" width="40%" height="40%" />    


You can use all of these events internally (within this *configuration*), i.e. to trigger other actions or local scripts. Currently, all events just invoke `logger.log:`, and write debug messages into the log.

You can **also remotely** press the buttons from your *Home Assistant UI*. They are published to `Home Assistant` via `button:`. One button is virtual only and not attached to any physical button:

````
button:
  - platform: template
    name: "DeepSleep Invoke"
    id: deep_sleep_button
    entity_category: "diagnostic"
    device_class: ""
    icon: mdi:sleep
    # send device to deep sleep remotely:
    on_press: 
      then:
        - text_sensor.template.publish:
            id: sleep_state
            state: "Deep Sleep (remote invoke)"
        - script.execute: prepare_for_sleep
````

*Home Assistant* shows this button in the device user interface, and when you click it, the device enters *deep sleep*. All *physical buttons* also got virtual *Home Assistant* buttons, so they, too, can be remotely operated:

````
  - platform: template
    name: "Button1 ShortPress"
    id: short_press1
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button1 ShortPress Pressed"
  
  - platform: template
    name: "Button1 LongPress"
    id: long_press1
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button1 LongPress Pressed"

  - platform: template
    name: "Button2 ShortPress"
    id: short_press2
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button2 ShortPress Pressed"
  
  - platform: template
    name: "Button2 LongPress"
    id: long_press2
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button2 LongPress Pressed"

  - platform: template
    name: "Button2 SuperLongPress"
    id: superlong_press2
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button2 SuperLongPress Pressed"
````

> [!NOTE]
> *Buttons* are **one-way**: *Home Assistant* can remotely control them, but when you operate a button locally via a physical device button, *Home Assistant* does not notice or log this, nor can you attach automations to a button. If you wanted to enable this, too, you'd have to publish dedicated *Home Assistant events* via its *API*.


#### Freely Programmable Switch
In addition, the push button can also act like a *switch*: for as long as the user *presses* the button, the switch is *ON*, and once the user releases the button, the switch turned *OFF*:

````
    # holding down the button:
    on_press:
      then:
        - logger.log: "physically switching ON left switch"
        - switch.template.publish:
            # switch is ON
            id: button1_switch
            state: ON

    # releasing pushed down button:
    on_release:
      then:
        - logger.log: "physically switching OFF left switch"
        - switch.template.publish:
            # switch is OFF
            id: button1_switch
            state: OFF
````
*Switches* perform **two-way communications**, so when you operate a switch - locally on the device, or remotely via *Home Assistant* - the action is logged by *Home Assistant*. Likewise, you *can* attach automations* to *switches*.


## Display Component
The *st7789v* display driver component used in the original *configuration* is considered *deprecated*:

This driver is considered deprecated:

````
display:
  - platform: st7789v
````

This configuration uses the modern and more general `ili9xxx` driver which superseeds the old driver. It can handle uniformly many different TFT displays and drivers, including the *st7789v*. 

This is the replacement component configured for the *T-Display display*:

````
display:
  - platform: ili9xxx
    model: ST7789V
    id: display1
    cs_pin: GPIO5
    dc_pin: GPIO16
    reset_pin: GPIO23
    dimensions:
      height: 240
      width: 135
      offset_height: 40
      offset_width: 52
    invert_colors: true
````

### Power-Efficient Display Management
In the original *configuration*, the device driver used the default `update_interval: 1s` and cleared its display each time (` auto_clear_enabled:` is *true* by default).

In essence, the *lambda code* had to redraw the entire display content every second, regardless of whether it needed changes or not. This wasted a lot of battery power because the microcontroller (and display controller) were kept busy for *85ms* each second just to do these redundant updates.

That's why the new *configuration* sets `auto_clear_enabled: false`. Only those portions that actually need updates will be redrawn. Display updates can be initiated from various components, i.e. when the battery voltage changes, the battery icon gets updated.

Drawing updates to the display now requires that the code takes care of *erasing this area* before drawing new things:

````
// draw icon:      
it.filled_rectangle(0, -3, 24, 24, BLACK); // erase icon area 
it.image(0, -3, id(wifiOn), GREEN, BLACK); // draw new icon
````

### Dimmable Display Backlight
The *display backlight* is implemented as a `light:` component, and this *light* is tied to its *GPIO 4* via an `output:`:

````
# use a separate "light" component for dimmable display backlight management:
output:
  - platform: ledc
    # GPIO4 is connected to display backlight:
    pin: 4
    id: display_backlight_pwm

# display backlight:
light:
  - platform: monochromatic
    output: display_backlight_pwm
    name: "Display Backlight"
    id: back_light
    # remember last dim state:
    restore_mode: RESTORE_AND_ON
    # support a pulse effect:
    effects:
      - pulse:
          name: noWifiConnection
          min_brightness: 60%
          max_brightness: 80%
````

This way, you can turn the backlight *on* and *off*, but you can also *dim* it: in *Home Assistant*, when you click the *light bulb icon* in the device *Controls*, a dimmable light control opens, and you can set the light intensity with a slider.



<img src="images/lilygo_t_display_deep_ha8-t.png" width="50%" height="50%" />    

At the bottom of this control, you see a drop-down list with available *light effects*. The *configuration* defines the *pulsating* effect *noWifiConnection* which is used initially when the device has not yet established a *WiFi connection*. With this *Home Assistant* control, you can turn this effect on and off manually any time you like.


````
# use a separate "light" component for dimmable display backlight management:
output:
  - platform: ledc
    # GPIO4 is connected to display backlight:
    pin: 4
    id: display_backlight_pwm

# display backlight:
light:
  - platform: monochromatic
    output: display_backlight_pwm
    name: "Display Backlight"
    id: back_light
    # remember last dim state:
    restore_mode: RESTORE_AND_ON
    # support a pulse effect:
    effects:
      - pulse:
          name: noWifiConnection
          min_brightness: 60%
          max_brightness: 80%

````

`restore_mode: RESTORE_AND_ON` makes sure your last dim level is stored and used as future default.




## Sample Configuration

The *configuration* below is ready for *copy & paste*. It is not just much more *power-efficient* than the [intial version](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display/programming/usingesphome). It has also all the built-in functionality required by a *battery-operated device*:

* **Status bar:** a small status bar shows a *WiFI* **and** a *battery* icon, indicating *connectivity* and *power status*. A horizontal bar shows the *reception strength* for *WiFI* which makes it easy to place the device in a spot with good *WiFi* coverage. In-between both icons, the current battery charge status is displayed in *percent* (unless connected to *USB* power).
* **Display Dimming:** pressing either one of the two buttons **quickly** controls display brightness. The selected brightness is stored as your new preference.
* **Deep Sleep:** When holding the *GPIO0* (boot) button for longer than *3s*, the device enters *deep sleep* in the most efficient mode, consuming only *370uA*. Pressing the other button wakes the device again.
* **Home Assistant:** in *Home Assistant*, *diagnostic sensors* report *battery voltage*, current source of power, state of charge in percent, and *WiFi reception* both in *dBm* and percent. Both push buttons are exposed in a number of ways: as switches, short-, long-, and superlong-press buttons. And a dedicated *deep sleep button* lets you invoke *deep sleep* remotely from *Home Assistant*.


### Configuration
Here is the *ready to use* complete ESPHome *configuration*:

````
# PREFERENCES and GLOBAL VARIABLES:
# save state changes to flash within 10s (i.e. new display backlight dim level)
preferences:
  flash_write_interval: 10s

globals:
  - id: isOnline
    type: bool
    restore_value: no
    initial_value: 'true'  # offline at first, this triggers refresh
  - id: lastSignalStrength # last WiFi signal strength
    type: uint
    restore_value: no
    initial_value: "-1"

# HARDWARE SENSORS 
sensor:
  # retrieve current WiFi signal strength in dBm:
  - platform: wifi_signal
    name: "WiFi Signal dB"
    id: wifi_signal_db
    #update_interval: 60s
  # retrieve current WiFi signal strength in percent:
  - platform: copy 
    source_id: wifi_signal_db
    name: "WiFi Signal Percent"
    id: wifi_signal_percent
    icon: mdi:cloud-percent
    filters:
      - lambda: return min(max(2 * (x + 100.0), 0.0), 100.0);
    unit_of_measurement: "Signal %"
    entity_category: "diagnostic"
    device_class: ""
  # battery voltage sensor
  - platform: adc
    pin: GPIO34
    id: battery_voltage
    name: "Voltage"
    update_interval: 1s
    #internal: true
    accuracy_decimals: 2
    attenuation: 12dB
    samples: 10
    entity_category: "diagnostic"
    device_class: "voltage"
    filters:
      # transform the raw value (voltage divider) to actual voltage:
      - multiply: 2.04
      # remove outliers (voltage spikes only):
      - quantile:
          window_size: 7
          send_every: 4
          send_first_at: 3
          quantile: .25
    # on new voltage readings, update battery statistics:
    on_value:
      then:
        - component.update: battery_percent
        - component.update: battery_status
    # automatically enter deep-sleep below 3.2V:
    on_value_range:
      below: 3.2
      then:
        - text_sensor.template.publish:
            id: sleep_state
            state: "Sleeping (low voltage)"
        - script.execute: prepare_for_sleep

  # publish battery voltage in arbitrary intervals (when ADC sensor is set to internal)
  #- platform: template 
  #  name: "Battery Voltage"
  #  id: battery_voltage_public
  #  update_interval: 60s
  #  accuracy_decimals: 2
  #  lambda: return id(battery_voltage).state;
  #  unit_of_measurement: "V" 
  #  device_class: voltage  
  #  state_class: measurement  
  #  entity_category: "diagnostic"
  # publish battery state of charge in percent      
  - platform: template
    name: "Battery %"
    id: battery_percent
    lambda: return id(battery_voltage).state;
    accuracy_decimals: 0
    unit_of_measurement: "%"
    icon: mdi:battery-medium    
    entity_category: "diagnostic"
    device_class: "battery"
    filters:
      # map battery voltages to associated SOC percentages:
      - calibrate_linear:
         method: exact
         datapoints:
          - 0.00 -> 0.0
          - 3.30 -> 1.0
          - 3.39 -> 10.0
          - 3.75 -> 50.0
          - 4.08 -> 97.0
          - 4.11 -> 99.0
          - 4.20 -> 100.0
      # cap at 100%
      - clamp:
          min_value: 0
          max_value: 100
          ignore_out_of_range: true
      # remove outliers (both directions):
      - median:
          window_size: 7
          send_every: 4
          send_first_at: 3
    
    # on new battery percentage, update text and icon on display:
    on_value: 
      then:
        # update battery percent on display:
        - lambda: |-
            // output battery percentage horizontally aligned:

            
            if (id(battery_voltage).state < 4.18) {
              // clear text background:
              id(display1).filled_rectangle(40, -2, 55, 20, BLACK);
              // output text center-aligned horizontally
              int display_centerwidth = id(display1).get_width()/2;
              // update battery percent:
              id(display1).printf(display_centerwidth, -2, id(lato), LIGHTGRAY, TextAlign::CENTER_HORIZONTAL, "%.0f%%", id(battery_percent).state);
            }

            // show battery icon in right corner of display:

            // clear icon background:
            id(display1).filled_rectangle(111, -3, 24, 24, BLACK);

            // read current percentage as integer: 
            int batPercent = (int)id(battery_percent).state;

            // draw appropriate icon:
            if (batPercent<5) {
              id(display1).image(111, -3, id(bat1), RED, BLACK);
            } else if(batPercent < 20) {
              id(display1).image(111, -3, id(bat2), ORANGE, BLACK);
            } else if(batPercent < 40) {
              id(display1).image(111, -3, id(bat3), ORANGE, BLACK);
            } else if(batPercent < 60) {
              id(display1).image(111, -3, id(bat3), GREEN, BLACK);
            } else if(batPercent < 80) {
              id(display1).image(111, -3, id(bat4), GREEN, BLACK);
            } else if(batPercent < 100) {
              id(display1).image(111, -3, id(bat5), GREEN, BLACK);
            } else {
              id(display1).image(111, -3, id(powerPlug), YELLOW, BLACK);
            }


text_sensor:
  # log power mode: USB or battery
  - platform: template
    name: "Battery Status"
    id: battery_status
    entity_category: "diagnostic"
    device_class: ""
    icon: mdi:power-plug-battery
    lambda: |-
      if (id(battery_voltage).state > 4.74) {
        id(display1).filled_rectangle(111, -3, 24, 24, BLACK);
        id(display1).image(111, -3, id(powerPlug), YELLOW, BLACK);
        // clear text background:
        id(display1).filled_rectangle(40, -2, 55, 20, BLACK);
        // output text center-aligned horizontally
        int display_centerwidth = id(display1).get_width()/2;
        id(display1).print(display_centerwidth, -2, id(lato), GRAY, TextAlign::CENTER_HORIZONTAL, "USB");
        return {"USB"};
      } else if (id(battery_voltage).state > 4.18) {
        id(display1).filled_rectangle(111, -3, 24, 24, BLACK);
        id(display1).image(111, -3, id(batcharge), YELLOW, BLACK);

        // clear text background:
        id(display1).filled_rectangle(40, -2, 55, 20, BLACK);
        // output text center-aligned horizontally
        int display_centerwidth = id(display1).get_width()/2;

        if (id(battery_voltage).state > 4.5) {
           id(display1).print(display_centerwidth, -2, id(lato), GREEN, TextAlign::CENTER_HORIZONTAL, "CV");
           return {"Constant Voltage"};
        } else {
           id(display1).print(display_centerwidth, -2, id(lato), YELLOW, TextAlign::CENTER_HORIZONTAL, "CC");
           return {"Constant Current"};
        }
      } else {
        return {"Battery"};
      }
  # log system state: running or deep sleep (and reason)
  - platform: template
    name: "DeepSleep State"
    id: sleep_state
    icon: "mdi:power-sleep"
    entity_category: "diagnostic"
    device_class: ""
    
    

# DEEP SLEEP

# enable deep sleep capabilities and set wakeup-pin in energy-efficient ext1 mode
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
          // Turn off LDO for another 80uA savings 
          id(vbat_ldo_pwren).turn_off();
      - delay: 120ms    
      # send esp32 to deep sleep:
      - deep_sleep.enter: deep_sleep_control


# PUSH BUTTONS that can be pushed physically and remotely via Home Assistant
button:
  - platform: template
    name: "DeepSleep Invoke"
    id: deep_sleep_button
    entity_category: "diagnostic"
    device_class: ""
    icon: mdi:sleep
    # send device to deep sleep remotely:
    on_press: 
      then:
        - text_sensor.template.publish:
            id: sleep_state
            state: "Sleeping (remote invoke)"
        - script.execute: prepare_for_sleep

  - platform: template
    name: "WiFi Measure Strength"
    id: update_wifi
    entity_category: "diagnostic"
    device_class: ""
    icon: mdi:wifi-sync
    # manually update wifi signal strength
    on_press:
      then:
        - sensor.template.publish:
            id: wifi_signal_db
            state: !lambda 'return id(wifi_signal_db).state;'

  - platform: template
    name: "Button1 ShortPress"
    id: short_press1
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button1 ShortPress Pressed"
  
  - platform: template
    name: "Button1 LongPress"
    id: long_press1
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button1 LongPress Pressed"

  - platform: template
    name: "Button2 ShortPress"
    id: short_press2
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button2 ShortPress Pressed"
  
  - platform: template
    name: "Button2 LongPress"
    id: long_press2
    # no device action defined yet
    on_press:
      then:
        - logger.log: "Button2 LongPress Pressed"

# ON/OFF SWITCHES that can be switched physically and remotely via Home Assistant:
switch:
  # ON while device button 1 is kept pressed down
  - platform: template
    name: "Button1 Switch" 
    restore_mode: ALWAYS_OFF
    id: button1_switch
    optimistic: true
    icon: "mdi:toggle-switch-outline"

  # ON while device button 1 is kept pressed down
  - platform: template
    name: "Button2 Switch" 
    restore_mode: ALWAYS_OFF
    id: button2_switch
    icon: "mdi:toggle-switch-outline"
    optimistic: true

  # GPOI14 set as output to control the PWR_EN of the LDO chip
  # GPIO14 = 0 : LDO Off
  # GPIO14 = 1 : LDO On (used to measure the current battery voltage)
  - platform: gpio
    pin: GPIO14
    name: "VBAT LDO Power Enable"
    id: vbat_ldo_pwren
    inverted: true

binary_sensor:
  # Home Assistant API connectivity
  - platform: status
    name: "API Home Assistant"
    id: api_status
    on_state: 
      then:
        - if:
            condition:
              lambda: 'return id(api_status).state;'
              # if Home Assistant API is connected, the board is running:
            then:
              - text_sensor.template.publish:
                  id: sleep_state
                  state: "Running"
            # if the API is not in reach, the board is still running:
            else:
              - text_sensor.template.publish:
                  id: sleep_state
                  state: "Running"
  
  # physical GPIOs (buttons)

  # left button (boot button):
  - platform: gpio
    name: "Button Left"
    id: button_left
    icon: "mdi:toggle-switch-outline"

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
    
    on_click:
    # very short push increases display backlight brightness:
    - min_length: 50ms
      max_length: 250ms
      then:
        - logger.log: "physically dimming up"
        - light.dim_relative:
              id: back_light
              relative_brightness: 5%
              transition_length: 0.1s
    # short press:
    - min_length: 251ms
      max_length: 500ms
      then:
        - logger.log: "physical Short Press 1"
        - button.press: short_press1
    # long press:
    - min_length: 501ms
      max_length: 3000ms
      then:
        - logger.log: "physical Long Press 1"
        - button.press: long_press1

    # super long press (<3s) without need to release
    on_multi_click:
        - timing:
            - ON for at least 3.1s
          then:
            # invoke deep sleep
            - text_sensor.template.publish:
                id: sleep_state
                state: "Sleeping (manual invoke)"
            - script.execute: prepare_for_sleep
    
    # holding down the button:
    on_press:
      then:
        - logger.log: "physically switching ON left switch"
        - switch.template.publish:
            # switch is ON
            id: button1_switch
            state: ON

    # releasing pushed down button:
    on_release:
      then:
        - logger.log: "physically switching OFF left switch"
        - switch.template.publish:
            # switch is OFF
            id: button1_switch
            state: OFF
  
  # right button
  - platform: gpio
    name: 'Button Right'
    id: button_right
    icon: "mdi:toggle-switch-outline"

    pin:
      number: GPIO35
      # low active:
      inverted: True
      # is also used as deep-sleep wakeup pin:
      allow_other_uses: true      
      mode:
        input: True

    # debounce:
    filters: 
      - delayed_on: 10ms
      - delayed_off: 10ms
    
    # very short push decreases display backlight brightness:
    on_click:
    - min_length: 50ms
      max_length: 250ms
      then:
        - logger.log: "physically dimming down"
        - light.dim_relative:
              id: back_light
              relative_brightness: -5%
              transition_length: 0.1s
    # short press:
    - min_length: 251ms
      max_length: 500ms
      then:
        - logger.log: "physical Short Press 2"
        - button.press: short_press2
    # long press:
    - min_length: 501ms
      max_length: 3000ms
      then:
        - logger.log: "physical Long Press 2"
        - button.press: long_press2

    # super long press (<3s) without need to release
    on_multi_click:
        - timing:
             - ON for at least 3.1s
          then:
             # update wifi strength sensor:
             - logger.log: "updating WiFi strength measurement"
             - button.press: update_wifi
             
    # holding down the button:
    on_press:
      then:
        - logger.log: "physically switching ON right switch"
        - switch.template.publish:
            # switch is ON
            id: button2_switch
            state: ON
    # releasing pushed down button:
    on_release:
      then:
        - logger.log: "physically switching OFF right switch"
        - switch.template.publish:
            # switch is OFF
            id: button2_switch
            state: OFF

# DISPLAY

# use a separate "light" component for dimmable display backlight management:
output:
  - platform: ledc
    # GPIO4 is connected to display backlight:
    pin: 4
    id: display_backlight_pwm

# display backlight:
light:
  - platform: monochromatic
    output: display_backlight_pwm
    name: "Display Backlight"
    id: back_light
    # remember last dim state:
    restore_mode: RESTORE_AND_ON
    # support a pulse effect:
    effects:
      - pulse:
          name: noWifiConnection
          min_brightness: 60%
          max_brightness: 80%

# internal SPI for display:
spi:
  clk_pin: GPIO18
  mosi_pin: GPIO19
  id: spi_bus

# display component (dedicated st7789 component is deprecated, use generic ili9xxx instead):
display:
  - platform: ili9xxx
    model: ST7789V
    id: display1
    # hardware pins:
    cs_pin: GPIO5
    dc_pin: GPIO16
    reset_pin: GPIO23
    # T-Display screen dimensions:
    dimensions:
      height: 240
      width: 135
      offset_height: 40
      offset_width: 52
    # T-Display requires inverted codes:
    invert_colors: true
    # do not auto-clear. Redraw only when needed.
    auto_clear_enabled: false
    update_interval: 1s
    # rotation: 90°
    
    lambda: |-
      // get horizontal display width:
      uint displayWidth = it.get_width();
      
      // are we currently connected to WiFi?
      if (WiFi.status() == WL_CONNECTED) {
        // did we just come online and were offline before?
        if (id(isOnline) == false) { 
          // disable display backlight pulse:
          id(back_light).turn_on().set_effect("none").perform(); 
          // draw icon:      
          it.filled_rectangle(0, -3, 24, 24, BLACK); // erase icon area (for icons with transparency)
          it.image(0, -3, id(wifiOn), GREEN, BLACK); // use black background (for icons w/o transparency)
          // update state change:
          id(isOnline) = true;
        }

        // draw signal strength bar only when connected to WiFi
        uint signal_strength = id(wifi_signal_percent).state; // get the current signal strength
        if (id(lastSignalStrength) != signal_strength)
        {
          id(lastSignalStrength) = signal_strength;
          uint bar_length = signal_strength * displayWidth / 100; // map signal strength to bar length
          // erase bar background:
          it.filled_rectangle(0, 24, displayWidth, 2, GRAY); 
          // draw the bar:
          it.filled_rectangle(0, 24, bar_length, 2, GREEN); 
        }
      } else {
        // did we just go offline and were online before?
        // this also applies to boot where global variable isOnline is preset to true
        if (id(isOnline) == true) { 
          // enable display backlight pulse:
          id(back_light).turn_on().set_effect("noWifiConnection").perform(); 
          // draw icon   
          it.filled_rectangle(0, -3, 24, 24, BLACK); // erase icon area (for icons with transparency)
          it.image(0, -3, id(wifiOn), GRAY, BLACK); 
          // erase wifi strength graph:
          it.filled_rectangle(0, 24, displayWidth, 2, GRAY); 
          id(lastSignalStrength) = 0;
          // update state change:    
          id(isOnline) = false;
        }
      }

font:
  - file:
      type: gfonts
      family: Lato
      weight: 400
    id: lato
    size: 20
  - file:
      type: gfonts
      family: Lato
      weight: 700
    id: latobold
    size: 24

color:
  - id: WHITE
    red: 100%
    green: 100%
    blue: 100%
    white: 100%
  - id: RED
    red: 100%
    green: 0%
    blue: 0%
    white: 0%
  - id: GREEN
    red: 0%
    green: 100%
    blue: 0%
    white: 0%
  - id: BLUE
    red: 0%
    green: 0%
    blue: 100%
    white: 0%
  - id: YELLOW
    red: 100%
    green: 100%
    blue: 0%
    white: 0%
  - id: ORANGE
    red: 100%
    green: 65%
    blue: 0%
    white: 0%
  - id: BLACK
    red: 0%
    green: 0%
    blue: 0%
    white: 0%
  - id: GRAY
    red: 10%
    green: 10%
    blue: 10%
    white: 0%
  - id: LIGHTGRAY
    red: 80%
    green: 80%
    blue: 80%
    white: 0%
  - id: MEDIUMGRAY
    red: 50%
    green: 50%
    blue: 50%
    white: 0%


image:
  - file: mdi:wifi
    id: wifiOn
    resize: 24x24
  - file: mdi:wifi-off
    id: wifiOff
    resize: 24x24
  - file: mdi:battery-off-outline
    id: bat1
    resize: 24x24
  - file: mdi:battery-outline
    id: bat2
    resize: 24x24
  - file: mdi:battery-low
    id: bat3
    resize: 24x24
  - file: mdi:battery-medium
    id: bat4
    resize: 24x24
  - file: mdi:battery-high
    id: bat5
    resize: 24x24
  - file: mdi:flash
    id: batcharge
    resize: 24x24
  - file: mdi:power-plug
    id: powerPlug
    resize: 24x24
````


> Tags: Lilygo, TTGO, T-Display, ESPHome, Deep Sleep, Ext0, Ext1, esp32_ext1_wakeup, Display Disable, Home Assistant, Button, Switch, Sensor, Power Efficiency, Power Save, Battery, Voltage Sensor

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display/programming/usingesphome/addingdeepsleep?396856101907245252) - created 2024-10-06 - last edited 2024-10-09
