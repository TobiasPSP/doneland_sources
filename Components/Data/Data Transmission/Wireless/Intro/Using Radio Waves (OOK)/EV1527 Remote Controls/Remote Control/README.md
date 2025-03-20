<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# EV1527 Remote Control

> Building a Simple EV1527-Compliant Remote Control

With *EV1527*-compliant sender and receiver breakout boards, it is easy to create simple remote control solutions.

## Overview

[*EV1527*-compliant senders and receivers](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/) are essentially a combination of basic [OOK (On-Off Keying) transmitters and receivers](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/) paired with an [EV1527 encoder chip](https://done.land/components/data/datatransmission/wireless/intro/usingradiowaves%28ook%29/ev1527remotecontrols/).

In the image below, the *EV1527*-compliant *sender* is shown on the left ([TX118SA](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/sender/tx118sa/)), and a matching receiver is on the right ([RX480-E](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/receiver/rx480e-4/)):

<img src="images/ev1527_sender_receiver_overview_t.png" width="70%" height="70%" />

Another type of sender you can use are commercially available *EV1527*-compliant remote controls. Internally, these contain the same sender chips, plus a few ready-to-use buttons, a battery, and a nice housing.

<img src="images/rc_remote_sniffer3_t.png" width="50%" height="50%" />

Maybe you have some of these remote controly laying around somewhere in your house gathering dust, and can reuse them in this project.

## Overview

In this project, we'll wirelessly control devices using radio waves and *EV1527 encoding*.

This setup uses *one-way transmission*, meaning you need both a *sender* and a *receiver*.

### No Feedback Mechanism

Since communication is one-way, the sender has no way of verifying whether the receiver received the signal. It is also unable to determine the current status of the controlled device.

So this type of remote control is ideal for devices that provide *natural* feedback. For example:

- **Garage doors:** You can see whether they are open or closed and hear the motor when activated.
- **Fans, air conditioners, lights:** These provide immediate visual or auditory confirmation when turned on or off.

### Frequency

Because signals are transmitted via radio waves, both sender and receiver must operate on the same frequency. Most *EV1527*-compliant devices use license-free ISM bands in the sub-GHz range:

- **315 MHz:** Common in the U.S.
- **433 MHz:** Common in Europe and Asia
- **868 MHz:** Less common for EV1527 but legal in Europe/Asia
- **915 MHz:** Rarely used for EV1527 but legal in the U.S.

> [!IMPORTANT]  
> Always verify the legal frequency regulations for your location. Additional rules, such as maximum RF transmission power or duty cycles, may apply.

### RF Transmission Power and Range

Since radio waves are public and can interfere with other signals, their use is strictly regulated in most countries. In addition to frequency restrictions, the transmission power is also legally limited.

*EV1527* is designed for short-range applications, such as remote controls within personal property. The typical operating range is a few hundred meters, and the RF power is limited to low values, i.e. **10mW (10dBm)** in Europe.

Exceeding this limit is not just illegal but generally unnecessary and can have drawbacks:

- **Interference:** Higher power increases the risk of jamming nearby remote controls. While *EV1527* uses unique ID codes to prevent accidental interference, excessive RF power can disrupt other devices.
- **Battery Life:** Higher transmission power drains battery-operated devices faster without offering any real benefit if your receiver is already within range.
- **Security Risks:** Stronger signals allow attackers to capture and replay remote control messages from a greater distance.

Some breakout boards exceed the **10mW** limit, which may be illegal in some regions. While enforcement is rare, it is still advisable to keep transmission power within legal limits in your personal interest.

> [!TIP]  
> If your remote control isn't working over short distances, increasing RF power is rarely the solution. The most common issue is a missing or improperly tuned antenna. Antennas are just as important as transmission power for ensuring reliable signal reception.

## Required Items



- **EV1527 Receiver:**  
  - A [breakout board](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/sender/), preferrably a receiver of type **superheterodyne**. Try and avoid receivers of type **superregenerative** as they are less reliable and *can* cause frustration. If you already have a *superregenerative receiver*, try it out. It may work perfectly well for you. If not, switch it out against a *superheterodyne*.    

    I am using a [RX480-E](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/receiver/rx480e-4/). Most *EV1527* receivers are wired very similarly.

    
    <img src="images/rx480-e_ev1527_receiver_t.png" width="50%" height="50%" />

- **EV1527 Sender:**  
  - A [breakout board](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/sender/) **-or-**  
  - A [*EV1527*-compliant RF remote control](https://www.google.com/search?q=ev1527+remote+control)    
      
      I am using a [TX118SA](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/sender/tx118sa/) and a commercially available ready-to-use remote control.

      
    <img src="images/tx118-s-4_ev1527_sender_t.png" width="40%" height="40%" />

### Cost
The required items are very inexpensive; however, prices can vary substantially depending on *where* you shop. I ordered the boards from *AliExpress* for less than 1-2€ per piece.

**Identical** boards can cost nearly 10 times as much when ordered from a local retailer, *Amazon*, or *eBay*. Just google around, and compare a bit.

As is almost always the case with such microelectronics, the higher prices are mainly due to the many additional intermediaries. The boards typically come from the same Chinese manufacturer anyway, regardless of where you purchase them.


## Antenna

Sender and receiver breakout boards often come without an antenna pre-soldered. 

Sometimes, a wire or coil antenna is bundled but needs to be soldered to the board. If you don't have an antenna, use a wire of appropriate length, i.e. *17.3 cm* long for *433 MHz* devices.    

Here is the formula to calculate the approproate antenna length for a given frequency:

  ````
  Length for λ/4-Antenna:
  =======================
  7495 / frequency (MHz) = antenna length (cm)
  
  433 MHz devices:
  ================
  7495 / 433.25 =  17.3 cm
  
  315 MHz devices:
  ================
  7495 / 315.00 =  23.8 cm
  ````

Connect an antenna to both the sender and the receiver board:

<img src="images/ook_ev1527_antenna_board_t.png" width="80%" height="80%" />

* **Coil Antenna:** if the board came with a coil antenna, these work very well and require very little space. You may want to put a piece of shrink tube over the coil. This looks cool but also makes sure you don't accidentally short-circuit the wire when touching, or in the rain.
* **DuPont Wire:** if the board uses a regular pin to connect the antenna, shortening a standard *DuPont* wire and using it as antenna can work very well.

## Assembling  Sender
Let's set up the sender (the "remote control"). If you are using a ready-to-use commercial RF remote control, you can skip this part.

These are the typical pins found on a sender breakout board:

| Pin | Description |
| --- | --- |
| **ANT**, **OUT**, **A** | either a pin, or a solder pad somewhere on the board. Connect the antenna here. |
| **+**, **V** | Positive voltage. Look up the voltage range in the board specs. The [TX118-SA](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/sender/tx118sa/) accepts *3-24V*. The higher the voltage the higher the RF output power. |
| **-**, **G** | Ground |
| **1**, **2**, **3**, **4** | Each pin controls a channel (and represents the buttons on commercial remote controls).<br/><br/>Depending on board, when a pin is connected either to *ground* or to *VCC*, the board starts to continuously send out the code for the particular channel. The board keeps sending this code until the pin is disconnected again. |

> [!NOTE]
> If your board does not have pins labeled `1`, `2`, etc., and  instead has a pin labeled `DAT` or `DATA`, then you have a generic [OOK sender board](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/sender/), not a [EV1527 sender board](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/).


#### Connections



* **Power:** connect the power supply pins to an appropriate power source. The [TX118SA](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/sender/tx118sa/) supports *3-24V*. Typically, senders require at least *5V* to output reasonable RF power. I am using a *4 AAA* battery pack (1.5V * 4 = 6V).
* **Antenna:** make sure you connect an antenna. You can destroy a sender board when operating without antenna, or with a grossly mismatched antenna.
* **Buttons:** connect each channel pin to a push button. Connect the other end of the push button to *ground* (other sender boards may have different requirements and may need the channel pins to be pulled up instead of down).


<img src="images/schematics_simple_ev1527_sender_t.png" width="80%" height="80%" />

### Testing

There is no indicator LED on the breakout board. You can test the setup either with a multimeter, or if you followed this article series, you can use the [Remote Control Sniffer](https://done.land/components/data/datatransmission/wireless/intro/usingradiowaves%28ook%29/sniffingrfremotes/#id-code-numeric-format) we created earlier:

* **Multimeter:** connect the multimeter in *series* with the power supply, and switch to *current* measurement. When you press one of the push buttons, your *EV1527* sender should start a RF transmission, drawing current in the range of *20-80mA*. Once you release the button, power consumption should be close to nil.
* **RC Sniffer:** if you built the [Remote Control Sniffer](https://done.land/components/data/datatransmission/wireless/intro/usingradiowaves%28ook%29/sniffingrfremotes/#id-code-numeric-format), it should show a unique *24bit* code whenever you press one of the push buttons. Each push button should always send the same ID code when you push it, and stop sending it once you release it.




> Tags: OOK, EV1527, Remote Control, Sender, Receiver

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/intro/usingradiowaves(ook)/ev1527remotecontrols/remotecontrol?971770031620254455) - created 2025-03-19 - last edited 2025-03-19
