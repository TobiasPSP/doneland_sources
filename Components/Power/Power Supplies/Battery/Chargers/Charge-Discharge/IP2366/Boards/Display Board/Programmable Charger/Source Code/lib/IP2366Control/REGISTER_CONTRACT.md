# Verified register boundary

This extraction preserves the IP2366_I2C V1.13 English register document supplied with BatCharger, plus explicit user/DUT validations. It is not a claim that other IC variants or board/firmware revisions have the same contract. The original document is `ip2366_i2c_regs_v1.13_en.pdf`; its history ends 26 June 2023. The implementation also retains bench-validated results from the exact tablet v25 `profiles/ip2366.yaml`, dated 9 October 2026. No new undocumented control fields are added.

| Boundary | Contract and evidence |
| --- | --- |
| I2C | 7-bit 0x75; 0xEA/0xEB include direction. 3.3 V; maximum 250 kHz; recommended 100-200 kHz. Pages 1-2 |
| Timing | Wake/INT high 100 ms before access; final read byte NACK; single-byte reads; 50 us preparation delay and recommended 1 ms between byte transactions. Pages 1-2 |
| Register updates | Read-modify-write controlled fields only; preserve all unrelated/reserved bits and read actual values. Page 1 |
| 0x00 | Mask 0xFD. LOADOTP bit7, RESETMCU bit6, INT_low bit5, sink DPDM/PD/SCP bits4/3/2, charger bit0. Default project policy 0x1C disabled / 0x1D enabled under that mask. Preserve bit1. Page 3 |
| 0x02 | Mask 0xFF, target_cell_mV=2500+10*code, maximum 4400. Page 3 |
| 0x03 | Mask 0xFF, charge_current_mA=100*code, maximum 9700, not below termination. Page 3 |
| 0x04 | Mask 0x07, shift0, cells=code. Codes2-6. User explicitly validated; absent from V1.13. Preserve bits7:3 |
| 0x06 | Mask 0xFF, precharge_current_mA=50*code. Page 3. Working 100-1000 mA range retained from exact DUT profile; maximum is an application/DUT policy, not specified as a maximum by V1.13 |
| 0x08 | Mask0xFC, termination bits7:4, 50 mA/code. Recharge bits3:2 set00 (no recharge). Preserve bits1:0. Pages 3-4 |
| 0x09 | Mask0x80, EN_Standby bit7=0 disables automatic standby. Preserve bits6:0. Bit6 is the separate immediate-standby command; it is not intentionally asserted. Page4. Enforced at initialization/configuration and by the slow audit |
| 0x0A | Mask0xE0, battery_low_cell_mV=2500+100*code. Preserve bits4:0. At 2700 mV/cell and below, document says software-only low-voltage protection. This setting also changes precharge/CC transition. Page 4 |
| 0x0B | Mask0xF0. Discharge enable bit7 kept0; source protocol flags bits6:4 kept1. Preserve bits3:0. Page 4 |
| 0x0C | Mask0xE0. Codes0-5:30/45/60/65/100/140 W. Preserve bits4:0. Page 4 labels output power; intended input/output scope explicitly validated by user/DUT |
| 0x22 | Mask0xC0, role00=UFP. Preserve bits5:0. Page 5 |
| 0x31 | Bit5 charging flag, bit4 completion, bit3 discharge, bits2:0 stage1/2/3 active,6 timeout. Read-only status in this library. Page 8 |
| 0x33 | Bit7 input present, bit6 input overvoltage. Input-voltage low-bit codebook disputed; library does not interpret it. Page 8 |
| 0x34 | Raw Type-C/PD connection status. No writes. Pages 8-9 |
| 0x38 | Output fault flags bits5/4 overcurrent/short. Write-one-to-clear prose conflicts with access column; library never writes/clears this register. Pages 9-10 |
| 0x50 then0x51 | Pack voltage, unsigned low/high value directly in mV. Page10 |
| 0x6E then0x6F | Battery current, unsigned low/high magnitude directly in mA. Page10 plus DUT charging/discharging measurements:0x07A3=1955 mA charge;0x07D1=2001 mA discharge. Never infer sign/direction from this magnitude |
| 0x77 | Bit7:0=20 uA,1=80 uA. Indication read before/after NTC voltage. No configuration write. Page11 |
| 0x78 then0x79 | NTC-node voltage directly in mV, nominal0-3300 mV. Page11. Thermistor curve/network and temperature conversion belong to caller |

Each low-byte read refreshes/latches its corresponding pair: low must precede high (page8). Independent pairs and status registers are not one atomic cross-register snapshot. A failed read means output is not valid; `readStatus` can retain partial status for diagnostics, so its false return must not be ignored.

The Arduino adapter retains the verified open-drain and timing implementation from Arduino-ESP32 2.0.17 plus BatCharger 1.0.3. Its default GPIO17/18/6 mapping is for that tablet setup; constructor parameters do not validate an arbitrary board's electrical design. INT is driven through the user-selected 10 kohm resistor, not directly tied to a rail. NTC protection, BMS, hardware power limits and physical measurement accuracy are outside this library's claims.


## Communication monitoring (1.1.0)

Every failed register read/write is followed immediately by Transport::probe() of the configured address (default Arduino address: 7-bit 0x75). If probing fails, the operation fails immediately with CommunicationFault::Disconnected. If the address responds, the identical register message is retried, with a maximum of six consecutive failed attempts. The sixth failure produces CommunicationFault::Unstable. Only a successful register transfer resets the streak; successful probes do not. This retry applies only to the driver's existing reads and idempotent configuration writes, never to fault-clear or reset commands. No readback mismatch is treated as a bus NACK. Failed reads do not publish an invalid output value.

communicationWarning() returns the application warning text, or nullptr. Communication faults latch until clearFailure()/begin(); a disconnected classification takes priority over instability during subsequent disable attempts. A successful retry does not set a terminal failure. Callers must stop an active session on a false return and must not automatically resume it. Initial absence in begin() remains a detection failure; the application may retry initialization periodically.


## Read-only boot snapshot (1.2.0)

readChargingSnapshot(ChargingSnapshot&) may be called before begin(). It never writes, enables, disables, resets or clears the chip. It uses SYS00 bit0 and unsigned current ADC >0 mA as the caller-requested activity gate, rechecking both after reading SYS02 target mV, SYS03 current mA, SYS04 masked cells and SYS08 termination mA. Termination uses bits7:4 times 50 mA, cells uses bits2:0 directly. Ranges use validateSettings(); only the four screen-controlled fields are captured, with other Settings members retaining their documented defaults. Outputs are not published on failed/invalid reads. Registers are independent observations, not an atomic hardware snapshot; the library does not infer current direction from its unsigned magnitude. Chemistry and SOC metadata do not exist in these registers and belong to the application. The caller must still invoke normal disable/initialization regardless of snapshot success. Firmware matching/persistence is deliberately outside this portable library.
