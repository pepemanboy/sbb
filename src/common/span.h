#ifndef SBB_COMMON_SPAN_H
#define SBB_COMMON_SPAN_H

#include "stdint.h"

namespace sbb {

struct Span {
  uint8_t *buffer;
  int length;
};

}  // namespace sbb

#endif  // SBB_COMMON_SPAN_H
