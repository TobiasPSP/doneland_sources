<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# T-Display

> Classic ESP32S Microcontroller With 1.14 Inch Color TFT At 135x240 Resolution

The [T-Display](https://www.lilygo.cc/products/lilygo%C2%AE-ttgo-t-display-1-14-inch-lcd-esp32-control-board) from [Lilygo](https://www.lilygo.cc/) is an affordable *general purpose* *ESP32S development board*. It comes with a 1.14" TFT color display (135x240 resolution) at high density (260PPI), a *USB-C* connector, and a *JST 1.25mm* connector for a rechargeable *LiIon battery*.


<img src="images/lilygo_tdisplay_all_angle_t.png" width="60%" height="60%" />

The package comes with a battery cable and is available with soldered or unsoldered header pins. The *ESP32S* is available in a *4MB* and a *16MB* version. A *shell case* can be ordered separately if you don't want to *3D print* your own.

| Item | Value |
| --- | --- |
| Microcontroller | ESP32S (Xtensa dual-core LX6) |
| UART | CH9102 |
| Flash RAM | 4M or 16M |
| Onboard functions | two programmable buttons, battery power detection, charger |
| Display | 1.14 Inch IPS LCD |
| Resolution | 135x240 |
| Density | High Density 260 PPI |
| Driver | ST7789 |
| Charger | TP4054 |
| Charging Current | 500mA |
| Size | 51.52x25.04x8.54mm |
| Voltage Regulator | AP2112K |
| Support | [T-Display Github](https://github.com/Xinyuan-LilyGO/TTGO-T-Display) |

## GPIOs
The board offers impressive 16 GPIOs, however certain restrictions apply:

| Count | Category | GPIOs  |
| --- | --- | --- |
| 8 | dedicated, input and output | 13,15,17,25-27,32-33 |
| 4 | dedicated, input only, no pullup/pulldown | 36-39 |
| 4 | caveats, restrictions apply | 2,12, 21-22 |


<img src="images/lilygo_tdisplay_top_2_t.png" width="90%" height="90%" />



### Eight Prime-Time GPIOs + Four Input-Only
Below are the *always-safe GPIOs* available on any *ESP32S*. The board uses two of these for the built-in display. 


| GPIO | Modes | Exposed? | Remark |
| --- | --- | --- | --- |
| 4 | Ain Din Dout | no | used for display BL |
| >13 | Ain Din Dout | available*) |
| >15 | Ain Din Dout | available*) |
| 16 | Din Dout | no | used for display DC |
| >17 | Din Dout | yes | available |
| >25 | Ain Aout Din Dout | yes | available |
| >26 | Ain Aout Din Dout | yes | available |
| >27 | Ain Din Dout | yes | available |
| >32 | Ain Din Dout | yes | available |
| >33 | Ain Din Dout | yes | available |
| 34 | Ain Din | no |  |
| 35 | Ain Din | no |  |
| 36 | Ain Din | yes | input only, no pullup/pulldown |
| 37 | Ain Din | yes | input only, no pullup/pulldown |
| 38 | Ain Din | yes | input only, no pullup/pulldown |
| 39 | Ain Din | yes | input only, no pullup/pulldown |

*) *HSPI* is not fully exposed anyway and therefore cannot be used - marked *GPIOs* are free to use for other purposes.

> *GPIOs* marked with `>` are recommended *GPIOs* that can serve as *input* and *output* and have no caveats or restrictions.


<img src="images/lilygo_tdisplay_front_angle_t.png" width="90%" height="90%" />

### Reserve GPIOs
Additional *GPIOs* can be used if your code does not require associated interfaces and/or can live with associated restrictions or caveats:

| GPIO | Modes | Caveat |
| --- | --- | --- | 
| 2| Ain Din Dout | on-board *LED*, *floating* or *low* to enter flashing mode |
| 12 | Ain Din Dout | boot fails if pulled *high*, strapping pin, HSPI |
| 21 | Din Dout | free to use if I2C is not used |
| 22 | Din Dout | free to use if I2C is not used |

## I2C and SPI

The board uses the default *ESP32 I2C* pins:

| Pin | Description |
| --- | --- |
| 21 | SDA |
| 22 | SCL |


<img src="images/lilygo_tdisplay_top_side_t.png" width="90%" height="90%" />

The board uses *VSPI* for its internal display. *HSPI* pins are not fully exposed (*GPIO14*/*CLK* missing) so *HSPI* is not meant to be used as a secondary *SPI* interface:


| Function | VSPI | HSPI | 
| --- | --- | --- | 
| MOSI | - | 13 | 
| MISO | - | 12 |
| CLK | - | - |
| CS | - | 15 |

*Lilygo* labels these *GPIOs* as freely usable.

## Strapping Pins
Here is a list of the exposed *strapping pins* that can influence (or impair) the boot process:

| GPIO | Exposed? | Restriction/Caveat |
| --- | --- | --- |
| 0  |  hard-wired boot button | *low* to run ROM serial boot loader. Else, run custom code |
| 2 | yes | Strapping function ignored when not in boot mode.  Else, must be *low/floating* to enter boot loader. |
| 5 | used internally for display | controls timing of *SDIO slave*, default is *high* during boot (rising-edge output). Irrelevant when chip uses normal SPI flash. Used for CS in VSPI. |
| 12 | yes | sets flash voltage (3.3V by default). If set to *high* on accident during boot, 3.3V flash receives 1.8V and browns out |
| 15 | yes | *low* silences boot messages, irrelevant |

### Caveats

You are good to use the GPIOs below as long as you do not use them as *inputs*, and do not hard-wire them to a given state:

* **GPIO2:** must never be hard-wired to *high*. In your code, you can freely use *GPIO2* because your code will not run anyway when boot mode is enabled via the *boot button*, and *GPIO2* only matters in this boot mode and is otherwise ignored.
* **GPIO12:** must never be hard-wired to *high*. In your code, you can freely use *GPIO2* because your code will only run *after* the flash voltage has been set.
* **GPIO15:** Freely usable. Whether nor not boot messages are emitted is not interfering with boot.

## Power

There are three options to supply power to the board:

| Source | Voltage Range | Remarks |
| --- | --- | --- |
| USB-C | 3.8-6.0V | *5V input* passes the internal *AP2112K* voltage regulator which delivers *3.3V* to the board |
| 5V pin | 3.8-6.0V | same as *USB input* |
| 3.3V pin | 2.3-3.6V  | input power bypasses the voltage regulator and is directly supplied to the board and chip. The input voltage must be in the range of *2.3-3.6V* for the CPU (but may need to be closer to *3.3V* for the display). If the voltage exceeds *3.6V*, the CPU may be destroyed. *ESP32S* may be powered directly by *LiFePo4* batteries, but never directly off *LiIon* batteries. Supplying power via *3.3V pin* is improving overall efficiency and minimizing power consumption but requires you to ensure correct voltage range |
| LiIon |  3.7-4.2V | All *T-Display* boards feature a *LiIon battery* connector (located on the back). When not connected to any other power source, *LiIon battery input* is processed by the same *AP2112K* voltage regulator that processes the *USB input voltage*. When connected to a *5V power source* like *USB*, an integrated charger (*TP4054*) recharges the *LiIon battery*.

## Materials

[Schematics PNG](materials/lilygo_t-display.png)    
[Schematics PDF](materials/lilygo_t-display.pdf)    
[3D Printable Shell](https://github.com/Xinyuan-LilyGO/TTGO-T-Display/tree/master/3d_file)    
[AP2112 Voltage Regulator](materials/ap2112_voltage_regulator.pdf)    
[TP4054 LiIon Charger](materials/tp4054_datasheet.PDF)    
[ST7789V Video Controller](materials/st7789_datasheet.pdf)    
 
> Tags: Lilygo, T-Display

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/lilygot-display/t-display?261761091530243112) - created 2024-09-29 - last edited 2024-09-29
