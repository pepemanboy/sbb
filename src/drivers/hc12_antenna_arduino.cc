#include "drivers/hc12_antenna_arduino.h"

#include "Arduino.h"
#include "common/span.h"
#include "common/status.h"
#include "drivers/debug_arduino.h"

namespace sbb {
namespace {

constexpr int kDefaultBaudRate = 9600;
constexpr int kSerialTimeout_ms = 1000;
constexpr int kMaxSetupRetries = 10;

}  // namespace

Status Hc12Antenna::ConfigureParameter(char *query) {
  hc12_serial_.println(query);
  SBB_DEBUG(query);
  size_t l = hc12_serial_.readBytes(rx_buffer_, sizeof(rx_buffer_));
  hc12_serial_.flush();
  rx_buffer_[l] = '\0';
  SBB_DEBUG((char *)rx_buffer_);
  if (!strstr((char *)rx_buffer_, "OK")) return Status::kError;
  return Status::kOk;
}

Status Hc12Antenna::Setup(int channel) {
  hc12_serial_.setTimeout(kSerialTimeout_ms);
  hc12_serial_.begin(kDefaultBaudRate);

  int retries = 0;
  while (SetupOneTime(channel) != Status::kOk) {
    SBB_DEBUG((char *)"Retrying");
    if (retries++ > kMaxSetupRetries) return Status::kError;
  }
  return Status::kOk;
}

Status Hc12Antenna::SetupOneTime(int channel) {
  Status status;
  pinMode(options_.set_pin, OUTPUT);
  pinMode(options_.rx_pin, INPUT);
  pinMode(options_.tx_pin, OUTPUT);

  SBB_DEBUG((char *)"Starting HC12 setup");

  SBB_DEBUG((char *)"Setting set pin LOW");
  digitalWrite(options_.set_pin, LOW);  // Enter setup mode
  delay(250);                           // As per datasheet

  char buf[20];

  SBB_DEBUG((char *)"Configuring channel");
  sprintf(buf, "AT+C%03hu", channel);
  status = ConfigureParameter(buf);
  if (status != Status::kOk) return status;

  SBB_DEBUG((char *)"Setting pin HIGH");
  digitalWrite(options_.set_pin, HIGH);  // Exit setup mode
  delay(250);                            // As per datasheet

  channel_ = channel;  // Acknowledge channel set
  SBB_DEBUG((char *)"Finished HC12 setup");

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
