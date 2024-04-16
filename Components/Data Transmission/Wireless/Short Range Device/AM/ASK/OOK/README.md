<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# On-Off-Keying (OOK)

> Transmit Data Using Simple OOK Protocol, Or Mimick More Sophisticated Encoding Formats Like EV1527

The most fundamental digital *ASK* encoding scheme is *On-Off keying* (*OOK*). 

## Transmits Any Data

You can use it to transmit *any* type of data, for example *sensor readings* or even *text messages*.

### EV1527 For Remote Controls

One *specific use case* is the *EV1527* encoding commonly used in commercial remote controls such as *garage door openers* or *home automation plugs*: 

Any *generic OOK* device can be programmed to understand the *EV1527* encoding and act as a remote control or remotely controlled device.

## OOK vs. EV1527-Ready

There is a wealth of breakout boards available that can transmit and receive radio signals in the *Short Range Device* frequency bands.

The fundamental difference - and important choice for you - is whether you want a breakout board that uses generic *OOK*, or whether you choose a dedicated *EV1527* device/board.

* **OOK:** Generic *OOK* devices can send or receive raw *OOK* bits. Such boards typically require a microcontroller that makes sense of these bits. Your software then has the freedom to implement whatever encoding scheme you want: you can then send arbitrary *EV1527* codes to control as many remote devices as you want, clone codes, or encode completely different data in your very own format, such as sensor readings.
* **EV1527-ready:** *EV1527*-ready senders come with a dedicated *EV1527* encoder chip and send out one or more *EV1527*-compliant codes. Such devices do not need any external components and no microcontroller or programming. *EV1527*-ready receivers typically implement some form of *learning mode*: when enabled, they pick up the control code emitted from a sender and store it. The *learning mode* basically *pairs* the remote control and the remotely controlled device. 



> Tags: ASK, OOK, EV1527

[Visit Page on Website](https://done.land/components/datatransmission/wireless/shortrangedevice/am/ask/ook?486260040016242407) - created 2024-04-15 - last edited 2024-04-15
