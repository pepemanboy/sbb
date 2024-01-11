#ifndef SBB_COMMON_ARRAY_SIZE_H
#define SBB_COMMON_ARRAY_SIZE_H

namespace sbb {
namespace array_size_internal {

template <typename T, int N>
constexpr int ArraySize(const T (&array)[N]) {
  return N;
}

}  // namespace array_size_internal
}  // namespace sbb

#define SBB_ARRAYSIZE(arr) sbb::array_size_internal::ArraySize(arr)

#endif  // SBB_COMMON_ARRAY_SIZE_H
