<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# EV1527 

> Special Data Format For RF Senders And Self-Learning Receivers


*EV1527* is a popular *encoding format* for *ASK* RF senders and receivers to transmit simple remote control messages.

## Dedicated EV1527 Devices

In *this* section, you find *dedicated EV1527* senders and receivers that already come with EV1527 encoding and decoding chips. They do not require any additional components or a microcontroller.

> [!NOTE]
> Once you add a microcontroller to your project, you can use *any* *ASK* sender and receiver to transmit *EV1527*-compliant code: the microcontroller then can act as *EV1527* encoder and decoder, and produces the required 24-bit *EV1527* codes. 

## EV1527 Requirements

Simple remote controls such as *garage door openers* and *home automation plugs* have very basic remote communication requirements:

* **Unique Key Code:** The digital code sent out by the remote control (*sender*) must be *unique enough* to not cause remote controls to interfere with each other and open or control the wrong devices.
* **Simple On/Off Commands:** The digital code also needs room for a limited data payload so that a remote control can control more than one device.


## Implementation

One solution to these requirements was the *EV1527* encoder chip that operates on the *Low Range Device* frequency bands, typically *315MHz* (US) and *433MHz* (Europe/Asia).

It uses the simple *ASK* modulation (a subtype of *amplitude modulation*) and encodes the control information as a 24-bit data package.

The first 20 bits are randomly set by the encoder manufacturer to *uniquely identify a remote control*. The remaining 4 bits control devices.

Since the *sender* can send out only *fixed codes* that are beyond the control of the user, the *receivers* typically have a *pairing mode* (aka *learning mode*) that allows them to pair themselves with the specific code emitted by a sender.

### Pairing

During *pairing*, the *receiver* picks up the *unique ID* code sent out by the remote control.

Once paired, the *receiver* responds to control messages only if the first 20 bits match the ID of the initially paired remote control.

### Sending Commands

Once you press a button on a remote control, it sends out a 24-bit data package:

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

[Visit Page on Website](https://done.land/components/datatransmission/wireless/shortrangedevice/am/ask/ev1527?152710041017241128) - created 2024-04-16 - last edited 2024-04-16
