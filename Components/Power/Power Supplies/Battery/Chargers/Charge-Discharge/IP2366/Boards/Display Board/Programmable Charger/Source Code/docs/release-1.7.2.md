# BatCharger 1.7.2

Displayed/telemetry SOC is capped at selected target minus one percentage point until IP2366 reports charge complete. A 70% target caps at 69%; a 100% target caps at 99%. On hardware completion the cap becomes the selected target. Zero-percent targets clamp to zero without underflow. Tablet, web/export and ESPNow use the same helper and active session target. This presentation change does not alter CV regulation, completion detection or protection.
