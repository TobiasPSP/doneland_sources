#pragma once
#include <LabLink.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <atomic>
namespace batcharger {
// Network task owns radio and its lifecycle. Main task consumes/produces only
// copied messages, so radio callbacks and WiFi restarts cannot touch hardware UI.
class LabQueue:public lablink::Transport {
    QueueHandle_t rx_=nullptr,tx_=nullptr;
    std::atomic<uint8_t> channel_{0};std::atomic<bool> ready_{false};
    std::atomic<uint32_t> drops_{0};
public:
    bool begin(){rx_=xQueueCreate(12,sizeof(lablink::Received));tx_=xQueueCreate(20,sizeof(lablink::Received));return rx_&&tx_;}
    bool receive(lablink::Received &out)override{return rx_&&xQueueReceive(rx_,&out,0)==pdTRUE;}
    bool send(const uint8_t *mac,const lablink::Packet &p)override{
        if(!ready_.load()||!tx_)return false;lablink::Received out;memcpy(out.mac,mac,6);out.packet=p;
        if(xQueueSend(tx_,&out,0)==pdTRUE)return true;++drops_;return false;
    }
    bool setChannel(uint8_t)override{return false;} // charger follows its WiFi/AP channel
    uint8_t channel()const override{return channel_.load();}
    bool ready()const{return ready_.load();}
    uint32_t drops()const{return drops_.load();}
    void sendFailure(){++drops_;}
    void radioState(bool ready,uint8_t channel){ready_.store(ready);channel_.store(channel);}
    bool deliver(const lablink::Received &in){if(rx_&&xQueueSend(rx_,&in,0)==pdTRUE)return true;++drops_;return false;}
    bool outgoing(lablink::Received &out){return tx_&&xQueueReceive(tx_,&out,0)==pdTRUE;}
    void discard(){lablink::Received message;while(rx_&&xQueueReceive(rx_,&message,0)==pdTRUE){}while(tx_&&xQueueReceive(tx_,&message,0)==pdTRUE){}}
};
} // namespace batcharger
