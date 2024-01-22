#ifndef SBB_COMMON_BITS_H
#define SBB_COMMON_BITS_H

namespace sbb {
namespace bits {

template <typename T>
constexpr T SingleBit(int bit) {
  return T(1) << bit;
}

template <typename T>
constexpr bool ReadBit(T bitmask, int bit) {
  return bitmask & SingleBit<T>(bit);
}

template <typename T>
constexpr T WriteBit(T bitmask, int bit) {
  return bitmask | SingleBit<T>(bit);
}

template <typename T, int N>
T WriteBits(T bitmask, const int (&bits)[N]) {
  for (int i = 0; i < N; ++i) {
    bitmask = WriteBit<T>(bitmask, bits[i]);
  }
  return bitmask;
}

template <typename T>
int CountBits(T bitmask) {
  int n = 0;
  for (int i = 0; i < static_cast<int>(sizeof(T)) * 8; ++i) {
    if (ReadBit<T>(bitmask, i)) ++n;
  }
  return n;
}

template <typename T>
int NthSetBitIndex(T bitmask, int n) {
  int set_bits = 0;
  for (int i = 0; i < static_cast<int>(sizeof(T)) * 8; ++i) {
    if (ReadBit<T>(bitmask, i)) {
      ++set_bits;
      if (set_bits == n + 1) return i;
    }
  }
  return -1;
}

}  // namespace bits
}  // namespace sbb

#endif  // SBB_COMMON_BITS_H
