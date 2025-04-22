<img src="/assets/images/convert.jpg" width="80%" height="80%" />
 
# Push - Let Home Assistant Control Visuals

> **Creating a Central Automation Script in Home Assistant to Manage Visuals in Dashboards and Remote Controls**

In this scenario, *Home Assistant* centrally updates all **Visuals** in *any* of your devices whenever the state of an **Effector** changes.

## Overview

These are the tasks the central automation script must perform:

1. **Device State Updates:**  
   When the state of a device (the **Effector**) changes, all **Visuals** representing that device must update accordingly.   
   
     **Example:**  when a plug is turned off, then all **Visuals** representing this plug in *any of your devices* should change from green to red.
2. **State Initialization:**  
   When a device with a relevant **Visual** becomes available, it must be initialized so that its **Visuals** show the correct state.   
   
     Else, the device could show a random state until the next time the state changes.


## Managing Automations

*Home Assistant* maintains a central automation script in `/config/automations.yaml`.

This file is **not** directly accessible through the Home Assistant UI unless you install separate add-ons like *File Editor* or *Studio Code Server*, but this is not necessary as there are better and safer ways to edit it.

### What Are Automations Anyway?

*Automations* leverage the true power in *Home Assistant* as they allow you to **teach** *Home Assistant* what it should do *automatically* when certain things occur.

This allows you to compose automations that involve multiple devices:
- If sensor *A* detects a temperature above *B*, turn on device *C*, i.e. a fan or air conditioning system.
- If a button is pressed on device *X*, toggle plug *Y*, effectively making the button a **remote control** that is **paired** to the plug.

### Accessing Automations

To view all automations:
1. Navigate to **Settings** → **Automations & Scenes**.
2. Click **Create Automation** to add a new automation.

Initially, this list is empty, but you can add any number of automation tasks.



## How Automations Work

Home Assistant stores all automations in a hidden file: `/config/automations.yaml`. This file is automatically managed and updated when you create or modify automations via the UI.

Here is how it works:


1. **Code in `automations.yaml`:**  
   Home Assistant reads `automations.yaml` at startup and reloads it when changes are made.
2. **Adding New Automation:**  
   Creating a new automation via the UI adds the corresponding code to `automations.yaml`. This ensures consistency while preventing errors.
3. **Wizard for Simplicity:**  
   The **Create Automation** wizard guides you through setting to compose automations via dropdown menus and simple prompts.
4. **Viewing & Editing Automations:**  
   - Automations can be found under **Settings** → **Automations & Scenes**.
   - Clicking an automation lets you **edit** it via the wizard and its simple controls.
   - Advanced users can access the **three-dot menu** in the top-right corner to **disable**, **delete**, or **Edit in YAML**.



### Working With The Real Code
The built-in wizard is great for simple automation tasks, but you'll soon hit its limitations, and also the wizard controls can sometimes be more confusing than helpful.

#### Accessing Source Code
When you click *Edit in Yaml*, you get to see the raw content of `automations.yaml` after all. You now can view the source code that the wizard has created for you, and even **edit** and change it.

You are, however, only working with the portion of `automations.yaml` that belong to your automation, and the UI shields you from other code. This is much clearer and protects you from accidentally damaging other automations.  



## Understanding Automations

Before you can fully leverage the power of *Home Assistant automations*, you need a basic understanding of how the code in automations really work. 

Using the simple wizard is not enough and too limited for most tasks. 

### Sample Automation
Create a simple automation using the wizard. Then click **Edit in YAML** and look at the raw YAML code.

For example, I created an automation that toggles a plug when a button is pressed. Here is the raw YAML code:

```yaml
alias: Toggle Plug T34-19
description: When push button is pressed, toggle state of plug
mode: single
triggers:
  - type: turned_on
    device_id: d93e239b5f04ccdd3b671c70303a45ab
    entity_id: 9490a273345f25f05d90e72c42bb2f20
    domain: binary_sensor
conditions: []
actions:
  - type: toggle
    device_id: 05a1d541fac7c7fc3d6127e1af0b0116
    entity_id: 8db7a92b4ce6e0168ccb4b3e7f9908ea
    domain: switch
```

### Understanding Code
Now try and make sense of the code. 

Here are two hints that help you simplify the wizard-generated code significantly:

* **YAML:**    
  Automations use the same simple *YAML* language that you already know from *ESPHome*. The same rules apply:   
  * tree structure, correct **indenting** is crucial.
  * key-value pairs, key ends with `:`
* **Entity ID:**    
  To reference particular devices, you use the unique device IDs. 
  * **GUIDs** the wizard uses cryptic *GUID* numbers
  * **Entity ID:** instead, use *Entity IDs* that you use everywhere else in the *Home Assistant UI* anyway.



Here is a much more readable version for the same automation:

```yaml
alias: Control Fan
description: Toggle the fan when the push button is pressed
triggers:
  - entity_id: binary_sensor.push_button_pushbutton1
    to: "on"
    trigger: state
actions:
  - target:
      entity_id: switch.plug_t34_38_switch_1
    action: switch.toggle
    data: {}
mode: single
```

### Testing Code
Copy the original wizard-generated code to an editor for backup, then replace the code with your simplified version. Save it, and test whether *Home Assistant* still correctly executes the automation.

This may be a mixed experience of trial and error, but eventually you get the idea, and it becomes evident how *simple* automation scripts often are: 

* **When?**  `trigger:` defines when an automation should execute
* **What?** `action:` defines the changes this automation should invoke

### Automation Code Explained 

By applying this know-how to the sample automation, you can now easily "decipher" it:

* **Documentation:**    
  `alias:` and `description:` are just comments that help you better understand what the code does when you revisit it in a few weeks.
* **When?**    
  `triggers:` defines when this automation should execute: it executes when the **state** of device with *Entity ID* **binary_sensor.push_button_pushbutton1** changes to **on** (when the push button is pressed).
* **What?**     
  `actions:` defines what *Home Assistant* should do when the trigger condition is met: the device with the *Entity ID* **switch.plug_t34_38_switch_1** (a plug) is instructed to perform the action **switch.toggle**: when the plug was *on*, it is now *off*, and vice versa.

[Visit Page on Website](https://done.land/projects/esphome/showingstate/push-hacontrolsvisuals?678462031331250650) - created 2025-03-30 - last edited 2025-03-30
