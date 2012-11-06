#include "value.h"
#include "future.h"

namespace rtm {
namespace rpc {

Value::Value() {
  status = kCallSuccess;
}

void Value::writeHeader(Encoder* e) {
  e->write<uint32_t>(status);
  if (status != kCallSuccess) {
    Log_Assert(!errorTrace_.empty(), "Call failed but no error recorded!");
    marshal::write(e, errorTrace_);
  } else {
    Log_Assert(errorTrace_.empty(), "Call succeeded but trace attached?");
  }
}

void Value::propagateError(const Future& f) {
  Log_Assert(!f.errorTrace.empty(), "Future in error state, but no call stack!");
  for (size_t i = 0; i < f.errorTrace.size(); ++i) {
    errorTrace_.push_back(f.errorTrace[i]);
  }
  char hostnameBuffer[1024];
  gethostname(hostnameBuffer, 1024);
  Log_Info("Propagating error: %s", errorTrace_.back().msg.c_str());
  errorTrace_.push_back(RPCError("forwarded"));
  status = kCallError;
}

void Value::setError(const std::string& msg) {
  Log_Info("Returning error: %s", msg.c_str());
  errorTrace_.push_back(RPCError(msg));
  status = kCallError;
}

void Value::setOutdated(const std::string& msg) {
  Log_Info("Returning outdated: %s", msg.c_str());
  errorTrace_.push_back(RPCError(msg));
  status = kCallOutdated;
}

} // namespace rpc
} // namespace rtm
