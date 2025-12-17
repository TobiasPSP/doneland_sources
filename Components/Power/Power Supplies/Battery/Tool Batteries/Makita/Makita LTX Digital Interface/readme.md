<img src="/assets/images/lightning.png" width="100%" height="100%" />


# Makita LTX Digital Interface


> Understanding The Proprietary Makita LTX Digital Service Interface

Makita LTX batteries (18V tool batteries) use a proprietary digital one-wire interface that can be used to query battery details, determine battery health, and even unlock previously locked batteries.

<img src="images/makita_ltx_side_t.webp" width="50%" height="50%" />

The interface is accessible via the yellow extra connector on the battery. 

## Overview

The digital interface in Makita LTX batteries is proprietary, and no official documentation exists. Genuine Makita chargers like the [DC18RC](https://www.makitatools.com/products/details/DC18RC) and official diagnostic tools like the [BTC04](https://www.youtube.com/watch?v=uumwieLu8CE) utilize this interface.


<img src="images/makita_obi_battconn_t.webp" width="50%" height="50%" />


The community has managed to reverse-engineer this interface, and there are already projects that illustrate how to build diagnostic tools for just a few bucks in material.



<details><summary>Community Achievements</summary><br/>

Here is a quick history about the persons and projects involved in reverse-engineering the Makita LTX 1-Wire protocol:

* [2021: Battery Hacking by Martin Jansson](https://martinjansson.netlify.app/posts/makita-battery-post-1): Martin Jansson is the key person in reverse-engineering the interface. In 2021, he started seriously reverse-engineering the protocol.
* [2024: Uncovering Command Set by Martin Jansson](https://martinjansson.netlify.app/posts/makita-battery-post-1): Three years later, Martin Jansson managed to extract the original firmware and found the key commands that can be sent to the digital interface.
* [2024: Open Battery Information by Martin Jansson](https://github.com/mnh-jansson/open-battery-information): Martin Jansson then developed an Arduino-based "Dongle" and a Python-based software to easily communicate with Makita LTX batteries. 

  <img src="images/obi_application_bl1860B.webp" width="50%" height="50%" />

* [2025: Building your own Makita Diagnostic Tool](https://www.youtube.com/watch?v=kUg9jWvf5FM): the YouTube channel [Well Dine Tips](https://www.youtube.com/@welldonetips) walks you through building your own Makita diagnostic tool, essentially using the resources from [Open Battery Information](https://github.com/mnh-jansson/open-battery-information), inexpensive resources (Arduino Nano Clone, Makita connector), and adds a [3D printable adapter case](https://shorturl.at/W719g).

* [2025: Stand-alone ESP32 solution with web interface](https://github.com/Belik1982/esp32-makita-bms-reader): at the end of 2025, Belik1982 published a derived project that ports the code from Arduino to the much more capable ESP32 microcontroller that can act as a web server and displays all settings on i.e. a smartphone. This solved many issues with the original solution that required a PC to actually display information. In addition, this project provides even more battery details than the original work.

</details>

## Protocol Overview

Makita LTX batteries use a 1-wire interface that is accessible through the yellow 7-pin connector. You source connector cables at places like [AliExpress](https://www.google.com/search?q=aliexpress+makita+charger+connector).

<img src="images/makita_obi_cable_t.webp" width="50%" height="50%" />

Only two pins are required for the digital interface (the second pin from each side):

* **1-Wire:**    
  Serves as the communication pin and needs to be pulled up by an external 4.7 kΩ resistor.
* **Enable (active high):**    
  must be pulled high via 4.7 kΩ resistor to activate the 1‑wire interface. 

<img src="images/makita_ltx_plug_connector.webp" width="50%" height="50%" />

* **Connector:**     
  Typically when you order the connectors, only six pins are connected. One pin is not connected. The pin next to the unconnected pin is **Enable**, and the *second* pin from the opposite side is carrying the **1-Wire** signal.     
* **Voltage:**     
  Both pins seem to be designed for **5V** however there are reports that **3.3V** may also work. That said, there are other reports stating that using 3.3V may introduce instability. That's why most projects either use 5V microcontrollers (like Arduino Nano), or add a level shifter and pull the pins up to the 5V rail.    

The purpose of the remaining pins on the connector is unknown, most users cut off the remaining wires:

<img src="images/makita_obi_adapted_connector_front_t.webp" width="20%" height="20%" />

> [!TIP]
> There is an excellent [write-up](https://github.com/rosvall/makita-lxt-protocol) on all protocol findings that are currently publicly known.



## Protocol

Makita uses the original 1-wire protocol. This is a half-duplex serial bus protocol developed by Dallas Semiconductor (now Maxim Integrated) for low-speed communication over a single data wire plus ground.

Devices connect via an open-drain data line pulled high by a 4.7kΩ resistor to 3-5V, allowing master or slaves to pull low for signaling. A master initiates all communication with a reset pulse (480μs low, then release), prompting slaves to respond with a presence pulse (60-240μs low). Each slave has a unique 64-bit factory-programmed ROM ID for addressing on multi-device buses.

Bits transmit in 60μs time slots without a clock: master starts each slot with a brief low pulse; slaves send "1" by doing nothing (line goes high) or "0" by holding low longer. Standard speed is 16.3kbps, with overdrive mode at 125kbps using shorter timings. Power can be parasitic (from data line) or external via Vcc.


### Communication

> [!NOTE] 
> Most details have been taken from [makita-lxt-protocol](https://github.com/rosvall/makita-lxt-protocol/tree/main) and just summarized below for better structure. Please visit the [original content](https://github.com/rosvall/makita-lxt-protocol/tree/main)  for more details.

Every command is preceeded by a 1-wire reset sequence, to which the battery asserts presence:

1. Transactions starts with a 1-wire bus reset (line pulled low for 500μs).     
2. Battery asserts by pulling the bus low from 550-650μs.     
3. Client then sends a command initiated by `cc`, followed by the command type (i.e. reading absolute temperature: `d7 0e 02`.
4. Battery returns response, i.e. `9d 0b 06`.


## Commands
Makita LTX batteries have evolved over time and use different BMS chips with slightly different command sets. 

### Common Commands
All battery types support querying basic battery information, including information like:

* Battery type   
* Capacity      
* Failure Code    
* Cycle Count

[More details here.](https://github.com/rosvall/makita-lxt-protocol/blob/main/basic_info_cmd.md)

### Specific Commands
Reading battery information such as cell voltages, temperature, charge level, and battery health indicators differs between battery types. 

#### 1. Determine Battery Type
That's why first the type of battery needs to be determined. The official Makita diagnostic tools [BTC04](https://www.youtube.com/watch?v=uumwieLu8CE) uses this scheme:

| Type | Identification |
| --- | --- |
| 0 | must support `cc dc 0b`, last byte of response must be `06` |
| 2 | does not support `cc dc 0b` but supports `cc dc 0a` when *test mode* was enabled |
| 3 | does not support the previous commands, but supports `cc d4 2c 00 02` |
| 5 | value of byte 3 (starting at 0) of ROM id is <100 | 
| 6 | byte 17 (starting at 0) of basic battery information response `cc aa 00` is decimal 30 |

#### 2. Issue Specific Commands
Once you know the battery type, you can use supported commands from the table below. 

* Battery types 0,2,3 terminate all results by sending byte `06`. 
* All results are in *little-endian* notation unless noted otherwise


| Action | Command | Battery Type | Returned Bytes | Data Type | 
| --- | --- | --- | --- | --- |
| Temperature (1/10K) | `cc d7 0e 00 02` | 0, 2, 3 | 3 | int16  |
|  | `cc 52` | 5 | 2 | int16  |
|  | `cc 10 21`, then `d4` | 6 | 1 | byte<br/>(`t = (-40*x + 9323)/100`)  |
| Voltage<br/>(Pack and Cells) | `cc d7 00 00 0c` | 0, 2, 3 | 13 | 6x int16 |
|  | `31`,`32`,`33`,`34`, or `35`<br/>(cell 1 - 5) | 5 | 2 | int16 |
|  | `cc 10 21`, then `d4`<br/>(10-cell battery) | 6 | 20 | [10x int16](https://github.com/rosvall/makita-lxt-protocol/blob/main/type6.md) |
| Enter Test Mode | `cc d9 96 a5` | 0, 2, 3 | 1 | -|
| Exit Test Mode | `cc d9 ff ff` | 0, 2, 3 | 1 | - |
| Charge Level | `cc d7 19 00 04` | 0 | 5 | int32  |
| Model String | `cc dc 0c` | 0,2 | 16 | string |
| Overdischarge Counter | `cc d4 ba 00 01` | 0 | 2 | byte |
|  | `cc d6 8d 05 01` | 2 | 2 | byte |
|  | `cc d6 09 03 01` | 3 | 2 | byte |
| Overload Counter | `cc d4 8d 00 07` | 0 | 8 | [Bitmask](https://github.com/rosvall/makita-lxt-protocol/blob/main/type0.md) |
|  | `cc d6 5f 05 07` | 0 | 8 | [Bitmask](https://github.com/rosvall/makita-lxt-protocol/blob/main/type2.md) |
|  | `cc d6 5b 03 04` | 3 | 6 | [Bitmask](https://github.com/rosvall/makita-lxt-protocol/blob/main/type3.md) |
| Health | `cc d4 50 01 02` | 0 | 3 | int16 |
|  | `cc d6 04 05 02` | 2 | 3 | int16 |
|  | `cc d6 38 02 02` | 3 | 3 | int16 |



## Calculated Values

The official Makita diagnostic tool [BTC04](https://www.youtube.com/watch?v=uumwieLu8CE) calculates indicators from the raw values:

### State-of-Charge
Scale of 0-7:

  ````
  ratio = charge_level / capacity / 2880

  if ratio == 0:
    sof = 0
  elif ratio < 10:
    sof = 1
  else:
    sof = min(ratio / 10, 7)
  ````

### Overdischarge percentage

Calculated like this:

  ````
  if overdischarge_count > 0 and cycle_count > 0:
    p = 4 + 100 * overdischarge_count / cycle_count
  else:
    p = 0
  ````

### Overload percentage

Calculated as follows:

  ````
  if sum(counters) > 0 and cycle_count > 0:
    p = 4 + 100 * sum(counters) / cycle_count
  else:
    p = 0
  ````

### Health

For batteries of type 0, a pre-calculated *health* value can be queried and is then scaled like this:

````
ratio = health / capacity
if ratio > 80:
  h = 4
else:
  h = ratio / 10 - 5
````

For all other battery types, a *health* value is calculated like this:

  ````
  f_ol = max(overload - 29, 0)
  f_od = max(35 - overdischarge, 0)
  dmg = cycles + cycles * (f_ol + f_od) / 32
  scale = 1000 if capacity in (26, 28, 40, 50) else 600
  h = 4 - dmg / scale
  ````



> Tags: Makita, One-Wire, 1-Wire, OneWire, Digital Interface, LTX, BTC04, DC18RC

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/toolbatteries/makita/makitaltxdigitalinterface?134231121517253207) - created 2025-12-16 - last edited 2025-12-16
