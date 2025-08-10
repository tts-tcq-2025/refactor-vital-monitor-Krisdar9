#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

VitalStatus evaluateVitals(const VitalSigns& vitals) {
    if (vitals.temperature > 102 || vitals.temperature < 95) {
        return VitalStatus::TemperatureOutOfRange;
    }
    if (vitals.pulseRate < 60 || vitals.pulseRate > 100) {
        return VitalStatus::PulseOutOfRange;
    }
    if (vitals.spo2 < 90) {
        return VitalStatus::Spo2OutOfRange;
    }
    return VitalStatus::OK;
}

void printAlert(VitalStatus status) {
    switch (status) {
        case VitalStatus::TemperatureOutOfRange:
            cout << "Temperature is critical!\n";
            break;
        case VitalStatus::PulseOutOfRange:
            cout << "Pulse Rate is out of range!\n";
            break;
        case VitalStatus::Spo2OutOfRange:
            cout << "Oxygen Saturation out of range!\n";
            break;
        default:
            break;
    }
}

void blinkIndicator() {
    for (int i = 0; i < 6; ++i) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
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
