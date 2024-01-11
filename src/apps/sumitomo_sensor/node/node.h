#ifndef SBB_SUMITOMO_SENSOR_NODE_NODE_H
#define SBB_SUMITOMO_SENSOR_NODE_NODE_H

#include "apps/sumitomo_sensor/event.h"
#include "apps/sumitomo_sensor/node/hardware.h"
#include "apps/sumitomo_sensor/node/ir_sensor.h"
#include "common/circular_buffer.h"
#include "common/debounce.h"
#include "common/led.h"
#include "common/message.h"
#include "common/time_converter.h"
#include "drivers/hc12_antenna_arduino.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node {

class Node {
 public:
  Node();

  void Setup();
  void Poll();

 private:
  void SetupHc12OrDie(int channel);

  void UpdateLeds(int64_t now_micros);
  void ReadIrSensor(int64_t now_micros);
  void HandleMessages (int64_t now_micros);

  bool MaybeProcessStatusQueryMessage(int64_t now_micros);
  bool MaybeProcessBroadcastChannelMessage(int64_t now_micros);

  Led led_green_;
  Led led_red_;
  Led led_yellow_;

  IrSensor ir_sensor_;

  int node_id_ = 0;

  TimeConverter time_;
  Hc12Antenna hc12_;

  CircularBuffer<Event, 20> events_ = {};

  MessageSerializer serializer_;
  MessageUnpacker unpacker_;

  uint32_t event_sequence_ = 0;
};

}  // namespace node
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_NODE_H
