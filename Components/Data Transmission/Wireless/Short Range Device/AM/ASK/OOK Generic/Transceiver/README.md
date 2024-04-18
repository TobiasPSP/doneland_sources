<img src="/assets/images/radio_walkytalky.png" width="100%" height="100%" />
 
# Transceivers

> A Transceiver Can Send And Receive Radio Signals And Establishes True Two-Way Communications 


In *simple* remote control or data transmission scenarios, information travels *one-way* only. Here, dedicated *senders* and *receivers* are best used.

In *more sophisticated* scenarios, true *two-way communication* is required:

* **Acknowledgement:** Sending *confirmations* that data transmissions were received correctly
* **Messengers:** Sending *text messages* 

## Sophisticated Remote Controls

Simple *remote controls* can control remote devices fairly reliably. You typically see the effect (i.e. an opening garage door). If the transmission was lost, and the garage door won't open, you get a bit closer to it and try again.

### Scenarios Requiring Acknowledgement

In scenarios where you can't immediately see the effect of the transmission, additional *acknowledgements* are often used. 

For example, when you build a *switch board* to control electric appliances in the house, you may want to actually see the status of each device, and whether it has responded appropriately.

In these scenarios, *transceivers* are needed that can both *send* and *receive* data.

A remote control in this case would use one *transceiver*. Initially, it would send out the same remote control signal, just like a dedicated *sender* would. Except that the *transceiver* would go into *receiver* mode once it has sent the control signal, and wait for confirmation.

On the remote side, another *transceiver* would be in *receiver* mode and pick up the signal. It would then enable or disable the intended appliance. At the same time, it would *send back* a confirmation so that the remote control knows the state of the controlled device.

### Clone Remote Controls

A *transceiver* can also be used to *clone* an existing remote control.

Since regular remote controls can send out *fixed control codes only*, either your *garage door* or *plug* (etc) came with a number of remote controls that all share the same hardware id, or you are left with just *one* remote control. 

*Cloning* a *remote control* is done by a *transceiver*. In *learning mode*, it uses its *receiver* to pick up and store the signal from the original remote control. Once done, it can then use its *sender* to play back the recorded control signals, mimicking (cloning) the original remote control.

This way, you can have as many remote controls for a given remotely controlled device as you want.

> Tags: Sender, Receiver, Transceiver, Clone, Remote Control

[Visit Page on Website](https://done.land/components/datatransmission/wireless/shortrangedevice/am/ask/ookgeneric/transceivers?810861040016243141) - created 2024-04-15 - last edited 2024-04-15
