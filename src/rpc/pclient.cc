#include "pclient.h"

namespace rtm {
namespace rpc {

bool PClient::call(util::StringPiece method, Message &request, Message &response) {
  std::string request_str, response_str;
  request.SerializeToString(&request_str);
  Future* f = invoke(method, util::StringPiece(request_str));
  if (!f) return false;
  RawFuture *rf = dynamic_cast<RawFuture*>(f);
  response.ParseFromString(rf->results());    // wait for the result
  delete f;

  return true;
}

Future* PClient::invoke(util::StringPiece method, util::StringPiece args) {
  Future *f = new RawFuture();
  send(f, method, args);
  Log_Debug("Request: %s", dynamic_cast<RawFuture*>(f)->to_str().c_str());
  return f;
}

} // namespace rpc
} // namespacd rtm
