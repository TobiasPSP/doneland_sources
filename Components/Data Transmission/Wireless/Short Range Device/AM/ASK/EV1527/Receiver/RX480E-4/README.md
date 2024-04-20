<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# RX480-E

> Self-Learning 4-Channel EV1527-Compliant Receiver With Latch- And Push-button Mode 

The *RX480-E* breakout board is a one-stop solution to add remote control capabilities to devices.

<img src="images/rx_ev1527_rx480e_side_t.png" width="60%" height="60%" />

The *receiver* chip receives *ASK* radio signals and has a built-in *EV1527* decoder that can decode the 24-bit data packets sent out by a *EV1527*-compliant remote control (*sender*).

> [!NOTE]
> Because of the built-in *EV1527* decoder chip, this board requires no external components or a microcontroller to interpret data sent from a *remote control*. At the same time, you cannot use this receiver to receive any other type of data, i.e. sensor readings.

The breakout board often comes bundled with a ready-to-use *remote control*.

<img src="images/rx_ev1527_rx480e_kit_t.png" width="60%" height="60%" />


> [!CAUTION]
> Make sure you purchase the version for the *frequency* you intend to use. You cannot change the frequency later. In *Europe*, use the *433MHz* version. The *315MHz* version is intended for the *US* market. In *Europe*, *315MHz* is reserved for *military services*, and you can get in *serious trouble* when you operate on this frequency.


## Self-Learning

In *EV1527*, the 24-bit code packets sent out by a remote control are *fixed* and defined by the *sender*. In order for a *receiver* to respond to them, both have to be *paired*. This is called *"learning"*.

<img src="images/rx_ev1527_rx480e_button_t.png" width="60%" height="60%" />

Essentially, the *receiver* can be placed into *learning mode* by pressing a button. Then the designated *remote control* is activated and sending out a *EV1527*-compliant data package. The *receiver* picks up this code and stores it. It is now *paired* and knows the code it is supposed to respond to.

### Invoking Self Learning

*Learning* (*pairing* with a remote control) is done by pressing the button on the top of the board.

#### Delete Existing Codes

To *pair* the board with a new *remote control* or *EV1527*-compliant *sender*, first delete all stored codes by pressing the button *eight* times. The built-in *LED* confirms this by blinking *seven* times.

#### Understanding Operation Modes

The board can operate in three different modes per channel:

* **Push button:** the selected channel is *on* only for as long as the remote control signal is received.
* **Self-Locking:** each time the board receives a code, it *toggles* from *on* to *off* and vice versa.
* **Mutual Exclusive:** like *self-locking*, but once a different channel becomes active, the channel falls back to *off*. In this mode, only *one* channel is active at any time.


#### Pairing

To *pair* a button on a *remote control* with a channel on the *receiver*, enter *learning mode* by pressing the button on the top of the receiver *once*, *twice*, or *three times* (depending on the operational mode you want to assign to this channel):

<img src="images/rx_ev1527_rx480e_top_t.png" width="60%" height="60%" />

| Mode  | Key Press | 
| --- | --- | 
| Push Button Mode | 1x  | 
| Self-Locking Mode | 2x | 
| Multually Exclusive Self-Locking | 3x  |  

When the *learning mode* is active, the *LED* is constantly *on*.

Now press the intended key on the *remote control*. To confirm, the *LED* blinks *three times*.

You can now repeat this step up to *four times* to assign *remote control buttons* to each of the four channels. Mixing modes for different channels is possible as you have to invoke the *learning mode* for each of the four channels individually.




## Technical Data


| Item | Value |
| --- | --- |
| Voltage | 3.3-5V |
| Frequency | 433MHz *or* 315MHz |
| Operating Current | 5mA |
| Modulation Mode | AM (OOK) |
| Transmission Rate | EV1527 |
| Size | 28x12.3x5mm |

## Pins
The board comes with *seven* pins plus a solder pad for an *antenna* that is marked as *ANT* on the back side.

<img src="images/rx_ev1527_rx480e_back_t.png" width="60%" height="60%" />

> [!TIP]
> For much better reach, always operate these devices *with an antenna*. If no designated antenna is at hand, use a plain *17.3cm* wire for *433MHz*, and a *23.8cm* wire for *315MHz*.


The pins are labeled on the back of the board:

| Pin | Tag | Description |
| --- | --- | --- |
| 1 | GND | negative pole |
| 2 | +V | +3.3-5V |
| 3 | D0 | received code 1 |
| 4 | D1 | received code 2 |
| 5 | D2 | received code 3 |
| 6 | D3 | received code 4 |
| 7 | VT | learning mode |





> Tags: EV1527, Receiver, RF, 315MHz, 433MHz

