<img src="/assets/images/light.png" width="80%" height="80%" />

# LED Controller

> Safely Driving LEDs With Constant Current Or Constant Voltage

LEDs cannot be connected directly to an arbitrary power supply. They need a specific **current** to work safely. Applying too much current, or connecting an LED with excessive reverse voltage, can destroy it quickly.

## Overview

When you apply power to any LED, **four things** can happen:

**Connecting power in correct polarity:**

1. **Voltage below Forward Voltage:**

    When the voltage is below the **forward voltage** (specific to a given LED and determined largely by its semiconductor chemistry, so typically related to its color), only very little current flows and the LED remains dark or very dim. LEDs do not have a perfectly sharp voltage threshold, but current rises very rapidly once the voltage approaches their normal forward voltage.

2. **Voltage around or above Forward Voltage:**

    Significant current can flow through the LED. How much current actually flows depends on the voltage:

    * 2a. **Current remains below the LED limit:**

        The LED lights up, and its brightness depends mainly on current. With increasing current, the LED gets brighter, while increasingly more energy is converted to heat as well. Close to their maximum current, high-performance LEDs can get very hot and require adequate cooling. At 50 % of the current, the same LED might already produce 70-80 % of the brightness and stays cool.

    * 2b. **Current exceeds the LED limit:**

        The LED produces excessive heat. Its forward voltage typically decreases as it heats up, which can allow more current to flow when powered from an uncontrolled voltage source. This leads to thermal runaway and quickly damages or destroys the LED.

**Connecting power in reverse polarity:**

3. **Voltage below Reverse Voltage:**

   When the reverse voltage remains below the LED's maximum permitted **reverse voltage**, only a tiny leakage current flows and the LED remains dark.

4. **Voltage exceeds LED Reverse Voltage:**

   The LED can enter reverse breakdown and may quickly get damaged or destroyed.

## Supplying Power to LEDs

The important property to control is the **current** flowing through an LED. The voltage across the LED then settles at its corresponding forward voltage. That's why DC-DC regulators designed specifically for LEDs are often called **LED drivers**: unlike ordinary *constant-voltage (CV)* regulators, many of them regulate output current directly (*constant-current, CC*).

Practically, three ways have been established to drive LEDs:

* **Resistor:**

  For low-power indicator LEDs, simply put a resistor in series. It limits the current by dropping the remaining supply voltage. Small variations and waste heat are negligible since such LEDs require only currents in the mA range.

* **Constant-Voltage (CV):**

  A *constant voltage* supply can be used when the operating conditions are carefully controlled (i.e. exactly specified LEDs with narrow production tolerances, and good cooling). For high-power LEDs, however, directly setting a voltage that happens to produce the desired current is generally less robust:

  * When the LED forward voltage changes, i.e. during heating, then the current changes as well (it rises when LEDs get hot).

  * With multiple LEDs or LED strings connected in parallel, small differences in forward voltage can cause current to be distributed unevenly, resulting in differences in brightness and temperature.

* **Constant-Current (CC):**

  For high-power LEDs or LED strings, this is generally the best power supply because you are directly controlling the property that matters most to the LED: its **current**.

## Dimming and Flash Patterns

Dimming is always possible with a power supply that can *dynamically adjust* the current: When you use a *constant current* regulator and reduce the current threshold, this directly reduces the LED brightness.

This type of dimming works particularly well because the LEDs remain continuously on and cannot cause flickering. However, many inexpensive regulators feature at best a manual potentiometer to adjust current, so this type of dimming is often not very practical.

### PWM (Pulse Width Modulation)

LEDs respond extremely fast and can be turned on and off in microseconds or less. That makes them ideal for PWM dimming: PWM turns the LED on and off at high frequency. 

When you set this frequency high enough, the human eye cannot distinguish the individual pulses, and visible flickering is avoided. If the PWM frequency is high but not high enough, you may still see flickering or banding in smartphone cameras and video recordings. Likewise, when you reduce the frequency (considerably), you get flashing patterns like the ones in an emergency light.

#### Driver with PWM Support
PWM is very simple to control. Almost any dirt-cheap microcontroller can produce it at almost any frequency. The much tougher part is the actual LED driver: it must support sufficiently fast switching if you want to dim LEDs or - using the same principle, but at a much lower frequency - make the LED flash (i.e. for emergency lights).

Many LED drivers expose a dedicated `PWM`, `DIM` or `ENABLE` pin for this purpose (although `ENABLE` pins may or may not work; some turn off the entire regulator, not just the output). The important part is that the driver electronics **remain powered while the LED current is switched on and off** in a controlled way.

#### Driver without PWM Support
If an LED driver does not provide such an input, an external MOSFET can sometimes be used before or after the driver to implement switching. This needs to be evaluated for the particular driver, though: 

Turning the entire DC regulator repeatedly off by placing the MOSFET on its input side can cause slow restarts or unwanted soft starts. Removing the DC regulator **load** rapidly by switching its output with the MOSFET can interfere with its feedback loop or cause voltage overshoot unless the regulator is designed to tolerate this type of operation.

In a nutshell:

* **Simple Continuous Operation at Full Brightness:**

  Any suitable LED driver will do, preferably *constant current*.

* **Adjustable LED brightness and/or Flash Patterns:**

  Prefer an LED driver with a dedicated PWM, DIM or fast ENABLE input.

## Built-In Drivers

Some LEDs come with built-in drivers or control electronics, especially *LED strips*. 

The popular and ubiquitous *WS2812 LED*, for example, combines LEDs with integrated current-control electronics and a digital communication interface. The electronics takes care of LED current control already, and you control brightness and color via a digital one-wire protocol, i.e. by using a microcontroller or a ready-to-use device.

In such cases, you **must supply** a **constant voltage (CV)** within the voltage range specified for the LED or LED strip (typically around 5 V for WS2812-type LEDs).


> Tags: LED Driver, WS2812, COnstant Current, Constant Voltage

[Visit Page on Website](https://done.land/components/light/ledcontroller?319805092109242628) - created 2024-09-08 - last edited 2026-09-23
