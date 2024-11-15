#include "apps/sumitomo_sensor/node_v3/hardware.h"

#include <stdint.h>
#include <Arduino.h>

#include "apps/sumitomo_sensor/node_v3/board.h"
#include "drivers/dip_switch.h"
#include "drivers/gpio.h"
#include "common/bits.h"
#include "common/array_size.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node_v3 {

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

  // Inductive sensors.
  for (const auto &gpio : kInductiveSensors){
     GpioConfigure(gpio);
  }

  // Interrupt pin.
  GpioConfigure(kInterruptPin);
}

void HardwareLedGreenSet(bool state) { GpioSet(kLedGreen, state); }

void HardwareLedRedSet(bool state) { GpioSet(kLedRed, state); }

void HardwareLedYellowSet(bool state) { GpioSet(kLedYellow, state); }

int HardwareDipSwitchGet() { return DipSwitchGet(kDipSwitch); }

uint32_t HardwareGetInductiveSensorsId() {
  int id = 0;
  // Only sensors 1 .. 8 are used for ID.
  for (int i = 1; i < SBB_ARRAYSIZE(kInductiveSensors) - 1; ++i) {
    if (GpioGet(kInductiveSensors[i])) {
      id |= bits::SingleBit<uint32_t>(i - 1);
    }
  }
  return id;
}

bool HardwareGetInterruptPin() {
  return GpioGet(kInterruptPin);
}

}  // namespace node_v3
}  // namespace sumitomo_sensor
}  // namespace sbb
