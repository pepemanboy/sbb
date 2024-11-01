#ifndef SBB_SUMITOMO_SENSOR_RECEIVER_RECEIVER_H
#define SBB_SUMITOMO_SENSOR_RECEIVER_RECEIVER_H

#include <stdint.h>

#include "apps/sumitomo_sensor/message_definitions.h"
#include "apps/sumitomo_sensor/receiver/config.h"
#include "apps/sumitomo_sensor/receiver/hardware.h"
#include "common/led.h"
#include "common/message.h"
#include "common/time_converter.h"
#include "common/timer.h"
#include "drivers/hc12_antenna_arduino.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {

class Receiver {
 public:
  Receiver();

  void Setup();
  void Poll();

 private:
  void SetupHc12OrDie(int channel);

  void UpdateLed(int64_t now_micros);
  void PollNode(int64_t now_micros);

  uint32_t FormatAddress(uint8_t address);

  const ReceiverConfig config_;

  Led led_;

  TimeConverter time_;
  Hc12Antenna hc12_;  // Init in constructor.

  MessageSerializer serializer_;
  MessageUnpacker unpacker_;

  Timer poll_node_timer_;
  int next_node_index_ = 0;
  uint32_t node_sequences_[kMaxNumNodes] = {};

  Timer setup_timer_;
};

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_RECEIVER_RECEIVER_H
