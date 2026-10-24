#pragma once
#include "app_ui.h"
#include <stdarg.h>
namespace batcharger {
class JsonWriter {
    char *out_;size_t capacity_,used_=0;bool valid_=true;
public:
    JsonWriter(char *out,size_t capacity):out_(out),capacity_(capacity){if(capacity)out[0]=0;}
    void add(const char *format,...){if(!valid_)return;va_list args;va_start(args,format);int n=vsnprintf(out_+used_,capacity_-used_,format,args);va_end(args);
        if(n<0||size_t(n)>=capacity_-used_){valid_=false;return;}used_+=size_t(n);}
    void text(const char *s){add("\"");for(const unsigned char *p=reinterpret_cast<const unsigned char *>(s);*p;++p){
        if(*p=='"'||*p=='\\')add("\\%c",*p);else if(*p<32)add("\\u%04x",unsigned(*p));else add("%c",*p);}add("\"");}
    void number(double n){if(isfinite(n))add("%.3f",n);else add("null");}
    size_t size()const{return valid_?used_:0;}
};
struct WebSnapshot {
    uint32_t revision=0,session=0,uptime_ms=0;
    State state=State::Missing;bool summary=false,disableConfirmed=false,profileSaveFailed=false,stopFailed=false,statusValid=false,chargeCompleteReported=false;
    SessionOrigin origin=SessionOrigin::None;uint8_t stage=0;
    Config config,active;AppOptions options;Measurement measurement;Totals totals;PlotHistory history;WifiSignal signal;
    char chargerStatus[64]={},graphStatus[160]={};
    char message[160]={},notice[192]={},network[160]={},lab[256]={},diagnostics[1660]={};
    void capture(const Ui &ui,const Controller &ctl,const AppOptions &o,const WifiSignal &wifi,const char *networkText,uint32_t now_ms){
        revision=ui.viewRevision();session=ctl.sessionsStarted;uptime_ms=now_ms;state=ctl.state;summary=ui.summaryVisible();
        disableConfirmed=ctl.disableConfirmed;profileSaveFailed=ctl.profileSaveFailed;config=ui.config;active=ctl.activeConfig();
        options=o;measurement=ctl.measurement;totals=ctl.totals;signal=wifi;
        if(history.revision!=ctl.history.revision)ctl.history.reduce(history);
        chargeCompleteReported=ctl.chargeCompleteReported;stopFailed=ctl.stopVerificationFailed();statusValid=ctl.statusValid;stage=ctl.status31&7;origin=ctl.sessionOrigin;
        snprintf(chargerStatus,sizeof(chargerStatus),"%s",ctl.chargerStatusText());snprintf(graphStatus,sizeof(graphStatus),"%s",ctl.graphStatusText());
        snprintf(message,sizeof(message),"%s",ctl.message);snprintf(notice,sizeof(notice),"%s",ui.notice());snprintf(network,sizeof(network),"%s",networkText);
        ui.diagnosticReport(diagnostics,sizeof(diagnostics));snprintf(lab,sizeof(lab),"%s",ui.labStatusText());
    }
    static const char *stateName(State s){switch(s){case State::Configure:return "configure";case State::Starting:return "starting";case State::Charging:return "charging";case State::Complete:return "complete";case State::Aborted:return "aborted";case State::Fault:return "fault";default:return "missing";}}
    static void configJson(JsonWriter &w,const Config &c){w.add("{\"chemistry\":%u,\"cells\":%u,\"percent\":%u,\"cell_mV\":%u,\"current_mA\":%u,\"termination_mA\":%u,\"terminationTime_min\":%u}",unsigned(c.chemistry),c.cells,c.percent,c.cell_mV,c.current_mA,c.termination_mA,c.terminationTime_min);}
    size_t stateJson(char *out,size_t capacity)const{
        JsonWriter w(out,capacity);w.add("{\"schema\":1,\"revision\":%lu,\"session\":%lu,\"sample\":%lu,\"uptime_ms\":%lu,\"state\":",(unsigned long)revision,(unsigned long)session,(unsigned long)history.serial,(unsigned long)uptime_ms);w.text(stateName(state));
        w.add(",\"summary\":%s,\"disableConfirmed\":%s,\"profileSaveFailed\":%s,\"message\":",summary?"true":"false",disableConfirmed?"true":"false",profileSaveFailed?"true":"false");w.text(message);
        w.add(",\"notice\":");w.text(notice);w.add(",\"config\":");configJson(w,config);w.add(",\"active\":");configJson(w,active);
        w.add(",\"history_revision\":%lu,\"stop_failed\":%s,\"stage_valid\":%s,\"stage\":%u,\"session_origin\":",(unsigned long)history.revision,stopFailed?"true":"false",statusValid?"true":"false",unsigned(stage));w.text(originName(origin));
        w.add(",\"charger_status\":");w.text(chargerStatus);w.add(",\"graph_status\":");w.text(graphStatus);
        w.add(",\"valid\":%s,\"voltage_mV\":%u,\"current_mA\":%u,\"temperature_C\":",measurement.valid?"true":"false",measurement.voltage_mV,measurement.current_mA);w.number(measurement.temperature_C);
        w.add(",\"soc_percent\":");if(active.cells&&session&&measurement.valid)w.number(displayedSoc_percent(lookup(active.chemistry,float(measurement.voltage_mV)/active.cells,false),chargeCompleteReported,active.percent));else w.add("null");
        uint32_t target=uint32_t(target_mV(active))*active.cells,minimum=uint32_t(low_mV(active.chemistry))*active.cells;if(minimum>target)minimum=target;
        w.add(",\"target_mV\":%lu,\"termination_mA\":%u,\"vmin_mV\":%lu,\"vmax_mV\":%lu,\"imax_mA\":%u,\"effectiveCurrent_mA\":%u,\"elapsed_ms\":%.0f,\"missing_ms\":%.0f,\"charge_mAh\":",(unsigned long)target,active.termination_mA,(unsigned long)minimum,(unsigned long)(target+1000),unsigned(limitedCurrent_mA(active)+300),limitedCurrent_mA(config),double(totals.elapsed_ms),double(totals.missing_ms));w.number(totals.charge_mAh);w.add(",\"energy_mWh\":");w.number(totals.energy_mWh);
        w.add(",\"options\":{\"persist\":%s,\"wifi\":%s,\"espNow\":%s,\"mode\":%u,\"ssid\":",options.persist?"true":"false",options.wifi?"true":"false",options.espNow?"true":"false",unsigned(options.mode));w.text(options.ssid);w.add(",\"hostname\":");w.text(options.hostname);w.add(",\"friendlyName\":");w.text(options.friendlyName);w.add(",\"voltageCalibration_mV\":%d,\"currentCalibration_mA\":%d",options.voltageCalibration_mV,options.currentCalibration_mA);w.add(",\"passwordSet\":%s},\"wifiState\":%u,\"rssi_dBm\":",options.password[0]?"true":"false",unsigned(signal.state));if(signal.state==WifiState::Connected)w.add("%d",int(signal.rssi_dBm));else w.add("null");
        w.add(",\"network\":");w.text(network);w.add(",\"espNowStatus\":");w.text(lab);w.add("}");return w.size();
    }
    size_t historyJson(char *out,size_t capacity,uint32_t requestSession,uint32_t after)const{
        bool reset=requestSession!=session||after!=history.revision;
        JsonWriter w(out,capacity);w.add("{\"schema\":2,\"session\":%lu,\"next\":%lu,\"reset\":%s,\"duration_ms\":%lu,\"total_samples\":%lu,\"total_modes\":%lu,\"compressed\":%s,\"modes_grouped\":%s,\"mode_overflow\":%s,\"samples\":[",
            (unsigned long)session,(unsigned long)history.revision,reset?"true":"false",(unsigned long)history.duration_ms,(unsigned long)history.totalSamples,(unsigned long)history.totalModes,history.compressed?"true":"false",history.modesGrouped?"true":"false",history.modeOverflow?"true":"false");
        if(reset)for(unsigned i=0;i<history.count;++i){const auto &p=history.points[i];w.add("%s[%lu,%u,%u]",i?",":"",(unsigned long)p.elapsed_ms,p.voltage_mV,p.current_mA);}
        w.add("],\"modes\":[");if(reset)for(unsigned i=0;i<history.modeCount;++i)w.add("%s[%lu,%u]",i?",":"",(unsigned long)history.modes[i].elapsed_ms,unsigned(history.modes[i].mode));w.add("]}");return w.size();
    }
    size_t diagnosticsJson(char *out,size_t capacity)const{JsonWriter w(out,capacity);w.add("{\"text\":");w.text(diagnostics);w.add("}");return w.size();}
    static size_t modelJson(char *out,size_t capacity){JsonWriter w(out,capacity);w.add("{\"schema\":1,\"defaults_mV\":[0,3650,4200,4400],\"low_mV\":[0,2500,3000,3000],\"curves\":[[]");
        for(unsigned chemistry=1;chemistry<=3;++chemistry){size_t count;const Point *points=curve(Chemistry(chemistry),count);w.add(",[");
            for(size_t i=0;i<count;++i)w.add("%s[%.0f,%.0f]",i?",":"",double(points[i].soc),double(points[i].mV));w.add("]");}w.add("]}");return w.size();}
    static size_t resultJson(char *out,size_t capacity,const RemoteResult &result){JsonWriter w(out,capacity);w.add("{\"id\":%lu,\"code\":%u,\"revision\":%lu,\"message\":",(unsigned long)result.id,result.code,(unsigned long)result.revision);w.text(result.message);w.add("}");return w.size();}
};
} // namespace batcharger
