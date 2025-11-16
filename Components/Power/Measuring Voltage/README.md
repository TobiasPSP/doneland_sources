<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Measuring Voltage 

> Measuring Voltage and Power Consumption 

**Voltage** is measured in *volts* (**V**) and represents the **electrical potential difference** that pushes electrons through a circuit.  

Unlike *electrical current* ([measured](https://done.land/components/power/measuringcurrent/) in *amperes*, **A**), higher voltage doesn’t require thicker wires — it allows more energy to be transferred without increasing the current. 

However, higher voltages demand better insulation, since stronger electric fields can overcome the insulating properties of materials (including human skin). Voltages above roughly **40 V** can penetrate healthy human skin and drive potentially dangerous currents through the body.  

Together, *voltage* and *current* determine the total electrical **power** (measured in *watts*, **W**).  

## Overview


Voltmeters, analog input pins on microcontrollers, and voltage dividers consisting of two series resistors all have one thing in common: a **high internal resistance**. 


This is crucial because voltage is measured by connecting the measuring device **in parallel**, so effectively like a **short circuit**. If the voltage measuring device would have a low resistance, it would indeed shorten the circuit.


## Use Cases

Measuring voltage is important for many reasons, including:  

* **Total Power Consumption / Battery Testing:**  
  When you also measure the *current*, you can calculate the **power** (in watts) and total **energy** consumed or stored. This enables power consumption analysis and battery capacity testing.  

* **Voltage Drop (Measuring Current Indirectly):**  
  By placing a known, low-value resistor (called [Shunt](https://done.land/components/power/measuringcurrent/viashunt/)) in series with a load, you can measure the *voltage drop* across it. Using *Ohm’s law* ( I = V/R ), this voltage drop reveals the current flowing through the circuit. This is the most common method for current measurement.

* **Battery Health Monitoring:**  
  Measuring the voltage of a battery or cell gives a quick indication of its **state of charge (SOC)** and health. A significantly reduced voltage under load can also signal internal resistance or degradation.

* **Power Supply Verification:**  
  In electronics projects, checking the voltage from regulators or USB ports ensures that microcontrollers, sensors, and displays receive stable and correct supply voltages.

* **Sensor Signal Reading:**  
  Many analog sensors (like temperature, light, or pressure sensors) output a voltage proportional to the measured quantity. Measuring that voltage allows a microcontroller to determine the sensor’s reading.

* **Detecting Faults or Loose Connections:**  
  Measuring voltage along a circuit can help locate **voltage drops** caused by high-resistance connectors, corroded terminals, or damaged cables.

* **Charging Systems and Solar Monitoring:**  
  In solar, automotive, or renewable energy systems, measuring voltage helps track **charging performance**, **panel output**, and **battery charging states**.

* **Safety Checks:**  
  Measuring voltage between conductive parts or to ground can verify that equipment is properly **isolated**, and detect potentially dangerous **leakage voltages** before handling.


Both *voltage* and *current* are ultimately measured as *voltages*: even an *ammeter* internally measures a voltage across a known resistance. So let’s first look at how voltage measurement works.  


## Analog Voltmeters

Classic analog voltmeters use a moving coil or iron element that responds to the *magnetic field* created by the current flowing through it. The deflection of the pointer is proportional to this current, and since the meter’s internal resistance is known, the current — and therefore the pointer’s position — is proportional to the *voltage* being measured.

**Example:**  
* **5 V:** With an internal resistance of *500 Ω*, *Ohm’s law* gives *I = U/R = 5 V / 500 Ω = 10 mA*. The resulting magnetic field deflects the pointer to indicate 5 V.  
* **10 V:** Doubling the voltage to *10 V* doubles the current to *20 mA*, producing twice the magnetic field strength and deflecting the pointer twice as far.  



## Digital Voltmeters

These are by far the most common tools: a *DMM* (*digital multimeter*) is a portable measuring device that measures *voltage* and *current*, so they are typically both a *voltmeter* and a *ammeter*.

### Analog-to-Digital Converter (ADC)
*Digital* voltmeters include an **ADC** (*Analog-to-Digital Converter*) that converts the analog voltage into a digital signal for display. When you use a microcontroller’s analog input pin to read voltage, you are effectively building a simple *digital voltmeter*.

### Using Microcontrollers
Microcontrollers like [Arduino](https://done.land/components/microcontroller/families/arduino/) or [ESP32](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/), cann too use an *ADC* to measure voltage. Often, microcontrollers come with integrated *ADCs*, or one can be added (like *ADS1115*).

This turns a microcontroller in a *digital voltmeter*, too - with the added benefit that your microcontroller can be programmed to automate tasks such as battery testing, or evaluating sensor input.


#### Connecting Voltage to ADC
To measure a voltage, connect an analog input pin of a microcontroller to the voltage source — but ensure the voltage stays within the pin’s safe range.  
- Most **Arduino** boards can handle **0–5 V** on analog inputs.  
- **ESP32** and **ESP8266** typically accept **0–3.3 V**, though some boards include internal dividers that allow higher input ranges.  


#### Adjust Input Voltage Range
If you need to measure higher voltages, use a *voltage divider* made from two high-value resistors. This divides the input voltage so that the analog pin only sees a safe fraction of the total. The actual voltage can then be calculated in software from the measured value.  

**Example:**  
Suppose you want to measure up to **12 V** with an ESP32 (max 3.3 V input). 

If you use a **voltage divider** with R1 = 30 kΩ and R2 = 10 kΩ:  

*Vout = Vin * ( (R2) / (R1 + R2))*    
*Vout = 12V * ( (10 kΩ) / (10 kΩ + 30 kΩ))*
*Vout = 12V * (1/4)*     
*Vout = **3V***    


That’s safely within range, and you can multiply the ADC reading by **4** in software to get the real voltage.  
 


### Tips for Accurate Voltage Measurement

* **Use high-value resistors** (10 kΩ–100 kΩ) in your divider to reduce power loss, but not so high that input noise or ADC leakage current becomes significant.  
* **Keep wires short and connections tight** to avoid noise pickup, especially when measuring millivolts or microvolts.  
* **Calibrate** your ADC or voltmeter using a known voltage reference for precise readings.  
* **Add a capacitor** (e.g. 0.1 µF–1 µF) between the ADC input and ground to smooth out fluctuations and noise.  
* **Avoid floating inputs** — always connect the ground of your measuring device and the circuit being measured.  
* **Use differential measurement** (if available) to measure voltage between two arbitrary points, not just relative to ground.  


### Typical Voltage Ranges in Practice

| Application | Typical Voltage | Notes |
|--------------|-----------------|-------|
| USB devices | 5 V | Standard for many microcontrollers and sensors |
| Li-ion / LiPo cells | 3.0–4.2 V | Varies with charge level |
| LiFePO₄ cells | 2.5–3.6 V | Stable chemistry, lower voltage |
| Automotive 12 V system | 11–14.4 V | Higher during charging |
| Solar panels | 18–40 V | Depends on configuration |
| Mains voltage (AC) | 110 V / 230 V | **Never measure directly with a microcontroller!** Use isolation and proper sensors. |




## Safety Notes

* Never connect high voltages (above 40 V DC or 25 V AC) directly to a microcontroller — use an isolated **voltage sensor module** or **optocoupler**.  
* Always verify the **ground reference** before connecting instruments to avoid short circuits.  
* When measuring mains or high-voltage circuits, use **CAT-rated** multimeters and **one-hand technique** to reduce shock risk.  

With these basics, you can safely and accurately measure voltage in everything from microcontroller projects to large power systems.


> Tags: Measure, Power Consumption, Voltmeter

[Visit Page on Website](https://done.land/components/power/measuringvoltage?898210111716250302) - created 2025-11-15 - last edited 2025-11-15
