#include <Arduino.h>

#include "apps/proto_qr/proto_qr.h"

using App = sbb::proto_qr::ProtoQr;

App app = {};

void setup() { app.Setup(); }

void loop() { app.Poll(); }
