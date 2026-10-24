#include <LabLinkAdapterServer.h>
#ifdef LABLINK_ADAPTER_APP_TESTS
#include "GraphAutoStop.h"
#include "ActionEngine.h"
#endif
#include <assert.h>
#include <deque>
#include <vector>
#include <stdio.h>
using namespace lablink;
struct Radio:Transport{
 std::deque<Received> in;std::vector<Packet> out;
 bool receive(Received&r)override{if(in.empty())return false;r=in.front();in.pop_front();return true;}
 bool send(const uint8_t*,const Packet&p)override{out.push_back(p);return true;}
 bool setChannel(uint8_t)override{return true;}uint8_t channel()const override{return 6;}
};
struct App:AdapterApplication{
 uint32_t revision=3,recording=7;unsigned writes=0;
 uint32_t targetRevision()override{return revision;}uint32_t recordingId()override{return recording;}
 const char*confirmation(const AdapterRequest&r)override{return r.op==AdapterOp::Execute?"Confirm test action":r.op==AdapterOp::GraphClear?"Clear?":nullptr;}
 void transact(const AdapterRequest&r,AdapterResponse&out)override{
  if(r.op==AdapterOp::Execute)++writes;
  if(r.op==AdapterOp::Readings){out.readings.targetRevision=revision;out.readings.current_mA=-619;out.readings.validity=2;}
  if(r.op==AdapterOp::GraphPage){out.graph.recordingId=recording;out.graph.generation=recording;out.offset=r.offset;out.count=4;for(unsigned i=0;i<4;i++){out.points[i].at_ms=uint64_t(r.offset+i)*30000;out.points[i].validity=0x7ff;out.points[i].cells_mV[7]=4001;}}
 }
};
static Packet request(uint32_t seq,Kind kind=Kind::AdapterRequest){Packet p;p.header.kind=kind;p.header.sequence=seq;p.header.deviceId=10;p.header.bootId=20;p.header.targetBootId=30;return p;}
int main(){
 // Exact codec widths, signed values, maximum strings, all eight cells.
 AdapterResponse value;value.readings.current_mA=-619;value.readings.validity=0x1fff;value.readings.stringCount=8;
 memset(value.readings.family,'f',31);memset(value.readings.flavor,'c',31);memset(value.readings.security,'s',23);memset(value.readings.manufactured,'d',15);
 Packet p=request(1,Kind::AdapterResponse);assert(write(p,value)&&p.payloadLength<=MaxPayload);uint8_t bytes[250];size_t size=encode(p,bytes,250);assert(size&&size<=250);Packet decoded;assert(decode(bytes,size,decoded));AdapterResponse round;assert(read(decoded,round)&&round.readings.current_mA==-619);
 for(unsigned n=0;n<p.payloadLength;n++){Packet shortPacket=p;shortPacket.payloadLength=n;AdapterResponse unchanged;unchanged.token=123;assert(!read(shortPacket,unchanged));assert(unchanged.token==123);}
 AdapterResponse page;page.op=AdapterOp::GraphPage;page.count=4;page.points[3].at_ms=UINT64_C(5000000000);assert(write(p,page)&&p.payloadLength<=210);assert(read(p,round)&&round.points[3].at_ms==UINT64_C(5000000000));
 AdapterResponse action;action.op=AdapterOp::ActionInfo;memset(action.action.name,'n',39);memset(action.action.confirmation,'m',139);assert(write(p,action)&&p.payloadLength<=210);
 // Membership, confirmation, lost replies, interleaved reads and stale targets.
 Radio radio;App app;AdapterServer server(radio,app,99,30,"SMBus Adapter");
 auto send=[&](const Packet&q,uint32_t now){Received rx;rx.mac[0]=1;rx.packet=q;rx.receivedAt_ms=now;radio.in.push_back(rx);server.tick(now);assert(!radio.out.empty());return radio.out.back();};
 auto sub=request(1,Kind::Subscribe);Subscription membership;membership.subscriptionId=4;write(sub,membership);assert(send(sub,100).header.kind==Kind::HeartbeatAck);
 AdapterRequest cmd;cmd.op=AdapterOp::Execute;cmd.targetRevision=3;cmd.recordingId=7;cmd.generation=7;cmd.index=1;
 auto q=request(2);write(q,cmd);AdapterResponse result;assert(read(send(q,101),result)&&result.code==ResultCode::ConfirmationRequired);cmd.confirmed=true;cmd.token=result.token;
 q=request(3);write(q,cmd);assert(read(send(q,102),result)&&result.code==ResultCode::Applied&&app.writes==1);
 auto original=q;AdapterRequest poll;q=request(4);write(q,poll);send(q,103);send(original,104);assert(app.writes==1);
 auto changed=original;changed.payload[1]^=1;send(changed,105);assert(app.writes==1);
 cmd.confirmed=false;cmd.token=0;q=request(5);write(q,cmd);assert(read(send(q,106),result)&&result.code==ResultCode::ConfirmationRequired);
 cmd.token=result.token;cmd.confirmed=true;app.revision=4;q=request(6);write(q,cmd);assert(read(send(q,107),result)&&result.code==ResultCode::Rejected&&app.writes==1);
 q=request(7);write(q,poll);q.header.targetBootId=29;size_t before=radio.out.size();Received old;old.mac[0]=1;old.packet=q;radio.in.push_back(old);server.tick(108);assert(radio.out.size()==before);
 cmd.op=AdapterOp::GraphPage;cmd.offset=620;cmd.confirmed=false;q=request(8);write(q,cmd);assert(read(send(q,110),result)&&result.points[0].at_ms==18600000&&result.points[3].cells_mV[7]==4001);
#ifdef LABLINK_ADAPTER_APP_TESTS
 // NoCurrent is strictly >10 seconds and only continuous valid samples count.
 GraphAutoStop stop;assert(stop.enabled&&stop.deadband_mA==0);
 for(uint32_t t=100;t<=10100;t+=1000)assert(stop.check(t,false,0,false,false,true,0)==0);
 assert(stop.check(11100,false,0,false,false,true,0)==4);stop.reset();
 assert(stop.check(100,true,100,false,false,true,10)==2);assert(!stop.check(100,true,0,false,false,true,10));
 assert(stop.check(100,true,0,false,false,true,-10)==3);
 assert(stop.check(100,false,0,true,true,true,10)==2);
 for(uint32_t t=100;t<60100;t+=1000)assert(!stop.check(t,true,100,true,true,true,-619));
 assert(!stop.check(60100,true,120,true,true,true,-1));
 assert(!stop.check(61100,true,100,true,true,false,0));
 assert(stop.check(62100,true,0,true,true,true,-619)==3);
 stop.reset();assert(!stop.check(63100,true,100,true,true,true,0));
 for(uint32_t t=64100;t<=73100;t+=1000)assert(!stop.check(t,true,0,true,true,true,0));
 assert(stop.check(74100,true,100,true,true,true,0)==4);stop.reset();
 for(uint32_t t=100;t<=8100;t+=1000)assert(!stop.check(t,false,0,false,false,true,0));
 stop.check(9100,false,0,false,false,false,0);assert(!stop.check(10100,false,0,false,false,true,0));
 stop.reset();stop.deadband_mA=5;assert(!stop.check(100,false,0,false,false,true,-5));assert(!stop.check(11100,false,0,false,false,true,-5)); // gap breaks continuity
 stop.enabled=false;assert(!stop.check(11101,true,0,true,true,true,0));
 // YAML action engine emits the physical reference bytes, with selected address.
 struct Bus{std::vector<std::vector<uint8_t>>tx;std::vector<uint8_t>addresses;std::vector<bool>stops;uint8_t error=0;
  uint8_t transmit(uint8_t a,const uint8_t*b,size_t n,bool stop){addresses.push_back(a);tx.emplace_back(b,b+n);stops.push_back(stop);return error;}
  bool readWord(uint8_t,uint16_t&v){v=0x1234;return true;}
 } bus;char message[160];
 assert(runActionSteps(0,0x55,bus,message,sizeof message));assert((bus.tx[0]==std::vector<uint8_t>{0,8,0})&&bus.addresses[0]==0x55&&bus.stops[0]);
 assert(runActionSteps(1,0x0b,bus,message,sizeof message));assert((bus.tx[1]==std::vector<uint8_t>{0x2a,1,0})&&bus.addresses[1]==0x0b);
 Bus challenge;assert(runActionSteps(3,0x0b,challenge,message,sizeof message));assert((challenge.tx[0]==std::vector<uint8_t>{0x71,0x14,0x02}));assert((challenge.tx[1]==std::vector<uint8_t>{0x73})&&!challenge.stops[1]);assert((challenge.tx[2]==std::vector<uint8_t>{0x71,0xcc,0xed}));assert((challenge.tx[3]==std::vector<uint8_t>{0x70,0x17,0x05}));
 Bus nack;nack.error=2;assert(!runActionSteps(3,0x0b,nack,message,sizeof message)&&nack.tx.size()==1);
#endif
 puts("PASS: adapter codec, history, confirmation/replay/target (and application tests when enabled)");
}
