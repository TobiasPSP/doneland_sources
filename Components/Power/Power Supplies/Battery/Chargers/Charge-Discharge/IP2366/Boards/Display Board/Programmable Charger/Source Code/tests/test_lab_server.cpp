#include "lab_charger_server.h"
#include <assert.h>
#include <deque>
#include <vector>
#include <stdio.h>
using namespace lablink;
using namespace batcharger;
struct Bus;
struct Endpoint:Transport {
 Bus&bus;uint8_t mac[6]={};uint8_t ch=6;bool online=true;std::deque<Received> queue;std::vector<Packet> sent;
 Endpoint(Bus&,uint8_t);
 bool receive(Received&r)override{if(!online||queue.empty())return false;r=queue.front();queue.pop_front();return true;}
 bool send(const uint8_t*destination,const Packet&p)override;
 bool setChannel(uint8_t c)override{ch=c;return true;}uint8_t channel()const override{return ch;}
 Packet last(Kind kind)const{for(auto it=sent.rbegin();it!=sent.rend();++it)if(it->header.kind==kind)return *it;assert(false);return Packet();}
};
struct Bus {uint32_t now=0;std::vector<Endpoint*> endpoints;};
Endpoint::Endpoint(Bus&b,uint8_t id):bus(b){mac[5]=id;bus.endpoints.push_back(this);}
bool Endpoint::send(const uint8_t*destination,const Packet&p){sent.push_back(p);if(!online)return false;bool broadcast=destination[0]==255;for(auto*e:bus.endpoints)if(e!=this&&e->online&&e->ch==ch&&(broadcast||sameMac(destination,e->mac))){Received r;r.packet=p;r.receivedAt_ms=bus.now;memcpy(r.mac,mac,6);e->queue.push_back(r);}return true;}
struct Port:LabChargerPort {
 uint32_t session_=0,revision_=1;bool active_=false,missingBattery=false;unsigned starts=0,aborts=0,ownerAborts=0;ChargerConfig config_;OperatingState state=OperatingState::Idle;
 uint32_t session()const override{return session_;}uint32_t revision()const override{return revision_;}bool active()const override{return active_;}
 ChargerConfig config()const override{return config_;}
 Telemetry telemetry(uint32_t)const override{Telemetry t;t.state=state;t.disableConfirmed=!active_;t.validity=VoltageValid|CurrentValid|TemperatureValid;t.voltage_mV=13600;t.current_mA=active_?2000:0;t.temperature_cC=2600;return t;}
 bool capabilities(uint8_t page,CapabilityPage&out)const override{if(page)return false;out.page=0;out.pageCount=1;out.count=1;out.properties[0].id=Property::SeriesCells;out.properties[0].minimum=2;out.properties[0].maximum=6;return true;}
 Result start(const ChargerConfig&c,bool proceed,uint32_t)override{Result r;r.effective=c;if(missingBattery&&!proceed){r.code=ResultCode::ConfirmationRequired;strcpy(r.message,"No battery detected. Proceed anyway?");return r;}++starts;++session_;config_=c;active_=true;state=OperatingState::Starting;return r;}
 Result abort(uint32_t,bool ownerLost)override{++aborts;ownerAborts+=ownerLost;active_=false;state=OperatingState::Aborted;Result r;r.effective=config_;return r;}
};
struct Rig {
 Bus bus;Endpoint serverWire{bus,1},wire1{bus,2},wire2{bus,3};Port port;
 LabChargerServer server{port,serverWire,100,200,"charger1","test"};Client one{wire1,101,201},two{wire2,102,202};
 void tick(uint32_t time,bool enabled=true){bus.now=time;server.tick(enabled,time);one.tick(time);two.tick(time);server.tick(enabled,time);one.tick(time);two.tick(time);}
 void connect(){tick(1);assert(one.deviceCount()==1&&two.deviceCount()==1);assert(one.select(0)&&two.select(0));tick(2);tick(3);assert(one.connected()&&two.connected()&&server.subscriberCount()==2);}
 void send(Endpoint&from,const Packet&p,uint32_t time){bus.now=time;from.send(serverWire.mac,p);server.tick(true,time);}
};
static void controlAndDuplicates(){Rig r;r.connect();assert(r.one.getCapabilities());r.tick(4);assert(!r.one.pending()&&r.one.capabilities().count==1&&r.one.capabilities().properties[0].maximum==6);
 assert(r.one.getConfig());r.tick(5);assert(r.one.hasConfig());ChargerConfig cfg;cfg.current_mA=2000;assert(r.one.start(cfg));auto original=r.wire1.last(Kind::Start);r.tick(6);assert(r.port.starts==1&&r.server.owner().deviceId()==101&&r.one.ownsSession());
 r.send(r.wire1,original,7);assert(r.port.starts==1);auto changed=original;StartRequest request;read(changed,request);request.config.current_mA=3000;write(changed,request);r.send(r.wire1,changed,8);assert(r.port.starts==1&&r.serverWire.last(Kind::Result).header.replyTo==original.header.sequence);Result result;assert(read(r.serverWire.last(Kind::Result),result)&&result.code==ResultCode::Rejected);
 // Non-owner Abort is allowed for the current session. Telemetry state must first reach observer.
 r.tick(1007);assert(r.two.sessionId()==r.port.session());assert(r.two.abort());r.tick(1008);assert(r.port.aborts==1&&!r.port.active_&&!r.server.owner().owned());
 r.send(r.wire1,original,1009);assert(r.port.starts==1); // cached Start never restarts
 auto stale=original;stale.header.sequence=original.header.sequence-1;r.send(r.wire1,stale,1010);assert(r.port.starts==1);
 // Wrong target boot and session cannot perform a new Start.
 auto wrong=original;wrong.header.sequence=1000;wrong.header.targetBootId=199;r.send(r.wire1,wrong,1011);assert(r.port.starts==1);
 wrong.header.targetBootId=200;wrong.header.sessionId=999;r.send(r.wire1,wrong,1012);assert(r.port.starts==1);
}
static void ownerDeadline(){Rig r;r.connect();ChargerConfig cfg;assert(r.one.start(cfg));r.tick(4);assert(r.server.owner().owned());r.one.setHeartbeatEnabled(false);
 for(uint32_t t=1004;t<=9004;t+=1000)r.tick(t);assert(r.port.active_&&r.port.ownerAborts==0);r.tick(10005);assert(!r.port.active_&&r.port.ownerAborts==1&&!r.server.owner().owned());assert(r.two.connected());
 // Observer keeps receiving and heartbeating; it cannot sustain somebody else's lease.
 assert(r.port.starts==1);r.tick(11005);assert(r.port.ownerAborts==1);
 // A manually started session has no ESP-NOW owner and continues without observers.
 r.port.start(cfg,false,12000);r.wire1.online=r.wire2.online=false;for(uint32_t t=12000;t<=45000;t+=1000)r.tick(t);assert(r.port.active_&&r.port.ownerAborts==1&&!r.server.owner().owned());
}
static void confirmation(){Rig r;r.connect();r.port.missingBattery=true;ChargerConfig cfg;assert(r.one.start(cfg));r.tick(4);assert(r.one.result().code==ResultCode::ConfirmationRequired&&r.one.result().confirmationToken&&r.port.starts==0);uint32_t token=r.one.result().confirmationToken;
 ChargerConfig wrong=cfg;wrong.current_mA=2000;assert(r.one.start(wrong,true,token));r.tick(5);assert(r.one.result().code==ResultCode::Rejected&&r.port.starts==0);
 assert(r.one.start(cfg,true,token));r.tick(6);assert(r.port.starts==1&&r.one.ownsSession());
 Rig revision;revision.connect();revision.port.missingBattery=true;assert(revision.one.start(cfg));revision.tick(4);token=revision.one.result().confirmationToken;++revision.port.revision_;assert(revision.one.start(cfg,true,token));revision.tick(5);assert(revision.port.starts==0&&revision.one.result().code==ResultCode::Rejected);
 Rig expiry;expiry.connect();expiry.port.missingBattery=true;assert(expiry.one.start(cfg));expiry.tick(4);token=expiry.one.result().confirmationToken;expiry.tick(30005);assert(expiry.one.start(cfg,true,token));expiry.tick(30006);assert(expiry.port.starts==0);
}
static void channelRecovery(){Rig r;r.connect();ChargerConfig cfg;assert(r.one.start(cfg));r.tick(4);r.serverWire.ch=11;
 for(uint32_t t=304;t<=9004;t+=300)r.tick(t);assert(r.one.channel()==11&&r.one.connected()&&r.one.ownsSession()&&r.port.active_&&r.port.ownerAborts==0);assert(r.server.owner().deviceId()==101);
}
static void staleHeartbeatAndMalformed(){Rig r;r.connect();ChargerConfig cfg;assert(r.one.start(cfg));r.tick(4);Packet hb=r.wire1.last(Kind::Heartbeat);r.one.setHeartbeatEnabled(false);
 // Replaying an old sequence does not renew owner deadline.
 r.send(r.wire1,hb,9000);r.tick(10005);assert(r.port.ownerAborts==1);
 Rig old;old.connect();assert(old.one.start(cfg));old.tick(4);hb=old.wire1.last(Kind::Heartbeat);hb.header.sequence+=100;old.one.setHeartbeatEnabled(false);Received queued;queued.packet=hb;queued.receivedAt_ms=5;memcpy(queued.mac,old.wire1.mac,6);old.serverWire.queue.push_back(queued);old.tick(10005);assert(old.port.ownerAborts==1);
 Rig malformed;malformed.connect();auto sub=malformed.wire1.last(Kind::Subscribe);sub.header.kind=Kind::Unsubscribe;sub.header.sequence+=20;sub.payloadLength=0;malformed.send(malformed.wire1,sub,4);assert(malformed.server.subscriberCount()==2);
}
static void retiredBoots(){Rig r;r.connect();auto original=r.wire1.last(Kind::Subscribe);auto changed=original;Result result;
 changed.header.bootId=202;r.send(r.wire1,changed,4);assert(read(r.serverWire.last(Kind::Result),result)&&result.code==ResultCode::Applied);
 r.send(r.wire1,original,5);assert(read(r.serverWire.last(Kind::Result),result)&&result.code==ResultCode::Rejected);assert(strcmp(result.message,"Retired client boot rejected")==0);
 for(uint32_t boot=203;boot<=217;++boot){changed.header.bootId=boot;r.send(r.wire1,changed,boot);assert(read(r.serverWire.last(Kind::Result),result)&&result.code==ResultCode::Applied);}
 changed.header.bootId=218;r.send(r.wire1,changed,218);assert(read(r.serverWire.last(Kind::Result),result)&&result.code==ResultCode::Rejected);assert(strcmp(result.message,"Device reboot history full; restart charger")==0);
 // Last accepted boot remains usable; an overflow must not erase existing state.
 changed.header.bootId=217;r.send(r.wire1,changed,219);assert(read(r.serverWire.last(Kind::Result),result)&&result.code==ResultCode::Applied);
}
static void subscriptionRecovery(){Rig r;r.connect();r.one.setHeartbeatEnabled(false);for(uint32_t t=1003;t<=31003;t+=1000)r.tick(t);assert(r.server.subscriberCount()==1);r.one.setHeartbeatEnabled(true);r.tick(31004);r.tick(31005);r.tick(31006);assert(r.server.subscriberCount()==2&&r.one.connected());assert(r.port.starts==0);}
static void friendlyNames(){Rig r;r.connect();
 assert(!strcmp(r.one.selected()->advertisement.name,"charger1"));
 uint64_t id=r.one.selected()->deviceId;uint32_t boot=r.one.selected()->bootId;
 r.server.name("Charger Bench A");r.tick(2003);
 assert(r.one.connected()&&r.one.deviceCount()==1&&r.one.selected()->deviceId==id&&r.one.selected()->bootId==boot);
 assert(!strcmp(r.one.selected()->advertisement.name,"Charger Bench A"));
 assert(!strcmp(r.two.selected()->advertisement.name,"Charger Bench A"));
 assert(r.port.starts==0);
}
int main(){friendlyNames();controlAndDuplicates();ownerDeadline();confirmation();channelRecovery();staleHeartbeatAndMalformed();retiredBoots();subscriptionRecovery();puts("PASS: in-memory multi-client charger control, capability read, duplicate/replayed commands, confirmation binding/expiry, owner-only 10-second timeout, manual sessions, channel/subscription recovery, malformed unsubscribe and retired-boot replay rejection");}
