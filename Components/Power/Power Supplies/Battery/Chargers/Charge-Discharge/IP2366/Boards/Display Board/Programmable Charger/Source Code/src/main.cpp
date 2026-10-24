#include <Arduino.h>
#include <Wire.h>
#include <Arduino_GFX_Library.h>
#include <esp_heap_caps.h>
#include <esp_mac.h>
#include <esp_system.h>
#include <lvgl.h>
#include <IP2366Arduino.h>
#include "app_ui.h"
#include "profile_store_arduino.h"
#include "settings_store_arduino.h"
#include "web_service.h"
#include "lab_charger_adapter.h"

namespace {
constexpr int Width=320,Height=480;
Arduino_ESP32QSPI displayBus(45,47,21,48,40,39);
Arduino_AXS15231B panel(&displayBus,GFX_NOT_DEFINED,0,false,Width,Height);
ip2366::ArduinoTransport chargerBus(17,18,6);
batcharger::ArduinoProfileStore profiles;
batcharger::ArduinoSettingsStore settingsStore;
batcharger::AppOptions options;
batcharger::Controller charger(chargerBus,&profiles);
batcharger::Ui ui(charger,&options);
batcharger::WebService *web=nullptr;
batcharger::LabQueue labQueue;
batcharger::LabChargerAdapter labPort(charger,ui);
batcharger::LabChargerServer *lab=nullptr;
bool persistedPreviously=false;
uint16_t *framebuffer;
uint8_t *drawBuffer;
void *lvglPool;
bool touchReady=false;
uint32_t tick_ms(){return millis();}
void fatal(const char *reason){Serial.printf("FATAL: %s\n",reason);for(;;)delay(1000);}
void flush(lv_display_t *display,const lv_area_t *area,uint8_t *pixels){
    int width=area->x2-area->x1+1,height=area->y2-area->y1+1;
    for(int y=0;y<height;++y)memcpy(framebuffer+(area->y1+y)*Width+area->x1,pixels+y*width*2,width*2);
    if(lv_display_flush_is_last(display)){panel.draw16bitRGBBitmap(0,0,framebuffer,Width,Height);}
    lv_display_flush_ready(display);
}
void touch(lv_indev_t *,lv_indev_data_t *data){
    data->state=LV_INDEV_STATE_RELEASED;if(!touchReady)return;
    // Exact command/one-contact decode reused from working v25 baseline.
    static const uint8_t command[]={0xb5,0xab,0xa5,0x5a,0,0,0,8,0,0,0};
    Wire.beginTransmission(0x3b);Wire.write(command,sizeof(command));
    uint8_t result=Wire.endTransmission(true);
    size_t count=result==0?Wire.requestFrom(uint8_t(0x3b),size_t(8),true):0;
    if(result||count!=8){while(Wire.available())Wire.read();return;}
    uint8_t raw[8];for(auto &b:raw)b=Wire.read();if(raw[1]!=1)return;
    uint16_t x=uint16_t(raw[2]&15)<<8|raw[3],y=uint16_t(raw[4]&15)<<8|raw[5];
    if(x>=Width||y>=Height)return;
    data->point.x=x;data->point.y=y;data->state=LV_INDEV_STATE_PRESSED;
}
}
extern "C" void *tablet_lvgl_pool_alloc(size_t size){return size<=LV_MEM_SIZE?lvglPool:nullptr;}
void setup(){
    Serial.begin(115200);pinMode(1,OUTPUT);digitalWrite(1,LOW);
    // Snapshot the live charging profile, then disable before display startup.
    chargerBus.begin();charger.initialize(millis());
    if(!psramFound())fatal("PSRAM unavailable");
    if(!charger.history.prepare())fatal("Session history PSRAM allocation failed");
    framebuffer=static_cast<uint16_t *>(heap_caps_calloc(Width*Height,2,MALLOC_CAP_SPIRAM|MALLOC_CAP_8BIT));
    drawBuffer=static_cast<uint8_t *>(heap_caps_malloc(Width*20*2,MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT));
    lvglPool=heap_caps_malloc(LV_MEM_SIZE,MALLOC_CAP_SPIRAM|MALLOC_CAP_8BIT);
    if(!framebuffer||!drawBuffer||!lvglPool)fatal("Display/LVGL allocation failed");
    if(!panel.begin())fatal("AXS15231B initialization failed");
    panel.draw16bitRGBBitmap(0,0,framebuffer,Width,Height);digitalWrite(1,HIGH);
    touchReady=Wire.begin(4,8,400000);Wire.setTimeOut(20);
    lv_init();lv_tick_set_cb(tick_ms);
    auto *display=lv_display_create(Width,Height);if(!display)fatal("Display allocation failed");
    lv_display_set_color_format(display,LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(display,drawBuffer,nullptr,Width*20*2,LV_DISPLAY_RENDER_MODE_PARTIAL);lv_display_set_flush_cb(display,flush);
    auto *input=lv_indev_create();if(!input)fatal("Input allocation failed");
    lv_indev_set_type(input,LV_INDEV_TYPE_POINTER);lv_indev_set_read_cb(input,touch);
    batcharger::Config restored;bool persisted=settingsStore.load(options,restored);persistedPreviously=options.persist;
    ui.begin(persisted?&restored:nullptr);
    uint8_t mac[6];uint32_t bootId=esp_random();if(!bootId)bootId=1;
    if(esp_read_mac(mac,ESP_MAC_WIFI_STA)==ESP_OK&&labQueue.begin())
        lab=new batcharger::LabChargerServer(labPort,labQueue,lablink::deviceIdFromMac(mac),bootId,options.friendlyName,batcharger::FirmwareVersion);
    else ui.notify("ESP-NOW interface allocation failed.");
    web=new batcharger::WebService(ui,charger,options,labQueue);
    if(!web->begin())ui.notify("WiFi interface could not start.");
    Serial.printf("BatCharger %s ready. Version and raw diagnostics are on the gear screen.\n",batcharger::FirmwareVersion);
}
void loop(){
    if(web)web->poll();
    uint32_t now_ms=millis();ui.commands(now_ms);auto previousState=charger.state;
    if(lab){lab->name(options.friendlyName);lab->tick(options.espNow&&labQueue.ready(),millis());}
    charger.tick(millis());
    static uint32_t labStatusAt_ms=0;
    if(lab&&uint32_t(millis()-labStatusAt_ms)>=500){labStatusAt_ms=millis();char status[256];const auto &owner=lab->owner();
        snprintf(status,sizeof(status),"ESP-NOW %s / channel %u\nID %016llX / boot %08lX\nSubscribers %u/8 / drops %lu\nOwner %016llX / heartbeat age %lu ms",
            !options.espNow?"off":labQueue.ready()?"ready":"starting",labQueue.channel(),(unsigned long long)lab->deviceId(),(unsigned long)lab->bootId(),lab->subscriberCount(),
            (unsigned long)(labQueue.drops()+lab->txDropped()),(unsigned long long)owner.deviceId(),(unsigned long)owner.age_ms(millis()));ui.labStatus(status);
    }
    static uint32_t savedSession=0;
    static batcharger::AppOptions savedOptions;static bool haveSavedOptions=false;
    static batcharger::AppOptions savedPreferences;static bool haveSavedPreferences=false,preferenceWarning=false;static uint32_t retryPreferences_ms=0;
    if((!haveSavedPreferences||!batcharger::sameOptions(options,savedPreferences))&&
       (!retryPreferences_ms||uint32_t(now_ms-retryPreferences_ms)>=2000)){
        if(settingsStore.saveOptions(options)){savedPreferences=options;haveSavedPreferences=true;retryPreferences_ms=0;preferenceWarning=false;}
        else{retryPreferences_ms=now_ms;if(!preferenceWarning){preferenceWarning=true;ui.notify("Preferences could not be saved. Retrying.");}}}
    if(charger.sessionsStarted!=savedSession){savedSession=charger.sessionsStarted;haveSavedOptions=false;}
    bool charging=charger.state==batcharger::State::Starting||charger.state==batcharger::State::Charging;
    if(options.persist&&charging&&(!haveSavedOptions||!batcharger::sameOptions(options,savedOptions))){
        savedOptions=options;haveSavedOptions=true;
        if(!settingsStore.save(options,charger.activeConfig())){charger.profileSaveFailed=true;ui.notify("Settings could not be persisted.");}}
    if(!options.persist)haveSavedOptions=false;
    if(persistedPreviously&&!options.persist&&!settingsStore.disable())ui.notify("Saved charger config could not be removed.");
    persistedPreviously=options.persist;
    static uint32_t refreshed_ms=0;
    if(charger.state!=previousState||uint32_t(millis()-refreshed_ms)>=125){refreshed_ms=millis();ui.refresh();}
    // Read-only diagnostics; never changes settings or applies guessed calibration.
    if(Serial.available()){int command=Serial.read();if(command=='d'||command=='D'){
        char text[1200];batcharger::diagnosticText(charger,text,sizeof(text));Serial.println(text);}}
    lv_timer_handler();if(web)web->publish();delay(3);
}
