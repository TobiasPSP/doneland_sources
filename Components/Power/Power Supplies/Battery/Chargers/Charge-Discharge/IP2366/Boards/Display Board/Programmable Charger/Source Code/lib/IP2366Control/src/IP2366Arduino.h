#pragma once
#include <Arduino.h>
#include "IP2366.h"

// Software I2C deliberately permits the IP2366's 50 us preparation delay AFTER
// each address ACK. Arduino-ESP32 2.0.17 Wire queues repeated-start writes and
// cannot insert that delay within its combined transaction. Touch still uses Wire.
// Open-drain modes verified in pinned esp32-hal-gpio.h/.c. Max nominal 100 kHz;
// actual GPIO overhead/interrupts slow it down. No push-pull HIGH on SDA/SCL.
namespace ip2366 {
class ArduinoTransport final:public Transport {
    const int Sda,Scl,Wake;
    const uint8_t Address;
    bool sclHigh(){
        digitalWrite(Scl,HIGH);uint32_t begin_us=micros();
        while(!digitalRead(Scl)){if(uint32_t(micros()-begin_us)>=2000)return false;}
        delayMicroseconds(5);return true;
    }
    void sclLow(){digitalWrite(Scl,LOW);delayMicroseconds(5);}
    bool start(){
        digitalWrite(Sda,HIGH);if(!sclHigh()||!digitalRead(Sda))return false;
        digitalWrite(Sda,LOW);delayMicroseconds(5);sclLow();return true;
    }
    bool stop(){
        digitalWrite(Sda,LOW);delayMicroseconds(5);bool ok=sclHigh();
        digitalWrite(Sda,HIGH);delayMicroseconds(5);return ok&&digitalRead(Sda);
    }
    bool send(uint8_t byte){
        for(unsigned bit=0;bit<8;++bit){digitalWrite(Sda,(byte&0x80)?HIGH:LOW);byte<<=1;
            if(!sclHigh())return false;sclLow();}
        digitalWrite(Sda,HIGH);if(!sclHigh())return false;
        bool ack=!digitalRead(Sda);sclLow();return ack;
    }
    bool address(bool read){bool ok=send(uint8_t(Address<<1)|(read?1:0));delayMicroseconds(50);return ok;}
    bool receive(uint8_t &byte){
        byte=0;digitalWrite(Sda,HIGH);
        for(unsigned bit=0;bit<8;++bit){if(!sclHigh())return false;byte=uint8_t(byte<<1)|uint8_t(digitalRead(Sda));sclLow();}
        // One byte per read: release SDA for final NACK, then STOP.
        digitalWrite(Sda,HIGH);if(!sclHigh())return false;sclLow();return true;
    }
public:
    explicit ArduinoTransport(int sda_gpio=17,int scl_gpio=18,int wake_gpio=6,uint8_t address_7bit=0x75)
        :Sda(sda_gpio),Scl(scl_gpio),Wake(wake_gpio),Address(address_7bit){}
    uint32_t failures=0;
    void begin(){
        if(Address>0x7F)return;
        if(Wake>=0){digitalWrite(Wake,HIGH);pinMode(Wake,OUTPUT);}
        digitalWrite(Sda,HIGH);digitalWrite(Scl,HIGH);
        pinMode(Sda,OUTPUT_OPEN_DRAIN|PULLUP);pinMode(Scl,OUTPUT_OPEN_DRAIN|PULLUP);
        delay(110); // GPIO6 side HIGH; physical INT level is an external hardware responsibility.
    }
    bool probe()override{if(Address>0x7F){++failures;return false;}bool ok=start()&&address(false);bool ended=stop();delay(1);if(!ok||!ended)++failures;return ok&&ended;}
    bool recover()override{
        if(Address>0x7F){++failures;return false;}
        digitalWrite(Sda,HIGH);digitalWrite(Scl,HIGH);
        if(!sclHigh())return false;
        for(unsigned i=0;i<9&&!digitalRead(Sda);++i){sclLow();if(!sclHigh())return false;}
        return stop();
    }
    bool read(uint8_t reg,uint8_t &value)override{
        if(Address>0x7F){++failures;return false;}
        bool ok=start()&&address(false)&&send(reg)&&start()&&address(true)&&receive(value);
        bool ended=stop();delay(1);if(!ok||!ended)++failures;return ok&&ended;
    }
    bool write(uint8_t reg,uint8_t value)override{
        if(Address>0x7F){++failures;return false;}
        bool ok=start()&&address(false)&&send(reg)&&send(value);
        bool ended=stop();delay(1);if(!ok||!ended)++failures;return ok&&ended;
    }
};

} // namespace ip2366
