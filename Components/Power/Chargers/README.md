<img src="/assets/images/charging.png" width="100%" height="100%" />


# Charging Batteries

> Chargers Control Voltage and Current To Safely Charge Batteries

*Rechargeable batteries* are everywhere today and provide powerful portable and cost-effective energy. 

Which makes *chargers* ever more interesting. In this section we take a look at *what exactly* a charger does and how it differs from normal *power supplies*.

## Understanding Charging

Batteries work both ways: you can *draw* energy (in which case the battery voltage slowly sinks), and you can *feed* energy (in which case the battery voltage slowly raises).

The art of *feeding energy* to a battery in an appropriate way is what makes *Chargers* unique.

### Voltage Drives, Current Matters 

To charge a battery, you cannot simply connect a power supply to it and hope for the best. Instead, there are two prerequisites:

* **High enough voltage:** the *charging voltage* must be above a certain threshold. If the voltage is too low, the energy won't flow into the battery, and nothing happens.
* **Low enough current:** you *must* limit the *current* so that the battery can accept and store the new energy. If you feed *too much* energy into the battery, it will heat up and eventually explode.

<details><summary>What happens when I connect a regular bench power supply to a battery?</summary><br/>

Three things can happen:

* **Voltage lower than battery voltage:** if the power supply voltage is significantly below the full charge battery voltage, no energy would flow from the supply to the battery. Possibly the battery would start to feed power to the power supply instead.
* **Small power supply:** if the voltage is high enough, and it is a small power supply with only a limited output current of maybe *1A*, it could in fact work as a charger at first. Once the battery is fully loaded, though, the power supply would continue to feed energy to the battery. The battery, unable to store any more energy, would heat up and eventually explode.
* **Big power supply:** should you connect a huge and powerful bench power supply to a battery, large currents flow into the battery. The battery would not be able to store so much energy so quickly, and the excess energy would heat up the battery and eventually cause it to catch fire or explode.


</details>

### What a Charger Does

A *charger* controls *voltage* and *current* to provide just the right amount of energy to the battery.

For lithium-based batteries, here is what that means:

* Phase 1 - **Constant Current (CC):** the charger first supplies a constant current to the battery: it automatically *raises the voltage* until the desired *current* flows. The battery now accepts and stores this current, and while it does so, its *voltage* slowly raises.
* Phase 2 - **Constant Voltage (CV):** while charging, the charger *monitors* the voltage, and when the voltage reaches a threshold that indicates that the battery is almost fully charged, it switches to *constant voltage*: the *voltage* gets fixed and no longer raises. Now, this fixed voltage can drive lesser and lesser energy into the battery. The *current* falls.
* Phase 3 - **Turning Off:** When the *current* that flows into the battery falls below a threshold, the battery is considered *fully charged*, and the charger stops charging the battery. 

This is the general recipe. The *actual* constant current in *Phase 1*, and the *actual* constant voltage in *Phase 2* depend on the battery chemistry and battery voltage you are charging.


### Technical Requirements

Here is what *any* charger must be capable of:

* **Energy source:** it needs to *receive* energy that it can pass on to the battery. The energy source can be *AC* or *USB* or a regular *bench power supply*
* **Power Regulator:** it needs to contain a *power regulator* that can control *voltage* and *current*

<details><summary>Is a **Buck** converter a charger?</summary><br/>

A **Buck** converter takes a range of input voltage and converts it to a lower *specific* output voltage. Many **Buck** converters can also control *constant current*, and if that's the case they can be used to charge batteries.

Let's assume you want to charge a single *18650 LiIon battery*, and let's assume this battery can accept a *5A* maximum charging current. Since it is a *LiIon* battery, its maximum voltage is *4.2V*.

When you set the **Buck** converter to a maximum voltage of *4.2V* and also set its *constant current* to *5A*, it will automatically follow much of the above mentioned *charging recipe*:

When you connect an empty *18650 LiIon cell* to it, first the *constant current* would kick in and limit the *current* to *5A* by lowering the *voltage* appropriately.

Once the battery gets charged, the voltage rises until at one point it reaches the maximum voltage of *4.2* that the **Buck** converter was set to. Now *constant voltage* limits the voltage to *4.2V*, and the current would slowly decrease.

The *Buck* regulator would still not be a safe charger because what's missing is step 3: cutting off the power when the battery is full. 

</details>



> Tags: Charger, CC, CV, Battery

:eye:&nbsp;[Visit Page on Website](https://done.land/components/power/chargers?247473031903243238) - last edited 2024-03-03
