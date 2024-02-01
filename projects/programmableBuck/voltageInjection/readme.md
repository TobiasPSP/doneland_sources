# Controlling Buck Converter Via Voltage Injection
:stopwatch: Reading time: 20 minutes.

## Quick Overview

Recently, I came across an [Instructables](https://www.instructables.com/DIgital-Controlled-Bench-Power-Supply/) article from *Robert Tidey* where he built a digitally controlled bench power supply based on readily available and cheap *XL4015*-based **5A CV CC** *Buck* breakout boards.

I immediately catched fire as this sounded like a clever technique, possibly adoptable to other (and possibly more powerful) *buck* converters, and useful to so many projects:

* **Bench Power Supply**: create your own modern bench power supply with cool custom-designed LCD, TFT or OLED displays, wireless controllable, with monitoring and data logging - thanks to digital control, ESP8266 et al can enhance functionality enourmously.
* **Automated Testing**: a script or computer program can quickly change voltage and current based on test protocols, i.e. for automated device testing.
* **Clever Chargers**: ever wanted to charge your *LiPo*s or *LiFePo4*s using *exactly* the recipe you trust most? With readily available and cheap components, you could build your own highly customizable battery charger that first charges gently with **CC**, then adds more current, and finally tops it off with a *constant voltage* charging phase, all of this of course with a charging protocol that shows battery health and can be used for documentation.
* **Sophisticated LED drivers**: tired of flickering **PWM** dimmed LEDs? Now you could directly control the *current* and create simple but effective *LED drivers* with wireless and bluetooth control for beautiful LED displays.

I am sure there are plenty additional community ideas what else you could do with digitally controllable power supplies.

So I visited Roberts [github](https://github.com/roberttidey/WifiPowerSupply) repository, and contacted him.

Below you can follow me with my steps to rebuild the digitally controllable power supply, and if you, too, catch fire, easily follow along and you build your own.

### Approaches To Digital Controllability

Off-the-shelf **Buck** converters typically come with two potentiometers to adjust *voltage* and *current*. To digitally control this, there are a few possible approaches:

* **Digital potentiometers**: Replace the manual resistors with digital potentiometers like the *MCP41**HV**51* (make sure it is this specific **HV** type as most digital potentiometers support only logic-level voltages and will be destroyed when used with the voltages present in **Buck** converters.
* **Injecting Voltage**: Potentiometers in **Buck** converters often work as simple *voltage dividers* to produce a given voltage that then is used to set output voltage and limit output current. When you turn the potentiometer to a defined value and leave it there, you can also produce a voltage, i.e. by a **DAC** (*digital-to-analog converter*), then *inject* this voltage to one of the potentiometer pins.

The latter is *Richards* approach, and there are at least two advantages over the digital potentiometer idea:

* **More granularity**: affordable high voltage digital resistors are 8bit (256 steps) whereas *DAC*s typically have 12-16 bits (more precise control)
* **Less Tweaking**: to use digital potentiometers, you first need to remove the physical potentiometers. While desoldering them is no rocket science, it is a significant change in the **Buck** device. To *inject* voltage, in contrast, you do not touch the **Buck** breakout board at all. There are just three easily-identifyable solder pins where you need to attach wires.

## Basic Setup

The schematics below explain the general idea and approach:

<img src="images/voltage injection fundamentals_w.svg" width="90%" height="90%" />


