#ifndef SBB_DRIVERS_DEBUG_ARDUINO_H
#define SBB_DRIVERS_DEBUG_ARDUINO_H

#include <Arduino.h>

namespace sbb {

class DebugSingleton {
 public:
  DebugSingleton(DebugSingleton const&) = delete;
  void operator=(DebugSingleton const&) = delete;

  static DebugSingleton& getInstance() {
    static DebugSingleton instance;
    return instance;
  }

  void EnableDebug(bool enable) {
    if (enable) {
      Serial.begin(9600);
    } else {
      Serial.end();
    }
    is_debug_enabled_ = enable;
  }

  bool is_debug_enabled() { return is_debug_enabled_; }

 private:
  DebugSingleton() {}

  bool is_debug_enabled_ = false;
};

#define SBB_DEBUG_ENABLE()                           \
  do {                                               \
    DebugSingleton::getInstance().EnableDebug(true); \
  } while (0)

#define SBB_DEBUG(x)                                        \
  do {                                                      \
    if (DebugSingleton::getInstance().is_debug_enabled()) { \
      Serial.println(x);                                    \
    }                                                       \
  } while (0)

}  // namespace sbb

#endif  // SBB_DRIVERS_DEBUG_ARDUINO_H
