<img src="/assets/images/lightning.png" width="100%" height="100%" />

# Measuring Voltage 

> Measuring Voltage and Power Consumption 

**Voltage** is measured in *volts* (**V**) and represents the **electrical potential difference** that pushes electrons through a circuit.  

Unlike *electrical current* (measured in *amperes*, **A**), higher voltage doesn’t require thicker wires — it allows more energy to be transferred without increasing the current. However, higher voltages demand better insulation, since stronger electric fields can overcome the insulating properties of materials (including human skin). Voltages above roughly **40 V** can penetrate healthy human skin and drive potentially dangerous currents through the body.  

Together, *voltage* and *current* determine the total electrical **power** (measured in *watts*, **W**).  


## Use Cases

Measuring voltage is important for many reasons, including:  

## Use Cases

Measuring voltage is important for many reasons, including:  

* **Total Power Consumption / Battery Testing:**  
  When you also measure the *current*, you can calculate the **power** (in watts) and total **energy** consumed or stored. This enables power consumption analysis and battery capacity testing.  

* **Voltage Drop (Measuring Current Indirectly):**  
  By placing a known, low-value resistor (*shunt resistor*) in series with a load, you can measure the *voltage drop* across it. Using *Ohm’s law* ( I = V/R ), this voltage drop reveals the current flowing through the circuit. This is the most common method for current measurement.

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


## Measuring Voltage

Both *voltage* and *current* are ultimately measured as *voltages*: even an *ammeter* internally measures a voltage across a known resistance. So let’s first look at how voltage measurement works.  

To measure a voltage, connect an analog input pin of a microcontroller to the voltage source — but ensure the voltage stays within the pin’s safe range.  

If you need to measure higher voltages, use a *voltage divider* made from two high-value resistors. This divides the input voltage so that the analog pin only sees a safe fraction of the total. The actual voltage can then be calculated in software from the measured value.  

Voltmeters, analog input pins, and voltage dividers all have a **high internal resistance**. This is crucial because connecting a voltmeter in parallel effectively bridges the circuit; high resistance ensures that only a tiny, negligible current flows and that the measurement doesn’t disturb the circuit.

---

### Analog Voltmeters

Classic analog voltmeters use a moving coil or iron element that responds to the *magnetic field* created by the current flowing through it. The deflection of the pointer is proportional to this current, and since the meter’s internal resistance is known, the current — and therefore the pointer’s position — is proportional to the *voltage* being measured.

**Example:**  
* **5 V:** With an internal resistance of *500 Ω*, *Ohm’s law* gives *I = U/R = 5 V / 500 Ω = 10 mA*. The resulting magnetic field deflects the pointer to indicate 5 V.  
* **10 V:** Doubling the voltage to *10 V* doubles the current to *20 mA*, producing twice the magnetic field strength and deflecting the pointer twice as far.  

---

### Digital Voltmeters

*Digital* voltmeters include an **ADC** (*Analog-to-Digital Converter*) that converts the analog voltage into a digital signal for display. When you use a microcontroller’s analog input pin to read voltage, you are effectively building a simple *digital voltmeter*.

> Tags: Measure, Power Consumption, Voltmeter
