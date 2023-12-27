#ifndef SUMITOMO_SENSOR_HARDWARE_H
#define SUMITOMO_SENSOR_HARDWARE_H

#include "stdint.h"

namespace sbb {
namespace sumitomo_sensor {

void HardwareInit();

void HardwareLedGreenSet(bool state);
void HardwareLedRedSet(bool state);
void HardwareLedYellowSet(bool state);

}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SUMITOMO_SENSOR_HARDWARE_H
