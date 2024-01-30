# DC-DC Converters

In *AC* circuits, transformers are used to transform one voltage into another using *magnetic fields*. This does not work for *DC* though.

For *DC*, to change the voltage you use electronic circuits that take a given *DC* voltage and convert it to a different *DC* voltage. 

Typically, *DC-DC Converters* accept a wide range of input voltages and convert it to a precise output voltage. For example, a *DC-DC Converter* can accept a wide range of input voltages from a car battery (12V) to a 9V block battery, and convert the input voltage to *5V* or *3.3V* required to run a microcontroller.

<details>
  
<summary>:information_source: How Do DC-DC Converters Work?</summary></summary><BR/>

  While transformers use the magnetic field created by *alternate current* and two coils with a different number of windings, *DC-DC Converters* work differently:
  
  They combine a fast transistor switch and a transient energy storage like a capacitor or a coil. Capacitors get loaded and unloaded in quick succession and "pump up" or lower the voltage. If more energy is needed, more expensive coils are used to temporarily store energy.

  There are excellent resources available at *YouTube* and in the net that explain in great detail how *DC-DC Converters* internally work. For *practical* purposes, they are breakout boards that take an input voltage and deliver a different voltage that can be adjusted with a potentiometer.
  
</details>
