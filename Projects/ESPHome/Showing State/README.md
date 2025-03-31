<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Showing Device State

> Creating Physical Dashboards To Show Device States

With home automation, eventually the desire arises to build remote switches or even complex dashboards to physically control your devices.

## Overview
In this section, I am looking at strategies, concepts and options to visually display the state of various devices. These concepts can be applied to any type of feedback you want to provide:

* **Simple LEDs:** use a simple LED or lamp that turns on when a device is on, and off otherwise. Use advanced effects like blinking or pulsing to show other states, i.e. *"unavailable"* or other error states.
* **WS2812 LEDs:** use programmable LEDs to use color effects for states, i.e. *green* for a running device, and *red* for a device that is off
* **Other:** use buzzers to sound an alarm when a certain condition is met. You get the idea: once you know how your dashboard can be informed of a state change with a particular device, you can invoke any action you want.

### Terminology

In order for everyone to be on the same page, here are three terms that I use:

* **Control:** the switch or user interface that controls a device, i.e. a button on a remote control
* **Effector:** the device that is being controlled, i.e. a fan, or a garage door
* **Visual:** the element that indicates the current device state, typically an LED, but this could as well be a display or a buzzer/alarm horn.

### Simple Cases...

If you create a device that contains **both** the **effectors** and **visuals**, things are very simple, i.e. my [remote-controllable 4-socket AC powerstrip](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/4-socketsmartpowerstrip/):

* **Effectors:** relais that turn the sockets on and off
* **Visuals:** bi-color LEDs that can turn red or green, based on power status

In such cases, the *ESPHome configuration* is simple because *effectors* and *visuals* live in the same *ESPHome configuration*, so they can address each other directly:

````
switch:
  - platform: output
    name: "Switch1"
    icon: "mdi:power-socket-eu"
    restore_mode: RESTORE_DEFAULT_OFF
    output: relay1
    on_turn_on:
      then: 
        - output.turn_on: led1
    on_turn_off:
      then:
        - output.turn_off: led1
````

When the *effector state* changes - regardless of who caused this state change - inside the *ESPHome configuration*, an an **event** is raised: `on_turn_on` or `on_turn_off`, respectively. 

This makes it trivial to tie the *Visual* to this event: 

1. State of **Effector** changes (i.e., plug is turned on). It does not matter who initiated this state change:
    * your device may have a button that turns plugs on and off
    * *Home Assistant* may have caused the state change (i.e., via a smartphone app or another automation)
    * the state change may have been based on a sensor reading or a similar *automated* source
2. *State change* event is raised.
3. Event handler updates the **Visual**.

Since this scenario is straight-forward, it is not covered in the remainder of this article. Visit [this sample project](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/4-socketsmartpowerstrip/) to see the concept in action.

### ...And Challenging Scenarios

The *real* challenge starts when you want to create a dashboard or remote control with the **Visuals** that lives in a device **separate** from the **Effector(s)**:

* **Remote Switch:**     
  You may want to have a number of separate remote controls that you place in locations different from where the actual **Effector** resides. For example, you want to control a lamp or garage door or fan from multiple locations.     
  
    When you turn on the **Effector** via *any* of these remote controls, you want *all* remote controls to update their **Visuals** to reflect the new state, i.e. light a green LED.

    **Note:** Remote controls **without Visuals**, i.e. just with control buttons, are much easier to handle.
* **Dashboard:**     
  Or you'd like to create a complex dashboard that controls all kinds of devices (**Effectors**) in your household.    
  
    Again, the **Visuals** now live in a device **separate** from all the effectors you control.     
    
    Still, you want your dashboard to always accurately reflect the state of the devices, even if a device state changes due to factors not controlled by your dashboard.



## Stategies

When a **Visual** is located in a device different from the **Effector**, there needs to be some kind of *notification process* so that the device with the **Visual** knows when an **Effector** changes state:

* **Push:**   
  An automation script inside *Home Assistant* manages the **Visuals** in your monitoring device. In this scenario, the monitoring device is just providing **Visuals** but not controlling them. *Home Assistant* manages the **Visuals** centrally.

    Since *Home Assistant* can take care of **all** of your monitoring devices in **one** automation script, there is one central place to maintain the relationships between **all** **Effectors** and **Visuals** that you may have, across an unlimited number of individual devices. Updates and maintenance are simple:
    
    * a device is later renamed  
    * you'd like assign other device(s) to a remote control  

    The drawback is that *Home Assistant* **updates Visuals** only on **Effector state changes**. If a monitoring device with  **Visual(s)** wasn't turned on or available *exactly at that point in time*, it misses the notification.

    So a central automation script must also detect when a monitoring device comes online, and **initialize** its **Visuals** correctly.

* **Pull:**    
  The device with the **Visuals** actively subscribes to *Home Assistant* events for the devices it wants to monitor. In this scenario, the monitoring device intelligently manages updating its **Visuals**, and *Home Assistant* only provides information on request.

    The downside is that the device now requires full access to the *Home Assistant API* which makes the device more valuable for attackers and can be a security issue. This coincidentally is the reason why *Home Assistant* does not enable API access for devices by default anymore, and you'd have to explicitly enable this type of access.

    Another downside is that the devices monitored are now hard-coded into the firmware of your monitoring device. You'd have to update the firmware for any monitoring device you have when a device later is renamed, or when you want to change the devices it monitors.

