#pragma once
namespace lablink {
struct Device {uint8_t mac[6]={};uint64_t deviceId=0;uint32_t bootId=0,lastSeen_ms=0;Advertisement advertisement;};
class Client {
 Transport& transport_;uint64_t id_;uint32_t boot_;Device devices_[12];size_t count_=0;int selected_=-1;
 uint32_t sequence_=0,now_=0,event_=0,lastReply_=0,lastHeartbeat_=0,lastHeartbeatSequence_=0,lastDiscover_=0,lastHop_=0,lastServerSequence_=0;
 uint32_t subscriptionId_=0,session_=0,subSent_=0;uint16_t interval_=1000;bool subscribed_=false,wantSubscription_=false,heartbeatEnabled_=true,owner_=false,recovering_=false;
 bool haveTelemetry_=false,haveConfig_=false;uint32_t telemetryReceivedAt_ms_=0;Telemetry telemetry_;ChargerConfig config_;CapabilityPage capabilities_;Result result_;
 bool haveMeter_=false,haveMeterConfig_=false;uint32_t meterReceivedAt_=0;MeterReadings meter_;MeterConfig meterConfig_;
 AdapterResponse adapter_;bool haveAdapter_=false;uint32_t adapterReceivedAt_=0;
 Packet pendingPacket_,subscribePacket_;bool pending_=false,subPending_=false;uint32_t pendingSince_=0,pendingSent_=0;unsigned retries_=0;
 Packet packet(Kind kind){Packet p;p.header.kind=kind;if(!++sequence_)++sequence_;p.header.sequence=sequence_;p.header.deviceId=id_;p.header.bootId=boot_;p.header.sessionId=session_;if(selected_>=0)p.header.targetBootId=devices_[selected_].bootId;return p;}
 void message(ResultCode code,const char*text){result_=Result();result_.code=code;strncpy(result_.message,text,sizeof(result_.message)-1);++event_;}
 bool sendSelected(const Packet&p){return selected_>=0&&transport_.send(devices_[selected_].mac,p);}
 bool command(Packet&p){if(selected_<0||pending_)return false;pendingPacket_=p;pending_=true;pendingSince_=pendingSent_=now_;retries_=1;sendSelected(p);return true;}
 void sendDiscover(){static const uint8_t broadcast[6]={255,255,255,255,255,255};Packet p=packet(Kind::Discover);p.header.targetBootId=0;p.header.sessionId=0;transport_.send(broadcast,p);lastDiscover_=now_;}
 void sendHeartbeat(){if(selected_<0||!wantSubscription_||!heartbeatEnabled_)return;Packet p=packet(Kind::Heartbeat);Heartbeat h;h.subscriptionId=subscriptionId_;h.owner=owner_;write(p,h);lastHeartbeatSequence_=p.header.sequence;sendSelected(p);lastHeartbeat_=now_;}
 void startSubscription(){if(selected_<0)return;Packet p=packet(Kind::Subscribe);Subscription s;s.subscriptionId=subscriptionId_;s.interval_ms=interval_;write(p,s);subscribePacket_=p;subPending_=true;subSent_=now_;sendSelected(p);}
 void rebooted(){subscribed_=false;subPending_=false;owner_=false;session_=0;lastServerSequence_=0;haveTelemetry_=false;haveConfig_=false;haveMeter_=haveMeterConfig_=false;if(pending_){pending_=false;message(ResultCode::Rejected,"Device restarted; command cancelled");}else message(ResultCode::Rejected,"Device restarted; session ownership cleared");}
 void receiveOne(const Received&rx){
  const Packet&p=rx.packet;if(p.header.deviceId==id_)return;
  if(p.header.kind==Kind::Advertise){Advertisement a;if(!read(p,a)||a.channel<1||a.channel>14)return;size_t i=0;for(;i<count_;i++)if(devices_[i].deviceId==p.header.deviceId)break;
   if(i==count_){if(count_==12)return;++count_;}auto&d=devices_[i];bool changed=d.bootId&&d.bootId!=p.header.bootId;
   memcpy(d.mac,rx.mac,6);d.deviceId=p.header.deviceId;d.bootId=p.header.bootId;d.lastSeen_ms=now_;d.advertisement=a;++event_;
   if(int(i)==selected_){if(changed)rebooted();lastReply_=now_;recovering_=false;transport_.setChannel(a.channel);if(wantSubscription_&&!subscribed_)startSubscription();else if(wantSubscription_&&subscribed_)sendHeartbeat();}return;
  }
  if(selected_<0)return;auto&d=devices_[selected_];if(p.header.deviceId!=d.deviceId||p.header.bootId!=d.bootId||p.header.targetBootId!=boot_||!sameMac(d.mac,rx.mac))return;
  bool expectedReply=(pending_&&p.header.replyTo==pendingPacket_.header.sequence)||(subPending_&&p.header.replyTo==subscribePacket_.header.sequence);
  if(lastServerSequence_&&!newerSequence(p.header.sequence,lastServerSequence_)&&!expectedReply)return;
  bool accepted=false;
  switch(p.header.kind){
   case Kind::HeartbeatAck:{HeartbeatAck h;if(!read(p,h)||h.subscriptionId!=subscriptionId_)break;subscribed_=wantSubscription_;subPending_=false;session_=p.header.sessionId;owner_=h.owner;accepted=true;break;}
   case Kind::Telemetry:{if(d.advertisement.type!=EquipmentType::Charger)break;Telemetry t;if(!read(p,t))break;telemetry_=t;telemetryReceivedAt_ms_=now_;haveTelemetry_=true;session_=p.header.sessionId;owner_=t.ownerDeviceId==id_&&t.ownerBootId==boot_&&(t.state==OperatingState::Charging||t.state==OperatingState::Starting);accepted=true;++event_;break;}
   case Kind::Config:{if(d.advertisement.type!=EquipmentType::Charger)break;ChargerConfig c;if(!read(p,c))break;config_=c;haveConfig_=true;accepted=true;if(pending_&&p.header.replyTo==pendingPacket_.header.sequence){pending_=false;message(ResultCode::Applied,"Configuration received");}break;}
   case Kind::Capabilities:{CapabilityPage c;if(!read(p,c))break;capabilities_=c;accepted=true;if(pending_&&p.header.replyTo==pendingPacket_.header.sequence){pending_=false;message(ResultCode::Applied,"Capabilities received");}break;}
   case Kind::Result:{Result r;if(!read(p,r))break;
    if(subPending_&&p.header.replyTo==subscribePacket_.header.sequence){subPending_=false;if(r.code==ResultCode::Applied){subscribed_=wantSubscription_;sendHeartbeat();}else{wantSubscription_=subscribed_=false;result_=r;++event_;}accepted=true;}
    else if(pending_&&p.header.replyTo==pendingPacket_.header.sequence){Kind action=pendingPacket_.header.kind;pending_=false;result_=r;session_=p.header.sessionId;if(r.code==ResultCode::Applied){if(action==Kind::Start){owner_=true;config_=r.effective;haveConfig_=true;sendHeartbeat();}else if(action==Kind::Abort)owner_=false;}accepted=true;++event_;}
    else if(wantSubscription_&&p.header.replyTo==lastHeartbeatSequence_&&r.code==ResultCode::Rejected){subscribed_=false;startSubscription();accepted=true;}
    break;}
   case Kind::MeterReadings:{
    if(d.advertisement.type!=EquipmentType::CurrentMeter||!pending_||pendingPacket_.header.kind!=Kind::GetMeterReadings||p.header.replyTo!=pendingPacket_.header.sequence)break;
    MeterReadings value;if(!read(p,value))break;uint64_t transit=elapsed(now_,pendingSince_);
    value.electricalAge_ms=uint32_t((uint64_t(value.electricalAge_ms)+transit)>UINT32_MAX?UINT32_MAX:uint64_t(value.electricalAge_ms)+transit);
    value.temperatureAge_ms=uint32_t((uint64_t(value.temperatureAge_ms)+transit)>UINT32_MAX?UINT32_MAX:uint64_t(value.temperatureAge_ms)+transit);
    meter_=value;haveMeter_=true;meterReceivedAt_=now_;session_=p.header.sessionId;
    pending_=false;owner_=false;message(ResultCode::Applied,"Meter readings received");accepted=true;break;}
   case Kind::MeterConfig:{
    if(d.advertisement.type!=EquipmentType::CurrentMeter||!pending_||pendingPacket_.header.kind!=Kind::GetMeterConfig||p.header.replyTo!=pendingPacket_.header.sequence)break;
    MeterConfig value;if(!read(p,value))break;meterConfig_=value;haveMeterConfig_=true;session_=p.header.sessionId;
    pending_=false;message(ResultCode::Applied,"Meter profile received");accepted=true;break;}
   case Kind::MeterResult:{
    if(d.advertisement.type!=EquipmentType::CurrentMeter)break;
    MeterResult value;if(!read(p,value))break;
    if(pending_&&p.header.replyTo==pendingPacket_.header.sequence){
     pending_=false;session_=p.header.sessionId;message(value.code,value.message);result_.confirmationToken=value.token;accepted=true;
    }else if(wantSubscription_&&p.header.replyTo==lastHeartbeatSequence_&&value.code==ResultCode::Rejected){
     subscribed_=false;startSubscription();accepted=true;
    }else if(subPending_&&p.header.replyTo==subscribePacket_.header.sequence){
     subPending_=false;wantSubscription_=subscribed_=false;message(value.code,value.message);accepted=true;
    }break;}
   case Kind::AdapterResponse:{
    if(d.advertisement.type!=EquipmentType::SMBusAdapter||!pending_||pendingPacket_.header.kind!=Kind::AdapterRequest||p.header.replyTo!=pendingPacket_.header.sequence)break;
    AdapterResponse value;AdapterRequest request;if(!read(p,value)||!read(pendingPacket_,request)||value.op!=request.op)break;
    adapter_=value;haveAdapter_=true;adapterReceivedAt_=now_;session_=p.header.sessionId;pending_=false;owner_=false;
    message(value.code,value.message[0]?value.message:"Adapter response");result_.confirmationToken=value.token;accepted=true;break;}
   default:break;
  }
  if(accepted){if(!lastServerSequence_||newerSequence(p.header.sequence,lastServerSequence_))lastServerSequence_=p.header.sequence;lastReply_=now_;d.lastSeen_ms=now_;recovering_=false;}
 }
 public:
 Client(Transport&transport,uint64_t deviceId,uint32_t bootId):transport_(transport),id_(deviceId),boot_(bootId?bootId:1){}
 void tick(uint32_t now_ms){
  now_=now_ms;Received rx;for(unsigned i=0;i<24&&transport_.receive(rx);i++)receiveOne(rx);
  uint32_t commandTimeout_ms=5000;
  if(pending_&&pendingPacket_.header.kind==Kind::AdapterRequest){AdapterRequest r;if(read(pendingPacket_,r)&&(r.op==AdapterOp::DiscoverDut||r.op==AdapterOp::Refresh||r.op==AdapterOp::GraphStart))commandTimeout_ms=120000;}
  if(pending_){if(elapsed(now_,pendingSince_)>=commandTimeout_ms){pending_=false;message(ResultCode::Timeout,"No command acknowledgment; inspect device state before retrying");}
   else if(elapsed(now_,pendingSent_)>=500){sendSelected(pendingPacket_);pendingSent_=now_;++retries_;}}
  if(subPending_&&elapsed(now_,subSent_)>=600){sendSelected(subscribePacket_);subSent_=now_;}
  bool lost=selected_>=0&&elapsed(now_,lastReply_)>=2500;
  if(selected_<0||lost){recovering_=selected_>=0;if(elapsed(now_,lastHop_)>=300){uint8_t first=transport_.firstChannel(),n=transport_.channelCount(),current=transport_.channel();uint8_t next=(!n||current<first||unsigned(current)>=unsigned(first)+n)?first:uint8_t(first+(current-first+1)%n);transport_.setChannel(next);lastHop_=now_;sendDiscover();}}
  else{recovering_=false;if(elapsed(now_,lastDiscover_)>=3000)sendDiscover();}
  if(wantSubscription_&&elapsed(now_,lastHeartbeat_)>=HeartbeatInterval_ms)sendHeartbeat();
 }
 void discover(){sendDiscover();if(selected_<0)lastHop_=now_-300;}
 bool select(size_t index){if(index>=count_)return false;if(selected_==int(index))return true;if(selected_>=0&&owner_)return false;
  if(selected_>=0&&int(index)!=selected_)unsubscribe();selected_=int(index);haveTelemetry_=haveConfig_=false;haveMeter_=haveMeterConfig_=false;session_=0;owner_=false;lastServerSequence_=0;lastReply_=now_;pending_=false;recovering_=false;
  transport_.setChannel(devices_[index].advertisement.channel);return subscribe();}
 bool clearSelection(){if(owner_)return false;if(selected_>=0)unsubscribe();selected_=-1;haveTelemetry_=haveConfig_=false;haveMeter_=haveMeterConfig_=false;pending_=subPending_=false;session_=0;recovering_=false;lastServerSequence_=0;lastHop_=now_-300;return true;}
 bool subscribe(uint16_t interval_ms=1000){if(selected_<0)return false;interval_=interval_ms<500?500:interval_ms>5000?5000:interval_ms;
  if(!wantSubscription_){if(!++subscriptionId_)++subscriptionId_;}wantSubscription_=true;startSubscription();return true;}
 bool unsubscribe(){if(selected_<0)return false;Packet p=packet(Kind::Unsubscribe);Subscription s;s.subscriptionId=subscriptionId_;s.interval_ms=interval_;write(p,s);bool sent=sendSelected(p);wantSubscription_=subscribed_=subPending_=false;return sent;}
 bool start(const ChargerConfig&config,bool proceed=false,uint32_t confirmationToken=0){if(selected_<0||!wantSubscription_)return false;Packet p=packet(Kind::Start);StartRequest request;request.config=config;request.proceed=proceed;request.confirmationToken=confirmationToken;if(!write(p,request))return false;return command(p);}
 bool abort(){Packet p=packet(Kind::Abort);return command(p);}
 bool meterSelected(uint32_t capability)const{return selected_>=0&&devices_[selected_].advertisement.type==EquipmentType::CurrentMeter&&(devices_[selected_].advertisement.capabilities&capability)==capability;}
 bool cancelMeterPoll(){if(!pending_||pendingPacket_.header.kind!=Kind::GetMeterReadings)return false;pending_=false;return true;}
 bool getMeterReadings(){if(!meterSelected(MeterPoll)||!subscribed_)return false;Packet p=packet(Kind::GetMeterReadings);return command(p);}
 bool getMeterConfig(){if(!meterSelected(MeterRecord)||!subscribed_)return false;Packet p=packet(Kind::GetMeterConfig);return command(p);}
 bool startMeter(const MeterConfig&config){if(!meterSelected(MeterRecord)||!subscribed_||!validMeterConfig(config))return false;Packet p=packet(Kind::MeterStart);write(p,config);return command(p);}
 bool stopMeter(){if(!meterSelected(MeterRecord)||!subscribed_)return false;Packet p=packet(Kind::MeterStop);return command(p);}
 bool clearMeter(bool confirmed=false,uint32_t token=0){if(!meterSelected(MeterClearConfirmed)||!subscribed_)return false;Packet p=packet(Kind::MeterClear);MeterClear c;c.confirmed=confirmed;c.token=token;write(p,c);return command(p);}
 const MeterReadings& meterReadings()const{return meter_;}bool hasMeterReadings()const{return haveMeter_;}
 const MeterConfig& meterConfig()const{return meterConfig_;}bool hasMeterConfig()const{return haveMeterConfig_;}
 uint32_t meterAge_ms(uint32_t sampleAge_ms)const{uint64_t age=uint64_t(sampleAge_ms)+elapsed(now_,meterReceivedAt_);return !haveMeter_||age>UINT32_MAX?UINT32_MAX:uint32_t(age);}
 bool getConfig(){Packet p=packet(Kind::GetConfig);return command(p);}
 bool adapterRequest(const AdapterRequest&request){if(selected_<0||!subscribed_||devices_[selected_].advertisement.type!=EquipmentType::SMBusAdapter)return false;Packet p=packet(Kind::AdapterRequest);if(!write(p,request))return false;haveAdapter_=false;return command(p);}
 bool cancelAdapterRead(){AdapterRequest r;if(!pending_||pendingPacket_.header.kind!=Kind::AdapterRequest||!read(pendingPacket_,r)||adapterMutation(r.op))return false;pending_=false;return true;}
 const AdapterResponse& adapterResponse()const{return adapter_;}bool hasAdapterResponse()const{return haveAdapter_;}
 uint32_t adapterResponseAge_ms()const{return elapsed(now_,adapterReceivedAt_);}
 bool getCapabilities(uint8_t page=0){Packet p=packet(Kind::GetCapabilities);CapabilityRequest r;r.page=page;write(p,r);return command(p);}
 void setHeartbeatEnabled(bool enabled){heartbeatEnabled_=enabled;if(enabled)lastHeartbeat_=now_-HeartbeatInterval_ms;}
 bool heartbeatEnabled()const{return heartbeatEnabled_;}bool subscribed()const{return subscribed_;}bool ownsSession()const{return owner_;}
 size_t deviceCount()const{return count_;}const Device& device(size_t index)const{return devices_[index<count_?index:0];}
 const Device* selected()const{return selected_<0?nullptr:&devices_[selected_];}
 bool connected()const{return selected_>=0&&!recovering_&&subscribed_&&elapsed(now_,lastReply_)<2500;}
 bool recovering()const{return recovering_;}bool pending()const{return pending_;}uint8_t channel()const{return transport_.channel();}
 uint32_t sessionId()const{return session_;}uint32_t lastReplyAge_ms()const{return elapsed(now_,lastReply_);}uint32_t retryCount()const{return retries_;}
 const Telemetry& telemetry()const{return telemetry_;}bool hasTelemetry()const{return haveTelemetry_;}
 uint32_t telemetryAge_ms()const{if(!haveTelemetry_)return UINT32_MAX;uint64_t age=uint64_t(telemetry_.sampleAge_ms)+elapsed(now_,telemetryReceivedAt_ms_);return age>UINT32_MAX?UINT32_MAX:uint32_t(age);}
 const ChargerConfig& config()const{return config_;}bool hasConfig()const{return haveConfig_;}
 const CapabilityPage& capabilities()const{return capabilities_;}const Result& result()const{return result_;}uint32_t eventCounter()const{return event_;}
};
} // namespace lablink
