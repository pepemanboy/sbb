#ifndef SBB_COMMON_MATH_H
#define SBB_COMMON_MATH_H

namespace sbb {

void IncrementAndWrap(int *x, int min, int max) {
  if (++(*x) > max) *x = min;
}

void DecrementAndWrap(int *x, int min, int max) {
  if (--(*x) < min) *x = max;
}

}  // namespace sbb

#endif  // SBB_COMMON_MATH_H
