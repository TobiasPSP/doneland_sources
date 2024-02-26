# Functional Parts
:stopwatch: Reading time: 5 minutes.

## Digitally Controlled Buck Converter In 3 Steps

* **[Part 1: The Interface:](1_buck_interface.md)** First we add a physical interface to the stock **Buck** converter by identifying the pins we need access to, then soldering wires or a connector to it.
* **[Part 2: Monitoring Voltage And Current:](2_monitoring_voltage_and_current.md)** Next, we connect a microcontroller to the interface and use it to monitor *voltage* and *current*. At this point, the **Buck** converter has a digital display showing its output parameters. *Constant voltage* and *constant current* still need to be set manually via *potentiometers* on the **Buck**.
* **[Part 3: Digitally Controlling The Buck:](3_injecting_voltage.md)** Finally, we also implement the *voltage injection* part where the microcontroller actively feeds back voltages into the **Buck** controller to mimick the behavior when the two *potentiometers* are manually changed. At this point, the **Buck** converter can be digitally controlled from the microcontroller.

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/projects/programmable%20buck%20converter/via%20voltage%20injection/1%20functional%20parts?643156020426240854)
