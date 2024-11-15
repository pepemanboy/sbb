#ifndef SBB_SUMITOMO_SENSOR_NODE_V3_HARDWARE_H
#define SBB_SUMITOMO_SENSOR_NODE_V3_HARDWARE_H

#include <stdint.h>

namespace sbb {
namespace sumitomo_sensor {
namespace node_v3 {

void HardwareInit();

void HardwareLedGreenSet(bool state);
void HardwareLedRedSet(bool state);
void HardwareLedYellowSet(bool state);

int HardwareDipSwitchGet();

uint32_t HardwareGetInductiveSensorsId();
bool HardwareGetInterruptPin();

}  // namespace node_v3
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_V3_HARDWARE_H
