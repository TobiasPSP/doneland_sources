#pragma once
#include "app_options.h"
namespace batcharger {
enum class RemoteAction:uint8_t {Start,Abort,Summary,Configure,Settings,Cancel};
struct RemoteCommand {
    uint32_t id=0,revision=0;
    RemoteAction action=RemoteAction::Start;
    Config config;
    AppOptions options;
    bool proceed=false;
};
struct RemoteResult {
    uint32_t id=0,revision=0;
    uint8_t code=0; // 0 applied, 1 rejected, 2 explicit battery confirmation needed
    char message[160]={};
};
inline bool sameConfig(const Config &a,const Config &b){return a.chemistry==b.chemistry&&a.cells==b.cells&&a.percent==b.percent&&a.cell_mV==b.cell_mV&&a.current_mA==b.current_mA&&a.termination_mA==b.termination_mA&&a.terminationTime_min==b.terminationTime_min;}
} // namespace batcharger
