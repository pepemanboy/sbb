#ifndef SBB_SUMITOMO_SENSOR_NODE_BOARD_H
#define SBB_SUMITOMO_SENSOR_NODE_BOARD_H

#include <Arduino.h>

#include "drivers/dip_switch.h"
#include "drivers/gpio.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node {

constexpr int kHc12TxPin = 6;
constexpr int kHc12RxPin = 5;
constexpr int kHc12SetPin = 4;

constexpr int kPn532TxPin = 2;
constexpr int kPn532RxPin = 3;

constexpr GpioPin kLedGreen = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 9};
constexpr GpioPin kLedRed = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 7};
constexpr GpioPin kLedYellow = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 8};

constexpr GpioPin kIrSensor = {
    .mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 2};

constexpr DipSwitchPins kDipSwitch = {
    .polarity = DipSwitchPolarity::kActiveLow,
    .pins =
        {
            10,  // [1] (LSB)
            11,  // [2]
            12,  // [3]
            // Note that [4] is not usable.
            A0,  // [5]
            A1,  // [6]
            A2,  // [7]
            A3   // [8] (MSB)
        },
    .number_of_pins = 7,
};

}  // namespace node
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_BOARD_H
