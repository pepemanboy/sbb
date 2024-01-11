#ifndef SBB_APPS_SUMITOMO_SENSOR_EVENT_H
#define SBB_APPS_SUMITOMO_SENSOR_EVENT_H

#include "stdint.h"

namespace sbb {
namespace sumitomo_sensor {

struct Event {
  int64_t micros;
  uint32_t sequence;
};

}  // sbb
}  // sumitomo sensor

#endif  // SBB_APPS_SUMITOMO_SENSOR_EVENTS_H
