#ifndef SBB_APPS_SUMITOMO_SENSOR_MESSAGE_DEFINITIONS_H
#define SBB_APPS_SUMITOMO_SENSOR_MESSAGE_DEFINITIONS_H

#include "stdint.h"

#include "common/array_size.h"
#include "event.h"

namespace sbb {
namespace sumitomo_sensor {

constexpr int kDefaultChannel = 1;
constexpr int kReceiverAddress = 0;
constexpr int kMaxNumNodes = 10;

struct StatusQueryMessage {
  static constexpr int kId = 1;

  uint32_t sequence;    
};

struct StatusResponseMessage {
  static constexpr int kId = 2;

  int64_t micros;
  bool has_event;
  Event event;
};

struct BroadcastChannelMessage {
  static constexpr int kId = 3;

  uint8_t channel;
  uint8_t node_addresses[kMaxNumNodes];
  uint8_t num_nodes;
};

}  // sumitomo_sensor
}  // namespace sbb

#endif  // SBB_APPS_SUMITOMO_SENSOR_MESSAGE_DEFINITIONS_H