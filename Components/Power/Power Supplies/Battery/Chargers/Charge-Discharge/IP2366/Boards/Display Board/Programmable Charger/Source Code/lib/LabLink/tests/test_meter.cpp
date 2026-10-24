#include "LabLinkMeterServer.h"
#include <assert.h>
#include <deque>
#include <vector>
#include <stdio.h>
using namespace lablink;
struct Wire:Transport {
 std::deque<Received> incoming;std::vector<Packet> sent;Wire*other=nullptr;
 uint8_t mac[6]={1,2,3,4,5,6};bool drop=false;
 bool receive(Received&r)override{if(incoming.empty())return false;r=incoming.front();incoming.pop_front();return true;}
 bool send(const uint8_t*,const Packet&p)override{
  sent.push_back(p);uint8_t bytes[250];size_t n=encode(p,bytes,sizeof bytes);assert(n);
  Received r;assert(decode(bytes,n,r.packet));memcpy(r.mac,mac,6);
  if(!drop&&other)other->incoming.push_back(r);return true;
 }
 bool setChannel(uint8_t)override{return true;}uint8_t channel()const override{return 6;}
};
struct App:MeterApplication{
 uint32_t epoch=1;unsigned starts=0,stops=0,clears=0;MeterReadings t;MeterConfig c;
 uint32_t session()override{return epoch;}MeterReadings readings()override{return t;}MeterConfig config()override{return c;}
 bool start(const MeterConfig&v,uint32_t e)override{if(e!=epoch||t.state!=MeterState::Ready)return false;c=v;++epoch;++starts;t.state=MeterState::Recording;return true;}
 bool stop(uint32_t e)override{if(e!=epoch)return false;if(t.state==MeterState::Recording){++stops;t.state=MeterState::Completed;}return true;}
 bool clear(uint32_t e)override{if(e!=epoch)return false;++clears;++epoch;t=MeterReadings();return true;}
};
int main(){
 // Exact signed integer round trips, truncation rejection and no mutation of
 // caller output on malformed payloads.
 Packet p;p.header.kind=Kind::MeterReadings;p.header.deviceId=1;p.header.bootId=2;p.header.sequence=3;
 MeterReadings t;t.current_mA=-1234;t.power_mW=-14808;t.charge_uAh=INT64_MIN;t.energy_uWh=INT64_MAX;
 t.internal_cC=-1250;t.external_cC=6000;t.duration_ms=5000000000ULL;t.temperaturePresent=3;
 assert(write(p,t));MeterReadings copy;assert(read(p,copy));
 assert(copy.current_mA==-1234&&copy.charge_uAh==INT64_MIN&&copy.energy_uWh==INT64_MAX&&copy.duration_ms==5000000000ULL);
 auto full=p.payloadLength;for(unsigned n=0;n<full;n++){p.payloadLength=n;copy.current_mA=99;assert(!read(p,copy));assert(copy.current_mA==99);}p.payloadLength=full;
 MeterConfig config;config.length_s=0;assert(!validMeterConfig(config));config.length_s=-1;config.interval_s=86400;assert(validMeterConfig(config));
 for(unsigned page=0;page<4;page++){auto c=meterCapabilities(page);assert(write(p,c));CapabilityPage d;assert(read(p,d)&&d.page==page);}
 Wire host,device;host.other=&device;device.other=&host;device.mac[5]=7;App app;
 MeterServer server(device,app,7,8,"power1");Client client(host,9,10);
 auto tick=[&](uint32_t now){client.tick(now);server.tick(now);client.tick(now);};
 client.discover();tick(1);assert(client.deviceCount()==1);assert(client.select(0));tick(2);assert(client.connected());
 assert(client.getMeterReadings());tick(3);assert(client.hasMeterReadings()&&client.sessionId()==1);
 // Lost applied response: same command retry does not start twice.
 config.interval_s=5;device.drop=true;assert(client.startMeter(config));tick(4);assert(app.starts==1);
 device.drop=false;tick(505);assert(!client.pending()&&app.starts==1&&client.result().code==ResultCode::Applied);
 assert(!client.ownsSession()); // Observation is not an actuator ownership lease.
 assert(client.clearMeter());tick(506);assert(client.result().code==ResultCode::ConfirmationRequired&&app.clears==0);
 auto token=client.result().confirmationToken;
 assert(client.clearMeter(true,token));device.drop=true;tick(507);assert(app.clears==1&&app.t.state==MeterState::Ready);
 device.drop=false;tick(1008);assert(!client.pending()&&app.clears==1);
 // A token cannot erase a later run.
 assert(client.clearMeter());tick(1009);token=client.result().confirmationToken;
 ++app.epoch;app.t.state=MeterState::Recording;
 assert(client.clearMeter(true,token));tick(1010);assert(app.clears==1&&client.result().code==ResultCode::Rejected);
 // Client loss never stops an independently sampling meter.
 client.setHeartbeatEnabled(false);server.tick(20000);assert(app.t.state==MeterState::Recording&&app.stops==0);
 // Retired client boots cannot replay old destructive commands.
 Packet old=host.sent.back();Received stale;stale.packet=old;memcpy(stale.mac,host.mac,6);
 Packet sub=old;sub.header.kind=Kind::Subscribe;sub.header.bootId=11;sub.header.sequence=1;Subscription subscription;subscription.subscriptionId=1;write(sub,subscription);
 Received fresh=stale;fresh.packet=sub;device.incoming.push_back(fresh);server.tick(20001);
 device.incoming.push_back(stale);server.tick(20002);assert(app.clears==1);
 // Wrong target boot never produces an action.
 stale.packet.header.targetBootId=999;device.incoming.push_back(stale);server.tick(20003);assert(app.clears==1);
 puts("PASS meter codec, signed limits, descriptors, pull, lost-reply retry, active clear, stale session, disconnect and boot protection");
}
