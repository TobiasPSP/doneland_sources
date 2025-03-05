<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# Temperature Sensors

> Finding The Best Sensor Type For Measuring Temperature

Measuring environmental temperature is essential, not only for building a weather station but also for enhancing the safety and performance of various devices. Temperature monitoring can help ensure safe battery charging or trigger notifications when a power supply reaches dangerously high temperatures.

There are several types of temperature sensors, each utilizing different physical properties to convert temperature into a measurable reading, with variations in temperature range, latency, and control interfaces.

Picking the right sensor type for a given use case is essential.

## Overview
Temperature sensors measure temperature in a number of different ways:

1. **Thermistors (NTC/PTC)**:  
   **Resistance** decreases as temperature rises (NTC) or vice versa (PTC). Their nonlinear behavior requires calibration.  

2. **Thermocouples**:  
   Made of two different metals joined at one end, thermocouples generate a tiny **voltage** based on the temperature difference. This voltage needs to be amplified using specialized circuitry, and cold-junction compensation is required. They can measure very **high temperatures**.  

3. **RTDs (Resistance Temperature Detectors)**:  
   RTDs are highly accurate and stable over a wide temperature range. They use platinum inside, which makes them expensive.  

4. **Semiconductor Temperature Sensors**:  
   Semiconductor material causes a change in voltage or current based on temperature. They are more linear than thermistors and are often used in ICs and with digital interfaces. One example is the popular [Dallas DS18B20](https://done.land/components/data/sensor/temperature/dallas/) sensor.  

| Sensor Type| Temperature Range| Latency| Interface| Voltage Range| Power Consumption (when active) | Cost| Other Characteristics|
|---|---|---|---|---|---|---|---|
| **Thermistors (NTC/PTC)**| -50°C to 150°C (typical)| few milliseconds| Analog| Varies (3-5V)| 1-10mA | Low| Nonlinear response, requires calibration|
| **Thermocouples**| -200°C to 2000°C| tens of milliseconds to seconds| Analog (Voltage output)| Varies (depends on type)| 5-50mA| Medium| High temperature range, needs compensation circuits|
| **RTDs (Resistance Temperature Detectors)**| -200°C to 850°C| few milliseconds| Analog (Resistance measurement)| 3.3V-5V| 1-5mA| High| Highly accurate, stable over time, linear response|
| **Semiconductor Sensors (i.e. Dallas)**| -55°C to 150°C| few milliseconds| Digital (I2C/SPI/[One-Wire](https://done.land/components/data/sensor/temperature/dallas/)/Analog)| 3V to 5V| 1-3mA| Medium| Linear response, easy integration|



> Tags: Thermistor, NTC, PTC, Thermocouple, RTD, Dallas, One-Wire, One Wire

[Visit Page on Website](https://done.land/components/data/sensor/temperature?737512031305251116) - created 2025-03-04 - last edited 2025-03-04
