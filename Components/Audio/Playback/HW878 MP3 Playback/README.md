<img src="/assets/images/amplifier.png" width="80%" height="80%" />

# HW-878 MP3 Prompter

> 5V MP3 File Playback Module With SD Card Slot And Small Amplifier

This *MP3 playback module* comes with a *SD Card Reader Slot* and can play back MP3 songs. A built-in mini amplifier (3W) lets you directly connect the board to a speaker.

The *SD Card* media is accessible via *USB* port from a computer.

> [!TIP]
>
> This board does not require any external components (other than a speaker) and can be operated without a microcontroller (9 tracks selectable). When controlled by a microcontroller, up to 31 tracks ae selectable. Via a solder bridge, tracks can be played circular (in a loop).

## Connections

The board comes with the following connectors:

| Connector     | Description                                                  |
| ------------- | ------------------------------------------------------------ |
| Speaker       | one speaker (mono), 4-8 Ohm, 3 Watt (newer board versions: 5W) |
| Headphone     | 3.5mm. When a head phone is connected, the speaker turns off. |
| Power Supply  | 5V                                                           |
| Trigger Ports | 9, can trigger playback of up to 9 song files (31 songs with external microcontroller) |
| Pause         | switches between *play* and *pause*                          |
| Circular Play | a solder bridge controls circular (endless) playing of a track |
| USB           | Micro-USB for power supply and/or computer access to *SD Card* media |

The board comes with a *USB* port that can supply power. It also allows a computer to access the *SD Card* like a flash drive. When the computer is accessing the *SD Card*, it cannot be used to play back music.

## LED

A status *LED* flashes when the *SD Card* is accessed. During music playback, the *LED* is on (not flashing).

## Volume

Volume can be adjusted with a potentiometer.

## Playing Order

The order in which sound files depends on the physical location of the file on the *SD Card* media controls the order. 

Make sure you freshly format the *SD Card* media and then save the files to the *SD Card* in the order in which you want to play them back.

> [!CAUTION]
>
> After you are done copying sound files from a computer to the *SD Card* via *USB*, disconnect the computer and then power off and on the board. You cannot play audio files while there is a computer connection accessing the *SD Card reader*.

## Manually Controlled

The board can be used *stand alone* in which case nine *trigger buttons* can be used to play the first nine tracks saved to the *SD Card* media. Pull *A1* trough *A9* to *GND* for at least *50ms*.

## Microcontroller-Controlled

If pin *A10* is grounded before powering the board, the board switches to *coding mode*.

In *coding mode*, pins *A1* through *A5* control up to 31 songs using binary encoding:

| Track | A1   | A2   | A3   | A4   | A5   |
| ----- | ---- | ---- | ---- | ---- | ---- |
| 1     | 1    | 0    | 0    | 0    | 0    |
| 2     | 0    | 1    | 0    | 0    | 0    |
| 3     | 1    | 1    | 0    | 0    | 0    |
| 4     | 0    | 0    | 1    | 0    | 0    |
| 5     | 1    | 0    | 1    | 0    | 0    |
| 6     | 0    | 1    | 1    | 0    | 0    |
| 7     | 1    | 1    | 1    | 0    | 0    |
| 8     | 0    | 0    | 0    | 1    | 0    |
| 31    | 1    | 1    | 1    | 1    | 1    |

To control playback, n *control mode* pins *A7*, *A8*, and *A9* are assigned as follows:

* **Next Track:** *A7* to *GND*
* **Previous Track:** *A8* to *GND*
* **Play or Pause:** *A9* to *GND*

## File Naming Scheme

The playback order of files stored on *SD Card* media depends on their physical file location. 

To control the file playback order, first *format* the media, then *copy* the files in the intended playback order onto the media.

Even though the physical storage location of sound files controls the playback order, the following naming scheme is required:

* **Folder 01:** After formatting the *SD Card* media, create a folder named *01*.
* **File Naming:** All sound files need to start with a three-digit number (*001*-*999*)

### Auto-Play

The module can automatically start playing a sound file after power-up. 

To enable this, add another folder named *99* on the *SD Card* media, and place the autostart audio file into this folder.

## Technical Data

| Item                                          | Description                                |
| --------------------------------------------- | ------------------------------------------ |
| Power Supply                                  | 5V, 1000mA                                 |
| Connectors For Sound Playback Trigger Buttons | 9                                          |
| Speaker Impedance                             | 1 Speaker, 4-8 Ohm, 3W                     |
| Bypass Mode                                   | High: bypass amplifier                     |
| SD Card Reader                                | up to 16GB Cards supported, FAT filesystem |
| Size                                          | 39x39x6mm                                  |

> Tags: Audio, 3W, Amplifier, Mono, HW-878, SD Card