<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Advanced ESPHome Configuration for Powerstrip

> Sophisticated ESPHome Configuration For A PowerStrip That Can Operate More Than One GPIO

The [simple ESPHome configuration](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/simpleesphomeconfiguration) discussed earlier used *one* GPIO per socket. That was sufficient to operate *relais* and also optionally to use a simple *signal LED* to signal socket state.

If you'd like to use more advanced *signal LEDs*, for example [bi-polar bi-color LEDs](https://done.land/components/light/led/signalleds/bi-colorsignals/bipolarbicolorled#using-two-gpios) that can signal different states (like *on* and *off*), you may need more than one *GPIO* per switch.

In this article, you learn how to design a *ESPHome configuration* that can operate *any number of GPIOs* per switch. This article assumes that you already familiarized yourself with the [simple ESPHome configuration](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/simpleesphomeconfiguration) which is used as a start for the advanced configuration below.

## Designing Configuration
Below is a *ESPHome configuration* for a [ESP32-C3 Super Mini](https://done.land/components/microcontroller/families/esp/esp32/c3/c3supermini) microcontroller. Since this microcontroller has *10 freely assignable GPIOs*, the configuration creates *five* switches that operate *two GPIO* in complimentary fashion: when a switch is *turned on*, then one *GPIO* is *high* while the other is *low*, and when the switch is *turned off*, both *GPIO* states reverse.

> [!TIP]
> The complimentary logic levels allow you to use it both for *low active* and *high active* relais, and you can connect a [bi-polar bi-color status LED](https://done.land/components/light/led/signalleds/bi-colorsignals/bipolarbicolorled) directly to the *GPIOs* for a switch. If you'd rather have both *GPIOs* work the same (i.e. to turn on two different devices), simply remove `inverted: true` for the GPIOs you want to change.

### ESP32-C3 Super Mini

Here is the initial part of the *configuration* that defines the microcontroller. I used a *ESP32-C3 Super Mini*, but you can easily change this part to any other supported microcontroller.

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
````

> [!IMPORTANT]
> If you do change the microcontroller type, make sure you also change the assigned GPIO numbers so they refer to GPIOs that are actually available with the microcontroller you picked.

Below is the pin assignment that the *configuration* defines. Note that *GPIO High* is the *GPIO* that is *high* when the switch is *on* (*high active*). *GPIO Low* is the *GPIO* that is *low* when the switch is *on* (*low active*):

| Switch | GPIO High | GPIO Low |
| --- | --- | --- |
| A | 2 | 0 |
| B | 4 | 3 |
| C | 20 | 21 |
| D | 7 | 10 |
| E | 5 | 6 |

Here is the part of the *configuration* that defines the switches and assigned *GPIOs*:

````
light:
  - platform: status_led
    name: "Status LED"
    id: esp_status_led
    icon: "mdi:alarm-light"
    pin:
      number: GPIO8
      inverted: true
    restore_mode: ALWAYS_OFF

output:
  - platform: gpio
    pin: GPIO0
    id: 'relay1'
    inverted: true
  - platform: gpio
    pin: GPIO2
    id: 'led1'
  - platform: gpio
    pin: GPIO3
    id: 'relay2'
    inverted: true
  - platform: gpio
    pin: GPIO4
    id: 'led2'
  - platform: gpio
    pin: GPIO21
    id: 'relay3'
    inverted: true
  - platform: gpio
    pin: GPIO20
    id: 'led3'
  - platform: gpio
    pin: GPIO10
    id: 'relay4'
    inverted: true
  - platform: gpio
    pin: GPIO7
    id: 'led4'
  - platform: gpio
    pin: GPIO6
    id: 'relay5'
    inverted: true
  - platform: gpio
    pin: GPIO5
    id: 'led5'
  
switch:
  - platform: output
    name: "Switch1"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_OFF
    output: relay1
    on_turn_on:
      then: 
        - output.turn_on: led1
    on_turn_off:
      then:
        - output.turn_off: led1

  - platform: output
    name: "Switch2"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_OFF
    output: relay2
    on_turn_on:
      then: 
        - output.turn_on: led2
    on_turn_off:
      then:
        - output.turn_off: led2
  
  - platform: output
    name: "Switch3"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_OFF
    output: relay3
    on_turn_on:
      then: 
        - output.turn_on: led3
    on_turn_off:
      then:
        - output.turn_off: led3

  - platform: output
    name: "Switch4"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_OFF
    output: relay3
    on_turn_on:
      then: 
        - output.turn_on: led4
    on_turn_off:
      then:
        - output.turn_off: led4

  - platform: output
    name: "Switch5"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_OFF
    output: relay5
    on_turn_on:
      then: 
        - output.turn_on: led5
    on_turn_off:
      then:
        - output.turn_off: led5
````

### How GPIO Grouping Works
Unfortunately, the key `output:` accepts only *one* output, and there can only be *one* `output:` per switch.

In order to *still* operate *two GPIOs*, the *configuration* uses the events `on_turn_on` and `on_turn_off`.

## Test Driving Microcontroller

Do not connect any components to your microcontroller. Power it up with its *USB connection*, then [install the configuration](https://done.land/tools/software/esphome/introduction/editconfiguration) to your microcontroller.

Once the new firmware is uploaded and the microcontroller has rebooted, *Home Assistant* [auto-detects your new device](https://done.land/tools/software/esphome/introduction/addtohomeassistant). Make sure you approve adding your new device to *Home Assistant* when asked.

Once done, it is now time to go and grab a coffee. Give *Home Assistant* a few minutes to *fully import* your new *ESPHome device*.

> [!IMPORTANT]
> If you start working right away with a freshly imported device in *Home Assistant*, it is not ready yet, and its *entities* may be missing, or are incomplete. It takes a few minutes for the import to be fully completed.


### Creating Test Environment

To test the *configuration*, set up a *test dashboard* in *Home Assistant*, essentially repeating the steps that you performed with the [simple configuration](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/simpleesphomeconfiguration).

When you operate a switch in your test dashboard, the two associated *GPIOs* should respond with complementary logic levels (when one is *high*, then the other is *low*, and vice versa).

#### Adding Signal LED
Once this works, you can hook up your [bi-polar bi-color signal LED](https://done.land/components/light/led/signalleds/bi-colorsignals/bipolarbicolorled) to both *GPIOs*. Do not forget to use a *current limiting resistor* that matches your LED, i.e. *330R*.

> [!TIP]
> If you use a classic *LED*, that's fine, too. It will light up just for *one* state, and remain dark for the *other state*. But again, do not forget to use a current limiting resistor.

With this in place, turn the switch *on* and *off*, and see how the *LED* changes color. If you'd like the colors to be switched around, simply wire the *LED* in opposite direction.

#### Adding Relais
Once the *LED* works as expected, you can now connect the *relais trigger line* to **one** of the two *GPIOs*. Which one you choose depends on the type of *relais logic*, and how you want the relais to behave. With a *low active* relais, connect it to the *GPIO Low* pin (see the table above for the pin numbers). If you'd like the relais to be *off* when the switch is *on*, or if you are using a *high active* relais, take the other *GPIO*.

> Tags: Powerstrip, EspHome, Configuration, Switch, Multiple GPIO
