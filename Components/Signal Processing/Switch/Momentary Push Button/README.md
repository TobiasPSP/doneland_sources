<img src="/assets/images/switch2.png" width="80%" height="80%" />
 
# Momentary Push Buttons

> Sending Short Signals To Microcontrollers Via A Physical Button Press

A momentary push button is a type of switch that only remains active while it is being pressed. Once the button is released, the circuit is disconnected, returning to its default state.


<img src="images/b3f_a14_tactile_momentary_overview_t.png" width="80%" height="80%" />



## Push Buttons In Microelectronics

*Classic* electric circuits - *car electric* or *hardwired lighting* in your home - uses *latching buttons* or *toggle switches*: these keep their state (open or closed) until the user physically changes the button state. The switch *directly* controls the electric load. This is simple and rugged, but also very unflexible.

In *electronics* and *microcontroller-based* circuits, buttons are used to **send a *signal*** to a processing unit: 

* In *modern home lighting systems* for example, the user instructs a backend unit (i.e. *Home Assistant* or other *smart home* components) to turn on the light by pressing a push button *once*.    
* The signal could as well come from a wireless app or a timer. The controller does the load switching, and the push button is just *one way of many* to instruct the controller to do so.


### Advantages

The use of push buttons in combination with some backend controller provides a lot of flexibility and advantages:

* **Multiple Trigger Sources:** a load like a *light source* can be controlled through as many trigger sources as you desire: a physical push button, remotely via app, timer-based, or based on sensor input such as a *human presence sensor*.
* **Programmable:** Since a push button is not hard-wired to a particular load, often the underlying microcontroller or processor that receives the push button signal can be freely programmed to switch whatever load you desire.
* **Low Voltage And Current:** Since push buttons only need to switch a digital signal, the physical requirements are low, and push buttons are cheap, can be small, and do not wear easily. Typical momentary push buttons are rated for voltages of up to *24V*, and currents of up to *50mA*, but this can vary greatly, so always check the data sheet or the printed ratings on the switch.
* **Safe:** Due to the low voltage and currents handled by push buttons, no dangerous voltage is exposed in the area where the user operates, and very thin (and cheap) wires can be used. There is next to no fire hazard. Plus, the backend controller can autonomously turn off a load in emergency situations or when overload or other adverse conditions are sensed.    
 

> [!NOTE]
> There is a huge variety of push buttons available, and there are also types that *can* switch high loads or sustain high voltage - it's just not their *typical* use case.

### Caveats

Here are a few things to consider:

* **Never Switch Loads Directly:** push buttons are not designed to directly switch large loads. While you get away with controlling a single signal LED with a push button, trying to switch a motor or even a more powerful LED can heat up and/or destroy the switch, and may cause a fire. So always use a *controller* to control the loads, or at minimum a *relais* or *MosFET* to do the actual load switching.
* **Careful With Latched Buttons:** in *microcontroller-based* circuits, avoid *latching buttons*: their state can only change by local physical manipulation (a user has to manually change the switch position). This is useful only in simple circuits with no central controller unit (i.e. microcontroller).


## Types
Most push buttons are *normally open*. Some push buttons expose both switch types, or multiple electrically separated switches, through additional pins or screw terminals.

| Switch Type | Description |
| --- | --- |
| NO | *Normally open*, *high active*, contact on button press |
| NC | *Normally closed*, *low active*, contact when button is *not* pressed |

> [!NOTE]
> Since *push buttons* are used to send signals to microcontrollers, their switch type isn't really important. The *active signal type* can be programmed into the microcontroller easily, regardless of what switch type you use.

> Tags: Momentary, Push Button

[Visit Page on Website](https://done.land/components/signalprocessing/switch/momentarypushbutton?917548091229241408) - created 2024-09-28 - last edited 2024-09-28
