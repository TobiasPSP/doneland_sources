<img src="/assets/images/sensor3.png" width="100%" height="100%" />
 
# Sensors

> Detecting Environmental Changes And Converting Them To Readable Signals

Sensors detect and respond to input from the *physical environment*, such as light, heat, motion, moisture, pressure, or other entities. The output is an *analog* or *digitally encoded* signal that can be converted to a human-readable display or transmitted for further processing.

## Sensor Breakout Boards

Typically, *sensors* are available separately or on ready-to-use breakout boards. Some sensors provide *analog* output in the form of a *voltage change*. Other sensors provide *digital output*, i.e. via a *I2C* interface. The latter require *microcontrollers* to interpret the digital output.

Breakout boards typically come with all external components required interface with a particular sensor. Such boards can also *protect* sensors that may be sensitive to *input voltage* and can be destroyed when applying voltage outside their specs. A breakout board hosting such a sensor would include a *voltage regulator*. Often, but not always, this allows sensor breakout boards to be operated with a wide range of voltages, making them usable both with *3.3V* and *5V* environments.

## Raw Sensors

At the heart of any sensor breakout board is the actual sensor device. You may use the sensor directly provided you exactly know its requirements, i.e. its minimum and maximum operating voltage.

> [!TIP]
> Some sensors require significant *currents* at regular intervals. Make sure your power supply and voltage regulator can supply the required *current*.

Using a sensor directly without a breakout board can save space and reduce power consumption since you can tailor the circuitry exactly to your needs. It often requires more work and skills than using standard breakout boards.

## Sensor Types
There is an abundance of sensors available. Here is a quick overview of the most commonly used sensor types, plus a few popular models.


- **Accelerometers**: ADXL345
- **CO2 sensors**: SCD-30, MH-Z19, MG-811
- **Flame sensors**: infrared flame sensors
- **Gas sensors**: MQ-2, MQ-135 (for CO2)
- **Gyroscope sensors**: MPU-6050
- **Humidity sensors**: DHT22
- **Light sensors**: LDR, photodiodes
- **Magnetic sensors**: Hall effect sensors
- **Motion sensors**: PIR sensors
- **pH sensors**: pH probes
- **Pressure sensors**: BMP180
- **Proximity sensors**: ultrasonic sensors like HC-SR04
- **Radar sensors**: RCWL-0516
- **Rain sensors**: rain detection modules
- **Soil moisture sensors**: soil hygrometers
- **Sound sensors**: microphones
- **Temperature sensors**: DHT11, DS18B20
- **Tilt sensors**: mercury switches
- **Touch sensors**: capacitive touch sensors
- **Water flow sensors**: YF-S201
- **Water level sensors**: float switches

In the subsections you find additional information on selected sensors.




> Tags: Sensor

[Visit Page on Website](https://done.land/components/sensor?656798061105240606) - created 2024-06-04 - last edited 2024-06-04
