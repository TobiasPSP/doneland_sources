#pragma once
#include <IP2366.h>
#include <vector>

namespace fixtures {
struct RegisterWrite {uint8_t reg,mask,value;};
struct Fake:ip2366::Transport {
    uint8_t registers[256]={};
    bool online=true,readFailure=false,writeFailure=false;
    unsigned recoveries=0,probes=0;
    std::vector<RegisterWrite> writes;
    std::vector<uint8_t> reads;
    Fake(){
        registers[0x00]=0xFF;registers[0x0B]=0xFF;registers[0x04]=0xA4;registers[0x08]=3;
        registers[0x0A]=0x1F;registers[0x0C]=0x1B;registers[0x22]=0x3F;
        registers[0x33]=0x80;registers[0x34]=0x90;registers[0x31]=0x22;
        word(0x50,12000);word(0x6E,1000);word(0x78,200);
    }
    void word(uint8_t reg,uint16_t value){registers[reg]=value&255;registers[reg+1]=value>>8;}
    bool read(uint8_t reg,uint8_t &value)override{reads.push_back(reg);if(!online||readFailure)return false;value=registers[reg];return true;}
    bool write(uint8_t reg,uint8_t value)override{writes.push_back({reg,0xFF,value});if(!online||writeFailure)return false;registers[reg]=value;return true;}
    bool probe()override{++probes;return online;}
    bool recover()override{++recoveries;return online;}
};
} // namespace fixtures
