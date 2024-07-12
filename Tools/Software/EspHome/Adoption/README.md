<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Adoption

> Adopting Provisioned ESPHome Devices 

Once you have *provisioned* a *ESPHome* device and made sure it can connect to your *WiFi*, it automatically surfaces in *ESPHome Dashboard* and can be *adopted*.

If you created your own *firmware file* from a specific *configuration* and uploaded this to the microcontroller, it is already part of your *ESPHome Dashboard*, and you can skip this article.

*Adoption* only applies to devices that use a *generic ESPHome firmware*. Such devices can potentially be added to *any* ESPHome Dashboard instance.

## Adopting New Device
Once a *provisioned ESPHome device* is connected to your *WiFi*, the *ESPHome Dashboard* picks it up and shows a green *DISCOVERED*:

<img src="images/1_adopt_tile_esphome.png" width="50%" height="50%" />

Note that the device uses the same *name* that was shown by the *ESPHome Web Tool* when you configured its *WiFi access*.

> [!TIP]
> If your device does not surface in your *ESPHome Dashboard*, then *ESPHome* can simply not find it. You either did not yet configure its *WiFi parameters*, or the device and *ESPHome* are connected to different networks (i.e. *WiFi* network and *wired network*), so *mDNS* does not work.


You can now *Adopt* the device.

<details><summary>Understanding ESPHome Adoption</summary><br/>


When *ESPHome* discovers a new device with a *generic firmware*, it offers to *add this device* to your *ESPHome environment*. If you accept by clicking *ADOPT*, you can assign a new name to the device, and *ESPHome* creates a *configuration* for this device, including unique access keys.

Once the device is adopted, you turned it into a *specific device*. You can now edit and update its *configuration*, and install new firmware wirelessly - but only in the *ESPHome instance* that *adopted* the device. The device is now no longer *generic* and can no longer be adopted by other *ESPHome instances*.


</details>


1. Click *Adopt*. *ESPHome* opens a dialog, and you can now assign a meaningful name to the device. Click *ADOPT*.

    <img src="images/2_adopt_addname.png" width="50%" height="50%" />

2. *ESPHome* now creates a specific *configuration* for your device that you can later use to configure it. The new configuration needs to be uploaded to the device (actually, a *firmware* representing the configuration). Click *INSTALL* if you want to do this now, or click *SKIP* if you want to adjust the configuration first. In this example, click *SKIP* because there are a few important adjustments to do.

    <img src="images/3_adopt_skip.png" width="50%" height="50%" />

3. In *ESPHome Dashboard*, look for the tile that represents the device. In its upper right corner, you should see the label *ONLINE*. The adoption process has renamed the *friendly name*, but the device still uses the awkward temporary name for its *hostname* (*mDNS name*):

    <img src="images/3_adopt_tile.png" width="50%" height="50%" />

4. To rename the *hostname*, click the *three-dot* menu, then click *Rename hostname*.

    <img src="images/4_adopt_rename.png" width="50%" height="50%" />

5. Enter the new host name. You can only use lower case letters, numbers, and a few special characters. Click *RENAME*.

    <img src="images/5_adopt_rename.png" width="50%" height="50%" />

*ESPHome* now recompiles the firmware and uploads it to your device. Click *CLOSE* to close the terminal window.

Once the device has rebooted, you are done: your device now uses the name you assigned, and the device host name has also been changed.


<img src="images/6_adopt_done.png" width="50%" height="50%" />

You can now click *EDIT* and review or expand your device *configuration*, save it, then click the *three dot* menu and choose *Install* - *Wirelessly* to program and work with your new device - but only in the *ESPHome instance* that *adopted* the device. The device is now no longer *generic* and can no longer be adopted by other *ESPHome instances*.


> Tags: EspHome, Adopt

[Visit Page on Website](https://done.land/tools/software/esphome/adoption?010732071511241259) - created 2024-06-07 - last edited 2024-07-10
