#include "drivers/pn_532_nfc_arduino.h"
//
#include <Arduino.h>

#include "common/array_size.h"

namespace sbb {
namespace {

constexpr int kReadTimeout_ms = 250;

}  // namespace

Pn532Nfc::Pn532Nfc(const Options &options)
    : options_(options),
      hsu_(options_.serial),
      nfc_(hsu_) {}

bool Pn532Nfc::Setup() {
  nfc_.begin();
  const uint32_t versionData = nfc_.getFirmwareVersion();
  if (versionData == 0) {
    return false;
  }

  nfc_.SAMConfig();
  return true;
}

bool Pn532Nfc::ReadCard(Card &card) {
  uint8_t bytes;
  const bool success = nfc_.readPassiveTargetID(
      PN532_MIFARE_ISO14443A, card.uid, &bytes, kReadTimeout_ms);

  return success && bytes == Card::kUidBytes;
}

bool Pn532Nfc::IsCardPresent() {
  Card card = {};
  return ReadCard(card);
}

}  // namespace sbb
