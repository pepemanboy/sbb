#ifndef SBB_DRIVERS_HC12_ANTENNA_ARDUINO_H
#define SBB_DRIVERS_HC12_ANTENNA_ARDUINO_H

#include "SoftwareSerial.h"
#include "common/span.h"
#include "common/status.h"

namespace sbb {

class Hc12Antenna {
 public:
  struct Options {
    int tx_pin;
    int rx_pin;
    int set_pin;
  };

  explicit Hc12Antenna(Options options)
      : options_(options), hc12_serial_(options_.rx_pin, options_.tx_pin){};

  Status Setup(int channel);
  void Write(Span message);
  bool IsReadAvailable();
  Span ReadBytesUntil(char character);

 private:
  Status ConfigureParameter(char* query);
  Status SetupOneTime(int channel);

  Options options_;
  SoftwareSerial hc12_serial_;

  uint8_t rx_buffer_[50];
  int rx_buffer_length_ = 0;

  int channel_ = 0;
};

}  // namespace sbb

#endif  // SBB_DRIVERS_HC12_ANTENNA_ARDUINO_H
