#pragma once
#include <LabLink.h>
#include "lab_ownership.h"
#include <stdio.h>
namespace batcharger {
// Portable server policy. All methods run on the charger main task. Transport
// is a bounded queue bridge; no radio callback can invoke this port.
class LabChargerPort {
public:
    virtual ~LabChargerPort(){}
    virtual uint32_t session()const=0;
    virtual uint32_t revision()const=0;
    virtual bool active()const=0;
    virtual lablink::ChargerConfig config()const=0;
    virtual lablink::Telemetry telemetry(uint32_t now_ms)const=0;
    virtual bool capabilities(uint8_t page,lablink::CapabilityPage &out)const=0;
    virtual lablink::Result start(const lablink::ChargerConfig &,bool proceed,uint32_t now_ms)=0;
    virtual lablink::Result abort(uint32_t now_ms,bool ownerLost)=0;
};
class LabChargerServer {
public:
    static constexpr unsigned MaxSubscribers=8;
    static constexpr uint32_t SubscriberTimeout_ms=30000;
private:
    struct Cached {bool used=false;uint32_t seq=0,fingerprint=0;lablink::Packet reply;};
    struct Peer {
        uint64_t id=0;uint32_t boot=0;uint8_t mac[6]={};bool subscribed=false;
        // Reject delayed packets from retired client boots without unbounded memory.
        uint32_t retiredBoots[16]={};uint8_t retiredCount=0;
        uint32_t subscription=0,lastSeen_ms=0,sentAt_ms=0,commandHighWater=0;uint16_t interval_ms=1000;
        Cached cache[4];unsigned nextCache=0;
        uint32_t token=0,confirmationAt_ms=0,confirmationRevision=0,confirmationSession=0;
        lablink::ChargerConfig confirmationConfig;
    } peers_[MaxSubscribers];
    LabChargerPort &port_;lablink::Transport &wire_;LabOwnership owner_;
    uint64_t deviceId_;uint32_t bootId_,sequence_=0,token_=0,advertisedAt_ms_=0;
    uint32_t observedSession_=0;lablink::OperatingState observedState_=lablink::OperatingState::Missing;
    char name_[32]={},firmware_[20]={};bool enabled_=false;
    uint32_t txDropped_=0,rxRejected_=0;
    const char *admissionError_="Eight device slots used; restart charger to clear";
    static constexpr uint32_t Features=lablink::CanSubscribe|lablink::CanReadConfig|lablink::CanStart|lablink::CanAbort|lablink::OwnerHeartbeat|lablink::HasCapabilities;
    static uint32_t fingerprint(const lablink::Packet &p){uint32_t h=2166136261u;
        auto add=[&](uint8_t b){h=(h^b)*16777619u;};add(uint8_t(p.header.kind));
        for(unsigned i=0;i<4;++i)add(uint8_t(p.header.sessionId>>(8*i)));
        for(unsigned i=0;i<p.payloadLength;++i)add(p.payload[i]);return h;
    }
    lablink::Packet packet(lablink::Kind kind,uint32_t reply=0,uint32_t targetBoot=0){lablink::Packet out;
        out.header.kind=kind;out.header.sequence=++sequence_;if(!out.header.sequence)out.header.sequence=++sequence_;
        out.header.replyTo=reply;out.header.deviceId=deviceId_;out.header.bootId=bootId_;out.header.targetBootId=targetBoot;out.header.sessionId=port_.session();return out;
    }
    void send(const uint8_t *mac,const lablink::Packet &p){if(!wire_.send(mac,p))++txDropped_;}
    lablink::Result result(lablink::ResultCode code,const char *text,uint16_t reason=0)const{lablink::Result r;r.code=code;r.reason=reason;
        r.effective=port_.config();snprintf(r.message,sizeof(r.message),"%s",text);return r;}
    void respond(const lablink::Received &input,const lablink::Result &r,Peer *peer=nullptr,bool cache=false){
        auto out=packet(lablink::Kind::Result,input.packet.header.sequence,input.packet.header.bootId);lablink::write(out,r);
        if(peer&&cache){auto &slot=peer->cache[peer->nextCache++%4];slot.used=true;slot.seq=input.packet.header.sequence;slot.fingerprint=fingerprint(input.packet);slot.reply=out;}
        send(input.mac,out);
    }
    Peer *find(uint64_t id){for(auto &p:peers_)if(p.id==id)return &p;return nullptr;}
    Peer *admit(const lablink::Received &input){auto *peer=find(input.packet.header.deviceId);
        admissionError_="Eight device slots used; restart charger to clear";
        if(!peer){for(auto &candidate:peers_)if(!candidate.id){peer=&candidate;break;}}
        if(!peer)return nullptr;
        if(peer->id&&peer->boot!=input.packet.header.bootId){
            for(unsigned i=0;i<peer->retiredCount;++i)if(peer->retiredBoots[i]==input.packet.header.bootId){admissionError_="Retired client boot rejected";return nullptr;}
            if(peer->retiredCount>=16){admissionError_="Device reboot history full; restart charger";return nullptr;}
            uint32_t retired[16];unsigned count=peer->retiredCount;
            memcpy(retired,peer->retiredBoots,count*sizeof(uint32_t));retired[count++]=peer->boot;
            *peer=Peer{};memcpy(peer->retiredBoots,retired,count*sizeof(uint32_t));peer->retiredCount=uint8_t(count);
        }
        if(!peer->id){peer->id=input.packet.header.deviceId;peer->boot=input.packet.header.bootId;}
        memcpy(peer->mac,input.mac,6);return peer;
    }
    void advertise(const uint8_t *mac,uint32_t reply=0,uint32_t targetBoot=0){auto out=packet(lablink::Kind::Advertise,reply,targetBoot);lablink::Advertisement a;
        a.type=lablink::EquipmentType::Charger;a.capabilities=Features;a.channel=wire_.channel();snprintf(a.name,sizeof(a.name),"%s",name_);snprintf(a.firmware,sizeof(a.firmware),"%s",firmware_);
        lablink::write(out,a);send(mac,out);
    }
    void telemetry(Peer &peer,uint32_t now_ms){auto out=packet(lablink::Kind::Telemetry,0,peer.boot);auto t=port_.telemetry(now_ms);
        t.ownerDeviceId=owner_.deviceId();t.ownerBootId=owner_.bootId();t.ownerRemaining_ms=owner_.owned()?(owner_.age_ms(now_ms)<LabOwnership::Timeout_ms?LabOwnership::Timeout_ms-owner_.age_ms(now_ms):0):0;
        lablink::write(out,t);send(peer.mac,out);peer.sentAt_ms=now_ms;
    }
    void process(const lablink::Received &input,uint32_t now_ms){const auto &in=input.packet;const auto &h=in.header;
        if(!h.deviceId||!h.bootId||!h.sequence||h.deviceId==deviceId_||in.payloadLength>lablink::MaxPayload){++rxRejected_;return;}
        if(h.kind==lablink::Kind::Discover){advertise(input.mac,h.sequence,h.bootId);return;}
        if(h.targetBootId!=bootId_){++rxRejected_;respond(input,result(lablink::ResultCode::Rejected,"Device restarted; rediscover"));return;}
        if(h.kind==lablink::Kind::Subscribe){lablink::Subscription s;
            if(!lablink::read(in,s)||!s.subscriptionId||s.interval_ms<500||s.interval_ms>5000){respond(input,result(lablink::ResultCode::Rejected,"Interval: 500-5000 ms; ID required"));return;}
            auto *peer=admit(input);if(!peer){respond(input,result(lablink::ResultCode::Rejected,admissionError_));return;}
            peer->subscribed=true;peer->subscription=s.subscriptionId;peer->interval_ms=s.interval_ms;peer->lastSeen_ms=now_ms;
            auto r=result(lablink::ResultCode::Applied,"Subscribed");r.confirmationToken=s.subscriptionId;respond(input,r);telemetry(*peer,now_ms);return;
        }
        Peer *peer=find(h.deviceId);
        if(!peer||peer->boot!=h.bootId||!lablink::sameMac(peer->mac,input.mac)){respond(input,result(lablink::ResultCode::Rejected,"Subscribe before using this device"));return;}
        if(h.kind==lablink::Kind::Start||h.kind==lablink::Kind::Abort){
            for(const auto &cached:peer->cache)if(cached.used&&cached.seq==h.sequence){
                if(cached.fingerprint==fingerprint(in))send(input.mac,cached.reply);else respond(input,result(lablink::ResultCode::Rejected,"Command ID reused with different content"));return;}
            if(peer->commandHighWater&&!lablink::newerSequence(h.sequence,peer->commandHighWater)){respond(input,result(lablink::ResultCode::Rejected,"Old command; read state before retrying"));return;}
            peer->commandHighWater=h.sequence;
        }
        if(!peer->subscribed){respond(input,result(lablink::ResultCode::Rejected,"Subscription expired; subscribe again"),peer,true);return;}
        if(h.kind==lablink::Kind::Heartbeat){lablink::Heartbeat heartbeat;
            if(!lablink::read(in,heartbeat)||heartbeat.subscriptionId!=peer->subscription){++rxRejected_;return;}
            peer->lastSeen_ms=now_ms;
            if(heartbeat.owner&&uint32_t(now_ms-input.receivedAt_ms)<LabOwnership::Timeout_ms)
                owner_.heartbeat(h.deviceId,h.bootId,h.sessionId,h.sequence,input.receivedAt_ms);
            auto out=packet(lablink::Kind::HeartbeatAck,h.sequence,h.bootId);lablink::HeartbeatAck ack;ack.subscriptionId=peer->subscription;ack.channel=wire_.channel();
            ack.owner=owner_.deviceId()==h.deviceId&&owner_.bootId()==h.bootId;lablink::write(out,ack);send(input.mac,out);return;
        }
        peer->lastSeen_ms=now_ms;
        if(h.kind==lablink::Kind::Unsubscribe){lablink::Subscription subscription;
            if(!lablink::read(in,subscription)||subscription.subscriptionId!=peer->subscription){respond(input,result(lablink::ResultCode::Rejected,"Subscription ID required"));return;}
            peer->subscribed=false;respond(input,result(lablink::ResultCode::Applied,"Unsubscribed; owner deadline still applies"));return;}
        if(h.kind==lablink::Kind::GetCapabilities){lablink::CapabilityRequest request;lablink::CapabilityPage page;
            if(!lablink::read(in,request)||!port_.capabilities(request.page,page)){respond(input,result(lablink::ResultCode::Rejected,"Unknown capabilities page"));return;}
            auto out=packet(lablink::Kind::Capabilities,h.sequence,h.bootId);lablink::write(out,page);send(input.mac,out);return;
        }
        if(h.kind==lablink::Kind::GetConfig){auto out=packet(lablink::Kind::Config,h.sequence,h.bootId);lablink::write(out,port_.config());send(input.mac,out);return;}
        if(h.kind==lablink::Kind::Start){lablink::StartRequest start;
            if(h.sessionId!=port_.session()){respond(input,result(lablink::ResultCode::Rejected,"Session changed; read state first"),peer,true);return;}
            if(!lablink::read(in,start)){respond(input,result(lablink::ResultCode::Rejected,"Malformed start profile"),peer,true);return;}
            if(port_.active()){respond(input,result(lablink::ResultCode::Rejected,"Charge already active; no takeover"),peer,true);return;}
            if(start.proceed&&(!peer->token||start.confirmationToken!=peer->token||now_ms-peer->confirmationAt_ms>=30000||
                port_.revision()!=peer->confirmationRevision||port_.session()!=peer->confirmationSession||!lablink::sameConfig(start.config,peer->confirmationConfig))){
                respond(input,result(lablink::ResultCode::Rejected,"Battery confirmation expired; start again"),peer,true);return;}
            peer->token=0;auto r=port_.start(start.config,start.proceed,now_ms);
            if(r.code==lablink::ResultCode::Applied){owner_.claim(h.deviceId,h.bootId,port_.session(),h.sequence,now_ms);}
            else if(r.code==lablink::ResultCode::ConfirmationRequired){peer->token=++token_;if(!peer->token)peer->token=++token_;
                peer->confirmationAt_ms=now_ms;peer->confirmationRevision=port_.revision();peer->confirmationSession=port_.session();peer->confirmationConfig=start.config;r.confirmationToken=peer->token;}
            respond(input,r,peer,true);return;
        }
        if(h.kind==lablink::Kind::Abort){
            if(h.sessionId!=port_.session()){respond(input,result(lablink::ResultCode::Rejected,"Session changed; abort not applied"),peer,true);return;}
            auto r=port_.abort(now_ms,false);owner_.observe(port_.session(),port_.active());respond(input,r,peer,true);return;
        }
        respond(input,result(lablink::ResultCode::Rejected,"Unsupported command"));
    }
public:
    LabChargerServer(LabChargerPort &port,lablink::Transport &transport,uint64_t id,uint32_t boot,const char *name,const char *firmware):port_(port),wire_(transport),deviceId_(id),bootId_(boot){
        snprintf(name_,sizeof(name_),"%.31s",name);snprintf(firmware_,sizeof(firmware_),"%.19s",firmware);
    }
    void name(const char *name){snprintf(name_,sizeof(name_),"%.31s",name);}
    void tick(bool enabled,uint32_t now_ms){
        owner_.observe(port_.session(),port_.active());
        if(owner_.expired(now_ms)){port_.abort(now_ms,true);owner_.clear();}
        bool changed=enabled!=enabled_;enabled_=enabled;
        for(auto &peer:peers_)if(peer.subscribed&&now_ms-peer.lastSeen_ms>=SubscriberTimeout_ms)peer.subscribed=false;
        if(!enabled)return;lablink::Received input;
        // Bounded work protects main-loop charger polling under radio traffic.
        for(unsigned i=0;i<6&&wire_.receive(input);++i)process(input,now_ms);
        owner_.observe(port_.session(),port_.active());
        if(changed||now_ms-advertisedAt_ms_>=2000){static const uint8_t Broadcast[6]={255,255,255,255,255,255};advertise(Broadcast);advertisedAt_ms_=now_ms;}
        auto state=port_.telemetry(now_ms).state;bool event=state!=observedState_||port_.session()!=observedSession_;observedState_=state;observedSession_=port_.session();
        for(auto &peer:peers_)if(peer.subscribed&&(event||now_ms-peer.sentAt_ms>=peer.interval_ms))telemetry(peer,now_ms);
    }
    const LabOwnership &owner()const{return owner_;}
    uint64_t deviceId()const{return deviceId_;}
    uint32_t bootId()const{return bootId_;}
    unsigned subscriberCount()const{unsigned count=0;for(const auto &p:peers_)if(p.subscribed)++count;return count;}
    uint32_t rejected()const{return rxRejected_;}uint32_t txDropped()const{return txDropped_;}
};
} // namespace batcharger
