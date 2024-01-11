#include "apps/sumitomo_sensor/node/node.h"

#include "apps/sumitomo_sensor/event.h"
#include "apps/sumitomo_sensor/message_definitions.h"
#include "apps/sumitomo_sensor/node/board.h"
#include "apps/sumitomo_sensor/node/hardware.h"
#include "drivers/clock.h"
#include "drivers/console.h"
#include "drivers/debug_arduino.h"
#include "drivers/hc12_antenna_arduino.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node {

Node::Node()
    : hc12_(Hc12Antenna::Options{kHc12TxPin, kHc12RxPin, kHc12SetPin}) {}

void Node::Setup() {
  SBB_DEBUG_ENABLE();
  HardwareInit();

  HardwareLedGreenSet(true);
  SetupHc12OrDie(kDefaultChannel);

  // Read DIP switch to configure node ID.
  node_id_ = HardwareDipSwitchGet();
  unpacker_.set_address(node_id_);
  SBB_DEBUGF("Node ID: %d", node_id_);
}

void Node::Poll() {
  const int64_t now_micros = time_.Update(ClockMicros());

  UpdateLeds(now_micros);
  ReadIrSensor(now_micros);
  HandleMessages(now_micros);

  // Throttle main loop.
  delay(10);
}

void Node::SetupHc12OrDie(int channel) {
  if (hc12_.Setup(channel) != Status::kOk) {
    HardwareLedGreenSet(false);
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

void Node::ReadIrSensor(int64_t now_micros) {
  const bool rising_edge_detected =
      ir_sensor_.Poll(HardwareIrSensorGet(), now_micros);
  led_yellow_.Control(ir_sensor_.debounced_state() ? Led::Command::kOn
                                                   : Led::Command::kOff);

  if (rising_edge_detected) {
    events_.PushAndMaybeEvict(
        {.micros = now_micros, .sequence = ++event_sequence_});
  }
}

void Node::HandleMessages(int64_t now_micros) {
  if (!hc12_.IsReadAvailable()) return;

  const Span rx = hc12_.ReadBytesUntil(0);
  if (unpacker_.Unpack(rx.buffer, rx.length)) {
    if (MaybeProcessStatusQueryMessage(now_micros)) return;
    if (MaybeProcessBroadcastChannelMessage(now_micros)) return;
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

bool Node::MaybeProcessBroadcastChannelMessage(int64_t now_micros) {
  BroadcastChannelMessage message;
  if (!unpacker_.MaybeFillMessage(&message)) return false;

  for (int i = 0; i < message.num_nodes; ++i) {
    if (message.node_addresses[i] == node_id_) {
      SetupHc12OrDie(message.channel);
      break;
    }
  }

  return true; 
}

}  // namespace node
}  // namespace sumitomo_sensor
}  // namespace sbb
