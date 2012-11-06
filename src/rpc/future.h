#ifndef RTM_FUTURE_H_
#define RTM_FUTURE_H_

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

#include "util/common.h"
#include "util/logging.h"
#include "util/marshal.h"
#include "exceptions.h"

namespace rtm {
namespace rpc {

enum CallStatus {
  kCallPending = 0, kCallSuccess = 1, kCallTimedOut = 2, kCallError = 3, kCallOutdated = 4
};

class Connection;

class Future: private boost::noncopyable {
protected:
  // The absolute time (on the local machine) by which this future must
  // be completed.
  double deadline_;

public:
  Connection* connection;
  int64_t id;

  CallStatus status;
  std::vector<RPCError> errorTrace;

  double peertime;

  Future();
  virtual ~Future();

  double timeLeft() {
    if (deadline_ < 0) {
      return 1e9;
    }
    return deadline_ - util::Now();
  }

  virtual void read(util::StringPiece) = 0;

  void init(Connection* socket, int64_t id);
  void wait();
  void readHeader(Decoder* d);
};

// Used for protobuf
class RawFuture: public Future {
public:
  RawFuture() { data = ""; }
  void read(util::StringPiece ret) {
    Log_Debug("RawFuture read ... ");
    Decoder d(ret);
    this->readHeader(&d);
    if (status == kCallSuccess) {
      if (!d.done()) d.read(&data);   // should always check before read
    } else {
      throw new rpc_exception;
    }
  }
  std::string to_str() {
    return data;
  }
  std::string results() {
    wait();
    return data;
  }

private:
  std::string data;
};

template<class T>
class AbstractFuture: public Future {
public:
  virtual const T& value() = 0;
};

template<>
class AbstractFuture<void> : public Future {

};

template<class T>
class ConstFuture: public AbstractFuture<T> {
private:
  T value_;
public:
  ConstFuture(const T& v) {
    value_ = v;
    this->status = kCallSuccess;
    this->waitedFor_ = true;
  }

  void wait() {
  }

  const T& value() {
    return value_;
  }

  void read(util::StringPiece) {
  }
};

class VoidFuture: public AbstractFuture<void> {
public:
  void read(util::StringPiece data) {
    Decoder d(data);
    this->readHeader(&d);
  }
};

template<class T>
AbstractFuture<T>* make_const(const T& v) {
  return new ConstFuture<T>(v);
}

} // namespace rpc
} // namespace rtm

#endif /* RTM_FUTURE_H_ */
