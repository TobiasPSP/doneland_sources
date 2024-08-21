<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Single-GPIO Bi-Color Signal LED

> Designing A Bi-Color Signal LED Driven By A Single GPIO

The powerstrip uses one *GPIO* per *socket* to switch a load. Optionally, the *state of each GPIO* needs to be visualized. For this, *no extra GPIO* or added complexity is wanted. Instead, in this section you see a few designs on how to create a bi-color *signal LED* that can be directly connected to a *GPIO*. The signal LED then changes color based on the state of the *GPIO*.

There are three different approaches discussed here:

* Using two separate LEDs on one GPIO
* Using a bi-polar bi-color LED
* Using a RGB or three-legged bi-color LED


## Using Two Separate LEDs
To indicate whether a socket is powered or not, *two LED* are used. When the socket is powered, a *green LED* is *on*, else a *red LED*.

### Schematics

In order to keep the effort minimal, both *LED* should be controlled by the *same GPIO* that also controls the *SSR*. Here is the schematic:


<img src="images/proj_6_ac_indicatorled_schematics.png" width="100%" height="100%" />

And here's a quick refresher on *LEDs* and where to find their *cathode* (**-**) and *anode* (**+**):

<img src="images/overview_led_4xsocket.png" width="60%" height="60%" />



### Description

The *LEDs* used in this project require approximately *10mA* to light up. At *3.3V*, this requires a current limiting resistor of *90 ohms* for the *green LED*, and *130 ohms* for the *red LED*:

````powershell
PS> Get-LedResistor -Current 10 -OperatingVoltage 3.3 -Color red, green


Required Resistor (Ohm) : 130
Operating Voltage (V)   : 3.3
Led Current (mA)        : 10
Led Voltage (V)         : 2
Led Color               : red

Required Resistor (Ohm) : 90
Operating Voltage (V)   : 3.3
Led Current (mA)        : 10
Led Voltage (V)         : 2.4
Led Color               : green

WARNING: LED Forward Voltage was guessed from color and can be completely different. Use at own risk.
````

The *GPIO* is either *high* (supplying *VDD*) or *low* (connected to *GND*).

* **Low:** When the *GPIO* is *low*, the **green** *LED* is on. Its *anode* (**+**) is connected to the positive voltage supply.
* **High:** When the *GPIO* is *high*, then the *green LED* is *off* (because being a *diode*, it cannot conduct power in this direction). Instead, the **red** *LED* turns on: its *cathode* (**-**) is connected to *GND*.

> [!IMPORTANT]
> Make up your mind *which LED* should turn on *when*. The circuit cannot be changed later. Since I am using a *low level trigger* board, the *solid state relais* is *on* when the *GPIO* is *low*. Accordingly, the **green** *LED* will be *on* when the outlet has power. If you want it the other way around, or if you want to use a *high level trigger* board, simply flip both *LEDs* and their resistors.



### Testing
Let's first test the schematics. For this, connect *3.3V* and *GND* to the rails of your breadboard. 

Then, connect one of the *GPIOs* that you use in your configuration (i.e. *GPIO4*) to both the *cathode* of the *green LED* and the *anode* of the *red LED*.



<img src="images/project_led_gpio_status_smartplug_ssr_red_t.png" width="60%" height="60%" />

Connect the *90 ohms* resistor to the *anode* of your *green LED*, and connect the other end of the resistor to *3.3V*.

Likewise, connect the *130 ohms* resistor to the *cathode* of your *red LED*, and connect the other end of the resistor to *GND*.

Now, when you change the switch in your *Home Assistant* dashboard that represents the *GPIO* you wired up, the *LEDs* should indicate the current switch status.

## Creating Signal LED Panels

For a *smart power strip* with *four sockets*, we need *four LED pairs*. I decided to keep it modular by placing two LED pairs on one perfboard. Make sure you place the *green* and the *red LED* in opposite orientation onto the perfboard:

<img src="images/project_led_gpio_status_smartplug_ssr_1_t.png" width="20%" height="20%" />

Next, ensure that both LED align with the perfboard and are not tilted:

<img src="images/project_led_gpio_status_smartplug_ssr_2_t.png" width="60%" height="60%" />

Finally, bend the LED legs all the way to the sides so the LEDs are fixed and won't slide out when you solder them to the perfboard.

<img src="images/project_led_gpio_status_smartplug_ssr_5_t.png" width="40%" height="40%" />


### Adding Resistors

Identify the side of the LEDs that will be connected to the *GPIO*: that's the *cathode* (shorter leg) of the *green LED* and the *anode* (longer leg) of the *red LED*.

On the *opposite* side of the *LEDs*, solder the *resistors* to the *LEDs*:


<img src="images/project_led_gpio_status_smartplug_ssr_6_t.png" width="40%" height="40%" />

Do this on both sides.

<img src="images/project_led_gpio_status_smartplug_ssr_7_t.png" width="60%" height="60%" />

Then trim off the legs of the *LEDs*. Do **Not** trim off any part of the resistors.

### Wires For GPIOs

Connect the other end of each *LED pair* with a wire, connecting the *red led anode* and the *green led cathode*. This provides you with two wires that later can be connected to the two *GPIOs* that you want to monitor.

### Wires For Plus And Minus

Connect the two resistors that come from the *red LEDs* somewhere in the middle of the perfboard. Where the resistors connect will be the place where you later connect *GND*.

Do the same with the two resistors that come from the *green LEDs*: where these connect will later be the supply point for *3.3V*.

> [!IMPORTANT]
> Since the wires will cross over each other at some point, you may want to put the resistors that come from the *green LEDs* in red *heat shrink*. Note how one resistor is covered in heat shrink in the picture below:

<img src="images/project_led_gpio_status_smartplug_ssr_8_t.png" width="60%" height="60%" />

Finally, add the power supply cables: connect a *red wire* to the junction point of the two *green LED resistors*, and add a *black wire* to the junction point where the two *red LED resistors* connect:

<img src="images/project_led_gpio_status_smartplug_ssr_11_tlabel.png" width="60%" height="60%" />



### Testing

Once you have finished the perfboard, you can perform a first test: connect *3.3V* and *GND* to your red and black wire. Next, connect one of the *GPIO wires* to *GND*, then to *3.3V*. The appropriate LED should turn on.

When that works, it's time to add the perfboard to your test setup: connect two wires to two of the GPIOs you use in this project (i.e. GPIO13 and GPIO14).

<img src="images/project_led_gpio_status_smartplug_ssr_13_t.png" width="60%" height="60%" />

Connect the perfboard cables for *3.3V* and *GND* to your breadboard power rail, then connect the two *GPIO wires* to the two GPIOs.

The two *LED pairs* on your perfboard should immediately start to signal the *GPIO state*, and when you go to your *Home Assistant test dashboard* and change the switches, then the *LEDs* on your perfboard should reflect these changes.

When this works for you, it is now time to add the *solid state relais*.


> Tags: Bi-Color, Signal LED

[Visit Page on Website](https://done.land/projects/esphome/switchesandcontrollingdevices/ssd-basedswitchbox/bi-colorsignalled?288563081521244352) - created 2024-08-20 - last edited 2024-08-11
