# Controlling Buck Converter Via ESP8266
:stopwatch: Reading time: 20 minutes.

## Quick Overview

Recently, I came across an [Instructables](https://www.instructables.com/DIgital-Controlled-Bench-Power-Supply/) article from *Robert Tidey* where he built a digitally controlled bench power supply based on readily available and cheap *XL4015*-based **5A CV CC** *Buck* breakout boards.

I immediately catched fire as this sounded like a clever technique which possibly can be adapted to other (and possibly more powerful) *buck* converters. So I visited Roberts [github](https://github.com/roberttidey/WifiPowerSupply) repository, and contacted him.

Here I documents my steps to rebuild the digitally controllable power supply in case these steps can help you build your own.

### Principle

Off-the-shelf **Buck** converters typically come with two potentiometers to adjust *voltage* and *current*. To digitally control this, there are a few possible approaches:

* **Digital potentiometers**: Replace the manual resistors with digital potentiometers like the *MCP41**HV**51* (make sure it is this specific **HV** type as most digital potentiometers support only logic-level voltages and will be destroyed when used with the voltages present in **Buck** converters.
* **Injecting Voltage**: Potentiometers in **Buck** converters often work as simple *voltage dividers* to produce a given voltage that then is used to set output voltage and limit output current. When you turn the potentiometer to a defined value and leave it there, you can also produce a voltage, i.e. by a **DAC** (*digital-to-analog converter*), then *inject* this voltage to one of the potentiometer pins.

The latter is *Richards* approach, and there are at least two advantages over the digital potentiometer idea:

* **More granularity**: affordable high voltage digital resistors are 8bit (256 steps) whereas *DAC*s typically have 12-16 bits (more precise control)
* **Less Tweaking**: to use digital potentiometers, you first need to remove the physical potentiometers. While desoldering them is no rocket science, it is a significant change in the **Buck** device. To *inject* voltage, in contrast, you do not touch the **Buck** breakout board at all. There are just three easily-identifyable solder pins where you need to attach wires.


<img src="images/buck.png" width="100%" height="100%" />
