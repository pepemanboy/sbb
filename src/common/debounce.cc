#include "common/debounce.h"

#include <stdint.h>

namespace sbb {

Debounce::Debounce(const int64_t debounce_micros)
    : debounce_micros_(debounce_micros) {}

bool Debounce::Poll(bool state, int64_t micros) {
  if (micros > last_state_change_micros_ + debounce_micros_) {
    if (debounced_state_ != state) {
      debounced_state_ = state;
      last_state_change_micros_ = micros;
    }
  }
  return debounced_state_;
}

}  // namespace sbb
