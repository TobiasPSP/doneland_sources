<img src="/assets/images/screenwire.png" width="100%" height="100%" />

# Displays

> Displaying Information Using OLED, TFT, Or LCD

*Displays* can be used to communicate with a user/operator. They work much similar to a *computer screen* but typically are much smaller. *Displays* can be as simple as a *matrix-style LCD monochrome text display* and go all the way up to sophisticated true color *graphics screens*, some providing *touch input* support.

## Technologies

These are the commonly used display technologies:

* **Signal LEDs** Basic *Signal LEDs* can signal state, In *DIY projects*, simple *Signal LEDs* are common place (requiring one *GPIO* **per LED**. That's why today, *Signal LEDs* are often replaced by *programmable WS2812 RGB LEDs* that can be daisy-chained. A *single GPIO* is required to control any number of such *LEDs* **individually**. 
* **LED Matrix Displays:** When multiple *LEDs* are combined, *LED matrix displays* evolve and can display numbers and text. More sophisticated *LED matrix displays* are comprised of freely programmable *dot matrices* where each dot is represented by a single *LED*. These displays can visualize simple graphics, however the individual dots are large, and the resolution is very low. Generally, *LED-based displays* offer *high brightness* and energy efficiency but are limited in color depth and resolution. *LED Matrix* displays are typically *multiplexed* using specialized driver ICs such as the *MAX7219* which can drive a *8x8 matrix display* with three *GPIOs*, and these matrices can then be daisy-chained. 
* **LCD (Liquid Crystal Display):** LCD technology emerged to provide higher resolution and more color accuracy than LED displays, at much lower energy consumption. *LCDs* use *liquid crystals* sandwiched between glass layers and requires a backlight for illumination. LCDs became widely popular in the *1980s* for watches, TVs, computer monitors, and mobile devices. Today, *LCD displays* are commonly used for *very low-cost devices*. In DIY projects, *LCD displays* are still very useful for very *bright* environments (like devices that are operated in direct sunshine). Such displays are limited to text characters and typically accessed via the simple **I2C interface** (requiring two *GPIOs*).
* **TFT (Thin Film Transistor):** A refinement of *LCD technology*, *TFT displays* use *active-matrix* technology, where each pixel is controlled by its own transistor. This results in faster response times, better color reproduction, and higher resolutions compared to earlier passive-matrix LCDs. However, *TFT* still require *backlight*, and due to their low contrast, they can be hard to read in direct sunshine. Today, *TFT* is used for most computer screens because of its cost-effectiveness and the circumstance that computer displays are typically not operated in super bright environments. In DIY projects, *TFT* is still the only affordable and robust technology for large color displays. Since such displays have high resolution, a large color depth, and potentially high frame rates, large amounts of data need to be transferred which is why the **SPI interface** is commonly used here. It requires four *GPIOs*. 
* **OLED (Organic Light Emitting Diode):** The latest advancement, *OLED displays* feature organic compounds that **emit light** when an electric current is applied: each pixel becomes its own small light source, and no backlight is required anymore. *OLED* provides superior contrast, deep blacks, and flexibility in design, allowing for thinner and more energy-efficient screens. They work equally well in darkness and bright environments and are today used in high end smartphones and TV screens. However, *OLEDs* are much more costly than *TFT*, have a much *shorter lifespan*, and are prone to *ghosting* (when a static image "burns in" over time). In DIY projects, typically *very small* and *monochrome OLEDs* are used. Since they do not display moving video or high resolutions, the slower but simpler **I2C interface** is commonly used. It requires only two *GPIOs*.
* **E-Paper/Electrophoretic Display (EPD) Technology:** Inside an *e-paper display* are millions of tiny microcapsules suspended in a fluid. Each microcapsule contains positively charged white particles and negatively charged black particles (or other color combinations). When an electric field is applied, the charged particles move within the capsules. **E-paper is bistable**: once an image is displayed, it remains on the screen without requiring additional power. The display only consumes power when updating (i.e., when the particles move), making it highly energy-efficient (for **static images**), and an *energy hog* when updating the display rapidly. Since it reflects ambient light, *E-Paper* is highly readable in bright sunlight and less straining on the eyes. It almost looks like real paper. Its use in DIY project is limited because of its high cost and its *very slow screen update process* during which the screen can visibly flicker multiple times. *E-Paper* is a promising technology, however there hasn't been much technological progress in this area for many years now. 


| Technology | Cost | Energy | Sunshine-Environment | Requires Microcontroller | GPIOs |
| --- | --- | --- | --- | --- | --- |
| Signal LED | low | medium | +++ | - | 1 |
| Programmable Signal LED (like *WS2812*) | medium | medium | +++ | yes | 1 (for any number) |
| LED Matrix | medium | medium | ++ | - | 3 |
| LCD | low | low | + | yes | 2 (I2C) |
| TFT | low | medium | -- | yes | 4 (SPI) |
| OLED | high | low | + | yes | 2 (I2C)/4 (SPI) |
| E-Paper | high | low | +++ | yes | 4 (SPI) |



## Operating Voltages

All the different display types uses *internal voltages* that can be as high as *15-30V* (as in the case of the *gate driver voltage* in *TFT displays*) and as low as *1.8V* (as in *LEDs* or *OLEDs*). 

*Display Drivers* (or simple current-limiting resistors with *Signal LEDs*) take care of safely converting the operating voltage to the voltages needed by the displays. That's why you **must always make sure** the driver logic of your *TFT*, *OLED*, *LED Matrix*, or whatever else matches the *operating voltage* your microcontroller or project uses.

There are displays that can handle a wide input voltage range and work equally well for *3.3V* and *5V* circuits, and there are other displays that have very specific requirements.

*LED-based* displays (like *LED Matrices*) often use simple *resistors* to limit the current. Such displays are then typically rated for **5V** and the classic *Arduino world*. To use them with **3.3V** (with modern microcontrollers such as *ESP*), you'd have to remove (or change) the current-limiting resistor.


> Tags: HID, Display, LCD, TFT, OLED, I2C, SPI, Matrix, E-Paper

[Visit Page on Website](https://done.land/components/humaninterface/display?628363051706242045) - created 2024-05-05 - last edited 2024-10-16
