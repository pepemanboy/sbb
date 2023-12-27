#include <Arduino.h>

#include "drivers/clock.h"

namespace sbb {

uint32_t ClockMicros() { return micros(); }

}  // namespace sbb
