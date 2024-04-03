#include <Arduino.h>

#include "drivers/dip_switch.h"

namespace sbb {

void DipSwitchConfigure(const DipSwitchPins &dip) {
  for (int pin : dip.pins) {
    pinMode(pin, INPUT_PULLUP);
  }
}

bool DipSwitchGetIndex(const DipSwitchPins &dip, int index) {
  if (index >= kDipSwitchMaxPins) return false;

  if (dip.polarity == DipSwitchPolarity::kActiveHigh) {
    return digitalRead(dip.pins[index]) == HIGH;
  } else {  // DipSwitchPolarity::kActiveLow
    return digitalRead(dip.pins[index]) == LOW;
  }
}

int DipSwitchGet(const DipSwitchPins &dip) {
  int result = 0;
  for (int i = 0; i < dip.number_of_pins; ++i) {
    if (DipSwitchGetIndex(dip, i)) {
      result += 1 << i;
    }
  }
  return result;
}

}  // namespace sbb
