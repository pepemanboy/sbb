#ifndef SBB_SUMITOMO_SENSOR_NODE_V3_BOARD_H
#define SBB_SUMITOMO_SENSOR_NODE_V3_BOARD_H

#include <Arduino.h>

#include "drivers/dip_switch.h"
#include "drivers/gpio.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node_v3 {

constexpr HardwareSerial *kHc12Serial = &Serial1;
constexpr int kHc12SetPin = 20;

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

constexpr GpioPin kInductiveSensors[] = {
  // Sensor 0.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 10},
  // Sensor 1.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 13},
  // Sensor 2.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 12},
  // Sensor 3.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 11},
  // Sensor 4.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 8},
  // Sensor 5.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 6},
  // Sensor 6.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 3},
  // Sensor 7.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 4},
  // Sensor 8.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 7},
  // Sensor 9.
  {.mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 9},
};

constexpr GpioPin kInterruptPin = {
  .mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 2};

}  // namespace node_v3
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_V3_BOARD_H
