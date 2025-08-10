#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(99, 102, 70));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));

  VitalSigns vitals = {98.6, 75, 98};
  assert(evaluateVitals(vitals) == VitalStatus::OK);

  assert(evaluateVitals({103.0, 80, 97}) == VitalStatus::TemperatureOutOfRange);
  assert(evaluateVitals({94.0, 80, 97}) == VitalStatus::TemperatureOutOfRange);

  assert(evaluateVitals({98.6, 55, 97}) == VitalStatus::PulseOutOfRange);
  assert(evaluateVitals({98.6, 101, 97}) == VitalStatus::PulseOutOfRange);

  assert(evaluateVitals({98.6, 75, 89}) == VitalStatus::Spo2OutOfRange);
}

