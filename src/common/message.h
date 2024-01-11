#ifndef SBB_COMMON_MESSAGE_H
#define SBB_COMMON_MESSAGE_H

#include "stdint.h"

#include "common/span.h"
#include "drivers/debug_arduino.h"
#include "external/ciropkt/ciropkt.h"
#include "external/ciropkt/result.h"

namespace sbb {

constexpr int kMessageBroadcastAddress = 255;

class MessageSerializer {
 public:
  template <typename Message>
  Span Serialize(uint8_t address, const Message &message) {
    packet_.address = address;
    packet_.command = Message::kId;
    pktUpdate(&packet_, reinterpret_cast<const uint8_t *>(&message),
              sizeof(Message));
    pktRefresh(&packet_);
    int len = sizeof(buffer_);
    pktSerialize(&packet_, buffer_, &len);
    return {buffer_, len};
  }

 private:
  uint8_t buffer_[255];
  packet_t packet_;
};

class MessageUnpacker {
 public:
  MessageUnpacker() : MessageUnpacker(0) {}
  explicit MessageUnpacker(uint8_t address) : address_(address) {}

  bool Unpack(uint8_t *buffer, int buffer_length) {
    pkt_res_t r = pktDeserialize(&packet_, buffer, buffer_length);
    if (r != pkt_Ok) {
      SBB_DEBUG(F("Deserialize error"));
      return false;
    }

    if (!pktCheck(&packet_)) {
      SBB_DEBUG(F("CRC error"));
      return false;
    }

    if (packet_.address != address_ &&
        packet_.address != kMessageBroadcastAddress) {
      return false;
    }

    return true;
  }

  template <typename Message>
  bool MaybeFillMessage(Message *message) {
    if (packet_.command != Message::kId) {
      return false;
    }

    if (packet_.data_size != sizeof(Message)) {
      SBB_DEBUG(F("Wrong size"));
      return false;
    }

    memcpy(message, packet_.data, sizeof(Message));
    return true;
  }

  void set_address(uint8_t address) { address_ = address; }

 private:
  uint8_t address_;
  packet_t packet_;
};

}  // namespace sbb

#endif  // SBB_COMMON_MESSAGE_H
