#ifndef SBB_SUMITOMO_SENSOR_NODE_V2_BOARD_H
#define SBB_SUMITOMO_SENSOR_NODE_V2_BOARD_H

#include <Arduino.h>

#include "drivers/dip_switch.h"
#include "drivers/gpio.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node_v2 {

constexpr HardwareSerial *kHc12Serial = &Serial1;
constexpr int kHc12SetPin = 20;

// v2.0 PCB has PN532 connected incorrectly to Serial3 (TX to TX and RX to RX),
// but it needs to be reworked to re-route pins to Serial2.
constexpr HardwareSerial *kPn532Serial = &Serial2;

constexpr GpioPin kLedGreen = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = A3};
constexpr GpioPin kLedRed = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = A5};
constexpr GpioPin kLedYellow = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = A4};

constexpr DipSwitchPins kDipSwitch = {
    .polarity = DipSwitchPolarity::kActiveLow,
    .pins =
        {
            A6,
            A7,
            A8,
            A9,
            A10,
            A11,
            A12,
            A13,
        },
    .number_of_pins = 8,
};

// Buzzer has external pullup.
constexpr GpioPin kCpgBuzzer = {.mode = GpioMode::kInput,
                                  .polarity = GpioPolarity::kActiveLow,
                                  .pin = 3};
constexpr GpioPin kCpgLed = {.mode = GpioMode::kInputPullUp,
                               .polarity = GpioPolarity::kActiveLow,
                               .pin = 2};

// J2.
constexpr GpioPin kTurretGreen = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 6};
// J3.
constexpr GpioPin kTurretYellow = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 8};
// J4.
constexpr GpioPin kTurretRed = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 11};
// J5.
constexpr GpioPin kTurretBuzzer = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 12};

}  // namespace node_v2
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_V2_BOARD_H
