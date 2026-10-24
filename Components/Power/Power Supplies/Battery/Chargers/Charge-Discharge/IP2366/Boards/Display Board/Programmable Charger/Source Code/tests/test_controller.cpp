#include "charger.h"
#include "app_options.h"
#include "fake_transport.h"
#include <vector>
#include <assert.h>
#include <string.h>
#include <stdio.h>
using namespace batcharger;
using fixtures::Fake;
static Config config(){Config c;c.chemistry=Chemistry::LiIon;c.cells=3;return c;}
static void equal(double value,double expected,double tolerance=0.00001){assert(fabs(value-expected)<tolerance);}
static bool hasWrite(const Fake &f,uint8_t reg){for(auto w:f.writes)if(w.reg==reg)return true;return false;}
int main(){
    equal(targetProgress_percent(60,70),85.7142857,0.001);
    equal(targetProgress_percent(80,70),100);equal(targetProgress_percent(0,0),100);
    equal(targetProgress_percent(NAN,70),0);
    assert(displayedSoc_percent(100,false)==99);
    assert(displayedSoc_percent(99.6f,false)==99);
    assert(displayedSoc_percent(100,true)==100);
    assert(displayedSoc_percent(80,true)==80);
    assert(displayedSoc_percent(45.5f,false)==45.5f);
    assert(displayedSoc_percent(72,false,70)==69);
    assert(displayedSoc_percent(69.6f,false,70)==69);
    assert(displayedSoc_percent(60,false,70)==60);
    assert(displayedSoc_percent(72,true,70)==70);
    assert(displayedSoc_percent(0,false,0)==0);
    assert(displayedSoc_percent(1,true,0)==0);
    assert(Config{}.terminationTime_min==360);
    // Mode-marker filtering is not a control debounce: raw flags remain current,
    // and a completion report disables immediately during a pending transition.
    Fake chatterBus;Controller chatter(chatterBus);assert(chatter.initialize(0));
    assert(chatter.start(config(),false,0)==Controller::StartResult::Started);
    for(uint32_t at=500;at<=10000;at+=500){chatterBus.registers[0x31]=at%1000?0x22:0x23;chatter.tick(at);assert(chatter.status31==chatterBus.registers[0x31]);}
    assert(chatter.history.modeCount==0); // raw register chatter cannot create measured markers
    chatterBus.registers[0x31]=0x35;chatter.tick(10500);
    assert(chatter.state==State::Complete&&chatter.disableConfirmed&&!(chatterBus.registers[0]&1));
    Config timed=config();timed.terminationTime_min=0;assert(validate(timed));timed.terminationTime_min=1;
    Fake timerBus;Controller timer(timerBus);assert(timer.initialize(0));
    assert(timer.start(timed,false,0)==Controller::StartResult::Started);timer.tick(500);
    timer.tick(60000);assert(timer.state==State::Charging && (timerBus.registers[0]&1));
    timer.tick(60001);assert(timer.state==State::Aborted && timer.disableConfirmed && !(timerBus.registers[0]&1));
    assert(!strcmp(timer.message,"Termination time reached") && timer.totals.elapsed_ms==60001);
    timer.tick(62001);assert(timer.state==State::Aborted && !(timerBus.registers[0]&1));
    Fake sixBus;Controller six(sixBus);assert(six.initialize(0));assert(six.start(config(),false,0)==Controller::StartResult::Started);
    six.tick(500);six.tick(21600000);assert(six.state==State::Charging);six.tick(21600001);
    assert(six.state==State::Aborted && six.disableConfirmed && !(sixBus.registers[0]&1));
    Fake wrapBus;Controller wrappedTimer(wrapBus);const uint32_t began=0xfffff000;
    assert(wrappedTimer.initialize(began));assert(wrappedTimer.start(timed,false,began)==Controller::StartResult::Started);
    wrappedTimer.tick(began+500);wrappedTimer.tick(began+60001);assert(wrappedTimer.state==State::Aborted && wrappedTimer.disableConfirmed);
    Fake lostAtStop;Controller failedTimer(lostAtStop);assert(failedTimer.initialize(0));
    assert(failedTimer.start(timed,false,0)==Controller::StartResult::Started);failedTimer.tick(500);lostAtStop.online=false;failedTimer.tick(60001);
    assert(failedTimer.state==State::Fault && !failedTimer.disableConfirmed);
    ProfileRecord legacy;Config persisted=config();persisted.terminationTime_min=720;
    assert(legacy.encode(persisted));Config restored;assert(legacy.decode(restored)&&restored.terminationTime_min==720);
    legacy.bytes[2]=1;legacy.bytes[3]=legacy.bytes[7]=0;
    uint32_t hash=ProfileRecord::checksum(legacy.bytes);for(unsigned n=0;n<4;++n)legacy.bytes[14+n]=uint8_t(hash>>(8*n));
    assert(legacy.decode(restored)&&restored.terminationTime_min==360);
    // Partial targets program reduced hardware CV and wait for hardware completion.
    for(auto chemistry:{Chemistry::Lfp,Chemistry::LiIon,Chemistry::LiHV}){
        Config partial=config();partial.chemistry=chemistry;partial.cells=4;partial.cell_mV=full_mV(chemistry);partial.percent=70;
        Fake bus;Controller control(bus);assert(control.initialize(0));
        assert(control.start(partial,false,0)==Controller::StartResult::Started);
        assert(bus.registers[0x02]==(target_mV(partial)-2500)/10);
        bus.word(0x50,target_mV(partial)*partial.cells+20);control.tick(1000);
        assert(control.state==State::Charging&&(bus.registers[0]&1));
        bus.registers[0x02]=0;control.tick(2500);
        assert(bus.registers[0x02]==(target_mV(partial)-2500)/10);
        bus.registers[0x31]=0x35;control.tick(3000);
        assert(control.state==State::Complete&&control.disableConfirmed&&control.chargeCompleteReported&&!(bus.registers[0]&1));
    }
    Fake fullBus;Controller fullCtl(fullBus);assert(fullCtl.initialize(0));assert(fullCtl.start(config(),false,0)==Controller::StartResult::Started);
    fullBus.word(0x50,12600);fullCtl.tick(1000);assert(fullCtl.state==State::Charging); // 100% retains normal hardware termination
    fullBus.registers[0x31]=0x35;fullCtl.tick(1500);assert(fullCtl.state==State::Complete&&fullCtl.chargeCompleteReported);
    // Signed pack calibration is applied once; integration uses corrected mA/mW.
    Fake calibratedBus;Controller calibrated(calibratedBus);assert(calibrated.initialize(0));
    calibrated.setCalibration(-105,-100);calibratedBus.word(0x50,12525);calibratedBus.word(0x6E,1000);
    assert(calibrated.start(config(),false,0)==Controller::StartResult::Started);
    calibrated.tick(1000);calibrated.tick(2000);
    assert(calibrated.measurement.raw_voltage_mV==12525&&calibrated.measurement.raw_current_mA==1000);
    assert(calibrated.measurement.voltage_mV==12420&&calibrated.measurement.current_mA==900);
    equal(calibrated.totals.charge_mAh,900.0/3600);equal(calibrated.totals.energy_mWh,12420.0*900/1000/3600);
    double before=calibrated.totals.charge_mAh;calibrated.setCalibration(105,100);calibrated.tick(3000);
    equal(calibrated.totals.charge_mAh,before);calibrated.tick(4000);equal(calibrated.totals.charge_mAh,before+1100.0/3600);
    calibrated.setCalibration(-5000,-5000);calibratedBus.word(0x50,10);calibratedBus.word(0x6E,10);calibrated.tick(5000);
    assert(calibrated.measurement.voltage_mV==0&&calibrated.measurement.current_mA==0);
    calibrated.setCalibration(5000,5000);calibratedBus.word(0x50,65535);calibratedBus.word(0x6E,65535);calibrated.tick(6000);
    assert(calibrated.measurement.voltage_mV==65535&&calibrated.measurement.current_mA==65535);
    assert(calibrated.state==State::Fault); // raw-power protection still trips despite calibration
    Fake protectedBus;Controller rawProtection(protectedBus);assert(rawProtection.initialize(0));rawProtection.setCalibration(-5000,-5000);
    assert(rawProtection.start(config(),false,0)==Controller::StartResult::Started);
    protectedBus.word(0x50,15000);protectedBus.word(0x6E,8000);rawProtection.tick(1000);assert(rawProtection.state==State::Fault);
    // A reported CV flag cannot move the measured marker during steady current.
    Fake modeBus;Controller modeCtl(modeBus);assert(modeCtl.initialize(0));Config modeConfig=config();modeConfig.chemistry=Chemistry::LiHV;modeConfig.cell_mV=4400;modeConfig.current_mA=2000;
    assert(modeCtl.start(modeConfig,false,0)==Controller::StartResult::Started);modeBus.registers[0x31]=0x23;
    for(unsigned second=1;second<=30;++second){modeBus.word(0x50,12000+second*3);modeBus.word(0x6E,2000);modeCtl.tick(second*1000);}
    assert(modeCtl.history.modeCount==1&&modeCtl.history.mode(0).mode==2);
    for(unsigned second=31;second<=60;++second){modeBus.word(0x50,13200);modeCtl.tick(second*1000);}
    assert(modeCtl.history.modeCount==1);
    for(unsigned second=61;second<=90;++second){modeBus.word(0x6E,2000-(second-60)*10);modeCtl.tick(second*1000);}
    assert(modeCtl.history.modeCount==2&&modeCtl.history.mode(1).mode==3);
    assert(!strcmp(modeCtl.graphStatusText(),"IP2366: Constant voltage (CV)"));
    // Published numerical cross-checks, independent power/energy calculation.
    Config c=config();assert(!validate(c));assert(target_mV(c)==4200);
    c.percent=80;assert(target_mV(c)==4120);equal(lookup(Chemistry::LiIon,4120,false),80,0.001);
    c.chemistry=Chemistry::Lfp;c.cell_mV=3650;assert(target_mV(c)==3470);
    equal(lookup(Chemistry::Lfp,13700.0f/4,false),27.5);
    c.chemistry=Chemistry::LiHV;c.cell_mV=4400;assert(target_mV(c)==4260);
    c.percent=100;assert(target_mV(c)==4400);
    c.cells=6;c.current_mA=9700;assert(limitedCurrent_mA(c)==3700);
    for(auto chem:{Chemistry::Lfp,Chemistry::LiIon,Chemistry::LiHV}){
        size_t n;const Point *p=curve(chem,n);for(size_t i=1;i<n;++i){assert(p[i].mV>=p[i-1].mV);assert(p[i].soc>p[i-1].soc);}
        for(unsigned percent=0;percent<=90;percent+=10){Config t=config();t.chemistry=chem;t.cell_mV=full_mV(chem);t.percent=percent;
            assert(target_mV(t)==uint16_t(lookup(chem,percent,true)/10)*10);assert(deviceSettings(t).target_cell_mV==target_mV(t));
            if(chem!=Chemistry::LiIon||percent<90)equal(lookup(chem,lookup(chem,percent,true),false),percent,0.002);}}
    // CV voltage is ambiguous: reaching the plateau must not claim completion.
    assert(displayedSoc_percent(lookup(Chemistry::LiIon,4200,false),false)==99);
    assert(displayedSoc_percent(lookup(Chemistry::LiIon,4200,false),true)==100);
    c=config();c.current_mA=1050;assert(validate(c));c=config();c.termination_mA=0;assert(validate(c));
    c=config();c.cells=0;assert(validate(c));
    Fake f;Controller ctl(f);assert(ctl.initialize(0));assert(!(f.registers[0]&1));
    assert(ctl.start(config(),false,10)==Controller::StartResult::Started);assert(ctl.state==State::Starting);
    assert(f.registers[0x02]==170);assert(f.registers[0x03]==10);assert(f.registers[0x04]==0xA3);
    assert(f.registers[0x06]==2);assert(f.registers[0x08]==0x23);assert(f.registers[0x0A]==0xBF);
    assert(f.registers[0x0B]==0x7F);assert(f.registers[0x0C]==0xBB);assert(f.registers[0x22]==0x3F);
    assert(f.registers[0x00]==0x1F); // reserved bit1 preserved
    assert(!hasWrite(f,0x31)&&!hasWrite(f,0x33)&&!hasWrite(f,0x34)&&!hasWrite(f,0x38));
    assert(!hasWrite(f,0x17)&&!hasWrite(f,0x77)); // externally managed controls
    ctl.tick(1010);ctl.tick(2010);ctl.tick(3010);
    equal(ctl.totals.charge_mAh,1000.0*2/3600);equal(ctl.totals.energy_mWh,12000.0*2/3600);
    equal(ctl.measurement.temperature_C,25,0.001); // 200 mV / 20 uA = 10 kohm
    equal(ntcTemperature_C(800,80),25,0.001); // 800 mV / 80 uA = 10 kohm
    equal(ntcTemperature_C(863,80),23.26,0.03); // reported board observation, 10.7875 kohm
    assert(isnan(ntcTemperature_C(0,80))&&isnan(ntcTemperature_C(3300,80))&&isnan(ntcTemperature_C(800,0)));
    // Register-pair low byte must immediately precede high byte.
    for(size_t i=0;i<f.reads.size();++i)if(f.reads[i]==0x51||f.reads[i]==0x6F||f.reads[i]==0x79){assert(i>0);assert(f.reads[i-1]+1==f.reads[i]);}
    f.writes.clear();f.registers[0x02]=0;ctl.tick(3510);
    assert(f.registers[0x02]==170);assert(f.writes.front().reg==0x00&&!(f.writes.front().value&1));
    assert(f.writes.back().reg==0x00&&(f.writes.back().value&1));
    f.registers[0x04]=0xA6;f.registers[0x09]=0xBF;ctl.tick(4010);
    assert(f.registers[0x04]==0xA3&&f.registers[0x09]==0x3F);
    ctl.tick(10010);assert(ctl.totals.missing_ms==6000);
    f.registers[0x31]=0x35;ctl.tick(10510);assert(ctl.state==State::Complete);assert(!(f.registers[0]&1));
    double charge=ctl.totals.charge_mAh;uint64_t elapsed=ctl.totals.elapsed_ms;
    f.registers[0]|=1;ctl.tick(12510);assert(!(f.registers[0]&1));ctl.tick(14510);
    equal(ctl.totals.charge_mAh,charge);assert(ctl.totals.elapsed_ms==elapsed);
    assert(ctl.configure());
    // User explicitly accepts zero-voltage pack, without bypassing configuration checks.
    f.registers[0x31]=0x22;f.word(0x50,0);
    assert(ctl.start(config(),false,15000)==Controller::StartResult::NoBattery);
    assert(ctl.start(config(),true,15000)==Controller::StartResult::Started);
    ctl.abort(15100);assert(ctl.state==State::Aborted&&ctl.disableConfirmed);assert(ctl.configure());
    f.word(0x50,13000);assert(ctl.start(config(),false,16000)==Controller::StartResult::Mismatch);
    f.word(0x50,12000);assert(ctl.start(config(),false,16000)==Controller::StartResult::Started);
    // Fault before configuration correction: must never re-enable or erase fault.
    f.writes.clear();f.registers[0x38]=0x10;f.registers[0x02]=0;ctl.tick(16500);
    assert(ctl.state==State::Fault);assert(!(f.registers[0]&1));assert(f.registers[0x38]==0x10);assert(!hasWrite(f,0x38));
    for(auto w:f.writes)if(w.reg==0x00)assert(!(w.value&1));
    // I2C failure latches fault; subsequent restoration never resumes charging.
    Fake link;Controller lost(link);assert(lost.initialize(0));assert(lost.start(config(),false,1)==Controller::StartResult::Started);
    link.online=false;lost.tick(501);assert(lost.state==State::Fault&&!lost.disableConfirmed);
    link.online=true;lost.tick(2501);assert(lost.disableConfirmed&&!(link.registers[0]&1));
    // Write failure must prevent any enable.
    Fake broken;Controller bad(broken);assert(bad.initialize(0));broken.writeFailure=true;
    assert(bad.start(config(),false,1)==Controller::StartResult::Failed);assert(bad.state==State::Fault);
    // Current magnitude while discharge/waiting must not count as charging.
    Fake direction;Controller d(direction);assert(d.initialize(0));assert(d.start(config(),false,0)==Controller::StartResult::Started);
    d.tick(1000);direction.registers[0x31]=0x04;d.tick(1500);d.tick(2000);equal(d.totals.charge_mAh,0);
    direction.registers[0x31]=0x22;d.tick(3000);d.tick(4000);equal(d.totals.charge_mAh,1000.0/3600);
    direction.registers[0x33]=0;d.tick(4500);assert(d.state==State::Fault);
    // Overflow/wrap: elapsed time uses unsigned tick deltas, totals use 64-bit/double.
    Fake wrap;Controller w(wrap);assert(w.initialize(0xFFFFFF00));assert(w.start(config(),false,0xFFFFFF00)==Controller::StartResult::Started);
    w.tick(744);assert(w.totals.elapsed_ms==1000);
    // Diagnostic current-limit readback is independent of the reported ADC current.
    Fake offset;Controller offsetCtl(offset);assert(offsetCtl.initialize(0));Config low=config();low.current_mA=200;
    assert(offsetCtl.start(low,false,0)==Controller::StartResult::Started);offset.word(0x6E,320);offsetCtl.tick(1000);
    assert(offsetCtl.measurement.current_limit_code==2&&offsetCtl.measurement.configured_current_mA==200);
    assert(offsetCtl.measurement.current_mA==320); // never hide an unverified physical/ADC offset
    char diagnostic[640];diagnosticText(offsetCtl,diagnostic,sizeof(diagnostic));assert(strstr(diagnostic,"0x03: 0x02 = 200 mA"));
    struct SwitchingBias:Fake {unsigned calls=0;bool read(uint8_t reg,uint8_t &v)override{
        if(reg==0x77){v=(++calls%2)?0:0x80;return true;}return Fake::read(reg,v);}} switching;
    Controller switchCtl(switching);assert(switchCtl.initialize(0));assert(switchCtl.sample(1000));
    assert(!switchCtl.measurement.excitation_stable&&isnan(switchCtl.measurement.temperature_C));
    Fake sensor;Controller ntc(sensor);assert(ntc.initialize(0));sensor.registers[0x77]=0x80;sensor.word(0x78,863);
    assert(ntc.sample(1000));equal(ntc.measurement.temperature_C,23.26,0.03);
    char ntcDiagnostic[1200];diagnosticText(ntc,ntcDiagnostic,sizeof(ntcDiagnostic));
    assert(strstr(ntcDiagnostic,FirmwareVersion)&&strstr(ntcDiagnostic,"10k / B3850 NTC")&&strstr(ntcDiagnostic,"T at 80uA: 23.3 C"));
    // First start may lose input during negotiation: disable, wait, reconfigure,
    // enable last, and require a subsequent active-charge observation.
    Fake boot;Controller first(boot);assert(first.initialize(0));assert(first.start(config(),false,10)==Controller::StartResult::Started);
    boot.registers[0x33]=0;first.tick(510);assert(first.state==State::Starting&&!(boot.registers[0]&1));
    first.tick(2010);assert(first.state==State::Starting&&!(boot.registers[0]&1));
    boot.registers[0x33]=0x80;boot.registers[0x04]=0xA6;boot.writes.clear();first.tick(2510);
    assert(first.state==State::Starting&&boot.registers[0x04]==0xA3&&(boot.registers[0]&1));
    assert(boot.writes.back().reg==0x00&&(boot.writes.back().value&1));
    first.tick(3010);assert(first.state==State::Charging);
    boot.registers[0x33]=0;first.tick(3510);assert(first.state==State::Fault&&!(boot.registers[0]&1));
    assert(!strcmp(first.message,"Charging input power lost"));uint8_t captured=first.fault33;
    boot.online=false;first.tick(4010);assert(!strcmp(first.message,"IP2366 was disconnected.")&&first.fault33==captured);
    Fake timeout;Controller never(timeout);assert(never.initialize(0));assert(never.start(config(),false,0)==Controller::StartResult::Started);
    timeout.registers[0x33]=0;never.tick(500);never.tick(10000);assert(never.state==State::Fault&&!strcmp(never.message,"Charging startup timed out"));
    Fake startupFault;Controller hard(startupFault);assert(hard.initialize(0));assert(hard.start(config(),false,0)==Controller::StartResult::Started);
    startupFault.registers[0x38]=0x10;hard.tick(500);assert(hard.state==State::Fault&&hard.fault38==0x10);
    // Initial detection has no manual retry and advances exactly after 1000 ms.
    Fake detection;detection.online=false;Controller automatic(detection);assert(!automatic.initialize(0));
    unsigned probes=detection.probes;automatic.tick(999);assert(detection.probes==probes&&automatic.state==State::Missing);
    detection.online=true;automatic.tick(1000);assert(automatic.state==State::Configure&&automatic.disableConfirmed);
    assert(!(detection.registers[0]&1));
    // Communication checks cover every post-detection screen, including Summary.
    for(State screen:{State::Configure,State::Starting,State::Charging,State::Complete,State::Aborted,State::Fault}){
        Fake check;Controller monitored(check);assert(monitored.initialize(0));monitored.state=screen;
        snprintf(monitored.message,sizeof(monitored.message),"Previous reason");check.online=false;
        monitored.tick(500);assert(monitored.state==State::Fault&&!monitored.disableConfirmed);
        assert(!strcmp(monitored.message,"IP2366 was disconnected."));
        check.online=true;monitored.tick(2500);
        assert(monitored.state==State::Fault&&monitored.disableConfirmed&&!(check.registers[0]&1));
        assert(!strcmp(monitored.message,"IP2366 was disconnected."));
    }
    Fake intermittent;Controller unstable(intermittent);assert(unstable.initialize(0));intermittent.readFailure=true;
    unstable.tick(500);assert(unstable.state==State::Fault&&!strcmp(unstable.message,"IP2366 communication instable"));
    Fake abortLink;Controller abortDisconnect(abortLink);assert(abortDisconnect.initialize(0));
    assert(abortDisconnect.start(config(),false,1)==Controller::StartResult::Started);
    abortLink.online=false;abortDisconnect.abort(2);
    assert(abortDisconnect.state==State::Fault&&!strcmp(abortDisconnect.message,"IP2366 was disconnected."));
    struct MemoryProfiles:ProfileStore {
        ProfileRecord record;bool present=false,failSave=false;unsigned saves=0;Fake *chip=nullptr;
        bool load(Config &out)override{if(chip)assert(!(chip->registers[0]&1));return present&&record.decode(out);}
        bool save(const Config &value)override{
            if(chip)assert(!(chip->registers[0]&1));++saves;
            return !failSave&&(present=record.encode(value));
        }
    } profiles;
    Fake rebootBus;profiles.chip=&rebootBus;Controller original(rebootBus,&profiles);assert(original.initialize(0));
    Config eighty=config();eighty.percent=80;
    assert(original.start(eighty,false,1)==Controller::StartResult::Started&&profiles.saves==1);
    Controller rebooted(rebootBus,&profiles);assert(rebooted.initialize(2));
    assert(rebooted.state==State::Configure&&rebooted.disableConfirmed&&!(rebootBus.registers[0]&1));
    assert(rebooted.bootDefaultsAvailable&&rebooted.bootProfileMatched);
    assert(rebooted.bootDefaults.chemistry==Chemistry::LiIon&&rebooted.bootDefaults.percent==80&&rebooted.bootDefaults.cell_mV==4200);
    assert(rebooted.bootDefaults.cells==3&&rebooted.bootDefaults.current_mA==1000&&rebooted.bootDefaults.termination_mA==100);
    assert(rebooted.totals.elapsed_ms==0&&rebooted.history.count==0);
    // Saved metadata alone never restores an inactive/completed session.
    Controller inactive(rebootBus,&profiles);assert(inactive.initialize(3)&&!inactive.bootDefaultsAvailable);
    // Stale matching metadata is rejected when a register value differs.
    rebootBus.registers[0]|=1;rebootBus.registers[0x03]=20;
    Controller stale(rebootBus,&profiles);assert(stale.initialize(4));
    assert(stale.bootDefaultsAvailable&&!stale.bootProfileMatched&&stale.bootDefaults.chemistry==Chemistry::None);
    assert(stale.bootDefaults.cell_mV==4120&&stale.bootDefaults.current_mA==2000&&stale.bootDefaults.percent==100);
    // Record byte order, round trip, corruption and unsupported version.
    ProfileRecord encoded;assert(encoded.encode(eighty));Config decoded;
    assert(encoded.bytes[8]==0x68&&encoded.bytes[9]==0x10&&encoded.decode(decoded)&&decoded.percent==80);
    encoded.bytes[10]^=1;assert(!encoded.decode(decoded));assert(encoded.encode(eighty));
    encoded.bytes[2]=99;assert(!encoded.decode(decoded));
    // Original request above the 100 W cap still matches the effective current.
    Config capped=config();capped.chemistry=Chemistry::LiHV;capped.cells=6;capped.cell_mV=4400;capped.current_mA=9700;
    assert(stale.start(capped,false,5)==Controller::StartResult::Started);
    assert(rebootBus.registers[0x03]==37);
    Controller cappedReboot(rebootBus,&profiles);assert(cappedReboot.initialize(6));
    assert(cappedReboot.bootProfileMatched&&cappedReboot.bootDefaults.current_mA==9700);
    // Unavailable flash does not bypass control validation or hide the failure.
    profiles.failSave=true;assert(cappedReboot.start(config(),false,7)==Controller::StartResult::Started);
    assert(cappedReboot.profileSaveFailed);cappedReboot.abort(8);
    AppOptions options;options.persist=options.wifi=options.espNow=true;options.mode=WifiMode::AccessPoint;
    assert(!validateOptions(options));SettingsRecord all;assert(all.encode(options,eighty));
    AppOptions readOptions;Config readConfig;assert(all.decode(readOptions,readConfig));
    assert(sameOptions(options,readOptions)&&readConfig.percent==80&&readConfig.cell_mV==4200);
    all.bytes[59]^=1;assert(!all.decode(readOptions,readConfig));
    options.hostname[0]='-';assert(validateOptions(options));options=AppOptions{};
    memset(options.ssid,'x',sizeof(options.ssid));assert(validateOptions(options));
    puts("PASS: source-value SOC lookups, encoding/masks, 100 W limit, integration, drift repair, ordering, zero-voltage override, completion/abort/fault latching, I2C failures, tick wrap");
}
