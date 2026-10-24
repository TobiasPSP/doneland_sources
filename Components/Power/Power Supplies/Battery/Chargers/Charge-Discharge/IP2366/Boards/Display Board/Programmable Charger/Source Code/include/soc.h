#pragma once
#include "app_types.h"
#include <stddef.h>

namespace batcharger {
// Digitized charging-terminal-voltage references, all internal values mV/cell.
// LFP: EVE LF105 1C, 25 C. Li-ion: Molicel P42A 1C, 23 C.
// LiHV: Grepow 4.4 V 0.5C, room temperature (user-approved rate exception).
// Unknown pack capacity prevents actual C-rate/current compensation. These
// reference profiles are approximate; CV voltage alone cannot resolve SOC.
// Point provenance, normalization and source hashes: docs/sources/charging-curves.json.
struct Point {float soc; float mV;};
// Apply before rounding. The IP2366 completion flag unlocks the target itself;
// a voltage-derived estimate cannot claim the goal early or exceed it afterward.
inline float displayedSoc_percent(float curveSoc_percent,bool chargeComplete,uint8_t target_percent=100) {
    float ceiling_percent=chargeComplete?target_percent:(target_percent?target_percent-1:0);
    return curveSoc_percent>ceiling_percent?ceiling_percent:curveSoc_percent;
}
// Presentation progress toward the requested SOC; never a completion signal.
inline float targetProgress_percent(float soc_percent,uint8_t target_percent){
    if(!isfinite(soc_percent)||soc_percent<0)return 0;
    if(!target_percent)return 100; // Valid SOC has already met a zero-percent goal.
    float progress=soc_percent*100.0f/target_percent;
    return progress>100?100:progress;
}
static const Point lfpCurve[]={{0,3000},{10,3360},{20,3410},{30,3430},{40,3435},{50,3445},{60,3455},{70,3465},{80,3475},{90,3495},{95,3515},{98,3575},{100,3650}};
static const Point ionCurve[]={{0,3000},{10,3500},{20,3590},{30,3670},{40,3750},{50,3830},{60,3930},{70,4020},{80,4120},{85,4170},{90,4200},{100,4200}};
static const Point hvCurve[]={{0,3460},{10,3780},{20,3850},{30,3880},{40,3920},{50,3970},{60,4050},{70,4140},{80,4260},{90,4390},{100,4400}};
inline const Point *curve(Chemistry c,size_t &n) {
    if(c==Chemistry::Lfp){n=sizeof(lfpCurve)/sizeof(*lfpCurve);return lfpCurve;}
    if(c==Chemistry::LiHV){n=sizeof(hvCurve)/sizeof(*hvCurve);return hvCurve;}
    n=sizeof(ionCurve)/sizeof(*ionCurve);return ionCurve;
}
inline float lookup(Chemistry c,float input,bool inverse) {
    size_t n;const Point *p=curve(c,n);
    float first=inverse?p[0].soc:p[0].mV,last=inverse?p[n-1].soc:p[n-1].mV;
    if(input<=first)return inverse?p[0].mV:p[0].soc;
    if(input>=last)return inverse?p[n-1].mV:p[n-1].soc;
    for(size_t i=1;i<n;++i){
        float x=inverse?p[i].soc:p[i].mV,prev=inverse?p[i-1].soc:p[i-1].mV;
        if(input<=x){float y=inverse?p[i].mV:p[i].soc,yp=inverse?p[i-1].mV:p[i-1].soc;
            return yp+(y-yp)*(input-prev)/(x-prev);}
    }
    return 0;
}
} // namespace batcharger
