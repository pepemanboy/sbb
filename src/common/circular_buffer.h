#ifndef SBB_COMMON_CIRCULAR_BUFFER_H
#define SBB_COMMON_CIRCULAR_BUFFER_H

namespace sbb {

template <typename T, int Size>
class CircularBuffer {
 public:
  CircularBuffer() = default;

  int AvailablePop() const {
    int available = head_ - tail_;
    if (available < 0) {
      available += Size;
    }
    return available;
  }

  const T& Peek() const { return buffer_[tail_]; }

  T Pop() {
    if (AvailablePop() > 0) {
      T ret = buffer_[tail_];
      ++tail_;
      if (tail_ >= Size) {
        tail_ = 0;
      }
      return ret;
    }
    return {};
  }

  void PushAndMaybeEvict(const T& element) {
    buffer_[head_] = element;
    ++head_;
    if (head_ >= Size) {
      head_ = 0;
    }
    if (head_ == tail_) {
      ++tail_;
      if (tail_ >= Size) {
        tail_ = 0;
      }
    }
  }

 private:
  T buffer_[Size] = {};
  int head_ = 0;
  int tail_ = 0;
};

}  // namespace sbb

#endif  // SBB_COMMON_CIRCULAR_BUFFER_H
