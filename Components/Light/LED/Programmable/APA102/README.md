<img src="/assets/images/light.png" width="80%" height="80%" />
 
# APA102

> Modern Controller With SPI Interface And Variable Clock Rate

The *WS2812* and all of its successors depend on a very *timing-sensitive* one-wire data protocol with a fixed *data frequency*.

This works well *wiring-wise* but is *hard to control* by microprocessors.

Simple *microprocessors* like *Arduino* or *ESP32* that are dedicated to **LED** control can provide the necessary timing. 

Multitasking microcontrollers and computers such as the *Raspberry Pi* cannot *always guarantee* the correct timings. *APA102* uses a different approach: itsstandard *two-wire* protocol **SPI** is widely supported: it has a *data line* and a *clock line*. When the microcontroller is busy, it now can simply *reduce the clock rate*.

## Two Types

There are two *types* available: *APA102C* (plastic package) and *APA102* (added metallized plate for better heat conduction).

## When To Use

*APA102* is a sophisticated solution for requirements where the strict and static one-wire protocol cannot be used.

In these scenarios, *APA102* offers a flexible communications protocol using standard *SPI*.

They are especially suitable for *persistance-of-vision* applications as they have a very high *PWM* frequency of *19.2kHz* and the higher *frame rates* due to the *faster SPI data interface*.

## When To Not Use

The performance potential unlocked by *APA102* typically well surpasses that of *DIY microcontrollers* and the general need for it in *DIY projects*.

Since *APA102* uses a completely different communications system, you would need completely different libraries.

Since there is no apparent benefit for *DIY projects* when compared to *WS2812B* or its successors, choosing the well-known *one-wire* protocol controllers instead seems reasonable for most use cases.

> Tags: APA102, LED, RGB, SPI, Controller, 5V
