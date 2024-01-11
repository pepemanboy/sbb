#ifndef SBB_SUMITOMO_SENSOR_RECEIVER_BOARD_H
#define SBB_SUMITOMO_SENSOR_RECEIVER_BOARD_H

#include "drivers/gpio.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {

constexpr int kHc12TxPin = 10;
constexpr int kHc12RxPin = 11;
constexpr int kHc12SetPin = 12;

constexpr GpioPin kLed = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 13};

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_RECEIVER_BOARD_H
