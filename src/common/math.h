#ifndef SBB_COMMON_MATH_H
#define SBB_COMMON_MATH_H

namespace sbb {

void IncrementAndWrap(int *x, int min, int max);

void DecrementAndWrap(int *x, int min, int max);

constexpr int DivideRoundUp(int numerator, int denominator) {
  return numerator / denominator + ((numerator % denominator) > 0 ? 1 : 0);
}

}  // namespace sbb

#endif  // SBB_COMMON_MATH_H
