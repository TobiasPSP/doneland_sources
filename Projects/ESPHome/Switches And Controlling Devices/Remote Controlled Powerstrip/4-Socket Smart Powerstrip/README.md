<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# 4-Socket Smart Powerstrip

> Enhancing Commercial 4-Socket Powerstrip With ESPHome-Based Home Assistant Controller

In this article, I am using the [4-Socket Commericial Powerstrip](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/repurposingpowerstrip) that I disassembled before: it comes with all that is needed for a *smart powerstrip*, including a *5V power supply* and individually switchable sockets.


## Adding Microcontroller
For this project, I am repurposing [this ESPHome configuration](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/dual-gpioesphomeconfiguration), and I am using a [ESP32-C3 Super Mini](https://done.land/components/microcontroller/families/esp/esp32/c3/c3supermini) because of its tiny footprint and low cost.

> [!NOTE]
> While you can solder all components directly to the *ESP32-C3 board* for robustness and minimal space requirements, I chose to solder header pins to the board, and use pluggable cables to be able to experiment and play with this prototype.


<img src="images/esp32-c3-super-mini-custom-prototypeboard3_t.png" width="40%" height="40%" />

The microcontroller is going to control *four sockets* and uses *two GPIOs* per switch that are *inverted* (so you can use *low level trigger* and *high level trigger* relais, and can use [bi-polar bi-color signal LEDs](https://done.land/components/light/led/signalleds/bi-colorsignals/bipolarbicolorled)).

Here is the *ESPHome configuration*:

````
esphome:
  name: powerstrip-400w-ssr-1
  friendly_name: SSR PowerStrip 400W
  platformio_options:
    board_build.f_flash: 40000000L
    board_build.flash_mode: dio
    board_build.flash_size: 4MB

esp32:
  board: esp32-c3-devkitm-1
  variant: esp32c3
  framework:
    type: arduino

# Enable logging
logger:

# Enable Home Assistant API
api:
  encryption:
    key: "xxx"

ota:
  - platform: esphome
    password: "xxx"

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Powerstrip-Ssr-400W"
    password: "xxx"

captive_portal:


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
````

### Custom Expansion Board
Since I want to *experiment* with this setup, I decided to create a simple custom *expansion board* for the *ESP32-C3 Super Mini* out of some left-over header pin sockets:


<img src="images/esp32-c3-super-mini-custom-prototypeboard1_t.png" width="40%" height="40%" />

The microcontroller can be plugged into the inner header row:

<img src="images/esp32-c3-super-mini-custom-prototypeboard6_t.png" width="40%" height="40%" />

On the back side, I connected the headers so each microcontroller pin has *two sockets* that I can use to connect a relais trigger and/or a signal LED:

<img src="images/esp32-c3-super-mini-custom-prototypeboard2_t.png" width="40%" height="40%" />


### Mounting Microcontroller

Inside the commercial socket housing, I reuse the screw mounts that were originally holding the mechanical buttons. 

## Adding Bi-Color Signal LEDs
The original socket comes with simple *3mm red signal LEDs* that are directly wired to *AC power*. They are *on* when a particular socket was powered.

If you want more sophisticated *singal LEDs* that can signal both *on* and *off* state, replace the existing *LED* with *3mm bi-color bi-polar LEDs* that can emit *red* **and** *green* light, based on their polarity.

### LED Replacement
Pull out the existing *LED*, and de-solder their wires (including their current limiting resistors).

Solder a *330R* current limiting resistor to one leg of your *bi-polar LED*, and solder two wires to the other end of the resistor and the remaining *LED leg*. Make sure these wires are long enough to be connected to the microcontroller later.

Slide in the new LED into the holes in the housing where the old *LEDs* were located, and secure them with some *hot glue* or *superglue*.


## Mounting Solid State Relais
I chose to use commonly available *DIY AC solid state relays* for this project. Both *low level* and *high level* trigger boards will work:

<img src="images/ssr_2a_ac_2_top_t.png" width="40%" height="40%" />

> [!IMPORTANT]
> These simple DIY *SSR* can only handle **light loads** of up to *440W* (*2A*). For switching some simple low current lights, that is perfect. If you need to switch larger loads, do use appropriately rated *mechanical relais* or *industrial SSR*. When using the *SSR* I used here, **clearly label** your powerstrip. You (or others) may not remember this crucial limitation when the powerstrip is in use later.

These boards come with low-quality screw terminals that are too small to use larger-diameter wire, plus the terminals waste a lot of space. That's why I decided to *remove the screw terminals* with a *hot air gun*, and solder cables directly. 

<img src="images/ssr_diy_relais_remove_screw_terminals_t.png" width="100%" height="100%" />


If you don't feel comfortable removing them, you could also solder your own wires directly to the solder pins on the backside of the board. If you do, you might want to use the *through-pins* of the *SSR* directly, and not use the *screw terminal pins*.

Each relay board comes with *two relais*, so *two boards* are required.

> [!TIP]
> You can get these *SSR boards* also with just *one*, or with *four* SSR relais. Since the boards need to fit into the existing smartstrip housing, using two *two-relais* boards worked best.

### Designing Relais Mount

To safely secure both boards, I designed and *3D printed* two simple holders, repurposing the screw holes that were left in the powerstrip housing from the removed mechanical buttons:

<img src="images/4-socket-powerstrip-ssr-mount.png" width="40%" height="40%" />

The mount is designed to be slid onto one of the screw mounts left from the mechanical switches, then secured with the screw that originally helt a mechanical switch:

<img src="images/4-socket-powerstrip-ssr-mount2.png" width="40%" height="40%" />

You can [download the STL file](materials/ssr1_holder_4socket_smart_powerstrip.stl) if you like. This is what the *3D printer* part looks like:

<img src="images/4-socket-smart-powerstrip-ssr-fixation3_t.png" width="40%" height="40%" />

### Assemble Solid State Relais

The *mount* slides onto one of the pillars that previously secured the mechanical buttons:

<img src="images/4-socket-smart-powerstrip-ssr-fixation1_t.png" width="60%" height="60%" />

The fixation can then be secured to the pillar using one of the original screws. The *SSR* is then placed onto the fixation, and also secured, using two screws:

<img src="images/4-socket-smart-powerstrip-ssr-fixation4_t.png" width="60%" height="60%" />

## Materials

[STL file for SSR mount](materials/ssr1_holder_4socket_smart_powerstrip.stl)

> Tags: Smart Powerstrip, Home Assistant, ESPHome, Bi-Color LED, Bi-Polar LED

[Visit Page on Website](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/4-socketsmartpowerstrip?220724091201243010) - created 2024-08-31 - last edited 2024-08-31
