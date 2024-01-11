#ifndef SBB_SUMITOMO_SENSOR_RECEIVER_HARDWARE_H
#define SBB_SUMITOMO_SENSOR_RECEIVER_HARDWARE_H

#include "stdint.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {

void HardwareInit();

void HardwareLedSet(bool state);

}  // receiver
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_RECEIVER_HARDWARE_H
