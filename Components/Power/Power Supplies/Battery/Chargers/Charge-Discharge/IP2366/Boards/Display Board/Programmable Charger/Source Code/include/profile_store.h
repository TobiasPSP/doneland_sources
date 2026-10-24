#pragma once
#include "settings.h"
#include <string.h>

namespace batcharger {
class ProfileStore {
public:
    virtual bool load(Config &config)=0;
    virtual bool save(const Config &config)=0;
    virtual ~ProfileStore()=default;
};

// Versioned, padding-independent byte contract. All voltages/currents are
// unsigned little-endian mV/mA. Four-byte FNV-1a detects corrupt records.
struct ProfileRecord {
    static constexpr size_t Size=18;
    uint8_t bytes[Size]={};
    static uint32_t checksum(const uint8_t *data){
        uint32_t value=2166136261u;
        for(size_t i=0;i<14;++i){value^=data[i];value*=16777619u;}return value;
    }
    bool encode(const Config &c){
        if(unsigned(c.chemistry)<1||unsigned(c.chemistry)>3||validate(c))return false;
        // v2 reuses the two v1 reserved bytes for little-endian minutes, keeping
        // the record size/embedded settings offsets stable. v1 restores 360 min.
        bytes[0]='B';bytes[1]='C';bytes[2]=2;bytes[3]=uint8_t(c.terminationTime_min);
        bytes[4]=uint8_t(c.chemistry);bytes[5]=c.cells;bytes[6]=c.percent;bytes[7]=uint8_t(c.terminationTime_min>>8);
        const uint16_t fields[]={c.cell_mV,c.current_mA,c.termination_mA};
        for(unsigned i=0;i<3;++i){bytes[8+i*2]=uint8_t(fields[i]);bytes[9+i*2]=uint8_t(fields[i]>>8);}
        uint32_t hash=checksum(bytes);for(unsigned i=0;i<4;++i)bytes[14+i]=uint8_t(hash>>(i*8));
        return true;
    }
    bool decode(Config &out)const{
        if(bytes[0]!='B'||bytes[1]!='C'||(bytes[2]!=1&&bytes[2]!=2)||
            (bytes[2]==1&&(bytes[3]||bytes[7]))||bytes[4]<1||bytes[4]>3)return false;
        uint32_t hash=0;for(unsigned i=0;i<4;++i)hash|=uint32_t(bytes[14+i])<<(i*8);
        if(hash!=checksum(bytes))return false;
        Config c;c.chemistry=Chemistry(bytes[4]);c.cells=bytes[5];c.percent=bytes[6];
        if(bytes[2]==2)c.terminationTime_min=uint16_t(bytes[3])|(uint16_t(bytes[7])<<8);
        c.cell_mV=uint16_t(bytes[8])|(uint16_t(bytes[9])<<8);
        c.current_mA=uint16_t(bytes[10])|(uint16_t(bytes[11])<<8);
        c.termination_mA=uint16_t(bytes[12])|(uint16_t(bytes[13])<<8);
        if(validate(c))return false;out=c;return true;
    }
};
inline bool matchesSnapshot(const Config &c,const ip2366::ChargingSnapshot &snapshot){
    if(!snapshot.active||unsigned(c.chemistry)<1||unsigned(c.chemistry)>3||validate(c))return false;
    const auto expected=deviceSettings(c);const auto &actual=snapshot.settings;
    return expected.cells==actual.cells&&expected.target_cell_mV==actual.target_cell_mV&&
        expected.charge_current_mA==actual.charge_current_mA&&expected.termination_current_mA==actual.termination_current_mA;
}
} // namespace batcharger
