#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <unordered_map>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

VitalStatus checkTemperature(float temp) {
    if (temp > 102 || temp < 95) {
        return VitalStatus::TemperatureOutOfRange;
    }
    return VitalStatus::OK;
}

VitalStatus checkPulse(float pulse) {
    if (pulse < 60 || pulse > 100) {
        return VitalStatus::PulseOutOfRange;
    }
    return VitalStatus::OK;
}

VitalStatus checkSpo2(float spo2) {
    if (spo2 < 90) {
        return VitalStatus::Spo2OutOfRange;
    }
    return VitalStatus::OK;
}

VitalStatus evaluateVitals(const VitalSigns& vitals) {
    VitalStatus status;

    status = checkTemperature(vitals.temperature);
    if (status != VitalStatus::OK) return status;

    status = checkPulse(vitals.pulseRate);
    if (status != VitalStatus::OK) return status;

    return checkSpo2(vitals.spo2);
}

void blinkIndicator() {
    for (int i = 0; i < 6; ++i) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

void printAlert(VitalStatus status) {
    static const std::unordered_map<VitalStatus, const char*> alertMessages = {
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
