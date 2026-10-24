#include "settings_store_arduino.h"
#include "wifi_signal.h"
#include <assert.h>
#include <algorithm>
using namespace batcharger;
int main(){
    ArduinoSettingsStore store;AppOptions options;options.wifi=true;options.espNow=true;
    snprintf(options.ssid,sizeof(options.ssid),"test-network");snprintf(options.password,sizeof(options.password),"test-password");snprintf(options.hostname,sizeof(options.hostname),"charger-test");
    // Save before chemistry/cell selection and before any charge: no valid
    // charger profile is necessary for connectivity persistence.
    assert(store.saveOptions(options));unsigned writes=Preferences::writes;
    assert(store.saveOptions(options)&&Preferences::writes==writes);
    AppOptions restored;Config config;
    assert(!store.load(restored,config)&&sameOptions(options,restored));
    assert(!restored.persist&&restored.wifi&&restored.espNow);
    options.persist=true;assert(store.saveOptions(options));
    config.chemistry=Chemistry::Lfp;config.cells=4;config.cell_mV=3650;config.current_mA=2000;config.terminationTime_min=725;
    assert(store.save(options,config));AppOptions next;Config recovered;
    assert(store.load(next,recovered)&&sameOptions(options,next)&&recovered.cells==4&&recovered.current_mA==2000&&recovered.terminationTime_min==725);
    // Upgrade a real v1-shaped embedded profile: old reserved bytes are zero,
    // both original checksums are valid, and missing time restores six hours.
    SettingsRecord old;assert(old.encode(options,config));
    auto *profile=old.bytes+8;profile[2]=1;profile[3]=profile[7]=0;
    uint32_t profileHash=ProfileRecord::checksum(profile);for(unsigned i=0;i<4;++i)profile[14+i]=uint8_t(profileHash>>(8*i));
    uint32_t settingsHash=SettingsRecord::hash(old.bytes);for(unsigned i=0;i<4;++i)old.bytes[187+i]=uint8_t(settingsHash>>(8*i));
    AppOptions migratedOptions;Config migratedConfig;assert(old.decode(migratedOptions,migratedConfig)&&migratedConfig.terminationTime_min==360);
    // Disabling charger persistence retains every connectivity setting.
    options.persist=false;assert(store.saveOptions(options)&&store.disable());
    assert(!store.load(next,recovered)&&sameOptions(options,next)&&next.wifi);
    // Existing 1.1.x combined records migrate without losing their options.
    Preferences::flash.clear();options.persist=true;assert(store.save(options,config));
    assert(store.load(next,recovered)&&sameOptions(options,next));assert(store.saveOptions(next));
    assert(store.disable());assert(!store.load(next,recovered)&&next.wifi&&next.persist);
    OptionsRecord record;assert(record.encode(options));record.bytes[41]^=1;assert(!record.decode(next));
    // v2 signed offsets round-trip independently of charger persistence.
    options.persist=false;options.voltageCalibration_mV=-105;options.currentCalibration_mA=25;
    assert(store.saveOptions(options));assert(!store.load(next,recovered)&&sameOptions(options,next));
    int16_t parsed=0;assert(parseCalibration("-105",parsed)&&parsed==-105);
    assert(parseCalibration("5000",parsed)&&parsed==5000);assert(parseCalibration("-5000",parsed)&&parsed==-5000);
    for(auto text:{"", "-", "5001", "-5001", "1.5", "--1", "12x"})assert(!parseCalibration(text,parsed));
    options.voltageCalibration_mV=5001;assert(validateOptions(options));options.voltageCalibration_mV=-105;
    // Real 173-byte v1 option records restore zero offsets and migrate on save.
    OptionsRecord legacyOptions;AppOptions zero;zero.wifi=true;snprintf(zero.ssid,sizeof(zero.ssid),"test-network");assert(legacyOptions.encode(zero));legacyOptions.bytes[2]=1;
    uint32_t legacyHash=OptionsRecord::hash(legacyOptions.bytes,OptionsRecord::LegacySize);
    for(unsigned n=0;n<4;++n)legacyOptions.bytes[169+n]=uint8_t(legacyHash>>(8*n));
    Preferences::flash["batcharger/options-v1"]={legacyOptions.bytes,legacyOptions.bytes+OptionsRecord::LegacySize};
    assert(!store.load(next,recovered)&&next.wifi&&next.voltageCalibration_mV==0&&next.currentCalibration_mA==0);
    assert(store.saveOptions(next)&&Preferences::flash["batcharger/options-v1"].size()==OptionsRecord::Size);
    // v2 calibration preferences migrate without adopting mDNS as the friendly name.
    OptionsRecord v2;AppOptions previous;previous.wifi=true;snprintf(previous.ssid,sizeof(previous.ssid),"test-network");previous.voltageCalibration_mV=-105;previous.currentCalibration_mA=25;
    snprintf(previous.hostname,sizeof(previous.hostname),"old-mdns");assert(v2.encode(previous));v2.bytes[2]=2;
    uint32_t v2Hash=OptionsRecord::hash(v2.bytes,OptionsRecord::CalibrationSize);
    for(unsigned n=0;n<4;++n)v2.bytes[173+n]=uint8_t(v2Hash>>(8*n));
    Preferences::flash["batcharger/options-v1"]={v2.bytes,v2.bytes+OptionsRecord::CalibrationSize};
    assert(!store.load(next,recovered)&&next.voltageCalibration_mV==-105&&next.currentCalibration_mA==25);
    assert(!strcmp(next.friendlyName,"Charger")&&!strcmp(next.hostname,"old-mdns"));
    snprintf(next.friendlyName,sizeof(next.friendlyName),"Charger Bench A");assert(store.saveOptions(next));
    AppOptions renamed;assert(!store.load(renamed,recovered)&&sameOptions(next,renamed));
    assert(!strcmp(renamed.hostname,"old-mdns")&&!renamed.persist);
    memset(next.friendlyName,'x',31);next.friendlyName[31]=0;assert(!validateOptions(next));assert(store.saveOptions(next));
    memset(next.friendlyName,'x',32);assert(validateOptions(next));
    snprintf(next.friendlyName,sizeof(next.friendlyName)," ");assert(validateOptions(next));
    snprintf(next.friendlyName,sizeof(next.friendlyName),"bad\nname");assert(validateOptions(next));
    WifiSignal signal;assert(signal.level()==0);signal.state=WifiState::AccessPoint;assert(signal.level()==4);
    signal.state=WifiState::Connected;
    for(int rssi:{-50,-60,-70,-85}){signal.rssi_dBm=rssi;assert(signal.level()==unsigned(rssi==-50?4:rssi==-60?3:rssi==-70?2:1));}
    puts("PASS: independent preferences/charger persistence, migration, corruption, deduplication and RSSI levels");
}
