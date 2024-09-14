#ifndef SBB_PROTO_QR_H
#define SBB_PROTO_QR_H

#include "common/debounce.h"
#include "common/timer.h"
#include "common/time_converter.h"

namespace sbb {
namespace proto_qr {

class ProtoQr {
 public:
  ProtoQr();

  void Setup();
  void Poll();

 private:
  TimeConverter time_ = {};
  Timer debug_timer_;  // Init in constructor.
  Debounce inductive_sensor_debounce_;  // Init in constructor.
};

}  // namespace proto_qr
}  // namespace sbb

#endif  // SBB_PROTO_QR_H
