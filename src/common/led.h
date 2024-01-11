#ifndef SBB_COMMON_LED_H
#define SBB_COMMON_LED_H

#include <stdint.h>

namespace sbb {

class Led {
 public:
  enum class Command {
    kOn,
    kOff,
    kToggle,
    kBlink,
  };

  Led() {}

  // Returns `state_`.
  bool Poll(int64_t micros);

  void Control(Command command, int64_t blink_period_ms = 500000);
  bool state() { return state_; }

 private:
  bool state_ = false;
  int64_t blink_period_micros_ = 0;
  int64_t blink_timestamp_micros_ = 0;
};

};  // namespace sbb

#endif  // SBB_COMMON_LED_H
