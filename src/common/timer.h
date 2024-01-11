#ifndef SBB_COMMON_TIMER_H
#define SBB_COMMON_TIMER_H

#include "stdint.h"

#include "common/maybe_valid.h"

namespace sbb {

class Timer {
public:
  explicit Timer(int64_t period_micros): period_micros_(period_micros) {}

  bool Poll(int64_t micros) {
    if (!next_trigger_micros_.valid) {
      next_trigger_micros_ = MakeValid(micros);
    }

    if (micros >= next_trigger_micros_.value) {
      next_trigger_micros_.value = micros + period_micros_;
      return true;
    }

    return false;
  }

private:
  const int64_t period_micros_;
  MaybeValid<int64_t> next_trigger_micros_;
};

}

#endif  // SBB_COMMON_TIMER_H