<img src="/assets/images/light.png" width="80%" height="80%" />
 
# SK6812

> WS2812B Clone With Four Instead of Three Channels To Control RGBW

The *SK6812* is very similar to the popular *WS2812B* but can control *four* instead of *three* channels.

It is a *clone* with all the risks and benefits. You get **RGBW** support for the price of a *WS2812B*, and due to a higher voltage range, you may be less subject to the effects of *voltage drop*.


## When To Use

If you want to control **RGBW**, the *SK6812* is the most economic solution.

The same goes for running *long* **LED strips**: color and brightness stabilization is better than with *WS2812* (unless you use *voltage injection*).



## When To Not Use


This is a *clone* trying to mimick the original *WS2812B*. 

*Clones* can be perfectly ok but do not always come with the same *quality* (i.e. smaller **LED** die = less brightness or issues with the *data protocol*)

Hobbyist should choose the *proven* *WS2813* (if you need redundant data wires) or the *cheaper* *WS2812B*. Both are not *much* more expensive than the *clones*.

*SK6812* uses **5V** supply voltage. For very long **LED strips** and huge *matrix displays*, you either need *voltage injection* or should choose a **12V** or **24V** controller type.

If you just need **RGB LED**, using the *WS2812* is sufficient and cheaper.


## Reverse Voltage Protection

*WS2812B* come with a *reverse voltage* protection: 

When polarity is reversed (or when you accidentally connect an **LED strip** at the wrong end), you are protected from destroying the strip.

## Datasheet

[SK6812 Datasheet](materials/sk6812_datasheet.pdf)




> Tags: SK6812, WS2812B, LED, RGB, Controller, 5V, Clone

