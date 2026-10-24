#pragma once
#include "LabLink.h"
namespace lablink {
// Application methods must serialize with local controls. expectedSession is
// checked under that same lock, not merely when receiving the radio packet.
class MeterApplication {
public:
 virtual ~MeterApplication(){}
 virtual uint32_t session()=0;
 virtual MeterReadings readings()=0;
 virtual MeterConfig config()=0;
 virtual bool start(const MeterConfig&,uint32_t expectedSession)=0;
 virtual bool stop(uint32_t expectedSession)=0;
 virtual bool clear(uint32_t expectedSession)=0;
 virtual CapabilityPage capabilities(uint8_t page){return meterCapabilities(page);}
};
class MeterServer {
 struct Peer {
  uint64_t id=0;uint32_t boot=0,retired[16]={};uint8_t retiredCount=0,mac[6]={};
  uint32_t subscription=0,seen=0,commandSequence=0,heartbeatSequence=0;
  uint32_t token=0,tokenSession=0,tokenAt=0;
  Packet request,reply;bool haveReply=false;
 };
 Transport& radio_;MeterApplication& app_;uint64_t id_;uint32_t boot_,sequence_=0,now_=0,tokenCounter_=0;
 Peer peers_[8];Advertisement advertisement_;
 Packet packet(Kind k,const Received&rx){
  Packet p;p.header.kind=k;p.header.deviceId=id_;p.header.bootId=boot_;
  if(!++sequence_)++sequence_;p.header.sequence=sequence_;
  p.header.targetBootId=rx.packet.header.bootId;p.header.replyTo=rx.packet.header.sequence;p.header.sessionId=app_.session();return p;
 }
 bool sameRequest(const Packet&a,const Packet&b){
  return a.header.kind==b.header.kind&&a.header.sessionId==b.header.sessionId&&a.payloadLength==b.payloadLength&&
   memcmp(a.payload,b.payload,a.payloadLength)==0;
 }
 void reply(Peer*peer,const Received&rx,Packet&p,bool cache){
  if(cache&&peer){peer->request=rx.packet;peer->reply=p;peer->haveReply=true;}
  radio_.send(rx.mac,p);
 }
 void result(Peer*peer,const Received&rx,ResultCode code,const char*message,bool cache=true,uint32_t token=0){
  Packet p=packet(Kind::MeterResult,rx);MeterResult r;r.code=code;r.token=token;strncpy(r.message,message,sizeof r.message-1);write(p,r);reply(peer,rx,p,cache);
 }
 Peer* peer(const Received&rx,bool create){
  const auto&h=rx.packet.header;Peer*empty=nullptr;
  for(auto&p:peers_){
   if(!p.id){if(!empty)empty=&p;continue;}if(p.id!=h.deviceId)continue;
   if(!sameMac(p.mac,rx.mac))return nullptr;
   if(p.boot!=h.bootId){
    if(!create||p.retiredCount==16)return nullptr;
    for(unsigned i=0;i<p.retiredCount;i++)if(p.retired[i]==h.bootId)return nullptr;
    p.retired[p.retiredCount++]=p.boot;p.boot=h.bootId;p.subscription=0;
    p.commandSequence=p.heartbeatSequence=p.token=0;p.haveReply=false;
   }
   return &p;
  }
  if(!create||!empty)return nullptr;
  empty->id=h.deviceId;empty->boot=h.bootId;memcpy(empty->mac,rx.mac,6);return empty;
 }
 void handle(const Received&rx){
  const auto&q=rx.packet;const auto&h=q.header;
  if(h.deviceId==id_)return;
  if(h.kind==Kind::Discover){
   if(h.targetBootId||q.payloadLength)return;
   auto p=packet(Kind::Advertise,rx);p.header.targetBootId=0;p.header.sessionId=0;
   advertisement_.channel=radio_.channel();write(p,advertisement_);radio_.send(rx.mac,p);return;
  }
  if(h.targetBootId!=boot_)return;
  Peer*s=peer(rx,h.kind==Kind::Subscribe);
  if(!s){result(nullptr,rx,ResultCode::Rejected,"Subscribe first or peer table full",false);return;}
  if(h.kind==Kind::Heartbeat){
   Heartbeat hb;if(!read(q,hb)||!s->subscription||hb.subscriptionId!=s->subscription)return;
   if(s->heartbeatSequence&&!newerSequence(h.sequence,s->heartbeatSequence))return;
   s->heartbeatSequence=h.sequence;s->seen=now_;
   auto p=packet(Kind::HeartbeatAck,rx);HeartbeatAck ack;ack.subscriptionId=s->subscription;ack.channel=radio_.channel();
   write(p,ack);radio_.send(rx.mac,p);return;
  }
  // Replay the exact result, including its original session, after packet loss.
  // Heartbeats use a separate high-water mark so retries remain valid.
  if(s->commandSequence&&h.sequence==s->commandSequence){
   if(s->haveReply&&sameRequest(q,s->request))radio_.send(rx.mac,s->reply);return;
  }
  if(s->commandSequence&&!newerSequence(h.sequence,s->commandSequence))return;
  s->commandSequence=h.sequence;s->haveReply=false;
  if(h.kind==Kind::Subscribe){
   Subscription sub;if(!read(q,sub)||!sub.subscriptionId){result(s,rx,ResultCode::Rejected,"Invalid subscription");return;}
   s->subscription=sub.subscriptionId;s->seen=now_;
   auto p=packet(Kind::HeartbeatAck,rx);HeartbeatAck ack;ack.subscriptionId=sub.subscriptionId;ack.channel=radio_.channel();write(p,ack);reply(s,rx,p,true);return;
  }
  if(!s->subscription||elapsed(now_,s->seen)>10000){result(s,rx,ResultCode::Rejected,"Subscription expired");return;}
  if(h.kind==Kind::Unsubscribe){
   Subscription sub;if(!read(q,sub)||sub.subscriptionId!=s->subscription){result(s,rx,ResultCode::Rejected,"Invalid subscription");return;}
   s->subscription=0;s->token=0;result(s,rx,ResultCode::Applied,"Unsubscribed");return;
  }
  if(h.kind==Kind::GetMeterReadings&&q.payloadLength==0){
   auto p=packet(Kind::MeterReadings,rx);auto value=app_.readings();write(p,value);reply(s,rx,p,true);return;
  }
  if(h.kind==Kind::GetMeterConfig&&q.payloadLength==0){
   auto p=packet(Kind::MeterConfig,rx);write(p,app_.config());reply(s,rx,p,true);return;
  }
  if(h.kind==Kind::GetCapabilities){
   CapabilityRequest request;if(!read(q,request)){result(s,rx,ResultCode::Rejected,"Invalid capability request");return;}
   auto value=app_.capabilities(request.page);if(request.page>=value.pageCount){result(s,rx,ResultCode::Rejected,"Invalid capability page");return;}
   auto p=packet(Kind::Capabilities,rx);write(p,value);reply(s,rx,p,true);return;
  }
  if(h.sessionId!=app_.session()){result(s,rx,ResultCode::Rejected,"Recording changed; poll before retrying");return;}
  if(h.kind==Kind::MeterStart){
   MeterConfig config;if(!read(q,config)||!validMeterConfig(config)){result(s,rx,ResultCode::Rejected,"Invalid recording profile");return;}
   bool ok=app_.start(config,h.sessionId);result(s,rx,ok?ResultCode::Applied:ResultCode::Rejected,ok?"Recording started":"Start blocked; check sensors or clear data");return;
  }
  if(h.kind==Kind::MeterStop&&q.payloadLength==0){
   bool ok=app_.stop(h.sessionId);result(s,rx,ok?ResultCode::Applied:ResultCode::Rejected,ok?"Recording stopped":"Recording changed");return;
  }
  if(h.kind==Kind::MeterClear){
   MeterClear c;if(!read(q,c)){result(s,rx,ResultCode::Rejected,"Invalid clear request");return;}
   if(!c.confirmed){
    if(!++tokenCounter_)++tokenCounter_;
    s->token=tokenCounter_;s->tokenSession=h.sessionId;s->tokenAt=now_;
    result(s,rx,ResultCode::ConfirmationRequired,"Confirm stop and erase recording",true,s->token);return;
   }
   bool valid=c.token&&c.token==s->token&&s->tokenSession==h.sessionId&&elapsed(now_,s->tokenAt)<=30000;
   s->token=0;bool ok=valid&&app_.clear(h.sessionId);
   result(s,rx,ok?ResultCode::Applied:ResultCode::Rejected,ok?"Recording cleared":"Clear confirmation expired or recording changed");return;
  }
  result(s,rx,ResultCode::Rejected,"Unsupported meter operation");
 }
public:
 MeterServer(Transport&r,MeterApplication&a,uint64_t id,uint32_t boot,const char*name):radio_(r),app_(a),id_(id),boot_(boot?boot:1){
  advertisement_.type=EquipmentType::CurrentMeter;advertisement_.capabilities=MeterRequiredCapabilities|MeterTemperatures;
  strncpy(advertisement_.name,name,sizeof advertisement_.name-1);strncpy(advertisement_.firmware,"meter-1.1",sizeof advertisement_.firmware-1);
 }
 void tick(uint32_t now){now_=now;Received rx;for(unsigned i=0;i<12&&radio_.receive(rx);i++)handle(rx);}
};
} // namespace lablink
