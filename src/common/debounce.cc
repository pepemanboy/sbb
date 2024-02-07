#include "common/debounce.h"

#include <stdint.h>

namespace sbb {

Debounce::Debounce(const int64_t debounce_micros)
    : debounce_micros_(debounce_micros) {}

bool Debounce::Poll(bool state, int64_t micros) {
  if (state) {
    last_on_micros_ = micros;
  }

  debounced_state_ = micros < last_on_micros_ + debounce_micros_;
  return debounced_state_;
}

}  // namespace sbb
