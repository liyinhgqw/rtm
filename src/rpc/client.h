#ifndef RTM_CLIENT_H_
#define RTM_CLIENT_H_

#include <boost/noncopyable.hpp>
#include <string>

#include "rpc/connection.h"
#include "util/marshal.h"
#include "util/string.h"

namespace rtm {
namespace rpc {

class Future;

class Request {
public:
  util::StringPiece serializedArgs;
  util::StringPiece currentMethod;
  double timeout;
};

class Client: public Serializable, private boost::noncopyable {
protected:
  Endpoint endpoint_;
  std::string serviceType_;
  Connection* connection_;

  void connect();
public:
  Client();
  Client(const Endpoint& info, util::StringPiece service) : connection_(NULL) {
    reset(info, service);
  }
  Future* send(Future* result, util::StringPiece method, util::StringPiece args);
  void reset(const Endpoint& info, util::StringPiece service);
  virtual Future* invoke(util::StringPiece method, util::StringPiece args) = 0;

  const Endpoint& endpoint() const;


  void write(Encoder *e) const {
    marshal::write(e, endpoint());
  }

  void read(Decoder *d) {
    marshal::read(d, &endpoint_);
    reset(endpoint_, serviceType_);
  }
};

} // namespace rpc
} // namespace rtm

#endif /* RTM_CLIENT_H_ */
