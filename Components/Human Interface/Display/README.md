<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# Displays

> Displaying Information Using OLED, TFT, Or LCD

Devices can use *displays* to communicate back to the user/operator. They can be simple *monochrome text displays* or sophisticated true color *graphics screens*, some providing *touch* support.

## Technologies

Most *DIY displays* use one of these technologies:

* **Simple LCD:** Simple *liquid crystal displays* can display monochrome text similar to *LED matrix displays*
* **TFT LCD:** *thin-film-transistors* enhance addressability and contrast and can display any graphical content in  many thousand colors.
In this section I am reviewing the **Human Interface** components I like and use in my projects
* **OLED:** *organic light emitting diodes* provide the best display quality and contrast: no backlighting is required since each pixel is an individual light source. Production is still expensive which is why *OLED displays* are either small or very expensive. Most *OLED displays* used for *DIY* are *single-color* although affordable full color displays are emerging.

## Interfaces

To connect *displays* to *microcontrollers*, these two interfaces are commonly used:

* **I2C:** This simple two-wire protocol is used for small monochrome displays with limited data transfer rates
* **SPI:** The clock-based four-wire-protocol is typically found in larger and colored *displays* where much larger amounts of data need to be transferred

Simple *matrix-style* LCD text displays typically use specific driver boards which in turn can be addressed using *I2C*.

> Tags: HID, Display, LCD, TFT, OLED, I2C, SPI, Matrix

