#include "common/led.h"

#include <Arduino.h>

namespace sbb {

bool Led::Poll(int64_t micros) {
  if (blink_period_micros_ > 0 &&
      blink_timestamp_micros_ + blink_period_micros_ < micros) {
    blink_timestamp_micros_ = micros;
    state_ = !state_;
  }

  return state_;
}

void Led::Control(Command command, int64_t blink_period_micros) {
  blink_timestamp_micros_ = 0;
  blink_period_micros_ = 0;
  switch (command) {
    case Command::kOn:
      state_ = true;
      break;
    case Command::kOff:
      state_ = false;
      break;
    case Command::kToggle:
      state_ = !state_;
      break;
    case Command::kBlink:
      blink_period_micros_ = blink_period_micros;
      break;
  }
}

}  // namespace sbb
