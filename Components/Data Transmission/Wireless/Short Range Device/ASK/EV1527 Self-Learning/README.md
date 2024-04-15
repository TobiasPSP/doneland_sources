<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# EV1527 Learning Code Format

> Special Data Format For RF Senders/Receivers To Manage Self-Learning Control Codes

Very often, *RF senders* and *receivers* are used in simple *remote control* scenarios: a typical *4-button remote control* for example remote-controls four individual devices.


## Fixed Control Codes
In these scenarios, *fixed control codes* are transmitted. These codes are permanently built into the senders.

This is why you *cannot* control the transmitted data with these devices. You cannot i.e. transmit *weather station* sensor data this way.

## Learning Receiver
On the other end, there must be a *receiver* that can *learn the fixed codes* emitted by the *sender*.


For this use case, *EV1527* is a standard format of learning codes that some *RF senders and receivers* implement.

> [!CAUTION]
> A *RF sender* or *receiver* that implements *EV1527* controls autonomously the content of the data that is transmitted. You *cannot* use such devices to transmit arbitrary sensor data.

## Working Principle

*Senders* that adhere to *EV1527* have *built-in* and *fixed* factory codes. They are programmed into the *sender* by the manufacturer and cannot be changed.

*Receivers* support a *learning mode*: when enabled, they detect the code sent out by a particular *sender*, and store it.

This way, *receivers* are *paired* with the *sender* by the end user.

### Cloning Remote Controls

There are also more sophisticated devices that combine a *receiver* and a *sender* in order to *clone* remote controls. They work fundamentally in the same way:

* **Learning Mode:** when you enable the *learning mode* of such a device, it enables its self-learning *receiver*. When you now send a *fixed* signal from an *original* remote control, it is picked up and stored.
* **Replay-Mode:** The device is also a *sender*, however it does not use *factory default fixed codes* but instead the codes it has previously picked up. This way, the device can *play back* the learned codes and *mimick* the behavior of the original remote control.




> Tags: EV1527, RF, Sender, Receiver, Remote Control, Self-Learning, Code, Clone Remote Control, TX118SA

[Visit Page on Website](https://done.land/components/datatransmission/wireless/radio/ev1527self-learning?492032041301241609) - created 2024-04-01 - last edited 2024-04-01
