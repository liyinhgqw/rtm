#ifndef RTM_VALUE_H_
#define RTM_VALUE_H_

#include <string>
#include <vector>

#include "util/marshal.h"
#include "util/string.h"

#include "rpc/connection.h"
#include "rpc/future.h"

namespace rtm {
namespace rpc {

class Value {
public:
  Value();

  // Write the serialized form of this value to 'e'.
  virtual void write(Encoder *e) = 0;

  void propagateError(const Future& f);
  void setError(const std::string& msg);

  CallStatus status;
protected:
  std::vector<RPCError> errorTrace_;
  void writeHeader(Encoder* e);
};

template<class T>
class ValueT: public Value {
protected:
public:
  T value;

  void write(Encoder* e);
};

template<class T>
inline void ValueT<T>::write(Encoder* e) {
  writeHeader(e);
  if (status == kCallSuccess) {
    marshal::write(e, value);
  }
}

template<>
class ValueT<void> : public Value {
public:
  void write(Encoder* e) {
    writeHeader(e);
  }
};


} // namespace rpc
} // namespace rtm

#endif /* RTM_VALUE_H_ */
