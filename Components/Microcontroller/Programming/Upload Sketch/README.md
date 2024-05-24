<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Uploading New Sketches

> Successfully Uploading New Firmware To A Development Board


Once you manage to connect


<details><summary>Testing COM Port Connection</summary><br/>


Once the *development board* is recognized by the computer and got a *COM Port* assigned, you are good to go. 

*IDEs* like *Arduino IDE* and *platformio* use generic tools to communicate to the development board over the assigned COM port. *ESPxxxx*-based development boards are managed by the tool *esptool* supplied by its vendor *Espressif*. 

Anyone can freely [download and install](https://github.com/espressif/esptool/tree/master/esptool) this tool, and you could install it *stand-alone* as part of your personal tool set if you like. Once there is a *COM Port* that you can use to communicate with a development board, tools like *esptool* can gather important *detail information* about a particular board and its hardware. That's useful to check *USB connectivity* as well as i.e. *verify* that your development board in fact came with the features and memory sizes a vendor promised.

On my *COM4*, I connected a *D1 Mini ESP8266* development board. With the command below, *esptool* examines the *Flash memory* of this board and reports back its total physical size, among other details:

````
PS> esptool --port COM4 flash_id
esptool.py v4.7.0
Serial port COM4
Connecting....
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting....
Detecting chip type... ESP8266
Chip is ESP8266EX
Features: WiFi
Crystal is 26MHz
MAC: 08:3a:8d:cc:dd:a9
Uploading stub...
Running stub...
Stub running...
Manufacturer: 5e
Device: 4016
Detected flash size: 4MB
Hard resetting via RTS pin...
````

Likewise, on my *COM port 77* I connected a *ESP32 S2 Mini* board. The same command can query this microcontroller as well:

````
PS> esptool --port COM76 flash_id
esptool.py v4.7.0
Serial port COM76
Connecting....
Detecting chip type... Unsupported detection protocol, switching and trying again...
Detecting chip type... ESP32-S2
Chip is ESP32-S2FNR2 (revision v1.0)
Features: WiFi, Embedded Flash 4MB, Embedded PSRAM 2MB, ADC and temperature sensor calibration in BLK2 of efuse V2
Crystal is 40MHz
MAC: 80:65:99:fc:f4:d0
Uploading stub...
Running stub...
Stub running...
Manufacturer: 20
Device: 4016
Detected flash size: 4MB
Flash type set in eFuse: quad (4 data lines)
Hard resetting via RTS pin...
````

Without delving too much into this topic, *esptool* and other console commands are *low level tools* that may require a bit of background information. For the *ESP S2* for example, due to the way how it connects to *USB*, it is necessary to query *COM77* (triggering a port exception), and then query *COM76*.

</details>



> Tags: USB, UART, TTL, Connect, Port, COM

