<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# Temperature Sensors

> Measuring Temperature

Measuring the environmental temperature is not just important when you plan to build a whether station. Temperature monitoring can be a valuable add-on for many devices, i.e. to safely charge batteries, or to get a notification when your power supply gets too hot.

There are a number of sensor types for measuring temperature. They differ in temperature range, latency, and control interface.

## Overview
Temperature sensors measure temperature and come in various types, each with unique characteristics and applications. Here's a quick summary of the most common types:

1. **Thermistors (NTC/PTC)**:    
  These are resistive temperature sensors. NTC thermistors decrease in resistance as temperature rises, while PTC thermistors increase. They're sensitive and accurate in a limited temperature range but have nonlinear behavior, requiring calibration.

2. **Thermocouples**:     
  Made of two different metals joined at one end, thermocouples generate a voltage based on the temperature difference. They're widely used for high-temperature measurements and offer a broad range of temperatures but require complex circuitry for accurate readings.

3. **RTDs (Resistance Temperature Detectors)**:     
  These are also resistive sensors, usually made from platinum. RTDs are highly accurate and stable over a wide temperature range, making them ideal for industrial applications, but they tend to be more expensive.

4. **Semiconductor Temperature Sensors**:     
  These sensors use a semiconductor material to measure temperature based on the change in voltage or current. They're often used in integrated circuits and are more linear than thermistors.

5. **Dallas/One-Wire Sensors (e.g., DS18B20)**:     
  These digital temperature sensors use the One-Wire protocol to communicate with microcontrollers. They are easy to use, accurate, and can be chained together on the same data line, making them ideal for projects requiring multiple sensors.

Each type has specific advantages depending on the required temperature range, accuracy, and ease of use.

| Sensor Type| Temperature Range| Latency| Interface| Voltage Range| Power Consumption (when active) | Cost| Other Characteristics|
|---|---|---|---|---|---|---|---|
| **Thermistors (NTC/PTC)**| -50°C to 150°C (typical)| few milliseconds| Analog| Varies (3-5V)| 1-10mA | Low| Nonlinear response, requires calibration|
| **Thermocouples**| -200°C to 2000°C|  tens of milliseconds to seconds | Analog (Voltage output) | Varies (depends on type) | 5-50mA| Medium| High temperature range, needs compensation circuits |
| **RTDs (Resistance Temperature Detectors)** | -200°C to 850°C| few milliseconds| Analog (Resistance measurement) | 3.3V-5V| 1-5mA| High| Highly accurate, stable over time, linear response |
| **Semiconductor Sensors**| -55°C to 150°C| few milliseconds| Digital (I2C/SPI/Analog) | 2.7V to 5.5V| 1-3mA| Medium| Linear response, easy integration, available in IC form |
| **Dallas/One-Wire Sensors**| -55°C to 125°C| few milliseconds| Digital (One-Wire)| 3V to 5.5V| 1-2mA | Low| Can chain multiple sensors, easy to use with microcontrollers |



> Tags: Thermistor, NTC, PTC, Thermocouple, RTD, Dallas, One-Wire, One Wire
