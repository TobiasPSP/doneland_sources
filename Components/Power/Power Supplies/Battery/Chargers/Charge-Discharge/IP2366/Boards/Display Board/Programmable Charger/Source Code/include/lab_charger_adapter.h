#pragma once
#include "app_ui.h"
#include "lab_charger_server.h"
#include <limits.h>
namespace batcharger {
inline lablink::ChargerConfig labConfig(const Config &c){lablink::ChargerConfig out;
    out.chemistry=c.chemistry>=Chemistry::Lfp&&c.chemistry<=Chemistry::LiHV?uint8_t(c.chemistry)-1:255;
    out.cells=c.cells;out.targetPercent=c.percent;out.cell_mV=c.cell_mV;out.current_mA=c.current_mA;out.termination_mA=c.termination_mA;return out;
}
inline lablink::PropertyDescriptor descriptor(lablink::Property id,lablink::Access access,lablink::Unit unit,lablink::ValueType type,uint16_t flags,int64_t minimum,int64_t maximum,int64_t step,uint32_t mask){
    lablink::PropertyDescriptor d;d.id=id;d.access=access;d.unit=unit;d.type=type;d.flags=flags;d.minimum=minimum;d.maximum=maximum;d.step=step;d.enumMask=mask;return d;
}
inline bool labCapabilities(uint8_t page,lablink::CapabilityPage &out){
    using namespace lablink;using P=Property;using A=Access;using U=Unit;using T=ValueType;
    const PropertyDescriptor fields[]={
        descriptor(P::Chemistry,A::ProfileWrite,U::Enumeration,T::UInt8,CompleteProfile,0,2,1,7),
        descriptor(P::SeriesCells,A::ProfileWrite,U::Count,T::UInt8,CompleteProfile,limits::CellsMin,limits::CellsMax,1,0),
        descriptor(P::CellEndVoltage,A::ProfileWrite,U::mV,T::UInt16,CompleteProfile,limits::CellMin_mV,limits::CellMax_mV,limits::CellStep_mV,0),
        descriptor(P::TargetPercent,A::ProfileWrite,U::Percent,T::UInt8,CompleteProfile,limits::PercentMin,limits::PercentMax,limits::PercentStep,0),
        descriptor(P::RequestedCurrent,A::ProfileWrite,U::mA,T::UInt16,uint16_t(CompleteProfile|DynamicLimit),limits::CurrentMin_mA,limits::CurrentMax_mA,limits::CurrentStep_mA,0),
        descriptor(P::TerminationCurrent,A::ProfileWrite,U::mA,T::UInt16,CompleteProfile,limits::TerminationMin_mA,limits::TerminationMax_mA,limits::TerminationStep_mA,0),
        descriptor(P::EffectiveCurrent,A::Read,U::mA,T::UInt32,uint16_t(Calculated|DynamicLimit),0,limits::CurrentMax_mA,100,0),
        descriptor(P::TargetPackVoltage,A::Read,U::mV,T::UInt32,Calculated,0,int64_t(limits::CellMax_mV)*limits::CellsMax,10,0),
        // ADC limits below describe the verified unsigned 16-bit encodings,
        // not sensor accuracy or a safe operating range.
        descriptor(P::BatteryVoltage,A::Read,U::mV,T::UInt32,Measured,0,65535,1,0),
        descriptor(P::BatteryCurrent,A::Read,U::mA,T::Int32,Measured,0,65535,1,0),
        descriptor(P::NtcTemperature,A::Read,U::CentiCelsius,T::Int32,uint16_t(Calculated|MonitoringOnly),INT32_MIN,INT32_MAX,1,0),
        descriptor(P::EstimatedSoc,A::Read,U::Percent,T::UInt8,Estimated,0,100,1,0),
        descriptor(P::ElapsedTime,A::Read,U::Milliseconds,T::UInt32,Calculated,0,UINT32_MAX,1,0),
        descriptor(P::DeliveredCharge,A::Read,U::MicroAh,T::UInt64,Calculated,0,INT64_MAX,1,0),
        descriptor(P::DeliveredEnergy,A::Read,U::MicroWh,T::UInt64,Calculated,0,INT64_MAX,1,0),
        descriptor(P::OperatingState,A::Read,U::Enumeration,T::UInt8,0,0,6,1,127),
        descriptor(P::StopReason,A::Read,U::Enumeration,T::UInt16,0,0,6,1,127),
        descriptor(P::SessionOwner,A::Read,U::DeviceId,T::Identifier,0,0,0,0,0),
        descriptor(P::ConfigureAndStart,A::Command,U::None,T::Command,uint16_t(Conditional|CompleteProfile),0,0,0,0),
        descriptor(P::Abort,A::Command,U::None,T::Command,Conditional,0,0,0,0),
        descriptor(P::Subscribe,A::Command,U::Milliseconds,T::Command,0,500,5000,1,0),
        descriptor(P::Unsubscribe,A::Command,U::None,T::Command,0,0,0,0,0)
    };
    constexpr size_t Count=sizeof(fields)/sizeof(fields[0]);constexpr unsigned Pages=(Count+PropertiesPerPage-1)/PropertiesPerPage;
    if(page>=Pages)return false;out=CapabilityPage{};out.page=page;out.pageCount=Pages;out.revision=1;
    for(unsigned i=page*PropertiesPerPage;i<Count&&out.count<PropertiesPerPage;++i)out.properties[out.count++]=fields[i];return true;
}
class LabChargerAdapter:public LabChargerPort {
    Controller &ctl_;Ui &ui_;
    static uint64_t microUnits(double milli){ // mAh/mWh -> uAh/uWh, once at the protocol boundary
        if(!isfinite(milli)||milli<=0)return 0;long double value=static_cast<long double>(milli)*1000;
        return value>=static_cast<long double>(INT64_MAX)?uint64_t(INT64_MAX):uint64_t(value+0.5L);
    }
    lablink::Result reply(lablink::ResultCode code,const char *text)const{lablink::Result r;r.code=code;
        const Config &c=ctl_.sessionsStarted?ctl_.activeConfig():ui_.config;r.effective=labConfig(c);r.effective.current_mA=limitedCurrent_mA(c);r.effective.cell_mV=target_mV(c);
        snprintf(r.message,sizeof(r.message),"%s",text);return r;
    }
public:
    LabChargerAdapter(Controller &controller,Ui &ui):ctl_(controller),ui_(ui){}
    uint32_t session()const override{return ctl_.sessionsStarted;}
    uint32_t revision()const override{return ui_.viewRevision();}
    bool active()const override{return ctl_.state==State::Starting||ctl_.state==State::Charging;}
    lablink::ChargerConfig config()const override{return labConfig(active()?ctl_.activeConfig():ui_.config);}
    bool capabilities(uint8_t page,lablink::CapabilityPage &out)const override{return labCapabilities(page,out);}
    lablink::Telemetry telemetry(uint32_t now_ms)const override{using namespace lablink;Telemetry t;const auto &m=ctl_.measurement;
        t.state=OperatingState(uint8_t(ctl_.state));t.sampleAge_ms=now_ms-ctl_.measurementAt_ms;t.disableConfirmed=ctl_.disableConfirmed;
        t.voltage_mV=m.voltage_mV;t.current_mA=m.current_mA; // unsigned hardware magnitude; never infer direction
        if(m.valid){t.validity=VoltageValid|CurrentValid;if(isfinite(m.temperature_C)&&double(m.temperature_C)*100>=INT32_MIN&&double(m.temperature_C)*100<=INT32_MAX){t.temperature_cC=int32_t(lround(double(m.temperature_C)*100));t.validity|=TemperatureValid;}}
        const Config &c=ctl_.activeConfig();if(ctl_.sessionsStarted&&m.valid&&c.cells){t.soc_percent=uint8_t(lround(displayedSoc_percent(lookup(c.chemistry,float(m.voltage_mV)/c.cells,false),ctl_.chargeCompleteReported,c.percent)));t.validity|=SocValid;}
        if(ctl_.sessionsStarted&&!ctl_.totals.missing_ms)t.validity|=TotalsValid;
        t.elapsed_ms=ctl_.totals.elapsed_ms>UINT32_MAX?UINT32_MAX:uint32_t(ctl_.totals.elapsed_ms);
        t.charge_uAh=microUnits(ctl_.totals.charge_mAh);t.energy_uWh=microUnits(ctl_.totals.energy_mWh);
        t.target_mV=uint32_t(target_mV(c))*c.cells;t.effectiveCurrent_mA=limitedCurrent_mA(c);t.termination_mA=c.termination_mA;
        if(ctl_.state==State::Complete)t.stopReason=uint16_t(StopReason::Complete);
        else if(ctl_.state==State::Aborted)t.stopReason=uint16_t(!strcmp(ctl_.message,"ESP-NOW owner heartbeat lost")?StopReason::OwnerLost:StopReason::Abort);
        else if(ctl_.state==State::Fault)t.stopReason=uint16_t(ctl_.failureKind?StopReason::Communication:StopReason::HardwareFault);
        else if(ctl_.state==State::Starting)t.stopReason=uint16_t(StopReason::Startup);
        return t;
    }
    lablink::Result start(const lablink::ChargerConfig &profile,bool proceed,uint32_t now_ms)override{
        using lablink::ResultCode;if(profile.chemistry>2)return reply(ResultCode::Rejected,"Unknown chemistry");Config c;
        c.terminationTime_min=ui_.config.terminationTime_min;
        c.chemistry=Chemistry(profile.chemistry+1);c.cells=profile.cells;c.percent=profile.targetPercent;c.cell_mV=profile.cell_mV;c.current_mA=profile.current_mA;c.termination_mA=profile.termination_mA;
        if(const char *why=validate(c))return reply(ResultCode::Rejected,why);
        Chemistry inferred=c.cell_mV<=3800?Chemistry::Lfp:c.cell_mV<=4200?Chemistry::LiIon:Chemistry::LiHV;
        if(c.chemistry!=inferred)return reply(ResultCode::Rejected,"Cell voltage and chemistry do not match");
        if(active()||ctl_.state==State::Missing)return reply(ResultCode::Rejected,"Charger is unavailable or active");
        if(ctl_.state!=State::Configure&&!ctl_.configure())return reply(ResultCode::Rejected,"Charger disable is not confirmed");
        auto outcome=ctl_.start(c,proceed,now_ms,SessionOrigin::RemoteHost);ui_.automationState(&c);
        if(outcome==Controller::StartResult::Started)return reply(ResultCode::Applied,"Charge started; owner heartbeat required");
        if(outcome==Controller::StartResult::NoBattery)return reply(ResultCode::ConfirmationRequired,"No battery detected. Proceed anyway?");
        return reply(ResultCode::Rejected,outcome==Controller::StartResult::Mismatch?"Battery does not fit cells/chemistry":ctl_.message);
    }
    lablink::Result abort(uint32_t now_ms,bool ownerLost)override{
        if(!active())return reply(lablink::ResultCode::Rejected,"No active charge to abort");
        ctl_.stop(State::Aborted,ownerLost?"ESP-NOW owner heartbeat lost":"Charge aborted",now_ms);ui_.automationState();
        return reply(ctl_.disableConfirmed?lablink::ResultCode::Applied:lablink::ResultCode::Rejected,ctl_.message);
    }
};
} // namespace batcharger
