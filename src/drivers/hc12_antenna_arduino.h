#ifndef SBB_DRIVERS_HC12_ANTENNA_ARDUINO_H
#define SBB_DRIVERS_HC12_ANTENNA_ARDUINO_H

#include <SoftwareSerial.h>

#include "common/span.h"

namespace sbb {

class Hc12Antenna {
 public:
  struct Options {
    int tx_pin;
    int rx_pin;
    int set_pin;
  };

  explicit Hc12Antenna(const Options& options)
      : options_(options), serial_(options_.rx_pin, options_.tx_pin) {}

  bool Setup(int channel);
  void Write(Span message);
  bool IsReadAvailable();
  Span ReadBytesUntil(char character);

 private:
  bool ConfigureParameter(char* query);
  bool SetupOneTime(int channel);

  Options options_;
  SoftwareSerial serial_;

  uint8_t rx_buffer_[50];
  int rx_buffer_length_ = 0;

  int channel_ = 0;
};

}  // namespace sbb

#endif  // SBB_DRIVERS_HC12_ANTENNA_ARDUINO_H
