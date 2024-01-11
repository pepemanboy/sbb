#include <Arduino.h>

#include "apps/sumitomo_sensor/receiver/receiver.h"

using App = sbb::sumitomo_sensor::receiver::Receiver;

App app = {};

void setup() { app.Setup(); }

void loop() { app.Poll(); }
