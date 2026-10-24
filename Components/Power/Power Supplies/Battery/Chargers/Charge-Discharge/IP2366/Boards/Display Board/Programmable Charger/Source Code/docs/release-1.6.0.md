# BatCharger 1.6.0 — stable mode markers and graph exports

## CC/CV marker chatter

Closely spaced CC/CV flags alone do not establish physical oscillation. The
reported test graph shows relatively smooth voltage/current alongside rapidly
changing stage flags. This release filters the **graph event log**, preserving
the live register status and every protection/control decision.

The initial TR/CC/CV mode appears immediately at the graph origin. A later mode
must be observed continuously for five seconds before it creates a gray vertical
line and label. Once confirmed, the marker uses the first observation's time,
not the end of the confirmation period. A return to the accepted mode, invalid
stage, inactive charging, failed status read or observation gap over one second
restarts confirmation. Ordinary status polling remains 500 ms.

The filter is shared before tablet/web history projections, so both graphs and
exports use the same markers. Raw register 0x31 status remains immediate above
the graph, on Configure/Charger and in Diagnostics. Short phase excursions are
omitted from the graph log; they are not retained as a separate raw event log.
Voltage/current samples are unchanged. Hardware completion, faults, input loss,
owner timeout and the software time limit are never delayed by this filter.

This is a presentation remedy, not a change to the IP2366 control loop or its
physical regulation. Physical instability would require measurement of the
voltage/current waveform before changing power-stage settings or components.

## Save as PNG / Save as PDF

The web Graph tab now has both buttons. They work during charging and with the
retained completed/stopped graph. Export is entirely browser-side from the
current bounded history snapshot, without fetching extra samples or blocking
the MCU control task. Buttons remain disabled until graph data is available.

Both formats contain:

- Voltage, current, power, temperature and SOC readings/bar.
- Chemistry, string count, cell voltage, target percentage, requested current
  and termination time.
- Full-session graph with voltage/current axis units, elapsed-time labels,
  charge-end/termination-current dotted lines and filtered mode markers.
- Elapsed time, delivered mAh/mWh, owner, state/reason and UTC capture timestamp.

PNG is a fixed 1600x1060 image. PDF embeds the same capture as a high-quality
8-bit RGB JPEG on one A4 landscape page (842x595 points), with aspect ratio
preserved. It is a raster PDF, not an editable vector plot. File names include
an ISO timestamp. No CDN, additional library or Internet connection is required.
WiFi credentials are not included. Export failures are reported in the web UI.

The implementation follows BW600's offscreen-canvas capture pattern. No
applicable web PDF exporter was found in the checked SMBus tablet-v25 source;
the small PDF writer was instead checked against Adobe's ISO 32000-1 reference.
Added embedded HTML/JS costs about 2.3 KB compressed compared with 1.5.0.

## Verified interfaces and validation

- Existing IP2366Control `Status::chargeStage()` contract and recorded register
  0x31 datasheet mapping: stages 1/2/3 are trickle/CC/CV. No register writes added.
- [Canvas export API](https://developer.mozilla.org/en-US/docs/Web/API/HTMLCanvasElement/toBlob):
  callback may return null; PNG is supported, JPEG type is checked, JPEG quality
  is supplied in the documented 0–1 range. Browser font readiness is awaited.
- [Adobe PDF 32000-1:2008](https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf):
  sections 7.5 (objects, byte-offset xref and trailer), 7.4.8 (DCTDecode), 8.9
  (image XObjects), and 8.3 (default user-space point units). Stream lengths and
  xref offsets count encoded bytes, including the JPEG binary data.

Controller, driver, settings, native LVGL fixtures, history/filter and shared
LabLink suites pass. Filter cases include rapid alternation, continuous phase
changes, gaps, invalid phases, reset and original-timestamp retention. A control
integration test verifies raw stage flags still update and completion immediately
disables during a pending transition. JavaScript tests verify fixed capture
dimensions, PDF byte offsets, invalid capture rejection and existing command
serialization/no-POST-replay behavior.

Actual PNG/PDF downloads were generated against the localhost charging fixture.
The PDF passes strict pypdf parsing and Poppler pdfinfo/rendering checks; both
images were visually reviewed. Sample exports and an export-controls screenshot
are in `docs/previews/`. ESP32-S3 release build passes. No hardware flashed and no
real charge started during validation. Reload the browser after uploading.
