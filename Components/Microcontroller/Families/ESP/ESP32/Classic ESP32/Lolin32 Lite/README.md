<img src="/assets/images/processor.png" width="80%" height="80%" />
 
# Lolin32 Lite

> Classic ESP32 With LiIon/LiPo Battery Support For Use In Portable Devices

The *Lolin32 Lite* development board uses a *ESP32* microcontroller and supports connecting an external *LiIon/LiPo* rechargeable battery. The battery can be charged through the *USB-C* connector. In combination with its low power consumption and small footprint, it is an ideal choice for use in portable devices.



<img src="images/esp32_lolin_connectors_t.png" width="40%" height="40%" />


## Technical Details



| Item | Description |
| --- | --- |
| Memory | external 4MB Flash |
| Clock Speed | 240MHz |
| Charging | 500mA charging current, LTH7/HM4054H |
| Power Consumption | 45.4mA (normal), 1.28mA (sleep mode) |
| Internal LED | GPIO22 |
| Battery | LiIon/LiPo 3.7V |
| USB-to-TTL | CH340 |
| Size | 49.2x25.5mm |
| Weight  | 6.6g |

### Comparison Lolin32 Lite vs. Lolin32 
The *Lolin32 **Lite*** development board is the *smaller version* of the *Lolin32* development board. The latter has its *JST 2.0 battery socket* placed on the side rather than next to the *USB connector*.

The differences between *Lolin32 **Lite*** and *Lolin32* are the *smaller footprint* of the *Lite* board, and as a consequence of its smaller size the lack of some pins: *RX0*, *TX0*, and *5V* are not exposed. There is also just one *GND* pin (instead of five), and just one *3.3V* pin (instead of three).

To further reduce the board size, it has a *reset* but no *boot* button. This turns out not to be a disadvantage though as the board reliably turns to *firmware upload mode* automatically when flashing it in *Arduino IDE*, *platform.io*, and *ESPHome*.

*Lolin32 **Lite*** specifically targets portable devices and focuses on a small footprint, rechargeable battery support (including charging), and the focus on *3.3V components* **only**. There is no *5V pin*, and its *GPIOs* are not *5V tolerant*. The board receives power solely via a connected battery or its *USB connector*. While you can supply power via its *3.3V* pin directly, this disables the built-in battery charger.

> [!NOTE]
> *Lolin32 **Lite*** should have more accurately be named *Lolin32 **Portable*** as it is just as powerful as *Lolin32* and not at all a *lite* version, rather optimized for **portable** use.



<img src="images/esp32_lolin_back_t.png" width="40%" height="40%" />

## Pins
The board has *26 pins*. 

<img src="images/esp32_lolin_lite_pins_t.png" width="100%" height="100%" />


## When To Use

These are some reasons for choosing a **Lolin32 Lite**:

| Feature | Use Cases |
| --- | --- |
| Portable Device | comes with everything needed to hook up a *LiIon/LiPo* battery and has a small footprint |
| Price | The board is relatively cheap |
| 3.3V | You are planning to use *3.3V* components and do not need *5V* support |


<img src="images/esp32_lolin_top_t.png" width="40%" height="40%" />


Here are some reasons to choose a different board:

| Use Case | Recommendation |
| --- | --- |
| External Power | Cannot be operated with external *3.3V or 5V power supply* (except via its *USB* connector) |
| 5V components | if you need to work with *5V* components you want to consider a different board.  |


<img src="images/esp32_lolin_front_t.png" width="40%" height="40%" />





## Materials
[Lolin Lite eBook](https://megma.ma/wp-content/uploads/2021/08/Wemos-ESP32-Lolin32-Board-BOOK-ENGLISH.pdf)   
[HM4054H Charger](materials/hm4054h_datasheet.pdf)   
[LTH7R Charger (Chinese)](materials/lth7r_datasheet_ch.pdf)   
[LTH7S Charger (Chinese)](materials/lth7s_datasheet_ch.pdf)   



  


> Tags: Microcontroller, ESP32, Lolin Lite, Battery, Charger

[Visit Page on Website](https://done.land/components/microcontroller/families/esp/esp32/classicesp32/lolin32lite?601146050916240343) - created 2024-05-15 - last edited 2024-07-16
