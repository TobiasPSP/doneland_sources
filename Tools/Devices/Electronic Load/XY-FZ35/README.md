<img src="/assets/images/electronicload2.png" width="80%" height="80%" />
 
# XY-FZ35

> 35W Electronic Load Module With LCD Display And Serial Interface

This is probably the most affordable ready-to-use module to create your own DIY electronic load: it can run stand-alone, and it can also be integrated into your own more sophisticated electronic load device. The original module was developed in 2019.

Without further enhancements, it serves as a small electronic load for up to 5A, 35W and 25V.

## Overview

This module uses a separate 5-30V power supply to power its electronics. The load is connected via a separate terminal and supports loads from DC 1.5V to 25.0V, a perfect fit for battery testing up to 5S. 

The load can be set with a rotary encoder (up to 5A or 35W, whichever is lower). The energy is dissipated with a heat sink and an intelligent fan activating above 10W or 40°C.

The built-in display shows the current, wattage, and elapsed time. It also records the total charge capacity drawn (mAh). It lacks recording of total energy drawn (mWh).

### Unique DIY features
While you can use the module stand-alone, it is clearly designed with DIY and fault-tolerance in mind:

* **Protection:**      
Adjustable over-voltage (OVP, default 25.2V), over-current (OCP, default 5.1A), over-power (OPP, default 35.5W), and low-voltage protection (LVP, default 1.5V), plus fixed over-temperature protection at ~80°C.
* **Reverse Polarity:**     
The module tolerates reverse polarity and will simply stop working, but reverse polarity is not causing any damage.    
* **UART (Serial):**    
While the module can be fully controlled via its display and rotary encoder, it features a UART interface and can be controlled and queried by simple commands. This way, you can create your own user interface with more sophisticated functionality, integrate it into Home Assistant, or add logging.   
* **Two-Part Shell:**   
The module can easily be separated into two parts: the front panel with LCD screen and rotary encoder which also hosts the microcontroller, and the back part with the terminals, MOSFET, heat sink, and fan. This simplifies mounting the module in a 3D printed housing: slide in the front part, then add the (larger) back part from behind.

### Strengths and Weaknesses

This module is designed to provide a momentary load, and to record the total **capacity** that was supplied (i.e. for battery testing). To enable this, the module has excellent current management.

The maker of this module apparently never intended to also provide **energy** details (i.e. *mWh*): while the module does come with high voltage precision, its poor terminals and connectors add considerable resistance, leading to voltage drops. With higher currents, it is common to see a gap of 0.2-0.3V between "real" voltage and the voltage the module reports.

So out-of-the-box, this module is not well suited to i.e. discharge batteries down to a specific voltage (i.e. storage voltage, or precise battery tests down to a given stop voltage). 

While it does feature "under-voltage protection (UVP)", conveniently stopping the discharge once the set voltage is reached, due to the mentioned voltage drop, the module "sees" as voltage that is considerably lower than it really is.

### Room for Improvement

This module is targeting DIY people. It can be used as-is, or easily enhanced thanks to its modular design and UART interface.

#### Energy Meter and Voltage Accuracy

While the module does not support 4-wire (Kelvin) connections, most of the voltage drop is caused internally by terminals and connectors. Here are a few enhancements that come to mind:

  - **Lower Contact Resistance:**         
    Desolder the cheap terminal for the load wires, and solder the wires directly to the PCB.  Or, replace the terminal with lower-resistance alternatives such as XT30 connectors.   
  - **Add Own Sensing:**        
    Use the module as load only, and add your own voltage and current sensing. For example, add a **INA228** to record capacity **and energy** in high precision.

    This also enables you to add additional modes like *constant power (CP/CW)*. Out-of-the-box, the module supports *constant current (CC)* only.

  - **Add Kelvin Probe:**    
    Even though the module has no separate voltage sensing terminal, it may help to add separate voltage sensing wires with a Kelvin clamp. You can see drastic improvements if the Kelvin clamp can be placed directly onto the battery nickel stripes or power supply terminals, bypassing contact resistance generated elsewhere.

#### User Interface   

The built-in user interface works surprisingly well, however there is always the option to do it yourself with this module: for example, if you do not like the small increment the rotary encoder uses for setting the current (requiring you to turn it many times just to change the current a little bit), then design and add your very own user interface.

* **UART is the key:**  
  Thanks to the UART connector, you can replace the existing user interface with your own. This way, you can choose your own increments or even provide dedicated buttons to set the current to frequently needed values. Internally, your user interface sends the requested parameter changes via UART to the module.
* **Read and Write:**    
  UART can also **read** real-time values, so you can completely hide the built-in front-end and replace it with your own sophisticated user interface (i.e. color TFT).     

  If you added your own voltage sensing module (see above), you can enhance the display with additional measurements (i.e. *mWh*, temperature, etc.).

* **Headless Module and Remote Control:**    
  Use *ESPHome* and a cheap ESP32-C3 Supermini to forward the controls to your Home Assistant dashboards. This effectively adds remote capabilities to the module. Since the module can provide real-time data in intervals of *1Hz* (once per second), this enables you to create sophisticated discharge diagrams in Home Assistant.  
  

#### Miscellaneous

Here is a selection of enhancements for the module that are simple to implement: just add a cheap microcontroller board, and have it control parts of the XY-FZ35 via its serial (UART) port.

* **Auto Under-Voltage Protection:**    

  Instead of manually setting the "under-voltage protection" for i.e. battery tests, your "smart" DIY load could sense the current load voltage, derive the number of cell strings, and automatically set the under-voltage setting. That's not just more convenient, it also removes room for disaster by ensuring that you never accidentally over-discharge a battery under test.


* **Temperature Monitoring:**        
  Electronic loads need to dissipate a lot of energy and can get hot. Add simple NTC resistors to the heat sink and inside of your housing, and display these values on your own user interface, or forward them to Home Assistant.

  While add it, add a connector for an external NTC resistor so you can also record the battery temperature of the battery you may be testing.



> Tags: Electronic Load, Constant Current, Constant Voltage, Constant Power, CC, CV, CP, CW

[Visit Page on Website](https://done.land/tools/devices/electronicload/xy-fz35?858058021815264332) - created 2026-02-14 - last edited 2026-02-14
