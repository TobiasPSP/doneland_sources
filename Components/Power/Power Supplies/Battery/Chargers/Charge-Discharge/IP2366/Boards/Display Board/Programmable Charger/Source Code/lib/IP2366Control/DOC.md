# IP2366Control 1.2.2

Version 1.2.2 adds read-only `Status::chargeStage()` and `chargeStageName()`.
V1.13 page 8 verifies 0x31 bits 2:0: 0 Standby, 1 Trickle, 2 CC, 3 CV,
4 Waiting, 5 Full, 6 Timeout, 7 Reserved. No register writes or control
thresholds change. Status labels must be used only after a successful status read.

Version 1.2.1 clears SYS_CTL9 (0x09) bit7 EN_Standby during initialization/configuration and settings enforcement. Mask0x80 preserves all lower bits. The firmware calls slow enforcement every 2000 ms. See REGISTER_CONTRACT.md for the supplied datasheet contract.

A standalone IP2366_I2C register driver, extracted from the hardware-confirmed BatCharger 1.0.3 firmware. The portable core has no Arduino, LVGL, display, battery-chemistry, SOC or application-session dependency. An optional Arduino transport preserves the tested GPIO I2C implementation.

Copy this entire `IP2366Control` folder into another PlatformIO project's `lib/` directory, or install its ZIP as an Arduino library. Include `<IP2366.h>` for the portable core and `<IP2366Arduino.h>` only when using the supplied ESP32 adapter.

## Public API

| Method | Meaning |
| --- | --- |
| `begin()` | Probe, attempt bounded bus recovery if needed, disable charging and apply idle port policy |
| `validateSettings(settings)` | Return `nullptr` if valid, or a static error string; no I/O |
| `configureCharger(settings)` | Validate, disable first, apply/read back all controlled fields; leave disabled |
| `chargerOn()` | Enable a previously configured charger; fails if configuration has not succeeded |
| `chargerOff()` | Disable charging, preserving unrelated register bits |
| `enforceSettings(settings, enable)` | Audit/repair desired settings with disable-first/enable-last sequencing |
| `applyIdleConfiguration()` | Enforce idle UFP/source/sink/140 W policy with charging disabled |
| `readVoltage(voltage_mV)` | Read unsigned pack voltage in mV |
| `readCurrent(current_mA)` | Read unsigned battery-current magnitude in mA; direction is separate |
| `readTargetVoltage(target_cell_mV)` | Read configured per-cell target voltage in mV |
| `readChargeCurrentLimit(current_mA, raw_code)` | Read current-limit mA and optionally its raw register code |
| `readStatus()` / `status()` | Acquire/read charge, input, Type-C and fault status; named predicates decode flags |
| `readNtc(reading)` | Read NTC voltage in mV and 20/80 uA excitation indications before/after the pair |
| `failure()` / `clearFailure()` | Inspect/reset the first read/write/readback/validation failure |
| `completionDetected()` | Report completion encountered during a configuration-repair operation |

I/O/action methods return `true` on success and `false` on failure. Do not consume an output argument after its read returns false. Read success establishes transfer/decode success; an out-of-range configuration readback is still returned in decoded units so the application can diagnose/audit it. Failure records retain the first issue until `clearFailure()` or `begin()`. `configureCharger` rejects invalid settings before writing hardware. A successful `chargerOn()` means verified enable-bit readback, not proof that current is flowing; use `readStatus()` and the measurements for that.

`chargerOn()` performs the explicit enable action after successful configuration. The caller remains responsible for checking input/status and applying its lifecycle/fault policy. The BatCharger application does this and retains the bounded startup handshake and latched faults. During active `enforceSettings` repair, missing input or a fault prevents re-enable; a completion flag leaves the charger disabled and sets `completionDetected()`. No method clears live status or fault flags automatically.

## Settings and units

```cpp
ip2366::Settings settings;
settings.cells = 3;
settings.target_cell_mV = 4200;
settings.charge_current_mA = 1000;
settings.termination_current_mA = 100;
settings.precharge_current_mA = 100;
settings.battery_low_cell_mV = 3000;
settings.power_limit_W = 140;

if (ip2366::IP2366::validateSettings(settings) == nullptr) {
    if (charger.configureCharger(settings)) {
        // Charger is now configured and OFF.
        // After application input/fault checks and an explicit start request:
        // charger.chargerOn();
    }
}
```

The driver owns all register masks, shifts, units and conversions. Accepted settings:

- Cells: 2-6, direct encoding in bits 2:0 of register 0x04, user-validated.
- Target: 2500-4400 mV/cell, 10 mV steps.
- Charge limit: 100-9700 mA, 100 mA steps, at least termination current.
- Termination: 50-750 mA, 50 mA steps. Zero semantics are not assumed.
- Precharge: 100-1000 mA, 50 mA steps; 100-1000 is the existing DUT-validated working range, not a manufacturer-defined maximum claim.
- Battery low: 2500-3200 mV/cell, 100 mV steps.
- Power selection: 30, 45, 60, 65, 100 or 140 W. Intended input/output scope is user-validated; the supplied English manual labels 0x0C as output power. This is not a battery-side power clamp.

Configuration retains the existing charger-only application policy: UFP, discharge output disabled, source protocol flags retained, sink protocols enabled, LOADOTP=0, RESETMCU=0, INT_low=0, automatic recharge disabled. The standalone driver does not invent alternate port roles or protection behavior.

The 100 W application limit, SOC-based target selection, pack acceptance, temperature model/protection, periodic scheduling, startup handshake, graph and totals belong to the application. The NTC API returns voltage/current indications, not temperature; a thermistor model and the actual circuit are needed for that conversion. NTC enable/excitation writes remain externally handled.

## Arduino adapter

```cpp
#include <IP2366.h>
#include <IP2366Arduino.h>

ip2366::ArduinoTransport bus(17, 18, 6); // SDA, SCL, GPIO driving INT through 10 kohm
ip2366::IP2366 charger(bus);

void setup() {
    bus.begin(); // Open drain, pull-ups, wake HIGH and 110 ms wake wait
    if (!charger.begin()) {
        // Show/handle unavailable charger. No automatic enable.
        return;
    }
}

void loop() {
    // Service your own UI, start requests, status checks and fault policy.
}
```

Optional constructor argument 4 is the 7-bit address (default 0x75). Values above 0x7F are rejected without touching the bus; do not pass the 8-bit 0xEA/0xEB address bytes. A wake GPIO of -1 omits GPIO drive for externally managed wake. The adapter has been verified against Arduino-ESP32 2.0.17 and the existing board setup; portability of other cores/electrical interfaces is not implied.

The adapter is unchanged in protocol behavior: nominal maximum 100 kHz from 5 us low/high delays plus GPIO overhead; up to 2 ms per released clock for stretching; 50 us preparation after each address ACK; 1 ms after each single-byte register transfer; final-byte NACK; bounded nine-clock bus clear and STOP. SDA/SCL are open drain and never driven push-pull HIGH. Electrical INT compatibility and pull-up design remain the caller's hardware responsibility.

To supply another transport, implement `ip2366::Transport`: `probe`, `recover`, and successful single-byte `read`/`write`, returning false on errors. The driver reads each measurement pair low byte first, high byte second. It assumes no auto-increment burst protocol.

## Provenance and tests

Contracts are preserved from the supplied Injoinic V1.13 register document and the exact existing DUT profile/source; see `REGISTER_CONTRACT.md` for the standalone contract, primary pages and explicit user-validated exceptions. The extraction introduces no new register meanings. Library-owned tests build the core with a fake transport and no application/Arduino/LVGL headers. Existing controller, GPIO protocol and actual LVGL tests also exercise this library through the complete application.

Run the portable tests from the library folder using Windows PowerShell 5.1 and LLVM:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tests/Run-Tests.ps1
```

Or compile `src/IP2366.cpp` and `tests/test_ip2366.cpp` with a host C++ compiler, C++17 and `src/` on the include path. The test fixture uses the host standard library; the embedded production core is also compiled by the pinned ESP32 toolchain.


## Communication monitoring (1.2.0)

Every failed register read/write is followed immediately by Transport::probe() of the configured address (default Arduino address: 7-bit 0x75). If probing fails, the operation fails immediately with CommunicationFault::Disconnected. If the address responds, the identical register message is retried, with a maximum of six consecutive failed attempts. The sixth failure produces CommunicationFault::Unstable. Only a successful register transfer resets the streak; successful probes do not. This retry applies only to the driver's existing reads and idempotent configuration writes, never to fault-clear or reset commands. No readback mismatch is treated as a bus NACK. Failed reads do not publish an invalid output value.

communicationWarning() returns the application warning text, or nullptr. Communication faults latch until clearFailure()/begin(); a disconnected classification takes priority over instability during subsequent disable attempts. A successful retry does not set a terminal failure. Callers must stop an active session on a false return and must not automatically resume it. Initial absence in begin() remains a detection failure; the application may retry initialization periodically.


## Read-only boot snapshot (1.2.0)

readChargingSnapshot(ChargingSnapshot&) may be called before begin(). It never writes, enables, disables, resets or clears the chip. It uses SYS00 bit0 and unsigned current ADC >0 mA as the caller-requested activity gate, rechecking both after reading SYS02 target mV, SYS03 current mA, SYS04 masked cells and SYS08 termination mA. Termination uses bits7:4 times 50 mA, cells uses bits2:0 directly. Ranges use validateSettings(); only the four screen-controlled fields are captured, with other Settings members retaining their documented defaults. Outputs are not published on failed/invalid reads. Registers are independent observations, not an atomic hardware snapshot; the library does not infer current direction from its unsigned magnitude. Chemistry and SOC metadata do not exist in these registers and belong to the application. The caller must still invoke normal disable/initialization regardless of snapshot success. Firmware matching/persistence is deliberately outside this portable library.

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2366/boards/displayboard/programmablecharger/sourcecode/lib/ip2366control?572709101024260659) - created 2026-10-23 - last edited 2026-10-23
