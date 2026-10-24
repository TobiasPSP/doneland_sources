# First-start input loss and diagnostic access — 1.0.2

User-reported symptom: first charge after tablet reboot briefly shows the graph, then automatically reaches Summary with "Charging input power lost". Subsequent starts work.

## Startup handshake

Previously successful enable readback immediately placed the application in the active Charging state. Any subsequent missing-input status was treated as loss of an established charging session. The observed report establishes the missing-input trigger; it does not independently establish the underlying electrical/PD renegotiation mechanism.

The application now distinguishes Starting from confirmed Charging:

1. Validate/apply settings and enable last as before, then enter Starting.
2. Before an active charge has been observed, a missing-input indication disables charging and waits for input, showing "Waiting for charging input" on the graph screen.
3. When input returns, reapply/verify the configuration while disabled and enable last. Require a subsequent valid active-charge status before entering Charging.
4. If active charging cannot be established within 10 seconds of the original Start, disable and latch "Charging startup timed out". This is an application deadline, not a claim about the IC's specified negotiation timing.
5. Hardware faults, failed I2C transactions/readbacks, and unexpected discharge remain immediate errors during startup. After Charging is confirmed, input loss still disables and latches "Charging input power lost". There is no automatic resume of a faulted established session.

Abort works during both Starting and Charging. Session elapsed time includes Starting, but charge/energy integration only uses confirmed charging measurements. This update does not clear fault/status flags or add guessed calibration.

## Diagnostics

Every screen now has a visible **DIAG** button at the upper right, including Configure, Summary and missing-device screens. The upper measurement tile on the graph remains a shortcut. Send `d` at 115200 baud over USB serial for the same snapshot.

The scrollable diagnostic view includes the first fault reason and captured status bytes, whether charger disable is confirmed, and the first failing I2C register/operation. A readback mismatch includes expected/actual/mask bytes. Later disable retries cannot overwrite the original fault reason. Raw NTC/current fields are available when a valid measurement exists; an early startup failure still exposes fault diagnostics without a sample.

Captured fault status bytes are the most recently acquired values when the application first faults; they are not guaranteed to be one atomic hardware snapshot. Status preceding a failed read can be stale. Readback-mismatch expected/actual fields are meaningful only for a recorded readback mismatch.

Native regressions cover startup input loss/recovery, disabled-first reconfiguration, subsequent active-charge confirmation, startup timeout, immediate startup hardware faults, established-session loss, and preservation of the first fault. Physical verification of this fix remains pending.
