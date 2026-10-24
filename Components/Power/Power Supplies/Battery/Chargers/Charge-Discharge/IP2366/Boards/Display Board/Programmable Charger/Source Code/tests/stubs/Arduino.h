#pragma once
#include <stdint.h>
#include <deque>
#include <vector>
#include <assert.h>
// GPIO constants from Arduino-ESP32 2.0.17 esp32-hal-gpio.h.
#define LOW 0
#define HIGH 1
#define OUTPUT 0x03
#define PULLUP 0x04
#define OUTPUT_OPEN_DRAIN 0x13
namespace gpioTest {
struct Edge {int sda;};
static uint32_t time_us=0;
static int sda=1,scl=1;
static bool holdClock=false;
static unsigned prepareDelays=0,byteDelays=0;
static std::deque<int> readSda;
static std::vector<Edge> rising;
static std::vector<int> pinModes;
static void reset(){sda=scl=1;holdClock=false;prepareDelays=byteDelays=0;readSda.clear();rising.clear();}
}
inline void pinMode(int pin,int mode){if(pin==17||pin==18)assert(mode==(OUTPUT_OPEN_DRAIN|PULLUP));gpioTest::pinModes.push_back(pin);}
inline void digitalWrite(int pin,int value){if(pin==17)gpioTest::sda=value;if(pin==18){if(value==HIGH)gpioTest::rising.push_back({gpioTest::sda});gpioTest::scl=value;}}
inline int digitalRead(int pin){if(pin==18)return gpioTest::holdClock?0:gpioTest::scl;assert(pin==17);assert(!gpioTest::readSda.empty());int value=gpioTest::readSda.front();gpioTest::readSda.pop_front();return value;}
inline void delayMicroseconds(unsigned us){gpioTest::time_us+=us;if(us==50)++gpioTest::prepareDelays;}
inline void delay(unsigned ms){gpioTest::time_us+=ms*1000;if(ms==1)++gpioTest::byteDelays;}
inline uint32_t micros(){return ++gpioTest::time_us;}
