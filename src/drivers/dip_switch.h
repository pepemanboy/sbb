#ifndef SBB_COMMON_DIP_SWITCH
#define SBB_COMMON_DIP_SWITCH

namespace sbb {

constexpr int kDipSwitchMaxPins = 10;

enum class DipSwitchPolarity {
  kActiveHigh,
  kActiveLow,
};

struct DipSwitchPins {
  DipSwitchPolarity polarity;
  int pins[kDipSwitchMaxPins];
  int number_of_pins;
};

void DipSwitchConfigure(const DipSwitchPins &dip);

bool DipSwitchGetIndex(const DipSwitchPins &dip, int index);

int DipSwitchGet(const DipSwitchPins &dip);

}  // namespace sbb

#endif  // SBB_COMMON_DIP_SWITCH
