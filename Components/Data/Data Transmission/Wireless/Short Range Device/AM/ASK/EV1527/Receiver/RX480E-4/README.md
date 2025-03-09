<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# RX480-E

> Self-Learning 4-Channel EV1527-Compliant Receiver With Latch- And Push-button Mode 

The *RX480-E* breakout board is a one-stop solution to add remote control capabilities to devices.

<img src="images/rx_ev1527_rx480e_side_t.png" width="60%" height="60%" />

This receiver does not require any additional external components to pick up and interpret control signals sent by a *EV1527*-compliant *remote control*.


## Overview

The *RX480-E* is a small breakout board capable of receiving *EV1527*-compliant signals from remote controls. It can distinguish four different signals so it can respond to up tp four buttons on a remote control.


The breakout board often comes bundled with a ready-to-use *remote control*, but any other *EV1527*-compliant remote control will do.

<img src="images/rx_ev1527_rx480e_kit_t.png" width="60%" height="60%" />

### Frequency
The board is available in two different frequencies: 433MHz (Europe) *or* 315MHz (US). Since the frequency is set by a fixed crystal, you cannot change it. 

Make sure you use the board version for the frequency that is legal to operate in your region, and also make sure the remote control operates in the same frequency.

| Frequency (MHz) | Typical Crystal Frequency (MHz) | Description |
| --- | --- | --- |
| 315.0 | 10.526 | US, Asia |
| 433.92 | 13.225 | Europe |
| 868.35 | 26.000 | rarely used |

If in doubt which frequency your board uses, look at the crystal frequency which is typically laser-engraved on the housing.

<img src="images/rx480-e_crystal_marked_t.png" width="60%" height="60%" />

The crystal frequency is multiplied by a factor (such as *32*), usually via *Phase-Locked Loop (PLL)*, to reach the transmission frequency.



## Pins and Wiring

The board comes with *seven* pins plus a solder pad for an *antenna* that is marked as *ANT* on the back side.

<img src="images/rx_ev1527_rx480e_back_t.png" width="60%" height="60%" />

### Add Antenna
Always operate the receiver *with an antenna*. If no designated antenna is at hand, use a plain *17.3cm* wire for *433MHz*, and a *23.8cm* wire for *315MHz*.


<img src="images/rx480-e_antenna.jpg" width="60%" height="60%" />

Typically, the boards come with no antenna soldered. Without an  antenna, reception is poor, and the receiver may not be able to pick up signals from a remote control at all.


<img src="images/rx480-e_antenna_connected_t.png" width="60%" height="60%" />


### Pins
The pins are labeled on the back of the board:

| Pin | Tag | Description |
| --- | --- | --- |
| 1 | GND | negative pole |
| 2 | +V | +3.3-5V |
| 3 | D0 | high when received code 1 |
| 4 | D1 | high when received code 2 |
| 5 | D2 | high when received code 3 |
| 6 | D3 | high when received code 4 |
| 7 | VT | high when received any valid code |

Connect **GND** and **+V** to power. The red on-board LED will blink once, then turns off again.

The pins **D0** through **D3** respond now to one of four predefined codes sent by the remote control. **VT** is a *summary* pin and turns *high* when *any* of the four valid codes is received.

However, before the receiver can respond to remote control button presses, you need to *pair* it to the remote control. During pairing, the receiver reads and stores ("learns") the specific codes sent by the remote control buttons.

> [!TIP]
> If you have used the receiver before, you might want to explicitly *reset* it to factory defaults, making sure it "forgets" any previously learned code.


## Factory Reset

Before you start working with the receiver, you should *reset* it to factory defaults. This makes sure no previously stored settings are interfering.

To reset the *receiver*, press the button *eight* times. Each time you press the button, the red on-board LED lights up. Once you have pressed the button eight times, after a second the LED blinks four times to indicate successful reset.

<img src="images/rx_ev1527_rx480e_top_t.png" width="60%" height="60%" />


## Pairing

The *receiver* needs to be *paired* with the remote control that you want to use with this *receiver*.

The pairing process works for *one remote control button at a time*, so if you want to teach the receiver four different remote control buttons, you need to repeat the learning process below four times:

<img src="images/rx_ev1527_rx480e_button_t.png" width="60%" height="60%" />


1. Press and hold the button on the receiver for one second. Once you release the button, the on-board LED lights up constantly after a short delay.
2. Now press the button on the remote control that you want to use. The receiver LED blinks three times to confirm, and the receiver returns to normal mode (receiving mode).

Press the button on the remote control again. The receiver LED will light up for as long as you press the button on the remote control.

Repeat the process for up to three additional buttons on your remote control.

> [!TIP]
> Since the receiver adds new button codes to the existing ones until its 4-button memory is full, make sure you **reset** the receiver as shown above before teaching it a completely new remote control. Resetting the receiver is also necessary when you want to change its latching mode.

### Tips & Tricks

Here are a few considerations if things don't work as intended:

* **Cannot Pair Remote Control:**    
  - Do receiver and remote control work on the same frequency? Check the crystal frequency if in doubt.
  - Did you attach an antenna to the receiver? Without antenna, reception is very poor, and the receiver may not pick up the remote signal
  - Check the remote control batteries. 
* **No LED Response When Pressing Remote Control Button:**    
  - Did you *pair* the receiver to this particular remote control button yet? Try *resetting* the receiver, then pairing again.
  - Did you attach an antenna to the receiver? Without antenna, reception is very poor, and the receiver may not pick up the remote signal

If things still don't work, try and identify where the problem is located:

* **Receiver:** focus on the receiver board first.    
  - **Reset** it: Can you see the built-in red LED confirm the reset by blinking four times? If not, the receiver board may be defective.
* **Sender:** once the receiver works, shift focus to the remote control (sender):
  - **Antenna:** does the remote control have an antenna? For basic testing, move the remote control close to the receiver to exclude range issues.
  - **Pair** it: repeat the pairing process. Check to see whether the receiver board LED responds to the remote control button press.
  - **Test other remote controls:** if the receiver does not respond to the remote control button press, test with a different remote control to exclude that your remote control may be defective, out of battery, or working in a different frequency range. Any EV1527 remote control can be used for testing, including typical garage door openers etc.

Once remote control and receiver fundamentally work, next you can perform range tests to see what the maximum distance is for the signal to be reliably picked up. If the range is too short, make sure both remote control and receiver use appropriate antennas.



## Setting Latch Mode

By default, the *receiver* is in *push button mode*: the output pin is *HIGH* for as long as the button on the *remote control* is pressed. Once the button is released, the output pin returns to *LOW* - just like a *push button* or *momentary switch* would behave. This is perfect for controlling *toggle actions* like *garage doors*, or *Home Assistant*, which typically require just a toggle *impulse*.

Depending on what you want to control, the board supports three different latching modes:

* **Push button:** *(default)* the selected channel is *on* only for as long as the remote control signal is received.
* **Self-Locking:** each time the board receives a code, it *toggles* from *on* to *off* and vice versa.
* **Mutual Exclusive:** like *self-locking*, but once a different channel becomes active, the channel falls back to *off*. In this mode, only *one* channel is active at any time.

### Changing Latch Mode
A new latch mode can only be set when the receiver is in factory default mode, so you need to **reset** it first: press the button *eight* times, and wait for the *four* confirmation blinks.



<img src="images/rx_ev1527_rx480e_top_t.png" width="60%" height="60%" />

### Selecting Latch Mode

To set a new latch mode, press the button *once*, *twice*, or *three times*:

| Mode  | Key Press | 
| --- | --- | 
| Push Button Mode | 1x  | 
| Self-Locking Mode | 2x | 
| Multually Exclusive Self-Locking | 3x  |  

This will set the latch mode and also immediately enter *pairing mode*: the *LED* lights up and waits for you to press a key on the *remote control* you want to pair. Once successfully paired, the *LED* blinks *three times*.

Repeat the pairing process as described above for up to three additional remote control buttons.

> [!IMPORTANT]
> Regardless of latching mode, the built-in LED continues to light up for as long as you press a paired remote control button. So the internal receiver LED does not signal the latch state. It signals whenever the receiver receives a valid signal code.


## Technical Data


| Item | Value |
| --- | --- |
| Voltage | 3.3-5V |
| Frequency | 433MHz *or* 315MHz |
| Operating Current | 5mA |
| Modulation Mode | AM (OOK) |
| Transmission Rate | EV1527 |
| Size | 28x12.3x5mm |




> Tags: EV1527, Receiver, RF, 315MHz, 433MHz

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/receiver/rx480e-4?575872040920243620) - created 2024-04-19 - last edited 2025-03-08
