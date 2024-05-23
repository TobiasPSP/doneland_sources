<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Preparing Sample Sketch

> How To Create A Test Sketch For A New Development Board

Once you have made sure that a new *development board* connects to your computer and gets a *COM port* assigned, and once you have set up the *development environment* of your choice (i.e. *Arduino IDE* or *platformio*), the next step is to understand how you can *program* a microcontroller.

## Arduino Framework
There are various *programming languages* and *frameworks* you can use to program *microcontrollers*. 

In this section I am focusing on the universal *Arduino Framework*: its sketches (programs) are written in the language *c++*. *C++* tends to be more *technical* compared to i.e. *MicroPython*, but *c++* is extremely *efficient* and does not waste resources. That's why sketches programmed using the *Arduino Framework* run on most microcontroller families, including the original *Arduinos*, powerful *ESPxxxx*, barebone *ATTinyxx*, and many more.

## Sketch
Here is the *famous* **blink** sketch that uses the *internal IDE* found on most development boards. When this sketch runs, it lets the *LED blink*. That's why this sketch is often used to verify that a microcontroller is fundamentally *ok*, and that the firmware upload was successful.

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

Let's see how this sketch can be uploaded to a variety of different *development boards* and *microcontrollers* using *Arduino IDE* and *platformio*.

> [!NOTE]
> You are about to witness a *miracle*: the sketch will run fine on a wide variety of completely different microcontrollers and development boards. The necessary *adjustments* to target the different *hardware designs* are performed automatically by the *IDE*. Your code is unaffected and remains *hardware-neutral*.  




## Arduino IDE
Launch *Arduino IDE* and choose *File/New* to open a new *sketch* window. Paste the sketch code from above into this window.

> [!TIP]
> You can also choose *File/Example/01.Basic/Blink* to create the *blink* sketch. One of the *strengths* of *Arduino IDE* is its *ease of use*: the menu *Examples* provides numerous code examples that can easily be loaded into a sketch window.


<img src="images/arduinoide_sketch.png" width="100%" height="100%" />


### Defining Target Board
Now tell *Arduino IDE* the name of the *target board*: 

* **Arduino Board:** If you are using an original *Arduino* microcontroller board (or a *clone*), go to *Tools/Board/Arduino AVR Boards*, and choose the name of the board you are using (i.e. *Arduino Nano*). *Arduino Uno WiFi* and *Arduino Every* can be found in the menu *Arduino megaAVR Boards*.
* **ESPxxx:** If you'd like to target a *ESPxxx* board, choose *Tools/Board/Arduino AVR Boards/ESP32 Arduino*, then choose the *ESPxxxx* board you are using, i.e. *Lolin S2 Mini*. If thie menu item *ESP32 Arduino* is missing, read below how to add non-Arduino boards to the menu.

To test these settings, choose *Sketch/Verify/Compile* (or press `CTRL`+`R`) and see whether the sketch compiles without errors.


<details><summary>Adding Support For Non-Arduino Boards</summary><br/>

Out of the box, *Arduino IDE* comes with support for *Arduino boards* (and its *clones*) only.

#### Support For ESP8266 And ESP32
To target the *ESP32* and/or *ESP8266* family of microprocessors, add the appropriate board manager like so:

1. Choose *File*/*Preferences*. In the text box *Additional Boards Manager URLs, add this: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json`, then click *OK*.


<img src="images/arduinoide_url.png" width="100%" height="100%" />

2. Go to *Tools*/*Board*/*Boards Manager*. In the search box at the top of the dialog window, enter *ESP32*. In the results list, choose *ESP32* by *Espressif*, and click *Install*. A 260MB download starts and can take a few minutes.

<img src="images/arduinoide_esp32.png" width="100%" height="100%" />

3. To add support for *ESP8266*, enter *ESP8266* into the textbox. In the results list, choose *ESP8266* by *ESP8266 Community*, and click *Install*. Once the new board managers are installed, click *Close*.

When you now open *Tools*/*Board*, there are two new submenus: *ESP32 Arduino* and *ESP8266 Boards*.

To add support for additional microcontroller families, follow the same scheme. 

#### Support For ATtiny

For example, to add support for *ATTiny* microcontrollers, add the additional *board manager url* `https://raw.githubusercontent.com/sleemanj/optiboot/master/dists/package_gogo_diy_attiny_index.json` (use *commas* to separate more than one url in the textbox).

Next, go to *Tools*/*Board*/*Boards Manager* once more, and search for *attiny*. Click *Install*.

<img src="images/arduinoide_esp32.png" width="100%" height="100%" />


Once this board manager is installed, you find another new submenu named *DIY ATtiny*.


<img src="images/arduinoide_attiny_list.png" width="100%" height="100%" />


</details>


> Tags: USB, UART, TTL, Connect, Port, COM

[Visit Page on Website](https://done.land/components/microcontroller/advice/preparingsamplesketch?297809051621241735) - created 2024-05-20 - last edited 2024-05-20
