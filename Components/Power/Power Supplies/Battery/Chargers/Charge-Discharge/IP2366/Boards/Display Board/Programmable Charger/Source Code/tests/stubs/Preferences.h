#pragma once
#include <map>
#include <string>
#include <vector>
#include <stdint.h>
#include <string.h>
// In-memory implementation of the exact Preferences byte API used by the adapter.
class Preferences {
    std::string prefix_;bool open_=false,readOnly_=true;
public:
    inline static std::map<std::string,std::vector<uint8_t>> flash;
    inline static unsigned writes=0;
    bool begin(const char *name,bool readOnly=false){prefix_=std::string(name)+"/";readOnly_=readOnly;open_=true;return true;}
    void end(){open_=false;}
    size_t getBytesLength(const char *key){auto i=flash.find(prefix_+key);return open_&&i!=flash.end()?i->second.size():0;}
    size_t getBytes(const char *key,void *out,size_t capacity){auto i=flash.find(prefix_+key);if(!open_||i==flash.end()||capacity<i->second.size())return 0;memcpy(out,i->second.data(),i->second.size());return i->second.size();}
    size_t putBytes(const char *key,const void *data,size_t length){if(!open_||readOnly_)return 0;auto p=static_cast<const uint8_t *>(data);flash[prefix_+key]={p,p+length};++writes;return length;}
    bool isKey(const char *key){return open_&&flash.count(prefix_+key);}
    bool remove(const char *key){return open_&&!readOnly_&&flash.erase(prefix_+key);}
};
