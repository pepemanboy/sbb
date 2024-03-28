#ifndef SBB_APPS_SUMITOMO_SENSOR_NODE_V2_SENSOR_H
#define SBB_APPS_SUMITOMO_SENSOR_NODE_V2_SENSOR_H

#include "common/debounce.h"
#include "common/rising_edge_detector.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node_v2 {

class Sensor {
 public:
  struct Options {
    int64_t debounce_micros;
  };

  explicit Sensor(const Options &options): debounce_(options.debounce_micros){}

  // Returns true on debounced `reading` rising edge.
  bool Poll(bool reading, int64_t micros) {
    const bool debounced_state = debounce_.Poll(reading, micros);
    return rising_edge_detector_.Update(debounced_state);
  }

  bool debounced_state() { return debounce_.debounced_state(); }

 private:
  Debounce debounce_;
  RisingEdgeDetector rising_edge_detector_;
};

}  // namespace node_v2
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_APPS_SUMITOMO_SENSOR_NODE_V2_SENSOR_H
