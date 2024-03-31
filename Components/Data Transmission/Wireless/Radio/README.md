<img src="/assets/images/radio.png" width="100%" height="100%" />
 
# Radio Transmission

> Electromagnetic Waves Transfer Data From A To B - No Wiring Required 

*Electromagnetic* waves can invisibly transfer information through the air, and we all use this technology in *smartphones*, with *WiFi*, *walky talkys* and even when we grab a *remote control*.

> [!NOTE]
> Do not confuse *radio waves* with *infrared light* (**IR**) which is also used to transfer information through the air. **IR** is *light* with a wave length invisible to the human eye and often used in *remote controls*. Since it is *light*, it needs a direct *line of sight* between *sender* and *receiver*.

*DIY* projects can use various radio technologies to transmit data wireless.

## Overview
Radio waves are emissions to the *public*: anyone in the vicinity can detect and read them. Even more important: anyone can *interfere* with anyone else in a radio spectrum.

Many important *public services* rely on robust radio transmission: emergency services, military, infrastructure, etc. This is why sending (and *receiving*) on radio frequencies is highly regulated in most countries.


### Frequencies By Region

When selecting radio devices, here are frequency ranges that are most likely *legal to use*:

| Region  | Frequency (MHz)  |
| --- | --- |
| Europe | 169, 433, 868 |
| North America | 300, 915 |
| Asia | 169, 433 |

> [!CAUTION]
> Always make sure you familiarize yourself with the legal regulations *in your particular country*. This table is just a *rough indicator*. Additional rules apply: the maximum radio emission is *limited*. For details, see below.

## Radio Services in DIY

In *DIY* projects, a variety of radio protocols and use cases exist:

* **Pure Data Transmission:** small *sender* and *receiver* allow you to send *raw digital data* from *A* to *B*, i.e. sensor information or to control devices like *garage doors*. You are completely free, and it is completely *up to you*, what kind of information you send and receive, and how you encode it.
* **LoRa (Long Range):** built on the latter, *LoRa* employs a standardized radio protocol designed to sustain noise. It can be used to bridge wide distances and includes *mesh* technology.



## Picking Frequencies
Obviously, picking a frequency is the initial and fundamental step in designing a *radio project*, for two reasons:

* **Legal:** you *must* pick a frequency that is *legal to use* in your country. Else, you may be *interfering* with other services, and may become *liable* for damages you cause. In addition, (severe) legal punishment is possible even if the risk of detection is low with low emission devices.
* **Technical:** when you have the *choice* of multiple *legal* frequencies, your *use case* determines which one to choose. The *lower* a radio frequency is the better can it pass buildings (walls, doors). The *higher* a frequency is the more does it behave like *light* and needs a *free line of sight* between sender and receiver. For example, if you live in a densly populated city in *Europe*, the *433MHz* band can pass buildings better than the *815MHz* band. If you'd like to set up a *data transmission* with free *line of sight*, the *815MHz* band works better (lower noise).

### Legal Considerations
Most countries designate frequency ranges for *free public use*, and we all use these frequencies every day: *hearing aids*, *wireless microphones*, *garage door openers*, *wireless door bells* etc. all use these frequencies.



In almost every region of the world, *band plans* exist that allocate frequency ranges for  *license-free* radio communications.

> [!NOTE]
> In addition to *regional* frequency bands (see below), there are *global* standards for *WiFi*: *2.4GHz* and *5GHz*. While there may be slight variations in the channel use, the *WiFi* frequencies can be used almost anywhere on this planet.

To check your region, you first need to know the *license plan(s)* in effect. Here is a list with examples showing the most commonly used *band plans*:

| Area | Band Plan |
| --- | --- |
| Europe | EU433, EU863-870, WiFi, BlueTooth
| South America | AU915-928
| North America | US902-928 |
| India | IN865-867 |
| Indonesia | AS923-925 |
| Malaysia | AS920-923 |


> [!NOTE]
> The *name* of a *band plan* already suggests the *frequency range*. While not the entire frequency range is free for you to use, this information is sufficient to pick suitable breakout boards. For example, a *LoRa* boards exist for *433*, *868*, and *915 MHz*. The first two can be used in the *EU*, and the *915MHz* version would be suitable for the **US**.

Some regions (like the **EU**) *harmonized* band plans among their members. Other countries regulate individually. The *Asian* region frequently uses *AS923-925* but there are exceptions. Always check for *your* country.

Likewise, *South America* typically uses *AU915-928*. Countries like *Mexico* adopted the *North American* standard *US902-928*.

> [!TIP]
> There may also be additional *national* opportunities. For example, in the **US**, *short range devices* can legally use frequencies as low as *300-390MHz* (i.e. *garage door openers*). In most other areas of the world, this band is exclusively reserved for military.



## Legal Radio Protocols
As you read above, frequencies are organized in *band plans*. The details regulate how a particular portion of frequencies can be used.

Among this fine print, it is regulated *what kind of radio services* you can use. 

For example, the popular *Citizen Band* (**CB**) radio is free to talk to your neighbor or friends on a *walky talky*. 

You *cannot* use this frequency in *DIY* projects to transmit digital sensor information, though.

Which is good. If anyone transmitted anything on a frequency, the result would be interference. You most likely do not want your neighbors' DIY *weather station* interfere with your **CB radio** chats by inserting bursts of digital noise transmissions.

## Maximum Radio Emission Power
The band plan also regulates the maximum radio power or *emission* (*ERP*, *Effective Radiated Power*). 

The more powerful radio emissions are, the stronger is the signal, and the wider is the distance you can bridge.


### Watt and +dBm
The maximum legal emission power can be quantified in raw emission power expressed either in *Watt* or in *dBm* (which is essentially the same, just *logarithmic*), i.e. *10mW/+10dBm*, *100mW/+20dBm* or *10W/+40dBm*. 

### Effective Radiated Emission (ERP)
**ERP** (*Effective Radiated Power*) is a more meaningful expression: what matters here is the *effective* radiated power. This takes into account what the radio power is like at the *receivers' side*. So it also takes into account the *antenna* and its *directivity*:

When you connect a highly directional *antenna*, the total radio power is radiated in one narrow direction, just like *light* in a highly focused *flash light* or a *laser beam*. 

> [!TIP]
> If you are restricted by a certain emission threshold but *free to use* any antenna you like, then using a highly directional antenna can multiply the distance you can gap by multitudes.


#### Security By Obscurity
While extending the reach through more radio power sounds great at first (*"the more the better"*), it extends the area in which you can interfere with others. 

For most use cases, a high radio power is not needed and even counter-productive: your *garage door opener* in *Germany* typically does not need to be received in *Argentina*. Especially with *DIY* projects, a tiny *ERP* may be all you need to gap the few meters or 100m you need for your project.

> [!TIP]
> *Security by Obscurity* is another important principle to keep in mind: a low ERP and a low maximum radio distance does not only *limit interference with others*. It also *shields you from others*. Rather than *encrypting* and *protecting* your data, a low *ERP* often much more effectively prevents others from listening in.



## Free Voice Radio Frequencies

There are additional free-to-use radio frequencies designated for analog and/or digital *voice communications* (i.e. walky talkys):

| Name | Frequency |
| --- | --- |
| CB (Citizen Band) | 27MHz |
| FreeNet | 149MHz |
| LPD (Low Power Device Voice) | 433MHz |
| PMR (Personal Mobile Radio) | 446MHz |
| FRS (Family Radio Service) | 462-467MHz |
| GMRS (General Mobile Radio Services) | 462-467MHz |
| MURS (Multi-Use Radio Service) | 151-154MHz |

> [!NOTE]
> The table presents an overview only. Additional rules exist. For example, *FreeNet* is available in *Germany* only. *PMR* is available in the *EU*. *FRS*, *GMRS*, and *MURS* are available in the *US*. *GMRS* requires an (easy to obtain) license. For *MURS*, additional regulations apply.

These frequencies are *not usable* for *DIY projects* as they are highly regulated, require *certified devices* and prohibt the transmission of radio data other than voice.


> Tags: Frequency, Garage Door Opener,  Band Plan, WiFi, FreeNet, LPD, PMR, FRS, GMRS, MURS

