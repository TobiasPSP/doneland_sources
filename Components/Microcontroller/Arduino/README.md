<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Arduino Family

> Arduinos Made Programming Microcontrollers Popular Among Hobbyists - Which Is Why There Are Tons Of Examples And Documentation, And Why Still So Many People Use Them


Around 2005, the *Arduino family of microcontrollers* started to open up the world of microcontrollers to the general public. From the start, they were *very easy to use*. The free *development environment*, **Arduino IDE**, works out of the box for *Arduinos*, no configuration needed. The *entry level* for *Arduinos* is very low.

<img src="images/arduino_nano_every_original_back_logo_t.png" width="80%" height="80%" />

## ATMega Microcontrollers

*Arduinos* were originally based on *ATMega* microcontrollers, and the boards were developed and produced by *Arduino LLC*. The name *Arduino* was borrowed from a bar where the founders liked to hang out.

The first boards were bulky, slow (using *ATMega8*), and came with very limited memory and only a few *GPIO* pins. 

Resources were improved over time, and footprint cut down. 

<img src="images/arduino_mega_top_front_t.png" width="80%" height="80%" />

<sup>This *original* **Arduino Nano Every** has a relatively small form factor and plenty of GPIOs</sup>

Today, there is a vast [Arduino Ecosystem](https://docs.arduino.cc/hardware/) with a variety of boards and processors.



### Arduino Mega and Nano

The two most popular *Arduino* family members illustrate the evolution: 


<img src="images/arduino_mega_top_front2_t.png" width="80%" height="80%" />

<sup>Arduino Mega (*right*) and Arduino Nano (*left*, almost the same features in a much smaller form factor)</sup>

### Pros and Cons

The biggest **PROS** for *Arduinos* are the *huge community*, the vast number of *code examples*, and the *ease of use*. 

There are important **CONS**, too:

* **No Wireless:** *Arduinos* do not come with any wireless support. You cannot connect them to the Internet, your home WiFi, or use *Bluetooth*.
* **Limited Memory:** modern *Arduinos* have added more memory and *GPIO* pins, but memory is still limited. When you create more sophisticated firmware, it is not unusual to run into compilation errors due to lack of memory.
* **High Energy Consumption:** Should you plan to run your devices on solar or battery power then *power consumption* becomes an issue, and *Arduinos* typically need relatively much power.
* **Expensive:** The *original Arduinos* and even most *clones* are relatively expensive compared to other microcontrollers.
* **Big:** some *Arduinos* like the *Nano* are comparably small, yet compared to other microcontroller boards they are still *huge* and make your devices bigger.

> [!NOTE]
> I started my first steps with *Arduino*, like so many others. Because of the *cons* listed above, I soon switched to other microcontrollers, though. That is why the examples on this site are focused on **ESP8266** and **ESP32**.


> Tags: Microcontroller, Arduino

:eye:&nbsp;[Visit Page on Website](https://done.land/components/microcontroller/arduino?264286031823244200) - last edited 2024-03-23
