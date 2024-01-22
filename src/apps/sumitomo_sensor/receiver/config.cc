#include "apps/sumitomo_sensor/receiver/config.h"

#include "common/bits.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {
namespace {

template <int N>
uint64_t NodeAddressMask(const int (&bits)[N]) {
  return WriteBits<uint64_t, N>(0, bits);
}

}  // namespace

ReceiverConfig GetConfig() {
  return {.channel = 10, .node_address_mask = NodeAddressMask<2>({10, 11})};
}

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb