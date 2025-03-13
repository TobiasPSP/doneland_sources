<img src="/assets/images/sensor3.png" width="100%" height="100%" />
 
# AS3935

> Detecting Lightning Strikes in a 40 km Radius via 500 kHz RF Impulses

The *AS3935* is one of the few available chips specialized in detecting the typical 500 kHz RF pulses emitted by lightning. It employs sophisticated algorithms to reject man-made disturbances and estimates the distance to a thunderstorm head down to *1 km* in 14 steps within a *40 km* radius.

## Overview

The *AS3935* operates within a wide voltage range of *2.4–5.5V* and can be controlled via [I²C](https://done.land/fundamentals/interface/i2c/) or [SPI](https://done.land/fundamentals/interface/spi/). It is available as a ready-to-use breakout board from several vendors, including [SparkFun](https://www.sparkfun.com/sparkfun-lightning-detector-as3935.html) and [CJMCU](https://www.google.com/search?q=as3935+cjmcu+aliexpress).

Programming the *AS3935* is possible using C++ libraries like *SparkFun Lightning Detector* ([source code](https://github.com/sparkfun/SparkFun_AS3935_Lightning_Detector_Library)). Additionally, [ESPHome](https://done.land/tools/software/esphome/introduction/) provides built-in support through the [AMS AS3935 Franklin Lightning Detector Component](https://esphome.io/components/sensor/as3935.html).

Boards with *AS3935* are fairly expensive. They cost in the range of €15-30.

## Caveats

Working with the *AS3935* can be challenging. While it supports both *I²C* and *SPI*, the *I²C* implementation can be unreliable, making *SPI* the recommended choice.

The main challenge in operating the *AS3935* lies in a conflict of interest: the sensor must be extremely sensitive to detect weak electromagnetic impulses from lightning, yet it is often placed near high electronic noise sources.

One of the most significant noise sources can be the **power supply**. Switching power supplies, such as cheap USB adapters, introduce substantial electrical noise that can interfere with detection and trigger frequent warning messages.

## Recommendations

To minimize noise and improve performance, consider the following:

### **1. Use the SPI Interface**  
Avoid the *I²C* interface due to its known instability.

### **2. Choose a Clean Power Supply**  
Preferably use **batteries** or a **linear power supply**. Avoid regular USB adapters or any switching power supplies, as they introduce excessive noise.

### **3. Use 5V**
Operate the board with *5V* instead of *3.3V* if you run into problems.

### **4. Optimize Sensor Placement**  
If possible, install the sensor **outdoors** and transmit its data wirelessly. This reduces exposure to the high-density electromagnetic interference (EMI) typically found indoors.

### **5. Set AFE to "Outdoors"**  
When configuring the board, always set *AFE* (gain) to **OUTDOORS**, even if the sensor is used indoors.  
- The **INDOORS** setting increases gain to compensate for signal loss due to building materials.  
- However, this backfires because the increased gain amplifies **indoor electronic noise**, leading to frequent *Disturber detected* messages.

### **6. Use a Lightning Generator for Testing**  
To reliably test the board, consider building a [lightning generator](https://sites.google.com/view/as3935workbook/home).  
This acts as a test instrument to trigger the sensor without relying on actual thunderstorms. The *AS3935* is sophisticated enough to **ignore electric lighters and simple spark generators**, making controlled testing useful.



## Final Thoughts

When properly set up, the *AS3935* performs well. While it may not detect every lightning strike and distance estimation can be imprecise—since lightning does not always emit RF pulses with consistent strength—it can be the icing on the cake for many ambitioned weather stations, despite the relatively high sensor cost.

However, if you simply want real-time lightning strike locations, consider using free, open-source triangulation networks like [Blitzortung.org](https://www.blitzortung.org/en/live_lightning_maps.php?map=10), where volunteers share live lightning detection data.

## Materials

[Datasheet](materials/as3935_datasheet.pdf)

> Tags: Lightning, 500kHz, Triangulation, UV

[Visit Page on Website](https://done.land/components/data/sensor/lightning/as3935?330928031810254712) - created 2025-03-09 - last edited 2025-03-09
