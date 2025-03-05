<img src="/assets/images/power.jpg" width="80%" height="80%" />

# LM2596 Buck Converter

> Input 4.5-40V, Output 1.2-37V, Current 3A, CV, CC


The **LM2596** from *Texas Instruments* is a monolithic buck converter accepting up to *40V* input and converting it to a lower voltage at a maximum current of *3A*. 

The chip exists in *fixed-output voltages* as well as in *variable output voltage*. It uses an internal 150 kHz switching frequency.


| Property | Value |
| --- | --- |
| Input Voltage | 4.5-40V |
| Output Voltage | 1.2-37V |
| Max Output Current | 3A |
| Efficiency | up to 96% |
| Switching Frequency | 150kHz |
| Standby Current | 80uA |

The controller supports shutting down the regulator circuit using logic level, dropping standby current to 80uA. To turn the regulator *on*, the *ON/OFF* pin needs to be pulled below *1.3V* (or connected to *GND*).

This feature can be used in *soft start* scenarios when the input power source is limited in the current it can deliver, preventing high initial current spikes. Buck converters require less input current at higher voltages: turning the regulator on only when the full voltage is present reduces input current requirements.

It can also be used for *under-voltage* protection scenarios where the output should be active only when a *minimum voltage threshold* is exceeded to protect sensitive consumers.

| Feature | Supported |
| --- | --- |
| Constant Current | yes |
| Over Current Protection | yes, two-stage reduction in switching frequency |
| Thermal Protection | yes |

[Data Sheet](materials/lm2596_datasheet.pdf)

> Tags: Buck, CC, CV, 3A, 40V, LM2596

[Visit Page on Website](https://done.land/components/power/powersupplies/dc-dc-converters/buck/lm2596?489125041911245144) - created 2024-04-11 - last edited 2024-04-11
