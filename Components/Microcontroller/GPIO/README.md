<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# GPIO

> General Purpose Input Output (GPIO)

*GPIO* (*General-Purpose Input/Output*) pins enable microcontrollers to interact with the external world. That's why they are so important, and that's why you should *know* what a *GPIO* can do and how it can be configured.

## Overview

*GPIOs* can be used as *input* or *output* and can work in *digital* or *analog* mode:

* **Digital Output:** a *digital output* can *source* and *sink* current. This is the most common type used to *invoke an action*, i.e. to turn on an *LED* or trigger a *relais switch*. It is also used to **send** *digital data* to devices like *displays*, using digital interfaces such as *I2C* or *SPI*.
* **Digital Input:** senses a *high* (*VCC*) and a *low* (*GND*) signal, i.e. to connect a push button, or to implement *digital data interfaces*. This is the most common type used to interface with buttons and other digital user interfaces, i.e. *rotary encoders*. It is also used to **receive** *digital data*.
* **Analog Input:** senses a range of input *voltage*, for example the result of an analog *sensor* or a *potentiometer*. The pin is internally routed to an *ADC* (*Analog-Digital-Converter*). The type of *ADC* determines the allowable input voltage range, and the voltage resolution that the *GPIO* can distinguish.
* **Analog Output:** the *GPIO* can provide a variable output voltage. Internally, the pin is routed to a *DAC* (*Digital-Analog-Converter*). The type of *DAC* determines the voltage range and its resolution.

> [!IMPORTANT]
> *GPIOs* must be set programmatically to one of these four modes. Not all *GPIOs* may support all modes. Some *GPIOs* may only serve as *input*. It depends on your microcontroller type whether it features a *ADC* and/or a *DAC*, and which *GPIOs* can connect to these.

## Pull-Up And Pull-Down Resistors
When a *GPIO* operates in *digital input* mode, so-called *pull-up* and *pull-down* resistors may become important.

Let's assume you connect a push button to a *GPIO* set to *digital input mode*. When the user now presses the push button, then the button connects the *GPIO* to whatever you wired it to, most typically either *VCC* (*high*) or *GND* (*low*). 

However, when the user is **not pressing** the push button, the *GPIO* is **not connected to anything**, and its state is *floating*: it has *random values* and can either be *high* or *low*.

* **Pull-Up Resistor:** A *pull-up resistor* is used when the *GPIO* should have a *high* value by default. A high-impedance resistor connects the *GPIO* to *VCC* so it is *high* unless you connect it to *GND*.
* **Pull-Down Resistor:** This works the other way around: when a *pull-down resistor* is enabled, it connects the *GPIO* to *GND* via a high-impedance resistor. The *GPIO* is now *low* by default. Only when you connect it to *VCC* will it change to *high*.

*GPIOs* may or may not have built-in *pull-up* and *pull-down* resistors that can be activated by code. If they are missing, add an *external* *pull-up* or *pull-down* resistor. *ESP32 microcontrollers* use *45kOhm* for their internal resistors. *10kOhm* resistors work just as well.

> [!TIP]
> *Pull-up* and *pull-down* resistors must be *high impedance* because you do not want to create a *short-circuit* when the *GPIO* is connected to *VCC* or *GND*. The lower the resistor, the faster can it set the pin state but the more current will it draw. Unless you are using special *high frequency* setups, a resistor value in the range of *10-100kOhm* seems like a good compromise. 


## Source And Sink
When a *GPIO* operates in *digital output* mode, it can *source* current, and it can *sink* current. Both terms basically descibe the *direction* of current flow.

### Sourcing Current (high active)
The most common type of circuitry is *sourcing* current: the *GPIO* is set to *high*, and the load is connected to *GND*.

In this mode, the *voltage* is always determined by the microcontroller. With a *ESP32*, for example, the *high* voltage is *3.3V*.

### Sinking Current (low active)
A lesser known but very flexible alternate way of wiring up your loads is *sinking* current: the *GPIO* is set to *low*, and the load is connected to *VCC* (or *any other voltage source*).

In this case, the *GPIO* acts as *GND* (when *low*), and *sinks any voltage* that you supply to it.

> [!TIP]
> With *sinking*, you are free to use any *voltage supply* at hand (provided it shares *GND* with the microcontroller). For example, when powering an *ESP32* with *5V USB*, you could power a *5V LED* directly from the power supply, and connect it to the *low active GPIO*.

> [!IMPORTANT]
> With *sinking*, GPIO **current and voltage limitations** still apply: i.e., the *ESP32 datasheet* states that *GPIOs* can handle voltages of up to only *3.3V*. In real world projects, many users successfully interface *ESP32 GPIOs* directly with *5V components* and use *sinking* with up to *5V*. Apparently *ESP32 GPIOs* are *5V tolerant*. Exceeding official datasheet specifications is entirely *on your own risk*, though.

### Sourcing And Sinking
Here is a great example illustrating how flexible *sinking* can be: a *digital output GPIO* needs a way for users to know whether the output is *on* or *off*. For this, two *LED* (one *green*, one *red*) should light up, depending on *GPIO state*.

Here is a very simple solution that uses *two LED*:

<img src="images/source_sink_led_schematics.png" width="100%" height="100%" />

* **Sinking (green):** the *green* LED is connected in *sinking* configuration: when the *GPIO* is *low*, it is connected to *GND*. The other end of the *LED* is connected to *VCC*. 
* **Sourcing (red):** the *red* LED is connected in *sourcing* configuration: when the *GPIO* is *high*, it provides *VCC*, and the other end of the *LED* is connected to *GND*.

This way, when the *GPIO* is *high*, the *red LED* is *on*, and when *GPIO* is *low*, the *green LED* is *on*.

## Absolute Limits
When working with *GPIO*, these pins must **always be operated within their specifications**:

* **Current:** in **output** mode, the maximum current for *ESP8266* is *12mA*, and for *ESP32* (depending on *GPIO*) either *20mA* or *40mA*. Other microcontrollers may have different limits, however they are similar. *GPIO* cannot directly drive high loads like *mechanical relais*, *power LED*, or *motors*. Use a MosFet for this.
* **Voltage:** in **digital input** mode, the maximum input value is *VCC*. A *3.3V ESP32 GPIO* should not be directly connected to a *5V component*. Use a *level shifter*, or at least add a current-limiting resistor.
* **Analog Voltages:** with **analog input**, the maximum voltage depends on the microcontroller *and* the PCB design. Exceeding the maximum analog voltage almost certainly destroys the *ADC* within milliseconds.


| Board | Analog Input Max Voltage |
| --- | --- |
| Arduino | 5V |
| ESP8266 | 1V |
| ESP32 | 3.3V |
| STM32 | 3.3V |
| RP2040 | 3.3V |

> [!NOTE]
> Some board manufacturers add voltage dividers in an effort to mimick *Arduino* behavior. *ESP8266 D1 Mini* boards often accept *5V* due to internal voltage dividers.

## ESP32 Current Limits

To provide you with some typical values, below are the specs for *ESP32 microcontrollers*:

| GPIO | Mode | Current |
| --- | --- | --- |
| 1,5,18,19,21,22,23| Source | 40mA |
| 0,2,4,12,13,14,15,25,26,27,32,33| Source | 40mA |
| 6,7,8,9,10,11,16,17| Source | 20mA |
| all of above | Sink | 28mA |

* *ESP32* use *three power domains* internally (that service groups of GPIOs), one of which has a lower *sourcing* limit than the other two.
* In early *ESP32 documentation*, *ESP8266 current limits* were published (*12mA*). This value applies to *ESP8266* only. *ESP32 GPIO* can source *20mA* and *40mA* (depending on GPIO).

> [!CAUTION]
> The sum of the total I/O current may not exceed *1.200mA*. Typically, the *voltage regulator* on your microcontroller board is a limiting factor that is kicking in much earlier: some types provide just *500mA*.

> Tags: Microcontroller, GPIO, Pull-Up, Pull-Down, Resistor, Sourcing, Sinking, LED
