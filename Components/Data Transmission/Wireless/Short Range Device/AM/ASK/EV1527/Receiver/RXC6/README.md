<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# RXC6

> Self-Learning 4-Channel EV1527-Compliant Receiver With Latch- And Push-button Mode 

The *RXC6* breakout board is a four-channel *EV1527*-compliant *receiver* and can be controlled with *EV1527*-compliant *remote controls* (senders).

<img src="images/rx_rxc8_side_t.png" width="60%" height="60%" />

It uses the *SYN470R* receiver chip and comes with a built-in *EV1527* decoder to decode  24-bit data packets sent by a *EV1527*-compliant remote control (*sender*).

The breakout board frequently comes bundled with a *RXB14 sender* breakout board. 

> [!CAUTION]
> The latest *RXC6* version, marked *V4* on the back of the board, is missing two solder bridges (*T1* and *T2*) that used to define the latch mode. There is currently *no documentation available* for the *V4* board explaining how latch mode is now working. By default, the board runs in *pulse* mode (similar to a push button): the contact is closed only while the appropriate remote control button is pressed. If you need the much more commonly used *latch* mode, there is currently no known way to put the *V4* board into *latch* mode.



<img src="images/rx_rxc8_back_t.png" width="60%" height="60%" />


## Self-Learning

In *EV1527*, the 24-bit code packets sent out by a remote control are *fixed* and defined by the *sender*. 

In order for a *receiver* to respond to them, both have to be *paired*. This is called *"learning"*.

<img src="images/rx_rxc8_top_t.png" width="60%" height="60%" />


### Clearing Memory

First clear all stored data: press and hold the button on the *receiver* until the *LED* lights. Keep pressing the button for a few more seconds until the *LED* turns off again. The *receiver memory* is now cleared.

### Pairing Remote Control


*Pairing* is done by pressing the button on the top of the *receiver* until the *LED* on the *receiver* lights up. This time, release the button immediately after the *LED* lights up. The device is now in *learning mode* and waiting to pick up a *remote control* signal.

Press a button on the *remote control* (or start the *sender* that should be paired with this *receiver*). The *LED* starts flashing when the sent code is successfully received and stored.

> [!NOTE]
> For pairing, you can press *any* button on the *remote control*. *EV1527*-compliant remote controls send a *20bit* ID code and then four additional bits representing the remote control keys. During pairing, only the *20bit* ID code is stored. Later, when you use the remote control, the *receiver* evaluates the remaining bits to figure out which button on the remote control was pressed, and enables the corresponding output pin.

#### Understanding Operation Modes

The board can operate in three different modes per channel:

* **Push button:** the selected channel is *on* only for as long as the remote control signal is received.
* **Self-Locking:** each time the board receives a code, it *toggles* from *on* to *off* and vice versa.
* **Mutual Exclusive:** like *self-locking*, but once a different channel becomes active, the channel falls back to *off*. In this mode, only *one* channel is active at any time.

In previous hardware versions of *RXC6*, this was done via solder bridges marked *T1* and *T2*:

| T1 | T2 | Mode |
| --- | --- | --- |
| open | open | Push Button |
| open | closed | Self-Locking |
| closed | closed | Mutual Exclusive |

In hardware version *V4* (marked on back of board), the solder bridges are missing. 

There are two *unmarked* open solder bridges on the board that may serve the same purpose (yet to be verified).



## Technical Data


| Item | Value |
| --- | --- |
| Voltage | 3.3-5.5V |
| Frequency | 433MHz *or* 315MHz |
| Operating Current | <4.1mA |
| Sensitivity | -110dBm |
| Modulation Mode | AM (OOK) |
| Transmission Rate | EV1527 |
| Size | 28x12.5x5mm |

## Pins
The board comes with *seven* pins plus a solder pad for an *antenna* that is marked as *ANT* on the back side.


<img src="images/rx_rxc8_back_t.png" width="60%" height="60%" />

| Pin | Tag | Description |
| --- | --- | --- |
| 1 | GND | negative pole |
| 2 | +V | +3.3-5.5V |
| 3 | D0 | received code 1 |
| 4 | D1 | received code 2 |
| 5 | D2 | received code 3 |
| 6 | D3 | received code 4 |
| 7 | VT | learning mode |


## Data Sheet

[SYN470R Receiver](materials/syn470r_datasheet.pdf)   
[Manual for *old* version](materials/manual.pdf)   
[YouTube Video for *old* version](https://www.youtube.com/watch?v=YsRBN86cis8)


> Tags: ASK, OOB, EV1527, Receiver, RF, Remote Control


