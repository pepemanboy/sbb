#ifndef SBB_APPS_SUMITOMO_SENSOR_EVENT_H
#define SBB_APPS_SUMITOMO_SENSOR_EVENT_H

#include <stdint.h>

namespace sbb {
namespace sumitomo_sensor {

struct Event {
  enum class Type {
    kRisingEdge,
    kFallingEdge,
  };
  Type type;
  int64_t micros;
  uint32_t sequence;
};

}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_APPS_SUMITOMO_SENSOR_EVENT_H
