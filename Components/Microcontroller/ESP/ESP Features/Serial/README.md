<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Serial

> Built-In Digital-To-Analog Converter (DAC) With High Speed Direct Memory Access (DMA)

*ESPxxx* come with *UART* controllers (*universal asynchronous serial receiver/transmitter*) which is a simple *two-wire protocol* for exchanging serial data.

One of its *UARTs* typically is connected to an external *USB-to-TTL* converter chip which in turn is wired to the *USB connector*. Most *ESPxxxx* development boards are connected via its *USB interface* and a *USB cable* to a computer in order to upload new firmware and output data to a terminal window.

## Basic Serial Communication
The *serial interface* connected to *USB* is a convenient way of communicating with the microcontroller and i.e. return status information or sensor data.

Here are the basic steps in code to output information to your development environment (like *Arduino IDE* or *platformio*):

````c++
#include <Arduino.h>


int c = 0;

void setup() {
  // initialize serial output with the appropriate baud rate:
  Serial.begin(115200);
  // wait for the driver to fully initialize:
  while(!Serial);
  // add a small delay IF YOU MUST OUTPUT data in setup() already:
  delay(500);
  Serial.println("Start");
}

void loop() {
  // output an incrementing counter each second:
  c++;
  Serial.println(c);
  delay(1000);
}
````

To run the sketch, follow these steps:

1. Compile and upload the sketch. Depending on the *IDE* you are using, choose *Upload and Monitor* instead of *Upload* (to open the serial monitor), choose *Monitor* if your sketch is already running, or (in Arduino IDE) open the *Serial Monitor*.
2. Make sure the *Serial Monitor* and your sketch use the *same baud rate* (*Speed*) or else you receive nothing or garbled characters.

When the sketch runs, it first outputs the text *Start*, then outputs an incrementing number, one per second.

> [!IMPORTANT]
> Before you can use the *serial interface* on an *ESPxxxx*, you need to include the *Arduino libraries*:

````c++
#include <Arduino.h>
````

### Initializing Serial Port
To successfully send information to the *IDE*, the sketch first needs to *initialize* the serial interface and set it to the desired *baud rate*. This is typically done in `setup();`:

````c++
  Serial.begin(115200);
````

### Waiting for Serial Port To Be Ready
It takes a moment for the serial port to be ready. If you start to output information right away, especially inside `setup();`, most likely you will lose this information unless you actively wait for the *serial interface* to be ready:

````c++
  // initialize serial output with the appropriate baud rate:
  Serial.begin(115200);
  // wait for the driver to fully initialize:
  while(!Serial);
  // add a small delay IF YOU MUST OUTPUT data in setup() already:
  delay(500);
````

This is a *two-step process*: `while(!Serial);` waits for the *drivers* to be initialized. The *serial interface is now *about to be ready* but **not yet ready at this point**.

If you output information *immediately thereafter* (i.e. inside `setup();`), you most likely still lose your data. To work around this, you'd have to add a *very small delay*, i.e. *500ms*.

> [!TIP]
> Use this only if you **must ensure** that all data is received by the terminal: adding checks and delays in `setup();` *will delay the start of the sketch* when you power on the microcontroller. Since serial data is often used just occasionally during *debugging*, and since it might not be a problem to miss a few pieces of data at the beginning, skipping these checks and delays results in a much *prompter start* of your sketch after power-on.




### Outputting Information
Data can be sent to the *serial interface* using `Serial.print();` (no linefeed), `Serial.println();` (adding a line feed), or one of the other *print* methods:


````c++
  Serial.println(c);
````

The output information is sent to the *Terminal Window*/*Serial Monitor* of your *IDE*:

* **Arduino IDE:** The *Serial Monitor* dialog window needs to be manually opened via *Tools/Serial Monitor* or `Control`+`Shift`+`M`. Make sure you select the correct *baud rate* in the *Serial Monitor* status bar.
* **PlatformIO:** The *Terminal* tab in the *console pane* is automatically opened. It is the same pane that shows the progress information during firmware uploads.

## Interacting With User
The *serial port* is *bidirectional*: you can *output* information to the *IDE terminal window*, and you can *receive* information sent by the user via *keypresses*.

> [!NOTE]
> When responding to user input, the particular behavior depends on the *IDE* and its *Serial Terminal* as well. Some terminals *echo* the user input while others do not. Some terminals allow just *one keypress* to be sent, others accept many consecutive keypresses.

Here is a sketch demonstrating *basic user interaction*: the sketch sends a *user prompt* to the *terminal window*, asking for user input. The user can then either press *1* or *0* to turn the built-in *LED* either *on* or *off*.

````c++
#include <Arduino.h>

void setup() {
  // initialize serial interface:
  Serial.begin(115200);
  while(!Serial);
  delay(500);

  // setup built-in led
  pinMode(LED_BUILTIN, OUTPUT);

  // report back internal LED pin
  Serial.print("Using built-in LED on GPIO ");
  Serial.print(LED_BUILTIN);
  Serial.println(".");
  Serial.println("Make sure this GPIO is correct, and your board in fact has a built-in LED.");

  // write initial user prompt:
  Serial.print("Enter Command (1 or 0)> ");
}

void loop() {
  // did the user input anything?
  if(Serial.available()) 
  {
    // read user input until user presses ENTER (and adds a newline (\n))
    char command = Serial.read();

    // echo user input
    Serial.println(command);

    // process user input:
    if(command == '1') {
      digitalWrite(LED_BUILTIN, HIGH); 
      Serial.println("[LED is ON]");
    } else if(command == '0')  {
      digitalWrite(LED_BUILTIN, LOW); 
      Serial.println("[LED is OFF]");
    } else {
      Serial.print("[Command not recognized: ");
      Serial.print(command);
      Serial.print(" Enter 1 or 0]");
    }

    // write prompt again:
    Serial.print("Enter Command (ON or OFF)> ");
  }
}
````

Depending on your *IDE*, the *user input* is entered differently:

* **Arduino IDE:** In the *Serial Monitor* dialog window, at the top there is an *input box* where you can enter information. Once you press the button *Send* at its right end, the entered information is sent.
* **PlatformIO:** Simply click into the *Terminal* tab inside the *console pane* (where the *serial output* is shown), then press the key you want to send. By default, *platformio* sends each keypress immediately, making user input especially convenient.

> [!CAUTION]
> The sketch uses the constant `LED_BUILTIN` and reports back the assigned *GPIO*. If the assigned *GPIO* is wrong, or if the constant `LED_BUILTIN` is not defined for your board, you can replace it with the actual *GPIO number* that is connected to the *LED*. Some boards turn the *LED off* when the *GPIO* is set to *HIGH*, effectively turning the *LED off* when it should be *on*, and vice versa. If that is the case, switch *LOW* and *HIGH* in the sketch. And finally: there are development boards (like the *DevKitC V4*) that *have no built-in user-controllable LED*, just a *power LED* that is constantly on and not controllable.


Here is the output from the *Terminal* window in *platformio*:

````
Using built-in LED on GPIO 15.
Make sure this GPIO is correct, and your board in fact has a built-in LED.
Enter Command (1 or 0)> 1
[LED is ON]
Enter Command (ON or OFF)> 0
[LED is OFF]
Enter Command (ON or OFF)> 0
[LED is OFF]
Enter Command (ON or OFF)> 1
[LED is ON]
Enter Command (ON or OFF)>
````


### Accepting String Commands
Reading and processing a single character via `Serial.Read();` is simple to code, simple to input, and clear: numbers are interpreted the same in *any culture*, and there is no potential for confusing *lower* and *upper* case.

Still, there are valid use cases where accepting more complex user input is required. Maybe you want to allow the user to not only switch the LED *on* and *off*, but also to *dim* it using various levels. In a nutshell, you may require more capable *user commands*.

Let's assume a sketch should support these user commands:

* *on*: turns the LED *on*
* *off*: turns the LED *off*
* *dim <int>*: turns LED *on* at the specified PWM brightness (1-255)

Here is a revised sketch that does this:

````c++
#include <Arduino.h>

void setup() {
  // initialize serial interface:
  Serial.begin(115200);
  while(!Serial);
  delay(500);

  // setup built-in led
  pinMode(LED_BUILTIN, OUTPUT);

  // report back internal LED pin
  Serial.print("Using built-in LED on GPIO ");
  Serial.print(LED_BUILTIN);
  Serial.println(".");
  Serial.println("Make sure this GPIO is correct, and your board in fact has a built-in LED.");

  // write initial user prompt:
  Serial.print("Enter Command ('on', 'off', 'dim <1-254>')> ");
}

void loop() {
  // did the user input anything?
  if(Serial.available()) 
  {
    // read user input until user presses ENTER (and adds a newline (\n))
    String command = Serial.readStringUntil('\n');

    // remove whitespace and newline characters:
    command.trim();

    // process user input:
    if(command == "on") {
      digitalWrite(LED_BUILTIN, HIGH); 
      Serial.println("[LED is ON]");
    } else if(command == "off")  {
      digitalWrite(LED_BUILTIN, LOW); 
      Serial.println("[LED is OFF]");
    } else if(command.startsWith("dim ")) {
      int dimLevel = command.substring(4).toInt();
      if (dimLevel<1 || dimLevel>254) {
        Serial.println("[Invalid DIM level. Must be a value between 1 and 254.]");
      } else {
        analogWrite(LED_BUILTIN, dimLevel);
      }
    } else {
      Serial.print("[Command not recognized: ");
      Serial.print(command);
      Serial.println("]");
    }

    // write prompt again:
    Serial.print("Enter Command ('on', 'off', 'dim <1-254>')> ");
  }
}
````

#### Adjustments for platformio
If you use *platformio* as your *IDE*, add these options to your projects' *platformio.ini*:

````
monitor_filters = send_on_enter
monitor_echo = yes
````

* `monitor_filters = send_on_enter` tells *platformio* that you *do not want it* to *automatically send off each keystroke* but instead want it to *wait for `ENTER`*. Without this setting, you would have to type each character no slower than *1000ms*, or else *incomplete* input would be transferred automatically.   
* `monitor_echo = yes` tells *platformio* to *echo the user input* while the user types it into the terminal window.


#### Playing With The Sketch
Click *Upload and Monitor* in *platformio*, or open the *Serial Monitor* in *Arduino IDE*.

You can now use the *three commands* to either turn the *LED* completely *on* or *off*, or set its *brightness level* in a range of *1-254*:

````
Using built-in LED on GPIO 15.
Make sure this GPIO is correct, and your board in fact has a built-in LED.
Enter Command ('on', 'off', 'dim <1-254>')> on
[LED is ON]
Enter Command ('on', 'off', 'dim <1-254>')> off
[LED is OFF]
Enter Command ('on', 'off', 'dim <1-254>')> dim 60
Enter Command ('on', 'off', 'dim <1-254>')> dim 1
Enter Command ('on', 'off', 'dim <1-254>')> dim 300
[Invalid DIM level. Must be a value between 1 and 254.]
Enter Command ('on', 'off', 'dim <1-254>')> dim 222
Enter Command ('on', 'off', 'dim <1-254>')> dim 44
Enter Command ('on', 'off', 'dim <1-254>')
````


> Tags: ESP32, ESP8266, Serial, println

[Visit Page on Website](https://done.land/components/microcontroller/esp/espfeatures/serial?587228051020245551) - created 2024-05-19 - last edited 2024-05-19
