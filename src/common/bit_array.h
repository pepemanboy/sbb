#ifndef SBB_COMMON_BIT_ARRAY_H
#define SBB_COMMON_BIT_ARRAY_H

#include <string.h>

#include "common/bits.h"
#include "common/math.h"

namespace sbb {

template <int Bits>
class BitArray {
 public:
  BitArray() = default;
  BitArray(const BitArray &bit) { memcpy(array_, bit.array_, Nibbles); }

  bool ReadBit(int bit) const {
    int nibble = bit / 8;
    int nibble_bit = bit % 8;
    return bits::ReadBit(array_[nibble], nibble_bit);
  }

  void WriteBit(int bit) {
    int nibble = bit / 8;
    int nibble_bit = bit % 8;
    array_[nibble] = bits::WriteBit(array_[nibble], nibble_bit);
  }

  template <int N>
  void WriteBits(const int (&bits)[N]) {
    for (int i = 0; i < N; ++i) {
      WriteBit(bits[i]);
    }
  }

  int CountBits() const {
    int n = 0;
    for (int nibble = 0; nibble < Nibbles; ++nibble) {
      n += bits::CountBits(array_[nibble]);
    }
    return n;
  }

  int NthSetBitIndex(int n) const {
    int set_bits = 0;
    for (int nibble = 0; nibble < Nibbles; ++nibble) {
      for (int bit = 0; bit < 8; ++bit) {
        if (bits::ReadBit<uint8_t>(array_[nibble], bit)) {
          ++set_bits;
          if (set_bits == n + 1) return nibble * 8 + bit;
        }
      }
    }
    return -1;
  }

 private:
  constexpr static int Nibbles = DivideRoundUp(Bits, 8);
  uint8_t array_[Nibbles] = {};
};

}  // namespace sbb

#endif  // SBB_COMMON_BIT_ARRAY_H
