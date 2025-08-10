#pragma once

struct VitalSigns {
    float temperature;
    float pulseRate;
    float spo2;
};

enum class VitalStatus {
    OK,
    TemperatureOutOfRange,
    PulseOutOfRange,
    Spo2OutOfRange
};

VitalStatus evaluateVitals(const VitalSigns& vitals);
void printAlert(VitalStatus status);
void blinkIndicator();
int vitalsOk(float temperature, float pulseRate, float spo2);

