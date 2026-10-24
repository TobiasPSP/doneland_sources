#pragma once
#include <stdint.h>
namespace batcharger { namespace limits {
// Instance limits shared by validation and the published capability descriptor.
// Hardware ranges/steps verified in the exact IP2366Control source + its
// REGISTER_CONTRACT.md; the 100 W battery-side ceiling is application policy.
constexpr uint8_t CellsMin=2,CellsMax=6,PercentMin=0,PercentMax=100,PercentStep=10;
constexpr uint16_t CellMin_mV=2500,CellMax_mV=4400,CellStep_mV=10;
constexpr uint16_t CurrentMin_mA=100,CurrentMax_mA=9700,CurrentStep_mA=100;
constexpr uint16_t TerminationMin_mA=50,TerminationMax_mA=750,TerminationStep_mA=50;
constexpr uint32_t PowerMax_mW=100000;
} }
