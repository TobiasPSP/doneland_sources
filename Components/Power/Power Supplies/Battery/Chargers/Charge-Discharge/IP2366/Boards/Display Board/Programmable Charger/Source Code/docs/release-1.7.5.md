# BatCharger 1.7.5

Graph export buttons are wider with single-line labels and share the top row with the IP2366 status; the legend remains beneath the buttons on the right. Narrow screens wrap the group.

Settings > ESPNow setup adds Friendly name (default Charger, maximum 31 bytes). The web Settings page can edit the same name. It always persists independently of charger configuration, calibration and WiFi/mDNS. v1/v2 preferences migrate to Charger and preserve existing values. Identity remains MAC-derived; changing the name does not restart WiFi or change device/boot identity. The existing LabLink Advertisement.name carries the name without a wire-format change. The tester already reads and shows Advertisement.name in Devices and Inspect, so no tester update is necessary.
