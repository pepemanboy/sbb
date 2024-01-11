#ifndef SBB_APPS_SUMITOMO_SENSOR_RECEIVER_HEART_BEATS_H
#define SBB_APPS_SUMITOMO_SENSOR_RECEIVER_HEART_BEATS_H

#include <stdint.h>

#include "apps/sumitomo_sensor/message_definitions.h"
#include "common/maybe_valid.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {

class HeartBeats {
 public:
  struct Config {
    int num_nodes;
    int64_t max_absent_micros;
  };
  explicit HeartBeats(const Config &config) : config_(config) {}

  void SignalNodePresent(int node_index, int64_t micros) {
    if (node_index < 0) return;
    if (node_index > config_.num_nodes) return;
    if (node_index > kMaxNumNodes) return;

    heart_beat_deadline_micros_[node_index] =
        MakeValid(micros + config_.max_absent_micros);
  }

  bool IsNodePresent(int node_index, int64_t micros) {
    return heart_beat_deadline_micros_[node_index].valid &&
           micros < heart_beat_deadline_micros_[node_index].value;
  }

 private:
  const Config config_;
  MaybeValid<int64_t> heart_beat_deadline_micros_[kMaxNumNodes] = {};
};

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_APPS_SUMITOMO_SENSOR_RECEIVER_HEART_BEATS_H
