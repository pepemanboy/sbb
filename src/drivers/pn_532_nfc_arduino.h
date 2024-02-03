#ifndef SBB_DRIVERS_PN_532_NFC_ARDUINO_H
#define SBB_DRIVERS_PN_532_NFC_ARDUINO_H

#include <PN532.h>
#include <PN532_SWHSU.h>
#include <SoftwareSerial.h>

namespace sbb {

class Pn532Nfc {
 public:
  struct Options {
    int tx_pin;
    int rx_pin;
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

  SoftwareSerial serial_;
  PN532_SWHSU hsu_;
  PN532 nfc_;
};

}  // namespace sbb

#endif  // SBB_DRIVERS_PN_532_RFID_ARDUINO_H
