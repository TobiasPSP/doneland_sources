<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Provision New Microcontroller

> Turn Your Microcontroller Board Into A Fully Managed ESPHome Device


*Provisioning* a new microcontroller is always the first step in an *ESPHome project*: it turns a generic microcontroller into a fully managed *ESPHome device*. *Provisioning* uploads *ESPHome firmware* to the microcontroller. 

Once done, the microcontroller can receive firmware *wirelessly* (no need anymore for *USB cables*, tools, and awkward button presses) and is fully manageable by your *ESPHome instance*.

## Supported Microcontrollers

You can provision any microcontroller that is supported by *ESPHome*:

* **Espressif:** *ESP8266*, *ESP32* including newer family members like *S2*, *S3*, *C3*. The latter are still under active development, so expect a few quirks and issues.
* **Raspberry:** *RP2040*
* **Beken and Realtec:** *Beken BK72xx* and *Realtec RTL87xx* are often found in commercial *smart devices* such as *sensors*, *lamps*, or *plugs* and can be converted to *ESPHome devices*, effectively freeing them from proprietary vendor clouds and turning them into locally controlled devices.

> [!NOTE]
> In practice, this is not always trivial since commercial devices typically have neither USB ports nor UART chips to upload new firmware.


## Provisioning Strategies

*Basic provisioning* only requires a *web browser*. After provisioning, the microcontroller can be used *at any time - now or later - for a specific project.

*Integrated provisioning* occurs automatically when you create a *ESPHome configuration* and design a particular *ESPHome device*.

<details><summary>Why Do Basic Provisioning?</summary><br/>

It's a valid question: why bother to peform a *basic provisioning* when a microcontroller gets provisioned *anyway* once you start a *ESPHome project* and create a *configuration* for a device?

#### Enable Wireless Access
The key benefit of *basic provisioning* is that it enables your microcontroller to receive *firmware updates wirelessly* without the need to install the initial firmware via the computer that is running **your instance of ESPHome**. Instead, with *basic provisioning*, you can *provision the microcontroller* using *any computer anywhere in the world*.

#### Enable Adoption
That's possible because *basic provisioning* is using a *generic ESPHome firmware* that is not yet bound to a specific *configuration* hosted by a specific *ESPHome instance*. Instead, this special firmware is *detectable by any ESPHome instance*, and once detected, can be easily *individualized* through an *adoption process*.

#### Test New Microcontrollers
*Basic provisioning* is also a good idea if you just want to *prepare* a bunch of microcontrollers for later use. As a welcome side effect, *basic provisioning* coincidentally tests the microcontroller and makes sure its components work as intended. It's a good idea to immediately apply *basic provisioning* to all new microcontrollers you purchase so you identify damaged items and can return them in time.

#### Speed Up Your Projects
Microcontrollers that have received a *basic provisioning* are ready for action: when it's time for a new project, simply take a provisioned microcontroller from your supply, and power it on.

Thanks to provisioning, they automatically connect to your *WiFi* and show in your *ESPHome dashboard* where you can *adopt* them: 

*Adoption* turns the *generic firmware* into a *specific device configuration* by creating a *configuration file* for it. Add a meaningful device name, set the devices' *mDNS host name*, and edit the *configuration* to reflect your hardware project - done.


</details>

## Basic Provisioning
Follow the steps below to apply *basic provisioning* to a microcontroller, for example to *test* and *prepare* a bunch of new microcontroller boards that you just ordered.


You do not need any specific *prerequisite* or *configuration* for this step, and in fact you do not even need *ESPHome*. A compatible web browser (i.e. *Chrome*) is all you need.

> [!TIP]
> If the *ESPHome Web Tool* used below does not work for your microcontroller, use alternate ways [to provision ESP32 S2 Mini and similar boards](https://done.land/tools/software/esphome/manualprovisioning) that use incompatible *USB/UART* connectivity.


<img src="images/s2_mini_top_overview_t.png" width="40%" height="40%" />

### Upload Generic ESPHome Firmware
In this first step, you upload generic *ESPHome firmware* to your microcontroller:

1. Connect the microcontroller via *USB cable* to your computer. Place the microcontroller in *firmware update mode*: hold its *boot* button while you shortly press its *reset* button. A *new usb device discovered* sound should play by your PC.
2. In a browser (*Chrome*, *Edge*), navigate to [web.esphome.io](https://web.esphome.io/), and click *CONNECT*.

    <img src="images/a_webinstaller.png" width="100%" height="100%" />

3. In supported browsers (i.e. *Chrome*, *Edge*), you now see the microcontroller board that is connected to your *USB port*. Select it, and click *Connect*:

    <img src="images/d_pair_esp.png" width="100%" height="100%" />

    > [!IMPORTANT]
    > If you can't see your connected microcontroller in the list, you may have to manually putting it into *firmware download mode* by holding the *boot* button while pressing the *reset* button. Release the *boot* button **after** you release the *reset* button.

4. You are presented with a menu. Click *Prepare for first use*:

    <img src="images/e_menu.png" width="100%" height="100%" />

5. A dialog explains that you are about to upload the basic *ESPHome firmware* to your microcontroller. Click *INSTALL*. 

    <img src="images/a1_firstuse.png" width="100%" height="100%" />

6. The *ESPHome default firmware* is copied to your microcontroller which takes a few seconds.

    <img src="images/b1_install.png" width="100%" height="100%" />

7. Once the installation is complete, you are greeted with a success message. Click *CLOSE*.  

    <img src="images/c1_done.png" width="100%" height="100%" />


8. Press the *reset* button on the microcontroller board to make sure it boots from the new firmware.

The device is now *provisioned*, however it is not yet connected to any specific *WiFi*. 

To actually use it in *ESPHome*, it needs to connect to the *WiFi* that *ESPHome* is connected to (see next step).

> [!TIP]
> Whether you provision the *WiFi access* as well or postpone this step to later is up to you. If you plan to use the microcontroller in your own environment, I recommend to *fully provision* it and add the *WiFi credentials* as well (see below).

### Connecting To WiFi
The provisioning process automatically re-connects to the device and shows this dialog:


<img src="images/d1_connect_wifi.png" width="100%" height="100%" />

If you do not want to configure *WiFi* at this point, click *CLOSE*. 

> [!TIP]
> You can always return to this point by connecting the microcontroller via USB cable, and opening [ESPHome Web Tool](https://web.esphome.io/) in your browser. Once the browser has connected to the microcontroller, click the *three-dot* menu to configure *WiFi access*.

To *fully provision* the device and make sure it can connect to your *WiFi* and be auto-detected by *ESPHome*, click *CONNECT TO WI-FI*. 

You can now select the *WiFi* and provide the *WiFi password*. The connection is then tested, and provisioning is successfully completed.

<img src="images/e1_provisioned.png" width="100%" height="100%" />

## What's Next
Once your microcontroller is *fully provisioned*, once you supply power to it, it connects to your *WiFi*.

*ESPHome* then automatically discovers the device and offers to [adopt](https://done.land/tools/software/esphome/adoption) it. Once *adopted*, you can start editing its *configuration* and using it.


> Tags: EspHome, Provisioning, WiFi

[Visit Page on Website](https://done.land/tools/software/esphome/provisionnewesp?261597071511241259) - created 2024-06-01 - last edited 2024-07-10
