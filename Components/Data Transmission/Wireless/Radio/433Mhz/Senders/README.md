<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Senders

> A Sender Emits A Signal On A Radio Frequency That Receivers Can Pick Up 

*Senders* can emit a radio frequency signal that carries information to a *receiver*. This way, you can transmit *sensor information*, *camera pictures*, or just *control signals* over the air.


<img src="images/433_send_receive_angle_t.png" width="40%" height="40%" />

They are very *inexpensive* and typically cost less than *EUR 2.00* per piece.

> [!NOTE]
> In this article, I am covering *senders* that transmit on *433MHz*. This is legal in *Europe*. In other regions, you may have to transmit on different frequencies. In the *US*, for example, the legal-to-use frequency is *315MHz*. The breakout boards covered in this article exist in multiple frequency versions. Make sure you purchase the version with the correct frequency. You cannot change the frequency later.

## Sender Types

*Senders* can be purchased both as *ready-to-use remote control* and as tiny *breakout boards*.

### RF Remote Controls
*RF Remote Controls* have a *RF sender* already built-in. When you press a button, the device emits a numeric code that a *receiver* can pick up.

<img src="images/433_remote_front_angle_t.png" width="40%" height="40%" />

While such remote controls are convenient to use and often sufficient to remote-control devices, they limit you in the kind of data you can transfer.

Some remote controls send out *fixed* numbers while other remote controls can *learn* the numbers they should later transmit.

When you purchase a *ready-to-go* remote control, make sure it works on the intended frequency.

<img src="images/433_remote_back_t.png" width="40%" height="40%" />

> [!CAUTION]
> Do not confuse *radio frequency senders* with *infrared senders*. Remote controls with a *IR* diode cannot be used to control *radio frequency receivers*.

<img src="images/ir_remote_front_angle_t.png" width="40%" height="40%" />

### Breakout Boards
*RF Sender* breakout boards are much more flexible. They are essentially just a *sender* that can send *anything* on the frequency it is designed for.

<img src="images/433_tx118sa-4_tx_angle_t.png" width="40%" height="40%" />

> [!NOTE]
> Do not confuse the *crystal frequency* printed  on the crystal with the emitted radio frequency. They are unrelated. Typically, there is no indication on the board that tells you the emitted frequency. If you do not *know* the frequency, all you can do is test the emission with a *spectrum analyzer*. 

### Antenna

Most *RF Sender* breakout boards come without a mounted *antenna*. You can operate them without an antenna, and due to their low *RF power*, typically no harm is caused to the circuitry. 

<img src="images/433_antenna_overview2_t.png" width="40%" height="40%" />


#### Operating Without Antenna
When operating without an antenna, a high percentage of the *RF Power* is not emitted to the air but instead reflected back into the circuitry. This *severely* limits the distance you can bridge. Without an *antenna*, your *sender* will hardly bridge a distance larger than just a few meters.

#### Correct Antenna Length
*Antennas* exist in various form factors, often as a *coil*. The only thing that matters is the *length* of the wire which must fit the *frequency*.

Here is a table with the required *antenna length* for *433MHz* and *315MHz* senders:

| Wave Length | 433MHz (cm) | 315 MHz (cm) |
| --- | --- | --- |
| Full | 69.2 | 95.2 |
| 3/4 | 51.9 | 71.4 |
| 5/8 | 43.3 | 59.5 |
| 1/2 | 34.6 | 47.6 |
| 1/4 | 17.3 | 23.8 |
| 1/8 | 8.65 | 11.9 |

> [!TIP]
> The *longer* the antenna, the better is the *RF emission*, and the *higher* are the distances you can bridge.



#### Self-Made Wire Antenna

Instead of (expensive) pre-made *coils*, you can simply use a plain *wire* instead. A *wire*  works better than a *coil* and emits more radio power but requires more space.



## Breakout Board Overview
A wide variety of *RF Sender* breakout boards exist. 

Aside from their (fixed) frequency, they differ in *size*, *emitted power*, *interface*, and some boards can act *both as sender and as receiver* (enabling two-way communications).

* [FS1000A](FS1000A): A very small board available in *433MHz* and *315MHz* that can be operated with *3.3V* and *5V*. The *RF Power* of *40mW* exceeds *European* legal limits.



> Tags: Frequency, Sender, Antenna, RF, Remote Control

