<img src="/assets/images/homeassistant.png" width="80%" height="80%" />
 
# Provisioning Directly

> Provisioning A New Microcontroller Directly Via USB Cable

In the previous examples, the microcontroller was provisioned via a *binary firmware file* that was either downloaded from *esphome.io*, or downloaded from your *ESPHome Dashboard*. [ESPHome Web Tool](https://web.esphome.io/) or [Adafruit ESPTool](https://adafruit.github.io/Adafruit_WebSerial_ESPTool/) was then used to upload the *firmware file* to the microcontroller.

Here is another way to *provision* a fresh microcontroller. It *directly uploads* the *firmware* to the microcontroller without first exporting the *firmware* to a file.

## Prerequisites
There are *two rules* that need to be met in order to *directly provision* a device from within *ESPHome*: 

* **Direct USB-Connection To ESPHome:** the microcontroller must be connected via *USB cable* to the computer *that is running ESPHome*. When you run *ESPHome* locally, this is your own computer, but if you run *ESPHome Add-On* inside *Home Assistant*, it would be the computer that runs *Home Assistant*. Often, this is a *Raspberry Pi*. If it is physically accessible, connect the *USB cable* to one of its *USB ports*.
* **Compatible Microcontroller:** the microcontroller (board) must be compatible with [ESPHome Web Tool](https://web.esphome.io/). If you can't upload firmware with this tool, then you can't upload it directly, either, because *ESPHome* is using the same tool chain. So if you get connection errors with your microcontroller, you are limited to [manual provisioning](https://done.land/tools/software/esphome/introduction/manualprovisioning).


## Provisioning Directly
Here are the steps to *provision* a new microcontroller *directly* from within *ESPHome*:

* **Add New Device:** create a *New Device* in *ESPHome Dashboard*.
* **Connect To ESPHome:** connect the microcontroller via *USB cable* to the computer **that is running ESPHome**.
* **Install:** install the *firmware* directly to the microcontroller via *USB cable*. 

> [!TIP]
> Keep in mind that we are talking here about *provisioning fresh microcontrollers*. The approach discussed here may be a convenient way to *provision new microcontrollers*. Once a microcontroller runs *ESPHome firmware* (regardless of how you eventually uploaded it), it is typically receiving future firmware updates *wirelessly*.


### Visit ESPHome Dashboard

If you are using *Home Assistant*, click *ESPHome* in its *sidebar*.

<details><summary>How To Open ESPHome Dashboard Without Home Assistant</summary><br/>

If you have [installed *ESPHome* stand-alone](https://done.land/tools/software/esphome#installing-stand-alone-esphome-instance), you need to first start the local *ESPHome webserver* via this command: `esphome dashboard d:\esphome_projects`. Make sure you adjust the path at the end of the command with the path to your local *ESPHome* project folder that you created during installation.

> [!TIP]
> You can enter above command in any *CLI console* (i.e. *cmd.exe* or *powershell.exe*), or you can press `WIN`+`R` to open the *Run* dialog, and enter the command here.


The command opens a console window that runs the local webserver. Now open a browser, and enter this url: `http://localhost:6052`. This opens the local stand-alone *ESPHome dashboard*.

</details>

<img src="images/gui_esphome_addon.png" width="100%" height="100%" />

### Add New Device

Inside the *ESPHome Dashboard*, add a new device:

1. Click *NEW DEVICE*. A dialog opens and explains things that you can ignore for now. Just click *CONTINUE*.

    <img src="images/1_esphome_config_start.png" width="100%" height="100%" />

2. Assign a *name* to your new device that describes your project and is not used with any other existing *ESPHome device*. Spaces are converted to hyphens. Click *Next*.

    <img src="images/2_esphome_config_name.png" width="70%" height="70%" />

3. Select the type of microcontroller you are using. 

    <img src="images/3_esphome_config_type.png" width="70%" height="70%" />

4. Accessing your device is protected by a *secret key* that is shown on the next dialog page. Since this key is saved in the *configuration file*, you don't need to remember it. 

<img src="images/4_esphome_config_secret.png" width="100%" height="100%" />

If you want to [review](https://done.land/tools/software/esphome/introduction/defaultconfiguration) or [edit](https://done.land/tools/software/esphome/introduction/editconfiguration) the *configuration*, click *SKIP*. 

Else, proceed directly to *uploading the firmware* by clicking *INSTALL*.

## Uploading Firmware
There are many ways how you can *upload firmware*. In this article, the *firmware* is *directly uploaded* via *USB cable*:

1. If you haven't initiated the *firmware upload process* above by clicking *INSTALL*, then look for the tile of your *ESPHome device* in *ESPHome Dashboard*, and click its  *three-dot* icon, and choose *Install*.

    <img src="images/install.png" width="60%" height="60%" />

2. Choose *Plug into the computer running ESPHome Dashboard*. 

    <img src="images/rasp_selectport.png" width="100%" height="100%" />

3. The port connected to the microcontroller in the screen shot below is shown as *dev/tty/USB0*, indicating that this port is provided by a *Linux* system (actually a *Raspberry Pi* running *Home Assistant*). On a *Windows* machine, the port would show as *COMxxx*.

    <img src="images/rasp_port.png" width="100%" height="100%" />

4. *ESPHome* compiles the firmware and uploads it to the microcontroller. This can take several minutes. A terminal window logs each step taken.

    <img src="images/rasp_install.png" width="100%" height="100%" />

5. Wait for the installation process to be finished. There is no distinct *finish* message: the dialog simply shows the output of the serial monitor until you click *STOP*. When you feel the installation is done (or when you are no longer interested in viewing the log entries), click *STOP* to close the window.


> [!TIP]
> The tools used here are fundamentally identical to the ones found in the [ESP Web Tool](https://web.esphome.io/), so the same limitations apply: microcontroller boards that are incompatible with *ESP Web Tool* (like the *ESP32 S2 Mini) do not work with direct connections either.

### Verify Success

Once the firmware has been uploaded to your microcontroller board, it reboots and becomes available: in *ESPHome dashboard*, its tile is now marked *ONLINE* in its upper right corner:

<img src="images/rasp_sensor_online.png" width="100%" height="100%" />

If your board does *not* show *ONLINE* after a few seconds, review the [troubleshooting tips](https://done.land/tools/software/esphome/introduction/troubleshooting). 


> Tags: EspHome, Provision, USB Cable, Configuration

[Visit Page on Website](https://done.land/tools/software/esphome/introduction/provisioningdirectly?350408071511241259) - created 2024-06-03 - last edited 2024-07-13
