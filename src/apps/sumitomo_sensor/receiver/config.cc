#include "apps/sumitomo_sensor/receiver/config.h"

#include "common/bit_array.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {
namespace {

template <int N>
BitArray<128> NodeAddressMask(const int (&bits)[N]) {
  BitArray<128> bit_array = {};
  bit_array.WriteBits(bits);
  return bit_array;
}

}  // namespace

ReceiverConfig GetConfig() {
  return {.node_address_mask = NodeAddressMask(
              {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19})};
}

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb
