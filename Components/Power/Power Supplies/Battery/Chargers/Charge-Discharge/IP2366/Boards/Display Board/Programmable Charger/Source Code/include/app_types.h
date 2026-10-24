#pragma once
#include <stdint.h>
#include <math.h>
#include "session_history.h"

namespace batcharger {
enum class Chemistry { None, Lfp, LiIon, LiHV };
enum class State { Missing, Configure, Starting, Charging, Complete, Aborted, Fault };
enum class SessionOrigin:uint8_t {None,Tablet,Web,RemoteHost};
inline const char *originName(SessionOrigin origin){return origin==SessionOrigin::Tablet?"TABLET":origin==SessionOrigin::Web?"WEB":origin==SessionOrigin::RemoteHost?"REMOTEHOST":"--";}
struct Config {
    Chemistry chemistry=Chemistry::None;
    uint8_t cells=0, percent=100;
    uint16_t cell_mV=4200, current_mA=1000, termination_mA=100;
    uint16_t terminationTime_min=360; // Software session limit, integer minutes (1..65535).
};
inline uint16_t full_mV(Chemistry c) {return c==Chemistry::Lfp?3650:c==Chemistry::LiHV?4400:4200;}
inline uint16_t low_mV(Chemistry c) {return c==Chemistry::Lfp?2500:3000;}
inline const char *chemistryName(Chemistry c) {
    return c==Chemistry::Lfp?"LiFePO4":c==Chemistry::LiIon?"Li-ion":c==Chemistry::LiHV?"LiHV":"Select chemistry";
}
struct Measurement {
    uint16_t voltage_mV=0,current_mA=0,ntc_mV=0; // Corrected pack telemetry.
    uint16_t raw_voltage_mV=0,raw_current_mA=0; // Unmodified IP2366 ADC for protection/diagnostics.
    uint16_t configured_current_mA=0;
    uint8_t excitation_uA=0,current_limit_code=0,ntc_bias_before=0,ntc_bias_after=0;
    bool excitation_stable=false;
    float temperature_C=NAN;
    bool valid=false;
};
struct Totals {
    double charge_mAh=0,energy_mWh=0;
    uint64_t elapsed_ms=0,missing_ms=0;
};
} // namespace batcharger
