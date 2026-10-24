# BatCharger 1.6.1

The numeric keyboard now has a light-blue **CLEAR** button to the left of
**CANCEL**. It empties the active field and keeps the keyboard open for a new
value. Cancel still restores the value from when editing began, including after
Clear. Both buttons hide when the keyboard closes.

Verified against pinned LVGL 9.2.2 `lv_textarea_set_text`: an empty string clears
the value even with accepted-character and length restrictions. Native UI
regression exercises Clear, continued keyboard visibility and Cancel restoration.
Native rendering and ESP32-S3 build checked. No device flashed.
