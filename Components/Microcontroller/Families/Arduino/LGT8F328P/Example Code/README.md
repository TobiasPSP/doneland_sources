<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Example Code

> Firmware Ideas and Concepts for LGT8F328P Boards



## Warm Up

* [Blink](https://done.land/components/microcontroller/families/arduino/lgt8f328p/examplecode/blink/):       
  Perfect start, with a simple blink sketch that blinks the built-in LED, enhanced with four GPIOs that also forward the blink signal, ready to control LEDs, drive MOSFETs or control LED drivers. Demonstrates the unique HDR mode, enabling up to 80 mA per GPIO.

* [Emergency Light Driver](https://done.land/components/microcontroller/families/arduino/lgt8f328p/examplecode/emergencylightdriver/):   
  Uses a `SY8750` LED driver IC to control original emergency equipment and implement custom flash patterns. Can also be used with any other high-performance and high-current lamps, not limited to LED. Maximum current per lamp/string is 2 A.   

  One of the topic discussed here is why using a PWM driver input for fast-switching light patterns is preferrable over simple MOSFET output control.

[Visit Page on Website](https://done.land/components/microcontroller/families/arduino/lgt8f328p/examplecode?386399091921264442) - created 2026-09-20 - last edited 2026-09-20
