<img src="/assets/images/charging.png" width="100%" height="100%" />

# IP2366 I2C Register Map

> Compilation of I2C-related Information applicable to I2C-Versions of IP2366

This reference consolidates the supplied Chinese V1.00, English V1.13, Chinese
V1.14 and Chinese V1.16 register manuals. It is a best-effort and work in progress, not a replacement
for matching the document to the actual IP2366_I2C chip/firmware variant:

* Use entirely at own risk. Documented fields, translation disagreements and experimental interpretations are distinguished below. A successful read or bus ACK does not establish safe write behavior.
* Add your own findings or corrections by leaving a comment below.

### Primary documents used in this revision

Page numbers below are PDF page numbers, starting at 1. They are not firmware
version numbers. The earlier three-document review checked the connection
diagram, transaction diagrams and disputed PDO tables visually. This revision
adds the complete V1.16 register text and checks its newly defined fields against
the existing reference. V1.16 prints an obsolete total of 18 pages in its footer,
but the supplied PDF actually has 22 pages; use the PDF page numbers below.

| ID | Supplied file | Document version/date | Pages | Role in this reference |
| --- | --- | --- | --- | --- |
| A | `ip2366_i2c_with_reg_v1.00.pdf` | Chinese V1.00, 2023-03-24 | 18 | Original baseline; older low-voltage codebook and a discharge-current lead. |
| B | `ip2366_i2c_regs_v1.13_en.pdf` | English V1.13, history ends 2023-06-26 | 12 | Useful English copy; contains discrepancies, missing wording and internal contradictions. |
| N | `ip2366_i2c.pdf` | **Chinese V1.14, 2023-10-27** | 18 | Earlier Chinese revision, despite the unversioned filename. Adds the 100 mA minimum trickle setting. |
| O | `ip2366_i2c_regs_v1.16_cn.pdf` | **Chinese V1.16, 2025-04-28** | 22 | Latest supplied register manual. Documents cell count, completion/timeout policy, independent input power, thermal controls, NTC enable and IC revision/temperature. |

Use [Ambiguities and DUT validation](#ambiguities-and-dut-validation) before choosing
a revision-sensitive decoder or writing a setting. Other source IDs refer to the
historical implementation resources in the source index; they were not re-audited
as part of the original three-document comparison. Source O is the primary
reference for the additional fields in this revision. The supplied PY32 display
firmware was also inspected as implementation evidence, not as a replacement for
the manufacturer contract or proof that it matches the installed factory binary.

## Reading this map

- All register addresses are hexadecimal, byte-wide addresses unless shown as a low/high pair.
- `k` is the numeric register field; `S` is the physical/configured series-cell count. This avoids the manuals' ambiguous reuse of `N` for both.
- `R/W` means documented read/write. `R` means documented read-only. `W1C?` marks a text/table inconsistency concerning write-one-to-clear.
- Reset values below describe **fields**, not a byte to write blindly. Reserved bits must be preserved. Read actual power-up values; defaults can vary.
- `A/B` identifies the original baseline comparison; N also agrees unless a difference is called out. `B/N` identifies additions absent from A. `O` identifies the supplied V1.16 manufacturer document; old evidence labels are retained unless explicitly extended. `lead` means an incomplete or unverified definition, not an implemented register contract.
- Boolean flags are shown as 0/1 with their specific meaning. A single-bit selector such as 20/80 microamperes or 2.4/3 A is a value selection, not a generic true/false flag.
- Extract a field with `k = (byte & mask) >> shift`. Convert once into the stated unit. A representable code range is not necessarily a supported configuration range or a measurement-accuracy guarantee.
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
| Wake timing | Wait until INT has been continuously high for 100 ms | A/B describe waking on high INT; N describes charging or EN as wake sources. Holding INT high to prevent sleep is a separate behavior. Confirm the chip variant. |
| Sleep indication | Stop I²C access within 16 ms of INT going low | Do not continuously poll a sleeping chip. |
| Sleep prevention | Manuals describe high INT as preventing sleep | Legacy package text claiming ground prevents sleep conflicts with this. |
| Reset command | `0x00[6]=1`; A, N and O specify a 2 s wait | B omits the wait. Re-read configuration afterward; not proof BAT_NUM is resampled. |
| Writes | Read, mask, modify, write only documented fields | Do not probe unknown registers with arbitrary writes. |
| Paired measurement reads | Read low byte first, then high; low-byte read refreshes both | Separate sequenced reads; combine `low + (high << 8)`. |
| Multiple chips | Standard devices share `0x75`; custom addresses require vendor customization | Two chips need separate buses, a mux, or verified distinct addresses. Do not assume your dual-chip board exposes both on one addressable bus. |

### Pins and connection diagram

A p.2 and N p.2 show the following IP2366_I2C package-pin assignments. These are
**IC pin numbers**, not header numbers on a charger module. Map the actual PCB
before connecting; do not confuse high-current power pins with logic signals.

| IC pin | Manual label | Connection shown |
| --- | --- | --- |
| 39 | LED1/IIC_SCL | SCL, with 2.2 kohm to VCCIO. |
| 38 | LED2/IIC_SDA | SDA, with 2.2 kohm to VCCIO. |
| 31 | LED3/IIC_INT | INT to the MCU, with 510 kohm to ground. |

The text specifies a 3.3 V communication level. The drawing labels the pull-up
rail VCCIO; it is not permission to connect the bus to battery voltage, VBUS or
5 V. The 2.2 kohm values are the application example, not a universal requirement
for every bus. A passive sniffer normally uses the DUT's existing pull-ups and
does not drive SDA/SCL. INT is driven by the chip after wake and becomes an input
before sleep; its complete output-drive specification is not supplied here, so
do not prescribe an MCU push-pull-high connection solely from the wake text.

### Single-register transfers

The diagrams in A p.3, B p.2 and N p.3 use this sequence. `ACK` is driven by the
receiver; the host deliberately NACKs the final read byte. Bytes below are
**on-wire** values, not API addresses:

```text
Read register r:
START -> EA -> ACK -> r -> ACK -> repeated START -> EB -> ACK -> data -> host NACK -> STOP

Write register r:
START -> EA -> ACK -> r -> ACK -> data -> ACK -> STOP
```

The waveform annotations show 50 microsecond preparation pauses after the write
address ACK, after the register-selector ACK, and after the read-address ACK.
The write diagram also shows a pause after the selector ACK. Implement these as
physical bus gaps; sleeping while filling a software transmit buffer does not
necessarily delay anything on the bus. The prose additionally recommends
single-byte reads at 100 kHz and 1 ms between bytes; the exact applicability of
that recommendation to separate complete transactions versus a burst is not
fully specified. No guaranteed automatic register-increment/burst contract is
given. A slow clock by itself is not proof that the illustrated inter-byte gaps
are present.

The example writing `0x5A` to `0x05` demonstrates the frame format only. **None of
the four supplied register lists defines `0x05`; do not reproduce that write on a DUT.**
The demonstrated real read from `0x31` returns `0x22` in the example capture;
this is an example observation, not its reset value.

For ordinary documented R/W fields, preserve unrelated bits with
`new_byte = (old_byte & ~mask) | ((k << shift) & mask)`, checking that `k` fits the
supported codebook. This is **not** a generic recipe for W1C, reset or one-shot
command bits: copying a latched 1 back into a W1C field can clear another event.
Stop on an address/data NACK; do not interpret missing data as a zero value.

## System and charging controls

| Address | Register / field | Bits | Access | Meaning / encoding | Field reset | Evidence |
| --- | --- | --- | --- | --- | --- | --- |
| `0x00` | SYS_CTL0 / En_LOADOTP | 7 | R/W | 1 reloads defaults on boot/wake; 0 retains settings through that mechanism. Manual discourages clearing without suitable reinitialization logic. | 1 | A/B |
| `0x00` | En_RESETMCU | 6 | R/W | Write 1 to reset registers to defaults; self-clears. Wait 2 s per A/N; B omits this delay. | 0 | A/B/N |
| `0x00` | En_INT_low | 5 | R/W | 1 enables an approximately 2 ms low INT exception indication. | 0 | A/B |
| `0x00` | En_Vbus_SinkDPdM | 4 | R/W | Input DP/DM fast-charge negotiation enable. | 1 | A/B |
| `0x00` | En_Vbus_SinkPd | 3 | R/W | Input PD negotiation enable. | 1 | A/B |
| `0x00` | En_Vbus_SinkSCP | 2 | R/W | Input SCP negotiation enable. | 1 | A/B |
| `0x00` | Reserved | 1 | Preserve | No usable definition. | 0 | A/B |
| `0x00` | En_Charger | 0 | R/W | 1 enables charging; 0 disables charging. B's translated parenthesis is awkward; A clearly describes no charging when disabled. | 1 | A/B |
| `0x01` | SYS_CTL1 | Unknown | Unknown | D labels it series-cell count, battery type, current-setting mode. No bit allocation or coding established. | Unknown | D lead only |
| `0x02` | SYS_CTL2 / Vset | 7:0 | R/W | Per-cell target `2500 + 10k` mV; maximum 4400 mV, so documented useful codes 0–190. Pack target nominally `S × Vcell`. | Unspecified | A/B |
| `0x03` | SYS_CTL3 / Iset | 7:0 | R/W | BAT-side charging-current limit `100k` mA; documented maximum 9700 mA. Must not be below termination current. | `0x61` = 9700 mA | A/B |
| `0x04` | SYS_CTL4 / Bat_Num | 2:0 | R/W | Series-cell count `S = k`, supported range 2-6. Codes 0, 1 and 7 have no documented supported meaning. Earlier DUT inference is now manufacturer-documented; hardware BAT_NUM interaction and variant applicability still require checking. | Unspecified | O p.5; DUT 2026-10-09 |
| `0x04` | Reserved | 7:3 | Preserve | Reserved in V1.16; retain their actual values. | Unspecified | O p.5 |
| `0x06` | SYS_CTL6 / Itk | 7:0 | R/W | Precharge/trickle current `50k` mA. Working IP2366 range **100-1000 mA**, codes `0x02-0x14`. Minimum documented by N; maximum adopted from DUT settings. No independent trickle threshold or timeout field exposed. | `0x04` = 200 mA | A/B/N; DUT 2026-10-09 |
| `0x08` | SYS_CTL8 / Istop | 7:4 | R/W | Termination current `50k` mA; field 0–15 gives 0–750 mA. **Zero is not documented as “disable termination.”** | 2 = 100 mA | A/B |
| `0x08` | Vrch | 3:2 | R/W | 0 no recharge; 1 target − `S×50 mV`; 2 target − `S×100 mV`; 3 target − `S×200 mV`. | 2 | A/B |
| `0x08` | Chg_OvTime | 1 | R/W | 0: automatically clear charging enable after full and retain the chip charging-timeout function. 1: do not automatically clear enable after full and remove the chip charging-timeout function. This does not define a programmable timeout duration or guarantee continuous output regulation. | 0 | O p.5 |
| `0x08` | Reserved | 0 | Preserve | No usable definition. | Unspecified | O p.5 |
| `0x09` | SYS_CTL9 / En_Standby | 7 | R/W | 1 permits standby; 0 disables it. | 1 | A/B |
| `0x09` | Standby | 6 | R/W | One-shot write 1 enters standby when not charging; requires bit 7 enabled. | 0 | A/B |
| `0x09` | En_BAT_Low | 5 | R/W | Enable fixed 5 V pack low-voltage shutdown; software protection only; also changes precharge-to-CC behavior. | 0 | A/B; O p.6 |
| `0x09` | Standby_Mode | 3 | R/W | D-revision IC only: 0 selects 10 microampere standby, 1 selects 100 microampere standby. O says a D IC entering standby with a load uses only the 100 microampere mode. These are stated modes, not a whole-board consumption guarantee. | ENP: 0; STB: 1 | O p.6 |
| `0x0A` | SYS_CTL10 / Set_BATlow | 7:5 | R/W | **A:** 0-4 = 2.8/2.9/3.0/3.1/3.2 V per cell; 5-7 unspecified. **B/N/O:** base threshold `2500 + 100k` mV per cell, codes 0-7. Also affects precharge-to-CC threshold. B/N/O say at or below 2.7 V software-only low-voltage protection. Apply O adjustment fields below when interpreting the complete threshold. | A/B/N: 2, meaning differs; O leaves unspecified and history says V1.15 changed the default | A p.6; B p.4; N p.6; O p.6 |
| `0x0A` | Adjust_En | 4 | R/W | 0 subtracts the supplementary low-voltage adjustment; 1 adds it. This is a sign selector, despite the name ending in En. | 0 | O p.6 |
| `0x0A` | Adjust_Data | 2:0 | R/W | Supplementary adjustment, documented as `100k` mV and applied per series cell in the pack-threshold formula. Interpret jointly with bits 7:5, bit 4 and `0x09[5]`; do not infer that every mathematical combination is supported. Bit 3 is reserved. | 0 | O p.6 |
| `0x0B` | SYS_CTL11 / En_Dc-Dc_Output | 7 | R/W | 1 enables discharge output; 0 disables it. | 1 | A/B |
| `0x0B` | En_Vbus_Src_DP_dM | 6 | R/W | Output DP/DM fast-charge enable. | 1 | A/B |
| `0x0B` | En_Vbus_SrcPd | 5 | R/W | Output PD enable. | 1 | A/B |
| `0x0B` | En_Vbus_SrcSCP | 4 | R/W | Output SCP enable. | 1 | A/B |
| `0x0B` | EN_DRV_EMI | 3 | R/W | Chip drive anti-EMI function: 1 enabled, 0 disabled. The manual gives no timing, efficiency or EMC-performance guarantee for this setting. | 0 | O p.7 |
| `0x0C` | SYS_CTL12 / Vbus_Src_Power | 7:5 | R/W | Codes 0/1/2/3/4/5 = 30/45/60/65/100/140 W; 6/7 undefined. O explicitly calls this input/output power selection. O also adds separate input-power control below. A says later `0x0C` versus `0x23-0x28` writes override earlier ones; N/O omit this precedence sentence, not proof of changed behavior. | 5 = 140 W | A p.6-7; B p.4; N p.6-7; O p.8 |
| `0x0C` | Chg_Power_En | 3 | R/W | 1 enables separate maximum input-power selection using bits 2:0. 0 leaves input power under the shared setting in bits 7:5. Read this bit before interpreting the upper field as the effective input limit. Bit 4 is reserved. | 0 | O p.8 |
| `0x0C` | Vbus_Snk_Power | 2:0 | R/W | Separate input-power codes 0/1/2/3/4/5 = 30/45/60/65/100/140 W; meaningful when bit 3 is enabled. Codes 6/7 undefined. Power settings are ceilings, not promised delivered or battery-side power. | 5 = 140 W | O p.8 |
| `0x0D` | SELECT_PDO / Pdo_select | 2:0 | R/W in O; R in B/N | O: 0 automatic highest adapter offer; 1/2/3/4/5 request 5/9/12/15/20 V. If the requested voltage is unavailable, O says the chip requests the nearest lower offered voltage. Codes 6/7 undefined. B has a different codebook. Read `0x35` capabilities and actual status/voltage; O does not define a live renegotiation sequence or selection persistence. N says adapter removal invalidates selection. | Automatic maximum; numeric reset cell blank in O | B p.4-5; N p.7; O p.8 |
| `0x10` | TEMP_LOOP_CTL / Temp_Loop_En | 7 | R/W | 1 enables internal thermal power reduction; 0 disables it. Reserved bits 6:3 must be retained. External battery NTC protection is separate. | O prints malformed `101` for this single bit; read actual state | O p.9 |
| `0x10` | Temp_Loop | 2:0 | R/W | Internal thermal-loop trigger `thermal_threshold_degC = 80 + 5k`. Codes 0-7 mathematically give 80-115 degrees Celsius; trip accuracy and hysteresis are unspecified. | `100` binary = code 4, nominal 100 degrees Celsius | O p.9 |
| `0x15` | CC3CC4_CTL / CC4_OUT | 7 | R/W | 0 low with internal 5.1 kohm pull-down; 1 high with 330 microampere pull-up. Manufacturer recommends driving only a MOS gate. This is not a general-purpose high-current output or an assigned fan pin. | 0 | O p.9 |
| `0x15` | CC3_OUT | 6 | R/W | Same drive definition as CC4_OUT. Bits 5:0 reserved; actual board routing must be identified first. | 0 | O p.9 |
| `0x16` | STANDBY_TIME / Standby_Time | 7:0 | R/W | No-activity standby delay `standby_delay_s = k`; minimum 2 s. Not the charging timeout or host display timeout. | `0x0A` = 10 s | O p.9 |
| `0x17` | NTC_CTL / NTC_EN | 7 | R/W | 1 enables NTC high/low-temperature protection; 0 disables it. This enables protection, not the temperature ADC or an ADC-valid flag. The register manual does not specify thermistor curve or protection-trip thresholds. | 1 | O p.9; DUT 2026-10-09 |
| `0x17` | Reserved | 6:0 | Preserve | Reserved in V1.16. | Unspecified | O p.9 |

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
| `0x22` | TypeC_CTL8 / Vbus_Mode_Set | 7:6 | R/W | 0 UFP/sink; 1 DFP/source; 3 DRP; 2 undefined. | A/N: 3; B: 0 | A p.7; B p.5; N p.7 default conflict |
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

None of the four supplied maps exposes a 28 V source-PDO current/enable field,
AVS voltage request, or PPS minimum/maximum-voltage field. The 28 V input category
in A/N's status register does not imply a corresponding writable source PDO.
The broader chip family supports EPR according to F, but that does not fill these
register-map gaps. B p.4 additionally says that more than 60 W requires an
E-marker recognition circuit; its 20 V/PPS prose requires recognized cable
capability for 5 A and otherwise limits to 3 A. These B-only constraints should
not be treated as permission to exceed the board/cable rating.

### Conflicting `0x0D[2:0]` input-PDO codebooks

| Field code | A: V1.00 | B: V1.13 English p.4-5 | N: V1.14 p.7 / O: V1.16 p.8 |
| --- | --- | --- | --- |
| 0 | Register absent | 5 V | Automatic: highest adapter PDO |
| 1 | Register absent | Printed `9W`, apparently a voltage-unit error | 5 V |
| 2 | Register absent | 12 V | 9 V |
| 3 | Register absent | 15 V | 12 V |
| 4 | Register absent | 20 V | 15 V |
| 5 | Register absent | Undefined | 20 V |
| 6/7 | Register absent | Undefined | Undefined |

Do not confuse these selection codes with the independent `0x33` input-voltage
status codes. `0x35` reports offered PDO availability, not the chosen contract or
measured voltage. O p.8 now explicitly marks `0x0D[2:0]` R/W, resolving
that access discrepancy for its documented variant. It agrees with N
on codes 0-5 and additionally describes nearest-lower-voltage fallback. The
older B/N access-column conflict remains relevant when identifying older variants.

**Corrected DUT observations (2026-10-09):** `0x0D` consistently reads **0**,
including with a PD supply negotiating 20 V. The earlier reported value 7 was
the displayed mask `0x07`, not the register value, and is withdrawn. Code 0 with
20 V input supports N's automatic-selection interpretation, rather than B's
0 = 5 V. The working YAML uses 0 automatic, 1-5 = 5/9/12/15/20 V, with 6 and 7
undefined. Codes 1-5 and write access remain untested. A 28 V-capable PD 3.1
supply did not yield 28 V charging input in this setup; this is an observation,
not an established universal input limit.

Separately, connecting a known 20 V PD input changed `0x33[2:0]` from 0 to 6.
This confirms **code 6 = 20 V on this DUT**, supporting A/N and contradicting B's
code-6 = 15 V entry. Other voltage-category codes remain untested; the preceding
code 0 is only an observed pre-connection state, not an established voltage.
Read-only exploration and passive captures should come before any controlled
write test of this field. O p.15 independently documents the A/N codebook
for `0x33[2:0]`; it does not make code 0 a valid voltage category.

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
| `0x35` | RECEIVED_PDO / PDO_DRP | 7 | R | Received partner PDO DRP flag. This is not the local role configuration in `0x22`. | O p.16 |
| `0x35` | PDO_USBCOM | 6 | R | Received USB-communications flag; O uses the wording USBCOMMIT. Not proof that this board has a working USB data interface. | O p.16 |
| `0x35` | PDO_28V | 5 | R | Fixed 28 V PDO received. Availability alone does not prove 28 V will be requested or accepted; `0x0D` defines no explicit 28 V request code. | O p.16 |
| `0x35` | PDO_20V | 4 | R | 1: fixed 20 V PDO received/available; 0: not received/available. No current value or selected-contract indication. | B/N + C; O p.16 |
| `0x35` | PDO_15V | 3 | R | 1: fixed 15 V received/available; 0: absent. | B/N + C |
| `0x35` | PDO_12V | 2 | R | 1: fixed 12 V received/available; 0: absent. | B/N + C |
| `0x35` | PDO_9V | 1 | R | 1: fixed 9 V received/available; 0: absent. | B/N + C |
| `0x35` | PDO_5V | 0 | R | 1: fixed 5 V received/available; 0: absent. Bits 7:5 are defined by O above, not reserved for that revision. | B/N + C; O p.16 |
| `0x38` | STATE_CTL3 / Vsys_Oc | 5 | R / W1C? | Latched output overcurrent; prose says write 1 to clear despite R column. | A/B inconsistency |
| `0x38` | Vsys_Scdt | 4 | R / W1C? | Latched output short-circuit; same access inconsistency. | A/B |
| `0x39` | IC_VERSION / IC_Version | 7:0 | R | Revision code 1 = B, 2 = C, 3 = D; other codes unspecified. Not a complete firmware-build ID or proof that every V1.16 control exists on a given chip. | O p.17 |
| `0x3A` | IC_TEMP / Thermal_loop | 7 | R | Internal thermal-loop trigger flag; keep separate from NTC enable/protection and external thermistor temperature. It is not a temperature-valid bit. | O p.17; DUT thermal-loop observation |
| `0x3A` | IC_TEMP | 6:0 | R | Internal IC temperature directly in degrees Celsius: `die_temperature_degC = byte & 0x7F`. Codes 0-127 are representable, not a calibrated operating range. Negative-temperature encoding, accuracy and update rate are unspecified. | O p.17; earlier DUT warming observations |

`0x38` describes repeated fault detections within roughly 600 ms and approximately 1.5 s before sleep. B's fault-recovery prose refers to toggling `0x22[7]`, but its own map defines `0x22[7:6]` as the Type-C role. Treat that recovery instruction as suspect; do not implement it blindly.

### Conflicting `0x33[2:0]` codebooks

| Code | A: V1.00 p.12 | B: V1.13 English p.8 / historical C decoder | N: V1.14 p.12 / O: V1.16 p.15 |
| --- | --- | --- | --- |
| 0 | Unspecified | Unspecified | Unspecified |
| 1 | 5 V | Unspecified | 5 V |
| 2 | 7 V | 5 V | 7 V |
| 3 | 9 V | 7 V | 9 V |
| 4 | 12 V | 9 V | 12 V |
| 5 | 15 V | 12 V | 15 V |
| 6 | 20 V | 15 V | 20 V |
| 7 | 28 V | 20 V | 28 V |

Use measured `0x52/0x53` voltage and known adapter profiles to identify the codebook your chip uses. A higher document version number does not prove it matches your chip or that every entry is correct.

## Measurements and identification bytes

| Address(es) | Register(s) | Access | Format / units | Evidence / caveat |
| --- | --- | --- | --- | --- |
| `0x50`, `0x51` | BATVADC_DAT0/1 | R | Low then high; combined value in mV at VBAT. | A/B |
| `0x52`, `0x53` | VsysVADC_DAT0/1 | R | Low then high; combined value in mV at VSYS. | A/B; confirm actual board node and voltage drop to USB VBUS. |
| `0x69` | TIMENODE1 | R | First ASCII identification/time-node character. | A p.14; B p.10; N p.15 |
| `0x6A` | TIMENODE2 | R | Second ASCII character. | A p.14; B p.10; N p.15 |
| `0x6B` | TIMENODE3 | R | Third ASCII character. | A p.15; B p.10; N p.15 |
| `0x6C` | TIMENODE4 | R | Fourth ASCII character. | A p.15; B p.10; N p.15 |
| `0x6D` | TIMENODE5 | R | Fifth ASCII character. | A/B/N; called a timestamp, but not established as a live clock or formal version ID. |
| `0x6E`, `0x6F` | IBATIADC_DAT0/1 | R | Low then high; unsigned battery-current magnitude in mA, positive in both directions. | A/B/N scale; independent DUT charging/discharging verification. |
| `0x70`, `0x71` | ISYS_IADC_DAT0 / IVsys_IADC_DAT1 | R | Low then high; unsigned system-current magnitude in mA, positive in both directions. | A/B/N scale; independent DUT verification; exact node not separately established. |
| `0x74`, `0x75` | Vsys_POW_DAT0/1 | R | Low then high; USB-side power magnitude in **10 mW/code**, `power_mW = 10 * raw16`, positive in both directions. | A/N scale; independent USB-side DUT verification 2026-10-09. B omits scale; history mistranslation does not remove telemetry. |
| `0x77` | INTC_IADC_DAT0 / NTC_IADC_DAT | R | Bit 7: 0 = 20 µA excitation; 1 = 80 µA. Bits 6:0 reserved. | A/B; this is an excitation-current indication, not battery current. |
| `0x78`, `0x79` | VGPIO0_NTC_DAT0/1 | R | Low then high; GPIO0/NTC voltage in mV, nominal 0–3300 mV. | A/B; no additional 3300/65535 scaling is specified. |

Read pairs in separate explicit statements so language expression-evaluation order cannot reverse them. Decode direction from validated operating state; the DUT current values are positive magnitudes in both directions and must not be reinterpreted as signed currents. NTC voltage plus excitation current can yield resistance; converting that to temperature requires the actual thermistor curve and board network.

### Conversion examples and measurement limits

For each documented pair, assemble `raw16 = low | (high << 8)` after reading low
first. The manuals state that a low-byte read refreshes the corresponding low
and high bytes. They do **not** define one atomic snapshot spanning battery
voltage, battery current, system voltage, system current and power. Do not present
values collected at different times as simultaneous without that qualification.

| Quantity | Decode | Example |
| --- | --- | --- |
| Battery voltage | `battery_voltage_mV = raw16` | Low `0x33`, high `0x34`: `0x3433 = 13363 mV`. |
| Battery/system current magnitude | `current_mA = raw16` | Low `0xFD`, high `0x07`: `2045 mA`. DUT measurements validate positive magnitudes in both directions; direction is separate. |
| System power | `system_power_mW = 10 * raw16` | Raw `1000`: `10000 mW = 10 W`. Use at least 32-bit arithmetic; the full 16-bit representation scales to 655350 mW, not a supported operating-power range. |
| NTC excitation selection | `(byte >> 7) & 1` | 0 selects 20 microamperes, 1 selects 80 microamperes. Lower bits do not change that selection. |
| NTC voltage | `ntc_voltage_mV = raw16` | Raw `1500` means 1500 mV; the documented range is 0-3300 mV. |
| Fixed-PDO base current | `pdo_base_current_mA = 20 * k` | `0x96` gives 3000 mA; do not confuse the code with 150 mA. |
| Fixed-PDO current including add bit | `pdo_current_mA = 20 * k + 10 * add` | `0x96` with its corresponding `0x2C` bit set gives a programmed 3010 mA before other limits/negotiation. |
| PPS programmed current | `pps_current_mA = 50 * k` | `0x3C` gives 3000 mA, not 5000 mA. |

If the actual board applies the indicated excitation current entirely through a
thermistor, `resistance_ohm = 1000 * ntc_voltage_mV / excitation_current_uA`.
Parallel resistors, clamps, leakage and current-source compliance can invalidate
that simple calculation. The I2C manuals provide no thermistor beta/Steinhart-Hart
coefficients, ADC accuracy, sample rate, signed-current encoding or die-temperature
calibration. They do not define SMBus PEC, SMBus block protocols or a device-ID
command; use the documented I2C register transfers rather than assuming SMBus
semantics from the electrical bus.

### Defined-bit index

These masks summarize the four supplied manuals, with O additions explicitly
identified. They are **defined-field masks, not write permissions or complete
reset bytes**. Preserve the complement for ordinary R/W changes; use the field
access and special command semantics above. A defined bit in V1.16 must not be
assumed writable on a different chip/firmware variant. Earlier masks remain
useful only for the earlier documents they describe.

| Address | Defined mask | Reserved mask | Purpose / primary pages A; B; N |
| --- | --- | --- | --- |
| `0x00` | `0xFD` | `0x02` | Charging/reset controls; 4; 3; 4. |
| `0x02` | `0xFF` | `0x00` | Per-cell charge voltage; 4; 3; 4. |
| `0x03` | `0xFF` | `0x00` | Battery charge-current limit; 5; 3; 5. |
| `0x04` | `0x07` | `0xF8` | O p.5: series-cell count. |
| `0x06` | `0xFF` | `0x00` | Trickle current; 5; 3; 5. |
| `0x08` | O: `0xFE`; A/B/N: `0xFC` | O: `0x01`; A/B/N: `0x03` | O p.5 adds completion/timeout policy bit 1. Older termination/recharge-only masks preserve this behavior without auditing it. |
| `0x09` | O: `0xE8`; A/B/N: `0xE0` | O: `0x17`; A/B/N: `0x1F` | O p.6 adds D-revision standby-mode bit 3. |
| `0x0A` | O: `0xF7`; A/B/N: `0xE0` | O: `0x08`; A/B/N: `0x1F` | O p.6 adds adjustment sign/value. Base threshold alone is incomplete when adjustment is nonzero. |
| `0x0B` | O: `0xF8`; A/B/N: `0xF0` | O: `0x07`; A/B/N: `0x0F` | O p.7 adds drive anti-EMI bit 3. |
| `0x0C` | O: `0xEF`; A/B/N: `0xE0` | O: `0x10`; A/B/N: `0x1F` | O p.8 adds separate input-power enable/code. |
| `0x0D` | `0x07` | `0xF8` | Input PDO; absent; 4-5; 7; O p.8 explicitly R/W. |
| `0x10` | `0x87` | `0x78` | O p.9: thermal-loop enable/threshold. |
| `0x15` | `0xC0` | `0x3F` | O p.9: CC3/CC4 output controls. |
| `0x16` | `0xFF` | `0x00` | O p.9: standby delay. |
| `0x17` | `0x80` | `0x7F` | O p.9: NTC protection enable. |
| `0x22` | `0xC0` | `0x3F` | Type-C role; 7; 5; 7. |
| `0x23` | `0xFF` | `0x00` | PDO current-selection/enables; 7-8; 5; 8. |
| `0x24`, `0x25`, `0x26`, `0x27`, `0x28` | Each `0xFF` | Each `0x00` | Fixed-PDO current codes; 8-9; 5-6; 8-9. |
| `0x29`, `0x2A` | Each `0xFF` | Each `0x00` | PPS current codes; 9; 6; 9-10. |
| `0x2B` | `0x7E` | `0x81` | Source-PDO enables; 9-10; 6; 10. |
| `0x2C` | `0x1F` | `0xE0` | Fixed-PDO 10 mA additions; 11; 7; 11. |
| `0x31` | `0x3F` | `0xC0` | Charge/discharge state; 11-12; 8; 11-12. |
| `0x32` | `0xC0` | `0x3F` | 5 V/high-voltage charging class; 12; 8; 12. |
| `0x33` | `0xC7` | `0x38` | Input voltage/presence/overvoltage; 12; 8; 12. |
| `0x34` | `0xFC` | `0x03` | Type-C/PD/fast-charge flags; 12-13; 8-9; 12-13. |
| `0x35` | O: `0xFF`; B/N: `0x1F` | O: `0x00`; B/N: `0xE0` | O p.16 defines DRP, USB communications and 28 V received-PDO flags in bits 7:5. |
| `0x38` | `0x30` | `0xCF` | Latched system faults; 13; 9-10; 13-14; O p.17 retains W1C/access conflict. |
| `0x39` | `0xFF` | `0x00` | O p.17: IC revision, read-only. |
| `0x3A` | `0xFF` | `0x00` | O p.17: die temperature and thermal-loop flag, read-only. |
| `0x50`, `0x51` | Each `0xFF` | Each `0x00` | Battery voltage low/high; 13-14; 10; 14. |
| `0x52`, `0x53` | Each `0xFF` | Each `0x00` | System voltage low/high; 14; 10; 14-15. |
| `0x69`, `0x6A`, `0x6B`, `0x6C`, `0x6D` | Each `0xFF` | Each `0x00` | Five ASCII characters; 14-15; 10; 15. |
| `0x6E`, `0x6F` | Each `0xFF` | Each `0x00` | Battery current low/high; 15; 10; 16. |
| `0x70`, `0x71` | Each `0xFF` | Each `0x00` | System current low/high; 15-16; 11; 16. |
| `0x74`, `0x75` | Each `0xFF` | Each `0x00` | System power low/high; 16; 11; 16-17. |
| `0x77` | `0x80` | `0x7F` | NTC excitation selector; 16; 11; 17. |
| `0x78`, `0x79` | Each `0xFF` | Each `0x00` | NTC/GPIO0 voltage low/high; 16-17; 11; 17. |

For multi-field bytes, reset codes must be shifted into their own fields. For
example, `0x08`'s termination code 2 and recharge code 2 contribute
`(2 << 4) | (2 << 2) = 0x28` under mask `0xFC`; they do not mean writing byte
`0x02`. Under O the complete defined mask is `0xFE`, but adding bit 1 to a
write policy requires an explicit completion/timeout decision; it is not merely
a formatting update to the old mask. Read actual values and preserve reserved bits. Blank reset cells and `X`
mean unspecified, not zero. Reserved cells printed R/W in Chinese copies or R
in B still must not be modified.

## Undocumented or questionable address leads

These rows are intentionally separated from the documented map. They are not permission to write these locations, and names alone do not determine whether they are configuration commands, raw GPIO ADC readings, or copied definitions for another chip.

| Address | Claimed name / purpose | What remains unknown | Source |
| --- | --- | --- | --- |
| `0x01` | SYS_CTL1: series count, battery type, current-setting mode | Bits, encoding, access, prerequisites, reset behavior, firmware applicability. Unused definition; matches an IP2368 heading. No verified cell-count field. | D |
| `0x04` | Earlier SYS_CTL4 battery-capacity lead | Superseded for the O-documented variant: O p.5 explicitly defines Bat_Num in bits 2:0. C's capacity label is not the current manufacturer definition. | C; O; DUT observations |
| `0x54` | IVBUS_IADC: input charging current | Width, scale, access, relevance; absent from A/B. | D |
| `0x7A` | VGPIO1_ISET: current setting | May be configuration-pin ADC data rather than writable current command. GPIO1 is INT in standard IP2366 I²C pinout, raising concern. | D |
| `0x7C` | VGPIO2_VSET: cell-voltage setting | Access and scale unknown; may be GPIO voltage telemetry. | D |
| `0x7E` | VGPIO3_FCAP: battery capacity | Conflicts with usual IP2366 GPIO3/PSET function. | D |
| `0x80` | VGPIO4_BATNUM: cell-count setting | No bit definition; name is consistent with BAT_NUM pin but does not prove writable S. Do not infer codes 2–6. | D |

D also calls `0x35` MOS_STATE, conflicting with B/N's RECEIVED_PDO and the historical C decoder. Together with the GPIO labels, this reduces confidence in its unexercised header definitions. A candidate address is evidence worth investigating, not a verified extension of the manufacturer map.



## Ambiguities and DUT validation

### Consolidated DUT results (2026-10-09)

Measurements below were independently compared unless stated otherwise. These
results determine the working YAML interpretation; historical manual conflicts
are retained for readers dealing with other revisions. Source O now documents
`0x04`, `0x17` and `0x3A` and confirms the working voltage-status/PDO codebooks;
the rows below retain their original experiment dates, not new bench testing. Reset defaults, physical
trip accuracy and write/recovery mechanisms are separate from read decoding.

| Register / topic | Result and working interpretation | Remaining boundary |
| --- | --- | --- |
| `0x33[2:0]` | Known 20 V PD connection changed code 0 to 6. Select A/N: 1-7 = 5/7/9/12/15/20/28 V. | Only code 6 experimentally validated; code 0 remains undefined. |
| `0x0D[2:0]` | Actual consistent value is 0, including negotiated 20 V; earlier 7 was the mask. Select N: 0 automatic, 1-5 = 5/9/12/15/20 V. | Codes 6/7 undefined; explicit selections and writes untested. |
| `0x6E/0x6F` | Low/high `A3 07` = 1955 mA charging; `D1 07` = 2001 mA discharging. Decode unsigned battery-current magnitude, 1 mA/code. | Direction must come from separate operating-state information; accuracy/range not characterized. |
| `0x70/0x71` | `76 05` = 1398 mA charging; `7E 05` = 1406 mA discharging. Decode unsigned system-current magnitude, 1 mA/code. | Exact measurement-node attribution not separately established. |
| `0x74/0x75` | `C8 0A` = 27600 mW charging; `09 0B` = 28250 mW discharging, verified on USB side. Decode positive USB-side power, 10 mW/code. | No accuracy specification inferred. |
| `0x22[7:6]` | `0xC0` observed: code 3 = dual-role. Code meaning agrees across manuals. | Untouched reset default disputed, not a decoding blocker. |
| `0x0A[7:5]` | 2.6 V setting = `0x20`; 3.0 V = `0xA0`. Select B/N: `threshold_mV_per_cell = 2500 + 100 * code`. | Actual physical cutoff accuracy not tested. |
| `0x0C[7:5]` | DUT calls this In/Out Power; input/output scope experimentally confirmed. O additionally documents independent input-power selection in `0x0C[3:0]`; the BAT-current limit at `0x03` is a separate constraint. | PDO write precedence remains unverified. |
| `0x06` | `0x04` = 200 mA; range 100-1000 mA, maximum `0x14`. Adopt as working IP2366 range, 50 mA steps, codes 2-20. | Minimum documented by N; maximum adopted from DUT-exposed range, not given in supplied manuals. |
| `0x04[2:0]` | Field number tracks experimentally changed series-cell settings. Direct cell count. | Specific tested counts not listed; now documented by O p.5, while hardware-strap/reset interaction remains unverified. |
| `0x17[7]` | Enabled = `0x80`, off = `0x00`. Battery NTC protection enable, not fault status. | Protection-trip behavior not tested. |
| `0x3A` | Lower 7 bits temperature in degrees Celsius; bit 7 internal thermal regulation active, user experimentally verified. | Calibration, threshold and full range not characterized. |
| `0x38` | DUT offers working Clear Errors action. | Exact write/clear mechanism not captured; W1C not yet established. |
| `0x69-0x6D` | ASCII `YLSII`; working meaning is five-byte manufacturer-defined identifier. | Manufacturer may encode model/version/date; no mandated format. Do not force timestamp conversion. |
| `0x56/0x57` | Existing controller never reads these addresses. No new decoder. | Incomplete discharge-current lead remains untested. |

### Historical conflicts and remaining tests

This historical working list is retained with V1.16 resolution notes below.
D03/D10 access/codebook and D15 documentation gaps are resolved by O for its
documented variant; D09 now also requires checking separate input-power fields.
They are not all still-open manufacturer-definition questions. **Contradictions**
are different statements in the supplied manuals. **Gaps** are information none
of the manuals establishes. A revision difference is not automatically an error,
and two agreeing documents do not prove the DUT uses their codebook.

Prioritize read-only/passive observations. Do not create a short circuit,
overcurrent, undervoltage, overtemperature or unsafe charge setting merely to
resolve a documentation gap. Any later write experiment needs its own protected
setup, confirmed register semantics and recovery plan; this table is not a set
of authorized write instructions.

| ID / priority | Type / topic | Exact source disagreement or gap | Evidence to collect from the DUT |
| --- | --- | --- | --- |
| D01 / first | Contradiction: `0x33[2:0]` voltage category | A p.12 and N p.12: codes 1-7 mean 5/7/9/12/15/20/28 V. B p.8 shifts 5 V to code 2 and omits 28 V. | Observe known, safely rated adapter contracts; record `0x33`, `0x34`, `0x52/0x53` and an independent voltage measurement. No configuration writes are needed. |
| D02 / first | Contradiction: `0x22[7:6]` role reset | A p.7/N p.7 list DRP code 3; B p.5 lists UFP code 0. Manuals also say actual defaults vary. | Capture power-up/wake reads and any existing-controller writes. A value after controller initialization is not an untouched reset value. |
| D03 / first | Contradiction: `0x0D` selection codes | B p.4-5: codes 0-4 select 5/9/12/15/20 V, with `9W` printed for code 1. N p.7: 0 automatic maximum, 1-5 select those voltages. A has no entry. | Prefer passive capture of the board controller's known adapter-selection operations, paired with measured input voltage and offered flags `0x35`. Readback alone may not reveal what each command means. |
| D04 / first | Gap: current sign/direction and node | A p.15-16, B p.10-11 and N p.16 give mA but no signedness or positive-direction convention for `0x6E/0x6F` and `0x70/0x71`. | Compare raw pairs with independent current measurements in idle, charging and discharging; record the status flags and measurement node. A positive magnitude alone does not establish two's-complement or direction. |
| D05 / first | Gap: power applicability/scale | A p.16 and N p.17 give 10 mW/code; B p.11 omits scaling. B's history incorrectly translates the removed battery-level feature as power. | Compare `10 * raw16` with independently measured system voltage/current under steady load, allowing for different measurement times/nodes. Do not delete the decoder merely because of B's mistranslated history. |
| D06 / next | Contradiction: wake source | A p.2/B p.1 say high INT wakes the device; N p.2 says charging or EN wakes it. All describe high INT as inhibiting sleep and require 100 ms high before communication. | Record INT and existing EN/charging events through normal sleep/wake cycles. Establish pin electrical behavior before any external drive experiment. |
| D07 / next | Revision difference: `0x0A[7:5]` low-voltage codes | A p.6: codes 0-4 = 2.8-3.2 V/cell. B p.4/N p.6: codes 0-7 = 2.5-3.2 V/cell; at/below 2.7 V software protection only. Code 2 therefore means 3.0 V or 2.7 V/cell. | First log existing settings with series count and firmware identification. Actual threshold verification needs a protected battery simulator/manufacturer clarification, not deep discharge of a real pack. |
| D08 / next | Revision difference: trickle minimum | N p.1/p.5 explicitly adds 100 mA minimum to `0x06`; A p.5/B p.3 omit a minimum. All give 50 mA/code and reset code 4. | Record normal precharge settings/current if the controller exposes this safely. Absence of a minimum in an older manual is not evidence that 0 or 50 mA is supported. No maximum is specified. |
| D09 / next | Gap: `0x0C` scope and write precedence | A p.6-7/N p.7 say input/output power; B p.4 says output. Only A p.7 states later `0x0C` versus `0x23-0x28` writes override earlier ones. | Capture existing-controller ordering, readback and advertised/negotiated capabilities. A power-limit read does not by itself establish enforcement on both directions. |
| D10 / resolved for O | Earlier contradiction: `0x0D` access | B p.4/N p.7 mark R despite selection prose. O p.8 explicitly marks R/W and describes lower-offer fallback. | Documentary write access is established for O's variant; actual renegotiation sequence, persistence and DUT write behavior remain to be verified. |
| D11 / later | Internal contradiction: `0x38` fault clear | A p.13, B p.9-10, N p.14 say write 1 to clear, while access is R. Chinese copies say at least two detections within 600 ms; B says more than two. About 1.5 s to sleep is given; B alone adds post-sleep persistence. | Capture naturally occurring faults and the existing controller's response, if available. Do not deliberately overload/short the board. W1C access, exact count and persistence remain unverified. |
| D12 / later | Suspect recovery instruction | B p.9-10 recommends toggling `0x22[7]` to reopen output, but that bit belongs to the two-bit Type-C role field. A/N omit this instruction; `0x0B[7]` is the documented output enable. | Seek a corrected manufacturer instruction or observe known-safe controller recovery. Do not substitute another register by guesswork or toggle the role bit blindly. |
| D13 / next | Internal contradiction: PPS default / extra limits | All list `0x29/0x2A` reset `0x3C`, giving 3 A at 50 mA/code. B p.6 says default 5 A and adds cable-dependent 3/5 A limits; B p.4 also adds the greater-than-60-W E-marker note. A/N do not supply those prose limits. | Record untouched register codes, actual source PDOs and recognized cable capability using safely rated equipment. Distinguish programmed, advertised, negotiated and measured current. |
| D14 / later | Incomplete lead: discharge-current pair | A p.14 has a sentence naming `0x56/0x57` for discharge current, but no register entries/units/latch rule; B/N omit it. | Read-only/passive comparison against a known discharge current may establish whether these addresses respond; keep raw bytes until width/scale/node are verified. |
| D15 / resolved definitions in O | Earlier gaps: `0x04`, `0x17`, `0x3A` | A/B/N omit these fields; O p.5/p.9/p.17 explicitly documents them, consistent with the recorded DUT interpretations. | Remaining questions concern variant applicability, BAT_NUM/reset interaction, temperature accuracy and physical protection-trip behavior, not whether V1.16 defines the fields. |
| D16 / later | Gaps: identity/burst/precision | Five ASCII bytes are defined, but no chip-ID format or live timestamp contract. No guaranteed burst increment, ADC accuracy, update interval or cross-register atomic snapshot is supplied. | Record `0x69-0x6D` before/after ordinary wake and power cycles, along with chip markings. Prefer explicit single-byte low/high reads; do not interpret unvalidated bursts as consecutive registers. |

Record each experiment with chip marking, PCB identity, known cell count, adapter
and cable, existing-controller firmware, raw transactions, before/after state,
independent measurement and any capture-loss indication. A result should be
labelled **confirmed on this DUT**, not silently promoted to a universal IP2366
definition. Several tests can settle a decoder's behavior without enabling any
configuration writes.

## Revision history and incompatibilities

The following is the Chinese document history through O p.1, cross-checked
with A p.1 and N p.1. B p.12 has
misaligned/mistranslated history wording, including the V1.00 wake text and the
V1.11 power/battery-level wording. These dates describe documents, not proven
silicon or firmware release dates.

| Version | Date | Change listed in the Chinese history |
| --- | --- | --- |
| V1.00 | 2023-03-24 | Initial release. |
| V1.10 | 2023-04-18 | Modified standby EN wake behavior; added charging-PDO selection. |
| V1.11 | 2023-04-24 | Removed I2C battery-level reading description because battery-level reading is unsupported. This is not deletion of the power registers. |
| V1.12 | 2023-06-13 | Added charging-wake description in standby. |
| V1.13 | 2023-06-26 | Extended low-voltage selection down to 2.5 V/cell. |
| V1.14 | 2023-10-27 | Minimum trickle-current setting specified as 100 mA. |
| V1.15 | 2024-02-28 | Changed the default low-battery voltage. The history does not give its new value and O leaves the field reset blank. |
| V1.16 | 2025-04-28 | Added battery-series-count and other functions. The history does not separately date every newly listed field. |

| Topic | Difference | Practical consequence |
| --- | --- | --- |
| Input fixed PDO | B/N add `0x0D` and `0x35`; B/N selection codes disagree. | Do not assume a single selection codebook or proven write permission. |
| Low-voltage selection | A starts at 2.8 V/cell; B/N at 2.5 V/cell. | Same bits can imply a 0.3 V/cell difference. |
| Voltage status | A/N include 28 V; B shifted codes omit it. | A decoder copied from the historical C implementation can misreport an A/N-style chip. |
| Role reset | A/N DRP; B UFP. | Read your actual initial state before controller initialization. |
| Trickle minimum | N explicitly specifies 100 mA; A/B omit it. | Do not assume lower settings are valid. |
| Power telemetry | B mistranslates the deleted battery-level feature as power. Chinese V1.14 resolves the wording. | Power telemetry is not shown to be unsupported by that revision entry. |
| PPS current default | `0x3C × 50 mA = 3 A`, B prose says 5 A. | Trust arithmetic, then actual advertisements; do not repeat prose as a measured default. |
| SELECT_PDO access | B/N mark it R; O explicitly marks it R/W and describes fallback to a lower offered voltage. | O resolves the documentary contradiction for its documented variant; verify actual application and renegotiation behavior. |
| Additional controls | O documents `0x04`, `0x08[1]`, `0x09[3]`, `0x0A[4,2:0]`, `0x0B[3]`, `0x0C[3:0]`, `0x10`, `0x15-0x17`, `0x35[7:5]`, `0x39` and `0x3A`. | Update both decoders and defined-bit masks; preserving a newly understood bit is not equivalent to auditing its behavior. |
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
| N | [Supplied Chinese register manual V1.14](materials/ip2366_i2c.pdf) | Inspected local file, 18 pages, revision dated 2023-10-27. This review uses its actual contents; the earlier inaccessible endpoint L is not independent corroboration and byte identity to that web endpoint is not asserted. |
| O | [Supplied Chinese register manual V1.16](materials/ip2366_i2c_regs_v1.16_cn.pdf) | Supplied alongside the PY32 host source; inspected 22-page register text, history dated 2025-04-28. Manufacturer text for IP2366_I2C; applicability to a particular chip/firmware must still be checked. Footer page totals remain incorrectly printed as 18. |

The inspected GitHub snapshot is commit `9a23b86ec0f2544c56b25e16900b5257347a150a`. For reproducibility, replace `main` in GitHub links with this commit. No exhaustive claim is made about private customer manuals, QQ group files, unindexed repositories, or chip-specific customized firmware.

## Passive decoding clarifications (2026-10-07)

V1.16 update (2026-10-21): the historical headings below retain their original
anchors. Manufacturer definitions in O now replace INFERRED labels for `0x04`,
`0x17` and `0x3A` on its documented variant. Original observations and untested
physical behavior remain separate evidence.

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
| `0x6E/0x6F`, `0x70/0x71` current | Decode unsigned current magnitude in mA; direction remains separate. | Independent charging/discharging comparisons confirmed on 2026-10-09; see consolidated results. |
| Example `0x6E=0xFD`, `0x6F=0x07` | `0x07FD = 2045`, hence unsigned-code interpretation 2045 mA. | Arithmetic cross-check, not proof of signedness, accuracy, or current direction. |
| `0x0A[7:5]`, `0x33[2:0]` | Use B/N threshold conversion and A/N voltage-category map. | DUT evidence 2026-10-09 resolves the working map; historical alternatives remain documented above. |
| `0x24` through `0x28` PDO currents | Label `20k` mA as the **base programmed current**, excluding the separate 10 mA add bit in `0x2C`. | A pages 8-11 confirms the two components. Effective advertisement also depends on enables, limits and negotiation; arbitrary cached reads are not an atomic snapshot. |
| `0x29/0x2A` PPS currents | Show programmed `50k` mA, not negotiated or measured current. `0x3C` is 3000 mA. | Enable state, cable capability and actual advertisements remain relevant. |
| `0x74/0x75` power | Decode USB-side magnitude in mW using 10 mW/code. | A/N scale independently verified in charging/discharging on the DUT. |
| `0x77` NTC current | Decode only bit 7: 20 or 80 microamperes of excitation. | A page 16; no battery-current or temperature interpretation. |
| `0x78/0x79` NTC voltage | Decode mV directly; do not apply an extra full-scale ADC factor. | A pages 16-17. Thermistor curve and actual board network are still needed for temperature. |
| Undefined enumeration codes or values beyond documented ranges | Retain the code and report `UNDEFINED_CODE` or `OUT_OF_RANGE`; never clamp to a plausible value. | Such output means interpretation is incomplete or outside the stated range, not necessarily a capture failure. |
| Observed configuration writes | Report the transmitted field values separately from successful readback. | Bus ACK does not establish that a setting was applied, remained active, or is safe. O resolves `0x0D` as R/W for its variant; the `0x38` access contradiction remains unresolved. |

### Newly recorded primary-source lead: 0x56/0x57

Source A page 14 contains an isolated sentence that discharge current is stored
in `0x56` and `0x57`, referring to `0x31[3]` as a discharge indicator. However,
the inspected map provides no corresponding complete register entries establishing
width, scale, signedness, latch behavior, or applicability. This conflicts with
the temptation to treat the sentence as a complete alternative current accessor.
It is an **unresolved lead only**: no physical-value decoder for these addresses
is enabled. Confirm against a matching manufacturer revision and bench readings
before adding an interpretation.

The supplied V1.14 manual N p.15 and English B p.10 omit this sentence. Its
absence does not prove the registers were removed, but it leaves the V1.00
lead without a complete definition in any of the supplied revisions.

### Bench-supported inference: 0x04 series-cell count

On 2026-10-07, passive capture of the user's IP2366 operating with a known 4S
battery returned `0x04` from register `0x04`. Together with similar-chip register
documentation (specific document/revision not supplied), this supports the working
interpretation `Bat_Num = register & 0x07`, in units of series-connected cells.
The proposed valid range is 2-6; codes 0, 1 and 7 are outside that inferred range,
but their actual hardware meaning has not been established.

On 2026-10-09 the user experimentally confirmed that changing the series-cell
setting changes this field to the corresponding cell count. Direct encoding is
therefore the working interpretation, not merely a single 4S correlation. The
tested counts were not individually enumerated. Power-up behavior, interaction
with BAT_NUM hardware and wider variant applicability remain unspecified.
Bits 7:3 are preserved. O p.5 now explicitly documents bits 2:0 as direct
cell count 2-6 and bits 7:3 as reserved; the earlier inference is confirmed
by primary documentation, not an inference that all variants behave identically.

### Bench-supported inferences: 0x17 and 0x3A

The user supplied the following working definitions on 2026-10-07, based on
similar-chip documentation and passive sniffing. No matching primary IP2366
register document or specific similar-chip revision was supplied.

The subsequent full review of A, B and N on 2026-10-09 still found no entries
for these addresses. The subsequent V1.16 review (2026-10-21) changes that
status: O p.9 documents `0x17`, and O p.17 documents `0x3A`. Read their current
definitions in the main tables above; the observations below retain their
historical context and do not establish physical accuracy or trip performance.

- `0x17[7]` is `NTC_EN`: 1 means battery NTC temperature protection enabled,
  0 disabled. On 2026-10-09 the DUT setting comparison confirmed enabled =
  `0x80`, disabled = `0x00`. Bits 6:0 are preserved; field polarity is verified,
  but this comparison is not a test of protection-trip behavior.
- `0x3A[6:0]` is an inferred unsigned, direct internal die temperature in degrees
  Celsius, with `0x3A[7]` indicating thermal-loop activity. A captured byte `0x1E`
  gives code 30 and an inactive-loop bit. The 30 degrees Celsius interpretation
  is plausible near room temperature/light load, but was not independently
  calibrated. On 2026-10-09 the user reported experimental verification that
  bit 7 indicates active internal thermal regulation. Accuracy, negative-temperature
  encoding and wider-range validation remain unspecified. O p.9 now documents
  the nominal configurable thermal threshold in `0x10[2:0]`, but not trip accuracy. Codes
  0-127 are the representable field range, not a verified operating/accuracy range.

The user later confirmed that the reported internal temperature rises plausibly
as the board warms during battery charging. This strengthens the temperature
interpretation but is not an independent calibration. The reading remains valid
when the thermal-loop flag is 0: a protection/loop-status bit is not an ADC-valid
bit. Active per-property and batch reads have also been reported working on this
DUT through the test instrument; that confirms acquisition on this setup, not
universal read side-effect freedom or write access.

These are separate properties: the internal die reading and thermal loop must
not be presented as the battery thermistor temperature or proof that battery NTC
protection works. For an O-matched variant these fields can now be labelled
manufacturer-documented; retain any separate DUT applicability/calibration
caveats. Historical passive observations alone do not establish safe write or
protection behavior.

### Charger integration and host-source findings (2026-10-21)

For the O low-voltage formula, distinguish the base code `k_base`, adjustment
code `k_adjust` and cell count `S`: `base_cell_mV = 2500 + 100 * k_base`,
`adjust_cell_mV = 100 * k_adjust`, and the stated pack threshold is
`S * (base_cell_mV +/- adjust_cell_mV)`, with the sign chosen by `0x0A[4]`.
For example, base code 5, adjustment code 1 and subtraction give a nominal
2900 mV per cell rather than 3000 mV. This is a mathematical cross-check of
the documented formula, not a recommendation to configure that combination
or proof of its physical trip point. O reuses `N` for two different quantities;
the separate variable names here avoid confusing adjustment code with cell count.

V1.16 adds controls that an older driver can silently inherit while preserving
unrelated bits. A read-only audit should distinguish requested settings from
their effective interpretation:

| Check | Why it matters |
| --- | --- |
| `0x08[1]` with termination/recharge | Bit 1 = 1 removes the chip charging-timeout function and leaves charging enable set after full. A separate host maximum-duration timer is a different mechanism. |
| Complete `0x0C` | Upper code 5 alone does not establish a 140 W input ceiling if bit 3 selects a lower separate input-power code. It also does not imply 140 W reaches the battery. |
| `0x09[5]` and complete `0x0A` | Fixed-5-V mode and supplementary adjustment can change the interpretation of a base low-voltage setting; the manual ties these settings to precharge/CC transition too. |
| `0x10` and `0x3A` | The thermal-loop configuration and trigger flag can help distinguish thermal power reduction from adapter or current-limit behavior. Do not disable thermal regulation merely to investigate reduced current. |
| `0x17`, `0x77`, `0x78/0x79` | Protection enable, excitation-current indication and external NTC voltage are separate properties. Read excitation around the voltage pair if it may change; a changed bias makes the resistance calculation ambiguous. |
| `0x39` and `0x69-0x6D` | Log IC revision and raw identification bytes independently. Neither alone proves every register in this document is supported. |

The supplied 1.47-inch PY32 host project contains active direct IP2366 register
reads despite filenames and symbols named SW6236. It confirms an implementation
using low/high voltage/current reads and `10 * raw16` mW power conversion. It
also contains old SW6236 unlock/gateway/low-current helpers, some disabled or
returning failure; those are not an IP2366 write-unlock or current-ramp contract.
No documented soft-start/ramp-rate adjustment was found in V1.16 or the active
charger-setting paths inspected.

Its Battery Series menu changes local SOC/display state rather than writing
`0x04`. Output Enable writes discharge enable `0x0B[7]`, not charging enable
`0x00[0]`. Its IP2366 external-NTC temperature is stored in a misleadingly named
`chip_temp_c10` field; it does not read die register `0x3A`. A separate local
PUYA ADC thermistor controls the fan. The source table is labelled 10 kohm/beta
3950, which is implementation evidence, not a verified thermistor specification
for every board. This distinction matters when replacing the original host.

The source also tolerates stale measurements after some read failures and has
display-sleep paths that suspend normal supervision. These are implementation
limitations to correct in a charger, not device requirements to copy. Source
provenance as the exact installed factory binary has not been established.

### Change record

- 2026-10-21: incorporated supplied manufacturer register document V1.16 and
  V1.15/V1.16 history. Promoted cell count, NTC enable and die-temperature fields
  from inference to documented definitions for the matching variant.
- 2026-10-21: added completion/timeout policy, low-voltage adjustment, separate
  input-power limit, thermal controls, D-revision standby mode, CC3/CC4 drive,
  standby delay, anti-EMI bit, received 28 V/partner flags and IC revision.
- 2026-10-21: updated defined-bit masks and PDO selection access/fallback;
  retained earlier revision conflicts, actual DUT results, unresolved W1C
  behavior and variant/accuracy limits. Added source-code integration caveats.

- 2026-10-09: consolidated independent DUT current/power measurements, newer
  low-voltage encoding, input/output power scope, NTC/cell-count/thermal-loop
  confirmations and 100-1000 mA working trickle range. Corrected PDO readback
  from the mistaken mask 7 to actual value 0; identifier observed as `YLSII`.

- 2026-10-09: compared all three supplied manuals, including visual inspection
  of connection/transaction diagrams and conflicting PDO tables. Identified the
  unversioned Chinese file as V1.14; added source/page provenance, IC pin wiring,
  preparation gaps, register-transfer examples and the warning that example
  register `0x05` is not defined in the map.
- 2026-10-09: added V1.14's 100 mA trickle-current minimum, B/N PDO-selection
  conflict, A/N versus B voltage-status and role-default differences, and explicit
  distinction between read access and disputed write permission at `0x0D`.
- 2026-10-09: corrected ASCII-register provenance and power-register R access;
  confirmed 10 mW/code from both Chinese manuals, retained B's omitted scale and
  corrected the battery-level/power revision-history interpretation.
- 2026-10-09: added all documented register masks, conversion examples,
  unspecified-contract boundaries and the D01-D16 DUT validation list. Preserved
  all earlier experimental findings and separated them from manufacturer fields.
- 2026-10-09: recorded the user-confirmed die-temperature warming trend without
  claiming accuracy, calibration, active thermal-loop validation or write safety.

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
- Consolidated DUT results above supersede earlier open current-signedness and
  working-codebook questions. Direction attribution, variant applicability,
  unknown-register leads, burst semantics and write-access contradictions remain
  separate limitations.

## Materials

* [IP2366 I2C Register Reference 1.16 (Chinese, latest supplied; 2025-04-28)](materials/ip2366_i2c_regs_v1.16_cn.pdf)
* [IP2366 Datasheet](materials/ip2366_datasheet.pdf)       
* [IP2366 I2C Register Reference 1.13 (English; compare disputed entries with Chinese originals)](materials/ip2366_i2c_regs_v1.13_en.pdf)    
* [IP2366 I2C Register Reference 1.14 (Chinese; 2023-10-27)](materials/ip2366_i2c.pdf)   
* [IP2366 I2C Register Reference 1.0 (2023-03-24)](materials/ip2366_i2c_with_reg_v1.00.pdf)      



> Tags: IP2366, I2C

[Visit Page on Website](https://done.land/components/power/powersupplies/battery/chargers/charge-discharge/ip2366/i2creference?999094101306262639) - created 2026-10-05 - last edited 2026-10-21
