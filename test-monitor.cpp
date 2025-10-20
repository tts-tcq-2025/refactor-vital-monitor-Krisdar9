#include "./monitor.h"
#include <assert.h>
#include <iostream>

using std::cout;

void testCheckVital() {
    assert(checkVital(50.0f, 40.0f, 60.0f, 0.1f, VitalStatus::PulseOutOfRange,
                     [](auto, auto, auto, auto) {}) == VitalStatus::OK);
    assert(checkVital(30.0f, 40.0f, 60.0f, 0.1f, VitalStatus::PulseOutOfRange,
                     [](auto, auto, auto, auto) {}) == VitalStatus::PulseOutOfRange);
    assert(checkVital(70.0f, 40.0f, 60.0f, 0.1f, VitalStatus::PulseOutOfRange,
                     [](auto, auto, auto, auto) {}) == VitalStatus::PulseOutOfRange);
}

void testWarnings() {
    printTemperatureWarning(95.0f, 95.0f, 102.0f, 102.0f * 0.015f);
    printTemperatureWarning(101.9f, 95.0f, 102.0f, 102.0f * 0.015f);
    printTemperatureWarning(98.0f, 95.0f, 102.0f, 102.0f * 0.015f);
    printPulseWarning(60.0f, 60.0f, 100.0f, 100.0f * 0.015f);
    printPulseWarning(99.0f, 60.0f, 100.0f, 100.0f * 0.015f);
    printPulseWarning(80.0f, 60.0f, 100.0f, 100.0f * 0.015f);
    printSpo2Warning(90.0f, 90.0f, 100.0f, 100.0f * 0.015f);
    printSpo2Warning(92.0f, 90.0f, 100.0f, 100.0f * 0.015f);
}

void testEvaluateVitals() {
    VitalSigns normal{98.6f, 75.0f, 97.0f};
    assert(evaluateVitals(normal) == VitalStatus::OK);

    VitalSigns tempHigh{110.0f, 75.0f, 97.0f};
    assert(evaluateVitals(tempHigh) == VitalStatus::TemperatureOutOfRange);

    VitalSigns pulseLow{98.6f, 50.0f, 97.0f};
    assert(evaluateVitals(pulseLow) == VitalStatus::PulseOutOfRange);

    VitalSigns spo2Low{98.6f, 75.0f, 80.0f};
    assert(evaluateVitals(spo2Low) == VitalStatus::Spo2OutOfRange);
}

void testVitalsOk() {
    assert(vitalsOk(98.6f, 75.0f, 97.0f) == 1);
    assert(vitalsOk(110.0f, 75.0f, 97.0f) == 0);
    assert(vitalsOk(98.6f, 50.0f, 97.0f) == 0);
    assert(vitalsOk(98.6f, 75.0f, 80.0f) == 0);
}


int main() {
    testCheckVital();
    testWarnings();
    testEvaluateVitals();
    testVitalsOk();

    cout << "All tests passed!\n";
    return 0;
}




