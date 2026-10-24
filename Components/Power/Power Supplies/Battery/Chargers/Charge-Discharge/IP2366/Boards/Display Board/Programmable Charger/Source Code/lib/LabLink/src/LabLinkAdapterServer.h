#pragma once
#include "LabLink.h"
namespace lablink {
class AdapterApplication {
public:
 virtual ~AdapterApplication(){}
 virtual uint32_t targetRevision()=0;
 virtual uint32_t recordingId()=0;
 virtual const char* confirmation(const AdapterRequest&)=0;
 virtual void transact(const AdapterRequest&,AdapterResponse&)=0;
};
class AdapterServer {
 struct Cached {uint32_t sequence=0;Packet request,reply;};
 struct Peer {
  uint64_t id=0;uint32_t boot=0,retired[16]={};uint8_t retiredCount=0,mac[6]={};
  uint32_t subscription=0,seen=0,commandSequence=0,heartbeatSequence=0;
  uint32_t token=0,tokenAt=0;AdapterRequest confirmation;
  Cached cache[4];uint8_t next=0;
 } peers_[8];
 Transport&radio_;AdapterApplication&app_;uint64_t id_;uint32_t boot_,sequence_=0,now_=0,token_=0;
 bool handling_=false;Advertisement advertisement_;
 Packet packet(Kind kind,const Received&rx){Packet p;p.header.kind=kind;p.header.deviceId=id_;p.header.bootId=boot_;if(!++sequence_)++sequence_;p.header.sequence=sequence_;p.header.replyTo=rx.packet.header.sequence;p.header.targetBootId=rx.packet.header.bootId;p.header.sessionId=app_.recordingId();return p;}
 bool same(const Packet&a,const Packet&b){return a.header.kind==b.header.kind&&a.header.sessionId==b.header.sessionId&&a.payloadLength==b.payloadLength&&!memcmp(a.payload,b.payload,a.payloadLength);}
 Peer*peer(const Received&rx,bool create){Peer*empty=nullptr;for(auto&p:peers_){if(!p.id){if(!empty)empty=&p;continue;}if(p.id!=rx.packet.header.deviceId)continue;if(!sameMac(p.mac,rx.mac))return nullptr;if(p.boot!=rx.packet.header.bootId){if(!create||p.retiredCount==16)return nullptr;for(unsigned i=0;i<p.retiredCount;i++)if(p.retired[i]==rx.packet.header.bootId)return nullptr;p.retired[p.retiredCount++]=p.boot;p.boot=rx.packet.header.bootId;p.subscription=p.commandSequence=p.heartbeatSequence=p.token=0;for(auto&c:p.cache)c.sequence=0;}return &p;}if(!create||!empty)return nullptr;empty->id=rx.packet.header.deviceId;empty->boot=rx.packet.header.bootId;memcpy(empty->mac,rx.mac,6);return empty;}
 void reply(Peer*s,const Received&rx,Packet&p){if(s){auto&c=s->cache[s->next++%4];c.sequence=rx.packet.header.sequence;c.request=rx.packet;c.reply=p;}radio_.send(rx.mac,p);}
 void sharedResult(Peer*s,const Received&rx,const char*message){auto p=packet(Kind::Result,rx);Result r;r.code=ResultCode::Rejected;strncpy(r.message,message,sizeof r.message-1);write(p,r);reply(s,rx,p);}
 void handle(const Received&rx){
  const auto&q=rx.packet;const auto&h=q.header;if(h.deviceId==id_)return;
  if(h.kind==Kind::Discover){if(h.targetBootId||q.payloadLength)return;auto p=packet(Kind::Advertise,rx);p.header.targetBootId=0;p.header.sessionId=0;advertisement_.channel=radio_.channel();write(p,advertisement_);radio_.send(rx.mac,p);return;}
  if(h.targetBootId!=boot_)return;
  Peer*s=peer(rx,h.kind==Kind::Subscribe);if(!s){sharedResult(nullptr,rx,"Subscribe first or peer table full");return;}
  if(h.kind==Kind::Heartbeat){Heartbeat hb;if(!read(q,hb)||!s->subscription||hb.subscriptionId!=s->subscription)return;if(s->heartbeatSequence&&!newerSequence(h.sequence,s->heartbeatSequence))return;s->heartbeatSequence=h.sequence;s->seen=rx.receivedAt_ms;auto p=packet(Kind::HeartbeatAck,rx);HeartbeatAck ack;ack.subscriptionId=s->subscription;ack.channel=radio_.channel();write(p,ack);radio_.send(rx.mac,p);return;}
  for(auto&c:s->cache)if(c.sequence==h.sequence){if(same(c.request,q))radio_.send(rx.mac,c.reply);return;}
  if(s->commandSequence&&!newerSequence(h.sequence,s->commandSequence))return;s->commandSequence=h.sequence;
  if(h.kind==Kind::Subscribe){Subscription sub;if(!read(q,sub)||!sub.subscriptionId){sharedResult(s,rx,"Invalid subscription");return;}s->subscription=sub.subscriptionId;s->seen=rx.receivedAt_ms;auto p=packet(Kind::HeartbeatAck,rx);HeartbeatAck ack;ack.subscriptionId=s->subscription;ack.channel=radio_.channel();write(p,ack);reply(s,rx,p);return;}
  if(!s->subscription||elapsed(now_,s->seen)>10000){sharedResult(s,rx,"Subscription expired");return;}
  if(h.kind==Kind::Unsubscribe){Subscription sub;if(!read(q,sub)||sub.subscriptionId!=s->subscription){sharedResult(s,rx,"Invalid subscription");return;}s->subscription=0;s->token=0;auto p=packet(Kind::Result,rx);Result r;write(p,r);reply(s,rx,p);return;}
  if(h.kind==Kind::GetCapabilities){CapabilityRequest request;if(!read(q,request)){sharedResult(s,rx,"Invalid capability page");return;}auto cap=adapterCapabilities(request.page);if(request.page>=cap.pageCount){sharedResult(s,rx,"Invalid capability page");return;}auto p=packet(Kind::Capabilities,rx);write(p,cap);reply(s,rx,p);return;}
  if(h.kind!=Kind::AdapterRequest){sharedResult(s,rx,"Unsupported adapter operation");return;}
  AdapterRequest request;if(!read(q,request)){sharedResult(s,rx,"Malformed adapter request");return;}
  AdapterResponse response;response.op=request.op;
  if(adapterMutation(request.op)&&request.op!=AdapterOp::DiscoverDut&&request.targetRevision!=app_.targetRevision()){
   response.code=ResultCode::Rejected;strncpy(response.message,"DUT selection changed; poll before retrying",139);
  } else {
   const char*text=app_.confirmation(request);
   if(text&&*text){
    if(!request.confirmed){if(!++token_)++token_;s->token=token_;s->tokenAt=now_;s->confirmation=request;response.code=ResultCode::ConfirmationRequired;response.token=s->token;strncpy(response.message,text,139);}
    else {const auto&c=s->confirmation;bool valid=request.token&&request.token==s->token&&elapsed(now_,s->tokenAt)<=30000&&request.op==c.op&&request.index==c.index&&request.targetRevision==c.targetRevision&&request.recordingId==c.recordingId&&request.generation==c.generation;s->token=0;if(valid)app_.transact(request,response);else{response.code=ResultCode::Rejected;strncpy(response.message,"Confirmation expired or target changed",139);}}
   }else app_.transact(request,response);
  }
  auto p=packet(Kind::AdapterResponse,rx);if(!write(p,response)){response.code=ResultCode::Rejected;strncpy(response.message,"Response exceeds protocol limit",139);write(p,response);}reply(s,rx,p);
 }
public:
 AdapterServer(Transport&r,AdapterApplication&a,uint64_t id,uint32_t boot,const char*name):radio_(r),app_(a),id_(id),boot_(boot?boot:1){advertisement_.type=EquipmentType::SMBusAdapter;advertisement_.capabilities=AdapterCapabilities;strncpy(advertisement_.name,name,31);strncpy(advertisement_.firmware,"smbus-1.2",19);}
 void tick(uint32_t now){if(handling_)return;handling_=true;now_=now;Received rx;if(radio_.receive(rx))handle(rx);handling_=false;}
};
} // namespace lablink
