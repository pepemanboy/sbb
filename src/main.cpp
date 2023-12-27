#include <Arduino.h>
#include "apps/sumitomo_sensor/sensor.h"

using App = sbb::sumitomo_sensor::Sensor;

App app = {};

void setup() {
  app.Setup();
}

void loop() {
  app.Poll();
}
