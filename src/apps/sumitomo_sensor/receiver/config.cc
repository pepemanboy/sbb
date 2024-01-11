#include "apps/sumitomo_sensor/receiver/config.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {

ReceiverConfig GetConfig() {
  return {
      .receiver_channel = 10,
      .node_addresses = {10, 11},
      .num_nodes = 2,
  };
}

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb