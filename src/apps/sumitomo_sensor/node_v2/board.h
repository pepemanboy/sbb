#ifndef SBB_SUMITOMO_SENSOR_NODE_V2_BOARD_H
#define SBB_SUMITOMO_SENSOR_NODE_V2_BOARD_H

#include <Arduino.h>

#include "drivers/gpio.h"
#include "drivers/dip_switch.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node_v2 {

constexpr int kHc12TxPin = 19;
constexpr int kHc12RxPin = 18;
constexpr int kHc12SetPin = 20;

constexpr int kPn532TxPin = 15;
constexpr int kPn532RxPin = 14;

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
            A14,
            A15
        },
    .number_of_pins = 10,
};

}  // namespace node_v2
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_V2_BOARD_H



