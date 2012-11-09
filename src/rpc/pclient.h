#ifndef PCLIENT_H_
#define PCLIENT_H_

#include <string>
#include <google/protobuf/message.h>
#include "util/common.h"
#include "util/logging.h"
#include "util/string.h"
#include "rpc/client.h"
#include "rpc/future.h"


namespace rtm {
namespace rpc {

using namespace google::protobuf;

class PClient: public Client {
public:
  PClient(const Endpoint& info, util::StringPiece service): Client(info, service) {}
  virtual bool call(util::StringPiece method, Message &request, Message &response);
  virtual bool raw_call(util::StringPiece method, std::string &request, std::string &response);
  virtual bool call_truetime(double&);
  virtual Future* invoke(util::StringPiece method, util::StringPiece args);
  bool run() {return true;}
};

} // namespace rpc
} // namespace rtm

#endif /* PCLIENT_H_ */

