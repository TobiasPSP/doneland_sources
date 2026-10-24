#pragma once
#include <Preferences.h>
#include "profile_store.h"

namespace batcharger {
// Exact Arduino-ESP32 2.0.17 Preferences source: begin=false means no handle;
// putBytes returns committed byte count, getBytes must return the exact length.
class ArduinoProfileStore final:public ProfileStore {
    bool readRecord(ProfileRecord &record){
        Preferences prefs;if(!prefs.begin("batcharger",true))return false;
        bool ok=prefs.getBytesLength("profile-v1")==ProfileRecord::Size&&
            prefs.getBytes("profile-v1",record.bytes,ProfileRecord::Size)==ProfileRecord::Size;
        prefs.end();return ok;
    }
public:
    bool load(Config &config)override{ProfileRecord record;return readRecord(record)&&record.decode(config);}
    bool save(const Config &config)override{
        ProfileRecord record,previous;if(!record.encode(config))return false;
        if(readRecord(previous)&&memcmp(previous.bytes,record.bytes,ProfileRecord::Size)==0)return true;
        Preferences prefs;if(!prefs.begin("batcharger",false))return false;
        bool ok=prefs.putBytes("profile-v1",record.bytes,ProfileRecord::Size)==ProfileRecord::Size;
        prefs.end();return ok;
    }
};
} // namespace batcharger
