#include <Arduino.h>

#include "drivers/gpio.h"

namespace sbb {
namespace {

int ArduinoInterruptTriggerMode(GpioInterruptTrigger trigger) {
  switch (trigger) {
    case GpioInterruptTrigger::kLow:
      return LOW;
    case GpioInterruptTrigger::kChange:
      return CHANGE;
    case GpioInterruptTrigger::kRisingEdge:
      return RISING;
    case GpioInterruptTrigger::kFallingEdge:
      return FALLING;
    case GpioInterruptTrigger::kHigh:
      return HIGH;
  }
}

}  // namespace

void GpioConfigure(const GpioPin &gpio) {
  switch (gpio.mode) {
    case GpioMode::kInput:
      pinMode(gpio.pin, INPUT);
      break;
    case GpioMode::kOutput:
      pinMode(gpio.pin, OUTPUT);
      break;
  }
}

void GpioSet(const GpioPin &gpio, bool state) {
  if (gpio.polarity == GpioPolarity::kActiveHigh) {
    digitalWrite(gpio.pin, state ? HIGH : LOW);
  } else {  // GpioPolarity::kActiveLow
    digitalWrite(gpio.pin, state ? LOW : HIGH);
  }
}

bool GpioGet(const GpioPin &gpio) {
  if (gpio.polarity == GpioPolarity::kActiveHigh) {
    return digitalRead(gpio.pin) == HIGH;
  } else {  // GpioPolarity::kActiveLow
    return digitalRead(gpio.pin) == LOW;
  }
}

void GpioAttachInterrupt(const GpioPin &gpio, GpioInterruptTrigger trigger,
                         GpioInterruptCallback callback) {
  attachInterrupt(digitalPinToInterrupt(gpio.pin), callback,
                  ArduinoInterruptTriggerMode(trigger));
}

}  // namespace sbb
