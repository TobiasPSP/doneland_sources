<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Preparing Sample Sketch

> How To Create A Test Sketch For A New Development Board

*Firmware* is the *software* that runs *directly* on a microcontroller. It is needed to tell the microcontroller what to do.

## Firmware
There are *two* general types of firmware: *specific* firmware that directly tells the microcontroller what to do, and *interpreter firmware* that *translates a high-level* programming language into machine code. In the latter case, the *firmware* by itself **does not** perform any tasks and requires additinal *scripts* or *user inputs* to actually do something.

> [!CAUTION]
> Since *firmware* is directly interacting with a *microcontroller*, it is **always** targeting a *specific microcontroller and board*. When you program *firmware* yourself, you specify the target microcontroller and board. When you *download and use pre-made (pre-compiled) firmware*, it **must have been made** exactly for **your microcontroller and board**.




### Directly Controlling Hardware
The firmware is directly *implementing the actions* that you want the microcontroller to do for you. This is the most common type of firmware found in *DIY projects*: 

You write specific firmware i.e. to read sensor data and display it, control *LED strips* or open a *relais* when a *WiFi command* is sent. Once uploaded to a microcontroller, it will do just that - until you decide to upload a different firmware.

Since the *firmware* is running directly on the *microcontroller* without any other layers or bottlenecks inbetween, even small microcontrollers can reach enormous performances.


<details><summary>Using Ready-Made Firmware</summary><br/>

This section is about *programming your own firmware*, but you can also use ready made firmware that someone else prepared. In this case, you can skip the remainder of this article.

[WLED](https://kno.wled.ge/) for example is an *open source* project for controlling *LED Strips*. You can get ready-to-go firmware for *ESP8266* and *ESP32* microcontrollers.

All you need to do is [wire up](https://kno.wled.ge/basics/getting-started/) the *LED Strip* to the microcontroller.

Next, *upload the firmware* (software) to the microcontroller. This can be done [right from within your browser](https://install.wled.me/).

There are plenty of *awesome open source projects* like this one. [CO2 Gadget](https://emariete.com/en/co2-meter-gadget/) is another one that turns a *CO2 sensor* into a *smartphone app*. It runs on any *ESP32* microcontroller, and it comes with a web browser-based *firmware flashing tool*.

The hardest part often is finding the correct links: the [authors' web page](https://emariete.com/en/co2-meter-gadget/) is huge and not structured well. Links to the browser-based firmware uploads can be found somewhere in the middle of it.





<img src="images/co2meter.png" width="100%" height="100%" />

There are different *firmware versions*, targeting *ESP32* microcontrollers with different *displays* attached to them.

> [!CAUTION]
> *Source code* is *hardware neutral*. Once it gets *compiled into a binary* by an *IDE*, it is converted into a *hardware-specific* firmware. This *firmware* can now only be used on the particular hardware (microcontroller board) that was specified during compile time. When you take the shortcut and directly upload *pre-fabricated firmware*, you must be certain that it was indeed made for *your particular microcontroller and board*. Else, the firmware will not run (correctly).


#### Home Automation
While the mentioned examples above handle *very specific* use cases, there is also somewhat generic *pre-made firmware*. [ESPEasy](https://github.com/letscontrolit/ESPEasy) for example is tailored towards *ESP32* microcontrollers, supports a [wide range of sensors and components](https://letscontrolit.com/wiki/index.php?title=Devices) and adds all the default code that is typically required to *remote control* a hardware device or integrate it into home automation frameworks like *ioBroker*, *openHAB*, *Domoticz*, *FHEM*.

So in a nutshell, *ESPEasy* is an example for a firmware that can be easily *customized* via a *web frontend*. In the next section, you learn about *Firmware Interpreters* which take the idea of *customizing* the firmware through user input a step further: *Interpreters* accept generic *scripts* and *user input* to do whatever you want with the hardware.


</details>


### Interpreters
In the case of *Interpreters*, the firmware is *not doing anything specific*. Instead, it waits for commands (typically *scripts* or *interactive user commands*) in a *higher level programming language*. 

This way, users do not have to write programs in *C++* to control hardware. Instead, they use *easier* programming languages that are *interpreted* by the firmware and *translated* into the machine commands that a microcontroller can understand. 

While programming is much easier, *interpreters* add overhead which degrades performance. This is why *interpreters* require more performat microcontrollers (like *ESP32*).

Here are the *Interpreter firmware* advantages:

* **Versatile:** Since the user can easily change commands or scripts, the microcontroller can do all kinds of things without the need of creating and uploading firmware each time.
* **Easy:** Interpreters support different *high level* programming languages like *LUA*, *Python*, *Basic*, *JavaScript*, etc. These languages feel more natural to *non-programmers*.

And here is the price you pay:

* **Overhead:** Interpreters add *computational effort* and introduce *bottlenecks*. That's why they need (much) more *RAM* and more performant microcontrollers. 
* **Energy:** Since the *microcontroller* has more work to do, *interpreters* increase the power consumption which can be prohobitive in battery-driven devices.

> [!TIP]
> *Interpreter firmware* can be great in *educational* scenarios where you can easily reprogram the microcontroller to cater different needs, and if you just can't wrap your head around the *C++* programming language that is required to write *firmware*. If however you want a microcontroller to run the *same code all the time* (i.e. inside a device you created), then do avoid *Interpreter firmware* and instead build your own *firmware* directly.

### Interpreter Languages
Free pre-compiled and ready-to-use *Interpreter firmware* is available for many *high level programming languages*:


#### LUA
* [Lua (eLUA)](https://eluaproject.net/overview/status/) *Embedded Lua* is a lightweight implementation of the *Lua* programming language for embedded systems.
* [NodeMCU](https://github.com/nodemcu/nodemcu-firmware) *NodeMCU* is a project that develops *ESP8266*- and *ESP32*-based *microcontroller boards* bundled with an adaption of *eLUA* that is guaranteed to match the hardware. The preinstalled (bundled) firmware can easily be replaced with any other firmware, including individual firmware written by yourself, if you are interested in the *hardware board* but not in *LUA*.


#### Python
* [MicroPython](https://github.com/micropython/micropython/): The *MicroPython* firmware can execute scripts written in *Python 3* and also supports *interactive console operation* (*REPL*, *read-eval-print loop*). It includes a small subset of the Python standard library and is optimized to run on microcontrollers with limited resources (RAM and storage).
* [CircuitPython](https://learn.adafruit.com/circuitpython-with-esp32-quick-start/installing-circuitpython): a derivative of *MicroPython*, designed by the company *Adafruit* to make learning and using Python on microcontrollers simpler. It focuses on ease of use and education.

#### JavaScript
* [Espruino](https://www.espruino.com/Download): *JavaScript* interpreter for microcontrollers to develop embedded applications using JavaScript with an interactive JavaScript environment.
* [JerryScript](https://github.com/nkolban/jerryscript-esp32) lightweight JavaScript engine intended for microcontrollers with constrained resources. It features a very low memory usage and can run on microcontrollers with less than 64KB of RAM. It supports a subset of the ES5.1 standard.

#### BASIC
* [ESPBasic](https://www.esp8266basic.com/): BASIC for ESP8266 microcontrollers. Allows easy and wireless programming.
* [TinyBASIC](https://github.com/slviajero/tinybasic): minimalistic version of the BASIC programming language designed for resource-constrained systems. 


#### Others
* [Squirrel](https://github.com/EternityForest/Acorns): high-level scripting language, somewhat inspired by Lua, designed to be lightweight and embeddable, with object-oriented approach.
* [TinyGo](https://tinygo.org/): *Go* compiler translating *Go* code into machine code that can run on microcontrollers.
* [WASM3](https://github.com/wasm3/wasm3) *WebAssembly* interpreter designed for small devices and microcontrollers that can run WebAssembly bytecode on microcontrollers.



## Development Environment
To create new *firmware*, you need a tool that lets you *write the code* and that can *compile the code* into the *binary firmware* that a microcontroller needs. Such a tool is called *IDE* (*Integrated Development Environment*).

There are two popular and free *generic IDEs*:

* [Arduino IDE](https://www.arduino.cc/en/software): originally created to program *Arduino* microcontroller boards that meanwhile can be easily extended to support microcontrollers and boards from other vendors, too (i.e. *ESP8266*, *ESP32*, *ATtiny*, etc.)
* [PlatformIO](https://platformio.org/): *plugin* for the free cross-platform *Microsoft* text editor *VSCode*. Due to the underlying *feature-rich VSCode editor*, it provides a *much more capable* editing experience, especially when code becomes more complex. 


## Creating Own Firmware
Firmware is written in the programming language *C++* which is considered to be *difficult to program*. However that is not true when it comes to programming *microcontroller firmware*. Here is why:

### Frameworks 

With *IDEs* like *Arduino IDE* and *platformio*, you are not really programming a *firmware* all on your own in *pure C++*. Instead, you are assisted by *Frameworks* that take care of most of the difficult technical aspects so you and your code can focus on the *genuine* things you want your code to do.

#### Frameworks Simplify C++
Thanks to *Frameworks*, you don't need to code the hardware directly. Instead, the *Framework* provides you with *simple-to-use* commands that internally take care of the difficult things.

If you for example wanted to turn on or off the built-in *LED* on your development board, you do not have to code complex bitwise register shifts, and in fact you do not even need to know the exact *pin number* the internal *LED* is attached to:


````c++
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);
````

The code uses one of the frameworks generic methods to control a *GPIO* pin. It uses one of the framework predefined *constants* to access exactly the pin that controls the internal *LED* on your particular board. 

#### Hard C++ Programming Without A Framework

Without the help of a *Framework*, you would have to use hardware-specific code like this to turn the LED on: 

````c++
DDRB |= _BV(DDB5);  // Set the corresponding bit in the DDR register to 1 to set Pin 13 to output mode
PORTB |= _BV(PB5);  // Set pin 13 high using bitwise OR with the bitmask for pin 13
````

Obviously, such code is beyond the scope of *hobbyists*, and worse yet, the code would *only* work on an *Atmel AVR microcontroller* (i.e. one of the original *Arduinos*), and only when the internal LED is connected to *Pin 13*. On i.e. *ESP32* microcontrollers, the code would look completely different:

````c++
REG_WRITE(GPIO_ENABLE_W1TS_REG, 1 << 2); // Set bit 2 in GPIO_ENABLE_W1TS_REG to enable output mode
REG_WRITE(GPIO_OUT_REG, REG_READ(GPIO_OUT_REG) | (1 << 2)); // // Set bit 2 in GPIO_OUT_W1TS_REG to turn on the LED
````

Thanks to Frameworks, code is simple to understand and *hardware neutral*. This allows the *community* to create code that targets a wide variety of microcontrollers and enables you to use code examples that originally might have been written for a completely different microcontroller.


> [!NOTE]
> The code comparison lets you appreciate why it was such a *game changer* when *Arduino IDE* introduced the *Arduino Framework* in the early *2000s*: suddenly, even *hobbyists* and *non-programmers* were able create *firmware* for microcontrollers.


## Arduino Framework
*Arduino Framework* is the most popular Framework for *hobbyists*:

* **Examples:** Since it has been around the longest time, there are the most *examples* available.
* **Hardware Neutral:** It targets a wide variety of microcontrollers and is not limited to a particular vendor
* **Simple to use:** Its *abstraction level* is high. It provides a very easy *coding environment*. 

### Adding Platform Support
Out of the box, *Arduino IDE* comes with support for *Arduino boards* (and its *clones*) only, but it takes just a few clicks to add *Platform Support* for almost any other microcontroller:

#### ESP8266 and ESP32
To add support for *ESP32* and/or *ESP8266* microprocessors, add the appropriate *board managers* like so:

1. Choose *File*/*Preferences*. In the text box *Additional Boards Manager URLs, add this: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json`, then click *OK*.


<img src="images/arduinoide_url.png" width="100%" height="100%" />

2. Go to *Tools*/*Board*/*Boards Manager*. In the search box at the top of the dialog window, enter *ESP32*. In the results list, choose *ESP32* by *Espressif*, and click *Install*. A 260MB download starts and can take a few minutes.

<img src="images/arduinoide_esp32.png" width="100%" height="100%" />

3. To add support for *ESP8266*, enter *ESP8266* into the textbox. In the results list, choose *ESP8266* by *ESP8266 Community*, and click *Install*. Once the new board managers are installed, click *Close*.

When you now open *Tools*/*Board*, there are two new submenus: *ESP32 Arduino* and *ESP8266 Boards*.

To add support for additional microcontroller families, follow the same scheme. 

#### ATtiny

To add support for *ATtiny* microcontrollers, add the additional *board manager url* `https://raw.githubusercontent.com/sleemanj/optiboot/master/dists/package_gogo_diy_attiny_index.json` (use *commas* to separate more than one url in the textbox).

Next, go to *Tools*/*Board*/*Boards Manager* once more, and search for *attiny*. Click *Install*.

<img src="images/arduinoide_esp32.png" width="100%" height="100%" />


Once this board manager is installed, you find another new submenu named *DIY ATtiny*.


<img src="images/arduinoide_attiny_list.png" width="100%" height="100%" />





<details><summary>How Platform Packages and Arduinos "Board Manager" Really Work</summary><br/>


*Arduino Framework* was originally developed for the *Arduino IDE*, and it is still *the only* framework that can be used in *Arduino IDE*. The framework itself is *separate*, though, and also used by other *IDEs* like *platformio*.

### Arduino Core - Platform Packages
When *Arduino IDE* surfaced many years ago, it was targeting only [Atmel](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/avr-mcus) microcontrollers:the microcontrollers used on *Arduino boards*. 

*Atmel* microcontrollers are *8-bit*, and soon enough the market demanded *faster* and *better* microcontrollers. 

To meet this need, *Arduino* decided to separate its *IDE* from the *platform support for specific microcontrollers*. *ArduinoFramework* was the name of this new abstraction layer. 

*Arduino Framework* uses a *hardware neutral* template called [ArduinoCore-API](https://github.com/arduino/ArduinoCore-API): it defines the API (all the required commands), constants, and tool chain needed to work with *any* microcontroller, however without adding any specific implementation.

[ArduinoCore-avr](https://github.com/arduino/ArduinoCore-avr) was the first *Platform Package* derived from this template and contained all the *hardware specific* implementations to make the API work on *AVR* microcontrollers.

[ArduinoCore-samd](https://github.com/arduino/ArduinoCore-samd) added support for *Atmel SAMD21* on boards like *Arduino/Genuino Zero*, *MKR1000*, and *MKRZero*.

Starting with version 1.6.4, *Arduino IDE* officially began to support *platform packages* from any third party which was welcomed by *users* and *companies* likewise:

* [ArduinoEsp8266](https://github.com/esp8266/Arduino): The community quickly added support for the extremely popular, cheap, and powerful *ESP8266* microcontroller (manufactured by the Chinese company *Espressif*). 
* [arduino-esp32](https://github.com/espressif/arduino-esp32): *Espressif* officially started to support their excellent line of *ESP32* microcontrollers on *Arduino IDE*.

All *Platform Packages* that you add through *Arduinos Board Manager* are stored here: *C:\Users\\[USERNAME]\AppData\Local\Arduino15\packages*.


</details>

## ESP-IDF (Espressif IoT Development Framework)
*ESP-IDF* is a framework created by the Chinese company *Espressif* to specifically target its line of *ESP32* microcontrollers. 

### Why Different Frameworks?
The more you *abstract* things, the *easier* they get, and *ease of use* is one of the highest priorities in the *Arduino ecosystem*. On the downside, the more you *abstract*, the more *control* you give up. 

*Arduino Framework* is based on its [ArduinoCore-API](https://github.com/arduino/ArduinoCore-API) platform template, and all *Platform Packages* must derive from it. That's a great idea because it ensures maximum compatibility across different microcontroller platforms. But it is also *limiting* if you are a *highly innovative Chinese manufacturer* who keeps adding awesome features by the month.

That's why *Espressif* decided to take its *Platform support* in *own hands*: Its framework *ESP-IDF* does not rely on *Arduinos update cycles* or *template restrictions*. It always provides the best and most specific platform support with the latest and greatest features and microcontrollers found in the *ESP32* ecosystem. You get much more options at the expense of giving up compatibiity to other microcontrollers.

To still support all *Arduino IDE users* and maintain compatibility with the vast number of *code examples* written in *Arduino Framework*, *Espressif* also maintains an *Arduino Platform Package* called [arduino-esp32](https://github.com/espressif/arduino-esp32). Internally, it is based on *ESP-IDF*.

### Arduino Core Lags Behind
This added *hardware abstraction layer* that you get with *arduino-esp32* inside the *Arduino Framework* takes time to maintain. Whenever *ESP-IDF* changes, *arduino-esp32* takes half a year or so until it catches up. 

The latest *Espressif Framework* is *ESP-IDF v5*. It introduced a great number of exciting new features, including supports for the latest *Espressif* microcontrollers (like the *C6* and *H2*).

As of this writing, the current [arduino-esp32 v2](https://github.com/espressif/arduino-esp32/releases/tag/2.0.17) release is still based on *ESP-IDF v4*. It still misses out on new features that already landed in the *ESP-IDF Framework*. 

Even though the *Arduino Platform Package* always lags behind a bit, it is just a matter of time until it eventually catches up. [arduino-esp32 v3](https://github.com/espressif/arduino-esp32/releases/tag/3.0.0-rc3) is based on the latest *ESP-IDF v5.1* Framework. This new *Arduino Platform Package* is already in *release candidate* status and will soon be released.



## Comparing Frameworks
Both *Arduino Framework* and *ESP-IDF* come with extensive libraries full of methods (commands) that help you keep your code simple, and focus on your genuine goals.

Obviously, *ESP-IDF* is only an option if you target *ESP32* microcontrollers. If you want to program a *different* microcontroller family, or if you want to share your code with a *maximum audience*, then *Arduino Framework* is for you. The same is true if you *must use* *Arduino IDE*: it only supports its own *Arduino Framework*.

But even if you do target *ESP32* microcontrollers and are using a modern *IDE* like *platformio* that lets you choose the Framework, you should still carefully consider the pros and cons:

* **Simplicity:** the *Arduino Framework* prioritizes *ease of use*, and its implementation of the *C++* programming language feels *easier* to many users. 
* **ESP32 Examples:** if you are interested in the latest and greatest features in the *ESP32* ecosystem, then you need good *example code*. Often, *Espressif* tutorials and examples are your only source, and they all use their own *ESP-IDF* framework.


### Language Differences
Because of their different API, code is not compatible between Frameworks. They all use *C++*, but each Framework has its own set of commands. To highlight some of the differences, let's take a look at the infamous *blink* sketch that lets an *LED* blink.

#### Arduino IDE

This is the code written in *Arduino Framework*:

````c++
void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  delay(1000);
}
````

The two methods `setup()` and `loop()` must always be present. They are used to easily organize the code: `setup()` gets executed *once* and can i.e. initialize things, for example *open the serial connection*.  `loop()` runs endlessly to perform the actual job.


#### ESP-IDF

Here is same functionality written in *Espressif* framework:

````c++
gpio_reset_pin(BLINK_GPIO);
/* Set the GPIO as a push/pull output */
gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
while(1) {
    /* Blink off (output low) */
    printf("Turning off the LED\n");
    gpio_set_level(BLINK_GPIO, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    /* Blink on (output high) */
    printf("Turning on the LED\n");
    gpio_set_level(BLINK_GPIO, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
````
The *code logic* is identical. Both frameworks abstract the *GPIO access*, however they are using different *methods* (commands) for it. 

But there are additional differences: *ESP-IDF* does not use predefined functions like `setup()` and `loop()`. The code simply uses an *endless **while** loop*.

## Uploading Firmware With Arduino IDE
Let's step through the process of uploading the *famous* **blink** sketch to a microcontroller and make its internal LED blink:

````c++
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}
````


Launch *Arduino IDE* and choose *File/New* to open a new *sketch* window. Paste the sketch code from above into this window.

> [!TIP]
> You can also choose *File/Example/01.Basic/Blink* to create the *blink* sketch. One of the *strengths* of *Arduino IDE* is its *ease of use*: the menu *Examples* provides numerous code examples that can easily be loaded into a sketch window.


<img src="images/arduinoide_sketch.png" width="100%" height="100%" />


### Defining Target Board
Now tell *Arduino IDE* the name of the *target board*: 

* **Arduino Board:** If you are using an original *Arduino* microcontroller board (or a *clone*), go to *Tools/Board/Arduino AVR Boards*, and choose the name of the board you are using (i.e. *Arduino Nano*). *Arduino Uno WiFi* and *Arduino Every* can be found in the menu *Arduino megaAVR Boards*.
* **ESP32:** If you'd like to target a *ESP32* board, choose *Tools/Board/Arduino AVR Boards/ESP32 Arduino*, then choose the *ESP32* board you are using, i.e. *Lolin S2 Mini*. If thie menu item *ESP32 Arduino* is missing, read below how to add non-Arduino boards to the menu.

To test these settings, choose *Sketch/Verify/Compile* (or press `CTRL`+`R`) and see whether the sketch compiles without errors.


> Tags: USB, UART, TTL, Connect, Port, COM

[Visit Page on Website](https://done.land/components/microcontroller/programming/preparingsamplesketch?297809051621241735) - created 2024-05-20 - last edited 2024-05-23
