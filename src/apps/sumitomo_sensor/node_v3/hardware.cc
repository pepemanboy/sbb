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

  const uint8_t pinb = PINB;
  const uint8_t pinh = PINH;
  const uint8_t pine = PINE;
  const uint8_t ping = PING;

  const bool sensors[] = {
    // Sensor 0 - pin 10 - B4.
    bits::ReadBit(pinb, 4),
    // Sensor 1 - pin 13 - B7.
    bits::ReadBit(pinb, 7),
    // Sensor 2 - pin 12 - B6.
    bits::ReadBit(pinb, 6),
    // Sensor 3 - pin 11 - B5.
    bits::ReadBit(pinb, 5),
    // Sensor 4 - pin 8 - H5.
    bits::ReadBit(pinh, 5),
    // Sensor 5 - pin 6 - H3.
    bits::ReadBit(pinh, 3),
    // Sensor 6 - pin 3 - E5.
    bits::ReadBit(pine, 5),
    // Sensor 7 - pin 4 - G5.
    bits::ReadBit(ping, 5),
    // Sensor 8 - pin 7 - H4.
    bits::ReadBit(pinh, 4),
    // Sensor 9 - pin 9 - H6.
    bits::ReadBit(pinh, 6),
  };

  // Only sensors 1 .. 8 are used for ID.
  for (int i = 1; i < SBB_ARRAYSIZE(kInductiveSensors) - 1; ++i) {
    if (!sensors[i]) {
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
