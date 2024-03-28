#include <Arduino.h>

#include "apps/sumitomo_sensor/node_v2/node.h"

using App = sbb::sumitomo_sensor::node_v2::Node;

App app = {};

void setup() { app.Setup(); }

void loop() { app.Poll(); }
