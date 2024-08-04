<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# GPIO

> General Purpose Input Output (GPIO)



*GPIO* (*General-Purpose Input/Output*) pins enable microcontrollers to interact with the outside world. *GPIOs* are among the most important microcontroller features, and the *number of available GPIOs* may be an important consideration when selecting a microcontroller board.


<img src="images/gpio_overview_naming2_overview_t.png" width="100%" height="100%" />

Both *board* **and** *type of microcontroller* together determine the number of GPIOs that you can use: some boards expose only some of the *GPIOs* in exchange for a *smaller board footprint*.


## Available GPIOs
**Not every header pin** exposed by a microcontroller board **is a GPIO**, and not every *GPIO* **may be used by you**.

### Power Supply

Some pins handle *power* and are no *GPIOs* in the first place:

* **GND** connects to *ground*
* **3V3** provdes access to the *regulated voltage* that is also powering the microcontroller
* **VBUS/5V** provides access to the raw *input voltage*.


<img src="images/gpio_overview_naming2_s2mini_t.png" width="100%" height="100%" />

### Special Functions
There may be some specialty pins exposed, i.e. **EN** which can be used to put the microcontroller in various *deep sleep* modes, or **RESET**, which resets the microcontroller.

### Reserved GPIOs

The remaining pins typically are all *GPIOs*. However you *still* can't just pick one of these remaining *GPIOs*. Some of them may be used for *internal purposes*:

* **Strapping:** *GPIOs* may play a crucial role during *booting*. They can be used freely after booting has completed but are off-limits before. Else, your microcontroller may not boot correctly or expose unexpected behavior.
* **Flash:** Some microcontrollers use *external flash memory* (which is integrated into the microcontroller module but still not part of its silicon). Since this memory is treated like an external component, some *GPIOs* are required to communicate with it. These GPIOs are permanently off-limits for you.


## Pin Labels
Beginners are easily confused by *GPIO pin labels*: 

Source code may refer to *GPIOs* by labels that start with **D** (i.e. *D4*), or **A** (i.e. *A1*). Then again, some other source code may use raw numbers, or labels like **GPIO** plus a number (i.e. *4*, or *GPIO4*).

> [!IMPORTANT]
> **D4** and **GPIO4** are **not the same thing**. **D4** can point to any *GPIO number* and depends on the board you are using.


Here is what the pin designators mean:

* **4 (raw number):** these designate the hardware pin numbers of a particular microcontroller
* **GPIO4:** same as pure numbers. *GPIO4* and *4* both refer to pin **4** on a microcontroller
* **D4:** arbitrary definition by a *board manufacturer*. Your *IDE* (*programming editor*) translates this label to the *real hardware pin number* at compile time. The real number depends on the physical board and microcontroller type you are using.


### Hardware-Neutral Code
The different pin label notations determine whether your code is *hardware-neutral*, or tied to a particular microcontroller type:

* **Hardware-Specific:** raw pin numbers are *hardware-specific* and apply only to a given *microcontroller type*. *GPIO4* or pin *4* would always refer to the same pin on any *ESP32 board*, but pin *4* could serve a completely different purpose on an *Arduino ATMega* board.
* **Hardware-Neutral:** **D***x* pin numbers are an *abstraction*: **D2** always refers to the *second usable digital gpio*, regardless of how a particular microcontroller board organizes its pins. This requires that your *IDE knows the pin mapping* for the particular microcontroller and board you are using, so it can translate the abstract label back to the real hardware pin number at compile time.



## Historic Context On GPIO Labels

It may not be entirely up to you whether you can use hardware-neutral pin labels like **D4**, or raw pin numbers like **2** or **GPIO2**: some board manufacturers stopped using the **D***x*- and **A***x*-notation altogether. 

When there are no abstract pin labels defined for a particular microcontroller board, you **must** use the hardware pin numbers.

### How Abstract Pin Labels Started

Older (and less capable) microcontrollers - like early *Arduinos* - used *GPIOs* that weren't *general purpose* but instead *hard-wired*, and could be used *exclusively* in *digital* **or** in *analog* mode.


That's why *historically*, the early *Arduino boards* labeled its *GPIOs* with **D***x* (for *digital GPIOs*) and **A***x* (for *analog GPIOs*):


<img src="images/gpio_overview_naming2_mega_t.png" width="100%" height="100%" />

For beginners, this simplified working with *GPIOs* because it was clear on first sight which pins represented usable *GPIOs*, and what their capabilities were.

### Modern Microcontrollers

With modern *microcontrollers*, *GPIOs* truly became *general purpose* and could now route any pins to *ADCs* and *DACs* as needed. Almost any *GPIO* can now be set to *input*, *outut*, *digital*, and *analog* mode, and digital interfaces like *I2C* and *SPI* aren't necessarily fixed to dedicated pins anymore, either.


The old pin notation was *still* often continued to use, i.e. the popular *ESP8266 D1 Mini* still labels its pins **D***x* - even though these pins now as well be used as *analog* inputs:

<img src="images/gpio_overview_naming2_esp8266d1mini_t.png" width="100%" height="100%" />


### ESP32 And Hardware Pin Numbers
As microcontrollers became even more capable, some board designers started to dump the abstract **D***x*- and **A***x*-labels altogether.

The *ESP32 S2 Mini* for example uses just hardware pin numbers:


<img src="images/gpio_overview_naming2_s2mini_t.png" width="100%" height="100%" />


With the appropriate *board translation table* in your *IDE*, your code would still be *hardware-neutral*: since *GPIOs* were now truly *generic*, the hardware pin *4* could finally be mapped to the abstract pin label *D4*.

Yet other board manufacturers started to *mix* labels: the *ESP32 DevKitC V4* uses the old **D***x* notation for some of its pins (to provide code compatibility) but uses raw numeric hardware pin numbers for the majority of its remaining *GPIOs*:

<img src="images/gpio_overview_naming2_esp32devkitc1v4_2_t.png" width="100%" height="100%" />

This way, users can continue to use simple code examples with their abstract *GPIO labels* that were written for other microcontroller boards. Here is the mapping for *ESP32 DevKitC V4* boards:

| Abstract Label | GPIO |
| --- | --- |
| D0 | 7 |
| D1 | 8 |
| D2 | 9 |
| D3 | 10 |




### Conclusion


With code examples written by someone else, check *how* the author has referenced *GPIO pins*:

* **Numbers/GPIO*x*:** make sure the code was written for the same microcontroller type you are using. You may have to replace the numbers with valid *GPIO pin numbers* available on your microcontroller type.
* **Dx Labels:** make sure your microcontroller board defines these labels. If not, replace them with the hardware pin number of any available *GPIO* on your microcontroller board.

### Your Own Code 
If you're writing code just for yourself, to be used privately in your own devices, then sticking to the hardware pin numbers of your particular microcontroller hardware is easiest and most robust. 

Why add complexity and abstract hardware if you don't need to maintain compatibility with different hardware in the first place?

> [!TIP]
> In fact, some *ESP32 boards* such as the *ESP32 S2 Mini* do no yet seem to be fully supported by *Arduino IDE*/*platformio*: pin labels like **D2** aren't defined for these boards, and when you use them in your code, you run into compile errors.


If you are planning to *publicly share* your code, or use it on different microcontroller platforms, abstract *GPIO labels* are better - provided your microcontroller board has defined them.


## GPIO Modes

*GPIOs* are *general purpose*, so they can be used in *four different ways*:

| Mode | Use Case |
| --- | --- |
| Digital Output | can *source* and *sink* current. This is the most common type to *invoke an action*, i.e. to turn on an *LED*, and can be used to **send** *digital information* to devices like *displays* using digital interfaces such as *I2C* or *SPI*. |
| Digital Input | differentiates a *high* (*VCC*) from a *low* (*GND*) signal. This is the most common type used to interface buttons and other digital components, i.e. *rotary encoders*. It is also used to **receive** *digital data*. |
| Analog Input | senses a *voltage range*, for example the readings from an analog *sensor*, or a *potentiometer*. This mode requires the *GPIO* to internally route to an *ADC* (*Analog-Digital-Converter*), and the type of *ADC* determines the allowable input voltage range and the voltage resolution that the *GPIO* can distinguish. |
| Analog Output | can provide a variable output voltage, i.e. to produce *sounds* or modulate wave forms. This mode requires the *GPIO* to internally route to a *DAC* (*Digital-Analog-Converter*). The type of *DAC* determines the output voltage range and its resolution. |

*(whether your microcontroller supports all four modes for a given GPIO is a different question.)*

### Setting Mode
A *GPIO* can always only work in *input* or *output* mode, and this mode must be set in your code.

````c++
pinMode(4, OUTPUT);
pinMode(13, INPUT);
````

#### Digital Output: Blinking LED
Here is a simple example illustrating how a *LED* connected to *GPIO13* can blink. Make sure you add an appropriate current limiting resistor to the *LED* (i.e. 150 ohms):

````c++
void setup() {
  pinMode(13, OUTPUT); // Set digital pin 13 as an output
}

void loop() {
  digitalWrite(13, HIGH); // Turn on the LED connected to pin 13
  delay(1000);            // Wait for 1 second
  digitalWrite(13, LOW);  // Turn off the LED
  delay(1000);            // Wait for 1 second
}
````
#### Analog Output
To send *analog* output to a *GPIO*, use `analogWrite()` instead of `digitalWrite()`.

> [!IMPORTANT]
> Most *GPIOs* cannot output *analog voltages*: this requires the *GPIO* to be internally routed to a *DAC* (*Digital-Analog-Converter*). Some microcontrollers do not even contain a *DAC*. *Analog output* capabilities are among the least used and the least commonly supported.



#### Digital Input: Button Press
Here is an example using a *GPIO* as an input that can be connected to a momentary switch in order to let a user invoke some action:

````c++
void setup() {
  pinMode(4, INPUT); // Set digital pin 4 as an input
}

void loop() {
  int buttonState = digitalRead(4); // Read the state of the button connected to pin 4
  if (buttonState == HIGH) {
    // Do something when the button is pressed
  }
}

````

#### Analog Input

To read *analog* input, use `analogRead()` instead of `digitalRead()`.

> [!IMPORTANT]
> Not every *GPIO* can read *analog input* (*analog voltage ranges*): this requires the *GPIO* to be internally routed to a *ADC* (*Analog-Digital-Converter*). 
Modern microcontrollers support this for almost all *GPIOs* whereas older microcontrollers provide distinct "analog" *GPIOs* which are labeled **A***x*.

````c++
void setup() {
  // // No need to set pinMode() for inputs, but you can for clarity
  pinMode(A0, INPUT);
}

void loop() {
  int sensorValue = analogRead(A0); // Read the value from analog pin A0
  // Do something with the sensor value
}
````



> [!IMPORTANT]
> Older microcontrollers like *ATMega* expose dedicated *analog input GPIOs* (typically labeled **A***x* on the boards) that do not support any other mode. That's why for such pins, no `pinMode()` needs to be set. Any truly *general purpose GPIO* that supports multiple modes **must be explicitly set** to either *input* or *output* mode using `pinMode()`.

## Pull-Up/Pull-Down Resistors
Whenever a *GPIO* is used as **input**, the *GPIO* can have a *floating* (or *random*/*indetermine*) state:

* **Determined State:** When you connect a push button to a *GPIO*, and the user now presses the push button, all is good: the button connects the *GPIO* to whatever you wired it to, most typically either *VCC* (*high*) or *GND* (*low*). 
* **Indetermined/Floating State:** When the user is **not pressing** the button, the *GPIO* is **not connected to anything**, and its state is *floating*: it can now have a *random value*, either *high* or *low*.

### Pulling Up Or Down
The solution is to set the *GPIO* to a *defined state* when it is not connected. For this, a *high impedance resistor* connects the *GPIO* to either *high* (*VCC*) or *low* (*GND*), providing it with a *default value*.

Since the resistor has a *high impedance*, it can be *over-ruled* by any other signal, i.e. when the user presses the button and connects the *GPIO* to *VCC* or *GND* **directly** (without a high-impedance resistor).

* **Pull-Up Resistor:** *GPIO* gets a *high* value by default. A high-impedance resistor connects the *GPIO* to *VCC* so it is *high* unless you connect it to *GND*.
* **Pull-Down Resistor:** This works the other way around: connects the *GPIO* to *GND* via a high-impedance resistor. The *GPIO* is now *low* by default. Only when you connect it to *VCC* will it change to *high*.

In modern microcontrollers, *GPIOs* come with *built-in pullup- and pulldown-resistors* that can be enabled by code. *ESP32 microcontrollers* for example use internal *45kOhm* resistors.

#### Pull-Up (active low)

This code assumes that the push button is connected to *GND*. When the push button is **not pressed**, the *GPIO* has a defined *high* state. When the button is pressed, it connects the *GPIO* to *GND* and goes *low*. The *high impedance* of the pull-up resistor prevents a short-circuit:

````c++
void setup() {
  pinMode(4, INPUT_PULLUP); // Set digital pin 4 as an input with internal pull-up resistor
}

void loop() {
  int buttonState = digitalRead(4); // Read the state of the button
  if (buttonState == LOW) {
    // Do something when the button is pressed
  }
}

````

The *GPIO* is said to be *active low:* when it is considered to be *active* (the user is pressing the button), the *GPIO* is *low*.

#### Pull-Down (active high)

If you'd rather like to connect the push button to *VCC* (positive voltage), you need a *pull-down resistor* instead that ensures that the *GPIO* by default is *low*, and only switches to *high* when the push button is pressed and connecting the *GPIO* to *VCC*:


````c++
void setup() {
  pinMode(4, INPUT_PULLDOWN); // Set digital pin 4 as an input with internal pull-down resistor
}

void loop() {
  int buttonState = digitalRead(4); // Read the state of the button
  if (buttonState == HIGH) {
    // Do something when the button is pressed
  }
}

````

#### External Resistors
Built-in *pull-up* and *pull-down* resistors may not be available for every *GPIO* (visit your microcontroller datasheet). In this case, simply add an external resistor (*10-100kOhm*) to the *GPIO*, and connect it to *GND* (*pull-down*) or *VCC* (*pull-up*).



## Source And Sink
When a *GPIO* operates in *digital output* mode, it can *source* and *sink* current. These terms descibe the *direction* of current flow.

### Sourcing Current (high active)
The most common type is *sourcing* current: to power a *load*, the *GPIO* is set to *high*, and the load is connected to *GND*. That is why this circuitry is called ***high** active*.


### Sinking Current (low active)
A lesser known but flexible alternative is to *sink* current: to power a *load*, the *GPIO* is set to *low*, and the load is connected to *VCC* (or *any other voltage source*). That is why this circuitry is called ***low** active*.

In this case, the *GPIO* acts as *GND* (when *low*), and *sinks any voltage* that you supply to it.

> [!TIP]
> With *sinking*, you are free to use any *voltage supply* at hand (provided it shares *GND* with the microcontroller). For example, you could power a *5V LED* directly from the power supply, and connect it to the *low active GPIO* of a *3.3V ESP32*. Even though *ESP32 datasheets* state otherwise, users all over the world successfully interface *ESP32 GPIOs* directly with *5V components* and use *sinking* with up to *5V*.  *ESP32 GPIOs* seem to be *5V tolerant*. Exceeding official datasheet specifications is entirely *at your own risk*, though.

### Sourcing And Sinking
Here is a great example illustrating how flexible *sinking* can be: a *digital output GPIO* needs a way for users to know whether the output is *on* or *off*. For this, two *LED* (one *green*, one *red*) should light up, depending on *GPIO state*.

Here is a very simple solution that uses *two LED*:

<img src="images/source_sink_led_schematics.png" width="100%" height="100%" />

* **Sinking (green):** the *green* LED is connected in *sinking* configuration: when the *GPIO* is *low*, it is connected to *GND*. The other end of the *LED* is connected to *VCC*. 
* **Sourcing (red):** the *red* LED is connected in *sourcing* configuration: when the *GPIO* is *high*, it provides *VCC*, and the other end of the *LED* is connected to *GND*.

This way, when the *GPIO* is *high*, the *red LED* is *on*, and when *GPIO* is *low*, the *green LED* is *on*.

> [!IMPORTANT]
> This example works great with *3.3V microcontrollers* but may destroy the *LED* with *5V microcontrollers*. Here is why: one *LED* is always operated in "wrong direction", and the *reverse breakdown voltage* for *LED* typically is around *5V*. When this voltage is exceeded, the *LED* gets damaged irreversibly. For *5V* systems, you would need to add a protective diode in parallel to the *LED*.


## Absolute Limits
*GPIOs* are sensitive and need to be used strictly within their specifications.

* **Current:** in **output** mode, the maximum current for *ESP8266* is *12mA*, and for *ESP32* (depending on *GPIO*) either *20mA* or *40mA*. Other microcontrollers may vary, however their maximum current is in the same region. This makes clear that *GPIO* **cannot directly drive high loads** like *mechanical relais*, *power LED*, or *motors*. Use a MosFet for this.
* **Voltage:** in **digital input** mode, the maximum input value is *VCC*. A *3.3V ESP32 GPIO* should not be directly connected to a *5V component*. Use a *level shifter*, or at least add a current-limiting resistor. That said, there are sources claiming that *ESP32 GPIOs* are *5V tolerant*, and users around the world connect *5V components* directly to *ESP32 GPIO* without issues.
* **Analog Voltages:** with **analog input**, the maximum voltage depends on the internal *ADC*. Some board designers add *voltage dividers* that further influence the maximum analog input voltage. Exceeding this limit almost certainly immediately destroys the *ADC*.


| Board | Analog Input Max Voltage |
| --- | --- |
| Arduino | 5V |
| ESP8266 | 1V |
| ESP32 | 3.3V |
| STM32 | 3.3V |
| RP2040 | 3.3V |


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

[Visit Page on Website](https://done.land/components/microcontroller/gpio?634161081204241838) - created 2024-08-03 - last edited 2024-08-03
