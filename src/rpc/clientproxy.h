#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "client.h"

#include <google/protobuf/message.h>
#include <list>
#include <string>

namespace rtm {
namespace rpc {

using namespace google::protobuf;

class ClientProxy {
public:
  static ClientProxy* create(std::string);
  virtual bool call(std::string, Message&, Message&) = 0;
protected:
  std::list<Client*> client_list_;
};

}  // namespace rpc
}  // namespace rtm

#endif /* CLIENTPROXY_H_ */
