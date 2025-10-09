#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <unordered_map>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

VitalStatus checkTemperature(float temp) {
    const float lower = 95.0;
    const float upper = 102.0;
    const float tolerance = upper * 0.015;   // 1.53

    if (temp < lower || temp > upper) {
        return VitalStatus::TemperatureOutOfRange;
    }
    if (temp <= lower + tolerance) {
        cout << "Warning: Approaching hypothermia\n";
    }    
    if (temp >= upper - tolerance) {
        cout << "Warning: Approaching hyperthermia\n";
    }
    return VitalStatus::OK;
}


VitalStatus checkPulse(float pulse) {
    const float lower = 60.0;
    const float upper = 100.0;
    const float tolerance = upper * 0.015;   // 1.5

    if (pulse < lower || pulse > upper) {
        return VitalStatus::PulseOutOfRange;
    }

    if (pulse >= lower && pulse <= lower + tolerance) {
        cout << "Warning: Approaching bradycardia\n";
    } else if (pulse >= upper - tolerance && pulse <= upper) {
        cout << "Warning: Approaching tachycardia\n";
    }

    return VitalStatus::OK;
}

VitalStatus checkSpo2(float spo2) {
    const float lower = 90.0;
    const float tolerance = 100.0 * 0.015;   // 1.5

    if (spo2 < lower) {
        return VitalStatus::Spo2OutOfRange;
    }
    if (spo2 <= lower + tolerance) {
        cout << "Warning: Approaching hypoxia\n";
    }
    return VitalStatus::OK;
}

VitalStatus evaluateVitals(const VitalSigns& vitals) {
    VitalStatus status = checkTemperature(vitals.temperature);
    status = (status == VitalStatus::OK) ? checkPulse(vitals.pulseRate) : status;
    status = (status == VitalStatus::OK) ? checkSpo2(vitals.spo2) : status;
    return status;
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
