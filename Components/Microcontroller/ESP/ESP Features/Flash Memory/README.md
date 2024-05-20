<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Flash Memory

> Persistent Memory That Can Be Assigned To Various Data Storage Systems

*ESPxxxx* modules come with integrated *Flash* memory which works almost like *SD Cards*. The *flash* memory can be integrated into the microcontroller dye, or mounted externally.

*Flash* memory provides comparably *huge storage capacity*: the most common size is *4MB*, but the range starts at *2MB* and does not end at *16MB*. 

*Flash* memory is *non-volatile*: data stays intact even when power is removed.

## Memory Size And Type
The first thing that you should do with a new development board is examining its *Flash* memory: what is its true *total physical size*, and did the *vendor* tell you the truth when you purchased the board?

### Using API Calls
The API methods *esp_flash_get_size()* and *spi_flash_get_chip_size()* both report the total *Flash* memory size:

* **esp_flash_get_size():** Part of the ESP-IDF API. Can handle different flash chips if specified. This is useful in complex hardware setups with multiple flash chips.
* **spi_flash_get_chip_size():** Part of the SPI Flash API. Specific to the main SPI flash chip, suitable for most standard use cases with a single flash chip. Returns the size of the main SPI flash chip directly. However, this method is considered *deprecated*: **starting in ESP-IDF *v5.0-dev-4037*, the method is now *removed* and no longer *available***.

Here is a sketch that uses *both methods* to report the total physical *Flash* size:

````c++
#include <Arduino.h>
#include "esp_spi_flash.h"

void setup() {
  Serial.begin(115200);
  while(!Serial);
  delay(500);
  Serial.println("Start");

  // Using spi_flash_get_chip_size()
  uint32_t flash_size_spi = spi_flash_get_chip_size();
  Serial.print("Flash size using spi_flash_get_chip_size(): ");
  Serial.print(flash_size_spi);
  Serial.println(" bytes");
  
  // Using esp_flash_get_size()
  uint32_t flash_size_esp;
  esp_flash_get_size(NULL, &flash_size_esp);
  Serial.print("Flash size using esp_flash_get_size(): ");
  Serial.print(flash_size_esp);
  Serial.println(" bytes");
}

void loop() {}
````

The result may look similar to this:

````
Flash size using spi_flash_get_chip_size(): 4194304 bytes
Flash size using esp_flash_get_size(): 4194304 bytes
````

If your development board uses just *one* flash memory module, the reported values should be identical.

### Summing Up Partition Table
The *flash partition table* organizes the *flash ram* into separate portions for different use cases. By reading the *partition table* and *summing up* these portions, the *total flash size* can be approximated.

Here is a sketch that sums up the *partition sizes*:

````c++
#include <Arduino.h>
#include "esp_partition.h"

void setup() {
  Serial.begin(115200);
  while(!Serial);
  delay(500);
  Serial.println("Start");

  // Initialize variables to calculate total flash size
  uint32_t total_flash_size = 0;

  // Get an iterator to the first partition
  esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, NULL);

  // Iterate over all application partitions
  while (it != NULL) {
    const esp_partition_t* partition = esp_partition_get(it);
    total_flash_size += partition->size;
    it = esp_partition_next(it);
  }

  // Release the iterator
  esp_partition_iterator_release(it);

  // Get an iterator to the first data partition
  it = esp_partition_find(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, NULL);

  // Iterate over all data partitions
  while (it != NULL) {
    const esp_partition_t* partition = esp_partition_get(it);
    total_flash_size += partition->size;
    it = esp_partition_next(it);
  }

  // Release the iterator
  esp_partition_iterator_release(it);

  // Print the total flash size
  Serial.print("Total flash size: ");
  Serial.print(total_flash_size);
  Serial.println(" bytes");

  // Optionally, print the total flash size in megabytes
  Serial.print("Total flash size: ");
}

void loop() {
  // Do nothing here
}
````

The result should be close to the sizes reported by the *API calls*:

````
Total flash size: 4157440 bytesp
````

> [!NOTE]
> Summing up *partition sizes* may yield a slightly smaller size as there can be unassigned memory.

### esptool.py: Detailed Hardware Info
The most accurate information can be gathered by the *python* script *esptool.py* (or its *wrapped* variant  *esptool.exe*). This software is provided by the manufacturer *espressif*. Coincidentally, it is the same tool used by *Arduino IDE* and *platformio* to upload sketches to *ESPxxxx* modules. 

Unfortunately, it is programmed in *Python* which is a prerequisite and needs to be installed.


<details><summary>Installing esptool</summary><br/>

Even though your *IDE* most likely already installed a version of *esptool.py* somewhere, the most straight-forward way is to install a *fresh copy* of the tool in a location of your choice. 

Here are the steps for a *Windows* computer:

1. [Install Python](https://www.python.org/downloads/) on your computer: download and run the installer, and **make sure you check the box *Add Python to PATH* before clicking *Install Now***.
2. Once *Python* has been installed, open a *PowerShell Console* with *Administrator privileges*. These privileges are not explicitly required but I ran into issues when trying the following steps as *regular user*.
3. In the *PowerShell console*, make sure the *Python package installer* is operational by entering `pip --version`. This should report its version number. If not, you may have to reinstall *Python* and this time make sure you add its folders to the *PATH environment variable* before you start the installation.
4. Next, install *esptool.py* by running this command: `pip install esptool`
5. To verify the installation, finally run this command: `esptool.py --version`.

The two most common troubleshooting issues are:

* **File not found:** Check the messages emitted during installation and look for errors. If all of the commands listed above ran successfully, then most likely the newly created folder paths were not added to the *PATH environment variable*.
* **esptool.exe vs. esptool.py:** in my case, no *esptool.py* script was installed. Instead, I ended up with a *wrapped version* called *esptool.exe*. This file is not a stand-alone executable and still requires *Python*. If *esptool.py* cannot be found, then try calling *esptool* (omitting the file extension).

Once you followed all steps, you can now run the command `esptool` from *any terminal window, including stand-alone *PowerShell consoles* as well as the *Terminal* pane inside *VSCode* - just make sure you *restarted* the application *after you adhjusted the **PATH** environment variable*.


<img src="images/esptool.PNG" width="100%" height="100%" />

Working with *esptool* is still not always pure joy: you will probably frequently run into *COM Port exceptions* when the port is still blocked or busy from a previous call or used by the *IDE* for other purposes.

Please add your *tips & tricks* as comments at the bottom of this page if you found ways of properly closing and opening the *COM ports* that connect the computer to the development board.


</details>

Once *esptool* is running on your computer, you can query the *flash memory* of a connected development board and find out its *size*, *Manufacturer ID*, and *Device ID*.

Here is a screen dump of a *PowerShell console* running the tool to query the *flash* memory of a development board connected at *COM76*:

````
PS C:\Users\Tobias> esptool --port COM76 flash_id
esptool.py v4.7.0
Serial port COM76
Connecting...
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

The *flash* memory found on that board is defined by the *Manufacturer Id* (in this case *20*), and the *Device Id* (in this case *4016*). The *detected flash size* is reported to be *4MB* (which matches what the *API calls* returned previously).

#### Finding Hardware Details
*Manufacturer ID* and *Device Id* are just numeric constants and per se *meaningless*. You can however *look up the Device ID* in [the file *flashchips.h*](https://raw.githubusercontent.com/flashrom/flashrom/main/include/flashchips.h).

In my case, the *Device Id* was *4016* which I simply *searched* in the file *flashchips.h*:

````
#define AMIC_A25LQ032		0x4016	/* Same as A25LQ32A, but the latter supports SFDP */
````

This *Device Id* is tied to the label *AMIC_A25LQ032* which in turn can be looked up in [the file *flashchips.c*](https://raw.githubusercontent.com/flashrom/flashrom/main/flashchips.c), revealing these hardware details:

````
{
		.vendor		= "AMIC",
		.name		= "A25LQ032/A25LQ32A",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25LQ032,
		.total_size	= 4096,
		.page_size	= 256,
		/* A25LQ32A supports SFDP */
		/* OTP: 64B total; read 0x4B, 0x48; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
		.probe		= PROBE_SPI_RDID,
		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 1024 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 64 } },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { { 64 * 1024, 64 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 4096 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { { 4096 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.printlock	= SPI_PRETTYPRINT_STATUS_REGISTER_SRWD_SEC_TB_BP2_WELWIP,
		.unlock		= SPI_DISABLE_BLOCKPROTECT_BP2_SRWD, /* TODO: 2nd status reg (read with 0x35) */
		.write		= SPI_CHIP_WRITE256,
		.read		= SPI_CHIP_READ,
		.voltage	= {2700, 3600},
	}
````


## Partition Table
Now that you know the *total size* of your *Flash memory*, let's dive into its *partition table*: this table organizes the *Flash* memory into isolated portions of storage space for different use cases.

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

Make sure you *upload and monitor* the sketch or open the *Serial Monitor* in another way so you can see the information that is returned by the code. 

Adjust the *baud rate* so that *sketch* and *Serial Monitor* use the same baud rate. 
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


### Partition Types

These are the most common partition types you will find:

| Label | Full Name | Description |
| --- | --- | --- |
| nvs | *NonVolatileStorage* | Wear-levelled *key-value* storage space for static information, preferences, etc. Content can be accessed via `#include <Preferences.h>` and `preferences`.  |
| otadata | Over-the-Air-Updates | keeps track of the OTA update status, including which firmware image (partition) is currently active and which one should be used on the next boot. |
| app0, app1 | Fallback for OTA | By using two app partitions (typically labeled app0 and app1) and the "otadata" partition, the ESP32 can safely switch between different firmware versions. If an OTA update fails, the device can revert to the previous known good firmware. |
| spiffs | Serial Peripheral Interface Flash File System | File-based storage space similar to a disk drive |
| coredump | Crash Analysis | Storage to store a dump in case of unexpected crashs. The core dump image can later be diagnosed by tools |

There may be additional partitions. Anyone can reorganize the *partition table* and add new *partitions* for additional use cases. For example, *spiffs* is a relatively *old and limited* form of *file-based data storage*. There are more robust and more performant alternatives like *LittleFS* and also filesystems like *FAT*. You may miss the partition *spiffs* for example, and instead find one used by *LittleFS*.

Generally, the *partition table* organizes the available *flash* memory in the most efficient way for a given use case. You may want to skip some partitions like *OTG* altogether in exchange for more storage space assignable to your sketches (*app0*).

> Tags: Flash, esptool, spiffs, LittleFS, app0, app1, OTG, otadata, nvs, partition table

[Visit Page on Website](https://done.land/components/microcontroller/esp/espfeatures/flashmemory?141516050021242211) - created 2024-05-20 - last edited 2024-05-20
