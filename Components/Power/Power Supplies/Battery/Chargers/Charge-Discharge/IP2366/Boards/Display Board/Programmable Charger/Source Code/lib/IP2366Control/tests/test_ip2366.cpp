// Standalone library test: intentionally does not include any application header.
#include <IP2366.h>
#include "fake_transport.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
using namespace ip2366;
using fixtures::Fake;
static Settings settings(){
    Settings s;s.cells=3;s.target_cell_mV=4200;s.charge_current_mA=1000;return s;
}
int main(){
    Settings s=settings();assert(!IP2366::validateSettings(s));
    Fake bus;bus.registers[0x09]=0xBF;IP2366 chip(bus);assert(chip.begin());assert(!(bus.registers[0]&1));
    assert(bus.registers[0x09]==0x3F); // bit7 only; preserve low-voltage/reserved bits
    bus.registers[0x09]=0xBF;assert(chip.applyIdleConfiguration()&&bus.registers[0x09]==0x3F);
    bus.writes.clear();assert(!chip.chargerOn());assert(bus.writes.empty());
    assert(chip.failure().kind==FailureKind::NotConfigured);chip.clearFailure();
    Settings invalid=s;invalid.cells=7;assert(IP2366::validateSettings(invalid));
    assert(!chip.configureCharger(invalid)&&bus.writes.empty());chip.clearFailure();
    invalid=s;invalid.target_cell_mV=4401;assert(IP2366::validateSettings(invalid));
    invalid=s;invalid.charge_current_mA=1050;assert(IP2366::validateSettings(invalid));
    invalid=s;invalid.charge_current_mA=9800;assert(IP2366::validateSettings(invalid));
    invalid=s;invalid.termination_current_mA=0;assert(IP2366::validateSettings(invalid));
    invalid=s;invalid.termination_current_mA=750;invalid.charge_current_mA=200;assert(IP2366::validateSettings(invalid));
    invalid=s;invalid.battery_low_cell_mV=2550;assert(IP2366::validateSettings(invalid));
    invalid=s;invalid.precharge_current_mA=50;assert(IP2366::validateSettings(invalid));
    invalid=s;invalid.power_limit_W=99;assert(IP2366::validateSettings(invalid));
    assert(chip.configureCharger(s));assert(!(bus.registers[0]&1));
    assert(bus.registers[0x02]==170&&bus.registers[0x03]==10&&bus.registers[0x04]==0xA3);
    assert(bus.registers[0x06]==2&&bus.registers[0x08]==0x23&&bus.registers[0x0A]==0xBF);
    assert(bus.registers[0x0B]==0x7F&&bus.registers[0x0C]==0xBB&&bus.registers[0x22]==0x3F);
    assert(chip.chargerOn()&&(bus.registers[0]&1));assert(chip.chargerOff()&&!(bus.registers[0]&1));
    uint16_t voltage_mV=0,current_mA=0,target_cell_mV=0,limit_mA=0;uint8_t limit_code=0;
    bus.word(0x50,13553);bus.word(0x6E,1097);
    assert(chip.readVoltage(voltage_mV)&&voltage_mV==13553);
    assert(chip.readCurrent(current_mA)&&current_mA==1097);
    assert(chip.readTargetVoltage(target_cell_mV)&&target_cell_mV==4200);
    assert(chip.readChargeCurrentLimit(limit_mA,&limit_code)&&limit_mA==1000&&limit_code==0x0A);
    bus.registers[0x77]=0x80;bus.word(0x78,863);NtcReading ntc;
    assert(chip.readNtc(ntc)&&ntc.voltage_mV==863&&ntc.excitation_uA==80&&ntc.excitation_stable);
    for(size_t i=0;i<bus.reads.size();++i)if(bus.reads[i]==0x51||bus.reads[i]==0x6F||bus.reads[i]==0x79){assert(i&&bus.reads[i-1]+1==bus.reads[i]);}
    assert(chip.readStatus()&&chip.status().chargingActive()&&chip.status().inputPresent());
    bus.registers[0x04]=0xA6;bus.writes.clear();assert(chip.enforceSettings(s,true));
    assert(bus.writes.back().reg==0x00&&(bus.writes.back().value&1));
    assert(bus.registers[0x04]==0xA3&&chip.configurationChanged());
    bus.registers[0x04]=0xA6;bus.registers[0x31]=0x35;assert(chip.enforceSettings(s,true));
    assert(chip.completionDetected()&&!(bus.registers[0]&1));
    bus.registers[0x31]=0x22;bus.registers[0x33]=0;bus.registers[0x04]=0xA6;bus.writes.clear();
    assert(!chip.enforceSettings(s,true));for(auto w:bus.writes)if(w.reg==0)assert(!(w.value&1));
    for(auto w:bus.writes)assert(w.reg!=0x31&&w.reg!=0x33&&w.reg!=0x34&&w.reg!=0x38&&w.reg!=0x77);
    struct WrongReadback:Fake {bool write(uint8_t reg,uint8_t value)override{
        if(reg==0x04){writes.push_back({reg,0xFF,value});return true;}return Fake::write(reg,value);}} broken;
    IP2366 mismatch(broken);assert(mismatch.begin());assert(!mismatch.configureCharger(s));
    assert(mismatch.failure().kind==FailureKind::Readback&&mismatch.failure().reg==0x04&&mismatch.failure().mask==7);
    assert(!(broken.registers[0]&1)&&!mismatch.chargerOn());
    Fake absent;absent.online=false;IP2366 missing(absent);assert(!missing.begin()&&absent.recoveries==1);
    // Boot snapshot precedes begin(): no writes and no control-bit mutation.
    Fake running;running.registers[0]=0x1D;running.registers[0x02]=170;
    running.registers[0x03]=10;running.registers[0x04]=0xAB;running.registers[0x08]=0x23;
    running.word(0x6E,1097);IP2366 beforeBoot(running);ChargingSnapshot snapshot;
    assert(beforeBoot.readChargingSnapshot(snapshot)&&snapshot.active);
    assert(snapshot.measured_current_mA==1097&&snapshot.settings.cells==3);
    assert(snapshot.settings.target_cell_mV==4200&&snapshot.settings.charge_current_mA==1000&&snapshot.settings.termination_current_mA==100);
    assert(running.writes.empty()&&(running.registers[0]&1));
    assert(beforeBoot.begin()&&!(running.registers[0]&1));
    assert(beforeBoot.readChargingSnapshot(snapshot)&&!snapshot.active);
    running.registers[0]|=1;running.word(0x6E,0);running.writes.clear();
    assert(beforeBoot.readChargingSnapshot(snapshot)&&!snapshot.active&&running.writes.empty());
    running.word(0x6E,200);running.registers[0x04]=0xA7;
    assert(!beforeBoot.readChargingSnapshot(snapshot)&&running.writes.empty());
    running.registers[0x04]=0xA3;running.readFailure=true;
    assert(!beforeBoot.readChargingSnapshot(snapshot)&&running.writes.empty());
    // Each failed message is immediately followed by a probe, including the
    // sixth. Probe ACKs do not reset the message streak. No partial read output.
    Fake unplugged;IP2366 disconnected(unplugged);assert(disconnected.begin());
    unplugged.online=false;unplugged.probes=0;unplugged.reads.clear();voltage_mV=1234;
    assert(!disconnected.readVoltage(voltage_mV)&&voltage_mV==1234);
    assert(unplugged.probes==1&&unplugged.reads.size()==1);
    assert(disconnected.communicationFault()==CommunicationFault::Disconnected);
    assert(!strcmp(disconnected.communicationWarning(),"IP2366 was disconnected."));
    Fake noisy;IP2366 unstable(noisy);assert(unstable.begin());noisy.readFailure=true;
    noisy.probes=0;noisy.reads.clear();assert(!unstable.readVoltage(voltage_mV));
    assert(noisy.reads.size()==6&&noisy.probes==6);
    assert(unstable.communicationFault()==CommunicationFault::Unstable);
    assert(!strcmp(unstable.communicationWarning(),"IP2366 communication instable"));
    struct Transient:Fake {
        unsigned remaining=0,attempts=0;bool awaitingProbe=false;
        bool read(uint8_t reg,uint8_t &value)override{
            assert(!awaitingProbe);++attempts;
            if(remaining){--remaining;awaitingProbe=true;return false;}
            return Fake::read(reg,value);
        }
        bool probe()override{awaitingProbe=false;return Fake::probe();}
    } transient;
    IP2366 retry(transient);assert(retry.begin());
    for(unsigned failures:{1u,5u}){
        transient.remaining=failures;transient.probes=transient.attempts=0;
        assert(retry.readVoltage(voltage_mV)&&voltage_mV==12000);
        assert(transient.probes==failures&&transient.attempts==failures+2);
        assert(retry.communicationFault()==CommunicationFault::None&&retry.failure().kind==FailureKind::None);
    }
    Fake badWrite;IP2366 writeRetry(badWrite);assert(writeRetry.begin());
    badWrite.registers[0]|=1;badWrite.writeFailure=true;badWrite.probes=0;badWrite.writes.clear();
    assert(!writeRetry.chargerOff()&&badWrite.writes.size()==6&&badWrite.probes==6);
    assert(writeRetry.failure().kind==FailureKind::Write&&writeRetry.communicationFault()==CommunicationFault::Unstable);
    badWrite.online=false;assert(!writeRetry.chargerOff());
    assert(writeRetry.communicationFault()==CommunicationFault::Disconnected); // disconnect takes priority
    puts("PASS: standalone IP2366 API, settings validation, explicit-unit reads, masks, ordering, off/on/configure, fault-safe enforcement and readback errors");
}
