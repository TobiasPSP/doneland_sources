<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Showing Device State

> Creating Physical Dashboards to Display Device States

With home automation, the need often arises to build remote switches or even complex dashboards to physically monitor and control devices.

## Overview

This section explores strategies, concepts, and options for visually displaying the state of various devices. These concepts can be applied to any type of feedback you want to provide:

* **Simple LEDs:** Use a basic LED or lamp that turns on when a device is active and off when it is not. Advanced effects like blinking or pulsing can indicate additional states, such as *"unavailable"* or error conditions.
* **WS2812 LEDs:** Use addressable LEDs to represent states with color effects—e.g., *green* for an active device and *red* for an inactive one.
* **Other Indicators:** Utilize buzzers or alarms to signal specific conditions audibly. Once your dashboard is informed of a state change, you can trigger any action as needed.

### Terminology

To ensure clarity, here are three key terms used throughout this discussion:

* **Control:** The switch or user interface that operates a device, such as a button on a remote control.
* **Effector:** The device being controlled, such as a fan or a garage door.
* **Visual:** The element that indicates the device’s current state—typically an LED, but it could also be a display, buzzer, or alarm horn.

### Simple Cases

When a device integrates both **effectors** and **visuals**, implementation is straightforward. For example, in my [remote-controllable 4-socket AC power strip](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/4-socketsmartpowerstrip/):

* **Effectors:** Relays that switch the sockets on and off.
* **Visuals:** Bi-color LEDs that change between red and green based on power status.

In such cases, the *ESPHome configuration* is simple because *effectors* and *visuals* exist within the same ESPHome setup, allowing direct interaction between them.


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
When the *effector state* changes—regardless of what caused the change—inside the *ESPHome configuration*, an **event** is raised: `on_turn_on` or `on_turn_off`, respectively. 

This makes it trivial to tie the **Visual** to this event:

1. The state of the **Effector** changes (e.g., a plug is turned on). It does not matter who initiated this state change:
    * A physical button on the device may have toggled the plug.
    * *Home Assistant* may have triggered the change (e.g., via a smartphone app or an automation).
    * The change could be automatic, based on a sensor reading or another automated trigger.
2. A *state change* event is raised.
3. The event handler updates the **Visual**.

Since this scenario is straightforward, it is not covered in the remainder of this article. Visit [this sample project](https://done.land/projects/esphome/switchesandcontrollingdevices/remotecontrolledpowerstrip/4-socketsmartpowerstrip/) to see the concept in action.

### ...And Challenging Scenarios

The *real* challenge begins when you want to create a dashboard or remote control with **Visuals** that exist in a **separate** device from the **Effector(s)**:

* **Remote Switch:**  
  You may want multiple remote controls placed in different locations, separate from where the **Effector** is. For example, you might want to control a lamp, garage door, or fan from multiple locations.  

    When you turn on the **Effector** from *any* of these remote controls, you want *all* remote controls to update their **Visuals** accordingly—e.g., lighting a green LED to indicate the device is on.  

    **Note:** Remote controls **without Visuals** (i.e., just buttons for control) are much easier to handle.
  
* **Dashboard:**  
  You may want to create a more complex dashboard that monitors and controls multiple **Effectors** across your home.  

    In this case, the **Visuals** exist in a separate device from the **Effectors** they monitor. However, you still want the dashboard to always reflect the real-time state of each device, even if the state changes due to actions outside the dashboard’s control.

## Strategies

When a **Visual** is located in a different device than the **Effector**, there must be a *notification process* to ensure that the device with the **Visual** updates when the **Effector** changes state. There are two main approaches:

* **Push:**  
  An automation script inside *Home Assistant* manages the **Visuals** in your monitoring device. In this approach, the monitoring device only displays **Visuals**, while *Home Assistant* centrally updates them.  

    Since *Home Assistant* can manage **all** monitoring devices in **one** automation script, it provides a single point of control for maintaining relationships between **Effectors** and **Visuals** across multiple devices. This makes updates and maintenance simple:
    
    * If a device is renamed.  
    * If you want to assign different **Effectors** to a remote control.  

    **Drawbacks:**     
    * *Home Assistant* updates **Visuals** only when an **Effector** state changes. If a monitoring device with **Visuals** was offline when the state change occurred, it will miss the update. 
    To solve this, the automation script must detect when a monitoring device comes online and **initialize** its **Visuals** to match the current state of the **Effectors**.

* **Pull:**  
  The device with the **Visuals** actively subscribes to *Home Assistant* events for the devices it wants to monitor. In this case, the monitoring device independently requests updates and manages its **Visuals**, with *Home Assistant* providing information on demand.  

    **Drawbacks:**  
    * The device requires full access to the *Home Assistant API*, making it a more valuable target for attackers. This is why *Home Assistant* no longer enables API access by default—you must explicitly allow it.  
    * The monitored devices are hard-coded into the firmware of the monitoring device. If a device is renamed or you want to track different devices, you must update the firmware of every monitoring device.


> Tags: ESPHome, Home Assistant, State, Visuals, Effectors, Push, Pull

[Visit Page on Website](https://done.land/projects/esphome/showingstate?664500031331250650) - created 2025-03-30 - last edited 2025-03-30
