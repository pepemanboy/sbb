#ifndef SBB_DRIVERS_DEBUG_ARDUINO_H
#define SBB_DRIVERS_DEBUG_ARDUINO_H

#include <Arduino.h>

#include "drivers/console.h"

namespace sbb {
namespace debug_internal {

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
      ConsoleInit();
    } else {
      ConsoleClose();
    }
    is_debug_enabled_ = enable;
  }

  bool is_debug_enabled() { return is_debug_enabled_; }

 private:
  DebugSingleton() {}

  bool is_debug_enabled_ = false;
};

}  // namespace debug_internal
}  // namespace sbb

#define SBB_DEBUG_ENABLE()                                                \
  do {                                                                    \
    sbb::debug_internal::DebugSingleton::getInstance().EnableDebug(true); \
  } while (0)

#define SBB_DEBUG(x)                                       \
  do {                                                     \
    if (sbb::debug_internal::DebugSingleton::getInstance() \
            .is_debug_enabled()) {                         \
      Serial.println(x);                                   \
    }                                                      \
  } while (0)

#define SBB_DEBUGF(...)                                    \
  do {                                                     \
    if (sbb::debug_internal::DebugSingleton::getInstance() \
            .is_debug_enabled()) {                         \
      ConsolePrintF(__VA_ARGS__);                           \
    }                                                      \
  } while (0)

#endif  // SBB_DRIVERS_DEBUG_ARDUINO_H
