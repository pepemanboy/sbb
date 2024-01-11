#ifndef SBB_COMMON_RISING_EDGE_DETECTOR_H
#define SBB_COMMON_RISING_EDGE_DETECTOR_H

namespace sbb {

class RisingEdgeDetector {
 public:
  RisingEdgeDetector() = default;

  bool Update(bool state) {
    const bool rising_edge_detected = state && !last_state_;
    last_state_ = state;
    return rising_edge_detected;
  }

 private:
  bool last_state_ = false;
};

}  // namespace sbb

#endif  // SBB_COMMON_RISING_EDGE_DETECTOR_H
