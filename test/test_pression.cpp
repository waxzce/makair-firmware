/**
 * @file test_pression.cpp
 * @author Makers For Life
 * @brief Unit tests for pression.cpp
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "../includes/pression.h"

#define KPA_MMH2O 101.97162129779
#define RATIO_VOLTAGE_DIVIDER 0.8192
#define V_SUPPLY 5.08

/// Old converting function using floats
int16_t convertSensor2PressureFloat(uint16_t sensorValue) {
    static float filteredVout = 0;
    double rawVout =  sensorValue * 3.3 / 1024.0;
    filteredVout = filteredVout + (rawVout - filteredVout) * 0.2;

    // Voltage divider ratio
    double vOut = filteredVout / RATIO_VOLTAGE_DIVIDER;

    // Pressure converted to kPA
    double pressure = (vOut / V_SUPPLY - 0.04) / 0.09;

    if (pressure <= 0.0) {
        return 0;
    }

    return pressure * KPA_MMH2O;
}

/**
 * @brief Test Fixture to test the pression file
 * 
 */
class PressionTest : public ::testing::Test {
 protected:
    PressionTest(){}
};

TEST_F(PressionTest, testConvertSensor2Pressure) {
    std::vector<uint16_t> input = {0, 100, 1000, 5000, 8000, 16000, 24000, 65535};
    std::vector<uint16_t> outputTruth;
    std::vector<uint16_t> output;

    for (int i = 0; i < input.size(); i++) {
        outputTruth.push_back(convertSensor2PressureFloat(input[i]));
        output.push_back(convertSensor2Pressure(input[i]));

        std::cout << outputTruth.back() <<" " << output.back() << std::endl;
    }

    for (int i = 0; i < output.size(); i++) {
        ASSERT_EQ(outputTruth[i], output[i]);
    }
}