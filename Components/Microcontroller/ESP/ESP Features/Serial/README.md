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
> Use this only if you **must ensure** that all data is received by the terminal: adding  checks and delays in `setup();` *will delay the start of the sketch* when you power on the microcontroller. Since serial data is often used just occasionally during *debugging*, and since it might not be a problem to miss a few pieces of data at the beginning, skipping these checks and delays results in a much *prompter start* of your sketch after power-on.




### Outputting Information
Data can be sent to the *serial interface* using `Serial.print();` (no linefeed), `Serial.println();` (adding a line feed), or one of the other *print* methods:


````c++
  Serial.println(c);
````

> Tags: ESP32, ESP8266, Serial, println

