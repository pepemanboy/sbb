#include <Arduino.h>

#include "drivers/console.h"

namespace sbb {

void ConsoleInit() { Serial.begin(9600); }

void ConsoleClose() { Serial.end(); }

void ConsolePrintF(const char* format, ...) {
  char buf[80];
  va_list args;
  va_start(args, format);
  vsprintf(buf, format, args);
  Serial.println(buf);
  Serial.flush();
  va_end(args);
}

}  // namespace sbb
