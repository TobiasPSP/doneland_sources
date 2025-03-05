<img src="/assets/images/air1.png" width="100%" height="100%" />
 
# Dallas One-Wire Temperature Sensor

> Affordable Industrial Temperature Sensors With One-Wire-Bus To Monitor Sensitive Devices And Environments

## Overview
*Dallas* temperature sensors are affordable and simple-to-use temperature sensors that use a *One-Wire-Bus*. Since each sensor has a unique hard-coded ID, any number of sensors can be connected to the same bus for efficient wiring. Only one GPIO is needed for any number of sensors.

<img src="images/dallas_single3_t.png" width="30%" height="30%" />

Dallas sensors cover a wide temperature range suitable for many DIY projects: from monitoring deep freezers (down to -55°C) to safe-guarding power supplies or chargers (up to +125°C).

They are exceptionally energy-efficient, requiring **~1mA** during active measurement (peaking at **1.5mA**). This makes them ideal for **battery-operated** applications or monitoring critical components like power supplies or chargers.

Sensors exist in three-pin TO-92 package as well as in waterproof versions with a steel cap in various sizes and shapes.

<img src="images/dallas_waterproof_t.png" width="50%" height="50%" />



### Digital Sensor

*Dallas* sensors emit a **digital signal**, so a microcontroller is needed to evaluate the sensor output. There are many advantages of digital output:


- **One-Wire Protocol:**  
  *Dallas* temperature sensors use the **One-Wire** protocol, requiring only a **single data line** for communication. Multiple sensors can be operated on the same data line (connected in parallel), as each sensor has a unique **64-bit serial number**.
- **Selectable Resolution:**  
  All models (except *DS18S20*) support **adjustable resolution**. Lower resolutions result in **faster response times**, while higher resolutions improve **accuracy**.

### Latency (Conversion Time)

The conversion time is the time it takes to receive a temperature reading. It varies based on the selected **resolution**:

| Resolution | Conversion Time (Latency) |
|-----------|--------------------------|
| 9-bit     | 94 ms                     |
| 10-bit    | 188 ms                    |
| 11-bit    | 375 ms                    |
| 12-bit    | 750 ms                    |

Depending on use case, you can prioritize accuracy (higher resolution) or fast and speedy response (lower resolution).

## Wiring
Each sensor has three connections:

| Pin | Description | Typical Color |
| --- | --- | --- |
| VCC | *3.0-5.5V* | red |
| GND | Ground | black |
| DATA | digital data line (one-wire protocol) | yellow |

Waterproof steel-embedded sensors are prewired with red, black, and yellow wires. 



<img src="images/dallas_waterproof_wires_t.png" width="50%" height="50%" />

Three-pin *TO-92* packages use the assignment illustrated below (viewed from the *flat* side of the TO-92 package):


<img src="images/dallas_schematic_to92.png" width="50%" height="50%" />

> [!NOTE]
> The picture also illustrates where to place the external pullup resistor. Neither waterproof sensor versions nor TO-92 packages include this pullup resistor.    

There are two connection methods:

| Method | Description |
| --- | --- |
| Normal | Connect **VCC** and **GND** to supply power, and **DATA** to an input GPIO of your microcontroller |
| Parasitic | Just connect **GND** and **DATA**. Do not connect **VCC**. The sensor receives power through **DATA**  |

### Typical Setup
In a typical setup, the dallas sensor is connected to a power source (**VCC** to *3.3V* or *5V*, and **GND** to ground), and the data line is connected to an input GPIO.

In this scenario, you can get away with not using an external pullup resistor when you connect only a single sensor: since the sensor is supplied with power through **VCC**, and since there is not much communication on **DATA**, it may be sufficient to enable the *internal* pullup resistor of your GPIO, or not use any pullup resistor at all.

However, it is strongly recommended to always use a strong external pullup resistor (*4.7kΩ*) for improved reliablity: the pullup resistor makes sure that the *one-wire* bus quickly returns to *high* (the default state). Once you start using multiple sensors on **DATA**, this is important to prevent data faults.

Simple breakout boards exist that include the *4.7kΩ* pullup resistor and a screw terminal for conveniently connecting one or more sensors.


<img src="images/dallas_pcb_top_t.png" width="50%" height="50%" />


### Using Parasitic Mode
Parasitic mode is a way to power the sensor using only *two* wires instead of *three*. In this setup, **VCC** is not connected.

Instead, the sensor now draws its power from the **DATA** line. This works because **DATA** is pulled *high* most of the time, and the sensor can store energy internally to bridge the short periods of time when **DATA** is pulled *low* during communication.

However, parasitic mode absolutely requires a strong external pullup resistor and does not work without it. The pullup resistor is essentially providing the power to all sensors in this scenario.

Since the power that can be supplied in parasitic mode is very limited, this setup can fail and is not as reliable as the typical setup with dedicated **VCC** power supply:

* **Too many sensors:**     
   All sensors take their power from **DATA** which in turn gets its power through the pullup resistor. Too many sensors exceed the power that can be supplied this way. In addition, each sensor uses **DATA** for communication and pulls it *low* frequently. Too many sensors can pull **DATA** *low* so frequently that the *high* phases no longer suffice to supply enough power.
* **Long cables and low temperatures:**      
  Both long cables and operating in low temperature conditions aggrevate the problems and further limit the power that can be supplied through **DATA**.


### 5V or 3.3V?
The sensor can be operated both with *3.3V* and *5V*, so it works well with both *3.3V* and *5V* microcontrollers.

You may want to generally run this sensor with *5V* though, even when using a *3.3V* microcontroller like *ESP32*. Long cables, low temperatures, and/or many sensors can cause voltage drops. Using *5V* provides a much more robust power supply in these cases.

To play safe, when using a *3.3V microcontroller*, add a level shifter to the **DATA** line. Since *ESP32 GPIOs* are generally considered *5V tolerant*, I am connecting **DATA** directly to ESP32 GPIOs, and am not using a level shifter or resistor. So far this has worked beautifully. However, do this entirely at your own risk.

## Sensor ID
Each *Dallas* sensor has a unique internal 64-bit ID number (address). This ensures that you can operate multiple sensors on the same **DATA** line and still address each sensor individually.

When using a *single Dallas sensor*, this internal address is not needed. After all, you are dealing with just one sensor, so the first (and only) sensor discovered is the one you want to communicate with.

Once you use *more than one* sensor on the same **DATA** line, the sensor ID number becomes mandatory: you **must** specify it to address the correct sensor.

### Finding Sensor ID
Unfortunately, the sensor ID is not visibly printed onto the sensor. You need to let your microcontroller scan for the sensor and log the sensor IDs it finds. 

*ESPHome* [supports](https://esphome.io/components/sensor/dallas_temp.html) *Dallas* sensors out of the box, and you find the sensor ids of all connected *Dallas* sensors in the microcontroller log:


<img src="images/dallas_esphome_logger.png" width="100%" height="100%" />

In the pictured example, a single *Dallas sensor* was connected and reported this 64-bit ID: `0xfb000000856e7928`.

Sensor IDs can then be used in your configuration to address each sensor individually.


### Dallas Sensor Tester (ESPHome)
You can create a simple *Sensor Tester* where you connect a single Dallas sensor and an OLED display. The tester then displays the sensor ID and the current temperature reading on the OLED display. That's a convenient tool when you need to work with multiple *Dallas* sensors, or would like to diagnose individual sensors.


<img src="images/dallas_tester_esp32-c3_t.png" width="80%" height="80%" />

Below *ESPHome configuration* was created for [ESP32-C3 SuperMini](https://done.land/components/microcontroller/families/esp/esp32/developmentboards/esp32-c3/c3supermini/). You can easily adjust the GPIOs to match any other development board. 

````
# GPIO   Usage
# =======================================
#  1     SDA I2C
#  3     SCL I2C
#  0     Dallas Sensor Input

one_wire:
  - platform: gpio
    pin: GPIO0
    id: one_wire_bus

sensor:
  - platform: dallas_temp
    one_wire_id: one_wire_bus
    name: "Dallas Sensor"
    id: dallas_sensor
    update_interval: 1s

# Enable I2C for OLED Display
i2c:
  sda: GPIO1
  scl: GPIO3
  scan: true  

# Configure the OLED Display
display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    update_interval: 1s
    lambda: |-
      int y_offset = 0;

      it.printf(0, y_offset, id(lato_12), "%.1f°C", id(dallas_sensor).state);
      y_offset += 14;

      // Get the sensor's unique address and display it
      std::string address = id(dallas_sensor).get_address_name();  // Retrieve the unique ID of the sensor
      it.printf(0, y_offset, id(lato_12), "%s", address.c_str());
      y_offset += 14;

# Load Google Font (Lato)
font:
  - file: "gfonts://Lato"
    id: lato_12
    size: 12
````

> [!IMPORTANT]
> *ESPHome* recently has [fundamentally changed](https://esphome.io/components/sensor/dallas_temp.html) the way how it supports *Dallas* sensors. This was due to an effort to abstract its underlying *One-Wire* protocol and make it accessible to other sensors as well. Since this change is a *breaking change*, older configuration examples may not work any longer or need adjustments.




Without specifying the *Dallas* internal ID, *ESPHome* can only work with a **single** sensor. Once you want to work with more than one sensor, **you must** specify the internal sensor IDs in your configuration.

That's why in *ESPHome*, you can only create testers that support a *single* device under test. Once the OLED screen displays the found sensor ID, you can add it to your *ESPHome configuration*.




## Sensor Models
The most popular and dominant *Dallas* sensor model is the **DS18B20**, but other models exist.


| Model       | Temp Range     | Special Features                        | Remarks                                      |
|------------|---------------|-----------------------------------------|----------------------------------------------|
| **DS18B20** | -55°C to +125°C | Waterproof version available, long cable support | Most popular model for DIY and industrial use |
| **DS18S20** | -55°C to +125°C | Fixed 9-bit resolution, slow conversion time | Less commonly used due to high latency |
| **DS1822**  | -55°C to +125°C | Minor internal differences from DS18B20 | Can be an alternative to DS18B20 |
| **DS28EA00** | -40°C to +85°C  | Tamper detection, GPIO support | Used in security, asset tracking, and authentication |

### Caveat: DS18S20
The *DS18S20* is a **low-cost** model with **reduced accuracy and speed**. It only supports **9-bit resolution**, but **does not benefit from the faster 9-bit mode** of other models.

- Unlike other Dallas sensors, the *DS18S20* takes **750ms per reading**, even though its output is limited to **9-bit resolution**.
- Internally, it applies **linear interpolation** to estimate **higher precision**, but it does not actually operate at 12-bit resolution.
- This means the *DS18S20* has **both lower accuracy and higher latency** compared to the *DS18B20*.

## Package Types

Dallas temperature sensors are available in multiple **form factors** to suit different applications. These form factors determine mounting options, durability, and environmental resistance.

## Common Packages

| Package   | Description | Advantages | Common Models |
|--------------|------------|------------|--------------|
| **TO-92**    | Small, three-pin plastic package, similar to a transistor | Compact, inexpensive, easy to integrate into PCBs and breadboards | DS18B20, DS18S20, DS1822 |
| **Stainless Steel Probe** | Waterproof enclosure with pre-attached cable | for outdoor, liquid, and industrial applications | DS18B20 |


### TO-92 
Cost-effective, especially for monitoring the temperature of electronic devices. However, the plastic casing has poor thermal conductivity, so proper placement is crucial.

Use thermal paste or epoxy if mounting on a heat sink or metal surface. Use thermal adhesive tape to fix it to a chassis or PCB.
 
- **Looks Like:** Small black transistor (similar to a 2N2222)
- **Size:** ~4.7mm x 4.0mm x 5.0mm (excluding leads)
- **Disadvantages:** 
  - limited heat dissipation
  - requires external protection if used in harsh environments


### Stainless Steel Probe (Waterproof)
Ensures efficient heat transfer and is ideal for harsh environments.

- **Looks Like:** A sealed metal cylinder with a cable
- **Typical Sizes:** 6mm diameter, 30-50mm length
- **Caveats:** 
  - cannot be directly mounted to a PCB
  - may be overkill (i.e. inside a device enclosure)



> Tags: One-Wire, One Wire, DS18B20, DS18S20, DS1822, DS28EA00
