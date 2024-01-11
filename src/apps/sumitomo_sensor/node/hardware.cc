#include "apps/sumitomo_sensor/node/hardware.h"

#include <Arduino.h>

#include "apps/sumitomo_sensor/node/board.h"
#include "drivers/dip_switch.h"
#include "drivers/gpio.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node {

void HardwareInit() {
  // LEDs.
  GpioConfigure(kLedGreen);
  GpioConfigure(kLedRed);
  GpioConfigure(kLedYellow);

  GpioSet(kLedGreen, false);
  GpioSet(kLedRed, false);
  GpioSet(kLedYellow, false);

  // IR sensor.
  GpioConfigure(kIrSensor);

  // DIP switch.
  DipSwitchConfigure(kDipSwitch);
}

void HardwareLedGreenSet(bool state) { GpioSet(kLedGreen, state); }

void HardwareLedRedSet(bool state) { GpioSet(kLedRed, state); }

void HardwareLedYellowSet(bool state) { GpioSet(kLedYellow, state); }

bool HardwareIrSensorGet() { return GpioGet(kIrSensor); }

int HardwareDipSwitchGet() { return DipSwitchGet(kDipSwitch); }

}  // namespace node
}  // namespace sumitomo_sensor
}  // namespace sbb
