#include "apps/sumitomo_sensor/receiver/hardware.h"

#include "apps/sumitomo_sensor/receiver/board.h"
#include "drivers/gpio.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {

void HardwareInit() {
  GpioConfigure(kLed);

  GpioSet(kLed, false);
}

void HardwareLedSet(bool state) { GpioSet(kLed, state); }

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb
