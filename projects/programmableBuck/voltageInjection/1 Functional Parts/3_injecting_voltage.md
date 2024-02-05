# Part 3: Controlling Voltage And Current Digitally
:stopwatch: Reading time: 15 minutes.

## Step 3: Regulating the **Buck** Controller

Once the microcontroller knows the exact *voltage* and *current*, it can start controlling the **Buck** converter, asking to increase or decrease *voltage* and/or *current*. How this is done is the clever trick and special beauty of this solution:

* **Potentiometers**: By design and stand-alone, the **Buck** converter controls *constant voltage* and *constant current* via two manually operated potentiometers. Both potentiometers are marked **W103** so they are **10K**.
* **Constant Voltage**: To keep the voltage constant, the voltage regulator *XL4016* inside the **Buck** converter uses a *voltage divider*, consisting of a 270R fixed resistor and the potentiometer. 

<img src="../images/voltageControl_w.png" width="90%" height="90%" />
