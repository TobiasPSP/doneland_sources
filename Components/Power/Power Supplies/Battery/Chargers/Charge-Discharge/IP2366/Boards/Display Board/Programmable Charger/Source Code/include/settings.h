#pragma once
#include <IP2366.h>
#include "soc.h"
#include "charger_limits.h"

namespace batcharger {
inline uint16_t target_mV(const Config &c) {
    // Hardware CV target per cell, quantized downward to the IP2366 10 mV step.
    if(c.percent==100)return c.cell_mV;
    float v=lookup(c.chemistry,c.percent,true);if(v>c.cell_mV)v=c.cell_mV;
    return uint16_t(v/10)*10;
}
inline uint16_t limitedCurrent_mA(const Config &c) {
    uint32_t pack_mV=uint32_t(target_mV(c))*c.cells;
    if(!pack_mV)return 0;
    // 100 W = 100,000,000 mV*mA. Downward quantization to 100 mA.
    uint32_t limit_mA=(100000000u/pack_mV)/100*100;
    if(limit_mA>9700)limit_mA=9700;
    return uint16_t(c.current_mA<limit_mA?c.current_mA:limit_mA);
}
inline ip2366::Settings deviceSettings(const Config &config) {
    ip2366::Settings result;
    result.cells=config.cells;
    result.target_cell_mV=target_mV(config);
    result.charge_current_mA=limitedCurrent_mA(config);
    result.termination_current_mA=config.termination_mA;
    result.precharge_current_mA=100;
    result.battery_low_cell_mV=low_mV(config.chemistry);
    result.power_limit_W=140;
    return result;
}
inline const char *validate(const Config &c) {
    if(c.chemistry<Chemistry::Lfp||c.chemistry>Chemistry::LiHV)return "Select a chemistry";
    if(c.cells<limits::CellsMin||c.cells>limits::CellsMax)return "Select 2S through 6S";
    if(c.cell_mV<limits::CellMin_mV||c.cell_mV>limits::CellMax_mV||c.cell_mV%limits::CellStep_mV)return "Cell voltage: 2500-4400 mV, steps of 10";
    if(c.percent>limits::PercentMax||c.percent%limits::PercentStep)return "Charge level: 0-100%, steps of 10";
    if(!c.terminationTime_min)return "Termination time: 1-65535 minutes";
    if(c.current_mA<limits::CurrentMin_mA||c.current_mA>limits::CurrentMax_mA||c.current_mA%limits::CurrentStep_mA)return "Charge current: 100-9700 mA, steps of 100";
    if(c.termination_mA<limits::TerminationMin_mA||c.termination_mA>limits::TerminationMax_mA||c.termination_mA%limits::TerminationStep_mA)return "Termination: 50-750 mA, steps of 50";
    if(c.current_mA<c.termination_mA)return "Charge current is below termination current";
    if(target_mV(c)<2500||target_mV(c)>4400)return "SOC target is outside the chip voltage range";
    if(limitedCurrent_mA(c)<c.termination_mA)return "100 W current limit is below termination current";
    return ip2366::IP2366::validateSettings(deviceSettings(c));
}
} // namespace batcharger
