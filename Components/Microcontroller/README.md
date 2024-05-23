<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Microcontrollers

> They Manage Sensors, LEDs And Other Components Much Cheaper Than Implementations With Discrete Elements Only.

What started in *PCs* and carried over to devices like *Smartphones* is now common-place even for *DIY projects*: instead of trying to implement features exclusively with *discrete elements* like transistors and some *ICs*, it is much easier and more *cost-effective* to add a **microcontroller**.


<details><summary>Microcontrollers used in Computers and Smartphones</summary><br/>

Here are some microcontrollers used in popular *computers*, *notebooks*, and *smartphones*:

| Microcontroller | Used In |
| --- | --- |
| Intel i3, i5, i7, i9, Xenon | Computers running *Windows* (Microsoft) |
| AMD Ryzen 3, 5, 7, 9, EPYC | Computers running *Windows* (Microsoft) |
| Apple Silicon M1, M1 Pro, M1 Max, M2 | Computers running *MacOs* (Apple) |
| Apple A14, A15, ... Bionic | *Apple* iPhone Smartphones | 
| Qualcom SnapDragon 4xxx, 6xxx, 7xxx, 8xxx | *Android* Smartphones |
| Mediatec Helio, Dimensity | *Android* Smartphones |
| Samsung Exynos | *Android* Smartphones |
| Huawai Kirin | *Android* Smartphones |

These *microcontrollers* are fundamentally no different from the microcontrollers I am discussing in this section, however they are *more powerful* and *harder to use*: after all, they are designed to run full-fledged general-purpose *operating systems*.

In *DIY* projects and to control hardware, *simpler microcontrollers* are used that are much *cheaper* (cost is often below EUR 1.00/piece) and very much easier to program.

</details>


## DIY Microcontrollers

In *DIY projects* and *hardware projects*, these are the typical microcontrollers used:


* [ATMega/Arduino](Arduino): *Arduino breakout boards* started to make *microcontrollers* popular among hobbyist and makers because they are *exceptionally easy to use* and come with a proven toolset. Until recently, *Arduinos* exclusively used the *ATMega* family of microcontrollers. Meanwhile, some *Arduino* breakout boards also use *ESP* and other microcontrollers. 
* [ESP/Espressif](ESP): Originally, the Chinese manufacturer *Espressif* produced *cheap but powerful* microcontrollers for the industry, and you find them in many *smart devices*. When *Espressif* released its **ESP8266** in 2015, it soon was integrated into the *Arduino* tool chain and became an instant success, primarily because of its *built-in WiFi* and its very low price. Meanwhile, the family of (much more powerful but equally cheap) *ESP32* has become the best *DIY microcontrollers*: they are much *cheaper* yet in almost all aspects *more powerful* than *Arduino* yet run the same code and can be programmed with the same tools.
* [ATtiny](ATTiny): for *less* computing intensive use cases, and when *small size* matters, *ATTiny* microcontrollers are are great alternative due to their very small size.
* Raspbetty Pi: for *more* computing intensive use cases, *Raspberry Pi* microcontrollers can run a *full-fledged operating system* (and behave like a "real" computer), typically *Raspberry Pi OS* (based on Demian), Ubuntu, and others. *Raspberry Pi* is used for for projects that require a lot of computational power and a full operating system, and can act as a *server* in the backend. *HomeAssistant* is an example: it runs on a *Raspberry Pi* which acts as the *HomeAssistant Server* and lets you control *IoT* devices that in turn each base on one of the other mentioned microcontrollers. The latest evolution is *Raspberry Pi 5*

## Development Boards
While you could use a *naked microcontroller* in your projects and wire it up *manually*, typically *development boards* are preferred: *ready-to-go* PCBs that combine a *microcontroller* with its most essential components such as a *voltage regulator* and a *Serial-to-USB* bridge.

### Originals and Clones

While the *microcontroller* itself is always produced by a given manufacturer, the *development boards* are produced by a variety of sources. You can get *original* development boards from renown vendors such as *Arduino*, *Adafruit*, or *Espressif*, and you can get *clones* from lesser-known companies.


<img src="images/clones2_t.png" width="80%" height="80%" />


*Clones* are typically *much cheaper* than the originals, especially with *Arduinos*. 



> [!NOTE]
> *Clones* discussed here have nothing to do with *product piracy* or *trying to deceive*. They *clone functionality only*, not *appearance*. You can always clearly identify whether a board was produced by a company like *Arduino*, or whether it is just *functionality-wise* the same but looks clearly different. Legal *Clones* *Clones* are possible because the *hardware design* is *open-source*, and it is neither *rocket science* nor a *copyright infringement* to add standard components like *voltage regulators* and *UART chips* to a *PCB*.



*Clones* are *per se* technically no better or worse than *originals*. They are different. Some vendors produce *Clones* with added benefit (like displays) at exceptional built quality. These can be *more expensive* than *Originals*. Other manufacturers use only the cheapest parts that barely meet the specifications. They still often work just fine yet cost only a fraction.

Here are the typical issues to be aware of (which coincidental are the very reasons for huge price differences):


| Issue | Symptom | Remark
| --- | --- | --- |
| Cheap voltage regulator | Once a few sensors/components are connected, the board starts to reboots or stops working | was an issue with ESP8266, fixed for most other boards meanwhile |
| Soldering issues | solder drops can cause short-circuits | Related to the level of *quality control*. Occurs only with mass products under great pricing pressure. Even then rare (1 out of 100). Can often be fixed, if present will show from the start (no reliablity issue) |
| PCB Quality | Labels hard to read | Directly related to the price point, does not affect functionality |

You decide what your focus is. Just keep in mind that *one* microcontroller won't get you far. When comparing prices, compare the price differences for *ten units*.


#### Is Buying Clones Evil?
While *technically ok*, may it be a *morally reprehensible* to use *Clones*?`Are you possibly *stealing intellectual property* when you buy from *obscure Asian profit makers*? Are these taking advantage of other peoples' development efforts to undercut prices?

No. Regardless of source, the *microcontroller* is always original and always legitimately purchased. The PCB *circuit designs* are *open source*. The tool chain is maintained by the *community*.

Cheap prices are more likely a result of *lean production*, *less middlemen* and *less distributors*. In fact, when you buy at a *local store* or at *Amazon*, you come across the *very same* boards that are also *directly available at sources like AliExpress* - just for a five- to tenfold price.



> Tags: Microcontroller, Arduino, ESP32, ESP8266, ATtiny, Raspberry Pi

[Visit Page on Website](https://done.land/components/microcontroller?237357031823244200) - created 2024-02-15 - last edited 2024-05-22
