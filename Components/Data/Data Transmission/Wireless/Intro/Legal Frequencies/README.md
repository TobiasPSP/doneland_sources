<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Legal Radio Frequencies

> Picking The Appropriate Radio Frequencies For Your Devices

Components and breakout boards that send and/or receive radio frequencies are available for many different radio frequencies. 

Often, identical-looking breakout boards are tuned to different frequency ranges, and it is crucial to order the correct boards because you cannot change the general frequency range later.

## Legal Considerations
Since radio waves are public, there has always been great competition among users. That's why countries **regulate** the use of radio frequencies. Before you start using radio waves yourself, you **must** know the key regulations, and **comply**. 

Keep in mind that radio frequencies are often used by crucial services like ambulances, the military, or aviation. If you do not comply with regulations, you may **interfere** with other services. While there are severe penalties, in the worst case you may also be faced with much more severe civil liabilities.

That said, there is no reason to be scared. Once you make sure your senders...

* **use appropriate frequencies** and 
* **do not exceed the maximum allowable RF power**,

...you are good to go. While there are more regulations in the fine print of most countries, sticking to these two rules keeps the potential for interferences low.

## "License-Free" Bands

There are **four** *license-free* frequency bands in the heavily contested and "valuable" sub-Gigahertz spectrum: **315/433/868/915 MHz**. 

> [!NOTE]
> The sub-Gigahertz-frequencies are "valuable" because these frequencies naturally enable long distance communications. Frequencies above 1 Gigahertz can only be used in short range, or require *satellites* or *mesh networks*.

Many components and breakout boards are tuned to one of these four frequency ranges.

<img src="images/fsk_rxtx_rfm69_back_t.png" width="40%" height="40%" />

Not all ranges are legal to use in a given country, so make sure you order components that are tuned to a frequency that you can legally use in your country:



| Frequency (MHz) | Range | Countries |
| --- | --- | --- |
| 315 | 310-318 | North America (FCC Part 15)<br/>Japan (315-316 MHz) |
| 433 | 433.05-434.79 | Europe (ETSI EN 300 220)<br/>Asia (varies by country) |
| 868 | 868.0-869.65 | Europe (ETSI EN 300 220) |
| 915 | 902-928 | USA (FCC Part 15)<br/>Australia (ACMA, **915**-928MHz)<br/>Asia (varies by country) |

These are the typical license-free bands for the regions:

| Region | Bands (MHz) |
| --- | --- |
| Europe | 433 and 868 |
| USA | 315 and 915 |
| Australia/NZ | 433 and 915 |
| Asia | 433 and 915 |


> [!IMPORTANT]
> Exceptions may exist, so to be 100% safe, **always check with your national regulations**.    


### Always Check Device Frequency

Make sure the device you order isn't just *theoretically* working in the desired frequency band. It must be *actually* **tuned** *to the desired frequency*. This cannot be changed later. Here is why this can be confusing:

* **Theory...** Often breakout boards use transceiver chips that can work in a wide frequency range, covering multiple bands. 

  So a breakout board may use a transceiver chip that may be programmed to frequencies in a wide range, i.e. from *420-980 MHz*.

* **...and Reality:** the transceiver chips require carefully tuned external component - like coils and resistors - that resonate with a frequency and filter out other frequencies.

  So while you may be able to program the transceiver chip to use different frequencies, this won't do you much good: the external hardware components of the board won't let these frequencies pass through, or impair the RF power so much that you'll barely get the frequency "on the air".

Often you find a marking on the board (like in the picture above) indicating the frequency band the board is designed for. 

In a nutshell, **never judge a board by the datasheet of the radio transmitter chip it uses**. Always **go by the specs of the particular board** itself.

## Gigahertz Bands
Frequencies above *1 GHz* aren't as heavily contested as sub-Gigahertz-frequencies as there are a number of limitations:

* **Complex:** using these frequencies requires technology that became available only in recent decades so there are much less competing users
* **Short Range:** by nature, such high frequencies require *line of sight* and are good only for short distance communication, limiting their immediate usefulness. With satellites or mesh networks, the reach can be significantly extended, though.

In addition, there is **much more** bandwidth to assign. The Gigahertz range covers 1-250 GHz, so the total frequency range is 250x larger than **all traditional frequencies combined** (0-1 GHz).

Gigahertz frequencies became available **after** worldwide globalization occured, so these bands are typically **globally** regulated:


| Frequency Band     | Region / Standard            | Typical Uses                                   | Notes |
|--------------------|------------------------------|------------------------------------------------|-------|
| 2.4–2.4835 GHz      | Worldwide ISM (ITU Region 1–3)| Wi-Fi (802.11b/g/n), Bluetooth, Zigbee, LoRa 2.4 GHz | Most widely available license-free band |
| 5.725–5.875 GHz     | Worldwide ISM                | Wi-Fi (802.11a/n/ac), radar, short-range links | Shared with weather radar and other services |
| 5.8 GHz (ISM subset)| Worldwide ISM                | Point-to-point links, analog video             | Sometimes distinguished from 5.725–5.875 GHz |
| 24.0–24.25 GHz      | Europe, some other regions   | Industrial sensors, radar, SRR                 | Limited to low power; short range |
| 57–64 GHz           | Worldwide (varies slightly)  | 60 GHz WiGig (802.11ad/ay), high-speed links   | Very short range; oxygen absorption at 60 GHz |
| 122–123 GHz         | Some countries               | Experimental, imaging, radar                   | Very limited adoption; regulated by local bodies |
| 244–246 GHz         | Some countries               | Experimental                                   | Also extremely short-range due to absorption |


### Use Cases
You are probably already using Gigahertz frequency ranges: *WiFI*, *Bluetooth*, *Zigbee* are all using it, and also *car distance radars* and many other commodities work in this range.

That's important to remember. You may not need sub-Gigahertz radio devices at all anymore. Many modern microcontrollers - like the popular ESP32 family - come with built-in *WiFi* and/or *Bluetooth* transceivers. 

So if you can live with the inherent technical limitations of the frequencies - line of sight, limited direct distance - then these license-free bands can be a great alternative.

For example, *Meshtastic* with its *LoRa* (*long range*) modulation is a popular public mesh network that traditionally operates in the sub-GHz bands.

Meanwhile, though, there are *LoRa* transceivers available - such as the *SX128x* - that work in the license-free 2.4 GHz band.

## Maximum Power

Picking a *license-free frequency* is the first and most important step. Adhering to legal RF power emissions is the second, and here is why:

Since radio frequencies are *public*, you generally shouldn't use more power than needed to transmit data from A to B. Why would you want your sensor data to be receivable miles away? In essence, you'd congest an already limited resource, interfere with fellow users, and make yourself (and your data) subject to unwanted *listen in*.

Worse yet: even when you send on a *license free frequency*, you can *still* interfere with other frequencies, i.e. the ambulance service, cell phones, or the military.

That's because senders - especially cheap ones - involuntarily send out *harmonics*: *multiples* of the primary frequency. If you send with high RF power, the harmonics will also be sent with high power and can seriously cause interferences.

So don't get yourself and others in trouble. Most license-free bands allow for only very small RF power. Here is a rough overview, always check with your actual national regulations:

| Band       | Region         | Frequency Range        | Max ERP / EIRP        | Notes |
|------------|----------------|------------------------|------------------------|-------|
| 315 MHz    | USA (FCC)      | 310–318 MHz            | 11 mV/m @ 3m (~-19 dBm ERP) | Very low field strength; limited to short-range use like keyfobs |
| 433 MHz    | Europe (ETSI)  | 433.05–434.79 MHz      | 10 mW ERP              | 1% duty cycle unless using LBT; common for SRDs |
|            | USA (FCC)      | 433.05–434.79 MHz      | Not officially ISM, but usable under Part 15 with strict limits |
| 868 MHz    | Europe (ETSI)  | 868.0–868.6 MHz (g1)    | 25 mW ERP              | 1% duty cycle; standard LoRaWAN uplink band |
|            | Europe (ETSI)  | 869.4–869.65 MHz (g3)   | 500 mW ERP             | 10% duty cycle; good for alarms |
| 915 MHz    | USA (FCC)      | 902–928 MHz            | 1 W **conducted** (30 dBm) + 6 dBi antenna = 36 dBm EIRP | No duty cycle limit, but must use FHSS or digital modulation |
|            | Australia/NZ   | 915–928 MHz            | 1 W EIRP               | Similar to US rules |


In a nutshell, legal RF power is often limited to as low as *10-25 mW* (10-14 dBm).

While you'll probably get away with using slightly higher RF power (some of the commercially available RF modules send with as much as *100mW*/*20dBm*), it is not a good idea to grossly exceed these limits or even use a power amplifier.

Should you really do need more range, use a better antenna, improve your location (line of sight, height), and/or use long range modulations like *LoRa*, and mesh networks like *Meshtastic*. These are much more effective than cranking up the RF power.

## Additional Regulations

In the fine print of your national regulations, you find additional rules, such as:

* **Antenna:** you may be limited to certain antennas because directional antennas basically act like a power amplifier
* **Use Case:** in a given band, you may be limited to certain use cases (digital transmissions, voice, modulations)
* **Duty Cycle:** you may have to adhere to certain duty cycles, i.e. you cannot send all the time.

If you use simple use cases - transmitting sensor data, opening a garage door, short range communications - you probably won't have much potential to violate these regulations.

If you are participating in public mesh networks - like LoRaWAN/meshtastic - the available software/firmware typically takes care of it and automatically limits the duty cycle as required. 



> Tags: RF, Frequency, Regulations, License-Free, ISM

