#include "LabLink.h"
#include <assert.h>
#include <stdio.h>
#include <deque>
#include <vector>
#include <limits>
using namespace lablink;
static Packet base(Kind kind=Kind::Discover){Packet p;p.header.kind=kind;p.header.sequence=0x12345678;p.header.deviceId=0x4c4c010203040506ULL;p.header.bootId=0x1234;return p;}
struct Fake:Transport {
 std::deque<Received> incoming;std::vector<Packet> sent;std::vector<uint8_t> hops;uint8_t ch=1;
 bool receive(Received&r)override{if(incoming.empty())return false;r=incoming.front();incoming.pop_front();return true;}
 bool send(const uint8_t*,const Packet&p)override{sent.push_back(p);return true;}
 bool setChannel(uint8_t c)override{ch=c;hops.push_back(c);return true;}uint8_t channel()const override{return ch;}
 void push(Packet p){Received r;r.packet=p;uint8_t mac[6]={1,2,3,4,5,6};memcpy(r.mac,mac,6);incoming.push_back(r);}
 Packet last(Kind k){for(auto i=sent.rbegin();i!=sent.rend();i++)if(i->header.kind==k)return *i;assert(false);return Packet();}
};
static Packet reply(Kind k,uint32_t seq=1,uint32_t replyTo=0){auto p=base(k);p.header.sequence=seq;p.header.deviceId=7;p.header.bootId=8;p.header.targetBootId=10;p.header.replyTo=replyTo;return p;}
static void advertise(Fake&f,uint32_t boot=8){auto p=reply(Kind::Advertise);p.header.bootId=boot;p.header.targetBootId=0;Advertisement a;a.type=EquipmentType::Charger;a.channel=6;strcpy(a.name,"charger1");write(p,a);f.push(p);}
static void subscribe(Fake&f,Client&c,uint32_t now=1){advertise(f);c.tick(now);assert(c.deviceCount()==1);assert(c.select(0));auto sub=f.last(Kind::Subscribe);Subscription s;assert(read(sub,s));auto p=reply(Kind::Result,1,sub.header.sequence);Result r;write(p,r);f.push(p);c.tick(now+1);auto hb=f.last(Kind::Heartbeat);Heartbeat h;assert(read(hb,h));assert(!h.owner&&h.subscriptionId==s.subscriptionId);auto ack=reply(Kind::HeartbeatAck,2,hb.header.sequence);HeartbeatAck a;a.subscriptionId=s.subscriptionId;a.channel=6;write(ack,a);f.push(ack);c.tick(now+2);assert(c.connected());}
static void codecTests(){
 auto p=base();uint8_t data[250];size_t n=encode(p,data,sizeof data);assert(n==40);assert(data[0]=='L'&&data[1]=='A'&&data[2]=='L'&&data[3]=='1');assert(data[12]==0x78&&data[15]==0x12);assert(data[20]==6&&data[25]==1);Packet decoded;assert(decode(data,n,decoded));assert(decoded.header.deviceId==p.header.deviceId);
 for(size_t i=0;i<40;i++)assert(!decode(data,i,decoded));data[4]=2;assert(!decode(data,n,decoded));data[4]=1;data[11]=1;assert(!decode(data,n,decoded));data[11]=0;data[9]=1;assert(!decode(data,n,decoded));data[9]=0;data[7]=39;assert(!decode(data,n,decoded));
 p=base(Kind::Telemetry);Telemetry t;t.state=OperatingState::Charging;t.voltage_mV=14600;t.current_mA=-120;t.temperature_cC=-1234;t.validity=VoltageValid|CurrentValid|TemperatureValid;t.charge_uAh=10000000000ULL;t.energy_uWh=100000000000ULL;t.ownerDeviceId=0xffffffffffffffffULL;t.soc_percent=99;assert(write(p,t));n=encode(p,data,sizeof data);assert(n<=250);assert(decode(data,n,decoded));Telemetry out;assert(read(decoded,out));assert(out.current_mA==-120&&out.temperature_cC==-1234&&out.charge_uAh==10000000000ULL&&out.voltage_mV==14600);
 auto malformed=p;malformed.payloadLength--;assert(!read(malformed,out));p.payload[p.payloadLength++]=0xaa;assert(read(p,out)); // unknown trailing minor extension
 p=base(Kind::Capabilities);CapabilityPage page;page.pageCount=1;page.count=5;page.properties[0].minimum=std::numeric_limits<int64_t>::min();page.properties[0].maximum=std::numeric_limits<int64_t>::max();assert(write(p,page));assert(p.payloadLength==187);assert(encode(p,data,sizeof data)==227);CapabilityPage pageOut;assert(read(p,pageOut));assert(pageOut.properties[0].minimum==page.properties[0].minimum&&pageOut.properties[0].maximum==page.properties[0].maximum);page.count=6;assert(!write(p,page));
 p=base(Kind::Start);StartRequest s;s.proceed=true;s.confirmationToken=0x12345678;s.config.current_mA=2000;assert(write(p,s));StartRequest start;assert(read(p,start));assert(start.proceed&&start.confirmationToken==s.confirmationToken&&sameConfig(start.config,s.config));p.payload[9]=2;assert(!read(p,start));
 Advertisement a;memset(a.name,'a',31);a.name[31]=0;memset(a.firmware,'b',19);a.firmware[19]=0;p=base(Kind::Advertise);assert(write(p,a));Advertisement b;assert(read(p,b));assert(strcmp(a.name,b.name)==0);p.payload[7]=255;assert(!read(p,b));
 assert(newerSequence(1,0xffffffffu));assert(!newerSequence(0xffffffffu,1));assert(!newerSequence(1,1));assert(elapsed(10,0xfffffff0u)==26);
 uint8_t mac[]={1,2,3,4,5,6};assert(deviceIdFromMac(mac)==0x4c4c010203040506ULL);
}
static void clientTests(){
 Fake f;Client c(f,9,10);subscribe(f,c);assert(c.channel()==6);assert(c.getConfig());auto request=f.last(Kind::GetConfig);auto cp=reply(Kind::Config,3,request.header.sequence);ChargerConfig cfg;cfg.current_mA=2000;write(cp,cfg);f.push(cp);c.tick(4);assert(c.hasConfig()&&c.config().current_mA==2000&&!c.pending());
 assert(c.start(cfg));auto start=f.last(Kind::Start);c.tick(505);auto retry=f.last(Kind::Start);assert(retry.header.sequence==start.header.sequence&&retry.header.bootId==start.header.bootId);
 // New telemetry may arrive before an old cached command ACK. That ACK must still apply.
 assert(c.telemetryAge_ms()==UINT32_MAX);auto tele=reply(Kind::Telemetry,9);tele.header.sessionId=42;Telemetry t;t.state=OperatingState::Starting;t.ownerDeviceId=9;t.ownerBootId=10;t.sampleAge_ms=20;write(tele,t);f.push(tele);c.tick(506);assert(c.ownsSession()&&c.telemetryAge_ms()==20);c.tick(507);assert(c.telemetryAge_ms()==21);
 auto res=reply(Kind::Result,4,start.header.sequence);res.header.sessionId=42;Result result;result.effective=cfg;write(res,result);f.push(res);c.tick(507);assert(!c.pending()&&c.ownsSession()&&c.sessionId()==42);assert(c.select(0)&&c.ownsSession());assert(!c.clearSelection());
 c.tick(1510);assert(c.telemetryAge_ms()==1024);tele.header.sequence=10;t.sampleAge_ms=5;write(tele,t);f.push(tele);c.tick(1511);assert(c.telemetryAge_ms()==5);tele.header.sequence=11;t.sampleAge_ms=UINT32_MAX-2;write(tele,t);f.push(tele);c.tick(1512);c.tick(1515);assert(c.telemetryAge_ms()==UINT32_MAX);Heartbeat h;assert(read(f.last(Kind::Heartbeat),h)&&h.owner);assert(f.last(Kind::Heartbeat).header.sessionId==42);
 c.setHeartbeatEnabled(false);size_t hbCount=0;for(auto&p:f.sent)hbCount+=p.header.kind==Kind::Heartbeat;c.tick(2520);size_t after=0;for(auto&p:f.sent)after+=p.header.kind==Kind::Heartbeat;assert(hbCount==after);c.tick(4020);assert(c.recovering());assert(!f.hops.empty());
 c.setHeartbeatEnabled(true);advertise(f);c.tick(4021);assert(!c.recovering());assert(read(f.last(Kind::Heartbeat),h)&&h.owner);
 assert(c.abort());auto abort=f.last(Kind::Abort);auto stopped=reply(Kind::Result,12,abort.header.sequence);stopped.header.sessionId=42;write(stopped,result);f.push(stopped);c.tick(4022);assert(!c.ownsSession());assert(c.clearSelection());assert(!c.selected()&&!c.hasTelemetry()&&c.telemetryAge_ms()==UINT32_MAX);
 // Server restart invalidates ownership, pending request, and session; never auto-restarts.
 Fake f2;Client c2(f2,9,10);subscribe(f2,c2);assert(c2.start(cfg));auto st=f2.last(Kind::Start);auto rr=reply(Kind::Result,3,st.header.sequence);rr.header.sessionId=42;write(rr,result);f2.push(rr);c2.tick(4);assert(c2.ownsSession());advertise(f2,88);c2.tick(5);assert(!c2.ownsSession()&&c2.sessionId()==0&&!c2.hasTelemetry());
 // Wrong target boot cannot acknowledge a command, nor can malformed payloads.
 auto sub=f2.last(Kind::Subscribe);auto bad=reply(Kind::Result,4,sub.header.sequence);bad.header.bootId=88;bad.header.targetBootId=11;write(bad,result);f2.push(bad);c2.tick(6);assert(!c2.connected());
 Fake f3;Client c3(f3,9,10);subscribe(f3,c3);assert(c3.start(cfg));c3.tick(5004);assert(!c3.pending()&&c3.result().code==ResultCode::Timeout);
}
int main(){codecTests();clientTests();puts("PASS: explicit LE codec/bounds, signed and 64-bit units, descriptor pages, command retry/dedupe, owner heartbeat, stale ACK ordering, channel recovery and reboot invalidation");}
