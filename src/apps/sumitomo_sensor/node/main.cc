#include <Arduino.h>
#include "apps/sumitomo_sensor/node/node.h"

using App = sbb::sumitomo_sensor::node::Node;

App app = {};

void setup() {
  app.Setup();
}

void loop() {
  app.Poll();
}
