#pragma once
#include <stdint.h>
// Exact function-like macro from pinned Arduino-ESP32 2.0.17
// cores/esp32/Arduino.h:211. Retain its semantics during encoder compilation.
inline unsigned arduinoWordMacroCalls=0;
inline uint16_t makeWord(uint16_t value){++arduinoWordMacroCalls;return value;}
#define word(...) makeWord(__VA_ARGS__)
