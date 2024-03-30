<img src="/assets/images/light.png" width="80%" height="80%" />
 
# SK6812

> WS2812B Clone With Four Instead of Three Channels To Control RGBW

The *SK6812* is very similar to the popular *WS2812B* but can control *four* instead of *three* channels.

Whenever you want to control **RGBW LED** instead of **RGB LED**, the *SK6812* is the most commonly chosen controller.



It is a *clone* with all the risks and benefits. You get **RGBW** support for the price of a *WS2812B*, and due to a higher voltage range, you may be less subject to the effects of *voltage drop*.


## When To Use

Here are the most important advantages over the *WS2182B*:

* **RGBW Support:** You want to control **RGBW LED** instead of **RGB LED**
* **3.3V Support:** While the *WS2812B* can be controlled using **3.3V**, this is outside the specs, and when the physical distance between microcontroller and *first* **LED** is longer than a few centimeters, you may have to use a *level shifter*. The *SK6812* has a *wider voltage range* and works reliably with **3.3V**.
* **Long Strips:** due to the *wider voltage range*, a *voltage drop* seems to have less negative effects. This can be a benefit when using **LED strips** longer than *2.5m* unless you use *voltage injection* anyway.

## When To Not Use

There have been reports that *protocol timing* may be different from *WS2812B*. Typically, *SK6812* are *compatible* but they are *clones* with slight variations.
There have also been reports that some *SK6812* use **LED** with smaller *dies* (lower brightness). If in doubt, check the data sheet of the particular *SK6812* you are planning to purchase.

If you want to control **RGB LED** (and do not need the additional channel for **RGBW**), then probably the safest approach is to use the proven *WS2182B*. Often there are no significant price differences.


## Datasheet

[SK6812 Datasheet](materials/sk6812_datasheet.pdf)




> Tags: SK6812, WS2812B, LED, RGB, Controller, 5V, Clone

[Visit Page on Website](https://done.land/components/light/led/programmable/sk6812?415038031819243633) - created 2024-03-06 - last edited 2024-03-19
