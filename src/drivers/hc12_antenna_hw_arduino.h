#ifndef SBB_DRIVERS_HC12_ANTENNA_HW_ARDUINO_H
#define SBB_DRIVERS_HC12_ANTENNA_HW_ARDUINO_H

#include <Arduino.h>

#include "common/span.h"

namespace sbb {

class Hc12AntennaHw {
 public:
  struct Options {
    HardwareSerial &serial;
    int set_pin;
  };

  explicit Hc12AntennaHw(const Options& options)
      : options_(options), serial_(options_.serial){}

  bool Setup(int channel);
  void Write(Span message);
  bool IsReadAvailable();
  Span ReadBytesUntil(char character);

 private:
  bool ConfigureParameter(char* query);
  bool SetupOneTime(int channel);

  Options options_;
  HardwareSerial &serial_;

  uint8_t rx_buffer_[50];
  int rx_buffer_length_ = 0;

  int channel_ = 0;
};

}  // namespace sbb

#endif  // SBB_DRIVERS_HC12_ANTENNA_HW_ARDUINO_H
