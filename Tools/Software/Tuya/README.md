<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Tuya

> Using Chinese Tuya Smart Devices

[Tuya](https://www.tuya.com/) is a Chinese company offering an *IoT platform* for generic *IoT devices*: *wireless plugs*, *lights*, and more. 

<img src="images/tuya_logo.png" width="30%" height="30%">]

When you come across a *smart device* with *tuya* logo, the device is designed and manufactured by a generic company that prepared the *device firmware* so that it utilizes the *Tuya cloud services*. 

> [!NOTE]
> For *customers* there are no fees: just register a *free account* with *Tuya*. Vendors contract separarely with *Tuya* to get permission to use their cloud: even small *IoT companies* with no budget to set up their own *cloud* can sell *smart devices*.

## Why deal with Tuya?
Devices with *Tuya* logo are *WiFi*-enabled and microcontroller-based, typically available at exceptionally competitive pricing.

For example, a *smart electric plug* with built-in *power meter* is regularly sold for less than €3 at [AliExpress](https://aliexpress.com/). That's less than a maker would pay for the parts.

Typical *consumers* control *Tuya* devices via smartphone app: [Tuya](https://apps.apple.com/de/app/tuya-smart/id1034649547) or [SmartLife](https://www.tuya.com/product/app-management/all-in-one-app) both work.


### ESPHome And Home Assistant
What makes *Tuya smart devices* especially exciting is that they can be used as part of *automations* in [Home Assistant](https://done.land/tools/software/homeassistant) and other automation platforms. 

You can even replace the *firmware* on their internal microcontroller to completely take control, and disconnected any *cloud dependencies*.

* **Home Assistant:** comes with an official *Tuya integration* that discovers all *Tuya*-enabled devices and makes their *entities* (device features) accessible. The integration uses the *Tuya cloud API* and requires no changes at the device: very simple to set up and use. The downside is that any failure in any part of the cloud service tool chain is a ***single** point of failure*, and *Tuya devices* become inaccessible - whether your *Internet connection* fails, the *Home Assistant integration* has a bug, or the *Tuya cloud API* does not respond.
* **ESPHome:** most *Tuya*-enabled devices use *ESP8266*, *Beken BK72xx*, or *Realtec RTL87xx*. They are all supported by *ESPHome*, so you can *replace* the proprietary *firmware* with *ESPHome firmware*, turning the device into a locally controllable *ESPHome device*. This replacement requires *expert knowledge*, but in exchange you *eliminate* all dependencies to the *Internet* and *Tuya cloud API*. For *Home Assistant*, the device is now an *ESPHome device*, and the *Tuya integration* is not used.

### Use Cases
Whether you access **original** *Tuya devices* through the built-in *Tuya integration*, or whether you **convert** *Tuya devices* to *ESPHome devices*: you use *cheap but relatively powerful Chinese hardware* as part of your *home automation*:

* **Control Applicances and Their Power Consumption:** use *smart plugs* to turn appliances in your household on and off, based on other devices managed by *Home Assistant*, i.e. *buttons*, *dashboards*, or *sensor readings*. I.e. create a physical dashboard with push buttons to control different appliances anywhere in your home, including power consumption monitoring (most *smart plugs* come with *power monitoring functionality*).
* **Build Smart Fire Hazard Protection Systems:** cheap (but reliable) *wireless Tuya smoke detectors* can be turned into a sophisticated *fire alarm network*, and *Home Assistant* can turn on *sirens or alarm lights* when *any* of the smoke detectors triggers, or send off an *email*. Cost of commercial systems with such a feature set would be prohibitive for private homes.
* **Create Open-Source Hue-like Lighting:** There are ubiquous *Tuya* lights and led stripes available, and combined with *Home Assistant*, you can design your own open-source *home light system* that controls *scenes* and can turn on illuminations based on time of day, whether you are at home, or whatnot.

These, and the many other use-cases basically illustrate what *Home Assistant* enables you to do. *Tuya* just adds many more *controllable devices* at a very reasonable cost.

## Caveats

*Tuya* is a *cloud service* that works out of the box and requires next to no configuration - *very easy to use*. This comes at a price:

* **Privacy:** *Tuya* knows when you turn on a *smart plug* in your home. Whether that's of concern to you is:  up to you
* **Reliability:** *Tuya smart devices* may stop working when the cloud service stops working. This is always true for devices that you manage via the *Home Assistant integration* (that is *always* controlling devices via the *Tuya cloud API*). The *SmartLife app* can control devices *locally*, too, and may serve as a fallback in case of *Internet outage*.


> [!IMPORTANT]
> It may be ok if the living room light scenes stop working or the garden illumination does not automatically turn on in the evening. If you *rely* on *controlling crucial devices*, avoid *cloud-based* solutions or add a fallback strategy. Such a fallback is sometimes built into the devices: *smart plugs* have a manual switch that always works (provided you have physical access to it).


### Local Control
One way of limiting the risk and improving *reliability* is to control *Tuya devices* **locally**. This is not officially supported by *Tuya*, so it involves either *workarounds* or **replacing** *Tuya*:

* [Tuya-Local](https://github.com/make-all/tuya-local): an alternate integration for *Home Assistant* that controls devices *locally* and may work without *Internet access*. Setting up *tuya-local* requires *network configuration changes* and figuring out *Tuya secret device keys* - **per device**. It is a *workaround* based on *reverse-engineering the Tuya API*. As such, it may stop working when the *API* changes, it may not be compatible with all device types, and there are regular report that *Internet outages* still caused issues.
* [LibreTiny](https://github.com/libretiny-eu): open-source development platform for *IoT modules* used in *Tuya devices*. This ecosystem consists of tools like [Itchiptool](https://github.com/libretiny-eu/ltchiptool) to read and replace *firmware*, and [esphome-kickstart](https://github.com/libretiny-eu/esphome-kickstart) ready-to-use *binary firmware files* to replace the *proprietary firmware* with *ESPHome firmware*. With *LibreTiny*, you *permanently remove* cloud dependencies and turn the device into a *real local ESPHome device*.

> [!TIP]
> Replacing device firmware with *ESPHome firmware* (or any other) can be done in a number of ways: some exploit bugs in the original firmware and work *wirelessly* (i.e. [Tuya Cloudcutter](https://github.com/tuya-cloudcutter/tuya-cloudcutter). Others require opening and sometimes even de-soldering the microcontroller in order to upload a new firmware via *UART programmer*. Replacing *device firmware* is the only solid way of removing *cloud dependencies*, but it is not for the faint-hearted and requires either solid experience or considerable determination.

### Worth the effort?
*"Freeing"* a *Tuya device* from the cloud takes effort, so unless you are genuinely interested in the involved techniques, carefully consider it:

* **Cloud Works Great For Most Users:** Try the official *cloud* approach first, and test the stability **for yourself**. Any part of the *cloud* tool chain is a *single point of failure*: your network setup, ISP, *Home Assistant*, its integration, *Tuya* cloud servers, etc. This explains why the *majority* of users enjoys flawless operation while a few users are regularly hit by frustrating issues and interruptions. With a bit of luck, *Tuya devices* work great for you *as-is*.
* **Solving Old Problems By Creating New Problems:** Always carefully evaluate solutions that claim to work *locally* (like [Tuya-Local](https://github.com/make-all/tuya-local)). Controlling *Tuya devices* locally is based on reverse engineering of the *Tuya local API*, and the result may not be supported for all device types, may require assigning *static IP addresses* or other *network and firewall configurations*, and may *still* require that the official *Tuya cloud API* is regularly contacted to update keys. Such solutions may work beautifully for you, but they are just *workarounds* with a lot of *configuration effort* that *do not really solve* the underlying problem and can stop working at any time (if the *Tuya local API* changes).
* **Great Alternative, But Not For Free:** With [LibreTiny](https://github.com/libretiny-eu), there is a *great* alternative that truly *removes any cloud dependency*. Such a conversion is technically challenging though.


### Conclusion
Evaluate using *Tuya devices* with the official *Home Assistant Tuya integration* first: chances are this works amazingly well for you.

If it does not, or if you'd like to remove *cloud dependency* for other reasons, the only other alternative is to replace the device *firmware* altogether, and use a new firmware that does not require *cloud services* at all. 

If replacing the *device firmware* is over your head, then stick with the official *Tuya cloud*, and limit the use of *Tuya devices* to use cases that you can afford to become temporarily unavailable.







> Tags: Home Assistant, ESPHome, Cloud, Cloudcutter, SmartLife, LibreTiny

[Visit Page on Website](https://done.land/tools/software/tuya?501206071119243057) - created 2024-07-18 - last edited 2024-07-18
