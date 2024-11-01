#ifndef SBB_DRIVERS_GPIO_H
#define SBB_DRIVERS_GPIO_H

namespace sbb {

typedef void (*GpioInterruptCallback)();

enum class GpioMode {
  kInput,
  kOutput,
  kInputPullUp,
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

enum class GpioInterruptTrigger {
  kLow,
  kChange,
  kRisingEdge,
  kFallingEdge,
  kHigh,
};

void GpioConfigure(const GpioPin &gpio);

void GpioSet(const GpioPin &gpio, bool state);

bool GpioGet(const GpioPin &gpio);

void GpioAttachInterrupt(const GpioPin &gpio, GpioInterruptTrigger trigger,
                         GpioInterruptCallback callback);

}  // namespace sbb

#endif  // SBB_DRIVERS_GIPO_H
