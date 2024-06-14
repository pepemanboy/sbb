#ifndef SBB_SUMITOMO_SENSOR_NODE_V2_HARDWARE_H
#define SBB_SUMITOMO_SENSOR_NODE_V2_HARDWARE_H

namespace sbb {
namespace sumitomo_sensor {
namespace node_v2 {

void HardwareInit();

void HardwareLedGreenSet(bool state);
void HardwareLedRedSet(bool state);
void HardwareLedYellowSet(bool state);

int HardwareDipSwitchGet();

bool HardwareGetInductiveSensor();

}  // node_v2
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_V2_HARDWARE_H
