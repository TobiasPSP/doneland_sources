<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Preparing Sample Sketch

> How To Create A Test Sketch For A New Development Board

Once you have made sure that a new *development board* connects to your computer and gets a *COM port* assigned, the next step is to create *firmware* for your microcontroller.

*Firmware* is the *software* that runs *directly* on a microcontroller.

## Firmware
Firmware is a *software* that is executed *directly* by the microcontroller. It is basically the software layer that directly interacts with the microcontroller.

There are *two* general types of firmware: *specific* firmware that directly tells the microcontroller what to do, and *interpreter firmware* that *translates a high-level* programming language into machine code. In the latter case, the *firmware* by itself **does not** perform any tasks and requires additinal *scripts* or *user inputs* to actually do something.

> [!CAUTION]
> Since *firmware* is directly interacting with a *microcontroller*, it is **always** targeting a *specific microcontroller and board*. When you program *firmware* yourself, you specify the target microcontroller and board. When you *download and use pre-made (pre-compiled) firmware*, it **must have been made** exactly for **your microcontroller and board**.




### Directly Controlling Hardware
The firmware is directly *taking care of* what you want the microcontroller to do. This is the most common type of firmware found in *DIY projects*: 

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

As you see, there are different *firmware versions*, targeting *ESP32* microcontrollers with different *displays* attached to them.

> [!CAUTION]
> Only *source code* is *hardware neutral*. Once it gets *compiled into a binary* by a *IDE*, it is converted into a *hardware-specific firmware*. This *firmware* can only be used on the particular hardware (microcontroller board) that was specified during compile time. When you take the shortcut and directly upload *pre-fabricated firmware*, you must be certain that it was indeed made for *your particular microcontroller and board*. Else, the firmware will not run (correctly).


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

There are two popular and free  * generic IDEs*:

* [Arduino IDE](https://www.arduino.cc/en/software): This *IDE* was originally created to make programming *Arduino* microcontroller boards a breeze, and it is definitely *simple to use*. Today, it can be easily extended to also support microcontrollers and boards from other vendors (i.e. *ESP8266*, *ESP32*, *ATtiny*, etc.)
* [PlatformIO](https://platformio.org/): This *IDE* is a *plugin* for the free cross-platform *Microsoft* text editor *VSCode*. As a *tool targeting professionals*, it is not just as *simple* to set up and may take an hour to get acquainted. Due to the underlying *feature-rich VSCode editor*, it is *much more capable* than *ArduinoIDE*, and once your code becomes a bit more complex, its *IntelliSense*, *Code Lens*, and many other tools and services ensure that it stays well manageable. *ArduinoIDE* in contrast is great only with *short code* and *very hard to use* once you start working with source code inside of *libraries*.


## Creating Own Firmware
Firmware is written in the programming language *C++* which is considered to be *difficult to use*. However that is not true when it comes to programming *microcontroller firmware*. Here is why:

### Frameworks 

With *IDEs* like *Arduino IDE* and *platformio*, you are not really programming a *firmware* all on your own in *pure C++*. Instead, you are taking advantage of a *Framework* that takes care of most of the hard work *transparently in the background* so you can focus on the *genuine* things you want your code to do.

#### Simple C++ Using A Framework

The *IDE* takes your code and *merges it* with a huge *predefined* set of *libraries* that in turn contain thousands of methods (commands) for your convenience. 

If you for example wanted to turn on or off the built-in *LED* on your development board, you do not have to code complex bitwise register shifts, and in fact you do not even need to know the exact *pin number* the internal *LED* is attached to.

Instead, you simply use one of the framework generic methods to control a *GPIO* pin, and you use one of the framework predefined *constants* to access exactly the pin that controls the internal *LED* on your particular board: 

````c++
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);
````

#### Hard C++ Programming Without A Framework

If you would not have the help of a *Framework* and had to rely solely on *C++*, you would have to use code like this to turn the LED on: 

````c++
DDRB |= _BV(DDB5);  // Set the corresponding bit in the DDR register to 1 to set Pin 13 to output mode
PORTB |= _BV(PB5);  // Set pin 13 high using bitwise OR with the bitmask for pin 13
````

Obviously, such code would be beyond the scope of *hobbyists*, and worse yet, the code would *only* work on an *Atmel AVR microcontroller* (i.e. one of the original *Arduinos*), and only when the internal LED is connected to *Pin 13*. On *ESP32* microcontrollers, the code would need to be completely different:

````c++
REG_WRITE(GPIO_ENABLE_W1TS_REG, 1 << 2); // Set bit 2 in GPIO_ENABLE_W1TS_REG to enable output mode
REG_WRITE(GPIO_OUT_REG, REG_READ(GPIO_OUT_REG) | (1 << 2)); // // Set bit 2 in GPIO_OUT_W1TS_REG to turn on the LED
````

Thanks to frameworks like *Arduino Framework*, code today is simple to understand and as *hardware neutral* as possible. This allowed the *community* to create code that targets a wide variety of microcontrollers and enables you to use code examples that originally might have been written for a completely different microcontroller.


> [!NOTE]
> These examples may illustrate *why* it was such a *game changer* when *Arduino IDE* introduced the *Arduino Framework* in the early *2000s*: suddenly, *hobbyists* and *non-programmers* could develop *firmware* for embedded systems.


## Arduino Framework
*Arduino Framework* is the most popular Framework for *hobbyists*. Here are some of the reasons:

* **Examples:** Since it has been around the longest time, there are the most *examples* available.
* **Hardware Neutral:** It targets a wide variety of microcontrollers and is not limited to a particular vendor
* **Simple to use:** Its *abstraction level* is high. It provides a very easy *coding environment*.

### Adding Platform Support
Today, it is easy to add support for almost *any* microcontroller family by adding appropriate *board packages* to *Arduino IDE*.


Out of the box, *Arduino IDE* comes with support for *Arduino boards* (and its *clones*).

#### ESP8266 and ESP32
To target the *ESP32* and/or *ESP8266* family of microprocessors, add the appropriate *board managers* like so:

1. Choose *File*/*Preferences*. In the text box *Additional Boards Manager URLs, add this: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json`, then click *OK*.


<img src="images/arduinoide_url.png" width="100%" height="100%" />

2. Go to *Tools*/*Board*/*Boards Manager*. In the search box at the top of the dialog window, enter *ESP32*. In the results list, choose *ESP32* by *Espressif*, and click *Install*. A 260MB download starts and can take a few minutes.

<img src="images/arduinoide_esp32.png" width="100%" height="100%" />

3. To add support for *ESP8266*, enter *ESP8266* into the textbox. In the results list, choose *ESP8266* by *ESP8266 Community*, and click *Install*. Once the new board managers are installed, click *Close*.

When you now open *Tools*/*Board*, there are two new submenus: *ESP32 Arduino* and *ESP8266 Boards*.

To add support for additional microcontroller families, follow the same scheme. 

#### ATtiny

To add support for *ATTiny* microcontrollers, add the additional *board manager url* `https://raw.githubusercontent.com/sleemanj/optiboot/master/dists/package_gogo_diy_attiny_index.json` (use *commas* to separate more than one url in the textbox).

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
*ESP-IDF* is a framework created by the Chinese company *Espressif* to specifically target its line of *ESP32* microcontrollers. You can only use it if you intend to target *ESP32* microcontrollers, and if you are using an *IDE* that supports switching frameworks.

*Arduino IDE* can *only* work with *Arduino Framework*. *platformio* in contrast lets you use whatever framework you want. On *platformio*, when you create a new project, you can choose which framework you would like to use.

### Why Different Frameworks?
Keep in mind what a *framework* is supposed to do: it is supposed to *handle all hardware specific* things so *you* and your code can focus on the genuine things that you want the code to do.

The more you *abstract* things, the *easier* things get, and *ease of use* is one of the highest priorities in the *Arduino ecosystem*. On the downside, the more you *abstract*, the less control do you have. 

*Arduino Framework* is based on its [ArduinoCore-API](https://github.com/arduino/ArduinoCore-API) platform template, and all *Platform Packages* must derive from it. That's cool because it ensures maximum compatibility. But it is not so cool if you are a *highly innovative Chinese manufacturer* who keeps adding awesome new features by the month.

That's why *Espressif* decided to take its *Platform support* in *own hands*: Its framework *ESP-IDF* does not rely on *Arduinos update cycles* or *template restrictions*. It always provides the best platform support with the latest and greatest features and microcontrollers, but *only for ESP32* microcontrollers (and its newer versions).

To also support all *Arduino IDE users* and maintain compatibility with the vast number of *code examples* written in *Arduino Framework*, the company also maintains a *Arduino Platform Package* called [arduino-esp32](https://github.com/espressif/arduino-esp32) which internally is based on *ESP-IDF*.

### Arduino Core Lags Behind
The added *hardware abstraction layer* that you get with *arduino-esp32* in the *Arduino Framework* is great most of the time. However it takes additional time to maintain and update this abstraction layer whenever *ESP-IDF* changes. It always *lags behind* a bit.

The latest *Espressif Framework* is *ESP-IDF v5*. It introduced a great number of exciting new features, and it supports new microcontrollers like the *C6* and *H2*.

As of this writing, the current [arduino-esp32](https://github.com/espressif/arduino-esp32/releases/tag/2.0.17) release is based on *ESP-IDF v4*. It still misses out on many new features that are already available in the *ESP-IDF Framework*. 

That said, even though the *Arduino Platform Package* always lags behind a bit, it is just a matter of time until it catches up. [arduino-esp32 v3](https://github.com/espressif/arduino-esp32/releases/tag/3.0.0-rc3) is based on the latest *ESP-IDF v5.1* Framework. This new *Arduino Platform Package* is already in *release candidate* status and will soon be released.



## Comparing Frameworks
As pointed out, both *Arduino Framework* and *ESP-IDF* come with extensive libraries full of methods (commands) that help you keep your code simple, and focus on your genuine goals.

Obviously, *ESP-IDF* is only an option if you target *ESP32* microcontrollers. If you want to program a *different* microcontroller family, or if you want to share your code with a *maximum audience*, then *Arduino Framework* is your only choice. The same is true if you insist on using *Arduino IDE*: it only supports its own *Arduino Framework*.

But even if you do target *ESP32* microcontrollers and are using a modern *IDE* like *platformio*, you should still carefully consider the framework to choose:

* **Simplicity:** the *Arduino Framework* prioritizes *ease of use*, and its implementation of the *C++* programming language feels *easier* for many users. 
* **ESP32 Examples:** if you are interested in the latest and greatest features found in new *ESP32* microcontrollers, then you need good *example code*. Often, *Espressif* tutorials and examples are the only source, and they use their own *ESP-IDF* framework.


### Language Differences
For the reasons mentioned a couple of times, code written in *one* framework is not compatible to a *different* framework. To highlight some of the differences, let's take a look at the famous *blink* sketch that lets a *LED* blink.

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

In *Arduino Framework*, the two methods `setup()` and `loop()` must always be present. They are used to easily organize your code: `setup()` gets executed *once* and can i.e. initialize things, for example *open the serial connection*.  `loop()` runs endlessly to perform the actual job.


#### ESP-IDF

The same functionality looks differently when written in the *Espressif* framework:

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

Both frameworks abstract the *GPIO access*, however they are using different *methods* (commands) for it. *ESP-IDF* does not use constructions like `setup()` and `loop()`. Instead, the code uses an *endless **while** loop*.

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

[Visit Page on Website](https://done.land/components/microcontroller/programming/preparingsamplesketch?297809051621241735) - created 2024-05-20 - last edited 2024-05-24
