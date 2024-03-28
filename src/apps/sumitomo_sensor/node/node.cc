#include <Arduino.h>

#include "apps/sumitomo_sensor/event.h"
#include "apps/sumitomo_sensor/message_definitions.h"
#include "apps/sumitomo_sensor/node/board.h"
#include "apps/sumitomo_sensor/node/hardware.h"
#include "apps/sumitomo_sensor/node/node.h"
#include "apps/sumitomo_sensor/node/sensor.h"
#include "common/bit_array.h"
#include "drivers/clock.h"
#include "drivers/console.h"
#include "drivers/debug_arduino.h"
#include "drivers/hc12_antenna_arduino.h"

namespace sbb {
namespace sumitomo_sensor {
namespace node {
namespace {

Sensor::Options GetSensorOptions(Node::Options::SensorType sensor_type) {
  switch (sensor_type) {
    case Node::Options::SensorType::kIrSensor:
      return {.debounce_micros = 500000};
    case Node::Options::SensorType::kNfcSensor:
      return {.debounce_micros = 5000000};
    default:
      return {};
  }
}

}  // namespace

Node::Node(const Options &options)
    : options_(options),
      sensor_(GetSensorOptions(options_.sensor_type)),
      hc12_(Hc12Antenna::Options{kHc12TxPin, kHc12RxPin, kHc12SetPin}),
      nfc_(Pn532Nfc::Options{Serial}) {}

void Node::Setup() {
  // SBB_DEBUG_ENABLE();
  HardwareInit(options_.sensor_type == Options::SensorType::kIrSensor);

  HardwareLedGreenSet(true);
  SetupHc12OrDie(kDefaultChannel);

  if (options_.sensor_type == Options::SensorType::kNfcSensor) {
    SetupNfcOrDie();
  }

  // Read DIP switch to configure node ID.
  node_id_ = HardwareDipSwitchGet();
  unpacker_.set_address(node_id_);
  SBB_DEBUGF("Node ID: %d", node_id_);
}

void Node::Poll() {
  const int64_t now_micros = time_.Update(ClockMicros());

  UpdateLeds(now_micros);
  ReadSensor(now_micros);
  HandleMessages(now_micros);

  // Throttle main loop.
  delay(10);
}

void Node::SetupNfcOrDie() {
  if (!nfc_.Setup()) {
    HardwareLedGreenSet(false);
    HardwareLedYellowSet(true);
    HardwareLedRedSet(true);
    while (1) {
      delay(100);
    }
  }
}

void Node::SetupHc12OrDie(int channel) {
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
  switch (options_.sensor_type) {
    case Options::SensorType::kIrSensor:
      return HardwareIrSensorGet();
    case Options::SensorType::kNfcSensor:
      return nfc_.IsCardPresent();
    default:
      return false;
  }
}

void Node::ReadSensor(int64_t now_micros) {
  const bool rising_edge_detected =
      sensor_.Poll(GetSensorRawReading(), now_micros);
  led_yellow_.Control(sensor_.debounced_state() ? Led::Command::kOn
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

  if (message.node_address_mask.ReadBit(node_id_)) {
    SetupHc12OrDie(message.channel);
  }

  return true;
}

}  // namespace node
}  // namespace sumitomo_sensor
}  // namespace sbb
