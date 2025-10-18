#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, TemperatureOutOfRange) {
    EXPECT_FALSE(vitalsOk(103, 80, 95));
    EXPECT_FALSE(vitalsOk(94, 80, 95));
}

TEST(Monitor, PulseRateOutOfRange) {
    EXPECT_FALSE(vitalsOk(98, 59, 95));
    EXPECT_FALSE(vitalsOk(98, 101, 95));
}

TEST(Monitor, Spo2OutOfRange) {
    EXPECT_FALSE(vitalsOk(98, 80, 89));
}

TEST(Monitor, AllVitalsOk) {
    EXPECT_TRUE(vitalsOk(98.1, 70, 98));
    EXPECT_TRUE(vitalsOk(95, 60, 90));
    EXPECT_TRUE(vitalsOk(102, 100, 90));
}

