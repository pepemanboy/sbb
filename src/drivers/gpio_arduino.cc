#include "drivers/gpio.h"

#include <Arduino.h>

namespace sbb {

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

}  // namespace sbb
