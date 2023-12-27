#include "sensor.h"

#include "drivers/clock.h"
#include "drivers/debug_arduino.h"

namespace sbb {
namespace sumitomo_sensor {

Sensor::Sensor() {}

void Sensor::Setup() {
  SBB_DEBUG_ENABLE();
  HardwareInit();

  led_green_.Control(Led::Command::kBlink);
  led_yellow_.Control(Led::Command::kBlink);
  led_red_.Control(Led::Command::kBlink);
}

void Sensor::Poll() {
  const int64_t now_micros = time_.Update(ClockMicros());

  HardwareLedGreenSet(led_green_.Poll(now_micros));
  HardwareLedYellowSet(led_yellow_.Poll(now_micros));
  HardwareLedRedSet(led_red_.Poll(now_micros));
}

}  // namespace sumitomo_sensor
}  // namespace sbb
