#include "common/math.h"

namespace sbb {

void IncrementAndWrap(int *x, int min, int max) {
  if (++(*x) > max) *x = min;
}

void DecrementAndWrap(int *x, int min, int max) {
  if (--(*x) < min) *x = max;
}

}  // namespace sbb
