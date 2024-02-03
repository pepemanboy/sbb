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
  return {.channel = 10,
          .node_address_mask = NodeAddressMask(
              {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73})};
}

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb
