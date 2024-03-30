<img src="/assets/images/light.png" width="80%" height="80%" />
 
# WS2811

> Distinct Controller With 3 Channels, Can Be Connected To Anything

The *WS2811* was the first **LED** controller widely used in daisy-chained **RGB LED**. It introduced the concept of *one-wire* communications. 

In contrast to all its successors, it is a separate *IC* and *not embedded* in **LED**. You are free to hook up any suitable **LED** you like.

> [!NOTE]
> *WS2811* uses **12V** supply voltage. Internally, it takes care that connected **LED** receive exactly the current they need.


## When To Use

*WS2811* is an *old concept* that probably is the *cheapest* way of creating **LED strips** or **displays** that run with **12V**.

**12V** supply voltage is perfect for driving a large number of **LED** as *currents* are *low*, and there is much less *voltage drop* than with **5V** controllers.

> [!NOTE]
> Do not be mistaken: a **LED strip** using *WS2811* can still be *controlled* by a *GPIO* from an *Arduino* or *ESP8266*. It just needs external **12V** power to drive the **LED**.

## When To Not Use


The controller is *designed* to control *three* **LED** at a time: it has *three* programmable *channels*, and *each channel* can drive *three* **LED**:


If you do not need to leverage its full potential, you can connect *just one* **RGB LED** to its three channels and build strips with truly individually addressable **LED**.

The standby power consumption is very high compared to more modern controllers. If you want to conserve energy or build a battery driven project you may want to use a different controller.



## Datasheet

[WS2811 datasheet](materials/ws2811_datasheet.pdf) 




> Tags: WS2811, LED, RGB, Controller, 12V

[Visit Page on Website](https://done.land/components/light/led/programmable/ws2811?443508031819245134) - created 2024-03-01 - last edited 2024-03-19
