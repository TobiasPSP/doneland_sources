# BatCharger 1.4.0 — full-session graphs and display revisions

All test-driven revisions discussed on 18 October 2026 are implemented.
Upload the charger firmware and reload the browser page. The ESP-NOW protocol
and test-tablet firmware do not change.

## History and graph reduction

`History` allocates 43,201 timestamped voltage/current points in PSRAM: twelve
hours at one-second resolution including endpoints, exceeding the ten-hour
requirement. Each point is 8 bytes (uint32 elapsed milliseconds, uint16 mV,
uint16 mA), totaling 345,608 bytes. Its separate 86,401-record mode-event log
also covers twelve hours at the maximum existing 500 ms status poll cadence;
8-byte events use 691,208 bytes. Static size assertions verify this allocation
contract. The combined source buffers use 1,036,816 PSRAM bytes; failed
allocation cannot enable a charge. Host tests use the same storage logic with
standard allocation rather than device PSRAM.

When the source-point buffer fills, progressive chronological min/max
compression retains the beginning and end of the session; it never becomes a
rolling window. Every bucket retains voltage and current extrema. The raw
twelve-hour guarantee applies before that compression. If the separate mode
log fills beyond its guaranteed duration/cadence budget, firmware explicitly
reports that it is full; normal charging/control continues.

Both plots cover the full elapsed-time span. Web uses at most 300 points;
tablet at most 240. Time buckets retain up to four chronological extrema
(voltage min/max and current min/max) plus session endpoints, so a smooth trace
can use fewer than the maximum points. Actual elapsed timestamps preserve gap
placement and irregular sample spacing. Connecting lines between samples are
interpolation, not additional measurements. Retained CC/CV/TR events are
separate from sample reduction. Dense mode events are grouped by display time
column; nearby labels are suppressed to prevent overlap while the raw event
log keeps their original timestamps. First reported charge mode is shown at
the lower left in white on black; subsequent events have gray vertical lines
and matching black/white mode labels. Initial trickle uses TR rather than
inventing CC or CV.

The exact LVGL 9.2.2 scatter implementation and `lv_map` source were inspected.
`lv_map` multiplies int32 coordinates, so raw long-session milliseconds can
overflow. Rendering converts original timestamps once into 0–1,000,000 parts
per million with uint64 intermediates. The stored times remain milliseconds.
Regression tests verify actual LVGL X coordinates across ten hours, not just
that data survives serialization. Series are opaque with rounded joins.

## Status, tiles and footer

The supplied IP2366 V1.13 register document, page 8, verifies 0x31 bits 2:0:
Standby 0, Trickle 1, CC 2, CV 3, Waiting 4, Full 5, Charging timeout 6;
7 is reserved. The read-only status decoder is in IP2366Control 1.2.2.
Successful existing status polls feed both screens; no extra I2C reads are
introduced. Detailed status appears on Charger/Configure even when idle and
above the graph. Fault, abort, completion and input-wait messages retain
priority on the graph. Invalid status reads display unavailable rather than
decoding unverified data.

The graph's top row now contains voltage, current and power tiles on the
tablet. Temperature and SOC are underneath. Web likewise orders Power between
Current and Temperature. Power is battery voltage_mV × current_mA / 1,000,000
in W; current remains the verified unsigned magnitude. Fine print is the
existing integrated delivered energy in mWh. The NTC tilde is removed. SOC
keeps its estimated label and gets a thin green/gray bar using the same
rounded percentage and existing 99% cap until accepted completion. Invalid
measurements make the bar gray.

The shared web footer says Connected or the connection failure, then Owner:
with TABLET, WEB or REMOTEHOST in a white rectangular outline. It tracks the
successful session's initiator, not the viewing client. Before any session it
shows --. Origin survives stop/configuration navigation until the next
successful Start. ESP-NOW heartbeat ownership and manual/web independence are
unchanged.

The false Summary warning during Starting/Charging is fixed. An explicit
stop-attempt flag gates the stop-verification warning. Genuine failed
stop-and-idle verification still warns, and successful recovery clears it.

## Web transport and validation

`/api/state` adds stage text/validity, session origin, stop-failure flag and
history revision. `/api/history` uses schema 2: timed `[elapsed_ms,mV,mA]`
points and independent `[elapsed_ms,mode]` events plus source counts,
duration/compression flags and revision. Since full-session reduction can
change earlier output points, a changed revision replaces the bounded plot;
an unchanged revision returns no arrays. This supersedes rolling-window
incremental append semantics. The 16,384-byte bounded JSON workspace covers
the worst-case projected arrays. Only reduced copies cross tasks; raw PSRAM
history is never copied into network snapshots. Browser request serialization,
read retries and independent radio pumping remain in place.

Validation includes controller/driver/GPIO/NVS regressions; ten-hour raw
retention and both-trace extrema; more than a day of progressive compaction;
72,001 independent mode events; LVGL ten-hour geometry and preview rendering;
CC/CV markers, SOC 99/100, unavailable readings, all documented/reserved
status codes, session origin and failed-stop warnings; typed JSON/browser
rendering; and existing ESP-NOW client/server ownership regressions.
Physical hardware was not flashed during development; ten-hour retention is
tested with simulated elapsed time, not a ten-hour physical charge.
