<img src="/assets/images/relais.png" width="80%" height="80%" />
 
# Wireless Controlled Relais

> Turning Devices On And Off Remotely


When *relais* are paired with a *radio receiver*, they can be controlled remotely *over the air*, i.e. with a *remote control* or in automation projects.

Most people use this setup every day without thinking about it: whenever you press the button on a *garage door opener*, switch channels on your *TV set*, or use home automation with a *smartphone app*, you are operating *relais* (or other type of switches) remotely - typically via *RF* (*radio frequency*).


## Overview

With *RF controlled* relais, the control information is transmitted *over the air* using *radio waves*. 

There are *two types* of *radio waves* used:

* **Unlicensed Bands (RF):** *unlicensed bands* (*315MHz* in the US, *433MHz* in Europe) are legal to use for anyone. Dedicated *senders* (*remote control*) and *receivers* (*relais*) communicate directly and require no external setup.
* **WiFi/Bluetooth:** the *2.4GHz* band is freely usable for anyone, too. This is where *WiFi*, *Bluetooth*, and related technologies operate. Control messages can be sent to relais, and since *WiFi* networks are typically connected to the *Internet*, this makes *relais* operable from *anywhere in the world*. 


## Examples

Ready-to-use *RF relais* are available for less than *EUR 3.00* per piece and can add *remote control capabilities* to any device:


<img src="images/relais_rfwifi_overview_top_t.png" width="80%" height="80%" />

> [!CAUTION]
> Look carefully at the device description to see *which technology* and *radio frequency* is used by a particular device. The picture shows (from *left* to *right*) a *WiFi-only*, a *WiFi/RF*, and a *RF-only 433MHz* device. 


## Which Technology?

There are *advantages* and *disadvantages* to both wireless technologies. Choose the one that matches your use case best.

### 315/433 MHz RF

In this band, your devices work almost like *walky talkies*: you operate a dedicated *sender* (in your remote control) and a dedicated *receiver* (attached to the *relais*).

The result is a direct *one-way communication* providing autonomy:

* **Simple:** Setup is *simple* and no special prerequisite is required, nor are there points of failure beyond your control.
* **Robust:** when your *WiFi* network fails or your *phone company's network* is temporarily down, your *RF-Controlled Solutions* continue to work.

For the very same reasons, there are also *negative aspects:**

* **Local Solution:** The distance you can bridge is limited to <10m: you need to be *close to the device* to operate it. This may be ok for *garage door openers* but prohibitive for *home automation* (where you'd like to monitor and control devices from anywhere in the world).
* **No Feedback:** because of the *one-way communication*, the controlled device cannot return a feedback. Typically, the feedback you get is a *visual* feedback only (the *garage door* opens).
* **Insecure:** while *RF*-solutions are not inherently insecure, they often are: radio frequencies are public and can be picked up by anyone. Most commonly, data sent via *RF* is neither *encrypted* nor *obscure*. The guaranteed protection is the limited reach (an attacker would need to be in physical proximity to listen in). This protection may be sufficient with enough distance to publicly accessible areas. It can as well be risky in densly populated metropol areas where attackers easily get close enough to your *sender* to sniff the *RF* data packages (and replay them later, i.e., to open your *garage door*).

> [!NOTE]
> There are plenty of good solutions to *secure RF transmissions*, i.e. *rolling codes* or *encryption*. Most *cheap out-of-the-box* solutions do not come with these, though.


### WiFi

Sending *control messages* via *WiFi* comes with a load of benefits:

* **Anywhere:** Commands issued by a *smartphone app* work anywhere and just need *Internet Access*. Your commands are automatically routed to your home *WiFi*, and then to the device that you want to control.
* **Feedback:** since *WiFi* uses two-way communications, the controlled device can return feedback, i.e. show its state or confirm the operation.
* **Secure:** *WiFi* data is encrypted by default. Attackers cannot listen in or use *playback attacks*.

For the very same reasons, there are important drawbacks as well:

* **Infrastructure:** This solution works on top of an existing *WiFi* infrastructure. It will not work with low or no *WiFi* coverage, i.e. outside your house or in the garden.
* **App & Cloud:** Most *out-of-the-box* solutions are very simple to set up because they base on specific *vendor solutions* and their *smartphone apps*. All of your actions are processed in the background by *vendor-owned* cloud datacenters. If their infrastructure is down, or when they decide to discontinue services, then you no longer can use your devices. Worse yet: anyone in control of the vendor backbone has the same control over your devices and could maliciously turn on or off your devices at will. In a nutshell, you are giving up a great amount of control.  

### Conclusions

There is no *one best* technology. You always need to make trade-offs.

#### When To Use RF

*RF* technology is best if you want to keep *all control* in your hands. 

Security concerns can be leveraged by either using *secure devices* (i.e. *garage door openers* with *rolling codes* rather than transmitting *predictable repetitive* codes), or better yet, by using *generic RF transceivers* to build and program your own secure solution.

One disadvantage cannot be overcome, though: *RF* solutions only work when *sender* and *receiver* are within a 10-20m range.

#### When To Use WiFi

*WiFi* technology is best when your devices are inside your *WiFi*-covered home, and when you want to control them from *anywhere in the world*.

The primary disadvantage of depending on potentially insecure *vendor cloud architecture* can be overcome by replacing the device firmware with *open source* solutions, or purchase devices with such firmware in the first place.

When you build your project from scratch, you can use *simple and cheap WiFi-enabled microprocessors* (such as the *ESP8266* and *ESP32*): set it up as a *webserver*, and connect a *relais* to one of its *GPIO* pins (using approproate techniques). This way, the microcontroller acts like a *webservice* and can control the *relais*.

> [!NOTE]
> When you go the *microcontroller* route, you *maximize your control* at the expense of *maximizing your work*: *you* are now in charge of everything yourself. It is up to you how you *expose* your microcontroller to the *Internet* to make it truly controllable from *anywhere* (i.e. using *MQTT*, or *host the microcontroller REST APIs* on *publicly accessible* servers).


## Hardware

Whether you buy a pure *ready-to-use* remote-controllable *relais*, or whether it is *embedded* in a *plug*, or whether you choose to create the functionality from the required components yourself, here is an overview of the general setup.

### Screw Terminals

If your device has *screw terminals*, here is what they do:

| Terminal | Description |
| --- | --- |
| Lin, Lout | The actual *AC switch*, connected to the *relais* |
| Nin, Nout | Short-circuited, the *neutral* **AC** line |
| S1, S2 | When connected, the *relais* can be closed manually |

*Lin* and *Lout* perform the switching while *Nin* and *Nout* are just passed through.

*S1* and *S2* typically enable you to optionally hook up a mechanical switch to also control the *relais* directly.

> [!CAUTION]
> *S1* and *S2* are exposed to *AC*! Never ever hook up a low voltage push button to these terminals!


### Beware: Hazardous Design
Whenever devices are connected to dangerous voltages, make sure you fully understand how these devices work, or else you (or users of your project) may get killed.

When looking at the traces of this particular device, it becomes evident that dangerous *AC* can be exposed at unexpected places:


<img src="images/relais_rf_traces.png" width="80%" height="80%" />

The board interconnects *Nin*, *Nout*, *S1*, and the *push button*. *AC mains voltage* is present at all of these locations.

*N* stands for *neutral AC line*, whereas *L* stands for *live AC line*. If you connect the device accordingly, "only" the *neutral AC line* will be exposed. 

However, if you use a *plug* (that can be plugged in either way), or if you are just careless, then *live AC* is present at all of these locations.

While the push button is normally safely shielded by a plastic cover, the connections *S1* and *S2* are designed to hook up a *manual switch*. 

In professional installations done by certified *electricians*, this would typically be a standard *AC* light switch. 

*DIY* makers however may be intreagued to connect other type of switches (i.e. simple low voltage push buttons), possibly without proper insulation or housing. 

This can turn out to be a deadly mistake with this particular board design.

> [!NOTE]
> Cheap Chinese devices often come in great quality. Just as often, though, they can have critical design issues and lack appropriate documentation. To be clear: the device discussed here was designed to be placed inside a *normal* *AC light switch* by a professional *electrician*. For this use case it can be considered *reasonably safe*. When used in hands of inexperienced *DIY makers*, though, it is *extremely hazardous*.

Let's start the hardware review now, discussing the essential parts required by any *RF-controlled relais*:


### RF Receiver

This is the commercial *ready-to-use* remote-controllable *relais* discussed above that can be controlled using *RF*:


<img src="images/relais_rf_front_t.png" width="80%" height="80%" />

> [!NOTE]
> Note the specs on the housing: this device is using *433MHz* radio frequency (so it is designed for *Europe*). In the US, other frequencies (i.e. *315/915MHz* are used).


Internally, it exposes all the components required by any *RF-controlled relais*.




#### Opening Housing

The two-part housing is pushed together by four pins and can easily be opened with a screw driver:

<img src="images/relais_rf_open_t.png" width="80%" height="80%" />

#### Relais

The *relais* is the predominant black part: its markings show the ratings: it is controlled by *5V* and can switch loads of up to *16A* at *220V*:

<img src="images/relais_rf_relais_t.png" width="80%" height="80%" />


#### RF Receiver and Antenna

This model uses a *PCB antenna* which can be seen in the picture below on the left side.

PCB antennas typically *perform poorly*: you either need a very strong *sender*, or you need to be *very close* to the device in order to control it. 

> [TIP]
> Occasionally, reception is so bad that the *remote control* needs to be within a *1m* range to the device. By cutting the *PCB trace* to the antenna and replacing it with a *17.3cm* wire, reception performace improves dramatically.


<img src="images/relais_rf_antenna_t.png" width="80%" height="80%" />

#### No Microcontroller

The circuit board has a rectangular elongated cutout, clearly seen on the above picture. 

This is where *WiFi*-enabled devices plug in a separate microcontroller board that takes care of communicating with *WiFi*.


*RF*-controlled boards like this one *do not need microcontrollers*. 




<img src="images/relais_rf_rx_t.png" width="80%" height="80%" />



Instead, close to the *antenna* you find a *chip* that hosts the *radio receiver circuit*, and a *13.560MHz* crystal that tunes it to *433,92MHz*.




#### Power Supply

The discussed device can be directly connected to *AC mains*. 

The majority of the remaining components on the board are resposible for supplying *DC* voltages to the electronic components, i.e. *diodes* for rectification, and the large *electrolytic capacitors* to *smoothen voltage ripple*.

> [!CAUTION]
> Note the *absence of a fuse*, and missing proper physical separation of *AC* and *DC* parts on the PCB.




<img src="images/relais_rf__ams1117_2_t.png" width="80%" height="80%" />

In the upper right corner of the board, a commonly used *AMS1117* voltage regulator chip provides a stabilized *3.3V* and can deliver up to *800mA*.

#### Button

On the backside, a *push button* is located. This is used to *pair* the *RF receiver* with the *remote control*. 

*Pairing* is required so that the *receiver* learns the unique hardware code sent by the remote control. After pairing, the device *specifically listens* to the remote control code(s) you paired it to.

Next to the button, you see an *LED*. It is used to provide *feedback*, i.e. to indicate whether a certain button press sequence has enabled *pairing mode*.


<img src="images/relais_rf_back_open_t.png" width="80%" height="80%" />

#### Pairing Process
Since most *RF receivers* use the same *standard RF receiver chips*, pairing is performed in a similar manner for most devices:

1. **Reset:** most receivers require an initial *reset* that can be invoked by pressing the button *eight* times. The *LED* typically flashes on success.
2. **Enter Pairing:** to enter pairing mode, either press the button *once*, *twice*, or *three times* and watch the *LED*. It lights up constantly when in *pairing mode*. If short button presses do not work, try holding the button for *2-3s*.
3. **Pair Remote Control:** While in pairing mode (the *LED* lights constantly), press a button on the *remote control*. On success, the *LED* starts blinking or turns off. The *receiver* is now *paired to the remote control*.


> [!TIP:]
> Some devices allow pairing with multiple remote controls. Repeat the pairing process to pair the device with another remote control. Perform a *reset* to clear all *paired remote controls* from the device.


#### Conclusion

The examined device comes with the fundamentally required components (albeit in a potentially hazardous board design):

* Power Supply
* RF Receiver with Button and LED
* Relais


### WiFi Receiver

A device designed to be controlled via *WiFi* (instead of *RF*) shares some components but requires also a few changes.

Here is a similar device which is *WiFi*-controlled:

<img src="images/relais_wifi_front_t.png" width="80%" height="80%" />


#### Opening

The two housing parts are held together by four clips. You can pry them open with a screwdriver. 


<img src="images/wifi_relais_open_t.png" width="80%" height="80%" />



#### WiFi Module

A separate breakout board marked *LN-02* is piggy-backed onto the main board. 

On the top rim, the PCB *WiFi antenna* is seen:

<img src="images/wifi_relais_ln02_t.png" width="80%" height="80%" />

> [!NOTE]
> The *plug-in piggy-back* board illustrates how these devices are manufactured: based on desired control type, the *WiFi* board can be plugged into the main board, or left out. Plug-in boards with different *WiFi*-enabled microcontrollers can be found, depending on microcontroller market prices and availability.





#### Microcontroller

The microcontroller is a *LN882*, produced by *Lightning*. This microcontroller is comparable in features to the well-known *ESP8266* from *Espressif*.

<img src="images/wifi_relais_ln02_close2_t.png" width="80%" height="80%" />

> [!TIP]
> For the longest time, *WiFi*-enabled devices used original *ESP8266* microcontrollers that could easily be reprogrammed. Newer devices use less documented variants. Various [Open Source Projects](https://openbekeniot.github.io/webapp/devicesList.html) aim to document, access and reprogram them. There are [detailed instructions](https://www.elektroda.de/rtvforum/topic4045390.html) for the *LN882* (albeit not in German, use Google translate).


#### Power Supply

A fuse resistor is present, as well as three large electrolytic capacitors. 


<img src="images/wifi_relais_front1_t.png" width="80%" height="80%" />

On the back, a *MB10* bridge rectifier and a *BP2525* transformerless *AC-to-DC* constant voltage converter turns *85-240V AC* directly to *5V DC* which is required to operate the *relais*.

A separate *AMS1117* provides the *3.3V* constant voltage required for the microcontroller.


<img src="images/wifi_relais_traces1_t.png" width="80%" height="80%" />

#### Board Design

The board and its traces show a better (safer) design: *Cut-outs* separate *AC* from *DC* parts, and while *Nin* and *Nout* are still connected (the cheap relais switches just one line and not both), the screw terminals for the *external switch* are *not connected* to *AC mains*.


#### Conclusion

A *WiFi*-controlled relais shares the same fundamental components:

* Transformerless Power Supply
* Relais

To control the relais, a separate microcontroller board is piggy-backed and digitally controls the *relais* via its *GPIO*. The *RF receiver* and its PCB antenna are missing here.


## Datasheets

[BP2525 AC-to-DC converter](materials/bp2525_datasheet.pdf)
[MB10 Bridge Rectifier](materials/mb10_datasheet.pdf)
[AMS1117 3.3V Voltage Regulator](materials/ams1117_datasheet.pdf)



> Tags: Relais, Remote Control, ASK, OOK, SRD

[Visit Page on Website](https://done.land/components/switch/relais/rfcontrolled?137944041230242855) - created 2024-04-29 - last edited 2024-05-02
