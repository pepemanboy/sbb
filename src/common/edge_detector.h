#ifndef SBB_COMMON_EDGE_DETECTOR_H
#define SBB_COMMON_EDGE_DETECTOR_H

namespace sbb {

class EdgeDetector {
 public:
  enum class EdgeType {
    kNoEdge,
    kRisingEdge,
    kFallingEdge,
  };

  EdgeDetector() = default;

  EdgeType Update(bool state) {
    if (last_state_ != state) {
      last_state_ = state;
      return state ? EdgeType::kRisingEdge : EdgeType::kFallingEdge;
    }

    return EdgeType::kNoEdge;
  }

 private:
  bool last_state_ = false;
};

}  // namespace sbb

#endif  // SBB_COMMON_EDGE_DETECTOR_H
