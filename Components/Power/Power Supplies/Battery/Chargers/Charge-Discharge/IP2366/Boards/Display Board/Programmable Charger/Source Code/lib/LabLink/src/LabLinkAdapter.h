#pragma once
// LabLink 1.2 SMBus adapter. All payload integers are explicitly little-endian.
namespace lablink {
constexpr uint32_t AdapterPoll=0x1000, AdapterActions=0x2000, AdapterHistory=0x4000, AdapterControl=0x8000;
constexpr uint32_t AdapterCapabilities=CanSubscribe|HasCapabilities|AdapterPoll|AdapterActions|AdapterHistory|AdapterControl;
enum class AdapterOp:uint8_t { Readings=0, ActionInfo=1, Execute=2, DiscoverDut=3, Refresh=4,
 GraphInfo=5, GraphPage=6, GraphStart=7, GraphPause=8, GraphClear=9, GraphConfig=10 };
enum class GraphStop:uint8_t { None=0, Manual=1, Full=2, Empty=3, NoCurrent=4, StorageFull=5, DutChanged=6 };
struct AdapterRequest {
 AdapterOp op=AdapterOp::Readings; uint16_t index=0;
 uint32_t targetRevision=0,recordingId=0,generation=0,offset=0;
 bool autoStop=true; uint16_t deadband_mA=0; bool confirmed=false; uint32_t token=0;
};
struct GraphInfo {
 uint32_t recordingId=1,generation=1,revision=0,count=0; uint64_t duration_ms=0;
 bool recording=false,autoStop=true;uint16_t deadband_mA=0;GraphStop stop=GraphStop::None;
};
struct GraphPoint {
 uint64_t at_ms=0;uint16_t validity=0;uint32_t voltage_mV=0;int32_t current_mA=0;
 uint16_t soc_percent=0,cells_mV[8]={};uint8_t flags=0;
}; // validity: pack=1,current=2,SOC=4,cells bits3..10; flags valid=1,full=2,empty=4.
struct AdapterReadings {
 uint32_t targetRevision=0,age_ms=UINT32_MAX,validity=0;
 uint8_t address=0,stringCount=0;char family[32]={},flavor[32]={},security[24]={},manufactured[16]={};
 uint32_t voltage_mV=0,designVoltage_mV=0,chargeVoltage_mV=0,design_mAh=0,full_mAh=0,remaining_mAh=0;
 int32_t current_mA=0,temperature_cC=0;uint16_t soc_percent=0,health_percent=0,cycles=0,chargingCurrent_mA=0;
 uint16_t cells_mV[8]={},cellValidity=0,batteryStatus=0;uint8_t flags=0;
}; // validity: V,I,SOC,T,design,FCC,remaining,health,cycles,designV,chargeV,chargeI,status bits0..12.
struct AdapterAction {uint16_t id=0,total=0;char name[40]={},confirmation[140]={};bool confirm=false;};
struct AdapterResponse {
 AdapterOp op=AdapterOp::Readings;ResultCode code=ResultCode::Applied;uint32_t token=0;
 char message[140]={};AdapterReadings readings;AdapterAction action;GraphInfo graph;
 uint32_t offset=0;uint8_t count=0;GraphPoint points[4];
};
inline bool adapterMutation(AdapterOp op){return op==AdapterOp::Execute||op==AdapterOp::DiscoverDut||op==AdapterOp::Refresh||uint8_t(op)>=7;}
inline const char* adapterPropertyName(uint16_t id){
 static const char*const names[]={"Cached battery data","Pack voltage","Battery current","SOC","Temperature","Design capacity","Full-charge capacity","Remaining capacity","String count"};
 if(id>=0x400&&id<=0x408)return names[id-0x400];
 static const char*const cells[]={"Cell 1 voltage","Cell 2 voltage","Cell 3 voltage","Cell 4 voltage","Cell 5 voltage","Cell 6 voltage","Cell 7 voltage","Cell 8 voltage"};
 if(id>=0x410&&id<=0x417)return cells[id-0x410];
 switch(id){case 0x420:return "BMS health";case 0x421:return "Security";case 0x422:return "Cycles";case 0x430:return "Graph history";case 0x431:return "Graph interval";case 0x432:return "Auto-stop";case 0x433:return "Current deadband";case 0x440:return "Design voltage";case 0x441:return "Charging voltage";case 0x442:return "Charging current";case 0x443:return "Manufacture date";case 0x480:return "Discover DUT";case 0x481:return "Refresh DUT";case 0x482:return "Invoke action";case 0x483:return "Start/resume graph";case 0x484:return "Pause graph";case 0x485:return "Clear graph";case 0x486:return "Configure graph";case 0x487:return "Action catalog";default:return nullptr;}
}
inline CapabilityPage adapterCapabilities(uint8_t page){
 static const uint16_t ids[]={0x400,0x401,0x402,0x403,0x404,0x405,0x406,0x407,0x408,0x410,0x411,0x412,0x413,0x414,0x415,0x416,0x417,0x420,0x421,0x422,0x430,0x431,0x432,0x433,0x440,0x441,0x442,0x443,0x480,0x481,0x482,0x483,0x484,0x485,0x486,0x487};
 CapabilityPage out;out.page=page;out.pageCount=8;out.revision=2;if(page>=out.pageCount)return out;
 for(unsigned i=unsigned(page)*5;i<sizeof(ids)/sizeof(ids[0])&&out.count<5;i++){
  uint16_t id=ids[i];auto&d=out.properties[out.count++];d.id=Property(id);d.access=Access::Read;d.type=ValueType::UInt32;d.flags=Conditional|MonitoringOnly;d.step=1;d.maximum=UINT32_MAX;
  if(id>=0x480&&id<=0x486){d.access=Access::Command;d.type=ValueType::Command;d.flags=0;d.maximum=d.step=0;}
  else if(id==0x400||id==0x421||id==0x430||id==0x443||id==0x487){d.type=ValueType::Identifier;d.maximum=d.step=0;}
  else if(id==0x401||(id>=0x410&&id<=0x417)||id==0x440||id==0x441){d.unit=Unit::mV;}
  else if(id==0x402){d.unit=Unit::mA;d.type=ValueType::Int32;d.minimum=INT32_MIN;d.maximum=INT32_MAX;}
  else if(id==0x404){d.unit=Unit::CentiCelsius;d.type=ValueType::Int32;d.minimum=INT32_MIN;d.maximum=INT32_MAX;}
  else if(id==0x403||id==0x420){d.unit=Unit::Percent;d.maximum=id==0x403?300:150;}
  else if(id>=0x405&&id<=0x407){d.unit=Unit::MilliAh;}
  else if(id==0x408||id==0x422){d.unit=Unit::Count;d.maximum=id==0x408?8:65535;}
  else if(id==0x431){d.unit=Unit::Seconds;d.minimum=1;d.maximum=3600;}
  else if(id==0x432){d.unit=Unit::Boolean;d.type=ValueType::Boolean;d.maximum=1;d.access=Access::ProfileWrite;d.flags=CompleteProfile;}
  else if(id==0x433){d.unit=Unit::mA;d.maximum=32767;d.access=Access::ProfileWrite;d.flags=CompleteProfile;}
  else if(id==0x442){d.unit=Unit::mA;d.maximum=65535;}
 }return out;
}
inline void put(Writer&w,const AdapterRequest&v){w.u8(uint8_t(v.op));w.u16(v.index);w.u32(v.targetRevision);w.u32(v.recordingId);w.u32(v.generation);w.u32(v.offset);w.u8(v.autoStop);w.u16(v.deadband_mA);w.u8(v.confirmed);w.u32(v.token);}
inline void get(Reader&r,AdapterRequest&v){v.op=AdapterOp(r.u8());v.index=r.u16();v.targetRevision=r.u32();v.recordingId=r.u32();v.generation=r.u32();v.offset=r.u32();uint8_t a=r.u8();v.deadband_mA=r.u16();uint8_t c=r.u8();v.token=r.u32();v.autoStop=a;v.confirmed=c;if(a>1||c>1||uint8_t(v.op)>10)r.skip(r.remaining()+1);}
inline void put(Writer&w,const GraphInfo&v){w.u32(v.recordingId);w.u32(v.generation);w.u32(v.revision);w.u32(v.count);w.u64(v.duration_ms);w.u8(v.recording);w.u8(v.autoStop);w.u16(v.deadband_mA);w.u8(uint8_t(v.stop));}
inline void get(Reader&r,GraphInfo&v){v.recordingId=r.u32();v.generation=r.u32();v.revision=r.u32();v.count=r.u32();v.duration_ms=r.u64();uint8_t b=r.u8(),a=r.u8();v.recording=b;v.autoStop=a;v.deadband_mA=r.u16();v.stop=GraphStop(r.u8());if(b>1||a>1||uint8_t(v.stop)>6)r.skip(r.remaining()+1);}
inline void put(Writer&w,const GraphPoint&v){w.u64(v.at_ms);w.u16(v.validity);w.u32(v.voltage_mV);w.i32(v.current_mA);w.u16(v.soc_percent);for(auto c:v.cells_mV)w.u16(c);w.u8(v.flags);}
inline void get(Reader&r,GraphPoint&v){v.at_ms=r.u64();v.validity=r.u16();v.voltage_mV=r.u32();v.current_mA=r.i32();v.soc_percent=r.u16();for(auto&c:v.cells_mV)c=r.u16();v.flags=r.u8();if(v.flags>7)r.skip(r.remaining()+1);}
inline void put(Writer&w,const AdapterReadings&v){
 w.u32(v.targetRevision);w.u32(v.age_ms);w.u32(v.validity);w.u8(v.address);w.u8(v.stringCount);w.string(v.family,31);w.string(v.flavor,31);w.string(v.security,23);w.string(v.manufactured,15);
 w.u32(v.voltage_mV);w.u32(v.designVoltage_mV);w.u32(v.chargeVoltage_mV);w.u32(v.design_mAh);w.u32(v.full_mAh);w.u32(v.remaining_mAh);w.i32(v.current_mA);w.i32(v.temperature_cC);
 w.u16(v.soc_percent);w.u16(v.health_percent);w.u16(v.cycles);w.u16(v.chargingCurrent_mA);for(auto c:v.cells_mV)w.u16(c);w.u16(v.cellValidity);w.u16(v.batteryStatus);w.u8(v.flags);
}
inline void get(Reader&r,AdapterReadings&v){
 v.targetRevision=r.u32();v.age_ms=r.u32();v.validity=r.u32();v.address=r.u8();v.stringCount=r.u8();r.string(v.family,sizeof v.family);r.string(v.flavor,sizeof v.flavor);r.string(v.security,sizeof v.security);r.string(v.manufactured,sizeof v.manufactured);
 v.voltage_mV=r.u32();v.designVoltage_mV=r.u32();v.chargeVoltage_mV=r.u32();v.design_mAh=r.u32();v.full_mAh=r.u32();v.remaining_mAh=r.u32();v.current_mA=r.i32();v.temperature_cC=r.i32();v.soc_percent=r.u16();v.health_percent=r.u16();v.cycles=r.u16();v.chargingCurrent_mA=r.u16();for(auto&c:v.cells_mV)c=r.u16();v.cellValidity=r.u16();v.batteryStatus=r.u16();v.flags=r.u8();if(v.stringCount>8||v.flags>7)r.skip(r.remaining()+1);
}
inline void put(Writer&w,const AdapterResponse&v){
 w.u8(uint8_t(v.op));w.u8(uint8_t(v.code));w.u32(v.token);
 if(v.code!=ResultCode::Applied){w.string(v.message,139);return;}
 switch(v.op){
 case AdapterOp::Readings:put(w,v.readings);break;
 case AdapterOp::ActionInfo:w.u16(v.action.id);w.u16(v.action.total);w.string(v.action.name,39);w.u8(v.action.confirm);w.string(v.action.confirmation,139);break;
 case AdapterOp::GraphInfo:case AdapterOp::GraphStart:case AdapterOp::GraphPause:case AdapterOp::GraphClear:case AdapterOp::GraphConfig:put(w,v.graph);break;
 case AdapterOp::GraphPage:w.u32(v.graph.recordingId);w.u32(v.graph.generation);w.u32(v.offset);w.u8(v.count);if(v.count>4){w.fail();return;}for(unsigned i=0;i<v.count;i++)put(w,v.points[i]);break;
 default:w.string(v.message,139);break;
 }
}
inline void get(Reader&r,AdapterResponse&v){
 v.op=AdapterOp(r.u8());v.code=ResultCode(r.u8());v.token=r.u32();if(uint8_t(v.op)>10||uint8_t(v.code)>3){r.skip(r.remaining()+1);return;}
 if(v.code!=ResultCode::Applied){r.string(v.message,sizeof v.message);return;}
 switch(v.op){
 case AdapterOp::Readings:get(r,v.readings);break;
 case AdapterOp::ActionInfo:{v.action.id=r.u16();v.action.total=r.u16();r.string(v.action.name,sizeof v.action.name);uint8_t c=r.u8();v.action.confirm=c;r.string(v.action.confirmation,sizeof v.action.confirmation);if(c>1)r.skip(r.remaining()+1);break;}
 case AdapterOp::GraphInfo:case AdapterOp::GraphStart:case AdapterOp::GraphPause:case AdapterOp::GraphClear:case AdapterOp::GraphConfig:get(r,v.graph);break;
 case AdapterOp::GraphPage:v.graph.recordingId=r.u32();v.graph.generation=r.u32();v.offset=r.u32();v.count=r.u8();if(v.count>4){r.skip(r.remaining()+1);return;}for(unsigned i=0;i<v.count;i++)get(r,v.points[i]);break;
 default:r.string(v.message,sizeof v.message);break;
 }
}
} // namespace lablink
