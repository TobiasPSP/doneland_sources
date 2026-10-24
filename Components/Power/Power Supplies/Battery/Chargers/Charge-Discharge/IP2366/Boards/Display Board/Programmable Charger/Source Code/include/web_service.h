#pragma once
#include <WiFi.h>
#include <esp_wifi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <esp_heap_caps.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <new>
#include "web_model.h"
#include "web_page.h"
#include "lab_queue.h"
namespace batcharger {
// Network task serializes coherent cached snapshots and submits typed commands.
// Only poll()/publish() access LVGL/controller, always on the main task.
class WebService {
    Ui &ui_;Controller &controller_;AppOptions &options_;LabQueue &lab_;
    lablink::EspNowTransport radio_;
    SemaphoreHandle_t radioMutex_=nullptr;bool radioActive_=false;
    WebServer server_{80};SemaphoreHandle_t mutex_=nullptr;QueueHandle_t commands_=nullptr,results_=nullptr;
    WebSnapshot *shared_=nullptr,*sending_=nullptr;char *json_=nullptr;
    static constexpr size_t JsonCapacity=16384;
    AppOptions sharedOptions_;WifiSignal signal_;
    char networkText_[160]="WiFi off",warning_[220]={};
    bool ready_=false;uint32_t publishedAt_ms_=0;
    static bool number(const String &s,uint32_t &n){if(!s.length()||s.length()>10)return false;uint64_t value=0;
        for(unsigned i=0;i<s.length();++i){if(s[i]<'0'||s[i]>'9')return false;value=value*10+(s[i]-'0');if(value>0xFFFFFFFFu)return false;}n=uint32_t(value);return true;}
    bool field(const char *name,uint32_t &value,uint32_t minimum,uint32_t maximum){return number(server_.arg(name),value)&&value>=minimum&&value<=maximum;}
    bool textField(const char *name,char *out,size_t capacity){if(!server_.hasArg(name))return false;String value=server_.arg(name);if(value.length()>=capacity)return false;memcpy(out,value.c_str(),value.length()+1);return true;}
    void sendJson(int code,size_t length){if(!length){server_.send(500,"application/json","{\"message\":\"Snapshot too large\"}");return;}
        server_.client().setNoDelay(true);server_.sendHeader("Cache-Control","no-store");server_.send(code,"application/json; charset=utf-8",String(json_));}
    void error(int code,const char *message){RemoteResult result;result.code=1;snprintf(result.message,sizeof(result.message),"%s",message);sendJson(code,WebSnapshot::resultJson(json_,JsonCapacity,result));}
    void report(const char *text,const char *warning=nullptr){xSemaphoreTake(mutex_,portMAX_DELAY);
        if(text)snprintf(networkText_,sizeof(networkText_),"%s",text);if(warning)snprintf(warning_,sizeof(warning_),"%s",warning);xSemaphoreGive(mutex_);}
    void snapshot(){xSemaphoreTake(mutex_,portMAX_DELAY);*sending_=*shared_;xSemaphoreGive(mutex_);}
    void command(){
        String origin=server_.header("Origin"),host=server_.header("Host");
        if(origin.length()&&origin!=String("http://")+host){error(403,"Use the tablet web page");return;}
        RemoteCommand c;uint32_t value=0;
        if(!field("id",c.id,1,0xFFFFFFFFu)||!field("revision",c.revision,0,0xFFFFFFFFu)){error(400,"Missing command ID or revision");return;}
        String action=server_.arg("action");
        if(action=="start"){
            c.action=RemoteAction::Start;
            if(!field("chemistry",value,1,3)){error(400,"Select a chemistry");return;}c.config.chemistry=Chemistry(value);
            if(!field("cells",value,2,6)){error(400,"Select 2S through 6S");return;}c.config.cells=uint8_t(value);
            if(!field("percent",value,0,100)){error(400,"Invalid charge level");return;}c.config.percent=uint8_t(value);
            if(!field("cell_mV",value,2500,4400)){error(400,"Invalid cell voltage");return;}c.config.cell_mV=uint16_t(value);
            if(!field("current_mA",value,100,9700)){error(400,"Invalid charge current");return;}c.config.current_mA=uint16_t(value);
            if(!field("termination_mA",value,50,750)){error(400,"Invalid termination current");return;}c.config.termination_mA=uint16_t(value);
            if(!field("terminationTime_min",value,1,65535)){error(400,"Invalid termination time (minutes)");return;}c.config.terminationTime_min=uint16_t(value);
            if(!field("proceed",value,0,1)){error(400,"Invalid confirmation");return;}c.proceed=value;
            if(const char *why=validate(c.config)){error(400,why);return;}
        }else if(action=="abort")c.action=RemoteAction::Abort;
        else if(action=="summary")c.action=RemoteAction::Summary;
        else if(action=="configure")c.action=RemoteAction::Configure;
        else if(action=="cancel")c.action=RemoteAction::Cancel;
        else if(action=="settings"){
            c.action=RemoteAction::Settings;xSemaphoreTake(mutex_,portMAX_DELAY);c.options=sharedOptions_;xSemaphoreGive(mutex_);
            if(!field("persist",value,0,1)){error(400,"Invalid charger persistence flag");return;}c.options.persist=value;
            if(!field("wifi",value,0,1)){error(400,"Invalid WiFi flag");return;}c.options.wifi=value;
            if(!field("espNow",value,0,1)){error(400,"Invalid ESPNow flag");return;}c.options.espNow=value;
            if(!field("mode",value,0,1)){error(400,"Invalid WiFi mode");return;}c.options.mode=WifiMode(value);
            if(!textField("ssid",c.options.ssid,sizeof(c.options.ssid))||!textField("hostname",c.options.hostname,sizeof(c.options.hostname))){error(400,"Invalid WiFi name");return;}
            if(!field("passwordChanged",value,0,1)){error(400,"Invalid password update flag");return;}
            if(value&&!textField("password",c.options.password,sizeof(c.options.password))){error(400,"Password is too long");return;}
            if(!textField("friendlyName",c.options.friendlyName,sizeof(c.options.friendlyName))){error(400,"Friendly name: maximum 31 bytes");return;}
            if(!parseCalibration(server_.arg("voltageCalibration_mV").c_str(),c.options.voltageCalibration_mV)||
               !parseCalibration(server_.arg("currentCalibration_mA").c_str(),c.options.currentCalibration_mA)){error(400,"Calibration: -5000 through +5000");return;}
            if(const char *why=validateOptions(c.options)){error(400,why);return;}
        }else{error(400,"Unknown action");return;}
        RemoteResult result;while(xQueueReceive(results_,&result,0)==pdTRUE){}
        if(xQueueSend(commands_,&c,0)!=pdTRUE){error(409,"Tablet busy; try again");return;}
        uint32_t began=millis();
        while(uint32_t(millis()-began)<2000){uint32_t remaining=2000-uint32_t(millis()-began);
            if(xQueueReceive(results_,&result,pdMS_TO_TICKS(remaining))==pdTRUE&&result.id==c.id){sendJson(result.code==1?409:200,WebSnapshot::resultJson(json_,JsonCapacity,result));return;}}
        error(504,"Command acknowledgement timed out. Check tablet state before retrying.");
    }
    void routes(){
        const char *headers[]={"Origin","Host"};server_.collectHeaders(headers,2);
        server_.on("/",HTTP_GET,[this](){server_.sendHeader("Cache-Control","no-store");server_.sendHeader("Content-Encoding","gzip");server_.send_P(200,"text/html; charset=utf-8",reinterpret_cast<const char *>(WebPageGzip),sizeof(WebPageGzip));});
        server_.on("/assets/montserrat-latin.woff2",HTTP_GET,[this](){server_.sendHeader("Cache-Control","public, max-age=604800");server_.send_P(200,"font/woff2",reinterpret_cast<const char *>(WebFont),sizeof(WebFont));});
        server_.on("/api/state",HTTP_GET,[this](){snapshot();sendJson(200,sending_->stateJson(json_,JsonCapacity));});
        server_.on("/api/model",HTTP_GET,[this](){sendJson(200,WebSnapshot::modelJson(json_,JsonCapacity));});
        server_.on("/api/history",HTTP_GET,[this](){uint32_t session=0,after=0;
            if(!number(server_.arg("session"),session)||!number(server_.arg("after"),after)){error(400,"Invalid history cursor");return;}
            snapshot();sendJson(200,sending_->historyJson(json_,JsonCapacity,session,after));});
        server_.on("/api/diagnostics",HTTP_GET,[this](){snapshot();sendJson(200,sending_->diagnosticsJson(json_,JsonCapacity));});
        server_.on("/api/command",HTTP_POST,[this](){command();});
        server_.onNotFound([this](){error(404,"Not found");});
    }
    void serving(const AppOptions &o,bool ap){
        bool mdns=MDNS.begin(o.hostname);if(mdns)mdns=MDNS.addService("http","tcp",80);
        server_.begin();String ip=(ap?WiFi.softAPIP():WiFi.localIP()).toString();char text[160];
        snprintf(text,sizeof(text),"%s: %.32s\nhttp://%s/\nhttp://%s.local/%s",ap?"AP":"WiFi",ap?o.hostname:o.ssid,ip.c_str(),o.hostname,mdns?"":" (mDNS unavailable)");report(text);
    }
    bool accessPoint(const AppOptions &o,bool fallback){
        WiFi.mode(WIFI_AP);char ssid[33];snprintf(ssid,sizeof(ssid),"%.32s",o.hostname);
        const char *password=strlen(o.password)>=8?o.password:"meincofi66";
        if(!WiFi.softAP(ssid,password)){report("Access Point failed","WiFi Access Point could not start.");return false;}
        serving(o,true);
        if(fallback){char text[220];String ip=WiFi.softAPIP().toString();
            snprintf(text,sizeof(text),"WiFi unavailable. Access Point %s is active. Open http://%s/",ssid,ip.c_str());
            xSemaphoreTake(mutex_,portMAX_DELAY);snprintf(warning_,sizeof(warning_),"%s",text);xSemaphoreGive(mutex_);}
        return true;
    }
    // The radio pump is independent of synchronous HTTP parsing/sending. The
    // network task pauses it before every explicit radio lifecycle change.
    void pauseRadio(){
        xSemaphoreTake(radioMutex_,portMAX_DELAY);lab_.radioState(false,0);
        radioActive_=false;radio_.end();lab_.discard();xSemaphoreGive(radioMutex_);
    }
    bool startRadio(wifi_interface_t interface){
        xSemaphoreTake(radioMutex_,portMAX_DELAY);radioActive_=radio_.begin(interface);
        bool started=radioActive_;lab_.radioState(started,started?radio_.channel():0);
        xSemaphoreGive(radioMutex_);return started;
    }
    void radioTask(){
        for(;;){
            if(xSemaphoreTake(radioMutex_,0)==pdTRUE){
                if(radioActive_){lablink::Received message;
                    lab_.radioState(true,radio_.channel());
                    for(unsigned i=0;i<8&&radio_.receive(message);++i)lab_.deliver(message);
                    for(unsigned i=0;i<4&&lab_.outgoing(message);++i)
                        if(!radio_.send(message.mac,message.packet))lab_.sendFailure();
                }
                xSemaphoreGive(radioMutex_);
            }
            vTaskDelay(pdMS_TO_TICKS(3));
        }
    }
    void task(){
        routes();WiFi.persistent(false);AppOptions applied;bool first=true,joining=false,station=false,servingNow=false,radioReady=false;
        wifi_interface_t radioInterface=WIFI_IF_STA;uint32_t joiningAt_ms=0,signalAt_ms=0,radioRetry_ms=0;
        for(;;){AppOptions desired;xSemaphoreTake(mutex_,portMAX_DELAY);desired=sharedOptions_;xSemaphoreGive(mutex_);
            bool changed=first||desired.wifi!=applied.wifi||(!desired.wifi&&desired.espNow!=applied.espNow)||desired.mode!=applied.mode||strcmp(desired.ssid,applied.ssid)||strcmp(desired.password,applied.password)||strcmp(desired.hostname,applied.hostname);
            if(changed){first=false;applied=desired;pauseRadio();radioReady=false;radioRetry_ms=0;server_.stop();MDNS.end();WiFi.disconnect(true,false);WiFi.mode(WIFI_OFF);
                joining=station=servingNow=false;
                if(!applied.wifi){if(applied.espNow){WiFi.mode(WIFI_STA);WiFi.setSleep(false);radio_.setChannel(6);}report(applied.espNow?"WiFi network off; ESP-NOW radio active":"WiFi off");}
                else if(applied.mode==WifiMode::AccessPoint)servingNow=accessPoint(applied,false);
                else{WiFi.mode(WIFI_STA);WiFi.setSleep(false);WiFi.setHostname(applied.hostname);WiFi.begin(applied.ssid,applied.password);
                    joining=true;joiningAt_ms=millis();report("Joining WiFi...");}
            }
            applied.espNow=desired.espNow;
            if(joining){if(WiFi.status()==WL_CONNECTED){joining=false;station=servingNow=true;serving(applied,false);}
                else if(uint32_t(millis()-joiningAt_ms)>=15000){joining=false;
                    pauseRadio();radioReady=false;radioRetry_ms=0;
                    WiFi.disconnect(false,false);servingNow=accessPoint(applied,true);}}
            if(station&&WiFi.status()!=WL_CONNECTED){pauseRadio();radioReady=false;radioRetry_ms=0;station=false;servingNow=false;server_.stop();MDNS.end();
                joining=true;joiningAt_ms=millis();WiFi.begin(applied.ssid,applied.password);report("WiFi lost; reconnecting...");}
            if(changed||uint32_t(millis()-signalAt_ms)>=1000){signalAt_ms=millis();WifiSignal signal;
                signal.state=!applied.wifi?WifiState::Off:station?WifiState::Connected:servingNow?WifiState::AccessPoint:WifiState::Connecting;
                if(station){wifi_ap_record_t info;if(esp_wifi_sta_get_ap_info(&info)==ESP_OK)signal.rssi_dBm=info.rssi;else signal.state=WifiState::Connecting;}
                xSemaphoreTake(mutex_,portMAX_DELAY);signal_=signal;xSemaphoreGive(mutex_);}
            // ESP-NOW shares the radio channel with WiFi. Never hop this server
            // away from its network; recovering instruments scan for us.
            wifi_interface_t requiredInterface=(!station&&!joining&&servingNow)?WIFI_IF_AP:WIFI_IF_STA;
            if(radioReady&&(!applied.espNow||radioInterface!=requiredInterface)){
                pauseRadio();radioReady=false;radioRetry_ms=0;
            }
            if(applied.espNow&&!radioReady&&(!radioRetry_ms||uint32_t(millis()-radioRetry_ms)>=1000)){
                radioRetry_ms=millis();radioInterface=requiredInterface;radioReady=startRadio(radioInterface);
                if(!radioReady)report(nullptr,"ESP-NOW could not start. Retrying.");
            }
            if(servingNow)server_.handleClient();vTaskDelay(pdMS_TO_TICKS(3));
        }
    }
public:
    WebService(Ui &ui,Controller &controller,AppOptions &options,LabQueue &lab):ui_(ui),controller_(controller),options_(options),lab_(lab){}
    bool begin(){
        mutex_=xSemaphoreCreateMutex();radioMutex_=xSemaphoreCreateMutex();commands_=xQueueCreate(4,sizeof(RemoteCommand));results_=xQueueCreate(4,sizeof(RemoteResult));
        void *shared=heap_caps_malloc(sizeof(WebSnapshot),MALLOC_CAP_SPIRAM|MALLOC_CAP_8BIT);
        void *sending=heap_caps_malloc(sizeof(WebSnapshot),MALLOC_CAP_SPIRAM|MALLOC_CAP_8BIT);
        json_=static_cast<char *>(heap_caps_malloc(JsonCapacity,MALLOC_CAP_SPIRAM|MALLOC_CAP_8BIT));
        if(!mutex_||!radioMutex_||!commands_||!results_||!shared||!sending||!json_)return false;
        shared_=new(shared)WebSnapshot;sending_=new(sending)WebSnapshot;sharedOptions_=options_;
        shared_->capture(ui_,controller_,options_,signal_,networkText_,millis());
        if(xTaskCreatePinnedToCore([](void *p){static_cast<WebService *>(p)->radioTask();},"charger-radio",4096,this,1,nullptr,0)!=pdPASS)return false;
        ready_=xTaskCreatePinnedToCore([](void *p){static_cast<WebService *>(p)->task();},"charger-web",8192,this,1,nullptr,0)==pdPASS;
        return ready_;
    }
    void poll(){
        if(!ready_)return;
        RemoteCommand command;if(xQueueReceive(commands_,&command,0)==pdTRUE){
            RemoteResult result=ui_.executeRemote(command,millis());publish(true);xQueueSend(results_,&result,0);}
        char text[160],warning[220];WifiSignal signal;
        if(xSemaphoreTake(mutex_,0)==pdTRUE){sharedOptions_=options_;snprintf(text,sizeof(text),"%s",networkText_);
            snprintf(warning,sizeof(warning),"%s",warning_);warning_[0]=0;signal=signal_;xSemaphoreGive(mutex_);
            ui_.networkStatus(text);ui_.wifiSignal(signal);if(warning[0])ui_.notify(warning);}
    }
    void publish(bool force=false){
        if(!ready_||(!force&&(!options_.wifi||uint32_t(millis()-publishedAt_ms_)<200)))return;
        if(xSemaphoreTake(mutex_,force?portMAX_DELAY:0)!=pdTRUE)return;
        sharedOptions_=options_;shared_->capture(ui_,controller_,options_,signal_,networkText_,millis());publishedAt_ms_=millis();xSemaphoreGive(mutex_);
    }
};
} // namespace batcharger
