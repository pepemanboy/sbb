#ifndef SBB_APPS_SUMITOMO_SENSOR_RECEIVER_CONFIG_H
#define SBB_APPS_SUMITOMO_SENSOR_RECEIVER_CONFIG_H

#include "stdint.h"
#include "apps/sumitomo_sensor/message_definitions.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {

struct ReceiverConfig {
  uint8_t receiver_channel;
  uint8_t node_addresses[kMaxNumNodes];
  uint8_t num_nodes;
};

ReceiverConfig GetConfig();

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_APPS_SUMITOMO_SENSOR_RECEIVER_CONFIG_H