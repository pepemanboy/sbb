#include "apps/sumitomo_sensor/node_v2/hardware.h"

#include <Arduino.h>

#include "apps/sumitomo_sensor/node_v2/board.h"
#include "drivers/dip_switch.h"
#include "drivers/gpio.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node_v2 {

void HardwareInit() {
  // LEDs.
  GpioConfigure(kLedGreen);
  GpioConfigure(kLedRed);
  GpioConfigure(kLedYellow);

  GpioSet(kLedGreen, false);
  GpioSet(kLedRed, false);
  GpioSet(kLedYellow, false);

  // DIP switch.
  DipSwitchConfigure(kDipSwitch);
}

void HardwareLedGreenSet(bool state) { GpioSet(kLedGreen, state); }

void HardwareLedRedSet(bool state) { GpioSet(kLedRed, state); }

void HardwareLedYellowSet(bool state) { GpioSet(kLedYellow, state); }

int HardwareDipSwitchGet() { return DipSwitchGet(kDipSwitch); }

}  // namespace node_v2
}  // namespace sumitomo_sensor
}  // namespace sbb
