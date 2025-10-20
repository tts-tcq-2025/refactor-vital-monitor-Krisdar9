#pragma once
#include <iostream>

enum class VitalStatus {
    OK,
    TemperatureOutOfRange,
    PulseOutOfRange,
    Spo2OutOfRange
};

struct VitalSigns {
    float temperature;
    float pulseRate;
    float spo2;
};

//  Generic checker
template<typename T, typename WarningFunc>
VitalStatus checkVital(
    T value, 
    T lower, 
    T upper, 
    float toleranceRatio,
    VitalStatus outOfRangeStatus,
    WarningFunc printWarning);

//  Warning print functions
void printTemperatureWarning(float temp, float lower, float upper, float tolerance);
void printPulseWarning(float pulse, float lower, float upper, float tolerance);
void printSpo2Warning(float spo2, float lower, float upper, float tolerance);

//  Individual checks
VitalStatus checkTemperature(float temp);
VitalStatus checkPulse(float pulse);
VitalStatus checkSpo2(float spo2);

VitalStatus evaluateVitals(const VitalSigns& vitals);

void blinkIndicator();
void printAlert(VitalStatus status);

int vitalsOk(float temperature, float pulseRate, float spo2);
