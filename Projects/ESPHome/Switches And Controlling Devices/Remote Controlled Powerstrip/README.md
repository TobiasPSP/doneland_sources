<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Remote Controlled Powerstrip

> Creating A PowerStrip That Can Be Controlled By EspHome And Home Assistant

In this project, I am building a *ESPHome device* that can control six *AC devices*: effectively, a remote-controlled powerstrip.


<details><summary>The story behind this project...</summary><br/>


Controlling *AC Devices* remotely can be a lot of fun and is very convenient, especially when you need to control devices in a lab (oscilloscope, soldering iron, fan, various lights and magnifying lights, 3d printer, filament heater, usb and bench power supplies, computer monitor, you name it...) or other hobby environment: 

Rather than searching for power buttons (often in inconvenient locations), simply turn devices on or off via  smartphone app, or create physical dashboards with all important power buttons snug together in one place.

### Tuya Smart Plugs
When I started this, I used *Tuya WiFi Smart Plugs* that can be controlled via smartphone apps like *Tuya* or *SmartLife*.


<img src="images/smart_plug_side_overview_t.png" width="60%" height="60%" />


### Home Assistant and ESPHome
That worked well, however I did not like the smartphone apps, so I integrated them into *Home Assistant*. That also worked amazingly well. Now I was able to build my own *dashboards*.


<img src="images/proj_6_ac_example_ha_dashboard.png" width="100%" height="100%" />

Since *Home Assistant* and *ESPHome* can beautifully team up, I also built some physical dashboards with real buttons, so I now was able to conveniently control all my electrical devices from one place.

This is where this story could find its *happy end*, and there would have been no need to start this project.

However, while working with the solution above, I started to experience its *issues* and *shortcomings*.

### Randomly Going Offline

At first, some of the *Tuya smart plugs* occasionally and randomly started to go offline, requiring me to *again* climb behind devices and manually toggle the *smart plug*.

I searched and investigated but never found a solid reason for this odd behavior. When I temporarily cut power to the smart plugs, they started to respond again. Waiting for a while would also magically solve the problem. Both was no option though.


> [!NOTE]
> This issue wasn't terribly limiting nor did it occur with a lot of plugs, or regularly. Still, it made me wonder how reliable this approach was.

### Interference On Close Distance

I then noticed that the plugs affected were always the same. Many plugs never exposed this odd behavior and worked rock-solid. 

Replacing the affected plugs did not change much. I then noticed though that the affected plugs were always located in close proximity to other *smart plugs* (a few of them in a *power strip* for example).

Apparently, these devices aren't properly shielded and may interfere with each other when used very close together.

At this point, I was almost ready to skip using *power strips*, and place the *smart plugs* further away from each other.


### Cloud-Dependent

Then we had a temporary *Internet outage* which made me realize the hard way how the *Home Assistant Tuya integration* really works: it uses exclusively the *Tuya Cloud API*, so when the *Internet* is down, so are all smart plugs. 

That's unfortunate because the official *Tuya* and *SmartLife* smartphone apps continue to work even without *Internet connectivity*. They use the *local fallback API* (that is also used by the *Tuya Local* integration).

*Internet outages* aren't very common in our region, and in this unlikely event I could always fall back to using the official smartphone apps, so again there was a workaround available. However, the issues and workarounds required seemed to add up, and this experience left me wondering *what else* might happen to the *cloud backend* that could mess up my setup.

The answer came a few weeks later when the *Tuya integration* did not load correctly and required a *new authentication*. 

> [!NOTE]
> When you start using the *Home Assistant Tuya Integration*, it asks you to *authenticate* it with your *Tuya* or *SmartLife* app. Basically, it requests an *API key*. By design, this needs to be done only once and doesn't differ from other web services.   

Only, I wasn't able to re-authenticate: no matter how often I tried, the error message kept coming back, and I realized that there really isn't any good logging which would enable users like me to better understand what's going on and who is causing the issue. 

As it turns out, I wasn't the only one affected, and the culprit was with a hickup at the *Tuya Cloud servers*. The (surprisingly approachable) *Tuya technical support* worked on it and increased server capacity, and since then the issue never came back. However, this only intensified the feeling that with my current solution, I was trusting a lot of things to work that were beyond my control: Internet connection, Tuya cloud, local interference, and bugs and shortcomings in the still relatively fresh *Tuya integration*.

### Power Consumption

One of the reasons why I started using *smart plugs* all over the place was to get a better understanding of power consumption: these awesome little *smart plugs* come with a quite good *power monitor*. The results have been surprising, and I was able to identify a few power hogs (for example our beloved but 15 years old big refrigerator). 

Monitoring power consumption backfired at the *smart plugs* though: it turned out that they consume a few watts themselves. They are pretty efficient, taking only *1-2W*, but with a lot of these plugs deployed, it adds up. Even more so since these plugs use *simple and cheap mechanical relais* that are renown for being *rugged* and *dependable*, but also *power hungry*.

So I started wondering whether it is really smart to operate one dedicated microcontroller per plug. If I wanted to control multiple devices in close proximity anyway, why not just take *one* microcontroller and have it control a bunch of devices? While at it, why not using *power-efficient* and *noise-free* solid state relais (*SSR*)?

### The Project

This project was born: one *ESP32* - running on *ESPHome firmware* - controls a number of *AC sockets* via *solid state relais*. This should address and solve all my issues:


* **No cloud:** *ESPHome* is a completely *local* solution under my full control. No outages when the *Internet* is down or the *Cloud service* has hickups. Plus, since requests are not routed via a *cloud service* anymore, the response times with *ESPHome* and direct communications should be much faster.

> [!NOTE]
> Response times with *Tuya* can be momentarily, but can also take up to a few seconds. This seems to be random and beyond user control, probably depending more on how the *cloud service* is queuing requests coming in from  the entire world.

* **No interference:** Since I am using just one microcontroller, there is no pile up of unshielded and cheap microcontrollers in close proximity anymore. 
* **Power-efficient:** I need to run just one *microcontroller*, and triggering an *SSD* relais takes just a few *mA*.


</details>



<details><summary>Disclaimer and Safety Warnings</summary><br/>

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

## Overview

Here is the fundamental concept of this *ESPHome PowerStrip* with all the fundamental parts:


<img src="images/circuit_concept_esphome_powerstrip.png" width="100%" height="100%" />

### Microcontroller

Since this power strip is supposed to be remotely controllable via *ESPHome* and *Home Assistant*, it requires a *WiFi-enabled microcontroller*. You need a microcontroller that is [supported by ESPHome](https://done.land/tools/software/esphome/introduction/provisionnewmicrocontroller#supported-microcontrollers) and that has at least *four available output GPIOs* (for a *four-socket-powerstrip*; one *GPIO* per socket).

For prototyping and testing, I am using a *ESP32 DevKitC V4* as there are *expansion boards* available for it that make prototyping a breeze. For production, I am using a *ESP32 S2 Mini* due to its much smaller foot print. Both microcontrollers come with *WiFi capabilities* and provide sufficient general purpose *GPIO*.


<img src="images/6xsocket_wifi_proj_parts_microcontroller_t.png" width="100%" height="100%" />



Here's a quick comparison of sizes for three suitable and popular *ESP32*-family members: *ESP32-C3 Supermini*, *ESP32-S2 Mini*, and *ESP32 DevKit*:

<img src="images/esp32_family_sizes_illustration_t.png" width="60%" height="60%" />

### Relays
Switching is performed by a *relay* (one per socket). If you need to switch small loads only (less than 400W), you can use very cheap and small *solid state relay boards* such as *G3MB-202P*. Such boards are small, come with *one*, *two*, *four*, or more relais, can be triggered directly via *GPIOs*, work with *3.3V* triggers, and are cheap. 

<img src="images/6xsocket_wifi_proj_parts_ssr2_t.png" width="60%" height="60%" />

Once you need to switch higher loads, you can either use mechanical relais that are often rated for *10A* or *16A*.

<img src="images/relay_mechanical_illustration_t.png" width="60%" height="60%" />

> [!CAUTION]
> When using a mechanical relais, make sure it has a *flyback diode* that takes care of high voltage spikes when the relais turns off and its magnetic field collapses. Also make sure your *5V power supply* provides enough current. Mechanical relais require much more current to operate than *SSR*.

Or, you use industrial *DA (*dc trigger-ac load*) SSR relais which are available in almost any strength:

<img src="images/ssr_da_40_illustration_t.png" width="40%" height="40%" />

> [!CAUTION]
> Legit industrial SSR are costly. If you get these for cheap, divide their ratings by factor 4. Fake SSR typically use thyristors rated for half the claimed load, and might catch fire when used close to their claimed maximum ratings. A *40A SSR* from doubtful origin can typically be safely used for up to *10A loads* (entirely your own risk, the only safe way to find out is disassembling the SSR and looking at its internal parts). Note also that SSR switching loads of more than 1-2A **require a heat sink**.

### Power Supply
Most *SSR* and *mechanical relais* require a *5V power supply* (the trigger signal can be *3.3V*). 

The safest way is adding completely shielded AC power modules like the ones from *Hi-Link*. If you are using *solid state relais*, you could use the *PM01* power supply that is good for *5V* and *600mA*.  

<img src="images/ac-power-pm01-illustration_t.png" width="40%" height="40%" />

If you want a little bit of security margin, or use mechanical relais, you may want to use the *5M05* which can deliver up to *1000mA*:

<img src="images/ac-power-5m05-illustration_t.png" width="40%" height="40%" />

### Sockets
Obviously, the power strip needs rugged sockets to plug in devices. You may want to either use pluggable sockets that you can plug into your housing.



<img src="images/6xsocket_wifi_proj_parts_socket_t.png" width="80%" height="80%" />

You can also use *DIN rail plugs* which are especially easy to mount to an aluminum rail that can be screwed into a casing:

<img src="images/socket-din-1_illustration_t.png" width="30%" height="30%" />

Probably one of the safest and easiest approaches is to purchase a power strip with individually switchable sockets, then use this as a base, and replace the switches with your relays.

<img src="images/powerstrip_individual_switch_t.png" width="100%" height="40%" />

### Signal LEDs
If the power strip is going to be located inaccessibly under a table or behind a chair, then *signal leds* won't help much - which is why they are completely *optional*.

If you implement them, then they should work *without requiring additional GPIOs* or complex programming. Instead, they need to work with the *same GPIO that switches the plug*.


<img src="images/6xsocket_wifi_proj_parts_led2_t.png" width="30%" height="30%" />

There are a few ways of implementing this:

* **Two LED:** using a *red* and a *green* LED in opposite direction is the easiest solution: one *LED* lights up when the *GPIO* is *high*, and the other one lights up when the *GPIO* is *low*. This solution can also be used with a *single RGB LED* provided it has *six* (and not *four*) legs so each *LED color* can be wired independently.
* **Bi-Color Bi-Polar:** *bi-color bi-polar LED* have two legs and can emit two different colors, depending on the polarity you use. To run such LED on one *GPIO*, a simple and cheap *OpAmp* is needed.
* **Bi-Color and RGB with Common Anode/Cathode:** Any other multi-color LED has either a *common anode* or a *common cathode*, so all *LED colors* share one side electrically. To use such *LED* on one *GPIO*, a cheap *dual OpAmp* is needed.

> [!TIP]
> Of course you can expand on this project, and add any type of visual indicator you want, including OLED displays or other fancy solutions. For this project, the requirement was to focus entirely on the switching part, and not congest the *ESPHome configuration* with anything else.


> Tags: Plug, Smart Plug, Home Assistant, ESPHome

[Visit Page on Website](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip?349454081302245855) - created 2024-08-01 - last edited 2024-08-01