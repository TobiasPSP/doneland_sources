<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Overview

> The "Big Picture" And Some Essential Terminology To Get Started

Before I get *practical* and show you step by step how to *actually use* microcontrollers in your projects, let's start with a quick *overview*, and clarify some basic *terminology* so we all are on the same page.

## Microcontroller

A *microcontroller* is basically a *chip*. From the outside, it doesn't look any different than other chips. Depending on the *complexity* of the microcontroller, the chip may come in an unexcited *DIP8* case, or it comes as a large flat sophisticated *SMD* case.


For a *microcontroller* to work, it requires just a few *external components*:

* **Crystal:** a *crystal* is needed to provide a stable *clock signal* unless it is a *very simple microcontroller* running at low clock speeds such as an *ATtiny* that uses an *internal oscillator* instead.
* **Voltage Regulator:** since microcontrollers are sensitive towards *voltage* and can be destroyed when too high a voltage is supplied, a *voltage regulator* ensures that the required voltage is supplied.
* **Capacitors:** *Decoupling capacitors* need to be placed close to the power pins of the microcontroller to filter out noise and stabilize the power supply.
* **Reset Circuitry:** a *button* and a *pull-up resistor* are needed to ensure that the *reset pin* is *disabled* unless the button is pressed.

### Supply Voltage
Microcontrollers require an exact supply voltage and can easily be destroyed when connected directly to *too much voltage**. 

Older microcontrollers use a *5V* supply voltage whereas most modern microcontrollers use *3.3V*.

### Memory
Most microcontrollers come with various types and sizes of *memory* built-in. The *flash memory* is the most important type of memory as it is the place where *code* can be stored. *Flash memory* is *non-volatile* (data stays intact when power is turned off) and works very similar to ordinary *SD Memory Cards*.

In *DIY*, microcontrollers today should have at least *4MB* Flash memory, or else they can only be used for very simple tasks and might not integrate well in *DIY Home Automation* solutions.

### Firmware

The *software* that tells the microcontroller what it should do is called *firmware* and resides in non-volatile *Flash memory*. 

When you *power on* or *reset* the microcontroller, it immediately starts executing the *firmware* code.

* Firmware can be *preloaded on the microcontroller* (i.e. on *NodeMCU boards*) or *uploaded manually* at any time.
* Firmware is offered by many parties and then typically does *fairly specific things* (like control *LED strips*), or can be written yourself using an *IDE* (*Integrated Development Environment*) like *Arduino IDE* or *platformio*. 


### Boot Loader

Every microcontroller has some basic *code* that is either safely stored in *ROM* or in a protected section of its *Flash memory*: the *boot loader*. 

When the microcontroller is instructed to run the *boot loader*, it invokes its *service interface*: you can now *manage* the microcontroller and i.e. upload new *firmware* to it.

The procedure to switch a microcontroller to *boot loader mode* varies by type. For example, on *ESP32*-based microcontrollers, you need to *pull GPIO0 low* while *resetting* the microcontroller. 

Typically, the tools you use to upload new *firmware* handle this automatically.

### Clock

All *microcontrollers* internally use a *clock*. This is not a *regular clock* to tell the time but rather an *oscillator* with a certain frequency. The microcontroller executes one command at a time, and the *clock* sets the rate at which this occurs.

Some *microcontrollers* use an *internal oscillator* while others require at least an external *crystal* to set the clock frequency.

### GPIO
A *GPIO* (*general-purpose input/output*) is a pin on a microcontroller that can be programmed to function as either an input or an output. When in *input* mode, it can read signals (i.e. *button states*) and often even voltages in a given range. In *output* mode, it works like a *switch* and can switch between *low* and *high* (i.e. to relais, lamps, transistors).

> [!NOTE]
> *GPIOs* can be switched *on* and *off* in very high frequency. This can be used to *dim LEDs* (using *PWM*), or to implement control protocols such as *I2C* or *SPI*. Control protocols can be used to transfer large amounts of data, i.e. to work with *displays* or *storage*.

In a nutshell, the more *GPIOs* a microcontroller exposes the more things you can control simultaneously.

## Microcontroller Modules

To make life easier for developers, companies like *Espressif* ship their microcontrollers as *modules* that come with most of the required *external components* in place, minimizing the work in hardware development. 

Such *modules* add a *crystal*, *Flash memory*, an *antenna* or *antenna jack* (if the microcontroller is WiFi-enabled), and sometimes they cover the components with a *metal cap* that *shields RF*.

## Development Board

*Development boards* make life a lot easier for *developers* and *hobbyists* as well.

*Development boards* are small *PCBs* that come with *everything needed* to safely run a microcontroller *out-of-the-box*. They add the following to the microcontroller chip:

* **USB Connector:** connecting the microcontroller to a computer (i.e. to upload new *firmware* or *communicate* with it)
* **USB-to-Serial Chip:** most microcontrollers internally use a *simple serial interface* to communicate with the outside world. Most computers have replaced *serial connectors* with *USB ports*. A *USB-to-Serial Chip* translates the *USB signals* to *serial signals*.
* **Voltage Regulator:** makes sure that you do not toast the microcontroller by supplying the wrong voltage. The valid input voltages depend on the type of *voltage regulator*. At minimum, the *USB-delivered 5V* are safely changed to the input voltage the microcontroller requires.
* **Anti-Noise:** variety of *capacitors* and other discrete components that *stabilize* the voltage and minimize electrical *noise* on the lines.
* **Buttons:** *development boards* come with a *Reset* button (hooked up to the microcontroller *Reset* pin). Some boards have another button labelled *Boot*. By holding the *Boot* button on *ESP32* boards, resetting the microcontroller launches the internal *boot loader*.
* **LED:** Most *development boards* come with a *power LED* (lights up when the board is using its internal *voltage regulator*), and a *user-programmable* second *LED* prewired to one of the *GPIOs*. Can either be a simple *LED* or a *WS2812* programmable *RGB LED*. Used for easy *status indication*, and to provide *user feedback*. There are development boards *without* such LED (i.e. *DevKitC V4*).
* **Crystal:** If the *microcontroller* is requiring an *external crystal*, the board supplies it and drives the *clock*.

### NodeMCU

Some *development boards* carry the term *NodeMCU* in their name. On the *hardware side*, they are regular *development boards*. However, they always come with special *firmware preloaded*. Here are the facts you should know about *NodeMCU*:

* **ESPxxx Microcontroller:** *NodeMCU* development boards *always* use an *ESP8266* or one of the *ESP32*-family microcontroller because the bundled *firmware* requires it.
* **eLUA Interpreter:** The preloaded (bundled) firmware runs an *eLUA Interpreter*. By connecting to the board via *USB*, you can send *scripts* written in the language *LUA* to tell the microcontroller what to do. So you do not necessarily need to *program own firmware* and *upload it*. 



> [!NOTE]
> Most users aren't even aware that *NodeMCU development boards* come with a bundled LUA firmware. They ignore the *firmware* part of the deal and treat *NodeMCU development boards* like a generic *development board*: most typically, they upload own firmware, essentially overwriting and deleting the bundled LUA firmware without using it.

## Flasher
*Flashing* is the process of *uploading new firmware* to the microcontroller.

A *flasher* is a tool that performs this process: it can take a *firmware file* and upload it to the *flash memory* of a microcontroller. The microcontroller then starts executing the new firmware after a *reset* (that is typically part of the *uploading process*). Note that the *flasher program* must match the type of microcontroller you use and is typically provided by the microcontroller manufacturer. 

* You use a *flasher* only when want to upload a *firmware file* that you got from someone else.    
* When you program *your own firmware* using one of the available free *development environments* such as *Arduino IDE* or *platformio*, the *flasher* is part of the *IDE* and transparently works in the background. 

> [!TIP:]
> A *very convenient* way of uploading new firmware to a microcontroller is *web based flashing* that surfaced only a few years ago: it works right from within a *Chrome* browser (other browsers do not yet support this feature), requires no prerequisities or installations, and is *very simple to use*. You'll find many examples in the remaining articles. 






## IDE (Integrated Development Environment)
*Programming firmware yourself* provides the maximum control and flexibility: you decide completely on your own what (and how) a microcontroller should behave, and you can freely use all of its features. That's because you are essentially writing the *entire software* that the microcontroller gets to see.

On the flipside, you need to *do all the work* yourself. Luckily, *programming new firmware* is no rocket science though, thanks to modern tools and free libraries. It does require *basic programming skills*.

### Writing Code
One of the most important tools required is a *IDE* (*Integrated Development Environment*). It basically does these things:

* **Write Code:** provides an editor in which you can write and test the code. The programming language is always *C++*. 
* **Libraries:** provides help in finding available free libraries that add specific commands to manage the components you are using (display drivers, sensors, LED strips, etc.)
* **Samples:** provides *sample code* that you can use as a start, then customize
* **Compile:** can *compile* your code into a *binary firmware image* that matches the type of microcontroller you are working with
* **Upload:** can *upload* the firmware you created to your microcontroller
* **Monitor:** provides a *console* or *terminal* to display the information sent back from the microcontroller over the serial interface, and to send back user input


### Two Free Choices
There are *two popular IDEs* used by *DIY hobbyists*: *Arduino IDE* and *platformio*. They both take care of all of the tasks listed above, and they both work with the same wide variety of *microcontrollers*.

> [!TIP:]
> Choosing an *IDE* is a matter of personal *taste and preference*. Some users use both side-by-side, and choose the *IDE* depending on what they plan to do. *Arduino IDE* is *very simple to use* but gets confusing when your projects grow. *platformio* targets *professional developers* but requires a few steps to set it up correctly and understand its *project structure.


### Other Development Environments
While the *IDEs* that I just mention are used to *create and upload completely new firmware*, there are other *development environments* that do not *touch the existing firmware* but rather *work with it*.

For example, *NodeMCU development board* come with its integrated *LUA firmware*. You can use a *LUA development environment* to talk to this firmware and send it jobs in the shape of *LUA scripts*.

Instead of *creating and changing firmware* on the lowest level, the *LUA development environment* lets you compose *LUA scripts*, *send them to the *LUA interpreter running in your NodeMCU default firmware*, and *communicate back and forth* with the *interpreter*.






> Tags: Microcontroller, Module, Crystal, Voltage Regulator, USB-to-Serial

[Visit Page on Website](https://done.land/components/microcontroller/programming/connecttopc?505691051225241424) - created 2024-05-01 - last edited 2024-05-27
