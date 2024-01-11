#ifndef SBB_COMMON_MAYBE_VALID_H
#define SBB_COMMON_MAYBE_VALID_H

namespace sbb {

template <typename T>
struct MaybeValid {
  bool valid;
  T value;
};

template <typename T>
MaybeValid<T> MakeMaybeValid(const T &value, bool valid) {
  return {valid, value};
}

template <typename T>
MaybeValid<T> MakeValid(const T &value) {
  return MakeMaybeValid(value, true);
}

template <typename T>
MaybeValid<T> MakeInvalid(const T &value) {
  return MakeMaybeValid(value, false);
}

}  // namespace sbb

#endif  // SBB_COMMON_MAYBE_VALID_H