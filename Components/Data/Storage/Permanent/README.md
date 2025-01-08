<img src="/assets/images/treasureChest.png" width="100%" height="100%" />
 
# Permanent Data Storage

> Storing Data In Non-Volatile Memory 

*Permanent* data storage uses storage media that can keep their content even when powered off. The most commonly used non-volatile memory is *flash memory*.


## Flash Memory

Almost all microcontrollers come with *flash memory*, either *internal* (integrated into the main chip) or *external* (as a separate chip). *Flash memory* is the place where your firmware is stored. That's why the microcontroller can remember your code even when you powered it off.

### Built-In

Most modern microcontrollers come with at least *4MB* of flash memory. When you compile a firmware, you can *partition* this memory area into designated parts. 

This way, you can utilize part of the memory for storing your firmware, repurpose other parts as a *file system* similar to a disk drive for data storage, and use yet other sections to implement features like *OTA* (*over-the-air* wireless updates where you need a storage area to hold the new firmware while the old firmware is still executing).


To store information, you have these options:

* **File System:** store information on a virtual disk drive that lives in your built-in flash memory. This is useful for storing large amounts of data. There are a number of different libraries that can emulate file systems in flash memory.
    > Whether or not you have access to a *file system* depends on the partitioning of your flash memory.
* **EEPROM:** Some microcontrollers like *Arduinos* come with dedicated *EPROM* memory which is another type of non-volatile memory. *ESP32* microcontrollers - like many others - do not invest in dedicated *EPROM*. Instead, they utilize a small part of their flash memory as *virtual EPROM*. With the **EEPROM* library, you can use up to *512 bytes* to permanently store data. That's useful to "remember" user options and other information that doesn't require much space.


### SD Card
The built-in flash memory has two disadvantages: its size is limited, and it cannot be removed.

If you need to *export* data, i.e. sensor data gathered by a device, then you can use [SD Cards](https://done.land/components/data/storage/permanent/onsdcards/). They are basically just *flash memory chips* that expose their pins through the SD Card contacts.

Typically, you would use a cheap [SD Card reader breakout board](https://done.land/components/data/storage/permanent/onsdcards/#connecting-sd-card-readers), but keep in mind that these "readers" really are just a mount for SD cards without any other logic. You could as well directly solder wires to the contacts of a SD card (which would make it hard to remove the card, though).

SD cards must be formatted in the *FAT* file system to be recognized by most libraries. There is no size limit, and you can safely use SD cards that have gigabytes of capacity. However, for non-technical reasons, most formatting software limits the *FAT* filesystem to media up to *32MB*. SD cards with larger capacity can only be formatted using *FAT32* or other file systems which are all incompatible.

### Caveats

Flash memory is very affordable, but it is relatively *slow*, and it *wears* with each read-write-process.

That's why flash memory is not ideal for storing high-frequency data: it may pose a bottle neck due to its slow speed, and if you store values in high frequency, your flash memory may wear out and become unusable after a few months.

> [!TIP]
> The role of external SD cards as declined as most modern microcontrollers today support wireless communication and can conveniently transfer sensor data immediately to a server without the need for local storage.

## FRAM (Ferroelectric RAM)

Another relatively unknown memory type is *FRAM*. This memory **does not wear**, so you can read and write data as often as you wish. 

| Feature             | FRAM                              | Flash                             |
|---------------------|------------------------------------|-----------------------------------|
| **Speed**           | Very fast read/write speeds, no erase-before-write required | Slower, requires erase-before-write for updates |
| **Write Endurance** | Extremely high (billions to trillions of cycles) | Limited (10,000 to 1,000,000 cycles) |
| **Data Retention**  | 10-100 years depending on technology | 10-20 years depending on usage and quality |
| **Power Consumption** | Very low power for both read and write | Higher power, especially for write and erase |
| **Capacity**        | Lower capacity, typically in kilobytes to megabytes | Higher capacity, typically in megabytes to terabytes |
| **Cost**            | More expensive per bit | Cheaper per bit |
| **Durability**      | Resistant to radiation and magnetic fields | More susceptible to radiation and magnetic fields |
| **Technology**      | Uses ferroelectric materials for data storage | Uses floating-gate transistors for data storage |
| **Applications**    | Real-time logging, high-write-cycle applications, embedded systems | Long-term data storage, firmware, and consumer devices |


There are external FRAM breakout boards available. However, FRAM memory is much more expensive than flash memory. An external FRAM board with *8KB* of storage capacity costs around €5.00. A *SD Card* with *8GB* of storage (that's a million times more) costs less.

> Tags: Data, Flash Memory, EEPROM, EPROM, FRAM, SD Card, Permanent Storage
