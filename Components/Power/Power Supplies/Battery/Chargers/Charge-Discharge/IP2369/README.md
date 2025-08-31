<img src="/assets/images/charging.png" width="100%" height="100%" />

# IP2369 Power Management IC

> Integrated 45W Charger/Discharger for Single LiIon/LiPo/LiFePo4 Batteries

The [IP2369](materials/ip2369_datasheet_en.pdf) is a highly integrated *power bank* system-on-chip (SOC) with a charger and a discharger that works with **2-6S** lithium cells (supports LiIon, LiPo, and LiFePo4).

It supports two USB ports simultaneously (1x USB-A output, 1x USB-C in-/output).

IP2369 has built-in I2C support and can be monitored or fine-tuned by a microcontroller.



## Overview
The special feature of IP2369 is its powerful 250kHz boost converter that can boost a voltage as low as 4.5V to as high as 25.2V.

This works both ways which is important:

* **Charging:**     
  You can charge your battery with as low as 5V USB. Depending on your battery pack configuration, IP2369 boosts this voltage to up to 25.2V:

  | Pack | Min charging voltage | Max charging voltage |
  |---|---:|---:|
  | 2S | 6.0 V | 8.4 V |
  | 3S | 9.0 V | 12.6 V |
  | 4S | 12.0 V | 16.8 V |
  | 5S | 15.0 V | 21.0 V |
  | 6S | 18.0 V | 25.2 V |

* **Discharging:**    
  The minimum battery configuration is **2S** (6.0-8.4V). Even at 6.0V input, IP2326 can boost this battery voltage to 20V output at 1.5A (30W) at 92% efficiency.

  That's why IP2326 supports full USB PD including voltages much higher than the battery voltage, i.e. 20V.

## Use Cases

The enormous flexibility allows for a wide range of use cases:

* **Powerbank:**     
  IP2326 works with almost any battery pack (except **1S**, single cells). Simply by adding a board with IP2326, you get a powerful powerbank solution with fast charging support both for input and output.  


* **Charger:**     
  You can use IP2326 as a charger only, too: for example, when you set IP2369 to **5S** configuration, a simple 5V USB input could be used to charge 18-20V tool batteries from Makita and similar vendors.

  Since the charger input supports fast charging protocols, if you connect a USB PD power supply, it would automatically request a higher input voltage and charge with up to 45W (i.e. 2.2A at 20V input).    

* **Boost Converter:**    
  You can use this chip as a boost converter only: when you configure it to **6S**, it would, for example, convert 5V (or 12V, or any voltage within its input range of 4.5-25V) input to around 24V output.

### Protections

IP2369 comes with all basic battery protection features:

* Short Circuit Protection
* Overcharge Protection
* Over-Discharge Protection
* Over-Current Protection

The system protects itself as well:

* Input Overvoltage Protection
* Input Undervoltage Protection
* IC Over-Temperature Protection

Optionally, an external 10K (B=3380) NTC Thermistor can be connected for added safety. 

* Charging stops at below 0C and above 45C.
* Discharging stops at below -20C and above 60C.

> Depending on the breakout board you are using, when connecting a NTC Thermistor to a board that was not previously equipped with a thermistor, it may be necessary to also change a resistor value on the board. Else, the thermistor would generate significantly wrong readings.   

### LED / State of Charge

IP2326 contains a state-of-charge meter that can be implemented with up to 4 LEDs.


## Charging / Input Voltage
IP2326 accepts an input voltage in the range of 4.5-25V. Typically, power is supplied via USB-C, but you can also connect a classic power supply.

When using USB-C input, IP2326 supports USB PD and other fast charging protocols:  AFC/FCP/PD2.0/PD3.0/PD3.1. 

When such protocols are available, IP2326 automatically requests higher input voltages that work best for the required output voltage. The maximum input current can reach 2.25A at 20V (45W) with an efficiency of 96%.

### Input Current
When no fast charging protocols are available (i.e. you use a simple power supply), the maximum input current is set by the input voltage:

| Input Voltage | Maximum Input Current | max Watt |
| --- | --- | --- |
| <6.5V  | 3A | 19.5W |
| <9.5V | 2A | 19W |
| <13.5V | 1.5A | 20.3W |
| <16.5V | 3A | 49.5W |
| <=24V | 2.25A | 54W |

> In addition, the maximum input power can be limited by a resistor in which case this lower value is in effect.



## Batteries 

IP2326 can configure both the cell chemistry (voltage per cell), and battery pack configuration (**2S-6S**). This is typically done via external resistors.

| Battery Pack | RBAT_NUM |
| --- | --- |
| 6S | 18K |
| 5S | 13K |
| 4S | 9.1K |
| 3S | 6.2K |
| 2S | 3.6K |

The battery type can also be configured via resistor:

| Chemistry | Max. Cell Voltage | RVSET | Remark |
| --- | --- | --- | --- |
| LiIon/LiPo | 4.2V | 9.1K | default |
| LiIon/LiPo | 4.1V | 6.2K | use only with verified batteries |
| LiIon/LiPo | 4.3V | 13K | use only with verified batteries |
| LiIon/LiPo | 4.35V | 18K | use only with verified batteries |
| LiIon/LiPo | 4.4V | 27K | use only with verified batteries |
| LiFePo4 | 3.65V | 3.6K | default |

## Output Voltage
IP2326 converts the battery voltage to USB 5V plus a range of fast charging protocols: PD2.0/PD3.0/PD3.1, QC2.0/QC3.0/QC3+, FCP, AFC, and Apple.

The output voltage can be supplied to both a USB-A and a USB-C port.

### Enabling/Disabling Output
IP2326 automatically enables output ports when a load is connected, provided the load is significant. Light loads may not trigger automatic turn-on.

A push button can be connected that manually opens the output ports.

#### Light-Load Shutdown

Since IP2326 was designed primarily for use in powerbanks, it automatically supports light load shutdown:

| Condition | Timeout when low load is detected |
| --- | --- |
| USB PD | 16 minutes |
| Multi-port output mode | <80mA (MOS Rds_ON@15mohm) 16 seconds |
| Single output port | <350mW 32 seconds |

### Maximum Output Power
With USB-C and PD2.0/PD3.0/PD3.1, the maximum output power can be limited:

| Maximum Output Power | Available Outputs | RPSET |
| --- | --- | --- |
| 45W | 5V/3A,9V/3A,12V/3A,15V/3A,20V/2.25A | 18K |
| 36W | 5V/3A,9V/3A,12V/3A,15V/2.4A,20V/1.8A  | 13K |
| 30W | 5V/3A,9V/3A,12V/2.5A,15V/2A,20V/1.5A  | 9.1K |
| 27W | 5V/3A,9V/3A,12V/2.25A,15V/1.8A  | 6.2K |
| 20W | 5V/3A,9V/2.22A,12V/1.67A  | 3.6K |

IP2369's USB-A1 and USB-C can also support QC2.0/QC3.0/QC3+, FCP, AFC, and Apple.

### Fast Charging Protocols
Since IP2326 is a single-inductor solution, it can only provide one output voltage at any time. That's why fast charging protocols are enabled with single output ports only. Once both output ports are used, fast charging protocols are disabled.

This is a safety feature. Here is why:

* When you connect a device to **either** the USB-C or the USB-A port, then this port can negotiate fast charging protocols, and IP2326 sets the requested voltage.
* If you connect a second device to the remaining other port, it would immediately receive the same voltage that the first port negotiated. This is dangerous and could destroy devices.
* This is why IP2326 disables any fast charging protocol once you connect a device to the second port, and falls back to standard USB 5V on both ports. This involves a temporary power break.


## Materials

[IP2369 Datasheet](materials/ip2369_datasheet_en.pdf)             
[IP2369 Datasheet Original (Chinese)](materials/ip2369_datasheet_ch.pdf)   

> Tags: Charger, Li-Ion, Li-Po, Boost Converter

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2369?728608081930253114) - created 2025-08-29 - last edited 2025-08-29
