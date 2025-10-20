#include "monitor.h"
#include <unordered_map>
#include <thread>
#include <chrono>
#include <iostream>

using std::cout;
using std::flush;
using std::unordered_map;

VitalStatus checkVital(float value, float lower, float upper, float toleranceRatio,
                       VitalStatus outOfRangeStatus, WarningFunc printWarning) {
    float tolerance = upper * toleranceRatio;
    if (value < lower || value > upper) {
        return outOfRangeStatus;
    }
    printWarning(value, lower, upper, tolerance);
    return VitalStatus::OK;
}

void printTemperatureWarning(float temp, float lower, float upper, float tolerance) {
    if (temp <= lower + tolerance) {
        cout << "Warning: Approaching hypothermia\n";
    } else if (temp >= upper - tolerance) {
        cout << "Warning: Approaching hyperthermia\n";
    }
}

void printPulseWarning(float pulse, float lower, float upper, float tolerance) {
    if (pulse <= lower + tolerance) {
        cout << "Warning: Approaching bradycardia\n";
    } else if (pulse >= upper - tolerance) {
        cout << "Warning: Approaching tachycardia\n";
    }
}

void printSpo2Warning(float spo2, float lower, float upper, float tolerance) {
    if (spo2 <= lower + tolerance) {
        cout << "Warning: Approaching hypoxia\n";
    }
}

VitalStatus checkTemperature(float temp) {
    return checkVital(temp, 95.0f, 102.0f, 0.015f, 
    VitalStatus::TemperatureOutOfRange, printTemperatureWarning);
}

VitalStatus checkPulse(float pulse) {
    return checkVital(pulse, 60.0f, 100.0f, 0.015f, 
    VitalStatus::PulseOutOfRange, printPulseWarning);
}

VitalStatus checkSpo2(float spo2) {
    return checkVital(spo2, 90.0f, 100.0f, 0.015f, 
    VitalStatus::Spo2OutOfRange, printSpo2Warning);
}

VitalStatus evaluateVitals(const VitalSigns& vitals) {
    VitalStatus status = checkTemperature(vitals.temperature);
    if (status != VitalStatus::OK) return status;

    status = checkPulse(vitals.pulseRate);
    if (status != VitalStatus::OK) return status;

    return checkSpo2(vitals.spo2);
}

void blinkIndicator() {
    for (int i = 0; i < 6; ++i) {
        cout << "\r* " << flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "\r *" << flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void printAlert(VitalStatus status) {
    static const unordered_map<VitalStatus, const char*> alertMessages = {
        {VitalStatus::TemperatureOutOfRange, "Temperature is critical!\n"},
        {VitalStatus::PulseOutOfRange, "Pulse Rate is out of range!\n"},
        {VitalStatus::Spo2OutOfRange, "Oxygen Saturation out of range!\n"}
    };

    auto it = alertMessages.find(status);
    if (it != alertMessages.end()) {
        cout << it->second;
    }
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalSigns vitals{temperature, pulseRate, spo2};
    VitalStatus status = evaluateVitals(vitals);
    if (status != VitalStatus::OK) {
        printAlert(status);
        blinkIndicator();
        return 0;
    }
    return 1;
}
