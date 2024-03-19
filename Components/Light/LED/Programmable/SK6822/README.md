<img src="/assets/images/light.png" width="80%" height="80%" />
 
# SK6822

> A WS2813 Clone With Some Shortcomings 

The *SK6822* is a *WS2813* *clone* with almost the same technical specifications.

## Differences

Its *input voltage range* seems wider (*3.3-7.5V*) than the original, allowing **3.3** microcontrollers to safely operate them.

Then again, the original *WS2813* tolerates *3.3V* as well when the distance between first **LED** and microcontroller is less than *30cm*.


## When To Use

*SK6822* may be an alternative when *price* matters.


## When To Not Use

This is a *clone* trying to mimick the original *WS2813*. 

While some of the specs seem *improved* over the original, you pay the price elsewhere:

There are reports about *strange timing issues* and *smaller LED die*. 

*Clones* can be perfectly ok but do not always come with the same *quality* (i.e. smaller **LED** die = less brightness or issues with the *data protocol*)

If you don't want to be a test pilot, choose the *WS2813* (if you need redundant data wires) or the *cheaper* and well proven *WS2812B*. Both are not *much* more expensive than the *clones* anyway.

## Datasheet

[WS2813 datasheet](materials/sk6822_datasheet.pdf)

> Tags: SK6822, LED, RGB, Controller, 5V, Clone
