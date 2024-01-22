#include "drivers/hc12_antenna_arduino.h"

#include <Arduino.h>

#include "common/span.h"
#include "common/status.h"
#include "drivers/debug_arduino.h"

namespace sbb {
namespace {

constexpr int kDefaultBaudRate = 9600;
constexpr int kSerialTimeout_ms = 1000;
constexpr int kMaxSetupRetries = 3;

}  // namespace

Status Hc12Antenna::ConfigureParameter(char *query) {
  SBB_DEBUG(query);
  hc12_serial_.println(query);
  hc12_serial_.flush();

  const size_t l = hc12_serial_.readBytes(rx_buffer_, sizeof(rx_buffer_));
  rx_buffer_[l] = '\0';
  SBB_DEBUG((char *)rx_buffer_);

  if (!strstr((char *)rx_buffer_, "OK")) {
    SBB_DEBUG(F("Error configuring parameter"));
    return Status::kError;
  }
  return Status::kOk;
}

Status Hc12Antenna::Setup(int channel) {
  hc12_serial_.setTimeout(kSerialTimeout_ms);
  hc12_serial_.begin(kDefaultBaudRate);

  int retries = 0;
  while (SetupOneTime(channel) != Status::kOk) {
    if (retries++ > kMaxSetupRetries) {
      SBB_DEBUG(F("Could not configure"));
      return Status::kError;
    } else {
      SBB_DEBUG(F("Retrying"));
    }
  }
  return Status::kOk;
}

Status Hc12Antenna::SetupOneTime(int channel) {
  Status status;

  pinMode(options_.set_pin, OUTPUT);
  pinMode(options_.rx_pin, INPUT);
  pinMode(options_.tx_pin, OUTPUT);
  delay(250);

  SBB_DEBUG(F("Starting HC12 setup"));

  SBB_DEBUG(F("Setting set pin LOW"));
  digitalWrite(options_.set_pin, LOW);  // Enter setup mode
  delay(250);                           // As per datasheet

  char buf[20];
  SBB_DEBUG(F("Setting default settings"));
  sprintf(buf, "AT+DEFAULT");
  status = ConfigureParameter(buf);
  if (status != Status::kOk) {
    SBB_DEBUG(F("Setting pin HIGH"));
    digitalWrite(options_.set_pin, HIGH);  // Exit setup mode
    return status;
  }

  SBB_DEBUG(F("Configuring channel"));
  sprintf(buf, "AT+C%03hu", channel);
  status = ConfigureParameter(buf);
  if (status != Status::kOk) {
    SBB_DEBUG(F("Setting pin HIGH"));
    digitalWrite(options_.set_pin, HIGH);  // Exit setup mode
    return status;
  }

  SBB_DEBUG(F("Setting pin HIGH"));
  digitalWrite(options_.set_pin, HIGH);  // Exit setup mode
  delay(250);                            // As per datasheet

  channel_ = channel;  // Acknowledge channel set
  SBB_DEBUG(F("Finished HC12 setup"));

  return Status::kOk;
}

void Hc12Antenna::Write(Span message) {
  hc12_serial_.write(message.buffer, message.length);
  hc12_serial_.write((uint8_t)0);
  hc12_serial_.flush();
}

bool Hc12Antenna::IsReadAvailable() { return hc12_serial_.available(); }

Span Hc12Antenna::ReadBytesUntil(char character) {
  const int len =
      hc12_serial_.readBytesUntil(character, rx_buffer_, sizeof(rx_buffer_));
  return Span{.buffer = rx_buffer_, .length = len};
}

}  // namespace sbb
