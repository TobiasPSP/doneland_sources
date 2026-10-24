#include "app_ui.h"
#include "arduino_word_macro.h"
#include "web_model.h"
#undef word
#include "lab_charger_adapter.h"
#include <vector>
#include <assert.h>
#include <stdio.h>
using namespace batcharger;
static uint32_t now_ms=1000;
static Ui *frameUi=nullptr;static Controller *frameController=nullptr;
static uint16_t pixels[320*480];
static uint8_t draw[320*30*2];
static lv_obj_t *checkbox(lv_obj_t *parent,const char *text);
static lv_point_t touchPoint;static bool touchPressed=false;static lv_indev_t *touchDevice=nullptr;
static void touchCheckbox(const char *text){
    auto *o=checkbox(lv_screen_active(),text);assert(o);lv_refr_now(nullptr);lv_area_t a;lv_obj_get_coords(o,&a);
    assert(a.x2-a.x1+1==276&&a.y2-a.y1+1==44);
    touchPoint.x=a.x2-8;touchPoint.y=(a.y1+a.y2)/2;
    touchPressed=true;lv_indev_read(touchDevice);now_ms+=40;touchPressed=false;lv_indev_read(touchDevice);now_ms+=40;
}
static uint32_t tick(){return now_ms;}
struct Fake:ip2366::Transport {
    uint8_t r[256]={};bool online=true,readFailure=false;
    Fake(){r[0x33]=0x80;r[0x31]=0x22;r[0x34]=0x90;r[0x77]=0x80;word(0x50,12000);word(0x6e,1000);word(0x78,800);}
    void word(uint8_t reg,uint16_t value){r[reg]=value&255;r[reg+1]=value>>8;}
    bool probe()override{return online;}bool recover()override{return online;}
    bool read(uint8_t reg,uint8_t &v)override{v=r[reg];return online&&!readFailure;}
    bool write(uint8_t reg,uint8_t v)override{r[reg]=v;return online;}
};
static void flush(lv_display_t *d,const lv_area_t *a,uint8_t *src){
    int width=a->x2-a->x1+1;for(int y=a->y1;y<=a->y2;++y)memcpy(pixels+y*320+a->x1,src+(y-a->y1)*width*2,width*2);lv_display_flush_ready(d);
}
static lv_obj_t *find(lv_obj_t *parent,const char *text){
    if(lv_obj_check_type(parent,&lv_label_class)&&!strcmp(lv_label_get_text(parent),text))return parent;
    for(unsigned i=0;i<lv_obj_get_child_count(parent);++i)if(auto *o=find(lv_obj_get_child(parent,i),text))return o;return nullptr;
}
static lv_obj_t *findType(lv_obj_t *parent,const lv_obj_class_t *type){
    if(lv_obj_check_type(parent,type))return parent;
    for(unsigned i=0;i<lv_obj_get_child_count(parent);++i)if(auto *o=findType(lv_obj_get_child(parent,i),type))return o;
    return nullptr;
}
static lv_obj_t *checkbox(lv_obj_t *parent,const char *text){
    if(lv_obj_check_type(parent,&lv_checkbox_class)&&!strcmp(lv_checkbox_get_text(parent),text))return parent;
    for(unsigned i=0;i<lv_obj_get_child_count(parent);++i)if(auto *o=checkbox(lv_obj_get_child(parent,i),text))return o;return nullptr;
}
static void check(const char *text,bool on){auto *o=checkbox(lv_screen_active(),text);assert(o);
    if(on)lv_obj_add_state(o,LV_STATE_CHECKED);else lv_obj_remove_state(o,LV_STATE_CHECKED);lv_obj_send_event(o,LV_EVENT_VALUE_CHANGED,nullptr);}
static void tap(const char *text){auto *o=find(lv_screen_active(),text);assert(o);auto *b=lv_obj_get_parent(o);assert(lv_obj_check_type(b,&lv_button_class));assert(!lv_obj_has_state(b,LV_STATE_DISABLED));lv_obj_send_event(b,LV_EVENT_CLICKED,nullptr);}
static void textareas(lv_obj_t *parent,std::vector<lv_obj_t *> &out){
    if(lv_obj_check_type(parent,&lv_textarea_class)){out.push_back(parent);return;}
    for(unsigned i=0;i<lv_obj_get_child_count(parent);++i)textareas(lv_obj_get_child(parent,i),out);
}
static void save(const char *directory,const char *name){
    now_ms+=100;lv_timer_handler();lv_refr_now(nullptr);
    const uint16_t background=uint16_t((0x14>>3)<<11|(0x17>>2)<<5|(0x19>>3));
    for(size_t corner:{size_t(0),size_t(319),size_t(320*479),size_t(320*480-1)})assert(pixels[corner]==background);
    char path[2048];snprintf(path,sizeof(path),"%s/%s.ppm",directory,name);FILE *f=fopen(path,"wb");assert(f);fprintf(f,"P6\n320 480\n255\n");
    for(auto p:pixels){uint8_t rgb[]={uint8_t(((p>>11)&31)*255/31),uint8_t(((p>>5)&63)*255/63),uint8_t((p&31)*255/31)};fwrite(rgb,1,3,f);}fclose(f);
    if(frameUi&&frameController){WebSnapshot snapshot;snapshot.capture(*frameUi,*frameController,frameUi->options(),frameUi->wifiSignal(),"WiFi snapshot",now_ms);
        char json[16384];auto write=[&](const char *suffix,size_t bytes){assert(bytes);snprintf(path,sizeof(path),"%s/%s.%s.json",directory,name,suffix);FILE *out=fopen(path,"wb");assert(out);fwrite(json,1,bytes,out);fclose(out);};
        write("state",snapshot.stateJson(json,sizeof(json)));write("history",snapshot.historyJson(json,sizeof(json),0,0));write("diagnostics",snapshot.diagnosticsJson(json,sizeof(json)));
        if(snapshot.history.count)write("delta",snapshot.historyJson(json,sizeof(json),snapshot.session,snapshot.history.revision));
        assert(arduinoWordMacroCalls==0);
        snprintf(path,sizeof(path),"%s/model.json",directory);f=fopen(path,"wb");assert(f);size_t bytes=WebSnapshot::modelJson(json,sizeof(json));assert(bytes);fwrite(json,1,bytes,f);fclose(f);}

}
int main(int argc,char **argv){
    const char *dir=argc>1?argv[1]:".";lv_init();lv_tick_set_cb(tick);
    auto *display=lv_display_create(320,480);lv_display_set_color_format(display,LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(display,draw,nullptr,sizeof(draw),LV_DISPLAY_RENDER_MODE_PARTIAL);lv_display_set_flush_cb(display,flush);
    touchDevice=lv_indev_create();lv_indev_set_type(touchDevice,LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(touchDevice,[](lv_indev_t *,lv_indev_data_t *data){data->point=touchPoint;data->state=touchPressed?LV_INDEV_STATE_PRESSED:LV_INDEV_STATE_RELEASED;});
    Fake io;Controller c(io);assert(c.initialize(0));AppOptions options;Ui ui(c,&options);frameUi=&ui;frameController=&c;ui.begin();save(dir,"configure-empty");
    const uint8_t stages[]={0,4,5,6,7};const char *stageNames[]={"Standby","Waiting","Full","Charging timeout","Reserved state (7)"};
    for(unsigned n=0;n<5;++n){io.r[0x31]=stages[n];now_ms+=500;c.tick(now_ms);ui.refresh();assert(c.state==State::Configure&&find(lv_screen_active(),stageNames[n]));
        if(n==0)save(dir,"configure-standby");if(n==1)save(dir,"configure-waiting");if(n==3)save(dir,"configure-timeout");}
    io.r[0x31]=0x22;now_ms+=500;c.tick(now_ms);ui.refresh();
    assert(!find(lv_screen_active(),"BatCharger 1.2.0")); // version belongs to diagnostics only
    ui.wifiSignal({WifiState::Connected,-52});assert(find(lv_screen_active(),"-52 dBm"));save(dir,"wifi-header-strong");
    ui.wifiSignal({WifiState::Connected,-84});assert(find(lv_screen_active(),"-84 dBm"));save(dir,"wifi-header-weak");
    ui.wifiSignal({WifiState::AccessPoint,0});assert(find(lv_screen_active(),"AP"));save(dir,"wifi-header-ap");
    ui.wifiSignal({WifiState::Connecting,0});assert(find(lv_screen_active(),"--"));save(dir,"wifi-header-connecting");
    ui.wifiSignal({WifiState::Off,0});
    tap(LV_SYMBOL_SETTINGS);assert(find(lv_screen_active(),"Settings")&&find(lv_screen_active(),"Diagnostics"));save(dir,"settings");tap("Diagnostics");char idleDiagnostic[1200];ui.diagnosticReport(idleDiagnostic,sizeof(idleDiagnostic));assert(find(lv_screen_active(),idleDiagnostic));save(dir,"diagnostics-idle");tap("Back");
    tap(LV_SYMBOL_SETTINGS);touchCheckbox("Persist charger config");assert(options.persist);
    touchCheckbox("Persist charger config");assert(!options.persist);
    touchCheckbox("Persist charger config");touchCheckbox("ESPNow");assert(options.espNow);touchCheckbox("WiFi");
    assert(!options.wifi&&find(lv_screen_active(),"WIFI"));
    std::vector<lv_obj_t *> wifiFields;textareas(lv_screen_active(),wifiFields);
    // Native configure fields remain behind the modal; WiFi adds three more.
    assert(wifiFields.size()==7);assert(!strcmp(lv_textarea_get_text(wifiFields[4]),""));
    assert(!strcmp(lv_textarea_get_text(wifiFields[5]),"")&&!strcmp(lv_textarea_get_text(wifiFields[6]),"charger1"));
    save(dir,"wifi-setup");lv_obj_send_event(wifiFields[4],LV_EVENT_FOCUSED,nullptr);save(dir,"wifi-keyboard");
    lv_obj_send_event(wifiFields[5],LV_EVENT_FOCUSED,nullptr);
    char tooLong[65];memset(tooLong,'x',64);tooLong[64]=0;
    assert(!ui.remoteText(tooLong)&&!strcmp(lv_textarea_get_text(wifiFields[5]),""));save(dir,"wifi-password");
    auto *wifiKeyboard=findType(lv_obj_get_parent(lv_obj_get_parent(wifiFields[4])),&lv_keyboard_class);assert(wifiKeyboard);
    lv_obj_send_event(wifiKeyboard,LV_EVENT_READY,nullptr);check("Access Point",true);tap("Apply");assert(options.wifi&&options.mode==WifiMode::AccessPoint&&options.persist&&options.espNow);
    save(dir,"settings-enabled");check("WiFi",false);check("Persist charger config",false);check("ESPNow",false);tap("Back");
    auto *start=lv_obj_get_parent(find(lv_screen_active(),"Start Charging"));assert(lv_obj_has_state(start,LV_STATE_DISABLED));
    tap("Li-ion");tap("3S");c.sample(1000);ui.refresh();save(dir,"configure-ready");
    std::vector<lv_obj_t *> fields;textareas(lv_screen_active(),fields);assert(fields.size()==4);
    lv_textarea_set_text(fields[1],"1050");assert(lv_obj_has_state(start,LV_STATE_DISABLED));
    lv_textarea_set_text(fields[1],"1000");assert(!lv_obj_has_state(start,LV_STATE_DISABLED));
    lv_textarea_set_text(fields[0],"3650");assert(ui.config.chemistry==Chemistry::Lfp&&ui.config.cell_mV==3650);
    tap("Li-ion");assert(ui.config.cell_mV==4200);
    lv_obj_send_event(fields[1],LV_EVENT_FOCUSED,nullptr);save(dir,"keyboard");
    lv_area_t edited,closeArea;lv_obj_get_coords(fields[1],&edited);lv_obj_get_coords(lv_obj_get_parent(find(lv_screen_active(),"CANCEL " LV_SYMBOL_CLOSE)),&closeArea);
    assert(edited.y2<closeArea.y1); // Close control never covers the value being edited.
    // Hide via keyboard READY, then reopen the same input via click.
    lv_obj_t *kb=nullptr;
    for(unsigned i=0;i<lv_obj_get_child_count(lv_screen_active());++i){auto *o=lv_obj_get_child(lv_screen_active(),i);if(lv_obj_check_type(o,&lv_keyboard_class))kb=o;}
    assert(kb);lv_obj_send_event(kb,LV_EVENT_READY,nullptr);assert(lv_obj_has_flag(kb,LV_OBJ_FLAG_HIDDEN));
    lv_obj_send_event(fields[1],LV_EVENT_CLICKED,nullptr);assert(!lv_obj_has_flag(kb,LV_OBJ_FLAG_HIDDEN));lv_obj_send_event(kb,LV_EVENT_READY,nullptr);
    // Cancel restores the current input and closes the keyboard without requiring a value.
    lv_obj_send_event(fields[1],LV_EVENT_CLICKED,nullptr);lv_textarea_set_text(fields[1],"2000");
    tap("CLEAR");assert(!strcmp(lv_textarea_get_text(fields[1]),""));assert(!lv_obj_has_flag(kb,LV_OBJ_FLAG_HIDDEN));
    save(dir,"keyboard-clear");
    tap("CANCEL " LV_SYMBOL_CLOSE);assert(!strcmp(lv_textarea_get_text(fields[1]),"1000"));
    assert(lv_obj_has_flag(kb,LV_OBJ_FLAG_HIDDEN));
    assert(ui.config.terminationTime_min==360 && find(lv_screen_active(),"12.600 V"));
    auto *packLabel=find(lv_screen_active(),"12.600 V");
    assert(lv_obj_get_style_text_font(packLabel,LV_PART_MAIN)==&lv_font_montserrat_18);
    lv_textarea_set_text(fields[3],"0");assert(lv_obj_has_state(start,LV_STATE_DISABLED));
    lv_textarea_set_text(fields[3],"360");
    tap("Start Charging");ui.commands(now_ms);assert(c.state==State::Configure && !(io.r[0]&1));
    assert(find(lv_screen_active(),"Charging Voltage")&&find(lv_screen_active(),"Termination Time")&&find(lv_screen_active(),"6 h 00 min"));
    assert(lv_color_to_u32(lv_obj_get_style_bg_color(lv_obj_get_parent(find(lv_screen_active(),"CANCEL")),LV_PART_MAIN))==lv_color_to_u32(lv_color_hex(0xff7c81)));
    save(dir,"confirm-charge");tap("CANCEL");ui.commands(now_ms);assert(c.state==State::Configure && !(io.r[0]&1));
    io.word(0x50,0);tap("Start Charging");tap("OK");ui.commands(now_ms);assert(find(lv_screen_active(),LV_SYMBOL_WARNING " No battery detected. Proceed anyway?"));save(dir,"no-battery");
    tap("Cancel");io.word(0x50,12000);tap("Start Charging");tap("OK");ui.commands(now_ms);assert(c.state==State::Starting&&c.sessionOrigin==SessionOrigin::Tablet);
    auto *end=find(lv_screen_active(),"End 12.600 V");auto *elapsed=find(lv_screen_active(),"00:00:00");
    auto *term=find(lv_screen_active(),"Term 100 mA");
    assert(end&&elapsed&&term&&lv_obj_get_parent(end)!=lv_obj_get_parent(term));
    assert(lv_obj_get_parent(elapsed)==lv_screen_active());
    save(dir,"graph-start-target");
    assert(find(lv_screen_active(),"0 mWh"));
    lv_area_t headingArea,timeArea,diagArea;
    lv_obj_get_coords(find(lv_screen_active(),"CHARGING"),&headingArea);
    lv_obj_get_coords(elapsed,&timeArea);lv_obj_get_coords(lv_obj_get_parent(find(lv_screen_active(),LV_SYMBOL_SETTINGS)),&diagArea);
    // The heading label's box spans the row; compare actual glyph width.
    lv_point_t headingSize;lv_text_get_size(&headingSize,"CHARGING",&lv_font_montserrat_24,0,0,292,LV_TEXT_FLAG_NONE);
    assert(timeArea.x1>headingArea.x1+headingSize.x&&timeArea.x2<diagArea.x1&&timeArea.y1<40);
    assert(lv_obj_get_style_text_font(end,0)==&lv_font_montserrat_10);
    io.r[0x33]=0;now_ms+=500;c.tick(now_ms);ui.refresh();
    assert(c.state==State::Starting&&find(lv_screen_active(),LV_SYMBOL_WARNING " Waiting for charging input")&&!find(lv_screen_active(),"SUMMARY"));save(dir,"starting-input-wait");
    io.r[0x33]=0x80;now_ms+=500;c.tick(now_ms);ui.refresh();assert(c.state==State::Starting);
    now_ms+=500;c.tick(now_ms);ui.refresh();assert(c.state==State::Charging);
    uint32_t began=now_ms;
    for(unsigned i=1;i<=120;++i){if(i==40||i==100)io.r[0x31]=0x23;if(i==80)io.r[0x31]=0x22;io.word(0x50,12000+i*4);io.word(0x6e,1000-i*3);now_ms=began+i*1000;c.tick(now_ms);ui.refresh();}
    save(dir,"charging");
    auto *plot=findType(lv_screen_active(),&lv_chart_class);assert(plot);
    unsigned checked=0;
    for(auto *series=lv_chart_get_series_next(plot,nullptr);series;series=lv_chart_get_series_next(plot,series)){
        unsigned last=lv_chart_get_point_count(plot)-1;int32_t value=lv_chart_get_y_array(plot,series)[last];
        assert(value==12480||value==640);lv_point_t point;lv_chart_get_point_pos_by_id(plot,series,last,&point);
        double minimum=value==12480?9000.0:0.0,maximum=value==12480?13600.0:1300.0;
        double expected=lv_obj_get_style_pad_top(plot,0)+lv_obj_get_content_height(plot)*(1.0-(value-minimum)/(maximum-minimum));
        assert(fabs(point.y-expected)<=1.01);++checked;
    }
    assert(checked==2); // 9..13.6 V and 0..1.3 A remain fixed after 120 samples.
    auto *temperature=find(lv_screen_active(),"NTC 25.0 C");assert(temperature);
    lv_obj_send_event(lv_obj_get_parent(temperature),LV_EVENT_CLICKED,nullptr);
    tap("Diagnostics");char diagnostic[1200];ui.diagnosticReport(diagnostic,sizeof(diagnostic));assert(find(lv_screen_active(),diagnostic));save(dir,"diagnostics");tap("Back");
    io.word(0x50,12600);now_ms+=1000;c.tick(now_ms);ui.refresh();
    assert(c.state==State::Charging&&find(lv_screen_active(),"~99% SOC"));save(dir,"charging-soc-capped");
    assert(lv_bar_get_value(findType(lv_screen_active(),&lv_bar_class))==990);
    assert(lv_color_to_u32(lv_obj_get_style_bg_color(findType(lv_screen_active(),&lv_bar_class),LV_PART_INDICATOR))==lv_color_to_u32(lv_color_hex(0x00ff35)));
    io.r[0x31]=0x35;now_ms+=500;c.tick(now_ms);ui.refresh();assert(c.state==State::Complete);assert(find(lv_screen_active(),"Done"));
    assert(find(lv_screen_active(),"~100% SOC"));save(dir,"complete");
    assert(lv_bar_get_value(findType(lv_screen_active(),&lv_bar_class))==1000);
    tap("Done");ui.commands(now_ms);assert(find(lv_screen_active(),"SUMMARY"));save(dir,"summary");
    tap("OK");ui.commands(now_ms);assert(c.state==State::Configure);assert(ui.config.cells==3&&ui.config.chemistry==Chemistry::LiIon);
    io.r[0x31]=0x22;tap("Start Charging");tap("OK");ui.commands(now_ms);assert(c.state==State::Starting);
    io.r[0x38]=0x10;now_ms+=500;c.tick(now_ms);ui.refresh();assert(find(lv_screen_active(),LV_SYMBOL_WARNING " IP2366 short-circuit fault"));save(dir,"fault");
    tap(LV_SYMBOL_SETTINGS);tap("Diagnostics");char faultDiagnostic[1200];ui.diagnosticReport(faultDiagnostic,sizeof(faultDiagnostic));
    assert(find(lv_screen_active(),faultDiagnostic));save(dir,"diagnostics-fault");
    io.online=false;Ui missing(c);frameUi=&missing;frameController=&c;c.initialize(now_ms);missing.begin();assert(!find(lv_screen_active(),"Test again"));save(dir,"missing");
    io.online=true;now_ms+=1000;c.tick(now_ms);missing.refresh();assert(c.state==State::Configure&&find(lv_screen_active(),"CONFIGURE"));
    io.online=false;now_ms+=500;c.tick(now_ms);missing.refresh();
    assert(find(lv_screen_active(),"SUMMARY")&&find(lv_screen_active(),LV_SYMBOL_WARNING " IP2366 was disconnected."));save(dir,"disconnected");
    assert(find(lv_screen_active(),LV_SYMBOL_WARNING " Charger disable NOT confirmed"));
    assert(lv_obj_has_state(lv_obj_get_parent(find(lv_screen_active(),"OK")),LV_STATE_DISABLED));
    io.online=true;c.tick(now_ms+2000);missing.refresh();tap("OK");missing.commands(now_ms+2000);
    io.readFailure=true;c.tick(now_ms+2500);missing.refresh();
    assert(find(lv_screen_active(),LV_SYMBOL_WARNING " IP2366 communication instable"));save(dir,"unstable");
    // SOC-limited target uses the effective configured pack voltage, not the
    // chemistry's full-charge voltage. Exercise a full 240-point history too.
    Fake limitedIo;Controller limited(limitedIo);assert(limited.initialize(now_ms));Ui limitedUi(limited);frameUi=&limitedUi;frameController=&limited;limitedUi.begin();
    tap("Li-ion");tap("3S");auto *dropdown=findType(lv_screen_active(),&lv_dropdown_class);assert(dropdown);
    lv_dropdown_set_selected(dropdown,8);lv_obj_send_event(dropdown,LV_EVENT_VALUE_CHANGED,nullptr);
    tap("Start Charging");tap("OK");limitedUi.commands(now_ms);assert(limited.state==State::Starting);
    assert(find(lv_screen_active(),"End 12.360 V"));save(dir,"graph-soc-target");
    for(unsigned i=0;i<320;++i){now_ms+=1000;limitedIo.word(0x50,11000+i*3);limited.tick(now_ms);limitedUi.refresh();}
    assert(limited.history.count==320);assert(lv_chart_get_point_count(findType(lv_screen_active(),&lv_chart_class))<=240);save(dir,"graph-full-history");
    // A non-default 750 mA reference and low measured current use the same
    // fixed scale; the references do not move with the measurement extrema.
    limited.abort(now_ms);assert(limited.configure());limitedUi.refresh();
    fields.clear();textareas(lv_screen_active(),fields);assert(fields.size()==4);
    lv_textarea_set_text(fields[2],"750");tap("Start Charging");tap("OK");limitedUi.commands(now_ms);
    assert(limited.state==State::Starting&&find(lv_screen_active(),"Term 750 mA"));
    limitedIo.word(0x6e,200);now_ms+=1000;limited.tick(now_ms);limitedUi.refresh();save(dir,"graph-high-termination");
    struct UiProfiles:ProfileStore {
        Config saved;bool load(Config &out)override{out=saved;return true;}
        bool save(const Config &in)override{saved=in;return true;}
    } profiles;
    profiles.saved=limited.activeConfig();Controller recovered(limitedIo,&profiles);assert(recovered.initialize(now_ms));
    Ui recoveredUi(recovered);frameUi=&recoveredUi;frameController=&recovered;recoveredUi.begin();
    assert(recovered.bootProfileMatched&&recoveredUi.config.percent==80&&recoveredUi.config.termination_mA==750);
    assert(recoveredUi.config.cell_mV==4200&&!(limitedIo.r[0]&1));
    assert(find(lv_screen_active(),"CONFIGURE")&&!find(lv_screen_active(),"CHARGING"));
    assert(!lv_obj_has_state(lv_obj_get_parent(find(lv_screen_active(),"Start Charging")),LV_STATE_DISABLED));
    save(dir,"configure-recovered");tap("Start Charging");tap("OK");recoveredUi.commands(now_ms);
    assert(recovered.state==State::Starting&&(limitedIo.r[0]&1));
    limitedIo.r[0x03]=20;Controller mismatched(limitedIo,&profiles);assert(mismatched.initialize(now_ms));
    Ui mismatchedUi(mismatched);frameUi=&mismatchedUi;frameController=&mismatched;mismatchedUi.begin();assert(!mismatched.bootProfileMatched);
    tap("OK");assert(mismatchedUi.config.chemistry==Chemistry::None&&mismatchedUi.config.current_mA==2000);
    assert(lv_obj_has_state(lv_obj_get_parent(find(lv_screen_active(),"Start Charging")),LV_STATE_DISABLED));save(dir,"configure-register-recovery");
    // Explicit full persistence overrides inactive/mismatched live defaults,
    // restores every selection, and still never enables charging at boot.
    options.persist=true;options.wifi=true;options.espNow=true;
    Ui persistedUi(mismatched,&options);frameUi=&persistedUi;frameController=&mismatched;
    persistedUi.begin(&profiles.saved);assert(persistedUi.config.percent==80&&persistedUi.config.chemistry==Chemistry::LiIon);
    assert(!(limitedIo.r[0]&1)&&find(lv_screen_active(),"CONFIGURE"));
    assert(!lv_obj_has_state(lv_obj_get_parent(find(lv_screen_active(),"Start Charging")),LV_STATE_DISABLED));save(dir,"configure-persisted");
    persistedUi.notify("WiFi unavailable. Access Point charger1 is active. Open http://192.168.4.1/");save(dir,"wifi-fallback");
    // Explicit web commands use the same controller, without simulated taps.
    // Automatic software timeout reaches Summary without pretending the IP2366
    // reported a full battery. The same verified disable path is used.
    Fake timedIo;Controller timedCtl(timedIo);assert(timedCtl.initialize(now_ms));Config timeConfig;timeConfig.chemistry=Chemistry::LiIon;timeConfig.cells=3;timeConfig.terminationTime_min=1;
    Ui timedUi(timedCtl);frameUi=&timedUi;frameController=&timedCtl;timedUi.begin(&timeConfig);
    tap("Start Charging");save(dir,"confirm-one-minute");tap("OK");timedUi.commands(now_ms);
    now_ms+=500;timedCtl.tick(now_ms);timedUi.refresh();now_ms+=59501;timedCtl.tick(now_ms);timedUi.refresh();
    assert(timedCtl.state==State::Aborted&&timedCtl.disableConfirmed&&!(timedIo.r[0]&1));
    assert(find(lv_screen_active(),"SUMMARY")&&find(lv_screen_active(),LV_SYMBOL_WARNING " Termination time reached"));save(dir,"timed-stop");
    Fake remoteIo;Controller remoteCtl(remoteIo);assert(remoteCtl.initialize(now_ms));AppOptions remoteOptions;Ui remoteUi(remoteCtl,&remoteOptions);remoteUi.begin();frameUi=&remoteUi;frameController=&remoteCtl;
    RemoteCommand command;command.id=1;command.action=RemoteAction::Start;command.revision=remoteUi.viewRevision();
    command.config.chemistry=Chemistry::LiIon;command.config.cells=3;
    remoteIo.word(0x50,0);auto result=remoteUi.executeRemote(command,now_ms);assert(result.code==2&&remoteCtl.state==State::Configure&&!(remoteIo.r[0]&1));
    command.proceed=true;command.revision=result.revision;command.config.current_mA=2000;
    result=remoteUi.executeRemote(command,now_ms);assert(result.code==1&&!(remoteIo.r[0]&1)); // confirmation binds all settings
    command.config.current_mA=1000;command.config.terminationTime_min=720;result=remoteUi.executeRemote(command,now_ms);assert(result.code==1&&!(remoteIo.r[0]&1));
    command.config.terminationTime_min=360;result=remoteUi.executeRemote(command,now_ms);assert(result.code==0&&remoteCtl.state==State::Starting&&remoteCtl.sessionOrigin==SessionOrigin::Web&&!remoteCtl.stopVerificationFailed());
    result=remoteUi.executeRemote(command,now_ms);assert(result.code==1); // cannot start twice
    command.action=RemoteAction::Abort;command.revision=0;result=remoteUi.executeRemote(command,now_ms);assert(result.code==0&&remoteCtl.state==State::Aborted&&!(remoteIo.r[0]&1));
    command.action=RemoteAction::Configure;command.revision=remoteUi.viewRevision();assert(remoteUi.executeRemote(command,now_ms).code==0);
    command.action=RemoteAction::Settings;command.revision=0;command.options.wifi=true;assert(remoteUi.executeRemote(command,now_ms).code==1&&!remoteOptions.wifi);
    command.revision=remoteUi.viewRevision();command.options.persist=true;command.options.espNow=true;
    snprintf(command.options.ssid,sizeof(command.options.ssid),"quoted\"ssid\\test");snprintf(command.options.password,sizeof(command.options.password),"secret-not-for-json");
    assert(remoteUi.executeRemote(command,now_ms).code==0&&remoteOptions.wifi&&remoteOptions.persist&&remoteOptions.espNow);save(dir,"web-command-settings");
    remoteIo.word(0x50,0);command.action=RemoteAction::Start;command.proceed=false;command.revision=remoteUi.viewRevision();result=remoteUi.executeRemote(command,now_ms);assert(result.code==2);
    uint32_t expired=result.revision;command.action=RemoteAction::Cancel;command.revision=expired;assert(remoteUi.executeRemote(command,now_ms).code==0);
    command.action=RemoteAction::Start;command.proceed=true;command.revision=expired;assert(remoteUi.executeRemote(command,now_ms).code==1&&!(remoteIo.r[0]&1));
    // Exercise the real lab adapter with fake register I/O and real LVGL.
    Fake labIo;Controller labCtl(labIo);assert(labCtl.initialize(now_ms));Ui labUi(labCtl);labUi.begin();LabChargerAdapter adapter(labCtl,labUi);
    frameUi=&labUi;frameController=&labCtl;labUi.labStatus("ESP-NOW ready / channel 6\nSubscribers 2/8 / owner test instrument");
    tap(LV_SYMBOL_SETTINGS);save(dir,"espnow-settings");tap("Back");
    lablink::ChargerConfig profile;profile.chemistry=1;profile.cells=3;profile.cell_mV=4200;
    labIo.word(0x50,0);assert(adapter.start(profile,false,now_ms).code==lablink::ResultCode::ConfirmationRequired);assert(!(labIo.r[0]&1));
    labIo.word(0x50,12000);assert(adapter.start(profile,false,now_ms).code==lablink::ResultCode::Applied);assert(labCtl.state==State::Starting&&(labIo.r[0]&1)&&labCtl.sessionOrigin==SessionOrigin::RemoteHost);
    assert(adapter.start(profile,false,now_ms).code==lablink::ResultCode::Rejected);
    labCtl.sample(now_ms);labCtl.totals.charge_mAh=1.234;labCtl.totals.energy_mWh=12.345;
    auto telemetry=adapter.telemetry(now_ms+75);assert(telemetry.voltage_mV==12000&&telemetry.current_mA==1000&&telemetry.temperature_cC==2500&&telemetry.sampleAge_ms==75);
    assert(telemetry.charge_uAh==1234&&telemetry.energy_uWh==12345&&telemetry.target_mV==12600&&telemetry.effectiveCurrent_mA==1000);
    lablink::CapabilityPage page;assert(adapter.capabilities(0,page)&&page.properties[0].enumMask==7);unsigned properties=0;
    for(unsigned n=0;n<page.pageCount;++n){assert(adapter.capabilities(n,page));properties+=page.count;lablink::Packet packet;assert(lablink::write(packet,page)&&packet.payloadLength<=lablink::MaxPayload);}
    assert(properties==22&&!adapter.capabilities(255,page));
    assert(adapter.abort(now_ms,true).code==lablink::ResultCode::Applied&&labCtl.state==State::Aborted&&!(labIo.r[0]&1));
    assert(find(lv_screen_active(),LV_SYMBOL_WARNING " ESP-NOW owner heartbeat lost"));save(dir,"espnow-owner-lost");
    profile.chemistry=255;assert(adapter.start(profile,false,now_ms).code==lablink::ResultCode::Rejected);
    assert(labCtl.configure());labUi.automationState();assert(adapter.start(labConfig(command.config),false,now_ms).code==lablink::ResultCode::Applied);
    labCtl.history.clear();
    for(unsigned n=0;n<=36000;++n)labCtl.history.add(uint16_t(11000+n/30),uint16_t(1000-n/40),n*1000);
    labCtl.history.observeMode(2,0);labCtl.history.observeMode(3,20000000);labCtl.history.observeMode(2,24000000);labCtl.history.observeMode(3,28000000);labCtl.history.observeMode(2,32000000);
    labCtl.measurement.voltage_mV=12200;labCtl.measurement.current_mA=100;
    labCtl.totals.elapsed_ms=36000000;labCtl.totals.charge_mAh=5500;labCtl.totals.energy_mWh=62900;labCtl.state=State::Charging;labUi.automationState();labUi.refresh();save(dir,"graph-ten-hours");
    assert(labCtl.history.count==36001);auto *socBar=findType(lv_screen_active(),&lv_bar_class);assert(socBar&&lv_bar_get_value(socBar)>=0&&lv_bar_get_value(socBar)<=1000);
    auto *longPlot=findType(lv_screen_active(),&lv_chart_class);assert(longPlot);PlotHistory projected;labCtl.history.reduce(projected,240);
    for(auto *series=lv_chart_get_series_next(longPlot,nullptr);series;series=lv_chart_get_series_next(longPlot,series)){
        for(unsigned n=0;n<projected.count;++n){lv_point_t position;lv_chart_get_point_pos_by_id(longPlot,series,n,&position);
            double expected=lv_obj_get_style_pad_left(longPlot,0)+double(projected.points[n].elapsed_ms)*lv_obj_get_content_width(longPlot)/projected.duration_ms;
            assert(fabs(position.x-expected)<=1.01);}}
    assert(find(lv_screen_active(),"NTC 25.0 C")&&!find(lv_screen_active(),"NTC ~25.0 C"));
    assert(labCtl.chargerStatusText()&&labCtl.graphStatusText());
    Fake targetIo;Controller targetCtl(targetIo);assert(targetCtl.initialize(now_ms));
    Config targetConfig;targetConfig.chemistry=Chemistry::Lfp;targetConfig.cells=4;targetConfig.cell_mV=3650;targetConfig.current_mA=2000;targetConfig.percent=70;
    targetIo.word(0x50,13000);Ui targetUi(targetCtl);frameUi=&targetUi;frameController=&targetCtl;targetUi.begin(&targetConfig);
    tap("Start Charging");tap("OK");targetUi.commands(now_ms);targetIo.word(0x50,13820);now_ms+=1000;targetCtl.tick(now_ms);targetUi.refresh();
    assert(find(lv_screen_active(),"~60% SOC")&&find(lv_screen_active(),"Target: 70%"));
    assert(lv_bar_get_value(findType(lv_screen_active(),&lv_bar_class))==857);
    save(dir,"graph-target-progress");
    targetIo.word(0x50,13860);now_ms+=1000;targetCtl.tick(now_ms);targetUi.refresh();
    assert(find(lv_screen_active(),"~69% SOC"));
    assert(lv_bar_get_value(findType(lv_screen_active(),&lv_bar_class))==986);
    save(dir,"graph-target-capped");assert(targetCtl.state==State::Charging);targetIo.r[0x31]=0x35;now_ms+=500;targetCtl.tick(now_ms);targetUi.refresh();
    assert(targetCtl.state==State::Complete&&targetCtl.chargeCompleteReported&&targetCtl.disableConfirmed&&!(targetIo.r[0]&1));
    assert(find(lv_screen_active(),"~70% SOC")&&lv_bar_get_value(findType(lv_screen_active(),&lv_bar_class))==1000);
    save(dir,"graph-target-complete");
    tap(LV_SYMBOL_SETTINGS);tap("Voltage Calibration (mV)");
    assert(find(lv_screen_active(),"CALIBRATION"));
    std::vector<lv_obj_t *> calFields;textareas(lv_screen_active(),calFields);assert(calFields.size()>=2);
    auto *calVoltage=calFields[calFields.size()-2],*calCurrent=calFields.back();
    lv_textarea_set_text(calVoltage,"-105");lv_textarea_set_text(calCurrent,"25");save(dir,"calibration-edit");
    lv_obj_send_event(calVoltage,LV_EVENT_FOCUSED,nullptr);save(dir,"calibration-keyboard");
    lv_obj_send_event(findType(lv_screen_active(),&lv_keyboard_class),LV_EVENT_READY,nullptr);tap("Apply");
    assert(targetUi.options().voltageCalibration_mV==-105&&targetUi.options().currentCalibration_mA==25);
    save(dir,"settings-calibrated");tap("Back");targetUi.commands(now_ms);targetUi.refresh();save(dir,"graph-calibrated");
    tap(LV_SYMBOL_SETTINGS);tap("ESPNow setup");
    assert(find(lv_screen_active(),"Friendly name"));
    std::vector<lv_obj_t *> nameFields;textareas(lv_screen_active(),nameFields);auto *nameField=nameFields.back();
    assert(!strcmp(lv_textarea_get_text(nameField),"Charger"));
    lv_textarea_set_text(nameField,"Charger Bench A");save(dir,"espnow-setup");
    lv_obj_send_event(nameField,LV_EVENT_FOCUSED,nullptr);assert(!targetUi.focusedPassword());
    assert(!targetUi.remoteText("12345678901234567890123456789012"));save(dir,"espnow-name-keyboard");
    lv_obj_send_event(findType(lv_screen_active(),&lv_keyboard_class),LV_EVENT_READY,nullptr);tap("Cancel");
    assert(!strcmp(targetUi.options().friendlyName,"Charger"));tap("ESPNow setup");
    nameFields.clear();textareas(lv_screen_active(),nameFields);lv_textarea_set_text(nameFields.back(),"Charger Bench A");tap("Apply");
    assert(!strcmp(targetUi.options().friendlyName,"Charger Bench A")&&!strcmp(targetUi.options().hostname,"charger1"));
    save(dir,"settings-friendly-name");tap("Back");
    puts("PASS: LabLink real charger adapter, complete profile/validation, telemetry units, descriptors and owner-loss UI");
    puts("PASS: native UI, square screen corners, typed web commands, confirmation binding, stale-command rejection and JSON snapshots");
}
