#pragma once
#include "session_controller.h"
#include "version.h"
#include <stdio.h>

namespace batcharger {
inline void diagnosticText(const Controller &ctl,char *text,size_t size){
    const auto &m=ctl.measurement;
    const char *kind=ctl.failureKind==1?"read failed":ctl.failureKind==2?"write failed":ctl.failureKind==3?"readback mismatch":ctl.failureKind==4?"invalid settings":ctl.failureKind==5?"not configured":"none";
    size_t used=size_t(snprintf(text,size,
        "BatCharger %s\nSOC curves: LFP/ion 1C; HV 0.5C\nReason: %s\nBoot defaults: %s\nProfile save failed: %s\nDisable confirmed: %s\nFirst I/O issue: %s\nRegister: 0x%02X\nExpected/actual/mask: %02X/%02X/%02X\n"
        "Fault status 31/33/34/38:\n%02X / %02X / %02X / %02X\n",
        FirmwareVersion,ctl.message,ctl.bootProfileMatched?"matching saved profile":ctl.bootDefaultsAvailable?"registers only":"none",
        ctl.profileSaveFailed?"yes":"no",ctl.disableConfirmed?"yes":"no",kind,ctl.failureReg,ctl.failureExpected,ctl.failureActual,ctl.failureMask,
        ctl.fault31,ctl.fault33,ctl.fault34,ctl.fault38));
    if(used>=size)return;
    if(!m.valid){snprintf(text+used,size-used,"No valid measurement sample");return;}
    double resistance_ohm=double(m.ntc_mV)*1000/m.excitation_uA;
    const double t20=ntcTemperature_C(m.ntc_mV,20),t80=ntcTemperature_C(m.ntc_mV,80);
    snprintf(text+used,size-used,
        "Battery ADC: %u mV\nCurrent ADC: %u mA\nCorrected: %u mV / %u mA\n0x03: 0x%02X = %u mA\n"
        "0x31/33: %02X / %02X\n0x77 before/after: %02X / %02X\n"
        "Bias: %u uA (%s)\nNTC ADC: %u mV\nInferred R: %.0f ohm\n"
        "10k / B3850 NTC:\nT at 20uA: %.1f C\nT at 80uA: %.1f C",
        m.raw_voltage_mV,m.raw_current_mA,m.voltage_mV,m.current_mA,m.current_limit_code,m.configured_current_mA,ctl.status31,ctl.status33,
        m.ntc_bias_before,m.ntc_bias_after,m.excitation_uA,m.excitation_stable?"stable":"changed",m.ntc_mV,resistance_ohm,t20,t80);
}
} // namespace batcharger
