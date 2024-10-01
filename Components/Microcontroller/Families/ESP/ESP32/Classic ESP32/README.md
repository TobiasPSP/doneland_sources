<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# ESP32

> The Classic ESP32 Microcontroller Sets New Standards And Comes As WROOM and WROVER

The *classic ESP32* is called *ESP32S*. Since its debut in 2016, many additional *ESP32 types* surfaced, i.e. *ESP32-S3* or *ESP32-C6*. But until today, the *ESP32S* remains popular among *DIY makers* because it is particularly straight-forward to use:

* *Well known:** Most *ESP32 examples* in the Internet or on YouTube are either for the *ESP8266* or the *ESP32S*. There is plenty of documentation.
* **Well supported:** No matter what you are planning to do with the microcontroller, chances are the *ESP32S* is fully supported. It has been around for almost 10 years, so by now, almost all editors, development environments, home automation systems, and whatnot have incorporated this microcontroller.
* **Well balanced:** The *ESP32S* comes with an exceptionally well balanced feature set and includes support for motor control, contains a *DAC* (*digital-to-analog converter*), *touch support*, and much more that may be useful for *DIY makers*.

That said, if you are looking for a *miniature footprint* or cutting-edge *low power consumption*, or if you are into the latest *wireless standards* such as *Matter* or *Threads*, then you may want to pick one of the *ESP32S* successors instead.

<img src="images/esp_wroom_top_front2_t.png" width="60%" height="60%" />

## ESP32 Types

The most popular and widely available *ESP32S* is the *WROOM-32D*. But there are quite a view variations. When you purchase **ESP32** dev boards, look for the fine print in the type:

* **WROOM-32:** First version of **ESP32**
* **WROOM-32D:** Revised version of **ESP32** with PCB antenna
* **WROOM-32E:** Same as *WROOM-32D* but with an IPX antenna jack for connecting an external antenna
* **WROVER:** Same as *WROOM-32* but with additional 4/8 MB *pSRAM*
* **WROVER-B:** Same as *WROOM-32D* but with additional 8MB *pSRAM*
* **WROVER-IB:** Same as *WROVER-B* but with an IPX antenna jack instead of a built-in PCB antenna

In addition, check the memory size. The price difference between *4MB* and *8MB* versions is typically very small, and the extra margin in memory may save your project one day.

Once you start planning on using a *ESP32S* in your project, one of the first things you want to find out is what the *GPIO pins* are that are safe to use. That's covered by the next section below.

## GPIOs
The GPIO information in this section applies to *all and every ESP32S* and to *all development boards that use an ESP32S*.

The GPIOs that are actually *exposed* and that can be used by you depend on the particular development board you purchase. There are boards with *38 pins*, *30 pins*, and even smaller form factors with much less pins. The fewer pins a development board exposes, the more of the *ESP32S* functionality is unavailable to you. Which can be perfectly ok: if you don't need the full set of *GPIOs* but would rather like to build smaller devices, then get a smaller development board. It's a trade-off between *space requirements* and *available features*.

> [!IMPORTANT]
> The information below **does not** apply to other *ESP32 microcontrollers* such as *ESP32-S2* or *ESP32-C3*. While their GPIO layout may be similar, it is not identical.

### Always-Safe ESP32 GPIOs

These GPIOs are **always safe to use** for *whatever purpose*:


| GPIO | Modes | Remark | Remark |
| --- | --- | --- | --- |
| 4 | Ain Din Dout | D4 | general purpose input/output GPIO|
| 16 | Din Dout | RX2 | general purpose input/output GPIO|
| 17 | Din Dout | TX2 | general purpose input/output GPIO|
| 25 | Ain Aout Din Dout | DAC1 | exposes DAC1 (if used) |
| 26 | Ain Aout Din Dout | DAC2 | exposes DAC2 (if used) |
| 27 | Ain Din Dout |  | general purpose input/output GPIO|
| 32 | Ain Din Dout |  | general purpose input/output GPIO|
| 33 | Ain Din Dout |  | general purpose input/output GPIO|
| 34 | Ain Din |  | input only, no pullup/pulldown |
| 35 | Ain Din |  | input only, no pullup/pulldown |
| 36 | Ain Din |  | input only, no pullup/pulldown |
| 37 | Ain Din |  | input only, no pullup/pulldown |
| 38 | Ain Din |  | input only, no pullup/pulldown |
| 39 | Ain Din |  | input only, no pullup/pulldown |




### Second-Choice GPIOs
If you need more GPIOs, you can look into using the GPIOs below. They serve other purposes as well, so make sure your using them does not cause conflicts. If your code i.e. does not use the *I2C* interface, it is perfectly ok to use these GPIOs for other purposes:

| GPIO | Modes | Caveat |
| --- | --- | --- | 
| 0| Ain Din Dout | input is pulled up, outputs PWM signal at boot, must be *low* to enter flashing mode |
| 1| Dout | **TX** pin for serial communications, debug output at boot |
| 2| Ain Din Dout | connected to on-board *LED*, *floating* or *low* to enter flashing mode |
| 3| Din | **RX** pin for serial communications, *high* at boot |
| 5| Din Dout | outputs PWM signal at boot, strapping pin, VSPI |
| 12 | Ain Din Dout | boot fails if pulled *high*, strapping pin, HSPI |
| 13 | Ain Din Dout | free to use if HSPI is not used|
| 14 | Ain Din Dout | free to use if HSPI is not used |
| 15 | Ain Din Dout | free to use if HSPI is not used |
| 18 | Din Dout | free to use if VSPI is not used |
| 19 | Din Dout | free to use if VSPI is not used |
| 21 | Din Dout | free to use if I2C is not used |
| 22 | Din Dout | free to use if I2C is not used |
| 23 | Din Dout | free to use if VSPI is not used |



### Interface Pins (I2C and SPI)
Most sensors and peripherals use either the *I2C* (slow speed) or *SPI* (high speed) interface. While these interfaces can be emulated in software, it is always best to use the dedicated hardware GPIOs. They are typically much faster and put less load on the microcontroller.

#### I2C


| GPIO | Remark |
| ---  | --- |
| 21  | SDA |
| 22  | SCL |



#### SPI


| Function | VSPI | HSPI | 
| --- | --- | --- | 
| MOSI | 23 | 13 | 
| MISO | 19 | 12 |
| CLK | 18 | 14 |
| CS | 5 | 15 |


### Strapping Pins

Some pins are called *strapping pins* because their logical state at boot time determines whether the microcontroller runs the ROM bootloader code, or your uploaded firmware. That's why strapping pins should be used with care.

As you see below, using strapping GPIOs in your code isn't as risky as some say:

| GPIO | Label | Remark |
| --- | --- | --- |
| 0  |  0 | *low* to run ROM serial boot loader. Else, run custom code |
| 2 | D2 | if GPIO is *high*, then GPIO2 is ignored.  Else, must be *low/floating* to enter boot loader. |
| 5 | D5 | controls timing of *SDIO slave*, default is *high* during boot (rising-edge output). Irrelevant when chip uses normal SPI flash. Used for CS in VSPI. |
| 12 | D12 | sets flash voltage (3.3V by default). If set to *high* on accident during boot, 3.3V flash receives 1.8V and browns out |
| 15 | D15 | *low* silences boot messages |

In reality, most restrictions apply during boot time only which is a period of time where your code has not even started to run:

* **GPIO0:** **do not use**
* **GPIO2:** must never be hard-wired to *high*. In your code, you can freely use *GPIO2* because your code will not run when boot mode was enabled via the *boot button*, and *GPIO2* only matters in boot mode.
* **GPIO5:** its strapping functionality does not apply to normal development boards, so it can be freely used unless *hardware SPI* is needed (i.e. for color displays or other high speed peripherals)
* **GPIO12:** must never be hard-wired to *high*. In your code, you can freely use *GPIO2* because your code will only run *after* the flash voltage has been set.
* **GPIO15:** Freely usable. Whether nor not boot messages are emitted is not interfering with boot.

The one thing to keep in mind is to not use strapping pins as *inputs* (you cannot control whether a user or input sensor delivers a *high* signal at the wrong time), and never hard-code strapping pins to *high* levels otherwise.

From your code, you can use these *GPIOs* without much restrictions.


### Serial Com GPIOs

The *serial communications interface* is used to upload new *firmware*, and often also to *communicate* with it: `Serial.print()` commands in your firmware code can output information, i.e. sensor data, that show in the *terminal window* of an *IDE*.

During normal operation, and if you don't need serial communications yourself, its two pins can be used for other purposes as well:


| GPIO | Label | Remark |
| --- | --- | --- |
| 1 | TX0 | serial comm (transmit)
| 3 | RX0 | serial comm (receive) |


However, using these GPIOs may require prerequisites to not interfere with required *serial comm* during *boot* or *firmware upload*.

Since *your firmware code* **can not** run at these sensitive instances, your code is always fine. What you do need to consider is your *hardware design* and *schematics*: **do not** physically pull-up or pull-down these pins or connect components to these pins that can alter their state during *boot*.

### Ghost GPIOs
For unknown reasons, six GPIOs are generally not exposed in the *ESP32S GPIO MUX*, so they are *never exposed* on *any board*:


| GPIO | Label | 
| --- | --- |
| 20 | newer versions may expose this GPIO after all |
| 24 | not working |
| 28-30 | not working |


> Tags: Microcontroller, ESP32, WROOM, WROVER, 32D, 32E, WROOM-32D, WROOM-32E, WROVER-B, WROVER-IB, PSRAM, GPIO

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/classicesp32?486134031823244200) - created 2024-03-23 - last edited 2024-09-29
