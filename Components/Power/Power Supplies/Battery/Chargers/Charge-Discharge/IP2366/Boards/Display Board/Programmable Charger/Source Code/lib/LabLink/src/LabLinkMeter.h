#pragma once
// LabLink 1.1 meter extension. Charger layouts and identifiers stay unchanged.
namespace lablink {
enum class MeterState:uint8_t { Ready=0,Recording=1,Completed=2 };
enum class MeterStopReason:uint8_t { None=0,Manual=1,AutoStop=2,FixedLength=3,Remote=4 };
enum MeterValidity:uint16_t { MeterVoltageValid=1,MeterCurrentValid=2,MeterPowerValid=4,
 MeterInternalValid=8,MeterExternalValid=16,MeterTotalsValid=32 };
enum MeterQuality:uint16_t { MeterIncomplete=1 };
enum class MeterProperty:uint16_t {
 Voltage=0x300,Current=0x301,Power=0x302,InternalTemperature=0x303,ExternalTemperature=0x304,
 Charge=0x305,Energy=0x306,Duration=0x307,State=0x308,StopReason=0x309,
 Interval=0x310,Length=0x311,AutoStop=0x312,Start=0x380,Stop=0x381,Clear=0x382
};
constexpr uint32_t MeterRequiredCapabilities=CanSubscribe|HasCapabilities|MeterPoll|MeterRecord|MeterClearConfirmed;
struct MeterConfig {uint32_t interval_s=5;int32_t length_s=-1;bool autoStop=false;};
inline bool validMeterConfig(const MeterConfig& c) {
 return c.interval_s>=1&&c.interval_s<=86400&&(c.length_s==-1||(c.length_s>=1&&c.length_s<=31536000));
}
struct MeterReadings {
 MeterState state=MeterState::Ready;MeterStopReason stopReason=MeterStopReason::None;
 uint16_t validity=0,quality=0;uint8_t temperaturePresent=0;
 uint32_t electricalAge_ms=UINT32_MAX,temperatureAge_ms=UINT32_MAX;
 uint32_t voltage_mV=0;int32_t current_mA=0,power_mW=0,internal_cC=0,external_cC=0;
 int64_t charge_uAh=0,energy_uWh=0;uint64_t duration_ms=0;
};
struct MeterClear {bool confirmed=false;uint32_t token=0;};
struct MeterResult {ResultCode code=ResultCode::Applied;uint16_t reason=0;uint32_t token=0;char message[96]={};};
inline void put(Writer&w,const MeterConfig&v){w.u32(v.interval_s);w.i32(v.length_s);w.u8(v.autoStop);}
inline void get(Reader&r,MeterConfig&v){v.interval_s=r.u32();v.length_s=r.i32();uint8_t b=r.u8();v.autoStop=b==1;if(b>1||!validMeterConfig(v))r.skip(r.remaining()+1);}
inline void put(Writer&w,const MeterReadings&v){
 w.u8(uint8_t(v.state));w.u8(uint8_t(v.stopReason));w.u16(v.validity);w.u16(v.quality);w.u8(v.temperaturePresent);
 w.u32(v.electricalAge_ms);w.u32(v.temperatureAge_ms);w.u32(v.voltage_mV);w.i32(v.current_mA);w.i32(v.power_mW);
 w.i32(v.internal_cC);w.i32(v.external_cC);w.i64(v.charge_uAh);w.i64(v.energy_uWh);w.u64(v.duration_ms);
}
inline void get(Reader&r,MeterReadings&v){
 v.state=MeterState(r.u8());v.stopReason=MeterStopReason(r.u8());v.validity=r.u16();v.quality=r.u16();v.temperaturePresent=r.u8();
 v.electricalAge_ms=r.u32();v.temperatureAge_ms=r.u32();v.voltage_mV=r.u32();v.current_mA=r.i32();v.power_mW=r.i32();
 v.internal_cC=r.i32();v.external_cC=r.i32();v.charge_uAh=r.i64();v.energy_uWh=r.i64();v.duration_ms=r.u64();
 if(uint8_t(v.state)>2||uint8_t(v.stopReason)>4||v.temperaturePresent>3)r.skip(r.remaining()+1);
}
inline void put(Writer&w,const MeterClear&v){w.u8(v.confirmed);w.u32(v.token);}
inline void get(Reader&r,MeterClear&v){uint8_t b=r.u8();v.confirmed=b==1;v.token=r.u32();if(b>1)r.skip(r.remaining()+1);}
inline void put(Writer&w,const MeterResult&v){w.u8(uint8_t(v.code));w.u16(v.reason);w.u32(v.token);w.string(v.message,95);}
inline void get(Reader&r,MeterResult&v){v.code=ResultCode(r.u8());v.reason=r.u16();v.token=r.u32();r.string(v.message,sizeof v.message);if(uint8_t(v.code)>3)r.skip(r.remaining()+1);}
inline const char* meterPropertyName(uint16_t id){
 switch(MeterProperty(id)){
 case MeterProperty::Voltage:return "Voltage";case MeterProperty::Current:return "Signed current";case MeterProperty::Power:return "Signed power";
 case MeterProperty::InternalTemperature:return "Internal NTC";case MeterProperty::ExternalTemperature:return "External NTC";
 case MeterProperty::Charge:return "Net charge";case MeterProperty::Energy:return "Net energy";case MeterProperty::Duration:return "Recording duration";
 case MeterProperty::State:return "Recording state";case MeterProperty::StopReason:return "Recording stop reason";
 case MeterProperty::Interval:return "Recording interval";case MeterProperty::Length:return "Recording length";case MeterProperty::AutoStop:return "AutoStop";
 case MeterProperty::Start:return "Configure and record";case MeterProperty::Stop:return "Stop recording";case MeterProperty::Clear:return "Confirmed clear";
 default:return nullptr;
 }
}
// Representation ranges, not hardware ratings. An adapter narrows these to its
// verified acquisition bounds. Length has a reserved -1; zero is invalid.
inline CapabilityPage meterCapabilities(uint8_t page) {
 CapabilityPage c;c.page=page;c.pageCount=4;c.revision=1;
 const MeterProperty ids[]={MeterProperty::Voltage,MeterProperty::Current,MeterProperty::Power,MeterProperty::InternalTemperature,MeterProperty::ExternalTemperature,
 MeterProperty::Charge,MeterProperty::Energy,MeterProperty::Duration,MeterProperty::State,MeterProperty::StopReason,
 MeterProperty::Interval,MeterProperty::Length,MeterProperty::AutoStop,MeterProperty::Start,MeterProperty::Stop,MeterProperty::Clear};
 if(page>=c.pageCount){c.count=0;return c;}
 for(unsigned j=unsigned(page)*5;j<16&&c.count<5;j++){
  auto&d=c.properties[c.count++];d.id=Property(uint16_t(ids[j]));d.step=1;d.flags=MonitoringOnly;d.type=ValueType::Int32;
  switch(ids[j]){
  case MeterProperty::Voltage:d.unit=Unit::mV;d.type=ValueType::UInt32;d.maximum=UINT32_MAX;d.flags|=Measured;break;
  case MeterProperty::Current:case MeterProperty::Power:d.unit=ids[j]==MeterProperty::Current?Unit::mA:Unit::mW;d.minimum=INT32_MIN;d.maximum=INT32_MAX;d.flags|=ids[j]==MeterProperty::Current?Measured:Calculated;break;
  case MeterProperty::InternalTemperature:case MeterProperty::ExternalTemperature:d.unit=Unit::CentiCelsius;d.minimum=INT32_MIN;d.maximum=INT32_MAX;d.flags|=Measured|Conditional;break;
  case MeterProperty::Charge:case MeterProperty::Energy:d.unit=ids[j]==MeterProperty::Charge?Unit::MicroAh:Unit::MicroWh;d.type=ValueType::Int64;d.minimum=INT64_MIN;d.maximum=INT64_MAX;d.flags|=Calculated;break;
  case MeterProperty::Duration:d.unit=Unit::Milliseconds;d.type=ValueType::UInt64;d.maximum=INT64_MAX;break;
  case MeterProperty::State:case MeterProperty::StopReason:d.unit=Unit::Enumeration;d.type=ValueType::Enumeration;d.maximum=ids[j]==MeterProperty::State?2:4;d.enumMask=ids[j]==MeterProperty::State?7:31;break;
  case MeterProperty::Interval:d.unit=Unit::Seconds;d.type=ValueType::UInt32;d.minimum=1;d.maximum=86400;d.access=Access::ProfileWrite;d.flags=CompleteProfile;break;
  case MeterProperty::Length:d.unit=Unit::Seconds;d.minimum=-1;d.maximum=31536000;d.access=Access::ProfileWrite;d.flags=CompleteProfile;break;
  case MeterProperty::AutoStop:d.unit=Unit::Boolean;d.type=ValueType::Boolean;d.maximum=1;d.access=Access::ProfileWrite;d.flags=CompleteProfile;break;
  default:d.access=Access::Command;d.type=ValueType::Command;d.flags=0;break;
  }
 }
 return c;
}
} // namespace lablink
