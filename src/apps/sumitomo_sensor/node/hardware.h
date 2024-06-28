#ifndef SBB_SUMITOMO_SENSOR_NODE_HARDWARE_H
#define SBB_SUMITOMO_SENSOR_NODE_HARDWARE_H

namespace sbb {
namespace sumitomo_sensor {
namespace node {

void HardwareInit(bool use_ir_sensor);

void HardwareLedGreenSet(bool state);
void HardwareLedRedSet(bool state);
void HardwareLedYellowSet(bool state);

bool HardwareIrSensorGet();

int HardwareDipSwitchGet();

}  // namespace node
}  // namespace sumitomo_sensor
}  // namespace sbb

#endif  // SBB_SUMITOMO_SENSOR_NODE_HARDWARE_H
