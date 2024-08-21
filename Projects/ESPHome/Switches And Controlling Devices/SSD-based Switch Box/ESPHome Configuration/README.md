<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# ESPHome Configuration for Powerstrip

> Designing And Testing ESPHome And Home Assistant Integration

Let's first design a basic *ESPHome configuration* for the microcontroller so we can test-drive the switches and remaining circuitry as we go.

If you are not familiar with *ESPHome* and don't know what a *configuration* is, you may want to head over to this [ESPHome Introduction](https://done.land/tools/software/esphome/introduction). In a nutshell, a *configuration* is the *programming* of your microcontroller, and as you see, with *ESPHome* there is no complex *C++ code*. You simply *describe* how you wired up your hardware - done.


## Basic ESPHome Configuration

The microcontroller controls a number of switches that in turn switch distinct *GPIOs*. 

This makes the *ESPHome configuration* very simple. Here is a basic configuration for six sockets using GPIOs available on a typical *ESP32 DevKitC* board (which I am using below for testing):

````
switch:
  - platform: gpio
    pin: GPIO4
    name: "LightSwitchSSR1"
    inverted: true

  - platform: gpio
    pin: GPIO13
    name: "LightSwitchSSR2"
    inverted: true

  - platform: gpio
    pin: GPIO14
    name: "LightSwitchSSR3"
    inverted: true

  - platform: gpio
    pin: GPIO16
    name: "LightSwitchSSR4"
    inverted: true

  - platform: gpio
    pin: GPIO17
    name: "LightSwitchSSR5"
    inverted: true

  - platform: gpio
    pin: GPIO20
    name: "LightSwitchSSR6"
    inverted: true
````


### Adjustments

You may want to adjust this *configuration* in three places:

* **GPIO:** I chose the *general purpose GPIOs* that are available with *ESP32* microcontrollers. If you are using a different microcontroller, adjust the *GPIOs* to the ones that can be used with your microcontroller. Below you can find an example for a *ESP32-S2 Mini*.
* **Inverted:** The *solid state relais* I use are *low level trigger*: to turn them *on*, the *GPIO signal* must be *low* (*high* turns them off). With *inverted: true* I ask *ESPHome* to pull the *GPIO low* when the switch is *on*, and vice versa. If you are using a *high level trigger* relais, simply remove this line for each *GPIO*.
* **Name:** Obviously, you can name your entities as you wish. The name you pick will later (in *Home Assistant*) become the default name for the switch. You can also rename it later.


## Test Driving Microcontroller

Do not connect any components to your microcontroller. Power it up with its *USB connection*, then [install the configuration](https://done.land/tools/software/esphome/introduction/editconfiguration) to your microcontroller.

Once the new firmware is uploaded and the microcontroller has rebooted, *Home Assistant* [auto-detects your new device](https://done.land/tools/software/esphome/introduction/addtohomeassistant). Make sure you approve adding your new device to *Home Assistant* when asked.

Once done, it is now time to go and grab a coffee. Give *Home Assistant* a few minutes to *fully import* your new *ESPHome device*.

> [!IMPORTANT]
> If you start working right away with a freshly imported device in *Home Assistant*, it is not ready yet, and its *entities* may be missing, or are incomplete. It takes a few minutes for the import to be fully completed.


### Creating Test Environment

Before connecting any component or hardware to your microcontroller, first test its basic functionality, and set up a *test dashboard*.

1. In *Home Assistant*, go to *Settings*, then *Devices & services*. On the *Integrations* tab, click *ESPHome*. You now see all of your imported *ESPHome devices*.

    <img src="images/6xsocket_ha1.png" width="100%" height="100%" />

2. Identify your device (mine is called *LightSwitch SSR #1*), and verify the number of *entities* reported below its name. There should be *7 entities*. If there is just one, you may have to wait a few more minutes for *Home Assistant* to fully import your device.

    <img src="images/6xsocket_ha2.png" width="100%" height="100%" />

3. Click on *7 entities*. You now see all seven *entities* and their *unique ID names*. Six of them represent the six switches you defined in your *configuration*. The seventh entity is added by default and can update the microcontroller firmware.

    <img src="images/6xsocket_ha3.png" width="100%" height="100%" />

4. Next, [add a new dashboard](https://done.land/tools/software/esphome/introduction/usingdashboards) in *Home Assistant*, and add the six entities that represent your six switches to the dashboard. You may rename your dashboards' default name *HOME* to something better. I called my dashboard *TestSwitch*. Your dashboard is easily accessible via the *Home Assistant sidebar* on the left side of the *Home Assistant screen*.

    <img src="images/6xsocket_ha4.png" width="100%" height="100%" />

### Testing Switch Logic
You now have a great test environment where you can change any of the switches and verify the results:

* Slide a switch to see if it stays that way. When it slides back after a moment, then your microcontroller may be offline or not reachable.
* Click on the icon in front of a switch. This opens a larger version of the switch control that tells you when this switch was changed the last time. Play with the switches, and verify that the logging works as expected.

    <img src="images/6xsocket_ha5.png" width="60%" height="60%" />

### Testing Logic Levels
Once that works, it's now time to test the actual *GPIOs* on your microcontroller.

<img src="images/proj_6_ac_example_multimeter_test2.png" width="100%" height="100%" />

Hook up a multimeter to one of the *GPIOs* you assigned to a switch, and to *GND*.

> [!IMPORTANT]
> Make sure you set your multimeter to a voltage range that can handle *5V* **before you connect the multimeter** to a *GPIO*. **Always disconnect** the multimeter before you turn it off again. Else, it may get **destroyed**: when you try and move its knob to **OFF**, it may switch to lower voltage ranges first (before it eventually reaches the **OFF** position). When the measured input signal is *high*, the *ADC* in cheap multimeters will be irreversibly damaged.

The multimeter should show either *0V* (*low*) or something close to *3.3V* (*high*). When you change the switch in your test dashboard that is associated with the *GPIO* you measure, the voltage should change.

If you used *inverted: true* in your *configuration*, the *GPIO* should show be *low* (and the multimeter should show *0V*) when the switch is **turned ON**.

Test this for all six *GPIOs* to make sure your logic works as intended.

> [!TIP]
> Verify that the *GPIO logic level* matches the logic level your *relais* requires. If the logic levels are mixed up, remove *inverted: true* from your configuration.

## Production Configuration

Once testing succeeded, it's time to design a production powerstrip. The *ESP32 DevKit4* microcontroller is bulky and expensive. A much cheaper, more powerful and very much smaller alternative is the *ESP32-S2 Mini*. This board is so small it fits easily even in tight enclosures.

These are the microcontroller-related parts of the configuration for a *ESP32-S2 Mini*:

````
substitutions:
  name: "powerstrip4-1"
  friendly_name: '4er PowerStrip #1'

esphome:
  name: "powerstrip4-1"
  friendly_name: "4er PowerStrip #1"
  min_version: 2024.6.0
  name_add_mac_suffix: false
  platformio_options:
    board_build.flash_mode: dio
  project:
    name: esphome.web
    version: dev

esp32:
  board: lolin_s2_mini
  variant: ESP32S2
  framework:
    type: arduino

````

### Refining the Configuration

For production, the *ESPHome configuration* was refined a little bit:

* **Icon:** each switch received a meaningful icon that later appears in *Home Assistant* and on your dashboards
* **Restore Mode:** each switch received a *restore mode*, so when the powerstrip is plugged out and loses power, it remembers the switch state and returns to the previous state when plugged in again.
* **Status LED:** the built-in *LED* on the microcontroller board was wired up as *status LED* that now blinks slowly while the microcontroller connects, and turns off once remote connectivity is established. The LED can now also be manually controlled like a switch.

Here is the final *ESPHome configuration*:

````

light:
  - platform: status_led
    name: "Status LED"
    id: esp_status_led
    icon: "mdi:alarm-light"
    restore_mode: ALWAYS_OFF
    pin:
      number: GPIO15
      inverted: false
      
switch:
  - platform: gpio
    pin: GPIO2
    name: "Switch1"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_ON
    inverted: true

  - platform: gpio
    pin: GPIO3
    name: "Switch2"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_ON
    inverted: true

  - platform: gpio
    pin: GPIO4
    name: "Switch3"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_ON
    inverted: true

  - platform: gpio
    pin: GPIO5
    name: "Switch4"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_ON
    inverted: true
````

> Tags: Powerstrip, EspHome, Configuration, Restore Mode, Switch

[Visit Page on Website](https://done.land/projects/esphome/switchesandcontrollingdevices/ssd-basedswitchbox/esphomeconfiguration?363939081521244352) - created 2024-08-10 - last edited 2024-08-10
