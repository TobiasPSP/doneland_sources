#include "IP2366.h"

namespace ip2366 {
const char *Status::faultReason()const{
    if(faults&0x10)return "IP2366 short-circuit fault";
    if(faults&0x20)return "IP2366 overcurrent fault";
    if(input&0x40)return "Input overvoltage";
    if((charge&7)==6)return "Charging timeout";
    return nullptr;
}

uint8_t IP2366::powerCode(uint16_t power_W){
    switch(power_W){case 30:return 0;case 45:return 1;case 60:return 2;case 65:return 3;case 100:return 4;case 140:return 5;default:return 0xFF;}
}
const char *IP2366::validateSettings(const Settings &s){
    if(s.cells<2||s.cells>6)return "Select 2S through 6S";
    if(s.target_cell_mV<2500||s.target_cell_mV>4400||s.target_cell_mV%10)return "Cell voltage: 2500-4400 mV, steps of 10";
    if(s.charge_current_mA<100||s.charge_current_mA>9700||s.charge_current_mA%100)return "Charge current: 100-9700 mA, steps of 100";
    if(s.termination_current_mA<50||s.termination_current_mA>750||s.termination_current_mA%50)return "Termination: 50-750 mA, steps of 50";
    if(s.charge_current_mA<s.termination_current_mA)return "Charge current is below termination current";
    if(s.precharge_current_mA<100||s.precharge_current_mA>1000||s.precharge_current_mA%50)return "Precharge: 100-1000 mA, steps of 50";
    if(s.battery_low_cell_mV<2500||s.battery_low_cell_mV>3200||s.battery_low_cell_mV%100)return "Battery low: 2500-3200 mV, steps of 100";
    if(powerCode(s.power_limit_W)==0xFF)return "Unsupported IP2366 power selection";
    return nullptr;
}

bool IP2366::readRegister(uint8_t reg,uint8_t &value){
    do {
        uint8_t next;
        if(transport_.read(reg,next)){value=next;consecutive_failures_=0;return true;}
    }while(failedTransaction(FailureKind::Read,reg));
    return false;
}
bool IP2366::writeRegister(uint8_t reg,uint8_t value){
    do {
        if(transport_.write(reg,value)){consecutive_failures_=0;return true;}
    }while(failedTransaction(FailureKind::Write,reg));
    return false;
}
bool IP2366::failedTransaction(FailureKind kind,uint8_t reg){
    // Probe the configured 7-bit address (tablet: 0x75) after EVERY failed
    // register transfer. A successful address ACK does not reset the streak.
    if(consecutive_failures_<6)++consecutive_failures_;
    if(!transport_.probe())communication_fault_=CommunicationFault::Disconnected;
    else if(consecutive_failures_>=6&&communication_fault_!=CommunicationFault::Disconnected)
        communication_fault_=CommunicationFault::Unstable;
    else if(consecutive_failures_<6)return true;
    if(failure_.kind==FailureKind::None){failure_.kind=kind;failure_.reg=reg;}
    return false;
}
const char *IP2366::communicationWarning()const{
    if(communication_fault_==CommunicationFault::Disconnected)return "IP2366 was disconnected.";
    if(communication_fault_==CommunicationFault::Unstable)return "IP2366 communication instable";
    return nullptr;
}
bool IP2366::readPair(uint8_t low,uint16_t &value){
    uint8_t l,h;if(!readRegister(low,l)||!readRegister(low+1,h))return false;
    value=uint16_t(h)<<8|l;return true;
}
bool IP2366::updateField(const Field &f){
    uint8_t old;if(!readRegister(f.reg,old))return false;
    uint8_t value=(old&uint8_t(~f.mask))|(f.value&f.mask);
    if(value==old)return true;
    if(!writeRegister(f.reg,value))return false;
    ++corrections_;uint8_t check;
    if(!readRegister(f.reg,check))return false;
    if(((check^value)&f.mask)==0)return true;
    if(failure_.kind==FailureKind::None){
        failure_.kind=FailureKind::Readback;failure_.reg=f.reg;
        failure_.expected=value;failure_.actual=check;failure_.mask=f.mask;
    }
    return false;
}

size_t IP2366::fields(const Settings *s,bool enable,Field *out){
    size_t n=0;
    out[n++]={0x22,0xC0,0};              // UFP, preserve lower bits
    out[n++]={0x0B,0xF0,0x70};          // No discharge, source protocol flags retained
    out[n++]={0x0C,0xE0,uint8_t(powerCode(s?s->power_limit_W:140)<<5)};
    out[n++]={0x09,0x80,0};             // SYS_CTL9: disable automatic standby
    if(s){
        out[n++]={0x02,0xFF,uint8_t((s->target_cell_mV-2500)/10)};
        out[n++]={0x03,0xFF,uint8_t(s->charge_current_mA/100)};
        out[n++]={0x04,0x07,s->cells};
        out[n++]={0x06,0xFF,uint8_t(s->precharge_current_mA/50)};
        out[n++]={0x08,0xFC,uint8_t((s->termination_current_mA/50)<<4)}; // no auto-recharge
        out[n++]={0x0A,0xE0,uint8_t(((s->battery_low_cell_mV-2500)/100)<<5)};
    }
    out[n++]={0x00,0xFD,uint8_t(0x1C|(enable?1:0))}; // Enable last; preserve bit 1
    return n;
}

bool IP2366::begin(){
    clearFailure();configured_=false;completion_detected_=configuration_changed_=false;status_=Status{};
    if(!transport_.probe()&&!(transport_.recover()&&transport_.probe()))return false;
    return chargerOff()&&applyIdleConfiguration();
}
bool IP2366::chargerOff(){return updateField({0x00,0x01,0});}
bool IP2366::chargerOn(){
    if(!configured_){if(failure_.kind==FailureKind::None)failure_.kind=FailureKind::NotConfigured;return false;}
    return updateField({0x00,0xFD,0x1D});
}
bool IP2366::configureCharger(const Settings &settings){
    if(validateSettings(settings)){
        if(failure_.kind==FailureKind::None)failure_.kind=FailureKind::InvalidSettings;return false;
    }
    configured_=false;
    return chargerOff()&&enforce(&settings,false);
}
bool IP2366::enforceSettings(const Settings &settings,bool enable){return enforce(&settings,enable);}
bool IP2366::applyIdleConfiguration(){return enforce(nullptr,false);}
bool IP2366::enforce(const Settings *s,bool enable){
    completion_detected_=configuration_changed_=false;
    if(s&&validateSettings(*s)){
        if(failure_.kind==FailureKind::None)failure_.kind=FailureKind::InvalidSettings;return false;
    }
    Field wanted[12];size_t n=fields(s,enable,wanted);bool mismatch=false;
    for(size_t i=0;i<n;++i){uint8_t value;if(!readRegister(wanted[i].reg,value))return false;
        mismatch|=((value^wanted[i].value)&wanted[i].mask)!=0;}
    if(!mismatch){if(s)configured_=true;return true;}
    configuration_changed_=true;configured_=false;
    if(!chargerOff())return false;
    for(size_t i=0;i<n-1;++i)if(!updateField(wanted[i]))return false;
    if(enable){
        if(!readStatus()||status_.faultReason()||!status_.inputPresent())return false;
        if(status_.chargeComplete()){
            completion_detected_=true;if(s)configured_=true;return true;
        }
    }
    if(!updateField(wanted[n-1]))return false;
    if(s)configured_=true;return true;
}

bool IP2366::readVoltage(uint16_t &voltage_mV){return readPair(0x50,voltage_mV);}
bool IP2366::readCurrent(uint16_t &current_mA){return readPair(0x6E,current_mA);}
bool IP2366::readChargingSnapshot(ChargingSnapshot &snapshot){
    ChargingSnapshot next;uint8_t system,cells,termination;
    if(!readRegister(0x00,system))return false;
    if(!(system&1)){snapshot=next;return true;}
    if(!readCurrent(next.measured_current_mA))return false;
    if(!next.measured_current_mA){snapshot=next;return true;}
    if(!readTargetVoltage(next.settings.target_cell_mV)||
       !readChargeCurrentLimit(next.settings.charge_current_mA)||
       !readRegister(0x04,cells)||!readRegister(0x08,termination))return false;
    next.settings.cells=cells&0x07;
    next.settings.termination_current_mA=uint16_t(termination>>4)*50;
    if(validateSettings(next.settings))return false;
    if(!readRegister(0x00,system)||!readCurrent(next.measured_current_mA))return false;
    next.active=(system&1)&&next.measured_current_mA>0;
    snapshot=next;return true;
}
bool IP2366::readTargetVoltage(uint16_t &target_cell_mV){
    uint8_t code;if(!readRegister(0x02,code))return false;target_cell_mV=uint16_t(code)*10+2500;return true;
}
bool IP2366::readChargeCurrentLimit(uint16_t &current_mA,uint8_t *raw_code){
    uint8_t code;if(!readRegister(0x03,code))return false;
    current_mA=uint16_t(code)*100;if(raw_code)*raw_code=code;return true;
}
bool IP2366::readStatus(){
    // Partial updates are intentionally retained for failure diagnostics. A false
    // return means this is NOT a complete/fresh four-register observation.
    return readRegister(0x31,status_.charge)&&readRegister(0x33,status_.input)&&
        readRegister(0x34,status_.typeC)&&readRegister(0x38,status_.faults);
}
bool IP2366::readNtc(NtcReading &reading){
    NtcReading next;
    if(!readRegister(0x77,next.bias_before)||!readPair(0x78,next.voltage_mV)||!readRegister(0x77,next.bias_after))return false;
    next.excitation_uA=(next.bias_after&0x80)?80:20;
    next.excitation_stable=((next.bias_before^next.bias_after)&0x80)==0;
    reading=next;return true;
}
} // namespace ip2366
