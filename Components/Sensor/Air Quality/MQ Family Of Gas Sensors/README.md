<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# MQ Family Of MOS Gas Sensors

> Family Of MOS Gas Sensors For Detection Of Substances In The Air


The *MQ Family Of Gas Sensors* are simple and cheap Chinese-made *MOS Sensors* that can detect different gases in the air. Sensor types (and target gases) depend on the detection material used inside the sensor.


<img src="images/mq_sensors_overview_t.png" width="100%" height="100%" />


> [!TIP]
> In Chinese, *"gas sensitive"* translates to *"**Q**ì **M**ǐn"* (*气敏*). *MQ* might have been derived from the Chinese words *"gas sensitive"*. Note also that numbering of sensors is not consecutive, so there is neither i.e. a *MQ-1* sensor nor a *MQ-14* sensor.




> [!CAUTION]
> *CO2* is a key substance for determining *air quality*. None of the *MQ* series sensors can detect *CO2*, including *MQ-135* (target gas: *air quality*). Use a dedicated *NDIR CO2 sensor* if you want reliable air quality monitoring.


## Overview
The *MQ* series of gas sensors are *MOS* sensors (*metal-oxide semiconductors*): they detect specific gases by changing their electrical resistance in response to the presence of these gases.


<details><summary>How do these sensors detect gases?</summary><br/>


The core of the sensor is a ceramic substrate coated with a thin layer of metal oxide as primary sensing element.

Each sensor type uses a different *metal oxide* which determines the *target gases* and *sensitivities*.

* In clean air, the metal oxide layer has a  baseline resistance. 
* The metal oxide surface causes target gases to undergo *oxidation* or *reduction* reactions which changes the number of free electrons in the metal oxide, thereby changing its resistance proportionally to the concentration of the target gas.
* The *sensor resistance* (as an indicator of gas concentration) is converted into a *voltage change* through a *voltage divider* with one known fixed *resistor* and outputted as *voltage*.


</details>

<details><summary>How do sensors differ, and how come they detect different gases?</summary><br/>

Different *MQ sensor types* exist with different detectable *target gases*:

| Sensor Type | Target Gas | Detection Range (ppm) |
| --- | --- | --- | 
| MQ-2 | propane, smoke, natural gas (flammable gases and smoke) | 10-10.000 | 
| MQ-3 | ethanol | 20-500   |
| MQ-4 | methane, natural gas (flammable gas) | 300-10.000  | 
| MQ-5 | propane, methane, LPG (combustible gas) | 300-10.000   |
| MQ-6 | LPG, CH4 (flammable gas) | 300-10.000 |
| MQ-7 | carbon monoxide | 10-500  |
| MQ-8 | H2 (hydrogen) | 100-1.000 |
| MQ-9 | CO (carbon monoxide), CH4 | CO: 10-500, CH4: 300-10.000 |
| MQ-131 | ozone | 10-1.000 |
| MQ-135 | ammonia, sulfide, benzene (air quality) |  10-1.000   | 
| MQ-136 | hydrogen sulfide (toxic gases) | 1-200 |
| MQ-137 | ammonia (toxic gases) | 5-500 |
| MQ-138 | organic vapors | 5-500 |
| MQ-139 | freon halogen | 10-1.000 |

> [!NOTE]
> Most types are cheap and cost between €1-2. Some models (i.e. MQ-131 and all above MQ-136ff) can be more costly.

### Metal Oxides Used In Sensors
While the general sensor design is identical in all sensor types, it is the actual *composition* of the *metal oxide* used in the sensing element that determines the *target gases* that a particular sensor can detect.

#### Core Metal Oxide
Most sensors use one of these two metal oxides to start with:

| Metal Oxide | Target Gases | Used in |
| --- | --- | --- |
| Tin Dioxide (SnO2) | flammable gases, alcohol, *air quality*-related gases | MQ-2, MQ-3, MQ-4, and MQ-135 |
| Iron Oxide (Fe2O3) | flammable gases, carbon monoxide (CO) | MQ-7, MQ-9 |

#### Doping
These metal oxides are then *doped* with additional materials to *enhance sensitivity* to specific gases.

The exact doping elements and their concentrations are usually proprietary information held by the manufacturer, but common dopants can include elements like *palladium (Pd)* or *platinum (Pt)* to improve response characteristics.

#### Stability
As a final step, the doped metal oxide is then mixed with *Aluminum Oxide (Al2O3)* which in itself is not active but is used to increase mechanical strength and surface area.


</details>

## Sensor Component

Each sensor (regardless of type) has *six pins*. Underneath the metal mesh that protects the sensor and prevents *explosion hazards* (due to the internal *heater*), the six pins and their purpose becomes evident:

<img src="images/mq_sensor_internal_t.png" width="60%" height="60%" />

### Analog Sensor Output
The *sensor element* is coated with metal (the actual metal *type* varies among sensor types and determines the detectable target gases as outlined above). It is connected on one side to both **A** pins, and on the other side to both **B** pins.

The *sensor element* acts like a *variable resistor* and its *resistance* varies based on the gas concentrations it can detect. To convert its *resistance* into a *measurable voltage (**AO**)*, a *load resistor* is used that acts as a simple voltage divider.

> [!IMPORTANT]
> The *load resistor* is not part of the sensor and is provided by *breakout boards*. If you want to use a *raw sensor*, add an appropriate *load resistor* to your circuitry yourself.

The actual load resistor *value* is typically chosen based on the expected range of gas concentrations and the sensor's resistance range (see datasheet for particular resistor type).

> [!TIP]
> *MQ-xxx breakout boards* are designed to be used with *5V microcontrollers*. If you want to use them with *3.3V*, either add your own *voltage divider* to further reduce *AO*, or *replace* the *load resistor* on the *breakout board* against a *higher value resistor*. 

### Heater
For the *detectable chemical reaction to take place*, a *heater element* is connected to both **H** pins that can be used interchangeably (in fact you could apply *AC* to the *heater circuit*).


<details><summary>How much current does the heater require?</summary><br/>

The *heaters resistance* determines the *current* that flows through it. 

A *MQ-135 sensor* i.e. has a *heater resistance* of *34 ohms* which at *5V* results in a *heating current* of *5V/34ohms* = *0.15A* (*5V*x*0.15A* = *0.75W*).


> [!NOTE]
> In the raw *sensor*, both *heating circuit* and *sensing circuit* are completely separated. The *heating circuit* must be operated with strictly *5V AC or DC* while the *sensor circuit* can theoretically be operated with up to *24V DC*. Breakout boards supply *5V DC* to both circuits.




</details>


## Breakout Boards
Often, the *MQ sensors* come pre-mounted on a supporting *breakout board*. All sensor types use the same fundamental *breakout board design*.

The *breakout board* adds the *essential load resistor*.

> [!NOTE]
> Depending on *sensor type*, the values for the *load resistor* vary.

### Digital Alarm Functionality
*Breakout boards* complement the *analog* sensor output (**AO**) with an additional *digital alarm output (**DO**)* that triggers when a setable *threshold* is exceeded:

Via a *potentiometer*, a *threshold voltage* is set, and when the analog sensor output exceeds this *threshold*, an *OpAmp* switches the digital output pin (**DO**) from *low* to *high*.


<img src="images/mq137_bottom_t.png" width="40%" height="40%" />

The *schematic* of the base *breakout board* illustrates its functionality:

<img src="images/schematic_mq_sensor_breakoutboard.png" width="100%" height="100%" />

* **Sensor/Pin AO:** the *sensor* pins *A* and *B* are connected to *VCC* and *AO*, directly providing the *analog sensor output*. This output is the *voltage drop* across a *voltage divider*, consisting of the *sensor resistance* (which varies with gas concentrations), and a *fixed resistor*.
* **Heater:** the sensor component internally uses a *NiCd heater* that is connected to *VCC* and *GND*. An additional *resistor* may limit the *heater current*. 
* **Alarm/Pin DO:** A *potentiometer* is used as a *voltage divider* to manually define a *reference voltage* that is fed into an *OpAmp*. The *OpAmp* compares this reference voltage to the actual *sensor voltage* (*AO*). When the *sensor voltage **exceeds*** the *reference voltage*, the *OpAmp* sets *D0* to *high* and  turns on the *LED* on the board.


## Caveats
Like all *MOS* sensors, they are fairly *unspecific* and sensitive to a range of *target gases*.

### Interference

The chemical reaction responsible for changing the *sensor resistance* (and thus its output) is susceptible to many unspecific environmental factors, such as *temperature* and *humidity*: 

*High* humidity causes over-shooting readings whereas *extremely low* humidity causes the sensor to stop working.


### High Power Consumption
The *heater* requires relatively high *current* (depending on sensor type) which makes using these sensors in battery-powered devices difficult.

### Warm-Up Time
The *heater* needs to *warm up* and bring the sensor to *operational temperatures* before it can work. Warming up takes *30s*.

For the same reason, usual *energy savings procedures* such as taking readings in intervals does not work well. For example, taking a reading every minute would require the sensor to *pre-heat* for *30s* each time.

### Burn-In Time
Since the sensor principle is based on a *chemical reaction*, the *metal oxid layer* inside the sensor requires an initial *burn in time* of *48h* (exact time depends on sensor type, see datasheet):

The sensor heater needs to run uninterrupted for *48h* so that coatings and chemical residues can settle. The sensor should be *calibrated* only after the *burn in* time during which the sensor readings have not stabilized yet.

That said, you may want to skip *burn in time* and immediately start using the sensor if you do not require *calibration* and *precise results* and just want to use the sensor to provide a *general tendency*.




> Tags: MQ-2, MQ-3, Sensor, Gas, Air, Ethanol, LPG, Alcohol, Propane, Hydrogen, CO, Methane, Flammable

[Visit Page on Website](https://done.land/components/sensor/airquality/mqfamilyofgassensors?695106071217240231) - created 2024-07-16 - last edited 2024-07-16
