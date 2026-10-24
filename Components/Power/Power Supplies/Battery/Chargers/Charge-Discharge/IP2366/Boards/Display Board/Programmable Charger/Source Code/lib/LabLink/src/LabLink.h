#pragma once
// LabLink 1.0: portable, bounded, explicit little-endian wire codec.
#include <stddef.h>
#include <stdint.h>
#include <string.h>

namespace lablink {
constexpr size_t MaxPacket=250, HeaderSize=40, MaxPayload=MaxPacket-HeaderSize;
constexpr uint8_t ProtocolMajor=1, ProtocolMinor=2;
constexpr uint32_t HeartbeatInterval_ms=1000, OwnerTimeout_ms=10000;
enum class EquipmentType:uint16_t { Unspecified=0,Charger=1,ElectronicLoad=2,CurrentMeter=3,SMBusAdapter=4,PowerSupply=5,UsbPdTrigger=6 };
enum class Kind:uint8_t { Discover=1,Advertise=2,Subscribe=3,Unsubscribe=4,Heartbeat=5,HeartbeatAck=6,GetCapabilities=7,Capabilities=8,GetConfig=9,Config=10,Telemetry=11,Start=12,Abort=13,Result=14,GetMeterReadings=32,MeterReadings=33,GetMeterConfig=34,MeterConfig=35,MeterStart=36,MeterStop=37,MeterClear=38,MeterResult=39,AdapterRequest=48,AdapterResponse=49 };
enum class ResultCode:uint8_t { Applied=0,Rejected=1,ConfirmationRequired=2,Timeout=3 };
enum class OperatingState:uint8_t { Missing=0,Idle=1,Starting=2,Charging=3,Complete=4,Aborted=5,Fault=6 };
enum Capability:uint32_t { CanSubscribe=1u,CanReadConfig=2u,CanStart=4u,CanAbort=8u,OwnerHeartbeat=16u,HasCapabilities=32u,MeterPoll=256u,MeterRecord=512u,MeterClearConfirmed=1024u,MeterTemperatures=2048u };
enum Validity:uint16_t { VoltageValid=1u,CurrentValid=2u,TemperatureValid=4u,SocValid=8u,TotalsValid=16u };
enum class Access:uint8_t { Read=1,ProfileWrite=3,Command=4 };
enum class Unit:uint8_t { None=0,Enumeration=1,Count=2,mV=3,mA=4,Percent=5,CentiCelsius=6,Milliseconds=7,MicroAh=8,MicroWh=9,DeviceId=10,Boolean=11,mW=12,Seconds=13,MilliAh=14 };
enum class ValueType:uint8_t { Unsigned=0,Signed=1,Enumeration=2,Boolean=3,Identifier=4,Command=5,UInt8=6,UInt16=7,UInt32=8,UInt64=9,Int32=10,Int64=11 };
enum class StopReason:uint16_t { None=0,Complete=1,Abort=2,OwnerLost=3,HardwareFault=4,Startup=5,Communication=6 };
enum PropertyFlag:uint16_t { Measured=1u,Estimated=2u,Calculated=4u,MonitoringOnly=8u,CompleteProfile=16u,DynamicLimit=32u,SignedChargePositive=64u,Conditional=128u };
enum class Property:uint16_t {
 Chemistry=0x100,SeriesCells=0x101,CellEndVoltage=0x102,TargetPercent=0x103,RequestedCurrent=0x104,TerminationCurrent=0x105,
 EffectiveCurrent=0x106,TargetPackVoltage=0x107,BatteryVoltage=0x110,BatteryCurrent=0x111,NtcTemperature=0x112,EstimatedSoc=0x113,
 ElapsedTime=0x114,DeliveredCharge=0x115,DeliveredEnergy=0x116,OperatingState=0x120,StopReason=0x121,SessionOwner=0x122,
 ConfigureAndStart=0x180,Abort=0x181,Subscribe=0x182,Unsubscribe=0x183
};
struct Header { Kind kind=Kind::Discover;uint16_t flags=0;uint32_t sequence=0,replyTo=0;uint64_t deviceId=0;uint32_t bootId=0,targetBootId=0,sessionId=0; };
struct Packet { Header header;uint8_t payload[MaxPayload]={};uint16_t payloadLength=0; };
struct Received { uint8_t mac[6]={};Packet packet;uint32_t receivedAt_ms=0; };
class Writer {
 uint8_t* data_;size_t capacity_,position_=0;bool good_=true;
 public:
 Writer(uint8_t* data,size_t capacity):data_(data),capacity_(capacity){}
 bool good()const{return good_;}size_t size()const{return position_;}void fail(){good_=false;}
 void u8(uint8_t value){if(position_<capacity_)data_[position_++]=value;else good_=false;}
 void u16(uint16_t value){u8(uint8_t(value));u8(uint8_t(value>>8));}
 void u32(uint32_t value){u16(uint16_t(value));u16(uint16_t(value>>16));}
 void u64(uint64_t value){u32(uint32_t(value));u32(uint32_t(value>>32));}
 void i32(int32_t value){u32(uint32_t(value));}void i64(int64_t value){u64(uint64_t(value));}
 void bytes(const uint8_t* data,size_t length){for(size_t i=0;i<length;i++)u8(data[i]);}
 void string(const char* value,size_t maxLength){size_t n=0;while(n<maxLength&&value[n])++n;if(n>255){good_=false;return;}u8(uint8_t(n));bytes(reinterpret_cast<const uint8_t*>(value),n);}
};
class Reader {
 const uint8_t* data_;size_t length_,position_=0;bool good_=true;
 public:
 Reader(const uint8_t* data,size_t length):data_(data),length_(length){}
 bool good()const{return good_;}size_t remaining()const{return position_<=length_?length_-position_:0;}
 uint8_t u8(){if(position_<length_)return data_[position_++];good_=false;return 0;}
 uint16_t u16(){uint16_t lo=u8();return uint16_t(lo|(uint16_t(u8())<<8));}
 uint32_t u32(){uint32_t lo=u16();return lo|(uint32_t(u16())<<16);}
 uint64_t u64(){uint64_t lo=u32();return lo|(uint64_t(u32())<<32);}
 int32_t i32(){uint32_t v=u32();return v<=0x7fffffffu?int32_t(v):int32_t(int64_t(v)-4294967296LL);}
 int64_t i64(){uint64_t v=u64();return v<=0x7fffffffffffffffULL?int64_t(v):-1-int64_t(~v);}
 void bytes(uint8_t* out,size_t n){for(size_t i=0;i<n;i++)out[i]=u8();}
 void skip(size_t n){if(n<=remaining())position_+=n;else good_=false;}
 void string(char* out,size_t capacity){size_t n=u8();if(!capacity){good_=false;return;}if(n>=capacity||n>remaining()){out[0]=0;good_=false;return;}bytes(reinterpret_cast<uint8_t*>(out),n);out[n]=0;}
};
inline bool knownKind(Kind k){return (uint8_t(k)>=1&&uint8_t(k)<=14)||(uint8_t(k)>=32&&uint8_t(k)<=39)||k==Kind::AdapterRequest||k==Kind::AdapterResponse;}
inline size_t encode(const Packet& p,uint8_t* out,size_t capacity){
 if(!out||p.payloadLength>MaxPayload||capacity<HeaderSize+p.payloadLength||!knownKind(p.header.kind)||p.header.flags||!p.header.sequence||!p.header.deviceId||!p.header.bootId)return 0;
 Writer w(out,capacity);w.u32(0x314c414cu);w.u8(ProtocolMajor);w.u8(ProtocolMinor);w.u8(uint8_t(p.header.kind));w.u8(HeaderSize);w.u16(p.header.flags);w.u16(p.payloadLength);
 w.u32(p.header.sequence);w.u32(p.header.replyTo);w.u64(p.header.deviceId);w.u32(p.header.bootId);w.u32(p.header.targetBootId);w.u32(p.header.sessionId);w.bytes(p.payload,p.payloadLength);return w.good()?w.size():0;
}
inline bool decode(const uint8_t* data,size_t length,Packet& out){
 if(!data||length<HeaderSize||length>MaxPacket)return false;Reader r(data,length);if(r.u32()!=0x314c414cu||r.u8()!=ProtocolMajor)return false;
 (void)r.u8();Packet p;p.header.kind=Kind(r.u8());uint8_t headerSize=r.u8();p.header.flags=r.u16();p.payloadLength=r.u16();
 if(headerSize<HeaderSize||headerSize>length||p.payloadLength!=length-headerSize||p.payloadLength>MaxPayload||p.header.flags||!knownKind(p.header.kind))return false;
 p.header.sequence=r.u32();p.header.replyTo=r.u32();p.header.deviceId=r.u64();p.header.bootId=r.u32();p.header.targetBootId=r.u32();p.header.sessionId=r.u32();r.skip(headerSize-HeaderSize);r.bytes(p.payload,p.payloadLength);
 if(!r.good()||!p.header.deviceId||!p.header.bootId||!p.header.sequence)return false;out=p;return true;
}
inline bool newerSequence(uint32_t value,uint32_t previous){uint32_t delta=value-previous;return delta!=0&&delta<0x80000000u;}
inline uint32_t elapsed(uint32_t now,uint32_t then){return now-then;}
inline bool sameMac(const uint8_t* a,const uint8_t* b){return memcmp(a,b,6)==0;}
inline uint64_t deviceIdFromMac(const uint8_t mac[6]){uint64_t id=0x4c4c000000000000ULL;for(unsigned i=0;i<6;i++)id|=uint64_t(mac[i])<<(8*(5-i));return id;}
struct Advertisement { EquipmentType type=EquipmentType::Unspecified;uint32_t capabilities=0;uint8_t channel=0;char name[32]={},firmware[20]={}; };
// chemistry: 0 LiFePO4, 1 Li-ion, 2 LiHV. Configuration is always a complete profile.
struct ChargerConfig {uint8_t chemistry=0,cells=4,targetPercent=100;uint16_t cell_mV=3650,current_mA=1000,termination_mA=100;};
inline bool sameConfig(const ChargerConfig&a,const ChargerConfig&b){return a.chemistry==b.chemistry&&a.cells==b.cells&&a.targetPercent==b.targetPercent&&a.cell_mV==b.cell_mV&&a.current_mA==b.current_mA&&a.termination_mA==b.termination_mA;}
struct StartRequest {ChargerConfig config;bool proceed=false;uint32_t confirmationToken=0;};
struct Subscription {uint32_t subscriptionId=0;uint16_t interval_ms=1000;};
struct Heartbeat {uint32_t subscriptionId=0;bool owner=false;};
struct HeartbeatAck {uint32_t subscriptionId=0;uint8_t channel=0;bool owner=false;};
struct Result {ResultCode code=ResultCode::Applied;uint16_t reason=0;uint32_t confirmationToken=0;ChargerConfig effective;char message[96]={};};
struct Telemetry {
 OperatingState state=OperatingState::Idle;uint16_t stopReason=0,validity=0;uint32_t sampleAge_ms=0;
 uint32_t voltage_mV=0;int32_t current_mA=0,temperature_cC=0;uint8_t soc_percent=0;uint32_t elapsed_ms=0;
 uint64_t charge_uAh=0,energy_uWh=0,ownerDeviceId=0;uint32_t ownerBootId=0;bool disableConfirmed=false;
 uint32_t target_mV=0,effectiveCurrent_mA=0;uint16_t termination_mA=0;uint32_t ownerRemaining_ms=0;
};
struct PropertyDescriptor {Property id=Property::Chemistry;Access access=Access::Read;Unit unit=Unit::None;ValueType type=ValueType::Unsigned;uint16_t flags=0;int64_t minimum=0,maximum=0,step=0;uint32_t enumMask=0;};
constexpr uint8_t PropertiesPerPage=5;
struct CapabilityPage {uint8_t page=0,pageCount=0,count=0;uint32_t revision=1;PropertyDescriptor properties[PropertiesPerPage];};
struct CapabilityRequest {uint8_t page=0;};
inline void configWrite(Writer&w,const ChargerConfig&v){w.u8(v.chemistry);w.u8(v.cells);w.u8(v.targetPercent);w.u16(v.cell_mV);w.u16(v.current_mA);w.u16(v.termination_mA);}
inline void configRead(Reader&r,ChargerConfig&v){v.chemistry=r.u8();v.cells=r.u8();v.targetPercent=r.u8();v.cell_mV=r.u16();v.current_mA=r.u16();v.termination_mA=r.u16();}
inline void put(Writer&w,const Advertisement&v){w.u16(uint16_t(v.type));w.u32(v.capabilities);w.u8(v.channel);w.string(v.name,31);w.string(v.firmware,19);}
inline void get(Reader&r,Advertisement&v){v.type=EquipmentType(r.u16());v.capabilities=r.u32();v.channel=r.u8();r.string(v.name,sizeof v.name);r.string(v.firmware,sizeof v.firmware);}
inline void put(Writer&w,const ChargerConfig&v){configWrite(w,v);}inline void get(Reader&r,ChargerConfig&v){configRead(r,v);}
inline void put(Writer&w,const StartRequest&v){configWrite(w,v.config);w.u8(v.proceed?1:0);w.u32(v.confirmationToken);}
inline void get(Reader&r,StartRequest&v){configRead(r,v.config);uint8_t b=r.u8();v.proceed=b==1;if(b>1){r.skip(r.remaining()+1);return;}v.confirmationToken=r.u32();}
inline void put(Writer&w,const Subscription&v){w.u32(v.subscriptionId);w.u16(v.interval_ms);}inline void get(Reader&r,Subscription&v){v.subscriptionId=r.u32();v.interval_ms=r.u16();}
inline void put(Writer&w,const Heartbeat&v){w.u32(v.subscriptionId);w.u8(v.owner?1:0);}inline void get(Reader&r,Heartbeat&v){v.subscriptionId=r.u32();uint8_t b=r.u8();v.owner=b==1;if(b>1)r.skip(r.remaining()+1);}
inline void put(Writer&w,const HeartbeatAck&v){w.u32(v.subscriptionId);w.u8(v.channel);w.u8(v.owner?1:0);}inline void get(Reader&r,HeartbeatAck&v){v.subscriptionId=r.u32();v.channel=r.u8();uint8_t b=r.u8();v.owner=b==1;if(b>1)r.skip(r.remaining()+1);}
inline void put(Writer&w,const Result&v){w.u8(uint8_t(v.code));w.u16(v.reason);w.u32(v.confirmationToken);configWrite(w,v.effective);w.string(v.message,95);}
inline void get(Reader&r,Result&v){v.code=ResultCode(r.u8());v.reason=r.u16();v.confirmationToken=r.u32();configRead(r,v.effective);r.string(v.message,sizeof v.message);if(uint8_t(v.code)>3)r.skip(r.remaining()+1);}
inline void put(Writer&w,const Telemetry&v){w.u8(uint8_t(v.state));w.u16(v.stopReason);w.u16(v.validity);w.u32(v.sampleAge_ms);w.u32(v.voltage_mV);w.i32(v.current_mA);w.i32(v.temperature_cC);w.u8(v.soc_percent);w.u32(v.elapsed_ms);w.u64(v.charge_uAh);w.u64(v.energy_uWh);w.u64(v.ownerDeviceId);w.u32(v.ownerBootId);w.u8(v.disableConfirmed?1:0);w.u32(v.target_mV);w.u32(v.effectiveCurrent_mA);w.u16(v.termination_mA);w.u32(v.ownerRemaining_ms);}
inline void get(Reader&r,Telemetry&v){v.state=OperatingState(r.u8());v.stopReason=r.u16();v.validity=r.u16();v.sampleAge_ms=r.u32();v.voltage_mV=r.u32();v.current_mA=r.i32();v.temperature_cC=r.i32();v.soc_percent=r.u8();v.elapsed_ms=r.u32();v.charge_uAh=r.u64();v.energy_uWh=r.u64();v.ownerDeviceId=r.u64();v.ownerBootId=r.u32();uint8_t b=r.u8();v.disableConfirmed=b==1;v.target_mV=r.u32();v.effectiveCurrent_mA=r.u32();v.termination_mA=r.u16();v.ownerRemaining_ms=r.u32();if(b>1||uint8_t(v.state)>6||v.soc_percent>100)r.skip(r.remaining()+1);}
inline void put(Writer&w,const CapabilityRequest&v){w.u8(v.page);}inline void get(Reader&r,CapabilityRequest&v){v.page=r.u8();}
inline void put(Writer&w,const CapabilityPage&v){w.u8(v.page);w.u8(v.pageCount);w.u8(v.count);w.u32(v.revision);if(v.count>PropertiesPerPage){w.fail();return;}for(unsigned i=0;i<v.count;i++){const auto&p=v.properties[i];w.u8(35);w.u16(uint16_t(p.id));w.u8(uint8_t(p.access));w.u8(uint8_t(p.unit));w.u8(uint8_t(p.type));w.u16(p.flags);w.i64(p.minimum);w.i64(p.maximum);w.i64(p.step);w.u32(p.enumMask);}}
inline void get(Reader&r,CapabilityPage&v){v.page=r.u8();v.pageCount=r.u8();v.count=r.u8();v.revision=r.u32();if(v.count>PropertiesPerPage||!v.pageCount||v.page>=v.pageCount){r.skip(r.remaining()+1);return;}for(unsigned i=0;i<v.count;i++){uint8_t n=r.u8();if(n<35||n>r.remaining()){r.skip(r.remaining()+1);return;}auto&p=v.properties[i];p.id=Property(r.u16());p.access=Access(r.u8());p.unit=Unit(r.u8());p.type=ValueType(r.u8());p.flags=r.u16();p.minimum=r.i64();p.maximum=r.i64();p.step=r.i64();p.enumMask=r.u32();r.skip(n-35);}}
template<class T> inline bool write(Packet&p,const T&v){Writer w(p.payload,MaxPayload);put(w,v);p.payloadLength=w.good()?uint16_t(w.size()):0;return w.good();}
template<class T> inline bool read(const Packet&p,T&v){if(p.payloadLength>MaxPayload)return false;Reader r(p.payload,p.payloadLength);T candidate;get(r,candidate);if(!r.good())return false;v=candidate;return true;}
// All typed payloads accept trailing bytes for compatible future minor extensions.
class Transport {
 public: virtual ~Transport(){};virtual bool receive(Received&)=0;virtual bool send(const uint8_t mac[6],const Packet&)=0;
 virtual bool setChannel(uint8_t)=0;virtual uint8_t channel()const=0;virtual uint8_t firstChannel()const{return 1;}virtual uint8_t channelCount()const{return 11;}
};
} // namespace lablink

#if defined(ARDUINO_ARCH_ESP32)
#include "LabLinkEspNow.h"
#endif
#include "LabLinkMeter.h"
#include "LabLinkAdapter.h"
#include "LabLinkClient.h"
