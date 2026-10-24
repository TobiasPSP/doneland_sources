#pragma once
// Exact Arduino ESP32 2.0.17 / ESP-IDF 4.4 callback signatures; not IDF 5.x.
#include <esp_now.h>
#include <esp_wifi.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <atomic>

namespace lablink {
class EspNowTransport:public Transport {
 struct Raw {uint8_t mac[6];uint16_t length;uint32_t receivedAt_ms;uint8_t data[MaxPacket];};
 QueueHandle_t received_=nullptr;wifi_interface_t interface_=WIFI_IF_STA;bool started_=false;
 std::atomic<uint32_t> receiveDrops_{0};uint32_t malformed_=0,sendErrors_=0;esp_err_t lastError_=ESP_OK;
 static std::atomic<EspNowTransport*>& instance(){static std::atomic<EspNowTransport*> value{nullptr};return value;}
 static void receivedCallback(const uint8_t*mac,const uint8_t*data,int length){
  auto*self=instance().load(std::memory_order_acquire);if(!self||!self->received_||!mac||!data||length<int(HeaderSize)||length>int(MaxPacket))return;
  Raw raw;memcpy(raw.mac,mac,6);raw.length=uint16_t(length);raw.receivedAt_ms=uint32_t(uint64_t(esp_timer_get_time())/1000);memcpy(raw.data,data,length);
  // Callback runs in WiFi task context, not an ISR. Never parse, allocate or block here.
  if(xQueueSend(self->received_,&raw,0)!=pdTRUE)self->receiveDrops_.fetch_add(1,std::memory_order_relaxed);
 }
 bool ensurePeer(const uint8_t* mac){
  esp_now_peer_info_t peer={};memcpy(peer.peer_addr,mac,6);peer.channel=0;peer.ifidx=interface_;peer.encrypt=false;
  if(esp_now_is_peer_exist(mac))lastError_=esp_now_mod_peer(&peer);else lastError_=esp_now_add_peer(&peer);
  return lastError_==ESP_OK;
 }
 public:
 // Caller must start WiFi and keep its lifecycle serialized with this object's methods.
 bool begin(wifi_interface_t interface=WIFI_IF_STA){
  if(started_)return interface_==interface;auto* active=instance().load(std::memory_order_acquire);if(active&&active!=this)return false;
  interface_=interface;if(!received_)received_=xQueueCreate(12,sizeof(Raw));if(!received_)return false;
  xQueueReset(received_);lastError_=esp_now_init();if(lastError_!=ESP_OK)return false;
  instance().store(this,std::memory_order_release);lastError_=esp_now_register_recv_cb(receivedCallback);if(lastError_!=ESP_OK){end();return false;}
  started_=true;return true;
 }
 void end(){if(instance().load(std::memory_order_acquire)==this){esp_now_unregister_recv_cb();instance().store(nullptr,std::memory_order_release);esp_now_deinit();}started_=false;if(received_)xQueueReset(received_);}
 bool receive(Received& out)override{
  if(!received_)return false;Raw raw;
  while(xQueueReceive(received_,&raw,0)==pdTRUE){Packet p;if(!decode(raw.data,raw.length,p)){++malformed_;continue;}memcpy(out.mac,raw.mac,6);out.packet=p;out.receivedAt_ms=raw.receivedAt_ms;return true;}return false;
 }
 bool send(const uint8_t mac[6],const Packet& packet)override{
  if(!started_||!mac)return false;uint8_t data[MaxPacket];size_t n=encode(packet,data,sizeof data);
  if(!n||!ensurePeer(mac)){++sendErrors_;return false;}lastError_=esp_now_send(mac,data,n);if(lastError_!=ESP_OK){++sendErrors_;return false;}return true;
 }
 bool setChannel(uint8_t value)override{
  wifi_country_t country={};if(esp_wifi_get_country(&country)!=ESP_OK)return false;
  if(value<country.schan||unsigned(value)>=unsigned(country.schan)+country.nchan)return false;
  lastError_=esp_wifi_set_channel(value,WIFI_SECOND_CHAN_NONE);return lastError_==ESP_OK;
 }
 uint8_t channel()const override{uint8_t c=0;wifi_second_chan_t secondary;return esp_wifi_get_channel(&c,&secondary)==ESP_OK?c:0;}
 uint8_t firstChannel()const override{wifi_country_t c={};return esp_wifi_get_country(&c)==ESP_OK?c.schan:1;}
 uint8_t channelCount()const override{wifi_country_t c={};return esp_wifi_get_country(&c)==ESP_OK?c.nchan:11;}
 uint32_t receiveDrops()const{return receiveDrops_.load(std::memory_order_relaxed);}uint32_t malformed()const{return malformed_;}uint32_t sendErrors()const{return sendErrors_;}esp_err_t lastError()const{return lastError_;}
};
} // namespace lablink
