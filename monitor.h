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

VitalStatus checkTemperature(float temp);
VitalStatus checkPulse(float pulse);
VitalStatus checkSpo2(float spo2);
VitalStatus evaluateVitals(const VitalSigns& vitals);

void printAlert(VitalStatus status);
void blinkIndicator();
int vitalsOk(float temperature, float pulseRate, float spo2);
