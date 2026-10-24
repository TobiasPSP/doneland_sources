#pragma once
#include "profile_store.h"
#include <string.h>
namespace batcharger {
inline bool parseCalibration(const char *text,int16_t &out){
    if(!text||!*text)return false;bool negative=*text=='-';if(negative)++text;
    if(!*text)return false;int32_t value=0;for(;*text;++text){if(*text<'0'||*text>'9')return false;value=value*10+(*text-'0');if(value>5000)return false;}
    out=int16_t(negative?-value:value);return true;
}
enum class WifiMode:uint8_t {AccessPoint,Join};
struct AppOptions {
    bool persist=false,wifi=false,espNow=false;
    int16_t voltageCalibration_mV=0,currentCalibration_mA=0;
    WifiMode mode=WifiMode::Join;
    char friendlyName[32]="Charger"; // LabLink Advertisement.name: max 31 bytes plus NUL.
    char ssid[33]="",password[64]="",hostname[64]="charger1";
};
inline const char *validateOptions(const AppOptions &o){
    if(o.voltageCalibration_mV < -5000||o.voltageCalibration_mV > 5000||o.currentCalibration_mA < -5000||o.currentCalibration_mA > 5000)return "Calibration: -5000 through +5000";
    if(!memchr(o.ssid,0,sizeof(o.ssid))||!memchr(o.password,0,sizeof(o.password))||!memchr(o.hostname,0,sizeof(o.hostname)))return "WiFi field is too long";
    if(!memchr(o.friendlyName,0,sizeof(o.friendlyName)))return "Friendly name: maximum 31 bytes";
    bool named=false;for(const unsigned char *p=reinterpret_cast<const unsigned char *>(o.friendlyName);*p;++p){
        if(*p<32||*p==127)return "Friendly name cannot contain control characters";if(*p>32)named=true;}
    if(!named)return "Enter a friendly name";
    if(o.mode!=WifiMode::AccessPoint&&o.mode!=WifiMode::Join)return "Select a WiFi mode";
    if(!o.hostname[0])return "Enter an mDNS name";
    size_t n=strlen(o.hostname);
    for(size_t i=0;i<n;++i){char c=o.hostname[i];if(!((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||(c=='-'&&i&&i+1<n)))return "mDNS: letters, digits and internal hyphens only";}
    if(o.wifi&&o.mode==WifiMode::Join&&!o.ssid[0])return "Enter a WiFi SSID";
    return nullptr;
}
inline bool sameOptions(const AppOptions &a,const AppOptions &b){
    return a.voltageCalibration_mV==b.voltageCalibration_mV&&a.currentCalibration_mA==b.currentCalibration_mA&&a.persist==b.persist&&a.wifi==b.wifi&&a.espNow==b.espNow&&a.mode==b.mode&&
        !strcmp(a.friendlyName,b.friendlyName)&&!strcmp(a.ssid,b.ssid)&&!strcmp(a.password,b.password)&&!strcmp(a.hostname,b.hostname);
}
// Connectivity/UI preferences persist independently of a valid charger profile.
struct OptionsRecord {
    static constexpr size_t Size=209,CalibrationSize=177,LegacySize=173;
    uint8_t bytes[Size]={};
    static uint32_t hash(const uint8_t *p,size_t size=Size){uint32_t h=2166136261u;for(size_t i=0;i<size-4;++i){h^=p[i];h*=16777619u;}return h;}
    bool encode(const AppOptions &o){
        if(validateOptions(o))return false;memset(bytes,0,Size);
        bytes[0]='B';bytes[1]='O';bytes[2]=3;bytes[4]=(o.persist?1:0)|(o.wifi?2:0)|(o.espNow?4:0);bytes[5]=uint8_t(o.mode);
        memcpy(bytes+8,o.ssid,strlen(o.ssid));memcpy(bytes+41,o.password,strlen(o.password));memcpy(bytes+105,o.hostname,strlen(o.hostname));
        uint16_t v=uint16_t(o.voltageCalibration_mV),i=uint16_t(o.currentCalibration_mA);
        bytes[169]=uint8_t(v);bytes[170]=uint8_t(v>>8);bytes[171]=uint8_t(i);bytes[172]=uint8_t(i>>8);
        memcpy(bytes+173,o.friendlyName,strlen(o.friendlyName));
        uint32_t h=hash(bytes);for(unsigned n=0;n<4;++n)bytes[205+n]=uint8_t(h>>(8*n));return true;
    }
    bool decode(AppOptions &out)const{
        if(bytes[0]!='B'||bytes[1]!='O'||(bytes[2]!=1&&bytes[2]!=2&&bytes[2]!=3)||bytes[3]||(bytes[4]&0xF8)||bytes[5]>1||bytes[6]||bytes[7])return false;
        size_t size=bytes[2]==1?LegacySize:bytes[2]==2?CalibrationSize:Size;
        uint32_t h=0;for(unsigned i=0;i<4;++i)h|=uint32_t(bytes[size-4+i])<<(8*i);if(h!=hash(bytes,size))return false;
        AppOptions o;o.persist=bytes[4]&1;o.wifi=bytes[4]&2;o.espNow=bytes[4]&4;o.mode=WifiMode(bytes[5]);
        memcpy(o.ssid,bytes+8,33);memcpy(o.password,bytes+41,64);memcpy(o.hostname,bytes+105,64);
        if(bytes[2]>=2){uint16_t v=uint16_t(bytes[169])|(uint16_t(bytes[170])<<8),i=uint16_t(bytes[171])|(uint16_t(bytes[172])<<8);
            o.voltageCalibration_mV=int16_t(v>=32768?int32_t(v)-65536:v);o.currentCalibration_mA=int16_t(i>=32768?int32_t(i)-65536:i);}
        if(bytes[2]==3)memcpy(o.friendlyName,bytes+173,32);
        if(validateOptions(o))return false;out=o;return true;
    }
};
struct SettingsRecord {
    static constexpr size_t Size=191;
    uint8_t bytes[Size]={};
    static uint32_t hash(const uint8_t *p){uint32_t h=2166136261u;for(size_t i=0;i<Size-4;++i){h^=p[i];h*=16777619u;}return h;}
    bool encode(const AppOptions &o,const Config &c){
        ProfileRecord profile;if(validateOptions(o)||!profile.encode(c))return false;
        memset(bytes,0,Size);bytes[0]='B';bytes[1]='S';bytes[2]=1;
        bytes[4]=(o.persist?1:0)|(o.wifi?2:0)|(o.espNow?4:0);bytes[5]=uint8_t(o.mode);
        memcpy(bytes+8,profile.bytes,18);memcpy(bytes+26,o.ssid,strlen(o.ssid));
        memcpy(bytes+59,o.password,strlen(o.password));memcpy(bytes+123,o.hostname,strlen(o.hostname));
        uint32_t h=hash(bytes);for(unsigned i=0;i<4;++i)bytes[187+i]=uint8_t(h>>(8*i));return true;
    }
    bool decode(AppOptions &out,Config &config)const{
        if(bytes[0]!='B'||bytes[1]!='S'||bytes[2]!=1||bytes[3]||(bytes[4]&0xF8)||bytes[5]>1||bytes[6]||bytes[7])return false;
        uint32_t h=0;for(unsigned i=0;i<4;++i)h|=uint32_t(bytes[187+i])<<(8*i);if(h!=hash(bytes))return false;
        AppOptions o;o.persist=bytes[4]&1;o.wifi=bytes[4]&2;o.espNow=bytes[4]&4;o.mode=WifiMode(bytes[5]);
        memcpy(o.ssid,bytes+26,33);memcpy(o.password,bytes+59,64);memcpy(o.hostname,bytes+123,64);
        ProfileRecord profile;memcpy(profile.bytes,bytes+8,18);Config c;
        if(validateOptions(o)||!profile.decode(c))return false;out=o;config=c;return true;
    }
};
} // namespace batcharger
