<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# MX-RM-5V / RF-5V

> Super-Regenerative ASK (Digital AM) Receiver

The *MX-RM-5V* breakout board is the European *433.92MHz* version, and the *RF-5V* is the US *315MHz* version.

The board is sometimes labeled *XY-MK-5V*.

<img src="images/rx_mx-rm-5v_side_t.png" width="60%" height="60%" />

It is primarily used in *remote control* solutions.

## Design Flaws

This *receiver* has a *very simple* receiver architecture: an oscillating *L-C* circuit is connected to a *LM358 OpAmp*. Receiving a signal drives the *OpAmp* into saturation.

While *sensitivity* is reasonable, *selectivity* is not. This *receiver* is easily jammed by strong signals, even when these signals are transmitted on a completely different frequency.

For example, when a device closer than 20cm to this *receiver* emits a *WiFi* signal, then this can be enough to render this receiver unusable: it won't pick up any legit signals anymore.

It may in fact be enough to mount this *receiver* close to a large capacitor to deafening it.

*Receivers* based on advanced receiver chips such as *SYN470* or *SYN480* are much more reliable.


## Versions

Two versions exist:

* **315MHz (US market):** this board is marked *RF-5V* on the back side. On the front side, a big 0.5W resistor is soldered on the board.
* **433.92MHz (European market):** this board is marked *MX-RM-5V* on the back. There is no big resistor soldered on the front side.

<img src="images/rx_mx-rm-5v_top_t.png" width="60%" height="60%" />


## Pins

The board exposes four pins that are labeled on the back:

<img src="images/rx_mx-rm-5v_back_t.png" width="60%" height="60%" />


| Pin | Label | Description |
| --- | --- | --- |
| 1 | GND | negative voltage |
| 2,3 | DATA | Data Out |
| 4 | VCC | 5V |


> [!CAUTION]
> Make sure the power supply is properly filtered and carries no exceptional noise which could interfere and distort reception.



## Antenna

This receiver can be operated without an antenna (which limits reception to just a few meters). For better reception, an antenna must be soldered.

[Here is](https://www.instructables.com/433-MHz-Coil-loaded-antenna/) how to create a simple coil-loaded antenna.

<img src="images/rx_mx-rm-5v_antenna_t.png" width="60%" height="60%" />

The antenna needs to be soldered to the unmarked through-hole connector on the lower right edge of the board, next to the inductive loop.

> [!TIP]
> Make sure your board has a soldered copper inductive loop has *three* windings. There have been reports of partially incorrectly assembled boards that use the *eight* winding coils designed for the *transmitter board*.





## Technical Data

| Item | Description |
| --- | --- |
| Voltage | 3-8V, 5V preferred |
| Current fully operational | 4mA |
| Frequency | *315MHz* or *433.92MHz* |
| RX Sensitivity | -105dBm |
| Modulation | ASK (AM) |
| Data rate | <10kbps |
| Distance | few feet (w/o antenna), 30-50m (with antenna) |
| Size  | 30.3x13.8x7mm |



> Tags: Receiver,ASK,OOK,AM,RF-5V,XY-MK-5V

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/receiver/mx-rm-5v?912853041919241233) - created 2024-04-18 - last edited 2024-04-18
