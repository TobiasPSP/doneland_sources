<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Amplitude Shift Keying (ASK)

> Simple AM Modulation For Digital Transmissions

In order to transport *digital information* over the air, there needs to be a physical representation for the states *1* and *0* that can be imposed on a radio frequency.

## Quick Overview

*Amplitude Shift Keying* (*ASK*) is a simple digital modulation technique often used in *remote controls* and other *short range devices*.


> [!NOTE]
> There are more digital modulation techniques such as *PSK* (*phase-shift keying*), *FSK* (*frequency-shift keying*), and *QAM* (*quadrature amplitude modulation*). *ASK* however is most frequently used in breakout boards and commercial remote controls because of its simplicity.

*ASK* is a variant of *amplitude modulation*: the radio frequency remains fixed. The information is expressed as a variation in *amplitude* of the radio waves.


> [!NOTE]
> *ASK* is used to transmit digital data over optical fibers, too. Here, a binary *1* is represented by a short pulse of light, and a binary *0* by the absence of light.



## On-Off Keying (OOK)

To transport digital information via *ASK*, the bits need to be transformed to radio signals.

In its most simplistic and common form, the value *1* is sent at a nominal amplitude, and the value *0* is represented by the absence of a radio signal (pause). This type of modulation is called *on-off keying* (*OOK*).

Since radio transmitters can *vary* the amplitude, using a simple *on-off scheme* with a *fixed* amplitude is inefficient from a *data transmission* point of view, but *very* efficient from an *implementation* point of view.

Since remote controls transmit only very little data, *OOK* overall is the best solution.


### Sophisticated Encoding Schemes

Once *data transmission* gets into the focus, i.e. when sending sensor data or text messages, more sophisticated encoding schemes can define additional symbols (groups of bits), and use different amplitude levels to identify these symbols.

This increases the data transmission speed as more information can be transmitted in the same time.

> [!TIP]
> *Morse code* can be viewed as *OOK* with *two symbols* instead of *one*: there is a symbol for a *short* tone and a symbol for a *long* tone. Imagine how much longer it would take for morse code messages if there was just *one* symbol, and all letters would need to be defined just by *short* tones.

### EV1527

*EV1527* represents a specialized encoding scheme frequently used in simple commercial remote controls. 

Actually, *EV1527* is the name of an *encoder chip* that first introduced this encoding scheme.

> [!NOTE]
> You do not need a dedicated encoder chip as long as you know the encoding details (especially its timing) and use a microcontroller. There are plenty of free libraries available at *github* that can generate the *EV1527* signals. One of the most popular library is [rc-switch](https://github.com/sui77/rc-switch).

*EV1527* uses *OOK* as carrier signal and transmits a 24-bit data packet. The first 20 bits represent a unique (random) hardware id set by the chip producer. 

The remaining four bits can be used for data, i.e. to address four separate switches.

This scheme ensures that with *2^20 = 1.048.576* different combinations, remote controls are roughly as specific as typical door locks and won't accidentally open the neighbors' garage door.

On the receiver side, a microcontroller can decode the *EV1527*-encoded information (i.e. by using the [rc-switch](https://github.com/sui77/rc-switch) library), or encoding is done by dedicated *decoder chips* such as the *ST3777*.

## Getting Into It

There is a multitude of breakout boards available for *ASK*, both *senders* and *receivers*. 

### Same Basic Principle

All *ASK* *senders* and *receivers* expose just *one data pin*. 

The data to be transmitted is fed to the *senders'* data pin and received at the *receivers'* data pin.

The intellectual part is the data *encoding*: the data to be transmitted needs to be transformed into indivuidual digital bits (*encoded*), and on the *receiver* side transformed back into the original data (*decoded*).

### Simple Route

If you do not want to wrap your head around *ASK* and *encoding/decoding*, then a number of ready-to-go *libraries* exist. 

[rc-switch](https://github.com/sui77/rc-switch) is a very popular example.

### Understanding Technology

If you are curious and hungry for more, [this article](https://www.romanblack.com/RF/cheapRFmodules.htm) provides a great in-depth introduction and explains the technical principles and myths attached to *ASK*.

I strongly recommend reading this article as it explains the tricks to use to improve data rate, stability, and reach of *ASK*-based solutions.


> Tags: ASK, OOK, EV1527, Amplitude-Shift Keying, On-Off Keying, Remote Control, RC-Switch, ST3777

[Visit Page on Website](https://done.land/components/data/datatransmission/wireless/shortrangedevice/am/ask?750969042315242843) - created 2024-04-15 - last edited 2024-04-15
