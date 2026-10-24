#pragma once
#include <stdint.h>
namespace batcharger {
// Main-task session lease. Telemetry/subscriber traffic never renews ownership.
class LabOwnership {
    uint64_t device_=0;uint32_t boot_=0,session_=0,lastHeartbeat_ms_=0,lastSequence_=0;
public:
    static constexpr uint32_t Timeout_ms=10000;
    uint64_t deviceId()const{return device_;}
    uint32_t bootId()const{return boot_;}
    uint32_t sessionId()const{return session_;}
    bool owned()const{return device_!=0;}
    void clear(){device_=0;boot_=session_=lastHeartbeat_ms_=lastSequence_=0;}
    void claim(uint64_t device,uint32_t boot,uint32_t session,uint32_t sequence,uint32_t now_ms){
        device_=device;boot_=boot;session_=session;lastSequence_=sequence;lastHeartbeat_ms_=now_ms;
    }
    void observe(uint32_t session,bool active){if(device_&&(!active||session!=session_))clear();}
    bool heartbeat(uint64_t device,uint32_t boot,uint32_t session,uint32_t sequence,uint32_t now_ms){
        if(!device_||device!=device_||boot!=boot_||session!=session_||int32_t(sequence-lastSequence_)<=0)return false;
        // A late heartbeat must not revive a lease whose deadline already expired.
        if(int32_t(now_ms-lastHeartbeat_ms_)<0||expired(now_ms))return false;
        lastSequence_=sequence;lastHeartbeat_ms_=now_ms;return true;
    }
    bool expired(uint32_t now_ms)const{return device_&&uint32_t(now_ms-lastHeartbeat_ms_)>=Timeout_ms;}
    uint32_t age_ms(uint32_t now_ms)const{return device_?uint32_t(now_ms-lastHeartbeat_ms_):0;}
};
} // namespace batcharger
