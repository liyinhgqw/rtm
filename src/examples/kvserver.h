#ifndef KVSERVER_H_
#define KVSERVER_H_

#include <string>
#include "rpc/pserver.h"
#include "kv.pb.h"

namespace rtm {
namespace rpc {

class Get: public MethodBase {
public:
  virtual Message* new_request_msg() {
    return new GetRequest;
    return 0;
  }
  virtual Message* new_response_msg() {
    return new GetResponse;
    return 0;
  }
  virtual void run(Message* request_, Message* response_) {
    GetRequest *request;
    GetResponse *response;
    request = dynamic_cast<GetRequest*>(request_);
    response = dynamic_cast<GetResponse*>(response_);
    std::string key = request->key();
    std::string value = "hello " + key + " !";
    response->set_value(value);
  }
};

} // namespace rpc
} // namespace rtm
#endif /* KVSERVER_H_ */
