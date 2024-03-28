#ifndef SBB_DRIVERS_PN_532_NFC_ARDUINO_H
#define SBB_DRIVERS_PN_532_NFC_ARDUINO_H

#include <Arduino.h>

#include <PN532.h>
#include <PN532_HSU.h>

namespace sbb {

class Pn532Nfc {
 public:
  struct Options {
    HardwareSerial &serial;
  };

  struct Card {
    constexpr static int kUidBytes = 4;
    uint8_t uid[kUidBytes];
  };

  explicit Pn532Nfc(const Options &options);

  bool Setup();
  bool ReadCard(Card &card);
  bool IsCardPresent();

 private:
  const Options options_;

  PN532_HSU hsu_;
  PN532 nfc_;
};

}  // namespace sbb

#endif  // SBB_DRIVERS_PN_532_RFID_ARDUINO_H
