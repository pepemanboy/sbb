#ifndef SUMITOMO_SENSOR_SENSOR_H
#define SUMITOMO_SENSOR_SENSOR_H

#include "common/led.h"
#include "common/time_converter.h"
#include "hardware.h"

namespace sbb {
namespace sumitomo_sensor {

class Sensor {
 public:
  Sensor();

  void Setup();
  void Poll();

 private:
  Led led_green_;
  Led led_red_;
  Led led_yellow_;

  TimeConverter time_;
};

}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SUMITOMO_SENSOR_SENSOR_H
