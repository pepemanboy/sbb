#include <Arduino.h>

#include "drivers/gpio.h"
#include "drivers/console.h"

namespace sbb {
namespace {

constexpr GpioPin kInductiveSensor = {
    .mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 21};
constexpr GpioPin kQrSensorReading = {
    .mode = GpioMode::kInput, .polarity = GpioPolarity::kActiveLow, .pin = 20};
constexpr GpioPin kQrSensorTrigger = {
    .mode = GpioMode::kOutput, .polarity = GpioPolarity::kActiveLow, .pin = 2};

bool sensor_interrupt_triggered_ = false;
void SensorInterruptCallback() { sensor_interrupt_triggered_ = true; }
bool GetAndMaybeClearSensorInterrupt() {
  if (!sensor_interrupt_triggered_) return false;
  sensor_interrupt_triggered_ = false;
  return true;
}

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
  if (GetAndMaybeClearSensorInterrupt() || GpioGet(kInductiveSensor)) {
    ConsolePrintF("Sensor Inductivo detectado");
  }
  
  delay(1000);
}

}  // namespace sbb
