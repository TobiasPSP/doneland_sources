<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Microcontroller Families

> How To Select The Right Microcontroller For Your Project

Today, there is a vast variety of *microcontrollers* and *boards* available for *DIY projects*, all with their individual strengths and weaknesses. 

In this section you get help selecting the right *microcontroller* for a given task, plus extensive information about many popular boards.

## Guidance

Here is a list of reasons for *when to choose* a particular microcontroller board. This list is neither complete nor authoritative. If you have additional tips or suggestions, please leave a comment below.

### Beginner
If you just want to get your hands dirty and find out what a microcontroller can do, then an *Arduino* (or one of its *Clones*) *might* be right for you: since *Arduinos* are around the longest, there is a wealth of resources and video tutorials available. They are renown for their easy-of-use, and using *Arduino IDE*, you'll be up and running quickly. 

The actual *type* of *Arduino* depends on your needs (i.e. the number of devices you want to control, *GPIOs*):
* *Arduino Uno*: too old and limited
* *Arduino Nano*: great *general purpose* choice
* *Arduino Every*, *Arduino Nano ESP32*: lack compatibility, ease-of-use. If you are after some of their special features, better pick a *real* *ESP32 board* (see below)

While *Arduinos* let you *quickly enjoy first successes*, they are *pricy* and *limited*. Both the (easy-to-use) *ArduinoIDE* and the *boards* stop to be fun once you catch fire and *want more*: *memory* is too limited for more sophisticated programs, *WiFi/Bluetooth* connectivity is lacking, *power consumption* is comparably high.

So *unless you are determined to exactly follow some Arduino training videos*, for beginners with a bit of basic technical understanding, the recommendation is to get a *ESP32 S2* and use it in *platformio* rather than *Arduino IDE*. This sets you up in the most *future-proof* way.

The *ESP32 S2* is a great and extremely powerful single-core microcontroller, is available for under EUR 2.00 (so you can buy a couple, just in case you toast one or want one to stay in a useful device you built), has plenty of memory even for the most advanced sketches, and is the last *ESP32* family member that comes with useful-to-experiment features like *DAC* (digital-to-analog converter).

| Microcontroller | Pro | Contra |
| --- | --- | --- |
| Arduino Nano | Simple Start | Quick to reach limits |
| ESP32 S2 | A little more time required to get started | Cheaper, more powerful, extensible future-proof tool chain |

### WiFi-Related

Any of the *ESP32* will do.

### High Computational Load

*Classic dual-core ESP32* or even better yet, the new *dual-core ESP32 S3* with *advanced AI vector analysis support* that runs code another *10%* faster.

### Low Computational Load And No Space

If you want a microcontroller to just *control hardware* and *sensors* in very *space-constrained* environments and with low *energy consumption*, then *ATtiny* is a good way to go.


### Battery-Powered Devices

All newer *ESP32* come with excellent and most efficient power-savings modes: *S2*, *S3*, *C3*, *C6*

### Unix/Linux

If you intend to run *full-fledged applications* on a *real operating system*, choose *Raspberry Pi*

> Tags: Microcontroller, Guidance, Select, Arduino, ESP32, ESP8266, ATtiny, Raspberry Pi

