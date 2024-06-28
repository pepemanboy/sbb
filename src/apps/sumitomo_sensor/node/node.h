#ifndef SBB_SUMITOMO_SENSOR_NODE_NODE_H
#define SBB_SUMITOMO_SENSOR_NODE_NODE_H

#include "apps/sumitomo_sensor/event.h"
#include "apps/sumitomo_sensor/node/hardware.h"
#include "apps/sumitomo_sensor/node/sensor.h"
#include "common/circular_buffer.h"
#include "common/debounce.h"
#include "common/led.h"
#include "common/message.h"
#include "common/time_converter.h"
#include "common/timer.h"
#include "drivers/hc12_antenna_arduino.h"
#include "drivers/pn_532_nfc_arduino.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node {

class Node {
 public:
  struct Options {
    enum SensorType {
      kIrSensor,
      kNfcSensor,
    };
    SensorType sensor_type;
  };

  Node(const Options &options);

  void Setup();
  void Poll();

 private:
  void SetupHc12OrDie(int channel);
  void SetupNfcOrDie();

  bool GetSensorRawReading();

  void UpdateLeds(int64_t now_micros);
  void ReadSensor(int64_t now_micros);
  void HandleMessages(int64_t now_micros);

  bool MaybeProcessStatusQueryMessage(int64_t now_micros);

  const Options options_;

  Led led_green_;
  Led led_red_;
  Led led_yellow_;

  Sensor sensor_;

  uint8_t node_id_ = 0;

  TimeConverter time_;
  Hc12Antenna hc12_;

  Pn532Nfc nfc_;

  CircularBuffer<Event, 20> events_ = {};

  MessageSerializer serializer_;
  MessageUnpacker unpacker_;

  uint32_t event_sequence_ = 0;

  Timer setup_timer_;
};

}  // namespace node
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_NODE_H
