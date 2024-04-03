#include "drivers/pn_532_nfc_arduino.h"
//
#include <Arduino.h>

#include "common/array_size.h"
#include "drivers/debug_arduino.h"

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

  int retries = 0;
  while (!SetupOneTime()) {
    if (retries++ > 3) {
      SBB_DEBUG(F("Could not configure PN532"));
      return false;
    } else {
      SBB_DEBUG(F("Retrying setup PN532"));
      delay(1000);
    }
  }
  return true;
}

bool Pn532Nfc::SetupOneTime() {
  const uint32_t versionData = nfc_.getFirmwareVersion();
  if (versionData == 0) {
    SBB_DEBUGF("Could not read PN532 version");
    return false;
  }

  nfc_.SAMConfig();
  SBB_DEBUGF("PN532 setup complete");
  return true;
}

bool Pn532Nfc::ReadCard(Card &card) {
  nfc_.SAMConfig();

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
