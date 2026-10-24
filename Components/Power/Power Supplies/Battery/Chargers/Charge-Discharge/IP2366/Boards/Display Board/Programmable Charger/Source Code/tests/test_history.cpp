#include "session_history.h"
#include "charge_mode_filter.h"
#include <assert.h>
#include <stdio.h>
using namespace batcharger;
static bool contains(const PlotHistory &p,uint32_t at){for(unsigned i=0;i<p.count;++i)if(p.points[i].elapsed_ms==at)return true;return false;}
int main(){
    History filtered;ChargeModeFilter filter;
    // Initial CC needs measured evidence, not the register's stage.
    for(uint32_t second=0;second<=30;++second){
        filter.observe(12000+3*second,2000+(second%2?4:0),13200,3,second*1000,filtered);
        if(second<12)assert(filtered.modeCount==0);
    }
    assert(filtered.modeCount==1&&filtered.mode(0).mode==2&&filtered.mode(0).elapsed_ms==0);
    // Near-target voltage with constant current must stay CC, even for minutes.
    for(uint32_t second=31;second<=180;++second)
        filter.observe(13180+second%3,2000+(second%2?5:0),13200,3,second*1000,filtered);
    assert(filtered.modeCount==1);
    // Ignore an isolated current dip and small ADC noise.
    for(uint32_t second=181;second<=220;++second)
        filter.observe(13180,second==185?1600:2000,13200,3,second*1000,filtered);
    assert(filtered.modeCount==1);
    // Sustained taper becomes CV and keeps an elapsed timestamp.
    for(uint32_t second=221;second<=260;++second)
        filter.observe(13200,2000-(second-220)*10,13200,3,second*1000,filtered);
    assert(filtered.modeCount==2&&filtered.mode(1).mode==3);
    assert(filtered.mode(1).elapsed_ms>=220000&&filtered.mode(1).elapsed_ms<240000);
    // A renewed rising voltage below goal and steady current becomes CC again.
    for(uint32_t second=261;second<=300;++second)
        filter.observe(12500+(second-261)*3,1600,13200,3,second*1000,filtered);
    assert(filtered.modeCount==3&&filtered.mode(2).mode==2);
    // Falling voltage/current far below goal is not classified as CV.
    for(uint32_t second=301;second<=340;++second)
        filter.observe(12500-(second-300)*3,1600-(second-300)*10,13200,3,second*1000,filtered);
    assert(filtered.modeCount==3);
    History startingCv;ChargeModeFilter cv;
    for(uint32_t second=0;second<=20;++second)cv.observe(13305,2000-second*10,13200,3,second*1000,startingCv);
    assert(startingCv.modeCount==1&&startingCv.mode(0).mode==3); // +105 mV ADC offset tolerated
    // A gap or explicit invalid-sample interruption discards pending evidence.
    History interrupted;ChargeModeFilter gapFilter;
    for(uint32_t second=0;second<=8;++second)gapFilter.observe(13200,2000-second*10,13200,3,second*1000,interrupted);
    gapFilter.interrupt();
    for(uint32_t second=10;second<=18;++second)gapFilter.observe(13200,2000-second*10,13200,3,second*1000,interrupted);
    assert(interrupted.modeCount==0);
    gapFilter.observe(13200,1700,13200,3,30000,interrupted);assert(interrupted.modeCount==0);
    History h;assert(h.prepare());
    for(uint32_t i=0;i<=36000;++i){uint16_t v=uint16_t(12000+i%100),a=1000;if(i==5)v=15000;if(i==90)a=8000;if(i==150)v=9000;if(i==190)a=100;
        assert(h.add(v,a,i*1000));}
    assert(h.count==36001&&!h.compressed&&h.point(0).elapsed_ms==0&&h.point(36000).elapsed_ms==36000000);
    PlotHistory p;h.reduce(p);assert(p.count<=300&&p.count>1&&p.totalSamples==36001&&p.duration_ms==36000000);
    assert(contains(p,0)&&contains(p,36000000)&&contains(p,5000)&&contains(p,90000)&&contains(p,150000)&&contains(p,190000));
    for(unsigned i=1;i<p.count;++i)assert(p.points[i].elapsed_ms>p.points[i-1].elapsed_ms);
    h.reduce(p,240);assert(p.count<=240&&contains(p,0)&&contains(p,36000000));
    h.observeMode(2,500);h.observeMode(2,1000);h.observeMode(4,2000);h.observeMode(3,12345);h.observeMode(2,67890);
    h.reduce(p);assert(p.modeCount==3&&p.modes[0].elapsed_ms==0&&p.modes[1].elapsed_ms==12345&&p.modes[2].elapsed_ms==67890);
    for(uint32_t i=36001;i<=100000;++i)assert(h.add(uint16_t(12000+i%100),1000,i*1000));
    assert(h.compressed&&h.point(0).elapsed_ms==0&&h.point(h.count-1).elapsed_ms==100000000);
    h.reduce(p);assert(p.totalSamples==100001&&p.count<=300&&contains(p,0)&&contains(p,100000000));
    History dense;assert(dense.prepare());for(uint32_t i=0;i<=72000;++i)dense.observeMode(i%2?2:3,i*500);
    dense.reduce(p);assert(dense.modeCount==72001&&!dense.modeOverflow&&p.modeCount<=300&&p.modesGrouped&&p.totalModes==72001);
    assert(p.modes[0].elapsed_ms==0&&p.modes[p.modeCount-1].elapsed_ms==36000000);
    History gap(16,8);gap.add(12000,1000,0);gap.add(12100,1000,1000);gap.add(12200,900,15000);gap.reduce(p);
    assert(p.count==3&&p.points[2].elapsed_ms==15000);assert(!gap.add(12000,0,14000));
    uint32_t rev=gap.revision;gap.clear();gap.reduce(p);assert(!p.count&&!p.modeCount&&p.revision!=rev);
    puts("PASS: >=10-hour raw history, full-span reduction, both-trace extrema, timestamps/gaps, progressive compaction, 72,001 independent mode events and bounded projection");
}
