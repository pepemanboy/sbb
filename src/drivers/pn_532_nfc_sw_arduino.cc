#include "drivers/pn_532_nfc_sw_arduino.h"
//
#include <Arduino.h>

#include "common/array_size.h"

namespace sbb {
namespace {

constexpr int kReadTimeout_ms = 250;

}  // namespace

Pn532NfcSw::Pn532NfcSw(const Options &options)
    : options_(options),
      software_serial_(options_.rx_pin, options_.tx_pin),
      hsu_(software_serial_),
      nfc_(hsu_) {}

bool Pn532NfcSw::Setup() {
  nfc_.begin();
  const uint32_t versionData = nfc_.getFirmwareVersion();
  if (versionData == 0) {
    return false;
  }

  nfc_.SAMConfig();
  return true;
}

bool Pn532NfcSw::ReadCard(Card &card) {
  uint8_t bytes;
  const bool success = nfc_.readPassiveTargetID(
      PN532_MIFARE_ISO14443A, card.uid, &bytes, kReadTimeout_ms);

  return success && bytes == Card::kUidBytes;
}

bool Pn532NfcSw::IsCardPresent() {
  Card card = {};
  return ReadCard(card);
}

}  // namespace sbb
