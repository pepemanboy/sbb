#include <Arduino.h>

#include "drivers/gpio.h"
#include "drivers/console.h"
#include "drivers/clock.h"

#include "common/debounce.h"
#include "common/time_converter.h"

namespace sbb {
namespace {

constexpr GpioPin kInductiveSensor = {
    .mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 21};
constexpr GpioPin kQrSensorReading = {
    .mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveHigh, .pin = 20};
constexpr GpioPin kQrSensorTrigger = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 2};

bool sensor_interrupt_triggered_ = false;
void SensorInterruptCallback() { sensor_interrupt_triggered_ = true; }
bool GetAndMaybeClearSensorInterrupt() {
  if (!sensor_interrupt_triggered_) return false;
  sensor_interrupt_triggered_ = false;
  return true;
}

Debounce debounce_{};
TimeConverter time_{};

}  // namespace

void setup() { 
  void ConsoleInit();
  GpioConfigure(kInductiveSensor);
  GpioConfigure(kQrSensorReading);
  GpioConfigure(kQrSensorTrigger);
  GpioAttachInterrupt(kInductiveSensor, GpioInterruptTrigger::kFallingEdge,
                      SensorInterruptCallback);
}

void loop() {
  const int64_t now_micros = time_.Update(ClockMicros());

  const bool inductive_sensor_reading = 
    GetAndMaybeClearSensorInterrupt() || GpioGet(kInductiveSensor);
  const bool debounced_inductive_sensor_reading = 
    debounce_.Poll(inductive_sensor_reading, now_micros);

  GpioSet(kQrSensorTrigger, debounced_inductive_sensor_reading);
  if (debounced_inductive_sensor_reading) {
    ConsolePrintF("Sensor Inductivo detectado");
  }

  if (GpioGet(kQrSensorReading)) {
    ConsolePrintF("Codigo QR detectado");
  }
  
  delay(10);
}

}  // namespace sbb
