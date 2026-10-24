#pragma once
#include <lvgl.h>
#include <stdlib.h>
#include <string.h>
#include "charger.h"
#include "app_options.h"
#include "wifi_signal.h"
#include "remote_command.h"

namespace batcharger {
class Ui {
    static constexpr uint32_t Bg=0x141719,Tile=0x20272c,Ink=0xe1e8eb,Muted=0x84949c;
    static constexpr uint32_t Orange=0xffbd69,Cyan=0x60d4e3,Green=0x89e5ad,SocGreen=0x00ff35,Red=0xff7c81;
    Controller &ctl;
    uint32_t viewRevision_=1;
    AppOptions ownedOptions_;
    AppOptions &options_;
    AppOptions wifiDraft_;
    lv_obj_t *focusedInput=nullptr,*wifiKeyboard=nullptr,*wifiBody=nullptr,*wifiSsid=nullptr,*wifiPassword=nullptr,*wifiHostname=nullptr;
    lv_obj_t *apRadio=nullptr,*joinRadio=nullptr,*networkLabel=nullptr;
    char networkText[160]="WiFi off";
    char labText_[256]="ESP-NOW off";lv_obj_t *labLabel_=nullptr;
    WifiSignal wifiSignal_;
    lv_obj_t *headerWifi_=nullptr,*modalWifi_=nullptr;
    void wifiHeader(lv_obj_t *parent,lv_obj_t *&slot){
        slot=lv_obj_create(parent);lv_obj_set_pos(slot,214,42);lv_obj_set_size(slot,92,18);
        lv_obj_set_style_bg_opa(slot,LV_OPA_TRANSP,0);lv_obj_set_style_border_width(slot,0,0);lv_obj_set_style_pad_all(slot,0,0);
        lv_obj_remove_flag(slot,LV_OBJ_FLAG_SCROLLABLE);lv_obj_remove_flag(slot,LV_OBJ_FLAG_CLICKABLE);
        label(slot,"off",30,1,62,Muted,&lv_font_montserrat_10);
        label(slot,LV_SYMBOL_WIFI,0,0,16,Muted,&lv_font_montserrat_14);
        for(int i=0;i<4;++i){auto *bar=lv_obj_create(slot);lv_obj_set_pos(bar,16+i*3,14-(3+i*3));lv_obj_set_size(bar,2,3+i*3);
            lv_obj_set_style_radius(bar,0,0);lv_obj_set_style_border_width(bar,0,0);lv_obj_set_style_pad_all(bar,0,0);
            lv_obj_remove_flag(bar,LV_OBJ_FLAG_SCROLLABLE);lv_obj_remove_flag(bar,LV_OBJ_FLAG_CLICKABLE);}
        label(slot,LV_SYMBOL_CLOSE,3,2,12,Red,&lv_font_montserrat_10);
        updateWifiHeader(slot);
    }
    void updateWifiHeader(lv_obj_t *slot){if(!slot)return;char text[32];
        if(wifiSignal_.state==WifiState::Connected)snprintf(text,sizeof(text),"%d dBm",int(wifiSignal_.rssi_dBm));
        else snprintf(text,sizeof(text),"%s",wifiSignal_.state==WifiState::AccessPoint?"AP":wifiSignal_.state==WifiState::Connecting?"--":"off");
        lv_label_set_text(lv_obj_get_child(slot,0),text);
        lv_obj_set_style_text_color(lv_obj_get_child(slot,1),lv_color_hex(wifiSignal_.level()?Cyan:Muted),0);
        for(unsigned i=0;i<4;++i)lv_obj_set_style_bg_color(lv_obj_get_child(slot,2+i),lv_color_hex(wifiSignal_.level()>i?Cyan:0x4e595f),0);
        if(wifiSignal_.state==WifiState::Off)lv_obj_remove_flag(lv_obj_get_child(slot,6),LV_OBJ_FLAG_HIDDEN);
        else lv_obj_add_flag(lv_obj_get_child(slot,6),LV_OBJ_FLAG_HIDDEN);
        lv_obj_invalidate(slot);
    }
    lv_obj_t *root=nullptr,*body=nullptr,*keyboard=nullptr,*modal=nullptr;
    lv_obj_t *chemButtons[3]={},*cellButtons[5]={};
    lv_obj_t *voltageInput=nullptr,*currentInput=nullptr,*terminationInput=nullptr,*timeInput=nullptr,*level=nullptr,*packVoltage=nullptr,*keyboardClose=nullptr,*keyboardClear=nullptr;
    char inputBefore_[8]={};
    Config confirmedConfig_;
    lv_obj_t *hint=nullptr,*battery=nullptr,*startButton=nullptr,*action=nullptr,*actionLabel=nullptr;
    lv_obj_t *voltageLabel=nullptr,*currentLabel=nullptr,*socLabel=nullptr,*timeLabel=nullptr,*tempLabel=nullptr,*statusLabel=nullptr,*endVoltageLabel=nullptr;
    lv_obj_t *chart=nullptr,*powerLabel=nullptr,*energyLabel=nullptr,*chargeLabel=nullptr,*socBar=nullptr;
    PlotHistory plot_;
    lv_obj_t *summaryWarning=nullptr,*subtitleLabel=nullptr;
    lv_chart_series_t *voltageSeries=nullptr,*currentSeries=nullptr;
    uint32_t shownSamples=0;
    int32_t chartMin_mV=0,chartMax_mV=1;
    int32_t chartMax_mA=1;
    uint32_t endVoltage_mV=0;
    uint16_t terminationCurrent_mA=0;
    bool building=false,summary=false,pendingStart=false,pendingOverride=false,pendingAbort=false,pendingConfigure=false,pendingSummary=false;
    State drawn=State::Missing;
    char summaryMessage[160]={};
    bool bootNoticeShown=false;
    bool remoteConfirmPending_=false;uint32_t remoteConfirmRevision_=0;Config remoteConfirmConfig_;
    char notice_[192]={};
    void bootNotice(){
        if(ctl.bootDefaultsAvailable&&!ctl.bootProfileMatched&&!bootNoticeShown){
            bootNoticeShown=true;
            dialog("Charger settings recovered. Select chemistry and check cell voltage and charge level; no matching saved profile was found.");
        }
    }
    static void style(lv_obj_t *o,uint32_t color){
        lv_obj_set_style_bg_color(o,lv_color_hex(color),0);lv_obj_set_style_bg_opa(o,LV_OPA_COVER,0);
        lv_obj_set_style_border_width(o,0,0);lv_obj_set_style_radius(o,10,0);
        lv_obj_set_style_pad_all(o,8,0);lv_obj_set_style_text_color(o,lv_color_hex(Ink),0);
    }
    lv_obj_t *label(lv_obj_t *p,const char *text,int x,int y,int width,uint32_t color=Ink,const lv_font_t *font=&lv_font_montserrat_14){
        auto *o=lv_label_create(p);lv_label_set_text(o,text);lv_obj_set_pos(o,x,y);lv_obj_set_width(o,width);
        lv_obj_set_style_text_font(o,font,0);lv_obj_set_style_text_color(o,lv_color_hex(color),0);return o;
    }
    lv_obj_t *button(lv_obj_t *p,const char *text,int x,int y,int width,int height,uint32_t color,lv_event_cb_t cb,void *user=nullptr){
        auto *o=lv_button_create(p);lv_obj_set_pos(o,x,y);lv_obj_set_size(o,width,height);style(o,color);
        lv_obj_set_style_shadow_width(o,0,0);lv_obj_set_style_text_font(o,&lv_font_montserrat_14,0);
        lv_obj_set_style_text_color(o,lv_color_hex(color==Tile?Ink:Bg),0);
        auto *t=lv_label_create(o);lv_label_set_text(t,text);lv_obj_center(t);
        if(cb)lv_obj_add_event_cb(o,cb,LV_EVENT_CLICKED,user?user:this);return o;
    }
    static Ui *self(lv_event_t *e){return static_cast<Ui *>(lv_event_get_user_data(e));}
    // LVGL 9.2.2 buttonmatrix example: style a key's draw descriptors by id1.
    static void styleKeyboardOk(lv_obj_t *kb){
        lv_obj_add_flag(kb,LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
        lv_obj_add_event_cb(kb,[](lv_event_t *e){
            auto *task=lv_event_get_draw_task(e);auto *base=static_cast<lv_draw_dsc_base_t *>(lv_draw_task_get_draw_dsc(task));
            if(base->part!=LV_PART_ITEMS)return;
            auto *obj=static_cast<lv_obj_t *>(lv_event_get_target(e));
            const char *text=lv_buttonmatrix_get_button_text(obj,base->id1);
            if(!text||strcmp(text,LV_SYMBOL_OK))return;
            if(auto *fill=lv_draw_task_get_fill_dsc(task)){fill->color=lv_color_hex(Green);fill->opa=LV_OPA_COVER;}
            if(auto *label=lv_draw_task_get_label_dsc(task))label->color=lv_color_hex(Bg);
        },LV_EVENT_DRAW_TASK_ADDED,nullptr);
    }
    static void warning(lv_obj_t *label,const char *text){lv_label_set_text_fmt(label,LV_SYMBOL_WARNING " %s",text);}
    void reset(const char *title,const char *subtitle){
        ++viewRevision_;
        notice_[0]=0;labLabel_=nullptr;
        building=true;modal=nullptr;headerWifi_=modalWifi_=nullptr;focusedInput=wifiKeyboard=wifiBody=networkLabel=nullptr;body=keyboard=hint=battery=startButton=action=actionLabel=nullptr;
        voltageInput=currentInput=terminationInput=timeInput=level=packVoltage=keyboardClose=keyboardClear=nullptr;
        chart=voltageLabel=currentLabel=socLabel=timeLabel=tempLabel=statusLabel=endVoltageLabel=nullptr;powerLabel=energyLabel=chargeLabel=socBar=nullptr;
        summaryWarning=nullptr;
        voltageSeries=currentSeries=nullptr;
        auto *old=root;root=lv_obj_create(nullptr);style(root,Bg);lv_obj_set_style_radius(root,0,0);lv_obj_set_style_pad_all(root,0,0);
        lv_obj_remove_flag(root,LV_OBJ_FLAG_SCROLLABLE);
        label(root,title,14,12,292,Ink,&lv_font_montserrat_24);
        subtitleLabel=label(root,subtitle,14,42,190,Muted,&lv_font_montserrat_12);
        wifiHeader(root,headerWifi_);
        button(root,LV_SYMBOL_SETTINGS,256,12,50,28,Tile,[](lv_event_t *e){self(e)->settingsScreen();});
        lv_screen_load(root);if(old)lv_obj_delete(old);
    }
    void closeModal(){++viewRevision_;notice_[0]=0;labLabel_=nullptr;if(modal){lv_obj_delete(modal);modal=nullptr;}modalWifi_=nullptr;focusedInput=wifiKeyboard=wifiBody=networkLabel=nullptr;}
    lv_obj_t *check(lv_obj_t *parent,const char *text,bool checked,int y,lv_event_cb_t callback){
        auto *o=lv_checkbox_create(parent);lv_checkbox_set_text(o,text);lv_obj_set_pos(o,4,y);
        lv_obj_set_size(o,276,44);lv_obj_set_style_pad_all(o,6,0);lv_obj_set_style_pad_column(o,10,0);
        lv_obj_set_style_pad_all(o,6,LV_PART_INDICATOR);lv_obj_set_style_bg_color(o,lv_color_hex(Tile),0);lv_obj_set_style_bg_opa(o,LV_OPA_COVER,0);
        lv_obj_set_style_text_font(o,&lv_font_montserrat_14,0);lv_obj_set_style_text_color(o,lv_color_hex(Ink),0);
        if(checked)lv_obj_add_state(o,LV_STATE_CHECKED);lv_obj_add_event_cb(o,callback,LV_EVENT_VALUE_CHANGED,this);return o;
    }
    void settingsScreen(bool diagnostics=false){
        closeModal();modal=lv_obj_create(root);lv_obj_set_size(modal,320,480);lv_obj_set_pos(modal,0,0);style(modal,Bg);
        lv_obj_set_style_radius(modal,0,0);
        lv_obj_set_style_pad_all(modal,0,0);lv_obj_remove_flag(modal,LV_OBJ_FLAG_SCROLLABLE);
        label(modal,"OPTIONS",14,12,220,Ink,&lv_font_montserrat_24);
        wifiHeader(modal,modalWifi_);
        button(modal,"Back",256,12,50,28,Tile,[](lv_event_t *e){self(e)->closeModal();});
        button(modal,"Settings",14,58,140,38,diagnostics?Tile:Cyan,[](lv_event_t *e){self(e)->settingsScreen(false);});
        button(modal,"Diagnostics",166,58,140,38,diagnostics?Cyan:Tile,[](lv_event_t *e){self(e)->settingsScreen(true);});
        auto *content=lv_obj_create(modal);lv_obj_set_pos(content,14,110);lv_obj_set_size(content,292,356);style(content,Bg);
        lv_obj_set_style_pad_all(content,0,0);lv_obj_set_scroll_dir(content,LV_DIR_VER);
        if(diagnostics){char text[1660];diagnosticReport(text,sizeof(text));label(content,text,0,0,276);return;}
        check(content,"Persist charger config",options_.persist,8,[](lv_event_t *e){auto *u=self(e);++u->viewRevision_;u->options_.persist=lv_obj_has_state(static_cast<lv_obj_t *>(lv_event_get_target(e)),LV_STATE_CHECKED);});
        check(content,"WiFi",options_.wifi,58,[](lv_event_t *e){auto *u=self(e);++u->viewRevision_;if(lv_obj_has_state(static_cast<lv_obj_t *>(lv_event_get_target(e)),LV_STATE_CHECKED))u->wifiDialog();else u->options_.wifi=false;});
        check(content,"ESPNow",options_.espNow,108,[](lv_event_t *e){auto *u=self(e);++u->viewRevision_;u->options_.espNow=lv_obj_has_state(static_cast<lv_obj_t *>(lv_event_get_target(e)),LV_STATE_CHECKED);});
        networkLabel=label(content,networkText,4,160,276,Muted,&lv_font_montserrat_12);
        if(options_.wifi)button(content,"WiFi setup",4,244,270,38,Tile,[](lv_event_t *e){self(e)->wifiDialog();});
        button(content,"ESPNow setup",4,300,270,38,Tile,[](lv_event_t *e){self(e)->espNowDialog();});
        button(content,"Voltage Calibration (mV)",4,356,270,38,Tile,[](lv_event_t *e){self(e)->calibrationDialog();});
        char calibration[80];snprintf(calibration,sizeof(calibration),"Voltage %+d mV / Current %+d mA",options_.voltageCalibration_mV,options_.currentCalibration_mA);
        label(content,calibration,4,402,276,Muted,&lv_font_montserrat_12);
        button(content,"Current Calibration (mA)",4,430,270,38,Tile,[](lv_event_t *e){self(e)->calibrationDialog();});
        labLabel_=label(content,labText_,4,488,276,Muted,&lv_font_montserrat_12);
    }
    lv_obj_t *wifiField(const char *name,const char *value,unsigned maximum,int y,bool password=false){
        label(wifiBody,name,2,y,270,Muted,&lv_font_montserrat_12);
        auto *field=lv_textarea_create(wifiBody);lv_obj_set_pos(field,0,y+19);lv_obj_set_size(field,272,38);style(field,Tile);
        lv_obj_set_style_text_font(field,&lv_font_montserrat_14,0);lv_textarea_set_one_line(field,true);lv_textarea_set_max_length(field,maximum);
        lv_textarea_set_password_mode(field,password);lv_textarea_set_text(field,value);
        lv_obj_add_event_cb(field,[](lv_event_t *e){
            if(lv_event_get_code(e)==LV_EVENT_VALUE_CHANGED){++self(e)->viewRevision_;return;}
            if(lv_event_get_code(e)!=LV_EVENT_FOCUSED&&lv_event_get_code(e)!=LV_EVENT_CLICKED)return;
            auto *u=self(e);++u->viewRevision_;u->focusedInput=static_cast<lv_obj_t *>(lv_event_get_target(e));
            lv_obj_remove_flag(u->wifiKeyboard,LV_OBJ_FLAG_HIDDEN);lv_keyboard_set_textarea(u->wifiKeyboard,u->focusedInput);
            lv_obj_set_height(u->wifiBody,168);lv_obj_scroll_to_view(u->focusedInput,LV_ANIM_OFF);
        },LV_EVENT_ALL,this);return field;
    }
    void espNowDialog(){
        closeModal();modal=lv_obj_create(root);lv_obj_set_size(modal,320,480);lv_obj_set_pos(modal,0,0);style(modal,Bg);
        lv_obj_set_style_radius(modal,0,0);lv_obj_set_style_pad_all(modal,0,0);lv_obj_remove_flag(modal,LV_OBJ_FLAG_SCROLLABLE);
        label(modal,"ESPNow setup",14,12,292,Ink,&lv_font_montserrat_24);
        wifiBody=lv_obj_create(modal);lv_obj_set_pos(wifiBody,14,56);lv_obj_set_size(wifiBody,292,360);style(wifiBody,Bg);
        lv_obj_set_style_pad_all(wifiBody,0,0);lv_obj_set_scroll_dir(wifiBody,LV_DIR_VER);
        wifiSsid=wifiField("Friendly name",options_.friendlyName,31,8);
        label(wifiBody,"Shown in the tester Devices list.\nMaximum 31 bytes. Default: Charger.\nUnique device ID and mDNS stay unchanged.",4,90,270,Muted,&lv_font_montserrat_12);
        button(modal,"Cancel",14,432,140,38,Red,[](lv_event_t *e){self(e)->settingsScreen();});
        button(modal,"Apply",166,432,140,38,Green,[](lv_event_t *e){auto *u=self(e);AppOptions next=u->options_;
            if(strlen(lv_textarea_get_text(u->wifiSsid))>31){u->notify("Friendly name: maximum 31 bytes");return;}
            snprintf(next.friendlyName,sizeof(next.friendlyName),"%s",lv_textarea_get_text(u->wifiSsid));
            if(const char *why=validateOptions(next)){u->notify(why);return;}u->options_=next;u->settingsScreen();});
        wifiKeyboard=lv_keyboard_create(modal);styleKeyboardOk(wifiKeyboard);lv_obj_set_size(wifiKeyboard,320,224);lv_obj_align(wifiKeyboard,LV_ALIGN_BOTTOM_MID,0,0);
        lv_keyboard_set_mode(wifiKeyboard,LV_KEYBOARD_MODE_TEXT_LOWER);lv_obj_add_flag(wifiKeyboard,LV_OBJ_FLAG_HIDDEN);
        auto hide=[](lv_event_t *e){auto *u=self(e);lv_obj_add_flag(u->wifiKeyboard,LV_OBJ_FLAG_HIDDEN);lv_obj_set_height(u->wifiBody,360);u->focusedInput=nullptr;};
        lv_obj_add_event_cb(wifiKeyboard,hide,LV_EVENT_READY,this);lv_obj_add_event_cb(wifiKeyboard,hide,LV_EVENT_CANCEL,this);
    }
    void calibrationDialog(){
        closeModal();modal=lv_obj_create(root);lv_obj_set_size(modal,320,480);lv_obj_set_pos(modal,0,0);style(modal,Bg);
        lv_obj_set_style_radius(modal,0,0);lv_obj_set_style_pad_all(modal,0,0);lv_obj_remove_flag(modal,LV_OBJ_FLAG_SCROLLABLE);
        label(modal,"CALIBRATION",14,12,292,Ink,&lv_font_montserrat_24);
        wifiBody=lv_obj_create(modal);lv_obj_set_pos(wifiBody,14,56);lv_obj_set_size(wifiBody,292,360);style(wifiBody,Bg);
        lv_obj_set_style_pad_all(wifiBody,0,0);lv_obj_set_scroll_dir(wifiBody,LV_DIR_VER);
        char value[16];snprintf(value,sizeof(value),"%d",options_.voltageCalibration_mV);wifiSsid=wifiField("Voltage Calibration (mV)",value,6,8);
        snprintf(value,sizeof(value),"%d",options_.currentCalibration_mA);wifiPassword=wifiField("Current Calibration (mA)",value,6,82);
        lv_textarea_set_accepted_chars(wifiSsid,"-0123456789");lv_textarea_set_accepted_chars(wifiPassword,"-0123456789");
        label(wifiBody,"Offsets are added to pack readings.\nRange -5000 to +5000; default 0.\nTotals use corrected readings from now on.",4,164,270,Muted,&lv_font_montserrat_12);
        button(modal,"Cancel",14,432,140,38,Red,[](lv_event_t *e){self(e)->settingsScreen();});
        button(modal,"Apply",166,432,140,38,Green,[](lv_event_t *e){auto *u=self(e);AppOptions next=u->options_;
            if(!parseCalibration(lv_textarea_get_text(u->wifiSsid),next.voltageCalibration_mV)||
               !parseCalibration(lv_textarea_get_text(u->wifiPassword),next.currentCalibration_mA)){u->notify("Calibration: -5000 through +5000");return;}
            u->options_=next;u->ctl.setCalibration(next.voltageCalibration_mV,next.currentCalibration_mA);u->settingsScreen();});
        wifiKeyboard=lv_keyboard_create(modal);styleKeyboardOk(wifiKeyboard);lv_obj_set_size(wifiKeyboard,320,224);lv_obj_align(wifiKeyboard,LV_ALIGN_BOTTOM_MID,0,0);
        lv_keyboard_set_mode(wifiKeyboard,LV_KEYBOARD_MODE_NUMBER);lv_obj_add_flag(wifiKeyboard,LV_OBJ_FLAG_HIDDEN);
        auto hide=[](lv_event_t *e){auto *u=self(e);lv_obj_add_flag(u->wifiKeyboard,LV_OBJ_FLAG_HIDDEN);lv_obj_set_height(u->wifiBody,360);u->focusedInput=nullptr;};
        lv_obj_add_event_cb(wifiKeyboard,hide,LV_EVENT_READY,this);lv_obj_add_event_cb(wifiKeyboard,hide,LV_EVENT_CANCEL,this);
    }
    void wifiDialog(){
        wifiDraft_=options_;closeModal();modal=lv_obj_create(root);lv_obj_set_size(modal,320,480);lv_obj_set_pos(modal,0,0);style(modal,Bg);
        lv_obj_set_style_radius(modal,0,0);
        lv_obj_set_style_pad_all(modal,0,0);lv_obj_remove_flag(modal,LV_OBJ_FLAG_SCROLLABLE);label(modal,"WIFI",14,12,292,Ink,&lv_font_montserrat_24);
        wifiHeader(modal,modalWifi_);
        wifiBody=lv_obj_create(modal);lv_obj_set_pos(wifiBody,14,56);lv_obj_set_size(wifiBody,292,360);style(wifiBody,Bg);
        lv_obj_set_style_pad_all(wifiBody,0,0);lv_obj_set_scroll_dir(wifiBody,LV_DIR_VER);
        auto radio=[](lv_event_t *e){auto *u=self(e);u->wifiDraft_.mode=lv_event_get_target(e)==u->apRadio?WifiMode::AccessPoint:WifiMode::Join;
            if(u->wifiDraft_.mode==WifiMode::AccessPoint){lv_obj_add_state(u->apRadio,LV_STATE_CHECKED);lv_obj_remove_state(u->joinRadio,LV_STATE_CHECKED);}
            else{lv_obj_add_state(u->joinRadio,LV_STATE_CHECKED);lv_obj_remove_state(u->apRadio,LV_STATE_CHECKED);}};
        apRadio=check(wifiBody,"Access Point",wifiDraft_.mode==WifiMode::AccessPoint,0,radio);
        joinRadio=check(wifiBody,"Join WiFi",wifiDraft_.mode==WifiMode::Join,48,radio);
        lv_obj_set_style_radius(apRadio,LV_RADIUS_CIRCLE,LV_PART_INDICATOR);lv_obj_set_style_radius(joinRadio,LV_RADIUS_CIRCLE,LV_PART_INDICATOR);
        wifiSsid=wifiField("SSID (Join WiFi)",wifiDraft_.ssid,32,108);
        wifiPassword=wifiField("Password",wifiDraft_.password,63,174,true);
        wifiHostname=wifiField("mDNS / AP name",wifiDraft_.hostname,63,240);
        button(modal,"Cancel",14,432,140,38,Tile,[](lv_event_t *e){self(e)->settingsScreen();});
        button(modal,"Apply",166,432,140,38,Cyan,[](lv_event_t *e){auto *u=self(e);
            snprintf(u->wifiDraft_.ssid,sizeof(u->wifiDraft_.ssid),"%s",lv_textarea_get_text(u->wifiSsid));
            snprintf(u->wifiDraft_.password,sizeof(u->wifiDraft_.password),"%s",lv_textarea_get_text(u->wifiPassword));
            snprintf(u->wifiDraft_.hostname,sizeof(u->wifiDraft_.hostname),"%s",lv_textarea_get_text(u->wifiHostname));
            u->wifiDraft_.wifi=true;if(const char *why=validateOptions(u->wifiDraft_)){u->notify(why);return;}
            u->options_=u->wifiDraft_;u->settingsScreen();});
        wifiKeyboard=lv_keyboard_create(modal);styleKeyboardOk(wifiKeyboard);lv_obj_set_size(wifiKeyboard,320,224);lv_obj_align(wifiKeyboard,LV_ALIGN_BOTTOM_MID,0,0);
        lv_keyboard_set_mode(wifiKeyboard,LV_KEYBOARD_MODE_TEXT_LOWER);lv_obj_add_flag(wifiKeyboard,LV_OBJ_FLAG_HIDDEN);
        auto hide=[](lv_event_t *e){auto *u=self(e);lv_obj_add_flag(u->wifiKeyboard,LV_OBJ_FLAG_HIDDEN);lv_obj_set_height(u->wifiBody,360);u->focusedInput=nullptr;};
        lv_obj_add_event_cb(wifiKeyboard,hide,LV_EVENT_READY,this);lv_obj_add_event_cb(wifiKeyboard,hide,LV_EVENT_CANCEL,this);
    }
    void dialog(const char *text,bool proceed=false,bool diagnostic=false){
        closeModal();modal=lv_obj_create(root);lv_obj_set_pos(modal,0,0);lv_obj_set_size(modal,320,480);style(modal,Bg);
        snprintf(notice_,sizeof(notice_),"%s",text);
        lv_obj_set_style_bg_opa(modal,LV_OPA_80,0);lv_obj_set_style_radius(modal,0,0);lv_obj_set_style_pad_all(modal,0,0);
        lv_obj_remove_flag(modal,LV_OBJ_FLAG_SCROLLABLE);
        int height=diagnostic?400:210;
        auto *card=lv_obj_create(modal);lv_obj_set_size(card,304,height);lv_obj_center(card);style(card,0x303b42);
        lv_obj_remove_flag(card,LV_OBJ_FLAG_SCROLLABLE);
        if(diagnostic){
            auto *content=lv_obj_create(card);lv_obj_set_pos(content,0,0);lv_obj_set_size(content,280,316);style(content,0x303b42);
            lv_obj_set_style_pad_all(content,0,0);lv_obj_set_scroll_dir(content,LV_DIR_VER);label(content,text,0,0,264);
        }else warning(label(card,"",8,12,270),text);
        button(card,proceed?"Cancel":"OK",8,height-65,proceed?125:264,38,Tile,[](lv_event_t *e){self(e)->closeModal();});
        if(proceed)button(card,"Proceed",147,145,125,38,Orange,[](lv_event_t *e){auto *u=self(e);u->closeModal();u->pendingStart=true;u->pendingOverride=true;});
    }
    static bool numeric(lv_obj_t *input,uint16_t &value){
        const char *s=lv_textarea_get_text(input);if(!*s)return false;
        uint32_t n=0;for(const char *p=s;*p;++p){if(*p<'0'||*p>'9')return false;n=n*10+unsigned(*p-'0');if(n>65535)return false;}
        value=uint16_t(n);return true;
    }
    bool readFields(){
        uint16_t v,i,t,minutes;
        if(!numeric(voltageInput,v)||!numeric(currentInput,i)||!numeric(terminationInput,t)||!numeric(timeInput,minutes))return false;
        config.cell_mV=v;config.current_mA=i;config.termination_mA=t;config.terminationTime_min=minutes;
        config.percent=uint8_t(lv_dropdown_get_selected(level)*10);return true;
    }
    void selected(){
        for(unsigned i=0;i<3;++i)lv_obj_set_style_bg_color(chemButtons[i],lv_color_hex(unsigned(config.chemistry)==i+1?Cyan:Tile),0);
        for(unsigned i=0;i<5;++i)lv_obj_set_style_bg_color(cellButtons[i],lv_color_hex(config.cells==i+2?Cyan:Tile),0);
        for(unsigned i=0;i<3;++i)lv_obj_set_style_text_color(chemButtons[i],lv_color_hex(unsigned(config.chemistry)==i+1?Bg:Ink),0);
        for(unsigned i=0;i<5;++i)lv_obj_set_style_text_color(cellButtons[i],lv_color_hex(config.cells==i+2?Bg:Ink),0);
    }
    void validateInputs(){
        if(building||!startButton)return;
        ++viewRevision_;
        bool parsed=readFields();
        if(packVoltage){char text[32];uint16_t cell_mV;
            if(numeric(voltageInput,cell_mV)&&config.cells)snprintf(text,sizeof(text),"%.3f V",double(cell_mV)*config.cells/1000.0);
            else snprintf(text,sizeof(text),"-- V");lv_label_set_text(packVoltage,text);}
        const char *why=parsed?validate(config):"Enter numeric values";
        if(why){lv_obj_add_state(startButton,LV_STATE_DISABLED);warning(hint,why);}
        else{lv_obj_remove_state(startButton,LV_STATE_DISABLED);
            char s[100];snprintf(s,sizeof(s),"Target %.2f V/cell | %u mA | SOC approximate",target_mV(config)/1000.0,limitedCurrent_mA(config));lv_label_set_text(hint,s);}
    }
    void hideKeyboard(){
        focusedInput=nullptr;
        if(keyboard)lv_obj_add_flag(keyboard,LV_OBJ_FLAG_HIDDEN);
        if(keyboardClose)lv_obj_add_flag(keyboardClose,LV_OBJ_FLAG_HIDDEN);
        if(keyboardClear)lv_obj_add_flag(keyboardClear,LV_OBJ_FLAG_HIDDEN);
        if(body)lv_obj_set_height(body,342);
        if(startButton)lv_obj_remove_flag(startButton,LV_OBJ_FLAG_HIDDEN);
    }
    void cancelKeyboard(){
        if(focusedInput)lv_textarea_set_text(focusedInput,inputBefore_);
        hideKeyboard();validateInputs();
    }
    void startSummary(){
        if(!readFields())return;
        if(const char *why=validate(config)){dialog(why);return;}
        confirmedConfig_=config;
        closeModal();modal=lv_obj_create(root);lv_obj_set_size(modal,320,480);lv_obj_set_pos(modal,0,0);style(modal,Bg);
        lv_obj_set_style_radius(modal,0,0);lv_obj_set_style_pad_all(modal,0,0);lv_obj_remove_flag(modal,LV_OBJ_FLAG_SCROLLABLE);
        label(modal,"CONFIRM CHARGE",14,20,292,Ink,&lv_font_montserrat_24);
        const char *names[]={"Charging Voltage","Charging Current","String Count","Cell Voltage","Charge Level","Termination Current","Termination Time"};
        char values[7][48];
        snprintf(values[0],48,"%.3f V",double(config.cell_mV)*config.cells/1000.0);
        snprintf(values[1],48,"%u mA",config.current_mA);
        snprintf(values[2],48,"%uS",config.cells);snprintf(values[3],48,"%u mV",config.cell_mV);
        snprintf(values[4],48,"%u%%",config.percent);snprintf(values[5],48,"%u mA",config.termination_mA);
        snprintf(values[6],48,"%u h %02u min",config.terminationTime_min/60,config.terminationTime_min%60);
        for(unsigned n=0;n<7;++n){label(modal,names[n],14,70+int(n)*37,178,Muted,&lv_font_montserrat_12);
            label(modal,values[n],192,66+int(n)*37,116,Ink,&lv_font_montserrat_18);}
        char effective[80];snprintf(effective,sizeof(effective),"Effective target %.3f V",double(target_mV(config))*config.cells/1000.0);
        label(modal,effective,14,342,292,Orange,&lv_font_montserrat_14);
        button(modal,"CANCEL",14,424,140,42,Red,[](lv_event_t *e){self(e)->closeModal();});
        button(modal,"OK",166,424,140,42,Green,[](lv_event_t *e){auto *u=self(e);u->closeModal();u->pendingStart=true;u->pendingOverride=false;});
    }
    lv_obj_t *input(const char *title,uint16_t value,int y){
        auto *row=lv_obj_create(body);lv_obj_set_pos(row,0,y);lv_obj_set_size(row,292,48);style(row,Tile);
        lv_obj_remove_flag(row,LV_OBJ_FLAG_SCROLLABLE);label(row,title,0,7,138,Muted,&lv_font_montserrat_12);
        auto *o=lv_textarea_create(row);lv_obj_set_pos(o,144,-3);lv_obj_set_size(o,132,38);
        lv_textarea_set_one_line(o,true);lv_textarea_set_max_length(o,5);lv_textarea_set_accepted_chars(o,"0123456789");
        style(o,0x303b42);lv_obj_set_style_text_font(o,&lv_font_montserrat_18,0);
        char s[12];snprintf(s,sizeof(s),"%u",value);lv_textarea_set_text(o,s);
        lv_obj_add_event_cb(o,[](lv_event_t *e){
            auto *u=self(e);if(u->building)return;
            if(lv_event_get_code(e)==LV_EVENT_FOCUSED||lv_event_get_code(e)==LV_EVENT_CLICKED){
                if(u->focusedInput!=lv_event_get_target(e)){++u->viewRevision_;
                    snprintf(u->inputBefore_,sizeof(u->inputBefore_),"%s",lv_textarea_get_text(static_cast<lv_obj_t *>(lv_event_get_target(e))));}
                u->focusedInput=static_cast<lv_obj_t *>(lv_event_get_target(e));
                lv_obj_remove_flag(u->keyboardClose,LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(u->keyboardClear,LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(u->keyboard,LV_OBJ_FLAG_HIDDEN);lv_keyboard_set_textarea(u->keyboard,static_cast<lv_obj_t *>(lv_event_get_target(e)));
                lv_obj_set_height(u->body,140);lv_obj_add_flag(u->startButton,LV_OBJ_FLAG_HIDDEN);
                lv_obj_update_layout(u->body);
                lv_obj_scroll_to_view_recursive(static_cast<lv_obj_t *>(lv_event_get_target(e)),LV_ANIM_OFF);
            }else if(lv_event_get_code(e)==LV_EVENT_VALUE_CHANGED){
                if(lv_event_get_target(e)==u->voltageInput){uint16_t v;if(numeric(u->voltageInput,v)){
                    u->config.chemistry=v<=3800?Chemistry::Lfp:v<=4200?Chemistry::LiIon:Chemistry::LiHV;u->selected();}}
                u->validateInputs();
            }
        },LV_EVENT_ALL,this);return o;
    }
    void configureScreen(){
        summary=false;reset("CONFIGURE",ctl.chargerStatusText());
        body=lv_obj_create(root);lv_obj_set_pos(body,14,62);lv_obj_set_size(body,306,342);style(body,Bg);
        lv_obj_set_style_pad_all(body,0,0);lv_obj_set_scroll_dir(body,LV_DIR_VER);
        const char *chem[]={"LiFePO4","Li-ion","LiHV"};
        for(unsigned i=0;i<3;++i)chemButtons[i]=button(body,chem[i],int(i)*98,0,94,38,Tile,[](lv_event_t *e){
            auto *u=self(e);for(unsigned j=0;j<3;++j)if(lv_event_get_target(e)==u->chemButtons[j]){
                u->config.chemistry=Chemistry(j+1);u->config.cell_mV=full_mV(u->config.chemistry);
                u->building=true;char s[12];snprintf(s,sizeof(s),"%u",u->config.cell_mV);lv_textarea_set_text(u->voltageInput,s);u->building=false;}
            u->selected();u->validateInputs();});
        const char *cells[]={"2S","3S","4S","5S","6S"};
        for(unsigned i=0;i<5;++i)cellButtons[i]=button(body,cells[i],int(i)*59,46,55,38,Tile,[](lv_event_t *e){
            auto *u=self(e);for(unsigned j=0;j<5;++j)if(lv_event_get_target(e)==u->cellButtons[j])u->config.cells=j+2;
            u->selected();u->validateInputs();});
        voltageInput=input("Cell voltage / mV",config.cell_mV,94);
        currentInput=input("Charge current / mA",config.current_mA,146);
        terminationInput=input("Termination / mA",config.termination_mA,198);
        level=lv_dropdown_create(body);lv_obj_set_pos(level,0,250);lv_obj_set_size(level,140,40);style(level,Tile);
        lv_obj_set_style_text_font(level,&lv_font_montserrat_14,0);
        lv_dropdown_set_options(level,"0%\n10%\n20%\n30%\n40%\n50%\n60%\n70%\n80%\n90%\n100%");
        lv_dropdown_set_selected(level,config.percent/10);
        lv_obj_add_event_cb(level,[](lv_event_t *e){self(e)->validateInputs();},LV_EVENT_VALUE_CHANGED,this);
        packVoltage=label(body,"-- V",152,260,140,Ink,&lv_font_montserrat_18);
        timeInput=input("Termination / min",config.terminationTime_min,298);
        battery=label(body,"Battery -- V",8,354,280,Orange,&lv_font_montserrat_18);
        hint=label(root,"",14,407,292,Muted,&lv_font_montserrat_10);
        startButton=button(root,"Start Charging",14,432,292,38,Green,[](lv_event_t *e){auto *u=self(e);u->hideKeyboard();u->startSummary();});
        lv_obj_set_style_opa(startButton,LV_OPA_40,LV_STATE_DISABLED);
        keyboard=lv_keyboard_create(root);styleKeyboardOk(keyboard);lv_obj_set_size(keyboard,320,224);lv_obj_align(keyboard,LV_ALIGN_BOTTOM_MID,0,0);
        lv_keyboard_set_mode(keyboard,LV_KEYBOARD_MODE_NUMBER);lv_obj_add_flag(keyboard,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_event_cb(keyboard,[](lv_event_t *e){auto *u=self(e);u->hideKeyboard();u->validateInputs();},LV_EVENT_READY,this);
        lv_obj_add_event_cb(keyboard,[](lv_event_t *e){self(e)->cancelKeyboard();},LV_EVENT_CANCEL,this);
        keyboardClose=button(root,"CANCEL " LV_SYMBOL_CLOSE,166,216,140,34,Red,[](lv_event_t *e){self(e)->cancelKeyboard();});
        keyboardClear=button(root,"CLEAR",14,216,140,34,0x8bd5ff,[](lv_event_t *e){auto *u=self(e);if(u->focusedInput){lv_textarea_set_text(u->focusedInput,"");u->validateInputs();}});
        lv_obj_add_flag(keyboardClose,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(keyboardClear,LV_OBJ_FLAG_HIDDEN);
        selected();building=false;validateInputs();
    }
    void missingScreen(){
        summary=false;reset("BAT CHARGER","Direct I2C / address 0x75");
        auto *tile=lv_obj_create(root);lv_obj_set_pos(tile,14,136);lv_obj_set_size(tile,292,160);style(tile,Tile);
        label(tile,LV_SYMBOL_WARNING " No 2366 Detected",8,12,260,Red,&lv_font_montserrat_18);
        label(tile,!strcmp(ctl.message,"No 2366 Detected")?"Check charger power and wiring":ctl.message,8,54,260,Muted);
        label(root,"Testing automatically every second...",14,406,292,Muted);building=false;
    }
    void chargingHeader(){
        char text[96];snprintf(text,sizeof(text),"%s   %s",chemistryName(ctl.activeConfig().chemistry),options_.hostname);
        lv_label_set_text(subtitleLabel,text);lv_label_set_long_mode(subtitleLabel,LV_LABEL_LONG_DOT);
        lv_obj_set_size(subtitleLabel,190,16); // Ends at x=204; WiFi starts at x=214.
    }
    void chargingScreen(){
        summary=false;reset("CHARGING",chemistryName(config.chemistry));chargingHeader();
        const Config &active=ctl.activeConfig();endVoltage_mV=uint32_t(target_mV(active))*active.cells;terminationCurrent_mA=active.termination_mA;
        auto tile=[&](int x,int y,int w,int h){auto *o=lv_obj_create(root);lv_obj_set_pos(o,x,y);lv_obj_set_size(o,w,h);style(o,Tile);lv_obj_set_style_pad_all(o,6,0);lv_obj_remove_flag(o,LV_OBJ_FLAG_SCROLLABLE);return o;};
        auto *v=tile(14,65,94,78),*i=tile(114,65,94,78),*p=tile(214,65,92,78);
        voltageLabel=label(v,"-- V",0,3,82,Orange,&lv_font_montserrat_18);
        currentLabel=label(i,"-- A",0,3,82,Cyan,&lv_font_montserrat_18);
        powerLabel=label(p,"-- W",0,3,80,Ink,&lv_font_montserrat_18);
        char text[48];snprintf(text,sizeof(text),"End %.3f V",endVoltage_mV/1000.0);endVoltageLabel=label(v,text,0,43,82,Red,&lv_font_montserrat_10);
        snprintf(text,sizeof(text),"Term %u mA",unsigned(terminationCurrent_mA));label(i,text,0,43,82,Cyan,&lv_font_montserrat_10);
        chargeLabel=label(p,"0 mAh",0,35,80,Muted,&lv_font_montserrat_10);
        energyLabel=label(p,"0 mWh",0,52,80,Muted,&lv_font_montserrat_10);
        auto *t=tile(14,151,142,60),*soc=tile(164,151,142,60);
        tempLabel=label(t,"NTC -- C",0,8,130,Ink,&lv_font_montserrat_14);
        socLabel=label(soc,"~--% SOC",0,3,130,Muted,&lv_font_montserrat_14);
        socBar=lv_bar_create(soc);lv_obj_set_pos(socBar,0,33);lv_obj_set_size(socBar,126,3);lv_bar_set_range(socBar,0,1000);lv_bar_set_value(socBar,0,LV_ANIM_OFF);
        snprintf(text,sizeof(text),"Target: %u%%",active.percent);label(soc,text,0,40,130,Muted,&lv_font_montserrat_10);
        lv_obj_set_style_bg_color(socBar,lv_color_hex(0x4e595f),LV_PART_MAIN);lv_obj_set_style_bg_opa(socBar,LV_OPA_COVER,LV_PART_MAIN);lv_obj_set_style_radius(socBar,0,LV_PART_MAIN);lv_obj_set_style_border_width(socBar,0,LV_PART_MAIN);
        lv_obj_set_style_bg_color(socBar,lv_color_hex(SocGreen),LV_PART_INDICATOR);lv_obj_set_style_bg_opa(socBar,LV_OPA_COVER,LV_PART_INDICATOR);lv_obj_set_style_radius(socBar,0,LV_PART_INDICATOR);
        lv_obj_add_flag(t,LV_OBJ_FLAG_CLICKABLE);lv_obj_add_event_cb(t,[](lv_event_t *e){self(e)->settingsScreen();},LV_EVENT_CLICKED,this);
        timeLabel=label(root,"00:00:00",166,21,80,Ink,&lv_font_montserrat_12);
        statusLabel=label(root,ctl.graphStatusText(),14,220,292,Muted,&lv_font_montserrat_12);
        chart=lv_chart_create(root);lv_obj_set_pos(chart,14,244);lv_obj_set_size(chart,292,172);style(chart,Tile);
        lv_chart_set_type(chart,LV_CHART_TYPE_SCATTER);lv_chart_set_point_count(chart,2);lv_chart_set_div_line_count(chart,5,5);
        lv_obj_set_style_line_color(chart,lv_color_hex(0x77848b),LV_PART_MAIN);lv_obj_set_style_line_opa(chart,LV_OPA_40,LV_PART_MAIN);
        lv_obj_set_style_line_width(chart,2,LV_PART_ITEMS);lv_obj_set_style_line_opa(chart,LV_OPA_COVER,LV_PART_ITEMS);lv_obj_set_style_line_rounded(chart,true,LV_PART_ITEMS);lv_obj_set_style_size(chart,0,0,LV_PART_INDICATOR);
        voltageSeries=lv_chart_add_series(chart,lv_color_hex(Orange),LV_CHART_AXIS_PRIMARY_Y);currentSeries=lv_chart_add_series(chart,lv_color_hex(Cyan),LV_CHART_AXIS_SECONDARY_Y);
        lv_chart_set_all_value(chart,voltageSeries,LV_CHART_POINT_NONE);lv_chart_set_all_value(chart,currentSeries,LV_CHART_POINT_NONE);
        chartMin_mV=int32_t(low_mV(active.chemistry))*active.cells;if(chartMin_mV>int32_t(endVoltage_mV))chartMin_mV=int32_t(endVoltage_mV);
        chartMax_mV=int32_t(endVoltage_mV)+1000;chartMax_mA=int32_t(limitedCurrent_mA(active))+300;
        lv_chart_set_range(chart,LV_CHART_AXIS_PRIMARY_Y,chartMin_mV,chartMax_mV);lv_chart_set_range(chart,LV_CHART_AXIS_SECONDARY_Y,0,chartMax_mA);
        lv_chart_set_range(chart,LV_CHART_AXIS_PRIMARY_X,0,1);lv_chart_set_range(chart,LV_CHART_AXIS_SECONDARY_X,0,1);
        plot_.count=plot_.modeCount=plot_.duration_ms=0;
        lv_obj_add_event_cb(chart,[](lv_event_t *e){
            auto *u=self(e);lv_area_t area;lv_obj_get_content_coords(u->chart,&area);int32_t height=lv_obj_get_content_height(u->chart),width=lv_obj_get_content_width(u->chart);
            auto *layer=lv_event_get_layer(e);
            auto reference=[&](int32_t value,int32_t minimum,int32_t maximum,uint32_t color){
                int32_t y=area.y1+height-int32_t((int64_t(value)-minimum)*height/(maximum-minimum));lv_draw_line_dsc_t line;lv_draw_line_dsc_init(&line);
                line.color=lv_color_hex(color);line.width=2;line.dash_width=2;line.dash_gap=4;line.p1.x=area.x1;line.p2.x=area.x1+width;line.p1.y=line.p2.y=y;lv_draw_line(layer,&line);
            };
            reference(int32_t(u->endVoltage_mV),u->chartMin_mV,u->chartMax_mV,Red);reference(u->terminationCurrent_mA,0,u->chartMax_mA,Cyan);
            int32_t labelRight=area.x1-4;uint32_t span=u->plot_.duration_ms?u->plot_.duration_ms:1;
            for(unsigned n=0;n<u->plot_.modeCount;++n){const auto &mode=u->plot_.modes[n];int32_t x=area.x1+int32_t(uint64_t(mode.elapsed_ms)*width/span);if(x>area.x2)x=area.x2;
                if(n){lv_draw_line_dsc_t line;lv_draw_line_dsc_init(&line);line.color=lv_color_hex(0x888888);line.width=1;line.p1.x=line.p2.x=x;line.p1.y=area.y1;line.p2.y=area.y2;lv_draw_line(layer,&line);}
                int32_t left=n?x-11:area.x1;if(left<area.x1)left=area.x1;if(left+22>area.x2)left=area.x2-22;
                if(n&&left<labelRight+4)continue;lv_area_t box;box.x1=left;box.x2=left+22;box.y1=area.y2-15;box.y2=area.y2;
                lv_draw_rect_dsc_t rect;lv_draw_rect_dsc_init(&rect);rect.bg_color=lv_color_hex(0);rect.bg_opa=LV_OPA_COVER;rect.radius=0;lv_draw_rect(layer,&rect,&box);
                lv_draw_label_dsc_t text;lv_draw_label_dsc_init(&text);text.color=lv_color_hex(0xffffff);text.font=&lv_font_montserrat_10;text.text=mode.mode==2?"CC":mode.mode==3?"CV":"TR";text.align=LV_TEXT_ALIGN_CENTER;box.y1+=2;lv_draw_label(layer,&text,&box);labelRight=left+22;
            }
        },LV_EVENT_DRAW_MAIN_END,this);
        action=button(root,"Abort Charge",14,432,292,38,Red,[](lv_event_t *e){auto *u=self(e);if(u->ctl.state==State::Starting||u->ctl.state==State::Charging)u->pendingAbort=true;else u->pendingSummary=true;});
        actionLabel=lv_obj_get_child(action,0);shownSamples=UINT32_MAX;building=false;graph();
    }
    static void duration(uint64_t ms,char *s,size_t n){uint64_t seconds=ms/1000;snprintf(s,n,"%02llu:%02u:%02u",(unsigned long long)(seconds/3600),unsigned(seconds/60%60),unsigned(seconds%60));}
    void summaryScreen(){
        summary=true;reset("SUMMARY",ctl.message);
        snprintf(summaryMessage,sizeof(summaryMessage),"%s",ctl.message);
        if(ctl.state==State::Fault||ctl.state==State::Aborted)warning(subtitleLabel,ctl.message);
        char t[64];duration(ctl.totals.elapsed_ms,t,sizeof(t));
        const char *names[]={"Total charging time","Charge delivered","Energy delivered"};
        for(int i=0;i<3;++i){auto *tile=lv_obj_create(root);lv_obj_set_pos(tile,14,76+i*99);lv_obj_set_size(tile,292,87);style(tile,Tile);
            label(tile,names[i],2,0,270,Muted);char s[64];
            if(i==0)snprintf(s,sizeof(s),"%s",t);else snprintf(s,sizeof(s),"%.1f %s",i==1?ctl.totals.charge_mAh:ctl.totals.energy_mWh,i==1?"mAh":"mWh");
            label(tile,s,2,30,270,i==2?Orange:Cyan,&lv_font_montserrat_24);}
        summaryWarning=label(root,"",14,388,292,Red,&lv_font_montserrat_10);
        action=button(root,"OK",14,432,292,38,Green,[](lv_event_t *e){self(e)->pendingConfigure=true;});
        building=false;
    }
    void graph(){
        if(!chart)return;ctl.history.reduce(plot_,240);if(!plot_.count){lv_obj_invalidate(chart);return;}
        unsigned count=plot_.count;lv_chart_set_point_count(chart,count<2?2:count);uint32_t span=plot_.duration_ms?plot_.duration_ms:1;
        // LVGL 9.2.2 lv_map multiplies in int32; raw long-session milliseconds
        // overflow there. Normalize to parts per million using uint64 once.
        lv_chart_set_range(chart,LV_CHART_AXIS_PRIMARY_X,0,1000000);lv_chart_set_range(chart,LV_CHART_AXIS_SECONDARY_X,0,1000000);
        for(unsigned j=0;j<(count<2?2:count);++j){const auto &p=plot_.points[j<count?j:0];int32_t x_ppm=int32_t(uint64_t(p.elapsed_ms)*1000000/span);
            lv_chart_set_value_by_id2(chart,voltageSeries,j,x_ppm,p.voltage_mV);lv_chart_set_value_by_id2(chart,currentSeries,j,x_ppm,p.current_mA);}
        lv_chart_refresh(chart);
    }

public:
    Config config;
    // Automation changes controller state on the main task, independently of
    // the currently displayed screen. Rebuild through the same native screens.
    void automationState(const Config *applied=nullptr){
        if(applied)config=*applied;remoteConfirmPending_=false;drawn=ctl.state;
        if(drawn==State::Starting||drawn==State::Charging)chargingScreen();
        else if(drawn==State::Configure)configureScreen();
        else if(drawn==State::Complete||drawn==State::Aborted||drawn==State::Fault)summaryScreen();
    }
    explicit Ui(Controller &controller,AppOptions *options=nullptr):ctl(controller),options_(options?*options:ownedOptions_){}
    void begin(const Config *persisted=nullptr){
        ctl.setCalibration(options_.voltageCalibration_mV,options_.currentCalibration_mA);
        if(persisted){config=*persisted;bootNoticeShown=true;}else if(ctl.bootDefaultsAvailable)config=ctl.bootDefaults;
        drawn=ctl.state;if(drawn==State::Missing)missingScreen();else{configureScreen();bootNotice();}
    }
    bool graphVisible()const{return chart&&!modal&&!summary;}
    bool summaryVisible()const{return summary;}
    const AppOptions &options()const{return options_;}
    const WifiSignal &wifiSignal()const{return wifiSignal_;}
    const char *notice()const{return notice_;}
    const char *labStatusText()const{return labText_;}
    void diagnosticReport(char *text,size_t capacity)const{diagnosticText(ctl,text,capacity);size_t used=strlen(text);if(used<capacity)snprintf(text+used,capacity-used,"\n\n%s",labText_);}
    void labStatus(const char *text){if(!strcmp(labText_,text))return;snprintf(labText_,sizeof(labText_),"%s",text);if(labLabel_)lv_label_set_text(labLabel_,labText_);}
    int32_t graphMinimum_mV()const{return chartMin_mV;}
    uint32_t viewRevision()const{return viewRevision_;}
    int32_t graphMaximum_mV()const{return chartMax_mV;}
    int32_t graphMaximum_mA()const{return chartMax_mA;}
    uint32_t graphEnd_mV()const{return endVoltage_mV;}
    uint16_t graphTermination_mA()const{return terminationCurrent_mA;}
    const char *focusedText()const{return focusedInput?lv_textarea_get_text(focusedInput):nullptr;}
    bool focusedPassword()const{return focusedInput&&lv_textarea_get_password_mode(focusedInput);}
    bool remoteText(const char *text){
        if(!focusedInput)return false;
        uint32_t maximum=lv_textarea_get_max_length(focusedInput);if(maximum&&strlen(text)>maximum)return false;
        const char *accepted=lv_textarea_get_accepted_chars(focusedInput);
        if(accepted)for(const char *p=text;*p;++p)if(!strchr(accepted,*p))return false;
        lv_textarea_set_text(focusedInput,text);++viewRevision_;return true;
    }
    void networkStatus(const char *text){if(!strcmp(networkText,text))return;snprintf(networkText,sizeof(networkText),"%s",text);if(networkLabel)lv_label_set_text(networkLabel,networkText);}
    void wifiSignal(const WifiSignal &signal){if(signal.state==wifiSignal_.state&&signal.rssi_dBm==wifiSignal_.rssi_dBm)return;
        wifiSignal_=signal;updateWifiHeader(headerWifi_);updateWifiHeader(modalWifi_);}
    void notify(const char *text){dialog(text);}
    RemoteResult executeRemote(const RemoteCommand &command,uint32_t now_ms){
        RemoteResult result;result.id=command.id;
        auto done=[&](uint8_t code,const char *message){result.code=code;result.revision=viewRevision_;snprintf(result.message,sizeof(result.message),"%s",message);return result;};
        if(command.action==RemoteAction::Abort){
            if(ctl.state!=State::Starting&&ctl.state!=State::Charging)return done(1,"No active charge to abort");
            ctl.abort(now_ms);summaryScreen();drawn=ctl.state;remoteConfirmPending_=false;return done(ctl.disableConfirmed?0:1,ctl.message);
        }
        if(command.revision!=viewRevision_)return done(1,"Tablet state changed. Refresh and try again.");
        if(command.action==RemoteAction::Settings){
            if(const char *why=validateOptions(command.options))return done(1,why);
            options_=command.options;ctl.setCalibration(options_.voltageCalibration_mV,options_.currentCalibration_mA);closeModal();return done(0,"Settings applied");
        }
        if(command.action==RemoteAction::Cancel){remoteConfirmPending_=false;closeModal();return done(0,"Cancelled");}
        if(command.action==RemoteAction::Configure){
            if(!ctl.configure())return done(1,"Charger must be stopped and disable confirmed");
            remoteConfirmPending_=false;drawn=ctl.state;configureScreen();return done(0,"Ready");
        }
        if(command.action==RemoteAction::Summary){
            if(ctl.state!=State::Complete&&ctl.state!=State::Aborted&&ctl.state!=State::Fault)return done(1,"Charge is not stopped");
            summaryScreen();drawn=ctl.state;return done(0,ctl.message);
        }
        if(ctl.state!=State::Configure)return done(1,"Return to Configure before starting");
        if(const char *why=validate(command.config))return done(1,why);
        Chemistry inferred=command.config.cell_mV<=3800?Chemistry::Lfp:command.config.cell_mV<=4200?Chemistry::LiIon:Chemistry::LiHV;
        if(command.config.chemistry!=inferred)return done(1,"Cell voltage and chemistry do not match");
        if(command.proceed&&(!remoteConfirmPending_||command.revision!=remoteConfirmRevision_||!sameConfig(command.config,remoteConfirmConfig_)))
            return done(1,"Battery confirmation expired. Start again.");
        remoteConfirmPending_=false;config=command.config;confirmedConfig_=config;closeModal();configureScreen();
        auto outcome=ctl.start(config,command.proceed,now_ms,SessionOrigin::Web);
        if(outcome==Controller::StartResult::Started){drawn=ctl.state;chargingScreen();return done(0,"Charge started");}
        if(outcome==Controller::StartResult::NoBattery){
            dialog("No battery detected. Proceed anyway?",true);remoteConfirmPending_=true;remoteConfirmConfig_=config;remoteConfirmRevision_=viewRevision_;
            return done(2,"No battery detected. Proceed anyway?");
        }
        const char *why=outcome==Controller::StartResult::Mismatch?"Battery does not fit String Count and/or Chemistry":ctl.message;
        if(ctl.state==State::Fault)refresh();else dialog(why);return done(1,why);
    }
    // Hardware mutations are dispatched from main loop, never a touch callback.
    void commands(uint32_t now_ms){
        ctl.setCalibration(options_.voltageCalibration_mV,options_.currentCalibration_mA);
        if(pendingSummary){pendingSummary=false;summaryScreen();}
        if(pendingConfigure){pendingConfigure=false;if(ctl.configure()){drawn=ctl.state;configureScreen();}}
        if(pendingAbort){pendingAbort=false;ctl.abort(now_ms);summaryScreen();drawn=ctl.state;}
        if(pendingStart){pendingStart=false;
            if(!readFields()||!sameConfig(config,confirmedConfig_)){dialog("Settings changed. Review and start again.");return;}
            auto result=ctl.start(config,pendingOverride,now_ms);pendingOverride=false;
            if(result==Controller::StartResult::NoBattery)dialog("No battery detected. Proceed anyway?",true);
            else if(result==Controller::StartResult::Mismatch)dialog("Battery does not fit String Count and/or Chemistry");
            else if(result==Controller::StartResult::Started){drawn=ctl.state;chargingScreen();}
            else if(ctl.state==State::Configure)dialog(ctl.message);
        }
    }
    void refresh(){
        if(ctl.state!=drawn){
            ++viewRevision_;
            drawn=ctl.state;
            if(drawn==State::Fault||drawn==State::Aborted)summaryScreen();
            if(drawn==State::Configure){
                if(ctl.bootDefaultsAvailable&&config.chemistry==Chemistry::None)config=ctl.bootDefaults;
                configureScreen();bootNotice();return;
            }
            if(drawn==State::Complete){if(action){lv_label_set_text(actionLabel,"Done");style(action,Green);lv_obj_set_style_text_color(action,lv_color_hex(Bg),0);}}
        }
        if(summary){
            if(strcmp(summaryMessage,ctl.message))summaryScreen();
            if(ctl.state==State::Fault||ctl.state==State::Aborted)warning(subtitleLabel,ctl.message);
            else lv_label_set_text(subtitleLabel,ctl.message);
            if(action){if(ctl.disableConfirmed)lv_obj_remove_state(action,LV_STATE_DISABLED);else lv_obj_add_state(action,LV_STATE_DISABLED);}
            if(summaryWarning){
                const char *why=ctl.stopVerificationFailed()?"Charger disable NOT confirmed":ctl.totals.missing_ms?"Totals exclude missing measurement intervals":nullptr;
                if(why)warning(summaryWarning,why);else lv_label_set_text(summaryWarning,"");
            }
            return;
        }
        if(battery){lv_label_set_text(subtitleLabel,ctl.chargerStatusText());char s[64];if(ctl.measurement.valid)snprintf(s,sizeof(s),"Battery %.3f V",ctl.measurement.voltage_mV/1000.0);else snprintf(s,sizeof(s),"Battery -- V");lv_label_set_text(battery,s);}
        if(voltageLabel){chargingHeader();char s[80];
            if(ctl.measurement.valid){
                snprintf(s,sizeof(s),"%.3f V",ctl.measurement.voltage_mV/1000.0);lv_label_set_text(voltageLabel,s);
                snprintf(s,sizeof(s),"%.3f A",ctl.measurement.current_mA/1000.0);lv_label_set_text(currentLabel,s);
                const Config &chargingConfig=ctl.activeConfig();
                float soc_percent=displayedSoc_percent(lookup(chargingConfig.chemistry,float(ctl.measurement.voltage_mV)/chargingConfig.cells,false),ctl.chargeCompleteReported,chargingConfig.percent);
                snprintf(s,sizeof(s),"~%.0f%% SOC",soc_percent);lv_label_set_text(socLabel,s);lv_bar_set_value(socBar,int32_t(lroundf(targetProgress_percent(soc_percent,chargingConfig.percent)*10)),LV_ANIM_OFF);
                if(isfinite(ctl.measurement.temperature_C))snprintf(s,sizeof(s),"NTC %.1f C",ctl.measurement.temperature_C);else snprintf(s,sizeof(s),LV_SYMBOL_WARNING " NTC unavailable");lv_label_set_text(tempLabel,s);
            }
            if(ctl.measurement.valid){snprintf(s,sizeof(s),"%.2f W",double(ctl.measurement.voltage_mV)*ctl.measurement.current_mA/1000000.0);lv_label_set_text(powerLabel,s);}
            else{lv_label_set_text(voltageLabel,"-- V");lv_label_set_text(currentLabel,"-- A");lv_label_set_text(powerLabel,"-- W");lv_label_set_text(tempLabel,"NTC -- C");lv_label_set_text(socLabel,"~--% SOC");lv_bar_set_value(socBar,0,LV_ANIM_OFF);}
            snprintf(s,sizeof(s),"%.0f mAh",ctl.totals.charge_mAh);lv_label_set_text(chargeLabel,s);
            snprintf(s,sizeof(s),"%.0f mWh",ctl.totals.energy_mWh);lv_label_set_text(energyLabel,s);
            duration(ctl.totals.elapsed_ms,s,sizeof(s));lv_label_set_text(timeLabel,s);
            if(!strcmp(ctl.message,"Waiting for charging input"))warning(statusLabel,ctl.message);
            else if(ctl.profileSaveFailed)warning(statusLabel,"Reboot defaults could not be saved");
            else if(ctl.history.modeOverflow)warning(statusLabel,"Mode-event log is full");
            else lv_label_set_text(statusLabel,ctl.graphStatusText());
            if(shownSamples!=ctl.history.revision){shownSamples=ctl.history.revision;graph();}
        }
    }
};
} // namespace batcharger
