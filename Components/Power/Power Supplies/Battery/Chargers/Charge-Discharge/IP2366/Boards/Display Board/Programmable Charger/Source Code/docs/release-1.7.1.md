# BatCharger 1.7.1


## 1.7.1: restored hardware CV termination
Supersedes the 1.7.0 partial-target software cutoff. All percentages program the IP2366 with the selected curve-derived cell voltage (100% uses the entered cell voltage unchanged). Partial targets round down to the hardware 10 mV step. The controller waits for IP2366 charge completion; reaching the voltage alone does not end the session. Existing time limit, fault handling, SOC display and target-relative progress remain. Example: 4S LiFePO4 at 70% programs 3.460 V/cell, 13.840 V total. Current limiting uses this programmed voltage.
