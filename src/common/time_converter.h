#ifndef SBB_COMMON_TIME_CONVERTER_H
#define SBB_COMMON_TIME_CONVERTER_H

#include <stdint.h>

namespace sbb {

class TimeConverter {
 public:
  TimeConverter() = default;
  int64_t Update(uint32_t u32_micros) {
    i64_micros_ += u32_micros - last_u32_micros_;
    last_u32_micros_ = u32_micros;
    return i64_micros_;
  }

 private:
  uint32_t last_u32_micros_ = 0;
  int64_t i64_micros_ = 0;
};

}  // namespace sbb

#endif  // SBB_COMMON_TIME_CONVERTER_H
