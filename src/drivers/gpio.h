#ifndef SBB_DRIVERS_GPIO_H
#define SBB_DRIVERS_GPIO_H

namespace sbb {

enum class GpioMode {
  kInput,
  kOutput,
};

enum class GpioPolarity {
  kActiveHigh,
  kActiveLow,
};

struct GpioPin {
  GpioMode mode;
  GpioPolarity polarity;
  int pin;
};

void GpioConfigure(const GpioPin &gpio);

void GpioSet(const GpioPin &gpio, bool state);

bool GpioGet(const GpioPin &gpio);

}  // namespace sbb

#endif  // SBB_DRIVERS_GIPO_H
