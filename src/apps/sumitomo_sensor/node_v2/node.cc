#include <Arduino.h>

#include "apps/sumitomo_sensor/event.h"
#include "apps/sumitomo_sensor/message_definitions.h"
#include "apps/sumitomo_sensor/node_v2/board.h"
#include "apps/sumitomo_sensor/node_v2/hardware.h"
#include "apps/sumitomo_sensor/node_v2/node.h"
#include "apps/sumitomo_sensor/node_v2/sensor.h"
#include "common/bit_array.h"
#include "drivers/clock.h"
#include "drivers/console.h"
#include "drivers/debug_arduino.h"
#include "drivers/hc12_antenna_hw_arduino.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node_v2 {
namespace {

constexpr int64_t kSetupInterval_micros = 61000000;  // 61s

Sensor::Options GetSensorOptions() {
  return {.debounce_micros = 5000000};
}

}  // namespace

Node::Node()
    : sensor_(GetSensorOptions()),
      hc12_(Hc12AntennaHw::Options{*kHc12Serial, kHc12SetPin}),
      setup_timer_(kSetupInterval_micros) {}

void Node::Setup() {
  // SBB_DEBUG_ENABLE();
  HardwareInit();

  // Read DIP switch to configure node ID.
  node_id_ = HardwareDipSwitchGet();
  unpacker_.set_address(node_id_);
  SBB_DEBUGF("Node ID: %d", node_id_);
}

void Node::Poll() {
  const int64_t now_micros = time_.Update(ClockMicros());

  UpdateLeds(now_micros);

  if (setup_timer_.Poll(now_micros)) {
    SetupHc12OrDie(kReceiverNodeComboChannel);
  }

  ReadSensor(now_micros);
  HandleMessages(now_micros);

  // Throttle main loop.
  delay(10);
}

void Node::SetupHc12OrDie(int channel) {
  HardwareLedGreenSet(true);
  if (!hc12_.Setup(channel)) {
    HardwareLedGreenSet(false);
    HardwareLedYellowSet(false);
    HardwareLedRedSet(true);
    while (1) {
      delay(100);
    }
  }

  led_green_.Control(Led::Command::kBlink);
}

void Node::UpdateLeds(int64_t now_micros) {
  HardwareLedGreenSet(led_green_.Poll(now_micros));
  HardwareLedYellowSet(led_yellow_.Poll(now_micros));
  HardwareLedRedSet(led_red_.Poll(now_micros));
}

bool Node::GetSensorRawReading() {
  return HardwareGetInductiveSensor();
}

void Node::ReadSensor(int64_t now_micros) {
  const bool rising_edge_detected =
      sensor_.Poll(GetSensorRawReading(), now_micros);
  led_yellow_.Control(sensor_.debounced_state() ? Led::Command::kOn
                                                : Led::Command::kOff);

  if (rising_edge_detected) {
    events_.PushAndMaybeEvict(
        {.micros = now_micros, .sequence = ++event_sequence_});
    SBB_DEBUGF("Card detected");
  }
}

void Node::HandleMessages(int64_t now_micros) {
  if (!hc12_.IsReadAvailable()) return;

  const Span rx = hc12_.ReadBytesUntil(0);
  if (unpacker_.Unpack(rx.buffer, rx.length)) {
    if (MaybeProcessStatusQueryMessage(now_micros)) return;
  }
}

bool Node::MaybeProcessStatusQueryMessage(int64_t now_micros) {
  StatusQueryMessage query;
  if (!unpacker_.MaybeFillMessage(&query)) return false;

  StatusResponseMessage status = {};

  if (events_.AvailablePop() > 0) {
    const uint32_t current_sequence = events_.Peek().sequence;
    if (query.sequence == current_sequence) {
      events_.Pop();
    }
    if (events_.AvailablePop() > 0) {
      status.has_event = true;
      status.event = events_.Peek();
      status.micros = now_micros;
    }
  }

  const Span packet = serializer_.Serialize(kReceiverAddress, status);
  hc12_.Write(packet);
  return true;
}

}  // namespace node_v2
}  // namespace sumitomo_sensor
}  // namespace sbb
