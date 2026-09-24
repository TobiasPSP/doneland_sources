<img src="/assets/images/lightning.png" width="100%" height="100%" />

# DC-DC Converters

> Modern Electronic Circuits To Lower Or Raise DC Voltage And Limit Current

Modern *switching* DC-DC converters are an [essential part of most power supplies](https://done.land/components/power/powersupplies/#voltage-regulators). 

Here, I am looking at actual implementations of DC-DC-converters, often available as affordable and ready-to-use modules from sources like *AliExpress*.

### Simple CV and CC Converters

Classic DC-DC converters are used to power electronic devices with a given steady voltage. These are typically *constant-voltage (CV)* regulators, and they can be found ubiquitously in "wall warts", integrated into devices, as notebook power supplies, and more.

Lab bench power supplies are an example of supplies that optionally use *constant-current (CC)* regulation, i.e. to protect the output from accidental overload or to support special lab scenarios such as battery charging or testing.

### Special Converters

Aside from pure CV and CC regulators, there are integrated specialty solutions that may be more adequate for what you are trying to do:

### [Battery Charging](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/)    

  Dedicated battery charger converters combine *DC-DC conversion* with a charging algorithm matched to the battery chemistry. For Li-ion batteries, they typically use *constant-current (CC)* charging until the battery approaches its maximum voltage, then switch to *constant-voltage (CV)* operation and terminate charging once the current has fallen below a defined threshold.

  A general lab bench power supply with CC capability, in contrast, can **imitate** the basic CC/CV part of this process by manually setting the appropriate voltage and current limits. However, its CC function is primarily an *output current limiter*, not a complete charging controller.

  Dedicated charger converters add the actual *charging logic* that a general-purpose CC/CV power supply lacks, i.e. automatic termination of charging once the current has fallen below a defined threshold and a reduced-current *pre-charge* for deeply discharged cells. A laboratory PSU, in contrast, continues regulating its configured voltage and current limits; it does not inherently know when a battery is considered fully charged or when charging should stop or restart.

  This makes dedicated charger converters preferable for unattended or permanently installed charging, especially when the DC-DC-controller you are using has no temperature probe that can cut charging in defective batteries or with other failure situations. A CC-capable DC-DC converter (including a lab bench PSU) is useful for testing and manually supervised charging only. In any other cases, you should use a **dedicated charger controller** instead.

### [Harvesting Solar Energy](https://done.land/components/power/powersupplies/solar/)    

  Uses *DC-DC converters* with *MPPT control* to operate solar panels efficiently.    

  In a nutshell, these regulators adjust the current drawn from the panel to keep its *input* voltage near the point where the panel delivers the most power. When the input voltage drops below this operating point, the regulator reduces the current it draws.

  Or put differently, these *constant current* regulators *automatically adjust* the constant current to maintain a certain voltage at the input. If this voltage drops, they decrease the constant current. 
  
  So in this scenario, the constant current isn't really constant, but the same regulation technique is used for a different purpose: to keep input voltage constant for a supply like a solar panel that can drop voltage when overloaded.

  More advanced MPPT implementations actively search for the optimum operating point as this point isn't fixed and can vary with temperature, solar intensity, shading, and other factors. A common technique, *Perturb & Observe (P&O)*, repeatedly probes slightly higher and lower input voltages and observes whether the resulting power increases or decreases. Since P&O is complex, such solutions often require a microcontroller as well as voltage and current measurement which makes them a magnitude more expensive. This makes true P&O implementations much more expensive than simple fixed-voltage MPPT regulators. Their additional power consumption can also become significant with small panels and defeat its purpose: to harvest more solar energy.

  Simpler implementations regulate the panel to a fixed input voltage that approximates its typical maximum-power voltage. This is less accurate, but inexpensive, often sufficiently effective and typically the better solution for small panels.

### [LED Drivers]()   

  *Dimmable* constant-current buck, boost, or buck/boost regulators with a *PWM* or dimming pin to quickly turn the LED current on and off. 
  
  Do not confuse this with *Enable* pins that typically shut down the entire regulator and are commonly used to add a switch for LED lights that turn them permanently on and off. They are typically not suitable for high-frequency switching although exceptions exist where actual *PWM* pins are labeled *Enable*.   

### [Powerbanks](https://done.land/components/power/powersupplies/battery/chargers/)   

Controllers for Powerbanks are typically **bi-directional** and can be used for charging *and* discharging.


For example, in simple *1 S* powerbanks, they *boost* the battery voltage (3.7 V) to 5 V USB, and they *buck* the 5 V USB back to charging voltage when connected to a charger. [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) is a good example.  

More advanced units support USB PD output at different output voltages and *buck/boost* converters to deliver voltages below *and* above the actual battery voltage. [IP2369](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2369/nouying45w/) is a good example.

Depending on implementation and chip, such solutions may contain *two* separate DC-DC converter stages that can operate independently (one for charging, one for output), or a shared converter stage that can *either* charge *or* supply.

The latter is cheaper with lower component count, but the converter itself cannot supply energy from the battery while charging it. In very simple designs (like [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/)), when a *regulated input* is mandatory (i.e. 5 V), as a workaround, this input voltage is passed through to the output during charging, so it appears as if such boards *can* deliver power while charging. 
    
One consequence of such designs is a brief power-path transition when the chip switches between external input and battery/boost operation, i.e. when a charger is connected or disconnected. Depending on load and output capacitance, this may cause a short voltage dip or even a brief power "outage" that can reset connected electronics.

## "Extras" to Watch Out For

Here is a summary of the most useful "extras" you may find (and possibly need) in  DC-DC converters:

* ***MPPT / Input Regulation:***     

  Automatic adjustment of the current drawn from a power source based on its input voltage, allowing sources (such as solar panels) to operate near their optimum power point.    

* ***Dimmable:***   

  Internal circuitry to rapidly enable and disable the output current without upsetting the regulator control loop, typically for LED projects where you either want to *dim* the LEDs using PWM, or for flash patterns in emergency lights. Here, they work for any kind of lamp, not just LEDs.   

* ***Combined/Bidirectional Regulators:***   

  Buck and boost functionality for bidirectional operation, i.e. charging and discharging a battery at different voltage levels. Depending on the implementation, this may use separate buck and boost stages or a single bidirectional *buck/boost* power stage.

> Tags: Switching, Power Supply, Voltage, Current, DC-DC Converter, Constant Current, Constant Voltage, Dimmable, LED Driver, Perturb & Observe, P&O

[Visit Page on Website](https://done.land/components/power/powersupplies/dc-dc-converters?021269091524263527) - created 2026-09-23 - last edited 2026-09-23
