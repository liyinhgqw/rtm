#include "client.h"
#include "connection.h"

namespace rtm {
namespace rpc {

void Client::connect() {
  connection_ = Connection::create(endpoint_);
  Log_Debug("client connection setup !");
  Log_Assert(connection_ != NULL, "connect null");
}

Client::Client() :
    connection_(NULL) {
}

Future* Client::send(Future* result, util::StringPiece method, util::StringPiece args) {
  if (connection_ == NULL) {
    connect();
  }
  Log_Info("Sending request for method %s", method.str().c_str());
  connection_->send(result, method, args);
  return result;
}

void Client::reset(const Endpoint& endpoint, util::StringPiece service) {
  endpoint_ = endpoint;
  serviceType_ = service.str();
}

const Endpoint& Client::endpoint() const {
  return endpoint_;
}


}
}
