# Screenshot and schematic provenance

Tablet PNGs were generated afresh using BatCharger 1.7.7 tests/Test-Preview.ps1 and the actual LVGL 9.2.2 UI. Web JPEGs were captured from the actual web/index.html in the in-app browser, served by the fixture-only tests/preview_server.py on loopback. The browser captures include all five tabs, the Start review dialog, a communication warning, long-session graph and 390-pixel responsive viewport. Mobile capture used the direct page at mobile viewport width, not the iframe compositor. All values and transition events are synthetic test fixtures; no physical charger was contacted.

The ten-hour stress fixture deliberately constructs graph traces and events to demonstrate retention/reduction/placement; it does not demonstrate the physical phase estimator. Browser screenshots are original JPEG captures; native frames were converted from PPM to PNG without changing UI contents. The wiring diagram is editable SVG with a companion PNG generated from the same drawing instructions.

capture-manifest.json records dimensions and SHA256 for each image. source-files-before.json records the original README and image checksums before documentation creation. Firmware remains 1.7.7: this is a documentation-only addition.
