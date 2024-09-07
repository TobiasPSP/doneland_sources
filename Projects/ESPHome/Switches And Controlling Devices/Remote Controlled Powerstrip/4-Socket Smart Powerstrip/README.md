<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# 4-Socket Smart Powerstrip

> Enhancing Commercial 4-Socket Powerstrip With ESPHome-Based Home Assistant Controller

In this article, I am using the [4-Socket Commericial Powerstrip](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/repurposingpowerstrip) that I disassembled before: it comes with all that is needed for a *smart powerstrip*, including a *5V power supply* and individually switchable sockets.


<img src="images/4-socket-smart-powerstrip-original-housing_t.png" width="100%" height="100%" />


## Adding Microcontroller
For this project, I am repurposing [this ESPHome configuration](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/dual-gpioesphomeconfiguration), using a [ESP32-C3 Super Mini](https://done.land/components/microcontroller/families/esp/esp32/c3/c3supermini) because of its tiny footprint and low cost.

> [!NOTE]
> While it makes sense to solder all wires directly to the *ESP32-C3 board* for robustness and to further reduce space requirements, I chose to use header pins and pluggable cables so I can experiment and play with this prototype.


<img src="images/esp32-c3-super-mini-custom-prototypeboard3_t.png" width="40%" height="40%" />

### ESPHome Configuration
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

### Testing
Upload the *ESPHome configuration* to the microcontroller, and make sure everything works as expected - before you proceed with anything else:

* **Add to Home Assistant:** *Home Assistant* should recognize your new device once it goes online for the first time. Add it to *Home Assistant*
* **Visit Device:** In *Home Assistant*, go to *Settings/Devices&services*, click *Devices* tab, search for your device name, and check to see whether your device (and all of its entities) can be found.

    <img src="images/4-socket-powerstrip-ha_test1.png" width="100%" height="100%" />

* **Test-Drive Switches:** Open the device and double-check that the *Controls* section looks like this:

    <img src="images/4-socket-powerstrip-ha_test2.png" width="100%" height="100%" />

    Even if you did not yet connect anything to the microcontroller, you can still test it: use the *Status LED* switch to turn the blue on-boad LED on and off.

Once everything works, you can disconnect the microcontroller and start mounting it in the powerstrip housing. Since the *AC*-driven *5V power supply* won't be functional until at the very end, you may want to connect the microcontroller to a powerbank via its *USB connection* so you can continuously test it while adding *LEDs* and relais boards.

> [!IMPORTANT]
> **Do not connect AC** to the powerstrip at this time. Since there are many uninsulated open contacts, that would be irresponsible and dangerous. We'll be able to do all testing with a safe *5V voltage supply* from a *USB powerbank*.

### Custom Expansion Board
Since I want to *play* with this setup and try out different components (such as different relays and signal LEDs), I created a simple *expansion board* for the *ESP32-C3 Super Mini* out of some left-over header pin sockets:


<img src="images/esp32-c3-super-mini-custom-prototypeboard1_t.png" width="40%" height="40%" />

The microcontroller plugs into the inner header row:

<img src="images/esp32-c3-super-mini-custom-prototypeboard6_t.png" width="40%" height="40%" />

On the reverse side, I connected the headers so each microcontroller pin now has *two sockets* that I can use to connect relais trigger and/or signal LEDs:

<img src="images/esp32-c3-super-mini-custom-prototypeboard2_t.png" width="40%" height="40%" />


### Mounting Microcontroller

Inside the commercial socket housing, I reuse the screw mounts that were originally holding the mechanical buttons. 

#### Mount directly
If you'd like to use the microcontroller board directly, a [3D printed part](materials/mc%20mount.stl) slides over one of the pilars of the original housing that previously secured the mechanical buttons, and can be screwed onto the pilar using the original screw:

<img src="images/4-socket-powerstrip-mc-mount.png" width="40%" height="40%" />

Flipped over, you see the recess for the screw that secures the part to the housing, and an *M2 hole* at one of the corners that will secure the *PCB*:

<img src="images/4-socket-powerstrip-mc-mount2.png" width="40%" height="40%" />

The part provides you with a *30x33mm* flat mounting area where you can i.e. use glue or strips to secure the microcontroller board directly. Use this [3D .stl file](materials/mc%20mount.stl) to slice and print the part if you like.

Slide the part over one of the screw pilars, then use the original screw to secure the part to it. Now you can glue or screw the microcontroller board onto the mounting area:

<img src="images/4-socket-powerstrip-mc-mount-installed_t.png" width="40%" height="40%" />

#### Mounting Expansion Board
Since I am using a fairly large *expansion board* (see above), it cannot be mounted on the mounting plate. The overall height would exceed the space constraints.

Instead, I drilled a *8mm* hole into the middle of the PCB so that it can slide onto the plastic pilar of the original housing. 


<img src="images/4-socket-powerstrip-esp32c3-pcb-expansion_t.png" width="30%" height="30%" />

With an even smaller [3D printed part](materials/mc%20mount%20small.stl), it can then secured using the original screw:

<img src="images/4-socket-powerstrip-mc-mount_small.png" width="20%" height="20%" />

Next, slide the PCB over one of the srew pilars:

<img src="images/4-socket-powerstrip-mc-pcb-mount_t.png" width="60%" height="60%" />

Press the *3D part* onto the pilar until the PCB cannot move anymore. Then use the original screw to tighten the cap on the pilar:


<img src="images/4-socket-smart-powerstrip-pcb_screw_t.png" width="60%" height="60%" />

Finally, plug in the *ESP32 C3 Super Mini*. You now have plenty of headroom to use header pins and cables and still be able to close the original housing:


<img src="images/4-socket-smart-powerstrip-esp32c3-complete_t.png" width="60%" height="60%" />





## Adding Bi-Color Signal LEDs
The original powerstrip came with simple *3mm red signal LEDs* that are directly wired to *AC power* and *on* when a particular socket was powered. You can leave them in place if that's what you want.

If you opt for more sophisticated *singal LEDs* that can signal both *on* and *off* state (in *red* and *green*), replace the existing *LED* with [3mm bi-color bi-polar LEDs](https://done.land/components/light/led/signalleds/bi-colorsignals/bipolarbicolorled) that can emit two colors, based on their polarity.

### LED Replacement
Pull out the existing *LED*, and de-solder their wires from the sockets (including their current limiting resistors).

Solder a *150R* current limiting resistor to one leg of your *bi-polar LED*. Solder two wires to the *LED* that are long enough to be connected to the microcontroller. Plug the wires into the two *GPIOs* that represent one switch, i.e. use *GPIO0* and *GPIO2* for *switch 1* (see *ESPHome configuration* above for GPIO assignments).


<img src="images/4-socket-smart-powerstrip-led-smdresistor2_t.png" width="60%" height="60%" />

> [!TIP]
> I had a left-over reel of 150R SMD resistors and used these with the *LEDs*. It is a bit more fiddly but works well and saves space.

Once you connect the *LED* to the microcontroller, power it on using external power (i.e. a powerbank). The LED should show a *red* light. If it emits *green*, then switch over the cables (reverse LED polarity).

<img src="images/4-socket-smart-powerstrip-led-smdresistor_test_t.png" width="60%" height="60%" />


Next, go to *Home Assistant* again, and navigate to your device's *control* panel (see above). 

<img src="images/4-socket-powerstrip-ha_test3_t.png" width="40%" height="40%" />

Turn *Switch 1* on. The *LED* should turn *green*. *Turn off* the switch. The *LED* should turn *red*.

Turn *on* the switch again, then remove power from the microcontroller. The *LED* is off. Now restore power. The *LED* should immediately come up with a *green* light. Thanks to the *restore mode*, each switch remembers its state.

Once all four *LED* work as expected, you can position them in the existing *3mm LED holes*, and glue them.

Now it's time to add the *relais* that do the actual *AC* switching. 

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

[STL file for large microcontroller mount](materials/mc%20mount.stl)     
[STL file for small microcontroller mount](materials/mc%20mount%20small.stl)     
[STL file for SSR mount](materials/ssr1_holder_4socket_smart_powerstrip.stl)     

> Tags: Smart Powerstrip, Home Assistant, ESPHome, Bi-Color LED, Bi-Polar LED

[Visit Page on Website](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/4-socketsmartpowerstrip?220724091201243010) - created 2024-08-31 - last edited 2024-09-06
