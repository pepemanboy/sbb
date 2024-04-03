#include "drivers/hc12_antenna_hw_arduino.h"

#include <Arduino.h>

#include "common/span.h"
#include "drivers/debug_arduino.h"

namespace sbb {
namespace {

constexpr int kDefaultBaudRate = 9600;
constexpr int kSerialTimeout_ms = 1000;
constexpr int kMaxSetupRetries = 3;

}  // namespace

bool Hc12AntennaHw::ConfigureParameter(char *query) {
  SBB_DEBUG(query);
  serial_.println(query);
  serial_.flush();

  const size_t l = serial_.readBytes(rx_buffer_, sizeof(rx_buffer_));
  rx_buffer_[l] = '\0';
  SBB_DEBUG((char *)rx_buffer_);

  if (!strstr((char *)rx_buffer_, "OK")) {
    SBB_DEBUG(F("Error configuring parameter"));
    return false;
  }
  return true;
}

bool Hc12AntennaHw::Setup(int channel) {
  serial_.setTimeout(kSerialTimeout_ms);
  serial_.begin(kDefaultBaudRate);

  int retries = 0;
  while (!SetupOneTime(channel)) {
    if (retries++ > kMaxSetupRetries) {
      SBB_DEBUG(F("Could not configure"));
      return false;
    } else {
      SBB_DEBUG(F("Retrying"));
      delay(1000);
    }
  }
  return true;
}

bool Hc12AntennaHw::SetupOneTime(int channel) {
  pinMode(options_.set_pin, OUTPUT);
  delay(250);

  SBB_DEBUG(F("Starting HC12 setup"));

  SBB_DEBUG(F("Setting set pin LOW"));
  digitalWrite(options_.set_pin, LOW);  // Enter setup mode
  delay(250);                           // As per datasheet

  char buf[20];
  SBB_DEBUG(F("Setting default settings"));
  sprintf(buf, "AT+DEFAULT");
  if (!ConfigureParameter(buf)) {
    SBB_DEBUG(F("Setting pin HIGH"));
    digitalWrite(options_.set_pin, HIGH);  // Exit setup mode
    return false;
  }

  SBB_DEBUG(F("Configuring channel"));
  sprintf(buf, "AT+C%03hu", channel);
  if (!ConfigureParameter(buf)) {
    SBB_DEBUG(F("Setting pin HIGH"));
    digitalWrite(options_.set_pin, HIGH);  // Exit setup mode
    return false;
  }

  SBB_DEBUG(F("Setting pin HIGH"));
  digitalWrite(options_.set_pin, HIGH);  // Exit setup mode
  delay(250);                            // As per datasheet

  channel_ = channel;  // Acknowledge channel set
  SBB_DEBUG(F("Finished HC12 setup"));

  return true;
}

void Hc12AntennaHw::Write(Span message) {
  serial_.write(message.buffer, message.length);
  serial_.write((uint8_t)0);
  serial_.flush();
}

bool Hc12AntennaHw::IsReadAvailable() { return serial_.available(); }

Span Hc12AntennaHw::ReadBytesUntil(char character) {
  const int len =
      serial_.readBytesUntil(character, rx_buffer_, sizeof(rx_buffer_));
  return Span{.buffer = rx_buffer_, .length = len};
}

}  // namespace sbb
