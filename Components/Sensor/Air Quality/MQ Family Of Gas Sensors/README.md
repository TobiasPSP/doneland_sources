<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# MQ Family Of MOS Gas Sensors

> Family Of MOS Gas Sensors For Detection Of Substances In The Air


The *MQ Family Of Gas Sensors* are simple and cheap Chinese-made *MOS Sensors* that can detect different gases in the air. Sensor types (and target gases) depend on the detection material used inside the sensor.



> [!TIP]
> In Chinese, *sensitive* translates to *Mĭngăn* and *Gas to* means *Qǐ lai*. *MQ* seems to have been derived from *sensitive to gas*. Note also that numbering of sensors is not consecutive, so there is neither i.e. a *MQ-1* sensor nor a *MQ-14* sensor.

> [!CAUTION]
> *CO2* is a key substance for determining *air quality*. None of the *MQ* series sensors can detect *CO2*, including *MQ-135* (target gas: *air quality*). Use a dedicated *NDIR CO2 sensor* if you want reliable air quality monitoring.


## Sensor Types
Here is a list of available sensors and their target gases:

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


## Pins
The sensors come with *six pins*:

| Pins | Description |
| --- | --- |
| 2xH | power supply for Nickel-Chromium heater |
| 2xA, 2xB | connected to the sensing element, both *A* and both *B* are interconnected (*analog output*) |

*A* and *B* deliver a *voltage* that corresponds to the concentration of the *target gas(es)*.

### Breakout Boards
*Breakout boards* often combine the sensor with a *potentiometer* and an *OpAmp* to provide an additional *digital output*: via a *potentiometer*, a *threshold voltage* is set, and when the analog sensor output exceeds the *threshold*, a digital output pin goes *high*.

## Caveats
These are *MOS sensors* so they are fairly *unspecific* and cannot be used to reliably detect *one specific gas*. *Humidity* has a significant influence on sensor readings.

All sensors are *5V* devices. 


### High Power Consumption
Since they require a *heater*, their power consumption can be relatively high. Some types require *800mW*. Usage in battery-driven devices is prohibitive for such sensors.

### Warm-Up Time
The *heater* inside the sensor needs to *warm up* before the sensor can work. This takes *20-30s*.

### Burn-In Time
For the sensor readings to stabilize, the sensor must have been operational for more than *24hrs*. In this initial phase, the *heater* might change the chemical structure of the sensing element, causing slight variations in sensor readings.


Technically, you just have to wait *20-30s* for the heater to warm up and can skip the *burn-in time* if it is ok for you that sensor readings may not be as stable within the first *24hrs*.

> [!TIP]
> You **should** perform a *24hrs burn in* if you plan to connect the sensor to a smart system that *calibrates* it: you do not want sensor readings to fluctuate during *calibration*.


> [!NOTE]
> Like most *MOS sensors*, they require an initial burn-in time of at least *24h*.




> Tags: MQ-2, MQ-3, Sensor, Gas, Air, Ethanol, LPG, Alcohol, Propane, Hydrogen, CO, Methane, Flammable

