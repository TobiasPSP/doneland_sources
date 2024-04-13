<img src="/assets/images/amplifier.png" width="80%" height="80%" />

# XY-P5W

> 3.7-24V 5W Stereo Amplifier With Bluetooth Connectivity

This small breakout board combines *Bluetooth 5.0* reception with a digital 2x5W stereo amplifier. It is based on the **5W** *PAM8406* digital power amplifier module.

<img src="images/audio-xy-p5w_angle2_t.png" width="50%" height="50%" />

> [!NOTE]
> The board discussed here is marked as *XY-WRBT* on its back side. It is also called *XY-P5W*. There are  *many variations* of this board available with subtle differences in board design and functionality. Some even ship with separate external remote control.

## Where To Use

This board comes with everything needed to built a small bluetooth-ready sound box. The output volume is moderate but sufficient (2x5W). 

Its wide voltage input range makes it versatile to use. Support for *LiIon* and *LiPo* batteries including automatic switch-off at low voltage and charging through *Micro USB* are convenient extras. 


## Technical Data

| Item               | Description                                  |
| ------------------ | -------------------------------------------- |
| Power Supply       | Micro USB, one lithium cell, external 3.7-24V supply |
| Audio Amplifier              | 2x5W |
| Speaker Impedance  | 2-8 Ohm (5W@2Ohm, 3W@4Ohm, 2W@8Ohm)           |
| Audio In           | Headphone Jack 3.5mm                         |
| Bluetooth Distance | <15 Meter, SNR >= 90dB                       |
| Size               | 42x32x5mm                                   |

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

Audio can be played to headphones via 3.5mm headphone jack, or by connecting two speakers with common ground to the speaker pins.

Volume is controlled by a half-rounded switch:

* **Volume:** turn switch towards the USB connector to lower volume, and turn it to the other direction to raise it.
* **Play/Pause:** press the button to toggle *play* and *pause*.

## On and Off

Next to the external power input pins, there are two solder pads marked *woke*. They can be used to turn the board on and off:

Connect the pins for 2 seconds to toggle between *on* and *off*.

<img src="images/audio-xy-p5w_top_t.png" width="50%" height="50%" />

## Through-Hole Pins

All pins are through-hole and accessible from the back side as well.

Some pins are labeled on the backside only:


<img src="images/audio-xy-p5w_back_t.png" width="50%" height="50%" />


## Operation

After supplying power, a *blue LED* starts blinking. The device is now in bluetooth *pairing mode* and can be detected by i.e. your smartphone.

Once a bluetooth connection is made and the board is coupled, the *blue LED* stops blinking and lights constantly.

When music is played back, the *blue LED* flashes slowly.

## Data Sheet

[PAM8406 5W Audio Amplifier](materials/pam8406_datasheet)



> Tags: Audio, 5W, Amplifier, Stereo, Bluetooth, XY-WRBT, XY-P5W, PAM8406

[Visit Page on Website](https://done.land/components/audio/amplifier/bluetooth/xy-p5w?321039041911244644) - created 2024-04-11 - last edited 2024-04-11
