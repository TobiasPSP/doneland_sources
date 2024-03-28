<img src="/assets/images/light.png" width="80%" height="80%" />
 
# APA102

> Modern Controller With SPI Interface And Variable Clock Rate


The *WS2812* and all of its successors depend on a very *timing-sensitive* one-wire data protocol with a fixed *data frequency* which is simple in respect to *wiring* but *complex* otherwise:

* **Limited Update Speed:** The fixed *data frequency* of *800kHz* is high enough for typical hobbyist projects but imposes a *hard limit* on the maximum data rate - even if the *microcontroller* was powerful enough to send the data faster. This limits the maximum *frame rate* with very long **LED strips** and large *matrix displays*.
* **Rigid Timing:** The data is expected to *always* come in at *800kHz*. This is ok for *real-time* microcontrollers like *Arduino* or *ESP32*, especially when they are dedicated to controlling **LED**. Multi-tasking microcontrollers like *Raspberry Pi* and *PC* cannot always guarantee this data rate as other tasks may temporarily keep them busy.


*APA102* uses a different approach: it uses the standard *two-wire* protocol **SPI** that is widely supported: **SPI** has a *data line* and *additionally* a *clock rate*. When the microcontroller is busy, it can simply *reduce the clock rate*. Likewise, it can also *increase* the *clock rate* to i.e. *4MHz* and send *much more* data for better *frame rates* even with super large displays.

> [!CAUTION]
> *APA102* is an example for a **LED** controller with *variable* data transmission. This is *not compatible* with the *one-wire protocol* used by all other controllers discussed here. To use *APA102*, you need to use completely different libraries and a *two-wire-connection*.   
> If you do not need the benefits of flexible clock rates, you may want to look into the *APA106* controller which is compatible to *WS2182*.

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

[Visit Page on Website](https://done.land/components/light/led/programmable/apa102?405038031819243633) - created 2024-03-19 - last edited 2024-03-19
