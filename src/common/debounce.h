#ifndef SBB_COMMON_DEBOUNCE_H
#define SBB_COMMON_DEBOUNCE_H

#include "stdio.h"

namespace sbb {

class Debounce {
 public:
  explicit Debounce(int64_t debounce_micros = 500000);

  // Returns `debounced_state_`.
  bool Poll(bool state, int64_t micros);

  bool debounced_state() { return debounced_state_; }

 private:
  int64_t debounce_micros_;  // Init in constructor.
  bool debounced_state_ = false;
  int64_t last_state_change_micros_ = 0;
};

}  // namespace sbb

#endif  // SBB_COMMON_DEBOUNCE_H
