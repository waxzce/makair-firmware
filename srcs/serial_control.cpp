/******************************************************************************
 * @author Makers For Life
 * @copyright Copyright (c) 2020 Makers For Life
 * @file serial_control.cpp
 * @brief Handle control protocol on the serial input
 *****************************************************************************/

#pragma once

#include "../includes/config.h"

// INCLUDES ===================================================================

// Associated header
#include "../includes/serial_control.h"

// Externals
#if HARDWARE_VERSION == 2 || HARDWARE_VERSION == 3
#include "Arduino.h"
#include "CRC32.h"
#endif

/// Internals
#include "../includes/pressure_controller.h"

// GLOBAL ITEMS ==============================================================

#define CONTROL_HEADER_SIZE 2
static const uint8_t header[CONTROL_HEADER_SIZE] = {0x05, 0x0A};
#define CONTROL_FOOTER_SIZE 2
static const uint8_t footer[CONTROL_FOOTER_SIZE] = {0x50, 0xA0};

// FUNCTIONS ==================================================================

/**
 * Convert an array of 2 bytes to a u16
 *
 * @param bytes Array of 2 elements
 * @return The corresponding u16 number
 */
// cppcheck-suppress unusedFunction
uint16_t toU16(byte bytes[]) {
    uint16_t num = (bytes[0] << 8) + bytes[1];
    return num;
}

/**
 * Convert an array of 4 bytes to a u32
 *
 * @param bytes Array of 4 elements
 * @return The corresponding u32 number
 */
// cppcheck-suppress unusedFunction
uint32_t toU32(byte bytes[]) {
    uint32_t num = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
    return num;
}

// cppcheck-suppress unusedFunction
void serialControlLoop() {
#if HARDWARE_VERSION == 2 || HARDWARE_VERSION == 3
    // Let's note this current time to avoid blocking too long here
    int time = millis();

    // We need to ensure we received the whole message
    while (((time + 2) >= millis()) && (Serial6.available() >= 11)) {
        // Let's check the first header byte
        if (Serial6.peek() == header[0]) {
            // If it is correct, we discard it and continue
            (void)Serial6.read();

            // Let's check the second header byte
            if (Serial6.peek() == header[1]) {
                // If it is correct, we discard it and continue
                (void)Serial6.read();

                // Let's prepare to compute a CRC
                CRC32 computedCRC;

                byte setting = Serial6.read();
                computedCRC.update(setting);

                byte rawValue[2];
                Serial6.readBytes(rawValue, 2);
                computedCRC.update(rawValue, 2);
                uint16_t value = toU16(rawValue);

                byte rawExpectedCRC[2];
                Serial6.readBytes(rawExpectedCRC, 4);
                uint32_t expectedCRC = toU32(rawExpectedCRC);

                // Let's check that the 2 bytes footer is correct
                if ((Serial6.read() != footer[0]) || (Serial6.read() != footer[1])) {
                    DBG_DO(Serial.println(
                        "Invalid footer for control message; discarding whole message"));
                    continue;
                }

                // The computed CRC must be the same as the one included with the message
                if (expectedCRC != computedCRC.finalize()) {
                    DBG_DO(Serial.println(
                        "Invalid CRC for control message; discarding whole message"));
                    continue;
                }

                DBG_DO({
                    Serial.print("Serial control message: setting = ");
                    Serial.print(setting);
                    Serial.print(", value = ");
                    Serial.print(value);
                    Serial.println();
                });

                switch (setting) {
                case 1:  // PeakPressure
                    pController.onPeakPressureSet(value);
                    break;

                case 2:  // PlateauPressure
                    pController.onPlateauPressureSet(value);
                    break;

                case 3:  // PEEP
                    pController.onPeepSet(value);
                    break;

                case 4:  // CyclesPerMinute
                    pController.onCycleSet(value);
                    break;

                case 5:  // ExpiratoryTerm
                    pController.onExpiratoryTermSet(value);
                    break;

                case 6:  // TriggerEnabled
                    pController.onTriggerEnabledSet(value);
                    break;

                case 7:  // TriggerOffset
                    pController.onTriggerOffsetSet(value);
                    break;

                default:
                    DBG_DO({
                        Serial.print("Unknown control setting: ");
                        Serial.print(setting);
                        Serial.println();
                    });
                    break;
                }
            } else {
                // This is not the begining of a message, let's discard it
                (void)Serial6.read();
                DBG_DO(Serial.println("Invalid header for control message; discarding a byte"));
            }
        } else {
            // This is not the begining of a message, let's discard it
            (void)Serial6.read();
            DBG_DO(Serial.println("Invalid header for control message; discarding a byte"));
        }
    }
#endif
}
