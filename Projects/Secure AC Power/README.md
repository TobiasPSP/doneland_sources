<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Control And Secure AC Power

> Monitoring Power Consumption And Securing Lab When Away From Home




This article involves *dangerous AC currents*. Working with AC currents requires utmost caution and expertise. 


<details><summary>Disclaimer and Safety Warnings</summary><br/>

#### Warning
Handling AC currents can be extremely dangerous. Improper handling can result in serious injury or death. Ensure all safety precautions are taken and consult with a professional.

#### Using Insulated Housing
Always consider that not *just you* but **anyone** may be exposed to your device: kids, cleaning personnel, colleagues, family members. 

Temporary setups are *not ok* for anything exposing *live AC currents*. 

Always keep your prototypes *disconnected from AC* when not under your direct supervision **until you enclose the electrical components within an insulated housing**, ensuring all connections are secure and no live parts are exposed. Double-check the installation to make sure the housing is properly sealed and provides full coverage. Ensure there are no gaps that could expose wires or connections.


#### Disclaimer
The information provided in this article is for educational and informational purposes only. The author and publisher are not responsible for any injuries, damages, or losses resulting from the use or misuse of the information provided. Working with electricity is inherently dangerous and should only be performed by qualified professionals. Always follow proper safety procedures and consult a licensed electrician before attempting any electrical work.


#### Safety Guidelines
- Always turn off the power at the main circuit breaker before starting any electrical work.
- Use insulated tools and wear rubber-soled shoes to reduce the risk of electrical shock.
- Never work on electrical systems in wet or damp conditions.
- Verify that the power is off using a reliable voltage tester or multimeter.
- Do not touch live wires or components with bare hands.
- If unsure about any procedure, consult a licensed electrician.


</details>


I wanted to add a *power meter* and *mains switch* to my lab in order to monitor overall power consumption and also *secure* it when not at home. Obviously, you can apply this scenario to *any other room* or *scenario* involving *AC power*.

> [!TIP]
> Recently, a *smoldering USB cable* in the kitchen caught my attention. It was part of a USB charger for a *mist humidifier*. It caused a short circuit and was close to catching fire. Considering the *density* of devices of various origin and quality, power supplies and batteries, loose cables, and prototypes that can be found in a lab, it's a great idea to (a) cut off *AC power* when the lab is unattended, and (b) install a smoke alarm (if you haven't done so already).

Power consumption needs to be logged automatically, and there needs to be a way to turn power *on* and *off* from anywhere in the world (in case I forgot to check before going on vacation).

## Home Assistant
From the requirements, a device is needed that integrates with [Home Assistant](https://done.land/tools/software/homeassistant) unless you want to implement *logging* and *safe remote access* yourself:

* **Logging:** *Home Assistant* logs device data and allows for analyzing power consumption as well as viewing total consumption.
* **Remote Access:** It is easy to set up [secure remote access](https://done.land/tools/software/homeassistant/internetaccess) for *Home Assistant*

The cheapest and easiest way of integrating with *Home Assistant* is to look for *WiFi-enabled components* that support [Tuya](https://done.land/tools/software/tuya).

## Power Meter
Since the scenario involves *high currents* (after all, the *total consumption* of *many AC devices* needs to be *metered* and *switched*), a *safe* switching and metering component is required. **Do not** build one yourself (it's not worth it), and **do not** use a simple *smart plug with power monitoring* either (their mechanical relais can't handle high currents, even if their datasheets claim otherwise).

I decided to go with a *smart rail meter* that supports *WiFi* and [Tuya](https://done.land/tools/software/tuya). *Rail meters* use solid state switches that support currents well above what is required in this scenario. 

<img src="images/atorch_smart_rail_meter1_t.png" width="50%" height="50%" />

The *rail meter* I picked was an *Atorch GR2PWS* rated at *50-320V AC/100A/32KW*. There are similar devices from other vendors. They cost around €15-20.

> [!IMPORTANT]
> Pay **very close** attention to the exact device **model** you order: most vendors sell models with limited features that look just the same. You need a model that supports both *WiFi* and *Switching*.

Here are the different models for the *Atorch* device I used (along with the feature-limited models you want to avoid):

| Feature | GR2P | GR2PW | **GR2PWS** |
| --- | --- | --- | --- |
| Power Monitoring | yes | yes | **yes** |
| WiFi | no | yes | **yes** |
| Switch | no | no | **yes** |


## Wiring

Wiring is very simple: the device comes with two screw terminals: *N-IN* and *L-IN* are connected to *AC power*, and *N-OUT* and *L-OUT* connect to the devices.

> [!NOTE]
> *AC power* uses two lines: ***L** (Live)* and ***N** (Neutral)*



Tags: Plug, Smart Plug, Power Monitor

[Visit Page on Website](https://done.land/projects/controlandsecureacpower?099878071720241015) - created 2024-07-19 - last edited 2024-07-19
