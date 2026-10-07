<img src="/assets/images/charging.png" width="100%" height="100%" />

# IP2366 I2C Register Map

> Compilation of I2C-related Information applicable to I2C-Versions of IP2366

This compilation is a best-effort and work in progress:

* Use entirely at own risk. There may - and will - be errors and inaccuracies and much of the information is infered, derived, tested, and interpreted.
* Add your own findings or corrections by leaving a comment below.

## Reading this map

- All register addresses are hexadecimal, byte-wide addresses unless shown as a low/high pair.
- `k` is the numeric register field; `S` is the physical/configured series-cell count. This avoids the manuals' ambiguous reuse of `N` for both.
- `R/W` means documented read/write. `R` means documented read-only. `W1C?` marks a text/table inconsistency concerning write-one-to-clear.
- Reset values below describe **fields**, not a byte to write blindly. Reserved bits must be preserved. Read actual power-up values; defaults can vary.
- `A/B` identifies documents agreeing on a field; `B only` means absent from A; `lead` means an implementation comment without a complete verified field definition.
- Unless a row explicitly lists reserved bits, all unlisted bits are reserved or undocumented. An unlisted address is not necessarily nonexistent.



### Communication requirements

| Item | Documented value or behavior | Implementation consequence |
| --- | --- | --- |
| 7-bit slave address | `0x75` | Use this with Arduino Wire and normal 7-bit APIs. |
| On-wire address bytes | Write `0xEA`, read `0xEB` | These include the R/W bit; do not pass `0xEA` as a 7-bit address. |
| Logic voltage | 3.3 V | A 5 V MCU requires level conversion. |
| Maximum clock | 250 kHz; suggested 100–200 kHz | Start at 100 kHz. |
| Data preparation | Manuals request ACK checking and about 50 µs after address; recommend single-byte reads and about 1 ms between bytes | Wire-buffer delays before `endTransmission()` do not necessarily introduce gaps on the physical bus. Verify timing if communication fails. |
| Last received byte | Host sends NACK, then STOP | Required to end a read correctly. |
| Wake timing | Wait about 100 ms after INT is high | V1.00/B describe INT-high wake; other descriptions emphasize charging/EN wake. Confirm variant behavior. |
| Sleep indication | Stop I²C access within 16 ms of INT going low | Do not continuously poll a sleeping chip. |
| Sleep prevention | Manuals describe high INT as preventing sleep | Legacy package text claiming ground prevents sleep conflicts with this. |
| Reset command | `0x00[6]=1`; V1.00 specifies a 2 s wait | Re-read configuration afterward; not proof BAT_NUM is resampled. |
| Writes | Read, mask, modify, write only documented fields | Do not probe unknown registers with arbitrary writes. |
| Paired measurement reads | Read low byte first, then high; low-byte read refreshes both | Separate sequenced reads; combine `low + (high << 8)`. |
| Multiple chips | Standard devices share `0x75`; custom addresses require vendor customization | Two chips need separate buses, a mux, or verified distinct addresses. Do not assume your dual-chip board exposes both on one addressable bus. |

## System and charging controls

| Address | Register / field | Bits | Access | Meaning / encoding | Field reset | Evidence |
| --- | --- | --- | --- | --- | --- | --- |
| `0x00` | SYS_CTL0 / En_LOADOTP | 7 | R/W | 1 reloads defaults on boot/wake; 0 retains settings through that mechanism. Manual discourages clearing without suitable reinitialization logic. | 1 | A/B |
| `0x00` | En_RESETMCU | 6 | R/W | Write 1 to reset registers to defaults; self-clears. Wait 2 s per A. | 0 | A/B |
| `0x00` | En_INT_low | 5 | R/W | 1 enables an approximately 2 ms low INT exception indication. | 0 | A/B |
| `0x00` | En_Vbus_SinkDPdM | 4 | R/W | Input DP/DM fast-charge negotiation enable. | 1 | A/B |
| `0x00` | En_Vbus_SinkPd | 3 | R/W | Input PD negotiation enable. | 1 | A/B |
| `0x00` | En_Vbus_SinkSCP | 2 | R/W | Input SCP negotiation enable. | 1 | A/B |
| `0x00` | Reserved | 1 | Preserve | No usable definition. | 0 | A/B |
| `0x00` | En_Charger | 0 | R/W | 1 enables charging; 0 disables charging. B's translated parenthesis is awkward; A clearly describes no charging when disabled. | 1 | A/B |
| `0x01` | SYS_CTL1 | Unknown | Unknown | D labels it series-cell count, battery type, current-setting mode. No bit allocation or coding established. | Unknown | D lead only |
| `0x02` | SYS_CTL2 / Vset | 7:0 | R/W | Per-cell target `2500 + 10k` mV; maximum 4400 mV, so documented useful codes 0–190. Pack target nominally `S × Vcell`. | Unspecified | A/B |
| `0x03` | SYS_CTL3 / Iset | 7:0 | R/W | BAT-side charging-current limit `100k` mA; documented maximum 9700 mA. Must not be below termination current. | `0x61` = 9700 mA | A/B |
| `0x04` | SYS_CTL4 / Bat_Num | 2:0 | R/W (inferred) | Series-cell count, inferred direct coding `k = S`, proposed range 2-6. A 4S battery returned byte `0x04`, supporting code 4 = 4 cells. Other codes and write behavior have not been validated. | Unknown | User bench observation, 2026-10-07; similar-chip inference |
| `0x04` | Reserved | 7:3 | -- | Preserve these bits; no meaning assigned. Reserved allocation is inferred, not manufacturer-confirmed for this variant. | Unknown | Similar-chip inference |
| `0x06` | SYS_CTL6 / Itk | 7:0 | R/W | Precharge/trickle current `50k` mA. No independent trickle threshold or timeout field exposed here in the inspected PDFs. | `0x04` = 200 mA | A/B |
| `0x08` | SYS_CTL8 / Istop | 7:4 | R/W | Termination current `50k` mA; field 0–15 gives 0–750 mA. **Zero is not documented as “disable termination.”** | 2 = 100 mA | A/B |
| `0x08` | Vrch | 3:2 | R/W | 0 no recharge; 1 target − `S×50 mV`; 2 target − `S×100 mV`; 3 target − `S×200 mV`. | 2 | A/B |
| `0x08` | Reserved | 1:0 | Preserve | No usable definition. | Unspecified | A/B |
| `0x09` | SYS_CTL9 / En_Standby | 7 | R/W | 1 permits standby; 0 disables it. | 1 | A/B |
| `0x09` | Standby | 6 | R/W | One-shot write 1 enters standby when not charging; requires bit 7 enabled. | 0 | A/B |
| `0x09` | En_BAT_Low | 5 | R/W | Enable fixed 5 V pack low-voltage shutdown; software protection only; also changes precharge-to-CC behavior. | 0 | A/B |
| `0x0A` | SYS_CTL10 / Set_BATlow | 7:5 | R/W | **A:** 0–4 = 2.8/2.9/3.0/3.1/3.2 V per cell; 5–7 unspecified. **B:** 0–7 = 2.5 through 3.2 V per cell in 0.1 V increments. Also affects precharge-to-CC threshold. B says ≤2.7 V has software-only low-voltage protection. | 2, meaning differs | Conflicting A/B |
| `0x0B` | SYS_CTL11 / En_Dc-Dc_Output | 7 | R/W | 1 enables discharge output; 0 disables it. | 1 | A/B |
| `0x0B` | En_Vbus_Src_DP_dM | 6 | R/W | Output DP/DM fast-charge enable. | 1 | A/B |
| `0x0B` | En_Vbus_SrcPd | 5 | R/W | Output PD enable. | 1 | A/B |
| `0x0B` | En_Vbus_SrcSCP | 4 | R/W | Output SCP enable. | 1 | A/B |
| `0x0C` | SYS_CTL12 / Vbus_Src_Power | 7:5 | R/W | Codes 0/1/2/3/4/5 = 30/45/60/65/100/140 W. Codes 6/7 undefined. A calls it input/output selection; B calls it output. A says writes interact with PDO settings: later writes override earlier ones. | 5 = 140 W | A/B, scope wording differs |
| `0x0D` | SELECT_PDO / Pdo_select | 2:0 | **Uncertain** | B describes selecting input fixed PDO: 0/1/2/3/4 = 5/9/12/15/20 V. Check availability in `0x35` first. Highest adapter profile is default; re-identify/reconfigure after the configuration becomes invalid. B labels field R despite selection text; C implements writes. | Unspecified | B only + C; access contradiction |
| `0x17` | NTC_CTL / NTC_EN | 7 | R/W (inferred) | 1 enables battery NTC temperature protection; 0 disables it. Similar-chip inference with user-reported passive validation; write behavior not experimentally established. | Unknown | User report, 2026-10-07 |
| `0x17` | Reserved | 6:0 | -- | Preserve; no assigned meaning. Allocation inferred from similar-chip documentation. | Unknown | Similar-chip inference |

Theoretical BAT CV windows, assuming the selected cell count is actually active and charger operation allows the requested voltage:

| Series count | Minimum target | Maximum target | Pack step |
| --- | --- | --- | --- |
| 2S | 5.00 V | 8.80 V | 20 mV |
| 3S | 7.50 V | 13.20 V | 30 mV |
| 4S | 10.00 V | 17.60 V | 40 mV |
| 5S | 12.50 V | 22.00 V | 50 mV |
| 6S | 15.00 V | 26.40 V | 60 mV |

These are register arithmetic, not verified continuous bench-supply operating ranges. They do not demonstrate startup into zero volts, absence of termination, accuracy, or stability.

## USB-C role and source PDO controls

| Address | Register / field | Bits | Access | Meaning / encoding | Field reset | Evidence |
| --- | --- | --- | --- | --- | --- | --- |
| `0x22` | TypeC_CTL8 / Vbus_Mode_Set | 7:6 | R/W | 0 UFP/sink; 1 DFP/source; 3 DRP; 2 undefined. | A: 3; B: 0 | A/B default conflict |
| `0x23` | TypeC_CTL9 / En_5VPdo_3A/2.4A | 7 | R/W | Default 5 V PDO current choice: 1 = 3 A; 0 = 2.4 A. Interaction with custom-current enable needs validation. | 1 | A/B |
| `0x23` | En_Pps2Pdo_Iset | 6 | R/W | Enable custom PPS2 current from `0x2A`. | 0 | A/B |
| `0x23` | En_Pps1Pdo_Iset | 5 | R/W | Enable custom PPS1 current from `0x29`. | 0 | A/B |
| `0x23` | En_20VPdo_Iset | 4 | R/W | Enable custom 20 V current from `0x28`. | 0 | A/B |
| `0x23` | En_15VPdo_Iset | 3 | R/W | Enable custom 15 V current from `0x27`. | 0 | A/B |
| `0x23` | En_12VPdo_Iset | 2 | R/W | Enable custom 12 V current from `0x26`. | 0 | A/B |
| `0x23` | En_9VPdo_Iset | 1 | R/W | Enable custom 9 V current from `0x25`. | 0 | A/B |
| `0x23` | En_5VPdo_Iset | 0 | R/W | Enable custom 5 V current from `0x24`. | 0 | A/B |
| `0x24` | TypeC_CTL10 / 5VPdo_Iset | 7:0 | R/W | Source 5 V advertised current `20k` mA, plus add bit from `0x2C[0]`. B states maximum 3 A. | `0x96` = 3 A | A/B |
| `0x25` | TypeC_CTL11 / 9VPdo_Iset | 7:0 | R/W | Source 9 V current `20k` mA, plus `0x2C[1]`. B maximum 3 A. | `0x96` | A/B |
| `0x26` | TypeC_CTL12 / 12VPdo_Iset | 7:0 | R/W | Source 12 V current `20k` mA, plus `0x2C[2]`. B maximum 3 A. | `0x96` | A/B |
| `0x27` | TypeC_CTL13 / 15VPdo_Iset | 7:0 | R/W | Source 15 V current `20k` mA, plus `0x2C[3]`. B maximum 3 A. | `0x96` | A/B |
| `0x28` | TypeC_CTL14 / 20VPdo_Iset | 7:0 | R/W | Source 20 V current `20k` mA, plus `0x2C[4]`. B maximum 5 A with cable recognition, otherwise 3 A. | `0xFA` = 5 A | A/B |
| `0x29` | TypeC_CTL23 / Pps1Pdo_Iset | 7:0 | R/W | PPS1 source advertised current `50k` mA. B discusses up to 5 A with cable recognition, otherwise 3 A, but its default prose contradicts field value. | `0x3C` = **3 A**, not 5 A | A/B |
| `0x2A` | TypeC_CTL24 / Pps2Pdo_Iset | 7:0 | R/W | PPS2 source current `50k` mA; same caveat as PPS1. | `0x3C` = **3 A** | A/B |
| `0x2B` | TypeC_CTL17 / En_Src_Pps2Pdo | 6 | R/W | Advertise PPS2 when 1. | 1 | A/B |
| `0x2B` | En_Src_Pps1Pdo | 5 | R/W | Advertise PPS1 when 1. | 1 | A/B |
| `0x2B` | En_Src_20VPdo | 4 | R/W | Advertise fixed 20 V when 1. | 1 | A/B |
| `0x2B` | En_Src_15VPdo | 3 | R/W | Advertise fixed 15 V when 1. | 1 | A/B |
| `0x2B` | En_Src_12VPdo | 2 | R/W | Advertise fixed 12 V when 1. | 1 | A/B |
| `0x2B` | En_Src_9VPdo | 1 | R/W | Advertise fixed 9 V when 1. Bits 7 and 0 are reserved. | 1 | A/B |
| `0x2C` | TypeC_CTL18 / EN_20VPDO_ADD | 4 | R/W | Add 10 mA to programmed 20 V PDO current. | 0 | A/B |
| `0x2C` | EN_15VPDO_ADD | 3 | R/W | Add 10 mA to 15 V PDO current. | 0 | A/B |
| `0x2C` | EN_12VPDO_ADD | 2 | R/W | Add 10 mA to 12 V PDO current. | 0 | A/B |
| `0x2C` | EN_9VPDO_ADD | 1 | R/W | Add 10 mA to 9 V PDO current. | 0 | A/B |
| `0x2C` | EN_5VPDO_ADD | 0 | R/W | Add 10 mA to 5 V PDO current. | 0 | A/B |

For custom current settings, the manual describes output overcurrent protection at about 1.1 times the configured PDO current for the listed higher-voltage/PPS fields. This is not equivalent to a tightly regulated lab CC setpoint. Changing source advertisements may also require renegotiation; no universal live-update sequence was established.

Neither inspected map exposes a 28 V source-PDO current/enable field, AVS voltage request, or PPS minimum/maximum-voltage field. The broader chip family supports EPR according to F, but that does not fill these register-map gaps.

## Status and partner capabilities

| Address | Register / field | Bits | Access | Meaning | Evidence |
| --- | --- | --- | --- | --- | --- |
| `0x31` | STATE_CTL0 / CHG_En | 5 | R | Charging-context flag; VbusOk counts. Does not prove nonzero BAT current. | A/B |
| `0x31` | CHG_End | 4 | R | 1 indicates full/charge complete. | A/B |
| `0x31` | Output_En | 3 | R | 1 discharge output open without reported abnormality. | A/B |
| `0x31` | Chg_state | 2:0 | R | 0 standby; 1 trickle; 2 CC; 3 CV; 4 waiting; 5 full; 6 timeout; 7 undefined. | A/B |
| `0x32` | STATE_CTL1 / Chg_State | 7:6 | R | 0 = 5 V input charging; 1 = high-voltage fast charging. Other codes unspecified. | A/B |
| `0x33` | STATE_CTL2 / Vbus_Ok | 7 | R | VBUS powered/present. | A/B |
| `0x33` | Vbus_Ov | 6 | R | VBUS input overvoltage flag. | A/B |
| `0x33` | Chg_Vbus | 2:0 | R | Input-voltage category; conflicting codebooks below. | A/B conflict |
| `0x34` | TypeC_STATE / Sink_Ok | 7 | R | Valid Type-C sink connection. | A/B |
| `0x34` | Src_Ok | 6 | R | Valid Type-C source connection. | A/B |
| `0x34` | Src_Pd_Ok | 5 | R | Source-side PD connection valid. | A/B |
| `0x34` | Sink_Pd_Ok | 4 | R | Sink-side PD connection valid. | A/B |
| `0x34` | Vbus_Sink_Qc_Ok | 3 | R | Input fast-charge flag; QC5V/PD5V excluded from fast-charge indication. | A/B |
| `0x34` | Vbus_Src_Qc_Ok | 2 | R | Output fast-charge flag; QC5V/PD5V excluded. | A/B |
| `0x35` | RECEIVED_PDO / PDO_20V | 4 | R | Received/available fixed 20 V PDO flag. No current value. | B only + C |
| `0x35` | PDO_15V | 3 | R | Fixed 15 V received/available. | B only + C |
| `0x35` | PDO_12V | 2 | R | Fixed 12 V received/available. | B only + C |
| `0x35` | PDO_9V | 1 | R | Fixed 9 V received/available. | B only + C |
| `0x35` | PDO_5V | 0 | R | Fixed 5 V received/available. Bits 7:5 reserved. | B only + C |
| `0x38` | STATE_CTL3 / Vsys_Oc | 5 | R / W1C? | Latched output overcurrent; prose says write 1 to clear despite R column. | A/B inconsistency |
| `0x38` | Vsys_Scdt | 4 | R / W1C? | Latched output short-circuit; same access inconsistency. | A/B |
| `0x3A` | IC_TEMP / Thermal_loop | 7 | R (inferred) | 1 indicates thermal loop active; 0 inactive. Not the external battery NTC temperature or its enable setting. | Similar-chip inference; user observed bit 7 = 0, 2026-10-07 |
| `0x3A` | IC_TEMP | 6:0 | R (inferred) | Inferred unsigned direct temperature in degrees Celsius: `temperature_degC = byte & 0x7F`. User observed `0x1E`, interpreted as 30 degrees Celsius. | User passive capture; plausible room/light-load result, not independent calibration |

`0x38` describes repeated fault detections within roughly 600 ms and approximately 1.5 s before sleep. B's fault-recovery prose refers to toggling `0x22[7]`, but its own map defines `0x22[7:6]` as the Type-C role. Treat that recovery instruction as suspect; do not implement it blindly.

### Conflicting `0x33[2:0]` codebooks

| Code | A: V1.00 | B: V1.13 English / C decoder |
| --- | --- | --- |
| 0 | Unspecified | Unspecified |
| 1 | 5 V | Unspecified |
| 2 | 7 V | 5 V |
| 3 | 9 V | 7 V |
| 4 | 12 V | 9 V |
| 5 | 15 V | 12 V |
| 6 | 20 V | 15 V |
| 7 | 28 V | 20 V |

Use measured `0x52/0x53` voltage and known adapter profiles to identify the codebook your chip uses. A higher document version number does not prove it matches your chip or that every entry is correct.

## Measurements and identification bytes

| Address(es) | Register(s) | Access | Format / units | Evidence / caveat |
| --- | --- | --- | --- | --- |
| `0x50`, `0x51` | BATVADC_DAT0/1 | R | Low then high; combined value in mV at VBAT. | A/B |
| `0x52`, `0x53` | VsysVADC_DAT0/1 | R | Low then high; combined value in mV at VSYS. | A/B; confirm actual board node and voltage drop to USB VBUS. |
| `0x69` | TIMENODE1 | R | First ASCII identification/time-node character. | B only + C |
| `0x6A` | TIMENODE2 | R | Second ASCII character. | B only + C |
| `0x6B` | TIMENODE3 | R | Third ASCII character. | B only + C |
| `0x6C` | TIMENODE4 | R | Fourth ASCII character. | B only + C |
| `0x6D` | TIMENODE5 | R | Fifth ASCII character. | B only + C; not established as a live clock or formal version ID. |
| `0x6E`, `0x6F` | IBATIADC_DAT0/1 | R | Low then high; combined BAT current in mA. | A/B; signedness/direction coding not specified. |
| `0x70`, `0x71` | ISYS_IADC_DAT0 / IVsys_IADC_DAT1 | R | Low then high; combined system-side current in mA. | A/B; inconsistent naming; signedness not specified. |
| `0x74`, `0x75` | Vsys_POW_DAT0/1 | R? | A gives combined power in 10 mW units. | B mistranslates battery level as power in the revision history. Chinese V1.14 confirms the removed feature is battery-level reading, not power telemetry. A gives 10 mW units; validate on the actual chip. |
| `0x77` | INTC_IADC_DAT0 / NTC_IADC_DAT | R | Bit 7: 0 = 20 µA excitation; 1 = 80 µA. Bits 6:0 reserved. | A/B; this is an excitation-current indication, not battery current. |
| `0x78`, `0x79` | VGPIO0_NTC_DAT0/1 | R | Low then high; GPIO0/NTC voltage in mV, nominal 0–3300 mV. | A/B; no additional 3300/65535 scaling is specified. |

Read pairs in separate explicit statements so language expression-evaluation order cannot reverse them. Decode direction from validated status until a signed current encoding is established. NTC voltage plus excitation current can yield resistance; converting that to temperature requires the actual thermistor curve and board network.

## Undocumented or questionable address leads

These rows are intentionally separated from the documented map. They are not permission to write these locations, and names alone do not determine whether they are configuration commands, raw GPIO ADC readings, or copied definitions for another chip.

| Address | Claimed name / purpose | What remains unknown | Source |
| --- | --- | --- | --- |
| `0x01` | SYS_CTL1: series count, battery type, current-setting mode | Bits, encoding, access, prerequisites, reset behavior, firmware applicability. Unused definition; matches an IP2368 heading. No verified cell-count field. | D |
| `0x04` | Earlier SYS_CTL4 battery-capacity lead | Superseded as the working interpretation by the inferred Bat_Num field above and the 4S/code-4 bench observation. C's capacity label remains an unverified conflicting lead; variant applicability is unresolved. | C; user observation 2026-10-07 |
| `0x54` | IVBUS_IADC: input charging current | Width, scale, access, relevance; absent from A/B. | D |
| `0x7A` | VGPIO1_ISET: current setting | May be configuration-pin ADC data rather than writable current command. GPIO1 is INT in standard IP2366 I²C pinout, raising concern. | D |
| `0x7C` | VGPIO2_VSET: cell-voltage setting | Access and scale unknown; may be GPIO voltage telemetry. | D |
| `0x7E` | VGPIO3_FCAP: battery capacity | Conflicts with usual IP2366 GPIO3/PSET function. | D |
| `0x80` | VGPIO4_BATNUM: cell-count setting | No bit definition; name is consistent with BAT_NUM pin but does not prove writable S. Do not infer codes 2–6. | D |

D also calls `0x35` MOS_STATE, conflicting with B/C's RECEIVED_PDO. Together with the GPIO labels, this reduces confidence in its unexercised header definitions. A candidate address is evidence worth investigating, not a verified extension of the manufacturer map.



## Revision history and incompatibilities

B lists: V1.00 2023-03-24; V1.10 2023-04-18 adds charge-PDO selection; V1.11 2023-04-24 removes battery-level reading as unsupported (the English translation incorrectly calls this power); V1.12 2023-06-13 changes standby/wake-related instructions; V1.13 2023-06-26 extends low-voltage selection down to 2.5 V. These dates are the document's own history, not independently verified firmware-release dates.

| Topic | Difference | Practical consequence |
| --- | --- | --- |
| Input fixed PDO | B adds `0x0D` and `0x35`. | Earlier statement that only automatic input selection is possible was incomplete. |
| Low-voltage selection | A starts at 2.8 V/cell; B at 2.5 V/cell. | Same bits can imply a 0.3 V/cell difference. |
| Voltage status | A includes 28 V; B shifted codes omit it. | A decoder copied from C can misreport an A-style chip. |
| Role reset | A DRP; B UFP. | Read your actual initial state. |
| Power telemetry | B mistranslates the deleted battery-level feature as power. Chinese V1.14 resolves the wording. | Power telemetry is not shown to be unsupported by that revision entry. |
| PPS current default | `0x3C × 50 mA = 3 A`, B prose says 5 A. | Trust arithmetic, then actual advertisements; do not repeat prose as a measured default. |
| SELECT_PDO access | B calls it selection but marks field R. | C's implementation supports the intended interpretation, but hardware confirmation is still required. |
| Fault clear | Both text and access column disagree. | Verify W1C behavior before designing recovery. |

F lists B, C, and D silicon/firmware families. ENP and STB variants differ in wake behavior and standby consumption; C variants require charging activation, and F recommends migration to D. It explicitly requires matching chip and firmware versions. Package markings such as your “993 00DY” and “323 00DY” were not reliably decoded by the sources inspected, so neither marking proves this map's applicability.

The repository also contains IP2368 V1.61/V1.63 documents. **They are not IP2366 register revisions.** Similar names do not justify importing IP2368-only controls into this map.


## Focused follow-up: register 0x01 (2026-10-05)

The initial 0x01 lead does not survive source inspection as evidence of a working IP2366 cell-count command. The Byoreh_94 STM32 header defines the address, but the posted implementation has no read/write call using that definition. Its initialization only configures GPIOs; its data-reading state machine polls status and ADC values. A generic WriteOneByte helper is present, but no concrete 0x01 invocation is shown.

The wording “series number setting, battery type, current setting mode” matches the IP2368 SYS_CTL1 heading. That IP2368 document nevertheless lists upper bits as reserved and only four chemistry/mode fields. Copying that heading is a plausible explanation for the IP2366 header comment; its provenance is not proved.

### Most complete bit definition found: IP2368 only

This is a comparison, **not an IP2366 map**.

| Bits | Name | Mask | IP2368 meaning | Reset |
| --- | --- | --- | --- | --- |
| 7:4 | Reserved | 0xF0 | Preserve; no exposed cell-count encoding | Unspecified |
| 3 | En_BATmode_set | 0x08 | Enable register-defined battery chemistry | 0 |
| 2 | Set_BATmode | 0x04 | 0 LiFePO4, 1 ordinary Li-ion; changes chemistry-dependent voltage behavior | 1 |
| 1 | En_Isetmode_set | 0x02 | Enable selection of current-versus-power interpretation | 0 |
| 0 | Set_Isetmode | 0x01 | 0 BAT charging current, 1 input charging power; affects 0x03[6:0] | 1 |

## GitHub projects and implementation resources

| Resource | What is present | Assessment |
| --- | --- | --- |
| [D-314/IP2368-Arduino-Library](https://github.com/D-314/IP2368-Arduino-Library) | MIT Arduino library, IP2366/IP2368 classes, raw register access, read examples, error-handling examples, extended-read examples, PDFs and editable translated documents. | The strongest inspected public firmware resource. README says write functions are not fully tested. |
| [Legacy D-314/IP2366-Arduino-Library](https://github.com/D-314/IP2366-Arduino-Library) | Referenced by the deprecated PlatformIO package. | Historical lead; use the combined repository as the inspected implementation. Do not count this as an independent corroboration. |
| [Release history](https://github.com/D-314/IP2368-Arduino-Library/releases) | IP2366 support added in 1.2.0; later releases mention power-reading and other fixes. | Useful history, not proof all remaining accessors are correct. |
| [Issue #3: inactive I²C on some boards](https://github.com/D-314/IP2368-Arduino-Library/issues/3) | Variant-dependent I²C discussion. | Chip identity/firmware matters; replacing LED wiring cannot establish that every chip supports I²C. |
| [Issue #4: IP2366 support](https://github.com/D-314/IP2368-Arduino-Library/issues/4) | IP2366 integration and board discussion. | Relevant connection reference; map the actual PCB rather than copying resistor numbers blindly. |
| [IP2366 examples](https://github.com/D-314/IP2368-Arduino-Library/tree/main/examples/IP2366) | SimpleDataRead, ErrorHandling, ExtendendDataRead. | Starting points for read-only exploration. |
| [PlatformIO legacy package](https://registry.platformio.org/libraries/d-314/IP2366) | Deprecated IP2366 package description. | Contains an INT-to-ground sleep claim conflicting with manufacturer text. Follow measured board behavior and the primary manual. |


## Source index

Links below are ordinary public URLs. “Inspected” means the document or code was actually retrieved and read; “lead” means availability or attached content was not verified.

| ID | Source | Status and value |
| --- | --- | --- |
| A | [Injoinic IP2366 register document V1.00, 18 pages](https://cdn.answeroverflow.com/1392432699419136040/IP2366_I2Cwith_reg_V1.00.pdf) | Inspected PDF. Revision dated 2023-03-24. Primary manufacturer text hosted by a third party. Baseline map. |
| B | [IP2366 I2C regs V1.13 EN.pdf](https://github.com/D-314/IP2368-Arduino-Library/blob/main/assets/pdf/IP2366/IP2366%20I2C%20regs%20V1.13%20EN.pdf) | Inspected from a local clone; 12 pages. English document distributed by the library author; manufacturer headings, but translation provenance and correspondence to any specific chip firmware are unverified. Revision history ends 2023-06-26. |
| B2 | [Editable V1.13 English DOCX](https://github.com/D-314/IP2368-Arduino-Library/blob/main/assets/pdf/IP2366/IP2366%20I2C%20regs%20V1.13%20EN.docx) | Exists in inspected repository; PDF was used for this map. |
| C | [D-314 IP236x Arduino repository](https://github.com/D-314/IP2368-Arduino-Library) | Inspected code, examples, and bundled PDFs. Repository name remains IP2368, but supports both chips. |
| C1 | [IP2366.cpp](https://github.com/D-314/IP2368-Arduino-Library/blob/main/src/IP2366.cpp) | IP2366-specific accessors and register constants. |
| C2 | [IP236x.cpp](https://github.com/D-314/IP2368-Arduino-Library/blob/main/src/IP236x.cpp) | Shared accessors, status decoding, ADC reads. |
| D | [Byoreh_94: STM32 IP2366 driver and data reading](https://damodev.csdn.net/68819742bb9d8e0ecec2d8bb.html) | Inspected author-posted C/header code, dated 2025-07-04. Supplies `0x01` and additional register-name leads; contains conflicts with PDFs. |
| E | [ql君/qlexcel: IP2366 explanation and practical experiments](https://damodev.csdn.net/6a4330f710ee7a33f2844693.html) | Inspected author's account, including BAT-side electronic-load startup experiment and communication notes. |
| F | [ChipSourceTek variant/version selection document](https://www.chipsourcetek.com/DataSheet/IP2366%20.pdf) | Inspected 4-page distributor document, dated 2024-01-25. Distinguishes B/C/D and ENP/STB variants. |
| G | [LCSC IP2366 I²C datasheet](https://datasheet.lcsc.com/lcsc/2401051807_INJOINIC-IP2366--I2C-version_C20415848.pdf) | General datasheet lead; includes pin and resistor configuration. Not an additional verified register map. |
| H | [IP2366_DEMO_V1.41 schematic](https://www.chipsourcetek.com/DataSheet/IP2366_DEMO_V1.41.pdf) | Indexed manufacturer schematic lead, useful for BAT_NUM and I²C pin routing. V1.41 is a schematic revision, not a register-map revision. |
| I | [Verified IP2366 EVM by yizhidianzi](https://oshwhub.com/yizhidianzi/ip2366-evm) | Indexed project description advertises exposed test points and an attached I²C manual; direct retrieval returned 403, attachments not inspected. |
| J | [原同学: bidirectional converter main power board](https://www.jlc-ycs.com/platform/detail/e29dd1986a0e45f897bc49dd04be9bae?type=1) | Inspected author project page, dated 2023-09-22. IP2366 I²C, GD32E230 firmware, display daughterboard, and listed firmware archive; archive not downloaded. |
| K | [ZHAO-POWER-H1 project](https://diy.szlcsc.com/p/sgxn/zhao-power-h1) | Indexed author project description: two IP2366 I²C devices, STM32 controller, additional ports. Software section explicitly says implementation was unfinished. |
| L | [ChipSourceTek original register-PDF endpoint](https://www.chipsourcetek.com/DataSheet/IP2366_I2C.pdf) | Direct web retrieval returned 403. Do not assume identical contents to A or B. |

The inspected GitHub snapshot is commit `9a23b86ec0f2544c56b25e16900b5257347a150a`. For reproducibility, replace `main` in GitHub links with this commit. No exhaustive claim is made about private customer manuals, QQ group files, unindexed repositories, or chip-specific customized firmware.

## Passive decoding clarifications (2026-10-07)

The following additions distinguish a register-map interpretation from a verified
physical measurement. They were recorded while deriving a YAML profile and a
PC-side interpreter for passive I2C recordings. They do not authorize active
queries, configuration writes, or protection/control decisions.

### Assembling measurements from separate transactions

A normal I2C transaction does not identify the physical width or meaning of a
register. The low/high grouping, byte order and scale come from this map, not
from the signal itself. For the documented pairs, source A page 11 requires low
before high because reading low refreshes both bytes. A pointer-selection write
followed by a repeated START and a read is part of a register read; it is not a
write of the returned measurement.

For a conservative passive decoder, combine only successful single-byte reads
of the specified low and high registers, in that order, with no intervening
transaction to the same device. Invalidate a pending pair after a failed transfer,
capture/output loss, capture pause/reset, reconnect, or an unexpected target
transaction. This adjacency rule is a decoder policy, **not an additional chip
timing requirement**. Other-device traffic does not by itself invalidate the
documented latch, but any reported capture loss does.

Without capture timestamps, ordered USB lines cannot establish a precise
acquisition-time interval. Host arrival times are not bus timestamps. Separate
reads are the baseline here; do not assume that a multi-byte read automatically
increments the register pointer merely because I2C permits multiple data bytes.
An explicit device-specific burst contract is needed before interpreting one.

### Remaining interpretation boundaries

| Topic | Decoder treatment | Evidence or validation needed |
| --- | --- | --- |
| `0x6E/0x6F`, `0x70/0x71` current signedness | Assemble the bit pattern as an explicitly labelled **unsigned code** in the documented mA/code scale. Do not infer positive/negative physical current or charge/discharge direction. | A pages 15-16 specifies mA but no signed representation; reference already flags this gap. Validate against independent current measurements in both directions. |
| Example `0x6E=0xFD`, `0x6F=0x07` | `0x07FD = 2045`, hence unsigned-code interpretation 2045 mA. | Arithmetic cross-check, not proof of signedness, accuracy, or current direction. |
| `0x0A[7:5]`, `0x33[2:0]` | Show the field code and preserve both A/B alternatives; do not silently choose the higher document version. | Identify actual chip behavior using independent voltage observations; document which codebook was validated. |
| `0x24` through `0x28` PDO currents | Label `20k` mA as the **base programmed current**, excluding the separate 10 mA add bit in `0x2C`. | A pages 8-11 confirms the two components. Effective advertisement also depends on enables, limits and negotiation; arbitrary cached reads are not an atomic snapshot. |
| `0x29/0x2A` PPS currents | Show programmed `50k` mA, not negotiated or measured current. `0x3C` is 3000 mA. | Enable state, cable capability and actual advertisements remain relevant. |
| `0x74/0x75` power | Convert once to mW using 10 mW/code; retain the chip-validation caveat. | A page 16 confirms scaling. Independent voltage/current measurements can cross-check applicability. |
| `0x77` NTC current | Decode only bit 7: 20 or 80 microamperes of excitation. | A page 16; no battery-current or temperature interpretation. |
| `0x78/0x79` NTC voltage | Decode mV directly; do not apply an extra full-scale ADC factor. | A pages 16-17. Thermistor curve and actual board network are still needed for temperature. |
| Undefined enumeration codes or values beyond documented ranges | Retain the code and report `UNDEFINED_CODE` or `OUT_OF_RANGE`; never clamp to a plausible value. | Such output means interpretation is incomplete or outside the stated range, not necessarily a capture failure. |
| Observed configuration writes | Report the transmitted field values separately from successful readback. | Bus ACK does not establish that a setting was applied, remained active, or is safe. Access contradictions at `0x0D` and `0x38` remain unresolved. |

### Newly recorded primary-source lead: 0x56/0x57

Source A page 14 contains an isolated sentence that discharge current is stored
in `0x56` and `0x57`, referring to `0x31[3]` as a discharge indicator. However,
the inspected map provides no corresponding complete register entries establishing
width, scale, signedness, latch behavior, or applicability. This conflicts with
the temptation to treat the sentence as a complete alternative current accessor.
It is an **unresolved lead only**: no physical-value decoder for these addresses
is enabled. Confirm against a matching manufacturer revision and bench readings
before adding an interpretation.

### Bench-supported inference: 0x04 series-cell count

On 2026-10-07, passive capture of the user's IP2366 operating with a known 4S
battery returned `0x04` from register `0x04`. Together with similar-chip register
documentation (specific document/revision not supplied), this supports the working
interpretation `Bat_Num = register & 0x07`, in units of series-connected cells.
The proposed valid range is 2-6; codes 0, 1 and 7 are outside that inferred range,
but their actual hardware meaning has not been established.

Only code 4 on the tested 4S setup has been observed as matching the cell count.
That single observation does not independently verify the full bit allocation,
direct encoding for other counts, R/W access, power-up behavior, interaction with
the BAT_NUM resistor, or applicability to other variants. Bits 7:3 are treated as
reserved and must be preserved. The passive YAML decoder labels this interpretation
as inferred; it does not authorize writes or protection/control decisions.

### Bench-supported inferences: 0x17 and 0x3A

The user supplied the following working definitions on 2026-10-07, based on
similar-chip documentation and passive sniffing. No matching primary IP2366
register document or specific similar-chip revision was supplied.

- `0x17[7]` is `NTC_EN`: 1 means battery NTC temperature protection enabled,
  0 disabled. Access is reported as R/W, inferred rather than tested by writes.
  Bits 6:0 are treated as reserved and preserved. `0x80` and `0x00` are examples
  with zero lower bits, not the only possible enable/disable byte values.
- `0x3A[6:0]` is an inferred unsigned, direct internal die temperature in degrees
  Celsius, with `0x3A[7]` indicating thermal-loop activity. A captured byte `0x1E`
  gives code 30 and an inactive-loop bit. The 30 degrees Celsius interpretation
  is plausible near room temperature/light load, but was not independently
  calibrated. No positive-loop-bit observation, accuracy, negative-temperature
  encoding, thermal threshold or wider-range validation was supplied. Codes
  0-127 are the representable field range, not a verified operating/accuracy range.

These are separate properties: the internal die reading and thermal loop must
not be presented as the battery thermistor temperature or proof that battery NTC
protection works. Passive decoders retain an INFERRED caveat. They authorize
neither active writes nor control/protection decisions.

### Change record

- 2026-10-07: added passive assembly policy and clarified that host arrival timing
  is not acquisition timing; no new chip timing requirement was inferred.
- 2026-10-07: cross-checked A's low/high latch rule, measurement units, NTC
  excitation and PDO add bits. Existing A/B conflicts were retained, not resolved.
- 2026-10-07: recorded the previously unlisted `0x56/0x57` sentence as an
  incomplete primary-source lead, not a verified register-map extension.
- 2026-10-07: added inferred `0x04[2:0]` Bat_Num decoding with a 4S/code-4
  bench observation; retained the earlier capacity label as a conflicting lead.
- 2026-10-07: added inferred `0x17[7]` NTC protection enable and read-only
  `0x3A` die-temperature/thermal-loop fields; recorded the `0x1E` observation
  without claiming independent temperature calibration or active-bit validation.
- Current direction/signedness, variant codebooks, unknown-register leads, burst
  semantics and write-access contradictions remain open for validation.

> Tags: IP2366, I2C

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2366/i2creference?999094101306262639) - created 2026-10-05 - last edited 2026-10-06
