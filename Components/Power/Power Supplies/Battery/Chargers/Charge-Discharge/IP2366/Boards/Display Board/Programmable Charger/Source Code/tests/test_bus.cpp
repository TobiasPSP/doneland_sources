#include <IP2366Arduino.h>
#include <stdio.h>
static uint8_t byteAt(unsigned first){uint8_t value=0;for(unsigned i=0;i<8;++i)value=uint8_t(value<<1)|gpioTest::rising.at(first+i).sda;return value;}
int main(){
    ip2366::ArduinoTransport bus;bus.begin();gpioTest::reset();
    gpioTest::readSda={1,0,1};assert(bus.probe());assert(byteAt(1)==0xEA);assert(gpioTest::prepareDelays==1);assert(gpioTest::readSda.empty());
    gpioTest::reset();gpioTest::readSda={1,0,0,0,1};assert(bus.write(0x02,170));
    assert(byteAt(1)==0xEA);assert(byteAt(10)==0x02);assert(byteAt(19)==170);assert(gpioTest::rising.size()==29);assert(gpioTest::byteDelays==1);
    gpioTest::reset();gpioTest::readSda={1,0,0,1,0,1,0,1,0,0,1,0,1,1};uint8_t value=0;
    assert(bus.read(0x50,value)&&value==0xA5);assert(byteAt(1)==0xEA);assert(byteAt(10)==0x50);assert(byteAt(20)==0xEB);
    assert(gpioTest::rising.size()==39);assert(gpioTest::rising[37].sda==HIGH); // final read byte NACK
    assert(gpioTest::prepareDelays==2&&gpioTest::byteDelays==1&&gpioTest::readSda.empty());
    gpioTest::reset();gpioTest::readSda={1,1,1};assert(!bus.probe()); // address NACK
    gpioTest::reset();gpioTest::holdClock=true;uint32_t before=gpioTest::time_us;assert(!bus.probe());assert(gpioTest::time_us-before<6000); // start + STOP timeouts, plus 1 ms byte gap
    gpioTest::reset();gpioTest::readSda={0,0,0,1,1};assert(bus.recover()); // bounded bus clear then STOP
    gpioTest::reset();ip2366::ArduinoTransport alternate(17,18,6,0x76);gpioTest::readSda={1,0,1};
    assert(alternate.probe()&&byteAt(1)==0xEC); // configurable 7-bit address
    gpioTest::reset();ip2366::ArduinoTransport invalid(17,18,6,0xEA);invalid.begin();
    assert(!invalid.probe()&&!invalid.read(0x50,value)&&!invalid.write(0x00,0)&&!invalid.recover());
    assert(gpioTest::rising.empty()); // reject 8-bit address bytes without touching the bus
    puts("PASS: software I2C byte order, ACK errors, address preparation delays, final NACK, open-drain setup, clock timeout and recovery");
}
