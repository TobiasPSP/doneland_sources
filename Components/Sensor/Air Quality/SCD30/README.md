<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# Sensirion SCD30

> Swiss I2C NDIS Sensor For CO2, Temperature And Humidity

The SCD30 is a *digital carbon dioxide* (*CO2*), *temperature*, and *humidity sensor* module developed by *Sensirion*, a Swiss sensor manufacturer. 

<img src="images/sensor_scd30_overview_t.png" width="50%" height="50%" />

It provides accurate and reliable measurements of *CO2 concentration*, *temperature*, and *humidity* in indoor air quality monitoring, HVAC systems, and greenhouse monitoring.

It can be interfaced using *I2C* or *Modbus*. A third option - *PWM* for CO2 concentration output - is experimental and may not be functioning yet.

> [!TIP]
> Price variations are huge with this sensor. You can get it from local vendors for as much as EUR 90 (per piece), and from Asian sources for less than EUR 20 (including a base shield with voltage regulator).    




## Overview
The [SCD30](https://sensirion.com/products/catalog/SCD30) sensor module uses *non-dispersive infrared* (*NDIR*) technology to directly and specifically measure CO2 levels.

Since this technology is complex, the board is fairly expensive. Price ranges vary (EUR 90 - EUR 20, depending on source). Using the sensor is simple and straight-forward thanks to its *I2C* interface.

|  Parameter  | Value |
| --- | --- |
| Interfaces | UART, I2C |
| DC supply voltage | 3.3-5V |
| Average Current | 19mA |
| max Current during measurement | 75mA |
| I2C Input High | 1.75 - 3V |
| I2C Input Low | -0.3 - 0.9V |
| Modbus Input High | 1.75 - 5.5V |
| Modbus Input Low | -0.3 - 0.9V |
| Output High | 2.4V |
| Output Low | 0.4V |
| Sensor lifetime | 15 years |
| Operating Conditions | <95%RH, <50C |
| Size | 35x23x7mm |
| Weight | 3.4g |


| CO2 Sensor  | Value |
| --- | --- |
| Range | 0-40.000ppm |
| Accuracy | +- 30ppm + 3% |
| Temperature Stability | +-2.5ppm/C |
| Response Time | 20s |
| Operating Conditions | 0-50C |

| Humidity Sensor | Value |
| --- | --- |
| Range | 0-100% |
| Accuracy | +-2% |
| Response Time | 8s |

| Temperature Sensor | Value |
| --- | --- |
| Range | -40 - +70C |
| Accuracy | +-0.3C |
| Response Time | >2s |

## Base Shield
The *SCD30 sensor module* can be used via its *seven* pins directly. 


A *base shield* exists that comes with a *voltage regulator* and two *JST 1.0 QWIICK* connectors which makes using the expensive sensor easier and safer.

The picture shows the (smaller green) *sensor board* on top, and the (larger pink) *shield board* underneath it. Both are connected via *seven pins*. The *voltage regulator* chip is covered by the mounted *sensor board*


<img src="images/sensor_scd30_sensor_t.png" width="50%" height="50%" />


Companies like *Adafruit* sell [kits](https://www.adafruit.com/product/4867) with *sensor* and *base shield* for around 60 EUR. The combo is available from Asian sources for 20 EUR.


> [!CAUTION]
> The *sensor board* does accept a wide range of *operating voltages* (*3.3-5.5V*) however **the *I2C* interface has a maximum voltage of *3V*** and can easily be operated outside its specifications or even damaged. That's why it is strongly recommended to operate the *sensor board* through the **companion base board** which comes with *voltage regulators* and *level shifters* ensuring the *sensor board* can be safely operated in any *3.3V* and *5V* environment.    







### Base Shield Connections
When using the *base shield*, *labeled solder pins* are provided:

<img src="images/sensor_scd30_pins_t.png" width="50%" height="50%" />

| Pin | Label | Description |
| --- | --- | --- |
| 1 | VIN | 3-5V |
| 2 | 3Vo | 3.3V *output* from internal voltage regulator |
| 3 | GND | Ground |
| 4 | SCL | I2C |
| 5 | SDA | I2C |
| 6 | RDY | *High* when data is ready to be read |


#### Stemma QT / Qwiick / 1.0 JST
On the opposite end, two 4-wire *QWIICK* (*Stemma QT*) connectors allow solder-free connections and *daisy-chaining I2C* devices.

> [!TIP]
> *Qwiick* and *Stemma QT* are just brand names for the same thing: a *JST 1.0 4-wire connector*. You can get cables with  these connectors from various sources for cheap. Note that the kits sold from Asian sources typically do not include these cables.   







<img src="images/sensor_scd30_qwiick_t.png" width="50%" height="50%" />

### Sensor Connections
The *sensor module* has *seven* pins. The pin-out is (from *left* to *right* as depicted):

<img src="images/sensor_scd30_hat_t.png" width="50%" height="50%" />

| Pin Number | Label | Description |
| --- | --- | --- |
| 1 | VDD | Supply voltage |
| 2 | GND | Ground |
| 3 | TX/SCL | Transmission line Modbus/I2C clock |
| 4 | RX/SDA | Receive line Modbus/I2C Data |
| 5 | RDY | Data ready pin, *high* when data is ready to be read |
|6 | PWM | PWM output of CO2 concentration (may not be functional) |
| 7 | SEL | Interface select: connect to *VDD* for *Modbus*, floating or *GND* for *I2C* |



### Materials

[Summary Information](materials/scd30_flyer.pdf)    
[Datasheet](materials/scd30_datasheet.pdf)    
[Interface Description](materials/scd30_interface.pdf)
[Low Power Mode](materials/scd30_lowpowermode.pdf)   
[Adafruit Example](https://learn.adafruit.com/adafruit-scd30/arduino)    


> Tags: CO2, Sensor, Sensirion, SCD30

[Visit Page on Website](https://done.land/components/sensor/airquality/scd30?691722061105240606) - created 2024-06-04 - last edited 2024-06-04
