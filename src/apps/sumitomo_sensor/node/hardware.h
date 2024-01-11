#ifndef SBB_SUMITOMO_SENSOR_NODE_HARDWARE_H
#define SBB_SUMITOMO_SENSOR_NODE_HARDWARE_H

namespace sbb {
namespace sumitomo_sensor {
namespace node {

void HardwareInit();

void HardwareLedGreenSet(bool state);
void HardwareLedRedSet(bool state);
void HardwareLedYellowSet(bool state);

bool HardwareIrSensorGet();

int HardwareDipSwitchGet();

}  // node
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_HARDWARE_H
