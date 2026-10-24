# Charger revisions from testing — implemented in 1.4.0

Discussion record, 18 October 2026. The user authorized implementation after
finishing the requests. Implemented in 1.4.0; see release-1.4.0.md. The text
below records the original agreed requests.

## Full-session graph

- Replace the rolling 300-point window with a graph covering the entire charge.
- Retain one-second source history for at least 10 hours, using PSRAM.
- Allow at least 36,001 samples including both endpoints. Voltage/current as
  uint16 mV/mA plus uint32 elapsed milliseconds require about 288 KB.
- Preserve actual elapsed timestamps so gaps are represented correctly.
- Reduce the full history to at most 300 plotted points on the web and the
  tablet's display limit. Preserve relevant peaks/dips and event locations.
- Behavior beyond allocated capacity remains to be defined; never silently
  revert to a rolling window.

## Charger state and transitions

- Replace generic Charging with detailed status decoded from IP2366 0x31.
- Place status ABOVE the graph on tablet and web.
- Verify exact stage encodings/names against the supplied datasheet before
  implementation. Preserve fault/waiting-for-input priority.
- At graph start, show initial CC/CV mode at lower left, white text on black.
- Each confirmed CC-to-CV or CV-to-CC change gets a gray vertical line and a
  bottom black label with the new mode in white.
- Store transition timestamps separately from reduced graph points; preserve
  positions across full-session scaling. Handle nearby label overlap.

## SOC bar

- Thin progress bar directly below SOC on tablet and web graph screens.
- Green portion represents displayed estimated SOC; gray is the remainder.
- Follow existing 99% cap until confirmed completion; unavailable SOC is gray.

## Web footer ownership

- Replace Connected/control-and-protection wording with Connected or the
  relevant connection fault, then Owner: and a white rectangular outlined label.
- TABLET: started on tablet; WEB: started through browser; REMOTEHOST: ESP-NOW.
- Track session initiator independently of currently viewing client. Existing
  ESP-NOW owner-heartbeat stop policy does not change.

## Confirmed fix: false disable warning during charging

The current web Summary sets its warning whenever disableConfirmed is false.
That flag is deliberately false during normal Starting/Charging, so viewing
Summary while a charge is active produces a misleading warning.

- Show a stop-verification warning only after a stop was attempted and its
  verification failed, not during an active charge.
- Keep genuine failed-stop warnings. The existing flag covers chargerOff plus
  idle-configuration enforcement; it does not prove the enable bit stayed on.
- Add regression coverage for Summary during Starting/Charging and for an
  actual failed stop. Check that the warning clears after successful recovery.

Evidence checked in current source: session_controller.h sets
disableConfirmed=false on successful Start and verifies chargerOff plus
restore(false) on stop; web/index.html currently tests only the flag without
checking whether the session is active. No firmware changes made in this note.


## Additional requests included

- Remove the tilde before the graph temperature.
- Insert a Power tile after Current and before Temperature, with W and delivered mWh.
- Also show the decoded 0x31 status on Charger/Configure outside active charging.
- Capacity beyond twelve hours uses progressive full-span extrema compression;
  the original beginning is retained, not replaced by a rolling window.
