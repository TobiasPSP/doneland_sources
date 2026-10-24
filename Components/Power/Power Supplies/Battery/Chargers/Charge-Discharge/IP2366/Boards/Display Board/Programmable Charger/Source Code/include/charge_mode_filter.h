#pragma once
#include "session_history.h"
namespace batcharger {
// Presentation-only estimates from unsigned charging mV/mA samples. Never used
// for hardware regulation, completion or protection. Sample gaps reset evidence.
class ChargeModeFilter {
    struct Point {uint32_t at_ms;uint16_t voltage_mV,current_mA;};
    Point raw_[3]={},window_[11]={};
    unsigned rawCount_=0,count_=0;uint8_t stable_=0,candidate_=0;
    uint32_t candidateAt_ms_=0,lastAt_ms_=0;
    static uint16_t median(uint16_t a,uint16_t b,uint16_t c){
        if(a>b){uint16_t t=a;a=b;b=t;}if(b>c){uint16_t t=b;b=c;c=t;}return a>b?a:b;
    }
public:
    static constexpr uint32_t Stable_ms=5000,MaximumGap_ms=2000;
    void clear(){stable_=0;interrupt();}
    void interrupt(){rawCount_=count_=0;candidate_=0;}
    void observe(uint16_t voltage_mV,uint16_t current_mA,uint32_t target_pack_mV,
                 uint8_t cells,uint32_t elapsed_ms,History &history){
        if(!cells||!target_pack_mV){interrupt();return;}
        if(rawCount_&&(elapsed_ms<=lastAt_ms_||elapsed_ms-lastAt_ms_>MaximumGap_ms))interrupt();
        lastAt_ms_=elapsed_ms;
        if(rawCount_==3){raw_[0]=raw_[1];raw_[1]=raw_[2];rawCount_=2;}
        raw_[rawCount_++]={elapsed_ms,voltage_mV,current_mA};
        if(rawCount_<3)return;
        Point next={raw_[1].at_ms,median(raw_[0].voltage_mV,raw_[1].voltage_mV,raw_[2].voltage_mV),
                    median(raw_[0].current_mA,raw_[1].current_mA,raw_[2].current_mA)};
        if(count_==11){for(unsigned n=1;n<count_;++n)window_[n-1]=window_[n];--count_;}
        window_[count_++]=next;
        uint32_t span_ms=next.at_ms-window_[0].at_ms;
        if(span_ms<Stable_ms)return;
        // Least-squares change across the window (5..10 seconds at nominal 1 Hz).
        double sumT=0,sumTT=0,sumV=0,sumI=0,sumTV=0,sumTI=0;
        for(unsigned n=0;n<count_;++n){double t=(window_[n].at_ms-window_[0].at_ms)/1000.0;
            sumT+=t;sumTT+=t*t;sumV+=window_[n].voltage_mV;sumI+=window_[n].current_mA;
            sumTV+=t*window_[n].voltage_mV;sumTI+=t*window_[n].current_mA;}
        double denominator=count_*sumTT-sumT*sumT;if(denominator<=0)return;
        double span_s=span_ms/1000.0;
        double voltageChange_mV=(count_*sumTV-sumT*sumV)/denominator*span_s;
        double currentChange_mA=(count_*sumTI-sumT*sumI)/denominator*span_s;
        double currentMargin_mA=sumI/count_*0.01;if(currentMargin_mA<20)currentMargin_mA=20;
        uint8_t mode=0;
        // Allow 60 mV/cell telemetry/regulation mismatch around CV, including
        // the observed +35 mV/cell offset. A falling supply is not a CV signal.
        bool nearTarget=next.voltage_mV+uint32_t(cells)*60>=target_pack_mV;
        if(nearTarget&&currentChange_mA<=-currentMargin_mA&&voltageChange_mV>=-10.0*cells)mode=3;
        else if(next.voltage_mV+uint32_t(cells)*10<target_pack_mV&&
                voltageChange_mV>=2.0*cells&&currentChange_mA>=-currentMargin_mA)mode=2;
        if(!mode||mode==stable_){candidate_=0;return;}
        if(candidate_!=mode){candidate_=mode;candidateAt_ms_=next.at_ms;return;}
        if(next.at_ms-candidateAt_ms_>=Stable_ms){
            stable_=mode;candidate_=0;history.observeMode(mode,candidateAt_ms_);
        }
    }
};
}
