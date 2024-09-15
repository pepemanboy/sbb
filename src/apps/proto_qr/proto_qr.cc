#include "apps/proto_qr/proto_qr.h"

#include <Arduino.h>

#include "common/debounce.h"
#include "common/time_converter.h"
#include "common/timer.h"
#include "drivers/clock.h"
#include "drivers/console.h"
#include "drivers/gpio.h"

namespace sbb {
namespace proto_qr {
namespace {

constexpr GpioPin kInductiveSensor = {.mode = GpioMode::kInputPullUp,
                                      .polarity = GpioPolarity::kActiveLow,
                                      .pin = 21};
constexpr GpioPin kQrSensorReading = {.mode = GpioMode::kInputPullUp,
                                      .polarity = GpioPolarity::kActiveLow,
                                      .pin = 20};
constexpr GpioPin kQrSensorTrigger = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 2};

constexpr int64_t kInductiveSensorDebounceMicros = 500000;  // 500ms.

bool sensor_interrupt_triggered_ = false;
void SensorInterruptCallback() { sensor_interrupt_triggered_ = true; }
bool GetAndMaybeClearSensorInterrupt() {
  if (!sensor_interrupt_triggered_) return false;
  sensor_interrupt_triggered_ = false;
  return true;
}

}  // namespace

ProtoQr::ProtoQr()
    : debug_timer_(500000),
      inductive_sensor_debounce_(kInductiveSensorDebounceMicros) {}

void ProtoQr::Setup() {
  ConsoleInit();
  GpioConfigure(kInductiveSensor);
  GpioConfigure(kQrSensorReading);
  GpioConfigure(kQrSensorTrigger);
  GpioAttachInterrupt(kInductiveSensor, GpioInterruptTrigger::kFallingEdge,
                      SensorInterruptCallback);
}

void ProtoQr::Poll() {
  const int64_t now_micros = time_.Update(ClockMicros());

  const bool inductive_sensor_reading =
      GetAndMaybeClearSensorInterrupt() || GpioGet(kInductiveSensor);
  const bool debounced_inductive_sensor_reading =
      inductive_sensor_debounce_.Poll(inductive_sensor_reading, now_micros);

  GpioSet(kQrSensorTrigger, debounced_inductive_sensor_reading);
  if (debounced_inductive_sensor_reading) {
    ConsolePrintF("Sensor Inductivo detectado");
  }

  if (GpioGet(kQrSensorReading)) {
    ConsolePrintF("Codigo QR detectado");
  }

  if (debug_timer_.Poll(now_micros)) {
    ConsolePrintF("Ok");
  }

  delay(10);
}

}  // namespace proto_qr
}  // namespace sbb
