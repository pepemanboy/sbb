#ifndef SBB_DRIVERS_PN_532_NFC_SW_ARDUINO_H
#define SBB_DRIVERS_PN_532_NFC_SW_ARDUINO_H

#include <Arduino.h>

#include <PN532.h>
#include <PN532_SWHSU.h>

namespace sbb {

class Pn532NfcSw {
 public:
  struct Options {
    int rx_pin;
    int tx_pin;
  };

  struct Card {
    constexpr static int kUidBytes = 4;
    uint8_t uid[kUidBytes];
  };

  explicit Pn532NfcSw(const Options &options);

  bool Setup();
  bool ReadCard(Card &card);
  bool IsCardPresent();

 private:
  const Options options_;

  SoftwareSerial software_serial_;
  PN532_SWHSU hsu_;
  PN532 nfc_;
};

}  // namespace sbb

#endif  // SBB_DRIVERS_PN_532_RFID_ARDUINO_H
