<img src="/assets/images/amplifier.png" width="80%" height="80%" />

# XY-WRBT (0W)

> 3.7-24V Bluetooth Audio Receiver Board

This board is a pure *Bluetooth* audio receiver and comes without an audio amplifier. 

Use it with the headphone jacks, or connect the stereo output to a dedicated external audio amplifier.


<img src="images/audio-xy-wrbt_angle2_t.png" width="50%" height="50%" />

> [!NOTE]
> The board discussed here is marked as *XY-WRBT* on its back side. It is *very similar* to *XY-P5W* which in contrast has a built-in *2x5W audio amplifier*.


## Where To Use

This board handles all the *Bluetooth* audio reception and comes with built-in support for handling *LiIon* and *LiPo* batteries.

It can serve well in *DIY Bluetooth Sound Boxes* where you choose to use a separate dedicated *audio amplifier*.

## Where To Avoid

If you are looking for a one-stop solution to creating a simple *Bluetooth* sound box, go get the integrated boards that come with *2x5W* or *2x15W* audio amplifiers on-board (*XY-P5W* or *XY-P15W*).


## Technical Data

| Item               | Description                                  |
| ------------------ | -------------------------------------------- |
| Power Supply       | Micro USB, one lithium cell, external 3.7-24V supply |
| Audio Amplifier              | no amplifier |
| Speaker Impedance  | no speaker connections, just pins to connect to external amplifier           |
| Audio In           | Headphone Jack 3.5mm                         |
| Bluetooth Distance | <15 Meter, SNR >= 90dB                       |
| Size               | 44x30x5mm                                   |

## Power Supply

The board can be supplied with power in many ways due to its wide voltage range:

* **Micro-USB:** connect a common smartphone charger via USB
* **Lithium battery:** power the board with one common LiIon or LiPo cell
* **External:** connect to car voltage or any other power supply (3.7-24V)

Any power supply should be capable of supplying *20W* of power (*4A* at *5V*). It *must* be greater than *10W* (*2A* at *5V*). Insufficient power supplies negatively affect sound quality.

### Using Lithium Battery

The board power can be supplied by a single *LiIon* or *LiPo* battery. The board automatically turns off when the input voltage drops below *3.3V*, protecting lithium batteries from over-discharge.

Once over-discharge protection has kicked in and automatically turned off the board, after recharging the battery power on the board again. To *unlock* the protection, it may be necessary to connect the *on* pins for at least *2 seconds* (if you connected an *on/off* push button to this port, press the button for >2sec.)

> [!TIP]
> When you power this board via battery, and the battery is approaching its empty state, the voltage falls to a level where the board starts making "sizzling" noises. This can be used as an indicator to recharge batteries before over-discharge protection kicks in.




The lithium battery can be directly charged via the *Micro USB* connection.

> [!TIP]
> Never operate lithium batteries without *battery protection board* (BMS): check your battery to find out whether it has a built-in *BMS*.


## Audio Out

Audio can be played to headphones via 3.5mm headphone jack, or by connecting the stereo output to an *external amplifier*.

> [!CAUTION]
> You cannot directly connect speakers to this board as it does not have a built-in audio amplifier.



Volume is controlled by a half-rounded switch:

* **Volume:** turn switch towards the USB connector to lower volume, and turn it to the other direction to raise it.
* **Play/Pause:** press the button to toggle *play* and *pause*.

## On and Off

Next to the external power input pins, there are two solder pads marked *woke*. They can be used to turn the board on and off:

Connect the pins for 2 seconds to toggle between *on* and *off*.

<img src="images/audio-xy-wrbt_top_t.png" width="50%" height="50%" />

## Through-Hole Pins

All pins are through-hole and accessible from the back side as well.

Some pins are labeled on the backside only:


<img src="images/audio-xy-wrbt_back_t.png" width="50%" height="50%" />


## Bluetooth Connect

After supplying power, a *blue LED* starts blinking. The device is now in bluetooth *pairing mode* and can be detected by i.e. your smartphone.

Once a bluetooth connection is made and the board is coupled, the *blue LED* stops blinking and lights constantly.

When music is played back, the *blue LED* flashes slowly.

> [!TIP]
> All *Bluetooth* functionality is provided by a *AC...* chip manufactured by [Zuhai Jie Li](https://www.zh-jieli.com/). This company produces cheap chips for a wide variety of consumer products.



> Tags: Audio, Stereo, Bluetooth, Receiver, XY-WRBT

[Visit Page on Website](https://done.land/components/audio/amplifier/bluetooth/xy-wrbt(0w)?623296041613240005) - created 2024-04-02 - last edited 2024-04-13
