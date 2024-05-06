<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Wireless Data Transmission

> Legal Frequencies, Modulations And Protocols 

*Electromagnetic* waves can invisibly transfer information through the air, and we all use this technology in *Smartphones*, *WiFi*, *Walky Talkys*, *Wireless Headphones*, and often even when we just grab a *Remote Control* and switch stations on the TV.


<img src="images/radio_comparison2_t.png" width="40%" height="40%" />

## Overview
To give you a quick overview of available *digital wireless transmission techniques*, here is a quick comparison:

| Technology | Range | Speed | Requires Microcontroller |
| --- | --- | --- | --- |
| WiFi | 40m | fast | yes (WiFi built into (most, not all) *ESP* microcontrollers) |
| Bluetooth | 15m | fast | yes (Bluetooth built into many (not all) *ESP* microcontrollers ) |
| ESPNow | 100m | fast | legacy protocol for *ESP* microcontrollers only |
| nRF24 | 5-20m | fast | yes, typically *SPI* interface |
| SRD | 5-20m | medium | no |
| LoRa | 1-10km | very slow | typically they come as complete breakout boards with microcontroller |


> [!NOTE]
> *Range* was estimated for *inhouse* use (excepz for *LoRa* where this makes no sense). Range depends on additional factors such as *antenna*, *rf output*, and *rx sensitivity* and are just rough estimates. Outside with *free line of sight*, the *range* can be *10-20x* higher.






## Frequencies

When *you* plan to use *radio waves* to transfer information as part of your *DIY Project*, it is important to understand the *frequencies* that are legal to use, the schemes in which data can be sent and received over the air, plus the specific physical *pros* and *cons* attached to given *frequency ranges*.

Here is a quick guideline:

| Use Case | Recommended Frequency |
| --- | --- |
| Indoor | 2.4GHz |
| Garden | 433MHz |
| Long Range | 868MHz |

### Maximizing Range
Two rules describe the effect of *frequency* on the *range* that can be reached:

#### Antenna

**Rule #1:** The *higher* a frequency, the *shorter* its *antenna* (*higher* frequencies have *shorter* wave lengths).

Antennas operating at higher frequencies can be considerably smaller.: 

* *2.4GHz WiFi/Bluetooth/ESPnow/nRF24* antennas measure around [3.06cm](https://www.google.com/search?q=c+%2F+2.452GHz+%2F+4) for a *lamda/4* monopole
* *868MHz SRD/LoRa* antennas measure around [8.63cm](https://www.google.com/search?q=c+%2F+868MHz+%2F+4) for the same *Lambda/4* monopole
* *433MHz SRD/LoRa* antennas measure around [17.27cm](https://www.google.com/search?q=c+%2F+433.92MHz+%2F+4) for the same *Lambda/4* monopole

Smaller antenna size can be advantageous where space is limited or where smaller devices are needed.

#### Environment
**Rule #2:** Use *higher frequencies* in **urban environments** and **inside buildings**. Use *lower frequencies* for *rural areas* and *long range connections*.

While it is true that *higher frequencies* are more *sensitive* to a free *line of sight* with no obstacles in the way (like *mountain ranges*), this  applies to *long range communications*. It *does not so much apply* to the kind of *short range communications* typically needed in *DIY projects*.

Obviously, a *metal-enforced concrete wall* will attenuate or block a radio signal, and the *higher* a frequency is, the more it is susceptible to this kind of obstacle.

However, most *concrete walls* and other obstacles **do have holes**, i.e. *windows*, *doors*, or *hallways* (normal *window glass* does not interfere with radio waves). These holes *do not block radio waves at all* **provided** the holes are bigger than the *radio wave length* that wants to pass it.

#### Higher Frequency = Smaller Wavelength

The *wave length* for *2.4GHz* (as used in *WiFi/Bluetooth/ESPnow/nRF24*) is just *12.5cm*, and most openings in *urban obstacles* are much larger.

The *wave length* for *433.92MHz* (as used in *SRD/LoRa*) is *69cm*, and such a *radio wave* would have to pass a door stock at pretty much the right *phase angle* to pass it unattenuated.

#### Smaller Wavelength = Better For Urban Environments

That's why for *indoor use* and in *urban environments*, *higher frequencies* perform generally better even though they are attenuated more when hitting obstacles.


> [!TIP]
> Another important factor in choosing a *frequency* is *radio interference* from other users. *SRD* is especially susceptible as it does not use *frequency spread*. In Europe, the *license-free 433MHz band* is narrow with  traffic focusing on a few frequencies only. The *868MHz band* is typically less limited.







### Frequency Allocations


Radio waves are emissions to the *public*: anyone in the vicinity can detect and read them. So anyone can also *interfere* with anyone else in a radio spectrum.

> [!NOTE]
> Radio waves can also *harm* people, at least when sent with sufficient transmit power. This is why both *frequency* and *maximum emission power* is strictly regulated in all countries of the world.

At the end of the day, national governments allocate frequencies and determine the conditions of use.

In a globalized world, harmonizations take place, though, and supra-national organizations negotiate regional and global frequency allocations. 

The *ITU* (*International Telecommunications Union*) has devided the world into [three regions](https://transition.fcc.gov/oet/spectrum/ituregions.pdf) with [geographical definitions](https://www.ecfr.gov/current/title-47/chapter-I/subchapter-A/part-2/subpart-B/section-2.104).

## ISM Radio Band

Almost all *frequency ranges* are *licensed*: you cannot use them without a proper *license*.

*ISM Radio Bands* are frequency ranges within the radio spectrum reserved internationally for *industrial, scientific*, and *medical* (*ISM*) purposes. These bands are *unlicensed*, making them attractive for *DIY Projects* and *short range devices*.

### Unlicensed

*ISM* bands are *unlicensed*: users do not need to acquire a *license* to use them.

*Unlicensed* means that you *do not need a specific license* (i.e. to operate a *microwave oven* which emits radio frequencies in the ISM frequency range). 

You [still have to adhere to regulations](https://www.ti.com/lit/an/swra048/swra048.pdf). So while you can operate a microwave oven, you cannot operate your own public broadcast radio station on the same frequency. Emissions must match approved use-cases, and your emitted radio power must meet technical criteria. 

So *unlicensed* does not **at all** mean *unregulated*.

Here are the key aspects of *ISM* radio bands:

* **No License:** Users need no specific license when they operate *senders* in accordance with the rules and technical specifications for a given ISM band.
* **Interference:** Users must tolerate even strong *interference* from other users. 

### Licensed

Most other frequency bands in the radio spectrum are *licensed*: a *licensed band* is assigned *strictly to certain users*. Using a *licensed* band requires a permission from the national government. 



Typically you need a *license* (i.e. *GSM*, *Radio Amateur*, *Public Broadcast Station*) or be member of a licensed group (i.e. *police*, *ambulance service*, *aviation*, *military*).


> [!TIP]
> It's a bit like in the physical world: *ISM* bands are *public parks*: anyone can go there but must live with interference caused by others (i.e. music, ball games, etc.). *Licensed bands* are *private property*, and when you illegally sneak in and make yourself at home, you are *trespassing* and will be prosecuted.



> [!NOTE]
> *Licensed* bands grant exclusive use and guarantee operation *without interference* from other services or users. *ISM* bands being *unlicensed* grant no protection from *interference*.


## History and Evolution

The initial *industrial* and *medical use* of *ISM bands* focused on *strong senders* such as *microwave ovens* or *diathermy devices*. While these devices can emit very strong radio signals, they are no *communications* device and have *no receivers*. *Interference* from other users and devices therefore was no problem.

For the same reasons, *ISM bands* were initially *not used for communications*. 

Only in recent decades, the ever increasing demand for *free wireless communications* with increasingly congested radio spectrums moved *ISM bands* to the fore again. After all, *ISM* bands are attractive for *free public communication* as they do not require any license to use. 


### Resiliency To Interference
Technological advances in microelectronics and subsequently in modulations and encodings eventually enabled reliable communications on *ISM bands* despite strong interference:

* **Spread Spectrum:** Communications systems with focus on reliability and/or long distance transmissions use digital *spread spectrum* techniques that spread out the RF signal onto a much wider frequency range. This makes them resilient against strong interferences from industrial applications which are typically blocking out only a distinct frequency. *WiFi* and *Bluetooth* are examples.
* **Low Range Devices:** Communications systems with must bridge a *very short distance* can typically be used safely even in the presence of strong interfering signals as their signal field strengths are strong enough in close vicinity. Examples include *garage door openers* and *wireless sensors*, *wireless door bells*, *baby phones* and alike.

> [!NOTE]
> Since *public communications* is neither *industrial*, nor *scientific* or *medical*, these use-cases are often referred to as *Non-ISM*.



## ISM Frequencies

*ISM* is comprised of a number of *frequency ranges* ("bands") defined by the *ITU Radio Regulations*:

| Frequency Range | Bandwidth | Example |
| --- | --- |--- | --- | --- |
| 6.765-6.795 MHz	| 30kHz | SRD |
| 13.553-13.567MHz |  14kHz | NFR (Near-field communication), RFID, SRD, Heating |
| 26.957-27.283MHz | 326kHz | NFR, CB Radio |
| 40.66-40.7MHz | 40kHz | SRD, earth exploration satellites |
| 433.05-434.79MHz | 1.74MHz | SRD, just Region 1 |
| 902-928MHz | 26MHz |  SRD, just Region 2 |
| 2.4-2.5GHz | 100MHz |  WiFi (802.11), Bluetooth, Plasma Lamps, ANT, Zigbee, Microwaves |
| 5.725-5.875GHz | 150MHz | WiFi (802.11) |
| 24-24.25GHz | 250MHz | Radar |
| 61 GHz-61.5GHz | 500MHz | car distance sensors, WiFi |
| 122-123GHz | 1GHz | local approval required|
| 244-246GHz | 2GHz | local approval required |

### Non-ISM Frequencies

The frequency range *863-870MHz* is often confused with *ISM* when in reality it is a *licensed* band.

In *Europe*, this frequency range is allocated by *CEPT* for *short range devices* (*SRD*) as part of [ERC Recommendation 70-03](https://docdb.cept.org/download/3700): the *EU863-870* band can be typically used wherever the *ISM radio spectrum* is defined by the *ETSI 307* standard.

Materials: [ETSI Short Range Devices](https://www.etsi.org/technologies/short-range-devices)

### National Exceptions

Many *national exceptions* exist as the national governments have the final say.


#### FreeNet
For example, in Germany the frequency ranges *9-10kHz* and *149.995-150.005* (*FreeNet* voice communications) are allocated for *unlicensed use*. 


#### 315MHz
The *US FCC* on the other hand allows *"periodic operation"* of *control signals* anywhere above *70MHz* as long as they meet [Section 15.231](https://www.law.cornell.edu/cfr/text/47/15.231). This is the legal foundation for *garage door openers* and other *digital senders* operating at *315MHz*. [More info](https://ww1.microchip.com/downloads/en/Appnotes/Atmel-4907-Application-of-315-MHz-Short-Range-Devices_Application-Note.pdf) on the *US-specific 315MHz band*.



## Band Plans

Based on region, *band plans* are created that define in detail which frequency is reserved for a particular purpose and usage.

Below are regional *band plans* that allocate frequency ranges for *license-free* radio communications in different regions of the world:


| Area | Band Plan |
| --- | --- |
| Europe | EU433, EU863-870, WiFi, BlueTooth
| South America | AU915-928
| North America | US902-928 |
| India | IN865-867 |
| Indonesia | AS923-925 |
| Malaysia | AS920-923 |

The two most influential agencies - based on size of market they impact - are the *FCC* in the US and *ETSI* in Europe. Among others, these agencies work on band plans and their future development, and also enforce rules.

Still, at the end each national government has the final say over the frequency allocations for their territory. They can adopt standardized regional band plans, add national exceptions and make adjustments.

The *Asian* region frequently uses band plan *AS923-925* but there are exceptions. 

Likewise, *South America* typically uses *AU915-928*. Countries like *Mexico* adopted the *North American* standard *US902-928*.

> [!TIP]
> There may also be additional *national* opportunities. For example, in the **US**, *short range devices* can legally use frequencies as low as *300-390MHz* (i.e. *garage door openers*). In most other areas of the world, this band is exclusively reserved for military.


### Allocating Frequencies To Services

How complex the actual frequency allocation within a band plan for a given country can become [illustrates the picture below](https://www.ntia.doc.gov/files/ntia/publications/2003-allochrt.pdf) (for the US):


<img src="images/usallocation.png" width="100%" height="100%" />

To review the individual allocations, a [detailed list](https://transition.fcc.gov/oet/spectrum/table/fcctable.pdf) exists. [Similar lists](https://docdb.cept.org/download/4316) exists for Europe and other regions of the world.


## Freely Usable Radio Frequencies

Fortunately, picking a *legal frequency* for *DIY data transmission* is not hard: 

Only a few frequency bands exist that are *free to use* and *do not require a license* to transmit digital data:

| Type | Frequency | Remarks |
| --- | --- | --- |
| Short Range Device (SRD) in Europe/Asia | 433MHz and 868MHz | 10mW at 433MHz/25mW at 868MHz with <1% duty cycle |
| Short Range Device (SRD) in the US | 310MHz and 915MHz | up to 1W |
| Bluetooth | 2.4GHz | internationally harmonized 2-way radio, up to 100mW (depending on Bluetooth standard) |
| WiFi | 2.4GHz | 802.11b/g/n/ax, most often used in WiFi-enabled microcontrollers |
| WiFi | 5GHz | 802.11a/h/ac/ax, very infrequently used in DIY data transmission due to its expense and limited distance |


### Harmonized vs Individual Rules

If you plan to use *WiFi* or *Bluetooth* then you are in luck: both technologies are largely harmonized throughout the world, and only very few exceptions exist for the common operating modes.

If you in contrast plan to transmit radio waves as a *Short Range Device*, substantial regional differences exist, both in *legal frequencies* and *maximum allowable radio power*.

Just how complex it can get when you want to stay within legal bounds illustrates [this document](https://www.analog.com/en/resources/technical-articles/fcc-and-etsi-requirements-for-shortrange-uhf-askmodulated-transmitters.html).

A [very good application note](https://ww1.microchip.com/downloads/en/Appnotes/Atmel-4907-Application-of-315-MHz-Short-Range-Devices_Application-Note.pdf) exists, explaining the *FCC* requirements for *SRD*s in various frequency ranges, including the underdocumented *315MHz* range.

> [!TIP]
> Once you *make sure you are using a legal frequency* (**not** using *315MHz* transmitters in Europe, and **not** using *433MHz* transmitters in the US), and when your transmitter **does not exceed *10mW***, you are most likely fully compliant, and more importantly: *not interfering* with anyone else.






## Use Cases

To find out the right *frequency* and *technology* for your project, compare it to the typical use cases below, and pick the same *frequency* and transmission rules.

### Remote Controls, i.e. Garage Door Openers, Homematic IP, Sensor Transmission, IoT

These are the most typical *short range devices*. They predominantly use *ASK* modulation (*Amplitude-Shift-Keyed*), a digital modulation based on traditional *AM* (*Amplitude Modulation*). 


* In Europe, 433.92MHz and 868.35MHz are used. The maximum transmit power is limited to *10mW* on *433MHz* (with no duty cycle), and *25mW* for *868MHz* (with a *duty cycle* of below *1%*).

* In the US, *315MHz* is used.

### LoRa - LongRange Transmission

Typically, *short range devices* have a *short range* (which is why they are called that way). However, the regulatory limitation is *low transmit power*. 

*Low transmit power* does not necessarily translate into *low transmission range*, though:

*LoRa* is a proprietary radio transmission protocol specifically designed to provide a **high** *transmission range* despite using a **low** transmission energy. It is based on *FSK* (*Frequency-shift keying*), a digital encoding on top of *FM* (*Frequency Modulation*).

In fact, *LoRa* is an excellent example for all the sophisticated new modulations evolving, as it uses *Chirp* (increasing and decreasing frequency shifts) and *spread-spectrum* (spreading the carrier signal to be more resilient towards noises).
 
To achieve its exceptional long range capabilities, *LoRa* can also be used in *mesh* topologies where other independently operated *LoRa* devices can pick up and forward the signal, and by *reducing the data transmission rate* to make it more fault tolerant.

* In Europe, *LoRa* typically uses *863-870MHz*, less frequenly *433MHz*. The maximum transmission power is *40mW* at a *1% duty cycle* (devices can transmit only 1% of the time).

* In the US, *LoRa* uses *902-928MHz*. The maximum transmission power is *1W* with a *400ms dwell time* (a maximum of *400ms* transmission time).

> [!CAUTION]
> This is a rough advisory, there are additional rules and requirements. The legal frequency range is for example organized in *channels* with designated *band widths*, and the use of channels may be restricted to specific tasks, i.e. *upload* or *download*, among other requirements.



### WiFi

*WiFi* is typically used to create a computer network and enable multiple devices to talk to each other. 

Since *WiFi* supports *mesh technology*, it is simple to cover a large area by using multiple *access points*.

Modern microcontroller boards like *ESP8266* and *ESP32* come with *WiFi*-functionality built-in. They can act as *access point* (setting up a new wireless network), *station mode* (joining an existing wireless network), and both modes combined.

By using *WiFi* to communicate, you are benefitting from a number of advantages:

* **Reach:** within the covered area of your *WiFi* network, reliable high speed data transmission is possible. The covered area can easily be extended by adding more meshed access points.
* **Legal:** *WiFi* is using an internationally harmonized frequency range. The typical WiFi standards are supported and legal to operate in most parts of the world.
* **Transparent Transmission:** you don't actually need to care much about implementing the data transport layer. Instead, your firmware can communicate with other devices inside your own WiFi or anywhere else on the world (provided your WiFi is connected to the Internet) simply by using http requests.

*WiFi* is *not* a premier option if you:

* want to use microcontroller boards that do not have *WiFi* built-in (i.e. *Arduino*)
* want to bridge areas not covered by your *WiFi* (i.e. sending data from your house to your neighbors house)

### Bluetooth

Bluetooth is a two-way transmission standard commonly used to exchange data between two devices. For this, the devices are *coupled* before they can communicate with each other.

Many modern microcontroller boards come with *Bluetooth* transceivers built-in. This enables you to create your own *Bluetooth* controllers or controlled devices.

In fact, you can use *Bluetooth* also *on both ends*, i.e. use a Bluetooth-enabled microcontroller board on both ends of your communication. 

Starting with *Bluetooth 5.0*, the emission power is up to *100mW*, which can gap distances of up to *40m* indoors and *200m* outdoors.

Bluetooth is using the same internationally harmonized *ISM* frequency band as WiFi (2.4GHz).

## Choosing Frequency
Picking an appropriate frequency is the initial and fundamental step in designing a *radio project*:

* **Legal:** you *must* pick a frequency that is *legal to use* in your country. Else, you may be *interfering* with other services, and may become *liable* for damages you cause. In addition, (severe) legal punishment is possible even if the risk of ham and detection *may be* low with *low emission* devices.
* **Technical:** when you have the *choice* of multiple *legal* frequencies, your *use case* determines which one to choose. The *lower* a radio frequency the better can it pass buildings (walls, doors). The *higher* a frequency the more does it need a *free line of sight*. For example, if you live in a densly populated city in *Europe*, the *433MHz* band can pass buildings better than the *815MHz* band. If you'd like to set up *data transmission* with free *line of sight* between sender and receiver, the *815MHz* band works better (because of lower interference from other services in the same band).

> [!NOTE]
> *WiFi* frequencies are largely harmonized across the world. They are the only *wireless technology* that has no fundamental regional regulations to watch out for (even though the use of *selected WiFi channels* may be limited to some regions).



## Maximum Emissions

The more radio power a transmitter emits, the greater is the distance it can gap, but also the greater is the area in which it can cause interference.

With *DIY projects*, most breakout transmitter boards use very low transmission power (typically *<10mW*). At this level, *interference* and *bodily harm* are very unlikely.

When picking hardware, transmission power can be defined in a number of units:

### Watt and +dBm
The maximum legal emission power can for example be quantified in *raw emission power* expressed either in *Watt* or in *dBm* (which is essentially the same, just *logarithmic*), i.e. *10mW/+10dBm*, *100mW/+20dBm* or *10W/+40dBm*.

Both *Watts* and *dBm* are focusing on the properties of the *sender*.

### Effective Radiated Emission (ERP)
**ERP** (*Effective Radiated Power*) is a more meaningful parameter: it views the *effective* radiated power at the *receivers side*. 

This also takes into account the kind of *antenna* the *sender* is using, and its *directivity*: When you connect a highly directional *antenna*, the total radio power is radiated in one narrow direction, just like *light* in a highly focused *flash light* or a *laser beam*. 

> [!TIP]
> If you are restricted by a certain emission threshold but *free to use* any antenna you like, then using a highly directional antenna can multiply the distance you can gap by multitudes.


### Security By Obscurity
While extending the reach through more radio power sounds great at first (*"the more the better"*), it not only extends the area in which you can *interfere* with others. It also extends the area in which others can *listen in* and *spy* on your transmissions.

A low ERP and a low maximum radio distance does not only *limit interference with others*. It also *shields you from others* and often is much more effective than *encrypting* data transmissions.

For most use cases, a high radio power is not needed and even counter-productive: your *garage door opener* in *Germany* typically does not need to be received in *Argentina*. Especially with *DIY* projects, a tiny *ERP* may be all you need to gap the few meters or 100m you need for your project.


## Free Voice Radio Frequencies

There are additional free-to-use radio frequencies designated for analog and/or digital *voice communications* (i.e. walky talkys):

<img src="images/radio_voice_t.png" width="40%" height="40%" />

| Name | Frequency | Wave Length |
| --- | --- | --- |
| CB (Citizen Band) | 27MHz | 11m |
| FreeNet | 149MHz | 2m |
| MURS (Multi-Use Radio Service) | 151-154MHz | 2m |
| LPD (Low Power Device Voice) | 433MHz | 70cm |
| PMR (Personal Mobile Radio) | 446MHz |  70cm |
| FRS (Family Radio Service) | 462-467MHz | 70cm |
| GMRS (General Mobile Radio Services) | 462-467MHz | 70cm |


> [!NOTE]
> The table presents an overview only. Additional rules exist. For example, *FreeNet* is available in *Germany* only. *PMR* is available in the *EU*. *FRS*, *GMRS*, and *MURS* are available in the *US*. *GMRS* requires an (easy to obtain) license. For *MURS*, additional regulations apply.




> [!CAUTION]
> These frequencies are *not usable* for *DIY projects* as they are *highly regulated*, require *certified devices* and prohibt the transmission of radio data other than voice.




### Amateur Radio (HAM)
Licensed *radio amateurs* are private persons that went through classes, took a test and received a certification ensuring they technically know precisely how radios work and how to not interfere with other radio services.

Radio amateurs typically are *enthusiasts* with a strong focus on radio *technology*.

<img src="images/radio_overview_t.png" width="40%" height="40%" />

Radio amateurs can use a large number of additional frequency bands, and emit radio power up to many kilowatts, but solely for *experimental purposes* related to *radio communications*. 

This includes *DIY* projects, however strictly related to *radio amateur purposes*. A *licensed radio amateur* cannot for example use his or her special privileges to transmit personal weather station data on a privileged frequency - except if this weather data is used in close relation to experiments testing radio emissions under different weather conditions.


> Tags: Frequency, Garage Door Opener,  Band Plan, WiFi, FreeNet, LPD, PMR, FRS, GMRS, MURS, 315MHz, 433MHz, 868MHz, 915MHz, LoRa, SRD

[Visit Page on Website](https://done.land/components/datatransmission/wireless?054116041215245756) - created 2024-04-15 - last edited 2024-05-05
