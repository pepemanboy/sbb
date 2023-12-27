#include "hardware.h"

#include "drivers/gpio.h"

namespace sbb {
namespace sumitomo_sensor {

namespace {

constexpr GpioPin kLedGreen = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 9};
constexpr GpioPin kLedRed = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 7};
constexpr GpioPin kLedYellow = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 8};

}  // namespace

void HardwareInit() {
  GpioConfigure(kLedGreen);
  GpioConfigure(kLedRed);
  GpioConfigure(kLedYellow);

  GpioSet(kLedGreen, false);
  GpioSet(kLedRed, false);
  GpioSet(kLedYellow, false);
}

void HardwareLedGreenSet(bool state) { GpioSet(kLedGreen, state); }

void HardwareLedRedSet(bool state) { GpioSet(kLedRed, state); }

void HardwareLedYellowSet(bool state) { GpioSet(kLedYellow, state); }

}  // namespace sumitomo_sensor
}  // namespace sbb
