<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Expansion Boards

> Expansion Boards For Classic ESP32 Development Boards

When working with microcontrollers, classic *breadboards* might not always work well for prototyping: microcontroller boards are so large that they don't fit on breadboards, or when they do, they occupy almost all usable space.

That's why for microcontroller projects, often *expansion boards* are used instead. 


<img src="images/expansionboard_overview_t.png" width="80%" height="80%" />


## Specific Microcontroller Breadboards
*Expansion boards* are *highly specific* and must match the microcontroller board that you want to use: at the heart of the *expansion board*, there is a socket where you plug in the microcontroller board. 

The pins of the plugged-in microcontroller board are then exposed via pins or screw terminals. As an added value, many *expansion boards* include voltage regulators, can be powered from a variety of sources, and may provide extra pins to supply power to your components.

> [!TIP]
> Whether an *expansion board* can completely *replace* a *breadboard* or just *complements* it depends on the complexity of your project.


## Benefits of Expansion Boards

For prototyping, *expansion boards* are not required but can fix a number of issues:


* **Space** As discussed, the primary target are *microcontroller boards* that are *too large* to fit on breadboards.
* **Power Supply:** *USB* can provide power for simple projects, however once you use a lot of components, or when components (like sensors) cause power surges, your entire setup may become *unstable*: voltage drops lead to *brown-outs*, and the microcontroller may unexpectedly reboot.
* **Additional Voltages:** Your project may require *two* stable power supplies, one for *3.3V* and another one for *5V*. The *built-in power regulator* found on most *development boards* is limited to *500mA* or even less.
* **Testing in the Field:** you may want to test your prototype in the field, car, plane, or boat, powering it via an external power source (i.e. *12V* on-board voltage socket). Most *development boards* support a very limited input voltage range and can be damaged when exposed to more than *7V*.

> [!TIP]
> Some *expansion boards* add battery charging capabilities and thus may not be limited to prototyping but can become part of the final device.


### Considerations

Here are the few considerations when using an *expansion board*:

* **Development Board:** *Expansion boards* are designed for a specific *development board*. Make sure the *expansion board* matches the *development board* you intend to use.
* **Jumpers:** some *expansion boards* use *jumpers* to set voltages for auxiliary power pins that are used to supply power to external components. Typically you can switch between *3.3V* and *5V*. Make sure you understand how your *expansion board* works, and verify that it supplies the voltages you need.
* **Power:** Most *expansion boards* come with robust voltage regulators but there are significant differences. Make sure the *expansion board voltage regulator* can provide the kind of power your prototype needs. Look for the maximum *current* that the *expansion board* supplies.

## List of Expansion Boards
A variety of *expansion boards* exist, and it is not feasible to cover them all in detail. Most *expansion boards* work similarly, and there are a few models that are highly popular.

Here is an updated list of *expansion boards* reviewed so far on this site:

| Article | Microcontroller | Pins | Compatible Boards |
| --- | --- | --- | --- |
| [Review](./devkitcv4) | ESP32S | 38 | DevKitC V4 or similar, width 24mm or 25.5mm |

> [!TIP]
> The term *ESP32S* refers to *classic* ESP32 microcontrollers like *WROVER* or *WROOM*. The term *ESP32* is much broader and refers to *any* microcontroller of the *ESP32 family*, including *WROVER* as well as *S2* or *C3*.   





> Tags: Microcontroller, ESP32, Expansion Board, Development Board

[Visit Page on Website](https://done.land/components/microcontroller/expansionboards?569323071504244301) - created 2024-07-03 - last edited 2024-07-03
