#include "apps/sumitomo_sensor/receiver/receiver.h"

#include <stdint.h>

#include "apps/sumitomo_sensor/message_definitions.h"
#include "apps/sumitomo_sensor/receiver/board.h"
#include "apps/sumitomo_sensor/receiver/config.h"
#include "common/array_size.h"
#include "common/bits.h"
#include "common/math.h"
#include "drivers/clock.h"
#include "drivers/console.h"
#include "drivers/debug_arduino.h"
#include "drivers/hc12_antenna_arduino.h"

namespace sbb {
namespace sumitomo_sensor {
namespace receiver {
namespace {

constexpr int64_t kPollNodeInterval_micros = 3000000;           // 3s
constexpr int64_t kBroadcastChannelInterval_micros = 30000000;  // 30s

}  // namespace

Receiver::Receiver()
    : config_(GetConfig()),
      hc12_({kHc12TxPin, kHc12RxPin, kHc12SetPin}),
      poll_node_timer_{kPollNodeInterval_micros},
      channel_broadcast_timer_{kBroadcastChannelInterval_micros} {}

void Receiver::Setup() {
  ConsoleInit();
  // SBB_DEBUG_ENABLE();

  HardwareInit();
  led_.Control(Led::Command::kOn);
}

void Receiver::Poll() {
  const int64_t now_micros = time_.Update(ClockMicros());

  UpdateLed(now_micros);

  if (channel_broadcast_timer_.Poll(now_micros)) {
    BroadcastChannel(now_micros);
  }

  if (poll_node_timer_.Poll(now_micros)) {
    PollNode(now_micros);
  }
}

void Receiver::SetupHc12OrDie(int channel) {
  if (hc12_.Setup(channel) != Status::kOk) {
    HardwareLedSet(false);
    while (1) {
      delay(100);
    }
  }

  led_.Control(Led::Command::kBlink);
}

void Receiver::UpdateLed(int64_t now_micros) {
  HardwareLedSet(led_.Poll(now_micros));
}

void Receiver::PollNode(int64_t now_micros) {
  // Send query to node.
  const uint32_t sequence = node_sequences_[next_node_index_];
  const uint8_t address =
      NthSetBitIndex(config_.node_address_mask, next_node_index_);
  const StatusQueryMessage query = {.sequence = sequence};
  const Span packet = serializer_.Serialize(address, query);
  hc12_.Write(packet);
  SBB_DEBUGF("Querying for node %d", next_node_index_);

  // Wait for response.
  const Span rx = hc12_.ReadBytesUntil(0);
  if (rx.length > 0) {
    ConsolePrintF("dispositivo %d ok", address);

    StatusResponseMessage response;
    if (unpacker_.Unpack(rx.buffer, rx.length) &&
        unpacker_.MaybeFillMessage(&response)) {
      if (response.has_event) {
        const int32_t millis_age =
            (response.micros - response.event.micros) / 1000;
        ConsolePrintF("pulso en dispositivo %d, hace %ld milisegundos", address,
                      millis_age);
        node_sequences_[next_node_index_] = response.event.sequence;
      }
    }
  }

  // Next node.
  IncrementAndWrap(&next_node_index_, 0,
                   CountBits(config_.node_address_mask) - 1);
}

void Receiver::BroadcastChannel(int64_t now_micros) {
  SetupHc12OrDie(kDefaultChannel);

  ConsolePrintF("levantando dispositivos");

  const BroadcastChannelMessage message = config_;
  const Span packet = serializer_.Serialize(kMessageBroadcastAddress, message);
  hc12_.Write(packet);

  SetupHc12OrDie(config_.channel);
}

}  // namespace receiver
}  // namespace sumitomo_sensor
}  // namespace sbb
