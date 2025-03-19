<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# EV1527 

> Special Data Encoding For RF Senders And Self-Learning Receivers


*EV1527* is a widely used **fixed-code OOK (On-Off Keying) modulation scheme** that transmits a **20-bit ID** plus **4-bit data**. The encoding consists of a **preamble**, a **synchronization bit**, and the **data transmission** using a specific pulse width format.  


Originally, *EV1527* was a proprietary *chip* manufactured by a Chinese company which then found so widespread adoption in affordable remote controls that its encoding scheme became a standard by itself.

*EV1527* uses a fixed message format and does not have
cryptographic protection. It is vulnerable to *replay attacks* where an attacker would listen for RF transmissions from a remote control, then play it back later to mimick the original remote control.

## EV1527 Senders And Receivers

In this section, you find *EV1527*-compliant senders and receivers that come with EV1527 encoding and decoding built-in. They do not require any additional components or a microcontroller and are very simple to implement.




### When To Use EV1527 (And When To Avoid)

Keep in mind that *EV1527* transfers data via radio waves. 

Radio waves have distinct advantages: they do not need an existing WiFi infrastructure, and often work across much longer distances (up to 400m with simple senders and receivers).

However, radio waves are public. Anyone can listen in, or send. *EV1527* is **not encrypted** and uses **repetitive (predictable) messages**.

*EV1527* is great for any simple *microcontroller-free* scenario that is **not security critical**. Use it for toys, to turn on garden lamps, or alike.

* **Microcontroller Available:** If your project already uses a microcontroller, use a generic [OOK sender/receiver](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/) and [implement the encoding yourself](https://done.land/components/data/datatransmission/wireless/intro/usingradiowaves(ook)/sniffingrfremotes/). This way, you can add security features such as rolling codes and encryption.

* If your project is security critical, consider wireless methods that come with encryption by default (i.e. *ESPNow*, *WiFi*, etc.). At minimum, use *rolling codes* that cannot be easily captured and replayed.  *EV1527* can be used in *replay attacks* from anyone close enough to receive the signals from your remote control.    
  
  Keep in mind that especially a *garage door opener* is a **highly security-sensitive device**. Anyone close enough to pick up your remote control signal can gain entry at his or her convenience when the remote control uses *EV1527*. 



### EV1527 Encoder Chip

The *EV1527* encoder chip takes care of turning a *24 bit number* into an encoded burst of signals that can be transmitted via radio frequencies.

The *24 bit number* consists of a *20 bit sender ID*, and *4 bits representing up to 4 buttons on a remote control*.

EV1527 encodes data with **pulse-width timing**. The durations are typically defined as:  

| **Bit Type**  | **High Pulse Duration (µs)** | **Low Pulse Duration (µs)** | **Total Duration (µs)** |
|--------------|---------------------------|--------------------------|-------------------------|
| **Logical '1'** | 275 µs | 1225 µs | 1500 µs |
| **Logical '0'** | 275 µs | 275 µs | 550 µs |
| **Sync Bit** | 275 µs | 2675 µs | 2950 µs |

- **Sync bit**: **275 µs HIGH + 2675 µs LOW** (long LOW period) marks the start of data.  
- **Logical '1'**: **275 µs HIGH + 1225 µs LOW**.  
- **Logical '0'**: **275 µs HIGH + 275 µs LOW**.  





### RF and Frequencies

EV1527-encoded signals can be sent by any basic [OOK sender](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/sender/). So a [EV1527 sender](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527/sender/) is just a [OOK sender](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/sender/) with a built-in *EV1527* encoder. 


Typically, *EV1527*-compliant remote controls use the license-free *315MHz* ISM band in the US, and the license-free *433MHz* ISM band in Europe and Asia.

* **315.00 MHz:** the *315MHz* band has just one channel at exactly *315.00MHz*. 
* **433.92 MHz:** the *433MHz* band has a total bandwidth of *1.72MHz*, offering room for up to 174 channels. *EV1527*-devices operate on channel 87 (433.92 MHz) which is the center frequency of this band.


### Replacing EV1527 Encoder Chip by Microcontrollers

When your project uses a microcontroller, using a dedicated *EV1527* encoder chip (or a sender/receiver with such a chip) often is counter-productive.

Your existing microcontroller can take over the encoding part and transmit the signals directly to a generic [OOK Sender](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/sender/) (or process the signals received with generic OOK receivers). 

This opens room for many opportunities not available with dedicated *EV1527 senders*:

* **Self-Learning Remotes:** a OOK receiver picks up signals from existing remotes, and replays them to a OOK sender. Since no dedicated *EV1527* encoder chip defines the first 20bit of the ID numbers, such a setup can combine the signals from many different remote controls in one place.
* **Other Encodings:** a microcontroller can use different encodings from different vendors to interpret the raw data from a OOK receiver, enabling you to work with *Samsung*, *Panasonic*, generic *EV1527*, and many other remote controls.
* **Security:** implement your own encodings and/or rolling codes that change after each transmission according to a secret list, effectively making replay-attacks harder or impossible.


## Pairing
Since *EV1527* uses fixed ID codes defined by the manufacturer of a *sender device*, a *pairing process* is required to couple a sender (remote control) and a receiver.

During *pairing*, the *receiver* picks up the *unique ID* code sent out by the remote control.

Once paired, the *receiver* responds to control messages only if the first 20 bits match the ID of the initially paired remote control.

## Operation

Once you press a button on a remote control, it sends out a 24-bit id number encoded in *EV1527* format:

The first 20bits are the unique remote control ID. The remaining 4bit are the payload. Each bit in this payload can represent a button on the remote control (up to 16 buttons).



### Receiving Commands
Once the *receiver* picks up a control message with matching *ID* (the *ID* in the control message matches the *ID* that was stored during initial *pairing*), it looks at the 4bit payload.

Depending on how many *channels* the *receiver* supports, it responds to the appropriate bits in the control message.

For example, most typical *EV1527*-compliant *receivers* support *four channels*. When you press one of the first four buttons on a remote control, you can control one of the four data out pins of the *receiver*.


If that is the case, the *receiver* looks at the *4-byte payload* and assigns the first four bits to its four digital outputs.


## Limitations

Most *EV1527*-compliant *receiver boards* can only be paired to a *remote control ID*, but not to a specific *remote control button*.

So if you have a eight-button *remote control*, you cannot control *two 4-channel receivers* with it: each *receiver* pairs to the *remote control ID* and assigns the first 4 bit of the payload to its four channels.

Likewise, since *receiver breakout boards* can only be paired to *one remote control ID*, you cannot use *multiple remote controls* to control a *receiver board*.

### ...And Workarounds

All mentioned limitations are caused by the rigit way the embedded *EV1527* encoders and decoders work. For simple remote control scenarios, this is absolutely fine because it makes using these devices extremely simple.

For more sophisticated scenarios (i.e. multiple remote controls for one device, assignment to specific buttons on a remote contol), all you need is to take control into your own hands:

* **OOK instead of EV1527:** use generic *OOK* (*ASK*) senders and/or receivers. This way, you are not limited anymore to hard-wired rules and behaviors
* **Microcontroller:** add a simple microcontroller to your project (such as *ESP8266* or *ESP32 C3*), and use one of the *EV1527* libraries to do the encoding and decoding yourself.

Depending on how you address things, you might use a microcontroller-based alternative either on the *sender* side or on the *receiver* side.

* **Multiple Remote Controls (Sender):** To use multiple remote controls with one *receiver*, all you really need is control over the *sender ID*. By using a microcontroller-based *sender* as *remote control*, you can clone one *sender ID* and use it with as many remote controls you want.
* **Multiple Remote Controls (Receiver):** A cheaper solution might be using a microcontroller-based setup on the *receiver* side, and continue to use default remote controls. All you need in this scenario is control over the *pairing process*: with a microcontroller-based approach, you can *pair* as many remote controls as you want and keep as many *remote control IDs* stored and approved as you like.

## Hardware Requirements

Hardware requirements are minimal. When you get *EV1527*-compatible breakout boards, no external components are required.



> Tags: EV1527, RF, Sender, Receiver, Remote Control, Self-Learning

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask/ev1527?152710041017241128) - created 2024-04-16 - last edited 2024-04-16
