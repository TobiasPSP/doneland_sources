<img src="/assets/images/light.png" width="80%" height="80%" />
 
# WS2812

> The Most Popular LED Controller Takes 5V, Can Control RGB LED And Daisy-Chain Using One Wire

The *WS2812* was the first *truly embedded* **LED** controller integrated right into *SMD* (and other) **LED**. This was a huge success, and the controller underwent a number of revisions to further improve it.

Today the *WS2812B* is the *most popular* and widely used controller type. 

> [!TIP] 
> The American company *Adafruit* even minted a new marketing term for it: *NeoPixel*. *NeoPixels* are no different from other *WS2812B* based **LED**, though.


## When To Use

*WS2182B* powers wonderful and *wonderfully cheap* programmable **LED**.

The chip runs with **5V** and has a *efficient standby* power consumption.

It is the perfect companion for *DIY projects* and embedded in a variety of boards, strips, matrix displays and breakout boards.

## When To Not Use

The culprit of this controller is its **5V** supply voltage and its limit to *three* channels.

These shortcomings define the cases where you may want to choose a *different* controller:

* **Many LED:** For *many* **LED** (like in very long *LED strips* or huge *matrix displays*), you should switch to a controller with a higher *voltage* (i.e. **12V** or *24V**). With **5V**, the *voltage drop* is considerable, and you would need to frequently *inject voltage* by supplying the voltage to multiple spots to keep voltage stable. Even this wouldn't help with the immense *current* needed that can quickly exceed *20A*.
* **RGBW:** You *can* drive the *three* channels in **RGB LED**, but you *cannot* drive the *four* channels required for **RGBW LED**
* **Fail Safe:** If the installation you plan is built into furniture or devices where you later *cannot service* them, the *one data line* of *WS2812* is a *single point of failure*: should *one* *WS2812* in your string fail, then all *following* **LED** will also fail. For more fail-safeness, choose a controller with a redundant *fallback data line*.


## Secret Revisions

In 2017 major improvements were backported from its rarely available and expensive successor *WS2813*, however without changing the part number. These *improved WS2812B* are still sold as *WS2182B*, making them indistinguishable from their early siblings under the same name.

*WS2812B* **LED** can therefore have significantly different properties:

* **Refresh Rate:** increased from 400Hz to 2000Hz for flicker free recordings in HD video.
* **Reduced Current:** *RGB port* current was reduced from *17.5mA* to *16.5mA*. The slight decrease in brightness is not visible and may also be compensated by more efficient **LED** today.
* **Reset Time:** increased from *50us* to *280us*

> [!CAUTION]
> The change in *reset time* can cause *breaking changes* when your projects drive these controllers with *extremely low* reset times. To fix, review the libraries you use and make sure you increase the *reset time* to *roubust* values of **>280us**.   


## Datasheet

The original [datasheet](materials/ws2812b_datasheet_original.pdf) of the initial *WS2812B* version was published by the American company *Adafruit*.

Around 2017, the *WS2812B* specifications changed (see above), and the manufacturer released a [new datasheet](materials/ws2812b_datasheet_revised.pdf).


> Tags: WS2812, WS2812B, LED, RGB, NeoPixel, Controller, 5V

[Visit Page on Website](https://done.land/components/light/led/programmable/ws2812?238337031419241823) - created 2024-03-19
