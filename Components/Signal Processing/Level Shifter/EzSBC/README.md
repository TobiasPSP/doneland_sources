<img src="/assets/images/components.png" width="80%" height="80%" />
 
# EzSBC Unidirectional 12V Level Shifters

> Controlling 12V Electronics With 5V Or 3.3V Microcontrollers

The small company [EzSBC](https://ezsbc.shop/search?q=level+shifter) offers specialized **unidirectional** level shifters designed for microcontrollers to interact with up to *18V* systems (i.e *12V* car electronics).

<img src="images/ezsbc_levelshift__compare_t.webp" width="50%" height="50%" />

The maker claims this level shifter can ["easily translate a 1MHz signal"](https://news.ezsbc.com/new-level-shifter-buffer/).

## Overview

Most mainstream level shifters support a limited voltage range, targeting microcontrollers and sensors that all run below *6V*.

The level shifters discussed here are based on *CD4504B* and support a wide voltage range from *3.3-18V* on both sides. There are no restrictions on which side must have a higher voltage than the other.

### Controlling Up To 18V Systems
*EzSBC*'s level shifters support a voltage range of *3.3-18V* on both input and output. The input voltage signals can be **higher or lower** than the output signals (however *all inputs* must share the same voltage, and *all outputs* must also share the same voltage).

That's why the pins on the board are not marked *low* and *high* but rather *input* and *output*. 

For example: 

* If you place the low-voltage microcontroller on the *input* side, then it can *send* information to the high-voltage system.    
* If you place the high voltage system on the *input* side instead, then the microcontroller can *receive* (read) information from the other system.

### Unidirectional

Communication is one-way (*unidirectional*): one side can always *send* (but not *receive*), the other side can always *receive* (but never *send*).


### Semi-Bidirectional

If you need to *send* **and** *receive* information, i.e. turn external systems on and off (*sending* commands), **but also** verify the external system state (*receiving* GPIO state), then you'd have to use *two* level shifters, and place your microcontroller on the *input* side of one and on the *output* side of the other.

Since that's fairly cumbersome, the company also offers a variant of its level shifter that implements 2x6 channels, six of which can be used as inputs, and the other six as outputs.

* **LS2:** 12 unidirectional channels 
* **LS3:** 6 channels in one direction, plus 6 channels in opposite direction


## LS2 - 12 Unidirectional Channels

The original **L2** level shifter provides 12 channels to send information uni-directional from one voltage domain to another:

<img src="images/ezsbc_levelshift_ls2_t.webp" width="50%" height="50%" />

| Pin | Description |
| --- | --- |
| `Vi` | Positive voltage of input system (3.3-18V) |
| `Vo` | Positive voltage of output system (3.3-18V) |
| `In1`- `In12` | 12 input channels |
| `O1`- `O12`|  12 output channels |
| `Gnd`| common ground |

The inputs have 500k resitors to ground and unused inputs may be left unconnected. When the input is not driven high the corresponding ouput pin will be low. The output swings close to ground and close to the output voltage level.

## LS3 - 2x6 Channels 

The variant **LS3** works like **LS2** but provides six *inputs* and six *outputs* per voltage domain:

<img src="images/ezsbc_levelshift_ls3_t.webp" width="50%" height="50%" />

Since this board has no distinct *inputs* and *outputs* that could be used to identify the voltage domain (as in `Vin` and `Vout`), the maker chose to call the two different voltage domains "low" and "high" (`Vlo` and `Vhi`).  

It is important to note though that "low" and "high" both support the same *3.3-18V* voltage range, and either side can be connected to a higher or lower voltage.

| Pin | Description |
| --- | --- |
| `Vlo` | Positive voltage of input system (3.3-18V) |
| `Vhi` | Positive voltage of output system (3.3-18V) |
| `InLo1`- `InLo6` | 6 input channels on "low" voltage domain |
| `OLo1`- `OLo6` | 6 output channels on "low" voltage domain |
| `OHi1`- `OHi6` | 6 output channels on "high" voltage domain |
| `InHi1`- `InHi6` | 6 input channels on "high" voltage domain |
| `Gnd`| common ground |

## What About LS1?
Is there also a **LS1** level shifter? Yes, [there was](https://www.tindie.com/products/ddebeer/i2c-bi-directional-level-shifter/). **LS1** was the company's initial design: an 8-channel **bidirectional** I2C level shifter sold via *tindie.com*. Its main selling point was its voltage-independence, supporting voltages of up to *12V*.

It seems to be no longer in production. Here is [more background information](https://news.ezsbc.com/new-level-shifter-buffer/) from the original maker.

## How It Works

**LS2** and **LS3** use two CMOS [CD4504B](materials/cd4504b_datasheet.pdf) hex voltage level shifter from Texas Instruments: six individual channels per chip shift input signals from one voltage to another. 

**LS2** uses both *CD4505B* for the same direction, whereas **LS3** uses one chip per direction and can thus deliver 6 inputs and 6 outputs.

According to an official [data sheet](materials/cd4504b_datasheet.pdf), the chip supply voltage is *5-18V*. However, this datasheet is an ugly scan dating back as far as 2004. At that time, microcontrollers generally used *5V* anyway. 

Meanwhile, the chip may have been revised. In Texas Instruments forums, the [use at *3V* seems to be possible](https://e2e.ti.com/support/logic-group/logic/f/logic-forum/998473/cd4504b-can-i-use-for-3-3v-to-12v-voltage-shift). In practical use cases (e.g. simple buffer or level shifter for 3.3V MCU to 5V logic), the CD4504B often “just works.” However, the threshold voltages and timing specs at 3.3 V are not guaranteed.

In a nutshell: for slow signal translation, the level shifters probably work fine even at voltages below *5V*. 



## Materials

[CD4505B Data Sheet](materials/cd4504b_datasheet.pdf)

> Tags: 12V, EZSBC, Car Electric

