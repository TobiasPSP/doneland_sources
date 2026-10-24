#pragma once
#include <stdint.h>
namespace batcharger {
enum class WifiState:uint8_t {Off,Connecting,Connected,AccessPoint};
struct WifiSignal {
    WifiState state=WifiState::Off;
    int16_t rssi_dBm=0;
    unsigned level()const{
        if(state==WifiState::AccessPoint)return 4;
        if(state!=WifiState::Connected)return 0;
        return rssi_dBm>=-55?4:rssi_dBm>=-65?3:rssi_dBm>=-75?2:1;
    }
};
} // namespace batcharger
