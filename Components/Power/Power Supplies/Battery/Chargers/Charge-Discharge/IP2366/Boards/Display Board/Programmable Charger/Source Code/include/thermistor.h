#pragma once
#include <stdint.h>
#include <math.h>

namespace batcharger {
static constexpr double NtcResistanceAt25C_ohm=10000.0;
static constexpr double NtcBeta_K=3850.0;
inline float ntcTemperature_C(uint16_t voltage_mV,uint8_t excitation_uA){
    if(!voltage_mV||voltage_mV>=3300||(excitation_uA!=20&&excitation_uA!=80))return NAN;
    const double resistance_ohm=double(voltage_mV)*1000/excitation_uA;
    return float(1.0/(1.0/298.15+log(resistance_ohm/NtcResistanceAt25C_ohm)/NtcBeta_K)-273.15);
}
} // namespace batcharger
