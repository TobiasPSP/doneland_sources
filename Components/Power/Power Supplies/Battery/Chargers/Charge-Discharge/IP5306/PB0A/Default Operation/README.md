<img src="/assets/images/charging.png" width="100%" height="100%" />

# PB0A Default Operation

> How To Use PB0A 1S LiIon Charger/Discharger Without Touching Its I2C Interface

The **PB0A** module can be used *as-is* and without utilizing its built-in *I2C* interface. This article discusses **PB0A** basic operation, wiring, and default behavior.


<img src="images/pb0a_top_t.png" width="30%" height="30%" />

If you want to *change* any of its *default* settings, you can add a *microcontroller* later and use its *I2C* interface.

> [!TIP]
> Before reading on, make sure you read the article about the [IP5306](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/) chip that **PB0A** uses, and the [**PB0A** overview article](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/).


## Overview

By default - without adjustments made through the *I2C* interface - **PB0A** works like this:

| Feature | Description |
| --- | --- |
| Battery | Connects to a single *LiIon* cell (*1S*) through two through-hole pins marked with a `battery symbol`. The pin next to the little "pin" in this symbol (adjacent to pin `K`) is `BAT+`, the other one (adjacent to `DATA` and `unmarked`) is `BAT-`. |
| Charger Input | Built-in *USB-C* connector serves as *external power source* to *charge* the battery. This connector is **uni-directional** and can only be used for charging. Charging occurs at a maximum of **2.1A**. |
| Power Output | Pins `5V-` and `5V+` provide stabilized output power at **5V** and a maximum of **2.4A** (12W).<br/>- when charging, this output is powered by charger<br/>- when not charging, this output is powered by battery and internal boost controller |
| Push Button | A push button can be installed at `K` and `5V-`. When present, a single push turns power output on manually, and a double short press turns output off manually. |
| Auto-Power | By default, power output is enabled *automatically* when a load is connected, and disabled *automatically* once the load drops **<50mA** for a period of **>32s**, so no push button (manual operation) is required |
| RGB LED | A single *RGB LED* indicates current operational status |


<img src="images/pb0a_pins_basic.png" width="100%" height="100%" />


## Wiring

This is the typical basic wiring:



<img src="images/pb0a_default_wiring.png" width="100%" height="100%" />



> Tags: Charger, Li-Ion, LiIon, Li-Po, LiPo, IP5306, PB0A, Powerbank

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip5306/pb0a/defaultoperation?757111071612250154) - created 2025-07-11 - last edited 2025-07-11
