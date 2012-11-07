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

bool PClient::call_truetime(double& peertime) {
  Log_Debug("Call truetime.");
  Future* f = invoke("", "");
  if (!f) return false;
  RawFuture *rf = dynamic_cast<RawFuture*>(f);
  rf->results();    // wait for the result
  peertime = rf->peertime;
  Log_Debug("Call truetime done.");
  return true;
}

Future* PClient::invoke(util::StringPiece method, util::StringPiece args) {
  Future *f = new RawFuture();
  send(f, method, args);
  return f;
}

} // namespace rpc
} // namespacd rtm
