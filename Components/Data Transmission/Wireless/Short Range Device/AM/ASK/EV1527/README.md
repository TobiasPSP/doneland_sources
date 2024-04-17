<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# EV1527 

> Special Data Format For RF Senders And Self-Learning Receivers


*EV1527* is a popular *encoding format* for *ASK* RF senders and receivers to transmit simple remote control messages.

## Dedicated EV1527 Devices

In *this* section, you find *dedicated EV1527* senders and receivers that already come with EV1527 encoding and decoding chips. They do not require any additional components or a microcontroller.

> [!NOTE]
> Once you add a microcontroller to your project, you can use *any* *ASK* sender and receiver to transmit *EV1527*-compliant code: the microcontroller then can act as *EV1527* encoder and decoder, and produces the required 24-bit *EV1527* codes. 

## EV1527 Requirements

Simple remote controls such as *garage door openers* and *home automation plugs* has very basic remote communication requirements:

* **Unique Key Code:** The digital code sent out by the remote control (*sender*) must be *unique enough* to not cause remote controls to interfere with each other and open or control the wrong devices.
* **Simple On/Off Commands:** The digital code also needs room for a limited data payload so that a remote control can control more than one device.


## Implementation

One solution to these requirements was the *EV1527* encoder chip that operates on the *Low Range Device* frequency bands, typically *315MHz* (US) and *433MHz* (Europe/Asia).

It uses the simple *ASK* modulation (a subtype of *amplitude modulation*) and encodes the control information as a 24-bit data package.

The first 20 bits are randomly set by the encoder manufacturer to ensure the uniqueness of the codes. The remaining 4 bits can control devices.

Since the *sender* can send out only *fixed codes* that are beyond the control of the user, the *receivers* typically have a *learning mode* that allows them to pair themselves with the specific code emitted by a sender.

## Hardware Requirements

Hardware requirements are minimal. When you get *EV1527*-compatible breakout boards, no external components are required.




> Tags: EV1527, RF, Sender, Receiver, Remote Control, Self-Learning

[Visit Page on Website](https://done.land/components/datatransmission/wireless/shortrangedevice/am/ask/ev1527?152710041017241128) - created 2024-04-16 - last edited 2024-04-16
