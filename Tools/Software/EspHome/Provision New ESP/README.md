<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Provision New Microcontroller

> Turn Your Microcontroller Board Into A Fully Managed ESPHome Device

Whenever you want to create a new microcontroller-based electronics project with *ESPHome*, the first step is to take a supported microcontroller board and *provision* it.

*Provisioning* means that you upload *ESPHome firmware* to the microcontroller. 

Once you have done this, your microcontroller can be updated *wirelessly* over *OTA* (*over-the-air* updates) and no longer needs *USB cables*, tools, and awkward button presses.

## Supported Microcontrollers

You can provision any microcontroller that is supported by *ESPHome*. This includes the popular *ESP8266* and *ESPS* (the "classic" *ESP32*).

> [!NOTE]
> *ESPHome* does support newer *ESP32* family members such as *S2*, *S3*, and *C3*. However, support for these is still under active development, so expect a few quirks and issues.

*ESPHome* is expanding constantly: meanwhile you can also use microcontrollers from other vendors, including *Raspberry*, *Beken*, and *Realtec*.

The latter two additions are especially important because *Beken BK72xx* and *Realtec RTL87xx* microcontrollers are often found inside commercial *smart devices* such as *sensors*, *lamps*, or *plugs*. You can replace their default firmware with *ESPHome* and effectively free these devices from their *vendor cloud*.

> [NOTE]
> In practice, this is not always trivial since commercial devices typically have neither USB ports nor UART chips to upload new firmware.


## Two Provisioning Strategies

When turning your microcontroller into a *ESPHome device*, you have two options:

* **Provisioning First, Programming Later:** You are uploading a basic *ESPHome firmware* that doesn't do anything beyond providing the default connectivity. Once this is done, your microcontroller is ready to be joined to your *WiFi*, can be autodetected by *Home Assistant*, and most importantly: you can now upload a *more specific configuration* at any time *wirelessly*. 
* **Provisioning And Programming In One Step** If you already *know* what your device is supposed to do, and you have already created a *configuration* for it, describing your hardware setup, then you can initialize your microcontroller directly with *your specific firmware*.

### Testing and Provisioning

This is an excellent use case for the *provisioning only* approach:

When you order new microcontroller boards in larger quantities, it is a good idea to test them right after delivery to not miss any return deadlines. Some users upload small test sketches to see if all is fine.

#### Provisioning = Efficient Hardware Test
A much more efficient approach is to *provision* new microcontrollers right away. All you need for this is a browser and a USB cable. If provisioning succeeds, then you know the microcontroller works as expected, and you have successfully tested all vital areas of the microcontroller.

#### Quick-Starting New Projects
Once you are ready to put one of your microcontrollers to work, just power it on. 

Thanks to provisioning, it automatically connects to your *WiFi* and is picked up by *ESPHome*. 

You can *wirelessly* upload any code changes without the need to press any physical buttons on the board or even search for a *USB cable*. You can continue to manage, edit, and upload to your microcontroller even if it is long burried unaccessibly inside some device.

## Provisioning Only
In the recipe below, you are *provisioning* your microcontroller only. 

You do not need any specific *prerequisite* or *configuration* for this step, and in fact you do not even need *ESPHome*. A compatible web browser (i.e. *Chrome*) is all you need.

> [!TIP]
> There are a few microcontrollers and boards that do not work with [ESPHome Web Tools](https://web.esphome.io/), for example *ESP32 S2 Mini*. Learn [how to provision ESP32 S2 Mini and similar boards](https://done.land/tools/software/esphome/provisionnewesp/workarounds).


<img src="images/s2_mini_top_overview_t.png" width="40%" height="40%" />

1. Connect the microcontroller with a *USB cable* to your computer. In your browser, navigate to [web.esphome.io](https://web.esphome.io/), and click *CONNECT*.

    <img src="images/a_webinstaller.png" width="100%" height="100%" />

2. In supported browsers (i.e. *Chrome*), you now see the microcontroller board that is connected to your *USB port*. Select it, and click *Connect*:

    <img src="images/d_pair_esp.png" width="100%" height="100%" />

    > [!IMPORTANT]
    > If you can't see your connected microcontroller in the list, you may have to manually putting it into *firmware download mode* by holding the *boot* button while pressing the *reset* button. Release the *boot* button **after** you release the *reset* button.

3. You are now presented with a few things you can do with your connected microcontroller. Click *Prepare for first use*:

    <img src="images/e_menu.png" width="100%" height="100%" />

4. A dialog explains that you are about to upload the basic *ESPHome firmware* to your microcontroller. Click *INSTALL*. 

    <img src="images/a1_firstuse.png" width="100%" height="100%" />

5. The *ESPHome default firmware* is copied to your microcontroller. This can take a few seconds.

    <img src="images/b1_install.png" width="100%" height="100%" />

6. Once the installation is complete, you are greeted with a success message. Meanwhile, your microcontroller reboots and starts with its brand new *ESPHome firmware*. You may want to press its *reset* button to make sure it leaves the *firmware download mode* and really restarts. Click *CLOSE*.

    <img src="images/c1_done.png" width="100%" height="100%" />

7. To complete *provisioning*, you can connect the microcontroller to your *WiFi*. This step is optional. If you don't know yet where you are going to use this microcontroller, click *CLOSE* (and you are done). Else, click *CONNECT TO WI-FI*. You are then asked to select the *SSID* and enter the *WiFi password*.

    <img src="images/d1_connect_wifi.png" width="100%" height="100%" />

8. After the microcontroller successfully connected to your *Wifi*, provisioning is successfully completed.

    <img src="images/e1_provisioned.png" width="100%" height="100%" />

> [!TIP]
> You can use this method not just for provisioning, but also to *re-connect* to a provisioned microcontroller at any time in the future. This way, you can view its logs or change its *WiFi* settings.



> Tags: EspHome, Home Assistant, Provision, Initialize, Configuration

[Visit Page on Website](https://done.land/tools/software/esphome/provisionnewesp?261597071511241259) - created 2024-07-01 - last edited 2024-07-10
