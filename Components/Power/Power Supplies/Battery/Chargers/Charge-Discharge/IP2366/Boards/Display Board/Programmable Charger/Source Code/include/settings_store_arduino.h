#pragma once
#include <Preferences.h>
#include "app_options.h"
namespace batcharger {
class ArduinoSettingsStore {
    bool read(SettingsRecord &r){Preferences p;if(!p.begin("batcharger",true))return false;
        bool ok=p.getBytesLength("settings-v1")==r.Size&&p.getBytes("settings-v1",r.bytes,r.Size)==r.Size;p.end();return ok;}
public:
    bool load(AppOptions &o,Config &c){
        SettingsRecord r;AppOptions legacy;Config charger;
        bool haveCharger=read(r)&&r.decode(legacy,charger);
        Preferences p;OptionsRecord record;bool haveOptions=false;
        if(p.begin("batcharger",true)){
            size_t length=p.getBytesLength("options-v1");haveOptions=(length==record.Size||length==record.CalibrationSize||length==record.LegacySize)&&p.getBytes("options-v1",record.bytes,record.Size)==length&&record.decode(o);p.end();}
        if(!haveOptions&&haveCharger)o=legacy;
        if(!o.persist||!haveCharger)return false;c=charger;return true;
    }
    bool saveOptions(const AppOptions &o){OptionsRecord r;if(!r.encode(o))return false;
        Preferences p;if(!p.begin("batcharger",false))return false;OptionsRecord old;
        bool same=p.getBytesLength("options-v1")==old.Size&&p.getBytes("options-v1",old.bytes,old.Size)==old.Size&&!memcmp(r.bytes,old.bytes,r.Size);
        bool ok=same||p.putBytes("options-v1",r.bytes,r.Size)==r.Size;p.end();return ok;
    }
    bool save(const AppOptions &o,const Config &c){SettingsRecord r,old;if(!r.encode(o,c))return false;
        if(read(old)&&!memcmp(r.bytes,old.bytes,r.Size))return true;
        Preferences p;if(!p.begin("batcharger",false))return false;
        bool ok=p.putBytes("settings-v1",r.bytes,r.Size)==r.Size;p.end();return ok;}
    bool disable(){Preferences p;if(!p.begin("batcharger",false))return false;
        bool ok=!p.isKey("settings-v1")||p.remove("settings-v1");p.end();return ok;}
};
} // namespace batcharger
