<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# SPIFF (SPI Flash File Storage)

> Built-In File-Based Data Storage

*SPIFF* takes a portion of the *Flash* memory and utilizes it similar to a *USB Stick*: data can be organized and stored as files, similar to attaching an external *SD Drive* to your microcontroller.

## Partition Table
In order to use *SPIFF*, the *Flash* memory needs to reserve a portion for *SPIFF*. *Flash* memory is organized by a partition table. The first step should be to examine the current *partition table*.

Here is a sketch that outputs the current *partition table*:

````c++
#include <Arduino.h>
#include "esp_partition.h"

void printPartitionTable() {
  const esp_partition_t *partition;
  esp_partition_iterator_t iterator = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
  
  if (iterator == NULL) {
    Serial.println("Failed to find any partitions");
    return;
  }

  do {
    partition = esp_partition_get(iterator);
    if (partition != NULL) {
      Serial.printf("Partition: %s, Type: %d, Subtype: %d, Address: 0x%06x, Size: 0x%06x, Label: %s\n",
                    partition->label,
                    partition->type,
                    partition->subtype,
                    partition->address,
                    partition->size,
                    partition->label);
    }
    iterator = esp_partition_next(iterator);
  } while (iterator != NULL);

  esp_partition_iterator_release(iterator);
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
  delay(500);
  Serial.println("Examining Partition Table:");
  printPartitionTable();
}

void loop() {}
````

Make sure you *upload and monitor* the sketch or open the *Serial Monitor* otherwise. Adjust the *baud rate* so that *sketch* and *Serial Monitor* use the same baud rate.

A typical result could look like this (example taken from a stock *S2 Mini*):

````
Examining Partition Table:
Partition: nvs, Type: 1, Subtype: 2, Address: 0x009000, Size: 0x005000, Label: nvs
Partition: otadata, Type: 1, Subtype: 0, Address: 0x00e000, Size: 0x002000, Label: otadata
Partition: app0, Type: 0, Subtype: 16, Address: 0x010000, Size: 0x140000, Label: app0
Partition: app1, Type: 0, Subtype: 17, Address: 0x150000, Size: 0x140000, Label: app1
Partition: spiffs, Type: 1, Subtype: 130, Address: 0x290000, Size: 0x160000, Label: spiffs
Partition: coredump, Type: 1, Subtype: 3, Address: 0x3f0000, Size: 0x010000, Label: coredump
````

As can be seen, the examined development board currently used a partition with a portion named *spiffs* that is reserved for *SPIFF*. The board is *good to go* to use *SPIFFS* provided the current *storage space* is sufficient (*0x160000* bytes = *1441792* bytes = *1.375* MB).

### Partition Types
A *Partition Table* organizes the storage space provided by the non-volatile *Flash memory*. Any data stored in *Flash* is stored persistently across reboots and power-offs.

These are the partition types and their meaning:

| Label | Full Name | Description |
| --- | --- | --- |
| nvs | *NonVolatileStorage* | Wear-levelled *key-value* storage space for static information, preferences, etc. Content can be accessed via `#include <Preferences.h>` and `preferences`.  |
| otadata | Over-the-Air-Updates | keeps track of the OTA update status, including which firmware image (partition) is currently active and which one should be used on the next boot. |
| app0, app1 | Fallback for OTA | By using two app partitions (typically labeled app0 and app1) and the "otadata" partition, the ESP32 can safely switch between different firmware versions. If an OTA update fails, the device can revert to the previous known good firmware. |
| coredump | Crash Analysis | Storage to store a dump in case of unexpected crashs. The core dump image can later be diagnosed by tools |




<img src="images/mcp4725_front_t.png" width="40%" height="40%" />


> Tags: ESP32, ESP8266, SPIFF, Partition, FileSystem


