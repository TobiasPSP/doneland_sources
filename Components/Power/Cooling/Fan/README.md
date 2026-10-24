<img src="/assets/images/lightning.png" width="100%" height="100%" />


# Fan

> Active Cooling By Increasing Air Flow

**Fans** are used in power electronics when space constraints, high heat dissipation, or other limitations make sufficient *passive* cooling (Heat Sink) impractical.

## Overview

Fans are essentially small ventilators that move air across heatsinks and heat-generating components. They come in many sizes and shapes. 

Fans improve heat dissipation through forced convection, which can be remarkably effective. Adding a fan to an overheating breakout board can often solve thermal problems, provided the airflow reaches the heat-generating components.


## 2-, 3-, 4-Wire Fans

There are 2-wire, 3-wire, and 4-wire fans. 

Fundamentally, all fans are 2-wire fans but can have extra functionality provided by additional wires:

| Fan Type | Fixed Speed | Variable Speed (`PWM`) |  `TACH` monitoring speed | 
| --- | --- | --- | --- |
| 2-Wire | yes |*(requires external driver)* | - |
| 3-Wire | yes | *(requires external driver)* | yes |
| 4-Wire | yes | yes | yes |

This maps to the fundamental use cases: 

| Usage | Fan | Remarks |
| --- | --- | --- |
| Fixed Speed | 2-Wire | Fan is either on or off |
| Fault Detection | 3-Wire | `TACH` wire delivers pulses proportional to rotational speed for RPM monitoring and fault detection |
| Variable Speed | 4-Wire | External PWM signal (25 kHz typ.) is interpreted by internal fan electronics, internal electronics reduces fan speed while the supply voltage remains constant |


## Fixed vs. Variable Speed

Operating a fan at **fixed speed** is simple: provide power to the fan, and the fan starts and runs at its maximum speed. Fixed speed can come at a cost, though:

* Unnecessary energy consumption
* Noise
* Increased mechanical wear

In noise-sensitive areas - essentially wherever people are present - fans are often operated with **variable speed**. The fan speed is adjusted to the actual cooling requirements by a **temperature-controlled fan driver**.

### Temperature-Controlled Fan Driver

Uses a NTC temperature probe to determine the actual cooling requirements, and outputs a PWM signal. For 4-wire fans with their dedicated PWM input, this is very simple. That's why 4-wire fan controllers are small and affordable.

If you are working with microcontroller boards, then your microcontroller can easily become a 4-wire fan driver. Just output a PWM signal at 25 kHz. Its duty cycle directly controls fan speed.

Technically, the 4-wire fan pulls up its PWM wire, so with 3.3 V MCUs, you must be a bit careful: check the fan's pull-up voltage. If it exceeds your MCU GPIO's maximum permitted voltage, use a small external transistor.



### Extra Requirements for 2-Wire and 3-Wire Fans
For 2- and 3-wire fans, the fan driver is more complex and cannot rely on a PWM signal because a 2- or 3-wire fan has no input for your PWM signal. 

Instead, the only way of varying the fan speed is by **varying the energy** that the fan receives:

* **Raw Averaging:**   
  The PWM signal controls a MOSFET that repeatedly switches the fan's power supply on and off, similar to dimming a LED. This is technically simple and requires only one additional MOSFET.  
  
  Unfortunately though, a fan is no LED, and depending on the fan and PWM frequency, the fan may not start at all, there may be whistling noises, the fan may become unreliable at low RPMs, and the fan may generally experience a reduced service life.   

  So this approach *may* work, but it needs careful investigation.   
* **Voltage Control:**   
  The most universally compatible approach for 2- and 3-wire fans to reduce fan speed is **reducing the supply voltage**.    
  
  Technically, this requires an additional linear regulator, a buck converter, or a PWM power stage with appropriate filtering. It also requires careful configuration: the voltage must remain above the minimum required for reliable operation. Especially the voltage needed to start a stationary fan may be higher than that needed to keep it spinning.   

  The easiest way for this solution is to get a ready-to-use breakout board. Some are available for as little as €2.   


### Summary

If you just want a spinning fan at fixed speed, a 2-wire fan is well suited and cost-effective.

If you want temperature-controlled fan speed, do yourself a favor and get a 4-wire fan. They are more expensive than 2-wire fans but save the money you would otherwise need for a proper external speed controller.

If you must use a 2- or 3-wire fan with variable speeds, get yourself a proper temperature-controlled fan controller breakout board. It is typically much cheaper and simpler to use than trying to add voltage regulation yourself.

## Fan Voltage

DC cooling fans are most commonly available for **5 V** and **12 V** operation. **24 V** is more common in industrial equipment.

### Best Fan Voltage


The best fan voltage depends primarily on (a) available supply rails and (b) fan power consumption.

* **Availability:**  
  For low-power fans, it is often simplest to use an existing supply rail. For example, a small 0.6 W fan can easily be operated from a sufficiently rated 5 V rail already present on a microcontroller board.    
  
  Obviously, the rail must have enough current capacity, including for startup, and the fan must not be powered directly from a GPIO.
* **Power Consumption:**  
  For more powerful fans, a higher supply voltage can reduce the current required to deliver the same power. For example, a beefy 6 W fan draws approximately 1.2 A at 5 V but only 0.5 A at 12 V. If a 12 V rail is available, using a 12 V fan may simplify wiring and reduce distribution losses. A buck converter can then provide lower voltages for other components if needed.

Examples:

| Fan size    | Typical power | 5 V current | 12 V current | 24 V current |
|-------------|---------------|-------------|--------------|--------------|
| 40 × 40 mm  | 0.6–1.5 W     | 120–300 mA  | 50–125 mA    | 25–63 mA     |
| 60 × 60 mm  | 1–2.5 W       | 200–500 mA  | 83–208 mA    | 42–104 mA    |
| 80 × 80 mm  | 1.5–3 W       | 300–600 mA  | 125–250 mA   | 63–125 mA    |
| 92 × 92 mm  | 2–4 W         | 400–800 mA  | 167–333 mA   | 83–167 mA    |
| 120 × 120 mm| 2–6 W         | 400–1200 mA | 167–500 mA   | 83–250 mA    |



## Fan Form Factors

Cooling fans are available in numerous sizes and designs and come in two fundamental designs:

* **Axial:**  
  Air moves parallel to the motor shaft (*the most common type in electronics*).
* **Radial (Blowers):**  
  Draw air in axially and expel it sideways, making them useful for directing airflow through narrow channels or restrictive heatsinks (e.g. *compact cooling systems for Raspberry Pi boards*).

### Dimensions

Most axial fans have square frames. Dimensions are specified by **Frame Width** and **Thickness**. Small fans are often identified by a four-digit designation:

* **2010**: Frame size 20x20 mm, thickness 10 mm.
* **3007**: Frame size 30x30 mm, thickness 7 mm.
* **3010**: Frame size 30x30 mm, thickness 10 mm.
* **4010**: Frame size 40x40 mm, thickness 10 mm.

Larger fans typically use explicit dimensions, e.g. 120x120x25 mm.

## Performance

Important selection criteria include:

* **Airflow (CFM or m³/h)**
* **Static pressure (Pa or mmH₂O)**
* **Noise level (dBA)**
* **Bearing type**

All of these influence fan suitability:

* High-airflow fans are best for unrestricted ventilation, whereas high-static-pressure fans perform better when airflow encounters significant resistance, such as dense heatsink fins or filters.
* High-performance fans with elevated noise levels may be excellent choices for server racks in a basement but unsuitable for equipment operated near people.

### Fan Lifespan

Fan lifespan is commonly specified in operating hours, often ranging from **20,000 to over 100,000 hours**, depending on **bearing** technology, operating temperature, and manufacturer specifications. The **fan bearing** is therefore one of the most important fan specifications that influences lifespan. 

* **Sleeve bearings:**  
  Inexpensive and generally quiet, but often have a shorter lifespan, particularly at elevated temperatures or in mounting orientations that interfere with lubrication.
* **Ball bearings:**  
  Generally offer greater durability, better high-temperature performance, and less sensitivity to mounting orientation, but tend to be more expensive and may produce additional mechanical noise.
* **Fluid Dynamic Bearings (FDB):**  
  Use a hydrodynamic film of lubricant to minimize friction and wear, combining quiet operation with potentially long service life.
* **Magnetic levitation bearings (MagLev):**  
  Use magnetic forces to support or stabilize the rotating assembly, reducing mechanical contact and potentially improving longevity and vibration characteristics. Depending on the design, conventional bearing surfaces may still be present.

For power electronics, where fans may operate continuously at elevated temperatures, ball bearings or high-quality fluid dynamic bearings are often preferable.

For simple DIY projects with moderate temperatures and occasional operation, inexpensive sleeve-bearing fans may be entirely sufficient.

> [!NOTE]
> Of course, operational factors such as Lubrication, temperature, dust, and operating conditions also play significant roles for fan lifespan.   



> Tags: Fan, Cooling Fan, Active Cooling, Forced Convection, Airflow, Static Pressure, Fan Speed, Variable Speed, Fan Controller, PWM, Voltage Control, MOSFET, 2-Wire Fan, 3-Wire Fan, 4-Wire Fan, Tachometer, NTC, Axial Fan, Radial Fan, Blower, Fan Supply Voltage, 5V Fan, 12V Fan, 24V Fan, Fan Bearings, Sleeve Bearing, Ball Bearing, Fluid Dynamic Bearing, Magnetic Levitation, Fan Lifespan

[Visit Page on Website](https://done.land/components/power/cooling/fan?695934101414263449) - created 2026-10-13 - last edited 2026-10-13
