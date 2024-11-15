#include <Arduino.h>

#include "apps/sumitomo_sensor/node_v3/node.h"

using App = sbb::sumitomo_sensor::node_v3::Node;

App app = {};

void setup() { app.Setup(); }

void loop() { app.Poll(); }
