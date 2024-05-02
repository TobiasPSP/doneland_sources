<img src="/assets/images/sun.png" width="100%" height="100%" />

# Solar 

> All About Solar Panels And How To Power DIY Projects With Them

*Solar energy* can conveniently power devices and supply endless energy, i.e. for remotely located sensors. It can also charge a powerbank or your smartphone while on a mountain trip.

In this section, I am discussing components required to harvest energy from sunshine, how to store harvested energy, and how to re-supply it in a usable form.

Three fundamental parts are required for a *DIY solar power supply*:




## Solar Panel

*Solar panels* convert *light* into *electrical power*. The generated power is in direct correlation to the light intensity. *Solar panels* by themselves cannot be used as reliable power source as *current* and *voltage* may vary greatly.

## Charger

*Chargers* are common place and not restricted to *solar applications*: they take a wide range of input voltage and deliver a fixed output voltage, plus they incorporate *security mechanisms* to protect batteries from *overcharging* and *under-voltage*.

A ***solar** charger* is a slightly misleading term that can represent different things:

* **Charger module with MPPT functionality:** a regular charger with an additional optimization to take advantage of the *sweet spot* where solar panels provide the highest efficiency. This is achieved by controlling the *current* that the charger draws from the *solar panel*.
* **Ready-to-use Solar Charger:** a *solar panel* with integrated circuitry to convert the fluctuating voltage from a *solar panel* to a useful *fixed voltage*, i.e. *5V* for *USB charging*.

> [!NOTE]
> To power simple *DIY projects*, a *regular charger* with an appropriate *input voltage range* is sufficient. Specialized *MPPT* charger modules can be benefitial but extra cost is often much better invested into a larger *solar panel*.

* **Rechargeable Battery:** Since *solar panels* deliver power only when the sun shines, a rechargeable battery acts like a *buffer*: it stores *solar energy* during sunshine and returns the stored energy at other times.

> [!NOTE]
> *Lithium*-based batteries are commonly used in *DIY projects* because of their *energy density*, and because most makers are familiar with them. In commercial devices such as *solar-powered garden lamps* etc., *NiMH* batteries are used. They are cheaper, more forgiving, less dangerous (no risk of fire and explosion), and most importantly have a higher *temperature tolerance*.



* **DC-DC Converter:** Typically, the battery voltage does not match the intended application: it is either too low or too high. *DC-DC converters* change the voltage to the required level. *Boost converter* raise the single-cell voltage to *5V* for *USB Charging*. A *buck converter* lowers the voltage to *3.3V* to power a microcontroller.


> [!NOTE]
> LiFePo4 batteries are perfect for powering *3.3V* microcontrollers: their voltage range matches the voltage range needed. This saves a *DC-DC converter*, and more importantly, it considerably improves *energy efficiency*.


## Voltage and Current

All starts with *voltage* and *current* - and the many ways to *[measure](Measuring%20Current)* and *monitor* both. 

This is the foundation on which tools like *multimeters*, *oscilloscopes* but also devices like *voltage regulators*, *chargers* and *battery protection systems* (BMS) operate.


> Tags: Solar Panel, Charger, DC-DC Converter, Solar Charger, MPPT, Battery


