<img src="/assets/images/battery.png" width="100%" height="100%" />


# 2S - Using 2 Batteries in Series

> 2S BMS Protect Two (Groups of) Batteries From Mishap. Combined With Balancing They Are A Perfect Fit For Your Batteries.

A **2S BMS** is needed to protect *two* batteries (or groups of batteries connected *in parallel*) that are connected *in series*. 

Each lithium battery has a voltage between *3.2V*-*4.2V*, depending on state of charge. When you connect two of them *in series*, the **BMS** needs to handle a voltage in the range of *6.4V*-*8.4V*.





## 3A

For currents up to **3A**, you can use a very small **BMS**:

<img src="images/bms_2s_3a_top_angle_t.png" width="100%" height="100%" />

The connectors are located on the back:

<img src="images/bms_2s_3a_bottom_t.png" width="100%" height="100%" />


Connect the batteries like this:

* First battery string to **B-** (-) and **BM** (+)
* Second battery string to **BM** (-) and **B+** (+)


The output voltage is available at **P+** and **P-**.

## 8A

For currents up to **8A**, a board with more powerful *MosFET* like this one is necessary:

<img src="images/bms_2s_8A_top_angle_t.png" width="100%" height="100%" />

The terminals are accessible both from top and bottom.

<img src="images/bms_2s_8a_bottom_t.png" width="100%" height="100%" />


Connect the batteries like this:

* First battery string to **B-** (-) and **BM** (+)
* Second battery string to **BM** (-) and **B+** (+)

The output voltage is available at **P+** and **P-**.

## 10A

For currents up to **10A**, a very *compact* board is available:

<img src="images/2s_10a_top_angle_t.png" width="100%" height="100%" />

Unfortunately, the compactness of the board did not leave room for markings on the front side. Instead, the markings for the soldering pads were printed on the *back side*:


<img src="images/2s_10a_bottom_t.png" width="100%" height="100%" />

On the other end, the board has a big soldering pad marked as **B-** which is accessible from both sides, and two smaller ones marked **B1** and **B+** on the backside whereas the solder pads are accessible on the front.


Connect the batteries like this:

* First battery string to **B-** (-) and **B1** (+)
* Second battery string to **B1** (-) and **B+** (+)

The output voltage is available at **B+** and **C-**. These two pads are accessible from both sides.


## 20A


For currents up to **20A**, you need a bigger board with more *MosFETs* that share the load, like this one:

<img src="images/bms_2s_20a_top_angle_t.png" width="100%" height="100%" />

All terminals are accessible both from top and bottom.


<img src="images/bms_2s_20a_bottom_t.png" width="100%" height="100%" />


Connect the batteries like this:

* First battery string to **0V** (-) and **4.2V** (+)
* Second battery string to **4.2V** (-) and **8.4V** (+)


The output voltage is available at **+** and **-** located in the inside of the board.



> Tags: Battery, BMS, 2S

:eye:&nbsp;[Visit Page on Website](https://powershell.one/doneland_test/components/power/bms/2s?268282020426240854) - last edited 2024-02-27
