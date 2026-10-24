#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#if defined(ARDUINO_ARCH_ESP32)
#include <esp_heap_caps.h>
#endif
namespace batcharger {
struct HistoryPoint {uint32_t elapsed_ms;uint16_t voltage_mV,current_mA;};
struct ModePoint {uint32_t elapsed_ms;uint8_t mode;};
static_assert(sizeof(HistoryPoint)==8,"History allocation assumes 8-byte points");
static_assert(sizeof(ModePoint)==8,"Mode event allocation assumes 8-byte records");
struct PlotHistory {
    static constexpr unsigned Capacity=300;
    HistoryPoint points[Capacity]={};ModePoint modes[Capacity]={};
    unsigned count=0,modeCount=0;uint32_t serial=0,revision=0,totalSamples=0,totalModes=0,duration_ms=0;
    bool compressed=false,modesGrouped=false,modeOverflow=false;
};
// Owned, lazily allocated PSRAM storage. Snapshots contain reduced copies only.
// 12 h at 1 Hz (including endpoints) plus every 500 ms mode transition.
class History {
    HistoryPoint *points_=nullptr;ModePoint *modes_=nullptr;
    unsigned capacity_,modeCapacity_;uint8_t lastMode_=0;
    static void *allocate(size_t bytes){
#if defined(ARDUINO_ARCH_ESP32)
        return heap_caps_malloc(bytes,MALLOC_CAP_SPIRAM|MALLOC_CAP_8BIT);
#else
        return malloc(bytes);
#endif
    }
    static void release(void *p){
#if defined(ARDUINO_ARCH_ESP32)
        heap_caps_free(p);
#else
        free(p);
#endif
    }
    // Four chronological extrema preserve both traces' min/max in each bucket.
    unsigned extrema(unsigned first,unsigned end,unsigned selected[4])const{
        for(unsigned j=0;j<4;++j)selected[j]=first;
        for(unsigned i=first+1;i<end;++i){
            if(points_[i].voltage_mV<points_[selected[0]].voltage_mV)selected[0]=i;
            if(points_[i].voltage_mV>points_[selected[1]].voltage_mV)selected[1]=i;
            if(points_[i].current_mA<points_[selected[2]].current_mA)selected[2]=i;
            if(points_[i].current_mA>points_[selected[3]].current_mA)selected[3]=i;
        }
        for(unsigned a=0;a<4;++a)for(unsigned b=a+1;b<4;++b)if(selected[b]<selected[a]){unsigned t=selected[a];selected[a]=selected[b];selected[b]=t;}
        unsigned n=0;for(unsigned j=0;j<4;++j)if(!j||selected[j]!=selected[j-1])selected[n++]=selected[j];return n;
    }
    void compact(){
        if(count<3)return;unsigned output=1;const HistoryPoint last=points_[count-1];
        for(unsigned first=1;first<count-1;first+=8){unsigned end=first+8;if(end>count-1)end=count-1;
            unsigned selected[4];unsigned n=extrema(first,end,selected);for(unsigned j=0;j<n;++j)points_[output++]=points_[selected[j]];
        }
        points_[output++]=last;count=output;compressed=true;
    }
public:
    static constexpr unsigned Capacity=43201,ModeCapacity=86401;
    unsigned count=0,modeCount=0;uint32_t serial=0,revision=0;bool compressed=false,modeOverflow=false;
    explicit History(unsigned capacity=Capacity,unsigned modeCapacity=ModeCapacity):capacity_(capacity),modeCapacity_(modeCapacity){}
    ~History(){release(points_);release(modes_);}History(const History&)=delete;History &operator=(const History&)=delete;
    bool prepare(){if(points_&&modes_)return true;if(capacity_<10||modeCapacity_<2)return false;
        points_=static_cast<HistoryPoint *>(allocate(sizeof(HistoryPoint)*capacity_));modes_=static_cast<ModePoint *>(allocate(sizeof(ModePoint)*modeCapacity_));
        if(points_&&modes_)return true;release(points_);release(modes_);points_=nullptr;modes_=nullptr;return false;
    }
    void clear(){count=modeCount=serial=0;++revision;compressed=modeOverflow=false;lastMode_=0;}
    const HistoryPoint &point(unsigned i)const{return points_[i];}
    const ModePoint &mode(unsigned i)const{return modes_[i];}
    bool add(uint16_t voltage_mV,uint16_t current_mA,uint32_t elapsed_ms){
        if(!prepare()||(count&&elapsed_ms<points_[count-1].elapsed_ms))return false;
        if(count==capacity_)compact();if(count==capacity_)return false;
        points_[count].elapsed_ms=elapsed_ms;points_[count].voltage_mV=voltage_mV;points_[count].current_mA=current_mA;++count;++serial;++revision;return true;
    }
    bool add(uint16_t voltage_mV,uint16_t current_mA){return add(voltage_mV,current_mA,count?points_[count-1].elapsed_ms+1000:0);}
    void observeMode(uint8_t stage,uint32_t elapsed_ms){
        if(stage<1||stage>3||stage==lastMode_||!prepare())return;lastMode_=stage;
        if(modeCount==modeCapacity_){if(!modeOverflow){modeOverflow=true;++revision;}return;}
        modes_[modeCount].elapsed_ms=modeCount?elapsed_ms:0;modes_[modeCount].mode=stage;++modeCount;++revision;
    }
    void reduce(PlotHistory &out,unsigned limit=PlotHistory::Capacity)const{
        if(limit>PlotHistory::Capacity)limit=PlotHistory::Capacity;if(limit<10)limit=10;
        out.count=out.modeCount=0;out.serial=serial;out.revision=revision;out.totalSamples=serial;out.totalModes=modeCount;
        out.duration_ms=count?points_[count-1].elapsed_ms:0;out.compressed=compressed;out.modesGrouped=false;out.modeOverflow=modeOverflow;
        if(modeCount&&modes_[modeCount-1].elapsed_ms>out.duration_ms)out.duration_ms=modes_[modeCount-1].elapsed_ms;
        if(count<=limit){for(unsigned i=0;i<count;++i)out.points[out.count++]=points_[i];}
        else{out.points[out.count++]=points_[0];unsigned bins=(limit-2)/4,cursor=1;uint32_t start=points_[0].elapsed_ms,span=points_[count-1].elapsed_ms-start;
            for(unsigned b=0;b<bins&&cursor<count-1;++b){unsigned first=cursor;
                while(cursor<count-1&&(!span||uint64_t(points_[cursor].elapsed_ms-start)*bins<uint64_t(b+1)*span))++cursor;
                if(b+1==bins)cursor=count-1;
                if(first<cursor){unsigned selected[4],n=extrema(first,cursor,selected);for(unsigned j=0;j<n;++j)out.points[out.count++]=points_[selected[j]];}
            }
            out.points[out.count++]=points_[count-1];
        }
        // Dense transition lines collapse to display time columns, never into
        // voltage samples. Original timestamps remain in the PSRAM event log.
        if(modeCount<=limit){for(unsigned i=0;i<modeCount;++i)out.modes[out.modeCount++]=modes_[i];}
        else{out.modes[out.modeCount++]=modes_[0];uint32_t span=out.duration_ms;if(!span)span=modes_[modeCount-1].elapsed_ms;if(!span)span=1;unsigned previous=0;
            for(unsigned i=1;i<modeCount;++i){unsigned column=unsigned(uint64_t(modes_[i].elapsed_ms)*(limit-2)/span);if(column>limit-2)column=limit-2;
                if(out.modeCount>1&&column==previous)out.modes[out.modeCount-1]=modes_[i];else if(out.modeCount<limit)out.modes[out.modeCount++]=modes_[i];previous=column;
            }out.modesGrouped=true;
        }
    }
};
} // namespace batcharger
