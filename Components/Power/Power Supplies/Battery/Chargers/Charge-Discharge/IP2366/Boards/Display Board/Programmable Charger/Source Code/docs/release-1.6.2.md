# BatCharger 1.6.2

The checkmark/accept key now has a vivid green background and dark foreground
on both numeric and WiFi keyboards. CLEAR and CANCEL behavior is unchanged.

Verified against the pinned LVGL 9.2.2 buttonmatrix drawing example and source:
the draw-task base descriptor's `id1` identifies the key; only the key whose
text is `LV_SYMBOL_OK` receives the fill/label override. This is presentation
only and does not change the keyboard map or event semantics.

Native preview and ESP32-S3 release build validated; no hardware flashed.
