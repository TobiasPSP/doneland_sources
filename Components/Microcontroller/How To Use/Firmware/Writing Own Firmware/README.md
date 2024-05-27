<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Writing Own Firmware

> Programming New Firmware Requires Just Mild Programming Skills Thanks To Great IDEs and Libraries


One of the *most flexible and powerful* ways is to *write the firmware for your microcontroller yourself*. 

This way, *you can access all microcontroller features*, and tailor the firmware exactly to your needs. You can also *skip any functionality* you do not need, and *optimize* your code in regards to *speed*, *energy consumption*, or *user interaction*. You are in *full control*.

You do need to program yourself, though. That's the downside. But thanks to excellent *IDEs*, *awesome software libraries*, and a wealth of *example code*, that's not so hard after all.


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

[Visit Page on Website](https://done.land/components/microcontroller/howtouse/firmware/writingownfirmware?421947051527240132) - created 2024-05-14 - last edited 2024-05-26
