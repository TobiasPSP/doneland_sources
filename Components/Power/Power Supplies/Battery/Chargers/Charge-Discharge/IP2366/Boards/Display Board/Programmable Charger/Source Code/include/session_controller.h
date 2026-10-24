#pragma once
#include <IP2366.h>
#include <stdio.h>
#include "settings.h"
#include "thermistor.h"
#include "profile_store.h"
#include "charge_mode_filter.h"

namespace batcharger {
// Application lifecycle and accounting only. All chip register knowledge,
// validation/encoding and hardware actions are delegated to IP2366Control.
class Controller {
    ip2366::IP2366 device_;
    ProfileStore *profileStore_;
    bool bootSnapshotTaken_=false,bootSnapshotValid_=false;
    ip2366::ChargingSnapshot bootSnapshot_;
    uint32_t fastAt_ms=0,slowAt_ms=0,sampleAt_ms=0,elapsedAt_ms=0,lastSample_ms=0,startedAt_ms=0,detectionAt_ms=0;
    bool profileReady=false,previousCountable=false,haveSample=false,startupWaiting=false;
    Measurement previous;
    Config desired;
    ChargeModeFilter modeFilter_;
    mutable char graphStatus_[96]={};
    int16_t voltageCalibration_mV_=0,currentCalibration_mA_=0;
    static uint16_t corrected(uint16_t raw,int16_t offset){int32_t value=int32_t(raw)+offset;return uint16_t(value<0?0:value>65535?65535:value);}

    void syncDevice(){
        const auto &s=device_.status();status31=s.charge;status33=s.input;status34=s.typeC;status38=s.faults;
        const auto &f=device_.failure();failureKind=uint8_t(f.kind);failureReg=f.reg;
        failureExpected=f.expected;failureActual=f.actual;failureMask=f.mask;
        corrections=device_.correctionCount();
    }
    bool chargerOff(){bool ok=device_.chargerOff();syncDevice();return ok;}
    bool chargerOn(){bool ok=device_.chargerOn();syncDevice();return ok;}
    bool configureCharger(){bool ok=device_.configureCharger(deviceSettings(desired));syncDevice();return ok;}
    bool status(){bool ok=device_.readStatus();statusValid=ok;syncDevice();
        if(!ok||!device_.status().chargingActive())modeFilter_.interrupt();
        return ok;}
    const char *faultReason()const{return device_.status().faultReason();}
    bool chargeStatus()const{return device_.status().chargingActive();}
    bool wantEnabled()const{return state==State::Charging||(state==State::Starting&&!startupWaiting);}
    bool restore(bool active){
        bool ok=profileReady?device_.enforceSettings(deviceSettings(desired),active):device_.applyIdleConfiguration();
        if(device_.configurationChanged())previousCountable=false;
        pendingCompletion=device_.completionDetected();syncDevice();return ok;
    }
    void clock(uint32_t now_ms){
        if(state==State::Starting||state==State::Charging)totals.elapsed_ms+=uint32_t(now_ms-elapsedAt_ms);
        elapsedAt_ms=now_ms;
    }
    void error(const char *why,uint32_t now_ms){
        if(const char *communication=device_.communicationWarning())why=communication;
        if(state==State::Fault){
            disableConfirmed=chargerOff();if(disableConfirmed)disableConfirmed=restore(false);
            if(const char *communication=device_.communicationWarning())snprintf(message,sizeof(message),"%s",communication);
            return;
        }
        stop(State::Fault,why,now_ms);
    }
public:
    State state=State::Missing;
    Measurement measurement;
    Totals totals;
    History history;
    uint8_t status31=0,status33=0,status34=0,status38=0;
    uint8_t fault31=0,fault33=0,fault34=0,fault38=0;
    uint8_t failureKind=0,failureReg=0,failureExpected=0,failureActual=0,failureMask=0;
    uint32_t corrections=0,samples=0,sessionsStarted=0,measurementAt_ms=0;
    bool disableConfirmed=false,pendingCompletion=false,statusValid=false,stopAttempted=false;
    bool chargeCompleteReported=false;
    SessionOrigin sessionOrigin=SessionOrigin::None;
    bool bootDefaultsAvailable=false,bootProfileMatched=false,profileSaveFailed=false;
    Config bootDefaults;
    char message[160]="No 2366 Detected";
    explicit Controller(ip2366::Transport &transport,ProfileStore *profiles=nullptr):device_(transport),profileStore_(profiles){}
    void setCalibration(int16_t voltage_mV,int16_t current_mA){
        if(voltageCalibration_mV_==voltage_mV&&currentCalibration_mA_==current_mA)return;
        voltageCalibration_mV_=voltage_mV;currentCalibration_mA_=current_mA;
        previousCountable=false;modeFilter_.interrupt(); // Do not integrate across a calibration step.
        if(measurement.valid){measurement.voltage_mV=corrected(measurement.raw_voltage_mV,voltage_mV);
            measurement.current_mA=corrected(measurement.raw_current_mA,current_mA);}
    }
    const Config &activeConfig()const{return desired;}
    const char *chargerStatusText()const{return !statusValid?"Status unavailable":device_.status().dischargeActive()?"Discharging":device_.status().chargeStageName();}
    const char *graphStatusText()const{
        if(state==State::Fault||state==State::Aborted||state==State::Complete||startupWaiting)return message;
        snprintf(graphStatus_,sizeof(graphStatus_),"IP2366: %s",chargerStatusText());return graphStatus_;
    }
    bool stopVerificationFailed()const{return stopAttempted&&!disableConfirmed&&state!=State::Starting&&state!=State::Charging;}

    bool initialize(uint32_t now_ms){
        detectionAt_ms=now_ms;
        state=State::Missing;profileReady=false;previousCountable=haveSample=false;
        pendingCompletion=false;disableConfirmed=false;statusValid=false;measurement.valid=false;chargeCompleteReported=false;
        if(!bootSnapshotTaken_){
            bootSnapshotTaken_=true;
            bootSnapshotValid_=device_.readChargingSnapshot(bootSnapshot_);
        }
        bool ok=device_.begin();syncDevice();
        if(!ok){snprintf(message,sizeof(message),"%s",failureKind?"IP2366 initialization failed":"No 2366 Detected");return false;}
        disableConfirmed=true;state=State::Configure;snprintf(message,sizeof(message),"Ready");
        if(bootSnapshotValid_&&bootSnapshot_.active){
            const auto &s=bootSnapshot_.settings;bootDefaults=Config{};
            bootDefaults.cells=s.cells;bootDefaults.cell_mV=s.target_cell_mV;
            bootDefaults.current_mA=s.charge_current_mA;bootDefaults.termination_mA=s.termination_current_mA;
            Config saved;
            if(profileStore_&&profileStore_->load(saved)&&matchesSnapshot(saved,bootSnapshot_)){
                bootDefaults=saved;bootProfileMatched=true;
            }
            bootDefaultsAvailable=true;
        }
        fastAt_ms=slowAt_ms=sampleAt_ms=elapsedAt_ms=now_ms;return true;
    }
    bool readVoltage(uint16_t &pack_mV){bool ok=device_.readVoltage(pack_mV);syncDevice();return ok;}
    enum class StartResult {Started,NoBattery,Mismatch,Invalid,Failed};
    StartResult start(const Config &config,bool proceedUndetected,uint32_t now_ms,SessionOrigin origin=SessionOrigin::Tablet){
        if(state!=State::Configure)return StartResult::Failed;
        device_.clearFailure();syncDevice();
        if(const char *why=validate(config)){snprintf(message,sizeof(message),"%s",why);return StartResult::Invalid;}
        if(!history.prepare()){snprintf(message,sizeof(message),"Session history allocation failed");return StartResult::Failed;}
        uint16_t pack_mV;
        if(!readVoltage(pack_mV)){error("Battery voltage read failed",now_ms);return StartResult::Failed;}
        if(pack_mV<100&&!proceedUndetected)return StartResult::NoBattery;
        if(pack_mV>=100&&pack_mV>uint32_t(config.cells)*full_mV(config.chemistry))return StartResult::Mismatch;

        if(!status()){error("Status read failed",now_ms);return StartResult::Failed;}
        if(const char *why=faultReason()){error(why,now_ms);return StartResult::Failed;}
        if(!device_.status().inputPresent()){error("No charging input power",now_ms);return StartResult::Failed;}
        desired=config;profileReady=true;
        pendingCompletion=false;
        if(!configureCharger()){error("Charging configuration failed",now_ms);return StartResult::Failed;}
        // Commit metadata after verified configuration but BEFORE enabling, so
        // a reboot immediately after enable has the matching profile available.
        profileSaveFailed=profileStore_&&!profileStore_->save(desired);
        if(!chargerOn()){error("Charging configuration failed",now_ms);return StartResult::Failed;}
        totals={};history.clear();modeFilter_.clear();haveSample=previousCountable=false;stopAttempted=false;chargeCompleteReported=false;sessionOrigin=origin;
        state=State::Starting;++sessionsStarted;startupWaiting=false;disableConfirmed=false;snprintf(message,sizeof(message),"Starting charger");
        startedAt_ms=now_ms;elapsedAt_ms=fastAt_ms=slowAt_ms=sampleAt_ms=now_ms;return StartResult::Started;
    }
    void stop(State outcome,const char *why,uint32_t now_ms){
        stopAttempted=true;
        chargeCompleteReported=outcome==State::Complete&&device_.status().chargeComplete();
        if(outcome==State::Fault&&state!=State::Fault){fault31=status31;fault33=status33;fault34=status34;fault38=status38;}
        clock(now_ms);state=outcome;previousCountable=false;pendingCompletion=false;
        snprintf(message,sizeof(message),"%s",why);
        disableConfirmed=chargerOff();if(disableConfirmed)disableConfirmed=restore(false);
        // A disconnect during the stop/disable action also requires Summary.
        if(const char *communication=device_.communicationWarning()){
            state=State::Fault;snprintf(message,sizeof(message),"%s",communication);
        }
    }
    void abort(uint32_t now_ms){if(state==State::Starting||state==State::Charging)stop(State::Aborted,"Charge aborted",now_ms);}
    bool configure(){
        if(!disableConfirmed||state==State::Starting||state==State::Charging||state==State::Missing)return false;
        // The user acknowledged the stopped session after disable was verified.
        // Start a fresh communication observation for the configuration screen.
        device_.clearFailure();syncDevice();
        state=State::Configure;snprintf(message,sizeof(message),"Ready");return true;
    }
    bool sample(uint32_t now_ms){
        Measurement next;ip2366::NtcReading ntc;
        bool ok=device_.readVoltage(next.voltage_mV)&&device_.readCurrent(next.current_mA)&&
            device_.readChargeCurrentLimit(next.configured_current_mA,&next.current_limit_code)&&device_.readNtc(ntc);
        syncDevice();
        if(!ok){measurement.valid=false;previousCountable=false;modeFilter_.interrupt();return false;}
        next.ntc_mV=ntc.voltage_mV;next.ntc_bias_before=ntc.bias_before;next.ntc_bias_after=ntc.bias_after;
        next.excitation_uA=ntc.excitation_uA;next.excitation_stable=ntc.excitation_stable;
        if(next.excitation_stable)next.temperature_C=ntcTemperature_C(next.ntc_mV,next.excitation_uA);
        next.raw_voltage_mV=next.voltage_mV;next.raw_current_mA=next.current_mA;
        next.voltage_mV=corrected(next.raw_voltage_mV,voltageCalibration_mV_);
        next.current_mA=corrected(next.raw_current_mA,currentCalibration_mA_);
        next.valid=true;measurement=next;measurementAt_ms=now_ms;++samples;
        if(state==State::Charging){
            bool countable=chargeStatus();
            if(haveSample){uint32_t dt_ms=uint32_t(now_ms-lastSample_ms);
                if(dt_ms<=2000&&previousCountable&&countable){
                    double average_mA=(double(previous.current_mA)+next.current_mA)*0.5;
                    double average_mW=(double(previous.voltage_mV)*previous.current_mA+double(next.voltage_mV)*next.current_mA)/2000.0;
                    totals.charge_mAh+=average_mA*dt_ms/3600000.0;totals.energy_mWh+=average_mW*dt_ms/3600000.0;
                }else if(dt_ms>2000)totals.missing_ms+=dt_ms;
            }
            previous=next;lastSample_ms=now_ms;haveSample=true;previousCountable=countable;
            history.add(next.voltage_mV,countable?next.current_mA:0,uint32_t(totals.elapsed_ms));
            if(countable)modeFilter_.observe(next.voltage_mV,next.current_mA,uint32_t(target_mV(desired))*desired.cells,
                                            desired.cells,uint32_t(totals.elapsed_ms),history);
            else modeFilter_.interrupt();
            if(uint64_t(next.raw_voltage_mV)*next.raw_current_mA>100000000ULL&&countable){error("Measured charging power exceeds 100 W",now_ms);return true;}
        }

        return true;
    }
    void tick(uint32_t now_ms){
        clock(now_ms);
        if((state==State::Starting||state==State::Charging)&&totals.elapsed_ms>uint64_t(desired.terminationTime_min)*60000ULL){
            stop(State::Aborted,"Termination time reached",now_ms);return;
        }
        if(state==State::Missing){
            if(uint32_t(now_ms-detectionAt_ms)>=1000)initialize(now_ms);
            return;
        }
        if(uint32_t(now_ms-fastAt_ms)>=500){
            fastAt_ms=now_ms;
            if(!status()){error("I2C status communication lost",now_ms);return;}
            if(state==State::Starting||state==State::Charging){
                if(const char *why=faultReason()){error(why,now_ms);return;}
                if(device_.status().dischargeActive()){error("Unexpected discharge state",now_ms);return;}
                if(!device_.status().inputPresent()){
                    if(state==State::Charging){error("Charging input power lost",now_ms);return;}
                    if(!chargerOff()){error("Startup charger disable failed",now_ms);return;}
                    disableConfirmed=true;startupWaiting=true;previousCountable=false;
                    snprintf(message,sizeof(message),"Waiting for charging input");
                }else{
                    if(device_.status().chargeComplete()){stop(State::Complete,"Charge complete",now_ms);return;}
                    if(state==State::Starting){
                        if(startupWaiting){
                            if(!configureCharger()||!chargerOn()){error("Startup configuration failed",now_ms);return;}
                            startupWaiting=false;disableConfirmed=false;snprintf(message,sizeof(message),"Starting charger");
                        }else if(chargeStatus()){state=State::Charging;snprintf(message,sizeof(message),"Charging");}
                    }
                }
                if(state==State::Starting&&uint32_t(now_ms-startedAt_ms)>=10000){error("Charging startup timed out",now_ms);return;}
                if(!chargeStatus())previousCountable=false;
            }
            uint16_t target_cell_mV;bool readOk=device_.readTargetVoltage(target_cell_mV);syncDevice();
            if(!readOk){error("Target-voltage read failed",now_ms);return;}
            if(profileReady&&target_cell_mV!=target_mV(desired)){
                if(!restore(wantEnabled())){error("Target-voltage correction failed",now_ms);return;}
                if(pendingCompletion){stop(State::Complete,"Charge complete",now_ms);return;}
            }
        }
        if(uint32_t(now_ms-slowAt_ms)>=2000){
            slowAt_ms=now_ms;
            if(!restore(wantEnabled())){error("Configuration readback/correction failed",now_ms);return;}
            if(pendingCompletion){stop(State::Complete,"Charge complete",now_ms);return;}
            if(!wantEnabled())disableConfirmed=true;
        }
        if(uint32_t(now_ms-sampleAt_ms)>=1000){sampleAt_ms=now_ms;if(!sample(now_ms))error("I2C measurement communication lost",now_ms);}
    }
};
} // namespace batcharger
