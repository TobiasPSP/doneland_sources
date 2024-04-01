<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# TX118SA

> 4-Channel RF Sender To Build Remote Controls Without Using Microcontrollers 

This board is designed to be used in *stand-alone* remote controls and does not  require a *microcontroller*. Each model comes with a *unique ID key* built in.

The board is equipped with a *voltage regulator* and accepts a wide range of input voltage from *3-24V*.


<img src="images/433_tx118sa-4_tx_angle_t.png" width="40%" height="40%" />


> [!CAUTION]
> Make sure you purchase the version for the *frequency* you intend to use. You cannot change the frequency later. In *Europe*, use the *433MHz* version. The *315MHz* version is intended for the *US* market. In *Europe*, *315MHz* is reserved for *military services*, and you can get in *serious trouble* when you operate on this frequency.



## What You Can (And Cannot)
This *sender* breakout board is somewhat special as it is *ready-to-go* to send *four different* *RF signals* that adhere to the *EV1527 learning code format*.

### Indented Use Cases

This is what you *can* do with this board:

* **Control Sending Data:** you can use simple buttons or a microcontroller to send out one of the four predefined data codes (connect one of the signal inputs to *GND*).
* **Receive Data:** with a separate *EV1527* compatible *receiver*, you can use its *learning mode* to learn the codes emitted from the *sender*. Now the *receiver* responds to the emitted signals and can be used to control devices.

### When To Not Use

And this is what you *cannot* do with this board:

* **Send Own Data:** you have no control over the data that is sent by this board. You cannot use it to send custom-formatted sensor data, i.e. to transmit readings from a *weather station*.
* **Receive Data:** receiving data emitted from this board is limited to *receivers* that can decode the *EV1527* data format.

### Conclusion
This board can be an excellent choice when you want to control external devices. Essentially, this board is the core of any *4-button RF remote control*, just without the housing.

Often, this board comes as a *package* with the appropriate *receiver* that is required to decode the signals.

> [!TIP]
> Do *not* use this board if you want to have control over the data you are sending.


## Specs

This breakout board by default emits *12.5mW* and is slightly over the legal limit of *10mW* in *Europe*. 

| Item | Value |
| --- | --- |
| Voltage | 3-24V |
| Frequency | 433MHz *or* 315MHz |
| Output Power | 11dBm / 12.5mW |
| Standby Current | <3uA |
| Operating Current | 10mA |
| Modulation Mode | AM (OOK) |
| Transmission Rate | <10 Kbps |
| Size | 15x11.8mm |

## Pins
The board comes with *three* pins plus a solder pad tp connect an *antenna*.

> [!TIP]
> Always operate these devices *with an antenna*. If no designated antenna is at hand, use a plain *17.3cm* wire for *433MHz*, and a *23.8cm* wire for *315MHz*.

Pins are counted from the *backside* with the model number visible in the top left corner (as depicted):

<img src="images/433_tx118sa-4_tx_bottom_t.png" width="30%" height="30%" />

The pin numbers are printed on the board next to the pin (on the back side of the board):

| Pin | Tag | Description |
| --- | --- | --- |
| 1 | - | negative pole |
| 2 | + | +3-24V |
| 3 | 1 | Send code A (connect to GND) |
| 4 | 2 | Send code B (connect to GND) |
| 5 | 3 | Send code C (connect to GND) |
| 6 | 4 | Send code D (connect to GND) |
| 7 | ANT | Antenna |




<img src="images/433_tx118sa-4_tx_top_t.png" width="30%" height="30%" />

## LED

The board comes with a *SMD **LED*** found on the opposite side of the pins, at the right side.

This **LED** can indicate various states of the device.



> Tags: TX118SA, EV1527, Sender, RF, 315MHz, 433MHz, 3.3V, 5V


