<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Amplitude Shift Keying (ASK)

> Simple AM Modulation For Digital Transmissions

In order to transport *digital information* over the air, there needs to be a physical representation for the states *1* and *0* that can be imposed on a radio frequency.

*Amplitude Shift Keying* (*ASK*) is a simple digital modulation technique often used in *remote controls* and *short range devices*.

> [!NOTE]
> There are other digital modulation techniques as well such as *PSK* (*phase-shift keying*), *FSK* (*frequency-shift keying*), and *QAM* (*quadrature amplitude modulation*). *ASK* however is most frequently used in breakout boards and commercial remote control solutions.

## Information Encoding

*Amplitude-shift keying* (*ASK*) is a variant of the fundamental *amplitude modulation*: the radio frequency remains fixed. The information is expressed as a variation in *amplitude* of the radio waves.

In *ASK*, a *symbol* can represent one or more bits. It is sent by transmitting a *fixed frequency* carrier wave with a specific *amplitude* for a specific time.

> [!NOTE]
> *ASK* is also often used to transmit digital data over optical fiber. Here, a binary *1* is represented by a short pulse of light, and a binary *0* by the absence of light.




### On-Off Keying (OOK)

In its most simplistic (and most common) form, a *symbol* represents one bit. The value *1* is sent at a nominal amplitude, and the value *0* is represented by the absence of a radio signal (pause). This type of modulation is called *on-off keying* (*OOK*).


### Sophisticated Encoding Schemes

Since radio transmitters can vary the amplitude, using a simple *on-off scheme* is potentially wasting resources. More sophisticated encoding schemes define additional symbols (groups of bits), and use different amplitude levels to identify these symbols.


### EV1527

*EV1527* represents an encoding scheme frequently used in simple commercial remote controls. Actually, *EV1527* is no encoding standard by itself but rather the model name of an *encoder chip* that first introduced this encoding scheme.

> [!NOTE]
> You do not need dedicated encoder chips as long as you know the encoding details (especially its timing). There are plenty of free libraries available at *github* that use generic microcontrollers to produce the *EV1527* signals. One of the most popular library is [rc-switch](https://github.com/sui77/rc-switch).

*EV1527* uses *ASK* as carrier signal and transmits a 24-bit data packet. The first 20 bits represent a unique (random) hardware id set by the chip producer. 

The remaining four bits can be used as data, i.e. to address four separate switches.

This scheme ensures that with roughly a million possible combinations, remote controls are specific (just like keys) and won't accidentally open the neighbors' garage door.

On the receiver side, a microcontroller can decode the *EV1527*-encoded information (i.e. by using the [rc-switch](https://github.com/sui77/rc-switch) library), or encoding is done by dedicated *decoder chips* such as the *ST3777*.



> Tags: ASK, OOK, EV1527, Amplitude-Shift Keying, On-Off Keying, Remote Control, RC-Switch, ST3777

[Visit Page on Website](https://done.land/components/datatransmission/wireless/shortrangedevice/ask?750969042315242843) - created 2024-04-15 - last edited 2024-04-15
