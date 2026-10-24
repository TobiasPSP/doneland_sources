#pragma once
#include <stdint.h>
#include <stddef.h>

// Portable IP2366_I2C control. No Arduino, LVGL, chemistry/SOC or application
// session dependency. Values at the public boundary carry their physical units.
namespace ip2366 {
static constexpr const char *LibraryVersion="1.2.2";

class Transport {
public:
    virtual bool read(uint8_t reg,uint8_t &value)=0;
    virtual bool write(uint8_t reg,uint8_t value)=0;
    virtual bool probe()=0;
    virtual bool recover()=0;
    virtual ~Transport()=default;
};

struct Settings {
    uint8_t cells=0;
    uint16_t target_cell_mV=0;
    uint16_t charge_current_mA=0;
    uint16_t termination_current_mA=100;
    uint16_t precharge_current_mA=100;
    uint16_t battery_low_cell_mV=3000;
    uint16_t power_limit_W=140;
};

struct Status {
    uint8_t charge=0,input=0,typeC=0,faults=0;
    // V1.13 page 8: 0x31 bits 2:0; code 7 is reserved.
    uint8_t chargeStage()const{return charge&0x07;}
    const char *chargeStageName()const{
        switch(chargeStage()){case 0:return "Standby";case 1:return "Trickle charging";case 2:return "Constant current (CC)";
        case 3:return "Constant voltage (CV)";case 4:return "Waiting";case 5:return "Full";case 6:return "Charging timeout";default:return "Reserved state (7)";}
    }
    bool inputPresent()const{return (input&0x80)!=0;}
    bool dischargeActive()const{return (charge&0x08)!=0;}
    bool chargeComplete()const{return (charge&0x10)!=0;}
    bool chargingActive()const{return (charge&0x20)&&(charge&7)>=1&&(charge&7)<=3&&inputPresent()&&!dischargeActive();}
    const char *faultReason()const;
};

struct NtcReading {
    uint16_t voltage_mV=0;
    uint8_t excitation_uA=0,bias_before=0,bias_after=0;
    bool excitation_stable=false;
};

struct ChargingSnapshot {
    bool active=false;
    uint16_t measured_current_mA=0;
    Settings settings;
};

enum class FailureKind:uint8_t {None,Read,Write,Readback,InvalidSettings,NotConfigured};
enum class CommunicationFault:uint8_t {None,Unstable,Disconnected};
struct Failure {
    FailureKind kind=FailureKind::None;
    uint8_t reg=0,expected=0,actual=0,mask=0;
};

class IP2366 {
public:
    explicit IP2366(Transport &transport):transport_(transport){}

    // Probe/recover, disable charger, set UFP and the existing source/sink policy.
    // Transport electrical initialization (if any) precedes begin(). Never enables.
    bool begin();
    static const char *validateSettings(const Settings &settings);

    // Configure always disables first and leaves charging disabled. Invalid
    // settings cause no writes. chargerOn requires successful configuration.
    bool configureCharger(const Settings &settings);
    bool chargerOff();
    bool chargerOn();

    // Audit desired fields; repair only on mismatch, disable first, enable last.
    // With enable=true, faults/missing input prohibit re-enable after repair.
    // A completion flag encountered during repair leaves charging disabled and
    // is exposed through completionDetected(). No status/fault flags are cleared.
    bool enforceSettings(const Settings &settings,bool enable);
    bool applyIdleConfiguration();

    bool readVoltage(uint16_t &voltage_mV);
    bool readCurrent(uint16_t &current_mA);
    bool readTargetVoltage(uint16_t &target_cell_mV);
    bool readChargeCurrentLimit(uint16_t &current_mA,uint8_t *raw_code=nullptr);
    bool readStatus();
    bool readNtc(NtcReading &reading);
    // Read-only, usable before begin(). active requires SYS00 charge enable
    // and nonzero unsigned current ADC, checked again after reading settings.
    // Returns only validated screen-controlled fields; no register is written.
    bool readChargingSnapshot(ChargingSnapshot &snapshot);

    const Status &status()const{return status_;}
    const Failure &failure()const{return failure_;}
    void clearFailure(){failure_=Failure{};communication_fault_=CommunicationFault::None;consecutive_failures_=0;}
    CommunicationFault communicationFault()const{return communication_fault_;}
    const char *communicationWarning()const;
    uint32_t correctionCount()const{return corrections_;}
    bool configurationChanged()const{return configuration_changed_;}
    bool completionDetected()const{return completion_detected_;}

private:
    struct Field {uint8_t reg,mask,value;};
    Transport &transport_;
    Status status_;
    Failure failure_;
    CommunicationFault communication_fault_=CommunicationFault::None;
    uint8_t consecutive_failures_=0;
    bool failedTransaction(FailureKind kind,uint8_t reg);
    bool configured_=false,configuration_changed_=false,completion_detected_=false;
    uint32_t corrections_=0;
    bool readRegister(uint8_t reg,uint8_t &value);
    bool writeRegister(uint8_t reg,uint8_t value);
    bool readPair(uint8_t low,uint16_t &value);
    bool updateField(const Field &field);
    bool enforce(const Settings *settings,bool enable);
    static size_t fields(const Settings *settings,bool enable,Field *result);
    static uint8_t powerCode(uint16_t power_W);
};
} // namespace ip2366
